/*
 Write and read SAPA HPAC format to and from buffer
*/
#include <stdio.h>
//#include "platform.h"

#include "gpp_sapa.h"
#include "bit2buff.h"

#define	GPP_SAPA_HPAC_SMALL_ZENTH_INVALID 0x3F 
#define	GPP_SAPA_HPAC_LARGE_ZENTH_INVALID 0xFF 
#define	GPP_SAPA_HPAC_SMALL_SLANT_INVALID 0xF  
#define	GPP_SAPA_HPAC_MEDIUM_SLANT_INVALID 0x7F  
#define	GPP_SAPA_HPAC_LARGE_SLANT_INVALID 0x3FF  
#define	GPP_SAPA_HPAC_EXTRA_LARGE_SLANT_INVALID 0x3FFF 
static const GPPDOUBLE SAPA_IONO_QUALITY[16] = { 0.00, 0.03, 0.05,0.07, 0.14, 0.28, 0.56,1.12,2.24,4.48,8.96,17.92,35.84,71.68,143.36,143.36 };
static const GPPDOUBLE SAPA_TROPO_QUALITY[8] = { 0.0,0.010,0.020,0.040,0.080,0.160,0.320,0.320 };

static const GPPUINT1 SAPA_TROPO_GRD_DELAY[2] = { SAPA_SMALL_TROPO_RESIDUAL_ZENITH_DELAY, SAPA_LARGE_TROPO_RESIDUAL_ZENITH_DELAY };
static const GPPUINT1 SAPA_IONO_RESIDUAL_SLANT_DELAY[4] = { SAPA_SMALL_IONO_RESIDUAL_SLANT_DELAY,SAPA_MEDIUM_IONO_RESIDUAL_SLANT_DELAY,SAPA_LARGE_IONO_RESIDUAL_SLANT_DELAY ,SAPA_EXTRA_LARGE_IONO_RESIDUAL_SLANT_DELAY };
static const GPPUINT2 SAPA_IONO_RESIDUAL_SLANT_INVALID[4] = { GPP_SAPA_HPAC_SMALL_SLANT_INVALID ,GPP_SAPA_HPAC_MEDIUM_SLANT_INVALID, GPP_SAPA_HPAC_LARGE_SLANT_INVALID,GPP_SAPA_HPAC_EXTRA_LARGE_SLANT_INVALID };


#define SAPA_T012_NBITS_SML 7
#define SAPA_T012_NBITS_LRG 9

#define SAPA_T00_NBITS_SML  SAPA_T012_NBITS_SML
#define SAPA_T00_NBITS_LRG  SAPA_T012_NBITS_LRG

#define SAPA_T01_NBITS_SML  SAPA_T012_NBITS_SML
#define SAPA_T01_NBITS_LRG  SAPA_T012_NBITS_LRG

#define SAPA_T10_NBITS_SML  SAPA_T012_NBITS_SML
#define SAPA_T10_NBITS_LRG  SAPA_T012_NBITS_LRG

#define SAPA_T11_NBITS_SML  9
#define SAPA_T11_NBITS_LRG  11


static const GPPUINT1 SAPA_TROPO_POLY_NBITS_SML[SAPA_MAX_TROPO_COEFF] = { SAPA_T00_NBITS_SML, SAPA_T01_NBITS_SML, SAPA_T10_NBITS_SML, SAPA_T11_NBITS_SML };
static const GPPUINT1 SAPA_TROPO_POLY_NBITS_LRG[SAPA_MAX_TROPO_COEFF] = { SAPA_T00_NBITS_LRG, SAPA_T01_NBITS_LRG, SAPA_T10_NBITS_LRG, SAPA_T11_NBITS_LRG };
static const GPPUINT1* SAPA_TROPO_POLY_NBITS[2] = { SAPA_TROPO_POLY_NBITS_SML, SAPA_TROPO_POLY_NBITS_LRG };


#define SAPA_TROPO_GRD_NBITS_SML 6
#define SAPA_TROPO_GRD_NBITS_LRG 8

static const GPPUINT1 SAPA_TROPO_GRD_NBITS[2] = { SAPA_TROPO_GRD_NBITS_SML, SAPA_TROPO_GRD_NBITS_LRG };

#define SAPA_TROPO_GRD_INVALID_SML 0x3F
#define SAPA_TROPO_GRD_INVALID_LRG 0xFF

static const GPPUINT1 SAPA_TROPO_GRD_INVALID[2] = { SAPA_TROPO_GRD_INVALID_SML, SAPA_TROPO_GRD_INVALID_LRG };


#define SAPA_C012_NBITS_SML 12
#define SAPA_C012_NBITS_LRG 14

#define SAPA_C00_NBITS_SML SAPA_C012_NBITS_SML
#define SAPA_C00_NBITS_LRG SAPA_C012_NBITS_LRG

#define SAPA_C01_NBITS_SML SAPA_C012_NBITS_SML
#define SAPA_C01_NBITS_LRG SAPA_C012_NBITS_LRG

#define SAPA_C10_NBITS_LRG SAPA_C012_NBITS_LRG
#define SAPA_C10_NBITS_SML SAPA_C012_NBITS_SML

#define SAPA_C11_NBITS_LRG 15
#define SAPA_C11_NBITS_SML 13

static const GPPUINT1 SAPA_IONO_POLY_NBITS_SML[SAPA_MAX_IONO_COEFF] = { SAPA_C00_NBITS_SML, SAPA_C01_NBITS_SML, SAPA_C10_NBITS_SML, SAPA_C11_NBITS_SML };
static const GPPUINT1 SAPA_IONO_POLY_NBITS_LRG[SAPA_MAX_IONO_COEFF] = { SAPA_C00_NBITS_LRG, SAPA_C01_NBITS_LRG, SAPA_C10_NBITS_LRG, SAPA_C11_NBITS_LRG };
static const GPPUINT1* SAPA_IONO_POLY_NBITS[2] = { SAPA_IONO_POLY_NBITS_SML, SAPA_IONO_POLY_NBITS_LRG };

#define SAPA_IONO_GRD_NBITS_SML 4
#define SAPA_IONO_GRD_NBITS_MED 7
#define SAPA_IONO_GRD_NBITS_LRG 10
#define SAPA_IONO_GRD_NBITS_EXTRALRG 14


static const GPPUINT1 SAPA_IONO_GRD_NBITS[4] = { SAPA_IONO_GRD_NBITS_SML, SAPA_IONO_GRD_NBITS_MED,SAPA_IONO_GRD_NBITS_LRG,SAPA_IONO_GRD_NBITS_EXTRALRG };

