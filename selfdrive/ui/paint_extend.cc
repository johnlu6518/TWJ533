#include "common/swaglog.h"
#include "paint_extend.hpp"
#include "ui.hpp"
#include <math.h>



//===== draw box/title/value/unit =====
void ui_draw_hud_text(UIState *s,
                        const int x,
                        const int y,
                        const char* font_string,
                        const int font_size,
                        const NVGcolor font_color) {
  nvgFontSize(s->vg, font_size);
  nvgFillColor(s->vg, font_color);
  nvgTextAlign(s->vg, NVG_ALIGN_LEFT|NVG_ALIGN_TOP);
  nvgText(s->vg, x, y, font_string, NULL);
}
void ui_draw_hud_box(UIState *s,
                    const int x,
                    const int y,
                    const int w,
                    const int h) {
  nvgBeginPath(s->vg);
  nvgRoundedRect(s->vg, x, y, h, w, 20);
  nvgStrokeColor(s->vg, COLOR_WHITE_ALPHA(80));
  nvgStrokeWidth(s->vg, 6);
  nvgStroke(s->vg);
}
void ui_draw_hud_title(UIState *s,
                        const int x,
                        const int y,
                        const int w,
                        const int h,
                        const char* font_string,
                        const int font_size,
                        const NVGcolor font_color,
                        const NVGalign font_algin) {
  nvgFontSize(s->vg, font_size);
  nvgFillColor(s->vg, font_color);
  nvgTextAlign(s->vg, NVG_ALIGN_CENTER);
  nvgText(s->vg, x + w / 2, y + 40, font_string, NULL);
}
void ui_draw_hud_value(UIState *s,
                        const int x,
                        const int y,
                        const int w,
                        const int h,
                        const char* font_string,
                        const int font_size,
                        const NVGcolor font_color,
                        const NVGalign font_algin) {
  nvgFontSize(s->vg, font_size);
  nvgFillColor(s->vg, font_color);
  nvgTextAlign(s->vg, NVG_ALIGN_CENTER);
  nvgText(s->vg, x + w / 2, y + h - 70, font_string, NULL);
}

void ui_draw_hud_unit(UIState *s,
                        const int x,
                        const int y,
                        const int w,
                        const int h,
                        const char* font_string,
                        const int font_size,
                        const NVGcolor font_color,
                        const NVGalign font_algin) {
  nvgFontSize(s->vg, font_size);
  nvgFillColor(s->vg, font_color);
  nvgTextAlign(s->vg, NVG_ALIGN_CENTER);
  nvgText(s->vg, x + w / 2, y + h - 20, font_string, NULL);
}

void ui_draw_hud_infobox(UIState *s,
                        const int x,
                        const int y,
                        const int w,
                        const int h,
                        const char* title_font_string,
                        const int title_font_size,
                        const NVGcolor title_font_color,
                        const NVGalign title_font_algin,
                        const char* value_font_string,
                        const int value_font_size,
                        const NVGcolor value_font_color,
                        const NVGalign value_font_algin,
                        const char* unit_font_string,
                        const int unit_font_size,
                        const NVGcolor unit_font_color,
                        const NVGalign unit_font_algin) {
  ui_draw_hud_box(s, x, y, w, h);
  ui_draw_hud_title(s, x, y, w, h, title_font_string, title_font_size, title_font_color, title_font_algin);
  ui_draw_hud_value(s, x, y, w, h, value_font_string, value_font_size, value_font_color, value_font_algin);
  ui_draw_hud_unit(s, x, y, w, h, unit_font_string, unit_font_size, unit_font_color, unit_font_algin);
}

