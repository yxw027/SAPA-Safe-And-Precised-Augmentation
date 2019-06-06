GPPLONG gpp_sapa_hpac_free_hpac(pGPP_SAPA_HPAC hpac)
{

	if (hpac) {
		if (hpac->header_block)
		{
			//memset(hpac->header_block, 0, sizeof(GPP_SAPA_HPAC_HEADER));
			free(hpac->header_block);
			hpac->header_block = NULL;
		}
		if (hpac->atmo)
		{
			GPPUINT1 area;
			for (area = 0; area < GPP_SAPA_MAX_AREA_COUNT; area++)
			{
				if (hpac->atmo[area])
				{
					if (hpac->atmo[area]->area_def)
					{
						//memset(hpac->atmo[area]->area_def, 0, sizeof(GPP_SAPA_HPAC_AREA));
						free(hpac->atmo[area]->area_def);
					}
					if (hpac->atmo[area]->tropo)
					{
						if (hpac->atmo[area]->tropo->tropo_poly_coeff_block)
						{
							//memset(hpac->atmo[area]->tropo->tropo_poly_coeff_block, 0, sizeof(GPP_SAPA_HPAC_TROPO_POLY_COEFFICIENT_BLOCK));
							free(hpac->atmo[area]->tropo->tropo_poly_coeff_block);
						}
						if (hpac->atmo[area]->tropo->tropo_grid)
						{
							//memset(hpac->atmo[area]->tropo->tropo_grid, 0, sizeof(GPP_SAPA_HPAC_TROPO_GRID_BLOCK));
							free(hpac->atmo[area]->tropo->tropo_grid);
						}
						//memset(hpac->atmo[area]->tropo, 0, sizeof(GPP_SAPA_HPAC_TROPO));
						free(hpac->atmo[area]->tropo);
					}
					if (hpac->atmo[area]->iono->iono_sat_block)
					{
						GPPUINT1 sys;
						for (sys = 0; sys < GPP_SAPA_MAX_SYS; sys++)
						{
							if (hpac->atmo[area]->iono->iono_sat_block[sys]) {
								GPPUINT1 sat;
								for (sat = 0; sat < GPP_SAPA_MAX_SAT; sat++)
								{
									if (hpac->atmo[area]->iono->iono_sat_block[sys][sat]) {
										if (hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_sat_poly)
										{
											//memset(hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_sat_poly, 0, sizeof(GPP_SAPA_HPAC_IONO_SAT_POLY));
											free(hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_sat_poly);
										}
										if (hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_sat_coeff)
										{
											//memset(hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_sat_coeff, 0, sizeof(GPP_SAPA_HPAC_IONO_SAT_COEFFICIENT));
											free(hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_sat_coeff);
										}
										if (hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_grid)
										{
											//memset(hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_grid, 0, sizeof(GPP_SAPA_HPAC_IONO_GRID_BLOCK));
											free(hpac->atmo[area]->iono->iono_sat_block[sys][sat]->iono_grid);
										}
										//memset(hpac->atmo[area]->iono->iono_sat_block[sys][sat], 0, sizeof(GPP_SAPA_HPAC_IONO_SAT_BLOCK));
										free(hpac->atmo[area]->iono->iono_sat_block[sys][sat]);
									}
								}
								//memset(hpac->atmo[area]->iono->iono_sat_block[sys], 0, sizeof(GPP_SAPA_HPAC_IONO_SAT_BLOCK));
								free(hpac->atmo[area]->iono->iono_sat_block[sys]);
							}
						}
						//memset(hpac->atmo[area]->iono->iono_sat_block, 0, sizeof(GPP_SAPA_HPAC_IONO_SAT_BLOCK));
						free(hpac->atmo[area]->iono->iono_sat_block);
					}
					//memset(hpac->atmo[area], 0, sizeof(GPP_SAPA_HPAC_AREA));
					free(hpac->atmo[area]);
				}

			}
			//memset(hpac->atmo, 0, sizeof(GPP_SAPA_HPAC_ATMO_BLOCK));
			free(hpac->atmo);
			hpac->atmo = NULL;
		}

	}


}