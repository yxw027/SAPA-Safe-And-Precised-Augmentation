
#ifndef GPP_SAPA_H
#define GPP_SAPA_H
/************************************************* * GPS Week and Second of 2010/01/01 00:00:00 UTC
*****************************************/
#define SAPA_GPS_WEEK_20100101 1564
#define SAPA_GPS_SEC_20100101 432000
#include "gpptime.h"
#include "compiler.h" //GPP types
#define GPP_SAPA_MAX_SIG    32  /* SF027, SF028 (okay although only 10 bits needed) */

#include <stdlib.h>
#include <stdio.h>
/*******************************************
 * SAPA specific parameters
 *******************************************/
#define GPP_SAPA_MAX_CONS   16  /* Constellation*/
#define GPP_SAPA_MAX_SYS	16
#define GPP_SAPA_MAX_SAT    64  /* SF011, SF012 (special values) */

#define GPP_SAPA_MAX_AREA_COUNT 32
#define GPP_SAPA_MAX_GRID_POINT_PRESENT 64

#define GPP_SAPA_OCB_FLAG_IDX_ORB 	0
#define GPP_SAPA_OCB_FLAG_IDX_CLK 	1
#define GPP_SAPA_OCB_FLAG_IDX_BIAS 	2

#define GPP_SAPA_GPS 0
#define GPP_SAPA_GLO 1
#define GNSS_HOURLY_TIME_TAG  0
#define GNSS_FULL_TIME_TAG	1
#define GPP_SAPA_SAT_PRESENT 0
#define GPP_SAPA_OCB_FLAG_PRESENT 1
#define GPP_SAPA_YAW_FLAG_PRESENT 1

/******************************************
  *	GPP SAPA ERROR Codes
  ******************************************/
#define GPP_SAPA_OK 						0
#define GPP_SAPA_ERROR_BASE 				-54000
#define GPP_SAPA_ERR_NOT_YET_IMPLEMENTED	(GPP_SAPA_ERROR_BASE-1)		/* -54001 */
#define GPP_SAPA_ERR_NOT_ENOUGH_MEMORY		(GPP_SAPA_ERROR_BASE-2)		/* -54002 */
#define GPP_SAPA_ERR_INVALID_OCB			(GPP_SAPA_ERROR_BASE-3)		/* -54003 */
#define GPP_SAPA_ERR_INVALID_OCB_SV			(GPP_SAPA_ERROR_BASE-4)		/* -54004 */
#define GPP_SAPA_ERR_INVALID_OCB_SV_ORB		(GPP_SAPA_ERROR_BASE-5)		/* -54005 */
#define GPP_SAPA_ERR_INVALID_OCB_SV_CLK		(GPP_SAPA_ERROR_BASE-6)		/* -54006 */
#define GPP_SAPA_ERR_INVALID_OCB_SV_PB		(GPP_SAPA_ERROR_BASE-7)		/* -54007 */
#define GPP_SAPA_ERR_INVALID_OCB_SV_CB		(GPP_SAPA_ERROR_BASE-8)		/* -54008 */
#define GPP_SAPA_ERR_INVALID_SVLIST			(GPP_SAPA_ERROR_BASE-9)		/* -54009 */
#define GPP_SAPA_ERR_INVALID_SIGLIST		(GPP_SAPA_ERROR_BASE-10)	/* -540010 */
#define GPP_SAPA_ERR_INVALID_CB_SIG		 	(GPP_SAPA_ERROR_BASE-11)		/*	-54011	*/
#define GPP_SAPA_ERR_INVALID_HPAC_AREA	 	(GPP_SAPA_ERROR_BASE-12)		/*	-54012	*/
#define GPP_SAPA_ERR_INVALID_HPAC_HEADER 	(GPP_SAPA_ERROR_BASE-13)		/*	-54013	*/
#define GPP_SAPA_ERR_INVALID_AREA	 		(GPP_SAPA_ERROR_BASE-14)		/*	-54014	*/
#define GPP_SAPA_ERR_INVALID_META	 		(GPP_SAPA_ERROR_BASE-15)		/*	-54015	*/


#define GPP_SAPA_ERR_PREAMBLE				(GPP_SAPA_ERROR_BASE-100) /* -54100	*/
#define GPP_SAPA_ERR_TYPE					(GPP_SAPA_ERROR_BASE-101) /* -54101	*/
#define GPP_SAPA_ERR_PAYLOAD_LENGTH			(GPP_SAPA_ERROR_BASE-102) /* -54102	*/
#define GPP_SAPA_ERR_CRC_TYPE				(GPP_SAPA_ERROR_BASE-103) /* -54103	*/
#define GPP_SAPA_ERR_CRC_FRAME				(GPP_SAPA_ERROR_BASE-104) /* -54104	*/

