#include <Arduino.h>


int nTasks=2;
SemaphoreHandle_t xSemaphore = NULL;
const int led1 = 18;
void ledoff (void * pvParameter);
void ledon (void * pvParameter);

void setup()
{
  Serial.begin(112500);
  delay(1000);
  pinMode (led1, OUTPUT);
  //Serial.println("Starting...");

  vSemaphoreCreateBinary( xSemaphore );
  xTaskCreate(ledon, "Toggle on LED", 1000, NULL, 1, NULL );
  xTaskCreate(ledoff, "Toggle off LED", 1000, NULL, 1, NULL );
 
}

void loop()
{
 vTaskDelay(1000);
}


void ledon (void * Parameter)
{
  xSemaphoreTake(xSemaphore, portMAX_DELAY);
  digitalWrite(led1, HIGH);
  Serial.println ("ON");
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  xSemaphoreGive(xSemaphore);
}

void ledoff (void * Parameter)
{
  xSemaphoreTake(xSemaphore, portMAX_DELAY);
  digitalWrite(led1, LOW);
  Serial.println("OFF");
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  xSemaphoreGive(xSemaphore);
}