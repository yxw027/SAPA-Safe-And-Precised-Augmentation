#include "gpp_sapa.h"
#include "bit2buff.h"




const GPPUINT1 SAPA_SV_IODE_LEN[GPP_SAPA_MAX_SYS]={SAPA_SV_IODE_LEN_GPS, SAPA_SV_IODE_LEN_GLO,};

const GPPUINT1 SAPA_SV_BITMASK_LEN_GPS[4]={32, 44, 56, 64};
const GPPUINT1 SAPA_SV_BITMASK_LEN_GLO[4]={24, 36, 48, 63};
const GPPUINT1 *SAPA_SV_BITMASK_LEN[2]={SAPA_SV_BITMASK_LEN_GPS, SAPA_SV_BITMASK_LEN_GLO};

const GPPUINT1 SAPA_CRC_BYTES[4] = { SAPA_CONST_LEN_BYTES_CRC_8,SAPA_CONST_LEN_BYTES_CRC_16,SAPA_CONST_LEN_BYTES_CRC_24,SAPA_CONST_LEN_BYTES_CRC_32 };




const GPPDOUBLE SAPA_TROPO_POLY_MIN_SML[SAPA_MAX_TROPO_COEFF]={SAPA_T00_MIN_SML, SAPA_T01_MIN_SML, SAPA_T10_MIN_SML, SAPA_T11_MIN_SML};
const GPPDOUBLE SAPA_TROPO_POLY_MAX_SML[SAPA_MAX_TROPO_COEFF]={SAPA_T00_MAX_SML, SAPA_T01_MAX_SML, SAPA_T10_MAX_SML, SAPA_T11_MAX_SML};

const GPPDOUBLE SAPA_TROPO_POLY_MIN_LRG[SAPA_MAX_TROPO_COEFF]={SAPA_T00_MIN_LRG, SAPA_T01_MIN_LRG, SAPA_T10_MIN_LRG, SAPA_T11_MIN_LRG};
const GPPDOUBLE SAPA_TROPO_POLY_MAX_LRG[SAPA_MAX_TROPO_COEFF]={SAPA_T00_MAX_LRG, SAPA_T01_MAX_LRG, SAPA_T10_MAX_LRG, SAPA_T11_MAX_LRG};

const GPPDOUBLE* SAPA_TROPO_POLY_MIN[2]={SAPA_TROPO_POLY_MIN_SML, SAPA_TROPO_POLY_MIN_LRG};
const GPPDOUBLE* SAPA_TROPO_POLY_MAX[2]={SAPA_TROPO_POLY_MAX_SML, SAPA_TROPO_POLY_MAX_LRG};

const GPPDOUBLE SAPA_TROPO_POLY_RES[SAPA_MAX_TROPO_COEFF]={SAPA_T00_RES, SAPA_T01_RES, SAPA_T10_RES, SAPA_T11_RES};



const GPPLONG LSAPA_TROPO_GRD_MIN[2]={LSAPA_TROPO_GRD_MIN_SML, LSAPA_TROPO_GRD_MIN_LRG};
const GPPLONG LSAPA_TROPO_GRD_MAX[2]={LSAPA_TROPO_GRD_MAX_SML, LSAPA_TROPO_GRD_MAX_LRG};

const GPPLONG LSAPA_TROPO_POLY_MIN_SML[SAPA_MAX_TROPO_COEFF] = { LSAPA_T00_MIN_SML, LSAPA_T01_MIN_SML, LSAPA_T10_MIN_SML, LSAPA_T11_MIN_SML };
const GPPLONG LSAPA_TROPO_POLY_MAX_SML[SAPA_MAX_TROPO_COEFF] = { LSAPA_T00_MAX_SML, LSAPA_T01_MAX_SML, LSAPA_T10_MAX_SML, LSAPA_T11_MAX_SML };

const GPPLONG LSAPA_TROPO_POLY_MIN_LRG[SAPA_MAX_TROPO_COEFF] = { LSAPA_T00_MIN_LRG, LSAPA_T01_MIN_LRG, LSAPA_T10_MIN_LRG, LSAPA_T11_MIN_LRG };
const GPPLONG LSAPA_TROPO_POLY_MAX_LRG[SAPA_MAX_TROPO_COEFF] = { LSAPA_T00_MAX_LRG, LSAPA_T01_MAX_LRG, LSAPA_T10_MAX_LRG, LSAPA_T11_MAX_LRG };

const GPPLONG* LSAPA_TROPO_POLY_MIN[2] = { LSAPA_TROPO_POLY_MIN_SML, LSAPA_TROPO_POLY_MIN_LRG };
const GPPLONG* LSAPA_TROPO_POLY_MAX[2] = { LSAPA_TROPO_POLY_MAX_SML, LSAPA_TROPO_POLY_MAX_LRG };




const GPPDOUBLE SAPA_TROPO_GRD_MIN[2] = { SAPA_TROPO_GRD_MIN_SML, SAPA_TROPO_GRD_MIN_LRG };
const GPPDOUBLE SAPA_TROPO_GRD_MAX[2] = { SAPA_TROPO_GRD_MAX_SML, SAPA_TROPO_GRD_MAX_LRG };


const GPPDOUBLE SAPA_IONO_POLY_MIN_SML[SAPA_MAX_IONO_COEFF] = { SAPA_C00_MIN_SML, SAPA_C01_MIN_SML, SAPA_C10_MIN_SML, SAPA_C11_MIN_SML };
const GPPDOUBLE SAPA_IONO_POLY_MAX_SML[SAPA_MAX_IONO_COEFF] = { SAPA_C00_MAX_SML, SAPA_C01_MAX_SML, SAPA_C10_MAX_SML, SAPA_C11_MAX_SML };

const GPPDOUBLE SAPA_IONO_POLY_MIN_LRG[SAPA_MAX_IONO_COEFF] = { SAPA_C00_MIN_LRG, SAPA_C01_MIN_LRG, SAPA_C10_MIN_LRG, SAPA_C11_MIN_LRG };
const GPPDOUBLE SAPA_IONO_POLY_MAX_LRG[SAPA_MAX_IONO_COEFF] = { SAPA_C00_MAX_LRG, SAPA_C01_MAX_LRG, SAPA_C10_MAX_LRG, SAPA_C11_MAX_LRG };

const GPPDOUBLE* SAPA_IONO_POLY_MIN[2] = { SAPA_IONO_POLY_MIN_SML, SAPA_IONO_POLY_MIN_LRG };
const GPPDOUBLE* SAPA_IONO_POLY_MAX[2] = { SAPA_IONO_POLY_MAX_SML, SAPA_IONO_POLY_MAX_LRG };


const GPPLONG LSAPA_IONO_POLY_MIN_SML[SAPA_MAX_IONO_COEFF] = { LSAPA_C00_MIN_SML, LSAPA_C01_MIN_SML, LSAPA_C10_MIN_SML, LSAPA_C11_MIN_SML };
const GPPLONG LSAPA_IONO_POLY_MAX_SML[SAPA_MAX_IONO_COEFF] = { LSAPA_C00_MAX_SML, LSAPA_C01_MAX_SML, LSAPA_C10_MAX_SML, LSAPA_C11_MAX_SML };

const GPPLONG LSAPA_IONO_POLY_MIN_LRG[SAPA_MAX_IONO_COEFF] = { LSAPA_C00_MIN_LRG, LSAPA_C01_MIN_LRG, LSAPA_C10_MIN_LRG, LSAPA_C11_MIN_LRG };
const GPPLONG LSAPA_IONO_POLY_MAX_LRG[SAPA_MAX_IONO_COEFF] = { LSAPA_C00_MAX_LRG, LSAPA_C01_MAX_LRG, LSAPA_C10_MAX_LRG, LSAPA_C11_MAX_LRG };

const GPPLONG* LSAPA_IONO_POLY_MIN[2] = { LSAPA_IONO_POLY_MIN_SML, LSAPA_IONO_POLY_MIN_LRG };
const GPPLONG* LSAPA_IONO_POLY_MAX[2] = { LSAPA_IONO_POLY_MAX_SML, LSAPA_IONO_POLY_MAX_LRG };


