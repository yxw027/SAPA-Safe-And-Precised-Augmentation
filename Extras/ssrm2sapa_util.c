/*
 * SAPA output and input from and to SSR_GEN_USE_STATES structure.
 */




#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <assert.h>

#include "platform.h"
#include "compiler.h"
#include "gnssbase.h"			/* macro GNSS_GET_ID_LIST_FROM_BITFIELDS_64 */

#include "ssrm2sapa_util.h"
#include "gpp_sapa.h"
#include "gnssrgen.h" /* SSR_GEN_USE_STATES */
#include "gnssrgen_mangle.h"





#define SAPA_RESERVED 255
#define GPP_SAPA_MSG_MAX_SYS 16
static const GPPUINT1 GPP_SAPA_MSG_SYS[GPP_SAPA_MAX_SYS]={	GNSS_SYS_GPS,	// GNSS_SYS_GPS		0
															GNSS_SYS_GLO,	// GNSS_SYS_GLO		1
															SAPA_RESERVED,	// Reserved 2
															SAPA_RESERVED,	// Reserved 3
															SAPA_RESERVED,	// Reserved 4
															SAPA_RESERVED,	// Reserved 5
															SAPA_RESERVED,	// Reserved 6
															SAPA_RESERVED,	// Reserved 7
															SAPA_RESERVED,	// Reserved 8
															SAPA_RESERVED,	// Reserved 9
															SAPA_RESERVED,	// Reserved 10
															SAPA_RESERVED,	// Reserved 11
															SAPA_RESERVED,	// Reserved 12
															SAPA_RESERVED,	// Reserved 13
															SAPA_RESERVED,	// Reserved 14
															SAPA_RESERVED};	// Reserved 15



/************************************************************************************************************/

GPPLONG GnssrSSR_Clocks2SAPA(GPP_SAPA_USE_STATES *sapa_states, const SSR_GEN_USE_STATES *use_states)
{
	GPPLONG rc;
	GPPUINT1 isys, sys, isat, sat;
	GPPUCHAR svlist[66], *pp;

	GPP_SAPA_OCB *ocb=NULL;
	SSR_GEN_SV_CLOCK_CORRECTION_SET *clocks=NULL;
	SSR_GEN_SV_ORBIT_CORRECTION_SET *orbits=NULL;
	GPP_SAPA_OCB_SV_CLK clk;

    if(!use_states->clocks) return 0;

    if(!sapa_states->ocb){
		if(rc=gpp_sapa_states_malloc_ocb(sapa_states)) return rc;
    }
	ocb=sapa_states->ocb;

    for(isys=0; isys<GNSS_SYS_MAX_SYS; isys++){
		sys=isys;

		if(GPP_SAPA_MSG_SYS[sys]==SAPA_RESERVED) continue;
		if(!use_states->clock_prn_bits[sys]) continue;

		pp=(GPPUCHAR *)&use_states->clock_prn_bits[sys];
		GNSS_GET_ID_LIST_FROM_BITFIELDS_64(pp,svlist);

		for(isat=1; isat<=svlist[0]; isat++){
			sat=svlist[isat]-1;

			if(!(clocks=use_states->clocks[sys][sat])) continue;

			memset(&clk, 0, sizeof(GPP_SAPA_OCB_SV_CLK));

			clk.clk_correction=clocks->d_clock[0];

			memcpy(&clk.wnt, &use_states->wn_t, sizeof(GPPT_WNT));

			//get IODE from orbit
			if(GNSS_HAS_IDX_IN_BITS_64(use_states->orbit_prn_bits[sys], sat)){
				if(orbits=use_states->orbits[sys][sat]){
					//TODO iode_continuity
				}
			}

			if(rc=gpp_sapa_ocb_add_clk(ocb, GPP_SAPA_MSG_SYS[sys], sat, &clk) ) return rc;

		}//isat
	}//isys
	return 0;
}//GnssrSSR_Clocks2SAPA()

/***********************************************************************************************************/

GPPLONG GnssrSSR_SAPA2Clocks(const GPP_SAPA_USE_STATES *sapa_states, SSR_GEN_USE_STATES *use_states, SSR_GEN_CONTROL *gen_ctl)
{
	GPPUINT1 isys, sys, isat, sat;
	GPPUINT4 prn;
	GPPUCHAR svlist[66], *pp;

	GPP_SAPA_OCB *ocb=NULL;
	GPP_SAPA_OCB_SV *sv=NULL;
	GPP_SAPA_OCB_SV_CLK *clk;

	SSR_GEN_SV_CLOCK_CORRECTION_SET clocks;

	if(!sapa_states) return -1;
	if(!use_states) return -1;

	if(!(ocb=sapa_states->ocb)) return 0;

	for(isys=0; isys<GPP_SAPA_MAX_SYS; isys++){
		sys=isys;

		if(!ocb->sv_prn_bits[sys]) continue;

		pp=(GPPUCHAR *)&ocb->sv_prn_bits[sys];
		GNSS_GET_ID_LIST_FROM_BITFIELDS_64(pp,svlist);

		for(isat=1; isat<=svlist[0]; isat++){
			sat=svlist[isat]-1;
			prn=sat+GNSS_SYS_SVN_MIN[GPP_SAPA_MSG_SYS[sys]];

			if(!(sv=ocb->sv[sys][sat])) continue;

			memset(&clocks, 0, sizeof(clocks));

			if(sv->ocb_bits&(1<<GPP_SAPA_OCB_FLAG_IDX_CLK)){
				if(!(clk=sv->clk)) continue;

				clocks.d_clock[0]=clk->clk_correction;

				GnssrSSRGenAddClockCorrections(gen_ctl, use_states, GPP_SAPA_MSG_SYS[sys], prn, &clocks);

printf("SAPA2Clocks %1c%02d\n", GNSS_SYS_SYS_RINEX_CODE[sys], sat+1);

			}//flag

		}//isat
	}//isys
	return 0;
}//GnssrSSR_SAPA2Clocks()

