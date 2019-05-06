// written for the Arduino Pro Mini (or clones)

#include <PS2Keyboard.h>
#include <LiquidCrystal.h>
//#include <SoftwareSerial.h>
#include <NeoSWSerial.h>


const int DataPin = 4;
const int IRQpin = 3;

/* LCD pins definitions to match your LCD 4 bit mode */
#define RS 12
#define ENA 11
#define RW 10
#define D7 9
#define D6 8
#define D5 7
#define D4 6

/* LCD Constants to match your display */
/* Columns in display */
#define NUM_COL 20
/* Rows in display */
#define NUM_ROW 4

/* current cursor position */
int8_t col = 0;
int8_t row = 0;

PS2Keyboard keyboard;
LiquidCrystal lcd(RS, RW, ENA, D4, D5, D6, D7);
//SoftwareSerial softSerial(A0, A1); // RX, TX
NeoSWSerial softSerial( A0, A1 );

void setup()
{
  pinMode(A0, INPUT);
  pinMode(A1, OUTPUT);
  
  // Set the data rate for the SoftwareSerial port
  softSerial.begin(9600);

  delay(500);
  keyboard.begin(DataPin, IRQpin);
  Serial.begin(9600);
  Serial.println("[debug serial ok]");

  // set up the LCD's number of columns and rows
  lcd.begin(NUM_COL, NUM_ROW);
  lcd.clear();  // clear the screen
  lcd.cursor(); // Enable Cursor
  lcd.blink();  // Blinking cursor

  lcd.setCursor(0, 0);
  lcd.print("[lcd ok]");
  scrollDown();
}

void loop()
{
  if (keyboard.available())
  {
    // read the next key
    char c = keyboard.read();

    // check for some of the special keys
    if (c == PS2_ENTER)
    {
      softSerial.print("\r");
      //Serial.println();
    }
    else
    {
      // otherwise, just print all normal characters
      softSerial.print(c);
      //Serial.print(c);
      //lcd.write(c);
    }
  }
  if (softSerial.available())
  {
    char r = softSerial.read();
    if( r >= 0x20 && r <= 0x7E) {
      // printable character
      lcd.write(r);
      advance();
    } else {
      // nonprintable character
      switch(r) {
        case 0x0A: // line feed
          scrollDown();
          break;
        case 0x0D: // carriage return
          carriageReturn();
          break;
        case 0x00: // null (not del?)
          rubout();
          break;
        case 0x0C: // new page
          clear();
          break;
      }
    }
    Serial.println(r, HEX);
  }
}

void advance() {
  col += 1;
  updateCursor();
}

void carriageReturn() {
  col = 0;
  updateCursor();
}

void rubout() {
  col -= 1;
  if( col < 0 ) {
    col = 0;
  }
  // TODO erase the actual character
  updateCursor();
}

void scrollDown() {
  row += 1;
  if( row >= NUM_ROW ) { 
    row = 0;
  }
  updateCursor();
}

void updateCursor() {
  lcd.setCursor(col, row);
}

void clear() {
  lcd.clear();
  row = 0;
  col = 0;
  updateCursor();
}

