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

#ifndef _NON_BLOCKING_COUNTDOWN_H_
#define _NON_BLOCKING_COUNTDOWN_H_

#include <time.h>
#include <Arduino.h>

class NonBlockingCountdown {
private:
    const unsigned long MAX_UNSIGNED_LONG = 4294967295; // Max millis() before starting at 0.
    unsigned long _lastMillis;
	unsigned long _interval;
public:
    NonBlockingCountdown(unsigned long interval);
    void delay();
    bool countFinished();
	void reset();
};

#endif
