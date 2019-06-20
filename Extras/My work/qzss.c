/******************************************
  *	QZSS ERROR Codes
  ******************************************/
#define QZSS_SSR_ERROR_BASE 						-54000
#define QZSS_SSR_ERR_NOT_YET_IMPLEMENTED			(QZSS_SSR_ERROR_BASE-1)		/* -54001 */
#define QZSS_SSR_ERR_NOT_ENOUGH_MEMORY				(QZSS_SSR_ERROR_BASE-2)		/* -54002 */
#define QZSS_SSR_ERR_INVALID_MASK					(QZSS_SSR_ERROR_BASE-3)		/* -54003 */
#define QZSS_SSR_ERR_INVALID_ORB					(QZSS_SSR_ERROR_BASE-4)		/* -54004 */
#define QZSS_SSR_ERR_INVALID_CLK					(QZSS_SSR_ERROR_BASE-5)		/* -54005 */
#define QZSS_SSR_ERR_INVALID_SAT_CODE_BIAS			(QZSS_SSR_ERROR_BASE-6)		/* -54006 */
#define QZSS_SSR_ERR_INVALID_SAT_PHASE_BIAS		   	(QZSS_SSR_ERROR_BASE-7)		/* -54007 */
#define QZSS_SSR_ERR_INVALID_SAT_CODE_PHASE_BIAS	(QZSS_SSR_ERROR_BASE-8)		/* -54008 */
#define QZSS_SSR_ERR_INVALID_URA					(QZSS_SSR_ERROR_BASE-9)		/* -54009 */
#define QZSS_SSR_ERR_INVALID_STEC					(QZSS_SSR_ERROR_BASE-10)	/* -54010 */
#define QZSS_SSR_ERR_INVALID_GRID					(QZSS_SSR_ERROR_BASE-11)	/* -54011 */
#define QZSS_SSR_ERR_INVALID_SERVICE_INFO			(QZSS_SSR_ERROR_BASE-12)	/* -54012 */
#define QZSS_SSR_ERR_INVALID_COMBINED				(QZSS_SSR_ERROR_BASE-13)	/* -54012 */




//================================functions to add data to structure For QZSS_SSR==========================================================================================


//---------------------------------------MASK------------------------------------------------------------------------------------------------------------------------------

