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

#include "pushbuttons.h"

/*
  Wemos D1 R2 - ESP8266:
   - Push button A -> D5
	 - Push button B -> D6

  Arduino Uno - only 2 buttons supported with interrupt mode
	 - Push button A -> 2
	 - Push button B -> 3

  Schematic: GND ---> Button ---> PIN (in pullup mode)
*/

// Init the push buttons handler with PINs
PushButtons Buttons(4);

// called when the button 1 is pressed
void OnButtonAClicked(void) {
  Serial.println("button A clicked");
}

// called when the button 2 is pressed
void OnButtonBClicked(void) {
  Serial.println("button B clicked");
}

/* Handlers for interrupts mode
  void OnButtonAInterrupt(void) {
    Buttons.HandleButton1Interrupt();
  }
  void OnButtonBInterrupt(void) {
    Buttons.HandleButton2Interrupt();
  }
*/

void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");

  /* Init in interrupts mode
    if ( !Buttons.Begin(OnButtonAInterrupt, OnButtonBInterrupt)) {
  */

  /* Init the push buttons in basic mode */
  if ( !Buttons.Begin()) {
    Serial.println("Unable to init Push Buttons Handler");
    while (1);
  }

  //init callback
  Buttons.OnButton1Clicked(OnButtonAClicked);
  Buttons.OnButton2Clicked(OnButtonBClicked);

  Serial.println("Push buttons ready");
}

void loop() {
  // process events for buttons handler
  Buttons.Process( millis() );
}
