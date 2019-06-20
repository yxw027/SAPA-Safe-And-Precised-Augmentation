//structures for qzss

//COMPACT SSR MASK

typedef struct SSR_MASK_MSG_HEADER
{
	GPPUINT2		msg_number;
	GPPUINT1		msg_sub_type_id;
	GPPUINT4		gns_hourly_epoch_time;
	GPPUINT1		ssr_update_interval;
	GPPUINT1		multiple_msg_indicator;
	GPPUINT1		iod_ssr;
	GPPUINT1		no_of_gnss;
}SSR_MASK_MSG_HEADER,*pSSR_MASK_MSG_HEADER;

typedef struct SSR_MASK_SPEC_PART
{
	GPPUINT1		gnss_id_1;
	GPPUINT8		compact_ssr_satellite_mask_1;
	GPPUINT2	    compact_ssr_signal_mask_1;
	GPPUINT1		cell_mask_availability_flag;
	GPPUINT			compact_ssr_cell_mask_1;
	GPPUINT1		gnss_id_nsys;
	GPPUINT8		compact_ssr_satellite_mask_nsys;
	GPPUINT2		compact_ssr_signal_mask_nsys;
	GPPUINT1		cell_mask_availability_flag;
	GPPUINT			compact_ssr_cell_mas_nsys;

}SSR_MASK_SPEC_PART,*pSSR_MASK_SPEC_PART;

typedef struct SSR_MASK
{
	pSSR_MASK_MSG_HEADER		header;
	pSSR_MASK_SPEC_PART			spec_part;

}SSR_MASK, *pSSR_MASK;


//COMPACT SSR GNSS ORBIT CORRECTION

typedef struct SSR_GNSS_ORB_MSG_HEADER
{
	GPPUINT2		msg_number;
	GPPUINT1		msg_sub_type_id;
	GPPUINT2		gns_hourly_epoch_time;
	GPPUINT1		ssr_update_interval;
	GPPUINT1		multiple_msg_indicator;
	GPPUINT1		iod_ssr;
}SSR_GNSS_ORB_MSG_HEADER,*pSSR_GNSS_ORB_MSG_HEADER;

typedef struct SSR_GNSS_ORB_SPEC_PART
{
	GPPUINT2	gnss_iode;
	GPPDOUBLE	compact_ssr_delta_radian;
	GPPDOUBLE	compact_ssr_delta_alongtrack;
	GPPDOUBLE	compact_ssr_delta_crosstrack;
	GPPUINT2	gnss_iode_sv_nsat;
	GPPDOUBLE	compact_ssr_delta_radial_sv_nsat;
	GGuDOUBLE	compact_ssr_delta_alongtrack_sv_nsat;
	GPPDOUBLE	compact_ssr_delta_crosstrack_sv_nsat;
}SSR_GNSS_ORB_SPEC_PART,*pSSR_GNSS_ORB_SPEC_PART;

typedef struct SSR_GNSS_ORB
{
	pSSR_GNSS_ORB_MSG_HEADER		header;
	pSSR_GNSS_ORB_SPEC_PART			spec_part;
}SSR_GNSS_ORB,*pSSR_GNSS_ORB;


//COMPACT SSR GNSS CLOCK CORRECTION

typedef struct SSR_GNSS_CLK_HEADER
{
	GPPUINT2		msg_number;
	GPPUINT1		msg_sub_type_id;
	GPPUINT2		gns_hourly_epoch_time;
	GPPUINT1		ssr_update_interval;
	GPPUINT1		multiple_msg_indicator;
	GPPUINT1		iod_ssr;
}SSR_GNSS_CLK_HEADER,*pSSR_GNSS_CLK_HEADER;

typedef struct SSR_GNSS_CLK_SPEC_PART
{
	GPPDOUBLE		compact_ssr_delta_clock_c0;
	GPPDOUBLE		compact_ssr_delta_clock_c0_nsat;
}SSR_GNSS_CLK_SPEC_PART,*pSSR_GNSS_CLK_SPEC_PART;

