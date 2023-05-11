/**
 *  \mainpage libpos API Reference
 *
 *  \section objects POS objects
 *
 */

#ifndef __LIBDEMO_AUGUSTA_HID_C___
#define __LIBDEMO_AUGUSTA_HID_C___

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <memory.h>

#include "libDemo_Augusta.h"
#ifndef WIN32
# include <dlfcn.h>
#endif

// Augusta process
extern void
_Augusta_process_function_list();
extern void
_Augusta_process_device();
extern void
_Augusta_process_config();
extern void
_Augusta_process_msr();
extern void
_Augusta_process_icc();
extern void
_Augusta_process_emv();
extern void
_Augusta_display_device_menu();
extern void
_Augusta_display_emv_menu();
extern void
_Augusta_display_msr_menu();
extern void
_Augusta_display_config_menu();
extern void
_Augusta_display_icc_menu();

IDT_COMMON_PROCESS COMMON;
IDT_PROCESS idtech_process;
IDT_DEMO_LIB_DISPLAY_MENU idtech_display_menu_from_lib;

void
IDT_PROCESS_clean() {
    idtech_process.pProcess_function_list = NULL;
    idtech_process.pProcess_device        = NULL;
    idtech_process.pProcess_config        = NULL;
    idtech_process.pProcess_msr = NULL;
    idtech_process.pProcess_icc = NULL;
    idtech_process.pProcess_emv = NULL;
    idtech_process.pProcess_pin = NULL;
}

void
libDemo_getMenuFn(IDT_DEMO_LIB_DISPLAY_MENU * _idtech_display_menu_from_lib) {
    *_idtech_display_menu_from_lib = idtech_display_menu_from_lib;
}

void
libDemo_init(IDT_COMMON_PROCESS _demo_Common_Process, IDT_DEMO_LIB_DISPLAY_MENU * _idtech_display_menu_from_lib) {
    COMMON = _demo_Common_Process;
    // intialize the process function
    IDT_PROCESS_clean();
    idtech_process.pProcess_function_list = _Augusta_process_function_list;
    idtech_process.pProcess_device        = _Augusta_process_device;
    idtech_process.pProcess_config        = _Augusta_process_config;
    idtech_process.pProcess_msr = _Augusta_process_msr;
    idtech_process.pProcess_icc = _Augusta_process_icc;
    idtech_process.pProcess_emv = _Augusta_process_emv;


    // intialize the display menu callback
    idtech_display_menu_from_lib = *_idtech_display_menu_from_lib;
    idtech_display_menu_from_lib.pDisplay_Menu_device = _Augusta_display_device_menu;
    idtech_display_menu_from_lib.pDisplay_Menu_emv    = _Augusta_display_emv_menu;
    idtech_display_menu_from_lib.pDisplay_Menu_msr    = _Augusta_display_msr_menu;
    idtech_display_menu_from_lib.pDisplay_Menu_config = _Augusta_display_config_menu;
    idtech_display_menu_from_lib.pDisplay_Menu_icc    = _Augusta_display_icc_menu;

    *_idtech_display_menu_from_lib = idtech_display_menu_from_lib;
    // into the function menu selection
    idtech_process.pProcess_function_list();
}

#endif /* ifndef __LIBDEMO_AUGUSTA_HID_C___ */
