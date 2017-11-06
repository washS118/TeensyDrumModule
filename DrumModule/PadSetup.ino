/*******************************************
 * sets up the pads using parrallel arrays *
 * pad order is as follows                 *
 * kick ----------- 35                     *
 * snare ---------- 38                     *
 * hi-tom --------- 50                     * 
 * hi-mid-tom ----- 48                     *
 * low-floor-tom -- 41                     *
 * crash1 --------- 49                     *
 * crash2 --------- 57                     *
 * ride-bell ------ 53                     *
 * hi-hat --------- 46 (changed by pedal)  *
 *******************************************/

unsigned char notes[] =       {35, 38, 50, 48, 41, 49, 57, 53, 46};    // midi notes for each pad
unsigned char pins[] =        {A0, A1, A2, A3, A4, A5, A6, A7, A8};    // swiched pin for each pad
unsigned int  thresholds[] =  {10, 10, 10, 10, 10, 10, 10, 10, 10};    // pad thresholds

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

