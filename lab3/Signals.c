//==============================================================================
//
// Title:		Signals.c
// Purpose:		A short description of the implementation.
//
// Created on:	21.10.2013 at 12:19:18 by Terran.
// Copyright:	UTI. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include "toolbox.h"
#include <ansi_c.h>
#include <formatio.h>
#include <utility.h>
#include <analysis.h>
#include <userint.h>
#include "Signals.h"
#include "AcquisitionSimulation.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables
static double rowSignal[ GRAPH_NPOINTS ];
static char fileName[MAX_PATHNAME_LEN]={0};
static int traceColor = VAL_RED;

//==============================================================================
// Static functions

//==============================================================================
// Global variables
int signalType = SIGNALTYPE_SINEWAVE; //tipul semnalului selectat in meniu
int plotHandle = NO_PLOT;  //variabila ce contine handle-ul plotului de pe graph
double amplitude = 5.0;	   //amplitudinea semnalului generat
double frequency = 1.0/113.0; //frecventa de achizitie a semnalului generat
double dutyCycle = 50.0; //factorul de umplere al semnalului dreptunghiular
BOOL saveFlag = FALSE; //flag ce indica daca butonul de salvare a fost apasat

//==============================================================================
// Global functions

/*******************************************************************************
	functia de callback a butonului de achizite
*******************************************************************************/
int CVICALLBACK ManualAcquisitionCB (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	static double phase = 0.0;
	
	switch (event)
	{
		case EVENT_COMMIT:
			//todo2
			
			switch(signalType)
			{
				case SIGNALTYPE_SINEWAVE:
					SineWave(GRAPH_NPOINTS, amplitude, frequency, &phase, rowSignal);
					break;
				case SIGNALTYPE_TRIANGLEWAVE:
					TriangleWave(GRAPH_NPOINTS, amplitude, frequency, &phase, rowSignal);
					break;
				case SIGNALTYPE_SQUAREWAVE:
					SquareWave(GRAPH_NPOINTS, amplitude, frequency, &phase, dutyCycle, rowSignal);
					break;
				case SIGNALTYPE_NOISE:
					WhiteNoise(GRAPH_NPOINTS, amplitude,0 , rowSignal);
					break;
			}
			
			break;
	}
	return 0;
}

/*******************************************************************************
	functia de callback a butonului de afisare
*******************************************************************************/
int CVICALLBACK ManualDisplayCB (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	double maxVal = 0.0;
	double minVal = 0.0;
	int maxIndex = 0;
	int minIndex = 0;
	double mean = 0.0;
	static int count = 0;
	char string[ MAX_PATHNAME_LEN ] = { 0 };
	
	switch (event)
	{
		case EVENT_COMMIT:
			//To do: 03
			//*********
			if (plotHandle != NO_PLOT)
				DeleteGraphPlot(panel, MAIN_PANEL_IDC_GRAPH_DISPLAY, plotHandle, VAL_IMMEDIATE_DRAW);
			
			plotHandle = PlotY(panel, MAIN_PANEL_IDC_GRAPH_DISPLAY, rowSignal, GRAPH_NPOINTS,
				VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, traceColor);
			
			MaxMin1D(rowSignal, GRAPH_NPOINTS, &maxVal, &maxIndex, &minVal, &minIndex);
			Mean(rowSignal, GRAPH_NPOINTS, &mean);
			
			SetCtrlVal(panel, MAIN_PANEL_IDC_NUM_MAX, maxVal);
			SetCtrlVal(panel, MAIN_PANEL_IDC_NUM_MIN, minVal);
			SetCtrlVal(panel, MAIN_PANEL_IDC_NUM_MEAN, mean);
			//To do: 08
			//*********
			
			//To do: 06
			GraphDisplayCB(panel, MAIN_PANEL_IDC_GRAPH_DISPLAY, EVENT_COMMIT, NULL, 0,0);
			
			//*********
			
			break;
	}
	return 0;
}

/*******************************************************************************
	functia de callback a controlului esantion
*******************************************************************************/
int CVICALLBACK SampleCB (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	double val = 0;
	double val2 = 0;
	
	switch (event)
	{
		case EVENT_COMMIT:
			//To do: 07
			GetCtrlVal(panel, MAIN_PANEL_IDC_NUM_SAMPLE_INDEX, &val);
			GetCtrlVal(panel, MAIN_PANEL_IDC_NUM_SAMPLE_VALUE, &val2);
			
			SetGraphCursor(panel, MAIN_PANEL_IDC_GRAPH_DISPLAY, 1, val, val2);
			
			//*********

			break;
	}
	return 0;
}

