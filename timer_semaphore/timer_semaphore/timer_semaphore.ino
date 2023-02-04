#include <Arduino_FreeRTOS.h>
#include <timers.h>
#include <semphr.h>

SemaphoreHandle_t interruptSemaphore;

const int semaphore1_green = 3;
const int semaphore1_yellow = 8;
const int sempahore1_red = 4;

const int semaphore2_green = 5;
const int semaphore2_yellow = 6;
const int sempahore2_red = 7;

const int push_button = 2;

TimerHandle_t timer = NULL;
bool firstTime = true; 
int logic = 1;
void setup() {
    Serial.begin(9600);
    pinMode(push_button, INPUT_PULLUP);
    xTaskCreate(TaskPedestrian,
              "Yellow blink",
              128, 
              NULL, 
              0, 
              NULL );
    pinMode(semaphore1_green, OUTPUT);
    pinMode(semaphore1_yellow, OUTPUT);
    pinMode(sempahore1_red, OUTPUT);

    pinMode(semaphore2_green, OUTPUT);
    pinMode(semaphore2_yellow, OUTPUT);
    pinMode(sempahore2_red, OUTPUT);

    digitalWrite(sempahore2_red, HIGH);
    digitalWrite(sempahore1_red, HIGH);
      xTimerStart(
        xTimerCreate( 
          "Timer",
          pdMS_TO_TICKS(10000),
          pdTRUE,
           0,
          vPeriodicTimerCallback
          ), 
        0);
        xTimerStart(
          xTimerCreate( 
            "Timer",
            pdMS_TO_TICKS(0),
            pdFALSE,
            0,
            vOneShotTimerCallback), 
          0);
    interruptSemaphore = xSemaphoreCreateBinary();
    if (interruptSemaphore != NULL) {
      attachInterrupt(digitalPinToInterrupt(push_button), interruptHandler, LOW);
    }

   


}
void interruptHandler() {
  xSemaphoreGiveFromISR(interruptSemaphore, NULL);
}
void TaskPedestrian(void *pvParameters)
{
  (void) pvParameters;
      volatile uint32_t ul;

  

  for (;;) {
    
    if (xSemaphoreTake(interruptSemaphore, 0) == pdPASS) {
      digitalWrite(sempahore1_red, LOW);
      digitalWrite(sempahore2_red, LOW); 
      digitalWrite(semaphore1_green, LOW);
      digitalWrite(semaphore2_green, LOW);
      digitalWrite(semaphore1_yellow, HIGH);
      digitalWrite(semaphore2_yellow, HIGH);
      for(ul = 0; ul < 100000; ul++){}    
      digitalWrite(semaphore1_yellow, LOW);
      digitalWrite(semaphore2_yellow, LOW);
      digitalWrite(sempahore1_red, HIGH);
      digitalWrite(sempahore2_red, HIGH);
      for(ul = 0; ul < 100000000; ul++){}            
      
    }
    vTaskDelay(1);
  }
} 
void vOneShotTimerCallback(){
      volatile uint32_t ul;

      digitalWrite(sempahore1_red, HIGH);
      for(ul = 0; ul < 100000; ul++){}    
      digitalWrite(sempahore1_red, LOW);
      for(ul = 0; ul < 100000; ul++){}    
      digitalWrite(sempahore1_red, HIGH);
      for(ul = 0; ul < 100000; ul++){}    
      digitalWrite(sempahore1_red, LOW);
      for(ul = 0; ul < 100000; ul++){}    

      digitalWrite(sempahore1_red, HIGH);
      for(ul = 0; ul < 100000; ul++){}    
      digitalWrite(sempahore1_red, LOW);
      for(ul = 0; ul < 100000; ul++){}    

      digitalWrite(sempahore1_red, HIGH);
      for(ul = 0; ul < 100000; ul++){}    
      digitalWrite(sempahore1_red, LOW);
      for(ul = 0; ul < 100000; ul++){}    

      digitalWrite(sempahore1_red, HIGH);
      for(ul = 0; ul < 100000; ul++){}    
      digitalWrite(sempahore1_red, LOW);
      for(ul = 0; ul < 100000; ul++){}    

      digitalWrite(sempahore1_red, HIGH);
      for(ul = 0; ul < 100000; ul++){}    
      digitalWrite(sempahore1_red, LOW); 
      for(ul = 0; ul < 100000; ul++){}
      digitalWrite(sempahore1_red, HIGH);
    

      //----
      digitalWrite(sempahore2_red, HIGH);
      for(ul = 0; ul < 100000; ul++){}    
      digitalWrite(sempahore2_red, LOW);
      for(ul = 0; ul < 100000; ul++){}    

      digitalWrite(sempahore2_red, HIGH);
      for(ul = 0; ul < 100000; ul++){}    
      digitalWrite(sempahore2_red, LOW);
      for(ul = 0; ul < 100000; ul++){}    

      digitalWrite(sempahore2_red, HIGH);
      for(ul = 0; ul < 100000; ul++){}    
      digitalWrite(sempahore2_red, LOW); 
      for(ul = 0; ul < 100000; ul++){}    

      digitalWrite(sempahore2_red, HIGH);
      for(ul = 0; ul < 100000; ul++){}    
      digitalWrite(sempahore2_red, LOW);
      for(ul = 0; ul < 100000; ul++){}    

      digitalWrite(sempahore2_red, HIGH);
      for(ul = 0; ul < 100000; ul++){}    
      digitalWrite(sempahore2_red, LOW);
      for(ul = 0; ul < 100000; ul++){}    

      digitalWrite(sempahore2_red, HIGH);
      for(ul = 0; ul < 100000; ul++){}    
      digitalWrite(sempahore2_red, LOW);
      digitalWrite(sempahore2_red, HIGH);
  
}
void vPeriodicTimerCallback(){
  volatile uint32_t ul;
  
  if(logic % 2== 0){
        digitalWrite(semaphore1_green, LOW);
        
        digitalWrite(semaphore1_yellow, HIGH);
        for(ul = 0; ul < 100000; ul++){}    
        digitalWrite(semaphore1_yellow, LOW);
        
        digitalWrite(sempahore1_red, HIGH);
        for(ul = 0; ul < 100000; ul++){}     
        digitalWrite(sempahore2_red, LOW);
        
        digitalWrite(semaphore2_yellow, HIGH);
        for(ul = 0; ul < 100000; ul++){}    
        digitalWrite(semaphore2_yellow, LOW);
    
        digitalWrite(semaphore2_green, HIGH);
        logic = 1;
       
        
        
  }else{
    if(!firstTime){
      digitalWrite(semaphore2_green, LOW);
        
      digitalWrite(semaphore2_yellow, HIGH);
      for(ul = 0; ul < 100000; ul++){}    
      digitalWrite(semaphore2_yellow, LOW);
    }else{
      firstTime = false;            
    }
      
    digitalWrite(sempahore2_red, HIGH);
    for(ul = 0; ul < 100000; ul++){}     
    digitalWrite(sempahore1_red, LOW);
        
    digitalWrite(semaphore1_yellow, HIGH);
    for(ul = 0; ul < 100000; ul++){}    
    digitalWrite(semaphore1_yellow, LOW);
    
    digitalWrite(semaphore1_green, HIGH); 
    logic = 2;
  }
}
void loop() {
  
  // put your main code here, to run repeatedly:

}
