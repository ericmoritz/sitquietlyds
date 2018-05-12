#include "main.h"
#include "timer.h"

MeditationTimer::MeditationTimer() {
  this->settle_seconds = DEFAULT_SETTLE;
  this->sit_minutes = DEFAULT_SIT;
  this->stop(); // Start stopped
}

void MeditationTimer::start(u32 start_tick) {
  this->start_tick = start_tick;
  this->stage = STAGE_SETTLE;
}
int MeditationTimer::on() {
  return this->stage != STAGE_OFF;
}

void MeditationTimer::stop() {
  this->stage = STAGE_OFF;
  this->start_tick = 0;
  this->current_tick = 0;
}

void MeditationTimer::update(u32 current_tick) {
  this->current_tick = current_tick;
  u32 elapsed_seconds = (this->current_tick - this->start_tick) / 1000;
  u32 elapsed_minutes = elapsed_seconds / 60;
  
  // Check for a stage flip
  if(this->stage == STAGE_SETTLE && elapsed_seconds >= this->settle_seconds) {
    // Switch stage
    this->stage = STAGE_SIT;
    // Return the new stage
  } else if (this->stage == STAGE_SIT && elapsed_minutes >= this->sit_minutes){
    this->stop();
  } 
  
  
}

u32 MeditationTimer::elapsed() {
  if(this->on()) 
    return this->current_tick - this->start_tick;
  else
    return 0;
}

u32 MeditationTimer::remaining() {
  u32 remaining = (this->sit_minutes * 60000) - this->elapsed();
  return remaining >= 0 ? remaining : 0;
}



