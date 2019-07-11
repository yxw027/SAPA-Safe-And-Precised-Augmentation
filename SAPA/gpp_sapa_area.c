/*
 Write and read SAPA OCB format to and from buffer
*/
#include <stdio.h>
//#include "platform.h"

#include "gpp_sapa.h"
#include "bit2buff.h"



//------------------------------------------- Declaration of functions to store data in Buffer for Area----------------------------------------
static GPPLONG gpp_sapa_area_header2buffer(const pGPP_SAPA_AREA p_area, const SAPA_GAD_HANDLE *gadHdl, GPPUINT1 *arealist,GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_area_area2buffer(const pGPP_SAPA_AREA p_area, GPPUINT1 area, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);

//-----------------------------------------Declaration of functions to read data from buffer for Area-----------------------------------------
static GPPLONG gpp_sapa_area_buffer2header(pGPP_SAPA_AREA p_area, GPPUINT1 *arealist, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_area_buffer2area(const pGPP_SAPA_AREA p_area, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);

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

	GPPUINT1 ia, arealist[258] = { 0, }; //256+2

	GPPLONG byte_pos0, bit_pos0;
	GPPLONG mybyte = 0, mybit = 0;
	if (!byte_pos) byte_pos = &mybyte;
	if (!bit_pos) bit_pos = &mybit;

	byte_pos0 = *byte_pos;
	bit_pos0 = *bit_pos;

	if (!p_area) return GPP_SAPA_ERR_INVALID_AREA;
	if (!gadHdl) return GPP_SAPA_ERR_INVALID_GAD_HANDLE;

	if (rc = gpp_sapa_area_header2buffer(p_area, gadHdl, &arealist, buffer, byte_pos, bit_pos)) return rc;
	for (ia = 1; ia <= arealist[0]; ia++) {
		GPPUINT1 area;
		area = arealist[ia];
		//printf("\n area=%d",arealist[0]);
		if(rc=gpp_sapa_area_area2buffer(p_area, area, buffer, byte_pos, bit_pos)) return rc;
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
	GPPUINT1 ia, arealist[258] = { 0, }; //256+2
	GPPLONG byte_pos0, bit_pos0;
	GPPLONG mybyte = 0, mybit = 0;
	GPPUINT1 area_count;

	if (!byte_pos) byte_pos = &mybyte;
	if (!bit_pos) bit_pos = &mybit;

	byte_pos0 = *byte_pos;
	bit_pos0 = *bit_pos;

	if (rc = gpp_sapa_area_buffer2header(p_area, &area_count, buffer, byte_pos, bit_pos)) return rc;

	for (ia = 1; ia <= area_count; ia++) {
			if (rc = gpp_sapa_area_buffer2area(p_area, buffer, byte_pos, bit_pos)) return rc;
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
static GPPLONG gpp_sapa_area_header2buffer(const pGPP_SAPA_AREA p_area, const SAPA_GAD_HANDLE *gadHdl, GPPUINT1 *arealist, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPP_SAPA_AREA_DEF_HEADER *header = p_area->header_block;
	printf("\nmessage sub type=%d", header->message_sub_type);
	printf("\nsol_id=%d", header->sol_id);
	printf("\nsol_processor_id=%d", header->sol_processor_id);
	printf("\nsol_issue_of_update=%d", header->sol_issue_of_update);
	printf("\narea_issue_of_update=%d", header->area_issue_of_update);
	printf("\nreserved=%d", header->reserved);
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 4, header->message_sub_type);    //SF001
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 7, header->sol_id);      //SF006
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 4, header->sol_processor_id);    //SF007
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 9, header->sol_issue_of_update);   //SF005
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 4, header->area_issue_of_update);
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 1, header->reserved);

	gpp_sapa_get_arealist(gadHdl->area_bits, arealist);

	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 5, arealist[0]);     //SF030
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
static GPPLONG gpp_sapa_area_buffer2header(pGPP_SAPA_AREA p_area, GPPUINT1 *area_count, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
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
	*area_count = header.area_count;
	printf("\n--------message sub type=%d", header.message_sub_type);
	printf("\n--------sol_id=%d", header.sol_id);
	printf("\n--------sol_processor_id=%d", header.sol_processor_id);
	printf("\n---------sol_issue_of_update=%d", header.sol_issue_of_update);
	printf("\n---------area_issue_of_update=%d", header.area_issue_of_update);
	printf("\n----------reserved=%d", header.reserved);

	if (rc = gpp_sapa_area_add_header(p_area, &header)) return rc;
	return 0;
}//gpp_sapa_area_buffer2header