#define SAPA_IONO_GRD_INVALID_SML 0xF
#define SAPA_IONO_GRD_INVALID_MED 0x7F
#define SAPA_IONO_GRD_INVALID_LRG 0x3FF
#define SAPA_IONO_GRD_INVALID_EXTRALRG 0x3FFF


static const GPPUINT1 SAPA_IONO_GRD_INVALID[4] = { SAPA_IONO_GRD_INVALID_SML, SAPA_IONO_GRD_INVALID_MED ,SAPA_IONO_GRD_INVALID_LRG ,SAPA_IONO_GRD_INVALID_EXTRALRG };

/********************************************************************************************************************************************************************
 *	Declaration of functions to store data in Buffer for HPAC
 *******************************************************************************************************************************************************************/
static GPPLONG gpp_sapa_hpac_header2buffer(const pGPP_SAPA_HPAC p_hpac, const SAPA_HANDLE *sapaHdl,GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_hpac_atmo2buffer(const pGPP_SAPA_HPAC p_hpac, const SAPA_HANDLE *sapaHdl, GPPUINT1 area, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_hpac_area2buffer(const pGPP_SAPA_HPAC p_hpac, const SAPA_HANDLE *sapaHdl, GPPUINT1 area, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_hpac_tropo2buffer(const pGPP_SAPA_HPAC p_hpac, const SAPA_HANDLE *sapaHdl, GPPUINT1 area, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_hpac_tropo_poly_coefficient_block2buffer(const pGPP_SAPA_HPAC p_hpac, const SAPA_HANDLE *sapaHdl,GPPUINT1 area, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_hpac_grd_tropo2buffer(const pGPP_SAPA_HPAC hpac, const SAPA_HANDLE *sapaHdl, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_hpac_tropo_grid_block2buffer(const pGPP_SAPA_HPAC p_hpac, const SAPA_HANDLE *sapaHdl,GPPUINT1 area, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_hpac_iono2buffer(const pGPP_SAPA_HPAC p_hpac, const SAPA_HANDLE *sapaHdl,GPPUINT1 area, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_hpac_iono_sv_bitmask2buffer(GPPUINT8 sv_prn_bits, GPPUINT1 sys, GPPUINT1 *svlist, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_hpac_iono_sat2buffer(const pGPP_SAPA_HPAC p_hpac, const SAPA_HANDLE *sapaHdl, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 area, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_hpac_iono_sat_poly2buffer(const pGPP_SAPA_HPAC p_hpac, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 area, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_hpac_iono_sat_coeff2buffer(const pGPP_SAPA_HPAC p_hpac, const SAPA_HANDLE *sapaHdl,GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 area, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_hpac_iono_sat_grid2buffer(const pGPP_SAPA_HPAC p_hpac, const SAPA_HANDLE *sapaHdl,GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 area, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);

/********************************************************************************************************************************************************************
 *	Delecation of function to read data from buffer for HPAC
 *******************************************************************************************************************************************************************/
static GPPLONG gpp_sapa_hpac_buffer2header(pGPP_SAPA_HPAC p_hpac, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_hpac_buffer2atmo(pGPP_SAPA_HPAC p_hpac, GPPUINT1 area, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_hpac_buffer2area(pGPP_SAPA_HPAC p_hpac, GPPUINT1 area, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_hpac_buffer2tropo(pGPP_SAPA_HPAC p_hpac, GPPUINT1 area, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_hpac_buffer2tropo_poly_coefficient_block(pGPP_SAPA_HPAC p_hpac, GPPUINT1 area, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_hpac_buffer2tropo_grid_block(pGPP_SAPA_HPAC p_hpac, GPPUINT1 area, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_hpac_buffer2iono(pGPP_SAPA_HPAC p_hpac, GPPUINT1 area, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_hpac_buffer2iono_sv_bitmask(GPPUINT8 *sv_prn_bits, GPPUINT1 sys, GPPUINT1 *svlist, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_hpac_buffer2iono_sat(pGPP_SAPA_HPAC p_hpac, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 area, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_hpac_buffer2iono_sat_poly(pGPP_SAPA_HPAC p_hpac, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 area, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_hpac_buffer2iono_sat_coeff(pGPP_SAPA_HPAC p_hpac, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 area, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_hpac_buffer2iono_sat_grid(pGPP_SAPA_HPAC p_hpac, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 area, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);


/**************************************************************************
 *	\brief Write SAPA HPAC message to buffer
 *
 *	\param[in] 	hpac 	Pointer to GPP_SAPA_HPAC structure
 *	\param[in]	sys		GNSS indicator
 *	\param[in]	*buffer
 *	\param[in]	*byte_pos
 *	\param[in]	*bit_pos
 *
 *	\retval 	Number of needed bits
 *	\retval 	Error Code
 *************************************************************************/
GPPLONG gpp_sapa_hpac2buffer(const pGPP_SAPA_HPAC hpac, const SAPA_HANDLE *sapaHdl,GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPLONG rc;
	GPPUINT1 ia;
	GPPUINT1 arealist[258] = { 0, };
	GPPLONG byte_pos0, bit_pos0;
	GPPLONG mybyte = 0, mybit = 0;

	// handling if byte_pos or bit_pos are null pointers
	if (!byte_pos) 	byte_pos = &mybyte;
	if (!bit_pos) 	bit_pos = &mybit;

	// get start position of byte_pos and bit_pos to get needed bits
	byte_pos0 = *byte_pos;
	bit_pos0 = *bit_pos;
	if (!hpac) return GPP_SAPA_ERR_INVALID_HPAC_HEADER;
	if(!sapaHdl) return GPP_SAPA_ERR_INVALID_HANDLE;

	if (rc = gpp_sapa_hpac_header2buffer(hpac, sapaHdl,buffer, byte_pos, bit_pos)) return rc;
	gpp_sapa_get_arealist(sapaHdl->hpacHdl->area_bits, arealist);
	for (ia = 0; ia < arealist[0]; ia++) {
		if (rc = gpp_sapa_hpac_atmo2buffer(hpac, sapaHdl,ia, buffer, byte_pos, bit_pos)) return rc;
	}
	return  gpp_sapa_get_bit_diff(*byte_pos, *bit_pos, byte_pos0, bit_pos0);
}//gpp_sapa_hpac2buffer()


/**************************************************************************
 *	\brief Read SAPA HPAC message from buffer
 *
 *	\param[in] 	hpac 	Pointer to GPP_SAPA_OCB structure
 *	\param[in]	*buffer
 *	\param[in]	*byte_pos
 *	\param[in]	*bit_pos
 *
 *	\retval 	Number of read bits
 *	\retval 	Error Code
 *************************************************************************/
GPPLONG gpp_sapa_buffer2hpac(pGPP_SAPA_HPAC hpac, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPLONG rc;
	GPPLONG byte_pos0, bit_pos0;
	GPPLONG mybyte = 0, mybit = 0;

	GPPUINT1 ia, no_of_areas;

	// handling if byte_pos or bit_pos are null pointers
	if (!byte_pos) 	byte_pos = &mybyte;
	if (!bit_pos) 	bit_pos = &mybit;

	// get start position of byte_pos and bit_pos to get needed bits
	byte_pos0 = *byte_pos;
	bit_pos0 = *bit_pos;

	if (rc = gpp_sapa_hpac_buffer2header(hpac,buffer, byte_pos, bit_pos)) return rc;
	no_of_areas = hpac->header_block->area_count;
	for (ia = 0; ia < no_of_areas; ia++) {
		if (rc = gpp_sapa_hpac_buffer2atmo(hpac, ia, buffer, byte_pos, bit_pos)) return rc;
	}
	return  gpp_sapa_get_bit_diff(*byte_pos, *bit_pos, byte_pos0, bit_pos0);
}//gpp_sapa_buffer2hpac()

/******************************************************************************
 *	\brief Write HPAC header to buffer
 *
 *	\param[in]	hpac
 *	\param[in]	*buffer
 *	\param[in]	*byte_pos
 *	\param[in]	*bit_pos
 *
 *	\retval 0 Ok
 *	\retval Error Code
 ******************************************************************************/
static GPPLONG gpp_sapa_hpac_header2buffer(const pGPP_SAPA_HPAC p_hpac, const SAPA_HANDLE *sapaHdl,GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPP_SAPA_HPAC_HEADER *header = NULL;
	GPPUINT1 time_tag_nbits;

	if (!(header=p_hpac->header_block)) return GPP_SAPA_ERR_INVALID_HPAC_HEADER;
	SAPA_HPAC_HANDLE *hpacHdl = NULL;
	if (!(hpacHdl = sapaHdl->hpacHdl)) return GPP_SAPA_ERR_INVALID_HPAC_HANDLE;
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 4, header->message_sub_type);										//SF001
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 1, hpacHdl->time_tag_type);														//SF002
	switch (hpacHdl->time_tag_type) {
	case SAPA_FULL_TIME_TAG:
		time_tag_nbits = 32;
		break;
	case SAPA_HOURLY_TIME_TAG:
		time_tag_nbits = 12;
		break;
	default: return GPP_SAPA_ERR_INVALID_TIME_TAG_TYPE;
	}
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, time_tag_nbits, header->time_tag);									//SF004
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 7, header->sol_id);													//SF006
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 4, header->sol_processor_id);										//SF007
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 9, header->sol_issue_of_update);									   //SF005
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 1, header->reserved);
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 4, header->area_issue_of_update);
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 5, header->area_count);												//SF030
	return 0;
}//gpp_sapa_hpac_header2buffer()

/******************************************************************************
 *	\brief Read HPAC header from buffer
 *
 *	\param[in]	hpac
 *	\param[in]	sys
 *	\param[in]	*buffer
 *	\param[in]	*byte_pos
 *	\param[in]	*bit_pos
 *
 *	\retval 0 Ok
 *	\retval Error Code
 ******************************************************************************/
static GPPLONG gpp_sapa_hpac_buffer2header(pGPP_SAPA_HPAC p_hpac,const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPLONG rc;
	GPP_SAPA_HPAC_HEADER header = { 0, };
	header.message_sub_type=gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 4);										//SF001
	header.time_tag_type=gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 1);										//SF002
	if (header.time_tag_type == GNSS_FULL_TIME_TAG)
	{
		header.time_tag=gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 32);														//SF004
	}
	else if (header.time_tag_type == GNSS_HOURLY_TIME_TAG)
	{
		header.time_tag=gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 12);														//SF003
	}
	header.sol_id=gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 7);												//SF006
	header.sol_processor_id=gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 4);										//SF007
	header.sol_issue_of_update=gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 9);									//SF005
	header.reserved = gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 1);									//SF069
	header.area_issue_of_update = gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 4);									//SF068
	header.area_count=gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 5);											//SF030
	if(rc=gpp_sapa_hpac_add_header(p_hpac, &header)) return rc;
	return 0;
}//gpp_sapa_hpac_buffer2header()

/******************************************************************************************************************************************************************
 *	\brief Store atmosphere block data into buffer
 ******************************************************************************************************************************************************************/
static GPPLONG gpp_sapa_hpac_atmo2buffer(const pGPP_SAPA_HPAC p_hpac, const SAPA_HANDLE *sapaHdl,GPPUINT1 area, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPLONG rc;
	if(rc=gpp_sapa_hpac_area2buffer(p_hpac, sapaHdl,area,buffer, byte_pos, bit_pos)) return rc;
	if(rc=gpp_sapa_hpac_tropo2buffer(p_hpac, sapaHdl, area, buffer, byte_pos, bit_pos)) return rc;
	if(rc=gpp_sapa_hpac_iono2buffer(p_hpac, sapaHdl, area, buffer, byte_pos, bit_pos)) return rc;
	return 0;
}//gpp_sapa_hpac_atmo2buffer()

/******************************************************************************************************************************************************************
 *	\brief Read atmosphere block data from buffer
 ******************************************************************************************************************************************************************/
static GPPLONG gpp_sapa_hpac_buffer2atmo(pGPP_SAPA_HPAC p_hpac, GPPUINT1 area,const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPLONG rc;
	if (rc = gpp_sapa_hpac_buffer2area(p_hpac,area, buffer, byte_pos, bit_pos)) return rc;
	if (rc=gpp_sapa_hpac_buffer2tropo(p_hpac, area, buffer, byte_pos, bit_pos)) return rc;
	if (rc=gpp_sapa_hpac_buffer2iono(p_hpac, area, buffer, byte_pos, bit_pos)) return rc;
	return 0;
}//gpp_sapa_hpac_buffer2atmo()

/******************************************************************************************************************************************************************
 *	\brief Store Area block data into buffer
 ******************************************************************************************************************************************************************/
static GPPLONG gpp_sapa_hpac_area2buffer(const pGPP_SAPA_HPAC p_hpac, const SAPA_HANDLE *sapaHdl, GPPUINT1 area, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPUINT1 tropo_block_indicator=0, iono_block_indicator=0;
	GPP_SAPA_HPAC_AREA *area_block = NULL;
	/*if (!(area_block = p_hpac->atmo[area]->area_def)) return GPP_SAPA_ERR_INVALID_HPAC_AREA;
	if (hpacHdl->hpacTropoHdl_bits[area] & (1 << GPP_SAPA_HPAC_NOT_PRESENT)) tropo_block_indicator = GPP_SAPA_HPAC_NOT_PRESENT;
	else if (hpacHdl->hpacTropoHdl_bits[area] & (1 << GPP_SAPA_HPAC_POLY_PRESENT)) tropo_block_indicator = GPP_SAPA_HPAC_POLY_PRESENT;
	else if (hpacHdl->hpacTropoHdl_bits[area] & (1 << GPP_SAPA_HPAC_POLY_AND_GRID_PRESENT)) tropo_block_indicator = GPP_SAPA_HPAC_POLY_AND_GRID_PRESENT;
	if (hpacHdl->hpacIonoHdl_bits[area] & (1 << GPP_SAPA_HPAC_NOT_PRESENT)) iono_block_indicator = GPP_SAPA_HPAC_NOT_PRESENT;
	else if (hpacHdl->hpacIonoHdl_bits[area] & (1 << GPP_SAPA_HPAC_POLY_PRESENT)) iono_block_indicator = GPP_SAPA_HPAC_POLY_PRESENT;
	else if (hpacHdl->hpacIonoHdl_bits[area] & (1 << GPP_SAPA_HPAC_POLY_AND_GRID_PRESENT)) iono_block_indicator = GPP_SAPA_HPAC_POLY_AND_GRID_PRESENT;*/
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 8, area_block->area_id);          //SF031
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 7, area_block->number_of_grid_point);               //SF039
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 2, area_block->tropo_block_indicator);       //SF040
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 2, area_block->iono_block_indicator);       //SF040
	return 0;
}//gpp_sapa_hpac_area2buffer()
/******************************************************************************************************************************************************************
 *	\brief Read Area block data from buffer
 ******************************************************************************************************************************************************************/
