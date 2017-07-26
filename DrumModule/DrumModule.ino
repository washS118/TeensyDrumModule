#include <MIDI.h>

#define threshold 10
#define delayAfterHit 100
#define channel 1
#define pin 0

struct PadData {
  int note;
  bool isOn;
};

const int numReadings = 10;     // larger values results in more smoothing but lower sensitivity

int readings[numReadings];      // the readings
int total = 0;                  // the running total
int average = 0;                // the average
int readIndex = 0;              // the current index in readings;

struct PadData snare;

void setup() {
  //Initialize Comms
  usbMIDI.begin();
  Serial.begin(38400);

  //Initialize readings
  for(int i = 0; i < numReadings; i++){
    readings[i] = 0;
  }

  //Initialize Pads
  snare.note = 38;
  snare.isOn = false;
}

//Input value
int val = 0;
int prev = 0;
int high = 0;
bool hasHit = false;

void loop() {
  //Track the previous average and get raw input
  prev = average;
  val = analogRead(pin);

  //Update Readings 
  total -= readings[readIndex];
  readings[readIndex] = val;
  total += readings[readIndex];

  //Increment readIndex wrap to match readings
  readIndex++;
  if(readIndex >= numReadings) readIndex = 0;

  //Find average
  average = total / numReadings;
  
  if(average > threshold){
    //Send a hit if at peak
    if(average >= prev){
      hasHit = false;
    }else if(!hasHit){
      //Using raw data in order to get higher MIDI values
      sendHit(&snare,val);
      hasHit = true;
    }
  }

  //Dispose of Midi input
  while(usbMIDI.read());
}

void sendHit(struct PadData *pad, int val){
  Serial.print("Hit with val ");
  Serial.println(val);
  
  usbMIDI.sendNoteOn(pad->note, val, channel);
  delay(delayAfterHit);
  usbMIDI.sendNoteOff(pad->note, val, channel);
}

/*
 * Dear Future Me.
 * Please Try to find a way around this mess.
 * It currently exists because most hits generate
 * two peaks in the data. I have tried increasing
 * the threshold but it ends up killing the sensitivity.
 * Ives also tried increasing the number of readings but
 * it results in the same issues.
 
void sendHit(struct PadData *pad, int val){
  //Swap between on and off on each peak
  if(!pad->isOn){
    usbMIDI.sendNoteOn(pad->note,val,channel);
    Serial.print("HIT with val ");
    Serial.println(val);
  }else{
    usbMIDI.sendNoteOff(pad->note,val,channel);
    Serial.println("Ending Hit");
  }
  pad->isOn = !pad->isOn;
  delay(delayAfterHit);
}
*/

