/*****************************************************************/
/*                                                               */
/*   CASIO fx-9860G SDK Library                                  */
/*                                                               */
/*   File name : [ProjectName].c                                 */
/*                                                               */
/*   Copyright (c) 2006 CASIO COMPUTER CO., LTD.                 */
/*                                                               */
/*****************************************************************/
// #define SH4

#include "fxlib.h"
#ifdef SH4
    #include "SH4_compatibility.h"
#else
    #define KEY_CTRL_EXE KEY_CHAR_PMINUS
#endif
#include "MonochromeLib.h"
#include "images.h"
#include "funcs.h"
#include "data.h"

#include "pages.h"


//****************************************************************************
//  AddIn_main (Sample program main function)
//
//  param   :   isAppli   : 1 = This application is launched by MAIN MENU.
//                        : 0 = This application is launched by a strip in eACT application.
//
//              OptionNum : Strip number (0~3)
//                         (This parameter is only used when isAppli parameter is 0.)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************
int AddIn_main(int isAppli, unsigned short OptionNum) {

    ML_clear_vram();
    ML_bmp_or(jwhgzs_png, 0, 0, 128, 64);
    WaitKey(KEY_CTRL_EXE);
    ML_clear_vram();
    ML_bmp_or(sn_png, 0, 0, 128, 64);
    WaitKey(KEY_CTRL_EXE);
    ML_clear_vram();
    ML_display_vram();

    PrintLocated(ML_SCREEN_WIDTH / 2, ML_SCREEN_HEIGHT / 2, "Press EXE to go!", 0);
    ML_display_vram();
    WaitKey(KEY_CTRL_EXE);
    page_game_entry();

    while (1)
        WaitAnyKey();

    return 1;
}




//****************************************************************************
//**************                                              ****************
//**************                 Notice!                      ****************
//**************                                              ****************
//**************  Please do not change the following source.  ****************
//**************                                              ****************
//****************************************************************************


#pragma section _BR_Size
unsigned long BR_Size;
#pragma section


#pragma section _TOP

//****************************************************************************
//  InitializeSystem
//
//  param   :   isAppli   : 1 = Application / 0 = eActivity
//              OptionNum : Option Number (only eActivity)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************
int InitializeSystem(int isAppli, unsigned short OptionNum) {
    return INIT_ADDIN_APPLICATION(isAppli, OptionNum);
}

#pragma section