static GPPLONG gpp_sapa_hpac_buffer2area(pGPP_SAPA_HPAC p_hpac, GPPUINT1 area,const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPLONG rc;
	GPP_SAPA_HPAC_AREA area_def = { 0, };
	area_def.area_id = gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 8);																		//SF031																															//SF015
	area_def.number_of_grid_point=gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 7);															//SF039
	area_def.tropo_block_indicator=gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 2);														//SF040
	area_def.iono_block_indicator=gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 2);															//SF040
	if (rc = gpp_sapa_hpac_add_area(p_hpac, area, &area_def)) return rc;
	return 0;
}//gpp_sapa_hpac_buffer2area()

/******************************************************************************************************************************************************************
 *	\brief Store Troposphere block data into buffer
 ******************************************************************************************************************************************************************/
static GPPLONG gpp_sapa_hpac_tropo2buffer(const pGPP_SAPA_HPAC p_hpac, const SAPA_HANDLE *sapaHdl, GPPUINT1 area, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPLONG  rc=0;
	//GPPINT1 tropo_block_indicator;
	/*if (hpacHdl->hpacTropoHdl_bits[area] & (1 << GPP_SAPA_HPAC_NOT_PRESENT)) tropo_block_indicator = GPP_SAPA_HPAC_NOT_PRESENT;
	else if (hpacHdl->hpacTropoHdl_bits[area] & (1 << GPP_SAPA_HPAC_POLY_PRESENT)) tropo_block_indicator = GPP_SAPA_HPAC_POLY_PRESENT;
	else if (hpacHdl->hpacTropoHdl_bits[area] & (1 << GPP_SAPA_HPAC_POLY_AND_GRID_PRESENT)) tropo_block_indicator = GPP_SAPA_HPAC_POLY_AND_GRID_PRESENT;*/
	GPPUINT1 tropo_block_indicator = p_hpac->atmo[area]->area_def->tropo_block_indicator;
	if (tropo_block_indicator == GPP_SAPA_HPAC_POLY_PRESENT || tropo_block_indicator == GPP_SAPA_HPAC_POLY_AND_GRID_PRESENT)					//1 or 2
	{
		if(rc=gpp_sapa_hpac_tropo_poly_coefficient_block2buffer(p_hpac, sapaHdl, area,buffer, byte_pos, bit_pos)) return 0;
	}
	if (tropo_block_indicator == GPP_SAPA_HPAC_POLY_AND_GRID_PRESENT)
		if(rc= gpp_sapa_hpac_grd_tropo2buffer(p_hpac, sapaHdl,buffer,byte_pos,bit_pos)) return 0;
	return rc;
}//gpp_sapa_hpac_tropo2buffer()

