#include <cvirte.h>		
#include <userint.h>
#include "FirstApp.h"
static int val;

static int mainPanel;

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((mainPanel = LoadPanel (0, "FirstApp.uir", MAIN_PANEL)) < 0)
		return -1;
	DisplayPanel (mainPanel);
	RunUserInterface ();
	DiscardPanel (mainPanel);
	return 0;
}

int CVICALLBACK OnMainPanel (int panel, int event, void *callbackData,
							 int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			if(ConfirmPopup ("Quit", "Do you Really want to quit ?"))
			{
			QuitUserInterface (0);
			}
			
			break;
	}
	return 0;
}

int CVICALLBACK OnExit (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(ConfirmPopup ("Quit", "Do you Really awant to quit ?"))
			{
			QuitUserInterface (0);
			}
			break;
	}
	return 0;
}

int CVICALLBACK OnPowerSwitch (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (mainPanel, MAIN_PANEL_POWER_SWITCH, &val);
			SetCtrlVal (mainPanel, MAIN_PANEL_POWER_LED, val);
			break;
	}
	return 0;
}
