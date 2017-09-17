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

#include <Arduino.h>
#include "pushbuttons.h"

#define SWITCH_DEBOUNCE	        50

PushButtons::PushButtons(uint8_t pinBt1, uint8_t pinBt2, uint8_t pinBt3, uint8_t pinBt4)
{
  this->pinBt1 = pinBt1;
  this->pinBt2 = pinBt2;
  this->pinBt3 = pinBt3;
  this->pinBt4 = pinBt4;

  this->basicMode = true;

  this->lastTimeBt1 = 0;
  this->stateBt1 = 0;
  this->debounceBt1 = false;

  this->lastTimeBt2 = 0;
  this->stateBt2 = 0;
  this->debounceBt2 = false;

  this->lastTimeBt3 = 0;
  this->stateBt3 = 0;
  this->debounceBt3 = false;

  this->lastTimeBt4 = 0;
  this->stateBt4 = 0;
  this->debounceBt4 = false;
}

bool PushButtons::Begin(isr isr1, isr isr2, isr isr3, isr isr4)
{
  if (this->pinBt1) {
    pinMode(this->pinBt1, INPUT_PULLUP);
    if ( isr1 != NULL ) attachInterrupt(digitalPinToInterrupt(this->pinBt1), isr1, CHANGE);
  }
  if (this->pinBt2) {
    pinMode(this->pinBt2, INPUT_PULLUP);
    if ( isr2 != NULL ) attachInterrupt(digitalPinToInterrupt(this->pinBt2), isr2, CHANGE);
  }
  if (this->pinBt3) {
    pinMode(this->pinBt3, INPUT_PULLUP);
    if ( isr3 != NULL ) attachInterrupt(digitalPinToInterrupt(this->pinBt3), isr3, CHANGE);
  }
  if (this->pinBt4) {
    pinMode(this->pinBt4, INPUT_PULLUP);
    if ( isr4 != NULL ) attachInterrupt(digitalPinToInterrupt(this->pinBt4), isr4, CHANGE);
  }

  if ( isr1 != NULL || isr2 != NULL || isr3 != NULL || isr4 != NULL ) {
    this->basicMode = false;
  }
  return true;
}

void PushButtons::HandleButton1Interrupt(void)
{
  this->stateBt1 = 1;
}

void PushButtons::HandleButton2Interrupt(void)
{
  this->stateBt2 = 1;
}

void PushButtons::HandleButton3Interrupt(void)
{
  this->stateBt3 = 1;
}

void PushButtons::HandleButton4Interrupt(void)
{
  this->stateBt4 = 1;
}

void PushButtons::Process(unsigned long t)
{
  if (this->basicMode) {
    if (digitalRead(this->pinBt1) == LOW) {
      this->stateBt1 = 1;
    }
    if (digitalRead(this->pinBt2) == LOW) {
      this->stateBt2 = 1;
    }
    if (digitalRead(this->pinBt3) == LOW) {
      this->stateBt3 = 1;
    }
    if (digitalRead(this->pinBt4) == LOW) {
      this->stateBt4 = 1;
    }
  }

  // checking button1 with debouncing
  if (this->pinBt1) {
    if ( this->stateBt1 && this->debounceBt1 == false ) {
      this->lastTimeBt1 = t % 1000;
      this->debounceBt1 = true;
    }
    if ( this->debounceBt1 && ((t % 1000 - this->lastTimeBt1) > SWITCH_DEBOUNCE) ) {
      if (digitalRead(this->pinBt1) == HIGH) {
        if (this->_onClick1) this->_onClick1();
      }
      this->stateBt1 = 0;
      this->debounceBt1 = false;
    }
  }

  // checking button2 with debouncing
  if (this->pinBt2) {
    if ( this->stateBt2 && this->debounceBt2 == false ) {
      this->lastTimeBt2 = t % 1000;
      this->debounceBt2 = true;
    }
    if ( this->debounceBt2 && ((t % 1000 - this->lastTimeBt2) > SWITCH_DEBOUNCE) ) {
      if (digitalRead(this->pinBt2) == HIGH) {
        if (this->_onClick2) this->_onClick2();
      }
      this->stateBt2 = 0;
      this->debounceBt2 = false;
    }
  }

  // checking button3 with debouncing
  if (this->pinBt3) {
    if ( this->stateBt3 && this->debounceBt3 == false ) {
      this->lastTimeBt3 = t % 1000;
      this->debounceBt3 = true;
    }
    if ( this->debounceBt3 && ((t % 1000 - this->lastTimeBt3) > SWITCH_DEBOUNCE) ) {
      if (digitalRead(this->pinBt3) == HIGH) {
        if (this->_onClick3) this->_onClick3();
      }
      this->stateBt3 = 0;
      this->debounceBt3 = false;
    }
  }

  // checking button4 with debouncing
  if (this->pinBt4) {
    if ( this->stateBt4 && this->debounceBt4 == false ) {
      this->lastTimeBt4 = t % 1000;
      this->debounceBt4 = true;
    }
    if ( this->debounceBt4 && ((t % 1000 - this->lastTimeBt4) > SWITCH_DEBOUNCE) ) {
      if (digitalRead(this->pinBt4) == HIGH) {
        if (this->_onClick4) this->_onClick4();
      }
      this->stateBt4 = 0;
      this->debounceBt4 = false;
    }
  }

}

void PushButtons::OnButton1Clicked( callback cb )
{
  this->_onClick1 = cb;
}

void PushButtons::OnButton2Clicked( callback cb )
{
  this->_onClick2 = cb;
}

void PushButtons::OnButton3Clicked( callback cb )
{
  this->_onClick3 = cb;
}

void PushButtons::OnButton4Clicked( callback cb )
{
  this->_onClick4 = cb;
}


