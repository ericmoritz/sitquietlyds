#ifndef MEDITATIONTIMER_H
#define MEDITATIONTIMER_H

#include <PA9.h>

#define STAGE_OFF 0
#define STAGE_SETTLE 1
#define STAGE_SIT 2
#define STAGE_UNCHANGED -1

class MeditationTimer {
  u32 start_tick; // in ms
  u32 current_tick; // in ms
  
 public:
  int stage; // 0 = off, 1 = settle, 2 = sit
  u32 settle_seconds;
  u32 sit_minutes;

  MeditationTimer();
  void start(u32 start_tick);
  void update(u32 current_tick);
  void stop();  
  int on();

  u32 elapsed();
  u32 remaining();
};

#endif
