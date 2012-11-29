#include "GPIB.h"
#include <iostream>
#include <ctime>
#include <time.h>
#include <iomanip>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "windows.h"
#include "keithley_functions.h"

using namespace std;

KeithleyDevice::KeithleyDevice() {
	int PrimaryAddress = 24;
	int SecondaryAddress = 0;
	// OK, I don't really understand this ibdev command, so I copied it straight
	// from the previous version. This could be the source of the error I had
	// when I tried to use this class with the device previously.
	Device = ibdev(                /* Create a unit descriptor handle         */
         0,              /* Board Index (GPIB0 = 0, GPIB1 = 1, ...) */
         PrimaryAddress,          /* Device primary address                  */
         SecondaryAddress,        /* Device secondary address                */
         T10s,                    /* Timeout setting (T10s = 10 seconds)     */
         1,                       /* Assert EOI line at end of write         */
         0);                      /* EOS termination mode                    */
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

void KeithleyDevice::current_pulse_sweep(double bottom, double top, int no_of_steps, char * filedir) {
	 time_t rawtime;
	 struct tm * timeinfo;

	 time(&rawtime);
	 timeinfo = localtime(&rawtime);

	 // This adds the [current time].txt to the end of the filename
	 char filename[2048];
	 strcpy(filename, filedir);

	 string eofnamestring;
	 ostringstream eofname;
	 eofname << timeinfo->tm_hour << timeinfo->tm_min << timeinfo->tm_sec << ".txt";
	 eofnamestring = eofname.str();
	 strcat(filename, eofnamestring.c_str());
	 cout << "Outputting to file " << filename << endl;
	
	// Function to sweep current pulses
	cout << "Activated pulse voltage" << endl;
	cout << "This function sweeps with a pulsing voltage" << endl;
	cout << "Lowest current " << bottom << " A" << endl;
	cout << "Highest current " << top << " A" << endl;
	cout << "Number of steps " << no_of_steps << endl;

	//for(
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

int KeithleyDevice::write(const char * c) {
	strcpy(stringinput,c);
	ibwrt(Device,stringinput,strlen(stringinput));
	cout << "string " << c << " hopefully written to device!";

	return 0;
	//strcpy(stringinput
}

int KeithleyDevice::read(void * c, int i) {
	// This function reads i no of bytes from the device.
	// void in this case can easily be a char[]
	// (at least this is how it was used in the previous version of this program.)
	ibrd(Device,c,i);

	return 0; // One day this will look for errors.
}

int KeithleyDevice::close_connection() {
	// from NI:
	// Note: The ibonl command is used to close down the unit descriptors after
	// you are done using them. You should call ibonl at the end of your 
	// application, once for each call you made to ibdev or ibfind. It is used 
	// this way:
	//
	// ud0: ibonl 0

	ibonl(Device, 0);

	return 0; // would be good to return errors from here sometime.
}

int KeithleyDevice::clear() {
	ibclr(Device);

	return 0; // TODO error checking
}