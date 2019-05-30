
//free hpac memory
GGPLONG gpp_sapa_hpac_free_hpac(pGGPP_SAPA_HPAC hpac)
{
	GPPUINT sys, sat, area;
	if (!hpac) return 0;
	if (hpac->atmo) return 0;

	for (area = 0; area < GPP_SAPA_MAX_AREA_COUNT; area++) {
		for (sys = 0; sys < GPP_SAPA_MAX_CONS; sys++) {
			for (sat = 0; sat < GPP_SAPA_MAX_SAT; sat++)
				if (hpac->atmo[area][sys][sat])
				{
					free(hpac->atmo[area][sys][sat]);
					hpac->atmo[area][sys][sat] = NULL;
				}

			free(hpac->atmo[area][sys]);
			hpac->atmo[area][sys] = NULL;
		}

		free(hpac->atmo[area]);
		hpac->atmo[area] = NULL;
	}

	free(hpac->atmo);
	hpac->atmo = NULL;

	return 0;
}