typedef struct SSR_GNSS_CLK
{
	pSSR_GNSS_CLK_HEADER			header;
	pSSR_GNSS_CLK_SPEC_PART			spec_part;
}SSR_GNSS_CLK, *pSSR_GNSS_CLK;


//COMPACT SSR GNSS SATELLITE CODE BIAS

typedef struct SSR_GNSS_SAT_CODE_BIAS_HEADER
{
	GPPUINT2		msg_number;
	GPPUINT1		msg_sub_type_id;
	GPPUINT4		gns_hourly_epoch_time;
	GPPUINT1		ssr_update_interval;
	GPPUINT1		multiple_msg_indicator;
	GPPUINT1		iod_ssr;
}SSR_GNSS_SAT_CODE_BIAS_HEADER, *pSSR_GNSS_SAT_CODE_BIAS_HEADER;

typedef struct SSR_GNSS_SAT_CODE_BIAS_SPEC_PART
{
	GPPDOUBLE		compact_ssr_code_bias_1;
	GPPDOUBLE		compact_ssr_coded_bias_ncode;
	GPPDOUBLE		compact_ssr_code_bias_1_nsat;
	GPPDOUBLE		compact_ssr_code_bias_ncode_nsat;

}SSR_GNSS_SAT_CODE_BIAS_SPEC_PART,*pSSR_GNSS_SAT_CODE_BIAS_SPEC_PART;

typedef struct SSR_GNSS_SAT_CODE_BIAS
{
	pSSR_GNSS_SAT_CODE_BIAS_HEADER			header;
	pSSR_GNSS_SAT_CODE_BIAS_SPEC_PART		spec_part;
}SSR_GNSS_SAT_CODE_BIAS, *pSSR_GNSS_SAT_CODE_BIAS;


//COMPACT SSR GNSS SATELLITE PHASE BIAS

typedef struct SSR_GNSS_SAT_PHASE_BIAS_HEADER
{
	GPPUINT2		msg_number;
	GPPUINT1		msg_sub_type_id;
	GPPUINT4		gns_hourly_epoch_time;
	GPPUINT1		ssr_update_interval;
	GPPUINT1		multiple_msg_indicator;
	GPPUINT1		iod_ssr;
}SSR_GNSS_SAT_PHASE_BIAS_HEADER, *pSSR_GNSS_SAT_PHASE_BIAS_HEADER;

typedef struct SSR_GNSS_SAT_PHASE_BIAS_SPEC_PART
{
	GPPDOUBLE		compact_ssr_phase_bias_1;
	GPPUINT1		compact_ssr_phase_discontinuity_indicator_1;
	GPPDOUBLE		compact_ssr_phase_bias_nphase;
	GPPUINT1		compact_ssr_phase_discontinuity_indicator_sphase;
	GPPDOUBLE		compact_ssr_phase_bias_1_nsat;
	GPPUINT1		compact_ss_phase_discontinuity_indiactor_1_nsat;
	GPPDOUBLE		compact_ssr_phase_bias_nphase_nsat;
	GPPUINT1		compact_ssr_phase_discontinioty_indiactator_nphase_nsat;

}SSR_GNSS_SAT_PHASE_BIAS_SPEC_PART,*pSSR_GNSS_SAT_PHASE_BIAS_SPEC_PART;

typedef struct SSR_GNSS_SAT_PHASE_BIAS
{
	pSSR_GNSS_SAT_PHASE_BIAS_HEADER			header;
	pSSR_GNSS_SAT_PHASE_BIAS_SPEC_PART		spec_part;

}SSR_GNSS_SAT_PHASE_BIAS, *pSSR_GNSS_SAT_PHASE_BIAS;


//COMPACT SSR GNSS SATELLITE CODE AND PHASE BIAS

