#include <stdio.h>
#include <string.h>
#include "demo_common.h"

IDT_COMMON_PROCESS COMMON;
extern IDT_PROCESS idtech_process;
extern IDT_DEMO_LIB_DISPLAY_MENU idtech_display_menu_from_lib;

void
_Augusta_display_device_menu();

void
WorldPayCallback(char * message, int returnCode, int emvCode) {
    printf("WORLDPAY RESPONSE>>>>>>>\n");
    printf("Return Code = %d\n", returnCode);
    printf("EMV Code = %d\n", emvCode);
    printf("Message = \n%s\n", message);
    //	 _Augusta_display_device_menu();
    if (idtech_display_menu_from_lib.pDisplay_Menu_current) {
        idtech_display_menu_from_lib.pDisplay_Menu_current();
        printf("Please Input your Selection. (0 - exit current menu)\n");
    }
}

void
_Augusta_process_device() {
    int choice;
    int r = 0;
    char str1[256] = { 0 };
    int len        = 512;

    memset(str1, 0, 256);
    do {
        _Augusta_display_device_menu();
        choice = COMMON.inputSelection();
        switch (choice) {
            case 1: {
                printf(">>1. Get Firmware Version\n");
                fflush(stdout);
                r = device_getFirmwareVersion(str1);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- Get Firmware Version Controller Failed! ErrorCode: 0x%02x, Info: %s ----- \n", r,
                        strErr);
                } else {
                    char str2[200] = { 0 };
                    sprintf(str2, "Firmware version: %s\n", str1);
                    printf(str2);
                }
                fflush(stdout);
            }
            break;
            case 2: {
                printf(">>2. Reboot Device\n");
                fflush(stdout);
                r = device_rebootDevice();
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- Do device_rebootDevice(), failed! ErrorCode:0x%02x ,Info: %s ----- \n", r,
                        strErr);
                } else {
                    //					char str2[200] = {0};
                    printf("Reboot Device Success!");
                }
                fflush(stdout);
            }
            break;
            case 3: {
                printf(">>3. Send Command\n");
                fflush(stdout);
                BYTE bbyte[5] = { 0x00 };
                int cmdlen;
                BYTE cmdData[_DATA_BUF_LEN] = { 0x00 };
                int cmdDataLen;
                bbyte[0] = 0x78;
                bbyte[1] = 0x31;
                cmdlen   = 2;
                BYTE rbbyte[512] = { 0 };
                memset(rbbyte, 0, 512);
                len = 512;

                r = device_SendDataCommand(bbyte, cmdlen, NULL, 0, rbbyte, &len);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- Do device_SendDataCommand(), failed! ErrorCode:0x%02x ,Info: %s ----- \n", r,
                        strErr);
                } else {
                    char str3[1024] = { 0 };
                    memset(str3, 0, 1024);
                    COMMON.convertBytesIntoHexStr(rbbyte, len, 0, str3);
                    printf("response code : %s\n", str3);
                }
                fflush(stdout);
            }
            break;
            case 4: {
                printf(">>4. Control MSR LED ON\n");
                fflush(stdout);
                r = device_controlLED(1, 0x11, 0, 0);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- Do device_controlLED(), failed! ErrorCode:0x%02x ,Info: %s ----- \n", r,
                        strErr);
                } else {
                    printf("MSR LED ON Success!\n");
                }
                fflush(stdout);
            }
            break;
            case 5: {
                printf(">>5. Control MSR LED OFF\n");
                fflush(stdout);
                r = device_controlLED(1, 0x00, 0, 0);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- Do device_controlLED(), failed! ErrorCode:0x%02x ,Info: %s ----- \n", r,
                        strErr);
                } else {
                    printf("MSR LED OFF Success!\n");
                }
                fflush(stdout);
            }
            break;
            case 6: {
                printf(">>6. Control MSR LED Blink\n");
                fflush(stdout);
                r = device_controlLED(1, 0x12, 500, 500);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- Do device_controlLED(), failed! ErrorCode:0x%02x ,Info: %s ----- \n", r,
                        strErr);
                } else {
                    printf("MSR LED Blink Success!\n");
                }
                fflush(stdout);
            }
            break;
            case 7: {
                printf(">>7. Control ICC LED ON\n");
                fflush(stdout);
                r = device_controlLED_ICC(1, 0);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- Do device_controlLED_ICC(), failed! ErrorCode:0x%02x ,Info: %s ----- \n", r,
                        strErr);
                } else {
                    printf("ICC LED ON Success!\n");
                }
                fflush(stdout);
            }
            break;
            case 8: {
                printf(">>8. Control ICC LED OFF\n");
                fflush(stdout);
                r = device_controlLED_ICC(0, 0);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- Do device_controlLED_ICC(), failed! ErrorCode:0x%02x ,Info: %s ----- \n", r,
                        strErr);
                } else {
                    printf("ICC LED OFF Success!\n");
                }
                fflush(stdout);
            }
            break;
            case 9: {
                printf(">>9. Control ICC LED Blink\n");
                fflush(stdout);
                r = device_controlLED_ICC(2, 500);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- Do device_controlLED_ICC(), failed! ErrorCode:0x%02x ,Info: %s ----- \n", r,
                        strErr);
                } else {
                    printf("ICC LED Blink Success!\n");
                }
                fflush(stdout);
            }
            break;
            case 10: {
                printf(">>10. Beep for 3 seconds\n");
                fflush(stdout);
                r = device_controlBeep(1, 4000, 3000);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getResponseCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- Do device_controlBeep(), failed! ErrorCode:0x%02x ,Info: %s ----- \n", r,
                        strErr);
                } else {
                    printf("Control Beep Success!\n");
                }
                fflush(stdout);
            }
            break;
            //		case 11:
            //		{
            //			printf(">>11. Set Date/Time\n");
            //            int r = device_setDateTime();
            //            if (r == RETURN_CODE_DO_SUCCESS)
            //            {
            //                printf("Set Date Time Successful.\r\n");
            //            }
            //            else
            //            {
            //			   char strErr[200] = {0};
            //			   memset(strErr,0,200);
            //			   device_getResponseCodeString(r, strErr);
            //			   printf(">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- Do device_setDateTime(), failed! ErrorCode:0x%02x ,Info: %s ----- \n",r,strErr);
            //           }
            //		}
            //      break;
            case 11:
                printf(">>11. Get Key Status\n");
                fflush(stdout);
                {
                    int newFormat    = 0;
                    BYTE status[100] = { 0 };
                    int statusLen    = 100;
                    r = device_getKeyStatus(&newFormat, status, &statusLen);
                    if (0 == newFormat && r == RETURN_CODE_DO_SUCCESS && statusLen > 0) {
                        printf("Get Key Status succeeded:\r\n");
                        if (status[0] == 0x01) {
                            printf("\tPIN DUKPT Key Loaded\r\n");
                        } else if (status[0] == 0xFF) {
                            printf("\tPIN DUKPT Key STOP\r\n");
                        } else {
                            printf("\tPIN DUKPT Key NOT Loaded\r\n");
                        }
                        if (status[1] == 0x01) {
                            printf("\tPIN Master Key Loaded\r\n");
                        } else {
                            printf("\tPIN Master Key NOT Loaded\r\n");
                        }
                        if (status[2] == 0x01) {
                            printf("\tPIN Session Key Loaded\r\n");
                        } else {
                            printf("\tPIN Session Key NOT Loaded\r\n");
                        }
                        if (status[3] == 0x01) {
                            printf("\tMSR DUKPT Key Loaded\r\n");
                        } else if (status[3] == 0xFF) {
                            printf("\tMSR DUKPT Key STOP\r\n");
                        } else {
                            printf("\tMSR DUKPT Key NOT Loaded\r\n");
                        }
                        if (status[4] == 0x01) {
                            printf("\tICC DUKPT Key Loaded\r\n");
                        } else if (status[4] == 0xFF) {
                            printf("\tICC DUKPT Key STOP\r\n");
                        } else {
                            printf("\tICC DUKPT Key NOT Loaded\r\n");
                        }
                        if (status[5] == 0x01) {
                            printf("\tAdmin Key Loaded\r\n");
                        } else if (status[5] == 0xFF) {
                            printf("\tAdmin Key STOP\r\n");
                        } else {
                            printf("\tAdmin Key NOT Loaded\r\n");
                        }
                    } else {
                        char strErr[200] = { 0 };
                        memset(strErr, 0, 200);
                        device_getResponseCodeString(r, strErr);
                        printf(
                            ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n	----- Do device_getKeyStatus(), failed! ErrorCode:0x%02x ,Info: %s ----- \n", r,
                            strErr);
                    }
                    fflush(stdout);
                }
                break;
            case 12: {
                printf(">>12. WorldPay Transaction\n");

                WorldPayData data;
                strcpy(data.accountID, "1188346\0");
                strcpy(data.accountToken, "E1EB3EFB049DFB599F1CB454E1CFC4FD14BF90BCE74456AE9E9490D7D609B466C81A3801\0");
                strcpy(data.acceptorID, "364798674\0");
                data.transactionType = TRANSACTION_TYPE_SALE;
                // data.transactionType = TRANSACTION_TYPE_PRE_AUTH;
                // data.transactionType = TRANSACTION_TYPE_COMPLETION;
                // data.transactionType = TRANSACTION_TYPE_VOID;
                // data.transactionType = TRANSACTION_TYPE_RETURN;
                strcpy(data.amount, "22.00\0");                 // specify transaction Amount
                data.timeout = 30;                              // Timeout for transaction
                data.isTest  = 1;                               // if test transaction, set to TRUE.  If live transactions, set to FALSE
                data.msrOnly = 0;                               // for EMV + MSR, set to FALSE.  If MSR swipe only, set to TRUE
                strcpy(data.transactionID, "3830\0");           // required if COMPLETION, VOID, RETURN.  Otherwise, leave blank
                strcpy(data.referenceNumber, "112233445566\0"); // required value. Set a reference number
                strcpy(data.terminalID, "12345\0");             // required value.  Set a terminal identifer
                strcpy(data.ticketNumber, "54321\0");           // required value. Set a ticket number
                data.duplicateCheck    = 0;                     // set to TRUE if you want to check for duplicate transactions
                data.duplicateOverride = 1;                     // set to TRUE if you want to allow duplicate charges to same card

                int requestMode = 1; // 0 = Return Gateway Response
                                     // 1 = Return Request + Gateway Response
                                     // 2 = Return Request Only

                r = executeTransaction(&data, WorldPayCallback, requestMode);
                if (r != IDG_P2_STATUS_CODE_DO_SUCCESS) {
                    char strErr[200] = { 0 };
                    memset(strErr, 0, 200);
                    device_getIDGStatusCodeString(r, strErr);
                    printf(
                        ">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- Execute WP Transaction Failed! ErrorCode:0x%02x, Info: %s ----- \n", r,
                        strErr);
                } else {
                    printf("Execute Transaction Succeeded\n");
                }
                fflush(stdout);
            }
            break;
            case 13: {
                 printf(">>13. Cancel WorldPay Transaction\n");
                 r = cancelWorldPay();
                 if (r != RETURN_CODE_DO_SUCCESS) {
                     printf("  Do cancelWorldPay(), failed! Error Code: %04X\n", r);
                 } else {
                     printf("Cancel WorldPay Transaction Succeeded\n");
                 }
                 fflush(stdout);
            }
            break;
                #ifndef WIN32
            case 14: {
                printf(">>14. Update Firmware\n");
                char firmware_file_name[30];
                printf("Please enter the firmware file name (Ex. Augusta_S_TTK_V1.00.XXX.fm):\n");
                fflush(stdout);
                fgets(firmware_file_name, 30, stdin);
                int i;
                for (i = 0; i < 30; i++) {
                    if (firmware_file_name[i] == '\n' || firmware_file_name[i] == '\r') {
                        firmware_file_name[i] = '\0';
                        break;
                    }
                }

                FILE * fp;
                if (NULL == (fp = fopen(firmware_file_name, "rb"))) {
                    printf("Could not open file %s\n", firmware_file_name);
                    fflush(stdout);
                    break;
                }

                BYTE firmwareData[_FIRMWARE_BUF_LEN / 4];
                int fw_size = 0;

                fseek(fp, 0, SEEK_END);
                fw_size = ftell(fp);
                if (fw_size > _FIRMWARE_BUF_LEN / 4) {
                    printf("Not enough buffer\n");
                    fflush(stdout);
                    break;
                }

                fseek(fp, 0, SEEK_SET);
                fread(firmwareData, fw_size, 1, fp);
                fclose(fp);

                printf("Firmware file size: %d\n", fw_size);
                printf("\033[1;31mUpdating firmware, please do not unplug the reader or close this program...\033[0m\n");
                fflush(stdout);
                r = device_updateFirmware(firmwareData, fw_size, firmware_file_name, 0, NULL, 0);
                if (r != RETURN_CODE_DO_SUCCESS) {
                    if (r == RETURN_CODE_FW_INIT_SUCCESS) {
                        //						printf("Initialize Firmware Update succeeded, please re-select the device after reboot, and do Update Firmware again.\n");
                        printf(
                            "\033[1;31mInitialize Firmware Update succeeded, please re-select the same device through Device Select Options menu, and do Update Firmware again.\033[0m\n");
                        printf(
                            "\033[1;31mWarning: Please do NOT close this program before firmware update is done.\033[0m\n");
                    } else {
                        //						printf("Firmware Update failed!\n");
                        printf("\033[1;31mFirmware Update failed!\033[0m\n");
                        printf("Error code: 0x%04X\n", r);
                    }
                } else {
                    //					printf("Firmware Update succeeded.\n");
                    printf(
                        "\033[1;31mFirmware Update succeeded.  Please re-select a device through Device Select Options menu.\033[0m\n");
                }
                fflush(stdout);
            }
            break;
                #endif /* ifndef WIN32 */
            //		case 13:
            //		{
            //			printf(">>13. USB KB Mode\n");
            //			int r = msr_switchUSBInterfaceMode(1);
            //			if (r == RETURN_CODE_DO_SUCCESS)
            //			{
            //				printf("Set USB KB Mode Succeeded.\r\n");
            //			}
            //			else
            //			{
            //			   char strErr[200] = {0};
            //			   memset(strErr,0,200);
            //			   device_getResponseCodeString(r, strErr);
            //			   printf(">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- Do msr_switchUSBInterfaceMode(), failed! ErrorCode:0x%02x ,Info: %s ----- \n",r,strErr);
            //		   }
            //		}
            //		break;
            //		case 14:
            //		{
            //			printf(">>14. USB HID Mode\n");
            //			int r = msr_switchUSBInterfaceMode(0);
            //			if (r == RETURN_CODE_DO_SUCCESS)
            //			{
            //				printf("Set USB KB Mode Succeeded.\r\n");
            //			}
            //			else
            //			{
            //			   char strErr[200] = {0};
            //			   memset(strErr,0,200);
            //			   device_getResponseCodeString(r, strErr);
            //			   printf(">>>>>>>>>>>>FAIL<<<<<<<<<<<<< \n   ----- Do msr_switchUSBInterfaceMode(), failed! ErrorCode:0x%02x ,Info: %s ----- \n",r,strErr);
            //		   }
            //		}
            //		break;
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
} /* _Augusta_process_device */

