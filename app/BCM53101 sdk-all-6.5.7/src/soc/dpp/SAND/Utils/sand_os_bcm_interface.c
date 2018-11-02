/* $Id: sand_os_bcm_interface.c,v 1.18 Broadcom SDK $
 * $Copyright: (c) 2016 Broadcom.
 * Broadcom Proprietary and Confidential. All rights reserved.$
*/



#include <shared/bsl.h>
#include <soc/dpp/drv.h>



#include <soc/dpp/SAND/Utils/sand_os_interface.h>
#include <soc/dpp/SAND/Utils/sand_integer_arithmetic.h>
#include <soc/dpp/SAND/Utils/sand_rand.h>

#include <sal/appl/io.h>
#include <sal/core/thread.h>

#include <shared/util.h>

#ifndef __KERNEL__
#include <time.h>
#endif

#ifdef VXWORKS
#include <tickLib.h>
#endif

#define SOC_SAND_OS_NOT_IMPLEMENTED /* sal_printf("*** %s:%d, %s: not implemented\n\r", __FILE__, __LINE__, FUNCTION_NAME()) */
#define SOC_SAND_OS_LNX_CHECK_0_ERR(_ret, _sand_ret, _str, _label) \
  do { \
    if (_ret != 0) \
    { \
      LOG_INFO(BSL_LS_BCM_COMMON, \
               (BSL_META("*** ERROR in %s:%d, %s: %s\n\r"), __FILE__, __LINE__, FUNCTION_NAME(), _str)); \
      _sand_ret = SOC_SAND_ERR; \
      goto _label; \
    } \
  } while (0)

int S_spl;

/*
 */
/*****************************************************
*NAME:
* soc_sand_os_qsort
*DATE:
* 30/JAN/2003
*FUNCTION:
*  This routine sorts an array of nmemb objects, the
*  initial element of which is pointed to by bot.
*  The size of each object is specified by size.
*  The contents of the array are sorted into ascending
*  order according to a comparison function pointed to
*  by compar, which is called with two arguments that
*  point to the objects being compared.
*  The function, compar, shall return an integer less
*  than, equal to, or greater than zero if the first
*  argument is considered to be respectively less than,
*  equal to, or greater than the second.
*INPUT:
*  SOC_SAND_DIRECT:
*    SOC_SAND_IN void *bot -
*      Initial element in array
*    SOC_SAND_IN uint32 nmemb -
*      No. of objects in array
*    SOC_SAND_IN uint32 size -
*      Size of one array element
*    SOC_SAND_IN int (* compar)(const void *,const void *) -
*      Comparison function
*  SOC_SAND_INDIRECT:
*    None.
*OUTPUT:
*  SOC_SAND_DIRECT:
*    None
*  SOC_SAND_INDIRECT:
*    Sorted array of objects.
*REMARKS:
* None
*SEE ALSO:
*****************************************************/
void
  soc_sand_os_qsort(
    void         *bot,
    uint32 nmemb,
    uint32 size,
    int (*compar)(void *, void *)
  )
{
  _shr_sort(bot, nmemb, size, compar);
  return ;
}

