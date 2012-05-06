// BitSpinner.cpp
//
// Copyright 2012 Don Schwarz <don.schwarz@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//    http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "AdaEncoder.h"

const int dataPin = A0;        // The Serial Data Pin to the Shift Register
const int clockPin = A1;       // The Clock Pin to the Shift Register
const int latchPin = A2;       // The Latch Pin to the Shift Register
const int binaryDigit9 = A3;   // HIGH = light 9th bargraph LED from left
const int binaryDigit10 = A4;  // HIGH = light 10th bargraph LED from left
const int digitSegmentG = A5;  // Select LED segment marked G on data sheet
const int digitSegmentF = 0;   // Select LED segment marked F on data sheet
const int digitSegmentE = 1;   // Select LED segment marked E on data sheet
const int digitSegmentD = 2;   // Select LED segment marked D on data sheet
const int digitSegmentA = 3;   // Select LED segment marked A on data sheet
const int digitSegmentC = 4;   // Select LED segment marked C on data sheet
const int digitSegmentB = 5;   // Select LED segment marked B on data sheet
const int encoderPinA = 6;     // Input pin for rotary encoder
const int encoderPinB = 7;     // Input pin for rotary encoder
const int digitSelect3 = 8;    // Select 3rd 7-segment LED digit from left
const int digitSelect2 = 9;    // Select 2nd 7-segment LED digit from left
const int digitSelect1 = 10;   // Select 1st 7-segment LED digit from left
const int digitSelect4 = 11;   // Select 4th 7-segment LED digit from left
const int encoderPush = 12;    // Pull-up resister enabled, LOW = pushed
const int hexSwitch = 13;      // Pull-up resister enabled, LOW = hex

const long debounceDelay = 50; // the debounce time; increase if the output flickers
const int blankDigit = 16;
const int digitDelayMs = 2;

// 4 2 1   8 4 2 1
// A B C   D E F G
const int led_table[] = {
  0x7E, // 0
  0x30, // 1
  0x6D, // 2
  0x79, // 3
  0x33, // 4
  0x5B, // 5
  0x5F, // 6
  0x70, // 7
  0x7F, // 8
  0x73, // 9
  0x77, // A
  0x1F, // B
  0x0D, // C
  0x3D, // D
  0x4F, // E
  0x47, // F
  0x00, // blankDigit
};

int counter = 0;
int velocity = 1;
bool counting = false;

void setup()
{
  // Dec/Hex display
  pinMode(digitSegmentA, OUTPUT); 
  pinMode(digitSegmentB, OUTPUT); 
  pinMode(digitSegmentC, OUTPUT); 
  pinMode(digitSegmentD, OUTPUT); 
  pinMode(digitSegmentE, OUTPUT); 
  pinMode(digitSegmentF, OUTPUT);  
  pinMode(digitSegmentG, OUTPUT);  
  pinMode(digitSelect1, OUTPUT); 
  pinMode(digitSelect2, OUTPUT);  
  pinMode(digitSelect3, OUTPUT);  
  pinMode(digitSelect4, OUTPUT);
  digitalWrite(hexSwitch, HIGH);
  pinMode(hexSwitch, INPUT);  
  // Binary display
  pinMode(binaryDigit9, OUTPUT);  
  pinMode(binaryDigit10, OUTPUT);  
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  // Rotary encoder
  digitalWrite(encoderPush, HIGH);
  pinMode(encoderPush, INPUT);  
  pinMode(encoderPinA, INPUT);
  digitalWrite(encoderPinA, HIGH);
  pinMode(encoderPinB, INPUT);
  digitalWrite(encoderPinB, HIGH);
  AdaEncoder::addEncoder('a', encoderPinA, encoderPinB);
}

void loop() 
{
  read_encoder_push();
  read_encoder_turn();
  update_counter();

  update_binary_display(counter);
  if (digitalRead(hexSwitch) == LOW) {
    update_hex_display(counter);
  } else {
    update_dec_display(counter);
  }
}

