/*
 * Notes to the programmer looking at this
 *
 * The program relies on 32-bit libraries, so when linking to new libraries
 * remember to link 32-bit libraries. 
 */


// initializing C++
#include "GPIB.h"
//#include <gtkmm.h> // removed to update to latest gtk
//#include <glibmm\thread.h> // removed to updated to latest gtk
#include <iostream>
#include <ctime>
#include <time.h>
#include <iomanip>
#include <string>
#include <iostream>
#include <fstream>
#include "windows.h"
#include "keithley_functions.h"

// Trying to update to latest GTK
#include <glib.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>

#define EARM  22  // The ibnotify Callback failed to rearm
#define EHDL  23  // The input handle is invalid
#define EWIP  26  // Wait already in progress on input ud
#define ERST  27  // The event notification was cancelled due to a reset of the interface
#define EPWR  28  // The system or board has lost power or gone to standby


using namespace std;

time_t startingtime;

GtkWidget *window;
GtkWidget *table;
GtkWidget *label1;
GtkWidget *entry1;
GtkWidget *label2;
GtkWidget *entry2;
GtkWidget *label3;
GtkWidget *entry3;
GtkWidget *button1;
GtkWidget *button2;
GtkWidget *button3;

// Added for testing GTK
GtkWidget *button4;

char  Buffer[101];             
//FILE *outputfile;
ofstream outputfile;

void GpibError(const char * msg); /* Error function declaration              */

//int Device = 0;                   /* Device unit descriptor                  */
//int BoardIndex = 0;               /* Interface Index (GPIB0=0,GPIB1=1,etc.)  */
//static char stringinput[512]; // TODO remove global variables in time for expansion

KeithleyDevice kdevice=KeithleyDevice();

/*-- This function gets the time --*/
char *gettime()
{
	time_t now = time(0);
	char *gtim = g_strdup(ctime(&now));
	tm *ptm = localtime(&now);
//	char *timebuffer = '0';
	cout << "TIME IN SECS " << ptm->tm_sec << endl;
	sprintf(gtim,"%02d:%02d:%2d %02d:%02d:%04d",ptm->tm_hour,ptm->tm_min,ptm->tm_sec,ptm->tm_mday,(ptm->tm_mon)+1,(ptm->tm_year)+1900);
	cout << "time " << gtim << endl;
	return gtim;
}

/*-- This function allows the program to exit properly when the window is closed --*/
gint destroyapp (GtkWidget *widget, gpointer gdata)
{
  g_print ("Quitting...\n");
  gtk_main_quit();
  return (FALSE);
}


//static void pulsesweepvoltage(double bottom, double top, int no_of_steps) {
//	// Function to sweep voltage with pulses
//	cout << "Activated pulse voltage" << endl;
//	cout << "This function sweeps with a pulsing voltage" << endl;
//	cout << "Lowest voltage " << bottom << " V" << endl;
//	cout << "Highest voltage " << top << " V" << endl;
//	cout << "Number of steps " << no_of_steps << endl;
//
//	for(int i=0; i<=no_of_steps; i++) {
//		// Set up the voltage
//		double tempvolt = bottom + (double)i * ( (top - bottom)/((double)no_of_steps) );
//
//		char tempbuff[100];
//		cout << "votage to set = " << tempvolt << endl;
//		strcpy(stringinput,":SOUR:VOLT:LEV:AMPL ");
//		strcat(stringinput,itoa(tempvolt,tempbuff,10));
//		printf("command: %s\n",stringinput);
//		ibwrt(Device,stringinput, strlen(stringinput));     /* Send the identification query command   */
//		Sleep(10);
//		// TODO Send the output to a file HERE
//		strcpy(stringinput,":SOUR:VOLT:LEV:AMPL 0");
//		ibwrt(Device, stringinput, strlen(stringinput));
//		Sleep(100);
//
//		cout << "Pulsed " << tempvolt << " V." << endl;
//	}
//
//	cout << "End of function";
//
//	// Should be pretty useful to exit the function with an error code at some point.
//	//return 0;
//
//}
//static void rampvoltagedown(int start, int end)
//{
//	printf("IN RAMP DOWN\n");
//	printf("Start Voltage %i\n",start);
//	printf("End Voltage %i\n",end);
//
//	for(int i=start; i>end-1; i=i-1)
//	{
//		char tempbuff[100];
//		cout << "votage to set = " << i << endl;
//		strcpy(stringinput,":SOUR:VOLT:LEV:AMPL "); // fill the first bit of the string with input
//		strcat(stringinput,itoa(i,tempbuff,10)); // add a bit to the end http://www.cplusplus.com/reference/cstdlib/itoa/
//		printf("command: %s\n",stringinput); // print the command sent
//		ibwrt(Device,stringinput, strlen(stringinput));     /* Send the identification query command   */
//		Sleep(100);
//	}
//
//}

