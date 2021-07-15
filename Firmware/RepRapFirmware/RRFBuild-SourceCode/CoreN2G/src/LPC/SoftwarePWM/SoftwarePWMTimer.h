/* mbed Microcontroller Library
* Copyright (c) 2006-2013 ARM Limited
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#ifndef SOFTWAREPWMTIMER_H
#define SOFTWAREPWMTIMER_H

#include "CoreImp.h"
#include "chip.h"
#include "SoftwarePWM.h"
#ifdef LPC_DEBUG
#include "Platform/MessageType.h"
#endif

class SoftwarePWMTimer
{
    
    
public:
    SoftwarePWMTimer();
    int enable(SoftwarePWM *pwm, uint32_t onTime, uint32_t offTime);
    void disable(int chan);
    void adjustOnOffTime(int chan, uint32_t onTime, uint32_t offTime);

#ifdef LPC_DEBUG
    void Diagnostics(MessageType mtype);
#endif

};


extern SoftwarePWMTimer softwarePWMTimer;

#ifdef LPC_DEBUG
extern uint32_t pwmInts;
extern uint32_t pwmCalls;
extern uint32_t pwmMinTime;
extern uint32_t pwmMaxTime;
extern uint32_t pwmAdjust;
#endif

#endif
