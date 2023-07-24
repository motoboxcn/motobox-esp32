#include <esp_adc_cal.h>
#include <lvgl.h>
#include <ui.h>

// 改变 ui 样式
void ui_wifi_connect_off()
{
    lv_obj_set_style_blend_mode(ui_weixing, LV_BLEND_MODE_MULTIPLY, 0);
    lv_obj_set_style_blend_mode(ui_websocket, LV_BLEND_MODE_MULTIPLY, 0);
    lv_obj_set_style_blend_mode(ui_wifi, LV_BLEND_MODE_MULTIPLY, 0);
    lv_obj_set_style_blend_mode(ui_luxiang, LV_BLEND_MODE_MULTIPLY, 0);
}

void ui_wifi_connect_on()
{
    // lv_obj_set_style_blend_mode(ui_weixing, LV_BLEND_MODE_NORMAL, 0);
    // lv_obj_set_style_blend_mode(ui_websocket, LV_BLEND_MODE_NORMAL, 0);
    lv_obj_set_style_blend_mode(ui_wifi, LV_BLEND_MODE_NORMAL, 0);
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
        lv_obj_set_style_arc_color(ui_speed, lv_color_hex(0x2274C2), LV_PART_INDICATOR | LV_STATE_DEFAULT ); // 设置颜色
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

}
// 初始化 ui 仪表盘 1-299 变化
void init_speed_dashboard()
{
    // Initialize dashboard
    for (int i = 0; i <= 299; i += 4)
    {
        speed_dashboard(i);
        lv_timer_handler();
        delay(5);
    }

    for (int j = 299; j >= 0; j -= 4)
    {
        speed_dashboard(j);
        lv_timer_handler();
        delay(5);
    }

    // Reset dashboard
    speed_dashboard(0);
    lv_timer_handler();
}



// 初始化ADC配置
void init_adc()
{
    adc1_config_width(ADC_WIDTH_BIT_12); // 设置ADC位宽为12位
    adc1_config_channel_atten(ADC1_CHANNEL_7, ADC_ATTEN_DB_0); // 设置通道7的衰减为0dB
}

// 电压检测 电量展示
void battery_dashboard(int battery)
{
    if (battery < 3300)
    {
        lv_img_set_src(ui_bettery, &ui_img_dianliang_png);
    }
    else if (battery < 3600)
    {
        lv_img_set_src(ui_bettery, &ui_img_dianliang1_png);
    }
    else
    {
        lv_img_set_src(ui_bettery, &ui_img_dianliang2_png);
    }
    lv_img_set_src(ui_bettery, &ui_img_dianliang2_png);
}

// 获取电压值
int get_battery()
{
    // 读取ADC值
    uint32_t adc_reading = adc1_get_raw(ADC1_CHANNEL_7);

    // 根据VREF和ADC最大值（2^12）计算电压值
    int voltage = (adc_reading * 1100) / 4095; // 若您的ADC位宽不是12位，则需要根据实际位宽修改这里的计算公式
    battery_dashboard(voltage);
}
