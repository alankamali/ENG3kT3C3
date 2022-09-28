#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_NeoPixel.h>

// LED Strip values
#define LED_Strip_COUNT 12 
#define LED_Strip_PIN A5
#define DelayVal 50 // Time (in milliseconds) to pause between pixels

//Servos setup
#define Servo1_pin
#define Servo2_pin
//The angles of when the gate will be opened or closed
#define gate_Opened 90 
#define gate_Closed 180



//IR setup
int IR_receiver1_pin = 13;
int IR_receiver2_pin = 12;
int IR_receiver3_pin = 11; //exit sensor

//LED Pin setup



// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_Strip_COUNT, LED_Strip_PIN, NEO_GRB + NEO_KHZ800);

Servo Servo1;
Servo Servo2;

 
unsigned long start_Time;
int count_Marble = 0;


//Assign pin numbers ****NEEDS TO BE CHANGED
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
//the size of the display (Width and the height) 
int cols = 16, row = 6;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void setup()
{
  	pinMode(2, OUTPUT); //LED1
  	pinMode(4, OUTPUT); //LED2
  	//Initialise LED Strip
	  
    strip.begin();
  
	//servos setup
	  Servo1.attach(Servo1_pin)
    Servo2.attach(Servo2_pin)
	
  	//IR setup
    pinMode (IR_receiver1_pin, INPUT); // sensor1 pin INPUT
    pinMode (IR_receiver2_pin, INPUT); // sensor2 pin INPUT
    pinMode (IR_receiver3_pin, INPUT); // sensor3  pin INPUT

    //lcd setup
    lcd.begin(cols, rows);
    //use lcd.print(message) to print. 
    lcd.print(0);
}

void loop()
{

  start_Time = millis();

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
  
  //XXXXXXX
  //Taking Sensor Data and doing shit START
  //XXXXXXX
  int statusSensor1 = digitalRead (IR_receiver1_pin);
  int statusSensor2 = digitalRead (IR_receiver2_pin);
  int statusSensor3 = digitalRead (IR_receiver3_pin);

  //for example, if sensor 1 detects a ball, turn led on and raise servo 1 for 
  //1.2seconds closed and .8 seconds open


//one of the gates
  if (statusSensor1 == 1){
  	DigitalWrite(LED1, HIGH);
    Servo1.write(gate_Opened);
    if(millis() - start_Time >= 1200){
      Servo1.write(gate_Closed);
      //open or close gate
    }
  }

//one of the gates 
  if (statusSensor2 == 1){
  	DigitalWrite(LED2, HIGH);
    Servo2.write(gate_Opened);
    if(millis() - start_Time >= 1200){ //decide what time it will close and change it
      Servo2.write(gate_Closed);
      //open or close gate
    }
  }

//Count the number of marble
  if(statusSensor3 = 1){
    count_Marble++;
    lcd.print(count_Marble);
  }


  /*
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

  //XXXXXXX
  //Taking Sensor Data and doing shit END
  //XXXXXXX
     
}
