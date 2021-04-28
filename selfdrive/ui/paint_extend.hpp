#pragma once
#include "ui.hpp"

//Pon 20210407 Add HUD UI
const int hud_infobar_h = 80;

const int hud_blindspot_w = 200;  //For Adam, Large = 400

const int hud_top_1_x = 270;
const int hud_top_1_y = 80;
const int hud_top_1_w = 180;
const int hud_top_1_h = 180;

const int hud_top_2_x = 470;
const int hud_top_2_y = 80;
const int hud_top_2_w = 180;
const int hud_top_2_h = 180;

const int hud_top_3_x = 1250;
const int hud_top_3_y = 80;
const int hud_top_3_w = 180;
const int hud_top_3_h = 180;

const int hud_top_4_x = 1450;
const int hud_top_4_y = 80;
const int hud_top_4_w = 180;
const int hud_top_4_h = 180;

const int hud_left_1_x = 60;
const int hud_left_1_y = 300;
const int hud_left_1_w = 180;
const int hud_left_1_h = 180;

const int hud_left_2_x = 60;
const int hud_left_2_y = 500;
const int hud_left_2_w = 180;
const int hud_left_2_h = 180;

const int hud_right_1_x = 1650;
const int hud_right_1_y = 300;
const int hud_right_1_w = 180;
const int hud_right_1_h = 180;

const int hud_right_2_x = 1650;
const int hud_right_2_y = 500;
const int hud_right_2_w = 180;
const int hud_right_2_h = 180;

void ui_draw_hud(UIState *s);