/******************************************************************************************************************************************************************
 *	\brief Read Troposphere block data from buffer
 ******************************************************************************************************************************************************************/
static GPPLONG gpp_sapa_hpac_buffer2tropo(pGPP_SAPA_HPAC p_hpac,GPPUINT1 area,const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPLONG  rc=0;
	if (p_hpac->atmo[area]->area_def->tropo_block_indicator == GPP_SAPA_HPAC_POLY_PRESENT || p_hpac->atmo[area]->area_def->tropo_block_indicator == GPP_SAPA_HPAC_POLY_AND_GRID_PRESENT)					//1 or 2
	{
		if (rc = gpp_sapa_hpac_buffer2tropo_poly_coefficient_block(p_hpac, area, buffer, byte_pos, bit_pos)) return 0;
	}
	if (p_hpac->atmo[area]->area_def->tropo_block_indicator == GPP_SAPA_HPAC_POLY_AND_GRID_PRESENT)
		if (rc = gpp_sapa_hpac_buffer2grd_tropo(p_hpac, area, buffer, byte_pos, bit_pos)) return 0;
	return rc;
}//gpp_sapa_hpac_buffer2tropo()

/******************************************************************************************************************************************************************
 *	\brief Store Troposphere Polynomial Coefficient block data into buffer
 ******************************************************************************************************************************************************************/
static GPPLONG gpp_sapa_hpac_tropo_poly_coefficient_block2buffer(const pGPP_SAPA_HPAC p_hpac, const SAPA_HANDLE *sapaHdl, GPPUINT1 area, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPUINT1 it, sz, equ_type;
	GPPUINT1 bit_id = 1;
	GPP_SAPA_HPAC_TROPO_POLY_COEFFICIENT_BLOCK *tpcb = NULL;

	tpcb = p_hpac->atmo[area]->tropo->tropo_poly_coeff_block;

	equ_type = tpcb->tropo_equation_type;
	sz = tpcb->tropo_coeff_size;

	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 3, equ_type);           //SF041

	while (bit_id <= 7 && tpcb->tropo_quality >= SAPA_TROPO_QUALITY[bit_id]) bit_id++;
	bit_id -= 1;
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 3, bit_id);                         //SF042

	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 8, p_hpac->atmo[area]->tropo->tropo_poly_coeff_block->ltropo_avhd);
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 1, sz);

	if (equ_type >= 3) return GPP_SAPA_ERR_INVALID_TROPO_EQ_TYPE;

	it = SAPA_T00_IDX;

	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, SAPA_TROPO_POLY_NBITS[sz][it], tpcb->ltropo_poly_coeff[it]);             
	if (equ_type > 0) {
		it = SAPA_T01_IDX;
		gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, SAPA_TROPO_POLY_NBITS[sz][it], tpcb->ltropo_poly_coeff[it]);
		it = SAPA_T10_IDX;
		gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, SAPA_TROPO_POLY_NBITS[sz][it], tpcb->ltropo_poly_coeff[it]);
}

	if (equ_type == 2) {
		it = SAPA_T11_IDX;
		gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, SAPA_TROPO_POLY_NBITS[sz][it], tpcb->ltropo_poly_coeff[it]);}
	return 0;
}//gpp_sapa_hpac_tropo_poly_coefficient_block2buffer()