/*****************************************************
*NAME:
* soc_sand_os_bsearch
*DATE:
* 30/JAN/2003
*FUNCTION:
*  This routine searches an array of nmemb objects,
*  the initial element of which is pointed to by
*  base0, for an element that matches the object
*  pointed to by key. The size of each element of
*  the array is specified by size.
*
*  The comparison function pointed to by compar is
*  called with two arguments that point to the key
*  object and to an array element, in that order. The
*  function shall return an integer less than, equal
*  to, or greater than zero if the key object is
*  considered, respectively, to be less than, to
*  match, or to be greater than the array element.
*  The array shall consist of all the elements that
*  compare greater than the key object, in that order.
*INPUT:
*  SOC_SAND_DIRECT:
*    SOC_SAND_IN void *key -
*      Element to match
*    SOC_SAND_IN void *base0,
*      Initial element in array
*    SOC_SAND_IN uint32 nmemb -
*      No. of objects in array
*    SOC_SAND_IN uint32 size -
*      Size of one array element
*    SOC_SAND_IN int (* compar)(const void *,const void *) -
*      Comparison function
*  SOC_SAND_INDIRECT:
*    None.
*OUTPUT:
*  SOC_SAND_DIRECT:
*    void * -
*      A pointer to a matching element of the array,
*      or a NULL pointer if no match is found. If two
*      elements compare as equal, which element is
*      matched is unspecified.
*  SOC_SAND_INDIRECT:
*    Sorted array of objects.
*REMARKS:
* None
*SEE ALSO:
*****************************************************/
void
  *soc_sand_os_bsearch(
    void    *key,
    void    *base0,
    uint32  nmemb,
    uint32  size,
    int (*compar)(void *, void *)
    )
{
  void  *ret;
  int   idx;

  idx = _shr_bsearch(base0, nmemb, size, key, compar);

    if (idx > 0) {
        /* Found */
        ret = ((void *) &((char *)(base0))[(idx) * (size)]);
    } else {
        ret = NULL;
    }

  return (ret) ;
}
/*****************************************************
*NAME:
* soc_sand_os_task_lock
*DATE:
* 30/JAN/2003
*FUNCTION:
*  Disable task rescheduling.
*INPUT:
*  SOC_SAND_DIRECT:
*    None.
*  SOC_SAND_INDIRECT:
*    None.
*OUTPUT:
*  SOC_SAND_DIRECT:
*    int
*      If non SOC_SAND_OK then operation failed.
*  SOC_SAND_INDIRECT:
*    Stopped preemption and task context switching.
*REMARKS:
*  Preemption will not be unlocked until
*  soc_sand_os_task_unlock() has been called as many
*  times as soc_sand_os_task_lock().
*SEE ALSO:
*****************************************************/
SOC_SAND_RET
  soc_sand_os_task_lock(
    void
    )
{
  SOC_SAND_RET
  soc_sand_ret = SOC_SAND_OK;
  uint32 flags;

  soc_sand_ret = soc_sand_os_stop_interrupts(&flags);
  SOC_SAND_OS_LNX_CHECK_0_ERR(soc_sand_ret, soc_sand_ret, "soc_sand_os_stop_interrupts failed", exit);

exit:
  return soc_sand_ret;
}
/*****************************************************
*NAME:
* soc_sand_os_task_unlock
*DATE:
* 30/JAN/2003
*FUNCTION:
*  Enable task rescheduling.
*INPUT:
*  SOC_SAND_DIRECT:
*    None.
*  SOC_SAND_INDIRECT:
*    None.
*OUTPUT:
*  SOC_SAND_DIRECT:
*    int
*      If non SOC_SAND_OK then operation failed.
*  SOC_SAND_INDIRECT:
*    Re-enabled preemption and task context switching.
*    See remarks.
*REMARKS:
*  Preemption will not be unlocked until
*  soc_sand_os_task_unlock() has been called as many
*  times as soc_sand_os_task_lock(). When the lock count is
*  decremented to zero, any tasks that were eligible
*  to preempt the current task will execute.
*SEE ALSO:
*****************************************************/
SOC_SAND_RET
  soc_sand_os_task_unlock(
    void
    )
{
  SOC_SAND_RET
    soc_sand_ret = SOC_SAND_OK;
  uint32 flags = 0;

  soc_sand_ret = soc_sand_os_start_interrupts(flags);
  SOC_SAND_OS_LNX_CHECK_0_ERR(soc_sand_ret, soc_sand_ret, "soc_sand_os_start_interrupts failed", exit);

exit:
  return soc_sand_ret;
}

/*****************************************************
*NAME:
* soc_sand_os_malloc
*DATE:
* 27/AUG/2002
*FUNCTION:
*  interface to memory allocation
*INPUT:
*  SOC_SAND_DIRECT:
*    SOC_SAND_IN     uint32 size - size (in bytes) to allocate
*  SOC_SAND_INDIRECT:
*OUTPUT:
*  SOC_SAND_DIRECT:
*    NULL in case of an error
*  SOC_SAND_INDIRECT:
*    None.
*REMARKS:
* We apply a verification mechanism for every malloc - free call
* every allocated block is joint with a head & tail of 4 bytes.
* the head holds the size of the user allocated block (in bytes)
* the tail holds a known signature (0xABCDEF12)
*SEE ALSO:
* soc_sand_os_malloc_any_size
*****************************************************/
void
  *soc_sand_os_malloc(
    SOC_SAND_IN uint32 size,
    char *str
  )
{
  return sal_alloc(size, str);
}
/*
 */
/*****************************************************
*NAME:
* soc_sand_os_free
*DATE:
* 27/AUG/2002
*FUNCTION:
*  interface to memory de-allocation
*INPUT:
*  SOC_SAND_DIRECT:
*     SOC_SAND_INOUT  void          *memblock
*       memory address to deallocate
*  SOC_SAND_INDIRECT:
*OUTPUT:
*  SOC_SAND_DIRECT:
*   non_zero in case of an error
*  SOC_SAND_INDIRECT:
*    memblock is cleared
*REMARKS:
* We apply a verification mechanism for every malloc - free call
* every allocated block is joint with a head & tail of 4 bytes.
* the head holds the size of the user allocated block (in bytes)
* the tail holds a known signature (0xABCDEF12)
* in this method we check that preseding the address memblock,
* there is a head, and after size bytes there is a tail
* with our signature (ABCDEF12).
*SEE ALSO:
* soc_sand_os_free_any_size
*****************************************************/
SOC_SAND_RET
  soc_sand_os_free(
    SOC_SAND_INOUT  void  *memblock
  )
{
  sal_free(memblock);

  return SOC_SAND_OK;
}
/*****************************************************
*NAME:
* soc_sand_os_malloc_any_size
*DATE:
* 27/AUG/2002
*FUNCTION:
*  interface to memory allocation
*INPUT:
*  SOC_SAND_DIRECT:
*    SOC_SAND_IN     uint32 size - size (in bytes) to allocate
*  SOC_SAND_INDIRECT:
*OUTPUT:
*  SOC_SAND_DIRECT:
*    NULL in case of an error
*  SOC_SAND_INDIRECT:
*    None.
*REMARKS:
* We apply a verification mechanism for every malloc - free call
* every allocated block is joint with a head & tail of 4 bytes.
* the head holds the size of the user allocated block (in bytes)
* the tail holds a known signature (0xABCDEF12)
*SEE ALSO:
* soc_sand_os_malloc
*****************************************************/
void
  *soc_sand_os_malloc_any_size(
    SOC_SAND_IN uint32 size,
        char *str
  )
{
  /* return sal_alloc(size, "soc_sand_os_malloc_any_size") ; */
   return sal_alloc(size, str) ; 
}/*
 */
