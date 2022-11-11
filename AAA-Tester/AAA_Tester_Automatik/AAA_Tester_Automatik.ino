// AATiS (Arbeitskreis Amateurfunk und Telekommunikation in der Schule e.V.) 
// https://www.aatis.de/content/
// Sketch developped by Enno Klatt
// Version 21.10.2022
// ------------------------------- User parameter ---------------------------------
// Parameters which may be changed by user within "config.ini" on SD-card
// will always be read at automatic-startup
// defaults in manual operation (Terminal)
double compareVoltage    = 1.0;     // voltage to decide good or bad battery
int referenceStressTime  = 5;       // duration of stress
double AREF_Voltage      = 1.1;     // reference voltage AREF
int stepsLoadTest        = 430;     // steps from loadposition to testposition
int stepsTestTrap        = 300;     // steps from testposition to trap
// or type 'r' in terminal to read config.ini
// type 'i' in terminal to show parameter
// Attention: config.ini with parameters must be present on SD-card
// Attention: Create empty Excel.csv on SD-card
// The sketch will not run withount SD-card
// ------------------------------- User parameter ---------------------------------

// Libraries for SD-card
#include <SPI.h>                  // Serial Peripheral Interface (SPI)
#include <SD.h>                   // Arduino SD-card library
                                  // Uses Arduino Pin: MOSI (11), MISO (12), CLK/SCK (13)
                                  // Adafruit SD shields and modules: SS (10)
File myFile;                      // derive myFile-object for file-operations

// Libraries Servo & Stepper
#include <Servo.h>                // Arduino servo motors library
#include <Stepper.h>              // Arduino stepper motors library

// Libraries LCD I2C
#include <Wire.h>                 // Arduino library needed for LiquidCrystal I2C
#include <LiquidCrystal_I2C.h>    // https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library
                                  // need to be copied in the "libraries" folder                        
// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include "RTClib.h"               // https://github.com/adafruit/RTClib/                           
RTC_DS1307 rtc;                   // derive rtc-object for RTC-functions
                                  // need to be copied in the "libraries" folder 
Servo myServo;                    // derive myServo-object for servo-functions
#define servoPin (7)              // Arduino-Pin of attached servo (trap)
int trapClosed = 5;               // position of trap good AA-battery
int trapOpen   = 90;              // position of trap bad AA-battery
int startAngle = 0;               // last position of servo
int stopAngle  = 0;               // new position of servo
boolean servoAttached = false;    // servo will be attached for each move
                                  // and deattached after the move
#define stressPin      (8)        // pin of stress-circuit
#define voltagePin     (A0)       // analog pin for voltage detection
boolean activeStress = false;     // toggle between an and off

#define operationPin  (A1)        // button left, start operation
#define stepPin       (A2)        // button right, move stepper
#define stopAutoPin   (A3)        // stop automatic operation/no battery
boolean operationOn = false;      // in operation or not
boolean standAlone  = false;      // standAlone means automatic operation
                                  // otherwise Terminal operation
                                  
// change this to the number of steps on your stepper
#define stepsPerRevolution 2048   // 28BYJ-48 Stepper Motor 
                                  // full-step mode (32 steps)
                                  // gear-ratio of 64:1
                                  // steps per revolution: 32 x 64 = 2048
#define motor_pin_1 (2)           // stepper-motor pin, Arduino-Pin 2
#define motor_pin_2 (4)           // stepper-motor pin, Arduino-Pin 4
#define motor_pin_3 (3)           // stepper-motor pin, Arduino-Pin 3
#define motor_pin_4 (5)           // stepper-motor pin, Arduino-Pin 5

                                  // derive stepper-object for stepper-functions
Stepper stepper(stepsPerRevolution, motor_pin_1, motor_pin_2, motor_pin_3, motor_pin_4);    
#define stepperSpeed 5 

LiquidCrystal_I2C lcd(0x27, 16, 2);     // derive lcd-object for lcd-functions
                                        // LCD-address is 0x27 for 16 x 2 LCD

// ---------------------- User input over Terminal ---------------------------------
// syntax for serial input 'letter:value' e.g. s:512
// syntax for serial input 'string:value' e.g. stepper:512
char          controlLetter = 'n';                    // holds the letter e.g. 'n'
String        stringCommand = "not";                  // holds the string "not" 
unsigned int  controlValue  = 0;                      // holds the serial input value

// Serial input, preparation for event-routine
#define MAX_BUF (32)
char buffer[MAX_BUF];               // where we store the message until we get a '\n'
int i_buf=0;                        // current index of buffer
boolean serialComplete = false;     // whether the serial input is complete
// ---------------------- User input over Terminal ---------------------------------
