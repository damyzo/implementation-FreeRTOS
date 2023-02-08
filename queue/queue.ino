#include <Arduino_FreeRTOS.h>
#include <queue.h>
//Хендлер за редица
QueueHandle_t queueHandle = NULL;

void setup() {
  
   Serial.begin(9600);
    pinMode(red_led, OUTPUT);
  //Креирање на тасковите 
  xTaskCreate(TaskSend, "Task1",128, NULL, 1, NULL);
  xTaskCreate(TaskReceive, "Task2", 128, NULL, 1, NULL);
  //Креирање на редица
  queueHandle = xQueueCreate(3, sizeof(int));
  //Започнување на распоредувачот
  vTaskStartScheduler();

}

void loop() {
  // put your main code here, to run repeatedly:

}

void TaskSend(void *pvParameters){
  BaseType_t xStatus;
  for(;;){
    xStatus = xQueueSendToBack(queueHandle, random(5), pdMS_TO_TICKS(500));
    if(xStatus != pdPASS){
      Serial.println("Could not send data to queue.");
    }
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}
void TaskReceive(void *pvParameters){
  int recievedValue;
  BaseType_t xStatus;
  
  
  for(;;){
    xStatus = xQueueReceive(queueHandle,&recievedValue, pdMS_TO_TICKS(100));
    if(xStatus == pdPASS){
      Serial.println("Received value ");
      Serial.println(recievedValue);
    }

    
  }
}
