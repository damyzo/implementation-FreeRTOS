#include <Arduino_FreeRTOS.h>
#include <timers.h>
#include <semphr.h>


//Pin numbers
const int semaphore1_green = 9;
const int semaphore1_yellow = 8;
const int sempahore1_red = 4;

const int semaphore2_green = 5;
const int semaphore2_yellow = 6;
const int sempahore2_red = 7;

const int push_button = 2;
const int push_button1 = 3;

//Semaphore and mutex handlers
SemaphoreHandle_t interruptSemaphore;
SemaphoreHandle_t interruptSemaphore1;
SemaphoreHandle_t mutex;

//Timer handlers
TimerHandle_t timer = NULL;
TimerHandle_t timer_oneshot = NULL;

//Global variables for the semaphore (from project not from FreeRtos) state
bool firstTime = true; 
int logic = 1;

void setup() {
    Serial.begin(9600); //Start the serial monitor
    pinMode(push_button, INPUT_PULLUP); // Set pin mode to interrupt button
    pinMode(push_button1, INPUT_PULLUP); // Set pin mode to interrupt button
    
    //Setup the pin modes for the first semaphore
    pinMode(semaphore1_green, OUTPUT);
    pinMode(semaphore1_yellow, OUTPUT);
    pinMode(sempahore1_red, OUTPUT);
    //Setup the pin modes for the second semaphore
    pinMode(semaphore2_green, OUTPUT);
    pinMode(semaphore2_yellow, OUTPUT);
    pinMode(sempahore2_red, OUTPUT);
    
    //Turn on the red lights on both semaphores
    digitalWrite(sempahore2_red, HIGH);
    digitalWrite(sempahore1_red, HIGH);
    
    //Create tasks for handling the interrupt
    xTaskCreate(TaskPedestrian, "Task1", 128, NULL, configMAX_PRIORITIES-1, NULL);  
    xTaskCreate(TaskPedestrian, "Task2", 128, NULL, 0, NULL);
    
    
    
    //Peiodic timer
    timer = xTimerCreate( "Timer", pdMS_TO_TICKS(10000), pdTRUE, 0, vPeriodicTimerCallback);
    xTimerStart(timer, 0);
    //Oneshot timer
    timer_oneshot = xTimerCreate( "Timer", pdMS_TO_TICKS(0), pdFALSE, 0, vOneShotTimerCallback);
    xTimerStart(timer_oneshot, 0);
    
    //Binary semaphore creation
    interruptSemaphore = xSemaphoreCreateBinary();
    if (interruptSemaphore != NULL) {
      //Setting up interrupt pins
      attachInterrupt(digitalPinToInterrupt(push_button), interruptHandler, LOW);
      attachInterrupt(digitalPinToInterrupt(push_button1), interruptHandler, LOW);
    }
    //Mutex creation
    mutex = xSemaphoreCreateMutex();
    if (mutex != NULL) {
      Serial.println("Mutex created");
    }
  
  
   vTaskStartScheduler();


}
void interruptHandler() {
  //Interrupt activates semaphore from FreeRtos
  xSemaphoreGiveFromISR(interruptSemaphore, NULL);
}

