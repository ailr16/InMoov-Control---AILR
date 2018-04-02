////////////////////////////////////////////////////////////////////////
// Arduino Bluetooth Interface with Mindwave
// 
// This is example code provided by NeuroSky, Inc. and is provided
// license free.
//
//  Control mental por niveles de atención
//  Modificado por Lozano Ramírez Angel Iván
//  2/04/2018
//  v0.8
//  Arduino Nano
//  https://goo.gl/XCEf7p
//  https://goo.gl/rQB4H5
////////////////////////////////////////////////////////////////////////

//Librería de servos
#include <Servo.h>

//Declaration of servos
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

#define LED 13              //Declarar valor 13 para LED 
#define BAUDRATE 57600      //Decalrar velocidad en 57600 baudios para comunicación Bluetooth
#define DEBUGOUTPUT 0       //Declarar lectura de bluetooth

#define powercontrol 10     //Declarar valor 10 para powercontrol

//Variables de CHECKSUM
byte generatedChecksum = 0;
byte checksum = 0; 
int payloadLength = 0;
byte payloadData[64] = {
  0};
byte poorQuality = 0;
byte attention = 0;
byte meditation = 0;

// Variables del sistema
long lastReceivedPacket = 0;
boolean bigPacket = false;

//////////////////////////////
// Configuración ATMEGA328P //
/////////////////////////////
void setup() {
//Salidas
  //Salidas PWM para servos
  pinkie.attach(11);
  ring.attach(9);
  middle.attach(5);
  index.attach(6);
  thumb.attach(10);
  
//Salida indicadora de calidad de señal
  pinMode(LED, OUTPUT);
  Serial.begin(BAUDRATE);           // USB

}

////////////////////////////////
// Leer datos de UART Serial  //
////////////////////////////////
byte ReadOneByte() {
  int ByteRead;

  while(!Serial.available());
  ByteRead = Serial.read();

#if DEBUGOUTPUT  
  //Serial.print((char)ByteRead);   // echo the same byte out the USB serial (for debug purposes)
#endif

  return ByteRead;
}

/////////////////
//Lazo Infinito//
////////////////
void loop() {


  // Buscar bytes
  if(ReadOneByte() == 170) {
    if(ReadOneByte() == 170) {

      payloadLength = ReadOneByte();
      if(payloadLength > 169)                      //Payload length can not be greater than 169
          return;

      generatedChecksum = 0;        
      for(int i = 0; i < payloadLength; i++) {  
        payloadData[i] = ReadOneByte();            //Read payload into memory
        generatedChecksum += payloadData[i];
      }   

      checksum = ReadOneByte();                      //Read checksum byte from stream      
      generatedChecksum = 255 - generatedChecksum;   //Take one's compliment of generated checksum

        if(checksum == generatedChecksum) {    

        poorQuality = 200;
        attention = 0;
        meditation = 0;

        for(int i = 0; i < payloadLength; i++) {    // Parse the payload
          switch (payloadData[i]) {
          case 2:
            i++;            
            poorQuality = payloadData[i];
            bigPacket = true;            
            break;
          case 4:
            i++;
            attention = payloadData[i];                        
            break;
          case 5:
            i++;
            meditation = payloadData[i];
            break;
          case 0x80:
            i = i + 3;
            break;
          case 0x83:
            i = i + 25;      
            break;
          default:
            break;
          } // switch
        } // for loop

#if !DEBUGOUTPUT

        // *** Add your code here ***

        if(bigPacket) {
          if(poorQuality == 0)
            digitalWrite(LED, HIGH);
          else
            digitalWrite(LED, LOW);
          //Serial.print("PoorQuality: ");
          //Serial.print(poorQuality, DEC);
          //Serial.print(" Attention: ");
          //Serial.print(attention, DEC);
          //Serial.print(" Time since last packet: ");
          //Serial.print(millis() - lastReceivedPacket, DEC);
          lastReceivedPacket = millis();
          //Serial.print("\n");

          switch(attention / 20) {
          case 0:       //Open
            pinkie.write(pinkieL);
            ring.write(ringL);
            middle.write(middleL);
            index.write(indexL);
            thumb.write(thumbL);         
            break;
          case 1:       //Grip (thumb and index)
            pinkie.write(pinkieL);
            ring.write(ringL);
            middle.write(middleL);
            index.write(indexH);
            thumb.write(thumbH);
            break;
          case 2:       //Grip (thumb and middle)
            pinkie.write(pinkieL);
            ring.write(ringL);
            middle.write(middleH);
            index.write(indexL);
            thumb.write(thumbH);
            break;
          case 3:        //Point (with index)
            pinkie.write(pinkieH);
            ring.write(ringH);
            middle.write(middleH);
            index.write(indexL);
            thumb.write(thumbH);                 
            break;
          case 4:        //Closed
            pinkie.write(pinkieH);
            ring.write(ringH);
            middle.write(middleH);
            index.write(indexH);
            thumb.write(thumbH);            
            break;
          }                     
        }
#endif        
        bigPacket = false;        
      }
      else {
        // Checksum Error
      }  // end if else for checksum
    } // end if read 0xAA byte
  } // end if read 0xAA byte
}