//#define length_bytes_from_bits(b) (((b)/8)+((b)%8?1:0))
#define SAPA_PREAMBLE 0x73	// First 8 bits in SAPA frame
#define SAPA_TYPE_OCB				0
#define SAPA_TYPE_HPAC				1
#define SAPA_TYPE_HPAC_AREA_DEF		2

#define SAPA_CONST_LEN_BYTES_BASE		32
#define SAPA_CONST_LEN_BYTES_CRC_8		8
#define SAPA_CONST_LEN_BYTES_CRC_16		16
#define SAPA_CONST_LEN_BYTES_CRC_24		24
#define SAPA_CONST_LEN_BYTES_CRC_32		32

#define SAPA_SV_IODE_LEN_GPS	8
#define SAPA_SV_IODE_LEN_GLO 	7

#define SAPA_RES_SV_CORRECTION 	0.002
#define SAPA_RES_PB_CORRECTION 	0.002
#define SAPA_RES_CB_CORRECTION 	0.02

#define SAPA_RES_AREA_AVG_VER_HEDRO_DELAY 0.004
#define SAPA_RES_TROPO_RESIDUAL_DELAY 0.004
#define SAPA_RES_IONO_RESIDUAL_DELAY 0.04

#define	SAPA_RES_TROPO_POLY_COEFF_T00 0.004
#define	SAPA_RES_TROPO_POLY_COEFF_T01 0.001
#define	SAPA_RES_TROPO_POLY_COEFF_T11 0.0002

#define	SAPA_RES_IONO_POLY_COEFF_C00 0.04
#define	SAPA_RES_IONO_POLY_COEFF_C01 0.008
#define	SAPA_RES_IONO_POLY_COEFF_C11 0.002

#define TROPO_POLY_COEFF_INDX_T00 0
#define TROPO_POLY_COEFF_INDX_T01 1
#define TROPO_POLY_COEFF_INDX_T10 2
#define TROPO_POLY_COEFF_INDX_T11 3

#define IONO_POLY_COEFF_INDX_C00 0
#define IONO_POLY_COEFF_INDX_C01 1
#define IONO_POLY_COEFF_INDX_C10 2
#define IONO_POLY_COEFF_INDX_C11 3

#define SAPA_SMALL_TROPO_RESIDUAL_ZENITH_DELAY	6
#define SAPA_LARGE_TROPO_RESIDUAL_ZENITH_DELAY	8

#define SAPA_SMALL_IONO_RESIDUAL_SLANT_DELAY	4
#define SAPA_MEDIUM_IONO_RESIDUAL_SLANT_DELAY	7
#define SAPA_LARGE_IONO_RESIDUAL_SLANT_DELAY	10
#define SAPA_EXTRA_LARGE_IONO_RESIDUAL_SLANT_DELAY 14

#define SAPA_RES_AREA_REF_LATITUDE	0.1
#define SAPA_RES_AREA_REF_LONGITUDE 0.1
#define SAPA_RES_AREA_GRID_LATITUDE_SPACING	 0.1
#define SAPA_RES_AREA_GRID_LONGITUDE_SPACING 0.1


static const GPPUINT1 SAPA_SV_IODE_LEN[GPP_SAPA_MAX_SYS]={SAPA_SV_IODE_LEN_GPS, SAPA_SV_IODE_LEN_GLO,};

static const GPPLONG SAPA_SV_BITMASK_LEN_GPS[4]={32, 44, 56, 64};
static const GPPLONG SAPA_SV_BITMASK_LEN_GLO[4]={24, 36, 48, 63};
static const GPPLONG *SAPA_SV_BITMASK_LEN[2]={SAPA_SV_BITMASK_LEN_GPS, SAPA_SV_BITMASK_LEN_GLO};

static const GPPLONG SAPA_BIAS_BITMASK_LEN_GPS[2] = { 6, 11 };
static const GPPLONG SAPA_BIAS_BITMASK_LEN_GLO[2] = { 5, 9 };
static const GPPUINT1 *SAPA_BIAS_BITMASK_LEN[2] = { SAPA_BIAS_BITMASK_LEN_GPS, SAPA_BIAS_BITMASK_LEN_GLO };

