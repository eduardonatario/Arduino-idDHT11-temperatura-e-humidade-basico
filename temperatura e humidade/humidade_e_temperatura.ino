/*
  Board            int.0   int.1   int.2   int.3   int.4   int.5
 Uno, Ethernet    2   3
 Mega2560   2   3   21    20    19    18
 Leonardo   3   2   0   1
 Due            (any pin, more info http://arduino.cc/en/Reference/AttachInterrupt)
 */

#include <idDHT11.h>

int idDHT11pin = 2; //Digital pin for comunications
int idDHT11intNumber = 0; //interrupt number (must be the one that use the previus defined pin (see table above)

//declaration
void dht11_wrapper(); // must be declared before the lib initialization

// Lib instantiate
idDHT11 DHT11(idDHT11pin,idDHT11intNumber,dht11_wrapper);

void setup()
{
  Serial.begin(9600);
//  Serial.println("idDHT11 Example program");
//  Serial.print("LIB version: ");
//  Serial.println(IDDHT11LIB_VERSION);
//  Serial.println("---------------");
}
// This wrapper is in charge of calling 
// mus be defined like this for the lib work
void dht11_wrapper() {
  DHT11.isrCallback();
}
void loop()
{
//  Serial.print("\nRecebendo informacao do sensor: ");
//  Serial.print("Read sensor: ");
//delay(100);

  
  DHT11.acquire();
  while (DHT11.acquiring())
    ;
  int result = DHT11.getStatus();
  switch (result)
  {
  case IDDHTLIB_OK: 
//    Serial.println("OK"); 
    break;
  case IDDHTLIB_ERROR_CHECKSUM: 
    Serial.println("Error\n\r\tChecksum error"); 
    break;
  case IDDHTLIB_ERROR_ISR_TIMEOUT: 
    Serial.println("Error\n\r\tISR Time out error"); 
    break;
  case IDDHTLIB_ERROR_RESPONSE_TIMEOUT: 
    Serial.println("Error\n\r\tResponse time out error"); 
    break;
  case IDDHTLIB_ERROR_DATA_TIMEOUT: 
    Serial.println("Error\n\r\tData time out error"); 
    break;
  case IDDHTLIB_ERROR_ACQUIRING: 
    Serial.println("Error\n\r\tAcquiring"); 
    break;
  case IDDHTLIB_ERROR_DELTA: 
    Serial.println("Error\n\r\tDelta time to small"); 
    break;
  case IDDHTLIB_ERROR_NOTSTARTED: 
    Serial.println("Error\n\r\tNot started"); 
    break;
  default: 
    Serial.println("Unknown error"); 
    break;
  }
  Serial.print("Humidade: ");
  Serial.print(DHT11.getHumidity(), 0); 
  Serial.println(" % ");

  Serial.print("Temperatura: ");
  Serial.print(DHT11.getCelsius(), 0);
  Serial.println(" c ");

  Serial.println(" ");


    
// tempo delay para exibicao das informacoes no monitor serial 
  delay(6000);
}

