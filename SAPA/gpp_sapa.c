#include "gpp_sapa.h"
#include "bit2buff.h"


const GPPDOUBLE SAPA_TROPO_COEFF_T00_MIN[2] = { GPP_SAPA_HPAC_SMALL_T00_MIN ,GPP_SAPA_HPAC_LARGE_T00_MIN };
const GPPDOUBLE SAPA_TROPO_COEFF_T00_MAX[2] = { GPP_SAPA_HPAC_SMALL_T00_MAX ,GPP_SAPA_HPAC_LARGE_T00_MAX };
const GPPDOUBLE SAPA_TROPO_COEFF_T01_MIN[2] = { GPP_SAPA_HPAC_SMALL_T01_MIN ,GPP_SAPA_HPAC_LARGE_T01_MIN };
const GPPDOUBLE SAPA_TROPO_COEFF_T01_MAX[2] = { GPP_SAPA_HPAC_SMALL_T01_MAX ,GPP_SAPA_HPAC_LARGE_T01_MAX };
const GPPDOUBLE SAPA_TROPO_COEFF_T11_MIN[2] = { GPP_SAPA_HPAC_SMALL_T11_MIN ,GPP_SAPA_HPAC_LARGE_T11_MIN };
const GPPDOUBLE SAPA_TROPO_COEFF_T11_MAX[2] = { GPP_SAPA_HPAC_SMALL_T11_MAX ,GPP_SAPA_HPAC_LARGE_T11_MAX };
const GPPDOUBLE SAPA_TROPO_COEFF_C00_MIN[2] = { GPP_SAPA_HPAC_SMALL_C00_MIN ,GPP_SAPA_HPAC_LARGE_C00_MIN };
const GPPDOUBLE SAPA_TROPO_COEFF_C00_MAX[2] = { GPP_SAPA_HPAC_SMALL_C00_MAX ,GPP_SAPA_HPAC_LARGE_C00_MAX };
const GPPDOUBLE SAPA_TROPO_COEFF_C01_MIN[2] = { GPP_SAPA_HPAC_SMALL_C01_MIN ,GPP_SAPA_HPAC_LARGE_C01_MIN };
const GPPDOUBLE SAPA_TROPO_COEFF_C01_MAX[2] = { GPP_SAPA_HPAC_SMALL_C01_MAX ,GPP_SAPA_HPAC_LARGE_C01_MAX };
const GPPDOUBLE SAPA_TROPO_COEFF_C11_MIN[2] = { GPP_SAPA_HPAC_SMALL_C11_MIN ,GPP_SAPA_HPAC_LARGE_C11_MIN };
const GPPDOUBLE SAPA_TROPO_COEFF_C11_MAX[2] = { GPP_SAPA_HPAC_SMALL_C11_MAX ,GPP_SAPA_HPAC_LARGE_C11_MAX };
const GPPDOUBLE SAPA_TROPO_RESIDUAL_ZENITH_MIN[2] = { GPP_SAPA_HPAC_SMALL_ZENTH_MIN ,GPP_SAPA_HPAC_LARGE_ZENTH_MIN };
const GPPDOUBLE SAPA_TROPO_RESIDUAL_ZENITH_MAX[2] = { GPP_SAPA_HPAC_SMALL_ZENTH_MAX ,GPP_SAPA_HPAC_LARGE_ZENTH_MAX };
const GPPDOUBLE SAPA_IONO_RESIDUAL_SLANT_MIN[4] = { GPP_SAPA_HPAC_SMALL_SLANT_MIN,GPP_SAPA_HPAC_MEDIUM_SLANT_MIN,GPP_SAPA_HPAC_LARGE_SLANT_MIN,GPP_SAPA_HPAC_EXTRA_LARGE_SLANT_MIN };
const GPPDOUBLE SAPA_IONO_RESIDUAL_SLANT_MAX[4] = { GPP_SAPA_HPAC_SMALL_SLANT_MAX,GPP_SAPA_HPAC_MEDIUM_SLANT_MAX,GPP_SAPA_HPAC_LARGE_SLANT_MAX,GPP_SAPA_HPAC_EXTRA_LARGE_SLANT_MAX };

const GPPUINT1 SAPA_SV_IODE_LEN[GPP_SAPA_MAX_SYS]={SAPA_SV_IODE_LEN_GPS, SAPA_SV_IODE_LEN_GLO,};

const GPPUINT1 SAPA_SV_BITMASK_LEN_GPS[4]={32, 44, 56, 64};
const GPPUINT1 SAPA_SV_BITMASK_LEN_GLO[4]={24, 36, 48, 63};
const GPPUINT1 *SAPA_SV_BITMASK_LEN[2]={SAPA_SV_BITMASK_LEN_GPS, SAPA_SV_BITMASK_LEN_GLO};

const GPPUINT1 SAPA_CRC_BYTES[4] = { SAPA_CONST_LEN_BYTES_CRC_8,SAPA_CONST_LEN_BYTES_CRC_16,SAPA_CONST_LEN_BYTES_CRC_24,SAPA_CONST_LEN_BYTES_CRC_32 };


/***************************************************************************
 *	\brief Get an Index list (starting with zero) of bits set in bitmask (prn_bits).
 *	svlist is an GPPUINT1 array with 66 fields. svlist[0] contains the total number of set bits in prn_bits
 *	svlist[65] is zero (control bit)
 *  svlist[1] is the idx of the first set bit
 ***************************************************************************/
void gpp_sapa_get_svlist(GPPUINT8 prn_bits, GPPUINT1 *svlist)
{
	GPPUINT1 sat=0, num=0;
	GPPUINT8 bit = 1;

	if (!svlist) return;

	memset(svlist, 0, 66*sizeof(GPPUINT1));

	for (sat = 0; sat < GPP_SAPA_MAX_SAT; sat++){
		if (prn_bits&(bit<<sat)){
			svlist[num + 1] = sat;
			num++;
		}
	}
	svlist[0] = num;
}//gpp_sapa_get_svlist()

/***************************************************************************
 *	\brief Get an Index list (starting with zero) of bits set in bitmask (prn_bits).
 *	svlist is an GPPUINT1 array with 34 fields. svlist[0] contains the total number of set bits in prn_bits
 *	svlist[65] is zero (control bit)
 *  svlist[1] is the idx of the first set bit
 ***************************************************************************/
void gpp_sapa_get_siglist(GPPUINT4 sig_bits, GPPUINT1 *siglist)
{
	GPPUINT1 sig=0, num=0;
	GPPUINT4 bit = 1;
	if (!siglist) return;

	memset(siglist, 0, 34*sizeof(GPPUINT1));

	for (sig=0; sig<GPP_SAPA_MAX_SIG; sig++) {
		if (sig_bits&(bit <<sig)) {
			siglist[num+1] = sig;
			num++;
		}
	}
	siglist[0] = num;
}//gpp_sapa_get_siglist()


/************************************************************************************************************
 * \brief Return Seconds passed in the hour when data is received.
 ************************************************************************************************************/
GPPINT gpp_sapa_get_hourly_time_tag(GPPINT seconds_of_week)
{
	return(seconds_of_week % 3600);
}//gpp_sapa_get_hourly_time_tag()


/************************************************************************************************************
 * \brief Returns seconds passed since the beginning including all gps_weeks.
 ************************************************************************************************************/
GPPINT gpp_sapa_get_full_time_tag(GPPINT gps_week, GPPINT seconds_of_week)
{
	return(((gps_week - 1) * 7 * 24 * 3600) + seconds_of_week);
}//gpp_sapa_get_full_time_tag()


//Returns Orbit ,Clock and  Bias flag value
void gpp_sapa_get_ocb_flag_value(GPPUINT1 ocb_bits, GPPUINT1 *o_flag, GPPUINT1 *c_flag, GPPUINT1 *b_flag)
{
	GPPUINT1 var = 1;
	*o_flag = (ocb_bits & (var << GPP_SAPA_OCB_FLAG_IDX_ORB)) ? 1 : 0;
	*c_flag = (ocb_bits & (var << GPP_SAPA_OCB_FLAG_IDX_CLK)) ? 1 : 0;
	*b_flag = (ocb_bits & (var << GPP_SAPA_OCB_FLAG_IDX_BIAS)) ? 1 : 0;
}
//Returns highest order of satellite set



/************************************************************************************************************
 *	\brief Allocate ocb, hpac, area in gpp_sapa_use_states structure
 ************************************************************************************************************/

GPPLONG gpp_sapa_states_free_ocb(GPP_SAPA_USE_STATES *use_states)
{
	if(!use_states) return -1;

	if(use_states->ocb){
		gpp_sapa_ocb_free_ocb(use_states->ocb);
		free(use_states->ocb);
		use_states->ocb=NULL;
	}
	return 0;
}//gpp_sapa_states_free_ocb()

/************************************************************************************************************/

GPPLONG gpp_sapa_states_malloc_ocb(GPP_SAPA_USE_STATES *use_states)
{
	if(!use_states) return -1;

	gpp_sapa_states_free_ocb(use_states);

	use_states->ocb=(GPP_SAPA_OCB*)calloc(1, sizeof(GPP_SAPA_OCB));
	if(!use_states->ocb) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;

	return 0;
}




//=============================================== functions to add data to structure For OCB =================================================
/************************************************************************************************************

 *        \brief Allocate two-dimensional sv pointer array
 11
 ***********************************************************************************************************/

GPPLONG gpp_sapa_ocb_malloc_sv(pGPP_SAPA_OCB ocb)
{
	if (!ocb) return GPP_SAPA_ERR_INVALID_OCB;

	if (!ocb->sv)
	{
		GPPUINT1 sys;
		ocb->sv = (pGPP_SAPA_OCB_SV**)calloc(GPP_SAPA_MAX_CONS, sizeof(GPP_SAPA_OCB_SV**));

		if (!ocb->sv) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;

		for (sys = 0; sys < GPP_SAPA_MAX_CONS; sys++)
		{
			ocb->sv[sys] = (GPP_SAPA_OCB_SV**)calloc(GPP_SAPA_MAX_SAT, sizeof(GPP_SAPA_OCB_SV));

			if (!(ocb->sv[sys])) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
		}
	}

	return 0; //ok

}//gpp_sapa_ocb_malloc_sv()

/************************************************************************************************************

 *        \brief free two-dimensional sv pointer array (and substructures) in GPP_SAPA_OCB

 ***********************************************************************************************************/

