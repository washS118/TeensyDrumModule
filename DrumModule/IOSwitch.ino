/************************************************
 * Provides functions to read switched I/O pins *
 ************************************************/

#define MAX_PINS 10;                      // how many pins are allowed

typedef struct {                          // defines pins for easy use in the read function
  bool pin0;
  bool pin1;
  bool pin2;
  bool pin3;
}SwitchKey;

SwitchKey keys[16];
unsigned char readPins[] = {A0,A1};       // which pins to use for reads
unsigned char controlPins[] = {0,1,2,3};  // which pins to use for controlling the switch

/**********************************
 * prepares the IO switch for use *
 **********************************/
void setupSwitchArray(){
  for(int i = 0; i < 16; i++){
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
  //TODO
  return -1;
}