//===== draw top hud 1/2/3/4 =====
void ui_draw_top_hud_infobox1(UIState *s) {
  int sidebar_fit_x = 0;
  char value[16];
  NVGcolor value_font_color = COLOR_WHITE_ALPHA(200);
  float steeringTorque = s->scene.car_state.getSteeringTorque();
  
  //Fit sidebar screen
  sidebar_fit_x = s->viz_rect.x + hud_top_1_x;

  if(((int)(steeringTorque) < -40) || ((int)(steeringTorque) > 40)) {
    value_font_color = nvgRGBA(255, 188, 3, 200);
  }
  if(((int)(steeringTorque) < -80) || ((int)(steeringTorque) > 80)) {
    value_font_color = nvgRGBA(255, 0, 0, 200);
  }


  //value
  snprintf(value, sizeof(value), "%.2f°",(steeringTorque));
  ui_draw_hud_infobox(s, sidebar_fit_x, hud_top_1_y, hud_top_1_w, hud_top_1_h,
                        "Steer Torque", 36, COLOR_WHITE, NVG_ALIGN_CENTER,
                        value, 64, COLOR_WHITE, NVG_ALIGN_CENTER,
                        "Nm", 48, COLOR_WHITE, NVG_ALIGN_CENTER);
}

void ui_draw_top_hud_infobox2(UIState *s) {
  int sidebar_fit_x = 0;
  char value[16];
  NVGcolor value_font_color = COLOR_WHITE_ALPHA(200);

  //Fit sidebar screen
  sidebar_fit_x = s->viz_rect.x + hud_top_2_x;

  if(s->scene.car_control.getActuators().getBrake()>0) {
    //OP Brake
    value_font_color = nvgRGBA(255, 0, 0, 200);
    snprintf(value, sizeof(value), "%.2f°",(s->scene.car_control.getActuators().getBrake()));
    ui_draw_hud_infobox(s, sidebar_fit_x, hud_top_2_y, hud_top_2_w, hud_top_2_h,
                        "OP Brake", 36, COLOR_WHITE, NVG_ALIGN_CENTER,
                        value, 64, COLOR_WHITE, NVG_ALIGN_CENTER,
                        "", 48, COLOR_WHITE, NVG_ALIGN_CENTER);
  } else {
    //OP Gas
    value_font_color = nvgRGBA(255, 188, 3, 200);
    snprintf(value, sizeof(value), "%.2f°",(s->scene.car_control.getActuators().getGas()));
    ui_draw_hud_infobox(s, sidebar_fit_x, hud_top_2_y, hud_top_2_w, hud_top_2_h,
                        "OP Gas", 36, COLOR_WHITE, NVG_ALIGN_CENTER,
                        value, 64, COLOR_WHITE, NVG_ALIGN_CENTER,
                        "", 48, COLOR_WHITE, NVG_ALIGN_CENTER);
  }
}

void ui_draw_top_hud_infobox3(UIState *s) {
  char value[16];

  //value
  snprintf(value, sizeof(value), "%.2f°",(s->scene.car_control.getActuators().getSteer()));
  ui_draw_hud_infobox(s, hud_top_3_x, hud_top_3_y, hud_top_3_w, hud_top_3_h,
                        "OP Steer", 36, COLOR_WHITE, NVG_ALIGN_CENTER,
                        value, 64, COLOR_WHITE, NVG_ALIGN_CENTER,
                        "", 48, COLOR_WHITE, NVG_ALIGN_CENTER);
}

void ui_draw_top_hud_infobox4(UIState *s) {
   char value[16];

  //value
  snprintf(value, sizeof(value), "%.2f°",(s->scene.car_control.getActuators().getSteeringAngleDeg()));
  ui_draw_hud_infobox(s, hud_top_4_x, hud_top_4_y, hud_top_4_w, hud_top_4_h,
                        "OP Angle", 36, COLOR_WHITE, NVG_ALIGN_CENTER,
                        value, 64, COLOR_WHITE, NVG_ALIGN_CENTER,
                        "", 48, COLOR_WHITE, NVG_ALIGN_CENTER);
}


//===== draw hud top/bottom/left/right
void ui_draw_top_hud(UIState *s) {

  ui_draw_top_hud_infobox1(s);
  ui_draw_top_hud_infobox2(s);
  ui_draw_top_hud_infobox3(s);
  ui_draw_top_hud_infobox4(s);
}

