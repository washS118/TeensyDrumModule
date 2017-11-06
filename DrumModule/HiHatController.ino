unsigned char cymbalIndex = 8;
unsigned char hatController = A9;
unsigned char openNote = 46;                    // midi note for open hat
unsigned char closedNote = 42;                  // midi note for closed hat
unsigned int  hatThreshold = 10;                // the cymbal's threshold
unsigned int  hatBuffer[BUFFER_SIZE];           // the buffer containing the raw analog values
unsigned char hatIndex = 0;                     // specifies which index is the most recent
unsigned int  lastHitTime = 0;                  // the millisecond the pad was last hit on
unsigned int  currentMax = 0;                   // the current maximum value in the buffer

void setupHiHat(){
  pinMode(hatController, INPUT);
  memset(hatBuffer, 0, sizeof(hatBuffer));
}

void updateHat(){
  if(digitalRead(hatController) == HIGH){
    pads[hatIndex].note = closedNote;
  }else{
    pads[hatIndex].note = openNote;
  }
}

void calculateHat(){
  if(currentMax >= hatThreshold){
    unsigned int time = millis();
    unsigned int timeSinceHit = time - lastHitTime;
    if(timeSinceHit > MIN_TIME_BETWEEN_NOTES){
      lastHitTime = time;
      if(digitalRead(hatController)) playMidiNote(closedNote, currentMax);
      else playMidiNote(openNote, currentMax);
    }
  }
}

