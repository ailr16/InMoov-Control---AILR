//////////////////////////////////////////////////
//                  Mano v0.7                   //
//       Toma objetos de acuerdo a tamaño       //
//               Control manual                 //
//          Angel Iván Lozano Ramírez           //
//              02.04.2017  00:15h              //
//////////////////////////////////////////////////


//Servomotors library
#include <Servo.h>

//Define servomotors
Servo pinkie;
Servo ring;
Servo middle;
Servo index;
Servo thumb;

//Logic states for each finger
int pinkieL = 180;
int pinkieH = 90;
int ringL = 180;
int ringH = 80;
int middleL = 0;
int middleH = 126;
int indexL = 100;
int indexH = 15;
int thumbL = 0;
int thumbH = 123;

//Define variables
char z;

void setup() {
  pinkie.attach(11);
  ring.attach(9);
  middle.attach(5);
  index.attach(6);
  thumb.attach(10);
  Serial.begin(9600);
}

void loop(){
  if(Serial.available()>0){
    z = Serial.read();
  }
  if(z=='a'){           //Send  char 'a' trough serial monitor for open hand
    allopnd();
  }
  else if(z == 's'){    //Send  char 's' trough serial monitor for close hand
    allclosed();
  }
  else if(z == 'd'){    //Send  char 'd' trough serial monitor for grip (index and thumb)
    indexthumb();
  }
}

//Close hand
void allclosed(){
  pinkie.write(pinkieH);
  ring.write(ringH);
  middle.write(middleH);
  index.write(indexH);
  thumb.write(thumbH);
}

//Open hand
void allopnd(){
  pinkie.write(pinkieL);
  ring.write(ringL);
  middle.write(middleL);
  index.write(indexL);
  thumb.write(thumbL);
}

//Grip (index and thumb)
void indexthumb(){
  pinkie.write(pinkieL);
  ring.write(ringL);
  middle.write(middleL);
  index.write(indexH);
  thumb.write(thumbH);
}