/******************************************************************************************************************************************************************
 *	\brief Read Troposphere Polynomial Coefficient block data from buffer
 ******************************************************************************************************************************************************************/
static GPPLONG gpp_sapa_hpac_buffer2tropo_poly_coefficient_block(pGPP_SAPA_HPAC p_hpac, GPPUINT1 area, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPLONG rc;
	GPPUINT1 sz, it, equ_type;
	GPP_SAPA_HPAC_TROPO_POLY_COEFFICIENT_BLOCK tpcb = { 0, };

	if ((tpcb.tropo_equation_type = gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 3)) >= 3) return GPP_SAPA_ERR_INVALID_TROPO_EQ_TYPE;          //SF041
	equ_type = tpcb.tropo_equation_type;

	tpcb.tropo_quality = SAPA_TROPO_QUALITY[gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 3)];                       //SF042

	gpp_sapa_buffer2float(buffer, byte_pos, bit_pos, SAPA_AVHD_MIN, 8, SAPA_AVHD_RES, NULL, &tpcb.tropo_avhd);   //SF043

	tpcb.tropo_coeff_size = gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 1);           //SF044
	sz = tpcb.tropo_coeff_size;


	it = SAPA_T00_IDX;
	gpp_sapa_buffer2float(buffer, byte_pos, bit_pos, SAPA_TROPO_POLY_MIN[sz][it], SAPA_TROPO_POLY_NBITS[sz][it], SAPA_TROPO_POLY_RES[it], NULL, &tpcb.tropo_poly_coeff[it]);

	if (equ_type > 0) {
		it = SAPA_T01_IDX;
		gpp_sapa_buffer2float(buffer, byte_pos, bit_pos, SAPA_TROPO_POLY_MIN[sz][it], SAPA_TROPO_POLY_NBITS[sz][it], SAPA_TROPO_POLY_RES[it], NULL, &tpcb.tropo_poly_coeff[it]);

		it = SAPA_T10_IDX;
		gpp_sapa_buffer2float(buffer, byte_pos, bit_pos, SAPA_TROPO_POLY_MIN[sz][it], SAPA_TROPO_POLY_NBITS[sz][it], SAPA_TROPO_POLY_RES[it], NULL, &tpcb.tropo_poly_coeff[it]);
	}

	if (equ_type == 2) {
		it = SAPA_T11_IDX;
		gpp_sapa_buffer2float(buffer, byte_pos, bit_pos, SAPA_TROPO_POLY_MIN[sz][it], SAPA_TROPO_POLY_NBITS[sz][it], SAPA_TROPO_POLY_RES[it], NULL, &tpcb.tropo_poly_coeff[it]);
	}

	if (rc = gpp_sapa_hpac_add_tropo_poly_coeff_block(p_hpac, area, &tpcb)) return rc;
	return 0;
}//gpp_sapa_hpac_buffer2tropo_poly_coefficient_block()
/******************************************************************************************************************************************************************
 *	\brief Store  Grid data into buffer
 ******************************************************************************************************************************************************************/
static GPPLONG gpp_sapa_hpac_grd_tropo2buffer(const pGPP_SAPA_HPAC hpac, const SAPA_HANDLE *sapaHdl, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPUINT1 ia, areaId, arealist[258];

	if (!sapaHdl) return GPP_SAPA_ERR_INVALID_HANDLE;

	if(!(sapaHdl->hpacHdl->tropo_blk_indicator & 2)) return 0; // needs to be optimized with definition

	gpp_sapa_get_arealist(sapaHdl->hpacHdl->area_bits, arealist); //identify all areas that shall be sent in this message if filled with valid values

	for (ia = 1; ia <= arealist[0]; ia++) {
		areaId = arealist[ia];

		if (GNSS_HAS_IDX_IN_BITS_64(hpac->atmo_bits[areaId / 64], areaId % 64)) {// have valid atmo data in hpac

			pGPP_SAPA_HPAC_ATMO_BLOCK atmo = NULL;
			pGPP_SAPA_HPAC_TROPO_GRID_BLOCK grd_tropo = NULL;
			GPPUINT1 igrd, sz;


			if (!(atmo = hpac->atmo[areaId])) return GPP_SAPA_ERROR_BASE;//double check; use error code here as this indicates an error in the add_tropo or add_iono data

			if (!atmo->tropo) continue; //okay, no tropo data in hpac
			if (!(grd_tropo = atmo->tropo->tropo_grid)) continue; //okay, no tropo data in hpac

			sz = grd_tropo->sz;
			gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 1, grd_tropo->sz);

			for (igrd = 0; igrd < grd_tropo->num_grid; igrd++) {
				if (GNSS_HAS_IDX_IN_BITS_64(grd_tropo->grid_bits, igrd)) {// have valid data
					gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, SAPA_TROPO_GRD_NBITS[sz], grd_tropo->grid[igrd]->lval);
				}
				else {
					gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, SAPA_TROPO_GRD_NBITS[sz], SAPA_TROPO_GRD_INVALID[sz]);
				}
			}
		}
	}//for loop ia

	return 0;
}//gpp_sapa_hpac_grd_tropo2buffer()

/******************************************************************************************************************************************************************
 *	\brief Store  buffer into Grid Data
 ******************************************************************************************************************************************************************/
