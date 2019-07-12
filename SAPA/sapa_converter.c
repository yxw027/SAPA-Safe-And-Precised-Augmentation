#include <string.h>
#include "gpp_sapa.h"
#include "gpp_sapa_debug.h"
#define GPP_SAPA_MAX_PAYLOAD_BUFFER_LENGTH_BYTES 8192
#define GPP_SAPA_MAX_MSG_BUFFER_LENGTH_BYTES (GPP_SAPA_MAX_PAYLOAD_BUFFER_LENGTH_BYTES+64)

GPPLONG gpp_sapa_ocb_asciifile2buffer()
{
	FILE *pAsciiDataset = NULL;			   // file pointer to ASCII file containing datasets
	char *line_buffer = NULL;			   // Read ASCII file line by line and store in this buffer
	char *line_buffer_for_common = NULL;   // Copy line data with COMMON_INFO for later use
	fpos_t  last_pos;			           // last position of pointer in file
	GPPLONG message_crc_type = 0, ea_flag = 0, crc_frame = 0;

	//Ascii Data set file
	char *ascii_filename = "ascii/SapaInteropTestDataset_001.ocb";
	//char *ascii_filename = "ascii/SapaInteropTestDataset_002.ocb";
	//char *ascii_filename = "ascii/SapaInteropTestDataset_003.ocb";
	//char *ascii_filename = "ascii/SapaInteropTestDataset_004.ocb";

	pGPP_SAPA_OCB pocb= NULL;													//Structure for SAPA
	pGPP_SAPA_OCB pocb_recive = NULL;

	pSAPA_HANDLE psapa_handle = NULL;

	GPPUCHAR *ocb_binary_buffer = NULL;											//Buffer to store the binary data
	GPPUCHAR *ocb_binary_buffer_recive = NULL;											//Buffer to store the binary data
	GPPUCHAR *ocb_sapa_buffer = NULL;
	GPPLONG *byte_pos = 0;														//Starting byte
	GPPLONG *bit_pos = 0;														//Starting bit
	ocb_binary_buffer = (GPPUCHAR *)calloc(GPP_SAPA_MAX_PAYLOAD_BUFFER_LENGTH_BYTES, sizeof(GPPUCHAR));		//Memory Allocation for buffer
	ocb_sapa_buffer = (GPPUCHAR *)calloc(GPP_SAPA_MAX_MSG_BUFFER_LENGTH_BYTES, sizeof(GPPUCHAR));			//Memory Allocation for Sapa buffer
	ocb_binary_buffer_recive = (GPPUCHAR *)calloc(GPP_SAPA_MAX_PAYLOAD_BUFFER_LENGTH_BYTES, sizeof(GPPUCHAR));		//Memory Allocation for buffer
	FILE *fp = stdout;

	pAsciiDataset = fopen(ascii_filename, "r");									//Read file
	if (pAsciiDataset)															//File handle check
	{
		GPPLONG rc;
		unsigned int size = 256;			   // size of line_buffer
		char *tokens[30] = { '\0' };		   // Store the tokens of the line read from the ASCII file
		GPPUINT1 cons_bits = 0;															//Used to fetch End of OCB
		//Allocate memory for line_buffer
		line_buffer = (GPPUCHAR*)calloc(size, sizeof(GPPUCHAR));				//Assuming Max  character of line is 255
		line_buffer_for_common = (GPPUCHAR*)calloc(size, sizeof(GPPUCHAR));		//Assuming Max  character of line is 255
		while (fgets(line_buffer, size, pAsciiDataset) != NULL)					//Read Line and save to line_buffer
		{
			/* skip lines beginning with '#' or blank lines  */
			if (*line_buffer == '#' || !*line_buffer)
			{
				continue;
			}
			else
			{
				//Check for OCB_COMMON_INFO in parsed token
				strcpy(line_buffer_for_common, line_buffer);									//Copy line_buffer data for later use
				GPPUINT4 ntok = gpp_sapa_split_arg_to_tokens(line_buffer, tokens);				//Split line_buffer to tokens
				if ((strncmp(tokens[0], "<OCB_COMMON_INFO>", 17) == 0) && ntok == 9)
				{
					if (!pocb)
					{
						pocb = calloc(1, sizeof(GPP_SAPA_OCB));
						psapa_handle = calloc(1, sizeof(SAPA_HANDLE));
						
						if (!pocb) 
							return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
					}
					if (pocb) 
					{		// allocate the sys-sat two dimensional pointer array
						gpp_sapa_ocb_free_ocb(pocb);
						gpp_sapa_handle_free_ocbHdl(psapa_handle);
					}
					//Check for number of satellites in this particular epoc data.
					fgetpos(pAsciiDataset, &last_pos);														//Save file index current position
					cons_bits = 0;																			//Reset cons_bit
					while (fgets(line_buffer, size, pAsciiDataset) != NULL)
					{
						/* skip lines beginning with '#' or blank lines  */
						if (*line_buffer == '#' || !*line_buffer || *line_buffer == NULL)
						{
							continue;
						}
						else
						{
							memset(tokens, NULL, sizeof(tokens));
							ntok = gpp_sapa_split_arg_to_tokens(line_buffer, tokens);

							if ((strncmp(tokens[0], "<OCB_SATELLITE_DATA>", 20) == 0) && ntok == 16)		//Checking for Satellite Data
							{
								
								if (atoi(tokens[2]) == 0)													//Checking DO NOT USE
								{
									if (tokens[1][0] == 'G')												//Set Bit for End of OCB (0,1,2....15)
										cons_bits = gpp_sapa_set_cons_bit(cons_bits, 0);
									else if (tokens[1][0] == 'R')
										cons_bits = gpp_sapa_set_cons_bit(cons_bits, 1);
								}
							}
							if ((strncmp(tokens[0], "<OCB_COMMON_INFO>", 17) == 0))							//Checking for Satellite Data
							{
								break;
							}
						}
					}
					fsetpos(pAsciiDataset, &last_pos);													//Set file pointer to saved position after COMMON_INFO

					//SAPA_OCB_HANDLE ocb_handle = { 0, };

					//Add OCB data to structure for this epoch.
					memset(tokens, NULL, sizeof(tokens));												//Clearing token memory for new data
					gpp_sapa_split_arg_to_tokens(line_buffer_for_common, tokens);
					int sys_index;
					GPPT_WNT wn_t = { 0, };														// Geo++ Time Handling Structure
					for (sys_index = 0; sys_index < GPP_SAPA_MAX_CONS; sys_index++)						//Add header to all the Systems used in this epoch
					{
						if (gpp_sapa_get_constellation_present_bit(cons_bits, sys_index) == 1)			//Check whether jth sys is present in epoch
						{
							GPP_SAPA_OCB_HEADER header = { 0, };
							header.message_sub_type = sys_index;				//Message SubType
							header.time_tag_type = 1;							//0 OR 1 User's Preference
							

							
							wn_t.wn = atoi(tokens[1]);
							wn_t.t = atof(tokens[2]);
							GPPUINT4 sec;
							if (header.time_tag_type) {
								sec = GPP_T_DIFF(SAPA_GPS_WEEK_20100101, SAPA_GPS_SEC_20100101, wn_t.wn, wn_t.t);
							}
							else
							{
								sec = ((GPPUINT4)wn_t.t) % 3600;
							}

							header.time_tag = sec;
							header.sol_id = atoi(tokens[3]);
							header.sol_processor_id = atoi(tokens[4]);
							header.sol_issue_of_update = atoi(tokens[5]);
							if (sys_index == gpp_sapa_get_highest_cons_set(cons_bits))						//Check End Of OCB data
							{
								header.end_of_obc_set = 1;							//End Of OCB 
							}
							else
							{
								header.end_of_obc_set = 0;							//End Of OCB
							}

							header.reserved = 0;
							header.sat_ref_datum = atoi(tokens[6]);
							header.yaw_flag = atoi(tokens[7]);
							header.ephemeris_type = atoi(tokens[8]);
							
							pocb->sv_prn_bits[sys_index] = 0;
							
							if (rc = gpp_sapa_ocb_add_header(pocb, sys_index, &header))
								return rc;

							
						}
					}

					while (fgets(line_buffer, size, pAsciiDataset) != NULL)
					{
						if (*line_buffer == '#' || !*line_buffer || *line_buffer == NULL)
						{
							continue;
						}
						else
						{
							memset(tokens, NULL, sizeof(tokens));													//Clearing token memory for new data
							ntok = gpp_sapa_split_arg_to_tokens(line_buffer, tokens);

							if ((strncmp(tokens[0], "<OCB_COMMON_INFO>", 17) == 0))
							{
								fsetpos(pAsciiDataset, &last_pos);
								break;
							}

							if ((strncmp(tokens[0], "<OCB_SATELLITE_DATA>", 20) == 0) && ntok == 16)				//Checking for Satellite Data
							{
								if (atoi(tokens[2]) == 0)															//Check Do Not Use
								{
									GPP_SAPA_OCB_SV sv = { 0, };
									GPP_SAPA_OCB_SV_ORB orb = { 0, };
									GPP_SAPA_OCB_SV_CLK clk = { 0, };
									
									int sys = 0;
									int sat = 0;

									//Getting constellation number from token
									if (tokens[1][0] == 'G')
										sys = 0;
									else if (tokens[1][0] == 'R')
										sys = 1;

									//Getting satellite number from token
									char sat_id[] = { tokens[1][1] , tokens[1][2] , tokens[1][3] };					//Checking satellite number
									sat = atoi(sat_id);

								/*	ocb_handle.time_tag_type = 1;
									ocb_handle.sys = sys;
*/
									//GNSS_SET_IDX_IN_BITS_64(psapa_handle->ocbHdl_bits[sys], sat);

									//char s			
									// The no of tokens must be XX
									// If no of tokens is not 14 then skip to next SATELLITE_DATA

									// If DO NOT USE FLAG ==1, then skip to next SATELLITE DATA in the same COMMON_INFO 
									// If this is last satellite data in that commmon_info then it should go to NEXT COMMON_INFO

									// check for any invliad fileds, out of range fields, 
									// If any invlid field is found, skip to next SATELLITE_DATA in the same COMMON_INFO field
									// If this is last satellite data in that commmon_info then it should go to NEXT COMMON_INFO

									//pOCB->sv_prn_bits[sys] = gpp_sapa_set_satellite_mask_position(pOCB->sv_prn_bits[sys], sat);
									//gpp_sapa_set_satellite_mask_position(&pOCB->sv_prn_bits[sys], sat);

									sv.do_not_use = atoi(tokens[2]);
									gpp_sapa_set_ocb_present_flags(&sv.ocb_bits, GPP_SAPA_OCB_FLAG_IDX_ORB, atoi(tokens[3]));
									gpp_sapa_set_ocb_present_flags(&sv.ocb_bits, GPP_SAPA_OCB_FLAG_IDX_CLK, atoi(tokens[4]));
									gpp_sapa_set_ocb_present_flags(&sv.ocb_bits, GPP_SAPA_OCB_FLAG_IDX_BIAS, atoi(tokens[5]));

									sv.continuity_indicator = atof(tokens[6]);

									if (rc = gpp_sapa_ocb_add_sv(pocb, sys, sat, &sv)) 
										return rc;

									orb.iode = atoi(tokens[7]);

									orb.d_orbit[0] = atof(tokens[9]);
									orb.d_orbit[1] = atof(tokens[10]);
									orb.d_orbit[2] = atof(tokens[11]);

									if (atof(tokens[12])) 
									{
										orb.sat_yaw = atof(tokens[13]);
									}
									else 
									{
										orb.sat_yaw = -1.0;
									}

									orb.wnt.wn = wn_t.wn;
									orb.wnt.t = wn_t.t;
									

									if (sv.ocb_bits&(1 << GPP_SAPA_OCB_FLAG_IDX_ORB))
									{
										//if (rc = gpp_sapa_config_add_ocb_config(psapa_handle, sys, sat, GPP_SAPA_OCB_BITS_ORB, &ocb_handle, fp))    //testing config=1
										//	return rc;

										if (rc = gpp_sapa_ocb_add_orb(pocb, sys, sat, &orb)) 
											return rc;
									}

									clk.iode_continuity = atof(tokens[8]);
									clk.clk_correction = atof(tokens[14]);
									clk.user_range_error = atof(tokens[15]);

									clk.wnt.wn = wn_t.wn;
									clk.wnt.t = wn_t.t;

									if (sv.ocb_bits&(1 << GPP_SAPA_OCB_FLAG_IDX_CLK))
									{
										//if (rc = gpp_sapa_config_add_ocb_config(psapa_handle, sys, sat, GPP_SAPA_OCB_BITS_CLK, &ocb_handle, fp))    //testing config=1
										//	return rc;

										if (rc = gpp_sapa_ocb_add_clk(pocb, sys, sat, &clk)) 
											return rc;
									}

									//Reading next line from file
									fgets(line_buffer, size, pAsciiDataset);										
									memset(tokens, NULL, sizeof(tokens));											//Clearing token memory for new data
									gpp_sapa_split_arg_to_tokens(line_buffer, tokens);

									if ((strncmp(tokens[0], "<OCB_SATPHASE_BIAS>", 19) == 0))						//Checking for Phase Bias data
									{
										//ocb_handle.ocb_bits[sat] = GPP_SAPA_OCB_BITS_PB;
										//if (rc = gpp_sapa_config_add_ocb_config(psapa_handle, sys, sat, GPP_SAPA_OCB_BITS_PB, &ocb_handle, fp))    //testing config=1
										//	return rc;

										int count_index = 1;
										int sig_pb = atoi(tokens[count_index]);										//Phase Bias data slot

										while (tokens[count_index] != NULL)											//Loop to access all the data slots and write to structures
										{
											GPP_SAPA_OCB_SV_BIAS_PB pb = { 0, };

											count_index++;
											pb.pb_correction = atof(tokens[count_index]);

											count_index++;
											pb.fix_flag = atoi(tokens[count_index]);

											count_index++;
											pb.countinity_indicator = atof(tokens[count_index]);

											pb.wnt.wn = wn_t.wn;
											pb.wnt.t = wn_t.t;

											if (rc = gpp_sapa_ocb_add_pb(pocb, sys, sat, sig_pb, &pb))
												return rc;

											count_index++;

											if (tokens[count_index] == NULL)
											{
												break;
											}

											sig_pb = atoi(tokens[count_index]);
										}

										//Reading next line from file
										fgets(line_buffer, size, pAsciiDataset);
										memset(tokens, NULL, sizeof(tokens));										//Clearing token memory for new data
										gpp_sapa_split_arg_to_tokens(line_buffer, tokens);

										if ((strncmp(tokens[0], "<OCB_SATCODE_BIAS>", 18) == 0))					//Checking for Code Bias data
										{
											//if (rc = gpp_sapa_config_add_ocb_config(psapa_handle, sys, sat, GPP_SAPA_OCB_BITS_CB, &ocb_handle, fp))    //testing config=1
											//	return rc;

											int count_index_code = 1;
											int sig_cb = atoi(tokens[count_index_code]);						//Code Bias data slot
											while (tokens[count_index_code] != NULL)								//Loop to access all the data slots and write to structures
											{
												GPP_SAPA_OCB_SV_BIAS_CB  cb = { 0, };

												count_index_code++;
												cb.cb_correction = atof(tokens[count_index_code]);

												cb.wnt.wn = wn_t.wn;
												cb.wnt.t = wn_t.t;

												if (rc = gpp_sapa_ocb_add_cb(pocb, sys, sat, sig_cb, &cb))
													return rc;

												count_index_code++;

												if (tokens[count_index_code] == NULL)
												{
													break;
												}

												sig_cb = atoi(tokens[count_index_code]);
											}
										} // CODE_BIAS ends
									} // PHASE_BIAS ends
									//ocb_sv_handle.ocb_bits = pocb->sv[sys][sat]->ocb_bits;
								}
							} // SATALLITE_DATA ends
						}
						fgetpos(pAsciiDataset, &last_pos);								
					}//Data Read inside COMMON_INFO While ends
					
				}// COMMON_INFO ends;
				int sys_index1,  isat;
				
				byte_pos = 0;
				bit_pos = 0;

				for (sys_index1 = 0; sys_index1 < GPP_SAPA_MAX_CONS; sys_index1++)      //add header to all the systems used in this epoch
				{
					if (gpp_sapa_get_constellation_present_bit(cons_bits, sys_index1) == 1)   //check whether jth sys is present in epoch
					{
						SAPA_OCB_HANDLE ocb_handle = { 0, };
						ocb_handle.time_tag_type = 1;
						ocb_handle.sys = sys_index1;

						if (rc = gpp_sapa_config_add_ocb_config(psapa_handle, sys_index1, &ocb_handle, fp))    //testing config=1
							return rc;

						GPPUINT1 configlist[66];
						GPPUINT1 iconf = 0;
						gpp_sapa_get_configlist(psapa_handle->ocbHdl_bits[sys_index1], configlist);
						iconf = configlist[configlist[0]];
						GPPUINT1 svlist[66] = { 0, };
						gpp_sapa_get_svlist(pocb->sv_prn_bits[sys_index1], svlist);
						for (isat = 1; isat <= svlist[0]; isat++)
						{
							GPPUINT1 sat_index1;
							sat_index1 = svlist[isat];
							if (pocb->sv[sys_index1][sat_index1]->ocb_bits & SAPA_OCB_ORB_BITS)
							{
								psapa_handle->ocbHdl[sys_index1][iconf]->ocb_bits[sat_index1] |= (SAPA_OCB_ORB_BITS);
								psapa_handle->ocbHdl[sys_index1][iconf]->prn_bits[sys_index1] |= (SAPA_OCB_ORB_BITS);
							}
							if (pocb->sv[sys_index1][sat_index1]->ocb_bits & SAPA_OCB_CLK_BITS)
							{
								psapa_handle->ocbHdl[sys_index1][iconf]->ocb_bits[sat_index1] |= (SAPA_OCB_CLK_BITS);
								psapa_handle->ocbHdl[sys_index1][iconf]->prn_bits[sys_index1] |= (SAPA_OCB_CLK_BITS);
							}
							if (pocb->sv[sys_index1][sat_index1]->ocb_bits & SAPA_OCB_BIAS_BITS)
							{
								psapa_handle->ocbHdl[sys_index1][iconf]->ocb_bits[sat_index1] |= (GPP_SAPA_OCB_BITS_PB);
								psapa_handle->ocbHdl[sys_index1][iconf]->prn_bits[sys_index1] |= (GPP_SAPA_OCB_BITS_PB);
							}
							if (pocb->sv[sys_index1][sat_index1]->ocb_bits & SAPA_OCB_BIAS_BITS)
							{
								psapa_handle->ocbHdl[sys_index1][iconf]->ocb_bits[sat_index1] |= (GPP_SAPA_OCB_BITS_CB);
								psapa_handle->ocbHdl[sys_index1][iconf]->prn_bits[sys_index1] |= (GPP_SAPA_OCB_BITS_CB);
							}
						}
					}
				}
				for (sys_index1 = 0; sys_index1 < GPP_SAPA_MAX_CONS; sys_index1++)						//add header to all the systems used in this epoch
				{
					if (gpp_sapa_get_constellation_present_bit(cons_bits, sys_index1) == 1)			//check whether jth sys is present in epoch
					{
						
							rc = gpp_sapa_ocb2buffer(pocb, psapa_handle->ocbHdl[sys_index1][0], ocb_binary_buffer, &byte_pos, &bit_pos);				//add data to buffer //gpp_sapa_ocb2buffer(pocb, sys_index1, ocb_binary_buffer, &byte_pos, &bit_pos);

					}
				}
				GPPLONG last_bit_pos=total_bits(&byte_pos, &bit_pos);
				//gpp_sapa_debug_fprintf_ocb(pocb, fp);
				//gpp_sapa_ocb_buffer_to_sapa_buffer(ocb_binary_buffer, last_bit_pos, ea_flag, message_crc_type, crc_frame, ocb_sapa_buffer);
				if (!pocb_recive)
				{
					pocb_recive = calloc(1, sizeof(GPP_SAPA_OCB));

					if (!pocb_recive)
						return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
				}
				if (pocb_recive)
				{														// allocate the sys-sat two dimensional pointer array
					gpp_sapa_ocb_free_ocb(pocb_recive);
				}
				//gpp_sapa_sapa_buffer_to_ocb_buffer(ocb_binary_buffer_recive, &rc, &ea_flag, &message_crc_type, &crc_frame, ocb_sapa_buffer);
				gpp_sapa_buffer2ocb(pocb_recive, ocb_binary_buffer, NULL, NULL);		//gpp_sapa_buffer2ocb(pocb_recive, ocb_binary_buffer_recive, NULL, NULL);
				printf("===========================================");
				gpp_sapa_debug_fprintf_ocb(pocb_recive, fp);
			}//Data Read File if not null ends

			
			
		}//File Reade while ends
		printf("file successfully\n");
	}//fopen ends
	else
	{
		printf("%s", "The file could not be opened");
	}//else ends
	free(ocb_binary_buffer);
	free(ocb_sapa_buffer);
	free(ocb_binary_buffer_recive);
}

