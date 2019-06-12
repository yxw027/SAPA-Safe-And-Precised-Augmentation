#ifndef GPP_SAPA_H_
#define GPP_SAPA_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32			// fuer Linux NICHT packen !!!, wie vorgehen bei WIN64 ???  NM 2016-02-23
#pragma pack(push,1)
#endif
#ifdef __WATCOMC__
#pragma off (unreferenced)
#endif

#include "gnssbase.h"
#include "gpptime.h"
#include "compiler.h" //GPP types

#include <stdlib.h>
#include <stdio.h>

/************************************************* * GPS Week and Second of 2010/01/01 00:00:00 UTC
*****************************************/
#define SAPA_GPS_WEEK_20100101 1564
#define SAPA_GPS_SEC_20100101 432000




/*******************************************
 * SAPA specific parameters
 *******************************************/
#define SAPA_MAX_SYS 16


#define GPP_SAPA_MAX_CONS   16  /* Constellation*/
#define GPP_SAPA_MAX_SYS	SAPA_MAX_SYS
#define GPP_SAPA_MAX_SAT    64  /* SF011, SF012 (special values) */
#define GPP_SAPA_MAX_SIG    32  /* SF027, SF028 (okay although only 10 bits needed) */

#define GPP_SAPA_MAX_AREA_COUNT 32
#define GPP_SAPA_MAX_GRID_POINT_PRESENT 128
#define GPP_SAPA_MAX_POLY_COEFF	4

#define GPP_SAPA_OCB_FLAG_IDX_ORB 	0
#define GPP_SAPA_OCB_FLAG_IDX_CLK 	1
#define GPP_SAPA_OCB_FLAG_IDX_BIAS 	2


//use "BITS" indicating a bitmask value
#define SAPA_OCB_ORB_BITS 0x01
#define SAPA_OCB_CLK_BITS 0x02
#define SAPA_OCB_BIAS_BITS 0x04





#define GPP_SAPA_GPS 0
#define GPP_SAPA_GLO 1
#define GNSS_HOURLY_TIME_TAG  0
#define GNSS_FULL_TIME_TAG	1

#define SAPA_HOURLY_TIME_TAG	0
#define SAPA_FULL_TIME_TAG		1


#define GPP_SAPA_SAT_PRESENT 0
#define GPP_SAPA_OCB_FLAG_PRESENT 1
#define GPP_SAPA_YAW_FLAG_PRESENT 1

#define GPP_SAPA_OCB_SAT_CORRECTION_MIN -16.382
#define GPP_SAPA_OCB_SAT_CORRECTION_MAX -16.382
#define GPP_SAPA_OCB_CB_CORRECTION_MIN -20.46
#define GPP_SAPA_OCB_CB_CORRECTION_MAX 20.46
#define GPP_SAPA_OCB_SAT_YAW_MIN 0
#define GPP_SAPA_OCB_SAT_YAW_MAX 354

#define GPP_SAPA_HPAC_AVHD_MIN -0.508
#define GPP_SAPA_HPAC_AVHD_MAX 0.508
#define GPP_SAPA_HPAC_SMALL_T00_MIN -0.252 
#define GPP_SAPA_HPAC_LARGE_T00_MIN -1.020 
#define GPP_SAPA_HPAC_SMALL_T00_MAX 0.252
#define GPP_SAPA_HPAC_LARGE_T00_MAX 1.020 
#define GPP_SAPA_HPAC_SMALL_T01_MIN -0.063  
#define GPP_SAPA_HPAC_LARGE_T01_MIN -0.255 
#define GPP_SAPA_HPAC_SMALL_T01_MAX 0.063
#define GPP_SAPA_HPAC_LARGE_T01_MAX 0.255
#define GPP_SAPA_HPAC_SMALL_T11_MIN -0.0510  
#define GPP_SAPA_HPAC_LARGE_T11_MIN -0.2046 
#define GPP_SAPA_HPAC_SMALL_T11_MAX 0.0510
#define GPP_SAPA_HPAC_LARGE_T11_MAX 0.2046
#define GPP_SAPA_HPAC_SMALL_C00_MIN -81.88 
#define GPP_SAPA_HPAC_LARGE_C00_MIN -327.64
#define GPP_SAPA_HPAC_SMALL_C00_MAX 81.88
#define GPP_SAPA_HPAC_LARGE_C00_MAX 327.64 
#define GPP_SAPA_HPAC_SMALL_C01_MIN -16.376   
#define GPP_SAPA_HPAC_LARGE_C01_MIN -65.528
#define GPP_SAPA_HPAC_SMALL_C01_MAX 16.376
#define GPP_SAPA_HPAC_LARGE_C01_MAX 65.528
#define GPP_SAPA_HPAC_SMALL_C11_MIN -8.190  
#define GPP_SAPA_HPAC_LARGE_C11_MIN -32.766  
#define GPP_SAPA_HPAC_SMALL_C11_MAX 8.190
#define GPP_SAPA_HPAC_LARGE_C11_MAX 32.766 
#define GPP_SAPA_HPAC_SMALL_ZENTH_MIN -0.124 
#define GPP_SAPA_HPAC_SMALL_ZENTH_MAX 0.124 
#define GPP_SAPA_HPAC_LARGE_ZENTH_MIN -0.508  
#define GPP_SAPA_HPAC_LARGE_ZENTH_MAX 0.508 
#define GPP_SAPA_HPAC_SMALL_SLANT_MIN -0.28 
#define GPP_SAPA_HPAC_MEDIUM_SLANT_MIN -2.52 
#define GPP_SAPA_HPAC_LARGE_SLANT_MIN -20.44 
#define GPP_SAPA_HPAC_EXTRA_LARGE_SLANT_MIN -327.64
#define GPP_SAPA_HPAC_SMALL_SLANT_MAX 0.28
#define GPP_SAPA_HPAC_MEDIUM_SLANT_MAX 2.52 
#define GPP_SAPA_HPAC_LARGE_SLANT_MAX 20.44
#define GPP_SAPA_HPAC_EXTRA_LARGE_SLANT_MAX 327.64

