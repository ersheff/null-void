// Null/Void Arduino firmware
// Eric Sheffield and Anna Weisling 2019

// knob input pins
#define knob1Pin A0
#define knob2Pin A1
#define knob3Pin A2

// switch and button input pins
#define switchPin 2
#define buttonPin 3

// voltmeter output pins
#define voltmeter1Pin 9
#define voltmeter2Pin 10
#define voltmeter3Pin 11

// min and max PWM values for meters for calibration
#define minPWM1 3
#define maxPWM1 144
#define minPWM2 3
#define maxPWM2 144
#define minPWM3 3
#define maxPWM3 144

// adjust length of time for voltmeter swipes
#define swipeDelay 10

// max for analog reads - set lower if knobs don't fully max at 1023 
#define maxKnob 1023

// reset timer length - n X incoming-serial-timing
// the resetCounter is only incremented every time serial data is received
// which is currently set to every 100ms in Pd
#define resetLength 50

// 255 is used as the start/end flag for serial input and output
// this means all incoming and outgoing values are clipped at
// 254 to prevent problems
#define sentinelFlag 255

// serial input/output arrays
byte transmitBits[6] = {0, 0, 0, 0, 0, sentinelFlag};
byte receiveBits[3] = {0, 0, 0};

// mode switch and reset counter variables
enum state {
  reset,
  settings,
  runrun
};
state currentState = reset;
int resetCounter;


void setup() {
  Serial.begin(9600);
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(voltmeter1Pin, OUTPUT);
  pinMode(voltmeter2Pin, OUTPUT);
  pinMode(voltmeter3Pin, OUTPUT);
}


void loop() {
  switch (currentState) {
    case reset:
      startSequence();
      break;
    case settings:
      readSensors();
      Serial.write(transmitBits, 6);
      delay(100);
      break;
    case runrun:
      readIncomingSerial();
      writeVoltmeterPWM();
      testReset();
      break;
  }
}


void readSensors() {
  // read the knobs, switch, and button and pack into trasmitBits array
  transmitBits[0] = map(analogRead(knob1Pin), 0, maxKnob, 0, 254);  
  transmitBits[1] = map(analogRead(knob2Pin), 0, maxKnob, 0, 254);
  transmitBits[2] = map(analogRead(knob3Pin), 0, maxKnob, 0, 254);
  transmitBits[3] = !digitalRead(switchPin);
  if(!digitalRead(buttonPin)){
    transmitBits[4] = 1;
    currentState = runrun;
  } else transmitBits[4] = 0;
}


void readIncomingSerial(){
  while(!Serial.available());
  byte sentinel = Serial.read();
  if(sentinel == sentinelFlag){
    Serial.readBytes(receiveBits, 3);  
  }
}


void writeVoltmeterPWM(){
    analogWrite(voltmeter1Pin, map(receiveBits[0], 0, 254, minPWM1, maxPWM1));
    analogWrite(voltmeter2Pin, map(receiveBits[1], 0, 254, minPWM2, maxPWM2));
    analogWrite(voltmeter3Pin, map(receiveBits[2], 0, 254, minPWM3, maxPWM3));
}


void testReset(){
  if(!digitalRead(buttonPin)){
    if(resetCounter++ > resetLength){
      resetCounter = 0;
      currentState = reset;
    }
  } else resetCounter = 0;
}


// startSequence does a "wipe" from min to max on each
// meter to check the min and max values for calibration
void startSequence() {
  // clear transmitBits
  for(int i = 0; i < 5; i++){
    transmitBits[i] = 0;
  }
  //send transmitBits to zero out Pd
  Serial.write(transmitBits, 6);
  // do the swipes
  for(int i = minPWM1; i <= maxPWM1; i++){
    analogWrite(voltmeter1Pin, i);
    delay(swipeDelay);
  }
  for(int i = maxPWM1; i >= minPWM1; i--){
    analogWrite(voltmeter1Pin, i);
    delay(swipeDelay);
  }
  for(int i = minPWM2; i <= maxPWM2; i++){
    analogWrite(voltmeter2Pin, i);
    delay(swipeDelay);
  }
  for(int i = maxPWM2; i >= minPWM2; i--){
    analogWrite(voltmeter2Pin, i);
    delay(swipeDelay);
  }
  for(int i = minPWM3; i <= maxPWM3; i++){
    analogWrite(voltmeter3Pin, i);
    delay(swipeDelay);
  }
  for(int i = maxPWM3; i >= minPWM3; i--){
    analogWrite(voltmeter3Pin, i);
    delay(swipeDelay);
  }
  currentState = settings;
}
