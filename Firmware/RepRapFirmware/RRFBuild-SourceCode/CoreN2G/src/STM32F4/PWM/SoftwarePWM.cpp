

#include <CoreImp.h>
#include "HybridPWM.h"
extern "C" void debugPrintf(const char* fmt, ...) __attribute__ ((format (printf, 1, 2)));
//#define LPC_DEBUG
#define SPWM_TIMER TIM7
HardwareTimer SPWMTimer(SPWM_TIMER);

// Minimum period between interrupts - in microseconds (to prevent starving other tasks)
static constexpr uint32_t MinimumInterruptDeltaUS = 50;

typedef struct {
    uint32_t nextEvent;
    Pin pin;
    uint32_t onOffTimes[2][2];
    uint8_t state;
    uint8_t onOffBuffer;
    bool newTimes;
    bool enabled;
} PWMState;

static PWMState States[MaxPWMChannels];
static int32_t startActive = -1;
static int32_t endActive = -1;
static uint32_t baseTime;
static uint32_t baseDelta;
static bool timerReady = false;
static TIM_HandleTypeDef *timerHandle;

static SoftwarePWM PWMChans[MaxPWMChannels];

#ifdef LPC_DEBUG
uint32_t pwmInts = 0;
uint32_t pwmCalls = 0;
uint32_t pwmMinTime = 0xffffffff;
uint32_t pwmMaxTime = 0;
uint32_t pwmAdjust = 0;
uint32_t pwmBad = 0;
uint32_t pwmBigDelta = 0;
uint32_t pwmVBigDelta = 0;
#endif

static void updateActive()
{
    int32_t first = -1;
    int32_t last = -1;
    for(uint32_t i = 0; i < MaxPWMChannels; i++)
        if (States[i].enabled)
        {
            last = i;
            if (first < 0) first = i;
        }
    bool timerRunning = (endActive >= 0);
    if (last >= 0)
    {
        startActive = first;
        endActive = last + 1;
        // If timer not currently running restart it
        if (!timerRunning)
        {
            //debugPrintf("Resume timer\n");
            SPWMTimer.resume();
        }
    }
    else
    {
        startActive = endActive = -1;
        SPWMTimer.pause();
        //debugPrintf("Pause timer\n");
    }
}

void syncAll()
{
    // briefy pause and then restart all active channels so that they are in sync.
    // this minimises the number of interrupts we need, to service the channels.
    SPWMTimer.pause();  //Stop the timer
    // set all active channels so that on the next event they will all move to state 0
    for(uint32_t i = 0; i < MaxPWMChannels; i++)
        if (States[i].enabled)
        {
            States[i].state = 1;
            States[i].nextEvent = MinimumInterruptDeltaUS;
        }
    baseTime = 0;
    baseDelta = MinimumInterruptDeltaUS;
    SPWMTimer.setOverflow(baseDelta, TICK_FORMAT);
    SPWMTimer.setCount(1);
    endActive = -1;
    updateActive();
} 

static void disable(int chan)
{
    States[chan].enabled = false;
    updateActive();
}

static int enable(Pin pin, uint32_t onTime, uint32_t offTime)
{
    // find a free slot
    for(uint32_t i = 0; i < MaxPWMChannels; i++)
        if (!States[i].enabled)
        {
            PWMState& s = States[i];
            s.pin = pin;
            s.onOffTimes[0][0] = onTime;
            s.onOffTimes[0][1] = offTime;
            s.onOffBuffer = 0;
            s.state = 0;
            fastDigitalWriteHigh(pin);
            s.newTimes = false;
            s.enabled = true;
            syncAll();        
            return i;
        }
    return -1;
}

static void adjustOnOffTime(int chan, uint32_t onTime, uint32_t offTime)
{
    PWMState& s = States[chan];
    uint32_t buffer = s.onOffBuffer ^ 1;
    s.onOffTimes[buffer][0] = onTime;
    s.onOffTimes[buffer][1] = offTime;
    s.newTimes = true;
}

// We handle interrupts directly to reduce overhead so this function
// is just a placeholder
extern "C" void SPWM_Handler(HardwareTimer *) __attribute__ ((hot));
void SPWM_Handler(HardwareTimer * notused)
{
}

extern "C" void TIM7_IRQHandler(void) noexcept __attribute__((optimize("O2")));
void TIM7_IRQHandler(void) noexcept
{
    __HAL_TIM_CLEAR_IT(timerHandle, TIM_IT_UPDATE); 
#ifdef LPC_DEBUG
    pwmInts++;
    const uint32_t startTime = SPWMTimer.getCount();;
#endif 
    uint32_t next = 0x7fffffff;
    uint32_t now = baseTime + baseDelta;
    baseTime = now;
    for(int i = startActive; i < endActive; i++)
        if (States[i].enabled)
        {
            PWMState& s = States[i];
            int32_t delta = (s.nextEvent - now);
            if (delta <= 0)
            {
                // time has expired, move to next state
                s.state ^= 1;
                const uint32_t newState = s.state;
                // do we need to switch to a new set of timing parameters?
                if (newState == 0)
                {
                    fastDigitalWriteHigh(s.pin);
                    if (s.newTimes)
                    {
                        s.onOffBuffer ^= 1;
                        s.newTimes = false;
                    }
                }
                else
                    fastDigitalWriteLow(s.pin);
                // adjust next time by any drift to keep things in sync
                delta += s.onOffTimes[s.onOffBuffer][newState];
                s.nextEvent = now + delta;
                // don't allow correction to go too far!
                if (delta < 0)
                {
                    // If delta is still -ve then this means that the call to the int handler
                    // was so late that it has exceeded the length of time of the current pulse.
                    // This may happen with very short pulses (ones that are less than our defined
                    // minimum). In this case we will have set a nextEvent time that is in the past.
                    // this is not a problem so long as the next pulse length is long enough that it
                    // can cover the accumulated delay and allow us to catch up. This is typically
                    // the case with a PWM signal. Obviously we can't set a next event time in the
                    // past so we zero it here, but carry the delta forwards in nextEvent.
                    delta = 0;
#ifdef LPC_DEBUG
                    pwmBigDelta++;
#endif
                }
#ifdef LPC_DEBUG
                pwmCalls++;
#endif
            }
            // at this point delta >= 0, now track the smallest delta as the next target time
            if ((uint32_t)delta < next)
                next = (uint32_t)delta;
        }
    // setup the timer for the nearest event time
    if (next < MinimumInterruptDeltaUS)
    {
        // extend the time if it is less than our minimum
        next = MinimumInterruptDeltaUS;
#ifdef LPC_DEBUG
        pwmAdjust++;
#endif
    }
    // Set the new compare value
    if (next > 0xffff) next = 0xffff;
    baseDelta = next;
    __HAL_TIM_SET_AUTORELOAD(timerHandle, next-1);
#ifdef LPC_DEBUG
    if (next >= 0xffff) pwmVBigDelta++;
    if (SPWMTimer.getCount(TICK_FORMAT) >= next)
        pwmBad++;
#endif
#ifdef LPC_DEBUG
    const uint32_t dt = SPWMTimer.getCount() - startTime;
    if (dt < pwmMinTime)
        pwmMinTime = dt;
    else if (dt > pwmMaxTime)
        pwmMaxTime = dt;
#endif
}