#define GPP_SAPA_AREA_REF_LAT_MIN -90.00 
#define GPP_SAPA_AREA_REF_LAT_MAX 90.00 
#define GPP_SAPA_AREA_REF_LONG_MIN -180.00 
#define GPP_SAPA_AREA_REF_LONG_MAX 180.00  
#define GPP_SAPA_AREA_GRID_LAT_SPACING_MIN 0.1 
#define GPP_SAPA_AREA_GRID_LAT_SPACING_MAX 3.2 
#define GPP_SAPA_AREA_GRID_LONG_SPACING_MIN 0.1 
#define GPP_SAPA_AREA_GRID_LONG_SPACING_MAX 3.2 
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
#define GPP_SAPA_ERR_INVALID_CB_SIG		 	(GPP_SAPA_ERROR_BASE-11)	/*	-54011	*/
#define GPP_SAPA_ERR_INVALID_HPAC_AREA	 	(GPP_SAPA_ERROR_BASE-12)	/*	-54012	*/
#define GPP_SAPA_ERR_INVALID_HPAC_HEADER 	(GPP_SAPA_ERROR_BASE-13)	/*	-54013	*/
#define GPP_SAPA_ERR_INVALID_AREA	 		(GPP_SAPA_ERROR_BASE-14)	/*	-54014	*/
#define GPP_SAPA_ERR_INVALID_META	 		(GPP_SAPA_ERROR_BASE-15)	/*	-54015	*/
#define GPP_SAPA_ERR_INVALID_SYS	 		(GPP_SAPA_ERROR_BASE-16)	/*	-54016	*/
#define GPP_SAPA_ERR_INVALID_OCB_HANDLE		(GPP_SAPA_ERROR_BASE-17)	/*	-54017	*/
#define GPP_SAPA_ERR_INVALID_TIME_TAG_TYPE 	(GPP_SAPA_ERROR_BASE-18)	/*	-54018	*/
#define GPP_SAPA_ERR_INVALID_HPAC_HANDLE	(GPP_SAPA_ERROR_BASE-19)	/*	-54019	*/
#define GPP_SAPA_ERR_INVALID_GAD_HANDLE		(GPP_SAPA_ERROR_BASE-20)	/*	-54020	*/

#define GPP_SAPA_ERR_PREAMBLE				(GPP_SAPA_ERROR_BASE-100) /* -54100	*/
#define GPP_SAPA_ERR_TYPE					(GPP_SAPA_ERROR_BASE-101) /* -54101	*/
#define GPP_SAPA_ERR_PAYLOAD_LENGTH			(GPP_SAPA_ERROR_BASE-102) /* -54102	*/
#define GPP_SAPA_ERR_CRC_TYPE				(GPP_SAPA_ERROR_BASE-103) /* -54103	*/
#define GPP_SAPA_ERR_CRC_FRAME				(GPP_SAPA_ERROR_BASE-104) /* -54104	*/

//#define length_bytes_from_bits(b) (((b)/8)+((b)%8?1:0))
#define SAPA_PREAMBLE 0x73	// First 8 bits in SAPA frame
#define SAPA_TYPE_OCB				0
#define SAPA_TYPE_HPAC				1
#define SAPA_TYPE_AREA				2

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


#define GPP_SAPA_MAX_OCB_CONFIGS 4
#define GPP_SAPA_OCB_BITS_ORB	0x01
#define GPP_SAPA_OCB_BITS_CLK	0x02
#define GPP_SAPA_OCB_BITS_PB	0x04
#define GPP_SAPA_OCB_BITS_CB	0x08
#define GPP_MAX_HPAC_CONFIGS 4



#define GPP_SAPA_OCB_CORECTION_MAX 3
#define GPP_SAPA_MAX_HPAC_BITS 4
#define GPP_SAPA_MAX_AREA_BITS 4

