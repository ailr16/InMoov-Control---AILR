///////////////////////////////////////////
//     Angel Iván Lozano Ramírez         //
//        Projecto Mano robótica         //
//            Firmware v0.4              //
//              21/04/2016               //
//   Control proporcional de una mano    //
//  robótica con  potenciómetro de 10K   //
//        https://goo.gl/XCEf7p          //
//        https://goo.gl/rQB4H5          //
///////////////////////////////////////////

#include<Servo.h>
Servo menique;
Servo anular;
Servo medio;
Servo indice;
Servo pulgar;

int pot = A0;
int valor = 0;
int val = 0;
int val2 = 0;
int val3 = 0;
int val4 = 0;
int val5 = 0;

void setup() {
  menique.attach(11);
  anular.attach(10);
  medio.attach(9);
  indice.attach(6);
  pulgar.attach(5);
  pinMode(pot, INPUT);
  Serial.begin(9600);
}

void loop() {
  valor = analogRead(pot);
  Serial.println(valor);

  val = map(valor, 0, 1023, 180, 60);      //Anular
  val2 = map(valor, 0, 1023, 0, 120);     //Medio
  val3 = map(valor, 0, 1023, 180, 64);    //Meñique
  val4 = map(valor, 0, 1023, 180, 92);    //Indice
  val5 = map(valor, 0, 1023, 0, 128);     //Pulgar
  
  menique.write(val3);
  anular.write(val);
  medio.write(val2);
  indice.write(val4);
  pulgar.write(val5);
}

