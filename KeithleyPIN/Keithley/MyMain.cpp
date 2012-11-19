/* This program is adapted from the Keithley program found in ../Keithley
 * using the ni4882 api. Minimal changes have been made, therefore artifacts
 * of the gui remain, despite the fact that there is no gui present to the
 * user.
 *
 * TODO
 * If useful, this program can be quickly adapted for use by the KUSB-488B by
 * use of the webpage 
 * http://digital.ni.com/public.nsf/allkb/85C6F4990C8BA691862575FB006F1EDB
 * and linking the 32-bit GPIB library instead of the ni4882 library.
 */

// initializing C++
#include "ni4882.h"
#include <gtkmm.h>
#include <glibmm\thread.h>
#include <iostream>
#include <ctime>
#include <time.h>
#include <iomanip>
#include <string>
#include <iostream>
#include <fstream>
#include "windows.h"
using namespace std;

time_t startingtime;


char  Buffer[1000];             
//FILE *outputfile;
ofstream outputfile1;
ofstream outputfile2;

void GpibError(const char * msg); /* Error function declaration              */

int Device = 0;                   /* Device unit descriptor                  */
int BoardIndex = 0;               /* Interface Index (GPIB0=0,GPIB1=1,etc.)  */
static char stringinput[512];










/*-- Main routine --*/

