#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "demo_common.h"

IDT_COMMON_PROCESS COMMON;
extern IDT_PROCESS idtech_process;
extern IDT_DEMO_LIB_DISPLAY_MENU idtech_display_menu_from_lib;

void
_Augusta_display_icc_menu();

void
_Augusta_process_icc() {
    int choice;
    BYTE status;
    int r = 0;
    BYTE ATR[_DATA_BUF_LEN];
    int ATRLen;
    BYTE resData[_DATA_BUF_LEN];
    int resLen;

    do {
        _Augusta_display_icc_menu();
        choice = COMMON.inputSelection();
        switch (choice) {
            case 1:
                printf(">>1. Power On ICC\n");
                fflush(stdout);
                ATRLen = _DATA_BUF_LEN;
                memset(ATR, 0, ATRLen);
                r = icc_powerOnICC(ATR, &ATRLen);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf("  Do icc_powerOnICC failed! ErrorCode:0x%02x ,Info: %s ----- \n", r, strErr);
                } else {
                    printf("ICC Power On Succeeded\nATR: ");
                    int i;
                    for (i = 0; i < ATRLen; i++) {
                        printf("%02X ", ATR[i]);
                    }
                    printf("\n");
                }
                fflush(stdout);
                break;
            case 2:
                printf(">>2. Power Off ICC\n");
                fflush(stdout);
                r = icc_powerOffICC();
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf("  Do icc_powerOffICC failed! ErrorCode:0x%02x ,Info: %s ----- \n", r, strErr);
                } else {
                    printf("ICC Power Off Succeeded\n");
                }
                fflush(stdout);
                break;
            case 3: {
                printf(">>3. Send APDU\n");
                fflush(stdout);
                // input
                const char * strAPDU = "00a404000e315041592e5359532e444446303100";
                BYTE byteAPDU[800];
                int byteAPDULen = 800;
                COMMON.convertHStrIntoHex(strAPDU, byteAPDU, &byteAPDULen);
                // output
                BYTE data[200];
                int dataLen = 200;
                r = icc_exchangeAPDU(byteAPDU, byteAPDULen, data, &dataLen);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- icc_exchangeAPDU failed!! ErrorCode:0x%02x ,Info: %s ----- \n", r,
                        strErr);
                    fflush(stdout);
                    break;
                }
                char str1[1024] = { 0 };
                COMMON.convertBytesIntoHexStr(data, dataLen, 1, str1);
                printf(">>Get APDU Data: %s.\n", str1);
                fflush(stdout);
            }
            break;
            case 4: {
                printf(">>4. Get APDU KSN\n");
                fflush(stdout);
                int rt = 0;
                BYTE KSN[10];
                int ksnLen = 10;
                memset(KSN, 0, 10);
                rt = icc_getAPDU_KSN(KSN, &ksnLen);
                if (rt == RETURN_CODE_DO_SUCCESS) {
                    char str2[100];
                    memset(str2, 0, 100);
                    COMMON.convertBytesIntoHexStr(KSN, 10, 1, str2);
                    printf("APDU KSN = %s\r\n", str2);
                } else {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(rt, strErr);
                    printf("APDU KSN failed! ErrorCode:0x%04x ,Info: %s ----- \n", rt, strErr);
                }
                fflush(stdout);
            }
            break;
            case 5: {
                printf(">>5. Get ICC DUKPT Key Type\n");
                fflush(stdout);
                BYTE type = 0x00;
                r = icc_getKeyTypeForICCDUKPT(&type);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf("Get Key Type For ICC DUKPT failed! ErrorCode:0x%02x ,Info: %s ----- \n", r, strErr);
                } else {
                    if (type == 0x00) {
                        printf("Key Type For ICCDUKPT Key: Data\r\n");
                    } else if (type == 0x01) {
                        printf("Key Type For ICCDUKPT Key: PIN\r\n");
                    } else {
                        printf("Key Type For ICCDUKPT Key: Error\r\n");
                    }
                }
                fflush(stdout);
            }
            break;
            //		case 6:
            //			printf(">>6. Set Format TDES\n");
            //			fflush(stdout);
            //			r = icc_setKeyFormatForICCDUKPT(0x00);
            //			if ( r != RETURN_CODE_DO_SUCCESS ) {
            //				char strErr[200] = {0};
            //				memset(strErr,0,200);
            //				device_getResponseCodeString(r, strErr);
            //				printf("  Do icc_setKeyFormatForICCDUKPT(0x00) failed! ErrorCode:0x%02x ,Info: %s ----- \n",r,strErr);
            //			}
            //			else{
            //				printf("Set Format TDES Succeeded\n");
            //			}
            //			fflush(stdout);
            //		break;
            //		case 7:
            //		{
            //			printf(">>7. Set Format AES\n");
            //			fflush(stdout);
            //			r = icc_setKeyFormatForICCDUKPT(0x01);
            //			if ( r != RETURN_CODE_DO_SUCCESS ) {
            //				char strErr[200] = {0};
            //				memset(strErr,0,200);
            //				device_getResponseCodeString(r, strErr);
            //				printf("  Do icc_setKeyFormatForICCDUKPT(0x01) failed! ErrorCode:0x%02x ,Info: %s ----- \n",r,strErr);
            //			}
            //			else{
            //				printf("Set Format AES Succeeded\n");
            //			}
            //			fflush(stdout);
            //		}
            //		break;
            //		case 8:
            //			printf(">>8. Enable ICC with Notification\n");
            //			r = icc_enable(1);
            //			if ( r != RETURN_CODE_DO_SUCCESS ) {
            //				char strErr[200] = {0};
            //				memset(strErr,0,200);
            //				device_getResponseCodeString(r, strErr);
            //				printf("  Do icc_enable failed! ErrorCode:0x%02x ,Info: %s ----- \n",r,strErr);
            //			}
            //			else{
            //				printf("Enable ICC with Notification Succeeded\n");
            //			}
            //		break;
            case 6:
                printf(">>6. Enable ICC without Notification\n");
                fflush(stdout);
                r = icc_enable(0);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf("  Do icc_enable failed! ErrorCode:0x%02x ,Info: %s ----- \n", r, strErr);
                } else {
                    printf("Enable ICC Succeeded\n");
                }
                fflush(stdout);
                break;
            case 7:
                printf(">>7. Disable ICC\n");
                fflush(stdout);
                r = icc_disable();
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf("  Do icc_disable failed! ErrorCode:0x%02x ,Info: %s ----- \n", r, strErr);
                } else {
                    printf("Disable ICC Succeeded\n");
                }
                fflush(stdout);
                break;
            case 8: {
                printf(">>8. Get Reader Status\n");
                fflush(stdout);
                BYTE status;
                r = icc_getICCReaderStatus(&status);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf("  Do icc_getICCReaderStatus failed! ErrorCode:0x%02x ,Info: %s ----- \n", r, strErr);
                } else {
                    printf("Get Reader Status Succeeded\n");
                    BYTE bit0 = (BYTE) (status & 0x01);
                    BYTE bit1 = (BYTE) ((status & 0x02) >> 1);
                    printf("Reader Status: %s %s\n", (bit0 == 1 ? "[ICC Powered]" : "[ICC Power Not Ready]"),
                      (bit1 == 1 ? "[Card Seated]" : "[Card Not Seated]"));
                }
                fflush(stdout);
            }
            break;
            case 9:
                printf(">>9. Get Function Status\n");
                fflush(stdout);
                int enabled;
                int withNotification;
                r = icc_getFunctionStatus(&enabled, &withNotification);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf("  Do icc_getFunctionStatus failed! ErrorCode:0x%02x ,Info: %s ----- \n", r, strErr);
                } else {
                    printf("Get Function Status Succeeded\n");
                    if (enabled) {
                        if (withNotification) {
                            printf("ICC Enabled and Notification On\n");
                        } else {
                            printf("ICC Enabled and Notification Off\n");
                        }
                    } else {
                        if (withNotification) {
                            printf("ICC Disabled and Notification On\n");
                        } else {
                            printf("ICC Disabled and Notification Off\n");
                        }
                    }
                }
                fflush(stdout);
                break;
            case 0:
                printf(">>0.Back To Main Menu\n");
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
} /* _Augusta_process_icc */

void
_Augusta_display_icc_menu() {
    idtech_display_menu_from_lib.pDisplay_Menu_current = _Augusta_display_icc_menu;
    printf("\t\t********** ICC Options [Augusta]************\n");
    printf("\t\t0.  Back To Main Menu\n");
    printf("\t\t1.  Power On ICC\n");
    printf("\t\t2.  Power Off ICC\n");
    printf("\t\t3.  Send APDU\n");
    printf("\t\t4.  Get APDU KSN\n");
    printf("\t\t5.  Get ICC DUKPT Key Type\n");
    //	printf("\t\t6.  Set Format TDES\n");
    //	printf("\t\t7.  Set Format AES\n");
    //	printf("\t\t8.  Enable ICC with Notification\n");
    //	printf("\t\t9.  Enable ICC without Notification\n");
    printf("\t\t6.  Enable ICC\n");
    printf("\t\t7.  Disable ICC\n");
    printf("\t\t8.  Get Reader Status\n");
    printf("\t\t9.  Get Function Status\n");
    printf("\t\t************************************************\n");
    fflush(stdout);
}
