#include <Servo.h>

// Joystick shield is connected to A0-A3
const uint8_t LEFT_JS_H = A0;   // Pin for Left Joystick Horizontal
const uint8_t LEFT_JS_V = A1;   // Pin for Left Joystick Vertical
const uint8_t RIGHT_JS_H = A3;  // Pin for Right Joystick Horizontal
const uint8_t RIGHT_JS_V = A2;  // Pin for Right Joystick Vertical

const uint8_t LEFT_JS_BUTTON = 2;   // Pin for Left Joystick Button
const uint8_t RIGHT_JS_BUTTON = 4;  // Pin for Right Joystick Button

// Instantiate Servo objects for base, horizontal, vertical and the claw
Servo base;
Servo horizontal;
Servo vertical;
Servo claw;

const uint8_t H_MAX = 160;  // Upper limit of horizontal movement
const uint8_t H_MIN = 52;   // Lower limit of horizontal movement
const uint8_t V_MAX = 180;  // Upper limit of vertical movement
const uint8_t V_MIN = 94;   // Lower limit of vertical movement
const uint8_t C_MAX = 95;   // Maximum open claw value
const uint8_t C_MIN = 57;   // Minimum closed claw value

#define POTENTIOMETER A8

int8_t joystick_left_v() {
  uint16_t value = analogRead(LEFT_JS_V);
  if (value < 400) return 1;  // Increase for UP joystick
  if (value > 600) return -1; // Decrease for DOWN joystick
  return 0;   // default to NO movement
}

int8_t joystick_right_v() {
  uint16_t value = analogRead(RIGHT_JS_V);
  if (value < 400) return 1;  // Increase for UP joystick
  if (value > 600) return -1; // Decrease for DOWN joystick
  return 0;   // default to NO movement
}

int8_t joystick_right_h() {
  uint16_t value = analogRead(RIGHT_JS_H);
  if (value < 400) return 1;  // Increase for UP joystick
  if (value > 600) return -1; // Decrease for DOWN joystick
  return 0;   // default to NO movement
}

void setup() {
  Serial.begin(115200);
  pinMode(LEFT_JS_BUTTON, INPUT_PULLUP);
  pinMode(RIGHT_JS_BUTTON, INPUT_PULLUP);

  pinMode(POTENTIOMETER, INPUT);
  // base.attach(5);
  horizontal.attach(9);
  vertical.attach(10);
  claw.attach(11);

  horizontal.write(H_MIN + (H_MAX - H_MIN) / 2);  // set mid-range vertical
  vertical.write(V_MIN + (V_MAX - V_MIN) / 2);  // set mid-range vertical
  claw.write(C_MIN + (C_MAX - C_MIN) / 2);  // open claw half way
  delay(500);
}

void loop() {
  // long potentiometer = analogRead(POTENTIOMETER);
  if (int8_t h_direction = joystick_left_v()) {
    Serial.print("H: ");
    Serial.println(h_direction);

    // Move in direction returned
    uint8_t h_position = horizontal.read();
    Serial.print("H at: ");
    Serial.println(h_position);
    // move if we're inside acceptable range
    if (h_position <= H_MIN && h_direction == -1) h_direction = 0;
    if (h_position >= H_MAX && h_direction == 1) h_direction = 0;
    if (h_direction)
      horizontal.write(h_position + h_direction);
  }

  // Vertical movement
  if (int8_t v_direction = joystick_right_v()) {
    Serial.print("V: ");
    Serial.println(v_direction);

    // Move in direction returned
    uint8_t v_position = vertical.read();
    Serial.print("V at: ");
    Serial.println(v_position);
    // move if we're inside acceptable range
    if (v_position <= V_MIN && v_direction == -1) v_direction = 0;
    if (v_position >= V_MAX && v_direction == 1) v_direction = 0;
    if (v_direction)
      vertical.write(v_position + v_direction);
  }

  // Claw movement
  if (int8_t c_direction = joystick_right_h()) {
    Serial.print("C: ");
    Serial.println(c_direction);

    // Move in direction returned
    uint8_t c_position = claw.read();
    Serial.print("C at: ");
    Serial.println(c_position);
    // move if we're inside acceptable range
    if (c_position <= C_MIN && c_direction == -1) c_direction = 0;
    if (c_position >= C_MAX && c_direction == 1) c_direction = 0;
    if (c_direction)
      claw.write(c_position + c_direction);
  }


  // Serial.println();
  delay(100);
}