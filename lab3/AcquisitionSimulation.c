//==============================================================================
//
// Title:		AcquisitionSimulation
// Purpose:		A short description of the application.
//
// Created on:	20.10.2013 at 17:54:18 by Terran.
// Copyright:	UTI. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "AcquisitionSimulation.h"
#include "toolbox.h"
#include "Signals.h"



//==============================================================================
// Constants

#define USER_EVENT         1000
#define MYEVENT_CLOSE       (USER_EVENT+1)
//#define MYEVENT_CLOSE1      (USER_EVENT+2)

//==============================================================================
// Types

//==============================================================================
// Static global variables
static int mainPanel = 0;
static int abtPanel = 0;
	//numarul de controale ce trebuiesc validate/invalidate
static const int nControls = 9;
	//controalele ce sunt validate/invalidate sunt puse intr-un vector
static const int controls[] = { MAIN_PANEL_IDC_GRAPH_DISPLAY, 
							    MAIN_PANEL_IDC_SW_ACQMODE,
							    MAIN_PANEL_IDC_BTT_MANUALDISPLAY,
							    MAIN_PANEL_IDC_BTT_FILELOAD, 
							    MAIN_PANEL_IDC_BTT_FILESAVE, 
							    MAIN_PANEL_IDC_BTT_MANUAL_ACQ, 
							    MAIN_PANEL_IDC_NUM_SAMPLE_INDEX, 
							    MAIN_PANEL_IDC_COLOR_TRACE, 
							    MAIN_PANEL_IDC_COLOR_CURSOR };

	///numarul de menuItems ce trebuiesc validate/invalidate
static const int nMenuItems = 4;
	//meniurile ce vor fi validate/invalidate sunt puse intr-un vector
static const int menuItems[] = { MENUBAR_FILE_NEW,
								 MENUBAR_FILE_LOAD, 
								 MENUBAR_FILE_SAVE,
								 MENUBAR_SIGNAL };

//==============================================================================
// Static functions
static int CheckMenuItem(int menuBar, int menuItem );

//==============================================================================
// Global variables

//==============================================================================
// Global functions

/*******************************************************************************
	functia main
*******************************************************************************/
/// HIFN The main entry-point function.
int main (int argc, char *argv[])
{
	int error = 0;
	int event = 0; //evenimentul prins de functia GetUserEvent. Poate fi un eveniment postat de 
	               //programator sau EVENT_COMMIT
	int val1 = 0; //prima valoare postata odata cu evenimentul (QueueUserEvent). In cazul unui
	              //eveniment EVENT_COMMIT val1 va contine handle-ul la panel
	int val2 = 0; //a doua valoare valoare postata odata cu evenimentul (QueueUserEvent). In cazul 
	              //unui eveniment EVENT_COMMIT val2 va contine id-ul controlului

	BOOL quitFlag = FALSE; //flag pentru iesirea din bucla de tratare a evenimentelor
	
	/* initialize and load resources */
	nullChk (InitCVIRTE (0, argv, 0));
	errChk (mainPanel = LoadPanel (0, "AcquisitionSimulation.uir", MAIN_PANEL));
	SetAxisScalingMode( mainPanel, MAIN_PANEL_IDC_GRAPH_DISPLAY, VAL_BOTTOM_XAXIS, VAL_MANUAL, 0.0, GRAPH_NPOINTS );
	//
	errChk (abtPanel = LoadPanel (0, "AcquisitionSimulation.uir", ABOUTPANEL));
	//*********
	
	/* display the panel and run the user interface */
	errChk (DisplayPanel (mainPanel));
	
	//To do: 01
	//*********
	while(!quitFlag)
	{
		event = GetUserEvent(1, &val1, &val2);
		switch(event)
		{
			case MYEVENT_CLOSE:
				//event
				quitFlag = TRUE;
			break;
		
		}
	}
			
	//errChk (RunUserInterface ());
	
Error:
	/* clean up */
	if (mainPanel > 0)
		DiscardPanel (mainPanel);
	return 0;
}

//==============================================================================
// UI callback function prototypes

