/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  MAIN_PANEL                       1       /* callback function: OnMainPanel */
#define  MAIN_PANEL_BINARYSWITCH          2       /* control type: binary, callback function: OnReteaSwitch */
#define  MAIN_PANEL_BINARYSWITCH_2        3       /* control type: binary, callback function: OnAchizitieSwitch */
#define  MAIN_PANEL_PANEL_GRAPH_SIGNAL    4       /* control type: strip, callback function: (none) */
#define  MAIN_PANEL_POWER_LED             5       /* control type: LED, callback function: (none) */
#define  MAIN_PANEL_ACHIZITIE_BUTTON      6       /* control type: command, callback function: (none) */
#define  MAIN_PANEL_AFISEAZA_BUTTON       7       /* control type: command, callback function: (none) */
#define  MAIN_PANEL_NUMERIC_ESANTION      8       /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_COLORNUM              9       /* control type: color, callback function: (none) */
#define  MAIN_PANEL_COLORNUM_2            10      /* control type: color, callback function: (none) */
#define  MAIN_PANEL_TOGGLEBUTTON          11      /* control type: textButton, callback function: (none) */
#define  MAIN_PANEL_STRING_VALOARE        12      /* control type: string, callback function: (none) */
#define  MAIN_PANEL_TOGGLEBUTTON_2        13      /* control type: textButton, callback function: (none) */
#define  MAIN_PANEL_STRING_MIN            14      /* control type: string, callback function: (none) */
#define  MAIN_PANEL_STRING_MAX            15      /* control type: string, callback function: (none) */
#define  MAIN_PANEL_STRING_AVG            16      /* control type: string, callback function: (none) */
#define  MAIN_PANEL_NUMERICSLIDE          17      /* control type: scale, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

#define  MENUBAR                          1
#define  MENUBAR_MENU1                    2
#define  MENUBAR_MENU1_ITEM1              3       /* callback function: OnFileNew */
#define  MENUBAR_MENU1_ITEM3              4       /* callback function: OnFileSave */
#define  MENUBAR_MENU1_ITEM4              5       /* callback function: OnFileLoad */
#define  MENUBAR_MENU2                    6
#define  MENUBAR_MENU2_MENU5              7       /* callback function: OnFileAbout */
#define  MENUBAR_MENU3                    8       /* callback function: OnExit */


     /* Callback Prototypes: */

int  CVICALLBACK OnAchizitieSwitch(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK OnExit(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK OnFileAbout(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK OnFileLoad(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK OnFileNew(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK OnFileSave(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK OnMainPanel(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnReteaSwitch(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif