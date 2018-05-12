#include "ui.h"
#include "gfx/all_gfx.c"
#include "main.h"


MeditationTimerUI::MeditationTimerUI() {
  this->settle_seconds = DEFAULT_SETTLE;
  this->sit_minutes = DEFAULT_SIT;

  PA_Init8bitBg(1,3);
  PA_Load8bitBgPal(1,(void *)mandala_Pal);
  PA_Load8bitBitmap(1,(void *)mandala_Bitmap);

  PA_Init8bitBg(0,3);
  PA_Load8bitBgPal(0, (void *)lotus_Pal);
  PA_Load8bitBitmap(0,(void *)lotus_Bitmap);

  PA_InitText(0, 2);
  PA_InitText(1, 2);  
  this->init_buttons();
  
}

void MeditationTimerUI::respond() {
  // Gather The Inputs
  this->track_inputs();
  this->draw_labels();
}

void MeditationTimerUI::start() {
      PA_SetSpriteAnim(0,BUTTON_IDX_START,1);
      this->__is_started = 1;
}
void MeditationTimerUI::stop() {
      this->__is_started = 0;
      PA_SetSpriteAnim(0,BUTTON_IDX_START,0);      
}

int MeditationTimerUI::is_started() {
  return this->__is_started;
}

void MeditationTimerUI::init_buttons() {
   PA_LoadSpritePal(0,
		    0,
		    (void*)buttons_Pal);

   PA_LoadSpritePal(0,
		    1,
		    (void*)bigbutton_Pal);


   PA_CreateSprite(0,
		   BUTTON_IDX_DECREASE_SETTLE, // sprite index
		   (void *)buttons_Sprite,
		   OBJ_SIZE_32X32,
		   1, // 256
		   0, // Palette
		   45, 
		   100);

   PA_CreateSprite(0,
		   BUTTON_IDX_INCREASE_SETTLE, // sprite index
		   (void *)buttons_Sprite,
		   OBJ_SIZE_32X32,
		   1, // 256
		   0, // Palette
		   180, 
		   100);
   PA_SetSpriteHflip(0, 1, 1);

   PA_CreateSprite(0,
		   BUTTON_IDX_INCREASE_SIT, // sprite index
		   (void *)buttons_Sprite,
		   OBJ_SIZE_32X32,
		   1, // 256
		   0, // Palette
		   180, 
		   150);
   PA_SetSpriteHflip(0, 2, 1);

   PA_CreateSprite(0,
		   BUTTON_IDX_DECREASE_SIT, // sprite index
		   (void *)buttons_Sprite,
		   OBJ_SIZE_32X32,
		   1, // 256
		   0, // Palette
		   45, 
		   150);

   PA_CreateSprite(0,
		   BUTTON_IDX_START, // sprite index
		   (void *)bigbutton_Sprite,
		   OBJ_SIZE_64X64,
		   1, // 256
		   1, // Palette
		   96, 
		   32);


}

void MeditationTimerUI::track_inputs() {
    int i; 
    
    for(i = 0; i < BUTTON_COUNT; i++) {
      if(Stylus.Newpress && PA_SpriteStylusOver(i)) {	
	this->button_down(i);
      } else if(Stylus.Held && PA_SpriteStylusOver(i)) {	
	this->button_held(i);
      } else if(Stylus.Released && PA_SpriteStylusOver(i)) {
	this->button_released(i);
      } else {
	this->button_up(i);
      }
    }

    if(Pad.Released.Start && !this->is_started()) {
      this->start();
    }else if (Pad.Released.Start && this->is_started()) {
      this->stop();
    }
}

void MeditationTimerUI::button_down(int i) {
  PA_SetSpriteAnim(0,i,1);
  
  this->push_button(i);
  this->toggle_button(i);
  
}

void MeditationTimerUI::button_held(int i) {
  int sample_rate = 8;
  if(Stylus.Downtime % sample_rate) return;
  button_down(i);

}

void MeditationTimerUI::button_released(int i) {
  button_up(i);
}

void MeditationTimerUI::button_up(int i) {
  // Only reset this for the button toggle buttons
  if(i < 4)
    PA_SetSpriteAnim(0,i,0);
}

// This is a button to keep track of the button clicks
void MeditationTimerUI::toggle_button(int i) {
  if(i < 4) return;
  switch(i) {
  case BUTTON_IDX_START: 
    if(!this->is_started()) {
      this->start();
    } else {
      this->stop();
    }
    break;
  }
}


void MeditationTimerUI::push_button(int i) {
  
  if(i > 3) return;

  switch(i) {
  case 0:
    this->settle_seconds--;
    break;
  case 1:
    this->settle_seconds++;
    break;
  case 2:
    this->sit_minutes++;
    break;
  case 3:
    this->sit_minutes--;
    break;
  }
  
  if(this->sit_minutes <= 0) this->sit_minutes = 1;
  if(this->settle_seconds <= 0) this->settle_seconds = 1;	
  
  if(this->sit_minutes > SIT_MAX) this->sit_minutes = SIT_MAX;
  if(this->settle_seconds > SETTLE_MAX) 
    this->settle_seconds = SETTLE_MAX; 
  button_up(i);
}


void MeditationTimerUI::time_string(char buffer[8], u32 ms) {
  unsigned int minutes = (unsigned int)(ms / 1000) / 60;  
  unsigned int seconds = (unsigned int)(ms / 1000) % 60;

  if(ms) {
    minutes = (unsigned int)(ms / 1000) / 60;  
    seconds = (unsigned int)(ms / 1000) % 60;
  } else {
    minutes = 0;
    seconds = 0;
  }
  
  sprintf(buffer, "%3u:%02u", minutes, seconds);

}

void MeditationTimerUI::draw_labels() {
  char number_str[4];

  PA_OutputText(0, 5, 12, "Settle for");
  sprintf(number_str, "%3u", (unsigned int)this->settle_seconds);
  PA_OutputText(0, 11, 14, "%s Seconds", number_str);

  PA_OutputText(0, 5, 18, "Then sit for");
  sprintf(number_str, "%3u", (unsigned int)this->sit_minutes);  
  PA_OutputText(0, 11, 20, "%s Minutes", number_str);
}


void MeditationTimerUI::draw_clock(u32 ms) {
  char time_string[8];
  this->time_string(time_string, ms);
  PA_OutputText(1, 12, 11, time_string);  
}