const GPPDOUBLE SAPA_IONO_GRD_MIN[4] = { SAPA_IONO_GRD_MIN_SML, SAPA_IONO_GRD_MIN_MDM, SAPA_IONO_GRD_MIN_LRG, SAPA_IONO_GRD_MIN_ELRG };
const GPPDOUBLE SAPA_IONO_GRD_MAX[4] = { SAPA_IONO_GRD_MAX_SML, SAPA_IONO_GRD_MIN_MDM, SAPA_IONO_GRD_MAX_LRG, SAPA_IONO_GRD_MIN_ELRG };


const GPPLONG LSAPA_IONO_GRD_MIN[4] = { LSAPA_IONO_GRD_MIN_SML, LSAPA_IONO_GRD_MIN_MDM, LSAPA_IONO_GRD_MIN_LRG, LSAPA_IONO_GRD_MIN_ELRG };
const GPPLONG LSAPA_IONO_GRD_MAX[4] = { LSAPA_IONO_GRD_MAX_SML, LSAPA_IONO_GRD_MIN_MDM, LSAPA_IONO_GRD_MAX_LRG, LSAPA_IONO_GRD_MIN_ELRG };


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

/***************************************************************************
 *	\brief Get an Index list (starting with zero) of bits set in bitmask (prn_bits).
 *	configlist is an GPPUINT1 array with 34 fields. configlist[0] contains the total number of set bits in prn_bits
 *	configlist[32] is zero (control bit)
 *  configlist[1] is the idx of the first set bit
 ***************************************************************************/
void gpp_sapa_get_configlist(GPPUINT8 config_bits, GPPUINT1 *configlist)
{
	gpp_sapa_get_svlist(config_bits, configlist);
}//gpp_sapa_get_configlist()



