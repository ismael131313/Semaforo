/*
 * teclas.c
 *
 *  Created on: Jun 18, 2023
 *      Author: ISMAEL
 */
#include "teclas.h"
//#include "Arduino.h"
//#include "HardwareSerial.h"
//#include "Print.h"

void buttonPressed(int16_t tecla) {
  // Acciones correspondientes al flanco descendente
  Serial.print("Tecla ");
  Serial.print(tecla);
  Serial.println(" presionada");
}
void buttonReleased(int16_t tecla) {
  // Acciones correspondientes al flanco ascendente
  Serial.print("Tecla ");
  Serial.print(tecla);
  Serial.println(" liberada");
}




