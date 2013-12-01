/*
  Blinks a message in morse code on the built-in LED.
 */
 
#include <ctype.h>

const String message = "communicating with friendly horses";

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
const int led = 13;

// How long to wait between certain blinks
const int repeat_delay = 2500;
const int unit_delay = 150;
const int letter_delay = 3 * unit_delay;
const int word_delay = 7 * unit_delay;
const int dot_length = unit_delay;
const int dash_length = 3 * unit_delay;

// maximum length of a morse code character
const byte morse_len = 5;

// 1 is short, 2 is long, 0 is end
const byte morse_map[][morse_len] = {
                     {1, 2, 0, 0, 0}, // a 0
                     {2, 1, 1, 1, 0}, // b 1
                     {2, 1, 2, 1, 0}, // c 2
                     {2, 1, 1, 0, 0}, // d 3
                     {1, 0, 0, 0, 0}, // e 4
                     {1, 1, 2, 1, 0}, // f 5
                     {2, 2, 1, 0, 0}, // g 6
                     {1, 1, 1, 1, 0}, // h 7
                     {1, 1, 0, 0, 0}, // i 8
                     {1, 2, 2, 2, 0}, // j 9
                     {2, 1, 2, 0, 0}, // k 10
                     {1, 2, 1, 1, 0}, // l 11
                     {2, 2, 0, 0, 0}, // m 12
                     {2, 1, 0, 0, 0}, // n 13
                     {2, 2, 2, 0, 0}, // o 14
                     {1, 2, 2, 1, 0}, // p 15
                     {2, 2, 1, 2, 0}, // q 16
                     {1, 2, 1, 0, 0}, // r 17
                     {1, 1, 1, 0, 0}, // s 18
                     {2, 0, 0, 0, 0}, // t 19
                     {1, 1, 2, 0, 0}, // u 20
                     {1, 1, 1, 2, 0}, // v 21
                     {1, 2, 2, 0, 0}, // w 22
                     {2, 1, 1, 2, 0}, // x 23
                     {2, 1, 2, 2, 0}, // y 24
                     {2, 2, 1, 1, 0}, // z 25
                   };

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

void morse_blink_letter(String c) {
  String tmp;
  
  // I don't know the right way to do this, but we only handle alpha chars for now
  if (! isalpha((int) c[0])) {
    Serial.println("got unexpected letter: " + c);
    return;
  }
  c.toLowerCase();
  
  // Get index of letter in morse_map
  byte letterval = c[0] - 97;  // 97 = ascii 'a'
  tmp = "letterval is: ";
  Serial.println(tmp + letterval);
  
  // Copy the units for the letter into a new array we can traverse
  byte pattern[morse_len];
  memcpy(pattern, morse_map[letterval], morse_len*sizeof(byte));
  
  // Signal each unit for the letter
  for (byte b = 0; b < morse_len; b++) {
    tmp = "val is: ";
    Serial.println(tmp + pattern[b]);
    
    switch (pattern[b]) {
      case 0:
        // done with letter
        return;
      case 1:
        // dot
        digitalWrite(led, HIGH);
        delay(dot_length);
        digitalWrite(led, LOW);
        
        break;
      case 2:
        // dash
        digitalWrite(led, HIGH);
        delay(dash_length);
        digitalWrite(led, LOW);
        
        break;
    }
    
    if (b < morse_len - 1) {
      // Not the last letter  (only pause between units)
      Serial.println("Delaying between units");
      delay(unit_delay);
    }
  }
}

void morse_blink_string(String str) {
  Serial.println("Given string to print: " + str);

  for (int i = 0; i < str.length(); i++) {
    // Character we're checking.  Save as String to get toLowerCase().
    String c = str.substring(i, i+1);
    Serial.println("blinking char: " + c);
    
    if (c == " ") {
      Serial.println("Delaying between words");
      delay(word_delay);
    } else {
      morse_blink_letter(c);
      
      // Delay between letters, unless next is a space that would delay anyway
      if (str[i+1] != ' ') {
        Serial.println("Delaying between letters");
        delay(letter_delay);
      }
    }
  }
}

// the loop routine runs over and over again forever:
void loop() {
  Serial.println("--- starting loop ---");
  morse_blink_string(message);
  delay(repeat_delay);
}
