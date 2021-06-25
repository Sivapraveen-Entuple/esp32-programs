#include "freertos/task.h"

#define LED_1 2
#define LED_2 3
#define LED_3 4

QueueHandle_t queue1;
QueueHandle_t queue2;
QueueHandle_t queue3;

static void QueueTransferTask(void *param_p)
{
  static int datSend;
  while(1)
  {
    datSend++;
    Serial.printf("Sending Data in QueueTransferTask: %d \n", datSend);
    xQueueSend(queue1, &datSend, (TickType_t)0);    
    vTaskDelay(10000 / portTICK_PERIOD_MS);
  }
}

static void QueueProcessTask(void *param_p)
{
  int datRec;
  while(1)
  {
    if(xQueueReceive(queue1, (void*)&datRec, (portTickType)portMAX_DELAY))
    {
      Serial.printf("Data Received in QueueProcessTask: %d \n", datRec);
      datRec++;
      xQueueSend(queue2, &datRec, (TickType_t)0);
    }
  }
}

static void QueueSendToCloudTask(void *param_p)
{
   int datSendCloud;
   while(1)
   {
    if(xQueueReceive(queue2, (void*)datSendCloud, (portTickType)portMAX_DELAY))
    {
      Serial.printf("Data sending to cl will be: %d !!! \n", datSendCloud);
    }
   } 
}



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

 // xTaskCreate(task1, "Task1", 1024*2, NULL, 1, NULL);           //   (taskFunction, Taskname, stack size, parameterToPass, Task priority, Task Handle)      
 // xTaskCreate(task2, "Task2", 1024*2, NULL, 1, NULL);
 // xTaskCreate(task3, "Task3", 1024*2, NULL, 1, NULL);

 xTaskCreate(QueueTransferTask, "Queue Transfer Task", 2048*3, NULL, 1, NULL);
 xTaskCreate(QueueProcessTask, "Queue Process Task", 2048*3, NULL, 1, NULL);
 xTaskCreate(QueueSendToCloudTask, "Queue Send To Cloud Task", 2048*3, NULL, 1, NULL);

  queue1 = xQueueCreate(5, sizeof(int));
  if(queue1 == NULL)
  {
    Serial.printf("Error Creating queue1 !!! \n");
  }
  queue2 = xQueueCreate(5, sizeof(int));
  if(queue2 == NULL)
  {
    Serial.printf("Error Creating queue2 !!! \n");
  }
  queue3 = xQueueCreate(5, sizeof(int));
  if(queue3 == NULL)
  {
    Serial.printf("Error Creating queue3 !!! \n");
  }
  Serial.printf("Setup done... \n");
}

void loop() {
  
  // put your main code here, to run repeatedly:

}