typedef struct SSR_GNSS_SAT_CODE_PHASE_BIAS_HEADER
{
	GPPUINT2		msg_number;
	GPPUINT1		msg_sub_type_id;
	GPPUINT4		gns_hourly_epoch_time;
	GPPUINT1		ssr_update_interval;
	GPPUINT1		multiple_msg_indicator;
	GPPUINT1		iod_ssr;
	GPPUINT1		code_bias_existing_flag;
	GPPUINT1		phase_bias_existing_flag;
	GPPUINT1		network_bias_correction;
	GPPUINT1		compact_network_id;
	GPPUINT			network_sv_mask;
}SSR_GNSS_SAT_CODE_PHASE_BIAS_HEADER,*pSSR_GNSS_SAT_CODE_PHASE_BIAS_HEADER;

typedef struct SSR_GNSS_SAT_CODE_PHASE_BIAS_SPEC_PART
{
	GPPDOUBLE		compact_ssr_code_bias_1;
	GPPDOUBLE		compact_ssr_phase_bias_1;
	GPPUINT1		compact_ssr_phase_discontinuity_indicator_1;
	GPPDOUBLE		compact_ssr_code_bias_ncode;
	GPPDOUBLE		compact_ssr_phase_bias_nphase;
	GPPUINT1		compact_ssr_phase_discontinuity_indiacator_nphase;
	GPPDOUBLE		compact_ssr_code_bias_1_sv2;
	GPPDOUBLE		compact_ssr_phase_bias_1_sv2;
	GPPUINT1		compact_ssr_phase_discontinuity_indicator_1_sv2;
	GPPDOUBLE		compact_ssr_code_bias_ncode_nsat;
	GPPDOUBLE		compact_ssr_phase_bias_nphase_nsat;
	GPPUINT1		compact_ssr_phase_discontinuity_indicator_nphase_nsat;
	

}SSR_GNSS_SAT_CODE_PHASE_BIAS_SPEC_PART,*pSSR_GNSS_SAT_CODE_PHASE_BIAS_SPEC_PART;

typedef struct SSR_GNSS_SAT_CODE_PHASE_BIAS
{
	pSSR_GNSS_SAT_CODE_PHASE_BIAS_HEADER			header;
	pSSR_GNSS_SAT_CODE_PHASE_BIAS_SPEC_PART			spec_part;
}SSR_GNSS_SAT_CODE_PHASE_BIAS, *pSSR_GNSS_SAT_CODE_PHASE_BIAS;


//COMPACT SSR GNSS URA

typedef struct SSR_GNSS_URA_HEADER
{
	GPPUINT2		msg_number;
	GPPUINT1		msg_sub_type_id;
	GPPUINT4		gns_hourly_epoch_time;
	GPPUINT1		ssr_update_interval;
	GPPUINT1		multiple_msg_indicator;
	GPPUINT1		iod_ssr;
}SSR_GNSS_URA_HEADER, *pSSR_GNSS_URA_HEADER;

typedef struct SSR_GNSS_URA_SPEC_PART
{
	GPPUINT1		ssr_ura;
	GPPUINT1		ssr_ura_nsat;

}SSR_GNSS_URA_SPEC_PART, *pSSR_GNSS_URA_SPEC_PART;


typedef struct SSR_GNSS_URA
{
	pSSR_GNSS_URA_HEADER			header;
	pSSR_GNSS_URA_SPEC_PART			spec_part;
}SSR_GNSS_URA,*pSSR_GNSS_URA;


//COMPACT SSR STEC CORRECTION

typedef struct STEC_RESIDUAL_CORRECTION_RANGE_0
{
	GPPDOUBLE		stec_residual_correction;

}STEC_RESIDUAL_CORRECTION_RANGE_0, * pSTEC_RESIDUAL_CORRECTION_RANGE_0;


typedef struct STEC_RESIDUAL_CORRECTION_RANGE_1
{
	GPPDOUBLE		stec_residual_correction;

}STEC_RESIDUAL_CORRECTION_RANGE_1, * pSTEC_RESIDUAL_CORRECTION_RANGE_1;


