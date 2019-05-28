#include "gpp_sapa.h"
#include "bit2buff.h"


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

	if (!siglist) return;

	memset(siglist, 0, 34*sizeof(GPPUINT1));

	for (sig=0; sig<GPP_SAPA_MAX_SIG; sig++) {
		if (sig_bits&(1<<sig)) {
			siglist[num+1] = sig;
			num++;
		}
	}
	siglist[0] = num;
}//gpp_sapa_get_siglist()



//Return Seconds passed in the hour when data is received.
GPPINT gpp_sapa_get_hourly_time_tag(GPPINT seconds_of_week)
{
	return(seconds_of_week % 3600);
}

//Returns seconds passed since the beginning including all gps_weeks.
GPPINT gpp_sapa_get_full_time_tag(GPPINT gps_week, GPPINT seconds_of_week)
{
	return(((gps_week - 1) * 7 * 24 * 3600) + seconds_of_week);
}


//Returns Orbit ,Clock and  Bias flag value
void gpp_sapa_get_ocb_flag_value(GPPUINT1 ocb_present_flag, GPPUINT1 *o_flag, GPPUINT1 *c_flag, GPPUINT1 *b_flag)
{
	GPPUINT1 var = 1;
	*o_flag = (ocb_present_flag & (var << GPP_SAPA_OCB_FLAG_IDX_ORB)) ? 1 : 0;
	*c_flag = (ocb_present_flag & (var << GPP_SAPA_OCB_FLAG_IDX_CLK)) ? 1 : 0;
	*b_flag = (ocb_present_flag & (var << GPP_SAPA_OCB_FLAG_IDX_BIAS)) ? 1 : 0;
}
//Returns highest order of satellite set



//=============================================== functions to add data to structure For OCB =================================================
/************************************************************************************************************

 *        \brief Allocate two-dimensional sv pointer array
 11
 ***********************************************************************************************************/