GPPLONG gpp_sapa_ocb_free_ocb(pGPP_SAPA_OCB ocb)
{
	if (ocb) {
		if (ocb->header_block)
		{
			free(ocb->header_block);
			ocb->header_block = NULL;
		}
		if (ocb->sv)
		{
			GPPUINT1 sys;
			for (sys = 0; sys < GPP_SAPA_MAX_SYS; sys++)
			{
				GPPUINT1 sat;
				for (sat = 0; sat < GPP_SAPA_MAX_SAT; sat++)
				{
					if (ocb->sv[sys][sat])
					{
						if (ocb->sv[sys][sat]->orb)
						{
							free(ocb->sv[sys][sat]->orb);
						}
						if (ocb->sv[sys][sat]->clk)
						{
							free(ocb->sv[sys][sat]->clk);
						}
						if (ocb->sv[sys][sat]->bias)
						{
							GPPUINT1 sig;
							if (ocb->sv[sys][sat]->bias->pb)
							{
								for (sig = 0; sig < GPP_SAPA_MAX_SIG; sig++)
								{
									if (ocb->sv[sys][sat]->bias->pb[sig])
									{
										free(ocb->sv[sys][sat]->bias->pb[sig]);
									}
								}
								free(ocb->sv[sys][sat]->bias->pb);
							}
							if (ocb->sv[sys][sat]->bias->cb)
							{
								for (sig = 0; sig < GPP_SAPA_MAX_SIG; sig++)
								{
									if (ocb->sv[sys][sat]->bias->cb[sig])
									{
										free(ocb->sv[sys][sat]->bias->cb[sig]);
									}
								}
								free(ocb->sv[sys][sat]->bias->cb);
							}
							free(ocb->sv[sys][sat]->bias);
						}
						free(ocb->sv[sys][sat]);
					}
				}
				if (ocb->sv[sys])
				{
					free(ocb->sv[sys]);
				}
			}
			free(ocb->sv);
			ocb->sv = NULL;
		}
	}

	return 0;

}//gpp_sapa_ocb_free_ocb()


GPPLONG gpp_sapa_ocb_add_sv(pGPP_SAPA_OCB ocb, GPPUINT1 sys, GPPUINT1 sat, const pGPP_SAPA_OCB_SV pset)
{
	pGPP_SAPA_OCB_SV sv = NULL;   // Pointer to OCB_SV

	if (!ocb) return GPP_SAPA_ERR_INVALID_OCB;

	if (!ocb->sv) {// allocate the sys-sat two dimensional pointer array
		GPPLONG rc;       //control variable
		if (rc = gpp_sapa_ocb_malloc_sv(ocb)) return rc;
	}

	if (!(sv = ocb->sv[sys][sat])) { // check if sv[sys][sat] is allocated
		ocb->sv[sys][sat] = (GPP_SAPA_OCB_SV*)calloc(1, sizeof(GPP_SAPA_OCB_SV));
		if (!(sv = ocb->sv[sys][sat])) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}
	memcpy(sv, pset, sizeof(GPP_SAPA_OCB_SV));

	return 0;
}//gpp_sapa_ocb_add_sv()



/************************************************************************************************************

 *        \brief Add an orbit set to ocb structure to handle it later with ocb->sv[sys][sat]->orb

 ***********************************************************************************************************/
