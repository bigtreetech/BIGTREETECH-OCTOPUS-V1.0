/*
 * freertos_tasks_c_additions.h
 *
 *  Created on: 6 Feb 2021
 *      Author: David
 *
 *  Extended task status function
 */

#include <freertos_task_additions.h>
#if defined(__LPC17xx__)
#if (configRECORD_STACK_HIGH_ADDRESS != 1)
# error configRECORD_STACK_HIGH_ADDRESS must be set to 1
#endif
volatile StackType_t *CheckSPCurrentTaskStack(const uint32_t *stackPointer)
{
    if(pxCurrentTCB == NULL || stackPointer == NULL) return NULL;
    if(stackPointer < pxCurrentTCB->pxStack || stackPointer > pxCurrentTCB->pxEndOfStack) return NULL; // stackPointer not in task stack
    return pxCurrentTCB->pxEndOfStack;
}
#endif

// This is similar to vTaskGetInfo() except that it returns a more detailed task state enumeration.
// Additionally, if the task is waiting for a resource (e.g. a mutex) then it passes back a pointer to that resource.
// Additionally, it clears the run-time counter.
void vTaskGetExtendedInfo( TaskHandle_t xTask, ExtendedTaskStatus_t *pxTaskStatus ) noexcept{
TCB_t *pxTCB;

	/* xTask is NULL then get the state of the calling task. */
	pxTCB = prvGetTCBFromHandle( xTask );

	pxTaskStatus->xHandle = ( TaskHandle_t ) pxTCB;
	pxTaskStatus->pcTaskName = ( const char * ) &( pxTCB->pcTaskName [ 0 ] );
	pxTaskStatus->uxCurrentPriority = pxTCB->uxPriority;
	pxTaskStatus->pxStackBase = pxTCB->pxStack;

	#if ( configUSE_MUTEXES == 1 )
	{
		pxTaskStatus->uxBasePriority = pxTCB->uxBasePriority;
	}
	#else
	{
		pxTaskStatus->uxBasePriority = 0;
	}
	#endif

	#if ( configGENERATE_RUN_TIME_STATS == 1 )
	{
		pxTaskStatus->ulRunTimeCounter = pxTCB->ulRunTimeCounter;
		pxTCB->ulRunTimeCounter = 0;	}
	#else
	{
		pxTaskStatus->ulRunTimeCounter = 0;
	}
	#endif

	pxTaskStatus->eCurrentState = eTaskGetExtendedState( pxTCB, &(pxTaskStatus->pvResource) );

	#if ( portSTACK_GROWTH > 0 )
	{
		pxTaskStatus->usStackHighWaterMark = prvTaskCheckFreeStackSpace( ( uint8_t * ) pxTCB->pxEndOfStack );
	}
	#else
	{
		pxTaskStatus->usStackHighWaterMark = prvTaskCheckFreeStackSpace( ( uint8_t * ) pxTCB->pxStack );
	}
	#endif
}

// This is like xTaskGetState except that it returns an extended status along with the identity of the resource it is waiting for
eExtendedTaskState eTaskGetExtendedState( TaskHandle_t xTask, const void **pvResource )
{
eExtendedTaskState eReturn;
List_t const * pxStateList, *pxDelayedList, *pxOverflowedDelayedList;
const TCB_t * const pxTCB = xTask;

	configASSERT( pxTCB );

	*pvResource = NULL;

	if( pxTCB == pxCurrentTCB )
	{
		/* The task calling this function is querying its own state. */
		eReturn = esRunning;
	}
	else
	{
		taskENTER_CRITICAL();
		{
			pxStateList = listLIST_ITEM_CONTAINER( &( pxTCB->xStateListItem ) );
			pxDelayedList = pxDelayedTaskList;
			pxOverflowedDelayedList = pxOverflowDelayedTaskList;
		}
		taskEXIT_CRITICAL();

		if( ( pxStateList == pxDelayedList ) || ( pxStateList == pxOverflowedDelayedList ) )
		{
			/* The task being queried is referenced from one of the Blocked lists. */
			if ( listLIST_ITEM_CONTAINER( &( pxTCB->xEventListItem ) ) != NULL )
			{
				*pvResource = listLIST_ITEM_CONTAINER( &( pxTCB->xEventListItem ) );
				eReturn = esResourceWaiting;
			}
			else if ( pxTCB->ucNotifyState == taskWAITING_NOTIFICATION )
			{
				eReturn = esNotifyWaiting;
			}
			else
			{
				eReturn = esDelaying;
			}
		}

		#if ( INCLUDE_vTaskSuspend == 1 )
			else if( pxStateList == &xSuspendedTaskList )
			{
				/* The task being queried is referenced from the suspended
				list.  Is it genuinely suspended or is it blocked
				indefinitely? */
				if( listLIST_ITEM_CONTAINER( &( pxTCB->xEventListItem ) ) == NULL )
				{
					#if( configUSE_TASK_NOTIFICATIONS == 1 )
					{
						/* The task does not appear on the event list item of
						and of the RTOS objects, but could still be in the
						blocked state if it is waiting on its notification
						rather than waiting on an object. */
						if ( pxTCB->ucNotifyState == taskWAITING_NOTIFICATION )
						{
							eReturn = esNotifyWaiting;
						}
						else
						{
							eReturn = esSuspended;
						}
					}
					#else
					{
						eReturn = esSuspended;
					}
					#endif
				}
				else
				{
					eReturn = esBlocked;
				}
			}
		#endif

		#if ( INCLUDE_vTaskDelete == 1 )
			else if( ( pxStateList == &xTasksWaitingTermination ) || ( pxStateList == NULL ) )
			{
				/* The task being queried is referenced from the deleted
				tasks list, or it is not referenced from any lists at
				all. */
				eReturn = esDeleted;
			}
		#endif

		else /*lint !e525 Negative indentation is intended to make use of pre-processor clearer. */
		{
			/* If the task is not in any other state, it must be in the
			Ready (including pending ready) state. */
			eReturn = esReady;
		}
	}

	return eReturn;
} /*lint !e818 xTask cannot be a pointer to const because it is a typedef. */