//static void rampvoltageup(int start, int end)
//{
//	printf("IN RAMP UP\n");
//	printf("Start Voltage %i\n",start);
//	printf("End Voltage %i\n",end);
//
//	for(int i=start; i<end+1; i=i+1)
//	{
//		char tempbuff[100];
//		cout << "votage to set = " << i << endl;
//		strcpy(stringinput,":SOUR:VOLT:LEV:AMPL ");
//		strcat(stringinput,itoa(i,tempbuff,10));
//		printf("command: %s\n",stringinput);
//		ibwrt(Device,stringinput, strlen(stringinput));     /* Send the identification query command   */
//		Sleep(100);
//	}
//
//}

static void warning_dialog(float voltage)
{
	cout << "DIALOG voltage = " << voltage << endl;
	GtkWidget *dialog;

//	dialog = gtk_dialog_new_with buttons(

}

static void button_clicked1()
{
	g_print ("Button1 (ON) Pressed\n");

	char *timebuffer = gettime();
	printf("time = %s\n",timebuffer);

	time_t seconds;

	startingtime = time(NULL);

	seconds = time (NULL);
	cout << seconds/3600 << "\t hours since January 1, 1970 " << endl;
	cout << seconds/60   << "\t minutes since January 1, 1970 " << endl;
	cout << startingtime << "\t minutes since January 1, 1970 " << endl;
	cout << seconds      << "\t seconds since January 1, 1970 " << endl;


	//strcpy(stringinput,":SOUR:VOLT:IMM:AMPL?");
	//ibwrt(Device,stringinput, strlen(stringinput));     /* Check what the voltage is set to   */
	kdevice.write(":SOUR:VOLT:IMM:AMPL?");
	//ibrd(Device, Buffer, 100);     /* Read up to 100 bytes from the device
	//							    * and puts it in Buffer*/
	kdevice.read(Buffer,100);

	if (ibsta & ERR) {
     GpibError("ibrd Error");	
	}
	Buffer[ibcntl] = '\0';        /* Null terminate the ASCII string         */
	printf("%s\n", Buffer);        /* Print the device identification         */

	float voltage = atof(Buffer);
	cout << "Voltage is set to: " << voltage << endl;

	if(voltage != 0.) warning_dialog(voltage);


	//strcpy(stringinput,":OUTP ON");
	//ibwrt(Device,stringinput, strlen(stringinput));     /* Send the ON command   */
	kdevice.write(":OUTP ON");
}

static void button_clicked2()
{
	g_print ("Button2 (OFF) Pressed\n");

	//strcpy(stringinput,":SOUR:VOLT:IMM:AMPL?");
	//ibwrt(Device,stringinput, strlen(stringinput));     /* Send the ON command   */
	kdevice.write(":SOUR:VOLT:IMM:AMPL?");

	//ibrd(Device, Buffer, 100);     /* Read up to 100 bytes from the device    */
	kdevice.read(Buffer,100);
	if (ibsta & ERR) {
     GpibError("ibrd Error");	
	}
	Buffer[ibcntl] = '\0';        /* Null terminate the ASCII string         */
	printf("%s\n", Buffer);        /* Print the device identification         */

	double startpoint = atof(Buffer);
	int endpoint = 0;

	cout << "start point : " << startpoint << endl;
	cout << "end   point : " << endpoint << endl;

	if(startpoint != 0)
	{
		printf("Need to ramp down\n");
		kdevice.rampvoltagedown(startpoint,endpoint);
	}

	//strcpy(stringinput,":OUTP OFF");
	//ibwrt(Device,stringinput, strlen(stringinput));     /* Send the identification query command   */
	kdevice.write("OUTP OFF");

}

