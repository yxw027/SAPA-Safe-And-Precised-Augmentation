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
	//FILE *fp1 = fopen("SapEcd_001.ocb", "r");
	//FILE *fp2 = fopen("sap/enc_001.ocb", "r");

	//if (fp1 == NULL || fp2 == NULL)
	//{
	//	printf("Error : Files not open");
	//	exit(0);
	//}

	//compare_files(fp1, fp2);
	//// closing both file 
	//fclose(fp1);
	//fclose(fp2);
	
	_getch(); // Hold the output screen 
	return 0;
}