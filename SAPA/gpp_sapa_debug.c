#include <string.h>
#include "gpp_sapa.h"

//System ID
GPPCHAR gpp_sapa_system_id(GPPUINT1 sys)
{
	switch (sys){
		case 0: return 'G';
		case 1: return 'R';
	}
	return 'X';
}



void gpp_sapa_debug_fprintf_ocb(const GPP_SAPA_OCB *p_ocb, FILE *fp)
{
	GPPUINT1 isys, isat, sat, isig, sig;
	GPPUINT1 siglist[34]={0,};
	GPPUINT1 svlist[66]={0,};

	GPP_SAPA_OCB_HEADER *header=NULL;
	GPP_SAPA_OCB_SV		*sv=NULL;
	GPP_SAPA_OCB_SV_CLK	*clk=NULL;
	GPP_SAPA_OCB_SV_ORB	*orb=NULL;
	GPP_SAPA_OCB_SV_BIAS *bias = NULL;
	GPP_SAPA_OCB_SV_BIAS_PB *pb = NULL;
	GPP_SAPA_OCB_SV_BIAS_CB *cb = NULL;
	if (!fp) fp = stdout;

	for (isys = 0; isys < GPP_SAPA_MAX_SYS; isys++){
		GPPUINT1 sys;
		sys=isys;

		if(p_ocb->header_block){
			if(header=p_ocb->header_block[sys]){
				GPPUINT4 sec = header->time_tag;
				GPPT_WNT wn_t = {0,};

				wn_t.wn = SAPA_GPS_WEEK_20100101 + (sec / 604800);
				wn_t.t = SAPA_GPS_SEC_20100101 + (sec % 604800);
				INTRN_CORRECT_ROLLOVER(wn_t.wn, wn_t.t, 604800.0e0);

				fprintf(fp, "\n");
				fprintf(fp, "Time %04d %8.1f \n", wn_t.wn, wn_t.t);

				fprintf(fp, "\n");

				fprintf(fp, "%-25s %3d\n", "Solution ID", header->sol_id);
				fprintf(fp, "%-25s %3d\n", "Solution Processor ID", header->sol_processor_id);
				fprintf(fp, "%-25s %3d\n", "End Of Set", header->end_of_obc_set);
				fprintf(fp, "%-25s %3u\n", "Sol Issue Of Update", header->sol_issue_of_update);
				fprintf(fp, "%-25s %3d\n", "Yaw Flag", header->yaw_flag);
				fprintf(fp, "%-25s %3d\n", "Sat Ref Datum", header->sat_ref_datum);
				fprintf(fp, "%-25s %3d\n", "Ephemeris Type", header->ephemeris_type);
				fprintf(fp, "\n");
			}
		}//p_ocb->header_block

		gpp_sapa_get_svlist(p_ocb->sv_prn_bits[sys], svlist);

		for (isat=1; isat<=svlist[0]; isat++) {
			GPPUINT1 o_flag = 0;
			GPPUINT1 c_flag = 0;
			GPPUINT1 b_flag = 0;

			sat = svlist[isat];
			if(p_ocb->sv){
				if(sv=p_ocb->sv[sys][sat]){
					fprintf(fp, "%-25s\n", "OCB_SATELLITE_DATA:");
					fprintf(fp, " %1c%02d", gpp_sapa_system_id(sys), sat);		//Satellite ID
					fprintf(fp, " %1d", sv->do_not_use);		//Do Not Use

					gpp_sapa_get_ocb_flag_value(sv->ocb_bits, &o_flag, &c_flag, &b_flag);

					fprintf(fp, " %1d", o_flag);		//Orbit Flag
					fprintf(fp, " %1d", c_flag);		//Clock Flag
					fprintf(fp, " %1d", b_flag);		//Bias Flag

					fprintf(fp, " %7.1f", sv->continuity_indicator);			//Continuity Indicator

					if (o_flag){
						if(orb=sv->orb){
							fprintf(fp, " %3d", orb->iode);									//IODE
							
							fprintf(fp, " %7.5f", orb->orb_radial_correction);					//Correction
							fprintf(fp, " %7.5f", orb->orb_along_track_correction);					//Correction
							fprintf(fp, " %7.5f", orb->orb_cross_track_correction);					//Correction
							
							fprintf(fp, " %6.3f", orb->sat_yaw);								//Satellite Yaw
						}
						else{
							fprintf(fp, " %5s %7s %7s %7s %6s", "n/a", "n/a", "n/a", "n/a", "n/a");
						}
					}

					if(c_flag){
						if(clk=sv->clk){
							fprintf(fp, " %7.1f", clk->iode_continuity);
							fprintf(fp, " %7.3f", clk->clk_correction);
							if(clk->user_range_error >= 0){
								fprintf(fp, " %7.2f", clk->user_range_error);
							}
							else{
								fprintf(fp, "%7s", "n/a");
							}
						}
						else{
							fprintf(fp, " %7s %7s %5s", "n/a", "n/a", "n/a");
						}
						fprintf(fp, "\n");
					}//c_flag
				}//sv->sv[sys][sat]
			}//p_ocb->sv

				if(b_flag)
				{
					if (bias = sv->bias) {
						fprintf(fp, "%-25s\n", "OCB_SATPHASE_BIAS:");
						gpp_sapa_get_siglist(bias->pb_sig_bits, siglist);
						for (isig = 1; isig <= siglist[0]; isig++)
						{
							sig = siglist[isig];
							fprintf(fp, " %2d(P)", sig);
							if (pb = bias->pb[sig])
							{
								fprintf(fp, " %1d", pb->fix_flag);
								fprintf(fp, " %6.1f", pb->countinity_indicator);
								fprintf(fp, " %7.3f", pb->pb_correction);
							}

						}//isig

						fprintf(fp, "\n");
						fprintf(fp, "%-25s\n", "OCB_SATCODE_BIAS:");
						gpp_sapa_get_siglist(bias->cb_sig_bits, siglist);
						for (isig = 1; isig <= siglist[0]; isig++)
						{
							sig = siglist[isig];
							fprintf(fp, " %2d(C)", sig);
							if (cb = bias->cb[sig])
							{
								fprintf(fp, " %7.3f", cb->cb_correction);
							}
						}//isig
					}
					
				}
				fprintf(fp, "\n");
		}//isat
	}//isys
}//sapa_fprintf_ocb()