static const GPPDOUBLE SAPA_CONTI_ID[8] = { 0.0,1.0, 5.0, 10.0, 30.0, 60.0, 120.0, 320.0 };
static const GPPDOUBLE SAPA_USER_RANGE_ERROR[8] = { 0.00,0.01, 0.02,0.05, 0.10, 0.30, 1.00,1.00 };
static const GPPDOUBLE SAPA_IONO_QUALITY[16] = { 0.00,0.03, 0.05,0.07, 0.14, 0.28, 0.56,1.12,2.24,4.48,8.96,17.92,35.84,71.68,143.36,143.36 };
static const GPPDOUBLE SAPA_TROPO_QUALITY[8] = { 0.0,0.010,0.020,0.040,0.080,0.160,0.320,0.320 };

static const GPPUINT1 SAPA_TROPO_RESIDUAL_ZENITH_DELAY[2] = { SAPA_SMALL_TROPO_RESIDUAL_ZENITH_DELAY, SAPA_LARGE_TROPO_RESIDUAL_ZENITH_DELAY };
static const GPPUINT1 SAPA_IONO_RESIDUAL_SLANT_DELAY[4] = { SAPA_SMALL_IONO_RESIDUAL_SLANT_DELAY,SAPA_MEDIUM_IONO_RESIDUAL_SLANT_DELAY,SAPA_LARGE_IONO_RESIDUAL_SLANT_DELAY ,SAPA_EXTRA_LARGE_IONO_RESIDUAL_SLANT_DELAY };

static const long sapa_const_crc_bytes[4] = { 8,16,24,32 };

static const GPPLONG SAPA_TROPO_COEFF_T012[2] = { 7,9 };
static const GPPLONG SAPA_TROPO_COEFF_T3[2] = { 9,11};
static const GPPLONG *SAPA_TROPO_COEFF[4] = { SAPA_TROPO_COEFF_T012,SAPA_TROPO_COEFF_T012,SAPA_TROPO_COEFF_T012 ,SAPA_TROPO_COEFF_T3 };

static const GPPLONG SAPA_IONO_COEFF_C012[2] = { 12,14 };
static const GPPLONG SAPA_IONO_COEFF_C3[2] = { 13,15 };
static const GPPLONG *SAPA_IONO_COEFF[4] = { SAPA_IONO_COEFF_C012,SAPA_IONO_COEFF_C012,SAPA_IONO_COEFF_C012 ,SAPA_IONO_COEFF_C3 };
//============================================= OCB Structures ============================================================================================================================
typedef struct GPP_SAPA_OCB_HEADER {
	GPPUINT1		message_sub_type;														//SF001	       -- first charcter of satellite ID
	GPPUINT1		time_tag_type;															//SF002		   -- can be 0 or 1,will be set manually in the code
	GPPUINT4		time_tag;																//SF003orSF004 -- <ascii_in>.ocb's OCB_COMMON_INFO[2]
	GPPUINT4		sys_id;																	//SF006		   -- <ascii_in>.ocb's OCB_COMMON_INFO[3]
	GPPUINT4		sys_processor_id;														//SF007        -- <ascii_in>.ocb's OCB_COMMON_INFO[4]
	GPPUINT4		sol_issue_of_update;													//SF005        -- <ascii_in>.ocb's OCB_COMMON_INFO[5]
	GPPUINT1		end_of_obc_set;															//SF010        -- will be set in the code
	GPPUINT1		yaw_flag;																//SF008        -- <ascii_in>.ocb's OCB_COMMON_INFO[7]
	GPPUINT1		sat_ref_datum;															//SF009        -- <ascii_in>.ocb's OCB_COMMON_INFO[6]
	GPPUINT1		ephemeris_type;															//SF016orSF017 -- <ascii_in>.ocb's OCB_COMMON_INFO[8]
} GPP_SAPA_OCB_HEADER, *pGPP_SAPA_OCB_HEADER;

typedef struct GPP_SAPA_OCB_SV_ORB {
	GPPUINT4		iode;																	//SF018orSF019 -- <ascii_in>.ocb's OCB_SATELLITE_DATA[7]
	GPPDOUBLE		orb_radial_correction;													//SF020		   -- <ascii_in>.ocb's OCB_SATELLITE_DATA[9]
	GPPDOUBLE		orb_along_track_correction;												//SF020		   -- <ascii_in>.ocb's OCB_SATELLITE_DATA[10]
	GPPDOUBLE		orb_cross_track_correction;												//SF020        -- <ascii_in>.ocb's OCB_SATELLITE_DATA[11]
	GPPDOUBLE		sat_yaw;																//SF021        -- <ascii_in>.ocb's OCB_SATELLITE_DATA[13]
} GPP_SAPA_OCB_SV_ORB, *pGPP_SAPA_OCB_SV_ORB;

