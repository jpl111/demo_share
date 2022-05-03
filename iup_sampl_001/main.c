#include <stdio.h>
#include <stdint.h>

#include "iup.h"

#include <assert.h>


#include <string.h>


#ifdef USG_WINMAIN
#include <windows.h>
#endif

//Declear
int     OnBtnOk(Ihandle* pSelf);

//File sel
int     OnClickSelFile(Ihandle* pSelf);


#ifdef USG_WINMAIN
int _stdcall WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow
)
#else
int main(int argc, char* argv[])

#endif
{
    Ihandle *dlg, *label,*pTextWnd,*pHbox,*pFileBtn,*pOkBtn,*pVBox,*pHboxLine2,*pSpaceLine2;

#ifdef USG_WINMAIN
    IupOpen(NULL, NULL);
#else
    IupOpen(&argc, &argv);
#endif

	//IupMessage("tutor001", "Hello From Iup!");


   // char szFileName[1024];

    //IupGetFile(szFileName);

    //First row
    label =  IupLabel("File:");
    IupSetAttribute(label,"SIZE","20");

    pTextWnd = IupText(NULL);
    IupSetAttribute(pTextWnd,"SIZE","150");
    IupSetAttribute(pTextWnd, "EXPAND", "HORIZONTAL");
    IupSetAttribute(pTextWnd, "NAME", "txt_file_name");
    IupSetAttribute(pTextWnd, "READONLY", "YES");

    pFileBtn = IupButton("..",NULL);
    IupSetAttribute(pFileBtn,"SIZE","30");
    IupSetCallback(pFileBtn,"ACTION",(Icallback)OnClickSelFile); //Set file selection callback

    pHbox = IupHbox(label,
             pTextWnd,
             pFileBtn,
             NULL);

    //Second row 
    pOkBtn = IupButton("Ok",NULL);
    IupSetAttribute(pOkBtn,"SIZE","60");

    IupSetCallback(pOkBtn,"ACTION",(Icallback)OnBtnOk);

    pSpaceLine2 = IupSpace();
    IupSetAttribute(pSpaceLine2, "EXPAND", "HORIZONTAL");
    pHboxLine2 = IupHbox(
        pSpaceLine2,
        pOkBtn,
        NULL
    );


    //Main layout for two row
    pVBox = IupVbox(pHbox,pHboxLine2,NULL);


   IupSetAttribute(pVBox, "MARGIN", "10x10");
   IupSetAttribute(pVBox, "GAP", "10");




    //Show model dialog
    dlg = IupDialog(pVBox);



    IupSetAttribute(dlg, "TITLE", "File Sel");
    //IupSetAttribute(dlg, "RESIZE", "NO");

    //IupShowXY(dlg, IUP_CENTER, IUP_CENTER);

    IupPopup(dlg,IUP_CENTER,IUP_CENTER);

    //After dialog disapeared,Get text input value
    const char* pValue = IupGetAttribute(pTextWnd,"VALUE");

    if(pValue)
    {
        printf("%s \n",pValue);
    }
    


   //IupMainLoop();

	IupClose();

    pValue = NULL; //The value not valid


    return 0;
    
}

int     OnBtnOk(Ihandle* pSelf)
{
    Ihandle* pItem = IupGetDialogChild(pSelf,"txt_file_name");

    assert(pItem);

    if(!pItem) 
    { 
        IupAlarm("Warning","App Error!","Ok",NULL,NULL);
        return IUP_CONTINUE;
    }

    const char* pVal = IupGetAttribute(pItem,"VALUE");

    if(strlen(pVal)<1)
    {

        IupAlarm("Warning","Nothing Input!!!","Ok",NULL,NULL);

        return IUP_CONTINUE;
    }

    return IUP_CLOSE; //Return IUP_CLOSE for close dialog ,Return IUP_IGNORE for ignore this operation
}

int     OnClickSelFile(Ihandle* pSelf)
{
     Ihandle* pItem = IupGetDialogChild(pSelf,"txt_file_name");

    assert(pItem);

    if(!pItem) 
    { 
        IupAlarm("Warning","App Error!","Ok",NULL,NULL);
        return IUP_CONTINUE;
    }

    char szFileName[1024];
    memset(szFileName,0,1024);
    IupGetFile(szFileName);

    IupSetAttribute(pItem,"VALUE",szFileName);


    return IUP_CONTINUE;
}