/*****************************************************
*NAME:
* soc_sand_os_free_any_size
*DATE:
* 27/AUG/2002
*FUNCTION:
*  interface to memory de-allocation
*INPUT:
*  SOC_SAND_DIRECT:
*     SOC_SAND_INOUT  void          *memblock
*       memory address to deallocate
*  SOC_SAND_INDIRECT:
*OUTPUT:
*  SOC_SAND_DIRECT:
*   non_zero in case of an error
*  SOC_SAND_INDIRECT:
*    memblock is cleared
*REMARKS:
* We apply a verification mechanism for every malloc - free call
* every allocated block is joint with a head & tail of 4 bytes.
* the head holds the size of the user allocated block (in bytes)
* the tail holds a known signature (0xABCDEF12)
* in this method we check that preseding the address memblock,
* there is a head, and after size bytes there is a tail
* with our signature (ABCDEF12).
*SEE ALSO:
*****************************************************/
SOC_SAND_RET
  soc_sand_os_free_any_size(
    SOC_SAND_INOUT  void  *memblock
  )
{
  sal_free(memblock);
  
  return SOC_SAND_OK;
}

/*****************************************************
*NAME:
* soc_sand_os_task_spawn
*DATE:
* 27/AUG/2002
*FUNCTION:
*  calls vxworks taskSpawn
*INPUT:
*  SOC_SAND_DIRECT:
*    just like Vx taskSpawn
*  SOC_SAND_INDIRECT:
*OUTPUT:
*  SOC_SAND_DIRECT:
*       Zero if error, task_id otherwise
*  SOC_SAND_INDIRECT:
*    a new task is spawned.
*REMARKS:
*SEE ALSO:
*****************************************************/
sal_thread_t
  soc_sand_os_task_spawn(
    SOC_SAND_IN     char          *name,     /* name of new task (stored at pStackBase) */
    SOC_SAND_IN     long          priority,  /* priority of new task */
    SOC_SAND_IN     long          options,   /* task option word */
    SOC_SAND_IN     long          stackSize, /* size (bytes) of stack needed plus name */
    SOC_SAND_IN     SOC_SAND_FUNC_PTR      entryPt,  /* entry point of new task */
    SOC_SAND_IN     long          arg1,      /* 1st of 10 req'd task args to pass to func */
    SOC_SAND_IN     long          arg2,
    SOC_SAND_IN     long          arg3,
    SOC_SAND_IN     long          arg4,
    SOC_SAND_IN     long          arg5,
    SOC_SAND_IN     long          arg6,
    SOC_SAND_IN     long          arg7,
    SOC_SAND_IN     long          arg8,
    SOC_SAND_IN     long          arg9,
    SOC_SAND_IN     long          arg10
  )
{
  return sal_thread_create("soc_sand_os_task_spawn", stackSize, priority, entryPt, NULL);
}

/*
 */
/*****************************************************
*NAME:
* soc_sand_os_task_delete
*DATE:
* 27/AUG/2002
*FUNCTION:
*  using vxWorks interface taskDelete
*INPUT:
*  SOC_SAND_DIRECT:
*    sal_thread_t  task_id  -  as returned by task_spawn
*  SOC_SAND_INDIRECT:
*OUTPUT:
*  SOC_SAND_DIRECT:
*    Non-zero in case of an error
*  SOC_SAND_INDIRECT:
*    a task is deleted.
*REMARKS:
*SEE ALSO:
*****************************************************/
SOC_SAND_RET
  soc_sand_os_task_delete(
    SOC_SAND_IN sal_thread_t  task_id
  )
{
  SOC_SAND_OS_NOT_IMPLEMENTED;  
  return SOC_SAND_ERR; 
}
/*****************************************************
*NAME:
* soc_sand_os_get_current_tid
*DATE:
* 10/MOV/2002
*FUNCTION:
*  returns the running thread tid
*INPUT:
*  SOC_SAND_DIRECT:
*  SOC_SAND_INDIRECT:
*OUTPUT:
*  SOC_SAND_DIRECT:
*       os task id. should never be zero
*  SOC_SAND_INDIRECT:
*REMARKS:
*SEE ALSO:
*****************************************************/
sal_thread_t
  soc_sand_os_get_current_tid(
    void
  )
{
  return sal_thread_self();
}

/*
 */
/*****************************************************
*NAME: soc_sand_os_task_delay_milisec
*DATE: 1/SEP/2003
*FUNCTION:
*  suspend a task for mili-second.
*  Call 'taskDelay()' with the appropriate ticks.
*INPUT:
*  SOC_SAND_DIRECT:
*     uint32 delay_in_milisec  - time to sleep
*  SOC_SAND_INDIRECT:
*OUTPUT:
*  SOC_SAND_DIRECT:
*    Non-zero in case of an error
*  SOC_SAND_INDIRECT:
*    a task (AKA thread) is delayed.
*REMARKS:
*SEE ALSO:
*****************************************************/
SOC_SAND_RET
  soc_sand_os_task_delay_milisec(
    SOC_SAND_IN uint32 delay_in_milisec
  )
{
  sal_msleep(delay_in_milisec);
  
  return SOC_SAND_OK;
}
/*
 */
