/*
 * uart.c
 *
 *  Created on: Jun 19, 2023
 *      Author: ISMAEL
 */
#include "teclas.h"
#include "arduino.h"
#include "uart.h"

//Indicamos el modo de operacion del semaforo

void cambiarModoOperacion() {
  // Cambiar el modo de operación del semáforo
  if (modoOperacion == NORMAL) {
    modoOperacion = DESCONECTADO;
  } else if (modoOperacion == DESCONECTADO) {
    modoOperacion = ALARMA;
  } else if (modoOperacion == ALARMA) {
    modoOperacion = NORMAL;
  }
  Serial.print("Modo de operacion: ");
  Serial.println(modoOperacion);
}



