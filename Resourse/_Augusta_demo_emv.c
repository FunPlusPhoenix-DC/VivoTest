#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "demo_common.h"

IDT_COMMON_PROCESS COMMON;
extern IDT_PROCESS idtech_process;
extern IDT_DEMO_LIB_DISPLAY_MENU idtech_display_menu_from_lib;

#if defined(WIN32) || defined(__MACH__)
EXPORT_SYMBOLS int emv_canceled  = 0;
EXPORT_SYMBOLS int emv_start     = 0;
EXPORT_SYMBOLS int isFromEMVMenu = 0;
#else
SHARED_SYMBOLS int emv_canceled;
SHARED_SYMBOLS int emv_start;
SHARED_SYMBOLS int isFromEMVMenu;
#endif

#define _BUF_LEN 1024

void
_Augusta_display_emv_menu();


int
EMV_Start() {
    printf("Start Transaction ");
    fflush(stdout);
    BYTE data[1024];
    int dataLen = 1024;

    emv_start = 1;
    //    const char *str1 = //"5F 2A 02 08 40";
    //    "df ef 20 01 00 9f 15 02  12 34 9f 16 0f 30 31 32 33 34 35 36 37 38 39 41 42 43 44 45 5f 2a 02 08 40";
    //    int r = COMMON.convertHStrIntoHex(str1, data, &dataLen);
    int r = emv_startTransaction(1500.00, 0.00, 2, 1, 120, NULL, 0, 0);
    if (r != RETURN_CODE_DO_SUCCESS) {
        printf("Failed!\n");
        printf("  Do emv_startTransaction(), failed!\n");
        // showErrInfo(r);
        device_controlLED_ICC(0, 0); // turn off LED
    } else {
        printf(" Start trans success -OK.\n");
    }
    fflush(stdout);
    emv_start = 0;
    return r;
}

int
EMV_Auth() {
    printf("Authenticate Transaction ");
    fflush(stdout);
    int r = emv_authenticateTransaction(NULL, 0);
    if (r != RETURN_CODE_DO_SUCCESS) {
        printf("  Do emv_authenticateTransaction(), failed!\n");
        // showErrInfo(r);
        device_controlLED_ICC(0, 0); // turn off LED
    } else {
        printf(" Authen   OK. \n");
    }
    fflush(stdout);
    return r;
}

int
EMV_cmpl() {
    printf("Complete Transaction ");
    fflush(stdout);
    BYTE data1[20];
    int dataLen1 = 20;
    //    unsigned char data2[20];
    //    int dataLen2 = 20;

    const char * str1 = "30 30";
    int r = COMMON.convertHStrIntoHex(str1, data1, &dataLen1);
    //    const char *str2 = "11 11 33 44 55 66 77 88 30 30";
    //    r = COMMON.convertHStrIntoHex(str2, data2, &dataLen2);
    //    r = emv_completeTransaction(0, data1,dataLen1,data2,dataLen2,NULL,0,NULL,0);
    r = emv_completeTransaction(0, data1, dataLen1, NULL, 0, NULL, 0, NULL, 0);
    if (r != RETURN_CODE_DO_SUCCESS) {
        printf("  Do emv_completeTransaction(), failed!\n");
        // showErrInfo(r);
        device_controlLED_ICC(0, 0); // turn off LED
    } else {
        printf(" apply host  OK.\n");
    }
    fflush(stdout);
    return r;
}

