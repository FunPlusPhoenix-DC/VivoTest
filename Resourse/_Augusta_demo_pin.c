#include <stdio.h>
#include <string.h>
#include "demo_common.h"

IDT_COMMON_PROCESS COMMON;
EXPORT_SYMBOLS IDT_PROCESS idtech_process;
EXPORT_SYMBOLS IDT_DEMO_LIB_DISPLAY_MENU idtech_display_menu_from_lib;

void
_Augusta_display_pin_menu();
void
_Augusta_process_pin() {
    int choice;
    int r = 0;
    char str1[256] = { 0 };

    memset(str1, 0, 256);
    pin_registerCallBk(COMMON.PIN_callBack);
    do {
        _Augusta_display_pin_menu();
        choice = COMMON.inputSelection();
        switch (choice) {
            case 1:
                printf(">>1. Get PIN from MSR\n");
                fflush(stdout);
                r = pin_getPIN(1, 1, null, 0, 30, 60, (char*)"EN", 2);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- Get PIN From MSR Failed! ErrorCode: 0x%02x, Info: %s ----- \n", r,
                        strErr);
                } else {
                    printf("PIN Get PIN Succeeded\n");
                    printf("Please Enter PIN on PIN Pad...\n");
                }
                fflush(stdout);
                break;
            case 2:{
                printf(">>2. Cancel PIN Entry\n");
                fflush(stdout);
                pin_cancelPINEntry();
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- Cancel PIN Entry Failed! ErrorCode: 0x%02x, Info: %s ----- \n", r,
                        strErr);
                } else {
                    printf("PIN Cancel PIN Succeeded\n");
                }
                fflush(stdout);
                break;
            }
                
            case 0:{
                if (isPINBusy) {
                    printf("PIN Busy\n");
                    choice = -1;
                } else {
                    printf(">>0. Back To Main Menu\n");
                }
                fflush(stdout);
                break;
            }
                
        }
    } while (choice != 0);
    // #ifdef WIN32
    if (choice == 0) {
//        idtech_process.pProcess_function_list();
        return;
    }
    // #endif
} /* _Augusta_process_pin */

void
_Augusta_display_pin_menu() {
    idtech_display_menu_from_lib.pDisplay_Menu_current = _Augusta_display_pin_menu;
    printf("\t\t********* Config Options [Augusta]**********\n");
    printf("\t\t0. Back To Main Menu\n");
    printf("\t\t1. Get PIN from MSR\n");
    printf("\t\t2. Cancel PIN Entry\n");
    printf("\t\t************************************************\n");
    fflush(stdout);
}
