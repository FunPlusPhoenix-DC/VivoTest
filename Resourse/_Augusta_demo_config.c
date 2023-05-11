#include <stdio.h>
#include <string.h>
#include "demo_common.h"

IDT_COMMON_PROCESS COMMON;
extern IDT_PROCESS idtech_process;
extern IDT_DEMO_LIB_DISPLAY_MENU idtech_display_menu_from_lib;


void
_Augusta_display_config_menu();

void
_Augusta_process_config() {
    int choice;
    int r = 0;
    char str1[256] = { 0 };

    memset(str1, 0, 256);
    do {
        _Augusta_display_config_menu();
        choice = COMMON.inputSelection();
        switch (choice) {
            case 1:
                printf(">>1. Get Model Number\n");
                fflush(stdout);
                r = config_getModelNumber(str1);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- Get Model Number Failed! ErrorCode: 0x%02x, Info: %s ----- \n", r,
                        strErr);
                } else {
                    char str2[200] = { 0 };
                    sprintf(str2, "Model Number: %s\n", str1);
                    printf(str2);
                }
                fflush(stdout);
                break;
            case 2: {
                printf(">>2. Get Serial Number\n");
                fflush(stdout);
                r = config_getSerialNumber(str1);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- Get Serial Number Failed! ErrorCode: 0x%02x, Info: %s ----- \n", r,
                        strErr);
                } else {
                    char str2[200] = { 0 };
                    sprintf(str2, "Serial Number: %s\n", str1);
                    printf(str2);
                }
                fflush(stdout);
            }
            break;

            case 3: {
                printf(">>3. Control Beep SW\n");
                fflush(stdout);
                r = config_setBeeperController(0);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- Control Beep Software Failed! ErrorCode: 0x%02x, Info: %s ----- \n", r,
                        strErr);
                } else {
                    printf("Beep controller with SW successfully\n");
                }
                fflush(stdout);
            }
            break;

            case 4: {
                printf(">>4. Control Beep FW\n");
                fflush(stdout);
                r = config_setBeeperController(1);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- Control Beep Firmware Failed! ErrorCode: 0x%02x, Info: %s ----- \n", r,
                        strErr);
                } else {
                    printf("Beep controller with FW successfully\n");
                }
                fflush(stdout);
            }
            break;
            case 5: {
                printf(">>5. Control MSR LED SW\n");
                fflush(stdout);
                r = config_setLEDController(0, 0);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- Control MSR LED Software Failed! ErrorCode: 0x%02x, Info: %s ----- \n", r,
                        strErr);
                } else {
                    printf("Control MSR LED SW successfully\n");
                }
                fflush(stdout);
            }
            break;

            case 6: {
                printf(">>6. Control MSR LED FW\n");
                fflush(stdout);
                r = config_setLEDController(1, 0);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- Control MSR LED Firmware Failed! ErrorCode: 0x%02x, Info: %s ----- \n", r,
                        strErr);
                } else {
                    printf("Control MSR LED FW successfully\n");
                }
                fflush(stdout);
            }
            break;
            case 7: {
                printf(">>7. Set Enc. Control ON\n");
                fflush(stdout);
                r = config_setEncryptionControl(1, 1);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- Set Encryption Control On Failed! ErrorCode: 0x%02x, Info: %s ----- \n", r,
                        strErr);
                } else {
                    printf("Set Enc. Control ON successfully\n");
                }
                fflush(stdout);
            }
            break;
            case 8: {
                printf(">>8. Set Enc. Control MSR ON\n");
                fflush(stdout);
                r = config_setEncryptionControl(1, 0);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- Set Encryption Control MSR On Failed! ErrorCode: 0x%02x, Info: %s ----- \n", r,
                        strErr);
                } else {
                    printf("Set Enc. Control MSR ON successfully\n");
                }
                fflush(stdout);
            }
            break;
            case 9: {
                printf(">>9. Set Enc. Control EMV/ICC ON\n");
                fflush(stdout);
                r = config_setEncryptionControl(0, 1);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- Set Encryption Control EMV/ICC On Failed! ErrorCode: 0x%02x, Info: %s ----- \n", r,
                        strErr);
                } else {
                    printf("Set Enc. Control EMV/ICC ON successfully\n");
                }
                fflush(stdout);
            }
            break;

            case 10: {
                printf(">>10. Get Config status\n");
                fflush(stdout);
                int msr = 0;
                int icc = 0;
                // MSR and ICC encryption status
                r = config_getEncryptionControl(&msr, &icc);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- Get Encryption Control Failed! ErrorCode: 0x%02x, Info: %s ----- \n", r,
                        strErr);
                } else {
                    printf("Get Enc. Control status:%s %s.\n", msr == 1 ? "MSR: ON " : "MSR: OFF ",
                      icc == 1 ? "ICC: ON " : "ICC: OFF ");
                }
                fflush(stdout);
                // Beeper status
                int beeperByWho = 0;
                r = config_getBeeperController(&beeperByWho);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- Get Beeper Controller Failed! ErrorCode: 0x%02x, Info: %s ----- \n", r,
                        strErr);
                } else {
                    printf("Beeper controller by:%s\n", beeperByWho == 1 ? "firmware. " : "software. ");
                }
                fflush(stdout);
                // MSR and ICC LED status
                int msrLED = 0;
                int iccLED = 0;
                r = config_getLEDController(&msrLED, &iccLED);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- Get MSRS LED Controller Failed! ErrorCode: 0x%02x, Info: %s ----- \n", r,
                        strErr);
                } else {
                    printf("MSR LED controller by:%s\n", (msrLED == 1 ? "firmware. " : "software. "));
                }
                fflush(stdout);
            }
            break;
            case 0:
                printf(">>0. Back To Main Menu\n");
                fflush(stdout);
                break;
        }
    } while (choice != 0);
    // #ifdef WIN32
    if (choice == 0) {
//        idtech_process.pProcess_function_list();
        return;
    }
    // #endif
} /* _Augusta_process_config */

void
_Augusta_display_config_menu() {
    idtech_display_menu_from_lib.pDisplay_Menu_current = _Augusta_display_config_menu;
    printf("\t\t********* Config Options [Augusta]**********\n");
    printf("\t\t0.  Back To Main Menu\n");
    printf("\t\t1.  Get Model Number\n");
    printf("\t\t2.  Get Serial Number\n");
    printf("\t\t3.  Control Beep SW\n");
    printf("\t\t4.  Control Beep FW\n");
    printf("\t\t5.  Control MSR LED SW\n");
    printf("\t\t6.  Control MSR LED FW\n");
    printf("\t\t7.  Set Enc. Control ON\n");
    printf("\t\t8.  Set Enc. Control MSR ON\n");
    printf("\t\t9.  Set Enc. Control EMV/ICC ON\n");
    printf("\t\t10. Get Config status\n");
    printf("\t\t************************************************\n");
    fflush(stdout);
}
