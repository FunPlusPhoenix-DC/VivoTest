/*
 * Copyright (C) ID TECH.
 *
 * Author: Eric
 *
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "demo_common.h"

IDT_COMMON_PROCESS COMMON;
extern IDT_PROCESS idtech_process;
extern IDT_DEMO_LIB_DISPLAY_MENU idtech_display_menu_from_lib;

// static int enableICC = 0;

void
display_Augusta_function_menu();

void
_Augusta_process_function_list() {
    int choice;

    //	msr_registerCallBk(COMMON.MSR_callBack);
    msr_registerCallBkp(COMMON.MSR_callBackp);

    emv_registerCallBk(COMMON.EMV_callBack);
    emv_allowFallback(1);
    registerLogCallBk(COMMON.SendDataLog,
      COMMON.ReadDataLog);

    // Get The Device Type
    // int deviceType = 1;

    //	if (!enableICC)
    //	{
    //		icc_enable(0); //To prevent cygwin issue (exception and quit).
    //		config_setBeeperController(1);
    //		enableICC = 1;
    //	}



    do {
        display_Augusta_function_menu();
        choice = COMMON.inputSelection();
        switch (choice) {
            case 1:
                if (idtech_process.pProcess_device) {
                    idtech_process.pProcess_device();
                }
                break;
            case 2:
                if (idtech_process.pProcess_config) {
                    idtech_process.pProcess_config();
                }
                break;
            case 3:
                if (idtech_process.pProcess_msr) {
                    idtech_process.pProcess_msr();
                }
                break;
            case 4:
                if (idtech_process.pProcess_icc) {
                    idtech_process.pProcess_icc();
                }
                break;
            case 5:
                if (idtech_process.pProcess_emv) {
                    idtech_process.pProcess_emv();
                }
                break;
            case 0:
                printf(">>0. Back To Device Selection Menu\n");
                fflush(stdout);
                break;
        }
    } while (choice != 0);
    if (choice == 0) {
        //      idtech_display_menu_from_lib.pDisplay_Menu_current = COMMON.main_display_device_list;
        COMMON.main_process_device_select();
    }
} /* _Augusta_process_function_list */

void
display_Augusta_function_menu() {
    idtech_display_menu_from_lib.pDisplay_Menu_current = display_Augusta_function_menu;
    printf("\t\t********** Universal SDK: [Augusta] ************\n");
    printf("\t\t0. Back To Device Selection Menu\n");
    printf("\t\t1. Device\n");
    printf("\t\t2. Config\n");
    printf("\t\t3. MSR\n");
    printf("\t\t4. ICC\n");
    printf("\t\t5. EMV\n");
    printf("\t\t************************************************\n");
    fflush(stdout);
}