GPPLONG gpp_sapa_ocb_malloc_sv(pGPP_SAPA_OCB ocb)
{
	GPPUINT1 sys;

	if (!ocb) return GPP_SAPA_ERR_INVALID_OCB;

	if (!ocb->sv) {

		ocb->sv = (pGPP_SAPA_OCB_SV**)calloc(GPP_SAPA_MAX_CONS, sizeof(GPP_SAPA_OCB**));

		if (!ocb->sv) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;

		for (sys = 0; sys < GPP_SAPA_MAX_CONS; sys++) {
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
	GPPUINT1 sys, sat;

	if (!ocb) return 0;
	if (!ocb->sv) return 0;

	for (sys = 0; sys < GPP_SAPA_MAX_CONS; sys++) {
		for (sat = 0; sat < GPP_SAPA_MAX_SAT; sat++) {
			if (ocb->sv[sys][sat]) {
				//free orbit, clock, and bias structures
				//set all values to zero
				memset(ocb->sv[sys][sat], 0, sizeof(GPP_SAPA_OCB_SV));
				free(ocb->sv[sys][sat]);
				ocb->sv[sys][sat] = NULL;
			}
		}
		free(ocb->sv[sys]);
		ocb->sv[sys] = NULL;
	}

	free(ocb->sv);

	ocb->sv = NULL;

	return 0;

}//gpp_sapa_ocb_free_ocb()


GPPLONG gpp_sapa_ocb_add_sv(pGPP_SAPA_OCB ocb, GPPUINT1 sys, GPPUINT1 sat, const pGPP_SAPA_OCB_SV pset)
{
	GPPLONG rc;							//control variable
	pGPP_SAPA_OCB_SV sv = NULL;			// Pointer to OCB_SV

	if (!ocb) return GPP_SAPA_ERR_INVALID_OCB;

	if (!ocb->sv) {// allocate the sys-sat two dimensional pointer array
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
	GPPLONG rc;							//control variable
	pGPP_SAPA_OCB_SV sv = NULL;			// Pointer to OCB_SV

	if (!ocb) return GPP_SAPA_ERR_INVALID_OCB;

	if (!ocb->sv) {// allocate the sys-sat two dimensional pointer array
		if (rc = gpp_sapa_ocb_malloc_sv(ocb)) return rc;
	}

	if (!(sv = ocb->sv[sys][sat])) { // check if sv[sys][sat] is allocated
		ocb->sv[sys][sat] = (GPP_SAPA_OCB_SV*)calloc(1, sizeof(GPP_SAPA_OCB_SV));
		if (!(sv = ocb->sv[sys][sat])) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!sv->orb) {//check if orbit structure is allocated
		sv->orb = (pGPP_SAPA_OCB_SV_ORB)calloc(1, sizeof(GPP_SAPA_OCB_SV_ORB));
		if (!sv->orb) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	memcpy(sv->orb, pset, sizeof(GPP_SAPA_OCB_SV_ORB));	//copy orbit data
	GPPUINT8 bit = 1;
	ocb->sv_prn_bits[sys] |= (bit << sat);							//set sat ID in sv_prn_bits bit mask
	sv->ocb_present_flag |= (1 << GPP_SAPA_OCB_FLAG_IDX_ORB);							//set ocb_present_flag as it is assumed that only valid data are stored in the structure

	return 0;

}//gpp_sapa_ocb_add_orb()

/************************************************************************************************************/

GPPLONG gpp_sapa_ocb_add_clk(pGPP_SAPA_OCB ocb, GPPUINT1 sys, GPPUINT1 sat, const pGPP_SAPA_OCB_SV_CLK pset)
{
	GPPLONG rc;							//control variable
	pGPP_SAPA_OCB_SV sv = NULL;			// Pointer to OCB_SV

	if (!ocb) return GPP_SAPA_ERR_INVALID_OCB;

	if (!ocb->sv) {// allocate the sys-sat two dimensional pointer array
		if (rc = gpp_sapa_ocb_malloc_sv(ocb)) return rc;
	}

	if (!(sv = ocb->sv[sys][sat])) { // check if sv[sys][sat] is allocated
		ocb->sv[sys][sat] = (GPP_SAPA_OCB_SV*)calloc(1, sizeof(GPP_SAPA_OCB_SV));
		if (!(sv = ocb->sv[sys][sat])) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!sv->clk) {//check if orbit structure is allocated
		sv->clk = (pGPP_SAPA_OCB_SV_CLK)calloc(1, sizeof(GPP_SAPA_OCB_SV_CLK));
		if (!sv->clk) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	memcpy(sv->clk, pset, sizeof(GPP_SAPA_OCB_SV_CLK));	//copy clock data
	GPPUINT8 bit = 1;
	ocb->sv_prn_bits[sys] |= (bit << sat);						//set sat ID in sv_prn_bits bit mask
	sv->ocb_present_flag |= (1 << GPP_SAPA_OCB_FLAG_IDX_CLK);							//set ocb_present_flag as it is assumed that only valid data are stored in the structure

	return 0;
}//gpp_sapa_ocb_add_clk()

/************************************************************************************************************/

GPPLONG gpp_sapa_ocb_add_pb(pGPP_SAPA_OCB ocb, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 sig, const pGPP_SAPA_OCB_SV_BIAS_PB pset)
{
	GPPLONG rc;									//control variable
	pGPP_SAPA_OCB_SV sv = NULL;					// Pointer to OCB_SV
	pGPP_SAPA_OCB_SV_BIAS bias = NULL;			// Pointer to OCB_SV_BIAS
	pGPP_SAPA_OCB_SV_BIAS_PB	pb = NULL;	// Pointer to OCB_SV_SATPHASEBIAS

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
	bias->pb_sig_bits |= (1 << sig);								//set signal in signal bit mask for this satellite
	GPPUINT8 bit = 1;
	ocb->sv_prn_bits[sys] |= (bit << sat);							//set sat ID in sv_prn_bits bit mask
	sv->ocb_present_flag |= (1 << GPP_SAPA_OCB_FLAG_IDX_BIAS);

	return 0; //GPP_SAPA_OK
}
//----------------------------------------------------------------------------------------------------------------------------

GPPLONG gpp_sapa_ocb_add_header(pGPP_SAPA_OCB ocb, GPPUINT1 sys, const pGPP_SAPA_OCB_HEADER pset)
{
	if (!ocb) return GPP_SAPA_ERR_INVALID_OCB;

	if (!ocb->header_block) { // check if sv[sys][sat] is allocated
		ocb->header_block = (pGPP_SAPA_OCB_HEADER*)calloc(GPP_SAPA_MAX_CONS, sizeof(pGPP_SAPA_OCB_HEADER));
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
	GPPLONG rc;									//control variable
	pGPP_SAPA_OCB_SV sv = NULL;					// Pointer to OCB_SV
	pGPP_SAPA_OCB_SV_BIAS bias = NULL;			// Pointer to OCB_SV_BIAS
	pGPP_SAPA_OCB_SV_BIAS_CB cb = NULL;	// Pointer to OCB_SV_SATPHASEBIAS

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


	memcpy(cb, pset, sizeof(GPP_SAPA_OCB_SV_BIAS_CB)); 	//Copy Phase bias content
	bias->cb_sig_bits |= (1 << sig);								//set signal in signal bit mask for this satellite
	GPPUINT8 bit = 1;
	ocb->sv_prn_bits[sys] |= (bit <<sat);							//set sat ID in sv_prn_bits bit mask
	sv->ocb_present_flag |= (1<<GPP_SAPA_OCB_FLAG_IDX_BIAS);

	return 0; //GPP_SAPA_OK
}
//==============================================functions to add data to structure For HPAC================================================================
GPPLONG gpp_sapa_hpac_add_header(pGPP_SAPA_HPAC hpac,GPPUINT1 sys, const pGPP_SAPA_HPAC_HEADER pset)
{
	if (!hpac) return GPP_SAPA_ERR_INVALID_HPAC_AREA;

	if (!hpac->header_block) {//check if Header structure is allocated
		hpac->header_block = (pGPP_SAPA_HPAC_HEADER*)calloc(GPP_SAPA_MAX_CONS, sizeof(pGPP_SAPA_HPAC_HEADER));
		if (!hpac->header_block) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->header_block[sys]) {//check if header_block[sys] structure is allocated
		hpac->header_block[sys] = (pGPP_SAPA_HPAC_HEADER)calloc(1, sizeof(GPP_SAPA_HPAC_HEADER));
		if (!hpac->header_block[sys]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}
	memcpy(hpac->header_block[sys], pset, sizeof(GPP_SAPA_HPAC_HEADER));	//copy header data

	return 0;
}//gpp_sapa_hpac_add_header()
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
GPPLONG gpp_sapa_hpac_add_area(pGPP_SAPA_HPAC hpac,GPPUINT1 sys, GPPUINT1 area, const pGPP_SAPA_HPAC_AREA pset)
{
	pGPP_SAPA_HPAC_ATMO_BLOCK atmo = NULL;		// Pointer to ATMO

	if (!hpac) return GPP_SAPA_ERR_INVALID_HPAC_AREA;

	if (!hpac->atmo) {//check if atmo structure is allocated
		hpac->atmo = (pGPP_SAPA_HPAC_ATMO_BLOCK**)calloc(GPP_SAPA_MAX_CONS, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK**));
		if (!hpac->atmo) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[sys]) {//check if atmo[sys] structure is allocated
		hpac->atmo[sys] = (pGPP_SAPA_HPAC_ATMO_BLOCK*)calloc(GPP_SAPA_MAX_AREA_COUNT, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK*));
		if (!hpac->atmo[sys]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[sys][area]) {//check if atmo[sys][area] structure is allocated
		hpac->atmo[sys][area] = (pGPP_SAPA_HPAC_ATMO_BLOCK)calloc(1, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK));
		if (!hpac->atmo[sys][area]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[sys][area]->area_def) {//check if area def structure is allocated
		hpac->atmo[sys][area]->area_def = (pGPP_SAPA_HPAC_AREA)calloc(1, sizeof(GPP_SAPA_HPAC_AREA));
		if (!hpac->atmo[sys][area]->area_def) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}
	memcpy(hpac->atmo[sys][area]->area_def, pset, sizeof(GPP_SAPA_HPAC_AREA));	//copy atmo block data
	return 0; //GPP_SAPA_OK
}//gpp_sapa_hpac_add_area()
//-----------------------------------------------------------------------------------------------------------------------------------------------------
GPPLONG gpp_sapa_hpac_add_tropo(pGPP_SAPA_HPAC hpac,GPPUINT1 sys, GPPUINT1 area, const pGPP_SAPA_HPAC_TROPO pset)
{
	pGPP_SAPA_HPAC_ATMO_BLOCK atmo = NULL;		// Pointer to ATMO

	if (!hpac) return GPP_SAPA_ERR_INVALID_HPAC_AREA;

	if (!hpac->atmo) {//check if atmo structure is allocated
		hpac->atmo = (pGPP_SAPA_HPAC_ATMO_BLOCK**)calloc(GPP_SAPA_MAX_CONS, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK**));
		if (!hpac->atmo) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[sys]) {//check if atmo[sys] structure is allocated
		hpac->atmo[sys] = (pGPP_SAPA_HPAC_ATMO_BLOCK*)calloc(GPP_SAPA_MAX_AREA_COUNT, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK*));
		if (!hpac->atmo[sys]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[sys][area]) {//check if atmo[sys][area] structure is allocated
		hpac->atmo[sys][area] = (pGPP_SAPA_HPAC_ATMO_BLOCK)calloc(1, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK));
		if (!hpac->atmo[sys][area]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[sys][area]->tropo) {//check if tropo structure is allocated
		hpac->atmo[sys][area]->tropo = (pGPP_SAPA_HPAC_TROPO)calloc(1, sizeof(GPP_SAPA_HPAC_TROPO));
		if (!hpac->atmo[sys][area]->tropo) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}
	memcpy(hpac->atmo[sys][area]->tropo, pset, sizeof(GPP_SAPA_HPAC_TROPO));	//copy clock data
	return 0; //GPP_SAPA_OK
}//gpp_sapa_hpac_add_tropo()
//----------------------------------------------------------------------------------------------------------------------------------------------------
GPPLONG gpp_sapa_hpac_add_tropo_block(pGPP_SAPA_HPAC hpac,GPPUINT1 sys, GPPUINT1 area, const pGPP_SAPA_HPAC_TROPO_BLOCK pset)
{
	pGPP_SAPA_HPAC_ATMO_BLOCK atmo = NULL;		// Pointer to ATMO
	pGPP_SAPA_HPAC_TROPO tropo = NULL;			// Pointer to TROPO
	if (!hpac) return GPP_SAPA_ERR_INVALID_HPAC_AREA;

	if (!hpac->atmo) {//check if atmo structure is allocated
		hpac->atmo = (pGPP_SAPA_HPAC_ATMO_BLOCK**)calloc(GPP_SAPA_MAX_CONS, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK**));
		if (!hpac->atmo) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[sys]) {//check if atmo[sys] structure is allocated
		hpac->atmo[sys] = (pGPP_SAPA_HPAC_ATMO_BLOCK*)calloc(GPP_SAPA_MAX_AREA_COUNT, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK*));
		if (!hpac->atmo[sys]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[sys][area]) {//check if atmo[sys][area] structure is allocated
		hpac->atmo[sys][area] = (pGPP_SAPA_HPAC_ATMO_BLOCK)calloc(1, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK));
		if (!hpac->atmo[sys][area]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[sys][area]->tropo) {//check if tropo structure is allocated
		hpac->atmo[sys][area]->tropo = (pGPP_SAPA_HPAC_TROPO)calloc(1, sizeof(GPP_SAPA_HPAC_TROPO));
		if (!hpac->atmo[sys][area]->tropo) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[sys][area]->tropo->tropo_block) {//check if tropo block structure is allocated
		hpac->atmo[sys][area]->tropo->tropo_block = (pGPP_SAPA_HPAC_TROPO_BLOCK)calloc(1, sizeof(GPP_SAPA_HPAC_TROPO_BLOCK));
		if (!hpac->atmo[sys][area]->tropo->tropo_block) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}
	memcpy(hpac->atmo[sys][area]->tropo->tropo_block, pset, sizeof(GPP_SAPA_HPAC_TROPO_BLOCK));	//copy tropo block data
	return 0; //GPP_SAPA_OK
}//gpp_sapa_hpac_add_tropo_block()
//--------------------------------------------------------------------------------------------------------------------------------------------------------
GPPLONG gpp_sapa_hpac_add_tropo_poly_coeff_block(pGPP_SAPA_HPAC hpac,GPPUINT1 sys, GPPUINT1 area, const pGPP_SAPA_HPAC_TROPO_POLY_COEFFICIENT_BLOCK pset)
{
	pGPP_SAPA_HPAC_ATMO_BLOCK atmo = NULL;		// Pointer to ATMO
	pGPP_SAPA_HPAC_TROPO tropo = NULL;			// Pointer to TROPO
	if (!hpac) return GPP_SAPA_ERR_INVALID_HPAC_AREA;

	if (!hpac->atmo) {//check if atmo structure is allocated
		hpac->atmo = (pGPP_SAPA_HPAC_ATMO_BLOCK**)calloc(GPP_SAPA_MAX_CONS, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK**));
		if (!hpac->atmo) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[sys]) {//check if atmo[sys] structure is allocated
		hpac->atmo[sys] = (pGPP_SAPA_HPAC_ATMO_BLOCK*)calloc(GPP_SAPA_MAX_AREA_COUNT, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK*));
		if (!hpac->atmo[sys]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[sys][area]) {//check if atmo[sys][area] structure is allocated
		hpac->atmo[sys][area] = (pGPP_SAPA_HPAC_ATMO_BLOCK)calloc(1, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK));
		if (!hpac->atmo[sys][area]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[sys][area]->tropo) {//check if tropo structure is allocated
		hpac->atmo[sys][area]->tropo = (pGPP_SAPA_HPAC_TROPO)calloc(1, sizeof(GPP_SAPA_HPAC_TROPO));
		if (!hpac->atmo[sys][area]->tropo) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[sys][area]->tropo->tropo_poly_coeff_block) {//check if tropo  poly coeff structure is allocated
		hpac->atmo[sys][area]->tropo->tropo_poly_coeff_block = (pGPP_SAPA_HPAC_TROPO_POLY_COEFFICIENT_BLOCK)calloc(1, sizeof(GPP_SAPA_HPAC_TROPO_POLY_COEFFICIENT_BLOCK));
		if (!hpac->atmo[sys][area]->tropo->tropo_poly_coeff_block) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}
	memcpy(hpac->atmo[sys][area]->tropo->tropo_poly_coeff_block, pset, sizeof(GPP_SAPA_HPAC_TROPO_POLY_COEFFICIENT_BLOCK));	//copy clock data
	return 0; //GPP_SAPA_OK
}//gpp_sapa_hpac_add_tropo_poly_coeff_block()
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
GPPLONG gpp_sapa_hpac_add_tropo_grid_block(pGPP_SAPA_HPAC hpac,GPPUINT1 sys, GPPUINT1 area, const pGPP_SAPA_HPAC_TROPO_GRID_BLOCK pset)
{
	GPPLONG rc;									//control variable
	pGPP_SAPA_HPAC_ATMO_BLOCK atmo = NULL;		// Pointer to ATMO
	pGPP_SAPA_HPAC_TROPO tropo = NULL;			// Pointer to TROPO
	if (!hpac) return GPP_SAPA_ERR_INVALID_HPAC_AREA;

	if (!hpac->atmo) {//check if atmo structure is allocated
		hpac->atmo = (pGPP_SAPA_HPAC_ATMO_BLOCK**)calloc(GPP_SAPA_MAX_CONS, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK**));
		if (!hpac->atmo) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[sys]) {//check if atmo[sys] structure is allocated
		hpac->atmo[sys] = (pGPP_SAPA_HPAC_ATMO_BLOCK*)calloc(GPP_SAPA_MAX_AREA_COUNT, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK*));
		if (!hpac->atmo[sys]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[sys][area]) {//check if atmo[sys][area] structure is allocated
		hpac->atmo[sys][area] = (pGPP_SAPA_HPAC_ATMO_BLOCK)calloc(1, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK));
		if (!hpac->atmo[sys][area]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[sys][area]->tropo) {//check if tropo structure is allocated
		hpac->atmo[sys][area]->tropo = (pGPP_SAPA_HPAC_TROPO)calloc(1, sizeof(GPP_SAPA_HPAC_TROPO));
		if (!hpac->atmo[sys][area]->tropo) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[sys][area]->tropo->tropo_grid) {//check if tropo grid structure is allocated
		hpac->atmo[sys][area]->tropo->tropo_grid = (pGPP_SAPA_HPAC_TROPO_GRID_BLOCK)calloc(1, sizeof(GPP_SAPA_HPAC_TROPO_GRID_BLOCK));
		if (!hpac->atmo[sys][area]->tropo->tropo_grid) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}
	memcpy(hpac->atmo[sys][area]->tropo->tropo_grid, pset, sizeof(GPP_SAPA_HPAC_TROPO_GRID_BLOCK));	//copy clock data
	return 0; //GPP_SAPA_OK
}//gpp_sapa_hpac_add_tropo_grid_block()
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
GPPLONG gpp_sapa_hpac_add_iono(pGPP_SAPA_HPAC hpac,GPPUINT1 sys, GPPUINT1 area, const pGPP_SAPA_HPAC_IONO pset)
{
	GPPLONG rc;									//control variable
	pGPP_SAPA_HPAC_ATMO_BLOCK atmo = NULL;		// Pointer to ATMO

	if (!hpac) return GPP_SAPA_ERR_INVALID_HPAC_AREA;

	if (!hpac->atmo) {//check if atmo structure is allocated
		hpac->atmo = (pGPP_SAPA_HPAC_ATMO_BLOCK**)calloc(GPP_SAPA_MAX_CONS, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK**));
		if (!hpac->atmo) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[sys]) {//check if atmo[sys] structure is allocated
		hpac->atmo[sys] = (pGPP_SAPA_HPAC_ATMO_BLOCK*)calloc(GPP_SAPA_MAX_AREA_COUNT, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK*));
		if (!hpac->atmo[sys]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[sys][area]) {//check if atmo[sys][area] structure is allocated
		hpac->atmo[sys][area] = (pGPP_SAPA_HPAC_ATMO_BLOCK)calloc(1, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK));
		if (!hpac->atmo[sys][area]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[sys][area]->iono) {//check if iono structure is allocated
		hpac->atmo[sys][area]->iono = (pGPP_SAPA_HPAC_IONO)calloc(1, sizeof(GPP_SAPA_HPAC_IONO));
		if (!hpac->atmo[sys][area]->iono) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}
	memcpy(hpac->atmo[sys][area]->iono, pset, sizeof(GPP_SAPA_HPAC_IONO));	//copy clock data
	return 0; //GPP_SAPA_OK
}//gpp_sapa_hpac_add_iono()

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
GPPLONG gpp_sapa_hpac_add_iono_sat_poly_block(pGPP_SAPA_HPAC hpac, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 area, const pGPP_SAPA_HPAC_IONO_SAT_POLY pset)
{
	GPPLONG rc;															//control variable
	pGPP_SAPA_HPAC_ATMO_BLOCK atmo = NULL;		// Pointer to ATMO
	pGPP_SAPA_HPAC_IONO iono = NULL;			// Pointer to OCB_SV_BIAS
	pGPP_SAPA_HPAC_IONO_SAT_BLOCK iono_sat_block = NULL;
	if (!hpac) return GPP_SAPA_ERR_INVALID_HPAC_AREA;

	if (!hpac->atmo) {//check if atmo structure is allocated
		hpac->atmo = (pGPP_SAPA_HPAC_ATMO_BLOCK**)calloc(GPP_SAPA_MAX_CONS, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK**));
		if (!hpac->atmo) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[sys]) {//check if atmo[sys] structure is allocated
		hpac->atmo[sys] = (pGPP_SAPA_HPAC_ATMO_BLOCK*)calloc(GPP_SAPA_MAX_AREA_COUNT, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK*));
		if (!hpac->atmo[sys]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[sys][area]) {//check if atmo[sys][area] structure is allocated
		hpac->atmo[sys][area] = (pGPP_SAPA_HPAC_ATMO_BLOCK)calloc(1, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK));
		if (!hpac->atmo[sys][area]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[sys][area]->iono) {////check if iono structure is allocated
		hpac->atmo[sys][area]->iono = (pGPP_SAPA_HPAC_IONO)calloc(1, sizeof(GPP_SAPA_HPAC_IONO));
		if (!hpac->atmo[sys][area]->iono) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[sys][area]->iono->iono_sat_block) {////check if iono Satellite structure is allocated
		hpac->atmo[sys][area]->iono->iono_sat_block = (pGPP_SAPA_HPAC_IONO_SAT_BLOCK*)calloc(GPP_SAPA_MAX_SAT, sizeof(GPP_SAPA_HPAC_IONO_SAT_BLOCK*));
		if (!hpac->atmo[sys][area]->iono->iono_sat_block) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}
	if (!(hpac->atmo[sys][area]->iono->iono_sat_block[sat])) { // check if iono satelite [sys][sat] is allocated
		hpac->atmo[sys][area]->iono->iono_sat_block[sat] = (pGPP_SAPA_HPAC_IONO_SAT_BLOCK)calloc(1, sizeof(GPP_SAPA_HPAC_IONO_SAT_BLOCK));
		if (!(hpac->atmo[sys][area]->iono->iono_sat_block[sat])) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}
	if (!hpac->atmo[sys][area]->iono->iono_sat_block[sat]->iono_sat_poly) {//check if iono satellite poly structure is allocated
		hpac->atmo[sys][area]->iono->iono_sat_block[sat]->iono_sat_poly = (pGPP_SAPA_HPAC_IONO_SAT_POLY)calloc(1, sizeof(GPP_SAPA_HPAC_IONO_SAT_POLY));
		if (!hpac->atmo[sys][area]->iono->iono_sat_block[sat]->iono_sat_poly) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}
	memcpy(hpac->atmo[sys][area]->iono->iono_sat_block[sat]->iono_sat_poly, pset, sizeof(GPP_SAPA_HPAC_IONO_SAT_POLY));
	GPPUINT8 bit = 1;
	hpac->atmo[sys][area]->iono->sat_prn_bits |= (bit << sat);       //set sat ID in sv_prn_bits bit mask
	return 0;
}//gpp_sapa_hpac_add_iono_sat_poly_block()
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
GPPLONG gpp_sapa_hpac_add_iono_sat_coeff_block(pGPP_SAPA_HPAC hpac, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 area, const pGPP_SAPA_HPAC_IONO_SAT_COEFFICIENT pset)
{
	GPPLONG rc;															//control variable
	pGPP_SAPA_HPAC_ATMO_BLOCK atmo = NULL;		// Pointer to ATMO
	pGPP_SAPA_HPAC_IONO iono = NULL;			// Pointer to OCB_SV_BIAS
	pGPP_SAPA_HPAC_IONO_SAT_BLOCK iono_sat_block = NULL;
	if (!hpac) return GPP_SAPA_ERR_INVALID_HPAC_AREA;

	if (!hpac->atmo) {//check if atmo structure is allocated
		hpac->atmo = (pGPP_SAPA_HPAC_ATMO_BLOCK**)calloc(GPP_SAPA_MAX_CONS, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK**));
		if (!hpac->atmo) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[sys]) {//check if atmo[sys] structure is allocated
		hpac->atmo[sys] = (pGPP_SAPA_HPAC_ATMO_BLOCK*)calloc(GPP_SAPA_MAX_AREA_COUNT, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK*));
		if (!hpac->atmo[sys]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[sys][area]) {//check if atmo[sys][area] structure is allocated
		hpac->atmo[sys][area] = (pGPP_SAPA_HPAC_ATMO_BLOCK)calloc(1, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK));
		if (!hpac->atmo[sys][area]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[sys][area]->iono) {////check if iono structure is allocated
		hpac->atmo[sys][area]->iono = (pGPP_SAPA_HPAC_IONO)calloc(1, sizeof(GPP_SAPA_HPAC_IONO));
		if (!hpac->atmo[sys][area]->iono) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[sys][area]->iono->iono_sat_block) {////check if iono Satellite structure is allocated
		hpac->atmo[sys][area]->iono->iono_sat_block = (pGPP_SAPA_HPAC_IONO_SAT_BLOCK*)calloc(GPP_SAPA_MAX_SAT, sizeof(GPP_SAPA_HPAC_IONO_SAT_BLOCK*));
		if (!hpac->atmo[sys][area]->iono->iono_sat_block) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}
	if (!(hpac->atmo[sys][area]->iono->iono_sat_block[sat])) { // check if iono satelite [sys][sat] is allocated
		hpac->atmo[sys][area]->iono->iono_sat_block[sat] = (pGPP_SAPA_HPAC_IONO_SAT_BLOCK)calloc(1, sizeof(GPP_SAPA_HPAC_IONO_SAT_BLOCK));
		if (!(hpac->atmo[sys][area]->iono->iono_sat_block[sat])) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}
	if (!hpac->atmo[sys][area]->iono->iono_sat_block[sat]->iono_sat_coeff) {//check if iono satellite structure is allocated
		hpac->atmo[sys][area]->iono->iono_sat_block[sat]->iono_sat_coeff = (pGPP_SAPA_HPAC_IONO_SAT_COEFFICIENT)calloc(1, sizeof(GPP_SAPA_HPAC_IONO_SAT_COEFFICIENT));
		if (!hpac->atmo[sys][area]->iono->iono_sat_block[sat]->iono_sat_coeff) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}
	memcpy(hpac->atmo[sys][area]->iono->iono_sat_block[sat]->iono_sat_coeff, pset, sizeof(GPP_SAPA_HPAC_IONO_SAT_COEFFICIENT));
	GPPUINT8 bit = 1;
	hpac->atmo[sys][area]->iono->sat_prn_bits |= (bit << sat);       //set sat ID in sv_prn_bits bit mask
	return 0;
}//gpp_sapa_hpac_add_iono_sat_coeff_block()
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
GPPLONG gpp_sapa_hpac_add_iono_sat_grid_block(pGPP_SAPA_HPAC hpac, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 area, const pGPP_SAPA_HPAC_IONO_GRID_BLOCK pset)
{
	pGPP_SAPA_HPAC_ATMO_BLOCK atmo = NULL;		// Pointer to ATMO
	pGPP_SAPA_HPAC_IONO iono = NULL;			// Pointer to OCB_SV_BIAS
	pGPP_SAPA_HPAC_IONO_SAT_BLOCK iono_sat_block = NULL;
	if (!hpac) return GPP_SAPA_ERR_INVALID_HPAC_AREA;

	if (!hpac->atmo) {//check if atmo structure is allocated
		hpac->atmo = (pGPP_SAPA_HPAC_ATMO_BLOCK**)calloc(GPP_SAPA_MAX_CONS, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK**));
		if (!hpac->atmo) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[sys]) {//check if atmo[sys] structure is allocated
		hpac->atmo[sys] = (pGPP_SAPA_HPAC_ATMO_BLOCK*)calloc(GPP_SAPA_MAX_AREA_COUNT, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK*));
		if (!hpac->atmo[sys]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[sys][area]) {//check if atmo[sys][area] structure is allocated
		hpac->atmo[sys][area] = (pGPP_SAPA_HPAC_ATMO_BLOCK)calloc(1, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK));
		if (!hpac->atmo[sys][area]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[sys][area]->iono) {////check if iono structure is allocated
		hpac->atmo[sys][area]->iono = (pGPP_SAPA_HPAC_IONO)calloc(1, sizeof(GPP_SAPA_HPAC_IONO));
		if (!hpac->atmo[sys][area]->iono) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}

	if (!hpac->atmo[sys][area]->iono->iono_sat_block) {////check if iono Satellite structure is allocated
		hpac->atmo[sys][area]->iono->iono_sat_block = (pGPP_SAPA_HPAC_IONO_SAT_BLOCK*)calloc(GPP_SAPA_MAX_SAT, sizeof(GPP_SAPA_HPAC_IONO_SAT_BLOCK*));
		if (!hpac->atmo[sys][area]->iono->iono_sat_block) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}
	if (!(hpac->atmo[sys][area]->iono->iono_sat_block[sat])) { // check if iono satelite [sys][sat] is allocated
		hpac->atmo[sys][area]->iono->iono_sat_block[sat] = (pGPP_SAPA_HPAC_IONO_SAT_BLOCK)calloc(1, sizeof(GPP_SAPA_HPAC_IONO_SAT_BLOCK));
		if (!(hpac->atmo[sys][area]->iono->iono_sat_block[sat])) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}
	if (!hpac->atmo[sys][area]->iono->iono_sat_block[sat]->iono_grid) {//check if iono grid structure is allocated
		hpac->atmo[sys][area]->iono->iono_sat_block[sat]->iono_grid = (pGPP_SAPA_HPAC_IONO_GRID_BLOCK)calloc(1, sizeof(GPP_SAPA_HPAC_IONO_GRID_BLOCK));
		if (!hpac->atmo[sys][area]->iono->iono_sat_block[sat]->iono_grid) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
	}
	memcpy(hpac->atmo[sys][area]->iono->iono_sat_block[sat]->iono_grid, pset, sizeof(GPP_SAPA_HPAC_IONO_GRID_BLOCK));
	GPPUINT8 bit = 1;
	hpac->atmo[sys][area]->iono->sat_prn_bits |= (bit << sat);       //set sat ID in sv_prn_bits bit mask
	return 0;
}//gpp_sapa_hpac_add_iono_sat_grid_block()
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
	GPPLONG rc;												//control variable
	pGPP_SAPA_AREA_DEF_BLOCK area_def_block = NULL;			// Pointer to AREA_DEF_BLOCK

	if (!p_area) return GPP_SAPA_ERR_INVALID_AREA;
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