/******************************************************************************
 *	\brief Store area defination block data into buffer
 ******************************************************************************/
static GPPLONG gpp_sapa_area_area2buffer(const pGPP_SAPA_AREA p_area, GPPUINT1 area, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPP_SAPA_AREA_DEF_BLOCK *area_def;
	if (!(area_def = p_area->area_def_block[area])) return GPP_SAPA_ERR_INVALID_AREA;
	printf("\narea_id=%d", area_def->area_id);
	printf("\nlarea_ref_lat=%d", area_def->larea_ref_lat);
	printf("\nlarea_ref_long=%d", area_def->larea_ref_long);
	printf("\narea_lat_grid_node_count=%d", area_def->area_lat_grid_node_count);
	printf("\narea_long_grid_node_count=%d", area_def->area_long_grid_node_count);
	printf("\nlarea_lat_grid_node_spacing=%d", area_def->larea_lat_grid_node_spacing);
	printf("\nlarea_long_grid_node_spacing=%d", area_def->larea_long_grid_node_spacing);
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 8, area_def->area_id);                //SF031
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 11, area_def->larea_ref_lat);                //SF032
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 12, area_def->larea_ref_long);                //SF033
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 3, area_def->area_lat_grid_node_count);            //SF034
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 3, area_def->area_long_grid_node_count);            //SF035
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 5, area_def->larea_lat_grid_node_spacing);                //SF036
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 5, area_def->larea_long_grid_node_spacing);                //SF037

	
	return 0;
}
/******************************************************************************
 *	Read area defination block data into buffer
 ******************************************************************************/
static GPPLONG gpp_sapa_area_buffer2area(const pGPP_SAPA_AREA p_area, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPLONG rc;
	GPP_SAPA_AREA_DEF_BLOCK area_def = { 0, };
	GPPUINT1 area;

	area_def.area_id = gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 8);                   //SF031
	area = area_def.area_id;
	gpp_sapa_buffer2float(buffer, byte_pos, bit_pos, SAPA_AREA_LAT_MIN, 11, SAPA_RES_AREA_REF_LATITUDE, NULL, &area_def.area_ref_lat);           //SF032
	gpp_sapa_buffer2float(buffer, byte_pos, bit_pos, SAPA_AREA_LONG_MIN, 12, SAPA_RES_AREA_REF_LONGITUDE, NULL, &area_def.area_ref_long);          //SF033
	area_def.area_lat_grid_node_count = gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 3);                //SF034
	area_def.area_long_grid_node_count = gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, 3);
	gpp_sapa_buffer2float(buffer, byte_pos, bit_pos, SAPA_AREA_GRD_LAT_MIN, 5, SAPA_RES_AREA_GRID_LATITUDE_SPACING, NULL, &area_def.area_lat_grid_node_spacing);     //SF036
	gpp_sapa_buffer2float(buffer, byte_pos, bit_pos, SAPA_AREA_GRD_LONG_MIN, 5, SAPA_RES_AREA_GRID_LONGITUDE_SPACING, NULL, &area_def.area_long_grid_node_spacing);        //SF037
	printf("\n-----------area_id=%d", area_def.area_id);
	printf("\n---------area_ref_lat=%f", area_def.area_ref_lat);
	printf("\n---------area_ref_long=%f", area_def.area_ref_long);
	printf("\n----------area_lat_grid_node_count=%d", area_def.area_lat_grid_node_count);
	printf("\n-----------area_long_grid_node_count=%d", area_def.area_long_grid_node_count);
	printf("\n-------------area_lat_grid_node_spacing=%f", area_def.area_lat_grid_node_spacing);
	printf("\n------------area_long_grid_node_spacing=%f", area_def.area_long_grid_node_spacing);
	if (rc = gpp_sapa_area_add_area_def(p_area, area, &area_def)) return rc;

	return 0;
}