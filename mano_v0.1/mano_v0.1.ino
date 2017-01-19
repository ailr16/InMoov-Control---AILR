/*
 * Código para calibración y prueba de Servomotores
 * Por Angel Iván Lozano Ramírez
 * 2016
 * https://github.com/ailr16/InMoov-Control---AILR
 * https://www.youtube.com/channel/UCJ5MFm2qRBsL5Vf8Yft5vpw
 */

#include <Servo.h>            //Librería para control de servos

Servo motor;                  //Creación de servo

int pot = 0;                  //Pin A0 para leer valor analógico
int angulo = 0;               //Valor tipo entero de 0 para ángulo
int valor = 0;


void setup() {
  pinMode(pot, INPUT);        //Pin A0 como entrada
  motor.attach(9);            //Servomotor en pin 9
  Serial.begin(9600);         //Iniciar comunicación serie con PC
}

void loop() {
  
   valor = analogRead(A0);    //Asignar lectura analógica a entero valor
   angulo  = map( valor, 0, 1024, 5, 180);      //Mapear límites y asignar a entero ángulo
   motor.write(angulo);       //Escribir ángulo en servomotor
   delay(1);                  //Retardo de 1ms
   
   Serial.println(valor);     //Imprimir valor en monitor serial

}