typedef struct SSR_STEC_HEADER
{
	GPPUINT2		msg_number;
	GPPUINT1		msg_sub_type_id;
	GPPUINT4		gns_hourly_epoch_time;
	GPPUINT1		ssr_update_interval;
	GPPUINT1		multiple_msg_indicator;
	GPPUINT1		iod_ssr;
	GPPUINT1		compact_ssr_stec_correction_type;
	GPPUINT1		compact_network_id;
	GPPUINT			network_sv_mask;
}SSR_STEC_HEADER, * pSSR_STEC_HEADER;

typedef struct SSR_STEC_SPEC_PART_0
{
	GPPUINT1		ssr_stec_qlty_indicator;
	GPPDOUBLE		poly_coeff_c00;
	GPPUINT1		ssr_stec_qlty_indicator_msat;
	GPPDOUBLE		poly_coeff_c00_msat;
}SSR_STEC_SPEC_PART_0, * pSSR_STEC_SPEC_PART_0;

typedef struct SSR_STEC_SPEC_PART_1
{
	GPPUINT1		ssr_stec_qlty_indicator;
	GPPDOUBLE		poly_coeff_c00;
	GPPDOUBLE		poly_coeff_c01;
	GPPDOUBLE		poly_coeff_c10;
	GPPUINT1		ssr_stec_qlty_indicator_msat;
	GPPDOUBLE		poly_coeff_c00_msat;
	GPPDOUBLE		poly_coeff_c01_msat;
	GPPDOUBLE		poly_coeff_c10_msat;

}SSR_STEC_SPEC_PART_1, * pSSR_STEC_SPEC_PART_1;

typedef struct SSR_STEC_SPEC_PART_2
{
	GPPUINT1		ssr_stec_qlty_indicator;
	GPPDOUBLE		poly_coeff_c00;
	GPPDOUBLE		poly_coeff_c01;
	GPPDOUBLE		poly_coeff_c10;
	GPPDOUBLE		poly_coeff_c11;
	GPPUINT1		ssr_stec_qlty_indicator_msat;
	GPPDOUBLE		poly_coeff_c00_msat;
	GPPDOUBLE		poly_coeff_c01_msat;
	GPPDOUBLE		poly_coeff_c10_msat;
	GPPDOUBLE		poly_coeff_c11_msat;
}SSR_STEC_SPEC_PART_2, * pSSR_STEC_SPEC_PART_2;


typedef struct SSR_STEC
{
	pSSR_STEC_HEADER					 header;
	pSSR_STEC_SPEC_PART_0				 spec_part_0;
	pSSR_STEC_SPEC_PART_1				 spec_part_1;
	pSSR_STEC_SPEC_PART_2				 spec_part_2;
	pSTEC_RESIDUAL_CORRECTION_RANGE_0	 range_0;
	pSTEC_RESIDUAL_CORRECTION_RANGE_0	 range_1;
}SSR_STEC, * pSSR_STEC;


//COMPACT SSR GRIDDED CORRECTION

typedef struct SSR_GRID_HEADER
{
	GPPUINT2		msg_number;
	GPPUINT1		msg_sub_type_id;
	GPPUINT4		gns_hourly_epoch_time;
	GPPUINT1		ssr_update_interval;
	GPPUINT1		multiple_msg_indicator;
	GPPUINT1		iod_ssr;
	GPPUINT1		tropospheric_delay_correction_type;
	GPPUINT1		stec_residual_correction_range;
	GPPUINT1		compact_network_id;
	GPPUINT			network_sv_mask;
	GPPUINT1		troposhperic_delay_qlty_indicator;
	GPPUINT1		no_of_grids
}SSR_GRID_HEADER,*pSSR_GRID_HEADER;

