#ifndef StopWatchApp_h
#define StopWatchApp_h

#include "StopWatch.h"

#define SWA_LONGCLICK 1200 // long click after 1.2s
#define SWA_BUTTONCHECK 10 // check button every 10 ms (also debouce time)
#define SWA_HISTORY 2      // remember last n times    

class StopWatchApp {
public:
    enum State { READY, RUNNING, STOPPED, SLEEP };
    enum State state();

    StopWatchApp(uint8_t buttonPin);
    unsigned long elapsed();

    void press();   // TODO: protect method
    void release(); // TODO: procted method

protected:
    void onWakeUp();
    void onSleep();

private:
    enum State _state;
    StopWatch _current, _clicked;
    StopWatch _history[SWA_HISTORY];
}

#endif
