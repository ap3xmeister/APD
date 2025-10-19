#include <cvirte.h>		
#include <userint.h>
#include "labb2.h"

static int val;
static int mainPanel;

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((mainPanel = LoadPanel (0, "labb2.uir", MAIN_PANEL)) < 0)
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

int CVICALLBACK OnReteaSwitch (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(mainPanel, MAIN_PANEL_BINARYSWITCH, &val);
			SetCtrlVal(mainPanel, MAIN_PANEL_POWER_LED, val);
			
			if(val == 1)
			{
				SetCtrlAttribute(mainPanel, MAIN_PANEL_BINARYSWITCH_2, ATTR_DIMMED, 0);
				SetCtrlAttribute(mainPanel, MAIN_PANEL_ACHIZITIE_BUTTON, ATTR_DIMMED, 0);
				SetCtrlAttribute(mainPanel, MAIN_PANEL_AFISEAZA_BUTTON, ATTR_DIMMED, 0);
				SetCtrlAttribute(mainPanel, MAIN_PANEL_NUMERIC_ESANTION, ATTR_DIMMED, 0);
				SetCtrlAttribute(mainPanel, MAIN_PANEL_STRING_VALOARE, ATTR_DIMMED, 0);
				SetCtrlAttribute(mainPanel, MAIN_PANEL_STRING_MIN, ATTR_DIMMED, 0);
				SetCtrlAttribute(mainPanel, MAIN_PANEL_STRING_AVG, ATTR_DIMMED, 0);
				SetCtrlAttribute(mainPanel, MAIN_PANEL_STRING_MAX, ATTR_DIMMED, 0);
				SetCtrlAttribute(mainPanel, MAIN_PANEL_COLORNUM, ATTR_DIMMED, 0);
				SetCtrlAttribute(mainPanel, MAIN_PANEL_COLORNUM_2, ATTR_DIMMED, 0);
				SetCtrlAttribute(mainPanel, MAIN_PANEL_TOGGLEBUTTON, ATTR_DIMMED, 0);
				SetCtrlAttribute(mainPanel, MAIN_PANEL_TOGGLEBUTTON_2, ATTR_DIMMED, 0);
			}
			else if(val == 0)
			{
				SetCtrlAttribute(mainPanel, MAIN_PANEL_BINARYSWITCH_2, ATTR_DIMMED, 1);
				SetCtrlAttribute(mainPanel, MAIN_PANEL_ACHIZITIE_BUTTON, ATTR_DIMMED, 1);
				SetCtrlAttribute(mainPanel, MAIN_PANEL_AFISEAZA_BUTTON, ATTR_DIMMED, 1);
				SetCtrlAttribute(mainPanel, MAIN_PANEL_NUMERIC_ESANTION, ATTR_DIMMED, 1);
				SetCtrlAttribute(mainPanel, MAIN_PANEL_STRING_VALOARE, ATTR_DIMMED, 1);
				SetCtrlAttribute(mainPanel, MAIN_PANEL_STRING_MIN, ATTR_DIMMED, 1);
				SetCtrlAttribute(mainPanel, MAIN_PANEL_STRING_AVG, ATTR_DIMMED, 1);
				SetCtrlAttribute(mainPanel, MAIN_PANEL_STRING_MAX, ATTR_DIMMED, 1);
				SetCtrlAttribute(mainPanel, MAIN_PANEL_COLORNUM, ATTR_DIMMED, 1);
				SetCtrlAttribute(mainPanel, MAIN_PANEL_COLORNUM_2, ATTR_DIMMED, 1);
				SetCtrlAttribute(mainPanel, MAIN_PANEL_TOGGLEBUTTON, ATTR_DIMMED, 1);
				SetCtrlAttribute(mainPanel, MAIN_PANEL_TOGGLEBUTTON_2, ATTR_DIMMED, 1);
				
				SetCtrlVal(mainPanel, MAIN_PANEL_BINARYSWITCH_2, 0);
				SetCtrlAttribute(mainPanel, MAIN_PANEL_NUMERICSLIDE, ATTR_DIMMED, 1);
			}
			
			
			

			break;
	}
	return 0;
}