void ui_draw_bottom_hud(UIState *s) {
  //Empty function
}

void ui_draw_left_hud_infobox1(UIState *s) {
  int sidebar_fit_x = 0;
  char value[16];
  NVGcolor value_font_color = COLOR_WHITE_ALPHA(200);
  float steeringAngleDeg = s->scene.car_state.getSteeringAngleDeg();

  //Fit sidebar screen
  sidebar_fit_x = s->viz_rect.x + hud_left_1_x;

  //show Orange if more than 15 degrees
  //show red if  more than 30 degrees
  if(((int)(steeringAngleDeg) < -15) || ((int)(steeringAngleDeg) > 15)) {
    value_font_color = nvgRGBA(255, 188, 3, 200);
  }
  if(((int)(steeringAngleDeg) < -30) || ((int)(steeringAngleDeg) > 30)) {
    value_font_color = nvgRGBA(255, 0, 0, 200);
  }

  //value
  snprintf(value, sizeof(value), "%.2f°",(steeringAngleDeg));
  ui_draw_hud_infobox(s, sidebar_fit_x, hud_left_1_y, hud_left_1_w, hud_left_1_h,
                        "Steer Angle", 36, COLOR_WHITE, NVG_ALIGN_CENTER,
                        value, 64, value_font_color, NVG_ALIGN_CENTER,
                        "degree", 48, COLOR_WHITE, NVG_ALIGN_CENTER);
}

void ui_draw_left_hud_infobox2(UIState *s) {
  int sidebar_fit_x = 0;
  char value[16];
  NVGcolor value_font_color = COLOR_WHITE_ALPHA(200);
  float steeringAngleDesiredDeg = s->scene.controls_state.getSteeringAngleDesiredDeg();
  
  //Fit sidebar screen
  sidebar_fit_x = s->viz_rect.x + hud_left_2_x;

  if(((int)(steeringAngleDesiredDeg) < -15) || ((int)(steeringAngleDesiredDeg) > 15)) {
    value_font_color = nvgRGBA(255, 188, 3, 200);
  }
  if(((int)(steeringAngleDesiredDeg) < -30) || ((int)(steeringAngleDesiredDeg) > 30)) {
    value_font_color = nvgRGBA(255, 0, 0, 200);
  }


  //value
  snprintf(value, sizeof(value), "%.2f°",(steeringAngleDesiredDeg));
  ui_draw_hud_infobox(s, sidebar_fit_x, hud_left_2_y, hud_left_2_w, hud_left_2_h,
                        "Desired Angle", 24, COLOR_WHITE, NVG_ALIGN_CENTER,
                        value, 64, COLOR_WHITE, NVG_ALIGN_CENTER,
                        "Degree", 48, COLOR_WHITE, NVG_ALIGN_CENTER);
}

void ui_draw_left_hud(UIState *s) {
  ui_draw_left_hud_infobox1(s);
  ui_draw_left_hud_infobox2(s);
}

void ui_draw_right_hud_infobox1(UIState *s) {
  if(s->scene.car_state.getSteeringPressed()) {
      ui_draw_hud_infobox(s, hud_right_1_x, hud_right_1_y, hud_right_1_w, hud_right_1_h,
                        "Steer Press", 36, COLOR_WHITE, NVG_ALIGN_CENTER,
                        "User", 64, COLOR_YELLOW, NVG_ALIGN_CENTER,
                        "", 48, COLOR_WHITE, NVG_ALIGN_CENTER);

  } else {
      ui_draw_hud_infobox(s, hud_right_1_x, hud_right_1_y, hud_right_1_w, hud_right_1_h,
                        "Steer Press", 36, COLOR_WHITE, NVG_ALIGN_CENTER,
                        "none", 64, COLOR_WHITE, NVG_ALIGN_CENTER,
                        "", 48, COLOR_WHITE, NVG_ALIGN_CENTER);
  }
}

