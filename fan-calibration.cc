#include <fstream>
#include <iostream>
#include <unistd.h>
#include <wiringPi.h>

using namespace std;

int main (void){
    int amount;
    const int FAN_PIN = 1;

    cout << "Calibration!" << endl;

	wiringPiSetup();
    pinMode (FAN_PIN, PWM_OUTPUT);

	while (1 == 1) {
		ifstream tempFile ("/sys/class/thermal/thermal_zone0/temp");

		cin >> amount;

        pwmWrite (FAN_PIN, amount);
	}

    return 0;
}
