///////////////////////////////////////////
//     Angel Iván Lozano Ramírez         //
//        Projecto Mano robótica         //
//            Firmware v0.5              //
//              25/06/2016               //
//    Secuencia de movimientos de una    //
//            mano robótica              //
//         https://goo.gl/XCEf7p         //
//         https://goo.gl/rQB4H5         //
///////////////////////////////////////////

#include <Servo.h>

Servo menique;
Servo anular;
Servo medio;
Servo indice;
Servo pulgar;

int meniqueH = 90;
int meniqueL = 180;
int anularH = 60;
int anularL = 180;
int medioH = 120;
int medioL = 0;
int indiceH = 92;
int indiceL = 180;
int pulgarH = 176;
int pulgarL = 20;

void setup() {
  menique.attach(11);  
  anular.attach(10);
  medio.attach(9);
  indice.attach(6);
  pulgar.attach(5);
}

void loop() {
  cero();
  delay(5000);
  uno();
  delay(5000);
  dos();
  delay(5000);
  tres();
  delay(5000);
  cuatro();
  delay(5000);
  cinco();
  delay(5000);
  cuatro();
  delay(5000);
  tres();
  delay(5000);
  dos();
  delay(5000);
  uno();
  delay(5000);
  cero();
  delay(5000);
  gesture();
  delay(5000);
}

void cero(){
  menique.write(meniqueH);
  anular.write(anularH);
  medio.write(medioH);
  indice.write(indiceH);
  pulgar.write(pulgarH);
}

void uno(){
  menique.write(meniqueH);
  anular.write(anularH);
  medio.write(medioH);
  indice.write(indiceL);
  pulgar.write(pulgarH);
}

void dos(){
  menique.write(meniqueH);
  anular.write(anularH);
  medio.write(medioL);
  indice.write(indiceL);
  pulgar.write(pulgarH);
}

void tres(){
  menique.write(meniqueH);
  anular.write(anularL);
  medio.write(medioL);
  indice.write(indiceL);
  pulgar.write(pulgarH);
}

void cuatro(){
  menique.write(meniqueL);
  anular.write(anularL);
  medio.write(medioL);
  indice.write(indiceL);
  pulgar.write(pulgarH);
}

void cinco(){
  menique.write(meniqueL);
  anular.write(anularL);
  medio.write(medioL);
  indice.write(indiceL);
  pulgar.write(pulgarL);
}

void gesture(){
  menique.write(meniqueL);
  anular.write(anularH);
  medio.write(medioH);
  indice.write(indiceL);
  pulgar.write(pulgarH);
}