void
_Augusta_process_emv() {
    int choice;

    //	emv_registerCallBk(COMMON.EMV_callBack);
    //	emv_allowFallback(1);
    emv_setAutoAuthenticateTransaction(1);
    emv_setAutoCompleteTransaction(1);
    do {
        COMMON.set_emv_Finished(0);
        _Augusta_display_emv_menu();
        int r = 0;
        choice = COMMON.inputSelection();
        switch (choice) {
            case 1: {
                printf(">>1.  Start EMV Transaction\n");
                fflush(stdout);
                emv_canceled = 0;
                r = EMV_Start();
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- Do Start EMV Trans, failed! ErrorCode:0x%02x ,Info: %s ----- \n", r,
                        strErr);
                    fflush(stdout);
                    break;
                }
                isFromEMVMenu = 1;
                while (COMMON.get_emv_Finished() == 0) { // enable the while loop to show the menu after the function is done.
                    Sleep(500);
                }
            }
            break;
            case 2:
                printf(">>2.  Authenticate EMV Trans\n");
                fflush(stdout);
                r = EMV_Auth();
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- Authenticate EMV Trans failed! ErrorCode:0x%02x ,Info: %s ----- \n", r,
                        strErr);
                    fflush(stdout);
                    break;
                }
                while (COMMON.get_emv_Finished() == 0) { // enable the while loop to show the menu after the function is done.
                    Sleep(500);
                }
                break;
            case 3:
                printf(">>3.  Complete EMV Trans\n");
                fflush(stdout);
                r = EMV_cmpl();
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- Complete EMV Trans failed!! ErrorCode:0x%02x ,Info: %s ----- \n", r,
                        strErr);
                    fflush(stdout);
                    break;
                }
                while (COMMON.get_emv_Finished() == 0) { // enable the while loop to show the menu after the function is done.
                    Sleep(500);
                }
                break;
            case 4: {
                printf(">>4. Cancel EMV Trans\n");
                fflush(stdout);
                r = emv_cancelTransaction();
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- Cancel EMV Trans failed!! ErrorCode:0x%02x ,Info: %s ----- \n", r,
                        strErr);
                    fflush(stdout);
                    break;
                }
                emv_canceled = 1;
                Sleep(100);
                printf("Cancel EMV Transaction succeeded\n");

                //			device_controlLED_ICC(0, 0);
                //			printf("Will wait EMV (complete transaction) for 10 seconds...\n");
                break;
                
            }
            
            case 5: {
                printf(">>5. Kernel Version\n");
                fflush(stdout);
                char ver[200];
                r = emv_getEMVKernelVersion(ver);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- Get Kernel Version failed!! ErrorCode:0x%02x ,Info: %s ----- \n", r,
                        strErr);
                    fflush(stdout);
                    break;
                }
                printf(">>Kernel Version: %s.\n", ver);
                fflush(stdout);
            }
            break;
            case 6:
                printf(">>6. Kernel Checksum\n");
                fflush(stdout);
                {
                    BYTE data[200];
                    int dataLen = 200;
                    r = emv_getEMVKernelCheckValue(data, &dataLen);
                    if (r != RETURN_CODE_DO_SUCCESS) {
                        char strErr[200] = { 0 };
                        memset(strErr, 0, 200);
                        device_getResponseCodeString(r, strErr);
                        printf(
                            ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- Get Kernel Check Value failed!! ErrorCode:0x%02x ,Info: %s ----- \n", r,
                            strErr);
                        fflush(stdout);
                        break;
                    }
                    char str1[1024] = { 0 };
                    COMMON.convertBytesIntoHexStr(data, dataLen, 1, str1);
                    printf(">>KernelCheckValue: %s.\n", str1);
                    fflush(stdout);
                }
                break;
            case 7: {
                printf(">>7. Config CheckValue\n");
                fflush(stdout);
                BYTE data[200];
                int dataLen = 200;
                r = emv_getEMVConfigurationCheckValue(data, &dataLen);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- Get EMV Configuration Version failed!! ErrorCode:0x%02x ,Info: %s ----- \n", r,
                        strErr);
                    fflush(stdout);
                    break;
                }
                char str1[1024] = { 0 };
                COMMON.convertBytesIntoHexStr(data, dataLen, 1, str1);
                printf(">>Config CheckValue: %s.\n", str1);
                fflush(stdout);
            }
            break;
            case 8:
                printf(">>8.  Retrieve AID  a0 00 00 00 03 10 10\n");
                fflush(stdout);
                {
                    int AIDlen8;
                    int tlvlen8;
                    tlvlen8 = 200;
                    BYTE AID[7] = { 0xa0, 0x00, 0x00, 0x00, 0x03, 0x10, 0x10 };
                    AIDlen8 = 7;
                    BYTE tlv[200] = { 0 };
                    memset(tlv, 0, 200);
                    r = emv_retrieveApplicationData(AID, AIDlen8, tlv, &tlvlen8);
                    if (r != RETURN_CODE_DO_SUCCESS) {
                        char strErr[200] = { 0 };
                        memset(strErr, 0, 200);
                        device_getResponseCodeString(r, strErr);
                        printf(
                            ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- Retrieve AID  a0 00 00 00 03 10 10 failed!! ErrorCode:0x%02x ,Info: %s ----- \n", r,
                            strErr);
                        fflush(stdout);
                        break;
                    }
                    printf(">>AID data:\n");
                    COMMON.printBytes(tlv, tlvlen8);
                    COMMON.printTLV(tlv, tlvlen8);
                }
                break;
            case 9: {
                printf(">>9.  Remove AID  a0 00 00 00 03 10 10 \n");
                fflush(stdout);
                BYTE AID[7] = { 0xa0, 0x00, 0x00, 0x00, 0x03, 0x10, 0x10 };
                int AIDlen  = 7;
                r = emv_removeApplicationData(AID, AIDlen);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- remove AID  a0 00 00 00 03 10 10 failed!! ErrorCode:0x%02x ,Info: %s ----- \n", r,
                        strErr);
                    fflush(stdout);
                    break;
                }
                printf(">>remove AID  a0 00 00 00 03 10 10 success\n");
                fflush(stdout);
            }
            break;
            case 10: {
                printf(">>10. List AID\n");
                fflush(stdout);
                BYTE data[200];
                int dataLen = 200;
                r = emv_retrieveAIDList(data, &dataLen);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- retrieveAIDList failed!! ErrorCode:0x%02x ,Info: %s ----- \n", r,
                        strErr);
                    fflush(stdout);
                    break;
                }
                char str1[1024] = { 0 };
                COMMON.convertBytesIntoHexStr(data, dataLen, 1, str1);
                printf(">>retrieve AIDList: %s.\n", str1);
                fflush(stdout);
            }
            break;
            case 11: {
                printf(">>11. Save AID a0 00 00 00 03 10 10  \n");
                fflush(stdout);
                int nameLen;
                BYTE AID11[7] = { 0xa0, 0x00, 0x00, 0x00, 0x03, 0x10, 0x10 };
                nameLen = 7;
                // sizeof(AID11) / sizeof(AID11[0]);
                BYTE tlv11[512] = { 0 };
                int tlvLen11    = 512;
                const char * str2     =
                  "9F01065649534130305F5701005F2A0208409F090200965F3601029F1B0400003A98DF25039F3704DF28039F0802DFEE150101DF13050000000000DF14050000000000DF15050000000000DF180100DF170400002710DF190100";
                //			char *str2 = "9a01065649534130305f5701005F2A0208409F090200965F3601029F1B0400003A98DF25039F3704DF28039F0802DFEE150101DF13050000000000DF14050000000000DF15050000000000DF180100DF170400002710DF190100";
                COMMON.convertHStrIntoHex(str2, tlv11, &tlvLen11);
                r = emv_setApplicationData(AID11, nameLen, tlv11, tlvLen11);

                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- Save AID a0 00 00 00 03 10 10 failed!! ErrorCode:0x%02x ,Info: %s ----- \n", r,
                        strErr);
                    fflush(stdout);
                    break;
                }
                printf(">>Save AID a0 00 00 00 03 10 10 success.\n");
                fflush(stdout);
            }
            break;
            case 12: {
                printf(">>12. Remove All AID\n");
                fflush(stdout);
                r = emv_removeAllApplicationData();
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- remove all AID failed!! ErrorCode:0x%02x ,Info: %s ----- \n", r,
                        strErr);
                    fflush(stdout);
                    break;
                }
                printf(">>remove All Application data. OK\n");
                fflush(stdout);
            }
            break;
            case 13: {
                printf(">>13. Load Default AID\n");
                fflush(stdout);
                BYTE name[20];
                int namelen = 20;

                BYTE tlv13[200];
                int tlvlen13 = 200;

                const char * namestr = "A0000000031010";
                const char * tlvstr  =
                  "9F01065649534130305F5701005F2A0208409F090200965F3601029F1B0400003A98DF25039F3704DF28039F0802DFEE150101DF13050000000000DF14050000000000DF15050000000000DF180100DF170400002710DF190100";

                COMMON.convertHStrIntoHex(namestr, name, &namelen);
                COMMON.convertHStrIntoHex(tlvstr, tlv13, &tlvlen13);

                int rt = emv_setApplicationData(name, namelen, tlv13, tlvlen13);
                if (rt != RETURN_CODE_DO_SUCCESS) {
                    printf(">>set AID.... A0000001524010 failed ......\n", rt);
                } else {
                    printf(">>set AID.... OK ... loading......\n");
                }
                fflush(stdout);

                namestr = "A0000000032010";
                tlvstr  =
                  "9F01065649534130305F5701005F2A0208409F090200965F3601029F1B0400003A98DF25039F3704DF28039F0802DFEE150101DF13050000000000DF14050000000000DF15050000000000DF180100DF170400002710DF190100";
                namelen  = 20;
                tlvlen13 = 200;
                COMMON.convertHStrIntoHex(namestr, name, &namelen);
                COMMON.convertHStrIntoHex(tlvstr, tlv13, &tlvlen13);

                if (emv_setApplicationData(name, namelen, tlv13, tlvlen13) != RETURN_CODE_DO_SUCCESS) {
                    printf(
                        ">>set AID.... A0000000032010 failed ......\n");
                } else {
                    printf(">>set AID.... OK ... loading......\n");
                }
                fflush(stdout);

                namestr = "A0000000041010";
                tlvstr  =
                  "5F5701005F2A0208409F090200025F3601029F1B0400003A98DF25039F3704DF28039F0802DFEE150101DF13050000000000DF14050000000000DF15050000000000DF180100DF170400002710DF190100";

                namelen  = 20;
                tlvlen13 = 200;
                COMMON.convertHStrIntoHex(namestr, name, &namelen);
                COMMON.convertHStrIntoHex(tlvstr, tlv13, &tlvlen13);

                if (emv_setApplicationData(name, namelen, tlv13, tlvlen13) != RETURN_CODE_DO_SUCCESS) {
                    printf(
                        ">>set AID.... A0000000041010 failed ......\n");
                } else {
                    printf(">>set AID.... OK ... loading......\n");
                }
                fflush(stdout);

                namestr = "A00000002501";
                tlvstr  =
                  "5F5701005F2A0208409F090200015F3601029F1B0400003A98DF25039F3704DF28039F0802DFEE150101DF13050000000000DF14050000000000DF15050000000000DF180100DF170400002710DF190100";

                namelen  = 20;
                tlvlen13 = 200;
                COMMON.convertHStrIntoHex(namestr, name, &namelen);
                COMMON.convertHStrIntoHex(tlvstr, tlv13, &tlvlen13);

                if (emv_setApplicationData(name, namelen, tlv13, tlvlen13) != RETURN_CODE_DO_SUCCESS) {
                    printf(
                        ">>set AID.... A00000002501 failed ......\n");
                } else {
                    printf(">>set AID.... OK ... loading......\n");
                }
                fflush(stdout);
                namestr = "A0000001523010";
                tlvstr  =
                  "5F5701005F2A0208409F090200015F3601029F1B0400003A98DF25039F3704DF28039F0802DFEE150101DF13050000000000DF14050000000000DF15050000000000DF180100DF170400002710DF190100";

                namelen  = 20;
                tlvlen13 = 200;
                COMMON.convertHStrIntoHex(namestr, name, &namelen);
                COMMON.convertHStrIntoHex(tlvstr, tlv13, &tlvlen13);

                if (emv_setApplicationData(name, namelen, tlv13, tlvlen13) != RETURN_CODE_DO_SUCCESS) {
                    printf(
                        ">>set AID.... A0000001523010 failed ......\n");
                } else {
                    printf(">>set AID.... OK ... loading......\n");
                }
                fflush(stdout);
                namestr = (char*)"A0000001524010";
                tlvstr  =
                  (char*)"5F5701005F2A0208409F090200015F3601029F1B0400003A98DF25039F3704DF28039F0802DFEE150101DF13050000000000DF14050000000000DF15050000000000DF180100DF170400002710DF190100";

                namelen  = 20;
                tlvlen13 = 200;
                COMMON.convertHStrIntoHex(namestr, name, &namelen);
                COMMON.convertHStrIntoHex(tlvstr, tlv13, &tlvlen13);
                rt = emv_setApplicationData(name, namelen, tlv13, tlvlen13);
                if (rt != RETURN_CODE_DO_SUCCESS) {
                    printf(">>set AID.... A0000001524010 failed ......\n", rt);
                } else {
                    printf(">>set AID.... OK ... loading......\n");
                }
                printf(">>set AID.... OK ... load  end ......\n");
                fflush(stdout);
            }
            break;
            case 14: {
                printf(">>14. Get Terminal Data\n");
                fflush(stdout);
                BYTE data[_DATA_BUF_LEN];
                int dataLen = _DATA_BUF_LEN;
                r = emv_retrieveTerminalData(data, &dataLen);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- Retrieve Terminal Data failed!! ErrorCode:0x%02x ,Info: %s ----- \n", r,
                        strErr);
                    fflush(stdout);
                    break;
                }
                printf(">>Retrieve Terminal Data:\n");
                COMMON.printBytes(data, dataLen);
                COMMON.printTLV(data, dataLen);
            }
            break;
            case 15: {
                printf(">>15. Remove Terminal Data\n");
                fflush(stdout);
                r = emv_removeTerminalData();
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- remove Terminal Data failed!! ErrorCode:0x%02x ,Info: %s ----- \n", r,
                        strErr);
                    fflush(stdout);
                    break;
                } else {
                    printf(">>remove Terminal Data success\n");
                }
                fflush(stdout);
            }
            break;
            case 16: {
                printf(">>16. Save Terminal Data\n");
                fflush(stdout);
                BYTE tlv16[512];
                int tlvlen16 = 512;
                //			char * terminalstr ="5F3601029F1A0208409F3501259F33036008C89F40056000F050019F1E085465726D696E616C9F150212349F160F3030303030303030303030303030309F1C0838373635343332319F4E2231303732312057616C6B65722053742E20437970726573732C204341202C5553412EDF260101DF1008656E667265737A68DF110101DF270100DFEE150101DFEE160100DFEE170107DFEE180180DFEE1E08D09C20F0C20E1400DFEE1F0180DFEE1B083030303135313030DFEE20013CDFEE21010ADFEE2203323C3C";
                const char * terminalstr =
                  "5F3601029F1A0208409F3501219F33036028C89F4005F000F0A0019F1E085465726D696E616C9F150212349F160F3030303030303030303030303030309F1C0838373635343332319F4E2231303732312057616C6B65722053742E20437970726573732C204341202C5553412EDF260101DF1008656E667265737A68DF110100DF270100DFEE150101DFEE160100DFEE170107DFEE180180DFEE1E08D0DC20D0C41E1400DFEE1F0180DFEE1B083030303135313030DFEE20013CDFEE21010ADFEE2203323C3C";
                COMMON.convertHStrIntoHex(terminalstr, tlv16, &tlvlen16);
                r = emv_setTerminalData(tlv16, tlvlen16);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- save Terminal Data failed!! ErrorCode:0x%02x ,Info: %s ----- \n", r,
                        strErr);
                    fflush(stdout);
                    break;
                } else {
                    printf(">>save Terminal Data success\n");
                }
                fflush(stdout);
            }
            break;
            case 17: {
                printf(">>17. Retrieve CAPK A0 00 00 99 99 E1 \n");
                fflush(stdout);
                BYTE data[500];
                int dataLen = 500;
                const char * str2 = "A0 00 00 99 99 E1";
                BYTE pdt1[500];
                int pdt1Len = 500;
                COMMON.convertHStrIntoHex(str2, pdt1, &pdt1Len);
                r = emv_retrieveCAPK(pdt1, pdt1Len, data, &dataLen);
                printf(">>>CAPK>>>\n");
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- retrieve CAPK  failed!! ErrorCode:0x%02x ,Info: %s ----- \n", r,
                        strErr);
                    fflush(stdout);
                    break;
                }
                char str1[1024] = { 0 };
                COMMON.convertBytesIntoHexStr(data, dataLen, 1, str1);
                printf(">>Retrieve CAPK: %s.\n", str1);
                fflush(stdout);
            }
            break;
            case 18: {
                printf(">>18. Remove CAPK A0 00 00 99 99 E1\n");
                fflush(stdout);
                const char * str2 = "A0 00 00 99 99 E1";
                BYTE pdt1[200];
                int pdt1Len = 200;
                COMMON.convertHStrIntoHex(str2, pdt1, &pdt1Len);
                r = emv_removeCAPK(pdt1, pdt1Len);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- Remove CAPK  failed!! ErrorCode:0x%02x ,Info: %s ----- \n", r,
                        strErr);
                    fflush(stdout);
                    break;
                }
                printf(">>Remove CAPK: OK.\n");
                fflush(stdout);
            }
            break;
            case 19: {
                printf(">>19. List CAPK\n");
                BYTE data[200];
                int dataLen = 200;
                r = emv_retrieveCAPKList(data, &dataLen);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- retrieve CAPK List failed!! ErrorCode:0x%02x ,Info: %s ----- \n", r,
                        strErr);
                    fflush(stdout);
                    break;
                }
                int count = dataLen / 6;
                printf(">>Retrieve CAPK list:\n");
                int i;
                for (i = 0; i < count; i++) {
                    printf("%02X %02X %02X %02X %02X %02X\n", data[i * 6], data[i * 6 + 1], data[i * 6 + 2],
                      data[i * 6 + 3], data[i * 6 + 4], data[i * 6 + 5]);
                }
                fflush(stdout);
            }
            break;
            case 20: {
                printf(">>20. Save CAPK a000009999e1 \n");
                fflush(stdout);
                const char * str2 =
                  "a000009999e10101f8707b9bedf031e58a9f843631b90c90d80ed69500000003700099c5b70aa61b4f4c51b6f90b0e3bfb7a3ee0e7db41bc466888b3ec8e9977c762407ef1d79e0afb2823100a020c3e8020593db50e90dbeac18b78d13f96bb2f57eeddc30f256592417cdf739ca6804a10a29d2806e774bfa751f22cf3b65b38f37f91b4daf8aec9b803f7610e06ac9e6b";
                BYTE pdt1[400];
                int pdt1Len = 400;
                COMMON.convertHStrIntoHex(str2, pdt1, &pdt1Len);
                r = emv_setCAPK(pdt1, pdt1Len);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- save CAPK  failed!! ErrorCode:0x%02x ,Info: %s ----- \n", r,
                        strErr);
                    fflush(stdout);
                    break;
                }
                printf(">>set CAPK: OK.\n");
                fflush(stdout);
            }
            break;
            case 21: {
                printf(">>21. Remove All CAPK\n");
                fflush(stdout);
                r = emv_removeAllCAPK();
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- remove all CAPK  failed!! ErrorCode:0x%02x ,Info: %s ----- \n", r,
                        strErr);
                    fflush(stdout);
                    break;
                }
                printf(">>Remove all CAPK: OK.\n");
                fflush(stdout);
            }
            break;
            case 22:
                printf(">>22. Load Default CAPK\n");
                fflush(stdout);
                {
                    printf("Please Wait. Loading Default CAPK...\r\n");
                    fflush(stdout);
                    const char * str22 =
                      "a000009999e10101f8707b9bedf031e58a9f843631b90c90d80ed69500000003700099c5b70aa61b4f4c51b6f90b0e3bfb7a3ee0e7db41bc466888b3ec8e9977c762407ef1d79e0afb2823100a020c3e8020593db50e90dbeac18b78d13f96bb2f57eeddc30f256592417cdf739ca6804a10a29d2806e774bfa751f22cf3b65b38f37f91b4daf8aec9b803f7610e06ac9e6b";
                    BYTE pdt22[800];
                    int pdt22Len = 800;
                    COMMON.convertHStrIntoHex(str22, pdt22, &pdt22Len);
                    r = emv_setCAPK(pdt22, pdt22Len);
                    if (r != RETURN_CODE_DO_SUCCESS) {
                        printf(" >>>>>>load ..... save CAPK  failed! .......... ----- \n");
                    } else {
                        printf(">>set CAPK: OK. load ........\n");
                    }
                    fflush(stdout);
                    pdt22Len = 800;
                    str22    =
                      "a000009999e20101c1056adce9e6f76ea77c89cb832f5a4817907a1a000000037000bd232e348b118eb3f6446ef4da6c3bac9b2ae510c5ad107d38343255d21c4bdf4952a42e92c633b1ce4bfec39afb6dfe147ecbb91d681dac15fb0e198e9a7e4636bdca107bcda3384fcb28b06afef90f099e7084511f3cc010d4343503e1e5a67264b4367daa9a3949499272e9b5022f";
                    COMMON.convertHStrIntoHex(str22, pdt22, &pdt22Len);
                    r = emv_setCAPK(pdt22, pdt22Len);
                    if (r != RETURN_CODE_DO_SUCCESS) {
                        printf(" >>>>>>load ..... save CAPK  failed! .......... ----- \n");
                    } else {
                        printf(">>set CAPK: OK. load ........\n");
                    }
                    fflush(stdout);
                    pdt22Len = 800;
                    str22    =
                      "a000009999e301011b795cbb0830e2c5231704fa57424d1c4e50f3e4000100017000bc01e12223e1a41e88bffa801093c5f8cec5cd05dbbdbb787ce87249e8808327c2d218991f97a1131e8a25b0122ed11e709c533e8886a1259addfdcbb396604d24e505a2d0b5dd0384fb0002a7a1eb39bc8a11339c7a9433a948337761be73bc497b8e58736da4636538ad282d3cd3db";
                    COMMON.convertHStrIntoHex(str22, pdt22, &pdt22Len);
                    r = emv_setCAPK(pdt22, pdt22Len);
                    if (r != RETURN_CODE_DO_SUCCESS) {
                        printf(" >>>>>>load ..... save CAPK  failed! .......... ----- \n");
                    } else {
                        printf(">>set CAPK: OK. load ........\n");
                    }
                    fflush(stdout);
                    pdt22Len = 800;
                    str22    =
                      "a000009999e40101ac8da3e12324d719c1d5c9e6e8580157196efeb9000000038000cbf2e40f0836c9a5e390a37be3b809bdf5d740cb1da38cfc05d5f8d6b7745b5e9a3fa6961e55ff20412108525e66b970f902f7ff4305dd832cd0763e3aa8b8173f84777100b1047bd1d744509312a0932ed25fed52a959430768ccd902fd8c8ad9123e6addb3f34b92e7924d729cb6473533ae2b2b55bf0e44964fdea8440117";
                    COMMON.convertHStrIntoHex(str22, pdt22, &pdt22Len);
                    r = emv_setCAPK(pdt22, pdt22Len);
                    if (r != RETURN_CODE_DO_SUCCESS) {
                        printf(" >>>>>>load ..... save CAPK  failed! .......... ----- \n");
                    } else {
                        printf(">>set CAPK: OK. load ........\n");
                    }
                    fflush(stdout);
                    pdt22Len = 800;
                    str22    =
                      "a000009999e50101ada2349afd118d55af782d37b64651af1ca61ee5000000038000d4fdae94dedbecc6d20d38b01e91826dc6954338379917b2bb8a6b36b5d3b0c5eda60b337448baffebcc3abdba869e8dadec6c870110c42f5aab90a18f4f867f72e3386ffc7e67e7ff94eba079e531b3cf329517e81c5dd9b3dc65db5f9043190be0be897e5fe48adf5d3bfa0585e076e554f26ec69814797f15669f4a255c13";
                    COMMON.convertHStrIntoHex(str22, pdt22, &pdt22Len);
                    r = emv_setCAPK(pdt22, pdt22Len);
                    if (r != RETURN_CODE_DO_SUCCESS) {
                        printf(" >>>>>>load ..... save CAPK  failed! .......... ----- \n");
                    } else {
                        printf(">>set CAPK: OK. load ........\n");
                    }
                    fflush(stdout);
                    pdt22Len = 800;
                    str22    =
                      "a000009999e601018aa4f4648f0dc62ab6aed92554ad1a831bafc9e4000100018000ebf9faecc3e5c315709694664775d3fbda5a504d89344dd920c55696e891d9ab622598a9d6ab8fbf35e4599cab7eb22f956992f8ab2e6535decb6b576fa0675f97c23dd4c374a66e6af419c9d204d0b9f93c08d789d63805660fbb629df1b488cfa1d7a13e9b729437eeafe718efa859348ba0d76812a99f31cd364f2a4fd42f";
                    COMMON.convertHStrIntoHex(str22, pdt22, &pdt22Len);
                    r = emv_setCAPK(pdt22, pdt22Len);
                    if (r != RETURN_CODE_DO_SUCCESS) {
                        printf(" >>>>>>load ..... save CAPK  failed! .......... ----- \n");
                    } else {
                        printf(">>set CAPK: OK. load ........\n");
                    }
                    fflush(stdout);
                    pdt22Len = 800;
                    str22    =
                      "a000000004fa01017f5acbb96b589f74cb959ed1c35bdb965c3f410600010001f800a4203e0c7beb27097b63c103c19fdcda671aea7f813065756f3b9b81810cbd4bc4dec548fbf1f3cdae51f847235cbf2c8badd8aca7c93bea3d44e80ed6a7b70e29622619db420accce07e1dd4e6c354f359fbdc9c5b70813926f77d827e52b19daf09bfae5274438bb8f61d17753c9ec0a8efa3b7e46f02692160d2653cdbcc71b7d48bd37968316eb444f6504b9421b7dd3035a2c117d8b1f76a8975440da9563618102397b881cef8ada7689edface32482a2dffed656e7f951db841da78368c6293bfc1053a86a845bfa6578e4b69f100b42b558fde1aecec6d250741bc783aa8a68a4261e7bb9246b10587a498d68dd955ce8b2b2433";
                    COMMON.convertHStrIntoHex(str22, pdt22, &pdt22Len);
                    r = emv_setCAPK(pdt22, pdt22Len);
                    if (r != RETURN_CODE_DO_SUCCESS) {
                        printf(" >>>>>>load ..... save CAPK  failed! .......... ----- \n");
                    } else {
                        printf(">>set CAPK: OK. load ........\n");
                    }
                    fflush(stdout);
                    pdt22Len = 800;
                    str22    =
                      "a000000004fb0101fc787db138f994a0c554cc6734eb3e48a55066cc0001000190009b170603a489c7546c45da57b8ffd1db2061240f0e8c6d1f9abdc6b265aa8911915c1a4eabd8d0ed4755d1b902ba06fe5a645b786cd241295517d44ef1a7c25d75afe0eb28066e4d69fee7abafdd5eeb230f14e402c9840825fa77ead12b5f1c5494701de1897f65fe6bf106d47545ebf70ce7c158068c61f0773534db742ab83c28038c1494f15905d0ad17cf1bd38d";
                    COMMON.convertHStrIntoHex(str22, pdt22, &pdt22Len);
                    r = emv_setCAPK(pdt22, pdt22Len);
                    if (r != RETURN_CODE_DO_SUCCESS) {
                        printf(" >>>>>>load ..... save CAPK  failed! .......... ----- \n");
                    } else {
                        printf(">>set CAPK: OK. load ........\n");
                    }
                    fflush(stdout);
                    pdt22Len = 800;
                    str22    =
                      "a000000004fc0101db50b5b0d966300760b1e42125277ba833b6523400010001f800b3296c91f4795bd97112606903407b6eff3ab39246e91095e51d17867da4ade59a48be2fe9b52710283d3d32260e2c7d247214c57d46aa6465e47e0a4b3ffaad8a7f6a190755bccfe3f3fb3989a9f6b1c9e1845bcccad6f20b1dac6033600234e81dac4153212b0f760c23099192aa6c4c9083beffd9a79d2a27b08fecc8e5d437d6c68550a839b1294151daba9d9cb2f160f60f749289f500c8c7f334bd20ebac4ab109cf3c182f1b781c7c097a7903530746c449b99e39e4db6493dd2a02e37c62ae8bc9a7470ecccf8dc06a18c33cd24b30d56f25d2755ce82aa4de4d2eaec07750a03db75ebd0d8ebc9f2a1d85a0d252eff40329be05";
                    COMMON.convertHStrIntoHex(str22, pdt22, &pdt22Len);
                    r = emv_setCAPK(pdt22, pdt22Len);
                    if (r != RETURN_CODE_DO_SUCCESS) {
                        printf(" >>>>>>load ..... save CAPK  failed! .......... ----- \n");
                    } else {
                        printf(">>set CAPK: OK. load ........\n");
                    }
                    fflush(stdout);
                    pdt22Len = 800;
                    str22    =
                      "a000000004fd0101fc505e4a83ff29a3b1bd28dabf52599b2ae9cb14000100019000c9485dbeb5e40415d1b397524f47685f306cfdc499d4e2e7d0cbaf222cfa8184bd111daeedc9cc6ec8540c3f7271ea9990119cc5c43180501d9f45252d6835053fae35696ae8cd67a325647449cf5e594da8f627209f7f03ae8d6dfc0db3e79e28e415df29a5b57d6814856cc30a96da5b8890363e507fcb2e283da1ebb5f18e8e24102b7d0192bb8e35a4f7cd05a435";
                    COMMON.convertHStrIntoHex(str22, pdt22, &pdt22Len);
                    r = emv_setCAPK(pdt22, pdt22Len);
                    if (r != RETURN_CODE_DO_SUCCESS) {
                        printf(" >>>>>>load ..... save CAPK  failed! .......... ----- \n");
                    } else {
                        printf(">>set CAPK: OK. load ........\n");
                    }
                    fflush(stdout);
                    pdt22Len = 800;
                    str22    =
                      "a000000004fe01018535f14cbd6b4ae5028618fab5ac1106549fd03c000100019000e76317965175a08bee510f58830e87b262c70d529803245fa8b88e0c753562de7aeb5a9e3e6c1a98e94d8db7c31407dac5d071e06b80b09e146f22db85f1d72d1ea18d22600032c6dd40e3714d5ada7de9d7d01e88391f893156d6f4bf13e9063559da0786de9bde6b1c9b0bb968edde07145abf877b931682ccb1fb800728724d04af241e2827e0fa1f62591914ff25";
                    COMMON.convertHStrIntoHex(str22, pdt22, &pdt22Len);
                    r = emv_setCAPK(pdt22, pdt22Len);
                    if (r != RETURN_CODE_DO_SUCCESS) {
                        printf(" >>>>>>load ..... save CAPK  failed! .......... ----- \n");
                    } else {
                        printf(">>set CAPK: OK. load ........\n");
                    }
                    fflush(stdout);
                    pdt22Len = 800;
                    str22    =
                      "a000000004ff0101439eb23d8a71b99f879c1a1f1765252d840b9a74000100019000f69dbb5e15983eae3ccf31cf4e47098c2fc16f97a0c710f84777efa99622d86502b138728ab12e3481a84d20e014ad2d634d2836f27f294924b895a87f91f81b8169d4dfdad8d7cbd741804cd61b467c7a9acfeceb71188caa73a907547699d45c9c7d2098ac2966266417f665a46bdd012c097dbd33d1d11aff6ec8a9c0ad814a65b48262ca011636079a328c1aaeb7";
                    COMMON.convertHStrIntoHex(str22, pdt22, &pdt22Len);
                    r = emv_setCAPK(pdt22, pdt22Len);
                    if (r != RETURN_CODE_DO_SUCCESS) {
                        printf(" >>>>>>load ..... save CAPK  failed! .......... ----- \n");
                    } else {
                        printf(">>set CAPK: OK. load ........\n");
                    }
                    fflush(stdout);
                    pdt22Len = 800;
                    str22    =
                      "a000000065020101b973e9f377b419c36ac9696ed95ffb25c8020687000100018000bb7f51983fd8707fd6227c23def5d5377a5a737cef3c5252e578efe136df87b50473f9341f1640c8d258034e14c16993fce6c6b8c3ceeb65fc8fbcd8eb77b3b05ac7c4d09e0fa1ba2efe87d3184db6718ae41a7cad89b8dce0fe80ceb523d5d647f9db58a31d2e71ac677e67fa6e75820736c9893761ee4acd11f31dbdc349ef";
                    COMMON.convertHStrIntoHex(str22, pdt22, &pdt22Len);
                    r = emv_setCAPK(pdt22, pdt22Len);
                    if (r != RETURN_CODE_DO_SUCCESS) {
                        printf(" >>>>>>load ..... save CAPK  failed! .......... ----- \n");
                    } else {
                        printf(">>set CAPK: OK. load ........\n");
                    }
                    fflush(stdout);
                    pdt22Len = 800;
                    str22    =
                      "a0000000650301017dc435dbde093d1f0ad0bae0fea4dc12056413dc00000003f800c9e6c1f3c6949a8a42a91f8d0224132b2865e6d953a5b5a54cffb0412439d54aeba79e9b399a6c104684df3fb727c7f55984db7a450e6aa917e110a7f2343a0024d2785d9ebe09f601d592362fdb237700b567ba14bbe2a6d3d23cf1270b3dd822b5496549bf884948f55a0d308348c4b723bafb6a7f3975ac397cad3c5d0fc2d178716f5e8e79e75beb1c84fa202f80e68069a984e008706b30c212305456201540787925e86a8b28b129a11af204b387cb6ee43db53d15a46e13901bebd5cecf4854251d9e9875b16e82ad1c5938a972842c8f1a42ebb5ae5336b04ff3da8b8dfbe606fca8b9084ee05bf67950ba89897cd089f924dbcd";
                    COMMON.convertHStrIntoHex(str22, pdt22, &pdt22Len);
                    r = emv_setCAPK(pdt22, pdt22Len);
                    if (r != RETURN_CODE_DO_SUCCESS) {
                        printf(" >>>>>>load ..... save CAPK  failed! .......... ----- \n");
                    } else {
                        printf(">>set CAPK: OK. load ........\n");
                    }
                    fflush(stdout);
                    pdt22Len = 800;
                    str22    =
                      "a000000003500101b769775668cacb5d22a647d1d993141edab7237b000100018000d11197590057b84196c2f4d11a8f3c05408f422a35d702f90106ea5b019bb28ae607aa9cdebcd0d81a38d48c7ebb0062d287369ec0c42124246ac30d80cd602ab7238d51084ded4698162c59d25eac1e66255b4db2352526ef0982c3b8ad3d1cce85b01db5788e75e09f44be7361366def9d1e1317b05e5d0ff5290f88a0db47";
                    COMMON.convertHStrIntoHex(str22, pdt22, &pdt22Len);
                    r = emv_setCAPK(pdt22, pdt22Len);
                    if (r != RETURN_CODE_DO_SUCCESS) {
                        printf(" >>>>>>load ..... save CAPK  failed! .......... ----- \n");
                    } else {
                        printf(">>set CAPK: OK. load ........\n");
                    }
                    fflush(stdout);
                    pdt22Len = 800;
                    str22    =
                      "a000000003510101b9d248075a3f23b522fe45573e04374dc4995d71000000039000db5fa29d1fda8c1634b04dccff148abee63c772035c79851d3512107586e02a917f7c7e885e7c4a7d529710a145334ce67dc412cb1597b77aa2543b98d19cf2cb80c522bdbea0f1b113fa2c86216c8c610a2d58f29cf3355ceb1bd3ef410d1edd1f7ae0f16897979de28c6ef293e0a19282bd1d793f1331523fc71a228800468c01a3653d14c6b4851a5c029478e757f";
                    COMMON.convertHStrIntoHex(str22, pdt22, &pdt22Len);
                    r = emv_setCAPK(pdt22, pdt22Len);
                    if (r != RETURN_CODE_DO_SUCCESS) {
                        printf(" >>>>>>load ..... save CAPK  failed! .......... ----- \n");
                    } else {
                        printf(">>set CAPK: OK. load ........\n");
                    }
                    fflush(stdout);
                    pdt22Len = 800;
                    str22    =
                      "a000000003530101ac213a2e0d2c0ca35ad0201323536d58097e4e5700000003f800bcd83721be52cccc4b6457321f22a7dc769f54eb8025913be804d9eabbfa19b3d7c5d3ca658d768caf57067eec83c7e6e9f81d0586703ed9dddadd20675d63424980b10eb364e81eb37db40ed100344c928886ff4ccc37203ee6106d5b59d1ac102e2cd2d7ac17f4d96c398e5fd993ecb4ffdf79b17547ff9fa2aa8eefd6cbda124cbb17a0f8528146387135e226b005a474b9062ff264d2ff8efa36814aa2950065b1b04c0a1ae9b2f69d4a4aa979d6ce95fee9485ed0a03aee9bd953e81cfd1ef6e814dfd3c2ce37aefa38c1f9877371e91d6a5eb59fdedf75d3325fa3ca66cdfba0e57146cc789818ff06be5fcc50abd362ae4b80996d";
                    COMMON.convertHStrIntoHex(str22, pdt22, &pdt22Len);
                    r = emv_setCAPK(pdt22, pdt22Len);
                    if (r != RETURN_CODE_DO_SUCCESS) {
                        printf(" >>>>>>load ..... save CAPK  failed! .......... ----- \n");
                    } else {
                        printf(">>set CAPK: OK. load ........\n");
                    }
                    fflush(stdout);
                    pdt22Len = 800;
                    str22    =
                      "a0000000039601017616e9ac8be014af88ca11a8fb17967b7394030e000000038000b74586d19a207be6627c5b0aafbc44a2ecf5a2942d3a26ce19c4ffaeee920521868922e893e7838225a3947a2614796fb2c0628ce8c11e3825a56d3b1bbaef783a5c6a81f36f8625395126fa983c5216d3166d48acde8a431212ff763a7f79d9edb7fed76b485de45beb829a3d4730848a366d3324c3027032ff8d16a1e44d8d";
                    COMMON.convertHStrIntoHex(str22, pdt22, &pdt22Len);
                    r = emv_setCAPK(pdt22, pdt22Len);
                    if (r != RETURN_CODE_DO_SUCCESS) {
                        printf(" >>>>>>load ..... save CAPK  failed! .......... ----- \n");
                    } else {
                        printf(">>set CAPK: OK. load ........\n");
                    }
                    fflush(stdout);
                    pdt22Len = 800;
                    str22    =
                      "a000000003570101251a5f5de61cf28b5c6e2b5807c0644a01d46ff5000100016000942b7f2ba5ea307312b63df77c5243618acc2002bd7ecb74d821fe7bdc78bf28f49f74190ad9b23b9713b140ffec1fb429d93f56bdc7ade4ac075d75532c1e590b21874c7952f29b8c0f0c1ce3aeedc8da25343123e71dcf86c6998e15f756e3";
                    COMMON.convertHStrIntoHex(str22, pdt22, &pdt22Len);
                    r = emv_setCAPK(pdt22, pdt22Len);
                    if (r != RETURN_CODE_DO_SUCCESS) {
                        printf(" >>>>>>load ..... save CAPK  failed! .......... ----- \n");
                    } else {
                        printf(">>set CAPK: OK. load ........\n");
                    }
                    fflush(stdout);
                    pdt22Len = 800;
                    str22    =
                      "a000000003580101753ed0aa23e4cd5abd69eae7904b684a34a57c2200010001c80099552c4a1ecd68a0260157fc4151b5992837445d3fc57365ca5692c87be358cdcdf2c92fb6837522842a48eb11cdffe2fd91770c7221e4af6207c2de4004c7dee1b6276dc62d52a87d2cd01fbf2dc4065db52824d2a2167a06d19e6a0f781071cdb2dd314cb94441d8dc0e936317b77bf06f5177f6c5aba3a3bc6aa30209c97260b7a1ad3a192c9b8cd1d153570afcc87c3cd681d13e997fe33b3963a0a1c79772acf991033e1b8397ad0341500e48a24770bc4cbe19d2ccf419504fdbf0389bc2f2fdcd4d44e61f";
                    COMMON.convertHStrIntoHex(str22, pdt22, &pdt22Len);
                    r = emv_setCAPK(pdt22, pdt22Len);
                    if (r != RETURN_CODE_DO_SUCCESS) {
                        printf(" >>>>>>load ..... save CAPK  failed! .......... ----- \n");
                    } else {
                        printf(">>set CAPK: OK. load ........\n");
                    }
                    fflush(stdout);
                    pdt22Len = 800;
                    str22    =
                      "a00000000354010106960618791a86d387301edd4a3baf2d34fef1b400010001f800c6ddc0b7645f7f16286ab7e4116655f56dd0c944766040dc68664dd973bd3bfd4c525bcbb95272b6b3ad9ba8860303ad08d9e8cc344a4070f4cfb9eeaf29c8a3460850c264cda39bbe3a7e7d08a69c31b5c8dd9f94ddbc9265758c0e7399adcf4362caee458d414c52b498274881b196dacca7273f687f2a65faeb809d4b2ac1d3d1efb4f6490322318bd296d153b307a3283ab4e5be6ebd910359a8565eb9c4360d24baaca3dbfe393f3d6c830d603c6fc1e83409dfcd80d3a33ba243813bbb4ceaf9cbab6b74b00116f72ab278a88a011d70071e06cab140646438d986d48281624b85b3b2ebb9a6ab3bf2178fcc3011e7caf24897ae7d";
                    COMMON.convertHStrIntoHex(str22, pdt22, &pdt22Len);
                    r = emv_setCAPK(pdt22, pdt22Len);
                    if (r != RETURN_CODE_DO_SUCCESS) {
                        printf(" >>>>>>load ..... save CAPK  failed! .......... ----- \n");
                    } else {
                        printf(">>set CAPK: OK. load ........\n");
                    }
                    fflush(stdout);
                    pdt22Len = 800;
                    str22    =
                      "a000000025600101894b8df19bdc691103c3b93979f5ee28c05888a7000100019000a8ee74edef3c0dca5102ff9b5707975ff67b60d64b5e7322d48de9d3bb6153f63512a091b606dd8fd5f6a14588324ef8827844c7ffc0bab2334ae5207770078b69cdc3f2c666cf69e28e16e1816714c4df313bef539cc01da9dd2d6f47de4f247c500b561c099166ad4fc16df12dfb684ac48d35cdd2c47a13a86a5a162306f64e33b092ab74eda71a4091d96e3daa47";
                    COMMON.convertHStrIntoHex(str22, pdt22, &pdt22Len);
                    r = emv_setCAPK(pdt22, pdt22Len);
                    if (r != RETURN_CODE_DO_SUCCESS) {
                        printf(" >>>>>>load ..... save CAPK  failed! .......... ----- \n");
                    } else {
                        printf(">>set CAPK: OK. load ........\n");
                    }
                    fflush(stdout);
                    pdt22Len = 800;
                    str22    =
                      "a000000025610101cccf27c49c15b2a9410ec6089223a3a01ea8433e00010001f80086c7254665e17ce6934df7d082569f208d1cc1ad8e9fb2fe23e3d7467be50b4f874f906adf2280ec9d204f6d10c037a23ce5fd8283c9ed47d1c669abdd7c1cb356c70bcdc44e5c8ae231555f7b786ac9c3155bcd51f28efbc1b33cc87277049219b2c890952736c4713487111678911d9f42e08074cf524e65d721d727f054e6b5e85ec92b3eb59ffee926dd6c314df555c94ad487a99b67cb7c7ba5e46a5b813ddb918b8e3e0423f4302a58686d1263c0baca9e82068c493289e3e6936eca5f9f77e06b0d6fbda718818b835020098c671c5dd7e9b8e8e841d2df32ee94a7f4748484ca44108ab241a5263ba1ff00d51360dddc749d30a1";
                    COMMON.convertHStrIntoHex(str22, pdt22, &pdt22Len);
                    r = emv_setCAPK(pdt22, pdt22Len);
                    if (r != RETURN_CODE_DO_SUCCESS) {
                        printf(" >>>>>>load ..... save CAPK  failed! .......... ----- \n");
                    } else {
                        printf(">>set CAPK: OK. load ........\n");
                    }
                    fflush(stdout);
                    pdt22Len = 800;
                    str22    =
                      "a000000152d00101de1bb8a37cddbceaab043aaef81634120349726d000100019000d05c2a09d09c9031366ec092bcac67d4b1b4f88b10005e1fc45c1b483ae7eb86ff0e884a19c0595a6c34f06386d776a21d620fc9f9c498adca00e66d129bcdd4789837b96dcc7f09da94ccac5ac7cfc07f4600df78e493dc1957deba3f4838a4b8bd4cefe4e4c6119085e5bb21077341c568a21d65d049d666807c39c401cdfee7f7f99b8f9cb34a8841ea62e83e8d63";
                    COMMON.convertHStrIntoHex(str22, pdt22, &pdt22Len);
                    r = emv_setCAPK(pdt22, pdt22Len);
                    if (r != RETURN_CODE_DO_SUCCESS) {
                        printf(" >>>>>>load ..... save CAPK  failed! .......... ----- \n");
                    } else {
                        printf(">>set CAPK: OK. load ........\n");
                    }
                    fflush(stdout);
                    pdt22Len = 800;
                    str22    =
                      "a000000152d10101ffda858cb2af08b79d750cc97fa6efe2ef228dda00010001f800a71af977c1079304d6dff3f665ab6db3fbdfa1b170287ac6d7bc0afcb7a202a4c815e1fc2e34f75a052564ee2148a39cd6b0f39cfaef95f0294a86c3198e349ff82eece633d50e5860a15082b4b342a90928024057dd51a2401d781b67ae7598d5d1ff26a441970a19a3a58011ca19284279a85567d3119264806caf761122a71fc0492ac8d8d42b036c394fc494e03b43600d7e02cb5267755ace64437cfa7b475ad40ddc93b8c9bcad63801fc492fd251640e41fd13f6e231f56f97283447ab44cbe11910db3c75243784aa9bdf57539c31b51c9f35bf8bc2495762881255478264b792bbdca6498777ae9120ed935bb3e8bea3eab13d9";
                    COMMON.convertHStrIntoHex(str22, pdt22, &pdt22Len);
                    r = emv_setCAPK(pdt22, pdt22Len);
                    if (r != RETURN_CODE_DO_SUCCESS) {
                        printf(" >>>>>>load ..... save CAPK  failed! .......... ----- \n");
                    } else {
                        printf(">>set CAPK: OK. load ........\n");
                    }
                    fflush(stdout);
                    pdt22Len = 800;
                    str22    =
                      "a000000333c001018b094d260bdf8bfc8b9a88b0c177a43fe2fae765000100019000c7cdb6f2a3fe80a8834cdddd326e1082aa2288f47c464d57b34718193431711a44119148055044cfe3313708bed0c98e1c589b0f53cf6d7e829fcd906d21a90fd4cb6baf13110c4685107c27e00981db29dc0ac186e6d701577f23865626244e1f9b2cd1ddfcb9e899b41f5084d8ccc178a7c3f4546cf93187106fab055a7ac67df62e778cb88823ba58cf7546c2b09f";
                    COMMON.convertHStrIntoHex(str22, pdt22, &pdt22Len);
                    r = emv_setCAPK(pdt22, pdt22Len);
                    if (r != RETURN_CODE_DO_SUCCESS) {
                        printf(" >>>>>>load ..... save CAPK  failed! .......... ----- \n");
                    } else {
                        printf(">>set CAPK: OK. load ........\n");
                    }
                    fflush(stdout);
                    pdt22Len = 800;
                    str22    =
                      "a000000333c10101b6372db9919f8c6c9c88e83d3c600a4ad8adc7a900010001f80092f083cbe46f8dcc0c04e498ba9952ba9d4c09c80dd277e579f07e45772846fa43dd3ab31cc6b08dd18695715949fb108e53a071d393a7fddbf9c5fb0b0507138797317480fc48d633ed38b401a451443ad7f15facda45a62abe24ff6343add0909ea8389348e54e26f842880d1a69f9214368ba30c18de5c5e0cb9253b5abc55fb6ef0a738d927494a30bbf82e340285363b6faa15673829dbb210e710da58ee9e578e7ce55dc812ab7d6dcce0e3b1ae179d664f3356eb951e3c91a1cbbf6a7ca8d0c7ec9c6af7a4941c5051099b9784e56c9162067b8c3b15c5fa4480a645cd2526a69c80ba8ef361be2aa9417defce35b62b0c9cf097d";
                    COMMON.convertHStrIntoHex(str22, pdt22, &pdt22Len);
                    r = emv_setCAPK(pdt22, pdt22Len);
                    if (r != RETURN_CODE_DO_SUCCESS) {
                        printf(" >>>>>>load ..... save CAPK  failed! .......... ----- \n");
                    } else {
                        printf(">>set CAPK: OK. load ........\n");
                    }

                    /*
                     * str22 ="";
                     * convertHStrIntoHex(str22,pdt22,&pdt22Len);
                     * r = emv_setCAPK(pdt22,pdt22Len);
                     * if ( r != RETURN_CODE_DO_SUCCESS ) {
                     *
                     * printf(" >>>>>>load ..... save CAPK  failed! .......... ----- \n" );
                     *
                     * }else
                     * printf(">>set CAPK: OK. load ........\n");
                     *
                     */
                    printf(">>set CAPK: OK. loaded end \n");
                    fflush(stdout);
                }
                break;
            case 23: {
                printf(">>23. Remove CRL\n");
                fflush(stdout);
                BYTE list23[500];
                int lsLen23   = 500;
                const char * crlstr = "a00000000350014455";
                COMMON.convertHStrIntoHex(crlstr, list23, &lsLen23);
                r = emv_removeCRL(list23, lsLen23);

                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- remove  CRL Failed!! ErrorCode:0x%02x ,Info: %s ----- \n", r,
                        strErr);
                    fflush(stdout);
                    break;
                }
                printf("remove   CRL success \n");
                fflush(stdout);
            }
            break;
            case 24: {
                printf(">>24. List CRL\n");
                fflush(stdout);
                BYTE list24[500] = { 0 };
                int lsLen24      = 500;
                memset(list24, 0, 500);
                r = emv_retrieveCRL(list24, &lsLen24);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- retrieve  CRL  list Failed!! ErrorCode:0x%02x ,Info: %s ----- \n", r,
                        strErr);
                    fflush(stdout);
                    break;
                }
                printf("retrieve CRL list success \nlist:\n");
                int i = 0;
                for (i = 0; i < lsLen24; i++) {
                    printf("%02X", list24[i]);
                    if ((i + 1) % 9 == 0)
                        printf("\n");
                }
                fflush(stdout);
            }
            break;
            case 25: {
                printf(">>25. Save CRL\n");
                fflush(stdout);
                BYTE list25[500];
                int lsLen25 = 500;
                //		char * crlstr25 = "a00000000350014455a000000004fe092355a000009999e1014394a00000000350000001a00000000350000002a00000000350000003a00000000350000004a00000000350000005a00000000350000006a00000000350000007a00000000350000008a00000000350000009a00000000350000010a00000000350000011a00000000350000012a00000000350000013a00000000350000014a00000000350000015a00000000350000016a00000000350000017a00000000350000018a00000000350000019a00000000350000020a00000000350000021a00000000350000022a00000000350000023a00000000350000024a00000000350000025a00000000350000026a00000000350000027a00000000350000028a00000000350000029";
                const char * crlstr25 =
                  "a00000000350014455a000000004fe092355a000009999e1014394a00000000350000001a00000000350000002a00000000350000003a00000000350000004a00000000350000005a00000000350000006a00000000350000007a00000000350000008a00000000350000009a00000000350000010a00000000350000011a00000000350000012a00000000350000013a00000000350000014a00000000350000015a00000000350000016a00000000350000017a00000000350000018a00000000350000019a00000000350000020a00000000350000021a00000000350000022a00000000350000023a00000000350000024a00000000350000025a00000000350000026a00000000350000027a00000000350000028a00000000350000029";
                COMMON.convertHStrIntoHex(crlstr25, list25, &lsLen25);
                r = emv_setCRL(list25, lsLen25);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- set   CRL Failed!! ErrorCode:0x%02x ,Info: %s ----- \n",
                        r, strErr);
                    fflush(stdout);
                    break;
                }
                printf("set  CRL success \n");
                fflush(stdout);
            }
            break;

            case 26: {
                printf(">>26. Remove All CRL\n");
                fflush(stdout);
                r = emv_removeAllCRL();
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- remove all CRL Failed!! ErrorCode:0x%02x ,Info: %s ----- \n", r,
                        strErr);
                    fflush(stdout);
                    break;
                }
                printf("remove all CRL success \n");
                fflush(stdout);
            }
            break;
            case 27: {
                printf(">>27. Retrieve Tags\n");
                fflush(stdout);
                //			BYTE tags[7] ={0x9f,0x02,0x9f,0x03,0x9c,0x57,0x5A};
                BYTE tags[50] =
                { 0xDF,     0x10,     0xDF,     0x10, 0xDF, 0x10, 0xDF, 0x10, 0xDF, 0x10, 0xDF, 0x10, 0xDF, 0x10, 0xDF,
                  0x10,
                  0xDF,
                  0x10,     0xDF,     0x10,     0x9f, 0x02, 0x9f, 0x03, 0x9c, 0x57, 0x5A, 0x5F, 0x36, 0x8E, 0x9F, 0x0D,
                  0x9F,
                  0x0E,     0x9F,     0x0F,     0x9F, 0x37, 0x9F, 0x4E, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91,
                  0x91,
                  0x91 };

                IDTTransactionData cardData;

                r = emv_retrieveTransactionResult(tags, 50, &cardData);

                //			r= emv_retrieveTransactionResult(tags,7,&cardData);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- retrieve  trans tags Failed!! ErrorCode:0x%02x ,Info: %s ----- \n", r,
                        strErr);
                    fflush(stdout);
                    return;
                }
                printf("\nUnencrypted Tags\n");
                COMMON.printTLV(cardData.emv_unencryptedTags, cardData.emv_unencryptedTagsLen);
                printf("\nEncrypted Tags\n");
                COMMON.printTLV(cardData.emv_encryptedTags, cardData.emv_encryptedTagsLen);
                printf("\nMasked Tags\n");
                COMMON.printTLV(cardData.emv_maskedTags, cardData.emv_maskedTagsLen);
            }
            break;
            case 28: {
                printf(">>28. Get Terminal ID\n");
                fflush(stdout);
                char terminalID2[30];
                r = emv_retrieveTerminalID(terminalID2);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- retrieve  Terminal ID Failed!! ErrorCode:0x%02x ,Info: %s ----- \n", r,
                        strErr);
                    break;
                }
                printf("retrieve  Terminal ID  success ID:%s.\n", terminalID2);
                fflush(stdout);
            }
            break;
            case 29:
                printf(">>29. Set Config #1 allow fallback\n");
                fflush(stdout);
                emv_allowFallback(1);
                break;
            case 30:
                printf(">>30. Set Config #2 auto Autentication\n");
                fflush(stdout);
                emv_setAutoAuthenticateTransaction(1);
                break;
            case 31:
                printf(">>31. Set Config #3 not allow fall back\n");
                fflush(stdout);
                emv_allowFallback(0);
                break;
            case 32:
                printf(">>32. Set Config #4 not auto Autentication\n");
                fflush(stdout);
                emv_setAutoAuthenticateTransaction(0);
                break;

            case 33: {
                // printf("\t\t33. Set Terminal ID -- fail no this api cann't use\n");
                // return;
                char t1[] = "99999999";
                r = emv_setTerminalID(t1);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- Set  Terminal ID Failed!! ErrorCode:0x%02x ,Info: %s ----- \n", r,
                        strErr);
                    fflush(stdout);
                    break;
                }
                printf("Set  Terminal ID  success \n");
                fflush(stdout);
            }
            break;

            case 34: {
                if (emv_getAutoAuthenticateTransaction() == 1) {
                    printf("\t\t34. Disable Auto Authenticate\n");
                    emv_setAutoAuthenticateTransaction(0);
                    printf("Auto Authenticate Disabled.\n");
                } else {
                    printf("\t\t34. Enable Auto Authenticate\n");
                    emv_setAutoAuthenticateTransaction(1);
                    printf("Auto Authenticate Enabled.\n");
                }

                //			COMMON.set_auto_emv_authenticate(!COMMON.get_auto_emv_authenticate());
                //
                //			if(COMMON.get_auto_emv_authenticate() == 1)
                //				printf("Auto Authenticate Enabled.\n");
                //			else
                //				printf("Auto Authenticate Disabled.\n");
                fflush(stdout);
            }
            break;
            case 35: {
                if (emv_getAutoCompleteTransaction() == 1) {
                    printf("\t\t35. Disable Auto Complete\n");
                    emv_setAutoCompleteTransaction(0);
                    printf("Auto Complete Disabled.\n");
                } else {
                    printf("\t\t35. Enable Auto Complete\n");
                    emv_setAutoCompleteTransaction(1);
                    printf("Auto Complete Enabled.\n");
                }
                //			COMMON.set_auto_emv_complete(!COMMON.get_auto_emv_complete());

                //			if(COMMON.get_auto_emv_complete() == 1)
                //				printf("Auto Complete Enabled.\n");
                //			else
                //				printf("Auto Complete Disabled.\n");
                fflush(stdout);
            }
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
} /* _Augusta_process_emv */

