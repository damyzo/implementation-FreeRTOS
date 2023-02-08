#include <Arduino_FreeRTOS.h>

TaskHandle_t semaphore1 = NULL;
TaskHandle_t semaphore2 = NULL;


const int semaphore1_green = 9;
const int semaphore1_yellow = 8;
const int sempahore1_red = 4;

const int semaphore2_green = 5;
const int semaphore2_yellow = 6;
const int sempahore2_red = 7;


void setup() {
    Serial.begin(9600);
    pinMode(semaphore1_green, OUTPUT);
    pinMode(semaphore1_yellow, OUTPUT);
    pinMode(sempahore1_red, OUTPUT);

    pinMode(semaphore2_green, OUTPUT);
    pinMode(semaphore2_yellow, OUTPUT);
    pinMode(sempahore2_red, OUTPUT);

    digitalWrite(sempahore2_red, HIGH);
    digitalWrite(sempahore1_red, HIGH);
    
    xTaskCreate(TaskFun, "Sema1", 128, 2, 2,&semaphore1);
    xTaskCreate(TaskFun, "Sema2", 128, 1, 1, &semaphore2);
    vTaskStartScheduler();
  

}

void loop() {
  // put your main code here, to run repeatedly:

}

void TaskFun(void *pvParameters){
  int semaphore = (int) pvParameters;
  volatile uint32_t ul;

  for (;;){
       
    Serial.println(pcTaskGetName(NULL));
  
    switch(semaphore){
      case 1:
        digitalWrite(sempahore2_red, LOW);
        
        digitalWrite(semaphore2_yellow, HIGH);
        for(ul = 0; ul < 100000; ul++){}    
        digitalWrite(semaphore2_yellow, LOW);
    
        digitalWrite(semaphore2_green, HIGH);
        //-------------
        for(ul = 0; ul < 1000000; ul++){}
        //-------------
        digitalWrite(semaphore2_green, LOW);
        
        digitalWrite(semaphore2_yellow, HIGH);
        for(ul = 0; ul < 100000; ul++){}    
        digitalWrite(semaphore2_yellow, LOW);
        
        digitalWrite(sempahore2_red, HIGH);
        vTaskPrioritySet(semaphore1, 2);
        vTaskPrioritySet(semaphore2, 1);
        break;
      case 2:
        digitalWrite(sempahore1_red, LOW);
        
        digitalWrite(semaphore1_yellow, HIGH);
        for(ul = 0; ul < 100000; ul++){}    
        digitalWrite(semaphore1_yellow, LOW);
    
        digitalWrite(semaphore1_green, HIGH);
        //-------------
        for(ul = 0; ul < 1000000; ul++){}
        //-------------
        digitalWrite(semaphore1_green, LOW);
        
        digitalWrite(semaphore1_yellow, HIGH);
        for(ul = 0; ul < 100000; ul++){}    
        digitalWrite(semaphore1_yellow, LOW);
        
        digitalWrite(sempahore1_red, HIGH);  
        vTaskPrioritySet(semaphore2, 2);
        vTaskPrioritySet(semaphore1, 1);      
        break;
     
      }
    
  }
}