/*****************************************************
*NAME: soc_sand_os_get_ticks_per_sec
*DATE: 25/AUG/2003
*FUNCTION:
*  get the system clock rate using vxWorks interface
*INPUT:
*  SOC_SAND_DIRECT:
*     None
*  SOC_SAND_INDIRECT:
*OUTPUT:
*  SOC_SAND_DIRECT:
*   int
*    TThe number of ticks per second of the system clock.
*  SOC_SAND_INDIRECT:
*    .
*REMARKS:
*SEE ALSO:
*****************************************************/
int
  soc_sand_os_get_ticks_per_sec(
    void
  )
{
  int
    ticks_per_sec;

    /* All the code that uses this function is not used in BCM, or doesn't care
       what exactly is the value. Hard-coded value is portable, and good enough. */
    ticks_per_sec = 100;

  return ticks_per_sec;
}
/*
 */
/*****************************************************
*NAME:
* soc_sand_os_tick_get
*DATE:
* 27/AUG/2002
*FUNCTION:
*  using vxWorks interface tickGet
*INPUT:
*  SOC_SAND_DIRECT:
*  SOC_SAND_INDIRECT:
*OUTPUT:
*  SOC_SAND_DIRECT:
*    Non-zero in case of an error
*  SOC_SAND_INDIRECT:
*     uint32 *ticks  - number of system ticks since stratup
*REMARKS:
*SEE ALSO:
*****************************************************/
SOC_SAND_RET
  soc_sand_os_tick_get(
    SOC_SAND_INOUT     uint32 *ticks
  )
{
#ifdef VXWORKS
  *ticks = tickGet();
#else
  SOC_SAND_OS_NOT_IMPLEMENTED;
#endif

  return SOC_SAND_OK ;
}

/*****************************************************
*NAME
*  soc_sand_os_nano_sleep
*TYPE:
*  PROC
*DATE:
*  25/SEP/2002
*FUNCTION:
*  Operating system service.
*  Delay a task from executing (nano seconds resolution).
*CALLING SEQUENCE:
*  soc_sand_os_nano_sleep(nano,premature)
*INPUT:
*  SOC_SAND_DIRECT:
*    uint32     nano -
*      Number of nano seconds to wait before trying
*      to return to 'running' state.
*      range: 0 - 1000000000 (0 to one second)
*    uint32     *premature -
*      This procedure loads pointed memory by
*      actual number of nano seconds elapsed since
*      requesting this operation.
*      range: 0 - 1000000000 (0 to one second)
*  SOC_SAND_INDIRECT:
*    None.
*OUTPUT:
*  SOC_SAND_DIRECT:
*    int -
*      If negative then some error has occurred.
*      If zero then procedure returned because of
*        premature timeout (some condition caused return of
*        control to calling task. This could be a signal,
*        for example).
*      Otherwise, control returned after required timeout.
*  SOC_SAND_INDIRECT:
*    Suspended task. Free CPU for other tasks.
*REMARKS:
*  None.
*SEE ALSO:
*****************************************************/
int
  soc_sand_os_nano_sleep(
    uint32     nano,
    uint32     *premature
  )
{
  sal_usleep(nano/1000);

  if (premature) {
        *premature = 0;
    }
  
  return SOC_SAND_OK;
}

  /*
 */
/*****************************************************
*NAME:
* soc_sand_os_get_time
*DATE:
* 27/AUG/2002
*FUNCTION:
*  get the current time of the clock (POSIX)
*INPUT:
*  SOC_SAND_DIRECT:
*  SOC_SAND_INDIRECT:
*OUTPUT:
*  SOC_SAND_DIRECT:
*    Non-zero in case of an error
*  SOC_SAND_INDIRECT:
*  uint32 *seconds -        elapsed time in seconds
*  uint32 *nano_seconds -   elapsed time within a second
*REMARKS: POSIX 1003.1b documentation
*SEE ALSO:
*****************************************************/
SOC_SAND_RET
  soc_sand_os_get_time(
    SOC_SAND_INOUT     uint32 *seconds,
    SOC_SAND_INOUT     uint32 *nano_seconds
  )
{
  SOC_SAND_RET
    ex = SOC_SAND_OK;
  sal_usecs_t usec;

  usec = sal_time_usecs();

  if (seconds)      *seconds    = usec/SECOND_USEC ;
  if (nano_seconds) *nano_seconds = (usec%SECOND_USEC)*1000;

  return ex ;
}
SOC_SAND_RET
  soc_sand_os_get_time_diff(
    SOC_SAND_IN     uint32 start_seconds,
    SOC_SAND_IN     uint32 start_nano_seconds,
    SOC_SAND_IN     uint32 end_seconds,
    SOC_SAND_IN     uint32 end_nano_seconds,
    SOC_SAND_OUT    uint32 *diff_seconds,
    SOC_SAND_OUT    uint32 *diff_nano_seconds
  )
{
  if(diff_seconds)
  {
    *diff_seconds = end_seconds - start_seconds;
  }
  if(diff_nano_seconds)
  {
    if(end_nano_seconds >= start_nano_seconds)
    {
      *diff_nano_seconds = end_nano_seconds - start_nano_seconds;
    }
    else
    {
      if(diff_seconds)
      {
        *diff_seconds = *diff_seconds - 1;
      }
      *diff_nano_seconds = end_nano_seconds + 1000000000 - start_nano_seconds;
    }
  }

  return SOC_SAND_OK;
}


