#include "thingProperties.h"
int sensor_pin = 0;
int pulse_signal = 0;
int upper_threshold = 815; //or your threshold of choice
int lower_threshold = 770; //or your threshold of choice
int counter = 0;

//float bPM = 0.0;

bool ignore = false;
bool first_peak_detected = false;
bool any_peak_detected = false;
unsigned long first_pulse_time = 0;
unsigned long second_pulse_time = 0;
unsigned long pulse_period = 0;

void setup() {
  // put your setup code here, to run once:
  delay(1500);
  initProperties();
  Serial.begin(9600);
  
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
  pulse_signal = analogRead(sensor_pin);
  //Serial.println(pulse_signal);

  // Find leading edge of heart beat
  if (pulse_signal > upper_threshold && any_peak_detected == false) {
    if (first_peak_detected == false) {
      first_pulse_time = millis();
      first_peak_detected = true;
    } else {
      second_pulse_time = millis();
      pulse_period = second_pulse_time - first_pulse_time;
      first_pulse_time = second_pulse_time;
    }
    any_peak_detected = true;
  }

  //Find trailing edge
  if (pulse_signal < lower_threshold) {
    any_peak_detected = false;
  }

  bPM = (1.0 / pulse_period) * 60.0 * 1000;
  Serial.println(bPM);

  delay(50);

  counter++;
  if (counter > 200){
    ArduinoCloud.update();
    Serial.println(bPM);
    counter = 0;
  }
}