static void button_clicked3()
{
	std::cout << "Button3 (QUIT) Pressed" << std::endl;
	gtk_main_quit();
}

static void button_clicked4() {
	// Function for the 'test' button
	// Mapped to the current_pulse_sweep function

	kdevice.current_pulse_sweep(0,10,100, "C:\\Users\\manager\\Documents\\");

	cout << "button 4 pressed, and function (hopefully) executed." << endl;
}

static void setvoltage()
{
	std::cout << "Voltage entered" << std::endl;
	
//	gchar *buff;
//	buff = gtk_entry_get_text(GTK_ENTRY(entry1));
	const gchar *entry_text;
	entry_text = gtk_entry_get_text(GTK_ENTRY(entry1));
	printf("Entry contents: %s\n", entry_text);

	//strcpy(stringinput,":SOUR:VOLT:IMM:AMPL?");
	//ibwrt(Device,stringinput, strlen(stringinput));     /* Send the ON command   */
	kdevice.write(":SOUR:VOLT:IMM:AMPL?");

	//ibrd(Device, Buffer, 100);     /* Read up to 100 bytes from the device    */
	kdevice.read(Buffer,100);
	if (ibsta & ERR) {
     GpibError("ibrd Error");	
	}
	Buffer[ibcntl] = '\0';        /* Null terminate the ASCII string         */
	printf("%s\n", Buffer);        /* Print the device identification         */

	float startpoint = atof(Buffer);
	int endpoint = atoi(entry_text);

	cout << "start point : " << startpoint << endl;
	cout << "end   point : " << endpoint << endl;

	if(startpoint<endpoint)
	{
		kdevice.rampvoltageup(startpoint,endpoint);
	}
	else
	{
		kdevice.rampvoltagedown(startpoint,endpoint);
	}

	//strcpy(stringinput,":SOUR:VOLT:IMM:AMPL?");
	//ibwrt(Device,stringinput, strlen(stringinput));     /* Send the ON command   */
	kdevice.write(":SOUR:VOLT:IMM:AMPL?");

	//ibrd(Device, Buffer, 100);     /* Read up to 100 bytes from the device    */
	kdevice.read(Buffer,100);

	if (ibsta & ERR) {
     GpibError("ibrd Error");	
	}
	Buffer[ibcntl] = '\0';        /* Null terminate the ASCII string         */
	cout << "SET VOLTAGE TO : " << Buffer << endl;

	float volt = atof(Buffer);
	cout << "VOLT = " << volt << endl;
	sprintf(Buffer,"%6.2f",volt);
	cout << "BUFFER " << Buffer << endl;

	gtk_entry_set_text(GTK_ENTRY(entry2), Buffer);
	gdk_window_process_all_updates();

}


void tfunc(gpointer null)
{
	gdk_threads_enter();

//	strcpy(stringinput,":READ?");
//	ibwrt(Device,stringinput, strlen(stringinput));     /* Send the identification query command   */

	//strcpy(stringinput,":OUTP:STAT?");
	//ibwrt(Device,stringinput, strlen(stringinput));     /* Send the identification query command   */
	kdevice.write(":OUTP:STAT?");

	//ibrd(Device, Buffer, 100);     /* Read up to 100 bytes from the device    */
	kdevice.read(Buffer,100);

	if (ibsta & ERR) {
      GpibError("ibrd Error");	
	}
	Buffer[ibcntl] = '\0';        /* Null terminate the ASCII string         */
//	printf("%s\n", Buffer);        /* Print the device identification         */

	if(atoi(Buffer) == 1)
	{
		//strcpy(stringinput,":READ?");
		//ibwrt(Device,stringinput, strlen(stringinput));     /* Send the identification query command   */
		kdevice.write(":READ?");

		//ibrd(Device, Buffer, 100);     /* Read up to 100 bytes from the device    */
		kdevice.read(Buffer,100);
		if (ibsta & ERR) {
		GpibError("ibrd Error");	
		}
		Buffer[ibcntl] = '\0';        /* Null terminate the ASCII string         */
//		printf("%s\n", Buffer);        /* Print the device identification         */

		time_t timenow = time(NULL);
		int difference = timenow-startingtime;
		if(difference >=60)
		{
			cout << "time elasped is 1 minute" << endl;
			cout << "staring time " << startingtime << endl;
			cout << "time now " << timenow << endl;
//			float current = atof(Buffer);
			char *outputstring = gettime();
			const gchar *voltage = gtk_entry_get_text(GTK_ENTRY(entry2));
			outputfile.open("current.txt",ios::app);
			cout << voltage << endl;
			cout << Buffer << endl;
			cout << timenow << endl;
			cout << outputstring << endl;
//			getchar();
			outputfile << outputstring << "\t" << timenow << "\t" << voltage << "\t" << Buffer;
			outputfile.close();
//			float voltage = atof(buff);
//			printf("time 1 %s\n",timeformat);
//			outputfile = fopen ("test.txt", "a+");
//			fprintf(outputfile, "%e %i %s\n", current, timenow, timeformat);
//			strcat(outputstring,Buffer);
//			printf("outputstring = %s\n",outputstring);
//			getchar();
//			fprintf(outputfile, "%s\n", outputstring);
//			fclose(outputfile);

			startingtime = timenow;
		}

		gtk_entry_set_text(GTK_ENTRY(entry3), Buffer);
		gdk_window_process_all_updates();
	}

	gdk_threads_leave();

}




