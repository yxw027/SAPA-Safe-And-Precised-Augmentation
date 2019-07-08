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



/*************************************************
* GPS Week and Second of 2010/01/01 00:00:00 UTC
*************************************************/
#define SAPA_GPS_WEEK_20100101 1564
#define SAPA_GPS_SEC_20100101 432000




/*******************************************
	* SAPA specific parameters
*******************************************/
#define SAPA_MAX_SYS 16

#define GPP_SAPA_MAX_CONS   16  /* Constellation*/
#define GPP_SAPA_MAX_SYS SAPA_MAX_SYS
#define GPP_SAPA_MAX_SAT    64  /* SF011, SF012 (special values) */
#define GPP_SAPA_MAX_SIG    32  /* SF027, SF028 (okay although only 10 bits needed) */

#define SAPA_MAX_AREA  256

#define GPP_SAPA_MAX_AREA_COUNT 32
#define GPP_SAPA_MAX_GRID_POINT_PRESENT 128

#define SAPA_MAX_TROPO_COEFF 4
#define	SAPA_MAX_IONO_COEFF 4


#define GPP_SAPA_OCB_FLAG_IDX_ORB  0
#define GPP_SAPA_OCB_FLAG_IDX_CLK  1
#define GPP_SAPA_OCB_FLAG_IDX_BIAS  2

//use postfix "_bits" to indicate a bitmask value, here SF014
#define SAPA_OCB_ORB_BITS  0x01
#define SAPA_OCB_CLK_BITS  0x02
#define SAPA_OCB_BIAS_BITS  0x04


#define GPP_SAPA_GPS 0
#define GPP_SAPA_GLO 1
#define GNSS_HOURLY_TIME_TAG  0
#define GNSS_FULL_TIME_TAG 1

#define SAPA_HOURLY_TIME_TAG 0
#define SAPA_FULL_TIME_TAG  1


#define GPP_SAPA_SAT_PRESENT 0
#define GPP_SAPA_OCB_FLAG_PRESENT 1
#define GPP_SAPA_YAW_FLAG_PRESENT 1

/******************************************
  * GPP SAPA MIN MAX Values
  ******************************************/

#define SAPA_SAT_MIN_MAX 16.382

#define SAPA_SAT_MIN -SAPA_SAT_MIN_MAX
#define SAPA_SAT_MAX SAPA_SAT_MIN_MAX

#define LSAPA_SAT_MIN 0
#define LSAPA_SAT_MAX 16382

#define SAPA_SV_MIN_MAX 16.382

#define SAPA_SV_MIN -SAPA_SV_MIN_MAX
#define SAPA_SV_MAX SAPA_SV_MIN_MAX

#define LSAPA_SV_MIN 0
#define LSAPA_SV_MAX 16382

#define SAPA_CB_MIN_MAX 20.46

#define SAPA_CB_MIN -SAPA_CB_MIN_MAX
#define SAPA_CB_MAX SAPA_CB_MIN_MAX

#define SAPA_CB_MIN 0
#define SAPA_CB_MAX 2046

#define SAPA_YAW_MIN 0
#define SAPA_YAW_MAX 354

#define LSAPA_YAW_MIN 0
#define LSAPA_YAW_MAX 354

#define SAPA_AVHD_MIN_MAX 0.508

#define SAPA_AVHD_MIN -SAPA_AVHD_MIN_MAX
#define SAPA_AVHD_MAX SAPA_AVHD_MIN_MAX

#define LSAPA_AVHD_MIN 0
#define LSAPA_AVHD_MAX 508

#define SAPA_T00_MIN_MAX_SML 0.252
#define SAPA_T00_MIN_MAX_LRG 1.020

#define SAPA_T00_MIN_SML -SAPA_T00_MIN_MAX_SML
#define SAPA_T00_MAX_SML  SAPA_T00_MIN_MAX_SML
#define SAPA_T00_MIN_LRG -SAPA_T00_MIN_MAX_LRG
#define SAPA_T00_MAX_LRG  SAPA_T00_MIN_MAX_LRG

#define LSAPA_T00_MIN_SML 0
#define LSAPA_T00_MAX_SML  252
#define LSAPA_T00_MIN_LRG 0
#define LSAPA_T00_MAX_LRG  1020

#define SAPA_T01_MIN_MAX_SML 0.063
#define SAPA_T01_MIN_MAX_LRG 0.255

#define SAPA_T01_MIN_SML -SAPA_T01_MIN_MAX_SML
#define SAPA_T01_MAX_SML  SAPA_T01_MIN_MAX_SML
#define SAPA_T01_MIN_LRG -SAPA_T01_MIN_MAX_LRG
#define SAPA_T01_MAX_LRG  SAPA_T01_MIN_MAX_LRG

#define LSAPA_T01_MIN_SML 0
#define LSAPA_T01_MAX_SML  63
#define LSAPA_T01_MIN_LRG 0
#define LSAPA_T01_MAX_LRG  255

#define SAPA_T10_MIN_SML -SAPA_T01_MIN_MAX_SML
#define SAPA_T10_MAX_SML  SAPA_T01_MIN_MAX_SML
#define SAPA_T10_MIN_LRG -SAPA_T01_MIN_MAX_LRG
#define SAPA_T10_MAX_LRG  SAPA_T01_MIN_MAX_LRG

#define LSAPA_T10_MIN_SML 0
#define LSAPA_T10_MAX_SML  63
#define LSAPA_T10_MIN_LRG 0
#define LSAPA_T10_MAX_LRG  255

#define SAPA_T11_MIN_MAX_SML 0.0510
#define SAPA_T11_MIN_MAX_LRG 0.2046

#define SAPA_T11_MIN_SML -SAPA_T11_MIN_MAX_SML
#define SAPA_T11_MAX_SML  SAPA_T11_MIN_MAX_SML
#define SAPA_T11_MIN_LRG -SAPA_T11_MIN_MAX_LRG
#define SAPA_T11_MAX_LRG  SAPA_T11_MIN_MAX_LRG

#define LSAPA_T11_MIN_SML 0
#define LSAPA_T11_MAX_SML  510
#define LSAPA_T11_MIN_LRG 0
#define LSAPA_T11_MAX_LRG  2046

#define SAPA_C00_MIN_MAX_SML 81.88
#define SAPA_C00_MIN_MAX_LRG 327.64

#define SAPA_C00_MIN_SML -SAPA_C00_MIN_MAX_SML
#define SAPA_C00_MAX_SML  SAPA_C00_MIN_MAX_SML
#define SAPA_C00_MIN_LRG -SAPA_C00_MIN_MAX_LRG
#define SAPA_C00_MAX_LRG  SAPA_C00_MIN_MAX_LRG

#define LSAPA_C00_MIN_SML 0
#define LSAPA_C00_MAX_SML  8188
#define LSAPA_C00_MIN_LRG 0
#define LSAPA_C00_MAX_LRG  32764

#define SAPA_C01_MIN_MAX_SML 16.376
#define SAPA_C01_MIN_MAX_LRG 65.528