void gpp_sapa_debug_fprintf_area(pGPP_SAPA_AREA p_area, FILE *fp)
{
	GPP_SAPA_AREA_DEF_HEADER *header=NULL;
	GPP_SAPA_AREA_DEF_BLOCK *area_def=NULL;
	if (!fp) fp = stdout;

	if (p_area->header_block)
	{
		if (header = p_area->header_block)
		{
			fprintf(fp, "\n");
			fprintf(fp, "\nAREA \n");
			fprintf(fp, "\n");

			fprintf(fp, "%-25s %2d\n", "Message Sub-Type", header->message_sub_type);
			fprintf(fp, "%-25s %3lu\n", "Solution ID", header->sol_id);
			fprintf(fp, "%-25s %2lu\n", "Solution Processor ID", header->sol_processor_id);
			fprintf(fp, "%-25s %3lu\n", "Sol Issue Of Update", header->sol_issue_of_update);
			fprintf(fp, "%-25s %2d\n", "Area Count", header->area_count);
			fprintf(fp, "\n");
		}
	}//p_area->header_block

	if (p_area->area_def_block)
	{
		GPPUINT1 area_count, iarea;
		area_count = p_area->header_block->area_count;
		for (iarea = 0; iarea < area_count; iarea++) {
			GPPUINT1 ai = iarea;
			if (area_def = p_area->area_def_block[ai])
			{
				fprintf(fp, "%-25s\n", "ATM_AREA_DEF:");
				fprintf(fp, " %2lu", area_def->area_id);											//Area ID
				fprintf(fp, " %7.5f", area_def->area_ref_lat);										//Area Reference Latitude
				fprintf(fp, " %7.5f", area_def->area_ref_long);									//Area Reference Longitude
				fprintf(fp, " %2d", area_def->area_lat_grid_node_count);							//Area Latitude Grid Node Count
				fprintf(fp, " %2d", area_def->area_long_grid_node_count);							//Area Longitude Grid Node Count
				fprintf(fp, " %7.5f", area_def->area_lat_grid_node_spacing);						//Area Latitude Grid Node Spacing
				fprintf(fp, " %7.5f", area_def->area_long_grid_node_spacing);						//Area Longitude Grid Node Spacing
				fprintf(fp, "\n");
			}
		}
		fprintf(fp, "\n");
	}//p_area->area_def_block
		
}//sapa_fprintf_area()

