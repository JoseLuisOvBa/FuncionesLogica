/*
 * Simulacion de refrigeracion de servidores
 * Por: Jose Luis Oviedo
 * Fecha: 18 de abril del 2022
 * 
 * caso 1: Es siguiente programa resuelve el problema de Refirgeracion
 * dando prioridad al modo manual.
 * 
 * Caso 2: El automatico se aciva con sobrecarga, con alta demanda o 
 * con la temperatura elevada a la referencia.
 * 
 * En caso 3: de que se cumplan al mismo tiempo la sobrecarga, 
 * con alta demanda y con la temperatura elevada a la referencia
 * se activan los dos modos: Manual y automatico
 * 
 * Si no se cumplen los caso anteriores que queda en espra
 * con lo modos manual y automatico apagados.
 */

// Bibliotecas
#include "DHT.h"


// Constantes
#define DHTPIN 12  // Digital pin connected to the DHT sensor 
#define DHTTYPE    DHT11     // DHT 11
const int BManual=14; // Manual ACTIVA LA REF AL SER ACTIVADO
const int BAltDem=15; // ALTA DEMANDA
const int BSobCar=13; // SOBRE CARGA DE FUNCIONAMIENTP
const int LManu=4;  // MANUAL
const int LAut=2;  // AUTOMA
unsigned long delayMS = 1000;


// Variables
unsigned long tiempo_inicio = 0, tiempo_actual;


// Definicion de objetos
DHT dht(DHTPIN, DHTTYPE);

// Condiciones iniciales




void setup() {
  Serial.begin(115200);
  Serial.println(F("DHT11 test!"));
  dht.begin();
  
  pinMode (BManual, INPUT_PULLUP);
  pinMode (BAltDem, INPUT_PULLUP);
  pinMode (BSobCar, INPUT_PULLUP);
  pinMode (LManu, OUTPUT);
  pinMode (LAut, OUTPUT);
  digitalWrite (LManu, LOW);
  digitalWrite (LAut, LOW);
}



void loop() {
// Condiciones iniciales
  float t;
  float tr=30;
  int edoManual;
  int edoAltDem;
  int edoSobCar;


  tiempo_actual = millis();
  
  if (tiempo_actual - tiempo_inicio > delayMS){
    t = dht.readTemperature();
    
    // Check if any reads failed and exit early (to try again).
    if (isnan(t)) {
      Serial.println(F("Error de lectura del sensor DHT11!"));
      return;
    }

    
    tiempo_inicio = tiempo_actual;
  }

  

   Serial.println(t);

  edoManual=digitalRead(BManual);
  edoAltDem=digitalRead(BAltDem);
  edoSobCar=digitalRead(BSobCar);


/***************  Caso 1 *******************************/
    if(edoManual){
    digitalWrite (LManu,1);  //  lectura de boton manual
    digitalWrite (LAut,0);
    } 

/***************  Caso 2 *******************************/

    else if((edoAltDem||edoSobCar)&&t>tr) {   //Alta demanda o Sobrecarga y Sensor
    digitalWrite (LManu,1); 
    digitalWrite (LAut,1);
    } 
/***************  Caso 3 *******************************/

    else if(edoAltDem||edoSobCar||t>tr) {     // Alta demando o Sobre Carga
    digitalWrite (LManu,0);
    digitalWrite (LAut,1);
    } 

/***************  si no se cumplen los casos anteriores **********/

    else {
    Serial.print(F("  En Espera . . . "));
    digitalWrite (LManu,0);
    digitalWrite (LAut,0);
    }
 
}