void ui_draw_right_hud_infobox2(UIState *s) {
  char value[16];
  if(s->scene.car_state.getBrake()>0) {
      snprintf(value, sizeof(value), "%.2f°", s->scene.car_state.getBrake());
      ui_draw_hud_infobox(s, hud_right_2_x, hud_right_2_y, hud_right_2_w, hud_right_2_h,
                        "User G/B", 36, COLOR_WHITE, NVG_ALIGN_CENTER,
                        value, 64, COLOR_RED, NVG_ALIGN_CENTER,
                        "", 48, COLOR_WHITE, NVG_ALIGN_CENTER);  
  } else {
    if(s->scene.car_state.getGasPressed()) {
        ui_draw_hud_infobox(s, hud_right_2_x, hud_right_2_y, hud_right_2_w, hud_right_2_h,
                          "User G/B", 36, COLOR_WHITE, NVG_ALIGN_CENTER,
                          "Pressed", 64, COLOR_YELLOW, NVG_ALIGN_CENTER,
                          "", 48, COLOR_WHITE, NVG_ALIGN_CENTER);  
    } else {
        ui_draw_hud_infobox(s, hud_right_2_x, hud_right_2_y, hud_right_2_w, hud_right_2_h,
                          "User G/B", 36, COLOR_WHITE, NVG_ALIGN_CENTER,
                          "none", 64, COLOR_WHITE, NVG_ALIGN_CENTER,
                          "", 48, COLOR_WHITE, NVG_ALIGN_CENTER);  
    }
  }
}

void ui_draw_right_hud(UIState *s) {
  ui_draw_right_hud_infobox1(s);
  ui_draw_right_hud_infobox2(s);
}

void ui_draw_info_text(UIState *s) {
   int sidebar_fit_x = s->viz_rect.x + 5;
   
   char infotext1[100];
   snprintf(infotext1, sizeof(infotext1), "upAccelCmd:%.2f/uiAccelCmd:%.2f/ufAccelCmd:%.2f", s->scene.controls_state.getUpAccelCmd() , s->scene.controls_state.getUiAccelCmd(), s->scene.controls_state.getUfAccelCmd());
   ui_draw_hud_text(s, sidebar_fit_x, 5, infotext1, 72, COLOR_YELLOW_APPHA(200));
   
}

void ui_draw_infobar(UIState *s) {
  const int x = s->viz_rect.x;
  const int y = s->viz_rect.bottom() - hud_infobar_h;
  const int w = s->viz_rect.w;
  const int text_x = w / 2 + x;
  const int text_y = y + 55;
  const bool brakeLights = s->scene.car_state.getBrakeLights();

  char infobar[100];
  // create time string
  char date_time[20];
  time_t rawtime = time(NULL);
  struct tm timeinfo;
  localtime_r(&rawtime, &timeinfo);
  strftime(date_time, sizeof(date_time),"%D %T", &timeinfo);
  //snprintf(infobar, sizeof(infobar), "%s", date_time);
  //snprintf(infobar, sizeof(infobar), "%s/FP:%s/SteerControl:%u", date_time, s->scene.car_params.getCarFingerprint().cStr() , (unsigned int) s->scene.car_params.getSteerControlType());
  snprintf(infobar, sizeof(infobar), "%s/MESpeed:%f/SteerControl:%u/FP:%s", date_time, s->scene.car_params.getMinEnableSpeed() , (unsigned int) s->scene.car_params.getSteerControlType(), s->scene.car_params.getCarFingerprint().cStr());



  nvgBeginPath(s->vg);
  nvgRect(s->vg, x, y, w, hud_infobar_h);
  nvgFillColor(s->vg, (brakeLights? COLOR_RED_ALPHA(200) : COLOR_BLACK_ALPHA(150)));
  nvgFill(s->vg);

  nvgFillColor(s->vg, COLOR_WHITE_ALPHA(200));
  nvgTextAlign(s->vg, NVG_ALIGN_CENTER);
  nvgText(s->vg, text_x, text_y, infobar, NULL);
}