/*******************************************************************************
	functia de callback a controalelor color numeric (cursor si trasare)
*******************************************************************************/
int CVICALLBACK OnChooseColorCB (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int val = 0;
	
	switch (event)
	{
		case EVENT_COMMIT:
			//To do: 05
			GetCtrlVal(panel, MAIN_PANEL_IDC_COLOR_CURSOR, &val);
			SetCursorAttribute(panel, MAIN_PANEL_IDC_GRAPH_DISPLAY, 1, ATTR_CURSOR_COLOR, val);
			
			GetCtrlVal(panel, MAIN_PANEL_IDC_COLOR_TRACE, &val);
			SetPlotAttribute(panel, MAIN_PANEL_IDC_GRAPH_DISPLAY, plotHandle, ATTR_TRACE_COLOR, val);
			traceColor = val;
			
			//*********

			break;
	}
	return 0;
}

/*******************************************************************************
	functia de callback a butoanelor salvare si incarcare
*******************************************************************************/
int CVICALLBACK FileIoCB (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int val = 0;
	int year = 0;
	int month = 0;
	int day = 0;
	int hour = 0;
	int minute = 0;
	int second = 0;
	char path[MAX_PATHNAME_LEN] = { 0 };
	
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal( panel, control, &val );
			switch( control )
			{
				case MAIN_PANEL_IDC_BTT_FILESAVE:
					//To do: 08
					if(saveFlag == 0)
					{
						GetSystemDate(&month, &day, &year);
						GetSystemTime(&hour, &minute, &second);
						sprintf(path, "RowSignal_%04d.%02d.%02d_%02d-%02d-%02d.dat", year, month, day, hour, minute, second);
						saveFlag = 1;
						SetCtrlAttribute(panel, MAIN_PANEL_IDC_BTT_FILELOAD, ATTR_DIMMED, 1);
						ArrayToFile(path, rowSignal, VAL_DOUBLE, GRAPH_NPOINTS, 1, VAL_GROUPS_TOGETHER, VAL_GROUPS_AS_COLUMNS, VAL_SEP_BY_TAB, VAL_CONST_WIDTH, VAL_ASCII, VAL_TRUNCATE);
					}
					else if(saveFlag == 1)
					{
						saveFlag = 0;
						SetCtrlAttribute(panel, MAIN_PANEL_IDC_BTT_FILELOAD, ATTR_DIMMED, 0);
					}
						
						
					//*********

					break;
				
				case MAIN_PANEL_IDC_BTT_FILELOAD:
					//To do: 09
					int fileSelected = FileSelectPopup(" ", " ", "*.dat", "Selecteaza fisierul!", VAL_LOAD_BUTTON, 0, 0, 0, 0, fileName);
					if(fileSelected)
					{
						FileToArray(fileName, rowSignal, VAL_DOUBLE, GRAPH_NPOINTS, 1, VAL_GROUPS_TOGETHER, VAL_GROUPS_AS_COLUMNS, VAL_ASCII);
						ManualDisplayCB(panel, MAIN_PANEL_IDC_GRAPH_DISPLAY, EVENT_COMMIT, NULL, 0, 0);
					}
					//*********

					break;
			}
			break;
	}
	return 0;
}

/*******************************************************************************
	functia de callback a grafului (atunci cand exista un cursor definit)
*******************************************************************************/
int CVICALLBACK GraphDisplayCB (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	double x = 0;
	double y = 0;
	
	switch (event)
	{
		case EVENT_COMMIT:
			//To do: 06
			GetGraphCursor(panel, MAIN_PANEL_IDC_GRAPH_DISPLAY, 1, &x, &y);
			
			SetCtrlVal(panel, MAIN_PANEL_IDC_NUM_SAMPLE_INDEX, x);
			SetCtrlVal(panel, MAIN_PANEL_IDC_NUM_SAMPLE_VALUE, y);
			//*********

			break;
	}
	return 0;
}

/*******************************************************************************
	functia de callback a numeric slide-ului interval de achizitie
*******************************************************************************/
int CVICALLBACK AcquisitionTimerPeriodCB (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	double val = 0.0;
	switch (event)
	{
		case EVENT_COMMIT:
			//To do 4
			//*********
			GetCtrlVal(panel, MAIN_PANEL_IDC_SL_ACQ_PERIOD, &val);
			SetCtrlAttribute(panel, MAIN_PANEL_SIMULATION_TIMER, ATTR_INTERVAL, val);
	
			break;
	}
	return 0;
}

/*******************************************************************************
	functia de callback a timerului de simulare
*******************************************************************************/
int CVICALLBACK OnSimulationTimerCB (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	
	switch (event)
	{
		case EVENT_TIMER_TICK:
			//To do: 04
			ManualAcquisitionCB(panel, MAIN_PANEL_IDC_GRAPH_DISPLAY, EVENT_COMMIT, NULL, 0, 0);
			ManualDisplayCB(panel, MAIN_PANEL_IDC_GRAPH_DISPLAY, EVENT_COMMIT, NULL, 0, 0);
			
			//*********
			
			
			break;
	}
	return 0;
}