uint32
  soc_sand_os_get_time_micro(
    void
  )
{
  return sal_time_usecs();
}
/*
 */
/*****************************************************
*NAME:
* soc_sand_os_mutex_create
*DATE:
* 27/AUG/2002
*FUNCTION:
*  creates a binary semaphore
*INPUT:
*  SOC_SAND_DIRECT:
*  SOC_SAND_INDIRECT:
*OUTPUT:
*  SOC_SAND_DIRECT:
*    Semaphore id -
*    0 if an error occured.
*  SOC_SAND_INDIRECT:
*REMARKS:
*SEE ALSO:
*****************************************************/
sal_mutex_t
  soc_sand_os_mutex_create(
    void
  )
{
  return sal_mutex_create("soc_sand_os_mutex_create");
}
/*
 */
/*****************************************************
*NAME:
* soc_sand_os_mutex_delete
*DATE:
* 27/AUG/2002
*FUNCTION:
*  deletes a binary semaphore
*INPUT:
*  SOC_SAND_DIRECT:
*  sal_mutex_t   sem_id  -  as recieved from mutex_create
*  SOC_SAND_INDIRECT:
*OUTPUT:
*  SOC_SAND_DIRECT:
*    Non-zero in case of an error
*  SOC_SAND_INDIRECT:
*REMARKS:
*SEE ALSO:
*****************************************************/
SOC_SAND_RET
  soc_sand_os_mutex_delete(
    SOC_SAND_IN sal_mutex_t  sem_id
  )
{
  sal_mutex_destroy(sem_id);
  
  return SOC_SAND_OK;
}
/*
 */
/*****************************************************
*NAME:
* soc_sand_os_mutex_take
*DATE:
* 27/AUG/2002
*FUNCTION:
*  takes the mutex semaphore, all other tasks trying
*  to take it will be blocked till it is given back.
*INPUT:
*  SOC_SAND_DIRECT:
*  sal_mutex_t   sem_id          -
*       as recieved from mutex_create
*   long   timeout  -
*       timeout (in system ticks) to wait before returning
*    with empty hands (may be infinite).
*  SOC_SAND_INDIRECT:
*OUTPUT:
*  SOC_SAND_DIRECT:
*    Non-SOC_SAND_OK in case of an error
*  SOC_SAND_INDIRECT:
*REMARKS: SOC_SAND_INFINITE_TIMEOUT is introduced (in the header file)
*         in order to avoid specific OS definitions.
*SEE ALSO:
*****************************************************/
SOC_SAND_RET
  soc_sand_os_mutex_take(
    SOC_SAND_IN sal_mutex_t  sem_id,
    SOC_SAND_IN long  timeout
  )
{
  int ex;
  
  ex = sal_mutex_take(sem_id, sal_mutex_FOREVER);
  
  return (ex ? SOC_SAND_ERR : SOC_SAND_OK);
}
/*
 */
/*****************************************************
*NAME:
* soc_sand_os_mutex_give
*DATE:
* 27/AUG/2002
*FUNCTION:
*  gives back the mutex semaphore, next task waiting for
*  it in its FIFO will be free to run.
*INPUT:
*  SOC_SAND_DIRECT:
*  sal_mutex_t   sem_id  -  as recieved from mutex_create
*  SOC_SAND_INDIRECT:
*OUTPUT:
*  SOC_SAND_DIRECT:
*    Non-SOC_SAND_OK in case of an error
*  SOC_SAND_INDIRECT:
*REMARKS:
*SEE ALSO:
*****************************************************/
SOC_SAND_RET
  soc_sand_os_mutex_give(
    SOC_SAND_IN sal_mutex_t  sem_id
  )
{
  int ex;
  
  ex = sal_mutex_give(sem_id);
  
  return (ex ? SOC_SAND_ERR : SOC_SAND_OK);
}

/*****************************************************
*NAME:
* soc_sand_os_stop_interrupts
*DATE:
* 27/AUG/2002
*FUNCTION:
* When dealing with the interrupts handling, it is
* common to use this facilty.
*INPUT:
*  SOC_SAND_DIRECT:
*  SOC_SAND_INDIRECT:
*OUTPUT:
*  SOC_SAND_DIRECT:
*    Non-zero in case of an error
*  SOC_SAND_INDIRECT:
*REMARKS: interrupts should be off for short short period
* since they make the clock go on...
*SEE ALSO:
*****************************************************/
SOC_SAND_RET
  soc_sand_os_stop_interrupts(
    uint32 *flags
  )
{
    /*
#ifdef PLISIM
    if (!SAL_BOOT_PLISIM)
#endif     
    */ 
    {
        S_spl = sal_splhi();
    }

    return SOC_SAND_OK;
}
/*
 */