GPPLONG gpp_sapa_ocb_add_orb(pGPP_SAPA_OCB ocb, GPPUINT1 sys, GPPUINT1 sat, const pGPP_SAPA_OCB_SV_ORB pset)
{
	pGPP_SAPA_OCB_SV sv = NULL;			// Pointer to OCB_SV

	GPPLONG rc;						//control variable
	GPPUINT1 ic;
	for (ic = 0; ic < GPP_SAPA_OCB_CORECTION_MAX; ic++)
	{
		if (pset->d_orbit[ic]<GPP_SAPA_OCB_SAT_CORRECTION_MIN || pset->d_orbit[ic]>GPP_SAPA_OCB_SAT_CORRECTION_MAX) return 0;
	}
	if (pset->sat_yaw< GPP_SAPA_OCB_SAT_YAW_MIN || pset->sat_yaw>GPP_SAPA_OCB_SAT_YAW_MAX) return 0;
	if (rc = gpp_sapa_ocb_malloc_sv(ocb)) return rc;

	if (!(sv = ocb->sv[sys][sat])) { // check if sv[sys][sat] is allocated
		ocb->sv[sys][sat] = (GPP_SAPA_OCB_SV*)calloc(1, sizeof(GPP_SAPA_OCB_SV));
		if (!(sv = ocb->sv[sys][sat])) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!sv->orb) {//check if orbit structure is allocated
		sv->orb = (pGPP_SAPA_OCB_SV_ORB)calloc(1, sizeof(GPP_SAPA_OCB_SV_ORB));
		if (!sv->orb) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	memcpy(sv->orb, pset, sizeof(GPP_SAPA_OCB_SV_ORB));	//copy orbit data
	GNSS_SET_IDX_IN_BITS_64(ocb->sv_prn_bits[sys], sat);							//set sat ID in sv_prn_bits bit mask
	GNSS_SET_IDX_IN_BITS_64(ocb->orb_prn_bits[sys], sat);							//set sat ID in sv_prn_bits bit mask
	sv->ocb_bits |= (1 << GPP_SAPA_OCB_FLAG_IDX_ORB);							//set ocb_bits as it is assumed that only valid data are stored in the structure

	return 0;

}//gpp_sapa_ocb_add_orb()

/************************************************************************************************************/

GPPLONG gpp_sapa_ocb_add_clk(pGPP_SAPA_OCB ocb, GPPUINT1 sys, GPPUINT1 sat, const pGPP_SAPA_OCB_SV_CLK pset)
{
	pGPP_SAPA_OCB_SV sv = NULL;			// Pointer to OCB_SV
	GPPLONG rc;							//control variable
	if (pset->clk_correction< GPP_SAPA_OCB_SAT_CORRECTION_MIN || pset->clk_correction>GPP_SAPA_OCB_SAT_CORRECTION_MAX) return 0;
	if (rc = gpp_sapa_ocb_malloc_sv(ocb)) return rc;

	if (!(sv = ocb->sv[sys][sat])) { // check if sv[sys][sat] is allocated
		ocb->sv[sys][sat] = (GPP_SAPA_OCB_SV*)calloc(1, sizeof(GPP_SAPA_OCB_SV));
		if (!(sv = ocb->sv[sys][sat])) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!sv->clk) {//check if orbit structure is allocated
		sv->clk = (pGPP_SAPA_OCB_SV_CLK)calloc(1, sizeof(GPP_SAPA_OCB_SV_CLK));
		if (!sv->clk) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	memcpy(sv->clk, pset, sizeof(GPP_SAPA_OCB_SV_CLK));	//copy clock data
	GNSS_SET_IDX_IN_BITS_64(ocb->sv_prn_bits[sys], sat);						//set sat ID in sv_prn_bits bit mask
	GNSS_SET_IDX_IN_BITS_64(ocb->clk_prn_bits[sys], sat);						//set sat ID in sv_prn_bits bit mask
	sv->ocb_bits |= (1 << GPP_SAPA_OCB_FLAG_IDX_CLK);							//set ocb_bits as it is assumed that only valid data are stored in the structure

	return 0;
}//gpp_sapa_ocb_add_clk()

/************************************************************************************************************/

GPPLONG gpp_sapa_ocb_add_pb(pGPP_SAPA_OCB ocb, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 sig, const pGPP_SAPA_OCB_SV_BIAS_PB pset)
{
	pGPP_SAPA_OCB_SV sv = NULL;					// Pointer to OCB_SV
	pGPP_SAPA_OCB_SV_BIAS bias = NULL;			// Pointer to OCB_SV_BIAS
	pGPP_SAPA_OCB_SV_BIAS_PB	pb = NULL;	// Pointer to OCB_SV_SATPHASEBIAS

	GPPLONG rc;			//control variable
	if (pset->pb_correction< GPP_SAPA_OCB_SAT_CORRECTION_MIN || pset->pb_correction>GPP_SAPA_OCB_SAT_CORRECTION_MAX) return 0;
	if (rc = gpp_sapa_ocb_malloc_sv(ocb)) return rc;

	if (!(sv = ocb->sv[sys][sat])) { // check if sv[sys][sat] is allocated
		ocb->sv[sys][sat] = (GPP_SAPA_OCB_SV*)calloc(1, sizeof(GPP_SAPA_OCB_SV));
		if (!(sv = ocb->sv[sys][sat])) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!sv->bias) {//check if orbit structure is allocated
		sv->bias = (pGPP_SAPA_OCB_SV_BIAS)calloc(1, sizeof(GPP_SAPA_OCB_SV_BIAS));
		if (!sv->bias) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}
	bias = sv->bias;


	if (!bias->pb) {
		bias->pb = (pGPP_SAPA_OCB_SV_BIAS_PB*)calloc(GPP_SAPA_MAX_SIG, sizeof(pGPP_SAPA_OCB_SV_BIAS_PB));// allocate pointer array with GPP_SAPA_MAX_SIG Pointers
		if (!bias->pb) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!bias->pb[sig]) {
		bias->pb[sig] = (pGPP_SAPA_OCB_SV_BIAS_PB)calloc(1, sizeof(GPP_SAPA_OCB_SV_BIAS_PB)); //allocate memory for SATPHASE_BIAS structure
		if (!bias->pb[sig]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}
	pb = bias->pb[sig];

	memcpy(pb, pset, sizeof(GPP_SAPA_OCB_SV_BIAS_PB)); 	//Copy Phase bias content
	GNSS_SET_IDX_IN_BITS_32(bias->pb_sig_bits, sig);		//set signal in signal bit mask for this satellite
	GNSS_SET_IDX_IN_BITS_64(ocb->sv_prn_bits[sys], sat);					//set sat ID in sv_prn_bits bit mask
	GNSS_SET_IDX_IN_BITS_64(ocb->pb_prn_bits[sys], sat);					//set sat ID in sv_prn_bits bit mask
	sv->ocb_bits |= (1 << GPP_SAPA_OCB_FLAG_IDX_BIAS);

	return 0; //GPP_SAPA_OK
}//gpp_sapa_ocb_add_pb()
//----------------------------------------------------------------------------------------------------------------------------

GPPLONG gpp_sapa_ocb_add_header(pGPP_SAPA_OCB ocb, GPPUINT1 sys, const pGPP_SAPA_OCB_HEADER pset)
{
	if (!ocb) return GPP_SAPA_ERR_INVALID_OCB;

	if (!ocb->header_block) { // check if sv[sys][sat] is allocated
		ocb->header_block = (pGPP_SAPA_OCB_HEADER*)calloc(GPP_SAPA_MAX_SYS, sizeof(pGPP_SAPA_OCB_HEADER));
		if (!ocb->header_block) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!ocb->header_block[sys]) {//check if orbit structure is allocated
		ocb->header_block[sys] = (pGPP_SAPA_OCB_HEADER)calloc(1, sizeof(GPP_SAPA_OCB_HEADER));
		if (!ocb->header_block[sys]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	memcpy(ocb->header_block[sys], pset, sizeof(GPP_SAPA_OCB_HEADER));	//copy clock data

	return 0;
}//gpp_sapa_ocb_add_header()

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

GPPLONG gpp_sapa_ocb_add_cb(pGPP_SAPA_OCB ocb, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 sig, const pGPP_SAPA_OCB_SV_BIAS_CB pset)
{
	pGPP_SAPA_OCB_SV sv = NULL;					// Pointer to OCB_SV
	pGPP_SAPA_OCB_SV_BIAS bias = NULL;			// Pointer to OCB_SV_BIAS
	pGPP_SAPA_OCB_SV_BIAS_CB cb = NULL;	// Pointer to OCB_SV_SATPHASEBIAS

	GPPLONG rc;					//control variable
	if (pset->cb_correction< GPP_SAPA_OCB_CB_CORRECTION_MIN || pset->cb_correction>GPP_SAPA_OCB_CB_CORRECTION_MAX) return 0;
	if(rc=gpp_sapa_ocb_malloc_sv(ocb)) return rc;

	if(!(sv=ocb->sv[sys][sat])) { // check if sv[sys][sat] is allocated
		ocb->sv[sys][sat]=(GPP_SAPA_OCB_SV*)calloc(1, sizeof(GPP_SAPA_OCB_SV));
		if (!(sv = ocb->sv[sys][sat])) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!sv->bias){//check if orbit structure is allocated
		sv->bias=(pGPP_SAPA_OCB_SV_BIAS)calloc(1, sizeof(GPP_SAPA_OCB_SV_BIAS));
		if (!sv->bias) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}
	bias=sv->bias;


	if(!bias->cb) {
		bias->cb=(pGPP_SAPA_OCB_SV_BIAS_CB*)calloc(GPP_SAPA_MAX_SIG, sizeof(pGPP_SAPA_OCB_SV_BIAS_CB));// allocate pointer array with GPP_SAPA_MAX_SIG Pointers
		if(!bias->cb) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if(!bias->cb[sig]) {
		bias->cb[sig] = (pGPP_SAPA_OCB_SV_BIAS_CB)calloc(1, sizeof(GPP_SAPA_OCB_SV_BIAS_CB)); //allocate memory for SATPHASE_BIAS structure
		if(!bias->cb[sig]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}
	cb = bias->cb[sig];

	memcpy(cb, pset, sizeof(GPP_SAPA_OCB_SV_BIAS_CB)); 	//Copy Phase bias content
	GNSS_SET_IDX_IN_BITS_32(bias->cb_sig_bits, sig);							//set signal in signal bit mask for this satellite
	GNSS_SET_IDX_IN_BITS_64(ocb->sv_prn_bits[sys], sat);							//set sat ID in sv_prn_bits bit mask
	GNSS_SET_IDX_IN_BITS_64(ocb->cb_prn_bits[sys], sat);							//set sat ID in sv_prn_bits bit mask
	sv->ocb_bits |= (1<<GPP_SAPA_OCB_FLAG_IDX_BIAS);

	return 0; //GPP_SAPA_OK
}//gpp_sapa_ocb_add_cb()



//==============================================functions to add data to structure For HPAC================================================================
GPPLONG gpp_sapa_hpac_add_header(pGPP_SAPA_HPAC hpac, const pGPP_SAPA_HPAC_HEADER pset)
{
	if (!hpac) return GPP_SAPA_ERR_INVALID_HPAC_AREA;

	if (!hpac->header_block) {//check if Header structure is allocated
		hpac->header_block = (pGPP_SAPA_HPAC_HEADER)calloc(1, sizeof(GPP_SAPA_HPAC_HEADER));
		if (!hpac->header_block) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	memcpy(hpac->header_block, pset, sizeof(GPP_SAPA_HPAC_HEADER));	//copy header data

	return 0;
}//gpp_sapa_hpac_add_header()
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
GPPLONG gpp_sapa_hpac_add_area(pGPP_SAPA_HPAC hpac, GPPUINT1 area, const pGPP_SAPA_HPAC_AREA pset)
{
	//pGPP_SAPA_HPAC_ATMO_BLOCK atmo = NULL;		// Pointer to ATMO

	if (!hpac) return GPP_SAPA_ERR_INVALID_HPAC_AREA;

	if (!hpac->atmo) {//check if atmo structure is allocated
		hpac->atmo = (pGPP_SAPA_HPAC_ATMO_BLOCK*)calloc(GPP_SAPA_MAX_AREA_COUNT, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK*));
		if (!hpac->atmo) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[area]) {//check if atmo[sys] structure is allocated
		hpac->atmo[area] = (pGPP_SAPA_HPAC_ATMO_BLOCK)calloc(1, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK));
		if (!hpac->atmo[area]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[area]->area_def) {//check if atmo[sys] structure is allocated
		hpac->atmo[area]->area_def = (pGPP_SAPA_HPAC_AREA)calloc(1, sizeof(GPP_SAPA_HPAC_AREA));
		if (!hpac->atmo[area]->area_def) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}
	memcpy(hpac->atmo[area]->area_def, pset, sizeof(GPP_SAPA_HPAC_AREA));	//copy atmo block data
	return 0; //GPP_SAPA_OK
}//gpp_sapa_hpac_add_area()
//-----------------------------------------------------------------------------------------------------------------------------------------------------
GPPLONG gpp_sapa_hpac_add_tropo(pGPP_SAPA_HPAC hpac,GPPUINT1 area, const pGPP_SAPA_HPAC_TROPO pset)
{
	//pGPP_SAPA_HPAC_ATMO_BLOCK atmo = NULL;		// Pointer to ATMO

	if (!hpac) return GPP_SAPA_ERR_INVALID_HPAC_AREA;
	if (!hpac->atmo) {//check if atmo structure is allocated
		hpac->atmo = (pGPP_SAPA_HPAC_ATMO_BLOCK*)calloc(GPP_SAPA_MAX_AREA_COUNT, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK*));
		if (!hpac->atmo) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[area]->tropo) {//check if tropo structure is allocated
		hpac->atmo[area]->tropo = (pGPP_SAPA_HPAC_TROPO)calloc(1, sizeof(GPP_SAPA_HPAC_TROPO));
		if (!hpac->atmo[area]->tropo) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	memcpy(hpac->atmo[area]->tropo, pset, sizeof(GPP_SAPA_HPAC_TROPO));	//copy clock data
	return 0; //GPP_SAPA_OK
}//gpp_sapa_hpac_add_tropo()
//--------------------------------------------------------------------------------------------------------------------------------------------------------
GPPLONG gpp_sapa_hpac_add_tropo_poly_coeff_block(pGPP_SAPA_HPAC hpac, GPPUINT1 area, const pGPP_SAPA_HPAC_TROPO_POLY_COEFFICIENT_BLOCK pset)
{
	//pGPP_SAPA_HPAC_ATMO_BLOCK atmo = NULL;		// Pointer to ATMO
	//pGPP_SAPA_HPAC_TROPO tropo = NULL;			// Pointer to TROPO
	if (!hpac) return GPP_SAPA_ERR_INVALID_HPAC_AREA;

	if (pset->tropo_avhd< GPP_SAPA_HPAC_AVHD_MIN || pset->tropo_avhd>GPP_SAPA_HPAC_AVHD_MAX) return 0;
	
	GPPUINT1 coeff_size = pset->tropo_coeff_size;
	if (pset->tropo_poly_coeff[TROPO_POLY_COEFF_INDX_T00] <SAPA_TROPO_COEFF_T00_MIN[coeff_size] || pset->tropo_poly_coeff[TROPO_POLY_COEFF_INDX_T00]>SAPA_TROPO_COEFF_T00_MAX[coeff_size])
		return 0;
	if (pset->tropo_poly_coeff[TROPO_POLY_COEFF_INDX_T01] <SAPA_TROPO_COEFF_T01_MIN[coeff_size] || pset->tropo_poly_coeff[TROPO_POLY_COEFF_INDX_T01]>SAPA_TROPO_COEFF_T01_MAX[coeff_size])
		return 0;
	if (pset->tropo_poly_coeff[TROPO_POLY_COEFF_INDX_T10] <SAPA_TROPO_COEFF_T01_MIN[coeff_size] || pset->tropo_poly_coeff[TROPO_POLY_COEFF_INDX_T10]>SAPA_TROPO_COEFF_T01_MAX[coeff_size])
		return 0;
	if (pset->tropo_poly_coeff[TROPO_POLY_COEFF_INDX_T11] <SAPA_TROPO_COEFF_T11_MIN[coeff_size] || pset->tropo_poly_coeff[TROPO_POLY_COEFF_INDX_T11]>SAPA_TROPO_COEFF_T11_MAX[coeff_size])
		return 0;

	if (!hpac->atmo) {//check if atmo structure is allocated
		hpac->atmo = (pGPP_SAPA_HPAC_ATMO_BLOCK*)calloc(GPP_SAPA_MAX_AREA_COUNT, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK*));
		if (!hpac->atmo) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[area]->tropo) {//check if tropo structure is allocated
		hpac->atmo[area]->tropo = (pGPP_SAPA_HPAC_TROPO)calloc(1, sizeof(GPP_SAPA_HPAC_TROPO));
		if (!hpac->atmo[area]->tropo) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[area]->tropo->tropo_poly_coeff_block) {//check if tropo  poly coeff structure is allocated
		hpac->atmo[area]->tropo->tropo_poly_coeff_block = (pGPP_SAPA_HPAC_TROPO_POLY_COEFFICIENT_BLOCK)calloc(1, sizeof(GPP_SAPA_HPAC_TROPO_POLY_COEFFICIENT_BLOCK));
		if (!hpac->atmo[area]->tropo->tropo_poly_coeff_block) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}
	memcpy(hpac->atmo[area]->tropo->tropo_poly_coeff_block, pset, sizeof(GPP_SAPA_HPAC_TROPO_POLY_COEFFICIENT_BLOCK));	//copy clock data
	return 0; //GPP_SAPA_OK
}//gpp_sapa_hpac_add_tropo_poly_coeff_block()
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
GPPLONG gpp_sapa_hpac_add_tropo_grid_block(pGPP_SAPA_HPAC hpac, GPPUINT1 area, const pGPP_SAPA_HPAC_TROPO_GRID_BLOCK pset)
{
	//pGPP_SAPA_HPAC_ATMO_BLOCK atmo = NULL;		// Pointer to ATMO
	//pGPP_SAPA_HPAC_TROPO tropo = NULL;			// Pointer to TROPO
	if (!hpac) return GPP_SAPA_ERR_INVALID_HPAC_AREA;
	GPPUINT1 no_of_grids,ig, res_size;
	res_size = pset->tropo_residual_size;
	no_of_grids = hpac->atmo[area]->area_def->number_of_grid_point;
	for (ig = 0; ig < no_of_grids; ig++)
	{
		if (pset->tropo_residuals[ig]< SAPA_TROPO_RESIDUAL_ZENITH_MIN[res_size] || pset->tropo_residuals[ig]>SAPA_TROPO_RESIDUAL_ZENITH_MAX[res_size])
			return 0;
	}
	if(pset->tropo_residuals)
	if (!hpac->atmo) {//check if atmo structure is allocated
		hpac->atmo = (pGPP_SAPA_HPAC_ATMO_BLOCK*)calloc(GPP_SAPA_MAX_AREA_COUNT, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK*));
		if (!hpac->atmo) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[area]->tropo) {//check if tropo structure is allocated
		hpac->atmo[area]->tropo = (pGPP_SAPA_HPAC_TROPO)calloc(1, sizeof(GPP_SAPA_HPAC_TROPO));
		if (!hpac->atmo[area]->tropo) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[area]->tropo->tropo_grid) {//check if tropo grid structure is allocated
		hpac->atmo[area]->tropo->tropo_grid = (pGPP_SAPA_HPAC_TROPO_GRID_BLOCK)calloc(1, sizeof(GPP_SAPA_HPAC_TROPO_GRID_BLOCK));
		if (!hpac->atmo[area]->tropo->tropo_grid) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}
	memcpy(hpac->atmo[area]->tropo->tropo_grid, pset, sizeof(GPP_SAPA_HPAC_TROPO_GRID_BLOCK));	//copy clock data
	return 0; //GPP_SAPA_OK
}//gpp_sapa_hpac_add_tropo_grid_block()
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
GPPLONG gpp_sapa_hpac_add_iono(pGPP_SAPA_HPAC hpac,GPPUINT1 area, const pGPP_SAPA_HPAC_IONO pset)
{
	//pGPP_SAPA_HPAC_ATMO_BLOCK atmo = NULL;		// Pointer to ATMO

	if (!hpac) return GPP_SAPA_ERR_INVALID_HPAC_AREA;

	if (!hpac->atmo) {//check if atmo structure is allocated
		hpac->atmo = (pGPP_SAPA_HPAC_ATMO_BLOCK*)calloc(GPP_SAPA_MAX_AREA_COUNT, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK*));
		if (!hpac->atmo) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[area]) {//check if atmo[area] structure is allocated
		hpac->atmo[area] = (pGPP_SAPA_HPAC_ATMO_BLOCK)calloc(1, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK));
		if (!hpac->atmo[area]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[area]->iono) {//check if iono structure is allocated
		hpac->atmo[area]->iono = (pGPP_SAPA_HPAC_IONO)calloc(1, sizeof(GPP_SAPA_HPAC_IONO));
		if (!hpac->atmo[area]->iono) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}
	memcpy(hpac->atmo[area]->iono, pset, sizeof(GPP_SAPA_HPAC_IONO));	//copy clock data
	return 0; //GPP_SAPA_OK
}//gpp_sapa_hpac_add_iono()

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
GPPLONG gpp_sapa_hpac_add_iono_sat_poly_block(pGPP_SAPA_HPAC hpac, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 area, const pGPP_SAPA_HPAC_IONO_SAT_POLY pset)
{
	//pGPP_SAPA_HPAC_ATMO_BLOCK atmo = NULL;		// Pointer to ATMO
	//pGPP_SAPA_HPAC_IONO iono = NULL;			// Pointer to OCB_SV_BIAS
	//pGPP_SAPA_HPAC_IONO_SAT_BLOCK iono_sat_block = NULL;
	if (!hpac) return GPP_SAPA_ERR_INVALID_HPAC_AREA;

	if (!hpac->atmo) {//check if atmo structure is allocated
		hpac->atmo = (pGPP_SAPA_HPAC_ATMO_BLOCK*)calloc(GPP_SAPA_MAX_AREA_COUNT, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK*));
		if (!hpac->atmo) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[area]) {//check if atmo[area] structure is allocated
		hpac->atmo[area] = (pGPP_SAPA_HPAC_ATMO_BLOCK)calloc(1, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK));
		if (!hpac->atmo[area]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[area]->iono) {//check if iono structure is allocated
		hpac->atmo[area]->iono = (pGPP_SAPA_HPAC_IONO)calloc(1, sizeof(GPP_SAPA_HPAC_IONO));
		if (!hpac->atmo[area]->iono) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[area]->iono->iono_sat_block) {////check if iono Satellite structure is allocated
		hpac->atmo[area]->iono->iono_sat_block = (pGPP_SAPA_HPAC_IONO_SAT_BLOCK**)calloc(GPP_SAPA_MAX_SYS, sizeof(GPP_SAPA_HPAC_IONO_SAT_BLOCK**));
		if (!hpac->atmo[area]->iono->iono_sat_block) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}
	if (!hpac->atmo[area]->iono->iono_sat_block[sys]) { // check if iono satelite [sys][sat] is allocated
		hpac->atmo[area]->iono->iono_sat_block[sys] = (pGPP_SAPA_HPAC_IONO_SAT_BLOCK*)calloc(GPP_SAPA_MAX_SAT, sizeof(GPP_SAPA_HPAC_IONO_SAT_BLOCK*));
		if (!hpac->atmo[area]->iono->iono_sat_block[sys]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}
	if (!hpac->atmo[area]->iono->iono_sat_block[sys][sat]) { // check if iono satelite [sys][sat] is allocated
		hpac->atmo[area]->iono->iono_sat_block[sys][sat] = (pGPP_SAPA_HPAC_IONO_SAT_BLOCK)calloc(1, sizeof(GPP_SAPA_HPAC_IONO_SAT_BLOCK));
		if (!hpac->atmo[area]->iono->iono_sat_block[sys][sat]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}
	if (!hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_sat_poly) {//check if iono satellite poly structure is allocated
		hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_sat_poly = (pGPP_SAPA_HPAC_IONO_SAT_POLY)calloc(1, sizeof(GPP_SAPA_HPAC_IONO_SAT_POLY));
		if (!hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_sat_poly) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}
	//printf("inq111%f\n",pset->iono_quality);

	memcpy(hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_sat_poly, pset, sizeof(GPP_SAPA_HPAC_IONO_SAT_POLY));

	//printf("inq2222%f\n", hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_sat_poly->iono_quality);

	GNSS_SET_IDX_IN_BITS_64(hpac->atmo[area]->iono->sat_prn_bits[sys], sat);
	return 0;
}//gpp_sapa_hpac_add_iono_sat_poly_block()
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
GPPLONG gpp_sapa_hpac_add_iono_sat_coeff_block(pGPP_SAPA_HPAC hpac, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 area, const pGPP_SAPA_HPAC_IONO_SAT_COEFFICIENT pset)
{
	//pGPP_SAPA_HPAC_ATMO_BLOCK atmo = NULL;		// Pointer to ATMO
	//pGPP_SAPA_HPAC_IONO iono = NULL;			// Pointer to OCB_SV_BIAS
	//pGPP_SAPA_HPAC_IONO_SAT_BLOCK iono_sat_block = NULL;
	if (!hpac) return GPP_SAPA_ERR_INVALID_HPAC_AREA;
	
	GPPUINT1 coeff_size = hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_sat_poly->iono_coeff_size;
	if (pset->iono_poly_coeff[IONO_POLY_COEFF_INDX_C00]< SAPA_TROPO_COEFF_C00_MIN[coeff_size] || pset->iono_poly_coeff[IONO_POLY_COEFF_INDX_C00]>SAPA_TROPO_COEFF_C00_MAX[coeff_size])
		return 0;
	if (pset->iono_poly_coeff[IONO_POLY_COEFF_INDX_C01]< SAPA_TROPO_COEFF_C01_MIN[coeff_size] || pset->iono_poly_coeff[IONO_POLY_COEFF_INDX_C01]>SAPA_TROPO_COEFF_C01_MAX[coeff_size])
		return 0;
	if (pset->iono_poly_coeff[IONO_POLY_COEFF_INDX_C10]< SAPA_TROPO_COEFF_C01_MIN[coeff_size] || pset->iono_poly_coeff[IONO_POLY_COEFF_INDX_C10]>SAPA_TROPO_COEFF_C01_MAX[coeff_size])
		return 0;
	if (pset->iono_poly_coeff[IONO_POLY_COEFF_INDX_C11]< SAPA_TROPO_COEFF_C11_MIN[coeff_size] || pset->iono_poly_coeff[IONO_POLY_COEFF_INDX_C11]>SAPA_TROPO_COEFF_C11_MAX[coeff_size])
		return 0;

	if (!hpac->atmo) {//check if atmo structure is allocated
		hpac->atmo = (pGPP_SAPA_HPAC_ATMO_BLOCK*)calloc(GPP_SAPA_MAX_AREA_COUNT, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK*));
		if (!hpac->atmo) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[area]) {//check if atmo[area] structure is allocated
		hpac->atmo[area] = (pGPP_SAPA_HPAC_ATMO_BLOCK)calloc(1, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK));
		if (!hpac->atmo[area]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[area]->iono) {//check if iono structure is allocated
		hpac->atmo[area]->iono = (pGPP_SAPA_HPAC_IONO)calloc(1, sizeof(GPP_SAPA_HPAC_IONO));
		if (!hpac->atmo[area]->iono) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[area]->iono->iono_sat_block) {////check if iono Satellite structure is allocated
		hpac->atmo[area]->iono->iono_sat_block = (pGPP_SAPA_HPAC_IONO_SAT_BLOCK**)calloc(GPP_SAPA_MAX_SYS, sizeof(GPP_SAPA_HPAC_IONO_SAT_BLOCK**));
		if (!hpac->atmo[area]->iono->iono_sat_block) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}
	if (!(hpac->atmo[area]->iono->iono_sat_block[sys])) { // check if iono satelite [sys][sat] is allocated
		hpac->atmo[area]->iono->iono_sat_block[sys] = (pGPP_SAPA_HPAC_IONO_SAT_BLOCK*)calloc(GPP_SAPA_MAX_SAT, sizeof(GPP_SAPA_HPAC_IONO_SAT_BLOCK*));
		if (!(hpac->atmo[area]->iono->iono_sat_block[sys])) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}
	if (!(hpac->atmo[area]->iono->iono_sat_block[sys][sat])) { // check if iono satelite [sys][sat] is allocated
		hpac->atmo[area]->iono->iono_sat_block[sys][sat] = (pGPP_SAPA_HPAC_IONO_SAT_BLOCK)calloc(1, sizeof(GPP_SAPA_HPAC_IONO_SAT_BLOCK));
		if (!(hpac->atmo[area]->iono->iono_sat_block[sys][sat])) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}
	if (!hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_sat_coeff) {//check if iono satellite structure is allocated
		hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_sat_coeff = (pGPP_SAPA_HPAC_IONO_SAT_COEFFICIENT)calloc(1, sizeof(GPP_SAPA_HPAC_IONO_SAT_COEFFICIENT));
		if (!hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_sat_coeff) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}
	memcpy(hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_sat_coeff, pset, sizeof(GPP_SAPA_HPAC_IONO_SAT_COEFFICIENT));
	GNSS_SET_IDX_IN_BITS_64(hpac->atmo[area]->iono->sat_prn_bits[sys], sat);		//set sat ID in sv_prn_bits bit mask
	return 0;
}//gpp_sapa_hpac_add_iono_sat_coeff_block()
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
GPPLONG gpp_sapa_hpac_add_iono_sat_grid_block(pGPP_SAPA_HPAC hpac, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 area, const pGPP_SAPA_HPAC_IONO_GRID_BLOCK pset)
{
	//pGPP_SAPA_HPAC_ATMO_BLOCK atmo = NULL;		// Pointer to ATMO
	//pGPP_SAPA_HPAC_IONO iono = NULL;			// Pointer to OCB_SV_BIAS
	//pGPP_SAPA_HPAC_IONO_SAT_BLOCK iono_sat_block = NULL;
	if (!hpac) return GPP_SAPA_ERR_INVALID_HPAC_AREA;

	GPPUINT1 no_of_grids, ig, res_size;
	res_size = pset->iono_residual_field_size;
	no_of_grids = hpac->atmo[area]->area_def->number_of_grid_point;
	for (ig = 0; ig < no_of_grids; ig++)
	{
		if (pset->iono_residuals[ig]< SAPA_TROPO_RESIDUAL_ZENITH_MIN[res_size] || pset->iono_residuals[ig]>SAPA_TROPO_RESIDUAL_ZENITH_MAX[res_size])
			return 0;
	}

	if (!hpac->atmo) {//check if atmo structure is allocated
		hpac->atmo = (pGPP_SAPA_HPAC_ATMO_BLOCK*)calloc(GPP_SAPA_MAX_AREA_COUNT, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK*));
		if (!hpac->atmo) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[area]) {//check if atmo[area] structure is allocated
		hpac->atmo[area] = (pGPP_SAPA_HPAC_ATMO_BLOCK)calloc(1, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK));
		if (!hpac->atmo[area]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[area]->iono) {//check if iono structure is allocated
		hpac->atmo[area]->iono = (pGPP_SAPA_HPAC_IONO)calloc(1, sizeof(GPP_SAPA_HPAC_IONO));
		if (!hpac->atmo[area]->iono) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[area]->iono->iono_sat_block) {////check if iono Satellite structure is allocated
		hpac->atmo[area]->iono->iono_sat_block = (pGPP_SAPA_HPAC_IONO_SAT_BLOCK**)calloc(GPP_SAPA_MAX_SYS, sizeof(GPP_SAPA_HPAC_IONO_SAT_BLOCK**));
		if (!hpac->atmo[area]->iono->iono_sat_block) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}
	if (!(hpac->atmo[area]->iono->iono_sat_block[sys])) { // check if iono satelite [sys][sat] is allocated
		hpac->atmo[area]->iono->iono_sat_block[sys] = (pGPP_SAPA_HPAC_IONO_SAT_BLOCK*)calloc(GPP_SAPA_MAX_SAT, sizeof(GPP_SAPA_HPAC_IONO_SAT_BLOCK*));
		if (!(hpac->atmo[area]->iono->iono_sat_block[sys])) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}
	if (!(hpac->atmo[area]->iono->iono_sat_block[sys][sat])) { // check if iono satelite [sys][sat] is allocated
		hpac->atmo[area]->iono->iono_sat_block[sys][sat] = (pGPP_SAPA_HPAC_IONO_SAT_BLOCK)calloc(1, sizeof(GPP_SAPA_HPAC_IONO_SAT_BLOCK));
		if (!(hpac->atmo[area]->iono->iono_sat_block[sys][sat])) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_grid) {//check if iono grid structure is allocated
		hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_grid = (pGPP_SAPA_HPAC_IONO_GRID_BLOCK)calloc(1, sizeof(GPP_SAPA_HPAC_IONO_GRID_BLOCK));
		if (!hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_grid) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}
	memcpy(hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_grid, pset, sizeof(GPP_SAPA_HPAC_IONO_GRID_BLOCK));
	GNSS_SET_IDX_IN_BITS_64(hpac->atmo[area]->iono->sat_prn_bits[sys], sat);       //set sat ID in sv_prn_bits bit mask
	return 0;
}//gpp_sapa_hpac_add_iono_sat_grid_block()
//
GPPLONG gpp_sapa_hpac_free_hpac(pGPP_SAPA_HPAC hpac)
{

	if (hpac) {
		if (hpac->header_block)
		{
			//memset(hpac->header_block, 0, sizeof(GPP_SAPA_HPAC_HEADER));
			free(hpac->header_block);
			hpac->header_block = NULL;
		}
		if (hpac->atmo)
		{
			GPPUINT1 area;
			for (area = 0; area < GPP_SAPA_MAX_AREA_COUNT; area++)
			{
				if (hpac->atmo[area])
				{
					if (hpac->atmo[area]->area_def)
					{
						//memset(hpac->atmo[area]->area_def, 0, sizeof(GPP_SAPA_HPAC_AREA));
						free(hpac->atmo[area]->area_def);
					}
					if (hpac->atmo[area]->tropo)
					{
						if (hpac->atmo[area]->tropo->tropo_poly_coeff_block)
						{
							//memset(hpac->atmo[area]->tropo->tropo_poly_coeff_block, 0, sizeof(GPP_SAPA_HPAC_TROPO_POLY_COEFFICIENT_BLOCK));
							free(hpac->atmo[area]->tropo->tropo_poly_coeff_block);
						}
						if (hpac->atmo[area]->tropo->tropo_grid)
						{
							//memset(hpac->atmo[area]->tropo->tropo_grid, 0, sizeof(GPP_SAPA_HPAC_TROPO_GRID_BLOCK));
							free(hpac->atmo[area]->tropo->tropo_grid);
						}
						//memset(hpac->atmo[area]->tropo, 0, sizeof(GPP_SAPA_HPAC_TROPO));
						free(hpac->atmo[area]->tropo);
					}
					if (hpac->atmo[area]->iono->iono_sat_block)
					{
						GPPUINT1 sys;
						for (sys = 0; sys < GPP_SAPA_MAX_SYS; sys++)
						{
							if (hpac->atmo[area]->iono->iono_sat_block[sys]) {
								GPPUINT1 sat;
								for (sat = 0; sat < GPP_SAPA_MAX_SAT; sat++)
								{
									if (hpac->atmo[area]->iono->iono_sat_block[sys][sat]) {
										if (hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_sat_poly)
										{
											//memset(hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_sat_poly, 0, sizeof(GPP_SAPA_HPAC_IONO_SAT_POLY));
											free(hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_sat_poly);
										}
										if (hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_sat_coeff)
										{
											//memset(hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_sat_coeff, 0, sizeof(GPP_SAPA_HPAC_IONO_SAT_COEFFICIENT));
											free(hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_sat_coeff);
										}
										if (hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_grid)
										{
											//memset(hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_grid, 0, sizeof(GPP_SAPA_HPAC_IONO_GRID_BLOCK));
											free(hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_grid);
										}
										//memset(hpac->atmo[area]->iono->iono_sat_block[sys][sat], 0, sizeof(GPP_SAPA_HPAC_IONO_SAT_BLOCK));
										free(hpac->atmo[area]->iono->iono_sat_block[sys][sat]);
									}
								}
								//memset(hpac->atmo[area]->iono->iono_sat_block[sys], 0, sizeof(GPP_SAPA_HPAC_IONO_SAT_BLOCK));
								free(hpac->atmo[area]->iono->iono_sat_block[sys]);
							}
						}
						//memset(hpac->atmo[area]->iono->iono_sat_block, 0, sizeof(GPP_SAPA_HPAC_IONO_SAT_BLOCK));
						free(hpac->atmo[area]->iono->iono_sat_block);
					}
					//memset(hpac->atmo[area], 0, sizeof(GPP_SAPA_HPAC_AREA));
					free(hpac->atmo[area]);
				}

			}
			//memset(hpac->atmo, 0, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK));
			free(hpac->atmo);
			hpac->atmo = NULL;
		}

	}

	return 0;
}//gpp_sapa_hpac_free_hpac()
//=============================================== functions to add data to structure For Area ====================================================================

GPPLONG gpp_sapa_area_add_header(pGPP_SAPA_AREA p_area, const pGPP_SAPA_AREA_DEF_HEADER pset)
{
	if (!p_area) return GPP_SAPA_ERR_INVALID_AREA;

	if (!p_area->header_block) {//check if orbit structure is allocated
		p_area->header_block = (pGPP_SAPA_AREA_DEF_HEADER)calloc(1, sizeof(GPP_SAPA_AREA_DEF_HEADER));
		if (!p_area->header_block) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	memcpy(p_area->header_block, pset, sizeof(GPP_SAPA_AREA_DEF_HEADER));	//copy header data

	return 0;
}//gpp_sapa_area_add_header()

GPPLONG gpp_sapa_area_add_area_def(pGPP_SAPA_AREA p_area,GPPUINT1 area, const pGPP_SAPA_AREA_DEF_BLOCK pset)
{
	//pGPP_SAPA_AREA_DEF_BLOCK area_def_block = NULL;			// Pointer to AREA_DEF_BLOCK

	if (!p_area) return GPP_SAPA_ERR_INVALID_AREA;
	if (pset->area_ref_lat< GPP_SAPA_AREA_REF_LAT_MIN || pset->area_ref_lat>GPP_SAPA_AREA_REF_LAT_MAX) return 0;
	if (pset->area_ref_long< GPP_SAPA_AREA_REF_LONG_MIN || pset->area_ref_long > GPP_SAPA_AREA_REF_LONG_MAX) return 0;
	if (pset->area_lat_grid_node_spacing< GPP_SAPA_AREA_GRID_LAT_SPACING_MIN || pset->area_lat_grid_node_spacing > GPP_SAPA_AREA_GRID_LAT_SPACING_MAX) return 0;
	if (pset->area_long_grid_node_spacing < GPP_SAPA_AREA_GRID_LONG_SPACING_MIN || pset->area_long_grid_node_spacing > GPP_SAPA_AREA_GRID_LONG_SPACING_MAX) return 0;

	if (!p_area->area_def_block) {//check if orbit structure is allocated
		p_area->area_def_block = (pGPP_SAPA_AREA_DEF_BLOCK*)calloc(GPP_SAPA_MAX_AREA_COUNT, sizeof(pGPP_SAPA_AREA_DEF_BLOCK));
		if (!p_area->area_def_block) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!p_area->area_def_block[area]) { // check if sv[sys][sat] is allocated
		p_area->area_def_block[area] = (pGPP_SAPA_AREA_DEF_BLOCK)calloc(1, sizeof(GPP_SAPA_AREA_DEF_BLOCK));
		if (!(p_area->area_def_block[area])) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}
	memcpy(p_area->area_def_block[area], pset, sizeof(GPP_SAPA_AREA_DEF_BLOCK));

	return 0;
}//gpp_sapa_area_add_area_def()
/************************************************************************************************************
* \brief Free SAPA_OCB_HANDLDE in SAPA_HANDLE
************************************************************************************************************/
	//GPPLONG gpp_sapa_handle_free_ocbHdl(SAPA_HANDLE *sapaHdl)
	//{
	// GPPUINT1 sys, icnfg;
	// if(!sapaHdl) return -1;
	//
	// if(!sapaHdl->ocbHdl) return 0;
	//
	// for(sys=0; sys<SAPA_MAX_SYS; sys++){
	//  if(!sapaHdl->ocbHdl[sys]) continue;
	//
	//  for(icnfg=0; icnfg<GPP_SAPA_MAX_OCB_CONFIGS; icnfg++){
	//   SAPA_OCB_HANDLE *ocbHdl=NULL;
	//
	//   if(!(ocbHdl=sapaHdl->ocbHdl[sys][icnfg])) continue;
	//
	//   memset(ocbHdl, 0, sizeof(SAPA_OCB_HANDLE));
	//   free(sapaHdl->ocbHdl[sys][icnfg]);
	//  }//icnfg
	//  memset(sapaHdl->ocbHdl[sys],0, GPP_SAPA_MAX_OCB_CONFIGS*sizeof(SAPA_OCB_HANDLE*));
	//  free(sapaHdl->ocbHdl[sys]);
	// }
	// memset(sapaHdl->ocbHdl, 0, SAPA_MAX_SYS*sizeof(SAPA_OCB_HANDLE**));
	// free(sapaHdl->ocbHdl);
	// sapaHdl->ocbHdl=NULL;
	//
	// return 0;
	//}//gpp_sapa_handle_free_ocbHdl()
	//
	GPPLONG gpp_sapa_handle_malloc_hpacHdl(pSAPA_HANDLE sapaHdl)
{
	if (!sapaHdl) return -1;

	if (!sapaHdl->hpacHdl)
	{
		sapaHdl->hpacHdl = (pSAPA_HPAC_HANDLE)calloc(1, sizeof(SAPA_HPAC_HANDLE));
		if (!sapaHdl->hpacHdl) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;

		GPPUINT1 area, sys, sat;

		for (area = 0; area < GPP_SAPA_MAX_AREA_COUNT; area++)
		{
			sapaHdl->hpacHdl->hpac_area_handle[area] = (pSAPA_HPAC_HANDLE_AREA)calloc(GPP_SAPA_MAX_AREA_COUNT, sizeof(SAPA_HPAC_HANDLE_AREA));
			if (!sapaHdl->hpacHdl->hpac_area_handle[area]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;

			for (sys = 0; sys < GPP_SAPA_MAX_SYS; sys++)
			{
				sapaHdl->hpacHdl->hpac_area_handle[area]->iono_handle[sys] = (pSAPA_HPAC_HANDLE_IONO*)calloc(GPP_SAPA_MAX_SYS, sizeof(SAPA_HPAC_HANDLE_IONO*));
				if (!sapaHdl->hpacHdl->hpac_area_handle[area]->iono_handle[sys]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;

				for (sat = 0; sat < GPP_SAPA_MAX_SAT; sat++)
				{
					sapaHdl->hpacHdl->hpac_area_handle[area]->iono_handle[sys][sat] = (SAPA_HPAC_HANDLE_IONO*)calloc(GPP_SAPA_MAX_SAT,sizeof(SAPA_HPAC_HANDLE_IONO));
					if (!sapaHdl->hpacHdl->hpac_area_handle[area]->iono_handle[sys][sat]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
				}
			}
		}
	}
	return 0; //ok
}

GPPLONG gpp_sapa_handle_malloc_ocbHdl(pSAPA_HANDLE sapaHdl)
{
	if (!sapaHdl) return -1;

	if (!sapaHdl->ocbHdl)
	{
		GPPUINT1 sys, config;
		sapaHdl->ocbHdl = (pSAPA_OCB_HANDLE **)calloc(SAPA_MAX_SYS, sizeof(pSAPA_OCB_HANDLE*));
		if (!sapaHdl->ocbHdl) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;

		for (sys = 0; sys < SAPA_MAX_SYS; sys++)
		{
			sapaHdl->ocbHdl[sys] = (pSAPA_OCB_HANDLE *)calloc(GPP_SAPA_MAX_OCB_CONFIGS, sizeof(pSAPA_OCB_HANDLE));

			if (!(sapaHdl->ocbHdl[sys])) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
			for (config = 0; config < GPP_SAPA_MAX_OCB_CONFIGS; config++)
			{
				sapaHdl->ocbHdl[sys]->ocb_sv_handle[config] = (pSAPA_OCB_HANDLE_SV)calloc(1, sizeof(SAPA_OCB_HANDLE_SV));
				if (!sapaHdl->ocbHdl[sys]->ocb_sv_handle[config]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
			}
		}
	}

	return 0; //ok

}


GPPLONG gpp_sapa_handle_free_hpachdl(SAPA_HANDLE *sapaHdl)
{
	GPPUINT1 sys, area, sat;

	if (!sapaHdl) return -1;

	if (!sapaHdl->hpacHdl) return 0;

	for (area = 0; area < GPP_SAPA_MAX_AREA_COUNT; area++)
	{
		if (!sapaHdl->hpacHdl->hpac_area_handle[area])
			continue;
		for (sys = 0; sys < GPP_SAPA_MAX_SYS; sys++)
		{
			if (!sapaHdl->hpacHdl->hpac_area_handle[area]->iono_handle[sys])
				continue;
			for (sat = 0; sat < GPP_SAPA_MAX_SAT; sat++)
			{
				if (!sapaHdl->hpacHdl->hpac_area_handle[area]->iono_handle[sys][sat])
					continue;
				free(sapaHdl->hpacHdl->hpac_area_handle[area]->iono_handle[sys][sat]);
			}

			free(sapaHdl->hpacHdl->hpac_area_handle[area]->iono_handle[sys]);

		}
		free(sapaHdl->hpacHdl->hpac_area_handle[area]);
	}

	free(sapaHdl->hpacHdl);
	return 0; //ok
}
//GPPLONG gpp_sapa_handle_malloc_ocbHdl(pSAPA_HANDLE sapaHdl)
//{
//	if (!sapaHdl) return -1;
//
//	if (!sapaHdl->ocbHdl)
//	{
//		GPPUINT1 sys;
//		sapaHdl->ocbHdl = (pSAPA_OCB_HANDLE **)calloc(GPP_SAPA_MAX_OCB_CONFIGS, sizeof(pSAPA_OCB_HANDLE *));
//
//		if (!sapaHdl->ocbHdl) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
//
//		for (sys = 0; sys < SAPA_MAX_SYS; sys++)
//		{
//			sapaHdl->ocbHdl[sys] = (pSAPA_OCB_HANDLE *)calloc(GPP_SAPA_MAX_OCB_CONFIGS, sizeof(pSAPA_OCB_HANDLE));
//
//			if (!(sapaHdl->ocbHdl[sys])) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
//		}
//	}
//
//	return 0; //ok
//
//}//gpp_sapa_sapaHdl_malloc_ocbHdl()



//GPPLONG gpp_sapa_config_add_ocb_config(SAPA_HANDLE *sapaHdl, GPPUINT1 sys, const SAPA_OCB_HANDLE *pset, FILE *fp)
//{
//	GPPUINT1 icnfg = 0;
//
//	if (!sapaHdl) return -1;
//	if (!pset) return GPP_SAPA_ERR_INVALID_OCB_HANDLE;
//
//	if (sys >= SAPA_MAX_SYS) return GPP_SAPA_ERR_INVALID_SYS;
//
//	if (!sapaHdl->ocbHdl) {
//		GPPLONG rc;
//		if (rc = gpp_sapa_handle_malloc_ocbHdl(sapaHdl))
//			return rc;
//	}
//	if (sapaHdl->ocb_config_bits[sys] >= (1 << GPP_SAPA_MAX_OCB_CONFIGS))
//	{
//		fprintf(fp, "SSRM2SAPA ERROR: TOO many OCB configs!\n");
//		return GPP_SAPA_ERR_INVALID_OCB_HANDLE;
//	}
//
//	for (icnfg = 0; icnfg < GPP_SAPA_MAX_OCB_CONFIGS; icnfg++)
//	{
//		if (!sapaHdl->ocbHdl[sys][icnfg])
//		{
//			sapaHdl->ocbHdl[sys][icnfg] = (SAPA_OCB_HANDLE*)calloc(1, sizeof(SAPA_OCB_HANDLE));
//			if (!(sapaHdl->ocbHdl[sys][icnfg])) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
//
//			memcpy(sapaHdl->ocbHdl[sys][icnfg], pset, sizeof(SAPA_OCB_HANDLE));
//			sapaHdl->ocb_config_bits[sys] = (1 << icnfg);
//			break;
//		}
//	}
//
//}

//==================================================================================================================================
// hpac malloc


//GPPLONG gpp_sapa_handle_malloc_hpacHdl(pSAPA_HANDLE sapaHdl)
//{
//	if (!sapaHdl) return -1;
//
//	if (!sapaHdl->hpacHdl)
//	{
//		GPPUINT1 area, sys, config,sat;
//		for (sys = 0; sys < SAPA_MAX_SYS; sys++)
//		{
//			for (area = 0; area < GPP_SAPA_MAX_AREA_COUNT; area++)
//			{
//				sapaHdl->hpacHdl[sys][area] = (pSAPA_HPAC_HANDLE*)calloc(GPP_SAPA_MAX_AREA_COUNT, sizeof(pSAPA_HPAC_HANDLE));
//				if (!sapaHdl->hpacHdl[sys][area]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
//
//				for (sat = 0; sat < GPP_SAPA_MAX_SAT; sat++)
//				{
//					sapaHdl->hpacHdl[sys][area][sat] = (pSAPA_HPAC_HANDLE)calloc(GPP_SAPA_MAX_SAT, sizeof(SAPA_HPAC_HANDLE));
//
//					if (!sapaHdl->hpacHdl[sys][area][sat]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
//				}
//			}
//		}
//
//	}
//	return 0; //ok
//
//}//gpp_sapa_sapaHdl_malloc_hpacHdl()



//GPPLONG gpp_sapa_config_add_hpac_config(SAPA_HANDLE *sapaHdl, GPPUINT1 sys, const SAPA_HPAC_HANDLE *pset, FILE *fp)
//{
//	GPPUINT1 icnfg = 0, sat;
//
//	if (!sapaHdl) return -1;
//	if (!pset) return GPP_SAPA_ERR_INVALID_HPAC_HANDLE;
//
//	if (sys >= SAPA_MAX_SYS) return GPP_SAPA_ERR_INVALID_SYS;
//
//	if (!sapaHdl->hpacHdl) {
//		GPPLONG rc;
//		if (rc = gpp_sapa_handle_malloc_hpacHdl(sapaHdl))
//			return rc;
//	}
//	//define GPP_MAX_HPAC_CONFIGS
//
//	for (sys = 0; sys < SAPA_MAX_SYS; sys++)
//	{
//		for (icnfg = 0; icnfg < GPP_MAX_HPAC_CONFIGS; icnfg++)
//		{
//			if (!sapaHdl->hpacHdl[sys][icnfg])
//			{
//				sapaHdl->hpacHdl[sys][icnfg] = (SAPA_HPAC_HANDLE*)calloc(1, sizeof(SAPA_HPAC_HANDLE));
//				if (!(sapaHdl->hpacHdl[sys][icnfg])) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
//
//				memcpy(sapaHdl->hpacHdl[sys][icnfg], pset, sizeof(SAPA_HPAC_HANDLE));
//				break;
//			}
//		}
//
//	}
//}
//

//================================================================================================================================

//GPPLONG gpp_sapa_config_add_gad_config(SAPA_HANDLE *sapaHdl,GPPUINT1 sys, const SAPA_GAD_HANDLE *pset, FILE *fp)
//{
//	if (!sapaHdl) return -1;
//	if (!pset) return GPP_SAPA_ERR_INVALID_GAD_HANDLE;
//
//	//if (sys >= SAPA_MAX_SYS) return GPP_SAPA_ERR_INVALID_SYS;
//
//	//if (!sapaHdl->gadHdl)
//	// if (rc = gpp_sapa_handle_malloc_gadHdl(sapaHdl))
//	//  return rc;
//
//	sapaHdl->gadHdl[sys] = (SAPA_GAD_HANDLE*)calloc(1, sizeof(SAPA_GAD_HANDLE));
//
//	memcpy(sapaHdl->gadHdl, pset, sizeof(SAPA_GAD_HANDLE));
//
//}
//
GPPLONG gpp_sapa_area_free_area(pGPP_SAPA_AREA area)
{
	GPPUINT1 iarea;

	if (!area) return 0;
	if (!area->area_def_block) return 0;

	for (iarea = 0; iarea < GPP_SAPA_MAX_AREA_COUNT; iarea++) {
		if (area->area_def_block[iarea]) {
			free(area->area_def_block[iarea]);
			area->area_def_block[iarea] = NULL;
		}
	}

	free(area->area_def_block);
	area->area_def_block = NULL;

	return 0;

}//gpp_sapa_area_free_area()
extern GPPLONG gpp_sapa_float2buffer(GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos, GPPDOUBLE min, GPPDOUBLE max, GPPUINT1 bits, GPPDOUBLE res, GPPUINT2 *invalid, GPPDOUBLE value)
{
	GN_LONG lval;

	if (value<min || value>max) {
		if (invalid) {
			gn_add_long_to_buffer(buffer, byte_pos, bit_pos, bits, *invalid);
		}
	}

	lval = (value - min) / res;

	gn_add_val_long_to_buffer(buffer, byte_pos, bit_pos, bits, lval);

} /* gpp_sapa_float2buffer() */

extern GPPFLOAT gpp_sapa_buffer2float(const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos, GPPDOUBLE min, GPPUINT1 bits, GPPDOUBLE res, GPPUINT2 *invalid)
{
	GN_LONG lval = gn_get_long_from_buffer(buffer, byte_pos, bit_pos, bits);
	if (invalid == lval)
		return lval;
	else
		return ((lval*res) + min);

} /* gpp_sapa_buffer2float() */
GPPLONG gpp_sapa_get_bit_diff(GPPLONG byte_pos, GPPLONG bit_pos, GPPLONG byte_pos0, GPPLONG bit_pos0)
{
	return (byte_pos - byte_pos0) * 8 + (bit_pos - bit_pos0);
}

void gpp_sapa_get_area_bits(GPPUINT8*area_bits, int value)
{
	area_bits[value / 64] = (1 << (value % 64)) | area_bits[value / 64];
}

void gpp_sapa_get_area_bits_value(GPPUINT8*area_bits, GPPUINT8*arr)
{
	int z = 1;
	arr = (GPPUINT8*)malloc(257 * sizeof(GPPUINT8));
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 64; j++)
			if (area_bits[i] & (63 - j) == 1) arr[z++] = 64 * i + j;
	arr[0] = z - 1;
}
//============================================================================================================================================
//											Needed for testing (Alternative will we replaced)
//============================================================================================================================================
//Returns 1 if a bit at position pos in cons_bits is set else return 0
GPPUINT1 gpp_sapa_get_constellation_present_bit(GPPUINT2 cons_bits, GPPUINT1 pos)
{
	GPPUINT2 base = 1;
	return (cons_bits & (base << pos)) ? 1 : 0;
}

//Returns highest order of cons_bit set
GPPUINT1 gpp_sapa_get_highest_cons_set(GPPUINT2 cons_bit)
{
	GPPUINT1 max_cons_id = 0, cons_id;
	for (cons_id = 0; cons_id < 12; cons_id++)
	{
		if ((cons_bit >> cons_id) & 1)
		{
			max_cons_id = cons_id;
		}
	}
	return(max_cons_id);
}

//Sets cons_bit position
GPPUINT1 gpp_sapa_set_cons_bit(GPPUINT1 cons_bits, GPPUINT1 pos)
{
	return ((1 << pos) | cons_bits);
}

//============================================================================================================================================

/************************************************************************************************************
 *	\brief Free SAPA_OCB_HANDLDE in SAPA_HANDLE
 ************************************************************************************************************/
//GPPLONG gpp_sapa_handle_free_ocbHdl(SAPA_HANDLE *sapaHdl)
//{
//	GPPUINT1 sys, icnfg;
//	if(!sapaHdl) return -1;
//
//	if(!sapaHdl->ocbHdl) return 0;
//
//	for(sys=0; sys<SAPA_MAX_SYS; sys++){
//		if(!sapaHdl->ocbHdl[sys]) continue;
//
//		for(icnfg=0; icnfg<GPP_SAPA_MAX_OCB_CONFIGS; icnfg++){
//			SAPA_OCB_HANDLE *ocbHdl=NULL;
//
//			if(!(ocbHdl=sapaHdl->ocbHdl[sys][icnfg])) continue;
//
//			memset(ocbHdl, 0, sizeof(SAPA_OCB_HANDLE));
//			free(sapaHdl->ocbHdl[sys][icnfg]);
//		}//icnfg
//		memset(sapaHdl->ocbHdl[sys],0, GPP_SAPA_MAX_OCB_CONFIGS*sizeof(SAPA_OCB_HANDLE*));
//		free(sapaHdl->ocbHdl[sys]);
//	}
//	memset(sapaHdl->ocbHdl, 0, SAPA_MAX_SYS*sizeof(SAPA_OCB_HANDLE**));
//	free(sapaHdl->ocbHdl);
//	sapaHdl->ocbHdl=NULL;
//
//	return 0;
//}//gpp_sapa_handle_free_ocbHdl()
//
//GPPLONG gpp_sapa_handle_free_hpacHdl(SAPA_HANDLE *sapaHdl)
//{
//	GPPUINT1 sys, area, sat;
//
//	if (!sapaHdl) return -1;
//
//	if (!sapaHdl->hpacHdl) return 0;
//
//	for (sys = 0; sys < SAPA_MAX_SYS; sys++)
//	{
//		if (!sapaHdl->hpacHdl[sys]) continue;
//
//		for (area = 0; area < GPP_SAPA_MAX_AREA_COUNT; area++)
//		{
//
//			for (sat = 0; sat < GPP_SAPA_MAX_SAT; sat++)
//			{
//				SAPA_HPAC_HANDLE* hpacHdl = NULL;
//				if (!(hpacHdl = sapaHdl->hpacHdl[sys][area][sat]))
//					continue;
//
//				memset(hpacHdl, 0, sizeof(SAPA_HPAC_HANDLE));
//				free(sapaHdl->hpacHdl[sys][area][sat]);
//			}
//
//			memset(sapaHdl->hpacHdl, 0, sizeof(SAPA_HPAC_HANDLE));
//			free(sapaHdl->hpacHdl[sys][area]);
//
//		}
//
//	}
//
//	return 0; //ok
//}
//
//GPPLONG gpp_sapa_handle_free_gadHdl(SAPA_HANDLE *sapaHdl)
//{
//	if (!sapaHdl) return -1;
//
//	if (!sapaHdl->gadHdl) return 0;
//
//	free(sapaHdl->gadHdl);
//
//	return 0;  //ok
//
//}
///************************************************************************************************************
// *	\brief Free SAPA_OCB_HANDLDE in SAPA_HANDLE
// ************************************************************************************************************/
//GPPLONG gpp_sapa_handle_malloc_ocbHdl(SAPA_HANDLE *sapaHdl)
//{
//	if(!sapaHdl) return -1;
//
//	if(!sapaHdl->ocbHdl){
//		sapaHdl->ocbHdl=(pSAPA_OCB_HANDLE**)calloc(SAPA_MAX_SYS, sizeof(SAPA_OCB_HANDLE**));
//		if(!sapaHdl->ocbHdl) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
//
//		GPPUINT1 sys;
//		for(sys=0; sys<SAPA_MAX_SYS; sys++) {
//			sapaHdl->ocbHdl[sys] = (SAPA_OCB_HANDLE**)calloc(GPP_SAPA_MAX_OCB_CONFIGS, sizeof(SAPA_OCB_HANDLE*));
//			if(!sapaHdl->ocbHdl[sys]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
//		}
//	}
//	return 0;
//}//gpp_sapa_handle_free_ocbHdl()

/*
if (!ocb->sv) {
		GPPUINT1 sys;
		ocb->sv = (pGPP_SAPA_OCB_SV**)calloc(GPP_SAPA_MAX_SYS, sizeof(GPP_SAPA_OCB**));

		if(!ocb->sv) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;

		for(sys=0; sys<GPP_SAPA_MAX_SYS; sys++) {
			ocb->sv[sys] = (GPP_SAPA_OCB_SV**)calloc(GPP_SAPA_MAX_SAT, sizeof(GPP_SAPA_OCB_SV));

			if (!(ocb->sv[sys])) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
		}
	}

*/

/************************************************************************************************************
 *	\brief Free SAPA_HANDLE
 ************************************************************************************************************/
GPPLONG gpp_sapa_handle_free_handle(SAPA_HANDLE **ppSapaHdl)
{

	SAPA_HANDLE *sapaHdl;

	if(!ppSapaHdl) return -1;
	sapaHdl=*ppSapaHdl;

	if(!sapaHdl) return 0;

	//gpp_sapa_handle_free_ocbHdl(sapaHdl);

	free(*ppSapaHdl);
	*ppSapaHdl=NULL;

	return 0;
}//gpp_sapa_handle_free_handle()

/************************************************************************************************************
 *	\brief Malloc SAPA_HANDLE
 ************************************************************************************************************/
GPPLONG gpp_sapa_handle_malloc_handle(SAPA_HANDLE **ppSapaHdl)
{
	if(!ppSapaHdl) return -1;
	if(*ppSapaHdl) gpp_sapa_handle_free_handle(ppSapaHdl);

	*ppSapaHdl=(SAPA_HANDLE*)calloc(1,sizeof(SAPA_HANDLE));
	if(!(*ppSapaHdl)) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;

	return 0;
}//gpp_sapa_handle_malloc_handle()

//--------------------------------------------------------------------Transport Layer SAPA OCB message----------------------------------------------------------------------------
GPPLONG gpp_sapa_ocb_buffer_to_sapa_buffer(const GPPUCHAR *ocb_buffer,GPPLONG len_sapa_bits, GPPLONG ea_flag, GPPLONG message_crc_type,GPPLONG crc_frame, GPPUCHAR *sapa_buffer)
{
	GPPLONG byte_pos =0, bit_pos = 0, num_data_bytes = 0;
	gn_add_ulong_to_buffer(sapa_buffer, &byte_pos, &bit_pos, 8, SAPA_PREAMBLE);
	gn_add_ulong_to_buffer(sapa_buffer, &byte_pos, &bit_pos, 7, SAPA_TYPE_OCB);

	num_data_bytes = length_bytes_from_bits(len_sapa_bits);
	if (!num_data_bytes) return GPP_SAPA_ERR_PAYLOAD_LENGTH;

	gn_add_ulong_to_buffer(sapa_buffer, &byte_pos, &bit_pos, 10, num_data_bytes);
	gn_add_ulong_to_buffer(sapa_buffer, &byte_pos, &bit_pos, 1, ea_flag);
	gn_add_ulong_to_buffer(sapa_buffer, &byte_pos, &bit_pos, 2, message_crc_type);
	gn_add_ulong_to_buffer(sapa_buffer, &byte_pos, &bit_pos, 4, crc_frame);

	memcpy((sapa_buffer+byte_pos), ocb_buffer, num_data_bytes);

	byte_pos += num_data_bytes;

	gn_add_ulong_to_buffer(sapa_buffer, &byte_pos, &bit_pos, SAPA_CRC_BYTES[message_crc_type] ,0);

	return 0;
}

GPPLONG gpp_sapa_sapa_buffer_to_ocb_buffer(GPPUCHAR *ocb_buffer, GPPLONG *len_sapa_bits, GPPLONG *ea_flag, GPPLONG *message_crc_type, GPPLONG *crc_frame, const GPPUCHAR *sapa_buffer)
{
	GPPLONG byte_pos = 0, bit_pos = 0, numDataBytes = 0;

	int type;
	long sapa_preamble = gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, 8);
	if (sapa_preamble != SAPA_PREAMBLE) return GPP_SAPA_ERR_PREAMBLE;

	type = gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, 7);

	if (type != SAPA_TYPE_OCB) return GPP_SAPA_ERR_TYPE;

	numDataBytes = gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, 10);

	if (!numDataBytes) return GPP_SAPA_ERR_PAYLOAD_LENGTH;
	*len_sapa_bits = numDataBytes * 8;
	*ea_flag = gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, 1);

	*message_crc_type = gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, 2);
	if (*message_crc_type > 3) return GPP_SAPA_ERR_CRC_TYPE;

	*crc_frame = gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, 4);

	memcpy(ocb_buffer, (sapa_buffer + byte_pos), numDataBytes);
	byte_pos += numDataBytes;

	GPPLONG crc = gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, SAPA_CRC_BYTES[*message_crc_type]);

	return 0;
}

