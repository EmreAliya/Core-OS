#include <Arduino.h>
#include <Wire.h>
#include "MPU6050.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>

MPU6050 imu;
SemaphoreHandle_t lcdMutex;
bool locked = false;

void TaskIMU(void *pv);
void TaskLCD(void *pv);
void TaskKeypad(void *pv);

void setup() {
  Serial.begin(115200);
  Wire.begin();
  imu.initialize();
  lcdMutex = xSemaphoreCreateMutex();

  xTaskCreatePinnedToCore(TaskIMU, "IMU", 2048, NULL, 2, NULL, 1);
  xTaskCreatePinnedToCore(TaskLCD, "LCD", 2048, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(TaskKeypad, "Keypad", 2048, NULL, 1, NULL, 1);
}

void loop() {}

void TaskIMU(void *pv) {
  while (1) {
    imu.getAcceleration();
    int16_t ax = imu.getAccelerationX();
    if (abs(ax) > 12000 && !locked) {
      locked = true;
      Serial.println("[IMU] Movement detected → Locking!");
    }
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void TaskLCD(void *pv) {
  while (1) {
    if (xSemaphoreTake(lcdMutex, portMAX_DELAY)) {
      Serial.printf("[LCD] State: %s\n", locked ? "LOCKED" : "UNLOCKED");
      xSemaphoreGive(lcdMutex);
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void TaskKeypad(void *pv) {
  while (1) {
    if (Serial.available()) {
      char c = Serial.read();
      if (c == 'u') locked = false;
      Serial.printf("[KEYPAD] Input: %c → System %s\n",
                    c, locked ? "LOCKED" : "UNLOCKED");
    }
    vTaskDelay(pdMS_TO_TICKS(200));
  }
}
