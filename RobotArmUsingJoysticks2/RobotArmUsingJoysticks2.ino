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

struct Servo_info {
  Servo servo_object;
  uint8_t servo_pin;
  uint8_t servo_min;
  uint8_t servo_max;
  uint8_t joystick_pin;
};

Servo_info servos [] = {
  {base,       5,  0, 180, LEFT_JS_H},
  {horizontal, 9, 52, 180, LEFT_JS_V},
  {vertical,  10, 94, 180, RIGHT_JS_V},
  {claw,      11, 60,  89, RIGHT_JS_H}  
};
const int8_t SERVO_COUNT = sizeof(servos) / sizeof(Servo_info);

int8_t joystick_read(uint8_t servo_number) {
  uint16_t value = analogRead(servos[servo_number].joystick_pin);
  if (value < 250) return 1;  // Increase for UP joystick
  if (value > 750) return -1; // Decrease for DOWN joystick
  return 0;   // default to NO movement
}

void setup() {
  Serial.begin(115200);
  pinMode(LEFT_JS_BUTTON, INPUT_PULLUP);
  pinMode(RIGHT_JS_BUTTON, INPUT_PULLUP);

  for (int i = 0; i < SERVO_COUNT; i++) {
    Servo_info servo = servos[i];
    servo.servo_object.attach(servo.servo_pin);
    uint8_t mid_range = servo.servo_min + (servo.servo_max - servo.servo_min) / 2;
    servo.servo_object.write(mid_range);
  }
  delay(200);
}

void loop() {
  for (int i = 0; i < sizeof(servos) / sizeof(Servo_info); i++) {
    if (int8_t move_direction = joystick_read(i)) {
      Serial.print(i);
      Serial.print(": direction: ");
      Serial.println(move_direction);

      // Move in indicated direction unless move would go outside MIN/MAX range
      uint8_t servo_position = servos[i].servo_object.read();
      Serial.print("at: ");
      Serial.println(servo_position);
      if ((servo_position <= servos[i].servo_min && move_direction == -1) ||
          (servo_position >= servos[i].servo_max && move_direction == 1))
        move_direction = 0;
      if (move_direction) {
        Serial.print("move to: ");
        Serial.println(servo_position + move_direction);
        servos[i].servo_object.write(servo_position + move_direction);
      }
    }
  }
  delay(50);
}