GPPLONG gpp_sapa_hpac_buffer_to_sapa_buffer(const GPPUCHAR *hpac_buffer, GPPLONG len_sapa_bits, GPPLONG ea_flag, GPPLONG message_crc_type, GPPLONG crc_frame, GPPUCHAR *sapa_buffer)
{
	GPPLONG byte_pos = 0, bit_pos = 0, num_data_bytes = 0;
	gn_add_ulong_to_buffer(sapa_buffer, &byte_pos, &bit_pos, 8, SAPA_PREAMBLE);
	gn_add_ulong_to_buffer(sapa_buffer, &byte_pos, &bit_pos, 7, SAPA_TYPE_HPAC);

	num_data_bytes = length_bytes_from_bits(len_sapa_bits);
	if (!num_data_bytes) return GPP_SAPA_ERR_PAYLOAD_LENGTH;

	gn_add_ulong_to_buffer(sapa_buffer, &byte_pos, &bit_pos, 10, num_data_bytes);
	gn_add_ulong_to_buffer(sapa_buffer, &byte_pos, &bit_pos, 1, ea_flag);
	gn_add_ulong_to_buffer(sapa_buffer, &byte_pos, &bit_pos, 2, message_crc_type);
	gn_add_ulong_to_buffer(sapa_buffer, &byte_pos, &bit_pos, 4, crc_frame);

	memcpy((sapa_buffer + byte_pos), hpac_buffer, num_data_bytes);

	byte_pos += num_data_bytes;

	gn_add_ulong_to_buffer(sapa_buffer, &byte_pos, &bit_pos, SAPA_CRC_BYTES[message_crc_type], 0);

	return 0;
}
GPPLONG gpp_sapa_sapa_buffer_to_hpac_buffer(GPPUCHAR *hpac_buffer, GPPLONG *len_sapa_bits, GPPLONG *ea_flag, GPPLONG *message_crc_type, GPPLONG *crc_frame, const GPPUCHAR *sapa_buffer)
{
	GPPLONG byte_pos = 0, bit_pos = 0, numDataBytes = 0;

	int type;
	long sapa_preamble = gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, 8);
	if (sapa_preamble != SAPA_PREAMBLE) return GPP_SAPA_ERR_PREAMBLE;

	type = gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, 7);
	if (type != SAPA_TYPE_HPAC) return GPP_SAPA_ERR_TYPE;

	numDataBytes = gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, 10);
	if (!numDataBytes) return GPP_SAPA_ERR_PAYLOAD_LENGTH;

	*len_sapa_bits = numDataBytes * 8;

	*ea_flag = gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, 1);

	*message_crc_type = gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, 2);
	if (*message_crc_type > 3) return GPP_SAPA_ERR_CRC_TYPE;

	*crc_frame = gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, 4);

	memcpy(hpac_buffer, (sapa_buffer + byte_pos), numDataBytes);
	byte_pos += numDataBytes;

	GPPLONG crc = gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, SAPA_CRC_BYTES[*message_crc_type]);

	return 0;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
