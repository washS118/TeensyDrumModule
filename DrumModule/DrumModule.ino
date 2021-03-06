#include <MIDI.h>

#define NUM_PADS 10                           // how many pads are supported by the controller
#define CHANNEL 10                             // the midi channel
#define BUFFER_SIZE 10                        // how many inputs should be stored
#define MIN_TIME_BETWEEN_NOTES 75             // how many milliseconds before next hit
#define MAX_MIDI_VELOCITY 127                 // the largest velocity accepted by the midi standard
#define USE_MAX true

typedef struct {
  unsigned int  threshold;                    // the threshold to determine what counts as idle
  unsigned char note;                         // the midi note to be played on hit
  unsigned char pin;                          // the pin index for using the switched pin mode
  unsigned int  defaultVelocity;                      // the velocity to use when USE_MAX is true
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
void loop() {    
  //updateHat();
  
  for(int i = 0; i < NUM_PADS; ++i){
    updatePad(&pads[i]);
    calculateNote(&pads[i]);
  }
}

/*********************************************
 * get input and update specified pad buffer *
 *********************************************/
void updatePad(PadData *pad){
  unsigned int val = analogRead(pad->pin);
  pad->inputBuffer[pad->bufferIndex] = val;
  pad->bufferIndex++;
  if(pad->bufferIndex >= BUFFER_SIZE){
    pad->bufferIndex = (unsigned int) 0;
  }

  unsigned int max = 0;
  for(int i = 0; i < BUFFER_SIZE; i++){
    if(pad->inputBuffer[i] > pad->threshold &&
       pad->inputBuffer[i] > max) 
        max = pad->inputBuffer[i];
  }

  if(max == pad->inputBuffer[BUFFER_SIZE / 2]){
    pad->currentMax = max;
  }else{
    pad->currentMax = 0;
  }
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
      unsigned int velocity = pad->currentMax;
      if(USE_MAX){
        velocity = pad->defaultVelocity;
      }
      
      playMidiNote(pad->note, velocity);
    }
  }
 }

/**************************************
 * play note using data stored in pad *
 **************************************/
void playMidiNote(unsigned char note, unsigned int velocity){
  //skip if note is zero (deactivated);
  if(note == 0) return;
  
  Serial.print(note);
  Serial.print(":");
  Serial.println(velocity);
  if(velocity > 127) velocity = MAX_MIDI_VELOCITY;
  usbMIDI.sendNoteOn(note, velocity, CHANNEL);
  usbMIDI.sendNoteOff(note, velocity, CHANNEL);
}