typedef struct GPP_SAPA_OCB_SV_CLK {
	GPPDOUBLE		iode_continuity;														//SF022        -- <ascii_in>.ocb's OCB_SATELLITE_DATA[8]
	GPPDOUBLE		clk_correction;															//SF020        -- <ascii_in>.ocb's OCB_SATELLITE_DATA[14]
	GPPDOUBLE		user_range_error;														//SF024        -- <ascii_in>.ocb's OCB_SATELLITE_DATA[15]
} GPP_SAPA_OCB_SV_CLK, *pGPP_SAPA_OCB_SV_CLK;

typedef struct GPP_SAPA_OCB_SV_BIAS_PB
{
	GPPUINT1		fix_flag;																//SF023        -- <ascii_in>.ocb's OCB_SATPHASE_BIAS[3]
	GPPDOUBLE		countinity_indicator;													//SF015        -- <ascii_in>.ocb's OCB_SATPHASE_BIAS[4]
	GPPDOUBLE		pb_correction;															//SF020        -- <ascii_in>.ocb's OCB_SATPHASE_BIAS[2]
} GPP_SAPA_OCB_SV_BIAS_PB, *pGPP_SAPA_OCB_SV_BIAS_PB;

typedef struct GPP_SAPA_OCB_SV_BIAS_CB {
	GPPDOUBLE		cb_correction;															//SF029        -- <ascii_in>.ocb's OCB_SATCODE_BIAS[2]
} GPP_SAPA_OCB_SV_BIAS_CB, *pGPP_SAPA_OCB_SV_BIAS_CB;

typedef struct GPP_SAPA_OCB_SV_BIAS {
	GPPUINT4					pb_sig_bits;												//to control the phase bias signals (SF025, SF026)
	pGPP_SAPA_OCB_SV_BIAS_PB	*pb;														//PhaseBias
	GPPUINT4					cb_sig_bits;												//control Code Bias (SF027)
	pGPP_SAPA_OCB_SV_BIAS_CB	*cb;														//CodeBias
} GPP_SAPA_OCB_SV_BIAS, *pGPP_SAPA_OCB_SV_BIAS;


typedef struct GPP_SAPA_OCB_SV {
    pGPP_SAPA_OCB_SV_ORB		orb;														//Orbit 
    pGPP_SAPA_OCB_SV_CLK		clk;														//Clock
    pGPP_SAPA_OCB_SV_BIAS		bias;														//Bias
	GPPUINT1					do_not_use;													//SF013       -- <ascii_in>.ocb's OCB_SATELLITE_DATA[2]
	GPPUINT1					ocb_present_flag;											//SF014       -- <ascii_in>.ocb's OCB_SATELLITE_DATA[3]
	GPPDOUBLE					continuity_indicator;										//SF015       -- <ascii_in>.ocb's OCB_SATELLITE_DATA[6]
} GPP_SAPA_OCB_SV, *pGPP_SAPA_OCB_SV;

typedef struct GPP_SAPA_OCB {
	GPPUINT8					sv_prn_bits[GPP_SAPA_MAX_CONS];
	pGPP_SAPA_OCB_HEADER		*header_block;												//Header Block
    pGPP_SAPA_OCB_SV			**sv;														//get access via sv[cons][sat]; cons=GPS,GLO; sat=0,1,2,...N
}GPP_SAPA_OCB, *pGPP_SAPA_OCB;
//-------------------------------------------------------------------------------------------------------

//============================================= HPAC Structures =========================================

typedef struct GPP_SAPA_HPAC_HEADER {
	GPPUINT1		message_sub_type;														//SF001	        -- first charcter of satellite ID
	GPPUINT1		time_tag_type;															//SF002			-- can be 0 or 1,will be set manually in the code
	GPPUINT4		time_tag;																//SF003orSF004	-- <ascii_in>.atm's ATM_HPAC_HEADER[1] & ATM_HPAC_HEADER[2]
	GPPUINT4		sys_id;																	//SF006			-- <ascii_in>.atm's ATM_HPAC_HEADER[3]
	GPPUINT4		sys_processor_id;														//SF007			-- <ascii_in>.atm's ATM_HPAC_HEADER[4]
	GPPUINT4		sol_issue_of_update;													//SF005			-- <ascii_in>.atm's ATM_HPAC_HEADER[5]
	GPPUINT1        area_count;																//SF030			-- 
} GPP_SAPA_HPAC_HEADER, *pGPP_SAPA_HPAC_HEADER;

