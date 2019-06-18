#ifndef SSRM2SAPA_UTIL_H
#define SSRM2SAPA_UTIL_H

#ifdef __cplusplus
extern "c" {
#endif

#ifdef GPP_GNSS_DLL_EXPORT
#include "creatdll.h"
#endif

//#include "platform.h"
#include "compiler.h"			// GPPUSHORT
//#include "rtcm30.h"				/* RTCM_SSRG_TROPO, RTCM_SSRG_IONO */
//#include "gridfile.h"			/* GRIDFILE_LLH */
#include "gpptime.h"			/* GPPT_WNT */
//#include "gnssr2obs.h"			/* GNS2O_RxSSRGParameters */
//#include "gnss_obs.h"			// GNSS_SATELLITE_QIX_BIAS

#include "gpp_sapa.h"			//GPP_SAPA structures



#ifdef _win32
#pragma pack(push,1)
#endif

//GPPLONG GnssrSSR_Clocks2SAPA(GPP_SAPA_USE_STATES *sapa_states,const SSR_GEN_USE_STATES *use_states);
//GPPLONG GnssrSSR_SAPA2Clocks(const GPP_SAPA_USE_STATES *sapa_states, SSR_GEN_USE_STATES *use_states, SSR_GEN_CONTROL *gen_ctl);

//GPPLONG GnssrSSR_Orbits2SAPA(GPP_SAPA_USE_STATES *sapa_states, const SSR_GEN_USE_STATES *use_states);
//GPPLONG GnssrSSR_SAPA2Orbits(const GPP_SAPA_USE_STATES *sapa_states, SSR_GEN_USE_STATES *use_states, SSR_GEN_CONTROL *gen_ctl);

/*GPPLONG GnssrSSR_Orbits2SAPA(GPP_SAPA_USE_STATES *sapa_states, SSRZ_HANDLE *ssrzHdl, const SSR_GEN_USE_STATES *use_states);
GPPLONG GnssrSSR_SAPA2Orbits(const GPP_SAPA_USE_STATES *sapa_states, SSRZ_HANDLE *ssrzHdl, SSR_GEN_USE_STATES *use_states, pSSR_GEN_CONTROL gen_ctl);

GPPLONG GnssrSSR_Cbs2SAPA(GPP_SAPA_USE_STATES *sapa_states, SSRZ_HANDLE *ssrzHdl, const SSR_GEN_USE_STATES *use_states);
GPPLONG GnssrSSR_SAPA2Cbs(const GPP_SAPA_USE_STATES *sapa_states, SSRZ_HANDLE *ssrzHdl, SSR_GEN_USE_STATES *use_states, pSSR_GEN_CONTROL gen_ctl);

GPPLONG GnssrSSR_Pbs2SAPA(GPP_SAPA_USE_STATES *sapa_states, SSRZ_HANDLE *ssrzHdl, const SSR_GEN_USE_STATES *use_states);
GPPLONG GnssrSSR_SAPA2Pbs(const GPP_SAPA_USE_STATES *sapa_states, SSRZ_HANDLE *ssrzHdl, SSR_GEN_USE_STATES *use_states, pSSR_GEN_CONTROL gen_ctl);
*/


#ifdef HAVE_PRAGMA_PACK
#pragma pack(pop)
#endif

#ifdef GPP_GNSS_DLL_EXPORT
#define GPP_NO_DLL_IMPORT
#include "creatdll.h"
#undef GPP_NO_DLL_IMPORT
#endif

#ifdef __cplusplus
}
#endif


#endif /* SSRM2SAPA_UTIL_H */
