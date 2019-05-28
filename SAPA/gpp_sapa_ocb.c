/*
 Write and read SAPA OCB format to and from buffer
*/
#include <stdio.h>
//#include "platform.h"

#include "gpp_sapa.h"
#include "bit2buff.h"

//================================== Declaration of functions to store data in Buffer for OCB ====================================================================================
static GPPLONG gpp_sapa_ocb_header2buffer(const pGPP_SAPA_OCB p_ocb, GPPUINT1 sys, GPPUINT1 *svlist, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_ocb_sv2buffer(const pGPP_SAPA_OCB p_ocb, GPPUINT1 sys, GPPUINT1 sat, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_ocb_orb2buffer(const pGPP_SAPA_OCB p_ocb, GPPUINT1 sys, GPPUINT1 sat, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_ocb_clk2buffer(const pGPP_SAPA_OCB p_ocb, GPPUINT1 sys, GPPUINT1 sat, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_ocb_bias2buffer(const pGPP_SAPA_OCB p_ocb, GPPUINT1 sys, GPPUINT1 sat, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_ocb_pb2buffer(const pGPP_SAPA_OCB p_ocb, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 sig, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_ocb_cb2buffer(const pGPP_SAPA_OCB p_ocb, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 sig, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);

//--------------------------------------Decelaration of function to read data from buffer for OCB---------------------------------------------------------------------------------------------------------------------------//
static GPPLONG gpp_sapa_ocb_buffer2header(pGPP_SAPA_OCB p_ocb, GPPUINT1 *sys, GPPUINT1 *svlist, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_ocb_buffer2sv(pGPP_SAPA_OCB p_ocb, GPPUINT1 sys, GPPUINT1 sat, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_ocb_buffer2orb(pGPP_SAPA_OCB p_ocb, GPPUINT1 sys, GPPUINT1 sat, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_ocb_buffer2clk(pGPP_SAPA_OCB p_ocb, GPPUINT1 sys, GPPUINT1 sat, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_ocb_buffer2bias(pGPP_SAPA_OCB p_ocb, GPPUINT1 sys, GPPUINT1 sat, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_ocb_buffer2pb(pGPP_SAPA_OCB p_ocb, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 sig, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_ocb_buffer2cb(pGPP_SAPA_OCB p_ocb, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 sig, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
/**************************************************************************
 *	\brief Write SAPA OCB message to buffer
 *
 *	\param[in] 	p_OCB 	Pointer to GPP_SAPA_OCB structure
 *	\param[in]	sys		GNSS indicator
 *	\param[in]	*buffer
 *	\param[in]	*byte_pos
 *	\param[in]	*bit_pos
 *
 *	\retval 	Number of needed bits
 *	\retval 	Error Code
 *************************************************************************/
GPPLONG gpp_sapa_ocb2buffer(const pGPP_SAPA_OCB p_ocb, GPPUINT1 sys, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPLONG rc;
	GPPUINT1 isat, sat = 0;
	GPPUINT1 svlist[66] = { 0, };
	GPPLONG byte_pos0, bit_pos0;
	GPPLONG mybyte = 0, mybit = 0;

	// handling if byte_pos or bit_pos are null pointers
	if (!byte_pos) 	byte_pos = &mybyte;
	if (!bit_pos) 	bit_pos = &mybit;

	// get start position of byte_pos and bit_pos to get needed bits
	byte_pos0 = *byte_pos;
	bit_pos0 = *bit_pos;

	if (rc = gpp_sapa_ocb_header2buffer(p_ocb, sys, svlist, buffer, byte_pos, bit_pos)) return rc;//sys is an argument here

	// get all valid satellites of this sys
	for (isat = 1; isat <= svlist[0]; isat++) {
		sat = svlist[isat];
		if (rc = gpp_sapa_ocb_sv2buffer(p_ocb, sys, sat, buffer, byte_pos, bit_pos)) return rc;
	}
	return  gpp_sapa_get_bit_diff(*byte_pos, *bit_pos, byte_pos0, bit_pos0);
}//gpp_sapa_ocb2buffer()
/**************************************************************************
 *	\brief Read SAPA OCB message from buffer
 *
 *	\param[in] 	p_OCB 	Pointer to GPP_SAPA_OCB structure
 *	\param[in]	sys		GNSS indicator
 *	\param[in]	*buffer
 *	\param[in]	*byte_pos
 *	\param[in]	*bit_pos
 *
 *	\retval 	Number of read bits
 *	\retval 	Error Code
 *************************************************************************/
GPPLONG gpp_sapa_buffer2ocb(pGPP_SAPA_OCB p_ocb, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPLONG rc;
	GPPLONG byte_pos0, bit_pos0;
	GPPLONG mybyte = 0, mybit = 0;

	GPPUINT1 sys, sat, isat;
	GPPUINT1 svlist[66];

	// handling if byte_pos or bit_pos are null pointers
	if (!byte_pos) 	byte_pos = &mybyte;
	if (!bit_pos) 	bit_pos = &mybit;

	// get start position of byte_pos and bit_pos to get needed bits
	byte_pos0 = *byte_pos;
	bit_pos0 = *bit_pos;

	if (rc = gpp_sapa_ocb_buffer2header(p_ocb, &sys, svlist, buffer, byte_pos, bit_pos)) return rc;//sys is an argument here

	// get all valid satellites of this sys
	for (isat = 1; isat <= svlist[0]; isat++) {
		sat = svlist[isat];
		if (rc = gpp_sapa_ocb_buffer2sv(p_ocb, sys, sat, buffer, byte_pos, bit_pos)) return rc;
	}
	return  gpp_sapa_get_bit_diff(*byte_pos, *bit_pos, byte_pos0, bit_pos0);
}//gpp_sapa_buffer2ocb()

/******************************************************************************
 *	\brief Write OCB header to buffer
 *
 *	\param[in]	p_ocb
 *	\param[in]	sys
 *	\param[in]	*buffer
 *	\param[in]	*byte_pos
 *	\param[in]	*bit_pos
 *
 *	\retval 0 Ok
 *	\retval Error Code
 ******************************************************************************/
static GPPLONG gpp_sapa_ocb_header2buffer(const pGPP_SAPA_OCB p_ocb, GPPUINT1 sys, GPPUINT1 *svlist, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPLONG rc;

	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 4, p_ocb->header_block[sys]->message_sub_type);										//SF001
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 1, p_ocb->header_block[sys]->time_tag_type);											//SF002

	if (p_ocb->header_block[sys]->time_tag_type == GNSS_FULL_TIME_TAG)
	{
		gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 32, p_ocb->header_block[sys]->time_tag);											//SF004
	}
	else if (p_ocb->header_block[sys]->time_tag_type == GNSS_HOURLY_TIME_TAG)
	{
		gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 12, p_ocb->header_block[sys]->time_tag);											//SF003
	}

	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 7, p_ocb->header_block[sys]->sys_id);													//SF006
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 4, p_ocb->header_block[sys]->sys_processor_id);										//SF007
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 9, p_ocb->header_block[sys]->sol_issue_of_update);									//SF005
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 1, p_ocb->header_block[sys]->end_of_obc_set);											//SF010
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 1, p_ocb->header_block[sys]->yaw_flag);												//SF008
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 1, p_ocb->header_block[sys]->sat_ref_datum);											//SF009
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 2, p_ocb->header_block[sys]->ephemeris_type);											//SF017

	if (rc = gpp_sapa_sv_bitmask2buffer(p_ocb->sv_prn_bits[sys], sys, svlist, buffer, byte_pos, bit_pos)) return rc;
	
	return 0;
}//gpp_sapa_ocb_header2buffer()


/******************************************************************************
 *	\brief Read OCB header from buffer
 *
 *	\param[in]	p_ocb
 *	\param[in]	sys
 *	\param[in]	*buffer
 *	\param[in]	*byte_pos
 *	\param[in]	*bit_pos
 *
 *	\retval 0 Ok
 *	\retval Error Code
 ******************************************************************************/
static GPPLONG gpp_sapa_ocb_buffer2header(pGPP_SAPA_OCB p_ocb, GPPUINT1 *sys, GPPUINT1 *svlist, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPLONG rc;
	GPP_SAPA_OCB_HEADER header = { 0, };

	header.message_sub_type = gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 4);									//SF001
	*sys = header.message_sub_type;

	header.time_tag_type = gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 1);									//SF002

	if (header.time_tag_type == GNSS_FULL_TIME_TAG)
	{
		header.time_tag = gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 32);									//SF004
	}
	else if (header.time_tag_type == GNSS_HOURLY_TIME_TAG)
	{
		header.time_tag = gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 12);									//SF003
	}

	header.sys_id = gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 7);											//SF006
	header.sys_processor_id = gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 4);									//SF007
	header.sol_issue_of_update = gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 9);								//SF005
	header.end_of_obc_set = gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 1);									//SF010
	header.yaw_flag = gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 1);											//SF008
	header.sat_ref_datum = gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 1);									//SF009
	header.ephemeris_type = gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 2);									//SF017

	if (rc = gpp_sapa_ocb_add_header(p_ocb, header.message_sub_type, &header)) return rc;

	if (rc = gpp_sapa_buffer2sv_bitmask(&p_ocb->sv_prn_bits[*sys], *sys, svlist, buffer, byte_pos, bit_pos)) return rc;

	return 0;
}//gpp_sapa_ocb_buffer2header()