void func( GtkWidget *widget, gpointer null )
{
GThread *tid;
//const gchar *name;

tid = g_thread_create( (GThreadFunc)tfunc, NULL, FALSE, NULL ); // depreciated API
//tid = g_thread_new( NULL, (GThreadFunc)tfunc, NULL );
}


/*-- Main routine --*/

int main(int argc, char* argv[])
{

//	  g_thread_init(NULL);
//    gdk_threads_init();
										// gdk_threads_init is depreciated 
										// http://developer.gnome.org/glib/2.31/glib-Deprecated-Thread-APIs.html


	/*-- Declare the GTK Widgets used in the program --*/
	/*--  Initialize GTK --*/
	gtk_init (&argc, &argv);

   int   PrimaryAddress = 24;      /* Primary address of the device           */
   int   SecondaryAddress = 0;    /* Secondary address of the device         */
   char  Buffer[101];             /* Read buffer                             */

   cout << ibcnt;

/*****************************************************************************
 * Initialization - Done only once at the beginning of your application.
 *****************************************************************************/

   //Device = ibdev(                /* Create a unit descriptor handle         */
   //      0,              /* Board Index (GPIB0 = 0, GPIB1 = 1, ...) */
   //      PrimaryAddress,          /* Device primary address                  */
   //      SecondaryAddress,        /* Device secondary address                */
   //      T10s,                    /* Timeout setting (T10s = 10 seconds)     */
   //      1,                       /* Assert EOI line at end of write         */
   //      0);                      /* EOS termination mode                    */
   if (ibsta & ERR) {           /* Check for GPIB Error                    */
      GpibError("ibdev Error"); 
   }

   //ibclr(Device);                 /* Clear the device                        */
   kdevice.clear();
   if (ibsta & ERR) {
      GpibError("ibclr Error");
   }

/*****************************************************************************
 * Main Application Body - Write the majority of your GPIB code here.
 *****************************************************************************/

   //ibwrt(Device, "*IDN?", 5);     /* Send the identification query command   */
   kdevice.write("*IDN?");
   if (ibsta & ERR) {
      GpibError("ibwrt Error");
   }

   //ibrd(Device, Buffer, 100);     /* Read up to 100 bytes from the device    */
   kdevice.read(Buffer,100);
   if (ibsta & ERR) {
      GpibError("ibrd Error");	
   }
   Buffer[ibcntl] = '\0';        /* Null terminate the ASCII string         */
   printf("%s\n", Buffer);        /* Print the device identification         */


   //ibwrt(Device, "*RST", 5);     
   //ibwrt(Device, "*CLS", 5);     
   //ibwrt(Device, ":SOUR:FUNC VOLT", 15);     
   //ibwrt(Device, ":SOUR:VOLT:MODE FIXED", 21);     
   //ibwrt(Device, ":SOUR:VOLT:LEV 0", 16);
   //ibwrt(Device, ":SENS:CURR:PROT 150E-6", 22);
   //ibwrt(Device, ":SENS:FUNC 'CURR'", 17);
   //ibwrt(Device, ":FORM:ELEM CURR", 15);
   //ibwrt(Device, ":TRIG:COUN 1", 12);

   kdevice.write("*RST");
   kdevice.write("*CLS");
   kdevice.write(":SOUR:FUNC VOLT");     
   kdevice.write(":SOUR:VOLT:MODE FIXED");     
   kdevice.write(":SOUR:VOLT:LEV 0");
   kdevice.write(":SENS:CURR:PROT 150E-6");
   kdevice.write(":SENS:FUNC 'CURR'");
   kdevice.write(":FORM:ELEM CURR");
   kdevice.write(":TRIG:COUN 1");

	/*-- Create the new window --*/
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	/*-- Set the window to be 640 x 480 pixels --*/
	gtk_window_set_default_size (GTK_WINDOW(window), 640, 480);
//	gtk_window_set_default_size (GTK_WINDOW(window), 500, 100);

	/*-- Set the window title --*/
	gtk_window_set_title(GTK_WINDOW (window), "Keithley 2410 Control");


	/*-- Create the buttons --*/

	label1  = gtk_label_new("Required Voltage (V)\n(press <Enter> to set):");
	entry1  = gtk_entry_new();
	label2  = gtk_label_new("Set Voltage (V):");
	entry2  = gtk_entry_new();
	label3  = gtk_label_new("Current (A):");
	entry3  = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY (entry1), "0.00");
	gtk_entry_set_text(GTK_ENTRY (entry2), "0.00");
	button1 = gtk_button_new_with_label("ON");
	button2 = gtk_button_new_with_label("OFF");
	button3 = gtk_button_new_with_label("QUIT");

	// Added to test GTK
	button4 = gtk_button_new_with_label("TEST");

	// Create the 1x2 table 
	// The table will expand as new widgets are placed in new cells
	table = gtk_table_new(1, 2, TRUE);

	// void                gtk_table_attach_defaults           (GtkTable *table,
    //                                                     GtkWidget *widget,
    //                                                     guint left_attach,
    //                                                     guint right_attach,
    //                                                     guint top_attach,
    //                                                     guint bottom_attach);
	gtk_table_attach_defaults(GTK_TABLE(table), label1,       0, 1, 0, 1);
	gtk_table_attach_defaults(GTK_TABLE(table), entry1,       1, 3, 0, 1);
	gtk_table_attach_defaults(GTK_TABLE(table), button1,      0, 1, 1, 2);
	gtk_table_attach_defaults(GTK_TABLE(table), button2,      1, 2, 1, 2);
	gtk_table_attach_defaults(GTK_TABLE(table), button3,      2, 3, 1, 2);
	gtk_table_attach_defaults(GTK_TABLE(table), label2,       0, 1, 2, 3);
	gtk_table_attach_defaults(GTK_TABLE(table), entry2,       1, 3, 2, 3);
	gtk_table_attach_defaults(GTK_TABLE(table), label3,       0, 1, 3, 4);
	gtk_table_attach_defaults(GTK_TABLE(table), entry3,       1, 3, 3, 4);
	
	// Added to test GTK
	gtk_table_attach_defaults(GTK_TABLE(table), button4,      0, 3, 4, 5);

	/*-- Connect the button to the button_was_clicked function --*/
	gtk_signal_connect(GTK_OBJECT(button1), "clicked", GTK_SIGNAL_FUNC(button_clicked1), NULL);
	gtk_signal_connect(GTK_OBJECT(button2), "clicked", GTK_SIGNAL_FUNC(button_clicked2), NULL);
	gtk_signal_connect(GTK_OBJECT(button3), "clicked", GTK_SIGNAL_FUNC(button_clicked3), NULL);
	gtk_signal_connect(GTK_OBJECT(button4), "clicked", GTK_SIGNAL_FUNC(button_clicked4), NULL);
	gtk_signal_connect(GTK_OBJECT(entry1), "activate", GTK_SIGNAL_FUNC(setvoltage), NULL); 
		/*-- Add the table to the window --*/
	gtk_table_set_row_spacings(GTK_TABLE(table),5);
	gtk_table_set_col_spacings(GTK_TABLE(table),5);
	gtk_container_add(GTK_CONTAINER(window), table);





	/*-- Set window border to zero so that text area takes up the whole window --*/
	gtk_container_border_width (GTK_CONTAINER (window), 5);

	//g_idle_add_full(G_PRIORITY_DEFAULT_IDLE, (GSourceFunc) &func, NULL,NULL); //caused error -410 when the Keithley was plugged in
	g_timeout_add_full(G_PRIORITY_DEFAULT_IDLE, 1000, (GSourceFunc) &func, NULL,NULL);


	/*-- Display the widgets --*/

	gtk_widget_show_all(window);

	/*-- Start the GTK event loop --*/
	gdk_threads_enter();
	gtk_main();
	gdk_threads_leave();

  /*-- Return 0 if exit is successful --*/
  return 0;


}