/*****************************************************
*NAME:
* soc_sand_os_start_interrupts
*DATE:
* 27/AUG/2002
*FUNCTION:
* When dealing with the interrupts handling, it is
* common to use this facilty.
*INPUT:
*  SOC_SAND_DIRECT:
*  SOC_SAND_INDIRECT:
*OUTPUT:
*  SOC_SAND_DIRECT:
*    Non-zero in case of an error
*  SOC_SAND_INDIRECT:
*REMARKS:
*SEE ALSO:
*****************************************************/
SOC_SAND_RET
  soc_sand_os_start_interrupts(
    uint32 flags
  )
{
    /*
#ifdef PLISIM
    if (!SAL_BOOT_PLISIM)
#endif     
    */ 
    {
        sal_spl(S_spl--);
    }
    return SOC_SAND_OK;
}

/*****************************************************
*NAME:
* soc_sand_os_msg_q_create
*DATE:
* 17/OCT/2002
*FUNCTION:
* allocating OS msgQ
*INPUT:
*  SOC_SAND_DIRECT:
*    int max_msgs -
*      Max number of messages that can be queued.
*    int max_msglength -
*      Max bytes in one message
*OUTPUT:
*  SOC_SAND_DIRECT:
*    long -
*      0 (null pointer) - if error
*      Identifier of message queue (pointer) - otherwise.
*  SOC_SAND_INDIRECT:
*REMARKS:
*  Queue always pends tasks in FIFO order.
*
*  Total size of memory reserved by the queue:
*  maxMsgs * maxMsgLength
*SEE ALSO:
*****************************************************/
void
  *soc_sand_os_msg_q_create(
    int max_msgs,
    int max_msglength
    )
{

  SOC_SAND_OS_NOT_IMPLEMENTED;
  return (void*)0xf; 
  
}
/*****************************************************
*NAME:
* soc_sand_os_msg_q_delete
*DATE:
* 17/OCT/2002
*FUNCTION:
* deleting OS msgQ
*INPUT:
*  SOC_SAND_DIRECT:
*    void *msg_q_id -
*      Identifier of the msgQ to delete
*  SOC_SAND_INDIRECT:
*OUTPUT:
*  SOC_SAND_DIRECT:
*    Non-SOC_SAND_OK in case of an error
*  SOC_SAND_INDIRECT:
*REMARKS:
*SEE ALSO:
*****************************************************/
SOC_SAND_RET
  soc_sand_os_msg_q_delete(
    void *msg_q_id
    )
{

  SOC_SAND_OS_NOT_IMPLEMENTED;
  return SOC_SAND_OK ;
}
/*****************************************************
*NAME:
* soc_sand_os_msg_q_send
*DATE:
* 17/OCT/2002
*FUNCTION:
* sending a message to a msgQ
*INPUT:
*  SOC_SAND_DIRECT:
*    void  *msg_q_id     -
*      Identifier of the message Q to send to.
*    char  *data -
*      Pointer to memory containing the message to
*      send (with correct size for identified queue,
*      that is, not more than maxMsgLength)
*    uint32 data_size -
*      Number of bytes in memory pointed by 'data'.
*    int          timeout -
*      Number of system ticks to wait for free space
*      on queue before returning (with error) to
*      the caller. If called from interrupt service
*      routine, this value must be SOC_SAND_NO_TIMEOUT.
*      If 'timeout' is set to SOC_SAND_INFINITE_TIMEOUT
*      then an infinite waiting period is applied.
*    int          priority -
*      Priority of loading message into the queue. If
*      zero then normal priority is required. Otherwise,
*      message is pushed to the head of the queue
*      (expedited).
*  SOC_SAND_INDIRECT:
*OUTPUT:
*  SOC_SAND_DIRECT:
*    Non-SOC_SAND_OK in case of an error
*  SOC_SAND_INDIRECT:
*REMARKS:
*  Priority of messages on the queue .
*SEE ALSO:
*****************************************************/
SOC_SAND_RET
  soc_sand_os_msg_q_send(
    void         *msg_q_id,
    char         *data,
    uint32 data_size,
    int          timeout,
    int          priority
  )
{
  SOC_SAND_OS_NOT_IMPLEMENTED;
  return SOC_SAND_OK ;
}
/*****************************************************
*NAME:
* soc_sand_os_msg_q_recv
*DATE:
* 17/OCT/2002
*FUNCTION:
* sending a message to a msgQ
*INPUT:
*  SOC_SAND_DIRECT:
*    void *msg_q_id        -
*      Identifier of the msgQ we are receiveing from.
*    unsigned char   *data -
*      Pointer to memory location to store received
*      message in. If the message is longer than
*      'max_nbytes', the remainder of the message is
*      discarded (no error indication is returned).
*    uint32 max_nbytes -
*      Size of buffer pointed by 'data'.
*    long timeout_in_ticks -
*      Timeout to wait if the msgQ is empty (May be
*      infinite).
*      After this time out, if the Q is still empty
*      the method returns empty handed.
*      For infinite timeout, use SOC_SAND_INFINITE_TIMEOUT.
*      For immediate return, use SOC_SAND_NO_TIMEOUT.
*  SOC_SAND_INDIRECT:
*OUTPUT:
*  SOC_SAND_DIRECT:
*   < 0 - error
*   = 0 - msg arrived
*   > 0 - timeout
*  SOC_SAND_INDIRECT:
*    See data
*REMARKS:
*SEE ALSO:
*****************************************************/
int
  soc_sand_os_msg_q_recv(
    void          *msg_q_id,
    unsigned char *data,
    uint32  max_nbytes,
    long          timeout_in_ticks
    )
{
  SOC_SAND_OS_NOT_IMPLEMENTED;
  return SOC_SAND_OK ;
}
/*****************************************************
*NAME:
* soc_sand_os_msg_q_num_msgs
*DATE:
*  14/FEB/2003
*FUNCTION:
*  Get number of messages currently loaded in msgQ
*INPUT:
*  SOC_SAND_DIRECT:
*    void *msg_q_id        -
*      Identifier of the msgQ to report on.
*  SOC_SAND_INDIRECT:
*OUTPUT:
*  SOC_SAND_DIRECT:
*    int -
*      If positive or zero: Number of queued messages.
*      Otherwise, some error condition has been
*      encountered.
*  SOC_SAND_INDIRECT:
*    None.
*REMARKS:
*SEE ALSO:
*****************************************************/
int
  soc_sand_os_msg_q_num_msgs(
    void          *msg_q_id
    )
{
  SOC_SAND_OS_NOT_IMPLEMENTED;
  return SOC_SAND_OK ;
}
/*
 */