typedef struct GPP_SAPA_HPAC_AREA {
	GPPUINT4		area_id;																//SF031			-- <ascii_in>.atm's ATM_HPAC_COMMON_DATA[1]
	GPPDOUBLE		area_continuity_indicator;												//SF015			-- <ascii_in>.atm's ATM_HPAC_COMMON_DATA[2]
	GPPUINT1		number_of_grid_point;													//SF039			--
	GPPUINT1		tropo_block_indicator;													//SF040			-- <ascii_in>.atm's ATM_HPAC_COMMON_DATA[3]
	GPPUINT1		iono_block_indicator;													//SF040			-- <ascii_in>.atm's ATM_HPAC_COMMON_DATA[5]
} GPP_SAPA_HPAC_AREA, *pGPP_SAPA_HPAC_AREA;

typedef struct GPP_SAPA_HPAC_TROPO_BLOCK
{
	GPPUINT1		tropo_equation_type;													//SF041			-- will be set manually in the code
	GPPDOUBLE		tropo_quality;															//SF042			-- <ascii_in>.atm's ATM_TROPO_DATA[1]
	GPPDOUBLE		tropo_avhd;																//SF043			-- <ascii_in>.atm's ATM_TROPO_DATA[2]
	GPPUINT1		tropo_coeff_size;														//SF044			--
}GPP_SAPA_HPAC_TROPO_BLOCK, *pGPP_SAPA_HPAC_TROPO_BLOCK;

typedef struct GPP_SAPA_HPAC_TROPO_POLY_COEFFICIENT_BLOCK
{
	GPPDOUBLE		tropo_poly_coeff[4];													//SF045orSF048orSF046orSF049orSF047orSF050-- <ascii_in>.atm's ATM_TROPO_DATA[3]
}GPP_SAPA_HPAC_TROPO_POLY_COEFFICIENT_BLOCK, *pGPP_SAPA_HPAC_TROPO_POLY_COEFFICIENT_BLOCK;

typedef struct GPP_SAPA_HPAC_TROPO_GRID_BLOCK
{
	GPPUINT1		tropo_residual_size;													//SF051
	GPPDOUBLE		tropo_residuals[GPP_SAPA_MAX_GRID_POINT_PRESENT];						//SF052orSF053	-- <ascii_in>.atm's ATM_TROPO_DATA[7] to .....
}GPP_SAPA_HPAC_TROPO_GRID_BLOCK, *pGPP_SAPA_HPAC_TROPO_GRID_BLOCK;

typedef struct GPP_SAPA_HPAC_TROPO
{
	pGPP_SAPA_HPAC_TROPO_BLOCK	tropo_block;												//Troposphere Block
	pGPP_SAPA_HPAC_TROPO_POLY_COEFFICIENT_BLOCK tropo_poly_coeff_block;						//Polynomial coefficient block
	pGPP_SAPA_HPAC_TROPO_GRID_BLOCK tropo_grid;												//Grid Block
} GPP_SAPA_HPAC_TROPO, *pGPP_SAPA_HPAC_TROPO;

typedef struct GPP_SAPA_HPAC_IONO_SAT_POLY
{
	GPPDOUBLE  iono_quality;																//SF055     -- <ascii_in>.atm's ATM_IONOSAT_DATA[2]
	GPPUINT1  iono_coeff_size;																//SF056     
}GPP_SAPA_HPAC_IONO_SAT_POLY,*pGPP_SAPA_HPAC_IONO_SAT_POLY;

typedef struct GPP_SAPA_HPAC_IONO_SAT_COEFFICIENT
{
	GPPDOUBLE  iono_poly_coeff[4];															//SF057orSF060orSF058orSF061orSF059orSF062 -- <ascii_in>.atm's ATM_IONOSAT_DATA[3]
}GPP_SAPA_HPAC_IONO_SAT_COEFFICIENT, *pGPP_SAPA_HPAC_IONO_SAT_COEFFICIENT;

typedef struct GPP_SAPA_HPAC_IONO_GRID_BLOCK
{
	GPPUINT1  iono_residual_field_size;														//SF063     
	GPPDOUBLE  iono_residuals[GPP_SAPA_MAX_GRID_POINT_PRESENT];								//SF064orSF065orSF066  -- <ascii_in>.atm's ATM_IONOSAT_DATA[7] to .....
}GPP_SAPA_HPAC_IONO_GRID_BLOCK, *pGPP_SAPA_HPAC_IONO_GRID_BLOCK;

