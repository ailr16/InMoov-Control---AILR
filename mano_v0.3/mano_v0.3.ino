///////////////////////////////////////////
//     Angel Iván Lozano Ramírez         //
//        Projecto Mano robótica         //
//            Firmware v0.3              //
//              01/04/2016               //
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
  menique.attach(3);
  anular.attach(5);
  medio.attach(6);
  indice.attach(10);
  pulgar.attach(11);
  pinMode(pot, INPUT);
  Serial.begin(9600);
}

void loop() {
  valor = analogRead(pot);
  Serial.println(valor);

  val = map(valor, 0, 1023, 180, 0);
  val2 = map(valor, 0, 1023, 0, 180);
  val3 = map(valor, 0, 1023, 180, 95);
  val4 = map(valor, 0, 1023, 180, 60);
  val5 = map(valor, 0, 1023, 0, 180);
  
  menique.write(val3);
  anular.write(val);
  medio.write(val2);
  indice.write(val4);
  pulgar.write(val5);
}