/*****************************************************
*NAME:
* soc_sand_os_memcpy
*DATE:
* 27/OCT/2002
*FUNCTION:
* copy memory from one location to another (ANSI)
*INPUT:
*  SOC_SAND_DIRECT:
*    void *        destination  - destination of copy
*    const void *  source       - source of copy
*    uint32 size         - size of memory to copy (in bytes)
*  SOC_SAND_INDIRECT:
*OUTPUT:
*  SOC_SAND_DIRECT:
*   Non-Zero in case of an error
*  SOC_SAND_INDIRECT:
*REMARKS:
* This routine copies size characters from the object pointed
* to by source into the object pointed to by destination.
* If copying takes place between objects that overlap,
* the behavior is undefined.
*SEE ALSO:
*****************************************************/
SOC_SAND_RET
  soc_sand_os_memcpy(
    void          *destination, /* destination of copy */
    const void    *source,      /* source of copy */
    uint32 size          /* size of memory to copy (in bytes) */
    )
{
  if(destination == NULL || source == NULL) {
    return SOC_SAND_ERR;
  }
  
  sal_memcpy(destination, source, (size_t)size) ;
 /*
  * memcpy returns the void* of the destination,
  * so there is no way to tell whether an error occured
  */
  return SOC_SAND_OK ;
}
/*****************************************************
*NAME:
* soc_sand_os_memcmp
*DATE:
* 27/OCT/2002
*FUNCTION:
* compare two blocks of memory (ANSI)
*INPUT:
*  SOC_SAND_DIRECT:
*    const void * s1    - array 1
*    const void * s2    - array 2
     uint32 n   - size of memory to compare
*  SOC_SAND_INDIRECT:
*OUTPUT:
*  SOC_SAND_DIRECT:
*   If all elements are equal, zero.
*   If elements differ and the differing element
*   from s1 is greater than the element from s2,
*   the routine returns a positive number ;
*   otherwise, it returns a negative number.
*  SOC_SAND_INDIRECT:
*REMARKS:
* This routine compares successive elements from two arrays
* of unsigned char, beginning at the addresses s1 and s2 (both of size n),
* until it finds elements that are not equal
*SEE ALSO:
*****************************************************/
int
  soc_sand_os_memcmp(
    const     void *s1, /* array 1 */
    const     void *s2, /* array 2 */
    uint32 n   /* size of memory to compare */
  )
{
  assert(s1 != NULL && s2 != NULL);
  
  return sal_memcmp(s1, s2, (size_t)n) ;
}
/*****************************************************
*NAME:
* soc_sand_os_memset
*DATE:
* 27/OCT/2002
*FUNCTION:
* set a block of memory (ANSI)
*INPUT:
*  SOC_SAND_DIRECT:
*    void *m,           - block of memory
*    int   c,           - character to store
*    uint32 n   - size of memory in bytes
*  SOC_SAND_INDIRECT:
*OUTPUT:
*  SOC_SAND_DIRECT:
*   Non-Zero in case of an error
*  SOC_SAND_INDIRECT:
*REMARKS:
* This routine stores c converted to an unsigned char
* in each of the elements of the array of
* unsigned char beginning at m, with size size
*SEE ALSO:
*****************************************************/
/*
 * loads memory with a char
 */
SOC_SAND_RET
  soc_sand_os_memset(
    void *m,           /* block of memory */
    int   c,           /* character to store  */
    uint32 n   /* size of memory in bytes */
  )
{
  if(m == NULL) {
    return SOC_SAND_ERR;
  }
  
  sal_memset(m, c, (size_t)n) ;
 /*
  * memcpy returns the void* of the destination,
  * so there is no way to tell whether an error occured
  */
  return SOC_SAND_OK ;
}
/*
 */
/*****************************************************
*NAME:
* soc_sand_os_strlen
*DATE:
* 27/OCT/2002
*FUNCTION:
* determine the length of a string (ANSI)
*INPUT:
*  SOC_SAND_DIRECT:
*    const char *s - string to check
*  SOC_SAND_INDIRECT:
*OUTPUT:
*  SOC_SAND_DIRECT:
*   The number of non-null characters in the string
*  SOC_SAND_INDIRECT:
*REMARKS:
* This procedure returns the number of
* characters in s, not including EOS
*SEE ALSO:
*****************************************************/
uint32
  soc_sand_os_strlen(
    const char* s /* string */
  )
{
  uint32 string_len ;
  string_len = sal_strlen(s ) ;
  return string_len ;
}