#define SAPA_C01_MIN_SML -SAPA_C01_MIN_MAX_SML
#define SAPA_C01_MAX_SML  SAPA_C01_MIN_MAX_SML
#define SAPA_C01_MIN_LRG -SAPA_C01_MIN_MAX_LRG
#define SAPA_C01_MAX_LRG  SAPA_C01_MIN_MAX_LRG

#define LSAPA_C01_MIN_SML 0
#define LSAPA_C01_MAX_SML  16376
#define LSAPA_C01_MIN_LRG 0
#define LSAPA_C01_MAX_LRG  65528

#define SAPA_C10_MIN_SML -SAPA_C01_MIN_MAX_SML
#define SAPA_C10_MAX_SML  SAPA_C01_MIN_MAX_SML
#define SAPA_C10_MIN_LRG -SAPA_C01_MIN_MAX_LRG
#define SAPA_C10_MAX_LRG  SAPA_C01_MIN_MAX_LRG

#define LSAPA_C10_MIN_SML 0
#define LSAPA_C10_MAX_SML  16376
#define LSAPA_C10_MIN_LRG 0
#define LSAPA_C10_MAX_LRG  65528

#define SAPA_C11_MIN_MAX_SML 8.190
#define SAPA_C11_MIN_MAX_LRG 32.766

#define SAPA_C11_MIN_SML -SAPA_C11_MIN_MAX_SML
#define SAPA_C11_MAX_SML  SAPA_C11_MIN_MAX_SML
#define SAPA_C11_MIN_LRG -SAPA_C11_MIN_MAX_LRG
#define SAPA_C11_MAX_LRG  SAPA_C11_MIN_MAX_LRG

#define LSAPA_C11_MIN_SML 0
#define LSAPA_C11_MAX_SML  8190
#define LSAPA_C11_MIN_LRG 0
#define LSAPA_C11_MAX_LRG  32766

#define SAPA_TROPO_GRD_MIN_MAX_SML 0.124
#define SAPA_TROPO_GRD_MIN_MAX_LRG 0.508

#define SAPA_TROPO_GRD_MIN_SML -SAPA_TROPO_GRD_MIN_MAX_SML
#define SAPA_TROPO_GRD_MAX_SML  SAPA_TROPO_GRD_MIN_MAX_SML

#define SAPA_TROPO_GRD_MIN_LRG -SAPA_TROPO_GRD_MIN_MAX_LRG
#define SAPA_TROPO_GRD_MAX_LRG  SAPA_TROPO_GRD_MIN_MAX_LRG

#define LSAPA_TROPO_GRD_MIN_SML 0
#define LSAPA_TROPO_GRD_MAX_SML  124

#define LSAPA_TROPO_GRD_MIN_LRG 0
#define LSAPA_TROPO_GRD_MAX_LRG  508

#define SAPA_IONO_GRD_MIN_MAX_SML 0.28
#define SAPA_IONO_GRD_MIN_MAX_MDN 2.52
#define SAPA_IONO_GRD_MIN_MAX_LRG 20.44
#define SAPA_IONO_GRD_MIN_MAX_ELRG 327.64


#define SAPA_IONO_GRD_MIN_SML -SAPA_IONO_GRD_MIN_MAX_SML
#define SAPA_IONO_GRD_MAX_SML  SAPA_IONO_GRD_MIN_MAX_SML

#define SAPA_IONO_GRD_MIN_MDM -SAPA_IONO_GRD_MIN_MAX_MDN
#define SAPA_IONO_GRD_MAX_MDM  SAPA_IONO_GRD_MIN_MAX_MDN

#define SAPA_IONO_GRD_MIN_LRG -SAPA_IONO_GRD_MIN_MAX_LRG
#define SAPA_IONO_GRD_MAX_LRG  SAPA_IONO_GRD_MIN_MAX_LRG

#define SAPA_IONO_GRD_MIN_ELRG -SAPA_IONO_GRD_MIN_MAX_ELRG
#define SAPA_IONO_GRD_MAX_ELRG SAPA_IONO_GRD_MIN_MAX_ELRG

#define LSAPA_IONO_GRD_MIN_SML 0
#define LSAPA_IONO_GRD_MAX_SML  28

#define LSAPA_IONO_GRD_MIN_MDM 0
#define LSAPA_IONO_GRD_MAX_MDM  252

#define LSAPA_IONO_GRD_MIN_LRG 0
#define LSAPA_IONO_GRD_MAX_LRG  2044

#define LSAPA_IONO_GRD_MIN_ELRG 0
#define LSAPA_IONO_GRD_MAX_ELRG 32764


#define SAPA_AREA_LAT_MIN_MAX 90.00
#define SAPA_AREA_LONG_MIN_MAX 180.00

#define SAPA_AREA_LAT_MIN -SAPA_AREA_LAT_MIN_MAX
#define SAPA_AREA_LAT_MAX SAPA_AREA_LAT_MIN_MAX

#define SAPA_AREA_LONG_MIN -SAPA_AREA_LONG_MIN_MAX
#define SAPA_AREA_LONG_MAX SAPA_AREA_LONG_MIN_MAX

#define SAPA_AREA_GRD_LAT_MIN 0.1
#define SAPA_AREA_GRD_LAT_MAX 3.2

#define SAPA_AREA_GRD_LONG_MIN SAPA_AREA_GRD_LAT_MIN
#define SAPA_AREA_GRD_LONG_MAX SAPA_AREA_GRD_LAT_MAX



//#define length_bytes_from_bits(b) (((b)/8)+((b)%8?1:0))
#define SAPA_PREAMBLE 0x73 // First 8 bits in SAPA frame
#define SAPA_TYPE_OCB    0
#define SAPA_TYPE_HPAC    1
#define SAPA_TYPE_AREA    2

#define SAPA_CONST_LEN_BYTES_BASE  32
#define SAPA_CONST_LEN_BYTES_CRC_8  8
#define SAPA_CONST_LEN_BYTES_CRC_16  16
#define SAPA_CONST_LEN_BYTES_CRC_24  24
#define SAPA_CONST_LEN_BYTES_CRC_32  32

#define SAPA_SV_IODE_LEN_GPS 8
#define SAPA_SV_IODE_LEN_GLO  7

#define SAPA_RES_SV_CORRECTION  0.002
#define SAPA_RES_PB_CORRECTION  0.002
#define SAPA_RES_CB_CORRECTION  0.02

#define SAPA_RES_AREA_AVG_VER_HEDRO_DELAY 0.004
#define SAPA_RES_TROPO_RESIDUAL_DELAY 0.004
#define SAPA_RES_IONO_RESIDUAL_DELAY 0.04


#define SAPA_TROPO_GRD_RES 0.004


#define SAPA_RES_TROPO_POLY_COEFF_T00 0.004
#define SAPA_RES_TROPO_POLY_COEFF_T01 0.001
#define SAPA_RES_TROPO_POLY_COEFF_T11 0.0002

#define SAPA_T00_RES 0.004
#define SAPA_T01_RES 0.001
#define SAPA_T10_RES 0.001
#define SAPA_T11_RES 0.0002


#define SAPA_C00_RES 0.04
#define SAPA_C01_RES 0.008
#define SAPA_C10_RES 0.008
#define SAPA_C11_RES 0.002