//Task function to handle the interrupt 
void TaskPedestrian(void *pvParameters)
{
  
  for (;;) {
    if (xSemaphoreTake(mutex, 10) == pdTRUE)
    {
      Serial.println(pcTaskGetName(NULL));    
      xSemaphoreGive(mutex);
    }
    if (xSemaphoreTake(interruptSemaphore, 3) == pdPASS) {
      
        Serial.println("Pedestrian semaphore started");
      
      xTimerStop(timer, 0);
      digitalWrite(semaphore2_green, LOW);
      digitalWrite(semaphore1_green, LOW);
      if(logic%2 != 0)
      {
        digitalWrite(semaphore2_yellow, HIGH);  
      }else{ 
        digitalWrite(semaphore1_yellow, HIGH);
      }
      
      vPortDelay(1000);
      digitalWrite(semaphore1_yellow, LOW);
      digitalWrite(semaphore2_yellow, LOW);
      digitalWrite(sempahore1_red, HIGH);
      digitalWrite(sempahore2_red, HIGH);
      vPortDelay(10000);
             
      firstTime = true;
      Serial.println("Pedestrian semaphore ended.");
      xTimerStart(timer, 0);      
    }
    vTaskDelay(10);
  }
} 
void vOneShotTimerCallback(){

      digitalWrite(sempahore1_red, HIGH);
      digitalWrite(sempahore2_red, HIGH);
      vPortDelay(400);
      digitalWrite(sempahore2_red, LOW);   
      digitalWrite(sempahore1_red, LOW);
      vPortDelay(400);
      digitalWrite(sempahore2_red, HIGH);    
      digitalWrite(sempahore1_red, HIGH);
      vPortDelay(400);
      digitalWrite(sempahore2_red, LOW);    
      digitalWrite(sempahore1_red, LOW);
      vPortDelay(400);    
      digitalWrite(sempahore2_red, HIGH);
      digitalWrite(sempahore1_red, HIGH);
      vPortDelay(400);
      digitalWrite(sempahore2_red, LOW);    
      digitalWrite(sempahore1_red, LOW);
      vPortDelay(400);   
      digitalWrite(sempahore2_red, HIGH);
      digitalWrite(sempahore1_red, HIGH);
      vPortDelay(400);
      digitalWrite(sempahore2_red, LOW);    
      digitalWrite(sempahore1_red, LOW);
      vPortDelay(400);   
      digitalWrite(sempahore2_red, HIGH);
      digitalWrite(sempahore1_red, HIGH);
      vPortDelay(400);
      digitalWrite(sempahore2_red, LOW);     
      digitalWrite(sempahore1_red, LOW);
      vPortDelay(400);  
      digitalWrite(sempahore2_red, HIGH);
      digitalWrite(sempahore1_red, HIGH);
      vPortDelay(400);
      digitalWrite(sempahore2_red, LOW);   
      digitalWrite(sempahore1_red, LOW); 
      vPortDelay(400);
      digitalWrite(sempahore1_red, HIGH);
      digitalWrite(sempahore2_red, HIGH);      
}
void vPeriodicTimerCallback(){
  volatile uint32_t ul;
  Serial.println("Periodic timer");
  if(logic % 2== 0){
      if(!firstTime){
        digitalWrite(semaphore1_green, LOW);
        
        digitalWrite(semaphore1_yellow, HIGH);
        vPortDelay(400);   
        digitalWrite(semaphore1_yellow, LOW);
    }else{
      firstTime = false;            
    }
        
        
        digitalWrite(sempahore1_red, HIGH);
        vPortDelay(1000);    
        digitalWrite(sempahore2_red, LOW);
        
        digitalWrite(semaphore2_yellow, HIGH);
        vPortDelay(400);       
        digitalWrite(semaphore2_yellow, LOW);
    
        digitalWrite(semaphore2_green, HIGH);
        logic = 1;
       
        
        
  }else{
    if(!firstTime){
      digitalWrite(semaphore2_green, LOW);
        
      digitalWrite(semaphore2_yellow, HIGH);
      vPortDelay(400);    
      digitalWrite(semaphore2_yellow, LOW);
    }else{
      firstTime = false;            
    }
      
    digitalWrite(sempahore2_red, HIGH);
    vPortDelay(1000);     
    digitalWrite(sempahore1_red, LOW);
        
    digitalWrite(semaphore1_yellow, HIGH);
    vPortDelay(400);   
    digitalWrite(semaphore1_yellow, LOW);
    
    digitalWrite(semaphore1_green, HIGH); 
    logic = 2;
  }
}
void loop() {
  
  // put your main code here, to run repeatedly:

}