GPPLONG gpp_sapa_area_buffer_to_sapa_buffer(const GPPUCHAR *area_buffer, GPPLONG len_sapa_bits, GPPLONG ea_flag, GPPLONG message_crc_type, GPPLONG crc_frame, GPPUCHAR *sapa_buffer)
{
	GPPLONG byte_pos = 0, bit_pos = 0, num_data_bytes = 0;
	gn_add_ulong_to_buffer(sapa_buffer, &byte_pos, &bit_pos, 8, SAPA_PREAMBLE);
	gn_add_ulong_to_buffer(sapa_buffer, &byte_pos, &bit_pos, 7, SAPA_TYPE_AREA);

	num_data_bytes = length_bytes_from_bits(len_sapa_bits);
	if (!num_data_bytes) return GPP_SAPA_ERR_PAYLOAD_LENGTH;

	gn_add_ulong_to_buffer(sapa_buffer, &byte_pos, &bit_pos, 10, num_data_bytes);
	gn_add_ulong_to_buffer(sapa_buffer, &byte_pos, &bit_pos, 1, ea_flag);
	gn_add_ulong_to_buffer(sapa_buffer, &byte_pos, &bit_pos, 2, message_crc_type);
	gn_add_ulong_to_buffer(sapa_buffer, &byte_pos, &bit_pos, 4, crc_frame);

	memcpy((sapa_buffer + byte_pos), area_buffer, num_data_bytes);

	byte_pos += num_data_bytes;

	gn_add_ulong_to_buffer(sapa_buffer, &byte_pos, &bit_pos, SAPA_CRC_BYTES[message_crc_type], 0);

	return 0;
}