/******************************************************************************
 *	\brief Write SV bitmask to buffer and compute svlist
 *****************************************************************************/
static GPPLONG gpp_sapa_sv_bitmask2buffer(GPPUINT8 sv_prn_bits, GPPUINT1 sys, GPPUINT1 *svlist, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPUINT1 bit_id = 0;

	if (!svlist) return GPP_SAPA_ERR_INVALID_SVLIST;
	
	gpp_sapa_get_svlist(sv_prn_bits, svlist);
	bit_id = 0;
	while (svlist[0] - SAPA_SV_BITMASK_LEN[sys][bit_id] > 0 && bit_id <= 3) bit_id++;							//Check (> || <)


	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 2, bit_id);																	//SF011
	gn_add_longlong_to_buffer(buffer, byte_pos, bit_pos, SAPA_SV_BITMASK_LEN[sys][bit_id], sv_prn_bits);

	return 0;
}//gpp_sapa_sv_bitmask2buffer()


/******************************************************************************
 *	\brief Read SV bitmask from buffer and compute svlist
 *****************************************************************************/
static GPPLONG gpp_sapa_buffer2sv_bitmask(GPPUINT8 *sv_prn_bits, GPPUINT1 sys, GPPUINT1 *svlist, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPUINT1 bit_id;

	bit_id = gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 2);
	*sv_prn_bits = gn_get_ulonglong_from_buffer(buffer, byte_pos, bit_pos, SAPA_SV_BITMASK_LEN[sys][bit_id]);
	
	gpp_sapa_get_svlist(*sv_prn_bits, svlist);
	

	return 0;
}//gpp_sapa_buffer2sv_bitmask()