GPPLONG qzss_ssr_mask_add_header(pSSR_MASK mask, const pSSR_MASK_MSG_HEADER pset)
{
	if (!mask) return QZSS_SSR_ERR_INVALID_MASK;

	if (!mask->header)
	{
		mask->header = (pSSR_MASK_MSG_HEADER*)calloc(1, sizeof(SSR_MASK_MSG_HEADER));
		if (!mask->header)
			return QZSS_SSR_ERR_NOT_ENOUGH_MEMORY;
	}

	return 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

GPPLONG qzss_ssr_mask_add_spec_part(pSSR_MASK mask, const pSSR_MASK_SPEC_PART pset)
{
	if (!mask) return QZSS_SSR_ERR_INVALID_MASK;

	if (!mask->header)
	{
		mask->header = (pSSR_MASK_SPEC_PART*)calloc(1, sizeof(SSR_MASK_SPEC_PART));
		if (!mask->header)
			return QZSS_SSR_ERR_NOT_ENOUGH_MEMORY;
	}

	return 0;
}

//---------------------------------------ORB------------------------------------------------------------------------------------------------------------------------------

GPPLONG qzss_ssr_mask_add_header(pSSR_GNSS_ORB orb; , const pSSR_GNSS_ORB_MSG_HEADER pset)
{
	if (!orb) return QZSS_SSR_ERR_INVALID_ORB;

	if (!orb->header)
	{
		orb->header = (pSSR_GNSS_ORB_MSG_HEADER*)calloc(1, sizeof(SSR_GNSS_ORB_MSG_HEADER));
		if (!orb->header)
			return QZSS_SSR_ERR_NOT_ENOUGH_MEMORY;
	}

	return 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

GPPLONG qzss_ssr_mask_add_spec_part(pSSR_GNSS_ORB orb; , const pSSR_GNSS_ORB_SPEC_PART pset)
{
	if (!orb) return QZSS_SSR_ERR_INVALID_ORB;

	if (!orb->header)
	{
		orb->header = (pSSR_GNSS_ORB_SPEC_PART*)calloc(1, sizeof(SSR_GNSS_ORB_SPEC_PART));
		if (!orb->header)
			return QZSS_SSR_ERR_NOT_ENOUGH_MEMORY;
	}

	return 0;
}

//---------------------------------------CLK------------------------------------------------------------------------------------------------------------------------------

GPPLONG qzss_ssr_mask_add_header(pSSR_GNSS_CLK clk; , const pSSR_GNSS_CLK_HEADER pset)
{
	if (!clk) return QZSS_SSR_ERR_INVALID_CLK;

	if (!clk->header)
	{
		clk->header = (pSSR_GNSS_CLK_HEADER*)calloc(1, sizeof(SSR_GNSS_CLK_HEADER));
		if (!clk->header)
			return QZSS_SSR_ERR_NOT_ENOUGH_MEMORY;
	}

	return 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

GPPLONG qzss_ssr_mask_add_spec_part(pSSR_GNSS_CLK clk; , const pSSR_GNSS_CLK_SPEC_PART pset)
{
	if (!clk) return QZSS_SSR_ERR_INVALID_CLK;

	if (!clk->header)
	{
		clk->header = (pSSR_GNSS_CLK_SPEC_PART*)calloc(1, sizeof(SSR_GNSS_CLK_SPEC_PART));
		if (!clk->header)
			return QZSS_SSR_ERR_NOT_ENOUGH_MEMORY;
	}

	return 0;
}

//---------------------------------------SAT_CODE_BIAS------------------------------------------------------------------------------------------------------------------------------


GPPLONG qzss_ssr_mask_add_header(pSSR_GNSS_SAT_CODE_BIAS sat_code_bias; , const pSSR_GNSS_SAT_CODE_BIAS_HEADER pset)
{
	if (!sat_code_bias) return QZSS_SSR_ERR_INVALID_SAT_CODE_BIAS;

	if (!sat_code_bias->header)
	{
		masat_code_biassk->header = (pSSR_GNSS_SAT_CODE_BIAS_HEADER*)calloc(1, sizeof(SSR_GNSS_SAT_CODE_BIAS_HEADER));
		if (!sat_code_bias->header)
			return QZSS_SSR_ERR_NOT_ENOUGH_MEMORY;
	}

	return 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

GPPLONG qzss_ssr_mask_add_spec_part(pSSR_GNSS_SAT_CODE_BIAS	sat_code_bias; , const pSSR_GNSS_SAT_CODE_BIAS_SPEC_PART pset)
{
	if (!sat_code_bias) return QZSS_SSR_ERR_INVALID_SAT_CODE_BIAS;

	if (!sat_code_bias->header)
	{
		sat_code_bias->header = (pSSR_GNSS_SAT_CODE_BIAS_SPEC_PART*)calloc(1, sizeof(SSR_GNSS_SAT_CODE_BIAS_SPEC_PART));
		if (!sat_code_bias->header)
			return QZSS_SSR_ERR_NOT_ENOUGH_MEMORY;
	}

	return 0;
}

//---------------------------------------SAT_PHASE_BIAS------------------------------------------------------------------------------------------------------------------------------


GPPLONG qzss_ssr_mask_add_header(pSSR_GNSS_SAT_PHASE_BIAS sat_phase_bias; , const pSSR_GNSS_SAT_PHASE_BIAS_HEADER pset)
{
	if (!sat_phase_bias) return QZSS_SSR_ERR_INVALID_SAT_PHASE_BIAS;

	if (!sat_phase_bias->header)
	{
		sat_phase_bias->header = (pSSR_GNSS_SAT_PHASE_BIAS_HEADER*)calloc(1, sizeof(SSR_GNSS_SAT_PHASE_BIAS_HEADER));
		if (!sat_phase_bias->header)
			return QZSS_SSR_ERR_NOT_ENOUGH_MEMORY;
	}

	return 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

GPPLONG qzss_ssr_mask_add_spec_part(pSSR_GNSS_SAT_PHASE_BIAS sat_phase_bias; , const pSSR_GNSS_SAT_PHASE_BIAS_SPEC_PART pset)
{
	if (!sat_phase_bias) return QZSS_SSR_ERR_INVALID_SAT_PHASE_BIAS;

	if (!sat_phase_bias->header)
	{
		sat_phase_bias->header = (pSSR_GNSS_SAT_PHASE_BIAS_SPEC_PART*)calloc(1, sizeof(SSR_GNSS_SAT_PHASE_BIAS_SPEC_PART));
		if (!sat_phase_bias->header)
			return QZSS_SSR_ERR_NOT_ENOUGH_MEMORY;
	}

	return 0;
}

//---------------------------------------SAT_CODE_PHASE_BIAS------------------------------------------------------------------------------------------------------------------------------


GPPLONG qzss_ssr_mask_add_header(pSSR_GNSS_SAT_CODE_PHASE_BIAS sat_code_phase_bias; , const pSSR_GNSS_SAT_CODE_PHASE_BIAS_HEADER pset)
{
	if (!sat_code_phase_bias) return QZSS_SSR_ERR_INVALID_SAT_CODE_PHASE_BIAS;

	if (!sat_code_phase_bias->header)
	{
		sat_code_phase_bias->header = (pSSR_GNSS_SAT_CODE_PHASE_BIAS_HEADER*)calloc(1, sizeof(SSR_GNSS_SAT_CODE_PHASE_BIAS_HEADER));
		if (!sat_code_phase_bias->header)
			return QZSS_SSR_ERR_NOT_ENOUGH_MEMORY;
	}

	return 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

GPPLONG qzss_ssr_mask_add_spec_part(pSSR_GNSS_SAT_CODE_PHASE_BIAS sat_code_phase_bias; , const pSSR_GNSS_SAT_CODE_PHASE_BIAS_SPEC_PART pset)
{
	if (!sat_code_phase_bias) return QZSS_SSR_ERR_INVALID_SAT_CODE_PHASE_BIAS;

	if (!sat_code_phase_bias->header)
	{
		sat_code_phase_bias->header = (pSSR_MASK_SPEC_PART*)calloc(1, sizeof(SSR_GNSS_SAT_CODE_PHASE_BIAS_SPEC_PART));
		if (!sat_code_phase_bias->header)
			return QZSS_SSR_ERR_NOT_ENOUGH_MEMORY;
	}

	return 0;
}

//---------------------------------------URA------------------------------------------------------------------------------------------------------------------------------

GPPLONG qzss_ssr_mask_add_header(pSSR_GNSS_URA ura; , const pSSR_GNSS_URA_HEADER pset)
{
	if (!ura) return QZSS_SSR_ERR_INVALID_URA;

	if (!ura->header)
	{
		ura->header = (pSSR_GNSS_URA_HEADER*)calloc(1, sizeof(SSR_GNSS_URA_HEADER));
		if (!ura->header)
			return QZSS_SSR_ERR_NOT_ENOUGH_MEMORY;
	}

	return 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

GPPLONG qzss_ssr_mask_add_spec_part(pSSR_GNSS_URA ura; , const pSSR_GNSS_URA_SPEC_PART pset)
{
	if (!ura) return QZSS_SSR_ERR_INVALID_URA;

	if (!ura->header)
	{
		ura->header = (pSSR_GNSS_URA_SPEC_PART*)calloc(1, sizeof(SSR_GNSS_URA_SPEC_PART));
		if (!ura->header)
			return QZSS_SSR_ERR_NOT_ENOUGH_MEMORY;
	}

	return 0;
}

//---------------------------------------STEC------------------------------------------------------------------------------------------------------------------------------


GPPLONG qzss_ssr_mask_add_header(pSSR_STEC stec; , const pSSR_MASK_MSG_HEADER pset)
{
	if (!stec) return QZSS_SSR_ERR_INVALID_STEC;

	if (!stec->header)
	{
		stec->header = (pSSR_STEC_HEADER*)calloc(1, sizeof(SSR_STEC_HEADER));
		if (!stec->header)
			return QZSS_SSR_ERR_NOT_ENOUGH_MEMORY;
	}

	return 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

GPPLONG qzss_ssr_mask_add_spec_part(pSSR_STEC stec; , const pSTEC_RESIDUAL_CORRECTION_RANGE_0 pset)
{
	if (!stec) return QZSS_SSR_ERR_INVALID_STEC;

	if (!stec->header)
	{
		stec->header = (pSTEC_RESIDUAL_CORRECTION_RANGE_0*)calloc(1, sizeof(STEC_RESIDUAL_CORRECTION_RANGE_0));
		if (!stec->header)
			return QZSS_SSR_ERR_NOT_ENOUGH_MEMORY;
	}

	return 0;
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
GPPLONG qzss_ssr_mask_add_spec_part(pSSR_STEC stec;, const pSTEC_RESIDUAL_CORRECTION_RANGE_1 pset)
{
	if (!stec) return QZSS_SSR_ERR_INVALID_STEC;

	if (!stec->header)
	{
		stec->header = (pSTEC_RESIDUAL_CORRECTION_RANGE_1*)calloc(1, sizeof(STEC_RESIDUAL_CORRECTION_RANGE_1));
		if (!stec->header)
			return QZSS_SSR_ERR_NOT_ENOUGH_MEMORY;
	}

	return 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

GPPLONG qzss_ssr_mask_add_spec_part(pSSR_STEC stec; , const pSSR_STEC_SPEC_PART_0 pset)
{
	if (!stec) return QZSS_SSR_ERR_INVALID_STEC;

	if (!stec->header)
	{
		stec->header = (pSSR_STEC_SPEC_PART_0*)calloc(1, sizeof(SSR_STEC_SPEC_PART_0));
		if (!stec->header)
			return QZSS_SSR_ERR_NOT_ENOUGH_MEMORY;
	}

	return 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

GPPLONG qzss_ssr_mask_add_spec_part(pSSR_STEC stec;, const pSSR_STEC_SPEC_PART_1 pset)
{
	if (!stec) return QZSS_SSR_ERR_INVALID_STEC;

	if (!stec->header)
	{
		stec->header = (pSSR_STEC_SPEC_PART_1*)calloc(1, sizeof(SSR_STEC_SPEC_PART_1));
		if (!stec->header)
			return QZSS_SSR_ERR_NOT_ENOUGH_MEMORY;
	}

	return 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

GPPLONG qzss_ssr_mask_add_spec_part(pSSR_STEC stec;, const pSSR_STEC_SPEC_PART_2 pset)
{
	if (!stec) return QZSS_SSR_ERR_INVALID_STEC;

	if (!stec->header)
	{
		stec->header = (pSSR_STEC_SPEC_PART_2*)calloc(1, sizeof(SSR_STEC_SPEC_PART_2));
		if (!stec->header)
			return QZSS_SSR_ERR_NOT_ENOUGH_MEMORY;
	}

	return 0;
}

//---------------------------------------GRID------------------------------------------------------------------------------------------------------------------------------


GPPLONG qzss_ssr_mask_add_header(pSSR_GRID grid; , const pSSR_GRID_HEADER pset)
{
	if (!grid) return QZSS_SSR_ERR_INVALID_GRID;

	if (!grid->header)
	{
		grid->header = (pSSR_GRID_HEADER*)calloc(1, sizeof(SSR_GRID_HEADER));
		if (!grid->header)
			return QZSS_SSR_ERR_NOT_ENOUGH_MEMORY;
	}

	return 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

GPPLONG qzss_ssr_mask_add_spec_part(pSSR_GRID grid; , const pSSD_GRID_SPEC_PART pset)
{
	if (!grid) return QZSS_SSR_ERR_INVALID_GRID;

	if (!grid->header)
	{
		grid->header = (pSSD_GRID_SPEC_PART*)calloc(1, sizeof(SSD_GRID_SPEC_PART));
		if (!grid->header)
			return QZSS_SSR_ERR_NOT_ENOUGH_MEMORY;
	}

	return 0;
}

//---------------------------------------SERVICE_INFO------------------------------------------------------------------------------------------------------------------------------


GPPLONG qzss_ssr_mask_add_header(pSSR_SERVICE_INFO service_info; , const pSSR_SERVICE_INFO_HEADER pset)
{
	if (!service_info) return QZSS_SSR_ERR_INVALID_SERVICE_INFO;

	if (!service_info->header)
	{
		service_info->header = (pSSR_SERVICE_INFO_HEADER*)calloc(1, sizeof(SSR_SERVICE_INFO_HEADER));
		if (!service_info->header)
			return QZSS_SSR_ERR_NOT_ENOUGH_MEMORY;
	}

	return 0;
}


GPPLONG qzss_ssr_mask_add_spec_part(pSSR_SERVICE_INFO service_info; , const pSSR_SERVICE_INFO_SPEC_PART pset)
{
	if (!service_info) return QZSS_SSR_ERR_INVALID_SERVICE_INFO;

	if (!service_info->header)
	{
		service_info->header = (pSSR_SERVICE_INFO_SPEC_PART*)calloc(1, sizeof(SSR_SERVICE_INFO_SPEC_PART));
		if (!service_info->header)
			return QZSS_SSR_ERR_NOT_ENOUGH_MEMORY;
	}

	return 0;
}

//---------------------------------------COMBINED------------------------------------------------------------------------------------------------------------------------------


GPPLONG qzss_ssr_mask_add_header(pSSR_GNSS_COMBINED combined; , const pSSR_GNSS_COMBINED_HEADER pset)
{
	if (!combined) return QZSS_SSR_ERR_INVALID_COMBINED;

	if (!combined->header)
	{
		combined->header = (pSSR_GNSS_COMBINED_HEADER*)calloc(1, sizeof(SSR_GNSS_COMBINED_HEADER));
		if (!combined->header)
			return QZSS_SSR_ERR_NOT_ENOUGH_MEMORY;
	}

	return 0;
}


GPPLONG qzss_ssr_mask_add_spec_part(pSSR_GNSS_COMBINED combined; , pSSR_GNSS_COMBINED_SPEC_PART pset)
{
	if (!combined) return QZSS_SSR_ERR_INVALID_COMBINED;

	if (!combined->header)
	{
		combined->header = (pSSR_GNSS_COMBINED_SPEC_PART*)calloc(1, sizeof(SSR_GNSS_COMBINED_SPEC_PART));
		if (!combined->header)
			return QZSS_SSR_ERR_NOT_ENOUGH_MEMORY;
	}

	return 0;
}