static const GPPDOUBLE SAPA_TROPO_COEFF_T00_MIN[2] = { GPP_SAPA_HPAC_SMALL_T00_MIN ,GPP_SAPA_HPAC_LARGE_T00_MIN };
static const GPPDOUBLE SAPA_TROPO_COEFF_T00_MAX[2] = { GPP_SAPA_HPAC_SMALL_T00_MAX ,GPP_SAPA_HPAC_LARGE_T00_MAX };
static const GPPDOUBLE SAPA_TROPO_COEFF_T01_MIN[2] = { GPP_SAPA_HPAC_SMALL_T01_MIN ,GPP_SAPA_HPAC_LARGE_T01_MIN };
static const GPPDOUBLE SAPA_TROPO_COEFF_T01_MAX[2] = { GPP_SAPA_HPAC_SMALL_T01_MAX ,GPP_SAPA_HPAC_LARGE_T01_MAX };
static const GPPDOUBLE SAPA_TROPO_COEFF_T11_MIN[2] = { GPP_SAPA_HPAC_SMALL_T11_MIN ,GPP_SAPA_HPAC_LARGE_T11_MIN };
static const GPPDOUBLE SAPA_TROPO_COEFF_T11_MAX[2] = { GPP_SAPA_HPAC_SMALL_T11_MAX ,GPP_SAPA_HPAC_LARGE_T11_MAX };
static const GPPDOUBLE SAPA_TROPO_COEFF_C00_MIN[2] = { GPP_SAPA_HPAC_SMALL_C00_MIN ,GPP_SAPA_HPAC_LARGE_C00_MIN };
static const GPPDOUBLE SAPA_TROPO_COEFF_C00_MAX[2] = { GPP_SAPA_HPAC_SMALL_C00_MAX ,GPP_SAPA_HPAC_LARGE_C00_MAX };
static const GPPDOUBLE SAPA_TROPO_COEFF_C01_MIN[2] = { GPP_SAPA_HPAC_SMALL_C01_MIN ,GPP_SAPA_HPAC_LARGE_C01_MIN };
static const GPPDOUBLE SAPA_TROPO_COEFF_C01_MAX[2] = { GPP_SAPA_HPAC_SMALL_C01_MAX ,GPP_SAPA_HPAC_LARGE_C01_MAX };
static const GPPDOUBLE SAPA_TROPO_COEFF_C11_MIN[2] = { GPP_SAPA_HPAC_SMALL_C11_MIN ,GPP_SAPA_HPAC_LARGE_C11_MIN };
static const GPPDOUBLE SAPA_TROPO_COEFF_C11_MAX[2] = { GPP_SAPA_HPAC_SMALL_C11_MAX ,GPP_SAPA_HPAC_LARGE_C11_MAX };
static const GPPDOUBLE SAPA_TROPO_RESIDUAL_ZENITH_MIN[2] = { GPP_SAPA_HPAC_SMALL_ZENTH_MIN ,GPP_SAPA_HPAC_LARGE_ZENTH_MIN };
static const GPPDOUBLE SAPA_TROPO_RESIDUAL_ZENITH_MAX[2] = { GPP_SAPA_HPAC_SMALL_ZENTH_MAX ,GPP_SAPA_HPAC_LARGE_ZENTH_MAX };
static const GPPDOUBLE SAPA_IONO_RESIDUAL_SLANT_MIN[4] = { GPP_SAPA_HPAC_SMALL_SLANT_MIN,GPP_SAPA_HPAC_MEDIUM_SLANT_MIN,GPP_SAPA_HPAC_LARGE_SLANT_MIN,GPP_SAPA_HPAC_EXTRA_LARGE_SLANT_MIN };
static const GPPDOUBLE SAPA_IONO_RESIDUAL_SLANT_MAX[4] = { GPP_SAPA_HPAC_SMALL_SLANT_MAX,GPP_SAPA_HPAC_MEDIUM_SLANT_MAX,GPP_SAPA_HPAC_LARGE_SLANT_MAX,GPP_SAPA_HPAC_EXTRA_LARGE_SLANT_MAX };


extern const GPPUINT1 SAPA_SV_IODE_LEN[GPP_SAPA_MAX_SYS];
extern const GPPUINT1 SAPA_SV_BITMASK_LEN_GPS[4];
extern const GPPUINT1 SAPA_SV_BITMASK_LEN_GLO[4];
extern const GPPUINT1 *SAPA_SV_BITMASK_LEN[2];
extern const GPPUINT1 SAPA_CRC_BYTES[4];



//============================================= OCB Structures ============================================================================================================================
typedef struct GPP_SAPA_OCB_HEADER {
	GPPUINT1		message_sub_type;		//SF001	       -- first charcter of satellite ID
	GPPUINT1		time_tag_type;			//SF002		   -- can be 0 or 1,will be set manually in the code
	GPPUINT4		time_tag;				//SF003orSF004 -- <ascii_in>.ocb's OCB_COMMON_INFO[2]
	GPPUINT4		sol_id;					//SF006		   -- <ascii_in>.ocb's OCB_COMMON_INFO[3]
	GPPUINT4		sol_processor_id;		//SF007        -- <ascii_in>.ocb's OCB_COMMON_INFO[4]
	GPPUINT4		sol_issue_of_update;	//SF005        -- <ascii_in>.ocb's OCB_COMMON_INFO[5]
	GPPUINT1		end_of_obc_set;			//SF010        -- will be set in the code
	GPPUINT1		reserved;				//SF069
	GPPUINT1		yaw_flag;				//SF008        -- <ascii_in>.ocb's OCB_COMMON_INFO[7]
	GPPUINT1		sat_ref_datum;			//SF009        -- <ascii_in>.ocb's OCB_COMMON_INFO[6]
	GPPUINT1		ephemeris_type;			//SF016orSF017 -- <ascii_in>.ocb's OCB_COMMON_INFO[8]
} GPP_SAPA_OCB_HEADER, *pGPP_SAPA_OCB_HEADER;

typedef struct GPP_SAPA_OCB_SV_ORB {
	GPPUINT4		iode;							//SF018orSF019 -- <ascii_in>.ocb's OCB_SATELLITE_DATA[7]
	GPPDOUBLE		d_orbit[GPP_SAPA_OCB_CORECTION_MAX];
	GPPDOUBLE		sat_yaw;						//SF021        -- <ascii_in>.ocb's OCB_SATELLITE_DATA[13]
	GPPT_WNT		wnt;
} GPP_SAPA_OCB_SV_ORB, *pGPP_SAPA_OCB_SV_ORB;