#define TROPO_POLY_COEFF_INDX_T00 0
#define TROPO_POLY_COEFF_INDX_T01 1
#define TROPO_POLY_COEFF_INDX_T10 2
#define TROPO_POLY_COEFF_INDX_T11 3

#define SAPA_T00_IDX 0
#define SAPA_T01_IDX 1
#define SAPA_T10_IDX 2
#define SAPA_T11_IDX 3


#define IONO_POLY_COEFF_INDX_C00 0
#define IONO_POLY_COEFF_INDX_C01 1
#define IONO_POLY_COEFF_INDX_C10 2
#define IONO_POLY_COEFF_INDX_C11 3

#define SAPA_SMALL_TROPO_RESIDUAL_ZENITH_DELAY 6
#define SAPA_LARGE_TROPO_RESIDUAL_ZENITH_DELAY 8

#define SAPA_SMALL_IONO_RESIDUAL_SLANT_DELAY 4
#define SAPA_MEDIUM_IONO_RESIDUAL_SLANT_DELAY 7
#define SAPA_LARGE_IONO_RESIDUAL_SLANT_DELAY 10
#define SAPA_EXTRA_LARGE_IONO_RESIDUAL_SLANT_DELAY 14

#define GPP_SAPA_HPAC_NOT_PRESENT 0
#define GPP_SAPA_HPAC_POLY_PRESENT 1
#define GPP_SAPA_HPAC_POLY_AND_GRID_PRESENT 2

#define GPP_SAPA_MAX_OCB_CONFIGS 4
#define GPP_SAPA_OCB_BITS_ORB 0x01
#define GPP_SAPA_OCB_BITS_CLK 0x02
#define GPP_SAPA_OCB_BITS_PB 0x04
#define GPP_SAPA_OCB_BITS_CB 0x08
#define GPP_SAPA_MAX_HPAC_CONFIGS 3

#define GPP_SAPA_AREA_BITS64 4

#define GPP_SAPA_OCB_CORECTION_MAX 3
#define GPP_SAPA_MAX_HPAC_BITS 4
#define GPP_SAPA_MAX_AREA_BITS 4


extern const GPPDOUBLE SAPT_TROPO_GRD_MIN[2];
extern const GPPDOUBLE SAPT_TROPO_GRD_MAX[2];
extern const GPPDOUBLE SAPA_IONO_RESIDUAL_SLANT_MIN[4];
extern const GPPDOUBLE SAPA_IONO_RESIDUAL_SLANT_MAX[4];

extern const GPPUINT1 SAPA_SV_IODE_LEN[GPP_SAPA_MAX_SYS];
extern const GPPUINT1 SAPA_SV_BITMASK_LEN_GPS[4];
extern const GPPUINT1 SAPA_SV_BITMASK_LEN_GLO[4];
extern const GPPUINT1 *SAPA_SV_BITMASK_LEN[2];
extern const GPPUINT1 SAPA_CRC_BYTES[4];


const GPPDOUBLE SAPA_TROPO_POLY_MIN_SML[SAPA_MAX_TROPO_COEFF];
const GPPDOUBLE SAPA_TROPO_POLY_MAX_SML[SAPA_MAX_TROPO_COEFF];
const GPPDOUBLE SAPA_TROPO_POLY_MIN_LRG[SAPA_MAX_TROPO_COEFF];
const GPPDOUBLE SAPA_TROPO_POLY_MAX_LRG[SAPA_MAX_TROPO_COEFF];
const GPPDOUBLE* SAPA_TROPO_POLY_MIN[2];
const GPPDOUBLE* SAPA_TROPO_POLY_MAX[2];
const GPPDOUBLE SAPA_TROPO_POLY_RES[SAPA_MAX_TROPO_COEFF];
const GPPDOUBLE SAPA_TROPO_GRD_MIN[2];
const GPPDOUBLE SAPA_TROPO_GRD_MAX[2];

const GPPDOUBLE SAPA_IONO_POLY_MIN_SML[SAPA_MAX_IONO_COEFF];
const GPPDOUBLE SAPA_IONO_POLY_MAX_SML[SAPA_MAX_IONO_COEFF];
const GPPDOUBLE SAPA_IONO_POLY_MIN_LRG[SAPA_MAX_IONO_COEFF];
const GPPDOUBLE SAPA_IONO_POLY_MAX_LRG[SAPA_MAX_IONO_COEFF];
const GPPDOUBLE* SAPA_IONO_POLY_MIN[2];
const GPPDOUBLE* SAPA_IONO_POLY_MAX[2];
const GPPDOUBLE SAPA_IONO_POLY_RES[SAPA_MAX_TROPO_COEFF];
const GPPDOUBLE SAPA_IONO_GRD_MIN[4];
const GPPDOUBLE SAPA_IONO_GRD_MAX[4];


/******************************************
* GPP SAPA ERROR Codes
******************************************/
#define GPP_SAPA_OK       0
#define GPP_SAPA_ERROR_BASE     -54000
#define GPP_SAPA_ERR_NOT_YET_IMPLEMENTED (GPP_SAPA_ERROR_BASE-1)  /*  -54001  */
#define GPP_SAPA_ERR_NOT_ENOUGH_MEMORY  (GPP_SAPA_ERROR_BASE-2)  /*  -54002  */
#define GPP_SAPA_ERR_INVALID_OCB   (GPP_SAPA_ERROR_BASE-3)  /*  -54003  */
#define GPP_SAPA_ERR_INVALID_OCB_SV   (GPP_SAPA_ERROR_BASE-4)  /*  -54004  */
#define GPP_SAPA_ERR_INVALID_OCB_SV_ORB  (GPP_SAPA_ERROR_BASE-5)  /*  -54005  */
#define GPP_SAPA_ERR_INVALID_OCB_SV_CLK  (GPP_SAPA_ERROR_BASE-6)  /*  -54006  */
#define GPP_SAPA_ERR_INVALID_OCB_SV_PB  (GPP_SAPA_ERROR_BASE-7)  /*  -54007  */
#define GPP_SAPA_ERR_INVALID_OCB_SV_CB  (GPP_SAPA_ERROR_BASE-8)  /*  -54008  */
#define GPP_SAPA_ERR_INVALID_SVLIST   (GPP_SAPA_ERROR_BASE-9)  /*  -54009  */
#define GPP_SAPA_ERR_INVALID_SIGLIST  (GPP_SAPA_ERROR_BASE-10) /*  -54010  */
#define GPP_SAPA_ERR_INVALID_CB_SIG    (GPP_SAPA_ERROR_BASE-11) /* -54011 */
#define GPP_SAPA_ERR_INVALID_HPAC_AREA   (GPP_SAPA_ERROR_BASE-12) /* -54012 */
#define GPP_SAPA_ERR_INVALID_HPAC_HEADER  (GPP_SAPA_ERROR_BASE-13) /* -54013 */
#define GPP_SAPA_ERR_INVALID_AREA    (GPP_SAPA_ERROR_BASE-14) /* -54014 */
#define GPP_SAPA_ERR_INVALID_META    (GPP_SAPA_ERROR_BASE-15) /* -54015 */
#define GPP_SAPA_ERR_INVALID_SYS    (GPP_SAPA_ERROR_BASE-16) /* -54016 */
#define GPP_SAPA_ERR_INVALID_OCB_HANDLE  (GPP_SAPA_ERROR_BASE-17) /* -54017 */
#define GPP_SAPA_ERR_INVALID_TIME_TAG_TYPE  (GPP_SAPA_ERROR_BASE-18) /* -54018 */
#define GPP_SAPA_ERR_INVALID_HPAC_HANDLE (GPP_SAPA_ERROR_BASE-19) /* -54019 */
#define GPP_SAPA_ERR_INVALID_GAD_HANDLE  (GPP_SAPA_ERROR_BASE-20) /* -54020 */
#define GPP_SAPA_ERR_INVALID_CONFIG   (GPP_SAPA_ERROR_BASE-21) /* -54021 */
#define GPP_SAPA_ERR_INVALID_SAT   (GPP_SAPA_ERROR_BASE-22) /* -54022 */
#define GPP_SAPA_ERR_INVALID_TROPO_EQ_TYPE (GPP_SAPA_ERROR_BASE-23) /* -54023 */
#define GPP_SAPA_ERR_INVALID_IONO_EQ_TYPE (GPP_SAPA_ERROR_BASE-24) /* -54024 */
#define GPP_SAPA_ERR_INVALID_HPAC   (GPP_SAPA_ERROR_BASE-25) /* -54025 */
#define GPP_SAPA_ERR_INVALID_GRD_IDX  (GPP_SAPA_ERROR_BASE-26) /* -54026 */



