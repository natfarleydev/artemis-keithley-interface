#ifndef KEITHLEY_FUNCTIONS
#define KEITHLEY_FUNCTIONS

using namespace std;

class KeithleyDevice {
public:
	void pulsesweepvoltage(double,double,int);
	void current_pulse_sweep(double,double,int,char *);
	void rampvoltagedown(int,int);
	void rampvoltageup(int,int);
	void forward_voltage_measurement(double,char *);
	int write(const char *);
	int read(void *,int);
	int close_connection();
	int clear();
	void cls();
	void rst();
	KeithleyDevice();
private:
 
	int Device;                   /* Device unit descriptor                  */
	int BoardIndex;               /* Interface Index (GPIB0=0,GPIB1=1,etc.)  */
	char stringinput[512]; 
};
#endif