static void initTimer() noexcept
{
    for(uint32_t i = 0; i < MaxPWMChannels; i++)
        States[i].enabled = false;
    uint32_t preScale = SPWMTimer.getTimerClkFreq()/1000000;
    //debugPrintf("ST base freq %d setting presacle %d\n", static_cast<int>(SPWMTimer.getTimerClkFreq()), static_cast<int>(preScale));
    SPWMTimer.setPrescaleFactor(preScale);
    SPWMTimer.setOverflow(0, TICK_FORMAT);
    SPWMTimer.attachInterrupt(SPWM_Handler);
    timerHandle = &(HardwareTimer_Handle[get_timer_index(SPWM_TIMER)]->handle);
    timerReady = true;
}


#ifdef LPC_DEBUG
void SPWMDiagnostics()
{
    debugPrintf("Ints: %u; Calls %u; fast: %uuS; slow %uuS adj %u bad %u big delta %u vbd %u\n", (unsigned)pwmInts, (unsigned)pwmCalls, (unsigned)pwmMinTime, (unsigned)pwmMaxTime, (unsigned)pwmAdjust, (unsigned)pwmBad, (unsigned)pwmBigDelta, (unsigned)pwmVBigDelta);
    pwmMinTime = UINT32_MAX;
    pwmMaxTime = 0;
    pwmInts = 0;
    pwmCalls = 0;
    pwmAdjust = 0;
    pwmBad = 0;
    pwmBigDelta = 0;
}
#endif

SoftwarePWM::SoftwarePWM() noexcept : channel(-1), period(0xffffffff)
{
} 

void SoftwarePWM::free() noexcept
{
    if (channel >= 0)
        disable(channel);
    channel = -1;
    period = 0xffffffff;
}


HybridPWMBase *SoftwarePWM::allocate(Pin pin, uint32_t freq, float value) noexcept
{
    //debugPrintf("SWPWM allocate pin %x, freq %d\n", static_cast<int>(pin), static_cast<int>(freq));
    if (!timerReady)
        initTimer();
    for(uint32_t i = 0; i < MaxPWMChannels; i++)
        if (PWMChans[i].period == 0xffffffff)
        {
            PWMChans[i].period = (freq!=0)?(1000000/freq):0;
            PWMChans[i].setValue(pin, value);
            return &PWMChans[i];
        }
    return nullptr;

}

void SoftwarePWM::setValue(Pin pin, float value) noexcept
{
    if (period == 0)
    {
        pinMode(pin, (value < 0.5) ? OUTPUT_LOW : OUTPUT_HIGH);
        return;
    }
    uint32_t onTime = (uint32_t)(period * value);
    if(onTime < MinimumInterruptDeltaUS){ onTime = 0; }
    if(onTime > (period-MinimumInterruptDeltaUS)){ onTime = period; }
    if (onTime == 0)
    {
        //debugPrintf("pin %d chan %d off\n", pin, channel);
        if (channel >= 0)
        {
            disable(channel);
            channel = -1;
        }
        pinMode(pin, OUTPUT_LOW);
    }
    else if (onTime == period)
    {
        if (channel >= 0)
        {
            disable(channel);
            channel = -1;
        }
        //debugPrintf("pin %d chan %d on\n", pin, channel);
        pinMode(pin, OUTPUT_HIGH);

    }
    else
    {
        if (channel < 0)
        {
            channel = enable(pin, onTime, period - onTime);
            //debugPrintf("pin %d chan %d pwm\n", pin, channel);
        }
        else
            adjustOnOffTime(channel, onTime, period - onTime);
    }
}

void SoftwarePWM::setValue(float value) noexcept
{
    setValue(pwmPin->pin, value);
}

void SoftwarePWM::appendStatus(const StringRef& reply) noexcept
{
    if (channel >= 0)
    {
        uint32_t now = baseTime + SPWMTimer.getCount();
        reply.catf(" channel %d next %d on %u off %u", (int)channel, (int)(States[channel].nextEvent - now), (unsigned)States[channel].onOffTimes[States[channel].onOffBuffer][0], (unsigned)States[channel].onOffTimes[States[channel].onOffBuffer][1]);
    }
    else
        reply.catf(" period %d", static_cast<int>(period));
}