#define GPP_SAPA_ERR_PREAMBLE    (GPP_SAPA_ERROR_BASE-100) /* -54100 */
#define GPP_SAPA_ERR_TYPE     (GPP_SAPA_ERROR_BASE-101) /* -54101 */
#define GPP_SAPA_ERR_PAYLOAD_LENGTH   (GPP_SAPA_ERROR_BASE-102) /* -54102 */
#define GPP_SAPA_ERR_CRC_TYPE    (GPP_SAPA_ERROR_BASE-103) /* -54103 */
#define GPP_SAPA_ERR_CRC_FRAME    (GPP_SAPA_ERROR_BASE-104) /* -54104 */




///************************************************************************************************************
// * \OCB Structure
// ************************************************************************************************************/

typedef struct GPP_SAPA_OCB_HEADER {
	GPPUINT1		message_sub_type;														//SF001	       -- first charcter of satellite ID
	GPPUINT1		time_tag_type;															//SF002		   -- can be 0 or 1,will be set manually in the code
	GPPUINT4		time_tag;																//SF003orSF004 -- <ascii_in>.ocb's OCB_COMMON_INFO[2]
	GPPUINT4		sol_id;																	//SF006		   -- <ascii_in>.ocb's OCB_COMMON_INFO[3]
	GPPUINT4		sol_processor_id;														//SF007        -- <ascii_in>.ocb's OCB_COMMON_INFO[4]
	GPPUINT4		sol_issue_of_update;													//SF005        -- <ascii_in>.ocb's OCB_COMMON_INFO[5]
	GPPUINT1		end_of_obc_set;															//SF010        -- will be set in the code
	GPPUINT1		reserved;																//SF069
	GPPUINT1		yaw_flag;																//SF008        -- <ascii_in>.ocb's OCB_COMMON_INFO[7]
	GPPUINT1		sat_ref_datum;															//SF009        -- <ascii_in>.ocb's OCB_COMMON_INFO[6]
	GPPUINT1		ephemeris_type;															//SF016orSF017 -- <ascii_in>.ocb's OCB_COMMON_INFO[8]
}GPP_SAPA_OCB_HEADER, *pGPP_SAPA_OCB_HEADER;

typedef struct GPP_SAPA_OCB_SV_ORB {
	GPPUINT4		iode;																	//SF018orSF019 -- <ascii_in>.ocb's OCB_SATELLITE_DATA[7]
	GPPDOUBLE		d_orbit[GPP_SAPA_OCB_CORECTION_MAX];
	GPPLONG		    ld_orbit[GPP_SAPA_OCB_CORECTION_MAX];
	GPPDOUBLE		sat_yaw;																//SF021        -- <ascii_in>.ocb's OCB_SATELLITE_DATA[13]
	GPPUINT1        yaw_bits;																//indicates if sat_yaw is valid
	GPPLONG			lsat_yaw;
	GPPT_WNT		wnt;
} GPP_SAPA_OCB_SV_ORB, *pGPP_SAPA_OCB_SV_ORB;

typedef struct GPP_SAPA_OCB_SV_CLK {
	GPPDOUBLE		iode_continuity;														//SF022        -- <ascii_in>.ocb's OCB_SATELLITE_DATA[8]
	GPPDOUBLE		clk_correction;															//SF020        -- <ascii_in>.ocb's OCB_SATELLITE_DATA[14]
	GPPLONG			lclk_correction;														//SF020        -- <ascii_in>.ocb's OCB_SATELLITE_DATA[14]
	GPPDOUBLE		user_range_error;														//SF024        -- <ascii_in>.ocb's OCB_SATELLITE_DATA[15]
	GPPT_WNT		wnt;
} GPP_SAPA_OCB_SV_CLK, *pGPP_SAPA_OCB_SV_CLK;


typedef struct GPP_SAPA_OCB_SV_BIAS_PB
{
	GPPUINT1		fix_flag;																//SF023        -- <ascii_in>.ocb's OCB_SATPHASE_BIAS[3]
	GPPDOUBLE		countinity_indicator;													//SF015        -- <ascii_in>.ocb's OCB_SATPHASE_BIAS[4]
	GPPDOUBLE		pb_correction;															//SF020        -- <ascii_in>.ocb's OCB_SATPHASE_BIAS[2]
	GPPLONG			lpb_correction;															//SF020        -- <ascii_in>.ocb's OCB_SATPHASE_BIAS[2]
	GPPT_WNT		wnt;
} GPP_SAPA_OCB_SV_BIAS_PB, *pGPP_SAPA_OCB_SV_BIAS_PB;

typedef struct GPP_SAPA_OCB_SV_BIAS_CB {
	GPPDOUBLE		cb_correction;															//SF029        -- <ascii_in>.ocb's OCB_SATCODE_BIAS[2]
	GPPLONG			lcb_correction;															//SF029        -- <ascii_in>.ocb's OCB_SATCODE_BIAS[2]
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

///************************************************************************************************************
// * \HPAC Structure
// ************************************************************************************************************/

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
	GPPLONG			ltropo_avhd;															//SF043			-- <ascii_in>.atm's ATM_TROPO_DATA[2]
	GPPUINT1		tropo_coeff_size;														//SF044			--
	GPPDOUBLE		tropo_poly_coeff[SAPA_MAX_TROPO_COEFF];								   //SF045orSF048orSF046orSF049orSF047orSF050-- <ascii_in>.atm's ATM_TROPO_DATA[3]
	GPPLONG			ltropo_poly_coeff[SAPA_MAX_TROPO_COEFF];								//SF045orSF048orSF046orSF049orSF047orSF050-- <ascii_in>.atm's ATM_TROPO_DATA[3]
}GPP_SAPA_HPAC_TROPO_POLY_COEFFICIENT_BLOCK, *pGPP_SAPA_HPAC_TROPO_POLY_COEFFICIENT_BLOCK;

