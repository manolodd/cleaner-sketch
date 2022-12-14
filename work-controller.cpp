/*
 * MIT License
 * 
 * Copyright 2021 Manuel Domínguez Dorado <ingeniero@ManoloDominguez.com>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "work-controller.h"

WorkController::WorkController(unsigned long interval) {
    _lastMillis = millis()+interval;
    _interval = interval;
}

WorkController::WorkController(void) {
    _lastMillis = millis()+DEFAULT_INTERVAL;
    _interval = DEFAULT_INTERVAL;
}

bool WorkController::isTimeToWork() {
    unsigned long currentMillis;
    unsigned long computedPeriod;
    currentMillis = millis();
    if (currentMillis < _lastMillis) {
        computedPeriod = MAX_UNSIGNED_LONG - _lastMillis + currentMillis;
    } else {
        computedPeriod = currentMillis - _lastMillis;
    }
    if (computedPeriod >= _interval) {
        _lastMillis = millis();
        return true;
    }
    return false;
}

void WorkController::setInterval(unsigned long interval) {
    _interval = interval;
}
