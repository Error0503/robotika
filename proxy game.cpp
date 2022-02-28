#include <time.h>
#include <stdlib.h>

#define START 0
#define ONGOING 1
#define WON 2
#define LOST 3
#define END 4
#define RESET 5

const int RED_LED = 13;
const int GREEN_LED = 12;
const int BUTTON = 4;
const int SENSOR = 2;

long readUltrasonicDistance()
{
	pinMode(SENSOR, OUTPUT);
	digitalWrite(SENSOR, LOW);

	delayMicroseconds(2);

	digitalWrite(SENSOR, HIGH);

	delayMicroseconds(10);

	digitalWrite(SENSOR, LOW);
	pinMode(SENSOR, INPUT);
	return pulseIn(SENSOR, HIGH);
}

void setup()
{
	pinMode(RED_LED, OUTPUT);
	pinMode(GREEN_LED, OUTPUT);
	pinMode(BUTTON, INPUT);
	pinMode(SENSOR, OUTPUT);
	Serial.begin(9600);
	srand(time(NULL));
}

int state = START;
int goal, distance, buttonState;
void loop()
{
	switch (state)
	{
	case START:
		goal = rand() % 300;
		Serial.print("Goal: ");
		Serial.println(goal);
		state = ONGOING;
		break;
	case ONGOING:
		buttonState = digitalRead(BUTTON);
		if (buttonState)
		{
			distance = 0.01723 * readUltrasonicDistance();
			state = END;
		}
		break;
	case END:
		Serial.print("Measured: ");
		Serial.println(distance);
		if (abs(goal - distance) < 10)
			state = WON;
		else
			state = LOST;
		break;
	case WON:
		digitalWrite(GREEN_LED, HIGH);
		if (digitalRead(BUTTON))
			state = RESET;
		break;
	case LOST:
		digitalWrite(RED_LED, HIGH);
		if (digitalRead(BUTTON))
			state = RESET;
		break;
	case RESET:
		digitalWrite(RED_LED, LOW);
		digitalWrite(GREEN_LED, LOW);
		state = START;
	}

	delay(100);
}