GPPLONG gpp_sapa_sapa_buffer_to_area_buffer(GPPUCHAR *area_buffer, GPPLONG *len_sapa_bits, GPPLONG *ea_flag, GPPLONG *message_crc_type, GPPLONG *crc_frame, const GPPUCHAR *sapa_buffer)
{
	GPPLONG byte_pos = 0, bit_pos = 0, numDataBytes = 0;

	int type;
	long sapa_preamble = gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, 8);
	if (sapa_preamble != SAPA_PREAMBLE) return GPP_SAPA_ERR_PREAMBLE;

	type = gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, 7);

	if (type != SAPA_TYPE_AREA) return GPP_SAPA_ERR_TYPE;

	numDataBytes = gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, 10);

	if (!numDataBytes) return GPP_SAPA_ERR_PAYLOAD_LENGTH;
	*len_sapa_bits = numDataBytes * 8;
	*ea_flag = gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, 1);

	*message_crc_type = gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, 2);
	if (*message_crc_type > 3) return GPP_SAPA_ERR_CRC_TYPE;

	*crc_frame = gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, 4);

	memcpy(area_buffer, (sapa_buffer + byte_pos), numDataBytes);
	byte_pos += numDataBytes;

	GPPLONG crc = gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, SAPA_CRC_BYTES[*message_crc_type]);

	//int i;
	//for (i = 0; i <= numDataBytes; i++)
	//{
	//	printf("\nByte %d, Integral Value : %d, Binary Valuefin: ", i, *(area_buffer + i));
	//	int x = 0;
	//	for (x = 0; x < 8; x++)    //prnbit testing
	//	{
	//		printf("%d", TestBit(*(area_buffer + i), x), x);
	//	}
	//}
	return 0;
}

