#include <string.h>
#include "gpp_sapa.h"

void gpp_sapa_debug_fprintf_ocb(pGPP_SAPA_OCB p_ocb, FILE *fp)
{
	GPPUINT1 isys, sys, isat, sat, isig, sig;
	GPPUINT1 siglist[34] = { 0, };

	if (!fp) fp = stdout;


	for (isys = 0; isys < GPP_SAPA_MAX_CONS; isys++)
	{
		if (p_ocb->header_block[isys])
		{
			GPPUINT4 sec = p_ocb->header_block[isys]->time_tag;
			GPPT_WNT wn_t = { 0, };

			wn_t.wn = SAPA_GPS_WEEK_20100101 + (sec / 604800);
			wn_t.t = SAPA_GPS_SEC_20100101 + (sec % 604800);
			INTRN_CORRECT_ROLLOVER(wn_t.wn, wn_t.t, 604800.0e0);

			fprintf(fp, "\n");
			fprintf(fp, "Time %04d %8.1f \n", wn_t.wn, wn_t.t);
			sys = isys;

			fprintf(fp, "\n");

			fprintf(fp, "%-25s %3d\n", "Solution ID", p_ocb->header_block[isys]->sol_id);
			fprintf(fp, "%-25s %2ul\n", "Solution Processor ID", p_ocb->header_block[isys]->sol_processor_id);
			fprintf(fp, "%-25s %1d\n", "End Of Set", p_ocb->header_block[isys]->end_of_obc_set);
			fprintf(fp, "%-25s %3u\n", "Sol Issue Of Update", p_ocb->header_block[isys]->sol_issue_of_update);
			fprintf(fp, "%-25s %1d\n", "Yaw Flag", p_ocb->header_block[isys]->yaw_flag);
			fprintf(fp, "%-25s %1d\n", "Sat Ref Datum", p_ocb->header_block[isys]->sat_ref_datum);
			fprintf(fp, "%-25s %1d\n", "Ephemeris Type", p_ocb->header_block[isys]->ephemeris_type);
			fprintf(fp, "\n");

			GPPUINT1 svlist[66] = { 0, };
			printf("SV_BITS: %llu  ...", p_ocb->sv_prn_bits[sys]);
			gpp_sapa_get_svlist(p_ocb->sv_prn_bits[sys], svlist);

			for (isat = 1; isat <= svlist[0]; isat++) {
				sat = svlist[isat];
				GPPUINT1 o_flag = 0;
				GPPUINT1 c_flag = 0;
				GPPUINT1 b_flag = 0;
				fprintf(fp, "%-25s\n", "OCB_SATELLITE_DATA:");
				fprintf(fp, " %1c%03d", gpp_sapa_system_id(sys), sat);		//Satellite ID
				fprintf(fp, " %1d", p_ocb->sv[sys][sat]->do_not_use);		//Do Not Use

				gpp_sapa_get_ocb_flag_value(p_ocb->sv[sys][sat]->ocb_present_flag, &o_flag, &c_flag, &b_flag);

				fprintf(fp, " %1d", o_flag);		//Orbit Flag
				fprintf(fp, " %1d", c_flag);		//Clock Flag
				fprintf(fp, " %1d", b_flag);		//Bias Flag

				fprintf(fp, " %7.1f", p_ocb->sv[sys][sat]->continuity_indicator);			//Continuity Indicator

				if (o_flag == 1)
				{
					fprintf(fp, " %3d", p_ocb->sv[sys][sat]->orb->iode);									//IODE
					fprintf(fp, " %7.5f", p_ocb->sv[sys][sat]->orb->orb_radial_correction);					//Radial Correction
					fprintf(fp, " %7.5f", p_ocb->sv[sys][sat]->orb->orb_along_track_correction);			//Along Track Correction
					fprintf(fp, " %7.5f", p_ocb->sv[sys][sat]->orb->orb_cross_track_correction);			//Cross Track Correction
					fprintf(fp, " %6.3f", p_ocb->sv[sys][sat]->orb->sat_yaw);								//Satellite Yaw
				}
				else
				{
					fprintf(fp, " %5s %7s %7s %7s %6s", "n/a", "n/a", "n/a", "n/a", "n/a");
				}

				if (c_flag == 1)
				{
					fprintf(fp, " %7.1f", p_ocb->sv[sys][sat]->clk->iode_continuity);
					fprintf(fp, " %7.3f", p_ocb->sv[sys][sat]->clk->clk_correction);
					if (p_ocb->sv[sys][sat]->clk->user_range_error >= 0)
					{
						fprintf(fp, " %7.2f", p_ocb->sv[sys][sat]->clk->user_range_error);
					}
					else
					{
						fprintf(fp, "%7s", "n/a");
					}
				}
				else
				{
					fprintf(fp, " %7s %7s %5s", "n/a", "n/a", "n/a");
				}

				fprintf(fp, "\n");

				if (b_flag == 1)
				{
					fprintf(fp, "%-25s\n", "OCB_SATPHASE_BIAS:");
					gpp_sapa_get_siglist(p_ocb->sv[sys][sat]->bias->pb_sig_bits, siglist);
					for (isig = 1; isig <= siglist[0]; isig++)
					{
						sig = siglist[isig];

						fprintf(fp, " %2d(P)", sig);
						fprintf(fp, " %1d", p_ocb->sv[sys][sat]->bias->pb[sig]->fix_flag);
						fprintf(fp, " %6.1f", p_ocb->sv[sys][sat]->bias->pb[sig]->countinity_indicator);
						fprintf(fp, " %7.3f", p_ocb->sv[sys][sat]->bias->pb[sig]->pb_correction);

					}//isig

					fprintf(fp, "\n");
					fprintf(fp, "%-25s\n", "OCB_SATCODE_BIAS:");
					gpp_sapa_get_siglist(p_ocb->sv[sys][sat]->bias->cb_sig_bits, siglist);
					for (isig = 1; isig <= siglist[0]; isig++)
					{
						sig = siglist[isig];

						fprintf(fp, " %2d(C)", sig);
						fprintf(fp, " %7.3f", p_ocb->sv[sys][sat]->bias->cb[sig]->cb_correction);
					}//isig
				}
				fprintf(fp, "\n");
			}
		}
	}
}//sapa_fprintf_ocb()