void CVICALLBACK OnFileNew (int menuBar, int menuItem, void *callbackData,
							int panel)
{
	SetCtrlVal(mainPanel, MAIN_PANEL_BINARYSWITCH, 0);
	SetCtrlVal(mainPanel, MAIN_PANEL_POWER_LED, 0);
	
	SetCtrlAttribute(mainPanel, MAIN_PANEL_BINARYSWITCH_2, ATTR_DIMMED, 1);
	SetCtrlAttribute(mainPanel, MAIN_PANEL_ACHIZITIE_BUTTON, ATTR_DIMMED, 1);
	SetCtrlAttribute(mainPanel, MAIN_PANEL_AFISEAZA_BUTTON, ATTR_DIMMED, 1);
	SetCtrlAttribute(mainPanel, MAIN_PANEL_NUMERIC_ESANTION, ATTR_DIMMED, 1);
	SetCtrlAttribute(mainPanel, MAIN_PANEL_STRING_VALOARE, ATTR_DIMMED, 1);
	SetCtrlAttribute(mainPanel, MAIN_PANEL_STRING_MIN, ATTR_DIMMED, 1);
	SetCtrlAttribute(mainPanel, MAIN_PANEL_STRING_AVG, ATTR_DIMMED, 1);
	SetCtrlAttribute(mainPanel, MAIN_PANEL_STRING_MAX, ATTR_DIMMED, 1);
	SetCtrlAttribute(mainPanel, MAIN_PANEL_COLORNUM, ATTR_DIMMED, 1);
	SetCtrlAttribute(mainPanel, MAIN_PANEL_COLORNUM_2, ATTR_DIMMED, 1);
	SetCtrlAttribute(mainPanel, MAIN_PANEL_TOGGLEBUTTON, ATTR_DIMMED, 1);
	SetCtrlAttribute(mainPanel, MAIN_PANEL_TOGGLEBUTTON_2, ATTR_DIMMED, 1);
	
	SetCtrlVal(panel, MAIN_PANEL_BINARYSWITCH_2, 0);
	SetCtrlAttribute(panel, MAIN_PANEL_NUMERICSLIDE, ATTR_DIMMED, 1);
}

void CVICALLBACK OnFileSave (int menuBar, int menuItem, void *callbackData,
							 int panel)
{
}

void CVICALLBACK OnFileLoad (int menuBar, int menuItem, void *callbackData,
							 int panel)
{
}

void CVICALLBACK OnFileAbout (int menuBar, int menuItem, void *callbackData,
							  int panel)
{
}

void CVICALLBACK OnExit (int menuBar, int menuItem, void *callbackData,
						 int panel)
{
	if(ConfirmPopup ("Exit", "Do you Really want to exit ?"))
	{
		QuitUserInterface (0);
	}
}

int CVICALLBACK OnAchizitieSwitch (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(mainPanel, MAIN_PANEL_BINARYSWITCH_2, &val);
			if(val == 1)
			{
				SetCtrlAttribute(mainPanel, MAIN_PANEL_NUMERICSLIDE, ATTR_DIMMED, 0);
				
				SetCtrlAttribute(panel, MAIN_PANEL_ACHIZITIE_BUTTON, ATTR_DIMMED, 1);
				SetCtrlAttribute(panel, MAIN_PANEL_AFISEAZA_BUTTON, ATTR_DIMMED, 1);
			}
			else if(val == 0)
			{
				SetCtrlAttribute(mainPanel, MAIN_PANEL_NUMERICSLIDE, ATTR_DIMMED, 1);
				
				SetCtrlAttribute(panel, MAIN_PANEL_ACHIZITIE_BUTTON, ATTR_DIMMED, 0);
				SetCtrlAttribute(panel, MAIN_PANEL_AFISEAZA_BUTTON, ATTR_DIMMED, 0);
			}
			
			break;
	}
	return 0;
}
