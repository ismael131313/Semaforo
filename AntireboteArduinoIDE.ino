#include "arduino.h"
// Definición de pines para las teclas y leds
const int PIN_TECLA_1 = 2;
const int PIN_TECLA_2 = 3;
const int PIN_LED_VERDE = 4;
const int PIN_LED_AMARILLO = 5;
const int PIN_LED_ROJO = 6;

// Estados posibles de la MEF antirebote
enum Estados {
  ESPERA,
  PRESIONADA,
  LIBERADA
};
// Estados posibles de la MEF para el modo de operación del semaforo
enum ModoOperacion {
  NORMAL,
  DESCONECTADO,
  ALARMA
};
// Estados posibles de la MEF para el control de tiempo en modo normal
enum BaseTiempo {
  MEDIO,
  TNORMAL,
  DOBLE
};

// Variables para el antirrebote de las teclas
Estados estadoActualTecla1 = ESPERA;
Estados estadoActualTecla2 = ESPERA;
// Variables para el control del semáforo
ModoOperacion modoOperacion = NORMAL;
BaseTiempo baseTiempo = TNORMAL;
unsigned long tiempoAnteriorTecla1 = 0;
unsigned long tiempoAnteriorTecla2 = 0;
unsigned long tiempoBase = 1000;  // Tiempo base en milisegundos
unsigned long tiempoAnterior = 0;

// Arreglo para definir la secuencia de LEDs en modo normal
const int secuenciaNormal[] = {PIN_LED_VERDE, PIN_LED_AMARILLO, PIN_LED_ROJO};
int indiceSecuencia = 0;

void setup() {
  pinMode(PIN_TECLA_1, INPUT_PULLUP);
  pinMode(PIN_TECLA_2, INPUT_PULLUP);
  pinMode(PIN_LED_VERDE, OUTPUT);
  pinMode(PIN_LED_AMARILLO, OUTPUT);
  pinMode(PIN_LED_ROJO, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // Actualizar el estado de la MEF para la tecla 1
  Estados nuevoEstadoTecla1 = actualizarMEFTecla(PIN_TECLA_1, estadoActualTecla1, tiempoAnteriorTecla1);
  if (nuevoEstadoTecla1 != estadoActualTecla1) {
    estadoActualTecla1 = nuevoEstadoTecla1;
    if (estadoActualTecla1 == PRESIONADA) {
      // Acciones cuando la tecla 1 es presionada
      buttonPressed(1);
        cambiarBaseTiempo();
    } else if (estadoActualTecla1 == LIBERADA) {
      // Acciones cuando la tecla 1 es liberada
      buttonReleased(1);
    }
  }
  
  // Actualizar el estado de la MEF para la tecla 2
  Estados nuevoEstadoTecla2 = actualizarMEFTecla(PIN_TECLA_2, estadoActualTecla2, tiempoAnteriorTecla2);
  if (nuevoEstadoTecla2 != estadoActualTecla2) {
    estadoActualTecla2 = nuevoEstadoTecla2;
    if (estadoActualTecla2 == PRESIONADA) {
      // Acciones cuando la tecla 2 es presionada
      buttonPressed(2);
        cambiarModoOperacion();
    } else if (estadoActualTecla2 == LIBERADA) {
      // Acciones cuando la tecla 2 es liberada
      buttonReleased(2);
    }
  }

  // Actualizar el estado del semáforo según el modo de operación
  switch (modoOperacion) {
    case NORMAL:
      semaforoNormal();
      break;
      
    case DESCONECTADO:
      semaforoDesconectado();
      break;
      
    case ALARMA:
      semaforoAlarma();
      break;
  }
}




Estados actualizarMEFTecla(int pinTecla, Estados estadoActual, unsigned long& tiempoAnterior) {
  Estados nuevoEstado = estadoActual;
  int lectura = digitalRead(pinTecla);
  
  switch (estadoActual) {
    case ESPERA:
      if (lectura == LOW) {
        nuevoEstado = PRESIONADA;
        tiempoAnterior = millis();
      }
      break;
      
    case PRESIONADA:
      if (lectura == HIGH) {
        nuevoEstado = LIBERADA;
        tiempoAnterior = millis();
      }
      break;
      
    case LIBERADA:
      if (lectura == HIGH && millis() - tiempoAnterior >= 50) {
        nuevoEstado = ESPERA;
      }
      break;
  }
  
  return nuevoEstado;
}

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
void cambiarBaseTiempo() {
  // Cambiar la base de tiempo para la condición de operación normal
  if (baseTiempo == MEDIO) {
    baseTiempo = TNORMAL;
    tiempoBase = 1000;
  } else if (baseTiempo == TNORMAL) {
    baseTiempo = DOBLE;
    tiempoBase = 2000;
  } else if (baseTiempo == DOBLE) {
    baseTiempo = MEDIO;
    tiempoBase = 500;
  }
}
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

void semaforoNormal() {
  // Secuencia de LEDs en modo normal
  unsigned long tiempoActual = millis();
  
  if (tiempoActual - tiempoAnterior >= tiempoBase) {
    tiempoAnterior = tiempoActual;
    
    digitalWrite(secuenciaNormal[indiceSecuencia], LOW);  // Apagar el LED actual
    
    indiceSecuencia = (indiceSecuencia + 1) % 3;//sizeof(secuenciaNormal);  // Avanzar al siguiente LED
    
    digitalWrite(secuenciaNormal[indiceSecuencia], HIGH);  // Encender el siguiente LED
  }
}

void semaforoDesconectado() {
  // LED amarillo intermitente cada 500 ms
  unsigned long tiempoActual = millis();
  digitalWrite(PIN_LED_VERDE, LOW);
  digitalWrite(PIN_LED_ROJO, LOW);
  if (tiempoActual - tiempoAnterior >= 500) {
    tiempoAnterior = tiempoActual;
    
    static bool estadoLED = false;
    
    if (estadoLED) {
      digitalWrite(PIN_LED_AMARILLO, HIGH);
      estadoLED = false;
    } else {
      digitalWrite(PIN_LED_AMARILLO, LOW);
      estadoLED = true;
    }
  }
}

void semaforoAlarma() {
  // LED rojo intermitente cada 1 s
  unsigned long tiempoActual = millis();
  digitalWrite(PIN_LED_VERDE, LOW);
  digitalWrite(PIN_LED_AMARILLO, LOW);
  if (tiempoActual - tiempoAnterior >= 1000) {
    tiempoAnterior = tiempoActual;
    
    static bool estadoLED = false;
    
    if (estadoLED) {
      digitalWrite(PIN_LED_ROJO, HIGH);
      estadoLED = false;
    } else {
      digitalWrite(PIN_LED_ROJO, LOW);
      estadoLED = true;
    }
  }
}