typedef struct SSR_GRID_SPEC_PART
{
	GPPDOUBLE		troposphere_hydrostatic_vertical_delay_grid_1;
	GPPDOUBLE		troposphere_wet_vertical_delay_grid_1;
	GPPDOUBLE		stec_residual_correction_grid_1;
	GPPDOUBLE		stec_residual_correction_grid_1_sv_msat;
	GPPDOUBLE		troposphere_hydrostatic_vertical_delay_grid_n;
	GPPDOUBLE		stec_residual_correction_grid_n;
	GPPDOUBLE		stec_residual_correctioon_grid_n_sv_msat;
}SSR_GRID_SPEC_PART,*pSSR_GRID_SPEC_PART;


typedef struct SSR_GRID
{
	pSSR_GRID_HEADER			header;
	pSSR_GRID_SPEC_PART			spec_part;

}SSR_GRID,*pSSR_GRID;



//COMPACT SSR SERVICE INFORMATION
//To be discussed

typedef struct SSR_SERVICE_INFO_HEADER
{
	

}SSR_SERVICE_INFO_HEADER,*pSSR_SERVICE_INFO_HEADER;


typedef struct SSR_SERVICE_INFO_SPEC_PART
{
	
}SSR_SERVICE_INFO_SPEC_PART,pSSR_SERVICE_INFO_SPEC_PART;


typedef struct SSR_SERVICE_INFO
{
	pSSR_SERVICE_INFO_HEADER			header;
	pSSR_SERVICE_INFO_SPEC_PART			spec_part;
}SSR_SERVICE_INFO,*pSSR_SERVICE_INFO;



//COMPACT SSR GNSS COMBINED CORRECTION

typedef struct SSR_GNSS_COMBINED_HEADER
{
	GPPUINT2		msg_number;
	GPPUINT1		msg_sub_type_id;
	GPPUINT4		gns_hourly_epoch_time;
	GPPUINT1		ssr_update_interval;
	GPPUINT1		multiple_msg_indicator;
	GPPUINT1		iod_ssr;
	GPPUINT1		orbit_existing_flag;
	GPPUINT1		clock_ecisting_flag;
	GPPUINT1		network_correction;
	GPPUINT1		compact_network_id;
	GPPUINT			network_sv_mask;
}SSR_GNSS_COMBINED_HEADER,*pSSR_GNSS_COMBINED_HEADER;

typedef struct SSR_GNSS_COMBINED_SPEC_PART
{
	GPPUINT2		gnss_iode;
	GPPDOUBLE		compact_ssr_delta_radian;
	GPPDOUBLE		compact_ssr_delta_alongtrack;
	GPPDOUBLE		compact_ssr_delta_crosstrack;
	GPPDOUBLE		compact_ssr_delta_clock_c0;
	GPPUINT2		gnss_iode_msat;
	GPPDOUBLE		compact_ssr_delta_radian_msat;
	GPPDOUBLE		compact_ssr_delta_alongtrack_msat;
	GPPDOUBLE		compact_ssr_delta_crosstrack_msat;
	GPPDOUBLE		compact_ssr_delta_clock_c0_msat;

}SSR_GNSS_COMBINED_SPEC_PART,*pSSR_GNSS_COMBINED_SPEC_PART;

typedef struct SSR_GNSS_COMBINED
{
	pSSR_GNSS_COMBINED_HEADER			header;
	pSSR_GNSS_COMBINED_SPEC_PART		spec_part;
}SSR_GNSS_COMBINED,*pSSR_GNSS_COMBINED;



//Structure for QZSS
typedef struct QZSS
{
	pSSR_MASK						mask;
	pSSR_GNSS_ORB					orb;
	pSSR_GNSS_CLK					clk;
	pSSR_GNSS_SAT_CODE_BIAS			sat_code_bias;
	pSSR_GNSS_SAT_PHASE_BIAS		sat_phase_bias;
	pSSR_GNSS_SAT_CODE_PHASE_BIAS	sat_code_phase_bias;
	pSSR_GNSS_URA					ura;
	pSSR_STEC						stec;
	pSSR_GRID						grid;
	pSSR_SERVICE_INFO				service_info;
	pSSR_GNSS_COMBINED				combined;

}QZSS, * q;

