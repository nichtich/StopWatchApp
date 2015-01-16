/******************************************************************************
 * Arduino Stopwatch controlled by a button
 *
 * Author: Jakob Voß
 *
 * https://github.com/nichtich/StopWatchApp/
 * 
 * Released to the public domain
 *****************************************************************************/

#include "StopWatchApp.h"

StopWatchApp::StopWatchApp(uint8_t buttonPin) :
    _buttonPin(buttonPin) 
{
    pinMode(_buttonPin, INPUT);
    _state = StopWatchApp::READY;

    // TODO: enable interrupt on _buttonPin (use TimerOne library)
}

enum StopWatchApp::State StopWatchApp::state() 
{
    return _state;
}

unsigned long elapsed() 
{
    if (_state == StopWatchApp::RUNNING && _clicked.elapsed() > 0) {
        // still pressed
        return _clicked.elapsed();
    } else {
        return _current.elapsed();
    }

}

void StopWatch::press() 
{
    _clicked.reset();
    _clicked.start();

    switch(_state) {
        // stop current watch
        case StopWatchApp::RUNNING:
            _watch.reset();
            _state = StopWatchApp::STOPPED;
            break;
        // start new watch
        case StopWatchApp::SLEEP:
            _watch.reset();
            _watch.start();
            _state = StopWatchApp::RUNNING;
            onWakeUp();
            break;
        case StopWatchApp::READY:
            _watch.reset();
            _watch.start();
            _state = StopWatchApp::RUNNING;
            break;
        // proceed current watch
        case StopWatchApp::STOPPED:
            _watch.start();
            _state = StopWatchApp::RUNNING;
            break;
    }
}

void StopWatch::release() 
{
    const bool longClick = _clicked.elapsed() >= SWA_LONGCLICK;

    // ignore release if not pressed before or click duration < 1ms
    if (!_clicked.elapsed()) { return; }

    if (longClick) {
        if (_state == StopWatchApp::RUNNING) {
            // reset current watch (or measure time of long click?)
            _current = _clicked;
        } else { // _state == StopWatchApp::STOPPED

        } // other states are not possible

        // ... put into history
        
        _state = StopWatchApp::READY;
    }

    _clicked.reset();
}

void StopWatchApp::sleep() 
{
    if (_state == StopWatchApp::READY) {
        onSleep();
        _state = StopWatchApp::SLEEPING;
        _laststate = _state;
    }
}

void StopWatchApp::onSleep() 
{
    // disable componentes such as LCD
}

void StopWatchApp::onWakeUp() 
{
    // enable components such as LCD
}

