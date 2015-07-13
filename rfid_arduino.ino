/*
  RFID Eval 13.56MHz Shield example sketch v10.1

  Aaron Weiss, aaron at sparkfun dot com
  OSHW license: http://freedomdefined.org/OSHW

  works with 13.56MHz MiFare 1k tags

  Based on hardware v13:
  D7 -> RFID RX
  D8 -> RFID TX
  D9 -> XBee TX
  D10 -> XBee RX

  The Arduino documentation states:

   Not all pins on the Leonardo and Micro support change interrupts, so only the following can be used for RX: 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).

  The RFID Eval 13.56MHz Shield uses pin 7 for RX, so to use a Leonardo the shield's D7 pin must be connected to one of the above pins on the Leonardo.

  Note: RFID Reset attached to D13 (aka status LED)

  Usage: Sketch prints 'Start' and waits for a tag. When a tag is in range, the shield reads the tag,
  blinks the 'Found' LED and prints the serial number of the tag to the serial port.

  06/04/2013 - Modified for compatibility with Arduino 1.0. Seb Madgwick.
  04/08/2015 - Modified for compatibility with Arduino Leonardo. Keith Hamm.
*/

#include <SoftwareSerial.h>

// Use a jumper to bridge the Arduino's D9 pin to the shield's D7 pin.
SoftwareSerial rfid(8, 9); // (RX, TX)

// Prototypes
void halt(void);
void parse(void);
void print_serial(void);
void read_serial(void);
void search(void);
void set_flag(void);

// Global var
int flag = 0;
int id[11];
String tag;


void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for serial port to connect. Needed for Leonardo only.
  }
  Serial.println("Start");

  // Initialize control over the keyboard.
  Keyboard.begin();

  rfid.begin(19200);
  delay(10);

  Serial.println("Waiting for SM130");
  
  delay(1000);
  reset_rfid();
  
  while (!rfid.available()) {
    ;
  }

  Serial.println("SM130 found");
  halt();
}


void loop() {
  search();
  delay(10);
  parse();
  set_flag();
//  print_serial();
  send_key();
  delay(100);
}


void reset_rfid() {
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);  // sets the LED on
  delay(1000);             // waits for a second
  digitalWrite(13, LOW);   // sets the LED off
  delay(1000); 
}


void halt() {
  // Halt tag.
  rfid.write((uint8_t) 255); // 0xFF
  rfid.write((uint8_t) 0);   // 0x00
  rfid.write((uint8_t) 1);   // 0x01
  rfid.write((uint8_t) 147); // 0x93
  rfid.write((uint8_t) 148); // 0x94
}


void search() {
  // Search for RFID tag.
  rfid.write((uint8_t) 255); // 0xFF
  rfid.write((uint8_t) 0);   // 0x00
  rfid.write((uint8_t) 1);   // 0x01
  rfid.write((uint8_t) 130); // 0x82
  rfid.write((uint8_t) 131); // 0x83
  delay(10);
}


void parse() {
  while (rfid.available()) {
    if (rfid.read() == 255) {
      for (int i = 1; i < 11; i++) {
        id[i] = rfid.read();
      }
    }
  }
}


void set_flag() {
  if (id[2] == 6) {
    flag++;
  }

  if (id[2] == 2) {
    flag = 0;
  }
}


//void print_serial() {
//  if (flag == 1) {
//    String one = String(id[8], HEX);
//    String two = String(id[7], HEX);
//    String three = String(id[6], HEX);
//    String four = String(id[5], HEX);
//    tag = String(one + two + three + four);
//    
//    Serial.println(tag);
//    delay(100);
//  }
//}


void send_key() {
  String tag01 = "d11110aa";
  String tag02 = "d115fb3a";
  String tag03 = "d1174daa";
  if (flag == 1) {
    String one = String(id[8], HEX);
    String two = String(id[7], HEX);
    String three = String(id[6], HEX);
    String four = String(id[5], HEX);
    tag = String(one + two + three + four);
    
    if (tag == tag01) { 
      Keyboard.write('a');
    } else if (tag == tag02) {
      Keyboard.write('b');
    } else if (tag == tag03) {
      Keyboard.write('c');
    }
    delay(100);
  }
}


