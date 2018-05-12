// Includes
#include <PA9.h>
#include <stdlib.h>
#include <time.h>

#include "bell.h"
#include "main.h"
#include "timer.h"
#include "ui.h"

int timer_id;

MeditationTimer *meditation_timer;
MeditationTimerUI *ui;

void sync_timer(u32 tick) {
    // Sync the timer and ui
    meditation_timer->settle_seconds = ui->settle_seconds;
    meditation_timer->sit_minutes = ui->sit_minutes;

    if(ui->is_started() && !meditation_timer->on()) {
      // Start the timer
      meditation_timer->start(tick);
    } else if(!ui->is_started() && meditation_timer->on()) {
      // Stop the timer
      meditation_timer->stop();
    }
}

void sync_ui(int old_stage, int new_stage) {
  // Draw the clock
  ui->draw_clock(meditation_timer->remaining());

  // React to the timer
  if(old_stage && old_stage != new_stage) {
    switch(new_stage) {
    case STAGE_SIT: // When the stage changes to sit, play the bell
      AS_SoundQuickPlay(bell);
      break;
    case STAGE_OFF: // When the stage changes to off, play the finish bell
      AS_SoundQuickPlay(bell);
      ui->stop();
      break;
    }
  }
}
// Function: main()
int main(int argc, char ** argv)
{
  PA_Init();    // Initializes PA_Lib
  PA_InitVBL(); // Initializes a standard VBL
  //PA_InitSound();
  //PA_InitASLibForSounds(AS_MODE_SURROUND | AS_MODE_16CH);
  AS_SetDefaultSettings(AS_PCM_16BIT, 44100, AS_SURROUND);
  
  StartTime(true);
  timer_id = NewTimer(true);
  
  meditation_timer = new MeditationTimer();
  ui = new MeditationTimerUI();
  
  // Infinite loop to keep the program running
  while (1) {
    u32 tick = Tick(timer_id);
    int old_stage = 0;
    int new_stage = 0;

    // Respond to user
    ui->respond();

    // Sync the timer with the ui
    sync_timer(tick);

    // Update the timer if it's on, update it
    if(meditation_timer->on()) {
      old_stage = meditation_timer->stage;
      meditation_timer->update(tick);
      new_stage = meditation_timer->stage;
    }

    // Sync the UI with the timer 
    sync_ui(old_stage, new_stage);

    PA_WaitForVBL();
      
  }

    
  return 0;
} // End of main()
