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
#define gate_Opened 45 
#define gate_Closed 90

int timee = 0;
bool check_check = true; 

//IR setup
int sensor1_pin = 13;
int sensor2_pin = 12;
int sensor3_pin = 11; //exit sensor
int sensor1_state = 0;
int sensor2_state = 0;
int sensor3_state = 0;

//LED Pin setup
#define LED1 2 //red
#define LED2 4 //red
#define LED3 6  //green
#define LED4 8  //green

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_Strip_COUNT, LED_Strip_PIN, NEO_GRB + NEO_KHZ800);

Servo Servo1;
Servo Servo2;

int max_count_Marble = 32767; //overflow of the UNO
int end_time1;
int end_time2;
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
    //start position of gates is open as agreed with motions teams
    Servo1.attach(Servo1_pin);
    Servo2.attach(Servo2_pin);
    Servo1.write(gate_Opened);
    Servo2.write(gate_Opened);
  
    //IR setup
    pinMode(sensor1_pin, INPUT_PULLUP); // sensor1 pin INPUT
    pinMode(sensor2_pin, INPUT_PULLUP); // sensor2 pin INPUT
    pinMode(sensor3_pin, INPUT_PULLUP); // sensor3  pin INPUT

    //lcd setup
    lcd.init();
    lcd.backlight();
    lcd.print("We are Box 5");
    Serial.begin(9600);
}

void loop()
{
  //check to see if marble has passed last sensor
  if (check_check == false) {
    timee += 1;
    if (timee >= 50) {
      check_check = true;
      timee = 0;
    }
  }

  sensor1_state = digitalRead(sensor1_pin);
  sensor2_state = digitalRead(sensor2_pin);
  sensor3_state = digitalRead(sensor3_pin);
  // Gate 1
  if (millis() > end_time1){
    digitalWrite(LED1, LOW);
    digitalWrite(LED3, HIGH);
    Servo1.write(gate_Opened);
  }
  if (sensor1_state == LOW){  //beam has been broken
    //green light off, red light on when beam is broken
    digitalWrite(LED1, HIGH);
    digitalWrite(LED3, LOW);
    Servo1.write(gate_Closed);
    end_time1 = millis() + 1200;
    //green light on, red light off after ball has passed
    digitalWrite(LED1, LOW);
    digitalWrite(LED3, HIGH);
  } else {
    //if beam not broken then red off, green on
    digitalWrite(LED1, LOW);
    digitalWrite(LED3, HIGH);
    Servo1.write(gate_Opened);
  }
  if (millis() > end_time2){
    digitalWrite(LED2, LOW);
    digitalWrite(LED4, HIGH);
    Servo2.write(gate_Opened);
  }
  //Gate 2
  if (sensor2_state == LOW){
    digitalWrite(LED2, HIGH);
    digitalWrite(LED4, LOW);
    Servo2.write(gate_Closed);
    end_time2 = millis() + 1200;
    //green light on, red light off after ball has passed
    digitalWrite(LED2, LOW);
    digitalWrite(LED4, HIGH);
  } else {
    //if beam not broken then red off, green on
    digitalWrite(LED1, LOW);
    digitalWrite(LED3, HIGH);
    Servo2.write(gate_Opened);
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
  }
  //XXXXXXX
  //LED STRIP CODE END
  //XXXXXXX

  //Count the number of marble
  if(sensor3_state == LOW && check_check == true){
    count_Marble++;
    check_check = false;

    lcd.clear();
    lcd.print(count_Marble + " Marbles have passed!");
    if(count_Marble >= max_count_Marble){
      count_Marble = 0;
    }
  }
}