GPPLONG length_bytes_from_bits(GPPLONG b)
{
	return (((b) / 8) + ((b) % 8 ? 1 : 0));
}
#if 0


//Write Buffer Data Into File
void buffer_data_write_into_file(GPPUCHAR *buffer)
{
	FILE *fPtr=NULL;
	char *binary_filename = "sap/encp_001.ocb";
	/*
	 * Open file in w (write) mode.
	 * "data/file1.txt" is complete path to create file
	 */
	fPtr = fopen(binary_filename, "ab");

	/* fopen() return NULL if last operation was unsuccessful */
	if (fPtr == NULL)
	{
		/* File not created hence exit */
		printf("Unable to create file.\n");
		//exit(EXIT_FAILURE);
	}

	/* Write data to file */
	fputs(buffer, fPtr);

	/* Close file to save file data */
	fclose(fPtr);
}
//Compare Two files
void compare_files(FILE *pre_binary_filename, FILE *binary_filename)
{
	char ch1 = getc(pre_binary_filename);
	char ch2 = getc(binary_filename);
	int error = 0, pos = 0, line = 1;
	while (ch1 != EOF && ch2 != EOF)
	{
		pos++;

		// if both variable encounters new
		// line then line variable is incremented
		// and pos variable is set to 0
		if (ch1 == '\n' && ch2 == '\n')
		{
			line++;
			pos = 0;
		}

		// if fetched data is not equal then
		// error is incremented
		if (ch1 != ch2)
		{
			error++;
			printf("Line Number : %d \tError"
				" Position : %d \n", line, pos);
		}

		// fetching character until end of file
		ch1 = getc(pre_binary_filename);
		ch2 = getc(binary_filename);
	}

	printf("Total Errors : %d\t", error);
}
int TestBit(GPPUINT8 A, int k)																							//only for bit mask testing
{
	GPPUINT8 value = 1;
	return ((A & (value << k)) ? 1:0);
}

#endif