typedef struct GPP_SAPA_HPAC_TROPO_GRD_CORRECTION
{
	GPPDOUBLE  val;
	GPPLONG  lval;
}GPP_SAPA_HPAC_TROPO_GRD_CORRECTION, *pGPP_SAPA_HPAC_TROPO_GRD_CORRECTION;

typedef struct GPP_SAPA_HPAC_TROPO_GRID_BLOCK
{
	GPPUINT1  sz; //bit size indicator SF051
	pGPP_SAPA_HPAC_TROPO_GRD_CORRECTION *grid;
	GPPUINT8 grid_bits;
	GPPUINT1 num_grid;
}GPP_SAPA_HPAC_TROPO_GRID_BLOCK, *pGPP_SAPA_HPAC_TROPO_GRID_BLOCK;

//typedef struct GPP_SAPA_HPAC_TROPO_GRID_BLOCK
//{
//	GPPUINT1		tropo_residual_size;													//SF051
//	GPPDOUBLE		tropo_residuals[GPP_SAPA_MAX_GRID_POINT_PRESENT];						//SF052orSF053	-- <ascii_in>.atm's ATM_TROPO_DATA[7] to .....
//	GPPLONG			ltropo_residuals[GPP_SAPA_MAX_GRID_POINT_PRESENT];						//SF052orSF053	-- <ascii_in>.atm's ATM_TROPO_DATA[7] to .....
//}GPP_SAPA_HPAC_TROPO_GRID_BLOCK, *pGPP_SAPA_HPAC_TROPO_GRID_BLOCK;

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
	GPPDOUBLE  iono_poly_coeff[SAPA_MAX_IONO_COEFF];								   //SF057orSF060orSF058orSF061orSF059orSF062 -- <ascii_in>.atm's ATM_IONOSAT_DATA[3]
	GPPLONG    liono_poly_coeff[SAPA_MAX_IONO_COEFF];								   //SF057orSF060orSF058orSF061orSF059orSF062 -- <ascii_in>.atm's ATM_IONOSAT_DATA[3]
}GPP_SAPA_HPAC_IONO_SAT_COEFFICIENT, *pGPP_SAPA_HPAC_IONO_SAT_COEFFICIENT;


typedef struct GPP_SAPA_HPAC_IONO_GRD_CORRECTION
{
	GPPDOUBLE  val;
	GPPLONG  lval;
}GPP_SAPA_HPAC_IONO_GRD_CORRECTION, *pGPP_SAPA_HPAC_IONO_GRD_CORRECTION;

typedef struct GPP_SAPA_HPAC_IONO_GRID_BLOCK
{
	GPPUINT1  sz; //bit size indicator SF051
	pGPP_SAPA_HPAC_IONO_GRD_CORRECTION *grid;
	GPPUINT8 grid_bits;
	GPPUINT1 num_grid;
}GPP_SAPA_HPAC_IONO_GRID_BLOCK, *pGPP_SAPA_HPAC_IONO_GRID_BLOCK;

//typedef struct GPP_SAPA_HPAC_IONO_GRID_BLOCK
//{
//	GPPUINT1   iono_residual_field_size;														//SF063
//	GPPDOUBLE  iono_residuals[GPP_SAPA_MAX_GRID_POINT_PRESENT];								//SF064orSF065orSF066  -- <ascii_in>.atm's ATM_IONOSAT_DATA[7] to .....
//	GPPLONG    liono_residuals[GPP_SAPA_MAX_GRID_POINT_PRESENT];								//SF064orSF065orSF066  -- <ascii_in>.atm's ATM_IONOSAT_DATA[7] to .....
//}GPP_SAPA_HPAC_IONO_GRID_BLOCK, *pGPP_SAPA_HPAC_IONO_GRID_BLOCK;


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
	GPPUINT8							atmo_bits[GPP_SAPA_AREA_BITS64];//this 4x64 bit mask controls the access to atmo
} GPP_SAPA_HPAC, *pGPP_SAPA_HPAC;

///************************************************************************************************************
// * \GeoGraphical Area Structure
// ************************************************************************************************************/

typedef struct GPP_SAPA_AREA_DEF_HEADER{
	GPPUINT1		message_sub_type;														//SF001	        -- first charcter of satellite ID
	GPPUINT4		sol_id;																	//SF006			-- <ascii_in>.atm's ATM_AREADEF_HEADER[1]
	GPPUINT4		sol_processor_id;														//SF007			-- <ascii_in>.atm's ATM_AREADEF_HEADER[2]
	GPPUINT4		sol_issue_of_update;													//SF005			-- <ascii_in>.atm's ATM_AREADEF_HEADER[3]
	GPPUINT1		area_issue_of_update;													//SF068
	GPPUINT1		reserved;																//SF069
	GPPUINT1        area_count;																//SF030			--
}GPP_SAPA_AREA_DEF_HEADER, *pGPP_SAPA_AREA_DEF_HEADER;

typedef struct GPP_SAPA_AREA_DEF_BLOCK
{
	GPPUINT4		area_id;																//SF031		   -- <ascii_in>.atm's ATM_AREA_DEF[1]
	GPPDOUBLE       area_ref_lat;															//SF032		   -- <ascii_in>.atm's ATM_AREA_DEF[2]
	GPPDOUBLE       area_ref_long;															//SF033		   -- <ascii_in>.atm's ATM_AREA_DEF[3]
	GPPULONG        larea_ref_lat;															//SF032		   -- <ascii_in>.atm's ATM_AREA_DEF[2]
	GPPULONG        larea_ref_long;															//SF033		   -- <ascii_in>.atm's ATM_AREA_DEF[3]
	GPPUINT1        area_lat_grid_node_count;												//SF034		   -- <ascii_in>.atm's ATM_AREA_DEF[4]
	GPPUINT1		area_long_grid_node_count;												//SF035		   -- <ascii_in>.atm's ATM_AREA_DEF[5]
	GPPDOUBLE		area_lat_grid_node_spacing;												//SF036		   -- <ascii_in>.atm's ATM_AREA_DEF[6]
	GPPDOUBLE       area_long_grid_node_spacing;											//SF037		   -- <ascii_in>.atm's ATM_AREA_DEF[7]
	GPPULONG		larea_lat_grid_node_spacing;											//SF036		   -- <ascii_in>.atm's ATM_AREA_DEF[6]
	GPPULONG        larea_long_grid_node_spacing;											//SF037		   -- <ascii_in>.atm's ATM_AREA_DEF[7]

	GPPUINT1		num_grid_points;//SF034 x SF035
}GPP_SAPA_AREA_DEF_BLOCK,*pGPP_SAPA_AREA_DEF_BLOCK;

typedef struct GPP_SAPA_AREA{
	pGPP_SAPA_AREA_DEF_HEADER header_block;													// Area Defination Header
	pGPP_SAPA_AREA_DEF_BLOCK  *area_def_block;												//Area Defination Block
	GPPUINT8					area_bits[GPP_SAPA_AREA_BITS64];   //bitmask array to handle the blocks
}GPP_SAPA_AREA, *pGPP_SAPA_AREA;