void
_Augusta_display_device_menu() {
    idtech_display_menu_from_lib.pDisplay_Menu_current = _Augusta_display_device_menu;
    printf("\t\t********* Device Options [Augusta]*********\n");
    printf("\t\t0.  Back To Main Menu\n");
    printf("\t\t1.  Get Firmware Version\n");
    printf("\t\t2.  Reboot Device\n");
    printf("\t\t3.  Send Command\n");
    printf("\t\t4.  Control MSR LED ON\n");
    printf("\t\t5.  Control MSR LED OFF\n");
    printf("\t\t6.  Control MSR LED Blink\n");
    printf("\t\t7.  Control ICC LED ON\n");
    printf("\t\t8.  Control ICC LED OFF\n");
    printf("\t\t9.  Control ICC LED Blink\n");
    printf("\t\t10. Beep for 3 seconds\n");
    //	printf("\t\t11. Set Date/Time\n");
    printf("\t\t11. Get Key Status\n");
    printf("\t\t12. WorldPay Transaction\n");
    printf("\t\t13. Cancel WorldPay Transaction\n");
    //	printf("\t\t14. USB HID Mode\n");
    //	printf("\t\t12. Initialize Firmware Update\n");
    #ifndef WIN32
    printf("\t\t14. Update Firmware (Need to run twice)\n");
    #endif
    printf("\t\t************************************************\n");
    fflush(stdout);
}