/*
 */
/*****************************************************
*NAME:
* soc_sand_os_strncpy
*DATE:
* 27/OCT/2002
*FUNCTION:
* copy characters from one string to another (ANSI)
*INPUT:
*  SOC_SAND_DIRECT:
*    char          *s1 - string to copy to
*    const char    *s2 - string to copy from
*    uint32 n   - max no. of characters to copy
*  SOC_SAND_INDIRECT:
*OUTPUT:
*  SOC_SAND_DIRECT:
*   Non-Zero in case of an error
*  SOC_SAND_INDIRECT:
*REMARKS:
* This routine copies n characters from string s2 to string s1.
* If n is greater than the length of s2, nulls are added to s1.
* If n is less than or equal to the length of s2,
* the target string will not be null-terminated
*SEE ALSO:
*****************************************************/
SOC_SAND_RET
  soc_sand_os_strncpy(
    char          *s1, /* string to copy to */
    const char    *s2, /* string to copy from */
    uint32 n   /* max no. of characters to copy */
  )
{
  sal_strncpy(s1, s2, (size_t)n ) ;
  /*
   * strncpy returns the char* of the destination,
   * so there is no way to tell whether an error occured
   */
  return SOC_SAND_OK ;
}
/*****************************************************
*NAME:
* soc_sand_os_sys_clk_rate_get
*DATE:
* 27/OCT/2002
*FUNCTION:
* get the system clock rate
*INPUT:
*  SOC_SAND_DIRECT:
*  SOC_SAND_INDIRECT:
*OUTPUT:
*  SOC_SAND_DIRECT:
*   uint32 -
*     The number of ticks per second of the system clock.
*  SOC_SAND_INDIRECT:
*REMARKS:
* This routine returns the system clock rate.
*SEE ALSO:
*****************************************************/
uint32
  soc_sand_os_sys_clk_rate_get(
    void
  )
{
/* All the code that uses this function is not used in BCM, or doesn't care
       what exactly is the value. Hard-coded value is portable, and good enough. */
  return 1000000;
}

/* {  Random function. */

/*
 * Use DuneDriver Rand.
 */
static
  SOC_SAND_RAND
   Soc_sand_os_rand = {{0}, 0, 0, 0, 0};

/*****************************************************
*NAME
*  soc_sand_os_srand
*TYPE:
*  PROC
*DATE:
*  25-May-03
*FUNCTION:
*  The srand function sets the starting point for generating
*  a series of pseudo-random integers
*INPUT:
*  SOC_SAND_DIRECT:
*    uint32 x -
*       Seed for random-number generation.
*  SOC_SAND_INDIRECT:
*    None.
*OUTPUT:
*  SOC_SAND_DIRECT:
*    void
*  SOC_SAND_INDIRECT:
*    NON
*REMARKS:
*  None.
*SEE ALSO:
*****************************************************/
void
  soc_sand_os_srand(
    uint32 x
  )
{
  soc_sand_rand_seed_set(&Soc_sand_os_rand, x);
  return;
}
/*****************************************************
*NAME
*  soc_sand_os_rand
*TYPE:
*  PROC
*DATE:
*  12-Jan-03
*FUNCTION:
*  Generates a pseudo-random integer between 0 and 2^32-1
*INPUT:
*  SOC_SAND_DIRECT:
*    void -
*  SOC_SAND_INDIRECT:
*    None.
*OUTPUT:
*  SOC_SAND_DIRECT:
*    uint32 -
*       The pseudo-random integer
*  SOC_SAND_INDIRECT:
*    NON
*REMARKS:
*  None.
*SEE ALSO:
*****************************************************/
uint32
  soc_sand_os_rand(
    void
  )
{
  uint32
    x;
  x = soc_sand_rand_u_long(&Soc_sand_os_rand);
  return x;
}
/* }  END Random function. */
/* {  IO printing functions. */
/*****************************************************
*NAME
*  soc_sand_os_printf
*TYPE:
*  PROC
*DATE:
*  12-Jan-03
*FUNCTION:
*  Print formatted output to the standard output stream.
*  Wrapper to 'printf'.
*INPUT:
*  SOC_SAND_DIRECT:
*    const char* format -
*       Format control
*    ...                -
*       Optional arguments
*  SOC_SAND_INDIRECT:
*    None.
*OUTPUT:
*  SOC_SAND_DIRECT:
*    int -
*      the number of characters printed, or a negative value if an error occurs.
*  SOC_SAND_INDIRECT:
*    NON
*REMARKS:
*  None.
*SEE ALSO:
*****************************************************/
int
  soc_sand_os_printf(
    SOC_SAND_IN char* format, ...
  )
{
  va_list
    args ;
  int
    i;

  va_start(args, format) ;
  i = sal_vprintf(format, args);
  va_end(args) ;
  
  return i;
}

/* } END IO printing functions. */

int
sand_sal_rand_in_kernel_mode(void)
{
  return 0;
}

