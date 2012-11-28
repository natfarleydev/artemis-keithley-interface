#include "GPIB.h"
#include <iostream>
#include <ctime>
#include <time.h>
#include <iomanip>
#include <string>
#include <iostream>
#include <fstream>
#include "windows.h"
#include "keithley_functions.h"

using namespace std;

KeithleyDevice::KeithleyDevice() {
	Device = 0;
	BoardIndex = 0;
}

void KeithleyDevice::pulsesweepvoltage(double bottom, double top, int no_of_steps) {
	// Function to sweep voltage with pulses
	cout << "Activated pulse voltage" << endl;
	cout << "This function sweeps with a pulsing voltage" << endl;
	cout << "Lowest voltage " << bottom << " V" << endl;
	cout << "Highest voltage " << top << " V" << endl;
	cout << "Number of steps " << no_of_steps << endl;

	for(int i=0; i<=no_of_steps; i++) {
		// Set up the voltage
		double tempvolt = bottom + (double)i * ( (top - bottom)/((double)no_of_steps) );

		char tempbuff[100];
		cout << "votage to set = " << tempvolt << endl;
		strcpy(stringinput,":SOUR:VOLT:LEV:AMPL ");
		strcat(stringinput,itoa(tempvolt,tempbuff,10));
		printf("command: %s\n",stringinput);
		ibwrt(this->Device,stringinput, strlen(stringinput));     /* Send the identification query command   */
		Sleep(1);
		// TODO Send the output to a file HERE
		strcpy(stringinput,":SOUR:VOLT:LEV:AMPL 0");
		ibwrt(Device, stringinput, strlen(stringinput));
		Sleep(10);

		cout << "Pulsed " << tempvolt << " V." << endl;
	}

	cout << "End of function";

	// Should be pretty useful to exit the function with an error code at some point.
	//return 0;
}

void KeithleyDevice::rampvoltagedown(int start, int end) {
	printf("IN RAMP DOWN\n");
	printf("Start Voltage %i\n",start);
	printf("End Voltage %i\n",end);

	for(int i=start; i>end-1; i=i-1)
	{
		char tempbuff[100];
		cout << "votage to set = " << i << endl;
		strcpy(stringinput,":SOUR:VOLT:LEV:AMPL "); // fill the first bit of the string with input
		strcat(stringinput,itoa(i,tempbuff,10)); // add a bit to the end http://www.cplusplus.com/reference/cstdlib/itoa/
		printf("command: %s\n",stringinput); // print the command sent
		ibwrt(Device,stringinput, strlen(stringinput));     /* Send the identification query command   */
		Sleep(100);
	}
}

void KeithleyDevice::rampvoltageup(int start, int end)
{
	printf("IN RAMP UP\n");
	printf("Start Voltage %i\n",start);
	printf("End Voltage %i\n",end);

	for(int i=start; i<end+1; i=i+1)
	{
		char tempbuff[100];
		cout << "votage to set = " << i << endl;
		strcpy(stringinput,":SOUR:VOLT:LEV:AMPL ");
		strcat(stringinput,itoa(i,tempbuff,10));
		printf("command: %s\n",stringinput);
		ibwrt(Device,stringinput, strlen(stringinput));     /* Send the identification query command   */
		Sleep(100);
	}

}