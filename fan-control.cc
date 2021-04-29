#include <fstream>
#include <iostream>
#include <unistd.h>
#include <wiringPi.h>

using namespace std;

int main (void){
    const float TEMP_MIN = 30.0;
    const float TEMP_MAX = 60.0;
	const int FAN_PIN = 1;

	wiringPiSetup();
    pinMode (FAN_PIN, PWM_OUTPUT);

	const unsigned int sleepInterval = 10;  // Seconds
	float temp;
    float percent;

    // Initial Run
    cout << "Startup!" << endl;
    pwmWrite (FAN_PIN, 1024);
    usleep(1000000);

	while (temp != -1) {
		ifstream tempFile ("/sys/class/thermal/thermal_zone0/temp");

		if (tempFile.fail()){
			return -1;
		}

		tempFile >> temp;
        temp = temp / 1000.0;
		cout << int(temp) << "°C";

		if (temp > TEMP_MAX) {
            percent = 100.0;
        } else if  (temp > TEMP_MIN) {
            percent = (temp - TEMP_MIN)/TEMP_MIN;
        } else {
            percent = 0.0;
        }

        pwmWrite (FAN_PIN, 824.0 + 200.0*(percent));
        cout << " - " << int(percent * 100) << "%" << endl;

		usleep(sleepInterval * 1000000);
	}

    return 0;
}