void read_encoder_turn() {
  int8_t clicks = 0;
  if (AdaEncoder::genie(&clicks, NULL) != NULL) {
    if (counting) {
      velocity += clicks;
    } else {
      counter += clicks;
    }
  }
}

void read_encoder_push() {
  static int lastButtonState = LOW;
  static long lastDebounceTime = 0;

  // TODO: would the hex/dec display be brighter if we used PinChangeInt here?
  bool reading = digitalRead(encoderPush);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  } 
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading == LOW) {
      counting = !counting;
    }
  }
  lastButtonState = reading;
}

void update_counter() {
  static int subcounter = 0;
  
  if (counting) {
    subcounter += velocity;
    counter += subcounter / 250;
    if (subcounter > 250) {
      subcounter = subcounter % 250;
    }
    if (subcounter < -250) {
      subcounter = -(-subcounter % 250);
    }
  }
  while (counter > 1023) {
    counter -= 1024;
  }
  while (counter < 0) {
    counter += 1024;
  }
}

void update_binary_display(int number) {
  static int lastNumber = -1;
  
  if (number != lastNumber) {
    // Pull latch LOW to send data
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, number >> 2);
    // Pull latch HIGH to stop sending data
    digitalWrite(latchPin, HIGH);
    // It would be nice if we could PWM these to match the brightness
    // of the shift-register LEDs.  Unfortunately, this chip only
    // supports PWM on pins 3, 5, 6, 9, 10, and 11.
    // TODO: fix this in the next rev of the board.
    digitalWrite(binaryDigit9, (number & 0x02) ? HIGH : LOW);
    digitalWrite(binaryDigit10, (number & 0x01) ? HIGH : LOW);
    lastNumber = number;
  }
}

void set_digit(int digit) {
  digitalWrite(digitSegmentA, (led_table[digit] & 0x40) ? LOW : HIGH);
  digitalWrite(digitSegmentB, (led_table[digit] & 0x20) ? LOW : HIGH);
  digitalWrite(digitSegmentC, (led_table[digit] & 0x10) ? LOW : HIGH);
  digitalWrite(digitSegmentD, (led_table[digit] & 0x08) ? LOW : HIGH);
  digitalWrite(digitSegmentE, (led_table[digit] & 0x04) ? LOW : HIGH);
  digitalWrite(digitSegmentF, (led_table[digit] & 0x02) ? LOW : HIGH);
  digitalWrite(digitSegmentG, (led_table[digit] & 0x01) ? LOW : HIGH);
}

void update_dec_display(int n) {
  set_digit((n >= 1000) ? ((n / 1000) % 10) : blankDigit);
  digitalWrite(digitSelect1, HIGH);
  delay(digitDelayMs);
  digitalWrite(digitSelect1, LOW);
  set_digit((n >= 100) ? ((n / 100) % 10) : blankDigit);
  digitalWrite(digitSelect2, HIGH);
  delay(digitDelayMs);
  digitalWrite(digitSelect2, LOW);
  set_digit((n >= 10) ? ((n / 10) % 10) : blankDigit);
  digitalWrite(digitSelect3, HIGH);
  delay(digitDelayMs);
  digitalWrite(digitSelect3, LOW);
  set_digit(n % 10);
  digitalWrite(digitSelect4, HIGH);
  delay(digitDelayMs);
  digitalWrite(digitSelect4, LOW);
}

void update_hex_display(int n) {
  set_digit(blankDigit);
  digitalWrite(digitSelect1, HIGH);
  delay(digitDelayMs);
  digitalWrite(digitSelect1, LOW);
  set_digit((n >= 256) ? ((n / 256) % 16) : blankDigit);
  digitalWrite(digitSelect2, HIGH);
  delay(digitDelayMs);
  digitalWrite(digitSelect2, LOW);
  set_digit((n >= 16) ? ((n / 16) % 16) : blankDigit);
  digitalWrite(digitSelect3, HIGH);
  delay(digitDelayMs);
  digitalWrite(digitSelect3, LOW);
  set_digit(n % 16);
  digitalWrite(digitSelect4, HIGH);
  delay(digitDelayMs);
  digitalWrite(digitSelect4, LOW);
}