/************************************************************************************************************/

GPPLONG GnssrSSR_Orbits2SAPA(GPP_SAPA_USE_STATES *sapa_states, const SSR_GEN_USE_STATES *use_states)
{
	GPPLONG rc;
	GPPUINT1 isys, sys, isat, sat;
	GPPUCHAR svlist[66], *pp;

	SSR_GEN_SV_ORBIT_CORRECTION_SET *orbits=NULL;
	GPP_SAPA_OCB_SV_ORB orb;

    if(!use_states->clocks) return 0;

    if(!sapa_states->ocb){
		if(rc=gpp_sapa_states_malloc_ocb(sapa_states)) return rc;
    }

    for(isys=0; isys<GNSS_SYS_MAX_SYS; isys++){
		sys=isys;

		if(GPP_SAPA_MSG_SYS[sys]==SAPA_RESERVED) continue;
		if(!use_states->orbit_prn_bits[sys]) continue;

		pp=(GPPUCHAR *)&use_states->orbit_prn_bits[sys];
		GNSS_GET_ID_LIST_FROM_BITFIELDS_64(pp,svlist);

		for(isat=1; isat<=svlist[0]; isat++){
			sat=svlist[isat]-1;

			if(!(orbits=use_states->orbits[sys][sat])) continue;

			memset(&orb, 0, sizeof(GPP_SAPA_OCB_SV_ORB));

			orb.orb_radial_correction=orbits->d_orbit[0];
			orb.orb_along_track_correction=orbits->d_orbit[1];
			orb.orb_cross_track_correction=orbits->d_orbit[2];

			memcpy(orb.d_orbit, orbits->d_orbit, 3*sizeof(GPPDOUBLE));
			orb.iode=orbits->iode;
			memcpy(&orb.wnt, &use_states->wn_t, sizeof(GPPT_WNT));


			if(rc=gpp_sapa_ocb_add_orb(sapa_states->ocb, GPP_SAPA_MSG_SYS[sys], sat, &orb) ) return rc;
printf("Orbits2SAPA %1c%02d\n", GNSS_SYS_SYS_RINEX_CODE[sys], sat+1);
		}//isat
	}//isys
	return 0;
}//GnssrSSR_Clocks2SAPA()

/***********************************************************************************************************/

GPPLONG GnssrSSR_SAPA2Orbits(const GPP_SAPA_USE_STATES *sapa_states, SSR_GEN_USE_STATES *use_states, SSR_GEN_CONTROL *gen_ctl)
{
	GPPUINT1 isys, sys, isat, sat;
	GPPUINT4 prn;
	GPPUCHAR svlist[66], *pp;

	GPP_SAPA_OCB *ocb=NULL;
	GPP_SAPA_OCB_SV *sv=NULL;
	GPP_SAPA_OCB_SV_ORB *orb;

	SSR_GEN_SV_ORBIT_CORRECTION_SET orbits;

	if(!sapa_states) return -1;
	if(!use_states) return -1;

	if(!(ocb=sapa_states->ocb)) return 0;

	for(isys=0; isys<GPP_SAPA_MAX_SYS; isys++){
		sys=isys;

		if(!ocb->sv_prn_bits[sys]) continue;

		pp=(GPPUCHAR *)&ocb->sv_prn_bits[sys];
		GNSS_GET_ID_LIST_FROM_BITFIELDS_64(pp,svlist);

		for(isat=1; isat<=svlist[0]; isat++){
			sat=svlist[isat]-1;
			prn=sat+GNSS_SYS_SVN_MIN[GPP_SAPA_MSG_SYS[sys]];

			if(!(sv=ocb->sv[sys][sat])) continue;

			memset(&orbits, 0, sizeof(orbits));

			if(sv->ocb_bits&(1<<GPP_SAPA_OCB_FLAG_IDX_ORB)){
				if(!(orb=sv->orb)) continue;

				orbits.d_orbit[0]=orb->orb_radial_correction;
				orbits.d_orbit[1]=orb->orb_along_track_correction;
				orbits.d_orbit[2]=orb->orb_cross_track_correction;

				memcpy(orbits.d_orbit,orb->d_orbit, 3*sizeof(GPPDOUBLE));
				orbits.iode=orb->iode;

				GnssrSSRGenAddOrbitCorrections(gen_ctl, use_states, GPP_SAPA_MSG_SYS[sys], prn, &orbits);
printf("SAPA2Orbits %1c%02d\n", GNSS_SYS_SYS_RINEX_CODE[sys], sat+1);
			}//flag

		}//isat
	}//isys
	return 0;
}//GnssrSSR_SAPA2Clocks()