static GPPLONG gpp_sapa_hpac_buffer2grd_tropo(const pGPP_SAPA_HPAC hpac, GPPUINT1 area,GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPUINT1 isValid = 1;
	GPPUINT1 lvalue;
	GPP_SAPA_USE_STATES states = { 0, };
	GPP_SAPA_HPAC_TROPO_GRID_BLOCK grid_block = { 0, };
	GPP_SAPA_HPAC_TROPO_GRD_CORRECTION tropo_grd = { 0, };
	GPPUINT1 ia,sz, igrd,no_of_grid,tropo_indi;
	tropo_indi = hpac->atmo[area]->area_def->tropo_block_indicator;
	if(tropo_indi!=2) return 0; // needs to be optimized with definition
	grid_block.sz=gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 1);
	sz = grid_block.sz;
	no_of_grid = hpac->atmo[area]->area_def->number_of_grid_point;
	for (igrd = 0; igrd < no_of_grid; igrd++) {
		GPPULONG rc;
		lvalue=gpp_sapa_buffer2float(buffer, byte_pos, bit_pos, SAPA_TROPO_GRD_MIN[sz], SAPA_TROPO_GRD_NBITS[sz], SAPA_TROPO_GRD_RES, &SAPA_TROPO_GRD_INVALID[sz],&tropo_grd.val);//SF052
		isValid = &lvalue;
		if (rc = gpp_sapa_hpac_add_grd_tropo_correction(&states, area, igrd, &tropo_grd)) return rc;
		if (isValid)
			GNSS_SET_IDX_IN_BITS_64(hpac->atmo[area]->tropo->tropo_grid->grid_bits, igrd);
	}
	return 0;
}//gpp_sapa_hpac_grd_tropo2buffer()
 
/******************************************************************************************************************************************************************
 *	\brief Store Ionospher block data into buffer
 ******************************************************************************************************************************************************************/
static GPPLONG gpp_sapa_hpac_iono2buffer(const pGPP_SAPA_HPAC p_hpac, const SAPA_HANDLE *sapaHdl, GPPUINT1 area, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPUINT1 syslist[18] = { 0, };
	GPPUINT1 svlist[66] = { 0, };
	GPP_SAPA_HPAC_IONO *iono_block = iono_block = p_hpac->atmo[area]->iono;
	if (p_hpac->atmo[area]->area_def->iono_block_indicator != 0)
	{
		GPPUINT1 isat, isys,sys;
		gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 3, iono_block->iono_equation_type);     //SF054
		sys = sapaHdl->hpacHdl->sys;
		for (isys = 1; isys <= sys; isys++) {

			GPPLONG rc;
			if (rc = gpp_sapa_hpac_iono_sv_bitmask2buffer(iono_block->sat_prn_bits[isys], isys, svlist, buffer, byte_pos, bit_pos)) return rc;
			for (isat = 1; isat <= svlist[0]; isat++) {
				GPPUINT1 sat;
				sat = svlist[isat];
				if (rc = gpp_sapa_hpac_iono_sat2buffer(p_hpac, sapaHdl, sys, sat, area, buffer, byte_pos, bit_pos)) return rc;
			}
		}
	}
	return 0;
}//gpp_sapa_hpac_iono2buffer()
/******************************************************************************************************************************************************************
 *	\brief Read Ionospher block data from buffer
 ******************************************************************************************************************************************************************/
static GPPLONG gpp_sapa_hpac_buffer2iono(pGPP_SAPA_HPAC p_hpac, GPPUINT1 area,const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPP_SAPA_HPAC_IONO iono = { 0, };
	GPPUINT1 svlist[66] = { 0, };

	if (p_hpac->atmo[area]->area_def->iono_block_indicator != 0)
	{
		GPPLONG rc;
		GPPUINT1 isat,sys;
		iono.iono_equation_type=gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 3);     //SF054
		if (rc = gpp_sapa_hpac_add_iono(p_hpac,area, &iono)) return rc;

		for (sys = 0; sys < 2; sys++)
		{
			if (rc = gpp_sapa_hpac_buffer2iono_sv_bitmask(&p_hpac->atmo[area]->iono->sat_prn_bits[sys], sys, svlist, buffer, byte_pos, bit_pos)) return rc;
			for (isat = 1; isat <= svlist[0]; isat++) {
				GPPUINT1 sat;
				sat = svlist[isat];
				if (rc = gpp_sapa_hpac_buffer2iono_sat(p_hpac, sys, sat, area, buffer, byte_pos, bit_pos)) return rc;
			}
		}
	}
	return 0;
}//gpp_sapa_hpac_buffer2iono()

/******************************************************************************************************************************************************************
 *	\brief Store Ionospher  Bit Mask  data into buffer
 ******************************************************************************************************************************************************************/
static GPPLONG gpp_sapa_hpac_iono_sv_bitmask2buffer(GPPUINT8 sv_prn_bits, GPPUINT1 sys, GPPUINT1 *svlist, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPUINT1 bit_id = 0;

	if (!svlist) return GPP_SAPA_ERR_INVALID_SVLIST;

	gpp_sapa_get_svlist(sv_prn_bits, svlist);
	bit_id = 0;
	while (svlist[0] - SAPA_SV_BITMASK_LEN[sys][bit_id] > 0 && bit_id <= 3) bit_id++;							//Check (> || <)

	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 2, bit_id);																	//SF011
	gn_add_longlong_to_buffer(buffer, byte_pos, bit_pos, SAPA_SV_BITMASK_LEN[sys][bit_id], sv_prn_bits);

	return 0;
}//gpp_sapa_hpac_iono_sv_bitmask2buffer()

/******************************************************************************************************************************************************************
 *	\brief Read Ionospher  Bit Mask  data from buffer
 ******************************************************************************************************************************************************************/
static GPPLONG gpp_sapa_hpac_buffer2iono_sv_bitmask(GPPUINT8 *sv_prn_bits, GPPUINT1 sys, GPPUINT1 *svlist, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPUINT1 bit_id;

	bit_id = gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 2);
	*sv_prn_bits= gn_get_ulonglong_from_buffer(buffer, byte_pos, bit_pos, SAPA_SV_BITMASK_LEN[sys][bit_id]);
	gpp_sapa_get_svlist(*sv_prn_bits, svlist);

	return 0;
}//gpp_sapa_hpac_buffer2iono_sv_bitmask()

/******************************************************************************************************************************************************************
 *	\brief Store Ionospher Satellite block data into buffer
 ******************************************************************************************************************************************************************/