typedef struct GPP_SAPA_HPAC_IONO_SAT_BLOCK
{
	pGPP_SAPA_HPAC_IONO_SAT_POLY iono_sat_poly;												//Ionosphere Satellite Poloynomial
	pGPP_SAPA_HPAC_IONO_SAT_COEFFICIENT	iono_sat_coeff;										//Ionosphere Satellite Coefficient
	pGPP_SAPA_HPAC_IONO_GRID_BLOCK	iono_grid;												//Ionosphere Grid Block
}GPP_SAPA_HPAC_IONO_SAT_BLOCK, *pGPP_SAPA_HPAC_IONO_SAT_BLOCK;

typedef struct GPP_SAPA_HPAC_IONO
{
	GPPUINT1  iono_equation_type;															//SF054     -- will be set manually in the code
	GPPUINT8  sat_prn_bits;																	//SF011      
	pGPP_SAPA_HPAC_IONO_SAT_BLOCK		*iono_sat_block;									//Ionosphere Block
} GPP_SAPA_HPAC_IONO, *pGPP_SAPA_HPAC_IONO;

typedef struct GPP_SAPA_HPAC_ATMO_BLOCK {
	pGPP_SAPA_HPAC_AREA  area_def;															//Area Data Block
	pGPP_SAPA_HPAC_TROPO tropo;																//Troposphere Data Block
	pGPP_SAPA_HPAC_IONO  iono;																//Ionosphare Data Block
}GPP_SAPA_HPAC_ATMO_BLOCK, *pGPP_SAPA_HPAC_ATMO_BLOCK;


typedef struct GPP_SAPA_HPAC {
	pGPP_SAPA_HPAC_HEADER				*header_block;										//Header Block
	pGPP_SAPA_HPAC_ATMO_BLOCK			**atmo;												//struct array to save data in area index
} GPP_SAPA_HPAC, *pGPP_SAPA_HPAC;

//-------------------------------------------------------------------------------------------------------

//============================================= AREA Structures =========================================
typedef struct GPP_SAPA_AREA_DEF_HEADER {
	GPPUINT1		message_sub_type;														//SF001	        -- first charcter of satellite ID
	GPPUINT4		sys_id;																	//SF006			-- <ascii_in>.atm's ATM_AREADEF_HEADER[1]
	GPPUINT4		sys_processor_id;														//SF007			-- <ascii_in>.atm's ATM_AREADEF_HEADER[2]
	GPPUINT4		sol_issue_of_update;													//SF005			-- <ascii_in>.atm's ATM_AREADEF_HEADER[3]
	GPPUINT1        area_count;																//SF030			-- 
} GPP_SAPA_AREA_DEF_HEADER, *pGPP_SAPA_AREA_DEF_HEADER;

typedef struct GPP_SAPA_AREA_DEF_BLOCK
{
	GPPUINT4		area_id;																//SF031		   -- <ascii_in>.atm's ATM_AREA_DEF[1]
	GPPDOUBLE       area_ref_lat;															//SF032		   -- <ascii_in>.atm's ATM_AREA_DEF[2]
	GPPDOUBLE       area_ref_long;															//SF033		   -- <ascii_in>.atm's ATM_AREA_DEF[3]
	GPPUINT1        area_lat_grid_node_count;												//SF034		   -- <ascii_in>.atm's ATM_AREA_DEF[4]
	GPPUINT1		area_long_grid_node_count;												//SF035		   -- <ascii_in>.atm's ATM_AREA_DEF[5]
	GPPDOUBLE		area_lat_grid_node_spacing;												//SF036		   -- <ascii_in>.atm's ATM_AREA_DEF[6]
	GPPDOUBLE       area_long_grid_node_spacing;											//SF037		   -- <ascii_in>.atm's ATM_AREA_DEF[7]
}GPP_SAPA_AREA_DEF_BLOCK,*pGPP_SAPA_AREA_DEF_BLOCK;

typedef struct GPP_SAPA_AREA {
	pGPP_SAPA_AREA_DEF_HEADER header_block;													// Area Defination Header
	pGPP_SAPA_AREA_DEF_BLOCK  *area_def_block;												//Area Defination Block
}GPP_SAPA_AREA, *pGPP_SAPA_AREA;
//-------------------------------------------------------------------------------------------------------

typedef struct GPP_SAPA_USE_STATES{
    pGPP_SAPA_OCB   ocb;
    pGPP_SAPA_HPAC  hpac;
    pGPP_SAPA_AREA  area;
} GPP_SAPA_USE_STATES, *pGPP_SAPA_USE_STATES;

