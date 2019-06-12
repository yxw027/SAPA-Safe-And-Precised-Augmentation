
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
