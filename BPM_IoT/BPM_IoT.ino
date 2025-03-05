#include "thingProperties.h"
int sensor_pin = 0;
int pulse_signal = 0;
int upper_threshold = 860; //or your threshold of choice
int lower_threshold = 800; //or your threshold of choice
int counter = 0;

//float BPM = 0.0;

bool ignore = false;
bool first_pulse_detected = false;
unsigned long first_pulse_time = 0;
unsigned long second_pulse_time = 0;
unsigned long pulse_period = 0;

void setup() {
  // put your setup code here, to run once:
  delay(1500);
  initProperties();
  
  //Connect to cloud and get info/errors
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  //Wait for cloud connection
  while (ArduinoCloud.connected() != 1) {
  ArduinoCloud.update();
  delay(500);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
