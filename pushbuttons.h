/*
  Push buttons handler with software debouncing and interrupts support

  MIT License

  Copyright (c) 2017 Denis MACHARD

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

// included only once
#pragma once

typedef void(*callback)();
typedef void(*isr)();

class PushButtons
{
  public:
    uint8_t pinBt1;
    uint8_t pinBt2;
    uint8_t pinBt3;
    uint8_t pinBt4;

    bool basicMode;

    volatile int stateBt1;
    long lastTimeBt1;
    bool debounceBt1;

    volatile int stateBt2;
    long lastTimeBt2;
    bool debounceBt2;

    volatile int stateBt3;
    long lastTimeBt3;
    bool debounceBt3;

    volatile int stateBt4;
    long lastTimeBt4;
    bool debounceBt4;

  public:
    PushButtons(uint8_t pinBt1, uint8_t pinBt2 = 0, uint8_t pinBt3 = 0, uint8_t pinBt4 = 0);
    bool Begin(isr isr1 = NULL, isr isr2 = NULL, isr isr3 = NULL, isr isr4 = NULL);
    void Process(unsigned long t);
    void HandleButton1Interrupt( void );
    void OnButton1Clicked( callback );
    void HandleButton2Interrupt( void );
    void OnButton2Clicked( callback );
    void HandleButton3Interrupt( void );
    void OnButton3Clicked( callback );
    void HandleButton4Interrupt( void );
    void OnButton4Clicked( callback );

  protected:
    callback _onClick1;
    callback _onClick2;
    callback _onClick3;
    callback _onClick4;
};