/*******************************************************************************
	functia de callback a MAIN_PANEL
*******************************************************************************/
/// HIFN Exit when the user dismisses the panel.
int CVICALLBACK MainPanelCB (int panel, int event, void *callbackData, int eventData1, int eventData2)
{
	switch(event)
	{
		case EVENT_CLOSE:
			//To do: 01
			//*********
			
			QueueUserEvent(MYEVENT_CLOSE, panel, MAIN_PANEL);
			
			//QuitUserInterface(0);
			break;
	}
	return 0;
}

/*******************************************************************************
	functia de callback a barei de menu a MAIN_PANEL
*******************************************************************************/
void CVICALLBACK OnMenuBar (int menuBar, int menuItem, void *callbackData, int panel)
{
	switch( menuItem )
	{
		case MENUBAR_FILE_NEW:
			SetCtrlVal( panel, MAIN_PANEL_IDC_SW_POWER, 0 );
			PowerSwitchCB (panel, MAIN_PANEL_IDC_SW_POWER, EVENT_COMMIT, 0, 0, 0 );
			break;
		
		case MENUBAR_FILE_LOAD:
			FileIoCB ( panel, MAIN_PANEL_IDC_BTT_FILELOAD, EVENT_COMMIT, 0, 0, 0 );
			break;
		
		case MENUBAR_FILE_SAVE:
			if( saveFlag )
			{
				SetCtrlVal( panel, MAIN_PANEL_IDC_BTT_FILESAVE, 0 ); 
			}
			else
			{
				SetCtrlVal( panel, MAIN_PANEL_IDC_BTT_FILESAVE, 1 ); 	
			}
			FileIoCB ( panel, MAIN_PANEL_IDC_BTT_FILESAVE, EVENT_COMMIT, 0, 0, 0 );
			SetMenuBarAttribute( menuBar, menuItem, ATTR_CHECKED, saveFlag); 
			break;
		
		case MENUBAR_FILE_EXIT:
			//To do: 01
			//*********
			QueueUserEvent(MYEVENT_CLOSE, panel, MAIN_PANEL);
			//QuitUserInterface(0);
			break;
		
		case MENUBAR_SIGNAL_SINE:
			CheckMenuItem( menuBar, menuItem);
			
			signalType = SIGNALTYPE_SINEWAVE;

			//To do: 02
			//*********

			break;
			
		case MENUBAR_SIGNAL_TRIANGLE:
			CheckMenuItem( menuBar, menuItem);

			//To do: 02
			//*********
			signalType = SIGNALTYPE_TRIANGLEWAVE;

			break;
			
		case MENUBAR_SIGNAL_SQUARE:
			CheckMenuItem( menuBar, menuItem);

			//To do: 02
			//*********
			signalType = SIGNALTYPE_SQUAREWAVE;

			break;
			
		case MENUBAR_SIGNAL_NOISE:
			CheckMenuItem( menuBar, menuItem);

			//To do: 02
			//*********
			signalType = SIGNALTYPE_NOISE;
			break;
			
		case MENUBAR_ABOUT_ABOUT:
			//To do: 10
			InstallPopup(abtPanel);
			//*********

			break;
	}
}

/*******************************************************************************
	functia de callback a switch-ului retea
*******************************************************************************/
int CVICALLBACK PowerSwitchCB (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int val = 0;
	int i = 0;
	int menuHandle = 0;
	
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal( panel, control, &val );
			SetCtrlVal( panel, MAIN_PANEL_IDC_POWER_LED, val );
			SetCtrlVal( panel, MAIN_PANEL_IDC_SW_ACQMODE, 0 );
			SetCtrlVal( panel, MAIN_PANEL_IDC_BTT_FILESAVE, 0 );
			SetCtrlVal( panel, MAIN_PANEL_IDC_BTT_FILELOAD, 0 );

			for( i = 0; i < nControls; i++ )
			{
				SetCtrlAttribute( panel, controls[i], ATTR_DIMMED, !val );	
			}
			SetCtrlAttribute( panel, MAIN_PANEL_IDC_SL_ACQ_PERIOD, ATTR_DIMMED, 1 );	
			
			menuHandle = GetPanelMenuBar(panel);
			for( i = 0; i < nMenuItems; i++ )
			{
				SetMenuBarAttribute( menuHandle, menuItems[i], ATTR_DIMMED, !val);
			}
			
			if( !val )
			{
				SetCtrlAttribute( panel, MAIN_PANEL_SIMULATION_TIMER, ATTR_ENABLED, 0 );
				DeleteGraphPlot( panel, MAIN_PANEL_IDC_GRAPH_DISPLAY, -1, VAL_IMMEDIATE_DRAW );	
				plotHandle = NO_PLOT;
				SetCtrlVal( panel, MAIN_PANEL_IDC_NUM_MIN, 0.0 );
				SetCtrlVal( panel, MAIN_PANEL_IDC_NUM_MAX, 0.0 );
				SetCtrlVal( panel, MAIN_PANEL_IDC_NUM_MEAN, 0.0 );
				SetCtrlVal( panel, MAIN_PANEL_IDC_NUM_SAMPLE_INDEX, 0.0 );
				SetCtrlVal( panel, MAIN_PANEL_IDC_NUM_SAMPLE_VALUE, 0.0 );
			}
			saveFlag = FALSE;
			
			break;
	}
	return 0;
}

