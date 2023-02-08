#include <Arduino_FreeRTOS.h>



void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  //Креирање на тасковите 
  xTaskCreate(ContinuousTask, "Cont",128, NULL, 1, NULL);
  xTaskCreate(PeriodicTask, "Per", 128, NULL, 1, NULL);
  //Започнување на распоредувачот
  vTaskStartScheduler();

}

void loop() {
  // put your main code here, to run repeatedly:

}
//функција за континуиран таск
void ContinuousTask(void *pvParameters){
  
  for(;;){
    Serial.println("Continous");
    vTaskDelay(pdMS_TO_TICKS(1000));

  }
}
//Функција за периодичен таск
void PeriodicTask(void *pvParameters){
 TickType_t currentTime = xTaskGetTickCount();
  for(;;){
    Serial.println("Periodic");
    vTaskDelayUntil(&currentTime, pdMS_TO_TICKS(3000));
  }
}
