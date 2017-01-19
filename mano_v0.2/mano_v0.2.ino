/*
 * Abre y cierra la mano cuando un botón es pulsado
 * Por Angel Iván Lozano Ramírez
 * 2016
 * https://github.com/ailr16/InMoov-Control---AILR
 * https://www.youtube.com/channel/UCJ5MFm2qRBsL5Vf8Yft5vpw
 */

#include<Servo.h>             //Librería para contolar Servos        
Servo menique;                //Servo para dedo meñique
Servo anular;                 //Servo para dedo anular
Servo medio;                  //Servo para dedo medio
Servo indice;                 //Servo para dedo indice
Servo pulgar;                 //Servo para dedo pulgar

int boton = 12;               //Señal TTL de Botón en pin 12
int estado = 0;               //Estado del botón en 0


void setup() {
  menique.attach(3);          //Servo en pin 3
  anular.attach(5);           //Servo en pin 5
  medio.attach(6);            //Servo en pin 6
  indice.attach(10);          //Servo en pin 10
  pulgar.attach(11);          //Servo en pin 11
  pinMode(boton, INPUT);      //Pin botón como entrada
}

void loop() {
  estado = digitalRead(boton);    //Lectura digital del pin boton

  if(estado == HIGH){           //Condicional si la lectura es alta
    cerrar();                   //Void cerrar()
  }   
  else{                         //Si la lectura es baja
    abrir();                    //Void arir()
  }
}
//////////////////////////////////////////////////////////////////////////
//LOS ÁNGULOS SE OBTIENEN A PARTIR DE LA CALIBRACIÓN CON mano_v0.1
//////////////////////////////////////////////////////////////////////////

void abrir(){
  menique.write(180);
  anular.write(180);
  medio.write(0);
  indice.write(180);
  pulgar.write(0);
}

void cerrar(){
  menique.write(95);
  anular.write(0);
  medio.write(180);
  indice.write(60);
  pulgar.write(180);
}