typedef struct GPP_SAPA_OCB_SV_CLK {
	GPPDOUBLE		iode_continuity;			//SF022        -- <ascii_in>.ocb's OCB_SATELLITE_DATA[8]
	GPPDOUBLE		clk_correction;				//SF020        -- <ascii_in>.ocb's OCB_SATELLITE_DATA[14]
	GPPDOUBLE		user_range_error;			//SF024        -- <ascii_in>.ocb's OCB_SATELLITE_DATA[15]
	GPPT_WNT		wnt;
} GPP_SAPA_OCB_SV_CLK, *pGPP_SAPA_OCB_SV_CLK;


typedef struct GPP_SAPA_OCB_SV_BIAS_PB
{
	GPPUINT1		fix_flag;																//SF023        -- <ascii_in>.ocb's OCB_SATPHASE_BIAS[3]
	GPPDOUBLE		countinity_indicator;													//SF015        -- <ascii_in>.ocb's OCB_SATPHASE_BIAS[4]
	GPPDOUBLE		pb_correction;															//SF020        -- <ascii_in>.ocb's OCB_SATPHASE_BIAS[2]
	GPPT_WNT		wnt;
} GPP_SAPA_OCB_SV_BIAS_PB, *pGPP_SAPA_OCB_SV_BIAS_PB;

typedef struct GPP_SAPA_OCB_SV_BIAS_CB {
	GPPDOUBLE		cb_correction;															//SF029        -- <ascii_in>.ocb's OCB_SATCODE_BIAS[2]
	GPPT_WNT		wnt;
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
	GPPUINT1 					ocb_bits;
	GPPDOUBLE					continuity_indicator;										//SF015       -- <ascii_in>.ocb's OCB_SATELLITE_DATA[6]
} GPP_SAPA_OCB_SV, *pGPP_SAPA_OCB_SV;

typedef struct GPP_SAPA_OCB {
	GPPUINT8					sv_prn_bits[GPP_SAPA_MAX_CONS];
	pGPP_SAPA_OCB_HEADER		*header_block;												//Header Block
    pGPP_SAPA_OCB_SV			**sv;														//get access via sv[cons][sat]; cons=GPS,GLO; sat=0,1,2,...N

    GPPUINT8					clk_prn_bits[SAPA_MAX_SYS];	//CP:2019/06/05 valid clock corrections
    GPPUINT8					orb_prn_bits[SAPA_MAX_SYS];	//CP:2019/06/05 valid orbit corrections
    GPPUINT8					pb_prn_bits[SAPA_MAX_SYS];	//CP:2019/06/05 valid phase bias corrections
    GPPUINT8					cb_prn_bits[SAPA_MAX_SYS];	//CP:2019/06/05 valid code bias corrections


}GPP_SAPA_OCB, *pGPP_SAPA_OCB;
//-------------------------------------------------------------------------------------------------------

//============================================= HPAC Structures =========================================

typedef struct GPP_SAPA_HPAC_HEADER {
	GPPUINT1		message_sub_type;														//SF001	        -- first charcter of satellite ID
	GPPUINT1		time_tag_type;															//SF002			-- can be 0 or 1,will be set manually in the code
	GPPUINT4		time_tag;																//SF003orSF004	-- <ascii_in>.atm's ATM_HPAC_HEADER[1] & ATM_HPAC_HEADER[2]
	GPPUINT4		sol_id;																	//SF006			-- <ascii_in>.atm's ATM_HPAC_HEADER[3]
	GPPUINT4		sol_processor_id;														//SF007			-- <ascii_in>.atm's ATM_HPAC_HEADER[4]
	GPPUINT4		sol_issue_of_update;													//SF005			-- <ascii_in>.atm's ATM_HPAC_HEADER[5]
	GPPUINT1		reserved;																//SF069
	GPPUINT1		area_issue_of_update;													//SF068
	GPPUINT1        area_count;																//SF030			--
} GPP_SAPA_HPAC_HEADER, *pGPP_SAPA_HPAC_HEADER;

typedef struct GPP_SAPA_HPAC_AREA {
	GPPUINT4		area_id;																//SF031			-- <ascii_in>.atm's ATM_HPAC_COMMON_DATA[1]
	GPPUINT1		number_of_grid_point;													//SF039			--
	GPPUINT1		tropo_block_indicator;													//SF040			-- <ascii_in>.atm's ATM_HPAC_COMMON_DATA[3]
	GPPUINT1		iono_block_indicator;													//SF040			-- <ascii_in>.atm's ATM_HPAC_COMMON_DATA[5]
} GPP_SAPA_HPAC_AREA, *pGPP_SAPA_HPAC_AREA;


typedef struct GPP_SAPA_HPAC_TROPO_POLY_COEFFICIENT_BLOCK
{
	GPPUINT1		tropo_equation_type;													//SF041			-- will be set manually in the code
	GPPDOUBLE		tropo_quality;															//SF042			-- <ascii_in>.atm's ATM_TROPO_DATA[1]
	GPPDOUBLE		tropo_avhd;																//SF043			-- <ascii_in>.atm's ATM_TROPO_DATA[2]
	GPPUINT1		tropo_coeff_size;														//SF044			--
	GPPDOUBLE		tropo_poly_coeff[GPP_SAPA_MAX_POLY_COEFF];								//SF045orSF048orSF046orSF049orSF047orSF050-- <ascii_in>.atm's ATM_TROPO_DATA[3]
}GPP_SAPA_HPAC_TROPO_POLY_COEFFICIENT_BLOCK, *pGPP_SAPA_HPAC_TROPO_POLY_COEFFICIENT_BLOCK;

typedef struct GPP_SAPA_HPAC_TROPO_GRID_BLOCK
{
	GPPUINT1		tropo_residual_size;													//SF051
	GPPDOUBLE		tropo_residuals[GPP_SAPA_MAX_GRID_POINT_PRESENT];						//SF052orSF053	-- <ascii_in>.atm's ATM_TROPO_DATA[7] to .....
}GPP_SAPA_HPAC_TROPO_GRID_BLOCK, *pGPP_SAPA_HPAC_TROPO_GRID_BLOCK;