GPPLONG gpp_sapa_hpac_asciifile2buffer()
{
	FILE *pAsciiDataset = NULL;			   // file pointer to ASCII file containing datasets
	char *line_buffer = NULL;			   // Read ASCII file line by line and store in this buffer
	char *line_buffer_for_common = NULL;   // Copy line data with COMMON_INFO for later use
	fpos_t  last_pos;			           // last position of pointer in file
	GPPLONG message_crc_type = 0, ea_flag = 0, crc_frame = 0;

	//Ascii Data set file
	char *ascii_filename = "ascii/SapaInteropTestDataset_001.atm";
	//char *ascii_filename = "ascii/SapaInteropTestDataset_002.ocb";
	//char *ascii_filename = "ascii/SapaInteropTestDataset_003.ocb";
	//char *ascii_filename = "ascii/SapaInteropTestDataset_004.ocb";

	pGPP_SAPA_USE_STATES pstates = NULL;
	pstates = (pGPP_SAPA_USE_STATES)calloc(1, sizeof(GPP_SAPA_USE_STATES));

	pGPP_SAPA_AREA parea = NULL;
	pGPP_SAPA_AREA parea_receive = NULL;
	pGPP_SAPA_HPAC phpac = NULL;
	pGPP_SAPA_HPAC phpac_recive = NULL;

	SAPA_HANDLE *psapa_handle = NULL;
	
	GPPUCHAR *area_binary_buffer = NULL;											//Buffer to store the binary data
	GPPUCHAR *area_binary_buffer_recive = NULL;											//Buffer to store the binary data
	GPPUCHAR *area_sapa_buffer = NULL;

	GPPUCHAR *hpac_binary_buffer = NULL;											//Buffer to store the binary data
	GPPUCHAR *hpac_binary_buffer_recive = NULL;											//Buffer to store the binary data
	GPPUCHAR *hpac_sapa_buffer = NULL;

	GPPLONG *byte_pos = 0;														//Starting byte
	GPPLONG *bit_pos = 0;														//Starting bit
	
	hpac_binary_buffer = (GPPUCHAR *)calloc(GPP_SAPA_MAX_PAYLOAD_BUFFER_LENGTH_BYTES, sizeof(GPPUCHAR));		//Memory Allocation for buffer
	hpac_sapa_buffer = (GPPUCHAR *)calloc(GPP_SAPA_MAX_MSG_BUFFER_LENGTH_BYTES, sizeof(GPPUCHAR));			//Memory Allocation for Sapa buffer
	hpac_binary_buffer_recive = (GPPUCHAR *)calloc(GPP_SAPA_MAX_PAYLOAD_BUFFER_LENGTH_BYTES, sizeof(GPPUCHAR));		//Memory Allocation for buffer
	
	area_binary_buffer = (GPPUCHAR *)calloc(GPP_SAPA_MAX_PAYLOAD_BUFFER_LENGTH_BYTES, sizeof(GPPUCHAR));		//Memory Allocation for buffer
	area_sapa_buffer = (GPPUCHAR *)calloc(GPP_SAPA_MAX_MSG_BUFFER_LENGTH_BYTES, sizeof(GPPUCHAR));			//Memory Allocation for Sapa buffer
	area_binary_buffer_recive = (GPPUCHAR *)calloc(GPP_SAPA_MAX_PAYLOAD_BUFFER_LENGTH_BYTES, sizeof(GPPUCHAR));		//Memory Allocation for buffer

	GPPUINT1 area_id[SAPA_MAX_AREA] = { 0 };		   // Store the tokens of the line read from the ASCII file
	FILE *fp = stdout;

	

	pAsciiDataset = fopen(ascii_filename, "r");									//Read file
	if (pAsciiDataset)															//File handle check
	{
		GPPLONG rc;
		char *tokens[30] = { '\0' };		   // Store the tokens of the line read from the ASCII file
		unsigned int size = 256;			   // size of line_buffer
		GPPUINT4 grid_points = 0;		   // Stores sys bitmask for each area.
		GPPUINT1 area_count = 0;
		//Allocate memory for line_buffer
		line_buffer = (GPPUCHAR*)calloc(size, sizeof(GPPUCHAR));				//Assuming Max  character of line is 255
		line_buffer_for_common = (GPPUCHAR*)calloc(size, sizeof(GPPUCHAR));		//Assuming Max  character of line is 255

		while (fgets(line_buffer, size, pAsciiDataset) != NULL)					//Read Line and save to line_buffer
		{
			//printf(line_buffer, "\n");
			/* skip lines beginning with '#' or blank lines  */
			if (*line_buffer == '#' || !*line_buffer)
			{
				continue;
			}
			else
			{
				//Check for ATM_HPAC_HEADER in parsed token
				strcpy(line_buffer_for_common, line_buffer);									//Copy line_buffer data for later use
				GPPUINT4 ntok = gpp_sapa_split_arg_to_tokens(line_buffer, tokens);				//Split line_buffer to tokens
				if ((strncmp(tokens[0], "<ATM_AREADEF_HEADER>", 20) == 0) && ntok == 4)
				{
					if (!parea)
					{
						pstates->area = (pGPP_SAPA_AREA)calloc(1, sizeof(GPP_SAPA_AREA));
						parea = pstates->area;
						psapa_handle = calloc(1, sizeof(SAPA_HANDLE));

						if (!parea)
							return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
					}
					if (parea)
					{														// allocate the sys-sat two dimensional pointer array
						gpp_sapa_area_free_area(parea);
						gpp_sapa_handle_free_gadHdl(psapa_handle);
					}
					//Check for number of satellites in this particular epoc data.
					fgetpos(pAsciiDataset, &last_pos);														//Save file index current position
					
					memset(area_id, 0, sizeof(area_id));
					while (fgets(line_buffer, size, pAsciiDataset) != NULL)
					{
						/* skip lines beginning with '#' or blank lines  */
						if (*line_buffer == '#' || !*line_buffer || *line_buffer == NULL)
						{
							continue;
						}
						else
						{
							memset(tokens, NULL, sizeof(tokens));
							ntok = gpp_sapa_split_arg_to_tokens(line_buffer, tokens);

							if (strncmp(tokens[0], "<ATM_AREA_DEF>", 14) == 0)		//Checking for Satellite Data
							{
								area_count++;
								area_id[area_count - 1] = atoi(tokens[1]);
							}
							if ((strncmp(tokens[0], "<ATM_HPAC_HEADER>", 17) == 0))							//Checking for Satellite Data
							{
								break;
							}
						}
					}

					fsetpos(pAsciiDataset, &last_pos);

					SAPA_GAD_HANDLE gad_handle = { 0, };

					memset(tokens, NULL, sizeof(tokens));												//Clearing token memory for new data
					ntok = gpp_sapa_split_arg_to_tokens(line_buffer_for_common, tokens);

					if ((strncmp(tokens[0], "<ATM_AREADEF_HEADER>", 20) == 0) && ntok == 4)
					{
						GPP_SAPA_AREA_DEF_HEADER area_header = { 0, };
						SAPA_GAD_HANDLE gad_handle = { 0, };
						area_header.message_sub_type = 0;
						area_header.sol_id = atoi(tokens[1]);
						area_header.sol_processor_id = atoi(tokens[2]);
						area_header.sol_issue_of_update = atoi(tokens[3]);
						area_header.area_issue_of_update = 0;
						area_header.reserved = 0;
						area_header.area_count = area_count;
						if (rc = gpp_sapa_area_add_header(parea, &area_header))
							return rc;
												
						while (fgets(line_buffer, size, pAsciiDataset) != NULL)
						{
							if (*line_buffer == '#' || !*line_buffer || *line_buffer == NULL)
							{
								continue;
							}
							else
							{
								memset(tokens, NULL, sizeof(tokens));													//Clearing token memory for new data
								ntok = gpp_sapa_split_arg_to_tokens(line_buffer, tokens);

								if ((strncmp(tokens[0], "<ATM_HPAC_HEADER>", 17) == 0))
								{
									fsetpos(pAsciiDataset, &last_pos);
									break;
								}
								if (strncmp(tokens[0], "<ATM_AREA_DEF>", 14) == 0)				//Checking for Satellite Data
								{
									fgetpos(pAsciiDataset, &last_pos);														//Save file index current position
									GPP_SAPA_AREA_DEF_BLOCK area_def_block = { 0, };
									GPPUINT1 area_idx;

									area_def_block.area_id = atoi(tokens[1]);
									area_idx = area_def_block.area_id;
									area_def_block.area_ref_lat = atof(tokens[2]);
									area_def_block.area_ref_long = atof(tokens[3]);
									area_def_block.area_lat_grid_node_count = atoi(tokens[4]);
									area_def_block.area_long_grid_node_count = atoi(tokens[5]);
									area_def_block.area_lat_grid_node_spacing = atof(tokens[6]);
									area_def_block.area_long_grid_node_spacing = atof(tokens[7]);
									area_def_block.num_grid_points = area_def_block.area_lat_grid_node_count*area_def_block.area_long_grid_node_count;
									grid_points = area_def_block.num_grid_points;
									
									//check for area index
									gpp_sapa_set_area_bits(gad_handle.area_bits, area_idx);

									if (rc = gpp_sapa_config_add_gad_config(psapa_handle, &gad_handle, fp))
										return rc;

									if (rc = gpp_sapa_area_add_area_def(parea, area_idx, &area_def_block))
										return rc;
								}
							}
						}
						break;
					}
				}
			}
		}
		
		//gpp_sapa_debug_fprintf_area(parea, fp);

		if(!parea_receive)
		{
			parea_receive = calloc(1, sizeof(GPP_SAPA_AREA));

			if (!parea_receive)
				return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
		}
		if (parea_receive)
		{														// allocate the sys-sat two dimensional pointer array
			gpp_sapa_hpac_free_hpac(parea_receive);
		}

		rc=gpp_sapa_area2buffer(parea, psapa_handle->gadHdl, area_binary_buffer, NULL, NULL);
		/*gpp_sapa_area_buffer_to_sapa_buffer(area_binary_buffer, rc, ea_flag, message_crc_type, crc_frame, area_sapa_buffer);
		gpp_sapa_sapa_buffer_to_area_buffer(area_binary_buffer_recive, &rc, &ea_flag, &message_crc_type, &crc_frame, area_sapa_buffer);
		*/
		gpp_sapa_buffer2area(parea_receive, area_binary_buffer, NULL, NULL);
		gpp_sapa_debug_fprintf_area(parea_receive, fp);

		while (fgets(line_buffer, size, pAsciiDataset) != NULL)					//Read Line and save to line_buffer
		{
			/* skip lines beginning with '#' or blank lines  */
			if (*line_buffer == '#' || !*line_buffer)
			{
				continue;
			}
			else
			{
				//Check for ATM_HPAC_HEADER in parsed token
				strcpy(line_buffer_for_common, line_buffer);									//Copy line_buffer data for later use
				GPPUINT4 ntok = gpp_sapa_split_arg_to_tokens(line_buffer, tokens);				//Split line_buffer to tokens
				if ((strncmp(tokens[0], "<ATM_HPAC_HEADER>", 17) == 0) && ntok == 6)
				{
					if (!phpac)
					{
						pstates->hpac = (pGPP_SAPA_HPAC)calloc(1, sizeof(GPP_SAPA_HPAC));
						phpac = pstates->hpac;
						psapa_handle = calloc(1, sizeof(SAPA_HANDLE));

						if (!phpac)
							return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
					}
					if (phpac)
					{														// allocate the sys-sat two dimensional pointer array
						gpp_sapa_hpac_free_hpac(phpac);
						//gpp_sapa_handle_free_hpacHdl(psapa_handle);
					}

					//Check for number of satellites in this particular epoc data.
					fgetpos(pAsciiDataset, &last_pos);														//Save file index current position
					//memset(sys_bit, 0, sizeof(sys_bit));
					
					while (fgets(line_buffer, size, pAsciiDataset) != NULL)
					{
						/* skip lines beginning with '#' or blank lines  */
						if (*line_buffer == '#' || !*line_buffer || *line_buffer == NULL)
						{
							continue;
						}
						else
						{
							memset(tokens, NULL, sizeof(tokens));
							ntok = gpp_sapa_split_arg_to_tokens(line_buffer, tokens);

							if ((strncmp(tokens[0], "<ATM_HPAC_HEADER>", 17) == 0))							//Checking for Satellite Data
							{
								break;
							}
						}
					}
					fsetpos(pAsciiDataset, &last_pos);

					SAPA_HPAC_HANDLE hpac_handle = { 0, };
					memset(tokens, NULL, sizeof(tokens));												//Clearing token memory for new data
					ntok = gpp_sapa_split_arg_to_tokens(line_buffer_for_common, tokens);
					if(strncmp(tokens[0], "<ATM_HPAC_HEADER>", 17) == 0)
					{
						GPP_SAPA_HPAC_HEADER header = { 0, };
						header.message_sub_type = 0;				//Message SubType
						header.time_tag_type = 1;							//0 OR 1 User's Preference

						hpac_handle.time_tag_type = 1;

						GPPT_WNT wn_t = { 0, };														// Geo++ Time Handling Structure
						wn_t.wn = atoi(tokens[1]);
						wn_t.t = atof(tokens[2]);
						GPPUINT4 sec;
						if (header.time_tag_type) {
							sec = GPP_T_DIFF(SAPA_GPS_WEEK_20100101, SAPA_GPS_SEC_20100101, wn_t.wn, wn_t.t);
						}
						else
						{
							sec = ((GPPUINT4)wn_t.t) % 
								0;
						}

						header.time_tag = sec;
						header.sol_id = atoi(tokens[3]);
						header.sol_processor_id = atoi(tokens[4]);
						header.sol_issue_of_update = atoi(tokens[5]);
						header.reserved = 0;
						header.area_issue_of_update = 0;
						header.area_count = area_count;
						
						hpac_handle.sys = 2;
						hpac_handle.time_tag_type = 1;
						hpac_handle.tropo_blk_indicator = 1;
						hpac_handle.iono_blk_indicator = 1;

						gpp_sapa_hpac_add_config_hpacHdl(psapa_handle, &hpac_handle, fp);

						if (rc = gpp_sapa_hpac_add_header(phpac, &header))
							return rc;
						
						fgetpos(pAsciiDataset, &last_pos);
						//Common_Data
						while (fgets(line_buffer, size, pAsciiDataset) != NULL)
						{
							if (*line_buffer == '#' || !*line_buffer || *line_buffer == NULL)
							{
								continue;
							}
							else
							{
								memset(tokens, NULL, sizeof(tokens));													//Clearing token memory for new data
								ntok = gpp_sapa_split_arg_to_tokens(line_buffer, tokens);
								if ((strncmp(tokens[0], "<ATM_HPAC_HEADER>", 17) == 0))
								{
									fsetpos(pAsciiDataset, &last_pos);
									break;
								}

								if (strncmp(tokens[0], "<ATM_HPAC_COMMON_DATA>", 22) == 0)				//Checking for Satellite Data
								{
									GPP_SAPA_HPAC_AREA h_area = { 0, };
									GPPUINT1 tropo_equation_type = 0;
									GPPUINT1 iono_equation_type = 0;

									h_area.area_id = atoi(tokens[1]);
									h_area.number_of_grid_point = grid_points;
									h_area.tropo_block_indicator = atoi(tokens[3]);
									tropo_equation_type = atoi(tokens[4]);
									h_area.iono_block_indicator = atoi(tokens[5]);
									iono_equation_type = atoi(tokens[6]);
									
									if (rc = gpp_sapa_hpac_add_area(phpac, h_area.area_id, &h_area))
										return rc;

									gpp_sapa_set_area_bits(psapa_handle->hpacHdl->area_bits, h_area.area_id);

									fgetpos(pAsciiDataset, &last_pos);
									//Tropo_Data
									while (fgets(line_buffer, size, pAsciiDataset) != NULL)
									{
										if (*line_buffer == '#' || !*line_buffer || *line_buffer == NULL)
										{
											continue;
										}
										else
										{
											memset(tokens, NULL, sizeof(tokens));													//Clearing token memory for new data
											ntok = gpp_sapa_split_arg_to_tokens(line_buffer, tokens);

											if ((strncmp(tokens[0], "<ATM_HPAC_COMMON_DATA>", 22) == 0) || (strncmp(tokens[0], "<ATM_HPAC_HEADER>", 17) == 0))
											{
												fsetpos(pAsciiDataset, &last_pos);
												break;
											}

											if (strncmp(tokens[0], "<ATM_TROPO_DATA>", 16) == 0)				//Checking for Satellite Data
											{
												GPP_SAPA_HPAC_TROPO_POLY_COEFFICIENT_BLOCK h_tropo_coeff = { 0, };
												GPP_SAPA_HPAC_TROPO_GRID_BLOCK h_grid_block = { 0, };
												SAPA_HPAC_HANDLE_TROPO tropo_handle = { 0, };
												GPP_SAPA_HPAC_TROPO_GRD_CORRECTION h_grd_correction = { 0, };

												h_tropo_coeff.tropo_equation_type = tropo_equation_type;
												h_tropo_coeff.tropo_quality = atof(tokens[1]);
												h_tropo_coeff.tropo_avhd = atof(tokens[2]);
												h_tropo_coeff.tropo_coeff_size = 1;									//Placed manually
												tropo_handle.tropo_coeff_size = 1;

												h_tropo_coeff.tropo_poly_coeff[SAPA_T00_IDX] = atof(tokens[3]);
												h_tropo_coeff.tropo_poly_coeff[SAPA_T01_IDX] = atof(tokens[4]);
												h_tropo_coeff.tropo_poly_coeff[SAPA_T10_IDX] = atof(tokens[5]);
												h_tropo_coeff.tropo_poly_coeff[SAPA_T11_IDX] = atof(tokens[6]);

												h_grid_block.sz = 1;								//Placed manually
												h_grid_block.num_grid = grid_points;
												tropo_handle.tropo_residual_size = 1;

												GPP_SAPA_HPAC_IONO iono = { 0, };
												iono.iono_equation_type = iono_equation_type;										//Placed Manually

												if (rc = gpp_sapa_hpac_add_tropo_poly_coeff_block(phpac, h_area.area_id, &h_tropo_coeff))
													return rc;

												if (rc = gpp_sapa_hpac_add_tropo_grid_block(phpac, h_area.area_id, &h_grid_block))
													return rc;

												if (rc = gpp_sapa_hpac_add_iono(phpac, h_area.area_id, &iono))
													return rc;

												if (rc = gpp_sapa_hpac_add_config_tropoHdl(psapa_handle, &tropo_handle, fp))
													return rc;

												int k = 7, res_index = 0;
												while (k < grid_points + 7)
												{
													h_grd_correction.val = atof(tokens[k]);;
													gpp_sapa_hpac_add_grd_tropo_correction(pstates, h_area.area_id, res_index, &h_grd_correction);
													k++;
													res_index++;
												}
												
												fgetpos(pAsciiDataset, &last_pos);
												SAPA_HPAC_HANDLE_IONO iono_handle = { 0, };
												GPPUINT2 sys_bit = 0;
												GPPUINT1 area_ix = h_area.area_id;
												while (fgets(line_buffer, size, pAsciiDataset) != NULL)
												{
													if (*line_buffer == '#' || !*line_buffer || *line_buffer == NULL)
													{
														continue;
													}
													else
													{
														memset(tokens, NULL, sizeof(tokens));													//Clearing token memory for new data
														ntok = gpp_sapa_split_arg_to_tokens(line_buffer, tokens);

														if ((strncmp(tokens[0], "<ATM_HPAC_COMMON_DATA>", 22) == 0) || (strncmp(tokens[0], "<ATM_HPAC_HEADER>", 17) == 0))
														{
															fsetpos(pAsciiDataset, &last_pos);
															break;
														}
														if (strncmp(tokens[0], "<ATM_IONOSAT_DATA>", 18) == 0)				//Checking for Satellite Data
														{
															GPP_SAPA_HPAC_IONO_SAT_POLY iono_sat_poly = { 0, };   //Ionosphere Satellite Poloynomial
															GPP_SAPA_HPAC_IONO_SAT_COEFFICIENT iono_sat_coeff = { 0, }; //Ionosphere Satellite Coefficient
															GPP_SAPA_HPAC_IONO_GRID_BLOCK iono_grid = { 0, };   //Ionosphere Grid Block
															GPP_SAPA_HPAC_IONO_GRD_CORRECTION iono_grd_correction = { 0, };

															int sys = 0;
															int sat = 0;

															//Getting constellation number from token
															if (tokens[1][0] == 'G')
																sys = 0;
															else if (tokens[1][0] == 'R')
																sys = 1;

															//Getting satellite number from token
															char sat_id[] = { tokens[1][1] , tokens[1][2] , tokens[1][3] };					//Checking satellite number
															sat = atoi(sat_id);

															GNSS_SET_IDX_IN_BITS_64(psapa_handle->hpacHdl->prn_bits[sys], sat);

															iono_sat_poly.iono_quality = atof(tokens[2]);
															iono_sat_poly.iono_coeff_size = 1;
															iono_handle.iono_coeff_size = 1;

															if (rc = gpp_sapa_hpac_add_iono_sat_poly_block(phpac, sys, sat, area_ix, &iono_sat_poly))
																return rc;

															iono_sat_coeff.iono_poly_coeff[0] = atof(tokens[3]);
															iono_sat_coeff.iono_poly_coeff[1] = atof(tokens[4]);
															iono_sat_coeff.iono_poly_coeff[2] = atof(tokens[5]);
															iono_sat_coeff.iono_poly_coeff[3] = atof(tokens[6]);

															if (rc = gpp_sapa_hpac_add_iono_sat_coeff_block(phpac, sys, sat, area_ix, &iono_sat_coeff))
																return rc;

															iono_grid.sz = 1;								//Placed manually
															iono_grid.num_grid = grid_points;
															iono_handle.iono_residual_field_size = 1;
															
															if (rc = gpp_sapa_hpac_add_iono_sat_grid_block(phpac, sys, sat, area_ix, &iono_grid))
																return rc;

															res_index = 0;
															k = 7;
															while (k < grid_points + 7)
															{
																iono_grd_correction.val = atof(tokens[k]);
																gpp_sapa_hpac_add_grd_iono_correction(pstates, area_ix, res_index, sat, sys, &iono_grd_correction);
																k++;
																res_index++;
															}
															if (rc = gpp_sapa_hpac_add_ionoHdl(psapa_handle, sys, &iono_handle, fp))
																return rc;

														} // IONO_DATA ends
													}
												}
												
												break;
											}
										}
									}//Data Read inside While ends
								}
							}
							fgetpos(pAsciiDataset, &last_pos);														//Save file index current position
						}
					}
				}// COMMON_INFO ends
				
				gpp_sapa_debug_fprintf_hpac(phpac, psapa_handle->hpacHdl, fp);

				if (!phpac_recive)
				{
					phpac_recive = calloc(1, sizeof(GPP_SAPA_HPAC));

					if (!phpac_recive)
						return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
				}
				if (phpac_recive)
				{														// allocate the sys-sat two dimensional pointer array
					if(rc=gpp_sapa_hpac_free_hpac(phpac_recive)) return rc;
				}
				byte_pos = 0;
				bit_pos = 0;
				rc = gpp_sapa_hpac2buffer(phpac,psapa_handle, hpac_binary_buffer, &byte_pos, &bit_pos);				//add data to buffer

				GPPLONG last_bit_pos = total_bits(&byte_pos, &bit_pos);
				/*gpp_sapa_hpac_buffer_to_sapa_buffer(hpac_binary_buffer, last_bit_pos, ea_flag, message_crc_type, crc_frame, hpac_sapa_buffer);
				gpp_sapa_sapa_buffer_to_hpac_buffer(hpac_binary_buffer_recive, &rc, &ea_flag, &message_crc_type, &crc_frame, hpac_sapa_buffer);*/

				byte_pos = 0;
				bit_pos = 0;
				gpp_sapa_buffer2hpac(phpac_recive, hpac_binary_buffer, &byte_pos, &bit_pos);

				//gpp_sapa_debug_fprintf_hpac(phpac_recive, psapa_handle, fp);
				
			}//Data Read File if not null ends

		}//File Reade while ends
		printf("file successfully\n");
	}//fopen ends
	else
	{
		printf("%s", "The file could not be opened");
	}//else ends
	free(area_binary_buffer);
	free(area_binary_buffer_recive);
	free(area_sapa_buffer);
	free(hpac_binary_buffer);
	free(hpac_sapa_buffer);
	free(hpac_binary_buffer_recive);
}


void gpp_sapa_set_ocb_present_flags(GPPUINT1 *ref_obj, int index, int setvalue)
{
	if(setvalue == 1)
		*ref_obj = ((1 << index) | *ref_obj);

	//return ref_obj;
}

GPPUINT4 gpp_sapa_split_arg_to_tokens(char **_buffer, GPPUCHAR **tok)
{
	GPPUINT1 tok_pos = 0;
	GPPUCHAR *temp = NULL;

	temp = strtok(_buffer, " ,");
	while (temp != NULL)
	{
		tok[tok_pos++] = temp;
		temp = strtok(NULL, " ,");
	}
	return tok_pos;
}



GPPLONG total_bits(GPPLONG *byte, GPPLONG *bits)
{
	return (*byte*8)+*bits;
}



GPPUINT1 GetAreaIndex(int fn_arr[33], int size, int area_id)
{
	int i;
	for (i = 0; i < size; i++) {
		if (fn_arr[i] == area_id){
			return i;
		}
	}
	return 0;
}
