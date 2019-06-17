// Test SAPA functions
#include <stdlib.h>
#include <stdio.h>

#include "platform.h"
#include "gnssbase.h"
#include "gpp_sapa.h"
#include "ssrm2sapa_util.h"
#include "gnssrgen.h" /* SSR_GEN_USE_STATES */
#include "gnssrtxt.h"






GPPUINT1 SV_GPS[4]={0,5,1,12};







static GPPLONG set_ocb_header(GPP_SAPA_USE_STATES *sapa_states)
{
	GPPLONG rc=0;
	GPP_SAPA_OCB_HEADER header={0,};

	if(!sapa_states) return -1;
    if(!sapa_states->ocb){
		if(rc=gpp_sapa_states_malloc_ocb(sapa_states)) return rc;
    }


	header.message_sub_type=0;
	header.sol_id=2;
	header.sol_processor_id=2;
	header.time_tag_type=1;
	header.time_tag=2000;
	header.yaw_flag=0;

	if(rc=gpp_sapa_ocb_add_header(sapa_states->ocb, GPP_SAPA_GPS, &header)) return rc;
	if(rc=gpp_sapa_ocb_add_header(sapa_states->ocb, GPP_SAPA_GLO, &header)) return rc;

	return 0;
}//set_ocb_header()


static GPPLONG set_use_states(SSR_GEN_USE_STATES *use_states, SSR_GEN_CONTROL *gen_ctl)
{
	GPPUINT1 sys;
	GPPUINT4 prn;

	SSR_GEN_SV_CLOCK_CORRECTION_SET clocks={0,};
	SSR_GEN_SV_ORBIT_CORRECTION_SET orbits={0,};

	//clock
	clocks.d_clock[0]=1.337245;
	clocks.iodc=10;

	//orbits
	orbits.d_orbit[0]=4.7131;
	orbits.d_orbit[1]=-1.9181;
	orbits.d_orbit[2]=+2.43281;
	orbits.iode=12;

	sys=GNSS_SYS_GPS;
	prn=5+GNSS_SYS_SVN_MIN[sys];
	GnssrSSRGenAddClockCorrections(gen_ctl, use_states, sys, prn, &clocks);
	GnssrSSRGenAddOrbitCorrections(gen_ctl, use_states, sys, prn, &orbits);

	prn=1+GNSS_SYS_SVN_MIN[sys];
	GnssrSSRGenAddClockCorrections(gen_ctl, use_states, sys, prn, &clocks);
	GnssrSSRGenAddOrbitCorrections(gen_ctl, use_states, sys, prn, &orbits);

	prn=10+GNSS_SYS_SVN_MIN[sys];
	GnssrSSRGenAddClockCorrections(gen_ctl, use_states, sys, prn, &clocks);
	GnssrSSRGenAddOrbitCorrections(gen_ctl, use_states, sys, prn, &orbits);


	sys=GNSS_SYS_GLO;
	prn=9+GNSS_SYS_SVN_MIN[sys];
	GnssrSSRGenAddClockCorrections(gen_ctl, use_states, sys, prn, &clocks);
	GnssrSSRGenAddOrbitCorrections(gen_ctl, use_states, sys, prn, &orbits);

	prn=2+GNSS_SYS_SVN_MIN[sys];
	GnssrSSRGenAddClockCorrections(gen_ctl, use_states, sys, prn, &clocks);
	GnssrSSRGenAddOrbitCorrections(gen_ctl, use_states, sys, prn, &orbits);

	prn=3+GNSS_SYS_SVN_MIN[sys];
	GnssrSSRGenAddClockCorrections(gen_ctl, use_states, sys, prn, &clocks);
	GnssrSSRGenAddOrbitCorrections(gen_ctl, use_states, sys, prn, &orbits);

	return 0;
}




