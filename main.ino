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


//IR setup
int IR_receiver1_pin = 13;
int IR_receiver2_pin = 12;
int IR_receiver3_pin = 11; //exit sensor

//LED Pin setup



// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_Strip_COUNT, LED_Strip_PIN, NEO_GRB + NEO_KHZ800);

Servo Servo1;
Servo Servo2;


void setup()
{
  	pinMode(2, OUTPUT); //LED1
  	pinMode(4, OUTPUT); //LED2
  	//Initialise LED Strip
	strip.begin();
  
	//servos setup
	Servo1.attach()
	
  	//IR setup
    pinMode (IR_receiver1_pin, INPUT); // sensor1 pin INPUT
    pinMode (IR_receiver2_pin, INPUT); // sensor2 pin INPUT
    pinMode (IR_receiver3_pin, INPUT); // sensor3  pin INPUT

}

void loop()
{
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
  if (statusSensor1 == 1){
  	DigitalWrite(LED1, HIGH);
    Servo1.write(90);
    if(//1.2 seconds has passed do shit)
  }
  
  //XXXXXXX
  //Taking Sensor Data and doing shit END
  //XXXXXXX
     
}
