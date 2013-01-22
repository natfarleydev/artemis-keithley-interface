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
	 eofname << timeinfo->tm_hour << timeinfo->tm_min << timeinfo->tm_sec << ".csv";
	 eofnamestring = eofname.str();
	 strcat(filename, eofnamestring.c_str());

	 ofstream outfile;

	 outfile.open(filename, ios::app);

	 if(outfile.is_open()) {
		cout << "Outputting to file " << filename << endl;
	 }
	 else {
		 cout << "Error opening " << filename << ". Will pulse anyway..." << endl;
	 }

	// Function to sweep current pulses
	cout << "Activated pulse voltage" << endl;
	cout << "This function sweeps with a pulsing voltage" << endl;
	cout << "Lowest voltage" << bottom << " V" << endl;
	cout << "Highest voltage" << top << " V" << endl;
	cout << "Number of steps " << no_of_steps << endl;
	char Buffer[1000];
	for(int i=0; i<=no_of_steps; i++) {
		ostringstream tempcurrstream;
		string tempcurrstring;

		double tempcurr = bottom + (double)i * ( (top - bottom)/(double)no_of_steps );
		// TODO set up this for loop for our IV curve.
		// Set up the voltage
		//double tempvolt = bottom + (double)i * ( (top - bottom)/((double)no_of_steps) );

		//char tempbuff[100];
		//cout << "voltage to set = " << tempvolt << endl;
		//strcpy(stringinput,":SOUR:VOLT:LEV:AMPL ");
		//strcat(stringinput,itoa(tempvolt,tempbuff,10));
		//printf("command: %s\n",stringinput);
		////ibwrt(this->Device,stringinput, strlen(stringinput));     /* Send the identification query command   */
		//this->write(stringinput);
		this->cls();
		this->rst();
		this->write(":SYST:BEEP:STAT OFF");
		this->write(":SENS:FUNC:CONC OFF");
		this->write(":SOUR:FUNC CURR");
		this->write(":SENS:FUNC 'VOLT:DC'");
		this->write(":SENS:VOLT:RANGE:AUTO ON");
		this->write(":SENS:VOLT:PROT 200"); //voltage protection level
		this->write(":SOUR:CURR:MODE LIST");
		this->write(":SENS:VOLT:DC:RANG 100");
		tempcurrstream << ":SOUR:LIST:CURR " << tempcurr << "," << tempcurr << "," << tempcurr << ",0.0";
		tempcurrstring = tempcurrstream.str();
		strcpy(stringinput,tempcurrstring.c_str());
		this->write(stringinput);
		//this->write(":SOUR:LIST:CURR 0.001,0.001,0.001,0.0");
		this->write(":TRIG:COUN 4");
		this->write(":SOUR:DEL 0.01");
		this->write(":ROUT:TERM FRONT");
		this->write(":OUTP ON");
		this->write(":READ?");
		
		this->read(Buffer,1000);
		Buffer[ibcnt] = '\0'; //end the buffer so we don't pick up faff from Keithley.


		//+	outputfile1 << gtim << "\t" << Buffer;
		outfile << Buffer;
		Sleep(10);
		this->write(":OUTP OFF");
		cout << "Made it do that thing. Yeah. " << endl;

	}

	outfile.close();
	if(outfile.is_open()) {
		cout << filename << " closed." << endl;
	}
	else {
		cout << filename << " is still open! Whoops!" << endl;
	}
}


string KeithleyDevice::forward_voltage_measurement(double i_value) {
	// This function is designed to take the forward voltage at a value i_value A.
	 //time_t rawtime;
	 //struct tm * timeinfo;

	 //time(&rawtime);
	 //timeinfo = localtime(&rawtime);

	 //// This adds the file directory to the filename
	 //char filename[2048];
	 //strcpy(filename, filedir);

	 //// TODO change to something more sensible
	 //string eofnamestring;
	 //ostringstream eofname;
	 //eofname << timeinfo->tm_hour << timeinfo->tm_min << timeinfo->tm_sec << ".csv";
	 //eofnamestring = eofname.str();
	 //strcat(filename, eofnamestring.c_str());

	 //ofstream outfile;

	 //// add to the end of the file.
	 //outfile.open(filename, ios::app);

	 //if(outfile.is_open()) {
		//cout << "Outputting to file " << filename << endl;
	 //}
	 //else {
		// cout << "Error opening " << filename << ". Will pulse anyway..." << endl;
	 //}

	// Function to sweep current pulses
	cout << "Activated pulse voltage" << endl;
	cout << "This function get the forward voltage" << endl;
	cout << "Target current " << i_value << " A" << endl;

	char Buffer[1000];
	//for(int i=0; i<=no_of_steps; i++) {
		ostringstream tempcurrstream;
		string tempcurrstring;

		//double tempcurr = bottom + (double)i * ( (top - bottom)/(double)no_of_steps );
		// TODO set up this for loop for our IV curve.
		// Set up the voltage
		//double tempvolt = bottom + (double)i * ( (top - bottom)/((double)no_of_steps) );

		//char tempbuff[100];
		//cout << "voltage to set = " << tempvolt << endl;
		//strcpy(stringinput,":SOUR:VOLT:LEV:AMPL ");
		//strcat(stringinput,itoa(tempvolt,tempbuff,10));
		//printf("command: %s\n",stringinput);
		////ibwrt(this->Device,stringinput, strlen(stringinput));     /* Send the identification query command   */
		//this->write(stringinput);
		this->cls();
		this->rst();
		this->write(":SYST:BEEP:STAT OFF");
		this->write(":SENS:FUNC:CONC OFF");
		this->write(":SOUR:FUNC CURR");
		this->write(":SENS:FUNC 'VOLT:DC'");
		this->write(":SENS:VOLT:RANGE:AUTO ON");
		this->write(":SENS:VOLT:PROT 200"); //voltage protection level
		this->write(":SOUR:CURR:MODE LIST"); // Set the source mode to list
		this->write(":SENS:VOLT:DC:RANG 100");
		tempcurrstream << ":SOUR:LIST:CURR " << i_value << "," << i_value << "," << i_value << ",0.0"; // List the measurements to take.
		tempcurrstring = tempcurrstream.str();
		strcpy(stringinput,tempcurrstring.c_str());
		this->write(stringinput);
		//this->write(":SOUR:LIST:CURR 0.001,0.001,0.001,0.0"); // That's what the previous 4 lines do if i_value == 0.001
		this->write(":TRIG:COUN 4");
		this->write(":SOUR:DEL 0.01");
		this->write(":ROUT:TERM FRONT");
		this->write(":OUTP ON");
		this->write(":READ?");
		
		this->read(Buffer,1000);
		Buffer[ibcnt] = '\0'; //end the buffer so we don't pick up faff from Keithley.


		//+	outputfile1 << gtim << "\t" << Buffer;
		string temp;
		temp = Buffer;
		Sleep(10);
		this->write(":OUTP OFF");
		cout << "Hopefully measured forward voltage at " << i_value << " A" << endl;
		return temp;
	//}

	//outfile.close();
	//if(outfile.is_open()) {
	//	cout << filename << " closed." << endl;
	//}
	//else {
	//	cout << filename << " is still open! Whoops!" << endl;
	//}
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
	cout << "string " << c << " hopefully written to device!" << endl;
	//Sleep(10);
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

void KeithleyDevice::cls() {
	ibwrt(Device, "*CLS", 5);
}

void KeithleyDevice::rst() {
	ibwrt(Device, "*RST",5);
}