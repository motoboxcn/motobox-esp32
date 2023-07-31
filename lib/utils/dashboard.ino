#include <lvgl.h>
#include <TFT_eSPI.h>
#include <ui.h>

// SCL 12, SDA 14,RES 27, DC 26, CS 25

/*Change to your screen resolution*/
static const uint16_t screenWidth = TFT_HEIGHT;
static const uint16_t screenHeight = TFT_WIDTH;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * screenHeight / 10];

TFT_eSPI tft = TFT_eSPI(); /* TFT instance */

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors((uint16_t *)&color_p->full, w * h, true);
    tft.endWrite();
    lv_disp_flush_ready(disp);
}

// 改变 ui 样式
void ui_wifi_connect_off()
{
    lv_obj_set_style_blend_mode(ui_weixing, LV_BLEND_MODE_MULTIPLY, 0);
    lv_obj_set_style_blend_mode(ui_websocket, LV_BLEND_MODE_MULTIPLY, 0);
    lv_obj_set_style_blend_mode(ui_wifi, LV_BLEND_MODE_MULTIPLY, 0);
    lv_obj_set_style_blend_mode(ui_luxiang, LV_BLEND_MODE_MULTIPLY, 0);
    lv_timer_handler();
}

void ui_wifi_connect_on()
{
    // lv_obj_set_style_blend_mode(ui_weixing, LV_BLEND_MODE_NORMAL, 0);
    // lv_obj_set_style_blend_mode(ui_websocket, LV_BLEND_MODE_NORMAL, 0);
    lv_obj_set_style_blend_mode(ui_wifi, LV_BLEND_MODE_NORMAL, 0);
    lv_timer_handler();
    // lv_obj_set_style_blend_mode(ui_luxiang, LV_BLEND_MODE_NORMAL, 0);
}

void ui_websocket_on()
{
    lv_obj_set_style_blend_mode(ui_websocket, LV_BLEND_MODE_NORMAL, 0);
    Serial.println("Connected to GPS WebSockets server");
}

void ui_gps_on()
{
    lv_obj_set_style_blend_mode(ui_weixing, LV_BLEND_MODE_NORMAL, 0);
}

void ui_gps_off()
{
    lv_obj_set_style_blend_mode(ui_weixing, LV_BLEND_MODE_MULTIPLY, 0);
}

void ui_trip_on()
{
    lv_obj_set_style_blend_mode(ui_luxiang, LV_BLEND_MODE_NORMAL, 0);
}

void ui_trip_off()
{
    lv_obj_set_style_blend_mode(ui_luxiang, LV_BLEND_MODE_MULTIPLY, 0);
}

// 时速超过 一定值时，仪表盘变化：
// 超过 80，arc 变黄色，label 变黄色
// 超过 120，arc 变红色，label 变红色
// 超过 199，arc 变红色，label 变红色，闪烁
// lv_obj_set_style_bg_opa(ui_Screen1, 255, LV_PART_MAIN| LV_STATE_DEFAULT); 设置闪烁，额外定时器实现闪烁控制
void speed_dashboard(int speed)
{
    lv_arc_set_value(ui_speed, speed);
    lv_label_set_text_fmt(ui_speed2, "%d", speed);

    if (speed < 80)
    {
        lv_obj_set_style_arc_color(ui_speed, lv_color_hex(0x2274C2), LV_PART_INDICATOR | LV_STATE_DEFAULT); // 设置颜色
    }
    else if (speed < 120)
    {
        lv_obj_set_style_arc_color(ui_speed, lv_color_hex(0x0A9F62), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    }
    else if (speed < 200)
    {
        lv_obj_set_style_arc_color(ui_speed, lv_color_hex(0xEF1616), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    }
    else
    {
        lv_obj_set_style_arc_color(ui_speed, lv_color_hex(0xEF1616), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    }
    lv_timer_handler();
}
// 初始化 ui 仪表盘 1-299 变化
void init_speed_dashboard()
{
    // Initialize dashboard
    for (int i = 0; i <= 299; i += 4 * 2)
    {
        speed_dashboard(i);
    }

    for (int j = 299; j >= 0; j -= 4 * 2)
    {
        speed_dashboard(j);
    }
    // Reset dashboard
    speed_dashboard(0);
}


// 初始化 ui
void dashboardInit()
{
    lv_init();
    tft.begin();        /* TFT init */
    tft.setRotation(3); /* Landscape orientation, flipped */

    lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * screenHeight / 10);
    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    /*Change the following line to your display resolution*/
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    ui_init();
    init_speed_dashboard();
}

// change ui Time label by gps time
// fmt GPS date as YYYY-MM-DD HH:MM:SS
void ui_time_update(const char *time)
{
    lv_label_set_text(ui_gpsTime, time);
}