void
_Augusta_display_emv_menu() {
    idtech_display_menu_from_lib.pDisplay_Menu_current = _Augusta_display_emv_menu;
    printf("\t\t********** EMV Options [Augusta]************\n");
    printf("\t\t0.  Back To Main Menu\n");
    printf("\t\t1.  Start EMV Trans\n");
    if (emv_getAutoAuthenticateTransaction() == 1) {
        printf("\t\t2.  Authenticate EMV Trans [Auto]\n");
    } else {
        printf("\t\t2.  Authenticate EMV Trans\n");
    }
    if (emv_getAutoCompleteTransaction() == 1) {
        printf("\t\t3.  Complete EMV Trans [Auto]\n");
    } else {
        printf("\t\t3.  Complete EMV Trans\n");
    }
    printf("\t\t4.  Cancel EMV Trans\n");
    printf("\t\t5.  Kernel Version\n");
    printf("\t\t6.  Kernel Checksum\n");
    printf("\t\t7.  Config Checksum\n");
    printf("\t\t8.  Retrieve AID\n");
    printf("\t\t9.  Remove AID\n");
    printf("\t\t10. List AID\n");
    printf("\t\t11. Save AID\n");
    printf("\t\t12. Remove All AID\n");
    printf("\t\t13. Load Default AID\n");
    printf("\t\t14. Get Terminal Data\n");
    printf("\t\t15. Remove Terminal Data\n");
    printf("\t\t16. Save Terminal Data\n");
    printf("\t\t17. Retrieve CAPK\n");
    printf("\t\t18. Remove CAPK\n");
    printf("\t\t19. List CAPK\n");
    printf("\t\t20. Save CAPK\n");
    printf("\t\t21. Remove All CAPK\n");
    printf("\t\t22. Load Default CAPK\n");
    printf("\t\t23. Remove CRL\n");
    printf("\t\t24. List CRL\n");
    printf("\t\t25. Save CRL\n");
    printf("\t\t26. Remove All CRL\n");
    printf("\t\t27. Retrieve Tags\n");
    printf("\t\t28. Get Terminal ID\n");
    printf("\t\t29. Set Config #1 allow fallback\n");
    printf("\t\t30. Set Config #2 auto Authentication\n");
    printf("\t\t31. Set Config #3 not allow fallback\n");
    printf("\t\t32. Set Config #4 not auto Autentication\n");
    printf("\t\t33. Set Terminal ID\n");
    if (emv_getAutoAuthenticateTransaction() == 1) {
        printf("\t\t34. Disable Auto Authenticate\n");
    } else {
        printf("\t\t34. Enable Auto Authenticate\n");
    }
    if (emv_getAutoCompleteTransaction() == 1) {
        printf("\t\t35. Disable Auto Complete\n");
    } else {
        printf("\t\t35. Enable Auto Complete\n");
    }
    printf("\t\t************************************************\n");
    fflush(stdout);
} /* _Augusta_display_emv_menu */
