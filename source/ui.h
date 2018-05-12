#ifndef MEDIATIONTIMERUI_H
#define MEDIATIONTIMERUI_H

#include <PA9.h>
#include "timer.h"


class MeditationTimerUI {
 public:
  MeditationTimerUI();
  void respond();
  void draw_clock(u32 ms);
  void start();
  void stop();
  int is_started();

  // State variables
  int settle_seconds;
  int sit_minutes;  
 private:
  int __is_started;

  void init_buttons();
  void track_inputs();
  void draw_text();
  void on_timer_stop();
  void button_down(int i);
  void button_held(int i);
  void button_released(int i);
  void button_up(int i);  

  void push_button(int i);
  void toggle_button(int i);

  void draw_labels();  
  void time_string(char buffer[8], u32 ms);  
};


#define BUTTON_COUNT 5
#define BUTTON_IDX_DECREASE_SETTLE 0
#define BUTTON_IDX_INCREASE_SETTLE 1
#define BUTTON_IDX_INCREASE_SIT 2
#define BUTTON_IDX_DECREASE_SIT 3
#define BUTTON_IDX_START 4

#define BUTTON_TIMEOUT 8


#endif
