//Sistema de control de temperatura v2

#include <OneWire.h>
#include <DallasTemperature.h>

// Pin donde conectaremos el sensor
  const int pinBoton = 6;
  const int pinReleRes = 7;
  const int pinReleVal = 8;
  const int pinDatosSensor = 9;
  boolean condicion = false;

// Instanciando
  OneWire objetoOneWire(pinDatosSensor);
  DallasTemperature sensorDS18B20(&objetoOneWire);

// Variables generales
  int buttonState;
  int cambioTemp;
  float TempSensor;
  float TempFijada;
  boolean llego = false;

void setup() {
  // Comunicación serial
    Serial.begin(9600);
    sensorDS18B20.begin();
  // Pines
    pinMode(pinBoton, INPUT);
    pinMode(pinReleRes, OUTPUT);
    pinMode(pinReleVal, OUTPUT);
}

void loop() {
  //Temperatura
    Serial.println("");
    Serial.println("0) Inicio del Loop");
    sensorDS18B20.requestTemperatures();
    TempSensor = sensorDS18B20.getTempCByIndex(0);
    
  // Proceso de evaluado
    procesoEvaluado();
    
  // Pantalla de diagnóstico
    procesoDiagnostico();
    
  // Proceso de corrección
    procesoCorreccion();
  
  delay(1000);
}

void procesoEvaluado(){
  Serial.println("1) Proceso de evaluado de temperatura");
  Serial.print("-- El boton está en: ");
  Serial.print(buttonState);
  Serial.println("");
  if(buttonState == true)
  {
    TempFijada = 50;
    Serial.print("-- Fijamos la temperatura a 50\n");
  }
  else
  {
    if(llego == true)
    {
      TempFijada = 30;
      Serial.print("-- Fijamos la temperatura a 30\n");
    }
  }
  if(TempSensor < TempFijada)
  {
    condicion = true;
    Serial.println("-- La temperatura del sensor es menor que la temperatura fijada");
  }
  else
  {
    condicion = false;
    Serial.println("-- La temperatura del sensor es mayor que la temperatura fijada");
  }
}

void procesoDiagnostico()
{
    Serial.println("3) Proceso de diagnóstico");
    Serial.print("-- Temperatura del sensor main: ");
    Serial.print(TempSensor);
    Serial.println("");
}

void procesoCorreccion(){
  Serial.println("4) Proceso de corrección");
  buttonState = digitalRead(pinBoton);
  
  if(condicion == true)
  {
    // Enciende la resistencia
      Serial.println("-- Proceso de encendido");
      Serial.println("--- Encendemos la resistencia");
      digitalWrite(pinReleRes, LOW);
      delay(30000);
      digitalWrite(pinReleRes, HIGH);
      Serial.println("--- Apagamos la resistencia");
      delay(20000);
      llego = false;
  }
  if(condicion == false)
  {
    // Apagamos la resistencia
      Serial.println("-- Proceso de apagado");
      Serial.println("--- Apagamos la resistencia");
      digitalWrite(pinReleRes, HIGH);
      llego = true;
      delay(1000);
  }
}