int main(int argc, char* argv[])
{

   int   PrimaryAddress = 24;      /* Primary address of the device           */
   int   SecondaryAddress = 0;    /* Secondary address of the device         */
   char  Buffer[1001];             /* Read buffer                             */

/*****************************************************************************
 * Initialization - Done only once at the beginning of your application.
 *****************************************************************************/

   Device = ibdev(                /* Create a unit descriptor handle         */
         0,              /* Board Index (GPIB0 = 0, GPIB1 = 1, ...) */
         PrimaryAddress,          /* Device primary address                  */
         SecondaryAddress,        /* Device secondary address                */
         T10s,                    /* Timeout setting (T10s = 10 seconds)     */
         1,                       /* Assert EOI line at end of write         */
         0);                      /* EOS termination mode                    */
   if (Ibsta() & ERR) {           /* Check for GPIB Error                    */
      GpibError("ibdev Error"); 
   }

   ibclr(Device);                 /* Clear the device                        */
   if (Ibsta() & ERR) {
      GpibError("ibclr Error");
   }

/*****************************************************************************
 * Main Application Body - Write the majority of your GPIB code here.
 *****************************************************************************/

   ibwrt(Device, "*IDN?", 5);     /* Send the identification query command   */
   if (Ibsta() & ERR) {
      GpibError("ibwrt Error");
   }

   ibrd(Device, Buffer, 1000);     /* Read up to 100 bytes from the device    */
   if (Ibsta() & ERR) {
      GpibError("ibrd Error");	
   }
   Buffer[Ibcnt()] = '\0';        /* Null terminate the ASCII string         */
   printf("%s\n", Buffer);        /* Print the device identification         */


   ibwrt(Device, "*CLS", 5);     /* Send the identification query command   */
   //ibwrt(Device, ":SOUR:FUNC VOLT", 15);     /* Send the identification query command   */
   //ibwrt(Device, ":SOUR:VOLT:MODE FIXED", 21);     /* Send the identification query command   */
   //ibwrt(Device, ":SOUR:VOLT:LEV 0", 16);     /* Send the identification query command   */
   //ibwrt(Device, ":SENS:CURR:PROT 150E-6", 22);     /* Send the identification query command   */
   //ibwrt(Device, ":SENS:FUNC 'CURR'", 17);     /* Send the identification query command   */
   //ibwrt(Device, ":FORM:ELEM CURR", 15);     /* Send the identification query command   */
   //ibwrt(Device, "*RST", 5);     /* Send the identification query command   */
   //ibwrt(Device, ":TRIG:COUN 1", 12);     /* Send the identification query command   */

   ibwrt(Device, "*RST", 5);     /* Send the identification query command   */
   ibwrt(Device, ":SYST:BEEP:STAT OFF", 19);
   ibwrt(Device, ":SENS:FUNC:CONC OFF", 19);    
   ibwrt(Device, ":SOUR:FUNC CURR", 15);     
   ibwrt(Device, ":SENS:FUNC 'VOLT:DC'", 20);
   //ibwrt(Device, ":SENS:VOLT:RANG 200", 19);
   ibwrt(Device, ":SENS:VOLT:RANG:AUTO", 20);
   ibwrt(Device, ":SENS:VOLT:PROT 100", 19);     
   ibwrt(Device, ":SOUR:CURR:MODE LIST", 20);     
   ibwrt(Device, ":SOUR:LIST:CURR 0.001,0.001,0.001,0.0", 37);    
   ibwrt(Device, ":TRIG:COUN 4", 12); 
   ibwrt(Device, ":SOUR:DEL 0.01", 13);  
   ibwrt(Device, ":ROUT:TERM FRONT", 15); 
   ibwrt(Device, ":OUTP ON", 8);   
   ibwrt(Device, ":READ?", 6);     

   ibrd(Device, Buffer, 1000);     /* Read up to 100 bytes from the device    */
 	if (Ibsta() & ERR) {
		GpibError("ibrd Error");	
		}
		Buffer[Ibcnt()] = '\0';        /* Null terminate the ASCII string         */
		printf("HERE WHAT WE READ\n");
		printf("%s\n", Buffer);        /* Print the device identification         */
		printf("HERE WHAT WE READ (FINISHED)\n");



	time_t now = time(0);
	char *gtim = g_strdup(ctime(&now));
	tm *ptm = localtime(&now);
//	char *timebuffer = '0';
	sprintf(gtim,"%02d:%02d:%02d %02d:%02d:%04d",ptm->tm_hour,ptm->tm_min,ptm->tm_sec,ptm->tm_mday,(ptm->tm_mon)+1,(ptm->tm_year)+1900);
	cout << "time " << gtim << endl;


	strcpy(stringinput,":OUTP OFF");
	ibwrt(Device,stringinput, strlen(stringinput));     /* Send the identification query command   */

    outputfile1.open("test1.txt",ios::app);
	outputfile1 << gtim << "\t" << Buffer;
	outputfile1.close();

// SECOND PIN


   ibwrt(Device, ":ROUT:TERM REAR", 15); 
   ibwrt(Device, ":OUTP ON", 8);   
   ibwrt(Device, ":READ?", 6);     

   ibrd(Device, Buffer, 1000);     /* Read up to 100 bytes from the device    */
 	if (Ibsta() & ERR) {
		GpibError("ibrd Error");	
		}
		Buffer[Ibcnt()] = '\0';        /* Null terminate the ASCII string         */
		printf("HERE WHAT WE READ\n");
		printf("%s\n", Buffer);        /* Print the device identification         */
		printf("HERE WHAT WE READ (FINISHED)\n");


	strcpy(stringinput,":OUTP OFF");
	ibwrt(Device,stringinput, strlen(stringinput));     /* Send the identification query command   */

    outputfile2.open("test2.txt",ios::app);
	outputfile2 << gtim << "\t" << Buffer;
	outputfile2.close();



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

    printf("Ibsta() = 0x%x  <", Ibsta());
    if (Ibsta() & ERR )  printf(" ERR");
    if (Ibsta() & TIMO)  printf(" TIMO");
    if (Ibsta() & END )  printf(" END");
    if (Ibsta() & SRQI)  printf(" SRQI");
    if (Ibsta() & RQS )  printf(" RQS");
    if (Ibsta() & CMPL)  printf(" CMPL");
    if (Ibsta() & LOK )  printf(" LOK");
    if (Ibsta() & REM )  printf(" REM");
    if (Ibsta() & CIC )  printf(" CIC");
    if (Ibsta() & ATN )  printf(" ATN");
    if (Ibsta() & TACS)  printf(" TACS");
    if (Ibsta() & LACS)  printf(" LACS");
    if (Ibsta() & DTAS)  printf(" DTAS");
    if (Ibsta() & DCAS)  printf(" DCAS");
    printf (" >\n");

    printf ("Iberr() = %d", Iberr());
    if (Iberr() == EDVR) printf(" EDVR <Driver error>\n");
    if (Iberr() == ECIC) printf(" ECIC <Not Controller-In-Charge>\n");
    if (Iberr() == ENOL) printf(" ENOL <No Listener>\n");
    if (Iberr() == EADR) printf(" EADR <Address error>\n");
    if (Iberr() == EARG) printf(" EARG <Invalid argument>\n");
    if (Iberr() == ESAC) printf(" ESAC <Not System Controller>\n");
    if (Iberr() == EABO) printf(" EABO <Operation aborted>\n");
    if (Iberr() == ENEB) printf(" ENEB <No GPIB board>\n");
    if (Iberr() == EOIP) printf(" EOIP <Async I/O in progress>\n");
    if (Iberr() == ECAP) printf(" ECAP <No capability>\n");
    if (Iberr() == EFSO) printf(" EFSO <File system error>\n");
    if (Iberr() == EBUS) printf(" EBUS <Command error>\n");
    if (Iberr() == ESTB) printf(" ESTB <Status byte lost>\n");
    if (Iberr() == ESRQ) printf(" ESRQ <SRQ stuck on>\n");
    if (Iberr() == ETAB) printf(" ETAB <Table Overflow>\n");
    if (Iberr() == ELCK) printf(" ELCK <Lock error>\n");
    if (Iberr() == EARM) printf(" EARM <Ibnotify rearm error>\n");
    if (Iberr() == EHDL) printf(" EHDL <Invalid Handle>\n");
    if (Iberr() == EWIP) printf(" EWIP <Wait already in progress>\n");
    if (Iberr() == ERST) printf(" ERST <Notification cancelled due to reset>\n");
    if (Iberr() == EPWR) printf(" EPWR <Power error>\n");

    printf("Ibcnt() = %u\n", Ibcnt());
    printf("\n");

    /* Call ibonl to take the device and interface offline */
    ibonl(Device, 0);

	gdk_threads_leave();


    //exit(1);
}