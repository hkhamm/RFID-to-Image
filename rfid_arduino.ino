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
  delay(30000);
  
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
  // print_serial();
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


void print_serial() {
  if (flag == 1) {
    String one = String(id[8], HEX);
    String two = String(id[7], HEX);
    String three = String(id[6], HEX);
    String four = String(id[5], HEX);
    tag = String(one + two + three + four);
    
    Serial.println(tag);
    delay(100);
  }
}


void send_key() {
  String taga = "d11110aa";
  String tagb = "d115fb3a";
  String tagc = "d1136ffa";
  String tagd = "d11a754a";
  String tage = "d1a96fa";
  String tagf = "d11df5a";
  String tagg = "d114d11a";
  String tagh = "d11d27a";
  String tagi = "d1174daa";
  String tagj = "d118fdea";
  String tagk = "d1ce8a";
  String tagl = "d1bbdaa";
  String tagm = "d1e494a";
  String tagn = "d11946a";
  String tago = "d11bfa2a";
  String tagp = "d11976a";
  String tagq = "d1d2d4a";
  String tagr = "d1169eaa";
  String tags = "d11bec7a";
  String tagt = "d1abcaa";
  String tagu = "d1b7daa";
  String tagv = "d1bebfa";
  String tagw = "d11422aa";
  String tagx = "d11bb65a";
  String tagy = "d11bf42a";
  String tagz = "d11753aa";
  String tag1 = "d11bb85a";
  String tag2 = "d118d3aa";
  String tag3 = "d119d6a";
  String tag4 = "d11cd32a";
  String tag5 = "d1af0aa";
  String tag6 = "d11bf22a";
  
  if (flag == 1) {
    String one = String(id[8], HEX);
    String two = String(id[7], HEX);
    String three = String(id[6], HEX);
    String four = String(id[5], HEX);
    tag = String(one + two + three + four);
    
    if (tag == taga) { 
      Keyboard.write('a');
    } else if (tag == tagb) {
      Keyboard.write('b');
    } else if (tag == tagc) {
      Keyboard.write('c');
    } else if (tag == tagd) {
      Keyboard.write('d');
    } else if (tag == tage) {
      Keyboard.write('e');
    } else if (tag == tagf) {
      Keyboard.write('f');
    } else if (tag == tagg) {
      Keyboard.write('g');
    } else if (tag == tagh) {
      Keyboard.write('h');
    } else if (tag == tagi) {
      Keyboard.write('i');
    } else if (tag == tagj) {
      Keyboard.write('j');
    } else if (tag == tagk) {
      Keyboard.write('k');
    } else if (tag == tagl) {
      Keyboard.write('l');
    } else if (tag == tagm) {
      Keyboard.write('m');
    } else if (tag == tagn) {
      Keyboard.write('n');
    } else if (tag == tago) {
      Keyboard.write('o');
    } else if (tag == tagp) {
      Keyboard.write('p');
    } else if (tag == tagq) {
      Keyboard.write('q');
    } else if (tag == tagr) {
      Keyboard.write('r');
    } else if (tag == tags) {
      Keyboard.write('s');
    } else if (tag == tagt) {
      Keyboard.write('t');
    } else if (tag == tagu) {
      Keyboard.write('u');
    } else if (tag == tagv) {
      Keyboard.write('v');
    } else if (tag == tagw) {
      Keyboard.write('w');
    } else if (tag == tagx) {
      Keyboard.write('x');
    } else if (tag == tagy) {
      Keyboard.write('y');
    } else if (tag == tagz) {
      Keyboard.write('z');
    } else if (tag == tag1) {
      Keyboard.write('1');
    } else if (tag == tag2) {
      Keyboard.write('2');
    } else if (tag == tag3) {
      Keyboard.write('3');
    } else if (tag == tag4) {
      Keyboard.write('4');
    } else if (tag == tag5) {
      Keyboard.write('5');
    } else if (tag == tag6) {
      Keyboard.write('6');
    }
    
    delay(100);
  }
}