typedef struct GPP_SAPA_HPAC_TROPO
{
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
	GPPDOUBLE  iono_poly_coeff[GPP_SAPA_MAX_POLY_COEFF];								   //SF057orSF060orSF058orSF061orSF059orSF062 -- <ascii_in>.atm's ATM_IONOSAT_DATA[3]
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
	GPPUINT8  sat_prn_bits[GPP_SAPA_MAX_CONS];												//SF011
	pGPP_SAPA_HPAC_IONO_SAT_BLOCK		**iono_sat_block;									//Ionosphere Block
} GPP_SAPA_HPAC_IONO, *pGPP_SAPA_HPAC_IONO;

typedef struct GPP_SAPA_HPAC_ATMO_BLOCK {
	pGPP_SAPA_HPAC_AREA  area_def;															//Area Data Block
	pGPP_SAPA_HPAC_TROPO tropo;																//Troposphere Data Block
	pGPP_SAPA_HPAC_IONO  iono;																//Ionosphare Data Block
}GPP_SAPA_HPAC_ATMO_BLOCK, *pGPP_SAPA_HPAC_ATMO_BLOCK;


typedef struct GPP_SAPA_HPAC {
	pGPP_SAPA_HPAC_HEADER				header_block;										//Header Block
	pGPP_SAPA_HPAC_ATMO_BLOCK			*atmo;												//struct array to save data in area index
} GPP_SAPA_HPAC, *pGPP_SAPA_HPAC;

//-------------------------------------------------------------------------------------------------------