void gpp_sapa_debug_fprintf_area(pGPP_SAPA_AREA p_area, FILE *fp)
{
	if (!fp) fp = stdout;

	if (p_area->header_block)
	{
		GPPUINT1 area_count, iarea;
		fprintf(fp, "\n");
		fprintf(fp, "AREA \n");
		fprintf(fp, "\n");

		fprintf(fp, "%-25s %2d\n", "Message Sub-Type", p_area->header_block->message_sub_type);
		fprintf(fp, "%-25s %3lu\n", "Solution ID", p_area->header_block->sol_id);
		fprintf(fp, "%-25s %2lu\n", "Solution Processor ID", p_area->header_block->sol_processor_id);
		fprintf(fp, "%-25s %3lu\n", "Sol Issue Of Update", p_area->header_block->sol_issue_of_update);

		area_count = p_area->header_block->area_count;
		fprintf(fp, "%-25s %2d\n", "Area Count", p_area->header_block->area_count);
		fprintf(fp, "\n");


		for (iarea = 0; iarea < area_count; iarea++) {
			GPPUINT1 ai = iarea;
			fprintf(fp, "%-25s\n", "ATM_AREA_DEF:");
			fprintf(fp, " %2lu", p_area->area_def_block[ai]->area_id);											//Area ID
			fprintf(fp, " %7.5f", p_area->area_def_block[ai]->area_ref_lat);										//Area Reference Latitude
			fprintf(fp, " %7.5f", p_area->area_def_block[ai]->area_ref_long);									//Area Reference Longitude
			fprintf(fp, " %2d", p_area->area_def_block[ai]->area_lat_grid_node_count);							//Area Latitude Grid Node Count
			fprintf(fp, " %2d", p_area->area_def_block[ai]->area_long_grid_node_count);							//Area Longitude Grid Node Count
			fprintf(fp, " %7.5f", p_area->area_def_block[ai]->area_lat_grid_node_spacing);						//Area Latitude Grid Node Spacing
			fprintf(fp, " %7.5f", p_area->area_def_block[ai]->area_long_grid_node_spacing);						//Area Longitude Grid Node Spacing
			fprintf(fp, "\n");
		}
	}	
}//sapa_fprintf_area()

