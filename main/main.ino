//libraries 
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_NeoPixel.h>


// LED Strip values
#define LED_Strip_COUNT 12 
#define LED_Strip_PIN 10
#define DelayVal 50 // Time (in milliseconds) to pause between pixels

//Servos setup
#define Servo1_pin 3
#define Servo2_pin 5
//The angles of when the gate will be opened or closed
#define gate_Opened 90 
#define gate_Closed 180



//IR setup
int IR_receiver1_pin = 13;
int IR_receiver2_pin = 12;
int IR_receiver3_pin = 11; //exit sensor

//LED Pin setup
#define LED1 2 //red
#define LED2 4 //red
#define LED3 6  //green
#define LED4 8  //green

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_Strip_COUNT, LED_Strip_PIN, NEO_GRB + NEO_KHZ800);

Servo Servo1;
Servo Servo2;

 
unsigned long end_time;
int count_Marble = 0;


//the size of the display (Width and the height) 
int cols = 16, rows = 2;
LiquidCrystal_I2C lcd(0x27, cols, rows); // LCD(address, cols rows); 


void setup()
{
  	pinMode(LED1, OUTPUT); //LED1
  	pinMode(LED2, OUTPUT); //LED2
    pinMode(LED3, OUTPUT); //LED3
  	pinMode(LED4, OUTPUT); //LED4 
  	//Initialise LED Strip
	  
    strip.begin();
  
	  //servos setup
    //assume start position of gates open
	  Servo1.attach(Servo1_pin);
    Servo2.attach(Servo2_pin);
    Servo1.write(gate_Opened);
    Servo2.write(gate_Opened);
	
  	//IR setup
    pinMode (IR_receiver1_pin, INPUT_PULLUP); // sensor1 pin INPUT
    pinMode (IR_receiver2_pin, INPUT_PULLUP); // sensor2 pin INPUT
    pinMode (IR_receiver3_pin, INPUT_PULLUP); // sensor3  pin INPUT

    //lcd setup
    //lcd.begin(cols, rows);
    lcd.init();
    lcd.backlight();
    lcd.print("sonething something ");
    Serial.begin(9600);
}

void loop()
{
  // Gate 1
  if (digitalRead(IR_receiver1_pin) == HIGH){
    digitalWrite(LED1, HIGH);
    end_time = millis() + 1200;
    Servo1.write(gate_Closed);
    if (millis() > end_time){
      digitalWrite(LED1, LOW);
      digitalWrite(LED3, HIGH);
      Servo1.write(gate_Opened);
    }
  }

  //Gate 2
  if (digitalRead(IR_receiver2_pin) == HIGH){
    
      digitalWrite(LED2, HIGH);
      end_time = millis() + 1200;
      Servo2.write(gate_Closed);
      if (millis() > end_time) {
          digitalWrite(LED2, LOW);
          digitalWrite(LED4, HIGH);
          Servo2.write(gate_Opened);
      }
  }


    //XXXXXXX
  //LED STRIP CODE START
  //XXXXXXX
  strip.clear(); // Set all pixel colors to 'off'
  for(int i=0; i < LED_Strip_COUNT; i++) { 
    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    strip.setPixelColor(i, strip.Color(0, 150, 0));
    strip.show();   // Send the updated pixel colors to the hardware.
    //delay(DelayVal); // Pause before next pass through loop
  }
  //XXXXXXX
  //LED STRIP CODE END
  //XXXXXXX
  

  //Count the number of marble
  if(digitalRead(IR_receiver3_pin) == HIGH){
    count_Marble++;
    //lcd.print(count_Marble);
  }


  /* similar formate we want
  if (millis() - startTime >= 45000){
    digitalWrite(gateOpen, LOW);
  }
  if (millis() - startTime >= 90000 && millis() - startTime <= 135000) {
    digitalWrite(gateClose, HIGH);
  }
  else
  {
    digitalWrite(gateClose, LOW);
  }
*/
}
