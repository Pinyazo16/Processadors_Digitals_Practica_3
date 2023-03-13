# Pràctica 3

En aquesta pràctica ens hem de familiartizar amb el funcionament i implementació de tasques.

Les tasques permeten al processador dur a terme diversess tasques simultàniament; de manera que, per exemple, mentre una tasca ha d’esperar un cert temps, es pot executar part d’una altra tasca. D’aquesta manera, evitem que tasques molt llargues bloquejin el processador durant molta estona.

## Exercissi 1

Aquest primer exercissi consistia a probar un codi que interclava dues escriptures per pantalla, una a través del `void loop()` i l’altra a través d’una tasca. Totes dues escriptures s’havien d’intercalar mitjançant funcions `delay()` .

```cpp
#include <Arduino.h>

void anotherTask( void * parameter );

void setup()
{
  Serial.begin(112500);
  /* we create a new task here */
  xTaskCreate(
    anotherTask, /* Task function. */
    "another Task", /* name of task. */
    10000, /* Stack size of task */
    NULL, /* parameter of the task */
    1, /* priority of the task */
    NULL); /* Task handle to keep track of created task */
}

/* the forever loop() function is invoked by Arduino ESP32 loopTask */
void loop()
{
  Serial.println("this is ESP32 Task");
  delay(1000);
}

/* this function will be invoked when additionalTask was created */
void anotherTask( void * parameter )
{
  /* loop forever */
  for(;;)
  {
    Serial.println("this is another Task");
    delay(1000);
  }
  /* delete a task when finish,
  this will never happen because this is infinity loop */
  vTaskDelete( NULL );
}
```

### Funció `setup()`

En aquesta primera funció “declarem” la tasca, definint tots els detalls d’aquesta com poden ser el nom de la funció, els paràmetres que utilitza, i la prioritat. Aquest últim concepte és realment importat quan treballem amb diverses tasques.

### Funció `loop()`

En aquesta funció definirem una de les escriptures que demana l’exercissi. En el codi podem veure que està escrit `Serial.println("this is ESP32 Task");` ja que aquesta escriptura podríem dir que la realitza el processador i no la tasca (tot i que el processador també realitza les tasques, en aquest cas ho fa directament, sense accedir a cap funció adicional).
Seguidament afegim un `delay(1000);` que permetrà a la tasca utilitzar aquest temps d’espera del processador per dur a terme part del seu processat.

### Tasca

La tasca “another task” com ja hem comentat anteriorment treu un missatge per pantalla. Al ser una tasca, un cop es processa aquesta es destrueix amb la funció `vTaskDelete();` , però nosaltres volem que aquesta es repeteixi de manera indefinida intercalant-se amb l’escriptura de la funció `loop()` . Això ho aconseguim posant el `Serial.println()` en un bucle infinit. En aquest cas un `for(;;)` . Però volem intercalar ambdues escriptures; per tant afegim també un `delay(1000)` per a que el processador doni pas a la funció `loop()` mentre passa el temps del `delay()` . 
D’aquesta manera aconseguim l’objectiu de l’exercissi; intercalar les dues escriptures per pantalla de forma indefinida.

## Exercissi 2

Aquest exercissi consisteix a escriure un programa que; utilitzant dues tasques, encengui i apagui un LED de forma intermitent. Com a comentari a l’enunciat sen’s suggereix utilitzar semàfors.

### Semàfors

Els semàfors són unes funcions que permeten controlar de manera més ordenada les tasques; més concretament, controlar l’ordre en que es processen. Els semàfors funcionen (tal com indica el nom) de manera semblant als semàfors de tràfic que trobem a les carreteres. 
Els semàfors (de codi) reserven el processador per una certa tasca durant un cert temps, o fins que la tasca finalitzi (hi ha diversos tipus de semàfors). Un cop ocorre això el semàfor permet l’accés d’altres tasques al processador, i es repeteix el mateix procediment.
Això ens permet no dependre de funcions `delay()` per intercalar tasques. Cada tipus de semàfor regula l’accés al processador de manera lleugerament diferent. Com hem comentat abans, alguns donen un temps màxim a cada tasca per accedir al processador. Altres alliberen el processador només quan la tasca ha finalitzat completament.

Malauradament, aquest exercissi no ens va funcionar. Tot i probar diferents tipus de semàfors i d’estar una bona estona tractant de diagnosticar els errors que tenia el codi, no vam aconseguir complir l’objectiu d’aquest exercissi.