/************************************************************************************************************
 * SAPA USE STATES
 ************************************************************************************************************/

typedef struct GPP_SAPA_USE_STATES{
    pGPP_SAPA_OCB   ocb;
    pGPP_SAPA_HPAC  hpac;
    pGPP_SAPA_AREA  area;
}GPP_SAPA_USE_STATES, *pGPP_SAPA_USE_STATES;


 /************************************************************************************************************
  * SAPA MSG HANDLE
  * This handle allows for the SAPA Msg settings
  ************************************************************************************************************/

typedef struct SAPA_OCB_HANDLE {
	GPPUINT1 sys;
	GPPUINT1 time_tag_type;
	GPPUINT8 prn_bits[GPP_SAPA_MAX_SYS];
	GPPUINT1 ocb_bits[GPP_SAPA_MAX_SAT];										//ocb_bits to configure OCB messages (0001 only orbits, 0010 only clock, 0100 only PB, 1000 only CB)
} SAPA_OCB_HANDLE, *pSAPA_OCB_HANDLE;

typedef struct SAPA_HPAC_HANDLE_IONO {
	GPPUINT2 sys_bits;																				//SF001
	GPPUINT1  iono_coeff_size;																	//SF056
	GPPUINT1  iono_residual_field_size;															//SF063
} SAPA_HPAC_HANDLE_IONO, *pSAPA_HPAC_HANDLE_IONO;

typedef struct SAPA_HPAC_HANDLE_TROPO {
	GPPUINT1  tropo_coeff_size;																	//SF056
	GPPUINT1  tropo_residual_size;																//SF063
} SAPA_HPAC_HANDLE_TROPO, *pSAPA_HPAC_HANDLE_TROPO;

typedef struct SAPA_HPAC_HANDLE {
	GPPUINT1  time_tag_type;
	GPPUINT8  prn_bits[SAPA_MAX_SYS];
	GPPUINT8  area_bits[GPP_SAPA_AREA_BITS64];													//indicating which area is part of the message
	GPPUINT1  blk_indicator;																	 //SF040; it controls which data shall be transmitted

	pSAPA_HPAC_HANDLE_IONO  *hpacIonoHdl;
	GPPUINT8   hpacIonoHdl_bits[GPP_SAPA_MAX_AREA_COUNT];
	pSAPA_HPAC_HANDLE_TROPO *hpacTropoHdl;
	GPPUINT8   hpacTropoHdl_bits[GPP_SAPA_MAX_AREA_COUNT];
} SAPA_HPAC_HANDLE, *pSAPA_HPAC_HANDLE;

typedef struct SAPA_GAD_HANDLE {
	GPPUINT8  area_bits[GPP_SAPA_AREA_BITS64];																		//indicating which area is part of the message
} SAPA_GAD_HANDLE, *pSAPA_GAD_HANDLE;

typedef struct SAPA_HANDLE {
	pSAPA_OCB_HANDLE  **ocbHdl;																	//one pointer for each GNSS
	GPPUINT8   ocbHdl_bits[GPP_SAPA_MAX_SYS];
	pSAPA_HPAC_HANDLE  *hpacTropoHdl;  //hpacTropoHdl[iconf]->
	GPPUINT8    hpacTropoHdl_bits;

	pSAPA_HPAC_HANDLE  **hpacIonoHdl; //hpacIonoHdl[sys][iconf]->
	GPPUINT8    hpacIonoHdl_bits[SAPA_MAX_SYS];

	pSAPA_GAD_HANDLE  *gadHdl;  //gadHdl[iconf]->
	GPPUINT8   gadHdl_bits;

	pSAPA_HPAC_HANDLE  *hpacHdl;
} SAPA_HANDLE, *pSAPA_HANDLE;

GPPLONG gpp_sapa_handle_free_ocbHdl(SAPA_HANDLE *sapaHdl);
GPPLONG gpp_sapa_handle_malloc_ocbHdl(SAPA_HANDLE *sapaHdl);

GPPLONG gpp_sapa_config_add_ocb_config(SAPA_HANDLE *sapaHdl, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 config, const SAPA_OCB_HANDLE *pset, FILE *fp);
GPPLONG gpp_sapa_config_add_hpac_config(SAPA_HANDLE *sapaHdl, const SAPA_HPAC_HANDLE *pset, FILE *fp);
GPPLONG gpp_sapa_config_add_hpac_iono_config(SAPA_HANDLE *sapaHdl, GPPUINT1 area, const SAPA_HPAC_HANDLE_IONO *pset, FILE *fp);
GPPLONG gpp_sapa_config_add_hpac_tropo_config(SAPA_HANDLE *sapaHdl, GPPUINT1 area, const SAPA_HPAC_HANDLE_TROPO *pset, FILE *fp);
GPPLONG gpp_sapa_config_add_gad_config(SAPA_HANDLE *sapaHdl, const SAPA_GAD_HANDLE *pset, FILE *fp);
GPPLONG gpp_sapa_handle_free_handle(SAPA_HANDLE **ppSapaHdl);
GPPLONG gpp_sapa_handle_malloc_handle(SAPA_HANDLE **ppSapaHdl);
GPPLONG gpp_sapa_handle_free_hpacHdl(SAPA_HANDLE *sapaHdl);
GPPLONG gpp_sapa_handle_free_gadHdl(SAPA_HANDLE *sapaHdl);

/******************************************************************************
 *  \brief Write SAPA OCB content to buffer
 *
 *  \param[in]  ocb     Pointer to GPP_SAPA_OCB structure
 *	\param[in]	*ocbHdl
 *  \param[in]  *buffer Pointer to buffer
 *  \param[in]  *byte_pos
 *  \param[in]  *bit_pos
 *
 *  \retval  needed bits (>0) or error code (<0)

 *****************************************************************************/