void gpp_sapa_get_arealist(const GPPUINT8 *area_bits, GPPUINT1 *arealist)
{
	GPPUINT2 idx=0, num=0;

	if(!arealist) return;
	memset(arealist, 0, 258 * sizeof(GPPUINT1));
	
	

	for(idx=0; idx<256; idx++){
		if(area_bits[idx/64]&GNSS_PRN_BIT_MASK_64[idx%64]){
			arealist[num+1]=idx;
			num++;
		}
	}
	arealist[0]=num;
	printf("\n----------------------------------------%d", arealist[0]);
}//gpp_sapa_get_arealist()






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

	if (!ocb->sv){
		GPPUINT1 sys;
		ocb->sv = (pGPP_SAPA_OCB_SV**)calloc(SAPA_MAX_SYS, sizeof(GPP_SAPA_OCB_SV**));

		if (!ocb->sv) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
		for (sys = 0; sys < SAPA_MAX_SYS; sys++){
			if (!ocb->sv[sys]){
				ocb->sv[sys] = (pGPP_SAPA_OCB_SV*)calloc(GPP_SAPA_MAX_SAT, sizeof(GPP_SAPA_OCB_SV*));
				if (!(ocb->sv[sys])) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
			}
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

	GPPLONG rc;       //control variable
	if (rc = gpp_sapa_ocb_malloc_sv(ocb)) return rc;

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
	GPPUINT1 isValid = 1;
	GPPUINT2 invalid;
	GPPUINT1 lvalue;
	pGPP_SAPA_OCB_SV sv = NULL;   // Pointer to OCB_SV
	GPPLONG rc;       //control variable
	if (rc = gpp_sapa_ocb_malloc_sv(ocb)) return rc;

	if (!(sv = ocb->sv[sys][sat])) { // check if sv[sys][sat] is allocated
		ocb->sv[sys][sat] = (GPP_SAPA_OCB_SV*)calloc(1, sizeof(GPP_SAPA_OCB_SV));
		if (!(sv = ocb->sv[sys][sat])) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!sv->orb) {//check if orbit structure is allocated
		sv->orb = (pGPP_SAPA_OCB_SV_ORB)calloc(1, sizeof(GPP_SAPA_OCB_SV_ORB));
		if (!sv->orb) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	lvalue = float2long(pset->d_orbit[0], &pset->ld_orbit[0], SAPA_RES_SV_CORRECTION, SAPA_SV_MIN, LSAPA_SV_MIN, LSAPA_SV_MAX, NULL);
	isValid = &lvalue;

	lvalue = float2long(pset->d_orbit[1], &pset->ld_orbit[1], SAPA_RES_SV_CORRECTION, SAPA_SV_MIN, LSAPA_SV_MIN, LSAPA_SV_MAX, NULL);
	isValid = &lvalue;

	lvalue = float2long(pset->d_orbit[2], &pset->ld_orbit[2], SAPA_RES_SV_CORRECTION, SAPA_SV_MIN, LSAPA_SV_MIN, LSAPA_SV_MAX, NULL);
	isValid = &lvalue;

	if (!isValid) {
		printf("SAPA Warning orbit of %1c%02d is out of range (invalid).\n", sys == 0 ? 'G' : 'R', sat);
		return 0;
	}

	invalid = GPP_SAPA_OCB_SAT_YAW_INVALID;
	pset->yaw_bits = float2long(pset->sat_yaw, &pset->lsat_yaw, GPP_SAPA_SAT_YAW_RES, SAPA_YAW_MIN, LSAPA_YAW_MIN, LSAPA_YAW_MAX, &invalid);

	memcpy(sv->orb, pset, sizeof(GPP_SAPA_OCB_SV_ORB)); //copy orbit data
	GNSS_SET_IDX_IN_BITS_64(ocb->sv_prn_bits[sys], sat);       //set sat ID in sv_prn_bits bit mask
	GNSS_SET_IDX_IN_BITS_64(ocb->orb_prn_bits[sys], sat);       //set sat ID in sv_prn_bits bit mask
	sv->ocb_bits |= SAPA_OCB_ORB_BITS;
	return 0;
}//gpp_sapa_ocb_add_orb()

/************************************************************************************************************/

GPPLONG gpp_sapa_ocb_add_clk(pGPP_SAPA_OCB ocb, GPPUINT1 sys, GPPUINT1 sat, const pGPP_SAPA_OCB_SV_CLK pset)
{
	GPPUINT1 isValid = 1;
	GPPUINT1 lvalue;
	pGPP_SAPA_OCB_SV sv = NULL;   // Pointer to OCB_SV
	GPPLONG rc;       //control variable
	if (rc = gpp_sapa_ocb_malloc_sv(ocb)) return rc;

	if (!(sv = ocb->sv[sys][sat])) { // check if sv[sys][sat] is allocated
		ocb->sv[sys][sat] = (GPP_SAPA_OCB_SV*)calloc(1, sizeof(GPP_SAPA_OCB_SV));
		if (!(sv = ocb->sv[sys][sat])) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!sv->clk) {//check if orbit structure is allocated
		sv->clk = (pGPP_SAPA_OCB_SV_CLK)calloc(1, sizeof(GPP_SAPA_OCB_SV_CLK));
		if (!sv->clk) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	lvalue = float2long(pset->clk_correction, &pset->lclk_correction, SAPA_RES_SV_CORRECTION, SAPA_SV_MIN, LSAPA_SV_MIN, LSAPA_SV_MAX, NULL);
	isValid = &lvalue;

	if (!isValid) {
		printf("SAPA Warning clock of %1c%02d is out of range (invalid).\n", sys == 0 ? 'G' : 'R', sat);
		return 0;
	}

	memcpy(sv->clk, pset, sizeof(GPP_SAPA_OCB_SV_CLK)); //copy clock data
	GNSS_SET_IDX_IN_BITS_64(ocb->sv_prn_bits[sys], sat);      //set sat ID in sv_prn_bits bit mask
	GNSS_SET_IDX_IN_BITS_64(ocb->clk_prn_bits[sys], sat);      //set sat ID in sv_prn_bits bit mask
	sv->ocb_bits |= SAPA_OCB_CLK_BITS;       //set ocb_bits as it is assumed that only valid data are stored in the structure

	return 0;
}//gpp_sapa_ocb_add_clk()

/************************************************************************************************************/

GPPLONG gpp_sapa_ocb_add_pb(pGPP_SAPA_OCB ocb, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 sig, const pGPP_SAPA_OCB_SV_BIAS_PB pset)
{
	GPPUINT1 isValid = 1;
	GPPUINT1 lvalue;
	pGPP_SAPA_OCB_SV sv = NULL;     // Pointer to OCB_SV
	pGPP_SAPA_OCB_SV_BIAS bias = NULL;   // Pointer to OCB_SV_BIAS
	pGPP_SAPA_OCB_SV_BIAS_PB pb = NULL; // Pointer to OCB_SV_SATPHASEBIAS

	GPPLONG rc;   //control variable
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

	lvalue = float2long(pset->pb_correction, &pset->lpb_correction, SAPA_RES_PB_CORRECTION, SAPA_SV_MIN, LSAPA_SV_MIN, LSAPA_SV_MAX, NULL);
	isValid = &lvalue;

	if (!isValid) {
		printf("SAPA Warning phase bias of %1c%02d is out of range (invalid).\n", sys == 0 ? 'G' : 'R', sat);
		return 0;
	}

	memcpy(pb, pset, sizeof(GPP_SAPA_OCB_SV_BIAS_PB));  //Copy Phase bias content
	GNSS_SET_IDX_IN_BITS_32(bias->pb_sig_bits, sig);  //set signal in signal bit mask for this satellite
	GNSS_SET_IDX_IN_BITS_64(ocb->sv_prn_bits[sys], sat);     //set sat ID in sv_prn_bits bit mask
	GNSS_SET_IDX_IN_BITS_64(ocb->pb_prn_bits[sys], sat);     //set sat ID in sv_prn_bits bit mask
	sv->ocb_bits |= SAPA_OCB_BIAS_BITS;

	return 0; //GPP_SAPA_OK
}//gpp_sapa_ocb_add_pb()
//----------------------------------------------------------------------------------------------------------------------------

GPPLONG gpp_sapa_ocb_add_header(pGPP_SAPA_OCB ocb, GPPUINT1 sys, const pGPP_SAPA_OCB_HEADER pset)
{
	if (!ocb) return GPP_SAPA_ERR_INVALID_OCB;

	if (!ocb->header_block) { // check if sv[sys][sat] is allocated
		ocb->header_block = (pGPP_SAPA_OCB_HEADER*)calloc(GPP_SAPA_MAX_SYS, sizeof(GPP_SAPA_OCB_HEADER*));
		if (!ocb->header_block) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!ocb->header_block[sys]) {//check if orbit structure is allocated
		ocb->header_block[sys] = (pGPP_SAPA_OCB_HEADER)calloc(1, sizeof(GPP_SAPA_OCB_HEADER));
		if (!ocb->header_block[sys]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	memcpy(ocb->header_block[sys], pset, sizeof(GPP_SAPA_OCB_HEADER)); //copy clock data
	return 0;
}//gpp_sapa_ocb_add_header()

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

GPPLONG gpp_sapa_ocb_add_cb(pGPP_SAPA_OCB ocb, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 sig, const pGPP_SAPA_OCB_SV_BIAS_CB pset)
{
	GPPUINT1 isValid = 1;
	GPPUINT1 lvalue;
	GPPLONG rc;         //control variable
	pGPP_SAPA_OCB_SV sv = NULL;     // Pointer to OCB_SV
	pGPP_SAPA_OCB_SV_BIAS bias = NULL;   // Pointer to OCB_SV_BIAS
	pGPP_SAPA_OCB_SV_BIAS_CB cb = NULL; // Pointer to OCB_SV_SATPHASEBIAS

	if (!ocb) return GPP_SAPA_ERR_INVALID_OCB;

	if (!ocb->sv) {// allocate the sys-sat two dimensional pointer array
		if (rc = gpp_sapa_ocb_malloc_sv(ocb)) return rc;
	}

	if (!(sv = ocb->sv[sys][sat])) { // check if sv[sys][sat] is allocated
		ocb->sv[sys][sat] = (GPP_SAPA_OCB_SV*)calloc(1, sizeof(GPP_SAPA_OCB_SV));
		if (!(sv = ocb->sv[sys][sat])) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!sv->bias) {//check if orbit structure is allocated
		sv->bias = (pGPP_SAPA_OCB_SV_BIAS)calloc(1, sizeof(GPP_SAPA_OCB_SV_BIAS));
		if (!sv->bias) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}
	bias = sv->bias;

	if (!bias->cb) {
		bias->cb = (pGPP_SAPA_OCB_SV_BIAS_CB*)calloc(GPP_SAPA_MAX_SIG, sizeof(pGPP_SAPA_OCB_SV_BIAS_CB));// allocate pointer array with GPP_SAPA_MAX_SIG Pointers
		if (!bias->cb) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!bias->cb[sig]) {
		bias->cb[sig] = (pGPP_SAPA_OCB_SV_BIAS_CB)calloc(1, sizeof(GPP_SAPA_OCB_SV_BIAS_CB)); //allocate memory for SATPHASE_BIAS structure
		if (!bias->cb[sig]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}
	cb = bias->cb[sig];

	lvalue = float2long(pset->cb_correction, &pset->lcb_correction, SAPA_RES_CB_CORRECTION, SAPA_CB_MIN, LSAPA_CB_MIN, LSAPA_CB_MAX, NULL);
	isValid = &lvalue;

	if (!isValid) {
		printf("SAPA Warning code bias of %1c%02d is out of range (invalid).\n", sys == 0 ? 'G' : 'R', sat);
		return 0;
	}

	memcpy(cb, pset, sizeof(GPP_SAPA_OCB_SV_BIAS_CB));  //Copy Phase bias content
	GNSS_SET_IDX_IN_BITS_32(bias->cb_sig_bits, sig);       //set signal in signal bit mask for this satellite
	GNSS_SET_IDX_IN_BITS_64(ocb->sv_prn_bits[sys], sat);       //set sat ID in sv_prn_bits bit mask
	GNSS_SET_IDX_IN_BITS_64(ocb->cb_prn_bits[sys], sat);       //set sat ID in sv_prn_bits bit mask
	sv->ocb_bits |= SAPA_OCB_BIAS_BITS;
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
	GPPUINT1 coeff_size;

	if (!hpac) return GPP_SAPA_ERR_INVALID_HPAC_AREA;

	coeff_size = pset->tropo_coeff_size;

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
	
	float2long(pset->tropo_avhd, &pset->ltropo_avhd, SAPA_AVHD_RES, SAPA_AVHD_MIN, LSAPA_AVHD_MIN, LSAPA_AVHD_MAX, NULL);
	float2long(pset->tropo_poly_coeff[SAPA_T00_IDX], &pset->ltropo_poly_coeff[SAPA_T00_IDX], SAPA_RES_TROPO_POLY_COEFF_T00, SAPA_TROPO_POLY_MIN[coeff_size][SAPA_T00_IDX], LSAPA_TROPO_POLY_MIN[coeff_size][SAPA_T00_IDX], LSAPA_TROPO_POLY_MAX[coeff_size][SAPA_T00_IDX],NULL);
	float2long(pset->tropo_poly_coeff[SAPA_T01_IDX], &pset->ltropo_poly_coeff[SAPA_T01_IDX], SAPA_RES_TROPO_POLY_COEFF_T01, SAPA_TROPO_POLY_MIN[coeff_size][SAPA_T01_IDX], LSAPA_TROPO_POLY_MIN[coeff_size][SAPA_T01_IDX], LSAPA_TROPO_POLY_MAX[coeff_size][SAPA_T01_IDX], NULL);
	float2long(pset->tropo_poly_coeff[SAPA_T10_IDX], &pset->ltropo_poly_coeff[SAPA_T10_IDX], SAPA_RES_TROPO_POLY_COEFF_T01, SAPA_TROPO_POLY_MIN[coeff_size][SAPA_T10_IDX], LSAPA_TROPO_POLY_MIN[coeff_size][SAPA_T10_IDX], LSAPA_TROPO_POLY_MAX[coeff_size][SAPA_T10_IDX], NULL);
	float2long(pset->tropo_poly_coeff[SAPA_T11_IDX], &pset->ltropo_poly_coeff[SAPA_T11_IDX], SAPA_RES_TROPO_POLY_COEFF_T11, SAPA_TROPO_POLY_MIN[coeff_size][SAPA_T11_IDX], LSAPA_TROPO_POLY_MIN[coeff_size][SAPA_T11_IDX], LSAPA_TROPO_POLY_MAX[coeff_size][SAPA_T11_IDX], NULL);


	memcpy(hpac->atmo[area]->tropo->tropo_poly_coeff_block, pset, sizeof(GPP_SAPA_HPAC_TROPO_POLY_COEFFICIENT_BLOCK));	//copy clock data
	return 0; //GPP_SAPA_OK
}//gpp_sapa_hpac_add_tropo_poly_coeff_block()



//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
GPPLONG gpp_sapa_hpac_add_tropo_grid_block(pGPP_SAPA_HPAC hpac, GPPUINT1 area, const pGPP_SAPA_HPAC_TROPO_GRID_BLOCK pset)
{

	if (!hpac) return GPP_SAPA_ERR_INVALID_HPAC_AREA;

	if(pset->grid)
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


/************************************************************************************************************
 *	\brief Add gridded Tropo data to hpac/SAPA_ USE  STATES
 *
 *	GPP_SAPA_USE_STATES is used to connect hpac and area definiton data
 ************************************************************************************************************/
GPPLONG gpp_sapa_hpac_add_grd_tropo_correction( pGPP_SAPA_USE_STATES states, GPPUINT1 iarea, GPPUINT1 igrd, GPP_SAPA_HPAC_TROPO_GRD_CORRECTION *pset)
{
	pGPP_SAPA_HPAC hpac=states->hpac;
	pGPP_SAPA_AREA area=states->area;

	pGPP_SAPA_HPAC_ATMO_BLOCK atmo=NULL;
	pGPP_SAPA_AREA_DEF_BLOCK area_def=NULL;

	pGPP_SAPA_HPAC_TROPO tropo=NULL;
	pGPP_SAPA_HPAC_TROPO_GRID_BLOCK grd_tropo=NULL;


	if(!hpac) return GPP_SAPA_ERR_INVALID_HPAC;

	if(!hpac->atmo){
		hpac->atmo=(pGPP_SAPA_HPAC_ATMO_BLOCK*)calloc(SAPA_MAX_AREA, sizeof(pGPP_SAPA_HPAC_ATMO_BLOCK));
		if(!hpac->atmo) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if(!(atmo=hpac->atmo[iarea])){
		hpac->atmo[iarea]=(pGPP_SAPA_HPAC_ATMO_BLOCK)calloc(1, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK));
		if(!(atmo=hpac->atmo[iarea])) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if(!area){
		printf("ERROR: Area with AreaID(%d) has to be defined first", iarea);
		return GPP_SAPA_ERR_INVALID_AREA;
	}

	if(!area->area_bits[iarea/64]&iarea%64){
		printf("ERROR: Area with AreaID(%d) has to be defined first", iarea);
		return GPP_SAPA_ERR_INVALID_AREA;
	}

	if(!(tropo=atmo->tropo)){
		atmo->tropo=(pGPP_SAPA_HPAC_TROPO)calloc(1, sizeof(GPP_SAPA_HPAC_TROPO));
		if(!(tropo=atmo->tropo)) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if(!(grd_tropo=tropo->tropo_grid)){
		tropo->tropo_grid=(pGPP_SAPA_HPAC_TROPO_GRID_BLOCK)calloc(1, sizeof(GPP_SAPA_HPAC_TROPO_GRID_BLOCK));
		if(!(grd_tropo=tropo->tropo_grid)) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if(grd_tropo->num_grid){
		if(grd_tropo->num_grid!=area_def->num_grid_points){
			grd_tropo->num_grid=area_def->num_grid_points;
			grd_tropo->grid=(GPP_SAPA_HPAC_TROPO_GRD_CORRECTION*)realloc(grd_tropo->grid, grd_tropo->num_grid*sizeof(GPP_SAPA_HPAC_TROPO_GRD_CORRECTION));
			if(!grd_tropo->grid) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
		}
	}
	else{
		grd_tropo->num_grid=area_def->num_grid_points;
		if(!grd_tropo->grid){
			grd_tropo->grid=(GPP_SAPA_HPAC_TROPO_GRD_CORRECTION*)calloc(grd_tropo->num_grid, sizeof(GPP_SAPA_HPAC_TROPO_GRD_CORRECTION));
			if(!grd_tropo->grid) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
		}
	}

	if(igrd>=grd_tropo->num_grid){
		printf("ERROR: grid point index (%d) out of range (number of grid points is %d)\n", igrd, grd_tropo->num_grid);
		return GPP_SAPA_ERR_INVALID_GRD_IDX;
	}

	//SF051 check required!
	grd_tropo->sz=0;

	float2long(pset->val, &pset->lval, SAPA_TROPO_GRD_RES, SAPA_TROPO_GRD_MIN[grd_tropo->sz], LSAPA_TROPO_GRD_MAX[grd_tropo->sz], LSAPA_TROPO_GRD_MIN[grd_tropo->sz], NULL);

	memcpy(&grd_tropo->grid[igrd], pset, sizeof(GPP_SAPA_HPAC_TROPO_GRD_CORRECTION));
	GNSS_SET_IDX_IN_BITS_64(grd_tropo->grid_bits, igrd);
	GNSS_SET_IDX_IN_BITS_64((hpac->atmo_bits[iarea/64]), (iarea%64));

	return 0;
}//gpp_sapa_hpac_add_grd_tropo_correction()







//--------------------------------------------------------------------------------------------------------------------------------------------------------------
GPPLONG gpp_sapa_hpac_add_iono(pGPP_SAPA_HPAC hpac,GPPUINT1 area, const pGPP_SAPA_HPAC_IONO pset)
{
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

//------------------------------------------------------------------------------------------------------------------------------------------------------
GPPLONG gpp_sapa_hpac_add_iono_sat_block(pGPP_SAPA_HPAC hpac, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 area, const pGPP_SAPA_HPAC_IONO_SAT_BLOCK pset)
{
	if (!hpac) return GPP_SAPA_ERR_INVALID_HPAC_AREA;

	if (!hpac->atmo) {//check if atmo structure is allocated
		hpac->atmo = (pGPP_SAPA_HPAC_ATMO_BLOCK*)calloc(GPP_SAPA_MAX_AREA_COUNT, sizeof(pGPP_SAPA_HPAC_ATMO_BLOCK));
		if (!hpac->atmo) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[area]) {//check if atmo[area] structure is allocated
		hpac->atmo[area] = (pGPP_SAPA_HPAC_ATMO_BLOCK)calloc(1, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK));
		if (!hpac->atmo[area]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[area]->iono) {////check if iono structure is allocated
		hpac->atmo[area]->iono = (pGPP_SAPA_HPAC_IONO)calloc(1, sizeof(GPP_SAPA_HPAC_IONO));
		if (!hpac->atmo[area]->iono) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[area]->iono->iono_sat_block) {////check if iono Satellite structure is allocated
		hpac->atmo[area]->iono->iono_sat_block = (pGPP_SAPA_HPAC_IONO_SAT_BLOCK**)calloc(SAPA_MAX_SYS, sizeof(GPP_SAPA_HPAC_IONO_SAT_BLOCK**));
		if (!hpac->atmo[area]->iono->iono_sat_block) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[area]->iono->iono_sat_block[sys]) {////check if iono Satellite structure is allocated
		hpac->atmo[area]->iono->iono_sat_block[sys] = (pGPP_SAPA_HPAC_IONO_SAT_BLOCK*)calloc(GPP_SAPA_MAX_SAT, sizeof(GPP_SAPA_HPAC_IONO_SAT_BLOCK*));
		if (!(hpac->atmo[area]->iono->iono_sat_block[sys])) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}
	if (!(hpac->atmo[area]->iono->iono_sat_block[sys][sat])) { // check if iono satelite [sys][sat] is allocated
		hpac->atmo[area]->iono->iono_sat_block[sys][sat] = (pGPP_SAPA_HPAC_IONO_SAT_BLOCK)calloc(1, sizeof(GPP_SAPA_HPAC_IONO_SAT_BLOCK));
		if (!(hpac->atmo[area]->iono->iono_sat_block[sys][sat])) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}
	memcpy(hpac->atmo[area]->iono->iono_sat_block[sys][sat], pset, sizeof(GPP_SAPA_HPAC_IONO_SAT_BLOCK));

	return 0;
}//gpp_sapa_hpac_add_iono_sat_block()
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
GPPLONG gpp_sapa_hpac_add_iono_sat_poly_block(pGPP_SAPA_HPAC hpac, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 area, const pGPP_SAPA_HPAC_IONO_SAT_POLY pset)
{
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
	GPPUINT1 coeff_size = hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_sat_poly->iono_coeff_size;
	float2long(pset->iono_poly_coeff[SAPA_T00_IDX], &pset->liono_poly_coeff[SAPA_T00_IDX], SAPA_RES_TROPO_POLY_COEFF_T00, SAPA_TROPO_POLY_MIN[coeff_size][SAPA_T00_IDX], LSAPA_TROPO_POLY_MIN[coeff_size][SAPA_T00_IDX], LSAPA_TROPO_POLY_MAX[coeff_size][SAPA_T00_IDX], NULL);
	float2long(pset->iono_poly_coeff[SAPA_T01_IDX], &pset->liono_poly_coeff[SAPA_T01_IDX], SAPA_RES_TROPO_POLY_COEFF_T01, SAPA_TROPO_POLY_MIN[coeff_size][SAPA_T01_IDX], LSAPA_TROPO_POLY_MIN[coeff_size][SAPA_T01_IDX], LSAPA_TROPO_POLY_MAX[coeff_size][SAPA_T01_IDX], NULL);
	float2long(pset->iono_poly_coeff[SAPA_T10_IDX], &pset->liono_poly_coeff[SAPA_T10_IDX], SAPA_RES_TROPO_POLY_COEFF_T01, SAPA_TROPO_POLY_MIN[coeff_size][SAPA_T10_IDX], LSAPA_TROPO_POLY_MIN[coeff_size][SAPA_T10_IDX], LSAPA_TROPO_POLY_MAX[coeff_size][SAPA_T10_IDX], NULL);
	float2long(pset->iono_poly_coeff[SAPA_T11_IDX], &pset->liono_poly_coeff[SAPA_T11_IDX], SAPA_RES_TROPO_POLY_COEFF_T11, SAPA_TROPO_POLY_MIN[coeff_size][SAPA_T11_IDX], LSAPA_TROPO_POLY_MIN[coeff_size][SAPA_T11_IDX], LSAPA_TROPO_POLY_MAX[coeff_size][SAPA_T11_IDX], NULL);

	memcpy(hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_sat_coeff, pset, sizeof(GPP_SAPA_HPAC_IONO_SAT_COEFFICIENT));
	GNSS_SET_IDX_IN_BITS_64(hpac->atmo[area]->iono->sat_prn_bits[sys], sat);		//set sat ID in sv_prn_bits bit mask
	return 0;
}//gpp_sapa_hpac_add_iono_sat_coeff_block()
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
GPPLONG gpp_sapa_hpac_add_iono_sat_grid_block(pGPP_SAPA_HPAC hpac, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 area, const pGPP_SAPA_HPAC_IONO_GRID_BLOCK pset)
{
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

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
GPPLONG gpp_sapa_hpac_add_grd_iono_correction(pGPP_SAPA_USE_STATES states, GPPUINT1 iarea, GPPUINT1 igrd, GPPUINT1 sat, GPPUINT1 sys, GPP_SAPA_HPAC_IONO_GRD_CORRECTION *pset)
{
	pGPP_SAPA_HPAC hpac = states->hpac;
	pGPP_SAPA_AREA area = states->area;

	pGPP_SAPA_HPAC_ATMO_BLOCK atmo = NULL;
	pGPP_SAPA_AREA_DEF_BLOCK area_def = NULL;

	pGPP_SAPA_HPAC_IONO iono = NULL;
	pGPP_SAPA_HPAC_IONO_GRID_BLOCK grd_iono = NULL;

	if (!hpac) return GPP_SAPA_ERR_INVALID_HPAC;

	if (!hpac->atmo) {
		hpac->atmo = (pGPP_SAPA_HPAC_ATMO_BLOCK*)calloc(SAPA_MAX_AREA, sizeof(pGPP_SAPA_HPAC_ATMO_BLOCK));
		if (!hpac->atmo) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!(atmo = hpac->atmo[iarea])) {
		hpac->atmo[iarea] = (pGPP_SAPA_HPAC_ATMO_BLOCK)calloc(1, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK));
		if (!(atmo = hpac->atmo[iarea])) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!area) {
		printf("ERROR: Area with AreaID(%d) has to be defined first", iarea);
		return GPP_SAPA_ERR_INVALID_AREA;
	}

	if (!area->area_bits[iarea / 64] & iarea % 64) {
		printf("ERROR: Area with AreaID(%d) has to be defined first", iarea);
		return GPP_SAPA_ERR_INVALID_AREA;
	}

	if (!(iono = atmo->iono)) {
		atmo->iono = (pGPP_SAPA_HPAC_IONO)calloc(1, sizeof(GPP_SAPA_HPAC_IONO));
		if (!(iono = atmo->iono)) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!(iono->iono_sat_block)) {
		iono->iono_sat_block = (pGPP_SAPA_HPAC_IONO_SAT_BLOCK**)calloc(GPP_SAPA_MAX_SYS, sizeof(GPP_SAPA_HPAC_IONO_SAT_BLOCK**));
		if (!(iono->iono_sat_block)) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}
	if (!(iono->iono_sat_block[sys])) {
		iono->iono_sat_block[sys] = (pGPP_SAPA_HPAC_IONO_SAT_BLOCK*)calloc(GPP_SAPA_MAX_SAT, sizeof(pGPP_SAPA_HPAC_IONO_SAT_BLOCK));
	}
	if (!(iono->iono_sat_block[sys][sat])) {
		iono->iono_sat_block[sys][sat] = (pGPP_SAPA_HPAC_IONO_SAT_BLOCK)calloc(1, sizeof(GPP_SAPA_HPAC_IONO_SAT_BLOCK));
		if (!iono->iono_sat_block[sys][sat]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!(grd_iono = iono->iono_sat_block[sys][sat]->iono_grid)) {
		iono->iono_sat_block[sys][sat]->iono_grid = (pGPP_SAPA_HPAC_IONO_GRID_BLOCK)calloc(1, sizeof(GPP_SAPA_HPAC_IONO_GRID_BLOCK));
		if (!(grd_iono = iono->iono_sat_block[sys][sat]->iono_grid)) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (grd_iono->num_grid) {
		if (grd_iono->num_grid != area_def->num_grid_points) {
			grd_iono->num_grid = area_def->num_grid_points;
			grd_iono->grid = (GPP_SAPA_HPAC_IONO_GRD_CORRECTION*)realloc(grd_iono->grid, grd_iono->num_grid * sizeof(GPP_SAPA_HPAC_IONO_GRD_CORRECTION));
			if (!grd_iono->grid) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
		}
	}
	else {
		grd_iono->num_grid = area_def->num_grid_points;
		if (!grd_iono->grid) {
			grd_iono->grid = (GPP_SAPA_HPAC_IONO_GRD_CORRECTION*)calloc(grd_iono->num_grid, sizeof(GPP_SAPA_HPAC_IONO_GRD_CORRECTION));
			if (!grd_iono->grid) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
		}
	}

	if (igrd >= grd_iono->num_grid) {
		printf("ERROR: grid point index (%d) out of range (number of grid points is %d)\n", igrd, grd_iono->num_grid);
		return GPP_SAPA_ERR_INVALID_GRD_IDX;
	}

	grd_iono->sz = 0;

	float2long(pset->val, &pset->lval, SAPA_IONO_GRD_RES, SAPA_IONO_GRD_MIN[grd_iono->sz], LSAPA_IONO_GRD_MAX[grd_iono->sz], LSAPA_IONO_GRD_MIN[grd_iono->sz], NULL);

	memcpy(&grd_iono->grid[igrd], pset, sizeof(GPP_SAPA_HPAC_IONO_GRD_CORRECTION));
	GNSS_SET_IDX_IN_BITS_64(grd_iono->grid_bits, igrd);
	GNSS_SET_IDX_IN_BITS_64((hpac->atmo_bits[iarea / 64]), (iarea % 64));

	return 0;
}

//---------------------------------------------------------------------------------------------------------------------------------
GPPLONG gpp_sapa_hpac_free_hpac(pGPP_SAPA_HPAC hpac)
{

	if (hpac) {
		if (hpac->header_block)
		{

			free(hpac->header_block);
			hpac->header_block = NULL;
		}
		if (hpac->atmo)
		{
			GPPUINT1 area, igrid;
			for (area = 0; area < GPP_SAPA_MAX_AREA_COUNT; area++)
			{
				if (hpac->atmo[area])
				{
					if (hpac->atmo[area]->area_def)
						free(hpac->atmo[area]->area_def);

					if (hpac->atmo[area]->tropo)
					{
						if (hpac->atmo[area]->tropo->tropo_poly_coeff_block)
							free(hpac->atmo[area]->tropo->tropo_poly_coeff_block);

						if (hpac->atmo[area]->tropo->tropo_grid)
						{
							if (hpac->atmo[area]->tropo->tropo_grid->grid)
							{
								for (igrid = 0; igrid < GPP_SAPA_MAX_GRID_POINT_PRESENT; igrid++)
									if (hpac->atmo[area]->tropo->tropo_grid->grid[igrid])
										free(hpac->atmo[area]->tropo->tropo_grid->grid[igrid]);


								free(hpac->atmo[area]->tropo->tropo_grid->grid);
							}
							free(hpac->atmo[area]->tropo->tropo_grid);
						}
						free(hpac->atmo[area]->tropo);
					}
					if (hpac->atmo[area]->iono)
					{
						if (hpac->atmo[area]->iono->iono_sat_block)
						{
							GPPUINT1 sys;
							for (sys = 0; sys < GPP_SAPA_MAX_SYS; sys++)
							{
								if (hpac->atmo[area]->iono->iono_sat_block[sys]) {
									GPPUINT1 sat;
									for (sat = 0; sat < GPP_SAPA_MAX_SAT; sat++)
									{
										if (hpac->atmo[area]->iono->iono_sat_block[sys][sat])
										{
											if (hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_sat_poly)
												free(hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_sat_poly);

											if (hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_sat_coeff)
												free(hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_sat_coeff);

											if (hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_grid)
											{
												if (hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_grid->grid)
												{
													for (igrid = 0; igrid < GPP_SAPA_MAX_GRID_POINT_PRESENT; igrid++)
														free(hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_grid->grid[igrid]);

													free(hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_grid->grid);
												}
												free(hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_grid);
											}
											free(hpac->atmo[area]->iono->iono_sat_block[sys][sat]);
										}
									}
									free(hpac->atmo[area]->iono->iono_sat_block[sys]);
								}
							}
							free(hpac->atmo[area]->iono->iono_sat_block);
						}
						free(hpac->atmo[area]->iono);
					}
					free(hpac->atmo[area]);
				}

			}
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


/************************************************************************************************************
 *	\brief Add an area definition block th GPP_SAPA_AREA structure
 ************************************************************************************************************/
GPPLONG gpp_sapa_area_add_area_def(pGPP_SAPA_AREA p_area, GPPUINT1 area, const pGPP_SAPA_AREA_DEF_BLOCK pset)
{
	GPPUINT1 ia;

	if (!p_area) return GPP_SAPA_ERR_INVALID_AREA;
	if(!pset) return GPP_SAPA_ERR_INVALID_AREA;

	ia=pset->area_id;// range of area_id (SF031) is 0-255. Use area_id as bit mask position

	if (!p_area->area_def_block) {//check if orbit structure is allocated
		p_area->area_def_block = (pGPP_SAPA_AREA_DEF_BLOCK*)calloc(SAPA_MAX_AREA, sizeof(pGPP_SAPA_AREA_DEF_BLOCK));
		if (!p_area->area_def_block) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!p_area->area_def_block[ia]) { // check if sv[sys][sat] is allocated
		p_area->area_def_block[ia] = (pGPP_SAPA_AREA_DEF_BLOCK)calloc(1, sizeof(GPP_SAPA_AREA_DEF_BLOCK));
		if (!(p_area->area_def_block[ia])) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}
	float2long(pset->area_ref_lat, &pset->larea_ref_lat, SAPA_RES_AREA_REF_LATITUDE, SAPA_AREA_LAT_MIN, LSAPA_AREA_LAT_MAX, LSAPA_AREA_LAT_MIN, NULL);
	float2long(pset->area_ref_long, &pset->larea_ref_long, SAPA_RES_AREA_REF_LONGITUDE, SAPA_AREA_LONG_MIN, LSAPA_AREA_LONG_MAX, LSAPA_AREA_LONG_MIN, NULL);
	float2long(pset->area_lat_grid_node_spacing, &pset->larea_lat_grid_node_spacing, SAPA_RES_AREA_GRID_LATITUDE_SPACING, SAPA_AREA_GRD_LAT_MIN, LSAPA_AREA_GRD_LAT_MAX, LSAPA_AREA_GRD_LAT_MIN, NULL);
	float2long(pset->area_long_grid_node_spacing, &pset->larea_long_grid_node_spacing, SAPA_RES_AREA_GRID_LONGITUDE_SPACING, SAPA_AREA_GRD_LONG_MIN, LSAPA_AREA_GRD_LONG_MAX, LSAPA_AREA_GRD_LONG_MIN, NULL);

	memcpy(p_area->area_def_block[ia], pset, sizeof(GPP_SAPA_AREA_DEF_BLOCK));
	GNSS_SET_IDX_IN_BITS_64(p_area->area_bits[ia/64], ia%64);
	return 0;
}//gpp_sapa_area_add_area_def()


/************************************************************************************************************
* \brief Free SAPA_OCB_HANDLDE in SAPA_HANDLE
************************************************************************************************************/
GPPLONG gpp_sapa_handle_free_ocbHdl(SAPA_HANDLE *sapaHdl)
{
	GPPUINT1 sys, config;

	if (!sapaHdl) return -1;
	if (!sapaHdl->ocbHdl) return 0;
	for (sys = 0; sys < GPP_SAPA_MAX_SYS; sys++)
	{
		if (!sapaHdl->ocbHdl[sys])
			continue;
		for (config = 0; config < GPP_SAPA_MAX_OCB_CONFIGS; config++)
		{
			if (!sapaHdl->ocbHdl[sys][config])
				continue;
			free(sapaHdl->ocbHdl[sys][config]);
		}
		free(sapaHdl->ocbHdl[sys]);
	}
	free(sapaHdl->ocbHdl);
	sapaHdl->ocbHdl = NULL;
	return 0;
}



GPPLONG gpp_sapa_handle_malloc_ocbHdl(SAPA_HANDLE *sapaHdl)
{
	GPPUINT1 sys;

	if (!sapaHdl) return -1;

	if (!sapaHdl->ocbHdl)
	{
		sapaHdl->ocbHdl = (pSAPA_OCB_HANDLE**)calloc(GPP_SAPA_MAX_SYS, sizeof(pSAPA_OCB_HANDLE*));
		for (sys = 0; sys < GPP_SAPA_MAX_SYS; sys++)
		{
			sapaHdl->ocbHdl[sys] = (pSAPA_OCB_HANDLE*)calloc(GPP_SAPA_MAX_OCB_CONFIGS, sizeof(SAPA_OCB_HANDLE*));
		}
	}
	return 0;
}


//------------------------------------------------------------------Handle------------------------------------
GPPLONG gpp_sapa_hpac_add_config_hpacHdl(pSAPA_HANDLE sapaHdl, const pSAPA_HPAC_HANDLE pset, FILE *fp)
{
	if (!sapaHdl) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;

	if (!sapaHdl->hpacHdl)
	{
		sapaHdl->hpacHdl = (pSAPA_HPAC_HANDLE)calloc(1, sizeof(SAPA_HPAC_HANDLE));
		if (!sapaHdl->hpacHdl) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	memcpy(sapaHdl->hpacHdl, pset, sizeof(SAPA_HPAC_HANDLE));
	return 0;
}
//-----------------------------------------------------------------------------------------------------------------------------------------
GPPLONG gpp_sapa_hpac_add_ionoHdl(pSAPA_HANDLE sapaHdl, GPPUINT1 sys, const pSAPA_HPAC_HANDLE_IONO pset, FILE *fp)
{
	GPPUINT1 configlist[66];
	GPPUINT1 iconf = 0;

	if (!sapaHdl) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;

	if (!sapaHdl->hpacIonoHdl)
	{
		sapaHdl->hpacIonoHdl = (pSAPA_HPAC_HANDLE_IONO**)calloc(GPP_SAPA_MAX_SYS, sizeof(SAPA_HPAC_HANDLE_IONO**));
		if (!sapaHdl->hpacIonoHdl) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!sapaHdl->hpacIonoHdl[sys])
	{
		sapaHdl->hpacIonoHdl[sys] = (pSAPA_HPAC_HANDLE_IONO*)calloc(GPP_SAPA_MAX_HPAC_CONFIGS, sizeof(SAPA_HPAC_HANDLE_IONO*));
		if (!sapaHdl->hpacIonoHdl[sys]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	gpp_sapa_get_configlist(sapaHdl->hpacIonoHdl_bits[sys], configlist);

	printf("config=%d", configlist[0]);
	if (configlist[0] == 64) {
		fprintf(fp, "SSRM2SAPA ERROR: TOO many OCB configs!\n");
		return GPP_SAPA_ERR_INVALID_OCB_HANDLE;
	}

	iconf = configlist[configlist[0]];

	if (!sapaHdl->hpacIonoHdl[sys][iconf])
	{
		sapaHdl->hpacIonoHdl[sys][iconf] = (pSAPA_HPAC_HANDLE_IONO)calloc(1, sizeof(SAPA_HPAC_HANDLE_IONO));
		if (!sapaHdl->hpacIonoHdl[sys][iconf]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	memcpy(sapaHdl->hpacIonoHdl[sys][iconf], pset, sizeof(pSAPA_HPAC_HANDLE_IONO));
	GNSS_SET_IDX_IN_BITS_64(sapaHdl->hpacIonoHdl_bits[sys], iconf);
	return 0;
}
//-----------------------------------------------------------------------------------------------------------------------------------------
GPPLONG gpp_sapa_hpac_add_config_tropoHdl(pSAPA_HANDLE sapaHdl, const SAPA_HPAC_HANDLE_TROPO *pset, FILE *fp)
{
	GPPUINT1 configlist[66];
	GPPUINT1 iconf = 0;

	if (!sapaHdl) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;

	if (!sapaHdl->hpacTropoHdl)
	{
		sapaHdl->hpacTropoHdl = (pSAPA_HPAC_HANDLE_TROPO*)calloc(GPP_SAPA_MAX_HPAC_CONFIGS, sizeof(SAPA_HPAC_HANDLE_TROPO*));
		if (!sapaHdl->hpacTropoHdl) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	gpp_sapa_get_configlist(sapaHdl->hpacTropoHdl_bits, configlist);

	printf("config=%d", configlist[0]);
	if (configlist[0] == 64) {
		fprintf(fp, "SSRM2SAPA ERROR: TOO many OCB configs!\n");
		return GPP_SAPA_ERR_INVALID_OCB_HANDLE;
	}

	iconf = configlist[configlist[0]];

	if (!sapaHdl->hpacTropoHdl[iconf])
	{
		sapaHdl->hpacTropoHdl[iconf] = (pSAPA_HPAC_HANDLE_TROPO)calloc(1, sizeof(SAPA_HPAC_HANDLE_TROPO));
		if (!sapaHdl->hpacTropoHdl) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	memcpy(sapaHdl->hpacTropoHdl[iconf], pset, sizeof(SAPA_HPAC_HANDLE_TROPO));
	GNSS_SET_IDX_IN_BITS_64(sapaHdl->hpacTropoHdl_bits, iconf);

	return 0;
}
//-----------------------------------------------------------------------------------------------------------------------------------------


GPPLONG gpp_sapa_handle_free_gadHdl(SAPA_HANDLE *sapaHdl)
{
	if (!sapaHdl) return -1;
	free(sapaHdl->gadHdl);
	sapaHdl->gadHdl = NULL;
	return 0; //ok
}//gpp_sapa_handle_free_gadHdl()

GPPLONG gpp_sapa_handle_malloc_gadHdl(pSAPA_HANDLE sapaHdl)
{
	if (!sapaHdl) return -1;
	if(sapaHdl->gadHdl) gpp_sapa_handle_free_gadHdl(sapaHdl);
	sapaHdl->gadHdl = (pSAPA_GAD_HANDLE)calloc(1, sizeof(SAPA_GAD_HANDLE));
	return 0; //ok
}//gpp_sapa_handle_malloc_gadHdl()




GPPLONG gpp_sapa_config_add_ocb_config(SAPA_HANDLE *sapaHdl, GPPUINT1 sys, const SAPA_OCB_HANDLE *pset, FILE *fp)
{
	GPPUINT1 configlist[66];
	GPPUINT1 iconf=0;

	if (!sapaHdl) return -1;
	if (!pset) return GPP_SAPA_ERR_INVALID_OCB_HANDLE;

	if (sys >= SAPA_MAX_SYS) return GPP_SAPA_ERR_INVALID_SYS;
	//if (config >= GPP_SAPA_MAX_OCB_CONFIGS) return GPP_SAPA_ERR_INVALID_CONFIG;

	if(!sapaHdl->ocbHdl){
		GPPLONG rc;
		if(rc=gpp_sapa_handle_malloc_ocbHdl(sapaHdl)) return rc;
	}

	gpp_sapa_get_configlist(sapaHdl->ocbHdl_bits[sys], configlist);

	printf("config=%d", configlist[0]);
	if(configlist[0]==64){
		fprintf(fp, "SSRM2SAPA ERROR: TOO many OCB configs!\n");
		return GPP_SAPA_ERR_INVALID_OCB_HANDLE;
	}

	iconf=configlist[configlist[0]];
	

	if (!sapaHdl->ocbHdl[sys][iconf]){
		sapaHdl->ocbHdl[sys][iconf] = (pSAPA_OCB_HANDLE)calloc(1, sizeof(SAPA_OCB_HANDLE));
		if (!(sapaHdl->ocbHdl[sys][iconf])) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}
	memcpy(sapaHdl->ocbHdl[sys][iconf], pset, sizeof(SAPA_OCB_HANDLE));
	GNSS_SET_IDX_IN_BITS_64(sapaHdl->ocbHdl_bits[sys], iconf);

	return 0; //ok
}//gpp_sapa_config_add_ocb_config()


//================================================================================================================================

GPPLONG gpp_sapa_config_add_gad_config(SAPA_HANDLE *sapaHdl, const SAPA_GAD_HANDLE *pset, FILE *fp)
{
	GPPUINT1 configlist[66];
	GPPUINT1 iconf = 0;

	if (!sapaHdl) return -1;
	if (!pset) return GPP_SAPA_ERR_INVALID_GAD_HANDLE;

	if (!sapaHdl->gadHdl)
	{
		sapaHdl->gadHdl = (SAPA_GAD_HANDLE**)calloc(1, sizeof(SAPA_GAD_HANDLE*));
	}
	gpp_sapa_get_configlist(sapaHdl->gadHdl_bits, configlist);

	if (configlist[0] == 64) {
		fprintf(fp, "SSRM2SAPA ERROR: TOO many Area Def configs!\n");
		return GPP_SAPA_ERR_INVALID_GAD_HANDLE;
	}

	iconf = configlist[configlist[0]];

	printf("====== %d ======\n", iconf);

	if (!sapaHdl->gadHdl[iconf]) {
		sapaHdl->gadHdl[iconf] = (SAPA_GAD_HANDLE*)calloc(1, sizeof(SAPA_GAD_HANDLE));
		if (!(sapaHdl->gadHdl[iconf])) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	memcpy(sapaHdl->gadHdl, pset, sizeof(SAPA_GAD_HANDLE));
	GNSS_SET_IDX_IN_BITS_64(sapaHdl->gadHdl_bits, iconf);

	return 0; //ok
}

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
extern void gpp_sapa_float2buffer(GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos, GPPDOUBLE min, GPPDOUBLE max, GPPUINT1 bits, GPPDOUBLE res, GPPUINT2 *invalid, GPPDOUBLE value)
{
	GN_LONG lval = 0;

	if (value<min || value>max) {
		if (invalid) {
			gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, bits, *invalid);
			return;
		}
		else
		{
			gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, bits, lval);
			return;
		}
	}

	lval = (value - min) / res;
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, bits, lval);


} /* gpp_sapa_float2buffer() */

GPPUINT1 float2long(GPPDOUBLE val, GPPLONG *lval, GPPDOUBLE Res, GPPDOUBLE Rmin, GPPLONG Lmax, GPPLONG Lmin, const GPPUINT2 *invalid)
{
	*lval = (val - Rmin) / Res;              //Conversion of float value to long
	//printf("  %ld ", *lval);

	if (*lval > Lmax || *lval < Lmin)     //Checking long value with max and min long values
	{
		if (invalid)
		{
			*lval = invalid;
		}
		return 0;
	}
	return 1;
}

GPPUINT1 gpp_sapa_buffer2float(const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos, GPPDOUBLE min, GPPUINT1 bits, GPPDOUBLE res, const GPPUINT2 *invalid, GPPDOUBLE *value)
{
	GPPLONG lval=gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, bits);

	if(invalid){
		if(lval==*invalid) return 0;
	}

	*value=(lval*res) + min;
	return 1;
}//gpp_sapa_buffer2float()









GPPLONG gpp_sapa_get_bit_diff(GPPLONG byte_pos, GPPLONG bit_pos, GPPLONG byte_pos0, GPPLONG bit_pos0)
{
	return (byte_pos - byte_pos0) * 8 + (bit_pos - bit_pos0);
}

void gpp_sapa_set_area_bits(GPPUINT8*area_bits, GPPUINT1 value)
{
	GPPUINT8 one = 1;
	area_bits[value / 64] |= (one << (value % 64));
}

//void gpp_sapa_get_arealist(GPPUINT8*area_bits, GPPUINT8 *arr)
//{
//	int z = 1;
//	GPPUINT8 one = 1;
//	for (int i = 0; i < 4; i++)
//		for (int j = 0; j < 64; j++)
//		{
//			GPPUINT8 temp = one << j;
//			if (area_bits[i] & temp)
//				arr[z++] = 64 * i + j;
//		}
//
//	arr[0] = z - 1;
//}

//============================================================================================================================================
//											Needed for testing (Alternative will we replaced)
//============================================================================================================================================
//Returns 1 if a bit at position pos in cons_bits is set else return 0
GPPUINT1 gpp_sapa_get_constellation_present_bit(GPPUINT2 cons_bits, GPPUINT1 pos)
{
	GPPUINT2 base = 1;
	return (cons_bits & (base << pos) ? 1 : 0);
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
	return ((1 << pos)|cons_bits);
}

//============================================================================================================================================


/************************************************************************************************************
 *	\brief Free SAPA_HANDLE
 ************************************************************************************************************/
GPPLONG gpp_sapa_handle_free_handle(SAPA_HANDLE **ppSapaHdl)
{

	SAPA_HANDLE *sapaHdl;

	if (!ppSapaHdl) return -1;
	sapaHdl = *ppSapaHdl;

	if (!sapaHdl) return 0;

	gpp_sapa_handle_free_ocbHdl(sapaHdl);

	free(*ppSapaHdl);
	*ppSapaHdl = NULL;

	return 0;
}//gpp_sapa_handle_free_handle()

/************************************************************************************************************
 *	\brief Malloc SAPA_HANDLE
 ************************************************************************************************************/
GPPLONG gpp_sapa_handle_malloc_handle(SAPA_HANDLE **ppSapaHdl)
{
	if (!ppSapaHdl) return -1;
	if (*ppSapaHdl) gpp_sapa_handle_free_handle(ppSapaHdl);

	*ppSapaHdl = (SAPA_HANDLE*)calloc(1, sizeof(SAPA_HANDLE));
	if (!(*ppSapaHdl)) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;

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
	GPPLONG sapa_preamble, type, crc;
	GPPLONG byte_pos=0, bit_pos=0, numDataBytes=0;

	if((sapa_preamble=gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, 8))!=SAPA_PREAMBLE) return GPP_SAPA_ERR_PREAMBLE;
	if((type=gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, 7))!= SAPA_TYPE_OCB) return GPP_SAPA_ERR_TYPE;
	if(!(numDataBytes=gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, 10))) return GPP_SAPA_ERR_PAYLOAD_LENGTH;

	*len_sapa_bits = numDataBytes * 8;
	*ea_flag = gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, 1);
	*message_crc_type = gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, 2);

	if (*message_crc_type > 3) return GPP_SAPA_ERR_CRC_TYPE;

	*crc_frame = gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, 4);

	memcpy(ocb_buffer, (sapa_buffer + byte_pos), numDataBytes);
	byte_pos += numDataBytes;

	crc = gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, SAPA_CRC_BYTES[*message_crc_type]);

	return 0;
}//gpp_sapa_sapa_buffer_to_ocb_buffer()

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
	GPPLONG sapa_preamble, type, crc;
	GPPLONG byte_pos=0, bit_pos=0, numDataBytes=0;

	if((sapa_preamble=gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, 8))!=SAPA_PREAMBLE) return GPP_SAPA_ERR_PREAMBLE;
	if((type=gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, 7))!= SAPA_TYPE_HPAC) return GPP_SAPA_ERR_TYPE;
	if(!(numDataBytes=gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, 10))) return GPP_SAPA_ERR_PAYLOAD_LENGTH;

	*len_sapa_bits = numDataBytes*8;
	*ea_flag = gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, 1);
	*message_crc_type = gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, 2);
	if (*message_crc_type > 3) return GPP_SAPA_ERR_CRC_TYPE;

	*crc_frame = gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, 4);

	memcpy(hpac_buffer, (sapa_buffer + byte_pos), numDataBytes);
	byte_pos += numDataBytes;

	crc = gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, SAPA_CRC_BYTES[*message_crc_type]);
	return 0;
}//gpp_sapa_sapa_buffer_to_hpac_buffer()

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
	GPPLONG sapa_preamble, type, crc;
	GPPLONG byte_pos=0, bit_pos=0, numDataBytes=0;

	if((sapa_preamble=gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, 8))!=SAPA_PREAMBLE) return GPP_SAPA_ERR_PREAMBLE;
	if((type=gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, 7))!= SAPA_TYPE_AREA) return GPP_SAPA_ERR_TYPE;
	if(!(numDataBytes=gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, 10))) return GPP_SAPA_ERR_PAYLOAD_LENGTH;

	*len_sapa_bits = numDataBytes * 8;
	*ea_flag = gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, 1);
	*message_crc_type = gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, 2);
	if (*message_crc_type > 3) return GPP_SAPA_ERR_CRC_TYPE;

	*crc_frame = gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, 4);

	memcpy(area_buffer, (sapa_buffer + byte_pos), numDataBytes);
	byte_pos += numDataBytes;

	crc = gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, SAPA_CRC_BYTES[*message_crc_type]);

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

