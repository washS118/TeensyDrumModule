#include <MIDI.h>

#define threshold 10
#define delayAfterHit 150
#define channel 1

struct PadData {
  int note;
  int pin;
  int prev;
  int val;
  bool isOn;
  bool hasHit;
};

const int numReadings = 10;     // larger values results in more smoothing but lower sensitivity

int total = 0;                  // the running total
int average = 0;                // the average
int readIndex = 0;              // the current index in readings;

const int numPads = 2;

struct PadData *pads[numPads];
struct PadData snare;
struct PadData hiTom;

void setup() {
  //Initialize Comms
  usbMIDI.begin();
  Serial.begin(38400);

  //Initialize Pads
  snare.note = 38;
  snare.pin = 0;
  snare.isOn = false;

  hiTom.note = 48;
  hiTom.pin = 1;
  hiTom.isOn = false;

  //Initialize pad array
  pads[0] = &snare;
  pads[1] = &hiTom;
}

void loop() {
  collectVelocities();
  processHits();
  
  //Dispose of Midi input
  while(usbMIDI.read());
}

//Input value
int val = 0;
int high = 0;

void collectVelocities(){
  for(int i = 0; i < numPads; i++){ 
    //Update previous reading
    pads[i]->prev = pads[i]->val;
    pads[i]->val = 0;

    //Reset smoothing algo;
    total = 0;
    high = 0;
    readIndex = 0;

    //Update Readings
    while(readIndex < numReadings){
      val = analogRead(pads[i]->pin);
      total += val;

      if(high < val) high = val;
      readIndex++;
    }

    //Find average
    if(total/numReadings >= threshold){
      pads[i]->val = high;
    }else{
      pads[i]->val = 0;
    }

    
  }
}

bool hitOnPass;
void processHits(){
  int i;
  hitOnPass = false;

  //Loop through each pad and send hit at peaks;
  for(i = 0; i < numPads; i++){
    if(pads[i]->val > pads[i]->prev){
        pads[i]->hasHit = false;
    }else if(!pads[i]->hasHit){
        if(pads[i]->val >= threshold){
          Serial.print("Pad ");
          Serial.print(pads[i]->note);
          Serial.print(" was hit with val ");
          Serial.println(pads[i]->val);
        
  
          usbMIDI.sendNoteOn(pads[i]->note, pads[i]->val, channel);
          pads[i]->isOn = true;
          pads[i]->hasHit = true;
          hitOnPass = true;
        }
     }
  }

  //Pause to allow sensors to drop below peak
  if(hitOnPass){
    delay(delayAfterHit);
  }

  //Shut off any pads that were hit
  for(i = 0; i < numPads; i++){
    if(pads[i]->isOn) {
      usbMIDI.sendNoteOff(pads[i]->note, pads[i]->val, channel);
      pads[i]->isOn = false;
    }
  }
}