/******************************************************************************
 *  \brief Write SAPA OCB content to buffer
 *
 *  \param[in]  ocb     Pointer to GPP_SAPA_OCB structure
 *  \param[in]  *buffer Pointer to buffer
 *  \param[in]  *byte_pos
 *  \param[in]  *bit_pos
 *
 *  \retval  needed bits (>0) or error code (<0)

 *****************************************************************************/

GPPLONG gpp_sapa_ocb2buffer(const pGPP_SAPA_OCB ocb, GPPUINT1 sys, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
GPPLONG gpp_sapa_buffer2ocb(pGPP_SAPA_OCB ocb, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);

GPPLONG gpp_sapa_hpac2buffer(const pGPP_SAPA_HPAC hpac, GPPUINT1 sys, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
GPPLONG gpp_sapa_buffer2hpac(pGPP_SAPA_HPAC hpac, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);

GPPLONG gpp_sapa_area2buffer(const pGPP_SAPA_AREA area, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
GPPLONG gpp_sapa_buffer2area(pGPP_SAPA_AREA area, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
//Internal functions

//Return Seconds passed in the hour when data is received
GPPINT gpp_sapa_get_hourly_time_tag(GPPINT seconds_of_week);
//Returns seconds passed since the beginning including all gps_weeks
GPPINT gpp_sapa_get_full_time_tag(GPPINT gps_week, GPPINT seconds_of_week);
//Returns Orbit ,Clock and  Bias flag value
void gpp_sapa_get_ocb_flag_value(GPPUINT1 ocb_present_flag, GPPUINT1* o_flag, GPPUINT1* c_flag, GPPUINT1* b_flag);
//Set OCB present flag bit
void gpp_sapa_set_ocb_present_flags(GPPUINT1 *ref_obj, int index, int setvalue);
//Split tokens
GPPUINT4 gpp_sapa_split_arg_to_tokens(char **_buffer, GPPUCHAR **tok);
//Returns 1 if a bit at position pos in cons_bits is set else return 0
GPPUINT1 gpp_sapa_get_constellation_present_bit(GPPUINT2 cons_bits, GPPUINT1 pos);
//Returns highest order of cons_bit set
GPPUINT1 gpp_sapa_get_highest_cons_set(GPPUINT2 cons_bit);
//Sets cons_bit position
GPPUINT1 gpp_sapa_set_cons_bit(GPPUINT1 cons_bits, GPPUINT1 pos);
//System ID
GPPCHAR gpp_sapa_system_id(GPPUINT1 sys_id);

void gpp_sapa_get_svlist(GPPUINT8 prn_bits, GPPUINT1 *svlist);
void gpp_sapa_get_siglist(GPPUINT4 sig_bits, GPPUINT1 *siglist);

//==================================Functions required in Data conversion from and to Buffer/Structure===============================================================
static GPPLONG gpp_sapa_sv_bitmask2buffer(GPPUINT8 sv_prn_bits, GPPUINT1 sys, GPPUINT1 *svlist, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_buffer2sv_bitmask(GPPUINT8 *sv_prn_bits, GPPUINT1 sys, GPPUINT1 *svlist, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_bias_bitmask2buffer(GPPUINT4 sig_prn_bits, GPPUINT1 sys, GPPUINT1 *siglist, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_bias_buffer2bitmask(GPPUINT1 sys, GPPUINT1 *siglist, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
//===================================Declaration to add data to structure For OCB==============================================================================================
GPPLONG gpp_sapa_ocb_malloc_sv(pGPP_SAPA_OCB ocb);
GPPLONG gpp_sapa_ocb_free_ocb(pGPP_SAPA_OCB ocb);
GPPLONG gpp_sapa_ocb_add_sv(pGPP_SAPA_OCB ocb, GPPUINT1 sys, GPPUINT1 sat, const pGPP_SAPA_OCB_SV pset);
GPPLONG gpp_sapa_ocb_add_orb(pGPP_SAPA_OCB ocb, GPPUINT1 sys, GPPUINT1 sat, const pGPP_SAPA_OCB_SV_ORB pset);
GPPLONG gpp_sapa_ocb_add_clk(pGPP_SAPA_OCB ocb, GPPUINT1 sys, GPPUINT1 sat, const pGPP_SAPA_OCB_SV_CLK pset);
GPPLONG gpp_sapa_ocb_add_pb(pGPP_SAPA_OCB ocb, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 sig, const pGPP_SAPA_OCB_SV_BIAS_PB pset);
GPPLONG gpp_sapa_ocb_add_header(pGPP_SAPA_OCB ocb, GPPUINT1 sys, const pGPP_SAPA_OCB_HEADER pset);
GPPLONG gpp_sapa_ocb_add_cb(pGPP_SAPA_OCB ocb, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 sig, const pGPP_SAPA_OCB_SV_BIAS_CB pset);

//=============================================== functions to add data to structure For HPAC =================================================
GPPLONG gpp_sapa_hpac_add_header(pGPP_SAPA_HPAC hpac,GPPUINT1 sys, const pGPP_SAPA_HPAC_HEADER pset);
GPPLONG gpp_sapa_hpac_add_area(pGPP_SAPA_HPAC hpac,GPPUINT1 sys, GPPUINT1 area, const pGPP_SAPA_HPAC_AREA pset);
GPPLONG gpp_sapa_hpac_add_tropo(pGPP_SAPA_HPAC hpac,GPPUINT1 sys, GPPUINT1 area, const pGPP_SAPA_HPAC_TROPO pset);
GPPLONG gpp_sapa_hpac_add_tropo_block(pGPP_SAPA_HPAC hpac,GPPUINT1 sys, GPPUINT1 area, const pGPP_SAPA_HPAC_TROPO_BLOCK pset);
GPPLONG gpp_sapa_hpac_add_tropo_poly_coeff_block(pGPP_SAPA_HPAC hpac,GPPUINT1 sys, GPPUINT1 area, const pGPP_SAPA_HPAC_TROPO_POLY_COEFFICIENT_BLOCK pset);
GPPLONG gpp_sapa_hpac_add_tropo_grid_block(pGPP_SAPA_HPAC hpac,GPPUINT1 sys, GPPUINT1 area, const pGPP_SAPA_HPAC_TROPO_GRID_BLOCK pset);
GPPLONG gpp_sapa_hpac_add_iono(pGPP_SAPA_HPAC hpac,GPPUINT1 sys, GPPUINT1 area, const pGPP_SAPA_HPAC_IONO pset);
GPPLONG gpp_sapa_hpac_add_iono_sat_poly_block(pGPP_SAPA_HPAC hpac, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 area, const pGPP_SAPA_HPAC_IONO_SAT_POLY pset);
GPPLONG gpp_sapa_hpac_add_iono_sat_coeff_block(pGPP_SAPA_HPAC hpac, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 area, const pGPP_SAPA_HPAC_IONO_SAT_COEFFICIENT pset);
GPPLONG gpp_sapa_hpac_add_iono_sat_grid_block(pGPP_SAPA_HPAC hpac, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 area, const pGPP_SAPA_HPAC_IONO_GRID_BLOCK pset);

//=============================================== functions to add data to structure For Area =================================================

GPPLONG gpp_sapa_area_add_header(pGPP_SAPA_AREA p_area, const pGPP_SAPA_AREA_DEF_HEADER pset);
GPPLONG gpp_sapa_area_add_area_def(pGPP_SAPA_AREA p_area, GPPUINT1 area, const pGPP_SAPA_AREA_DEF_BLOCK pset);

//------------------------------------------------------------Transport Layer SAPA message------------------------------------------------------------------------------------
GPPLONG gpp_sapa_ocb_buffer_to_sapa_buffer(const GPPUCHAR *ocb_buffer, GPPLONG len_sapa_bits, GPPLONG ea_flag, GPPLONG message_crc_type, GPPLONG crc_frame, GPPUCHAR *sapa_buffer);
GPPLONG gpp_sapa_sapa_buffer_to_ocb_buffer(GPPUCHAR *ocb_buffer, GPPLONG *len_sapa_bits, GPPLONG *ea_flag, GPPLONG *message_crc_type, GPPLONG *crc_frame, const GPPUCHAR *sapa_buffer);
//Write Buffer Data Into File
void buffer_data_write_into_file(GPPUCHAR *buffer);
//Compare Two Files
void compare_files(FILE *pre_binary_filename, FILE *binary_filename);
GPPLONG gpp_sapa_get_bit_diff(GPPLONG byte_pos, GPPLONG bit_pos, GPPLONG byte_pos0, GPPLONG bit_pos0);
GPPLONG length_bytes_from_bits(GPPLONG b);
GPPLONG total_bits(GPPLONG *byte, GPPLONG *bits);
int TestBit(GPPULONGLONG *A, int k);
#endif // GPP_SAPA_H