//============================================= AREA Structures =========================================
typedef struct GPP_SAPA_AREA_DEF_HEADER {
	GPPUINT1		message_sub_type;														//SF001	        -- first charcter of satellite ID
	GPPUINT4		sol_id;																	//SF006			-- <ascii_in>.atm's ATM_AREADEF_HEADER[1]
	GPPUINT4		sol_processor_id;														//SF007			-- <ascii_in>.atm's ATM_AREADEF_HEADER[2]
	GPPUINT4		sol_issue_of_update;													//SF005			-- <ascii_in>.atm's ATM_AREADEF_HEADER[3]
	GPPUINT1		area_issue_of_update;													//SF068
	GPPUINT1		reserved;																//SF069
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



/************************************************************************************************************
 * SAPA MSG HANDLE
 * This handle allows for the SAPA Msg settings
 ************************************************************************************************************/
 /************************************************************************************************************
  * SAPA MSG HANDLE
  * This handle allows for the SAPA Msg settings
  ************************************************************************************************************/
typedef struct SAPA_OCB_HANDLE {
	GPPUINT1 sys;
	GPPUINT1 time_tag_type;
	GPPUINT1 end_of_obc_set;			//SF010        -- will be set in the code
	GPPUINT1 reserved;													//SF069
	GPPUINT1 ocb_bits; //ocb_bits to configure OCB messages (0001 only orbits, 0010 only clock, 0100 only PB, 1000 only CB)
} SAPA_OCB_HANDLE, *pSAPA_OCB_HANDLE;


typedef struct SAPA_GAD_HANDLE {
	GPPUINT1  sys;																//SF001
	GPPUINT1  reserved;															//SF069
	GPPUINT1  area_issue_of_update;												//SF068
	//GPPUINT4  area_bits;														//indicating which area is part of the message
} SAPA_GAD_HANDLE, *pSAPA_GAD_HANDLE;


typedef struct SAPA_HPAC_HANDLE {
	GPPUINT1  sys;																//SF001         -- first charcter of satellite ID
	GPPUINT1  time_tag_type;
	GPPUINT1  reserved;															//SF069
	GPPUINT1  area_issue_of_update;												//SF068
	GPPUINT8  grid_bits;					 //SF039   --
	//GPPUINT4  area_bits;					//indicating which area is part of the message
	GPPUINT1  tropo_coeff_size;              //SF044   --
	GPPUINT1  tropo_residual_size;             //SF051
	GPPUINT1  iono_coeff_size;                //SF056
	GPPUINT1  iono_residual_field_size;              //SF063
} SAPA_HPAC_HANDLE, *pSAPA_HPAC_HANDLE;



typedef struct SAPA_HANDLE {
	pSAPA_OCB_HANDLE  **ocbHdl; //one pointer for each GNSS
	GPPUINT1   ocb_config_bits[SAPA_MAX_SYS];

	pSAPA_HPAC_HANDLE  **hpacHdl[SAPA_MAX_SYS];
	pSAPA_GAD_HANDLE gadHdl[SAPA_MAX_SYS];
} SAPA_HANDLE, *pSAPA_HANDLE;


GPPLONG gpp_sapa_handle_free_ocbHdl(SAPA_HANDLE *sapaHdl);
GPPLONG gpp_sapa_handle_malloc_ocbHdl(SAPA_HANDLE *sapaHdl);

GPPLONG gpp_sapa_config_add_ocb_config(SAPA_HANDLE *sapaHdl, GPPUINT1 sys, const SAPA_OCB_HANDLE *pset, FILE *fp);
GPPLONG gpp_sapa_config_add_hpac_config(SAPA_HANDLE *sapaHdl, GPPUINT1 sys, const SAPA_HPAC_HANDLE *pset, FILE *fp);
GPPLONG gpp_sapa_config_add_gad_config(SAPA_HANDLE *sapaHdl, GPPUINT1 sys, const SAPA_GAD_HANDLE *pset, FILE *fp);

GPPLONG gpp_sapa_handle_free_handle(SAPA_HANDLE **ppSapaHdl);
GPPLONG gpp_sapa_handle_malloc_handle(SAPA_HANDLE **ppSapaHdl);
GPPLONG gpp_sapa_handle_free_hpacHdl(SAPA_HANDLE *sapaHdl);
GPPLONG gpp_sapa_handle_free_gadHdl(SAPA_HANDLE *sapaHdl);

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

GPPLONG gpp_sapa_ocb2buffer(const pGPP_SAPA_OCB ocb, const SAPA_OCB_HANDLE *ocbHdl, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
GPPLONG gpp_sapa_buffer2ocb(pGPP_SAPA_OCB ocb, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);

GPPLONG gpp_sapa_hpac2buffer(const pGPP_SAPA_HPAC hpac, const SAPA_HPAC_HANDLE *hpacHdl, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
GPPLONG gpp_sapa_buffer2hpac(pGPP_SAPA_HPAC hpac, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);

GPPLONG gpp_sapa_area2buffer(const pGPP_SAPA_AREA area, const SAPA_GAD_HANDLE *gadHdl, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
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


void gpp_sapa_get_svlist(GPPUINT8 prn_bits, GPPUINT1 *svlist);
void gpp_sapa_get_siglist(GPPUINT4 sig_bits, GPPUINT1 *siglist);

//==================================Functions required in Data conversion from and to Buffer/Structure===============================================================
static GPPLONG gpp_sapa_sv_bitmask2buffer(GPPUINT8 sv_prn_bits, GPPUINT1 sys, GPPUINT1 *svlist, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_buffer2sv_bitmask(GPPUINT8 *sv_prn_bits, GPPUINT1 sys, GPPUINT1 *svlist, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);

static GPPLONG gpp_sapa_bias_bitmask2buffer(GPPUINT4 sig_prn_bits, GPPUINT1 sys, GPPUINT1 *siglist, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_bias_buffer2bitmask(GPPUINT1 sys, GPPUINT1 *siglist, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);

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
GPPLONG gpp_sapa_hpac_free_hpac(pGPP_SAPA_HPAC hpac);
GPPLONG gpp_sapa_hpac_add_header(pGPP_SAPA_HPAC hpac, const pGPP_SAPA_HPAC_HEADER pset);
GPPLONG gpp_sapa_hpac_add_area(pGPP_SAPA_HPAC hpac, GPPUINT1 area, const pGPP_SAPA_HPAC_AREA pset);
GPPLONG gpp_sapa_hpac_add_tropo(pGPP_SAPA_HPAC hpac, GPPUINT1 area, const pGPP_SAPA_HPAC_TROPO pset);
GPPLONG gpp_sapa_hpac_add_tropo_poly_coeff_block(pGPP_SAPA_HPAC hpac, GPPUINT1 area, const pGPP_SAPA_HPAC_TROPO_POLY_COEFFICIENT_BLOCK pset);
GPPLONG gpp_sapa_hpac_add_tropo_grid_block(pGPP_SAPA_HPAC hpac, GPPUINT1 area, const pGPP_SAPA_HPAC_TROPO_GRID_BLOCK pset);
GPPLONG gpp_sapa_hpac_add_iono(pGPP_SAPA_HPAC hpac,GPPUINT1 area, const pGPP_SAPA_HPAC_IONO pset);
GPPLONG gpp_sapa_hpac_add_iono_sat_poly_block(pGPP_SAPA_HPAC hpac, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 area, const pGPP_SAPA_HPAC_IONO_SAT_POLY pset);
GPPLONG gpp_sapa_hpac_add_iono_sat_coeff_block(pGPP_SAPA_HPAC hpac, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 area, const pGPP_SAPA_HPAC_IONO_SAT_COEFFICIENT pset);
GPPLONG gpp_sapa_hpac_add_iono_sat_grid_block(pGPP_SAPA_HPAC hpac, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 area, const pGPP_SAPA_HPAC_IONO_GRID_BLOCK pset);

//=============================================== functions to add data to structure For Area =================================================
GPPLONG gpp_sapa_area_free_area(pGPP_SAPA_AREA area);
GPPLONG gpp_sapa_area_add_header(pGPP_SAPA_AREA p_area, const pGPP_SAPA_AREA_DEF_HEADER pset);
GPPLONG gpp_sapa_area_add_area_def(pGPP_SAPA_AREA p_area, GPPUINT1 area, const pGPP_SAPA_AREA_DEF_BLOCK pset);

//=============================================== functions to add data to structure For Handle =================================================
//GPPLONG gpp_sapa_handle_malloc_ocbHdl(SAPA_HANDLE *sapaHdl);
//------------------------------------------------------------Transport Layer SAPA message------------------------------------------------------------------------------------
GPPLONG gpp_sapa_ocb_buffer_to_sapa_buffer(const GPPUCHAR *ocb_buffer, GPPLONG len_sapa_bits, GPPLONG ea_flag, GPPLONG message_crc_type, GPPLONG crc_frame, GPPUCHAR *sapa_buffer);
GPPLONG gpp_sapa_sapa_buffer_to_ocb_buffer(GPPUCHAR *ocb_buffer, GPPLONG *len_sapa_bits, GPPLONG *ea_flag, GPPLONG *message_crc_type, GPPLONG *crc_frame, const GPPUCHAR *sapa_buffer);
GPPLONG gpp_sapa_hpac_buffer_to_sapa_buffer(const GPPUCHAR *hpac_buffer, GPPLONG len_sapa_bits, GPPLONG ea_flag, GPPLONG message_crc_type, GPPLONG crc_frame, GPPUCHAR *sapa_buffer);
GPPLONG gpp_sapa_sapa_buffer_to_hpac_buffer(GPPUCHAR *hpac_buffer, GPPLONG *len_sapa_bits, GPPLONG *ea_flag, GPPLONG *message_crc_type, GPPLONG *crc_frame, const GPPUCHAR *sapa_buffer);
GPPLONG gpp_sapa_area_buffer_to_sapa_buffer(const GPPUCHAR *area_buffer, GPPLONG len_sapa_bits, GPPLONG ea_flag, GPPLONG message_crc_type, GPPLONG crc_frame, GPPUCHAR *sapa_buffer);
GPPLONG gpp_sapa_sapa_buffer_to_area_buffer(GPPUCHAR *area_buffer, GPPLONG *len_sapa_bits, GPPLONG *ea_flag, GPPLONG *message_crc_type, GPPLONG *crc_frame, const GPPUCHAR *sapa_buffer);
//Write Buffer Data Into File
void buffer_data_write_into_file(GPPUCHAR *buffer);
//Compare Two Files
void compare_files(FILE *pre_binary_filename, FILE *binary_filename);
GPPLONG gpp_sapa_get_bit_diff(GPPLONG byte_pos, GPPLONG bit_pos, GPPLONG byte_pos0, GPPLONG bit_pos0);
GPPLONG length_bytes_from_bits(GPPLONG b);
GPPLONG total_bits(GPPLONG *byte, GPPLONG *bits);



void gpp_sapa_debug_fprintf_ocb(const GPP_SAPA_OCB *p_ocb, FILE *fp);
void gpp_sapa_debug_fprintf_hpac(pGPP_SAPA_HPAC p_hpac, FILE *fp);
void gpp_sapa_debug_fprintf_area(pGPP_SAPA_AREA p_area, FILE *fp);



/************************************************************************************************************
 * Malloc and free functions for GPP_SAPA_USE_STATES structure
 ************************************************************************************************************/

GPPLONG gpp_sapa_states_free_ocb(GPP_SAPA_USE_STATES *use_states);
GPPLONG gpp_sapa_states_malloc_ocb(GPP_SAPA_USE_STATES *use_states);



/*

# ifndef GNSS_BASE_H_
static const GPPUINT1 GNSS_PRN_BIT_MASK_8[8] = { 0x01,0x02,0x04,0x08,
										0x10,0x20,0x40,0x80 };


static const GPPUINT2 GNSS_PRN_BIT_MASK_16[16] = { 0x0001,0x0002,0x0004,0x0008,
											0x0010,0x0020,0x0040,0x0080,
											0x0100,0x0200,0x0400,0x0800,
											0x1000,0x2000,0x4000,0x8000 };


static const GPPUINT4 GNSS_PRN_BIT_MASK_32[32] = { 0x00000001,0x00000002,0x00000004,0x00000008,
											0x00000010,0x00000020,0x00000040,0x00000080,
											0x00000100,0x00000200,0x00000400,0x00000800,
											0x00001000,0x00002000,0x00004000,0x00008000,
											0x00010000,0x00020000,0x00040000,0x00080000,
											0x00100000,0x00200000,0x00400000,0x00800000,
											0x01000000,0x02000000,0x04000000,0x08000000,
											0x10000000,0x20000000,0x40000000,0x80000000 };

#if defined(__WATCOMC__) && (__WATCOMC__ < 1280)
static const GPPUINT8 GNSS_PRN_BIT_MASK_64[64] = {
											0x0000000000000001,0x0000000000000002,0x0000000000000004,0x0000000000000008,
											0x0000000000000010,0x0000000000000020,0x0000000000000040,0x0000000000000080,
											0x0000000000000100,0x0000000000000200,0x0000000000000400,0x0000000000000800,
											0x0000000000001000,0x0000000000002000,0x0000000000004000,0x0000000000008000,
											0x0000000000010000,0x0000000000020000,0x0000000000040000,0x0000000000080000,
											0x0000000000100000,0x0000000000200000,0x0000000000400000,0x0000000000800000,
											0x0000000001000000,0x0000000002000000,0x0000000004000000,0x0000000008000000,
											0x0000000010000000,0x0000000020000000,0x0000000040000000,0x0000000080000000,
											0x0000000100000000,0x0000000200000000,0x0000000400000000,0x0000000800000000,
											0x0000001000000000,0x0000002000000000,0x0000004000000000,0x0000008000000000,
											0x0000010000000000,0x0000020000000000,0x0000040000000000,0x0000080000000000,
											0x0000100000000000,0x0000200000000000,0x0000400000000000,0x0000800000000000,
											0x0001000000000000,0x0002000000000000,0x0004000000000000,0x0008000000000000,
											0x0010000000000000,0x0020000000000000,0x0040000000000000,0x0080000000000000,
											0x0100000000000000,0x0200000000000000,0x0400000000000000,0x0800000000000000,
											0x1000000000000000,0x2000000000000000,0x4000000000000000,0x8000000000000000 };
#else
static const GPPUINT8 GNSS_PRN_BIT_MASK_64[64] = {
											0x0000000000000001ULL,0x0000000000000002ULL,0x0000000000000004ULL,0x0000000000000008ULL,
											0x0000000000000010ULL,0x0000000000000020ULL,0x0000000000000040ULL,0x0000000000000080ULL,
											0x0000000000000100ULL,0x0000000000000200ULL,0x0000000000000400ULL,0x0000000000000800ULL,
											0x0000000000001000ULL,0x0000000000002000ULL,0x0000000000004000ULL,0x0000000000008000ULL,
											0x0000000000010000ULL,0x0000000000020000ULL,0x0000000000040000ULL,0x0000000000080000ULL,
											0x0000000000100000ULL,0x0000000000200000ULL,0x0000000000400000ULL,0x0000000000800000ULL,
											0x0000000001000000ULL,0x0000000002000000ULL,0x0000000004000000ULL,0x0000000008000000ULL,
											0x0000000010000000ULL,0x0000000020000000ULL,0x0000000040000000ULL,0x0000000080000000ULL,
											0x0000000100000000ULL,0x0000000200000000ULL,0x0000000400000000ULL,0x0000000800000000ULL,
											0x0000001000000000ULL,0x0000002000000000ULL,0x0000004000000000ULL,0x0000008000000000ULL,
											0x0000010000000000ULL,0x0000020000000000ULL,0x0000040000000000ULL,0x0000080000000000ULL,
											0x0000100000000000ULL,0x0000200000000000ULL,0x0000400000000000ULL,0x0000800000000000ULL,
											0x0001000000000000ULL,0x0002000000000000ULL,0x0004000000000000ULL,0x0008000000000000ULL,
											0x0010000000000000ULL,0x0020000000000000ULL,0x0040000000000000ULL,0x0080000000000000ULL,
											0x0100000000000000ULL,0x0200000000000000ULL,0x0400000000000000ULL,0x0800000000000000ULL,
											0x1000000000000000ULL,0x2000000000000000ULL,0x4000000000000000ULL,0x8000000000000000ULL };
#endif



#define GNSS_SET_ID_IN_BITS_8(sats,id) ((sats)|=GNSS_PRN_BIT_MASK_8[(id)-1])
#define GNSS_SET_ID_IN_BITS_16(sats,id) ((sats)|=GNSS_PRN_BIT_MASK_16[(id)-1])
#define GNSS_SET_ID_IN_BITS_32(sats,id) ((sats)|=GNSS_PRN_BIT_MASK_32[(id)-1])
#define GNSS_SET_ID_IN_BITS_64(sats,id) ((sats)|=GNSS_PRN_BIT_MASK_64[(id)-1])
#define GNSS_HAS_ID_IN_BITS_8(sats,id) ((sats)&GNSS_PRN_BIT_MASK_8[(id)-1])
#define GNSS_HAS_ID_IN_BITS_16(sats,id) ((sats)&GNSS_PRN_BIT_MASK_16[(id)-1])
#define GNSS_HAS_ID_IN_BITS_32(sats,id) ((sats)&GNSS_PRN_BIT_MASK_32[(id)-1])
#define GNSS_HAS_ID_IN_BITS_64(sats,id) ((sats)&GNSS_PRN_BIT_MASK_64[(id)-1])
#define GNSS_UNSET_ID_IN_BITS_8(sats,id) ((sats)&=GNSS_PRN_INV_BIT_MASK_8[(id)-1])
#define GNSS_UNSET_ID_IN_BITS_16(sats,id) ((sats)&=GNSS_PRN_INV_BIT_MASK_16[(id)-1])
#define GNSS_UNSET_ID_IN_BITS_32(sats,id) ((sats)&=GNSS_PRN_INV_BIT_MASK_32[(id)-1])
#define GNSS_UNSET_ID_IN_BITS_64(sats,id) ((sats)&=GNSS_PRN_INV_BIT_MASK_64[(id)-1])

#define GNSS_SET_IDX_IN_BITS_8(sats,idx) ((sats)|=GNSS_PRN_BIT_MASK_8[(idx)])
#define GNSS_SET_IDX_IN_BITS_16(sats,idx) ((sats)|=GNSS_PRN_BIT_MASK_16[(idx)])
#define GNSS_SET_IDX_IN_BITS_32(sats,idx) ((sats)|=GNSS_PRN_BIT_MASK_32[(idx)])
#define GNSS_SET_IDX_IN_BITS_64(sats,idx) ((sats)|=GNSS_PRN_BIT_MASK_64[(idx)])
#define GNSS_HAS_IDX_IN_BITS_8(sats,idx) ((sats)&GNSS_PRN_BIT_MASK_8[(idx)])
#define GNSS_HAS_IDX_IN_BITS_16(sats,idx) ((sats)&GNSS_PRN_BIT_MASK_16[(idx)])
#define GNSS_HAS_IDX_IN_BITS_32(sats,idx) ((sats)&GNSS_PRN_BIT_MASK_32[(idx)])
#define GNSS_HAS_IDX_IN_BITS_64(sats,idx) ((sats)&GNSS_PRN_BIT_MASK_64[(idx)])
#define GNSS_UNSET_IDX_IN_BITS_8(sats,idx) ((sats)&=GNSS_PRN_INV_BIT_MASK_8[(idx)])
#define GNSS_UNSET_IDX_IN_BITS_16(sats,idx) ((sats)&=GNSS_PRN_INV_BIT_MASK_16[(idx)])
#define GNSS_UNSET_IDX_IN_BITS_32(sats,idx) ((sats)&=GNSS_PRN_INV_BIT_MASK_32[(idx)])
#define GNSS_UNSET_IDX_IN_BITS_64(sats,idx) ((sats)&=GNSS_PRN_INV_BIT_MASK_64[(idx)])

#endif //GNSS_BASE_H_
*/

#ifdef __WATCOMC__
#pragma on (unreferenced)
#endif


#ifdef __cplusplus
}
#endif

#endif //GPP_SAPA_H_
