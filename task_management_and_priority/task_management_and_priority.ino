#include <Arduino_FreeRTOS.h>

void setup() {
  // Подесување
  //Стартување на Serial монитор
    Serial.begin(9600);
    //Креирање на таскови
    xTaskCreate(TaskFun,"Task1",128,"parameter1",1,NULL);
    xTaskCreate(TaskFun,"Task2",128,"parameter2",2,NULL);
    //Започнување на таскови со работа
    vTaskStartScheduler();
}
//Функција која ќе ја извршуваат тасковите
void TaskFun(void *pvParameters){
  for(;;){
    //Печатење на име на таскот
    Serial.println(pcTaskGetName(NULL));
    //Печатење на параметрите на таскот
    Serial.println((char*) pvParameters);
    //Влегување на таскот во Block состојба 1 секунда
    vTaskDelay(pdMS_TO_TICKS(1000));
    //Менување на приоритетот на таскот
    vTaskPrioritySet(configMAX_PRIORITIES-1, NULL);
    //Бришење на таск
    vTaskDelete(NULL);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
