#include <Arduino.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
# define LCD_ACTIVE 0

// Button Inputs:
// Middle 500 500
// X axis 0-1024 left to right
// Y axis 0-1024 top to bottom
// Button on 1 as standard and 0 when pressed

enum ControlMode {
	MANUAL,
	SWEEP
};

// Pins
const int trigPin = 6;
const int echoPin = 11;
const int redLEDPin = 9;
const int greenLEDPin = 8;
const int xAxisPin = A2;
const int yAxisPin = A3;
const int joyStickPin = 13;
const int buttonPin = 7;

// Variables
long duration;
long cm;
bool lastButtonState = HIGH;
int angle = 90;
ControlMode mode = MANUAL;
// LiquidCrystal_I2C lcd(0x27, 16, 2); // Lcd address is 0x27
Servo servo;
// Sweep state variables
int sweepAngle = 10;
int sweepDirection = 1;
unsigned long lastSweepTime = 0;
const unsigned long sweepInterval = 15;


// Functions
void dangerLight(long distance);
void sonarPulse(int angle);
void changeMode(ControlMode *mode);
void handleManual();
void handleSweep();

void setup() 
{
	// Display
	// lcd.init();
	// lcd.clear();
	// lcd.backlight();

	// Servo
	servo.attach(10);
	servo.write(90);

	// Pins
	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);
	pinMode(redLEDPin, OUTPUT);
	pinMode(greenLEDPin, OUTPUT);
	pinMode(joyStickPin, INPUT_PULLUP);
	pinMode(buttonPin, INPUT_PULLUP);
	// Serial Monitor
	Serial.begin(9600);
}

void loop() 
{
	bool	buttonState = digitalRead(buttonPin);
	
	if (buttonState == LOW && lastButtonState == HIGH)
		changeMode(&mode);
	lastButtonState = buttonState;
	if (mode == SWEEP)
		handleSweep();
	if (mode == MANUAL)
		handleManual();
}

// Functions:

void dangerLight(long distance)
{
	if( distance < 30)
	{
		digitalWrite(redLEDPin, HIGH);
		digitalWrite(greenLEDPin, LOW);
		// if (LCD_ACTIVE)
		// {
		// 	lcd.setCursor(2,1);
		// 	lcd.print("DANGER HERE!    ");
		// }
	}
	else
	{
		digitalWrite(redLEDPin, LOW);
		digitalWrite(greenLEDPin, HIGH);
		// if (LCD_ACTIVE)
		// {
		// 	lcd.setCursor(2, 1);
		// 	lcd.print("You are safe    ");
		// }
	}
}

void sonarPulse(int angle)
{
	digitalWrite(trigPin, LOW);
	delayMicroseconds(5);
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);
	duration = pulseIn(echoPin, HIGH, 25000);
	if (duration == 0)
		return ;
	cm = duration * 0.034 / 2;
	// if (LCD_ACTIVE)
	// {
	// 	lcd.setCursor(0,0);
	// 	lcd.print("Distance: ");
	// 	lcd.print(cm);
	// 	lcd.print("cm   ");
	// }
	dangerLight(cm);
}

void	changeMode(ControlMode *mode)
{
	if (*mode == SWEEP)
		*mode = MANUAL;
	else
		*mode = SWEEP;
}

void handleSweep()
{
	if (millis() - lastSweepTime < sweepInterval)
		return ;
	lastSweepTime = millis();
	servo.write(sweepAngle);
	sonarPulse(sweepAngle);
	sweepAngle += sweepDirection;
	if (sweepAngle <= 10 || sweepAngle >= 170)
		sweepDirection = -sweepDirection;
}

void handleManual()
{
	int	xPosition = analogRead(xAxisPin);
	int	joyStickState = digitalRead(joyStickPin);

	if (joyStickState == 0)
		angle = 90;
	if (xPosition < 450 && angle < 170)
		angle += 3;
	else if (xPosition > 550 && angle > 10)
		angle -= 3;
	servo.write(angle);
	sonarPulse(angle);
}