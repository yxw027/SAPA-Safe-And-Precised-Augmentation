#include <stdio.h>
#include<conio.h> //including conio.h for _getch function.
void gpp_sapa_ocb_asciifile2buffer();
void gpp_sapa_hpac_asciifile2buffer();
int main()
{
	//This function reads ascii files epoch by epoch and writes in SAPA structures
	//It also reads from SAPA structures and copies into binary buffer
	gpp_sapa_ocb_asciifile2buffer();
	gpp_sapa_hpac_asciifile2buffer();
	
	_getch(); // Hold the output screen 
	return 0;
}