/*******************************************************************************
	functia de callback a switch-ului mod de achizitie
*******************************************************************************/
int CVICALLBACK AcquisitionModeCB (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int val = 0 ;
	
	switch (event)
	{
		case EVENT_COMMIT:
			
			GetCtrlVal( panel, control, &val );
			SetCtrlAttribute( panel, MAIN_PANEL_IDC_BTT_MANUAL_ACQ, ATTR_DIMMED, val );
			SetCtrlAttribute( panel, MAIN_PANEL_IDC_BTT_MANUALDISPLAY, ATTR_DIMMED, val );
			SetCtrlAttribute( panel, MAIN_PANEL_IDC_SL_ACQ_PERIOD, ATTR_DIMMED, !val );
			SetCtrlAttribute( panel, MAIN_PANEL_IDC_BTT_FILELOAD, ATTR_DIMMED, val ); 
			//To do: 04
			if(val == 1)
			{
				SetCtrlAttribute(panel, MAIN_PANEL_SIMULATION_TIMER, ATTR_ENABLED, val);
			}
			else if(val == 0)
			{
				SetCtrlAttribute(panel, MAIN_PANEL_SIMULATION_TIMER, ATTR_ENABLED, val);
			}
			//*********
			
			break;
	}
	return 0;
}

/*******************************************************************************
	functia de callback a panelului about
*******************************************************************************/
//To do: 10
int CVICALLBACK OnAboutPanelCB (int panel, int event, void *callbackData,
							  int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			RemovePopup(0);

			break;
	}
	return 0;
}
//*********

/*******************************************************************************
	functia de check si uncheck pentru meniu signal
*******************************************************************************/
static int CheckMenuItem(int menuBar, int menuItem )
{
	int err = 0;

	if( menuItem == MENUBAR_SIGNAL_SINE )
	{
		SetMenuBarAttribute( menuBar, menuItem, ATTR_CHECKED, 1);
	}
	else
	{
		SetMenuBarAttribute( menuBar, MENUBAR_SIGNAL_SINE, ATTR_CHECKED, 0);
	}

	if( menuItem == MENUBAR_SIGNAL_TRIANGLE )
	{
		SetMenuBarAttribute( menuBar, menuItem, ATTR_CHECKED, 1);
	}
	else
	{
		SetMenuBarAttribute( menuBar, MENUBAR_SIGNAL_TRIANGLE, ATTR_CHECKED, 0);
	}

	if( menuItem == MENUBAR_SIGNAL_SQUARE )
	{
		SetMenuBarAttribute( menuBar, menuItem, ATTR_CHECKED, 1);
	}
	else
	{
		SetMenuBarAttribute( menuBar, MENUBAR_SIGNAL_SQUARE, ATTR_CHECKED, 0);
	}

	if( menuItem == MENUBAR_SIGNAL_NOISE )
	{
		SetMenuBarAttribute( menuBar, menuItem, ATTR_CHECKED, 1);
	}
	else
	{
		SetMenuBarAttribute( menuBar, MENUBAR_SIGNAL_NOISE, ATTR_CHECKED, 0);
	}

	return err;
}





