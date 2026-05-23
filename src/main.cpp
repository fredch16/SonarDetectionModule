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

	// Reduced timeout for faster sweep. To detect objects further away increase that value.
	long duration = pulseIn(echoPin, HIGH, 3000);

	// No echo received
	if (duration == 0)
		return 10000; //large value that doesn't show on processing
	long distance = duration * 0.034 / 2;
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

	delay(2);
	long distance = getDistance();
	Serial.print(angle);
	Serial.print(",");
	Serial.println(distance);
	angle += direction;
	// Full sweep
	if (angle >= 180 || angle <= 0)
		direction *= -1;
	delay(8);
}