void gpp_sapa_get_syslist(GPPUINT8 sys_bits, GPPUINT1 *syslist)
{
	GPPUINT1 sys = 0, num = 0;
	GPPUINT8 bit = 1;

	if (!syslist) return;

	memset(syslist, 0, 18 * sizeof(GPPUINT1));

	for (sys = 0; sys < GPP_SAPA_MAX_SYS; sys++) {

		if (sys_bits&(bit << sys)) {
			syslist[num + 1] = sys;
			num++;
		}
	}
	syslist[0] = num;
}
//Sets the bit position according to the index value
void gpp_sapa_set_hpac_bits(GPPUINT1 *set_bits, GPPUINT1 value)
{
	if (!set_bits) return -1;
	if(value<8)
	*set_bits |= (1 << value);
}

//Returns the set bit position in the arguement, -1 if no SetBit
GPPUINT1 gpp_sapa_get_hpac_bits(GPPUINT1 set_bits)
{
	GPPINT1 i,ans=-1;
	for (i = 0; i < 8; i++)
		if ((1 << i) & set_bits)
		{
			//printf("Bhaisaab returning this 1 %d\n ", ans);
			ans = i;
			break;
		}
	//printf("Bhaisaab returning this 2 %d\n ", ans);
	return ans;
}

//Returns the set bit position in the arguement, -1 if no SetBit
GPPUINT1 gpp_sapa_get_config_bits(GPPUINT1 set_bits)
{
	int i;
	for (i = 0; i < 8; i++)
		if ((1 << i) & set_bits)
			return i;
}


GPPLONG length_bytes_from_bits(GPPLONG b)
{
	return (((b) / 8) + ((b) % 8 ? 1 : 0));
}
