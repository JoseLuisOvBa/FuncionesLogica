/*
 * Ejemplo de finicones logicas
 * Por: Jose Luis Oviedo
 * Fecha: 11 de abril del 2022
 * 
 * Este programa es para practicar las funicones logicas
 */

// Bibliotecas
//


// Constantes
const int LED1=2;
const int BOTON1=4;

// Variables
int dato1;


// Definicion de objetos
// Condiciones iniciales

void setup() {
  pinMode (BOTON1, INPUT_PULLUP);
  pinMode (LED1, OUTPUT);
  digitalWrite (LED1, LOW);
}

void loop() {
  dato1=digitalRead(BOTON1);
  digitalWrite (LED1,dato1);
  
}
