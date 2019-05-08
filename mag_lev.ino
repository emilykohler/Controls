/*
 * code by Emily and Herve 
 * for magnetic levitation
 * 
 */
int setPoint = 520; // our "goal" sensor value
int dlyVal = 800; // delay value 
int writeValue; // motor speed value

float gain = 5.6;
float kp = 1.0;
float kd = 2.0;
int output;

// Error Variables for PD
float error;
float lastError;
float rateError;

// Motor inputs for PCB
int IN1 = 3;
int IN2 = 5;

// sensor pin
int hallSensor = A2;

// Set up times for error calculations for PD
unsigned long currentTime;
unsigned long lastTime;
unsigned long elapsedTime;

// Sensor variables 
int sensorValue;
int sensorValue1;
int sensorValue2;


void setMagnet(int input){
  // a function to set the speed of the magnetic
  // the input variable is the output of the PD controller
  if (input < 50){
    // doesn't let the writeValue go too low
    writeValue = 50;
    analogWrite(IN1, 0);
    analogWrite(IN2, writeValue);
  }
  else if (input > 250){
    // doesn't let the writeValue go above limits
    writeValue = 250;
    analogWrite(IN1, 0);
    analogWrite(IN2, writeValue);
  }
  else {
    // sets the writeValue to the input
    writeValue = input;
    analogWrite(IN1, 0);
    analogWrite(IN2, writeValue);
  }
  //Serial.print(writeValue);
  //Serial.println();
}


void setup() {
  pinMode(hallSensor, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  error = 0;
  lastError = 0;
  lastTime = millis();
  
  //Serial.begin(115200);
}

// My BangBang code
void loop() {
  sensorValue1 = analogRead(hallSensor);
  sensorValue2 = analogRead(hallSensor);
  sensorValue = (sensorValue1+sensorValue2)/2; // averaged sensor value
  //Serial.print(sensorValue);
  //Serial.print(",");

  currentTime = millis();
  elapsedTime = currentTime - lastTime;
  lastTime = currentTime;

  error = setPoint - sensorValue;
  rateError = (error-lastError)/elapsedTime;
  lastError = error;

  output = gain*(kp*error + kd*rateError);
  //Serial.print(output);
  //Serial.print(",");

  if (sensorValue > setPoint){
    output = 0;
  }

  //Serial.println(output);

  setMagnet(output);

  delayMicroseconds(dlyVal);
}
