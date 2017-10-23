/*******************************************
 * sets up the pads using parrallel arrays *
 * pad order is as follows                 *
 * kick,snare                              *
 *******************************************/

unsigned char notes[] =       { 35, 38};
unsigned char pins[] =        {  0,  1};
unsigned int  thresholds[] =  {100, 10};

void setupPads(){
  for(int i = 0; i < NUM_PADS; i++){
    pads[i].note = notes[i];
    pads[i].pin = pins[i];
    pads[i].threshold = thresholds[i];
    
    memset(&pads[i].inputBuffer, 0, sizeof(pads[i].inputBuffer));
    pads[i].bufferIndex = 0;
    pads[i].lastHitTime = 0;
  }
}