void gpp_sapa_debug_fprintf_hpac(pGPP_SAPA_HPAC p_hpac, SAPA_HPAC_HANDLE *hpacHdl, FILE *fp)
{
	GPP_SAPA_HPAC_HEADER *header = NULL;
	GPP_SAPA_HPAC_ATMO_BLOCK *atmo_block = NULL;
	GPP_SAPA_HPAC_AREA *area_def = NULL;
	GPP_SAPA_HPAC_TROPO_POLY_COEFFICIENT_BLOCK *tropo_poly_coeff = NULL;
	GPP_SAPA_HPAC_TROPO_GRID_BLOCK *tropo_grid = NULL;
	GPP_SAPA_HPAC_IONO *iono_block = NULL;
	GPP_SAPA_HPAC_IONO_SAT_POLY *iono_poly = NULL;
	GPP_SAPA_HPAC_IONO_SAT_COEFFICIENT	*iono_coeff = NULL;
	GPP_SAPA_HPAC_IONO_GRID_BLOCK *iono_grid = NULL;
	GPPUINT1 svlist[66]={0,};

	if (!(fp)) fp = stdout;

	if (p_hpac->header_block)
	{
		fprintf(fp, "\n");
		fprintf(fp, "\nHPAC \n");
		if (header = p_hpac->header_block)
		{
			GPPUINT4 sec = header->time_tag;
			GPPT_WNT wn_t = { 0, };

			wn_t.wn = SAPA_GPS_WEEK_20100101 + (sec / 604800);
			wn_t.t = SAPA_GPS_SEC_20100101 + (sec % 604800);
			INTRN_CORRECT_ROLLOVER(wn_t.wn, wn_t.t, 604800.0e0);

			fprintf(fp, "\n");
			fprintf(fp, "Time %04d %8.1f \n", wn_t.wn, wn_t.t);
			fprintf(fp, "\n");

			fprintf(fp, "%-25s %3lu\n", "Solution ID", header->sol_id);
			fprintf(fp, "%-25s %2lu\n", "Solution Processor ID", header->sol_processor_id);
			fprintf(fp, "%-25s %3lu\n", "Sol Issue Of Update", header->sol_issue_of_update);
			fprintf(fp, "%-25s %2d\n", "Sol Area Of Count", header->area_count);
		}
	
	}
	if(p_hpac->atmo)
	{
		GPPUINT1 iarea, area_count;
		area_count = p_hpac->header_block->area_count;
		for (iarea = 0; iarea < area_count; iarea++) {
			GPPUINT1 ai = iarea;
			if (atmo_block = p_hpac->atmo[ai])
			{
				if (area_def = atmo_block->area_def) {
					fprintf(fp, "\n");
					fprintf(fp, "%-25s\n", "ATM_HPAC_COMMON_DATA:");
					fprintf(fp, " %3d", area_def->area_id);								//Area ID
					fprintf(fp, " %2d", area_def->number_of_grid_point);					//Number of Grid Point
					fprintf(fp, " %1d", area_def->tropo_block_indicator);					//Tropo Block Indicator
					fprintf(fp, " %1d", area_def->iono_block_indicator);					//Iono Block Indicator
				}
				if(atmo_block->tropo)
				if (tropo_poly_coeff = atmo_block->tropo->tropo_poly_coeff_block){
						fprintf(fp, "\n");
					fprintf(fp, "%-25s\n", "ATM_TROPO_DATA:");
					fprintf(fp, " %1d", tropo_poly_coeff->tropo_equation_type);			//Tropo Equation Type
					fprintf(fp, " %7.3f", tropo_poly_coeff->tropo_quality);				//Tropo Quantity
					fprintf(fp, " %7.3f", tropo_poly_coeff->tropo_avhd);				//Area Average Ver Hydro

					fprintf(fp, " %7.3f", tropo_poly_coeff->tropo_poly_coeff[TROPO_POLY_COEFF_INDX_T00]);//Tropo Poly Coeff
					fprintf(fp, " %7.3f", tropo_poly_coeff->tropo_poly_coeff[TROPO_POLY_COEFF_INDX_T01]);//Tropo Poly Coeff
					fprintf(fp, " %7.3f", tropo_poly_coeff->tropo_poly_coeff[TROPO_POLY_COEFF_INDX_T10]);//Tropo Poly Coeff
					fprintf(fp, " %7.3f", tropo_poly_coeff->tropo_poly_coeff[TROPO_POLY_COEFF_INDX_T11]);//Tropo Poly Coeff
				}
				if (atmo_block->tropo) {
					if (atmo_block->tropo->tropo_grid) {
						if (tropo_grid = atmo_block->tropo->tropo_grid) {
							GPPUINT1 ig, no_of_grid;
							no_of_grid = p_hpac->atmo[ai]->area_def->number_of_grid_point;
							for (ig = 0; ig < no_of_grid; ig++)
							{
								fprintf(fp, " %7.3f", tropo_grid->tropo_residuals[ig]);			//Tropo Grid Residual
							}
						}
					}
				}
				fprintf(fp, "\n");
				if(iono_block =atmo_block->iono)
				fprintf(fp, " %1d", iono_block->iono_equation_type);							//Iono Equaction Type

				GPPUINT1 isys, syslist[18] = { 0, };

				gpp_sapa_get_syslist(hpacHdl->hpacIonoHdl[ai]->sys_bits, syslist);				//Convert from bits to SYS ID
				for (isys = 1; isys <= syslist[0]; isys++) {
					GPPUINT1 sys;
					sys = syslist[isys];

					gpp_sapa_get_svlist(iono_block->sat_prn_bits[sys], svlist);
					GPPUINT1 isat;
					for (isat = 1; isat <= svlist[0]; isat++) {
						GPPUINT1 sat;
						sat = svlist[isat];
						fprintf(fp, "\n");
						fprintf(fp, "%-25s\n", "ATM_IONOSAT_DATA:");
						fprintf(fp, " %1c%03d", gpp_sapa_system_id(sys), sat);		//Satellite ID
						if (iono_poly = iono_block->iono_sat_block[sys][sat]->iono_sat_poly)
						{
							fprintf(fp, " %7.3f", iono_poly->iono_quality);	//Iono Quality
						}
						if (iono_coeff = iono_block->iono_sat_block[sys][sat]->iono_sat_coeff) {
							fprintf(fp, " %7.3f", iono_coeff->iono_poly_coeff[IONO_POLY_COEFF_INDX_C00]);	//Iono ply coeff
							fprintf(fp, " %7.3f", iono_coeff->iono_poly_coeff[IONO_POLY_COEFF_INDX_C01]);
							fprintf(fp, " %7.3f", iono_coeff->iono_poly_coeff[IONO_POLY_COEFF_INDX_C10]);
							fprintf(fp, " %7.3f", iono_coeff->iono_poly_coeff[IONO_POLY_COEFF_INDX_C11]);
						}
						if(iono_grid=iono_block->iono_sat_block[sys][sat]->iono_grid)
						{
							GPPUINT1 ig, no_of_grid;
							no_of_grid = p_hpac->atmo[ai]->area_def->number_of_grid_point;
							for (ig = 0; ig < no_of_grid; ig++)
							{
								fprintf(fp, " %7.2f", iono_grid->iono_residuals[ig]);
							}
						}
					}
				}
			}
			fprintf(fp, "\n");
		}
	}
			

	
}//sapa_fprintf_hpac()