/******************************************************************************
 *	\brief Store sv block data into buffer
 ******************************************************************************/
static GPPLONG gpp_sapa_ocb_sv2buffer(const pGPP_SAPA_OCB p_ocb, GPPUINT1 sys, GPPUINT1 sat, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPLONG rc;
	pGPP_SAPA_OCB_SV sv = NULL;
	GPPUINT1 bit_id = 1;

	if (!(sv=p_ocb->sv[sys][sat])) return GPP_SAPA_ERR_INVALID_OCB_SV;

	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 1, sv->do_not_use);

	//CP: sv->do_not_use is related to all fields of the satellite block
	if(sv->do_not_use) return 0;

	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 3, sv->ocb_present_flag);															//SF014

	while (p_ocb->sv[sys][sat]->continuity_indicator >= SAPA_CONTI_ID[bit_id] && bit_id <= 7) bit_id++;
	bit_id -= 1;																														 //SF015
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 3, bit_id);

	if(sv->ocb_present_flag&(1 << GPP_SAPA_OCB_FLAG_IDX_ORB)) {
		if (rc = gpp_sapa_ocb_orb2buffer(p_ocb, sys, sat, buffer, byte_pos, bit_pos)) return rc;
	}

	if(sv->ocb_present_flag&(1 << GPP_SAPA_OCB_FLAG_IDX_CLK)) {
		if (rc = gpp_sapa_ocb_clk2buffer(p_ocb, sys, sat, buffer, byte_pos, bit_pos)) return rc;
	}

	if(sv->ocb_present_flag&(1 << GPP_SAPA_OCB_FLAG_IDX_BIAS)) {
		if (rc = gpp_sapa_ocb_bias2buffer(p_ocb, sys, sat, buffer, byte_pos, bit_pos)) return rc;
	}
	return 0;
}//gpp_sapa_ocb_sv2buffer


/******************************************************************************
 *	\brief Read sv block data from buffer
 ******************************************************************************/
