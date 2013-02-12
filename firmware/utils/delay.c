/**
 *  \file   delay.c
 *
 *  \brief  This file contains APIs to configure a DMTimer instance for
 *          operation and to generate a requested amount of delay.
*/

/*
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
*/
/*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


#include "delay.h"


/****************************************************************************
**                        FUNCTION DEFINITION
****************************************************************************/

/**
 * \brief   This function configures a DMTimer instance for use.
 *
 * \param   None
 *
 * \return  None.
 *
 * \Note   This a wrapper API. The actual implementation can be found in
 *         platform specific files.
 */

void DelayTimerSetup(void)
{
    SysDelayTimerSetup();
}


/**
 * \brief   This function generates a delay of specified milli-seconds.
 *
 * \param   milliSec     This is the number of milli-seconds of delay.
 *
 * \return  None.
 *
 * \Note   This a wrapper API. The actual implementation can be found in
 *         platform specific files.
 *         This function shouldnot be called when StartTimer, StopTimer and
 *         IsTimerElapsed functionality is in use.
 */

void delay(unsigned int milliSec)
{
    Sysdelay(milliSec);
}

/**
 * \brief   This function starts the timer for millisec timeout.
 *
 * \param   milliSec     This is the number of milli-seconds of delay.
 *
 * \return  None.
 */

void StartTimer(unsigned int millisec)
{
    SysStartTimer(millisec);
}

/**
 * \brief   This function starts the timer for millisec timeout.
 *
 * \param   None.
 *
 * \return  None.
 *
 * \NOTE    delay functionality cannot be used till StopTimer is called.
 */
void StopTimer()
{
    SysStopTimer();
}

/**
 * \brief   This function checks whether timer is expired for set milli secs 
 *
 * \param   None. 
 *
 * \return  None.
 *
 * \NOTE   SysStartTimer has to be called prior to checking status.
 *         delay functionality cannot be used till SysStopTimer is called.
 */
unsigned int IsTimerElapsed(void)
{
    return (SysIsTimerElapsed());
}

