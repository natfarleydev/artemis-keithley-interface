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

void KeithleyDevice::voltage_pulse_sweep(double bottom, double top, int no_of_steps, char * filedir) {
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

	 ofstream outfile;

	 outfile.open(filename);

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
	//for(int i=0; i<=no_of_steps; i++) {
		// Set up the voltage
		//double tempvolt = bottom + (double)i * ( (top - bottom)/((double)no_of_steps) );

		//char tempbuff[100];
		//cout << "voltage to set = " << tempvolt << endl;
		//strcpy(stringinput,":SOUR:VOLT:LEV:AMPL ");
		//strcat(stringinput,itoa(tempvolt,tempbuff,10));
		//printf("command: %s\n",stringinput);
		////ibwrt(this->Device,stringinput, strlen(stringinput));     /* Send the identification query command   */
		//this->write(stringinput);
		//+   ibwrt(Device, "*RST", 5);     /* Send the identification query command   */
//+   ibwrt(Device, ":SYST:BEEP:STAT OFF", 19);
//+   ibwrt(Device, ":SENS:FUNC:CONC OFF", 19);    
//+   ibwrt(Device, ":SOUR:FUNC CURR", 15);     
//+   ibwrt(Device, ":SENS:FUNC 'VOLT:DC'", 20);
		this->cls();
		this->rst();
		this->write(":SYST:BEEP:STAT OFF");
		this->write(":SENS:FUNC:CONC OFF");
		this->write(":SOUR:FUNC CURR");
		this->write(":SENS:FUNC 'VOLT:DC'");
		this->write(":SENS:VOLT:RANGE AUTO");
		//+   ibwrt(Device, ":SENS:VOLT:PROT 100", 19);     
//+   ibwrt(Device, ":SOUR:CURR:MODE LIST", 20);     
//+   ibwrt(Device, ":SOUR:LIST:CURR 0.001,0.001,0.001,0.0", 37);    
//+   ibwrt(Device, ":TRIG:COUN 4", 12); 
//+   ibwrt(Device, ":SOUR:DEL 0.01", 13);  
//+   ibwrt(Device, ":ROUT:TERM FRONT", 15); 
//+   ibwrt(Device, ":OUTP ON", 8);   
//+   ibwrt(Device, ":READ?", 6);     
//+
//+   ibrd(Device, Buffer, 1000);    
		this->write(":SENSE:VOLT:PROT 100");
		this->write(":SOUR:CURR:MODE LIST");
		this->write(":SOUR:LIST:CURR 0.001,0.001,0.001,0.0");
		this->write(":TRIG:COUN 4");
		this->write(":SOUR DEL 0.01");
		this->write(":ROUT:TERM REAR");
		this->write(":OUTP ON");
		this->write(":READ?");

		this->read(Buffer,1000);

		//+	outputfile1 << gtim << "\t" << Buffer;
		outfile << Buffer;
		//Sleep(10);
		//// TODO Send the output to a file HERE
		//strcpy(stringinput,":SOUR:VOLT:LEV:AMPL 0");
		//ibwrt(Device, stringinput, strlen(stringinput));
		//Sleep(10);

		cout << "Made it do that thing. Yeah. " << endl;

//		+   ibwrt(Device, "*CLS", 5);     /* Send the identification query command   */
//+   //ibwrt(Device, ":SOUR:FUNC VOLT", 15);     /* Send the identification query command   */
//+   //ibwrt(Device, ":SOUR:VOLT:MODE FIXED", 21);     /* Send the identification query command   */
//+   //ibwrt(Device, ":SOUR:VOLT:LEV 0", 16);     /* Send the identification query command   */
//+   //ibwrt(Device, ":SENS:CURR:PROT 150E-6", 22);     /* Send the identification query command   */
//+   //ibwrt(Device, ":SENS:FUNC 'CURR'", 17);     /* Send the identification query command   */
//+   //ibwrt(Device, ":FORM:ELEM CURR", 15);     /* Send the identification query command   */
//+   //ibwrt(Device, "*RST", 5);     /* Send the identification query command   */
//+   //ibwrt(Device, ":TRIG:COUN 1", 12);     /* Send the identification query command   */
//+
//+   ibwrt(Device, "*RST", 5);     /* Send the identification query command   */
//+   ibwrt(Device, ":SYST:BEEP:STAT OFF", 19);
//+   ibwrt(Device, ":SENS:FUNC:CONC OFF", 19);    
//+   ibwrt(Device, ":SOUR:FUNC CURR", 15);     
//+   ibwrt(Device, ":SENS:FUNC 'VOLT:DC'", 20);
//+   //ibwrt(Device, ":SENS:VOLT:RANG 200", 19);
//+   ibwrt(Device, ":SENS:VOLT:RANG:AUTO", 20);
//+   ibwrt(Device, ":SENS:VOLT:PROT 100", 19);     
//+   ibwrt(Device, ":SOUR:CURR:MODE LIST", 20);     
//+   ibwrt(Device, ":SOUR:LIST:CURR 0.001,0.001,0.001,0.0", 37);    
//+   ibwrt(Device, ":TRIG:COUN 4", 12); 
//+   ibwrt(Device, ":SOUR:DEL 0.01", 13);  
//+   ibwrt(Device, ":ROUT:TERM FRONT", 15); 
//+   ibwrt(Device, ":OUTP ON", 8);   
//+   ibwrt(Device, ":READ?", 6);     
//+
//+   ibrd(Device, Buffer, 1000);     /* Read up to 100 bytes from the device    */
//+ 	if (Ibsta() & ERR) {
//+		GpibError("ibrd Error");	
//+		}
//+		Buffer[Ibcnt()] = '\0';        /* Null terminate the ASCII string         */
//+		printf("HERE WHAT WE READ\n");
//+		printf("%s\n", Buffer);        /* Print the device identification         */
//+		printf("HERE WHAT WE READ (FINISHED)\n");
//+
//+
//+
//+	time_t now = time(0);
//+	char *gtim = g_strdup(ctime(&now));
//+	tm *ptm = localtime(&now);
//+//	char *timebuffer = '0';
//+	sprintf(gtim,"%02d:%02d:%02d %02d:%02d:%04d",ptm->tm_hour,ptm->tm_min,ptm->tm_sec,ptm->tm_mday,(ptm->tm_mon)+1,(ptm->tm_year)+1900);
//+	cout << "time " << gtim << endl;
//+
//+
//+	strcpy(stringinput,":OUTP OFF");
//+	ibwrt(Device,stringinput, strlen(stringinput));     /* Send the identification query command   */
//+
//+    outputfile1.open("test1.txt",ios::app);
//+	outputfile1 << gtim << "\t" << Buffer;
//+	outputfile1.close();
//+
//+// SECOND PIN
//+
//+
//+   ibwrt(Device, ":ROUT:TERM REAR", 15); 
//+   ibwrt(Device, ":OUTP ON", 8);   
//+   ibwrt(Device, ":READ?", 6);     
//+
//+   ibrd(Device, Buffer, 1000);     /* Read up to 100 bytes from the device    */
//+ 	if (Ibsta() & ERR) {
//+		GpibError("ibrd Error");	
//+		}
//+		Buffer[Ibcnt()] = '\0';        /* Null terminate the ASCII string         */
//+		printf("HERE WHAT WE READ\n");
//+		printf("%s\n", Buffer);        /* Print the device identification         */
//+		printf("HERE WHAT WE READ (FINISHED)\n");
//+
//+
//+	strcpy(stringinput,":OUTP OFF");
//+	ibwrt(Device,stringinput, strlen(stringinput));     /* Send the identification query command   */
//+
//+    outputfile2.open("test2.txt",ios::app);
//+	outputfile2 << gtim << "\t" << Buffer;
//+	outputfile2.close();
//+
//+
//+
//+  /*-- Return 0 if exit is successful --*/
//+  return 0;
//+

	//}

	outfile.close();
	if(outfile.is_open()) {
		cout << filename << " closed." << endl;
	}
	else {
		cout << filename << " is still open! Whoops!" << endl;
	}
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

void KeithleyDevice::cls() {
	ibwrt(Device, "*CLS", 5);
}

void KeithleyDevice::rst() {
	ibwrt(Device, "*RST",5);
}