static GPPLONG gpp_sapa_ocb_buffer2sv(pGPP_SAPA_OCB p_ocb, GPPUINT1 sys, GPPUINT1 sat, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPLONG  rc;
	GPP_SAPA_OCB_SV sv = { 0, };
	GPPULONG cont_indi;

	sv.do_not_use=gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 1);

	if(sv.do_not_use) return 0;

	sv.ocb_present_flag=gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 3);								//SF014
	sv.continuity_indicator = SAPA_CONTI_ID[gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 3)];	   //SF015

	if(rc=gpp_sapa_ocb_add_sv(p_ocb, sys, sat, &sv)) return rc;//CP: add SV parameters here

	if (sv.ocb_present_flag&(1 << GPP_SAPA_OCB_FLAG_IDX_ORB))
	{
		if(rc=gpp_sapa_ocb_buffer2orb(p_ocb, sys, sat, buffer, byte_pos, bit_pos)) return rc;
	}

	if (sv.ocb_present_flag&(1 << GPP_SAPA_OCB_FLAG_IDX_CLK))
	{
		if(rc=gpp_sapa_ocb_buffer2clk(p_ocb, sys, sat, buffer, byte_pos, bit_pos)) return rc;
	}

	if (sv.ocb_present_flag&(1 << GPP_SAPA_OCB_FLAG_IDX_BIAS))
	{
		if(rc=gpp_sapa_ocb_buffer2bias(p_ocb, sys, sat, buffer, byte_pos, bit_pos)) return rc;
	}
	return 0;
}//gpp_sapa_ocb_buffer2sv()

/******************************************************************************
 *	\brief Store Orbit Data Into Buffer
 ******************************************************************************/
static GPPLONG gpp_sapa_ocb_orb2buffer(const pGPP_SAPA_OCB p_ocb, GPPUINT1 sys, GPPUINT1 sat, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	pGPP_SAPA_OCB_SV_ORB orb = NULL; //CP 2019/05/09 use pointer(s) for better reading and to avoid copy/paste mistakes

	if (!(orb = p_ocb->sv[sys][sat]->orb)) return GPP_SAPA_ERR_INVALID_OCB_SV_ORB;

	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, SAPA_SV_IODE_LEN[sys], p_ocb->sv[sys][sat]->orb->iode);								//SF018
	gn_add_val_double_to_buffer(buffer, byte_pos, bit_pos, 14, p_ocb->sv[sys][sat]->orb->orb_radial_correction, SAPA_RES_SV_CORRECTION);
	gn_add_val_double_to_buffer(buffer, byte_pos, bit_pos, 14, p_ocb->sv[sys][sat]->orb->orb_along_track_correction, SAPA_RES_SV_CORRECTION);
	gn_add_val_double_to_buffer(buffer, byte_pos, bit_pos, 14, p_ocb->sv[sys][sat]->orb->orb_cross_track_correction, SAPA_RES_SV_CORRECTION);

	if (p_ocb->header_block[sys]->yaw_flag == GPP_SAPA_YAW_FLAG_PRESENT)
	{
		gn_add_val_double_to_buffer(buffer, byte_pos, bit_pos, 6, p_ocb->sv[sys][sat]->orb->sat_yaw, 6);//SF021
	}
	return 0;
}//gpp_sapa_ocb_orb2buffer()


/******************************************************************************
 *	\brief Read Orbit Data from Buffer
 ******************************************************************************/
static GPPLONG gpp_sapa_ocb_buffer2orb(pGPP_SAPA_OCB p_ocb, GPPUINT1 sys, GPPUINT1 sat, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPLONG rc;
	GPP_SAPA_OCB_SV_ORB orb = { 0, };

	orb.iode = gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, SAPA_SV_IODE_LEN[sys]);										//SF018
	orb.orb_radial_correction = gn_get_val_double_from_buffer(buffer, byte_pos, bit_pos, 14, SAPA_RES_SV_CORRECTION);				//SF020
	orb.orb_along_track_correction = gn_get_val_double_from_buffer(buffer, byte_pos, bit_pos, 14, SAPA_RES_SV_CORRECTION);		//SF020
	orb.orb_cross_track_correction = gn_get_val_double_from_buffer(buffer, byte_pos, bit_pos, 14, SAPA_RES_SV_CORRECTION);		//SF020

	if (p_ocb->header_block[sys]->yaw_flag == GPP_SAPA_YAW_FLAG_PRESENT)
		orb.sat_yaw = gn_get_val_double_from_buffer(buffer, byte_pos, bit_pos, 6, 6);//SF021

	if (rc = gpp_sapa_ocb_add_orb(p_ocb, sys, sat, &orb)) return rc;//CP 2019/05/09 add read orb structure here

	return 0;
}//gpp_sapa_ocb_buffer2orb()


