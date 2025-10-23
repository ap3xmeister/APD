//==============================================================================
//
// Title:		ProcessData.c
// Purpose:		A short description of the implementation.
//
// Created on:	28.10.2013 at 18:53:14 by Terran.
// Copyright:	UTI. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include <userint.h>
#include <ansi_c.h>
#include <utility.h>
#include "ProcessData.h"
#include "SerialECG.h"

//==============================================================================
// Constants
#define PACK_BEGING		'<'
#define PACK_END		'>'

#define AUTOMAT_PACK_START	1
#define AUTOMAT_PACK_DATA	2

//==============================================================================
// Types

//==============================================================================
// Static global variables
static char pack[ 128 ] = { 0 };
static unsigned char packIndex = 0;
static automateState = AUTOMAT_PACK_START;

//==============================================================================
// Static functions

//==============================================================================
// Global variables

//==============================================================================
// Global functions
// 
//	formatul pachetului este >123 123 123<
//
int ProcessComInBuffer( char *comBuffer, int comBufferLenght )
{
	int err = 0;
	int i = 0;
	static int iCh0 = 0, iCh1 = 0, iCh2 = 0;
	
	for( i = 0; i < comBufferLenght; i++ )
	{
		switch( automateState )
		{
			case AUTOMAT_PACK_START:
				
				if (comBuffer[i] == PACK_BEGING)
                {
                    packIndex = 0;
                    memset(pack, 0, sizeof(pack));
                    automateState = AUTOMAT_PACK_DATA;
                }
                break;
				
				break;
			case AUTOMAT_PACK_DATA:
				
				if (comBuffer[i] == PACK_END)
                {
                    // finalizez pachetul curent
                    pack[packIndex] = '\0';

                    // parsez valorile din pachetul "<val1 val2 val3>"
                    sscanf(pack, "%d %d %d", &iCh0, &iCh1, &iCh2);

                    // plotez valorile în cele trei StripChart-uri
                    PlotStripChartPoint(mainPanel, MAIN_PANEL_IDC_DISP_ECG1, iCh0);
                    PlotStripChartPoint(mainPanel, MAIN_PANEL_IDC_DISP_ECG2, iCh1);
                    PlotStripChartPoint(mainPanel, MAIN_PANEL_IDC_DISP_ECG3, iCh2);

                    // revin la starea initiala
                    automateState = AUTOMAT_PACK_START;
                }
                else
                {
                    // adaug caracterul în bufferul de pachet
                    if (packIndex < sizeof(pack) - 1)
                        pack[packIndex++] = comBuffer[i];
                    else
                    {
                        // daca e prea mare, resetez automatul
                        automateState = AUTOMAT_PACK_START;
                        packIndex = 0;
                    }
                }
                break;

				break;
		}
	}
	
	return err;
}

