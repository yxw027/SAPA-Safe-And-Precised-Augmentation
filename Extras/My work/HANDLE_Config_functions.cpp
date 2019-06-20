#include<gpp_sapa.h>

GPPLONG gpp_sapa_handle_malloc_ocbHd1(pSAPA_HANDLE sapaHd1)
{
	if (!sapaHd1) return GPP_SAPA_ERR_INVALID_SAPAHD1;

	if (!sapaHd1->ocbHd1)
	{
		GPPUINT1 sys;
		sapaHd1->ocbHd1 = (pSAPA_OCB_HANDLE **)calloc(GPP_MAX_OCB_CONFIGS, sizeof(pSAPA_OCB_HANDLE *));

		if (!sapaHd1->ocbHd1) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;

		for (sys = 0; sys < SAPA_MAX_SYS; sys++)
		{
			sapaHd1->ocbHd1[sys] = (pSAPA_OCB_HANDLE *)calloc(GPP_MAX_OCB_CONFIGS, sizeof(pSAPA_OCB_HANDLE));

			if (!(sapaHd1->ocbHd1[sys])) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
		}
	}

	return 0; //ok

}//gpp_sapa_sapaHd1_malloc_ocbHd1()



static GPPLONG gpp_sapa_config_add_ocb_config(SAPA_HANDLE *sapaHd1, GPPUINT1 sys, const SAPA_OCB_HANDLE *pset, FILE *fp)
{
	GPPLONG rc;
	GPPUINT1 icnfg = 0;

	if (!sapaHd1) return -1;
	if (!pset) return GPP_SAPA_ERR_INVALID_OCB_HANDLE;

	if (sys >= SAPA_MAX_SYS) return GPP_SAPA_ERR_INVALID_SYS;

	if (!sapaHd1->ocbHd1)
		if (rc = gpp_sapa_handle_malloc_ocbHd1(sapaHd1))
			return rc;
	
	if (sapaHd1->ocb_config_bits[sys] >= (1 << GPP_SAPA_MAX_OCB_CONFIGS))
	{
		fprintf(fp, "SSRM2SAPA ERROR: TOO many OCB configs!\n");
		return GPP_SAPA_ERR_INVALID_OCB_HANDLE;
	}

	for (icnfg = 0; icnfg < GPP_MAX_OCB_CONFIGS; icnfg++)
	{
		if (!sapaHd1->ocbHd1[sys][icnfg])
		{
			sapaHd1->ocbHd1[sys][icnfg] = (SAPA_OCB_HANDLE*)calloc(1, sizeof(SAPA_OCB_HANDLLE));
			if (!(sapaHd1->ocbHd1[sys][icnfg])) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;

			memcpy(sapaHd1->ocbHd1[sys][icnfg], pset, sizeof(SAPA_OCB_HANDLE));
			sapaHd1->ocb_config_bits[sys] = (1 << icnfg);
			break;
		}
	}

}

//==================================================================================================================================
// hpac malloc


GPPLONG gpp_sapa_handle_malloc_hpacHd1(pSAPA_HANDLE sapaHd1)
{
	if (!sapaHd1) return GPP_SAPA_ERR_INVALID_SAPAHD1;

	if (!sapaHd1->hpacHd1)
	{
		GPPUINT1 area,sys,config;
		for (sys = 0; sys < SAPA_MAX_SYS; sys++)
		{
			for (area = 0; area < SAPA_MAX_AREA; area++)
			{
				sapaHd1->hpacHd1[sys][area] = (pSAPA_HPAC_HANDLE*)calloc(GPP_MAX_HPAC_AREA, sizeof(pSAPA_HPAC_HANDLE));
				if (!sapaHd1->hpacHd1[sys][area]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;

				for (sat = 0; sat < SAPA_MAX_SAT; sat++)
				{
					sapaHd1->hpacHd1[sys][area][sat] = (pSAPA_HPAC_HANDLE)calloc(GPP_MAX_HPAC_SAT, sizeof(SAPA_HPAC_HANDLE));

					if (!sapaHd1->hpacHd1[sys][area][sat]) return GPP_SAPPA_ERR_NOT_ENOUGH_MEMORY;
				}
			}
		}
		
	}
	return 0; //ok

}//gpp_sapa_sapaHd1_malloc_hpacHd1()



static GPPLONG gpp_sapa_config_add_hpac_config(SAPA_HANDLE *sapaHd1, GPPUINT1 sys, const SAPA_HPAC_HANDLE *pset, FILE *fp)
{
	GPPLONG rc;
	GPPUINT1 icnfg = 0, sys, sat;

	if (!sapaHd1) return -1;
	if (!pset) return GPP_SAPA_ERR_INVALID_HPAC_HANDLE;

	if (sys >= SAPA_MAX_SYS) return GPP_SAPA_ERR_INVALID_SYS;

	if (!sapaHd1->hpacHd1)
		if (rc = gpp_sapa_handle_malloc_hpacHd1(sapaHd1))
			return rc;

	//define GPP_MAX_HPAC_CONFIGS

	for (sys = 0; sys < SAPA_MAX_SYS; sys++)
	{
		for (icnfg = 0; icnfg < GPP_MAX_HPAC_CONFIGS; icnfg++)
		{
			if (!sapaHd1->hpacHd1[sys][icnfg])
			{
				sapaHd1->hpacHd1[sys][icnfg] = (SAPA_HPAC_HANDLE*)calloc(1, sizeof(SAPA_HPAC_HANDLE));
				if (!(sapaHd1->hpacHd1[sys][icnfg])) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;

				memcpy(sapaHd1->hpacHd1[sys][icnfg], pset, sizeof(SAPA_HPAC_HANDLE));
				break;
			}
		}

	}
}


//================================================================================================================================

static GPPLONG gpp_sapa_config_add_gad_config(SAPA_HANDLE *sapaHd1, const SAPA_GAD_HANDLE *pset, FILE *fp)
{

	GPPUINT1 icnfg = 0;

	if (!sapaHd1) return -1;
	if (!pset) return GPP_SAPA_ERR_INVALID_GAD_HANDLE;

	//if (sys >= SAPA_MAX_SYS) return GPP_SAPA_ERR_INVALID_SYS;

	//if (!sapaHd1->gadHd1)
	//	if (rc = gpp_sapa_handle_malloc_gadHd1(sapaHd1))
	//		return rc;
	
	sapaHd1->gadHd1 = (SAPA_HPAC_HANDLE*)calloc(1, sizeof(SAPA_HPAC_HANDLE));

	memcpy(sapaHd1->gadHd1, pset, sizeof(SAPA_GAD_HANDLE));

}
	