/******************************************************************************
 *	\brief Write SAPA OCB clk to buffer
 ******************************************************************************/
static GPPLONG gpp_sapa_ocb_clk2buffer(const pGPP_SAPA_OCB p_ocb, GPPUINT1 sys, GPPUINT1 sat, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPUINT1 iode_cont;
	GPPUINT1 user_range_err;
	pGPP_SAPA_OCB_SV_CLK clk = NULL; //CP 2019/05/09 use pointer(s) for better reading and to avoid copy/paste mistakes

	if (!(clk = p_ocb->sv[sys][sat]->clk)) return GPP_SAPA_ERR_INVALID_OCB_SV_CLK;

	GPPUINT1 bit_id = 1,bit=1;
	while (p_ocb->sv[sys][sat]->clk->iode_continuity >= SAPA_CONTI_ID[bit_id] && bit_id <= 7) bit_id++;
	bit_id -= 1;
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 3, bit_id);								//SF022
	gn_add_val_double_to_buffer(buffer, byte_pos, bit_pos, 14, clk->clk_correction, SAPA_RES_SV_CORRECTION);							//SF020
	while (p_ocb->sv[sys][sat]->clk->user_range_error >= SAPA_USER_RANGE_ERROR[bit] && bit <= 7) bit++;
	bit -= 1;																													//SF024
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 3, bit);
	return 0;
}//gpp_sapa_ocb_clk2buffer()


/******************************************************************************
 *	\brief Read SAPA OCB clk from buffer
 ******************************************************************************/
static GPPLONG gpp_sapa_ocb_buffer2clk(pGPP_SAPA_OCB p_ocb, GPPUINT1 sys, GPPUINT1 sat, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPLONG rc;
	GPP_SAPA_OCB_SV_CLK clk = { 0, };
	clk.iode_continuity = SAPA_CONTI_ID[gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 3)];	  //SF022
	clk.clk_correction = gn_get_val_double_from_buffer(buffer, byte_pos, bit_pos, 14, SAPA_RES_SV_CORRECTION);							//SF020
	clk.user_range_error = SAPA_USER_RANGE_ERROR[gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 3)];							//SF024

	if (rc = gpp_sapa_ocb_add_clk(p_ocb, sys, sat, &clk)) return rc;//CP 2019/05/09 add read clk structure here

	return 0;
}//gpp_sapa_ocb_buffer2clk()

/******************************************************************************
 *	\brief Write SAPA OCB bias to buffer
 ******************************************************************************/
static GPPLONG gpp_sapa_ocb_bias2buffer(const pGPP_SAPA_OCB p_ocb, GPPUINT1 sys, GPPUINT1 sat, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPUINT1 sig = 0;
	GPPUINT1 isig = 0;
	GPPUINT1 siglist[34] = { 0, };

	//Phase Bias
	gpp_sapa_bias_bitmask2buffer(p_ocb->sv[sys][sat]->bias->pb_sig_bits, sys, siglist, buffer, byte_pos, bit_pos);
	for (isig = 1; isig <= siglist[0]; isig++)
	{
		sig = siglist[isig];
		gpp_sapa_ocb_pb2buffer(p_ocb, sys, sat, sig, buffer, byte_pos, bit_pos);
	}

	//Code Bias
	gpp_sapa_bias_bitmask2buffer(p_ocb->sv[sys][sat]->bias->cb_sig_bits, sys, siglist, buffer, byte_pos, bit_pos);
	for (isig = 1; isig <= siglist[0]; isig++)
	{
		sig = siglist[isig];
		gpp_sapa_ocb_cb2buffer(p_ocb, sys, sat, sig, buffer, byte_pos, bit_pos);
	}

	return 0;
}

