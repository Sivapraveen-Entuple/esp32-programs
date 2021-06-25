#include "freertos/task.h"
#include "driver/i2c.h"

#define LED_1 2
#define LED_2 3
#define LED_3 4

QueueHandle_t queue1;
QueueHandle_t queue2;
QueueHandle_t queue3;

static void task1(void *param_p)
{
  while(1)
  {
    digitalWrite(LED_1, HIGH);
    Serial.printf("LED_1 High ... \n");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    digitalWrite(LED_1, LOW);
    Serial.printf("LED_1 LOW ... \n");
    vTaskDelay(1000 / portTICK_PERIOD_MS);  
  }  
}

static void task2(void *param_p)
{
  while(1)
  {
    digitalWrite(LED_2, HIGH);
    Serial.printf("LED_2 High ... \n");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    digitalWrite(LED_2, LOW);
    Serial.printf("LED_2 Low ... \n");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

static void task3(void *param_p)
{
  while(1)
  {
    digitalWrite(LED_3, HIGH);
    Serial.printf("LED_3 High ... \n");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    digitalWrite(LED_3, LOW);
    Serial.printf("LED_3 Low ... \n");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }  
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);

  xTaskCreate(task1, "Task1", 1024*2, NULL, 1, NULL);           //   (taskFunction, Taskname, stack size, parameterToPass, Task priority, Task Handle)      
  xTaskCreate(task2, "Task2", 1024*2, NULL, 1, NULL);
  xTaskCreate(task3, "Task3", 1024*2, NULL, 1, NULL);

  queue1 = xQueueCreate(5, sizeof(int));
  queue2 = xQueueCreate(5, sizeof(int));
  queue3 = xQueueCreate(5, sizeof(int));
  
  Serial.printf("Setup done... \n");

}

void loop() {
  // put your main code here, to run repeatedly:

}
