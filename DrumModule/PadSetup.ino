/*******************************************
 * sets up the pads using parrallel arrays *
 * pad order is as follows                 *
 * deactivated ---- 00                     *
 * kick ----------- 35                     *
 * snare ---------- 38                     * 
 * low-floor-tom -- 41                     *
 * low-tom -------- 45                     *
 * crash1 --------- 49                     *
 * hi-tom --------- 50                     *
 * ride-bow ------- 51                     *          
 * splash --------- 52                     *
 * crash2 --------- 57                     *
 * hi-hat-closed -- 42 (changed by pedal)  *
 * hi-hat-open ---- 46 (changed by pedal)  *
 *******************************************/

 /*
  * thresholds
  * 10+ - functional
  * 00  - disconnected
  * 01  - always hi
  * 02  - tethered to other pad
  */

unsigned char notes[] =           { 35,  38,  50,  45,   0,  49,  42,  51,   0,   0};    // midi notes for each pad
unsigned char pins[] =            { A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7,  A8,  A9};    // swiched pin for each pad
unsigned int  thresholds[] =      { 30,  30,  30,  20,  20,  60, 100,  30,   1,  00};    // pad thresholds
unsigned int  defaultVelocity[] = {127, 127, 127, 127, 127, 050, 127, 127, 127, 127};

/*******************
 * setup pad array *
 *******************/
void setupPads(){
  for(int i = 0; i < NUM_PADS; i++){
    pads[i].note = notes[i];
    pads[i].pin = pins[i];
    pads[i].threshold = thresholds[i];
    pads[i].defaultVelocity = defaultVelocity[i];
    
    memset(&pads[i].inputBuffer, 0, sizeof(pads[i].inputBuffer));
    pads[i].bufferIndex = 0;
    pads[i].lastHitTime = 0;
    pads[i].currentMax  = 0;
  }
}

