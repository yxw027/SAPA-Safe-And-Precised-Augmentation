/*
 Write and read SAPA OCB format to and from buffer
*/
#include <stdio.h>
//#include "platform.h"

#include "gpp_sapa.h"
#include "bit2buff.h"


#define SAPA_RES_AREA_REF_LATITUDE	0.1
#define SAPA_RES_AREA_REF_LONGITUDE 0.1
#define SAPA_RES_AREA_GRID_LATITUDE_SPACING	 0.1
#define SAPA_RES_AREA_GRID_LONGITUDE_SPACING 0.1

GPPUINT2 *invalid_area = 0;



//------------------------------------------- Declaration of functions to store data in Buffer for Area----------------------------------------
static GPPLONG gpp_sapa_area_header2buffer(const pGPP_SAPA_AREA p_area, const SAPA_GAD_HANDLE *gadHdl, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_area_area2buffer(const pGPP_SAPA_AREA p_area, GPPUINT1 area, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);

//-----------------------------------------Declaration of functions to read data from buffer for Area-----------------------------------------
static GPPLONG gpp_sapa_area_buffer2header(pGPP_SAPA_AREA p_area, GPPUINT1 *no_of_areas, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_area_buffer2area(pGPP_SAPA_AREA p_area, GPPUINT1 area, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);


/**************************************************************************
 *	\brief Write SAPA Area Dedination message to buffer
 *
 *	\param[in] 	p_area 	Pointer to GPP_SAPA_AREA structure
 *	\param[in]	sys		GNSS indicator
 *	\param[in]	*buffer
 *	\param[in]	*byte_pos
 *	\param[in]	*bit_pos
 *
 *	\retval 	Number of needed bits
 *	\retval 	Error Code
 *************************************************************************/
GPPLONG gpp_sapa_area2buffer(const pGPP_SAPA_AREA p_area, const SAPA_GAD_HANDLE *gadHdl,GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPLONG rc;

	GPPUINT1 ia,no_of_areas;

	GPPLONG byte_pos0, bit_pos0;
	GPPLONG mybyte = 0, mybit = 0;

	if (!byte_pos) byte_pos = &mybyte;
	if (!bit_pos) bit_pos = &mybit;

	byte_pos0 = *byte_pos;
	bit_pos0 = *bit_pos;

	if (!p_area) return GPP_SAPA_ERR_INVALID_AREA;
	if (!gadHdl) return GPP_SAPA_ERR_INVALID_GAD_HANDLE;

	if (rc = gpp_sapa_area_header2buffer(p_area, gadHdl, buffer, byte_pos, bit_pos)) return rc;
	no_of_areas = p_area->header_block->area_count;
	for (ia = 0; ia < no_of_areas; ia++) {
		if(rc=gpp_sapa_area_area2buffer(p_area,ia, buffer, byte_pos, bit_pos)) return rc;
	}

	return  gpp_sapa_get_bit_diff(*byte_pos, *bit_pos, byte_pos0, bit_pos0);
}//gpp_sapa_ocb2buffer()

/**************************************************************************
 *	\brief Read SAPA Area message from buffer
 *
 *	\param[in] 	p_OCB 	Pointer to GPP_SAPA_AREA structure
 *	\param[in]	sys		GNSS indicator
 *	\param[in]	*buffer
 *	\param[in]	*byte_pos
 *	\param[in]	*bit_pos
 *
 *	\retval 	Number of read bits
 *	\retval 	Error Code
 *************************************************************************/
GPPLONG gpp_sapa_buffer2area(pGPP_SAPA_AREA p_area, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPLONG rc;
	GPPUINT1 ia, no_of_areas;
	GPPLONG byte_pos0, bit_pos0;
	GPPLONG mybyte = 0, mybit = 0;

	if (!byte_pos) byte_pos = &mybyte;
	if (!bit_pos) bit_pos = &mybit;

	byte_pos0 = *byte_pos;
	bit_pos0 = *bit_pos;

	if (rc = gpp_sapa_area_buffer2header(p_area, &no_of_areas, buffer, byte_pos, bit_pos)) return rc;

	for (ia = 0; ia < no_of_areas; ia++) {
			if (rc = gpp_sapa_area_buffer2area(p_area,ia, buffer, byte_pos, bit_pos)) return rc;
	}

	return  gpp_sapa_get_bit_diff(*byte_pos, *bit_pos, byte_pos0, bit_pos0);
}//gpp_sapa_buffer2area()

/******************************************************************************
 *	\brief Write OCB header to buffer
 *
 *	\param[in]	p_area
 *	\param[in]	sys
 *	\param[in]	*buffer
 *	\param[in]	*byte_pos
 *	\param[in]	*bit_pos
 *
 *	\retval 0 Ok
 *	\retval Error Code
 ******************************************************************************/
static GPPLONG gpp_sapa_area_header2buffer(const pGPP_SAPA_AREA p_area, const SAPA_GAD_HANDLE *gadHdl, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPP_SAPA_AREA_DEF_HEADER *header = p_area->header_block;
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 4, header->message_sub_type);								//SF001
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 7, header->sol_id);											//SF006
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 4, header->sol_processor_id);								//SF007
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 9, header->sol_issue_of_update);						    //SF005
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 4, gadHdl->area_issue_of_update);
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 1, gadHdl->reserved);
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 5, header->area_count);										//SF030
	return 0;
}//gpp_sapa_area_header2buffer()