static GPPLONG gpp_sapa_config_add_ocb_config(SAPA_HANDLE *sapaHdl, GPPUINT1 sys, const SAPA_OCB_HANDLE *pset, FILE *fp)
{
	GPPLONG rc;
	GPPUINT1 icnfg=0;

	if(!sapaHdl) return -1;
	if(!pset) return GPP_SAPA_ERR_INVALID_OCB_HANDLE;

	if(sys>=SAPA_MAX_SYS) return GPP_SAPA_ERR_INVALID_SYS;

	if(!sapaHdl->ocbHdl){
		if(rc=gpp_sapa_handle_malloc_ocbHdl(sapaHdl)) return rc;
	}


	if(sapaHdl->ocb_config_bits[sys]>=(1<<GPP_SAPA_MAX_OCB_CONFIGS)){
		fprintf(fp, "SSRM2SAPA ERROR: Too many OCB configs!\n");
		return GPP_SAPA_ERR_INVALID_OCB_HANDLE;
	}

	for(icnfg=0; icnfg<GPP_SAPA_MAX_OCB_CONFIGS; icnfg++){
		if(!(sapaHdl->ocbHdl[sys][icnfg])){
			sapaHdl->ocbHdl[sys][icnfg]=(SAPA_OCB_HANDLE*)calloc(1, sizeof(SAPA_OCB_HANDLE));
			if(!(sapaHdl->ocbHdl[sys][icnfg])) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
			memcpy(sapaHdl->ocbHdl[sys][icnfg], pset, sizeof(SAPA_OCB_HANDLE));
			sapaHdl->ocb_config_bits[sys]|=(1<<icnfg);
			break;
		}
	}
	return 0;
}//gpp_sapa_config_set_OCB_bits()


int main(){

	FILE *fp=stdout;
	GPPLONG rc=0, rcRCVR=0;
	GPPUINT1 icnfg;

	GPP_SAPA_USE_STATES sapa_states={0,};
	GPP_SAPA_USE_STATES sapa_statesRCVR={0,};

	SSR_GEN_USE_STATES use_states={0,};
	SSR_GEN_USE_STATES use_statesRCVR={0,};

	SSR_GEN_CONTROL *gen_ctl=0;

	GPPUCHAR *buffer=calloc(2048, sizeof(GPPUCHAR));

	SAPA_HANDLE *sapaHdl=NULL;
	SAPA_OCB_HANDLE tmpOcbHdl={0,};


	rc=gpp_sapa_handle_malloc_handle(&sapaHdl);


	if(!sapa_statesRCVR.ocb){
		rc=gpp_sapa_states_malloc_ocb(&sapa_statesRCVR);
	}

	// configure three different S-M 0-0 (OCB GPS) messages
	tmpOcbHdl.ocb_bits=GPP_SAPA_OCB_BITS_ORB;
	gpp_sapa_config_add_ocb_config(sapaHdl, GPP_SAPA_GPS, &tmpOcbHdl , fp); //only orbit corrections, sapaHdl->ocbHdl[GPP_SAPA_GPS][0]

	tmpOcbHdl.ocb_bits=GPP_SAPA_OCB_BITS_CLK;
	gpp_sapa_config_add_ocb_config(sapaHdl, GPP_SAPA_GPS, &tmpOcbHdl , fp);//only clock corrections, sapaHdl->ocbHdl[GPP_SAPA_GPS][1]

	tmpOcbHdl.ocb_bits=(GPP_SAPA_OCB_BITS_PB|GPP_SAPA_OCB_BITS_CB);
	gpp_sapa_config_add_ocb_config(sapaHdl, GPP_SAPA_GPS, &tmpOcbHdl , fp);//only bias corrections, sapaHdl->ocbHdl[GPP_SAPA_GPS][2]


	// get input data
	rc=set_use_states(&use_states, gen_ctl);

	rc=set_ocb_header(&sapa_states);
	rc=GnssrSSR_Clocks2SAPA(&sapa_states, &use_states);
	rc=GnssrSSR_Orbits2SAPA(&sapa_states, &use_states);

	gpp_sapa_debug_fprintf_ocb(sapa_states.ocb, stdout);


	for(icnfg=0; icnfg<3; icnfg++){
		rc=gpp_sapa_ocb2buffer(sapa_states.ocb, sapaHdl->ocbHdl[GPP_SAPA_GPS][icnfg], buffer, NULL, NULL);
		printf("OCB2buffer %d bits\n", rc);
		rcRCVR=gpp_sapa_buffer2ocb(sapa_statesRCVR.ocb, buffer, NULL, NULL);
		printf("buffer2OCB %d bits\n", rc);
	}

	rc=GnssrSSR_SAPA2Clocks(&sapa_statesRCVR, &use_statesRCVR, gen_ctl);
	rc=GnssrSSR_SAPA2Orbits(&sapa_statesRCVR, &use_statesRCVR, gen_ctl);

	gpp_sapa_debug_fprintf_ocb(sapa_statesRCVR.ocb, stdout);



	gpp_sapa_handle_free_handle(&sapaHdl);
	if(buffer) free(buffer);
	buffer=NULL;



	return (0);
}//main()
