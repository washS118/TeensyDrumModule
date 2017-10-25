/************************************************
 * Provides functions to read switched I/O pins *
 ************************************************/

#define MAX_PINS 10                       // how many pins are allowed
#define READ_DELAY 0                      // milliseconds between setting pins and reading value

typedef struct {                          // defines pins for easy use in the read function
  bool pin0;
  bool pin1;
  bool pin2;
  bool pin3;
}SwitchKey;

SwitchKey keys[16];                       // array to store keys
unsigned char readPins[] = {A0,A1};       // which pins to use for reads
unsigned char controlPins[] = {0,1,2,3};  // which pins to use for controlling the switch

/**********************************
 * prepares the IO switch for use *
 **********************************/
void setupSwitch(){
  unsigned int i;
  for(i = 0; i < sizeof(controlPins); i++){
    pinMode(controlPins[i], OUTPUT);
  }
  
  for(i = 0; i < 16; i++){
    keys[i].pin0 = i & B0001;
    keys[i].pin1 = i & B0010;
    keys[i].pin2 = i & B0100;
    keys[i].pin3 = i & B1000;
  }
}


/*******************************************************
 * reads a value from the switched pin                 *
 * returns -1 if pin does not exist or is out of range *
 *******************************************************/
int readSwitchedPin(int pin){
  //return if pin is out of bounds
  if(pin > MAX_PINS) return -1;

  // get array indexes
  unsigned char keyIndex = pin % 16;
  unsigned char pinIndex = pin / 16;

  // return if pinIndex out of bounds
  if(pinIndex > sizeof(controlPins)) return -1;

  // get key and read pin
  SwitchKey key = keys[keyIndex];
  unsigned char readPin = readPins[pinIndex];

  // set all control pins to low
  digitalWrite(controlPins[0], HIGH);
  digitalWrite(controlPins[1], HIGH);
  digitalWrite(controlPins[2], HIGH);
  digitalWrite(controlPins[3], HIGH);

  // set needed pins to high
  if(key.pin0) digitalWrite(controlPins[0], HIGH);
  if(key.pin1) digitalWrite(controlPins[1], HIGH);
  if(key.pin2) digitalWrite(controlPins[2], HIGH);
  if(key.pin3) digitalWrite(controlPins[3], HIGH);

  // pause and return val at readPin
  delay(READ_DELAY);
  return analogRead(readPin);
}