void ui_draw_blinker(UIState *s) {
  // dp blinker, from kegman
  const int viz_blinker_w = 280;
  const int viz_blinker_x = s->viz_rect.centerX() - viz_blinker_w/2;
  const bool leftBlinker = s->scene.car_state.getLeftBlinker();
  const bool rightBlinker = s->scene.car_state.getRightBlinker();
  if(leftBlinker) {
    nvgBeginPath(s->vg);
    nvgMoveTo(s->vg, viz_blinker_x, s->viz_rect.y + header_h/4);
    nvgLineTo(s->vg, viz_blinker_x - viz_blinker_w/2, s->viz_rect.y + header_h/4 + header_h/4);
    nvgLineTo(s->vg, viz_blinker_x, s->viz_rect.y + header_h/2 + header_h/4);
    nvgClosePath(s->vg);
    nvgFillColor(s->vg, nvgRGBA(0,255,0,s->scene.ui_extend.blinker_blinkingrate>=60?190:30));
    nvgFill(s->vg);
  }
  if(rightBlinker) {
    nvgBeginPath(s->vg);
    nvgMoveTo(s->vg, viz_blinker_x+viz_blinker_w, s->viz_rect.y + header_h/4);
    nvgLineTo(s->vg, viz_blinker_x+viz_blinker_w + viz_blinker_w/2, s->viz_rect.y + header_h/4 + header_h/4);
    nvgLineTo(s->vg, viz_blinker_x+viz_blinker_w, s->viz_rect.y + header_h/2 + header_h/4);
    nvgClosePath(s->vg);
    nvgFillColor(s->vg, nvgRGBA(0,255,0,s->scene.ui_extend.blinker_blinkingrate>=60?190:30));
    nvgFill(s->vg);
  }
  if(leftBlinker || rightBlinker) {
    s->scene.ui_extend.blinker_blinkingrate -= 3;
    if(s->scene.ui_extend.blinker_blinkingrate<0) s->scene.ui_extend.blinker_blinkingrate = 120;
  }
}

void ui_draw_blindspot(UIState *s) {
  const int y = s->viz_rect.bottom() - hud_blindspot_w;
  const bool leftBlindspot = s->scene.car_state.getLeftBlindspot();
  const bool rightBlindspot = s->scene.car_state.getRightBlindspot();;

  if (leftBlindspot) {
    const int left_x = s->viz_rect.x;
    nvgBeginPath(s->vg);
    nvgMoveTo(s->vg, left_x, y);
    nvgLineTo(s->vg, left_x, y+hud_blindspot_w);
    nvgLineTo(s->vg, left_x+hud_blindspot_w, y+hud_blindspot_w);
    nvgClosePath(s->vg);
    nvgFillColor(s->vg, COLOR_YELLOW_APPHA(200));
    nvgFill(s->vg);
  }

  if (rightBlindspot) {
    const int right_x = s->viz_rect.right();
    nvgBeginPath(s->vg);
    nvgMoveTo(s->vg, right_x, y);
    nvgLineTo(s->vg, right_x, y+hud_blindspot_w);
    nvgLineTo(s->vg, right_x-hud_blindspot_w, y+hud_blindspot_w);
    nvgClosePath(s->vg);
    nvgFillColor(s->vg, COLOR_YELLOW_APPHA(200));
    nvgFill(s->vg);
  }
}

//===== draw hud =====
void ui_draw_hud(UIState *s) {
  ui_draw_info_text(s);
  ui_draw_top_hud(s);
  ui_draw_bottom_hud(s);
  ui_draw_left_hud(s);
  ui_draw_right_hud(s);
  ui_draw_infobar(s);
  ui_draw_blindspot(s);
  ui_draw_blinker(s);
}