static GPPLONG gpp_sapa_hpac_iono_sat2buffer(const pGPP_SAPA_HPAC p_hpac, const SAPA_HANDLE *sapaHdl,GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 area, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPLONG rc=0;
	GPPUINT1 iono_block_indicator = p_hpac->atmo[area]->area_def->iono_block_indicator;;
	/*if (hpacHdl->hpacIonoHdl_bits[area] & (1 << GPP_SAPA_HPAC_NOT_PRESENT)) iono_block_indicator = GPP_SAPA_HPAC_NOT_PRESENT;
	else if(hpacHdl->hpacIonoHdl_bits[area] & (1 << GPP_SAPA_HPAC_POLY_PRESENT)) iono_block_indicator = GPP_SAPA_HPAC_POLY_PRESENT;
	else if(hpacHdl->hpacIonoHdl_bits[area] & (1 << GPP_SAPA_HPAC_POLY_AND_GRID_PRESENT)) iono_block_indicator = GPP_SAPA_HPAC_POLY_AND_GRID_PRESENT;*/
	if (iono_block_indicator == GPP_SAPA_HPAC_POLY_PRESENT || iono_block_indicator == GPP_SAPA_HPAC_POLY_AND_GRID_PRESENT)					//1 or 2
	{
		if (rc = gpp_sapa_hpac_iono_sat_poly2buffer(p_hpac, sys, sat, area, buffer, byte_pos, bit_pos)) return 0;
		if (rc = gpp_sapa_hpac_iono_sat_coeff2buffer(p_hpac, sapaHdl, sys, sat, area, buffer, byte_pos, bit_pos)) return 0;
	}
	if (iono_block_indicator == GPP_SAPA_HPAC_POLY_AND_GRID_PRESENT)					// 2
	{
		if (rc = gpp_sapa_hpac_iono_sat_grid2buffer(p_hpac, sapaHdl, sys, sat, area, buffer, byte_pos, bit_pos)) return 0;
	}
	return rc;
}//gpp_sapa_hpac_iono_sat2buffer()

/******************************************************************************************************************************************************************
 *	\brief Read Ionospher Satellite block data from buffer
 ******************************************************************************************************************************************************************/
static GPPLONG gpp_sapa_hpac_buffer2iono_sat(pGPP_SAPA_HPAC p_hpac, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 area,const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPLONG rc=0;
	GPPUINT1 iono_block_indi = p_hpac->atmo[area]->area_def->iono_block_indicator;
	if (iono_block_indi == GPP_SAPA_HPAC_POLY_PRESENT || iono_block_indi == GPP_SAPA_HPAC_POLY_AND_GRID_PRESENT)					//1 or 2
	{
		if (rc = gpp_sapa_hpac_buffer2iono_sat_poly(p_hpac, sys, sat, area, buffer, byte_pos, bit_pos)) return 0;
		if (rc = gpp_sapa_hpac_buffer2iono_sat_coeff(p_hpac, sys, sat, area, buffer, byte_pos, bit_pos)) return 0;
	}
	if (iono_block_indi == GPP_SAPA_HPAC_POLY_AND_GRID_PRESENT)					// 2
	{
		if (rc = gpp_sapa_hpac_buffer2iono_sat_grid(p_hpac, sys, sat, area, buffer, byte_pos, bit_pos)) return 0;
	}
	return rc;
}//gpp_sapa_hpac_buffer2iono_sat()

/******************************************************************************************************************************************************************
 *	\brief Store Ionospher Satellite Polynomial block data into buffer
 ******************************************************************************************************************************************************************/

static GPPLONG gpp_sapa_hpac_iono_sat_poly2buffer(const pGPP_SAPA_HPAC p_hpac, GPPUINT1 sys,GPPUINT1 sat, GPPUINT1 area, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPUINT1 bit_id = 1;
	GPP_SAPA_HPAC_IONO_SAT_POLY *iono_poly = NULL;
	if (!(iono_poly = p_hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_sat_poly)) return GPP_SAPA_ERR_INVALID_HPAC_AREA;
	while (bit_id <= 15 && iono_poly->iono_quality >= SAPA_IONO_QUALITY[bit_id]) bit_id++;
	bit_id -= 1;
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 4, bit_id);			//SF055
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 1, iono_poly->iono_coeff_size);					//SF056
	return 0;
}//gpp_sapa_hpac_iono_sat_poly2buffer()

/******************************************************************************************************************************************************************
 *	\brief Read Ionospher Satellite Polynomial block data from buffer
 ******************************************************************************************************************************************************************/
static GPPLONG gpp_sapa_hpac_buffer2iono_sat_poly(pGPP_SAPA_HPAC p_hpac, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 area,const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPLONG rc;
	GPP_SAPA_HPAC_IONO_SAT_POLY iono_sat_poly = { 0, };
	iono_sat_poly.iono_quality=SAPA_IONO_QUALITY[gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 4)];				//SF055
	iono_sat_poly.iono_coeff_size=gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 1);								//SF056
	if(rc=gpp_sapa_hpac_add_iono_sat_poly_block(p_hpac,sys,sat,area,&iono_sat_poly)) return rc;
	return 0;
}//gpp_sapa_hpac_buffer2iono_sat_poly()

/******************************************************************************************************************************************************************
 *	\brief Store Ionospher Satellite Coefficient  block data into buffer
 ******************************************************************************************************************************************************************/
static GPPLONG gpp_sapa_hpac_iono_sat_coeff2buffer(const pGPP_SAPA_HPAC p_hpac, SAPA_HANDLE *sapaHdl, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 area, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPUINT1 coeff_size, equ_type,sz,it,iconf;
	GPPUINT8 configlist[66] = { 0, };
	GPP_SAPA_HPAC_IONO_SAT_COEFFICIENT *tpcb = NULL;
	tpcb = p_hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_sat_coeff;
	equ_type = p_hpac->atmo[area]->iono->iono_equation_type;
	gpp_sapa_get_configlist(sapaHdl->ocbHdl_bits[sys], configlist);
	iconf = configlist[configlist[0]];
	coeff_size = sapaHdl->hpacIonoHdl[sys][iconf]->iono_coeff_size;
	sz = coeff_size;
	if (equ_type >= 3) return GPP_SAPA_ERR_INVALID_IONO_EQ_TYPE;

	it = SAPA_C00_IDX;
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, SAPA_IONO_POLY_NBITS[sz][it], tpcb->liono_poly_coeff[it]);
	if (equ_type > 0) {
		it = SAPA_C01_IDX;
		gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, SAPA_IONO_POLY_NBITS[sz][it], tpcb->liono_poly_coeff[it]);
		it = SAPA_C10_IDX;
		gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, SAPA_IONO_POLY_NBITS[sz][it], tpcb->liono_poly_coeff[it]);
	}
	if (equ_type == 2) {
		it = SAPA_C11_IDX;
		gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, SAPA_TROPO_POLY_NBITS[sz][it], tpcb->liono_poly_coeff[it]);
	}
	return 0;
}//gpp_sapa_hpac_iono_sat_coeff2buffer()

/******************************************************************************************************************************************************************
 * \brief Read Ionospher Satellite Coefficient  block data from buffer
 ******************************************************************************************************************************************************************/
