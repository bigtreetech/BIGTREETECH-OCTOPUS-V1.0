/*
 * RTOS.cpp
 *
 *  Created on: 30 Mar 2018
 *      Author: David
 */

#include "RTOSIface.h"

#ifdef RTOS

# include "FreeRTOS.h"
# include "task.h"
# include "semphr.h"
# include <atomic>

static_assert(Mutex::TimeoutUnlimited == portMAX_DELAY, "Bad value for TimeoutUnlimited");

// Create the semaphore. A semaphore must only be created once. The name is not copied, so pName must point to read-only or persistent storage.
void Mutex::Create(const char *pName) noexcept
{
	xSemaphoreCreateRecursiveMutexStatic(this);
	name = pName;
	next = mutexList;
	mutexList = this;
}

// Take ownership of a mutex returning true if successful, false if timed out
bool Mutex::Take(uint32_t timeout) noexcept
{
	return xSemaphoreTakeRecursive(GetHandle(), timeout) == pdTRUE;
}

// Release a mutex returning true if successful.
// Note that the return value does not indicate whether the mutex is still owned, because it may have been taken more than once.
bool Mutex::Release() noexcept
{
	return xSemaphoreGiveRecursive(GetHandle()) == pdTRUE;
}

TaskBase *Mutex::GetHolder() const noexcept
{
	return reinterpret_cast<TaskBase *>(xSemaphoreGetMutexHolder(GetConstHandle()));
}

TaskBase *TaskBase::taskList = nullptr;
TaskBase::TaskId TaskBase::numTasks = 0;

Mutex *Mutex::mutexList = nullptr;

#else

void Mutex::Create(const char *pName) noexcept
{
}

bool Mutex::Take(uint32_t timeout) noexcept
{
	return true;
}

bool Mutex::Release() noexcept
{
	return true;
}

TaskHandle Mutex::GetHolder() const noexcept
{
	return nullptr;
}

#endif

MutexLocker::MutexLocker(Mutex *m, uint32_t timeout) noexcept
{
	handle = m;
	acquired =
#ifdef RTOS
				(m == nullptr) || m->Take(timeout);
#else
				true;
#endif
}

MutexLocker::MutexLocker(Mutex& m, uint32_t timeout) noexcept
{
	handle = &m;
	acquired =
#ifdef RTOS
				m.Take(timeout);
#else
				true;
#endif
}

// Release the lock early (non-counting)
void MutexLocker::Release() noexcept
{
#ifdef RTOS
	if (acquired)
	{
		if (handle != nullptr)
		{
			handle->Release();
		}
		acquired = false;
	}
#else
	acquired = false;
#endif
}

// Acquire it again, if it isn't already owned (non-counting)
bool MutexLocker::ReAcquire(uint32_t timeout) noexcept
{
#ifdef RTOS
	if (!acquired)
	{
		acquired = (handle == nullptr) || handle->Take(timeout);
	}
#else
	acquired = true;
#endif
	return acquired;
}

MutexLocker::~MutexLocker() noexcept
{
	Release();
}

#ifdef RTOS

BinarySemaphore::BinarySemaphore() noexcept
{
	 xSemaphoreCreateBinaryStatic(this);
}

bool BinarySemaphore::Take(uint32_t timeout) noexcept
{
	return xSemaphoreTake(GetHandle(), timeout);
}

bool BinarySemaphore::Give() noexcept
{
	return xSemaphoreGive(GetHandle());
}

// Link the task into the thread list and allocate a short task ID to it. Task IDs start at 1.
void TaskBase::AddToList() noexcept
{
	TaskCriticalSectionLocker lock;

	++numTasks;
	taskId = numTasks;
	next = taskList;
	taskList = this;
}

// Terminate a task and remove it from the thread list
void TaskBase::TerminateAndUnlink() noexcept
{
	if (taskId != 0)
	{
		taskId = 0;
		vTaskDelete(GetFreeRTOSHandle());

		// Unlink the task from the thread list
		TaskCriticalSectionLocker lock;
		for (TaskBase** tpp = &taskList; *tpp != nullptr; tpp = &(*tpp)->next)
		{
			if (*tpp == this)
			{
				*tpp = (*tpp)->next;
				break;
			}
		}
	}
}

// Wake up this task from an ISR
void TaskBase::GiveFromISR() noexcept
{
	if (taskId != 0)			// check that the task has been created and not terminated
	{
		BaseType_t higherPriorityTaskWoken = pdFALSE;
		vTaskNotifyGiveFromISR(GetFreeRTOSHandle(), &higherPriorityTaskWoken);
		portYIELD_FROM_ISR(higherPriorityTaskWoken);
	}
}

#endif

void ReadWriteLock::LockForReading() noexcept
{
#ifdef RTOS
	if (writeLockOwner != TaskBase::GetCallerTaskHandle())
	{
		for (;;)
		{
			uint8_t nr = numReaders;
			if (nr & 0x80)
			{
				vTaskDelay(1);					// delay while writing is pending or active
			}
			else if (numReaders.compare_exchange_strong(nr, nr + 1))
			{
				break;
			}
		}
	}
#endif
}

void ReadWriteLock::ReleaseReader() noexcept
{
#ifdef RTOS
	if (writeLockOwner != TaskBase::GetCallerTaskHandle())
	{
		--numReaders;
	}
#endif
}

void ReadWriteLock::LockForWriting() noexcept
{
#ifdef RTOS
	// First wait for other writers to finish, then grab the write lock
	for (;;)
	{
		uint8_t nr = numReaders;
		if (nr & 0x80)
		{
			vTaskDelay(1);					// delay while writing is pending or active
		}
		else if (numReaders.compare_exchange_strong(nr, nr | 0x80))
		{
			break;
		}
	}

	// Now wait for readers to finish
	while (numReaders != 0x80)
	{
		vTaskDelay(1);
	}

	writeLockOwner = TaskBase::GetCallerTaskHandle();
#endif
}

void ReadWriteLock::ReleaseWriter() noexcept
{
#ifdef RTOS
	if (writeLockOwner == TaskBase::GetCallerTaskHandle())
	{
		writeLockOwner = nullptr;
		numReaders = 0;
	}
	else if ((numReaders & 0x7F) != 0)
	{
		// We must have downgraded to a read lock
		--numReaders;
	}
#endif
}

void ReadWriteLock::DowngradeWriter() noexcept
{
#ifdef RTOS
	if (writeLockOwner == TaskBase::GetCallerTaskHandle())
	{
		numReaders = 1;
		writeLockOwner = nullptr;
	}
#endif
}

// End