static GPPLONG gpp_sapa_ocb_buffer2bias(pGPP_SAPA_OCB p_ocb, GPPUINT1 sys, GPPUINT1 sat, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPLONG rc;
	GPPUINT1 isig, sig = 0;
	GPPUINT1 siglist[34] = { 0, };

	//Phase Bias
	gpp_sapa_bias_buffer2bitmask(sys, siglist, buffer, byte_pos, bit_pos);					//SF026
	for (isig = 1; isig <= siglist[0]; isig++)
	{
		sig = siglist[isig];
		if (rc = gpp_sapa_ocb_buffer2pb(p_ocb, sys, sat, sig, buffer, byte_pos, bit_pos)) return rc;
	}

	//Code Bias
	gpp_sapa_bias_buffer2bitmask(sys, siglist, buffer, byte_pos, bit_pos);					//SF026
	for (isig = 1; isig <= siglist[0]; isig++)
	{
		sig = siglist[isig];
		if (rc = gpp_sapa_ocb_buffer2cb(p_ocb, sys, sat, sig, buffer, byte_pos, bit_pos)) return rc;
	}

	return 0;
}
static GPPLONG gpp_sapa_bias_bitmask2buffer(GPPUINT4 sig_prn_bits, GPPUINT1 sys, GPPUINT1 *siglist, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPUINT1 bit_id = 0;

	if (!siglist) return GPP_SAPA_ERR_INVALID_SIGLIST;
	gpp_sapa_get_siglist(sig_prn_bits, siglist);

	bit_id = 0;
	while (siglist[0] - SAPA_BIAS_BITMASK_LEN[sys][bit_id] > 0 && bit_id <= 1) bit_id++;							//Check (> || <)

	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 1, bit_id);
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, SAPA_BIAS_BITMASK_LEN[sys][bit_id], sig_prn_bits);

	return 0;
}
static GPPLONG gpp_sapa_bias_buffer2bitmask(GPPUINT1 sys, GPPUINT1 *siglist, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPUINT1 bit_id = 0;
	GPPUINT4 sig_prn_bits = 0;

	bit_id = gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 1);
	sig_prn_bits = gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, SAPA_BIAS_BITMASK_LEN[sys][bit_id]);

	gpp_sapa_get_siglist(sig_prn_bits, siglist);

	return 0;
}
/******************************************************************************
 *	\brief Write SAPA OCB PB to buffer
 ******************************************************************************/
static GPPLONG gpp_sapa_ocb_pb2buffer(const pGPP_SAPA_OCB p_ocb, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 sig, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPUINT1 bit_id = 1;
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 1, p_ocb->sv[sys][sat]->bias->pb[sig]->fix_flag);					//SF023
	while (p_ocb->sv[sys][sat]->bias->pb[sig]->countinity_indicator >= SAPA_CONTI_ID[bit_id] && bit_id <= 7) bit_id++;
	bit_id -= 1;																													//SF015
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 3, bit_id);
	gn_add_val_double_to_buffer(buffer, byte_pos, bit_pos, 14, p_ocb->sv[sys][sat]->bias->pb[sig]->pb_correction, SAPA_RES_PB_CORRECTION);		//SF020

	return 0;
}//gpp_sapa_ocb_pb2buffer()


/******************************************************************************
 *	\brief Read SAPA OCB PB from buffer
 ******************************************************************************/
static GPPLONG gpp_sapa_ocb_buffer2pb(pGPP_SAPA_OCB p_ocb, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 sig, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPLONG rc;
	GPP_SAPA_OCB_SV_BIAS_PB pb = { 0, };

	pb.fix_flag = gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 1);													//SF023
	pb.countinity_indicator = SAPA_CONTI_ID[gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 3)];						//SF015
	pb.pb_correction = gn_get_val_double_from_buffer(buffer, byte_pos, bit_pos, 14, SAPA_RES_PB_CORRECTION);			    //SF020

	if (rc = gpp_sapa_ocb_add_pb(p_ocb, sys, sat, sig, &pb)) return rc;

	return 0;
}//gpp_sapa_ocb_pb2buffer()

/******************************************************************************
 *	\brief Write SAPA OCB CB to buffer
 ******************************************************************************/
static GPPLONG gpp_sapa_ocb_cb2buffer(const pGPP_SAPA_OCB p_ocb, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 sig, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	gn_add_val_double_to_buffer(buffer, byte_pos, bit_pos, 11, p_ocb->sv[sys][sat]->bias->cb[sig]->cb_correction, SAPA_RES_CB_CORRECTION);						//SF029

	return 0;
}//gpp_sapa_ocb_cb2buffer()

/******************************************************************************
 *	\brief Read SAPA OCB CB from buffer
 ******************************************************************************/
static GPPLONG gpp_sapa_ocb_buffer2cb(pGPP_SAPA_OCB p_ocb, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 sig, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPLONG rc;
	GPP_SAPA_OCB_SV_BIAS_CB cb = { 0, };

	cb.cb_correction = gn_get_val_double_from_buffer(buffer, byte_pos, bit_pos, 11, SAPA_RES_CB_CORRECTION);						//SF029

	if (rc = gpp_sapa_ocb_add_cb(p_ocb, sys, sat, sig, &cb)) return rc;

	return 0;
}//gpp_sapa_ocb_cb2buffer()








