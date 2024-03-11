#include <lvgl.h>
#include <ui.h>
#include <Arduino.h>

// 电压检测 电量展示
void battery_dashboard(int battery)
{
    Serial.printf("battery: %d\n", battery);
    if (battery < 3300)
    {
        lv_img_set_src(ui_battery, &ui_img_dianliang_png);
    }
    else if (battery < 3600)
    {
        lv_img_set_src(ui_battery, &ui_img_dianliang1_png);
    }
    else
    {
        lv_img_set_src(ui_battery, &ui_img_dianliang2_png);
    }
    lv_img_set_src(ui_battery, &ui_img_dianliang2_png);
    delay(1000);
}

void loop_adc(void *pvParameters)
{
    float vtmp = analogRead(34);  // 从IO34 利用 ADC 获取电压
    vtmp = vtmp / 4095 * 3.3 * 2; // 电压分压
    battery_dashboard(vtmp * 1000);
}

void setup_adc()
{
    xTaskCreate(loop_adc, "loop_adc", 1024*2, NULL, 10, NULL);
}