GPPLONG gpp_sapa_get_bit_diff(GPPLONG byte_pos, GPPLONG bit_pos, GPPLONG byte_pos0, GPPLONG bit_pos0)
{
	return (byte_pos - byte_pos0) * 8 + (bit_pos - bit_pos0);
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
	GPPUINT1 max_cons_id = 0;
	for (GPPUINT1 cons_id = 0; cons_id < 12; cons_id++)
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














#if 0


//--------------------------------------------------------------------Transport Layer SAPA OCB message----------------------------------------------------------------------------
GPPLONG gpp_sapa_ocb_buffer_to_sapa_buffer(const GPPUCHAR *ocb_buffer,GPPLONG len_sapa_bits, GPPLONG ea_flag, GPPLONG message_crc_type,GPPLONG crc_frame, GPPUCHAR *sapa_buffer)
{
	GPPLONG byte_pos =0, bit_pos = 0, num_data_bytes = 0;
	gn_add_ulong_to_buffer(sapa_buffer, &byte_pos, &bit_pos, 8, 115);
	gn_add_ulong_to_buffer(sapa_buffer, &byte_pos, &bit_pos, 7, SAPA_TYPE_OCB);
	printf("\n bits=%d", len_sapa_bits);
	num_data_bytes = length_bytes_from_bits(len_sapa_bits);
	if (!num_data_bytes) return GPP_SAPA_ERR_PAYLOAD_LENGTH;
	printf("value of num=%ld", num_data_bytes);
	gn_add_ulong_to_buffer(sapa_buffer, &byte_pos, &bit_pos, 10, num_data_bytes);
	printf("ea flag=%d", ea_flag);
	gn_add_ulong_to_buffer(sapa_buffer, &byte_pos, &bit_pos, 1, ea_flag);

	printf("message crc type=%d", message_crc_type);
	gn_add_ulong_to_buffer(sapa_buffer, &byte_pos, &bit_pos, 2, message_crc_type);
	gn_add_ulong_to_buffer(sapa_buffer, &byte_pos, &bit_pos, 4, crc_frame);
	printf("\nsapa nuffer=%d", sapa_buffer);
	printf("byte pos=%d", byte_pos);
	printf("\ncrc=%d", message_crc_type);
	printf("\n num_data_bytes ======================================================================================%d", num_data_bytes);
	memcpy((sapa_buffer+byte_pos), ocb_buffer, num_data_bytes);

	printf("value of  ocb buffer=%d", ocb_buffer);
	printf("\ncrc=%d",message_crc_type);
	byte_pos += num_data_bytes;
	printf("\nByte %d", byte_pos);
	int i;
	for (i = 0; i <= byte_pos; i++)
	{
		printf("\nByte %d, Integral Value : %d, Binary Value: ", i, *(sapa_buffer + i));
		int x = 0;
		for (x = 0; x < 8; x++)    //prnbit testing
		{
			printf("%d", TestBit(*(sapa_buffer + i), x), x);
		}
	}
	printf("\ncrc========================================%ld", sapa_const_crc_bytes[message_crc_type]);
	gn_add_ulong_to_buffer(sapa_buffer, &byte_pos, &bit_pos, sapa_const_crc_bytes[message_crc_type] ,0);
	return 0;
}
GPPLONG gpp_sapa_sapa_buffer_to_ocb_buffer(GPPUCHAR *ocb_buffer, GPPLONG *len_sapa_bits, GPPLONG *ea_flag, GPPLONG *message_crc_type, GPPLONG *crc_frame, const GPPUCHAR *sapa_buffer)
{
	GPPLONG byte_pos = 0, bit_pos = 0, numDataBytes = 0, crc;

	int type;
	long sapa_preamble= gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, 8);
	if (sapa_preamble != SAPA_PREAMBLE) return GPP_SAPA_ERR_PREAMBLE;

	type = gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, 7);
	printf("type=%d",type);
	if (type != SAPA_TYPE_OCB) return GPP_SAPA_ERR_TYPE;

	numDataBytes = gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, 10);
	printf("num=%d", numDataBytes);
	if (!numDataBytes) return GPP_SAPA_ERR_PAYLOAD_LENGTH;
	*len_sapa_bits = numDataBytes * 8;
	*ea_flag = gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, 1);

	*message_crc_type = gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, 2);
	if (*message_crc_type > 3) return GPP_SAPA_ERR_CRC_TYPE;

	*crc_frame = gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, 4);
	printf("num data byte=%d", numDataBytes);
	memcpy(ocb_buffer, (sapa_buffer+byte_pos), numDataBytes);
	byte_pos += numDataBytes;

	crc = gn_get_ulong_from_buffer(sapa_buffer, &byte_pos, &bit_pos, sapa_const_crc_bytes[*message_crc_type]);
	printf("\nvalue of crc=%d", crc);

	int i;
	for (i = 0; i <= numDataBytes; i++)
	{
		printf("\nByte %d, Integral Value : %d, Binary Valuefin: ", i, *(ocb_buffer + i));
		int x = 0;
		for (x = 0; x < 8; x++)    //prnbit testing
		{
			printf("%d", TestBit(*(ocb_buffer + i), x), x);
		}
	}
	return 0;
}
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
GPPLONG length_bytes_from_bits(GPPLONG b)
{
	return (((b) / 8) + ((b) % 8 ? 1 : 0));
}
#endif
