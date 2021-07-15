/*
 * Duet3DAdditions.h
 *
 *  Created on: 6 Feb 2021
 *      Author: David
 */

#ifndef SRC_INCLUDE_FREERTOS_TASK_ADDITIONS_H_
#define SRC_INCLUDE_FREERTOS_TASK_ADDITIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
	esRunning = 0,		/* A task is querying the state of itself, so must be running. */
	esReady,			/* The task being queried is in a read or pending ready list. */
	esNotifyWaiting,	/* The task being queried is waiting for notification. */
	esResourceWaiting,	/* The task being queried is waiting for a resource (e.g. mutex) to become free. */
	esDelaying,			/* The task being queried is delaying. */
	esSuspended,		/* The task being queried is in the Suspended state, or is in the Blocked state with an infinite time out. */
	esBlocked,			/* The task is blocked indefinitely. */
	esDeleted,			/* The task being queried has been deleted, but its TCB has not yet been freed. */
	esInvalid			/* Used as an 'invalid state' value. */
} eExtendedTaskState;

/* Used with the uxTaskGetSystemState() function to return the state of each task
in the system. */
typedef struct xEXTENDED_TASK_STATUS
{
	TaskHandle_t xHandle;			/* The handle of the task to which the rest of the information in the structure relates. */
	const char *pcTaskName;			/* A pointer to the task's name.  This value will be invalid if the task was deleted since the structure was populated! */ /*lint !e971 Unqualified char types are allowed for strings and single characters only. */
	eExtendedTaskState eCurrentState;	/* The state in which the task existed when the structure was populated. */
	UBaseType_t uxCurrentPriority;	/* The priority at which the task was running (may be inherited) when the structure was populated. */
	UBaseType_t uxBasePriority;		/* The priority to which the task will return if the task's current priority has been inherited to avoid unbounded priority inversion when obtaining a mutex.  Only valid if configUSE_MUTEXES is defined as 1 in FreeRTOSConfig.h. */
	uint32_t ulRunTimeCounter;		/* The total run time allocated to the task so far, as defined by the run time stats clock.  See http://www.freertos.org/rtos-run-time-stats.html.  Only valid when configGENERATE_RUN_TIME_STATS is defined as 1 in FreeRTOSConfig.h. */
	StackType_t *pxStackBase;		/* Points to the lowest address of the task's stack area. */
	configSTACK_DEPTH_TYPE usStackHighWaterMark;	/* The minimum amount of stack space that has remained for the task since the task was created.  The closer this value is to zero the closer the task has come to overflowing its stack. */
	const void *pvResource;			/* The resource we are waiting one */
} ExtendedTaskStatus_t;

void vTaskGetExtendedInfo( TaskHandle_t xTask, ExtendedTaskStatus_t *pxTaskStatus ) noexcept;
eExtendedTaskState eTaskGetExtendedState( TaskHandle_t xTask, const void **pvResource ) noexcept;

#ifdef __cplusplus
}
#endif

#endif /* SRC_INCLUDE_FREERTOS_TASK_ADDITIONS_H_ */