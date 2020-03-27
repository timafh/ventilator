// originally written by Johnny Lee <jcl5m1+ventilator@gmail.com>

#include <Arduino.h>
#include <Servo.h>
#include "Components/AlarmSystem/AlarmSystem.h"
#include "Components/Configuration/ConfigurationManager.h"
#include "Components/DeviceManagement/DeviceInfoManager.h"
#include "Modules/SingleButtonMenu/SingleButtonMenu.h"
#include "Modules/Ventilator/Ventilator.h"

#include "globals.h"

Servo myservo;

// instanciate AlarmSystem
AlarmSystem alarmSystem;

// instanciate ConfigurationManager
ConfigurationManager configurationManager;
DeviceInfoManager deviceInfoManager;

SingleButtonMenu singleButtonMenu;
Ventilator ventilator;

//some variables to tweek
#define version "20201603.1"
#define rate 16           // breathing cycles per minute
#define enable_motor true // useful for debugging without noise

#define max_speed 180
#define min_speed 0
#define PEEP_speed 40 //approx 5cm/H2O
#define led_pin 13
#define button_pin A5
#define current_pin A0
#define servo_pin 3
#define serial_baud 9600

int buttonState = 1;
int buttonStatePrev = 1;
int speed_state = 0;
int loop_count = 0;
int click_loop_count = 0;
int click_count = 0;

int target_speed_high = 0;
int target_speed_low = 0;

int cycle_counter = 0;
int cycle_phase = 0;
int mode = 0;
int current = 0;

void setup()
{
  // Register comperator to execute every 1 ms
  OCR0A = 0xAF;
  TIMSK0 |= _BV(OCIE0A);

  analogReference(INTERNAL); // sets reference to 1.1v

  singleButtonMenu.setup();

  configurationManager.ReadConfiguration();
  deviceInfoManager.ReadDeviceInfo();

  Serial.begin(serial_baud);
  Serial.print("Version:\t");
  Serial.println(version);

  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, HIGH);

  ventilator.setup();
}

SIGNAL(TIMER0_COMPA_vect)
{
  alarmSystem.tick();
  ventilator.tick();
}

void loop()
{
  singleButtonMenu.tick();

  // approximate pressure mapping fro original blower. Other blowers will vary
  // 40 ~= 5cm/H2O
  // 60 ~= 10cm/H2O
  // 90 ~= 18cm/H2O
  // 120 ~= 32cm/H2O

  if (speed_state == 0)
  {
    target_speed_high = 60;
    target_speed_low = PEEP_speed;
  }
  if (speed_state == 1)
  {
    target_speed_high = 70;
    target_speed_low = PEEP_speed;
  }
  if (speed_state == 2)
  {
    target_speed_high = 80;
    target_speed_low = PEEP_speed;
  }
  if (speed_state == 3)
  {
    target_speed_high = 90;
    target_speed_low = PEEP_speed;
  }
  if (speed_state == 4)
  {
    target_speed_high = 100;
    target_speed_low = PEEP_speed;
  }

  //CPAP mode, both speed are the same
  if (mode == 0)
    target_speed_low = target_speed_high;

  // handle breath in/out cycle at target rate/min
  cycle_counter += 1;
  if ((30 * 100) / rate < cycle_counter)
  {
    cycle_phase = (cycle_phase + 1) % 2;
    cycle_counter = 0;
    Serial.print(loop_count / 100.0);
    Serial.print("\tphase speed:");
    if (cycle_phase == 0)
    {
      if (enable_motor)
        myservo.write(target_speed_high);
      Serial.println(target_speed_high);
    }
    else
    {
      if (enable_motor)
        myservo.write(target_speed_low);
      Serial.println(target_speed_low);
    }
  }

  // for debugging breathing back pressure sensing
  //  current = analogRead(current_pin);
  //  Serial.print(current);
  //  Serial.print(",");
  //  Serial.println(digitalRead(button_pin));

  loop_count += 1;
  delay(10); // approximately 100 cycles per second
}
