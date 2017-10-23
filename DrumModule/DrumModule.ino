#include <MIDI.h>

#define NUM_PADS 2                            // how many pads are supported by the controller
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
}PadData;

PadData pads[NUM_PADS];                       // container for all pads

/**************************
 * program initialization *
 **************************/
void setup() {
  setupPads();
  setupSwitchArray();
}

/*************
 * main loop *
 *************/
void loop() {
  //TODO
}

/*********************************************
 * get input and update specified pad buffer *
 *********************************************/
void updatePad(PadData *pad){
  //TODO
}

