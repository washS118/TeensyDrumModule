/*******************************************
 * sets up the pads using parrallel arrays *
 * pad order is as follows                 *
 * kick,snare                              *
 *******************************************/

unsigned char notes[] =       {35, 38};    // midi notes for each pad
unsigned char pins[] =        {A0, A1};    // swiched pin for each pad
unsigned int  thresholds[] =  {10, 10};    // pad thresholds

/*******************
 * setup pad array *
 *******************/
void setupPads(){
  for(int i = 0; i < NUM_PADS; i++){
    pads[i].note = notes[i];
    pads[i].pin = pins[i];
    pads[i].threshold = thresholds[i];
    
    memset(&pads[i].inputBuffer, 0, sizeof(pads[i].inputBuffer));
    pads[i].bufferIndex = 0;
    pads[i].lastHitTime = 0;
    pads[i].currentMax  = 0;
  }
}