GPPLONG gpp_sapa_ocb2buffer(const pGPP_SAPA_OCB ocb, const SAPA_OCB_HANDLE *ocbHdl, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
GPPLONG gpp_sapa_buffer2ocb(pGPP_SAPA_OCB ocb, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);

/******************************************************************************
 *  \brief Write SAPA HPAC content to buffer
 *
 *  \param[in]  hpac     Pointer to GPP_SAPA_OCB structure
 *	\param[in]	*hpacHdl
 *  \param[in]  *buffer Pointer to buffer
 *  \param[in]  *byte_pos
 *  \param[in]  *bit_pos
 *
 *  \retval  needed bits (>0) or error code (<0)

 *****************************************************************************/
GPPLONG gpp_sapa_hpac2buffer(const pGPP_SAPA_HPAC hpac, const SAPA_HPAC_HANDLE *hpacHdl, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
GPPLONG gpp_sapa_buffer2hpac(pGPP_SAPA_HPAC hpac, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);

/******************************************************************************
 *  \brief Write SAPA Area content to buffer
 *
 *  \param[in]  area     Pointer to GPP_SAPA_OCB structure
 *	\param[in]	*gadHdl
 *  \param[in]  *buffer Pointer to buffer
 *  \param[in]  *byte_pos
 *  \param[in]  *bit_pos
 *
 *  \retval  needed bits (>0) or error code (<0)

 *****************************************************************************/
GPPLONG gpp_sapa_area2buffer(const pGPP_SAPA_AREA area, const SAPA_GAD_HANDLE *gadHdl, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
GPPLONG gpp_sapa_buffer2area(pGPP_SAPA_AREA area, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);

/************************************************************************************************************
 * Malloc and free functions for GPP_SAPA_USE_STATES structure
 ************************************************************************************************************/
GPPLONG gpp_sapa_states_free_ocb(GPP_SAPA_USE_STATES *use_states);
GPPLONG gpp_sapa_states_malloc_ocb(GPP_SAPA_USE_STATES *use_states);

/***********************************************************************************************************************************************************
 * Functions Required In Data Conversion From And To Buffer/Structure
 ***********************************************************************************************************************************************************/
static GPPLONG gpp_sapa_sv_bitmask2buffer(GPPUINT8 sv_prn_bits, GPPUINT1 sys, GPPUINT1 *svlist, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_buffer2sv_bitmask(GPPUINT8 *sv_prn_bits, GPPUINT1 sys, GPPUINT1 *svlist, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);

static GPPLONG gpp_sapa_bias_bitmask2buffer(GPPUINT4 sig_prn_bits, GPPUINT1 sys, GPPUINT1 *siglist, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
static GPPLONG gpp_sapa_bias_buffer2bitmask(GPPUINT1 sys, GPPUINT1 *siglist, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);

/*************************************************************************************************************************************
 * Declaration Of Add Data To Structure For OCB
 **************************************************************************************************************************************/
GPPLONG gpp_sapa_ocb_malloc_sv(pGPP_SAPA_OCB ocb);
GPPLONG gpp_sapa_ocb_free_ocb(pGPP_SAPA_OCB ocb);
GPPLONG gpp_sapa_ocb_add_sv(pGPP_SAPA_OCB ocb, GPPUINT1 sys, GPPUINT1 sat, const pGPP_SAPA_OCB_SV pset);
GPPLONG gpp_sapa_ocb_add_orb(pGPP_SAPA_OCB ocb, GPPUINT1 sys, GPPUINT1 sat, const pGPP_SAPA_OCB_SV_ORB pset);
GPPLONG gpp_sapa_ocb_add_clk(pGPP_SAPA_OCB ocb, GPPUINT1 sys, GPPUINT1 sat, const pGPP_SAPA_OCB_SV_CLK pset);
GPPLONG gpp_sapa_ocb_add_pb(pGPP_SAPA_OCB ocb, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 sig, const pGPP_SAPA_OCB_SV_BIAS_PB pset);
GPPLONG gpp_sapa_ocb_add_header(pGPP_SAPA_OCB ocb, GPPUINT1 sys, const pGPP_SAPA_OCB_HEADER pset);
GPPLONG gpp_sapa_ocb_add_cb(pGPP_SAPA_OCB ocb, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 sig, const pGPP_SAPA_OCB_SV_BIAS_CB pset);

/********************************************************************************************************************************************
 * Declaration Of Add Data To Structure For HPAC
 *********************************************************************************************************************************************/
GPPLONG gpp_sapa_hpac_free_hpac(pGPP_SAPA_HPAC hpac);
GPPLONG gpp_sapa_hpac_add_header(pGPP_SAPA_HPAC hpac, const pGPP_SAPA_HPAC_HEADER pset);
GPPLONG gpp_sapa_hpac_add_area(pGPP_SAPA_HPAC hpac, GPPUINT1 area, const pGPP_SAPA_HPAC_AREA pset);
GPPLONG gpp_sapa_hpac_add_tropo(pGPP_SAPA_HPAC hpac, GPPUINT1 area, const pGPP_SAPA_HPAC_TROPO pset);
GPPLONG gpp_sapa_hpac_add_tropo_poly_coeff_block(pGPP_SAPA_HPAC hpac, GPPUINT1 area, const pGPP_SAPA_HPAC_TROPO_POLY_COEFFICIENT_BLOCK pset);
GPPLONG gpp_sapa_hpac_add_tropo_grid_block(pGPP_SAPA_HPAC hpac, GPPUINT1 area, const pGPP_SAPA_HPAC_TROPO_GRID_BLOCK pset);
GPPLONG gpp_sapa_hpac_add_iono(pGPP_SAPA_HPAC hpac, GPPUINT1 area, const pGPP_SAPA_HPAC_IONO pset);
GPPLONG gpp_sapa_hpac_add_iono_sat_block(pGPP_SAPA_HPAC hpac, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 area, const pGPP_SAPA_HPAC_IONO_SAT_BLOCK pset);
GPPLONG gpp_sapa_hpac_add_iono_sat_poly_block(pGPP_SAPA_HPAC hpac, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 area, const pGPP_SAPA_HPAC_IONO_SAT_POLY pset);
GPPLONG gpp_sapa_hpac_add_iono_sat_coeff_block(pGPP_SAPA_HPAC hpac, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 area, const pGPP_SAPA_HPAC_IONO_SAT_COEFFICIENT pset);
GPPLONG gpp_sapa_hpac_add_iono_sat_grid_block(pGPP_SAPA_HPAC hpac, GPPUINT1 sys, GPPUINT1 sat, GPPUINT1 area, const pGPP_SAPA_HPAC_IONO_GRID_BLOCK pset);

/********************************************************************************************************************************************
 * Declaration Of Add Data To Structure For Area
 *********************************************************************************************************************************************/
GPPLONG gpp_sapa_area_free_area(pGPP_SAPA_AREA area);
GPPLONG gpp_sapa_area_add_header(pGPP_SAPA_AREA p_area, const pGPP_SAPA_AREA_DEF_HEADER pset);
GPPLONG gpp_sapa_area_add_area_def(pGPP_SAPA_AREA p_area, GPPUINT1 area, const pGPP_SAPA_AREA_DEF_BLOCK pset);

/********************************************************************************************************************************************
 * Declaration Of Add Data To Structure For Handle
 *********************************************************************************************************************************************/
GPPLONG gpp_sapa_hpac_handle_add_hpac_iono_handle(pSAPA_HANDLE sapaHdl, GPPUINT1 config, GPPUINT1 area, const pSAPA_HPAC_HANDLE_IONO pset);
GPPLONG gpp_sapa_hpac_handle_add_hpac_tropo_handle(pSAPA_HANDLE sapaHdl, GPPUINT1 config, GPPUINT1 area, const pSAPA_HPAC_HANDLE_TROPO pset);

/********************************************************************************************************************************************
 * Declaration Of Transport Layer SAPA message
 *********************************************************************************************************************************************/
GPPLONG gpp_sapa_ocb_buffer_to_sapa_buffer(const GPPUCHAR *ocb_buffer, GPPLONG len_sapa_bits, GPPLONG ea_flag, GPPLONG message_crc_type, GPPLONG crc_frame, GPPUCHAR *sapa_buffer);
GPPLONG gpp_sapa_sapa_buffer_to_ocb_buffer(GPPUCHAR *ocb_buffer, GPPLONG *len_sapa_bits, GPPLONG *ea_flag, GPPLONG *message_crc_type, GPPLONG *crc_frame, const GPPUCHAR *sapa_buffer);
GPPLONG gpp_sapa_hpac_buffer_to_sapa_buffer(const GPPUCHAR *hpac_buffer, GPPLONG len_sapa_bits, GPPLONG ea_flag, GPPLONG message_crc_type, GPPLONG crc_frame, GPPUCHAR *sapa_buffer);
GPPLONG gpp_sapa_sapa_buffer_to_hpac_buffer(GPPUCHAR *hpac_buffer, GPPLONG *len_sapa_bits, GPPLONG *ea_flag, GPPLONG *message_crc_type, GPPLONG *crc_frame, const GPPUCHAR *sapa_buffer);
GPPLONG gpp_sapa_area_buffer_to_sapa_buffer(const GPPUCHAR *area_buffer, GPPLONG len_sapa_bits, GPPLONG ea_flag, GPPLONG message_crc_type, GPPLONG crc_frame, GPPUCHAR *sapa_buffer);
GPPLONG gpp_sapa_sapa_buffer_to_area_buffer(GPPUCHAR *area_buffer, GPPLONG *len_sapa_bits, GPPLONG *ea_flag, GPPLONG *message_crc_type, GPPLONG *crc_frame, const GPPUCHAR *sapa_buffer);

/******************************************************************************
 * Internal Functions
 *****************************************************************************/

 /******************************************************************************
  * Return Seconds passed in the hour when data is received
  *****************************************************************************/
GPPINT gpp_sapa_get_hourly_time_tag(GPPINT seconds_of_week);

/******************************************************************************
  * Returns seconds passed since the beginning including all gps_weeks
  *****************************************************************************/
GPPINT gpp_sapa_get_full_time_tag(GPPINT gps_week, GPPINT seconds_of_week);

/******************************************************************************
  * Returns Orbit ,Clock and  Bias flag value
  *****************************************************************************/
void gpp_sapa_get_ocb_flag_value(GPPUINT1 ocb_present_flag, GPPUINT1* o_flag, GPPUINT1* c_flag, GPPUINT1* b_flag);

/******************************************************************************
  * Set OCB present flag bit
  *****************************************************************************/
void gpp_sapa_set_ocb_present_flags(GPPUINT1 *ref_obj, int index, int setvalue);

/******************************************************************************
  * Split tokens
  *****************************************************************************/
GPPUINT4 gpp_sapa_split_arg_to_tokens(char **_buffer, GPPUCHAR **tok);

/******************************************************************************
  * Returns 1 if a bit at position pos in cons_bits is set else return 0
  *****************************************************************************/
GPPUINT1 gpp_sapa_get_constellation_present_bit(GPPUINT2 cons_bits, GPPUINT1 pos);

/******************************************************************************
  * Returns highest order of cons_bit set
  *****************************************************************************/
GPPUINT1 gpp_sapa_get_highest_cons_set(GPPUINT2 cons_bit);

/******************************************************************************
  * Sets cons_bit position
  *****************************************************************************/
GPPUINT1 gpp_sapa_set_cons_bit(GPPUINT1 cons_bits, GPPUINT1 pos);

/******************************************************************************
  * Sets the bit position according to the index value
  *****************************************************************************/
void gpp_sapa_set_hpac_bits(GPPUINT1 *set_bits, GPPUINT1 value);

/******************************************************************************
  * Returns the set bit position in the arguement, -1 if no SetBit
  *****************************************************************************/
GPPUINT1 gpp_sapa_get_hpac_bits(GPPUINT1 *set_bits);

/******************************************************************************
  * Returns the set bit position in the arguement, -1 if no SetBit
  *****************************************************************************/
GPPUINT1 gpp_sapa_get_config_bits(GPPUINT1 set_bits);

/*************************************************************************************************
  * Get an index list(starting with 0) of Set Bits in bitmask(prn_bits). BitMask  contains 66 bits
  ************************************************************************************************/
void gpp_sapa_get_svlist(GPPUINT8 prn_bits, GPPUINT1 *svlist);


/*************************************************************************************************
  * Get an index list(starting with 0) of Set Bits in bitmask(prn_bits). BitMask  contains 18 bits
  ************************************************************************************************/
void gpp_sapa_get_syslist(GPPUINT8 sys_bits, GPPUINT1 *syslist);

/*************************************************************************************************
  * Get an index list(starting with 0) of Set Bits in bitmask(prn_bits). BitMask  contains 34 bits
  ************************************************************************************************/
void gpp_sapa_get_siglist(GPPUINT4 sig_bits, GPPUINT1 *siglist);

/*************************************************************************************************
  * Get an index list(starting with 0) of Set Bits in bitmask(prn_bits). BitMask  contains 34 bits
  ************************************************************************************************/
void gpp_sapa_get_configlist(GPPUINT8 config_bits, GPPUINT1 *configlist);

/*************************************************************************************************
  * Declaration Of Float To Buffer Add Buffer To Float
 ************************************************************************************************/
extern void gpp_sapa_float2buffer(GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos, GPPDOUBLE min, GPPDOUBLE max, GPPUINT1 bits, GPPDOUBLE res, GPPUINT2 *invalid, GPPDOUBLE value);
GPPUINT1 gpp_sapa_buffer2float(const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos, GPPDOUBLE min, GPPUINT1 bits, GPPDOUBLE res, const GPPUINT2 *invalid, GPPDOUBLE *value);

/*************************************************************************************************
  *Get Delaration between the byte abd bit pos
 ************************************************************************************************/
GPPLONG gpp_sapa_get_bit_diff(GPPLONG byte_pos, GPPLONG bit_pos, GPPLONG byte_pos0, GPPLONG bit_pos0);

/************************************************************************************************
  * Get Bytes from length of bits
*************************************************************************************************/
GPPLONG length_bytes_from_bits(GPPLONG b);

/*************************************************************************************************
  * Get the total bits of location
  ************************************************************************************************/
GPPLONG total_bits(GPPLONG *byte, GPPLONG *bits);

/*************************************************************************************************
  * Set Bits in bitmask(area_bits). BitMask  contains 64 bits
  ************************************************************************************************/
void gpp_sapa_set_area_bits(GPPUINT8*area_bits, int value);

/*************************************************************************************************
  * Get an index list(starting with 0) of Set Bits in bitmask(area_bits). BitMask  contains 64 bits
  ************************************************************************************************/
void gpp_sapa_get_area_bits_value(GPPUINT8*area_bits, GPPUINT8*arr);

/************************************************************************************************************
 *	\brief Double To Long Conversion
 ************************************************************************************************************/
GPPULONG double2long(GPPDOUBLE val, GPPDOUBLE Res, GPPDOUBLE Rmin);
GPPLONG float2long(GPPDOUBLE val, GPPDOUBLE Res, GPPDOUBLE Rmin, GPPLONG Lmax, GPPLONG Lmin, GPPUINT2 *invalid);

#ifdef __WATCOMC__
#pragma on (unreferenced)
#endif


#ifdef __cplusplus
}
#endif

#endif //GPP_SAPA_H_