/*****************************************************************************
 *                      Function GPIBERROR
 * This function will notify you that a NI-488 function failed by
 * printing an error message.  The status variable IBSTA will also be
 * printed in hexadecimal along with the mnemonic meaning of the bit
 * position. The status variable IBERR will be printed in decimal
 * along with the mnemonic meaning of the decimal value.  The status
 * variable IBCNT will be printed in decimal.
 *
 * The NI-488 function IBONL is called to disable the hardware and
 * software.
 *
 * The EXIT function will terminate this program.
 *****************************************************************************/
void GpibError(const char *msg) {

    printf("%s\n", msg);

    printf("ibsta = 0x%x  <", ibsta);
    if (ibsta & ERR )  printf(" ERR");
    if (ibsta & TIMO)  printf(" TIMO");
    if (ibsta & END )  printf(" END");
    if (ibsta & SRQI)  printf(" SRQI");
    if (ibsta & RQS )  printf(" RQS");
    if (ibsta & CMPL)  printf(" CMPL");
    if (ibsta & LOK )  printf(" LOK");
    if (ibsta & REM )  printf(" REM");
    if (ibsta & CIC )  printf(" CIC");
    if (ibsta & ATN )  printf(" ATN");
    if (ibsta & TACS)  printf(" TACS");
    if (ibsta & LACS)  printf(" LACS");
    if (ibsta & DTAS)  printf(" DTAS");
    if (ibsta & DCAS)  printf(" DCAS");
    printf (" >\n");

    printf ("iberr = %d", iberr);
    if (iberr == EDVR) printf(" EDVR <Driver error>\n");
    if (iberr == ECIC) printf(" ECIC <Not Controller-In-Charge>\n");
    if (iberr == ENOL) printf(" ENOL <No Listener>\n");
    if (iberr == EADR) printf(" EADR <Address error>\n");
    if (iberr == EARG) printf(" EARG <Invalid argument>\n");
    if (iberr == ESAC) printf(" ESAC <Not System Controller>\n");
    if (iberr == EABO) printf(" EABO <Operation aborted>\n");
    if (iberr == ENEB) printf(" ENEB <No GPIB board>\n");
    if (iberr == EOIP) printf(" EOIP <Async I/O in progress>\n");
    if (iberr == ECAP) printf(" ECAP <No capability>\n");
    if (iberr == EFSO) printf(" EFSO <File system error>\n");
    if (iberr == EBUS) printf(" EBUS <Command error>\n");
    if (iberr == ESTB) printf(" ESTB <Status byte lost>\n");
    if (iberr == ESRQ) printf(" ESRQ <SRQ stuck on>\n");
    if (iberr == ETAB) printf(" ETAB <Table Overflow>\n");
    if (iberr == ELCK) printf(" ELCK <Lock error>\n");
    if (iberr == EARM) printf(" EARM <Ibnotify rearm error>\n");
    if (iberr == EHDL) printf(" EHDL <Invalid Handle>\n");
    if (iberr == EWIP) printf(" EWIP <Wait already in progress>\n");
    if (iberr == ERST) printf(" ERST <Notification cancelled due to reset>\n");
    if (iberr == EPWR) printf(" EPWR <Power error>\n");

    printf("ibcntl = %u\n", ibcntl);
    printf("\n");

    /* Call ibonl to take the device and interface offline */
    //ibonl(Device, 0);
	kdevice.close_connection();

	gdk_threads_leave();


    //exit(1);
}