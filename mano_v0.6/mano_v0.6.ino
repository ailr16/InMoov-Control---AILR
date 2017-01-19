////////////////////////////////////////////////////////////////////////
// Arduino Bluetooth Interface with Mindwave
// 
// This is example code provided by NeuroSky, Inc. and is provided
// license free.
//
//  Control mental por niveles de atención
//  Modificado por Lozano Ramírez Angel Iván
//  2/12/2016
//  v0.6
//  Arduino Nano
//  https://goo.gl/XCEf7p
//  https://goo.gl/rQB4H5
////////////////////////////////////////////////////////////////////////

//Librería de servos
#include <Servo.h>

//Declaración de servos
Servo menique;
Servo anular;
Servo medio;
Servo indice;
Servo pulgar;

//Declaración de estados lógicos de dedos
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
  menique.attach(11);  
  anular.attach(9);
  medio.attach(5);  
  indice.attach(6);
  pulgar.attach(10);
  
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

          switch(attention / 10) {
          case 0:
            menique.write(meniqueH);
            anular.write(anularH);
            medio.write(medioH);
            indice.write(indiceH);
            pulgar.write(pulgarH);          
            break;
          case 1:
            menique.write(meniqueH);
            anular.write(anularH);
            medio.write(medioH);
            indice.write(indiceL);
            pulgar.write(pulgarH);
            break;
          case 2:
            menique.write(meniqueH);
            anular.write(anularH);
            medio.write(medioL);
            indice.write(indiceL);
            pulgar.write(pulgarH);
            break;
          case 3:              
            menique.write(meniqueH);
            anular.write(anularL);
            medio.write(medioL);
            indice.write(indiceL);
            pulgar.write(pulgarH);             
            break;
          case 4:
            menique.write(meniqueL);
            anular.write(anularL);
            medio.write(medioL);
            indice.write(indiceL);
            pulgar.write(pulgarH);             
            break;
          case 5:
            menique.write(meniqueL);
            anular.write(anularL);
            medio.write(medioL);
            indice.write(indiceL);
            pulgar.write(pulgarL);             
            break;
          case 6:              
            menique.write(meniqueH);
            anular.write(anularH);
            medio.write(medioH);
            indice.write(indiceH);
            pulgar.write(pulgarL);              
            break;
          case 7:
            menique.write(meniqueL);
            anular.write(anularH);
            medio.write(medioH);
            indice.write(indiceL);
            pulgar.write(pulgarH);             
            break;    
          case 8:
            menique.write(meniqueH);
            anular.write(anularH);
            medio.write(medioH);
            indice.write(indiceL);
            pulgar.write(pulgarL);
            break;
          case 9:
            menique.write(meniqueL);
            anular.write(anularL);
            medio.write(medioL);
            indice.write(indiceL);
            pulgar.write(pulgarL);  
            break;
          case 10:
            menique.write(meniqueL);
            anular.write(anularL);
            medio.write(medioL);
            indice.write(indiceL);
            pulgar.write(pulgarL);  
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


