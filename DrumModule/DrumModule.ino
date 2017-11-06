#include <MIDI.h>

#define NUM_PADS 8                            // how many pads are supported by the controller
#define CHANNEL 1                             // the midi channel
#define BUFFER_SIZE 10                        // how many inputs should be stored
#define MIN_TIME_BETWEEN_NOTES 1              // how many milliseconds before next hit

typedef struct {
  unsigned int  threshold;                    // the threshold to determine what counts as idle
  unsigned char note;                         // the midi note to be played on hit
  unsigned char pin;                          // the pin index for using the switched pin mode
  unsigned int  inputBuffer[BUFFER_SIZE];     // the buffer containing the raw analog values
  unsigned char bufferIndex;                  // specifies which index is the most recent
  unsigned int  lastHitTime;                  // the millisecond the pad was last hit on
  unsigned int  currentMax;                   // the current maximum value in the buffer
}PadData;

PadData pads[NUM_PADS];                       // container for all pads

/**************************
 * program initialization *
 **************************/
void setup() {
  setupPads();
  setupSwitch();
}

/*************
 * main loop *
 *************/
unsigned int buffer[] = {0,0,0,0,0,0,0,0,0,0};
unsigned char currentIndex = 0;
 
void loop() {
  Serial.println(analogRead(A0));
  for(int i = 0; i < NUM_PADS; ++i){
    updatePad(&pads[i]);
    calculateNote(&pads[i]);
  }

  updateHat();
  calculateHat();
}

/*********************************************
 * get input and update specified pad buffer *
 *********************************************/
void updatePad(PadData *pad){
  unsigned int val = analogRead(pad->pin);
  pad->inputBuffer[pad->bufferIndex] = val;
  pad->bufferIndex++;
  if(pad->bufferIndex >= BUFFER_SIZE) pad->bufferIndex = (unsigned int) 0;

  unsigned int max = 0;
  for(int i = 0; i < BUFFER_SIZE; i++){
    if(pad->inputBuffer[i] > pad->threshold &&
      pad->inputBuffer[i] > max) max = pad->inputBuffer[i];
  }

  pad->currentMax = max;
}

/*******************************************************
 * calculates the midi note to be played               *
 * if note needs played, it will send a trigger signal *
 *******************************************************/
 void calculateNote(PadData *pad){
  if(pad->currentMax >= pad->threshold){
    unsigned int time = millis();
    unsigned int timeSinceHit = time - pad->lastHitTime;
    if(timeSinceHit > MIN_TIME_BETWEEN_NOTES){
      pad->lastHitTime = time;
      playMidiNote(pad->note, pad->currentMax);
    }
  }
 }

/**************************************
 * play note using data stored in pad *
 **************************************/
void playMidiNote(unsigned char note, unsigned int velocity){
  if(note != 35) return;
  if(velocity > 127) velocity = 127;
  usbMIDI.sendNoteOn(note, velocity, CHANNEL);
  usbMIDI.sendNoteOff(note, velocity, CHANNEL);
}