static GPPLONG gpp_sapa_hpac_buffer2iono_sat_coeff(pGPP_SAPA_HPAC p_hpac, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 area, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{

	GPPLONG rc;
	GPPUINT1 coeff_size, equ_type,it, grid,igrid,sz;
	GPP_SAPA_HPAC_IONO_SAT_COEFFICIENT tpcb = { 0, };
	coeff_size = p_hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_sat_poly->iono_coeff_size;
	equ_type = p_hpac->atmo[area]->iono->iono_equation_type;
	grid = p_hpac->atmo[area]->area_def->number_of_grid_point;
	for (igrid = 0; igrid <= grid; igrid++)
	{
		sz = p_hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_grid->grid;
	}
	it = SAPA_C00_IDX;
	gpp_sapa_buffer2float(buffer, byte_pos, bit_pos, SAPA_IONO_POLY_MIN[sz][it], SAPA_TROPO_POLY_NBITS[sz][it], SAPA_IONO_POLY_RES[it], NULL, &tpcb.iono_poly_coeff[it]);

	if (equ_type > 0) {
		it = SAPA_T01_IDX;
		gpp_sapa_buffer2float(buffer, byte_pos, bit_pos, SAPA_IONO_POLY_MIN[sz][it], SAPA_TROPO_POLY_NBITS[sz][it], SAPA_IONO_POLY_RES[it], NULL, &tpcb.iono_poly_coeff[it]);

		it = SAPA_T10_IDX;
		gpp_sapa_buffer2float(buffer, byte_pos, bit_pos, SAPA_IONO_POLY_MIN[sz][it], SAPA_TROPO_POLY_NBITS[sz][it], SAPA_IONO_POLY_RES[it], NULL, &tpcb.iono_poly_coeff[it]);
	}

	if (equ_type == 2) {
		it = SAPA_T11_IDX;
		gpp_sapa_buffer2float(buffer, byte_pos, bit_pos, SAPA_IONO_POLY_MIN[sz][it], SAPA_TROPO_POLY_NBITS[sz][it], SAPA_IONO_POLY_RES[it], NULL, &tpcb.iono_poly_coeff[it]);
	}
	if (rc = gpp_sapa_hpac_add_iono_sat_coeff_block(p_hpac, sys, sat, area, &tpcb)) return rc;

	return 0;
}//gpp_sapa_hpac_buffer2iono_sat_coeff()

/******************************************************************************************************************************************************************
 * \brief Store Ionospher Satellite Grid block data into buffer
 ******************************************************************************************************************************************************************/
static GPPLONG gpp_sapa_hpac_iono_sat_grid2buffer(const pGPP_SAPA_HPAC p_hpac, const SAPA_HANDLE *sapaHdl, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 area, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPUINT1 ia, areaId, arealist[258];

	if (!sapaHdl) return GPP_SAPA_ERR_INVALID_HANDLE;

	if ((sapaHdl->hpacHdl->tropo_blk_indicator & 2)) return 0; // needs to be optimized with definition

	gpp_sapa_get_arealist(sapaHdl->hpacHdl->area_bits, arealist); //identify all areas that shall be sent in this message if filled with valid values

	for (ia = 1; ia <= arealist[0]; ia++) {
		areaId = arealist[ia];

		if (GNSS_HAS_IDX_IN_BITS_64(p_hpac->atmo_bits[areaId / 64], areaId % 64)) {// have valid atmo data in hpac

			pGPP_SAPA_HPAC_ATMO_BLOCK atmo = NULL;
			pGPP_SAPA_HPAC_IONO_GRID_BLOCK grd_iono = NULL;
			GPPUINT1 igrd, sz;


			if (!(atmo = p_hpac->atmo[areaId])) return GPP_SAPA_ERROR_BASE;//double check; use error code here as this indicates an error in the add_tropo or add_iono data

			if (!atmo->iono) continue; //okay, no tropo data in hpac
			if (!(atmo->iono->iono_sat_block)) continue;
			if (!(atmo->iono->iono_sat_block[sys][sat])) continue;
			if (!(grd_iono = atmo->iono->iono_sat_block[sys][sat]->iono_grid)) continue; //okay, no tropo data in hpac

			sz = grd_iono->sz;
			gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 1, grd_iono->sz);

			for (igrd = 0; igrd < grd_iono->num_grid; igrd++) {
				if (GNSS_HAS_IDX_IN_BITS_64(grd_iono->grid_bits, igrd)) {// have valid data
					gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, SAPA_IONO_GRD_NBITS[sz], grd_iono->grid[igrd]->lval);
				}
				else {
					gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, SAPA_IONO_GRD_NBITS[sz], SAPA_IONO_GRD_INVALID[sz]);
				}
			}
		}
	}//for loop ia
	return 0;
}//gpp_sapa_hpac_iono_sat_grid2buffer()

/******************************************************************************************************************************************************************
 * \brief Read Ionospher Satellite Grid block data from buffer
 ******************************************************************************************************************************************************************/
static GPPLONG gpp_sapa_hpac_buffer2iono_sat_grid(pGPP_SAPA_HPAC hpac, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 area, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos) {
	GPP_SAPA_USE_STATES states = { 0, };
	GPP_SAPA_HPAC_IONO_GRID_BLOCK iono_grid_block = { 0, };
	GPP_SAPA_HPAC_IONO_GRD_CORRECTION iono_grd = { 0, };
	GPPUINT1 ia, igrd, size, no_of_grid, iono_indi, sz, lvalue;
	GPPUINT1 *isValid;
	pGPP_SAPA_HPAC_ATMO_BLOCK atmo = NULL;
	iono_indi = hpac->atmo[area]->area_def->iono_block_indicator;

	if (iono_indi != 2) return 0; // needs to be optimized with definition
	atmo = hpac->atmo[area];
	iono_grid_block.sz = atmo->iono->iono_sat_block[sys][sat]->iono_grid->sz;
	sz = iono_grid_block.sz;

	no_of_grid = hpac->atmo[area]->area_def->number_of_grid_point;

	for (igrd = 0; igrd < no_of_grid; igrd++) {
		GPPULONG rc;
		lvalue = gpp_sapa_buffer2float(buffer, byte_pos, bit_pos, SAPA_IONO_GRD_MIN[sz], SAPA_IONO_GRD_NBITS[sz], SAPA_IONO_GRD_RES, &SAPA_IONO_RESIDUAL_SLANT_INVALID[sz], &iono_grd.val); //SF064
		isValid = &lvalue;
		if (rc = gpp_sapa_hpac_add_grd_iono_correction(&states, area, igrd, sat, sys, &iono_grd))
			return rc;
		if (isValid)
			GNSS_SET_IDX_IN_BITS_64(hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_grid->grid_bits, igrd);
	}
	return 0;
}