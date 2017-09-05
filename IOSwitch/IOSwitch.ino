//Data for proccessing input
const int numReads = 5;
int reads[numReads];
int readIndex;
int total;
void setupGetVal(){
  for(int i = 0; i < numReads; i++){
    reads[i] = 0;
  }

  readIndex = 0;
  total = 0;
}

//Data for switch control pins
const int numControlPins = 4;
int controlPins[numControlPins];
int readPin = A0;
void setupIOSwitch(){
  controlPins[0] = 0;
  controlPins[1] = 1;
  controlPins[2] = 2;
  controlPins[3] = 3;

  pinMode(readPin, INPUT);
  for(int i = 0; i < numControlPins; i++){
    pinMode(controlPins[i], OUTPUT);
  }
}

//Data for detecting hits
const int threshold = 10;
const int throttle = 2;

void setup() {
  setupGetVal();
  setupIOSwitch();

  Serial.begin(300);
}

void loop() {
  int val = getVal(readPin);
  if(threshold <= val) Serial.println(val);
  else Serial.println(0);

  //delay(throttle);
}

/*
 * Needed vars for getVal
 * const int numReads = 10;
 * int reads[10];
 * int readIndex;
 * int total;
 */
int getVal(int pin){
  total = total - reads[readIndex];
  reads[readIndex] = analogRead(readPin);
  total = total + reads[readIndex];
  
  readIndex++;
  if(readIndex >= numReads) readIndex = 0;
  
  return total/numReads;
}

/*
 * Needed vars for readSwitchedPin
 * const int numControlPins = 4;
 * int controlPins[numControlPins];
 * int readPin = A0;
 */
int readSwitchedPin(int pin){
  for(int i = 0; i < numControlPins; i++){
    if(pin % 2 == 1) digitalWrite(controlPins[i], HIGH);
    else digitalWrite(controlPins[i], LOW);
    pin = pin / 2;
  }

  return analogRead(readPin);
}
