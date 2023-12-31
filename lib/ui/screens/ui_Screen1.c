// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.1
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "../ui.h"

void ui_Screen1_screen_init(void)
{
ui_Screen1 = lv_obj_create(NULL);
lv_obj_clear_flag( ui_Screen1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_Screen1, 40, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_Screen1, lv_color_hex(0x05915D), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Screen1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_grad_color(ui_Screen1, lv_color_hex(0x055088), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_main_stop(ui_Screen1, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_grad_stop(ui_Screen1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_grad_dir(ui_Screen1, LV_GRAD_DIR_VER, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_speed = lv_arc_create(ui_Screen1);
lv_obj_set_width( ui_speed, 150);
lv_obj_set_height( ui_speed, 150);
lv_obj_set_x( ui_speed, 8 );
lv_obj_set_y( ui_speed, -40 );
lv_obj_set_align( ui_speed, LV_ALIGN_BOTTOM_LEFT );
lv_arc_set_range(ui_speed, 0,299);
lv_arc_set_value(ui_speed, 199);

lv_obj_set_style_bg_color(ui_speed, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_speed, 255, LV_PART_INDICATOR| LV_STATE_DEFAULT);
lv_obj_set_style_bg_grad_color(ui_speed, lv_color_hex(0x0A9F62), LV_PART_INDICATOR | LV_STATE_DEFAULT );

lv_obj_set_style_opa(ui_speed, 0, LV_PART_KNOB| LV_STATE_DEFAULT);

ui_speedText = lv_label_create(ui_Screen1);
lv_obj_set_width( ui_speedText, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_speedText, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_speedText, -56 );
lv_obj_set_y( ui_speedText, 8 );
lv_obj_set_align( ui_speedText, LV_ALIGN_CENTER );
lv_label_set_text(ui_speedText,"199");
lv_obj_set_style_text_color(ui_speedText, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_speedText, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_speedText, &lv_font_montserrat_42, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_kmhText = lv_label_create(ui_Screen1);
lv_obj_set_width( ui_kmhText, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_kmhText, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_kmhText, -57 );
lv_obj_set_y( ui_kmhText, 60 );
lv_obj_set_align( ui_kmhText, LV_ALIGN_CENTER );
lv_label_set_text(ui_kmhText,"km/h");
lv_obj_set_style_text_color(ui_kmhText, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_kmhText, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_kmhText, &lv_font_montserrat_20, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_altitude = lv_img_create(ui_Screen1);
lv_img_set_src(ui_altitude, &ui_img_haiba_png);
lv_obj_set_width( ui_altitude, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_altitude, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_altitude, 32 );
lv_obj_set_y( ui_altitude, -47 );
lv_obj_set_align( ui_altitude, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_altitude, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_altitude, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_localtionText = lv_label_create(ui_Screen1);
lv_obj_set_width( ui_localtionText, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_localtionText, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_localtionText, -58 );
lv_obj_set_y( ui_localtionText, 94 );
lv_obj_set_align( ui_localtionText, LV_ALIGN_CENTER );
lv_label_set_text(ui_localtionText,"SuZhou");
lv_obj_set_style_text_color(ui_localtionText, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_localtionText, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_localtionText, &lv_font_montserrat_16, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_roll = lv_img_create(ui_Screen1);
lv_img_set_src(ui_roll, &ui_img_1869354606);
lv_obj_set_width( ui_roll, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_roll, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_roll, 45 );
lv_obj_set_y( ui_roll, 5 );
lv_obj_set_align( ui_roll, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_roll, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_roll, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_rollText = lv_label_create(ui_Screen1);
lv_obj_set_width( ui_rollText, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_rollText, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_rollText, 102 );
lv_obj_set_y( ui_rollText, 4 );
lv_obj_set_align( ui_rollText, LV_ALIGN_CENTER );
lv_label_set_text(ui_rollText,"3.14°");
lv_obj_set_style_text_color(ui_rollText, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_rollText, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_rollText, &lv_font_montserrat_22, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_wifi = lv_img_create(ui_Screen1);
lv_img_set_src(ui_wifi, &ui_img_953604683);
lv_obj_set_width( ui_wifi, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_wifi, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_wifi, 112 );
lv_obj_set_y( ui_wifi, -96 );
lv_obj_set_align( ui_wifi, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_wifi, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_wifi, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_gps = lv_img_create(ui_Screen1);
lv_img_set_src(ui_gps, &ui_img_weixing_png);
lv_obj_set_width( ui_gps, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_gps, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_gps, -119 );
lv_obj_set_y( ui_gps, -94 );
lv_obj_set_align( ui_gps, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_gps, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_gps, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_altitudeText = lv_label_create(ui_Screen1);
lv_obj_set_width( ui_altitudeText, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_altitudeText, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_altitudeText, 92 );
lv_obj_set_y( ui_altitudeText, -47 );
lv_obj_set_align( ui_altitudeText, LV_ALIGN_CENTER );
lv_label_set_text(ui_altitudeText,"31m");
lv_obj_set_style_text_color(ui_altitudeText, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_altitudeText, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_altitudeText, &lv_font_montserrat_22, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_gpsTime = lv_label_create(ui_Screen1);
lv_obj_set_width( ui_gpsTime, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_gpsTime, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_gpsTime, 3 );
lv_obj_set_y( ui_gpsTime, -89 );
lv_obj_set_align( ui_gpsTime, LV_ALIGN_CENTER );
lv_label_set_text(ui_gpsTime,"2023-07-03 21:21:30");
lv_obj_set_style_text_color(ui_gpsTime, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_gpsTime, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_gpsTime, &lv_font_montserrat_18, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_handing = lv_img_create(ui_Screen1);
lv_img_set_src(ui_handing, &ui_img_direction_png);
lv_obj_set_width( ui_handing, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_handing, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_handing, 27 );
lv_obj_set_y( ui_handing, 56 );
lv_obj_set_align( ui_handing, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_handing, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_handing, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_handingText = lv_label_create(ui_Screen1);
lv_obj_set_width( ui_handingText, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_handingText, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_handingText, 83 );
lv_obj_set_y( ui_handingText, 59 );
lv_obj_set_align( ui_handingText, LV_ALIGN_CENTER );
lv_label_set_text(ui_handingText,"245°");
lv_obj_set_style_text_color(ui_handingText, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_handingText, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_handingText, &lv_font_montserrat_22, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_bettery = lv_img_create(ui_Screen1);
lv_img_set_src(ui_bettery, &ui_img_dianliang_png);
lv_obj_set_width( ui_bettery, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_bettery, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_bettery, 122 );
lv_obj_set_y( ui_bettery, -82 );
lv_obj_set_align( ui_bettery, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_bettery, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_bettery, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_gpsText = lv_label_create(ui_Screen1);
lv_obj_set_width( ui_gpsText, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_gpsText, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_gpsText, 44 );
lv_obj_set_y( ui_gpsText, 94 );
lv_obj_set_align( ui_gpsText, LV_ALIGN_CENTER );
lv_label_set_text(ui_gpsText,"-,-");
lv_obj_set_style_text_color(ui_gpsText, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_gpsText, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_gpsText, &lv_font_montserrat_12, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_gpsNuText = lv_label_create(ui_Screen1);
lv_obj_set_width( ui_gpsNuText, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_gpsNuText, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_gpsNuText, -100 );
lv_obj_set_y( ui_gpsNuText, -94 );
lv_obj_set_align( ui_gpsNuText, LV_ALIGN_CENTER );
lv_label_set_text(ui_gpsNuText,"99");
lv_obj_set_style_text_color(ui_gpsNuText, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_gpsNuText, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_gpsNuText, &lv_font_montserrat_12, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_hdopNuText = lv_label_create(ui_Screen1);
lv_obj_set_width( ui_hdopNuText, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_hdopNuText, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_hdopNuText, -120 );
lv_obj_set_y( ui_hdopNuText, -77 );
lv_obj_set_align( ui_hdopNuText, LV_ALIGN_CENTER );
lv_label_set_text(ui_hdopNuText,"99");
lv_obj_set_style_text_color(ui_hdopNuText, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_hdopNuText, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_hdopNuText, &lv_font_montserrat_12, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_add_event_cb(ui_speed, ui_event_speed, LV_EVENT_ALL, NULL);

}