/******************************************************************************
 *	\brief Read Area header from buffer
 *
 *	\param[in]	p_area
 *	\param[in]	sys
 *	\param[in]	*buffer
 *	\param[in]	*byte_pos
 *	\param[in]	*bit_pos
 *
 *	\retval 0 Ok
 *	\retval Error Code
 ******************************************************************************/
static GPPLONG gpp_sapa_area_buffer2header(pGPP_SAPA_AREA p_area, GPPUINT1 *no_of_areas, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPLONG rc;
	GPP_SAPA_AREA_DEF_HEADER header = { 0, };
	header.message_sub_type=gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 4);													//SF001
	header.sol_id=gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 7);															//SF006
	header.sol_processor_id=gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 4);													//SF007
	header.sol_issue_of_update=gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 9);												//SF005
	header.area_issue_of_update = gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 4);											//SF068
	header.reserved = gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 1);														//SF069
	header.area_count=gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 5);														//SF030
	*no_of_areas = header.area_count;
	if (rc = gpp_sapa_area_add_header(p_area, &header)) return rc;
	return 0;
}//gpp_sapa_area_buffer2header

/******************************************************************************
 *	\brief Store area defination block data into buffer
 ******************************************************************************/
static GPPLONG gpp_sapa_area_area2buffer(const pGPP_SAPA_AREA p_area, GPPUINT1 area, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPP_SAPA_AREA_DEF_BLOCK *area_def = p_area->area_def_block[area];
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 8, area_def->area_id);																//SF031
	gpp_sapa_float2buffer(buffer, byte_pos, bit_pos, GPP_SAPA_AREA_REF_LAT_MIN, GPP_SAPA_AREA_REF_LAT_MAX,11, SAPA_RES_AREA_REF_LATITUDE,&invalid_area, area_def->area_ref_lat);							//SF032
	gpp_sapa_float2buffer(buffer, byte_pos, bit_pos, GPP_SAPA_AREA_REF_LONG_MIN, GPP_SAPA_AREA_REF_LONG_MAX, 12,SAPA_RES_AREA_REF_LONGITUDE,&invalid_area, area_def->area_ref_long);						//SF033
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 3, p_area->area_def_block[area]->area_lat_grid_node_count);												//SF034
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 3, p_area->area_def_block[area]->area_long_grid_node_count);												//SF035
	gpp_sapa_float2buffer(buffer, byte_pos, bit_pos, GPP_SAPA_AREA_GRID_LAT_SPACING_MIN, GPP_SAPA_AREA_GRID_LAT_SPACING_MAX,5,SAPA_RES_AREA_GRID_LATITUDE_SPACING,&invalid_area, area_def->area_lat_grid_node_spacing);	//SF036
	gpp_sapa_float2buffer(buffer, byte_pos, bit_pos, GPP_SAPA_AREA_GRID_LONG_SPACING_MIN,GPP_SAPA_AREA_GRID_LONG_SPACING_MAX,5,SAPA_RES_AREA_GRID_LONGITUDE_SPACING,&invalid_area, area_def->area_long_grid_node_spacing);//SF037
	return 0;
}

/******************************************************************************
 *	Read area defination block data into buffer
 ******************************************************************************/
static GPPLONG gpp_sapa_area_buffer2area(const pGPP_SAPA_AREA p_area, GPPUINT1 area, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPLONG rc;
	GPP_SAPA_AREA_DEF_BLOCK area_def = { 0, };
	area_def.area_id=gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 8);																				//SF031
	area_def.area_ref_lat= gpp_sapa_buffer2float(buffer, byte_pos, bit_pos,GPP_SAPA_AREA_REF_LAT_MIN, 11, SAPA_RES_AREA_REF_LATITUDE,&invalid_area);											//SF032
	area_def.area_ref_long= gpp_sapa_buffer2float(buffer, byte_pos, bit_pos, GPP_SAPA_AREA_REF_LONG_MIN,12, SAPA_RES_AREA_REF_LONGITUDE,&invalid_area);										//SF033
	area_def.area_lat_grid_node_count=gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 3);																//SF034
	area_def.area_long_grid_node_count=gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 3);																//SF035
	area_def.area_lat_grid_node_spacing= gpp_sapa_buffer2float(buffer, byte_pos, bit_pos, GPP_SAPA_AREA_GRID_LAT_SPACING_MIN, 5, SAPA_RES_AREA_GRID_LATITUDE_SPACING, &invalid_area);					//SF036
	area_def.area_long_grid_node_spacing= gpp_sapa_buffer2float(buffer, byte_pos, bit_pos, GPP_SAPA_AREA_GRID_LONG_SPACING_MIN, 5, SAPA_RES_AREA_GRID_LONGITUDE_SPACING, &invalid_area);				    //SF037
	if(rc=gpp_sapa_area_add_area_def(p_area, area, &area_def)) return rc;
	return 0;
}