void gpp_sapa_debug_fprintf_hpac(pGPP_SAPA_HPAC p_hpac, FILE *fp)
{
	if (!(fp)) fp = stdout;

	if (p_hpac->header_block)
	{
		fprintf(fp, "\n");
		fprintf(fp, "HPAC \n");
		fprintf(fp, "\n");
		
		if (p_hpac->header_block)
		{
			GPPUINT1 iarea, area_count;
			GPPUINT4 sec = p_hpac->header_block->time_tag;
			GPPT_WNT wn_t = { 0, };

			wn_t.wn = SAPA_GPS_WEEK_20100101 + (sec / 604800);
			wn_t.t = SAPA_GPS_SEC_20100101 + (sec % 604800);
			INTRN_CORRECT_ROLLOVER(wn_t.wn, wn_t.t, 604800.0e0);

			fprintf(fp, "\n");
			fprintf(fp, "Time %04d %8.1f \n", wn_t.wn, wn_t.t);
			fprintf(fp, "\n");

			fprintf(fp, "%-25s %3lu\n", "Solution ID", p_hpac->header_block->sol_id);
			fprintf(fp, "%-25s %2lu\n", "Solution Processor ID", p_hpac->header_block->sol_processor_id);
			fprintf(fp, "%-25s %3lu\n", "Sol Issue Of Update", p_hpac->header_block->sol_issue_of_update);
			area_count = p_hpac->header_block->area_count;
			fprintf(fp, "%-25s %2d\n", "Sol Area Of Count", area_count);
				
			for (iarea = 0; iarea < area_count; iarea++) {
				GPPUINT1 ai = iarea;
				fprintf(fp, "\n");
				fprintf(fp, "%-25s\n", "ATM_HPAC_COMMON_DATA:");
				fprintf(fp, " %3d", p_hpac->atmo[ai]->area_def->area_id);								//Area ID
				fprintf(fp, " %2d", p_hpac->atmo[ai]->area_def->number_of_grid_point);					//Number of Grid Point
				fprintf(fp, " %1d", p_hpac->atmo[ai]->area_def->tropo_block_indicator);					//Tropo Block Indicator
				fprintf(fp, " %1d", p_hpac->atmo[ai]->area_def->iono_block_indicator);					//Iono Block Indicator
					
				fprintf(fp, "\n");
				fprintf(fp, "%-25s\n", "ATM_TROPO_DATA:");
				fprintf(fp, " %1d", p_hpac->atmo[ai]->tropo->tropo_poly_coeff_block->tropo_equation_type);			//Tropo Equation Type
				fprintf(fp, " %7.3f", p_hpac->atmo[ai]->tropo->tropo_poly_coeff_block->tropo_quality);				//Tropo Quantity
				fprintf(fp, " %7.3f", p_hpac->atmo[ai]->tropo->tropo_poly_coeff_block->tropo_avhd);				//Area Average Ver Hydro
				//fprintf(fp, " %1d", p_hpac->atmo[ai]->tropo->tropo_block->tropo_coeff_size);			//Tropo Poly coeff size

				fprintf(fp, " %7.3f", p_hpac->atmo[ai]->tropo->tropo_poly_coeff_block->tropo_poly_coeff[TROPO_POLY_COEFF_INDX_T00]);//Tropo Poly Coeff
				fprintf(fp, " %7.3f", p_hpac->atmo[ai]->tropo->tropo_poly_coeff_block->tropo_poly_coeff[TROPO_POLY_COEFF_INDX_T01]);//Tropo Poly Coeff
				fprintf(fp, " %7.3f", p_hpac->atmo[ai]->tropo->tropo_poly_coeff_block->tropo_poly_coeff[TROPO_POLY_COEFF_INDX_T10]);//Tropo Poly Coeff
				fprintf(fp, " %7.3f", p_hpac->atmo[ai]->tropo->tropo_poly_coeff_block->tropo_poly_coeff[TROPO_POLY_COEFF_INDX_T11]);//Tropo Poly Coeff

				//fprintf(fp, " %1d", p_hpac->atmo[ai]->tropo->tropo_grid->tropo_residual_size);			//Tropo Residual Field Size
				GPPUINT1 ig, no_of_grid;
				no_of_grid = p_hpac->atmo[ai]->area_def->number_of_grid_point;
				for(ig=0;ig< no_of_grid;ig++)
				{ 
					fprintf(fp, " %7.3f", p_hpac->atmo[ai]->tropo->tropo_grid->tropo_residuals[ig]);			//Tropo Grid Residual
				}

					
				fprintf(fp, " %1d", p_hpac->atmo[iarea]->iono->iono_equation_type);							//Iono Equaction Type
				//fprintf(fp, " %7.3f", p_hpac->atmo[iarea]->iono->sat_prn_bits);							//Satellite prn bits 
				GPPUINT1 svlist[66] = { 0, };
				GPPUINT1 isys, isat;
				for (isys = 0; isys < 2; isys++)				//isys < 2    for testing (GPP_SAPA_MAX_CONS)
				{
					GPPUINT1 sys;
					sys = isys;
					gpp_sapa_get_svlist(p_hpac->atmo[ai]->iono->sat_prn_bits[sys], svlist);
					for (isat = 1; isat <= svlist[0]; isat++) {
						GPPUINT1 sat = svlist[isat];
						fprintf(fp, "\n");
						fprintf(fp, "%-25s\n", "ATM_IONOSAT_DATA:");
						fprintf(fp, " %1c%03d", gpp_sapa_system_id(sys), sat);		//Satellite ID
						fprintf(fp, " %7.3f", p_hpac->atmo[ai]->iono->iono_sat_block[sys][sat]->iono_sat_poly->iono_quality);	//Iono Quality
						//fprintf(fp, " %1d", p_hpac->atmo[iarea]->iono->iono_sat_block[sat]->iono_sat_poly->iono_coeff_size);	//Iono ply coeff
						fprintf(fp, " %7.3f", p_hpac->atmo[ai]->iono->iono_sat_block[sys][sat]->iono_sat_coeff->iono_poly_coeff[IONO_POLY_COEFF_INDX_C00]);	//Iono ply coeff
						fprintf(fp, " %7.3f", p_hpac->atmo[ai]->iono->iono_sat_block[sys][sat]->iono_sat_coeff->iono_poly_coeff[IONO_POLY_COEFF_INDX_C01]);
						fprintf(fp, " %7.3f", p_hpac->atmo[ai]->iono->iono_sat_block[sys][sat]->iono_sat_coeff->iono_poly_coeff[IONO_POLY_COEFF_INDX_C10]);
						fprintf(fp, " %7.3f", p_hpac->atmo[ai]->iono->iono_sat_block[sys][sat]->iono_sat_coeff->iono_poly_coeff[IONO_POLY_COEFF_INDX_C11]);
						//fprintf(fp, " %1d", p_hpac->atmo[sys][iarea]->iono->iono_sat_block[sat]->iono_grid->iono_residual_field_size);

						for (ig = 0; ig < no_of_grid; ig++)
						{
							fprintf(fp, " %7.2f", p_hpac->atmo[ai]->iono->iono_sat_block[sys][sat]->iono_grid->iono_residuals[ig]);
						}
					}
				}
			}
		}
		
	}
}//sapa_fprintf_hpac()
