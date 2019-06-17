GPPLONG gpp_sapa_config_add_gad_config(SAPA_HANDLE *sapaHdl, GPPUINT1 sys, const SAPA_GAD_HANDLE *pset, FILE *fp)
{
	if (!sapaHdl) return -1;
	if (!pset) return GPP_SAPA_ERR_INVALID_GAD_HANDLE;

	sapaHdl->gadHdl = (SAPA_GAD_HANDLE*)calloc(1, sizeof(SAPA_GAD_HANDLE));
	memcpy(sapaHdl->gadHdl, pset, sizeof(SAPA_GAD_HANDLE));
	return 0; //ok
}
Mridul Gupta(14.06.2019 17:57) :
	GPPLONG gpp_sapa_handle_malloc_hpacHdl(pSAPA_HANDLE sapaHdl)
{
	if (!sapaHdl) return -1;

	if (!sapaHdl->hpacHdl)
	{
		sapaHdl->hpacHdl = (pSAPA_HPAC_HANDLE)calloc(1, sizeof(SAPA_HPAC_HANDLE));
		if (!sapaHdl->hpacHdl) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;

		GPPUINT1 area, sys, sat;

		for (area = 0; area < GPP_SAPA_MAX_AREA_COUNT; area++)
		{
			sapaHdl->hpacHdl->hpac_area_handle[area] = (pSAPA_HPAC_HANDLE_AREA)calloc(GPP_SAPA_MAX_AREA_COUNT, sizeof(SAPA_HPAC_HANDLE_AREA));
			if (!sapaHdl->hpacHdl->hpac_area_handle[area]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;

			for (sys = 0; sys < GPP_SAPA_MAX_SYS; sys++)
			{
				sapaHdl->hpacHdl->hpac_area_handle[area]->iono_handle[sys] = (pSAPA_HPAC_HANDLE_IONO*)calloc(GPP_SAPA_MAX_SYS * sizeof(SAPA_HPAC_HANDLE_IONO*));
				if (!sapaHdl->hpacHdl->hpac_area_handle[area]->iono_handle[sys]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;

				for (sat = 0; sat < GPP_SAPA_MAX_SAT; sat++)
				{
					sapaHdl->hpacHdl->hpac_area_handle[area]->iono_handle[sys][sat] = (SAPA_HPAC_HANDLE_IONO*)calloc(GPP_SAPA_MAX_SAT * sizeof(SAPA_HPAC_HANDLE_IONO));
					if (!sapaHdl->hpacHdl->hpac_area_handle[area]->iono_handle[sys][sat]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
				}
			}
		}
	}
	return 0; //ok
}

Mridul Gupta(14.06.2019 17:58) :
	GPPLONG gpp_sapa_handle_malloc_ocbHdl(pSAPA_HANDLE sapaHdl)
{
	if (!sapaHdl) return -1;

	if (!sapaHdl->ocbHdl)
	{
		GPPUINT1 sys, config;
		sapaHdl->ocbHdl = (pSAPA_OCB_HANDLE **)calloc(SAPA_MAX_SYS, sizeof(pSAPA_OCB_HANDLE*));
		if (!sapaHdl->ocbHdl) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;

		for (sys = 0; sys < SAPA_MAX_SYS; sys++)
		{
			sapaHdl->ocbHdl[sys] = (pSAPA_OCB_HANDLE *)calloc(GPP_SAPA_MAX_OCB_CONFIGS, sizeof(pSAPA_OCB_HANDLE));

			if (!(sapaHdl->ocbHdl[sys])) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
			for (config = 0; config < GPP_SAPA_MAX_OCB_CONFIGS; config++)
			{
				sapaHdl->ocbHdl[sys]->ocb_sv_handle[config] = (pSAPA_OCB_HANDLE_SV)calloc(1, sizeof(SAPA_OCB_HANDLE_SV));
				if (!sapaHdl->ocbHdl[sys]->ocb_sv_handle[config]) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;
			}
		}
	}

	return 0; //ok

}

Mridul Gupta(14.06.2019 17:59) :
	GPPLONG gpp_sapa_config_add_ocb_config(SAPA_HANDLE *sapaHdl, GPPUINT1 sys, const SAPA_OCB_HANDLE *pset, FILE *fp)
{
	GPPUINT1 icnfg = 0;

	if (!sapaHdl) return -1;
	if (!pset) return GPP_SAPA_ERR_INVALID_OCB_HANDLE;

	if (sys >= SAPA_MAX_SYS) return GPP_SAPA_ERR_INVALID_SYS;

	if (!sapaHdl->ocbHdl) {
		GPPLONG rc;
		if (rc = gpp_sapa_handle_malloc_ocbHdl(sapaHdl))
			return rc;
	}
	if (sapaHdl->ocb_config_bits[sys] >= (1 << GPP_SAPA_MAX_OCB_CONFIGS))
	{
		fprintf(fp, "SSRM2SAPA ERROR: TOO many OCB configs!\n");
		return GPP_SAPA_ERR_INVALID_OCB_HANDLE;
	}

	for (icnfg = 0; icnfg < GPP_SAPA_MAX_OCB_CONFIGS; icnfg++)
	{
		if (!sapaHdl->ocbHdl[icnfg])
		{
			sapaHdl->ocbHdl[icnfg] = (SAPA_OCB_HANDLE*)calloc(1, sizeof(SAPA_OCB_HANDLE));
			if (!(sapaHdl->ocbHdl[sys][icnfg])) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;

			memcpy(sapaHdl->ocbHdl[icnfg], pset, sizeof(SAPA_OCB_HANDLE));
			sapaHdl->ocb_config_bits[sys] = (1 << icnfg);
			break;
		}
	}

}

Mridul Gupta(14.06.2019 18:00) :
	GPPLONG gpp_sapa_handle_free_hpachdl(SAPA_HANDLE *sapaHdl)
{
	GPPUINT1 sys, area, sat;

	if (!sapaHdl) return -1;

	if (!sapaHdl->hpacHdl) return 0;

	for (area = 0; area < GPP_SAPA_MAX_AREA_COUNT; area++)
	{
		if (!sapaHdl->hpacHdl->hpac_area_handle[area])
			continue;
		for (sys = 0; sys < GPP_SAPA_MAX_SYS; sys++)
		{
			if (!sapaHdl->hpacHdl->hpac_area_handle[area]->iono_handle[sys])
				continue;
			for (sat = 0; sat < GPP_SAPA_MAX_SAT; sat++)
			{
				if (!sapaHdl->hpacHdl->hpac_area_handle[area]->iono_handle[sys][sat])
					continue;
				free(sapaHdl->hpacHdl->hpac_area_handle[area]->iono_handle[sys][sat]);
			}

			free(sapaHdl->hpacHdl->hpac_area_handle[area]->iono_handle[sys]);

		}
		free(sapaHdl->hpacHdl->hpac_area_handle[area]);
	}

	free(sapaHdl->hpacHdl);
	return 0; //ok
}

Mridul Gupta(17.06.2019 10:42) :
	GPPLONG gpp_sapa_handle_free_ocbHdl(SAPA_HANDLE *sapaHdl)
{
	if (!sapaHdl)
		return -1;
	if (sapaHdl->ocbHdl)
		return 0;
	GPPUINT1 sys, config;

	for (sys = 0; sys < SAPA_MAX_SYS; sys++)
	{
		if (!sapaHdl->ocbHdl[sys])
			continue;
		if (!sapaHdl->ocbHdl[sys]->ocb_sv_handle)
			continue;
		for (config = 0; config < GPP_SAPA_MAX_OCB_CONFIGS; config++)
		{
			if (!sapaHdl->ocbHdl[sys]->ocb_sv_handle[config])
				continue;
			free(sapaHdl->ocbHdl[sys]->ocb_sv_handle[config]);
		}
		free(sapaHdl->ocbHdl[sys]->ocb_sv_handle);
		free(sapaHdl->ocbHdl[sys]);
	}
	free(sapaHdl->ocbHdl);
	return 0; //ok
}

Mridul Gupta(17.06.2019 14:43) :
	GPPLONG gpp_sapa_config_add_ocb_config(SAPA_HANDLE *sapaHdl, GPPUINT1 sys, const SAPA_OCB_HANDLE *pset, FILE *fp)
{
	GPPUINT1 icnfg = 0;

	if (!sapaHdl) return -1;
	if (!pset) return GPP_SAPA_ERR_INVALID_OCB_HANDLE;

	if (sys >= SAPA_MAX_SYS) return GPP_SAPA_ERR_INVALID_SYS;

	if (!sapaHdl->ocbHdl) {
		GPPLONG rc;
		if (rc = gpp_sapa_handle_malloc_ocbHdl(sapaHdl))
			return rc;
	}
	if (sapaHdl->ocb_config_bits[sys] >= (1 << GPP_SAPA_MAX_OCB_CONFIGS))
	{
		fprintf(fp, "SSRM2SAPA ERROR: TOO many OCB configs!\n");
		return GPP_SAPA_ERR_INVALID_OCB_HANDLE;
	}

	for (icnfg = 0; icnfg < GPP_SAPA_MAX_OCB_CONFIGS; icnfg++)
	{
		if (!sapaHdl->ocbHdl[sys]->ocb_sv_handle[icnfg])
		{
			sapaHdl->ocbHdl[sys]->ocb_sv_handle[icnfg] = (SAPA_OCB_HANDLE*)calloc(1, sizeof(SAPA_OCB_HANDLE));
			if (!(sapaHdl->ocbHdl[sys]->ocb_sv_handle[icnfg])) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;

			memcpy(sapaHdl->ocbHdl[sys]->ocb_sv_handle[icnfg], pset, sizeof(SAPA_OCB_HANDLE));
			sapaHdl->ocb_config_bits[sys] = (1 << icnfg);
			break;
		}
	}

}

Mridul Gupta(17.06.2019 14:57) :
	GPPLONG gpp_sapa_config_add_hpac_config(SAPA_HANDLE *sapaHdl, GPPUINT1 area, const SAPA_HPAC_HANDLE *pset, FILE *fp)
{
	GPPUINT1 icnfg, sys;

	if (!sapaHdl) return -1;
	if (!pset) return GPP_SAPA_ERR_INVALID_HPAC_HANDLE;

	if (area >= GPP_SAPA_MAX_AREA_COUNT) return GPP_SAPA_ERR_INVALID_AREA;

	if (!sapaHdl->hpacHdl) {
		GPPLONG rc;
		if (rc = gpp_sapa_handle_malloc_hpacHdl(sapaHdl))
			return rc;
	}

	for (sys = 0; sys < SAPA_MAX_SYS; sys++)
	{
		if (sapaHdl->hpacHdl->hpac_area_handle[area]->iono_handle[sys])
			for (icnfg = 0; icnfg < GPP_MAX_HPAC_CONFIGS; icnfg++)
			{
				if (!sapaHdl->hpacHdl->hpac_area_handle[area]->iono_handle[sys][icnfg])
				{
					sapaHdl->hpacHdl->hpac_area_handle[area]->iono_handle[sys][icnfg] = (SAPA_HPAC_HANDLE_IONO*)calloc(1, sizeof(SAPA_HPAC_HANDLE_IONO));
					if (!(sapaHdl->hpacHdl->hpac_area_handle[area]->iono_handle[sys][icnfg])) return GPP_SAPA_ERR_NOT_ENOUGH_MEMORY;

					memcpy(sapaHdl->hpacHdl->hpac_area_handle[area]->iono_handle[sys][icnfg], pset, sizeof(SAPA_HPAC_HANDLE));
					break;
				}
			}
	}
	return 0; //ok;
}

GPPLONG gpp_sapa_handle_free_gadHdl(SAPA_HANDLE *sapaHdl)
{
	if (!sapaHdl) return -1;

	if (!sapaHdl->gadHdl) return 0;

	free(sapaHdl->gadHdl);

	return 0;  //ok

}



GPPLONG gpp_sapa_handle_free_hpacHdl(SAPA_HANDLE *sapaHdl)
{
	GPPUINT1 sys, area, sat;

	if (sapaHdl!) return -1;

	if (!sapaHdl->hpacHdl) return 0;

	for (sys = 0; sys < SAPA_MAX_SYS; sys++)
	{
		if (!sapaHdl->hpacHdl[sys]) continue;

		for (area = 0; area < SAPA_MAX_AREA; area++)
		{

			for (sat = 0; sat < SAPA_MAX_SAT; sat++)
			{
				SAPA_HPAC_HANDLE* hpacHdl = NULL;
				if (!(hpacHdl = sapaHdl->hpacHdl[sys][area][sat]))
					continue;

				memset(ocbHdl, 0, sizeof(SAPA_HPAC_HANDLE));
				free(sapaHdl->hpacHdl[sys][area][sat]);
			}

			if (!(hpacHdl = sapaHdl->hpacHdl[sys][area]))
				continue;
			memset(hpacHdl, 0, sizeof(SAPA_HPAC_HANDLE));
			free(sapaHdl->hpacHdl[sys][area]);

		}

	}

	return 0;	//ok
}
