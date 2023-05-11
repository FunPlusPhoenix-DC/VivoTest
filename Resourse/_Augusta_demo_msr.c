#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "demo_common.h"

IDT_COMMON_PROCESS COMMON;
EXPORT_SYMBOLS IDT_PROCESS idtech_process;
EXPORT_SYMBOLS IDT_DEMO_LIB_DISPLAY_MENU idtech_display_menu_from_lib;

void
_Augusta_display_msr_menu();

void
_Augusta_process_msr() {
    int choice;
    BYTE resData[_DATA_BUF_LEN];
    int resLen;
    int r;

    //	msr_registerCallBk(COMMON.MSR_callBack);
    //	msr_registerCallBkp(COMMON.MSR_callBackp);
    do {
        _Augusta_display_msr_menu();
        choice = COMMON.inputSelection();
        switch (choice) {
            case 1:
                printf(">>1. Start MSR\n");
                fflush(stdout);
                r = msr_startMSRSwipe(30);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    printf("  Do msr_startMSRSwipe(), failed! Error Code: %04X\n", r);
                } else {
                    printf("MSR Start MSR Swipe Succeeded\n");
                    printf("Please Swipe Card...\n");
                }
                fflush(stdout);
                #ifdef WIN32
                # ifdef DBG
                while (isMSRBusy) { // for debug purpose, otherwise the breakpoints in MSR callback function won't work (it will hang in the MSR callback function).
                    Sleep(100);
                }
                # endif
                #endif
                break;
            case 2:{
                printf(">>2. Cancel MSR\n");
                fflush(stdout);
                r = msr_cancelMSRSwipe();
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf("  Do msr_cancelMSRSwipe failed! ErrorCode:0x%02x ,Info: %s ----- \n", r, strErr);
                } else {
                    printf("MSR Cancel MSR Swipe Succeeded\n");
                }
                fflush(stdout);
                break;
            }
                
            case 3:{
                printf(">>3. Set Expiration Mask ON\n");
                fflush(stdout);
                r = msr_setExpirationMask(1);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf("  Do msr_setExpirationMask(1) failed! ErrorCode:0x%02x ,Info: %s ----- \n", r, strErr);
                } else {
                    printf("Set Expiration Mask ON Succeeded\n");
                }
                fflush(stdout);
                break;
            }
                
            case 4:{
                printf(">>4. Set Expiration Mask OFF\n");
                fflush(stdout);
                r = msr_setExpirationMask(0);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf("  Do msr_setExpirationMask(0), failed! ErrorCode:0x%02x ,Info: %s ----- \n", r, strErr);
                } else {
                    printf("Set Expiration Mask OFF Succeeded\n");
                }
                fflush(stdout);
                break;
            }
                
            case 5:{
                printf(">>5. Get Expiration Mask Status\n");
                fflush(stdout);
                BYTE response = 0x00;
                r = msr_getExpirationMask(&response);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf("  Do msr_getExpirationMask(), failed! ErrorCode:0x%02x ,Info: %s ----- \n", r, strErr);
                } else {
                    printf("Get Expiration Mask Status Succeeded\n");
                    printf("Expiration Masking: %s\r\n", ((response == 0x30) ? "Masked" : "Unmasked"));
                }
                fflush(stdout);
                break;
            }
                
            case 6:{
                printf(">>6. Set PAN Clear Digits\n");
                fflush(stdout);
                r = msr_setClearPANID(0x04);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf("  Do msr_setClearPANID(), failed! ErrorCode:0x%02x ,Info: %s ----- \n", r, strErr);
                } else {
                    printf("Set PAN Clear Digits Succeeded\n");
                }
                fflush(stdout);
                break;
            }
                
            case 7: {
                printf(">>7. Get PAN Clear Digits\n");
                fflush(stdout);
                BYTE response = 0x00;
                r = msr_getClearPANID(&response);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf("  Do msr_getClearPANID(), failed! ErrorCode:0x%02x ,Info: %s ----- \n", r, strErr);
                } else {
                    printf("Get Clear PAN Digits Succeeded\n");
                    printf("Get Clear PAN Digits Response: %d\r\n", response);
                }
                fflush(stdout);
                break;
            }
            


            case 8:{
                printf(">>8. Set Swipe Force Enc. ON\n");
                fflush(stdout);
                r = msr_setSwipeForcedEncryptionOption(1, 1, 1, 1);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf("  Do msr_setSwipeForcedEncryptionOption(1), failed! ErrorCode:0x%02x ,Info: %s ----- \n", r,
                      strErr);
                } else {
                    printf("Set Swipe Force Enc. ON Succeeded\n");
                }
                fflush(stdout);
                break;
            }
                
            case 9:{
                printf(">>9. Set Swipe Force Enc. OFF\n");
                    fflush(stdout);
                    r = msr_setSwipeForcedEncryptionOption(0, 0, 0, 0);
                    if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf("  Do msr_setSwipeForcedEncryptionOption(0), failed! ErrorCode:0x%02x ,Info: %s ----- \n", r,
                      strErr);
                } else {
                    printf("Set Swipe Force Enc. OFF Succeeded\n");
                }
                fflush(stdout);
                break;
            }
            
                    
            
            case 10: {
                printf(">>10. Get Swipe Force Enc.\n");
                fflush(stdout);
                BYTE format = 0x00;
                r = msr_getSwipeForcedEncryptionOption(&format);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf("  Do msr_getSwipeForcedEncryptionOption(), failed! ErrorCode:0x%02x ,Info: %s ----- \n", r,
                      strErr);
                } else {
                    printf("Get Swipe Force Enc. Succeeded\n");
                    if ((format & 0x01) == 0x01) {
                        printf("\tTrack 1 Swipe Force Encryption: ON\r\n");
                    } else {
                        printf("\tTrack 1 Swipe Force Encryption: OFF\r\n");
                    }
                    if ((format & 0x02) == 0x02) {
                        printf("\tTrack 2 Swipe Force Encryption: ON\r\n");
                    } else {
                        printf("\tTrack 2 Swipe Force Encryption: OFF\r\n");
                    }
                    if ((format & 0x04) == 0x04) {
                        printf("\tTrack 3 Swipe Force Encryption: ON\r\n");
                    } else {
                        printf("\tTrack 3 Swipe Force Encryption: OFF\r\n");
                    }
                    if ((format & 0x08) == 0x08) {
                        printf("\tTrack 3 Option 0 Swipe Force Encryption: ON\r\n");
                    } else {
                        printf("\tTrack 3 Option 0 Swipe Force Encryption: OFF\r\n");
                    }
                }
                fflush(stdout);
                break;
            }
            
            case 11:{
                printf(">>11. Set Swipe Mask ON.\n");
                fflush(stdout);
                r = msr_setSwipeMaskOption(1, 1, 1);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf("  Do msr_setSwipeMaskOption(1), failed! ErrorCode:0x%02x ,Info: %s ----- \n", r, strErr);
                } else {
                    printf("Set Swipe Mask ON Succeeded\n");
                }
                fflush(stdout);
                break;
            }
                
            case 12:{
                printf(">>12. Set Swipe Mask OFF\n");
                fflush(stdout);
                r = msr_setSwipeMaskOption(0, 0, 0);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf("  Do msr_setSwipeMaskOption(0), failed! ErrorCode:0x%02x ,Info: %s ----- \n", r, strErr);
                } else {
                    printf("Set Swipe Mask OFF Succeeded\n");
                }
                fflush(stdout);
                break;
            }
                
            case 13: {
                printf(">>13. Get Swipe Mask\n");
                fflush(stdout);
                BYTE format = 0x00;
                r = msr_getSwipeMaskOption(&format);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf("  Do msr_getSwipeMaskOption(), failed! ErrorCode:0x%02x ,Info: %s ----- \n", r, strErr);
                } else {
                    printf("Get Swipe Mask Status Succeeded\n");
                    if ((format & 0x01) == 0x01) {
                        printf("\tTrack 1 Mask Option: ON\r\n");
                    } else {
                        printf("\tTrack 1 Mask Option: OFF\r\n");
                    }
                    if ((format & 0x02) == 0x02) {
                        printf("\tTrack 2 Mask Option: ON\r\n");
                    } else {
                        printf("\tTrack 2 Mask Option: OFF\r\n");
                    }
                    if ((format & 0x04) == 0x04) {
                        printf("\tTrack 3 Mask Option: ON\r\n");
                    } else {
                        printf("\tTrack 3 Mask Option: OFF\r\n");
                    }
                }
                fflush(stdout);
                break;
            }
            

            case 14: {
                printf(">>14. Set MSR Setting\n");
                fflush(stdout);
                BYTE settingVal[1] = { 0 };
                settingVal[0] = 0x04;
                r = msr_setSetting(0x49, settingVal, 1);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf("  Do msr_setSetting(), failed! ErrorCode:0x%02x ,Info: %s ----- \n", r, strErr);
                } else {
                    printf("Set MSR Setting Succeeded\n");
                }
                fflush(stdout);
                break;
            }
            
            case 15: {
                printf(">>15. Get MSR Setting\n");
                fflush(stdout);
                BYTE settingVal[256] = { 0 };
                int valLen = 256;
                r = msr_getSetting(0x49, settingVal, &valLen);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf("  Do msr_getSetting(), failed! ErrorCode:0x%02x ,Info: %s ----- \n", r, strErr);
                } else {
                    printf("Get MSR Setting Succeeded:\n");
                    char str1[1024] = { 0 };
                    COMMON.convertBytesIntoHexStr(settingVal, valLen, 1, str1);
                    printf("\tMSR Setting: 0x49: %s.\n", str1);
                }
                fflush(stdout);
            }
            break;
            //		case 16:
            //			printf(">>16. Set Swipe TDES\n");
            //			fflush(stdout);
            //			r = msr_setSwipeEncryption(0x01);
            //			if ( r != RETURN_CODE_DO_SUCCESS ) {
            //				char strErr[200] = {0};
            //				memset(strErr,0,200);
            //				device_getResponseCodeString(r, strErr);
            //				printf("  Do msr_setSwipeEncryption(0x01), failed! ErrorCode:0x%02x ,Info: %s ----- \n",r,strErr);
            //			}
            //			else{
            //				printf("Set Swipe TDES Succeeded\n");
            //			}
            //			fflush(stdout);
            //		break;
            //		case 17:
            //			printf(">>17. Set Swipe AES\n");
            //			fflush(stdout);
            //			r = msr_setSwipeEncryption(0x02);
            //			if ( r != RETURN_CODE_DO_SUCCESS ) {
            //				char strErr[200] = {0};
            //				memset(strErr,0,200);
            //				device_getResponseCodeString(r, strErr);
            //				printf("  Do msr_setSwipeEncryption(0x02), failed! ErrorCode:0x%02x ,Info: %s ----- \n",r,strErr);
            //			}
            //			else{
            //				printf("Set Swipe AES Succeeded\n");
            //			}
            //			fflush(stdout);
            //		break;
            //
            //		case 18:
            //		{
            //			printf(">>18. Get Swipe Encryption.\n");
            //			fflush(stdout);
            //			BYTE format = 0x00;
            //			r = msr_getSwipeEncryption(&format);
            //			if ( r != RETURN_CODE_DO_SUCCESS ) {
            //				char strErr[200] = {0};
            //				memset(strErr,0,200);
            //				device_getResponseCodeString(r, strErr);
            //				printf("  Do msr_getExpirationMask(0), failed! ErrorCode:0x%02x ,Info: %s ----- \n",r,strErr);
            //			}
            //			else{
            //				printf("Get Expiration Mask Status Succeeded\n");
            ////                if (format == 0x31)
            //				if (format == 0x00)
            //                {
            //                    printf("\tSwipe Encryption for MSR: TDES\r\n");
            //                }
            ////                else if (format == 0x32)
            //				else if (format == 0x01)
            //                {
            //                    printf("\tSwipe Encryption for MSR: AES\r\n");
            //                }
            //				else if (format == 0x02)
            //				{
            //					printf("\tSwipe Encryption for MSR: TransArmor\r\n");
            //				}
            //                else
            //                {
            //                    printf("\tSwipe Encryption for MSR: None\r\n");
            //                }
            //			}
            //			fflush(stdout);
            //		}
            //		break;


            case 16:{
                printf(">>16. Enter Buffer Mode\n");
                fflush(stdout);
                r = msr_captureMode(1, 1);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf("  Do msr_captureMode(1,1), failed! ErrorCode:0x%02x ,Info: %s ----- \n", r, strErr);
                } else {
                    printf("Enter Buffer Mode Succeeded\n");
                }
                fflush(stdout);
                break;
            }
                
            //		case 20:
            //			printf(">>20. Enter Auto Mode\n");
            //			fflush(stdout);
            //			r = msr_captureMode(0,0);
            //			if ( r != RETURN_CODE_DO_SUCCESS ) {
            //				char strErr[200] = {0};
            //				memset(strErr,0,200);
            //				device_getResponseCodeString(r, strErr);
            //				printf("  Do msr_captureMode(0,0), failed! ErrorCode:0x%02x ,Info: %s ----- \n",r,strErr);
            //			}
            //			else{
            //				printf("Enter Auto Mode Succeeded\n");
            //			}
            //			fflush(stdout);
            //		break;
            case 17:
                {
                    printf(">>17. Disable MSR\n");
                fflush(stdout);
                r = msr_disable();
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf("  Do msr_disable(), failed! ErrorCode:0x%02x ,Info: %s ----- \n", r, strErr);
                } else {
                    printf("Disable MSR Succeeded\n");
                }
                fflush(stdout);
                break;
                }
            //		case 22:
            //		{
            //			printf(">>22. Set White List\n");
            //			BYTE* Augusta_MAC_BDK = "0123456789ABCDEFFEDCBA9876543210";
            //			BYTE whiteList[1024]={0};
            //			int whiteLislen =1024;
            //			char * str_whiteLis ="3072020101316D300C1300020304B499020304B499300C13000203092A490203092A49300C13000203092BE00203092BE0300C13000203097DCA0203097DCB300C13000203099C630203099C63300C130002030BDDE402030BDE473017130B436F6D6F7461204361726402030ACC1002030ACC73";
            //			COMMON.convertHStrIntoHex(str_whiteLis,whiteList,&whiteLislen);
            //			r = msr_setWhiteList(whiteList,whiteLislen,Augusta_MAC_BDK);
            //			if ( r != RETURN_CODE_DO_SUCCESS ) {
            //				char strErr[200] = {0};
            //				memset(strErr,0,200);
            //				device_getResponseCodeString(r, strErr);
            //				printf("  Do msr_setWhiteList(), failed! ErrorCode:0x%02x ,Info: %s ----- \n",r,strErr);
            //			}
            //			else{
            //				printf("Set White List Succeeded\n");
            //			}
            //		}
            //		break;
            //		case 23:
            //		{
            //			printf(">>23. Get White List\n");
            //			BYTE whiteList[512];
            //			int whiteLislen =512;
            //
            //			r = msr_RetrieveWhiteList(whiteList,&whiteLislen);
            //			if ( r != RETURN_CODE_DO_SUCCESS ) {
            //				char strErr[200] = {0};
            //				memset(strErr,0,200);
            //				device_getResponseCodeString(r, strErr);
            //				printf("  Do msr_RetrieveWhiteList(), failed! ErrorCode:0x%02x ,Info: %s ----- \n",r,strErr);
            //			}
            //			else{
            //				printf("Get White List Succeeded\n");
            //				char str1[1024]={0};
            //				COMMON.convertBytesIntoHexStr(whiteList, whiteLislen, 1, str1);
            //				printf("\tWhite List: %s.\n", str1);
            //
            //			}
            //		}
            //		break;

            case 18: {
                {
                printf(">>21. Get MSR Function Status\n");
                fflush(stdout);
                int enabled;
                int isBufferMode;
                int withNotification;
                r = msr_getFunctionStatus(&enabled, &isBufferMode, &withNotification);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf("  Do icc_getFunctionStatus(), failed! ErrorCode:0x%02x ,Info: %s ----- \n", r, strErr);
                } else {
                    printf("Get MSR Function Status Succeeded\n");

                    if (enabled) {
                        printf("\tMSR Reader:[%s][%s][%s] ", (enabled == 1 ? "Enabled " : "Disabled "),
                          (isBufferMode == 1 ? "Buffer Mode " : "Auto Mode "),
                          (withNotification == 1 ? " with Notification.\n" : " without Notification.\n"));
                    } else {
                        printf("\tMSR Reader Disabled.\n");
                    }
                }
                fflush(stdout);
            }
            break;
            }
            case 0:{
                if (isMSRBusy) {
                    printf("MSR Busy\n");
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
} /* _Augusta_process_msr */

void
_Augusta_display_msr_menu() {
    idtech_display_menu_from_lib.pDisplay_Menu_current = _Augusta_display_msr_menu;
    printf("\t\t********** MSR Options [Augusta]************\n");
    printf("\t\t0.  Back To Main Menu\n");
    printf("\t\t1.  Start MSR\n");
    printf("\t\t2.  Cancel MSR\n");
    printf("\t\t3.  Set Expiration Mask ON\n");
    printf("\t\t4.  Set Expiration Mask OFF\n");
    printf("\t\t5.  Get Expiration Mask Status\n");
    printf("\t\t6.  Set PAN Clear Digits\n");
    printf("\t\t7.  Get PAN Clear Digits\n");
    printf("\t\t8.  Set Swipe Force Enc. ON\n");
    printf("\t\t9.  Set Swipe Force Enc. OFF\n");
    printf("\t\t10. Get Swipe Force Enc.\n");
    printf("\t\t11. Set Swipe Mask ON.\n");
    printf("\t\t12. Set Swipe Mask OFF.\n");
    printf("\t\t13. Get Swipe Mask.\n");
    printf("\t\t14. Set MSR Setting.\n");
    printf("\t\t15. Get MSR Setting.\n");
    //	printf("\t\t16. Set Swipe TDES.\n");
    //	printf("\t\t17. Set Swipe AES.\n");
    //	printf("\t\t18. Get Swipe Encryption.\n");
    printf("\t\t16. Enter Buffer Mode.\n");
    //	printf("\t\t20. Enable Auto Mode.\n");
    printf("\t\t17. Disable MSR.\n");
    //	printf("\t\t22. Set White List.\n");
    //	printf("\t\t23. Get White List.\n");
    printf("\t\t18. Get MSR Function Status.\n");
    printf("\t\t************************************************\n");
    fflush(stdout);
}
