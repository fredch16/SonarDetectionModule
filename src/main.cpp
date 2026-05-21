#include <Arduino.h>
#include <ESP32Servo.h>

// Pins
const int trigPin = 5;
const int echoPin = 18;
const int servoPin = 23;

Servo servo;

int angle = 0;
int direction = 1;

long getDistance()
{
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);

	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);
	// Reduced timeout for faster sweep
	long duration = pulseIn(echoPin, HIGH, 3000);
	// No echo received
	if (duration == 0)
		return 9999;
	long distance = duration * 0.034 / 2;
	// // Clamp max range to 30 cm
	// if (distance > 30)
	// 	distance = 300;
	return distance;
}

void setup()
{
	Serial.begin(115200);

	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);

	servo.attach(servoPin);

	servo.write(angle);

	delay(500);
}

void loop()
{
	servo.write(angle);

	// Small settle delay
	delay(5);

	long distance = getDistance();

	Serial.print(angle);
	Serial.print(",");
	Serial.println(distance);

	// Smoother sweep
	angle += direction;

	// Full sweep
	if (angle >= 180 || angle <= 0)
		direction *= -1;

	// Faster sweep speed
	delay(8);
}