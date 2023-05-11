#if !defined(DEMO_COMMON_INCLUDE_)
#define DEMO_COMMON_INCLUDE_
#include "IDTDef.h"

// define the function pointer to dynamically call the processing by different device type;
typedef struct {
    void (* pProcess_function_list)();
    void (* pProcess_device)();
    void (* pProcess_config)();
    void (* pProcess_msr)();
    void (* pProcess_icc)();
    void (* pProcess_ctls)();
    void (* pProcess_emv)();
    void (* pProcess_pin)();
    void (* pProcess_lcd)();
    void (* pProcess_ws)();
    //		void (*pProcess_cmr)();
} IDT_PROCESS;
typedef struct _IDT_DEMO_LIB_DISPLAY_MENU {
    void (* pDisplay_Menu_function_list)();
    void (* pDisplay_Menu_device)();
    void (* pDisplay_Menu_config)();
    void (* pDisplay_Menu_msr)();
    void (* pDisplay_Menu_icc)();
    void (* pDisplay_Menu_ctls)();
    void (* pDisplay_Menu_emv)();
    void (* pDisplay_Menu_pin)();
    void (* pDisplay_Menu_lcd)();
    void (* pDisplay_Menu_ws)();
    //		void (*pDisplay_Menu_cmr)();
    void (* pDisplay_Menu_current)();
} IDT_DEMO_LIB_DISPLAY_MENU;


typedef struct {
    // Main process_device_select
    void (* main_display_device_list)();
    // Main process_device_select
    void (* main_process_device_select)();
    // Send Data Log
    void (* SendDataLog)(BYTE * data, int dataLen);
    // Read Data Log
    void (* ReadDataLog)(BYTE * data, int dataLen);

    // FW
    void (* FW_callBack)(int deviceType, int state, int currentBlock, int totalBlocks, int ResultCode);
    // RKI
    void (* RKI_callBack)(int ResultCode, char * macValue);
    // PIN
    void (* PIN_callBack)(int type, IDTPINData * pinData);
    // LCD
    void (* LCD_callBack)(int type, IDTLCDItem * lcdItem);
    // Camera
    void (* CMR_callBack)(int type, IDTCMRData * cmrData);
    // Card Status and Front Switch
    void (* CSFS_callBack)(BYTE status);
    // MSR
    void (* printMSRData)(IDTMSRData * cardData);
    void (* printTransactionData)(IDTMSRData * cardData);
    void (* MSR_callBack)(int type, IDTMSRData cardData1);
    void (* MSR_callBackp)(int type, IDTMSRData * cardData1);
    // EMV
    void (* printBytes)(unsigned char * data, int len);
    void (* printTLV)(unsigned char * data, int len);
    int (* convertBytesIntoHexStr)(unsigned char * hexData, int datalen, int withChar_LineFeed, char * str);
    int (* convertHStrIntoHex)(const char * srcStr, unsigned char * hexData, int * datalen);
    void (* EMV_callBack)(int device_type, int device_state, unsigned char * data, int dataLen,
      IDTTransactionData * cardData, EMV_Callback * emvCallback, int transactionResultCode);

    //	void (*set_auto_emv_authenticate)(int auto_authenticate);
    //	int (*get_auto_emv_authenticate)( );
    //
    //	void (*set_auto_emv_complete)(int auto_complete);
    //	int (*get_auto_emv_complete)( );


    void (* set_emv_Finished)(int auto_Finished);
    int (* get_emv_Finished)();

    void (* set_pin_Finished)(int auto_Finished);
    int (* get_pin_Finished)();

    void (* getDUKPT)(int type);

    int (* inputSelection)();

    int (* printAIDList)(unsigned char * hexData, int datalen);

    void (* process_exit)();
} IDT_COMMON_PROCESS;


extern void
SendDataLog(BYTE * data, int dataLen);
extern void
ReadDataLog(BYTE * data, int dataLen);
extern void
PIN_callBack(int type, IDTPINData * pinData);
extern void
LCD_callBack(int type, IDTLCDItem * lcdItem);
extern void
CMR_callBack(int type, IDTCMRData * cmrData);
extern void
CSFS_callBack(BYTE status);
extern void
printMSRData(IDTMSRData * cardData);
extern void
printTransactionData(IDTTransactionData * cardData);

extern void
FW_callBack(int deviceType, int state, int currentBlock, int totalBlocks, int ResultCode);
extern void
RKI_callBack(int ResultCode, char * macValue);

extern void
MSR_callBack(int type, IDTMSRData cardData1);
extern void
MSR_callBackp(int type, IDTMSRData * cardData1);

extern void
printBytes(unsigned char * data, int len);
extern void
printTLV(unsigned char * data, int len);
extern int
convertBytesIntoHexStr(unsigned char * hexData, int datalen, int withChar_LineFeed, char * str);
extern int
convertHStrIntoHex(const char * srcStr, unsigned char * hexData, int * datalen);

extern int
printAIDList(unsigned char * hexData, int datalen);
extern void
EMV_callBack(int device_type, int device_state, unsigned char * data, int dataLen, IDTTransactionData * cardData,
  EMV_Callback * emvCallback, int transactionResultCode);

extern void
getDUKPT(int type);

// extern void set_auto_emv_authenticate(int auto_authenticate);
// extern int get_auto_emv_authenticate();
//
// extern void set_auto_emv_complete (int auto_complete);
// extern int get_auto_emv_complete();

extern void
set_emv_Finished(int auto_Finished);
extern int
get_emv_Finished();
extern void
set_pin_Finished(int auto_Finished);
extern int
get_pin_Finished();
extern int
inputSelection();
extern void
process_exit();

// IDT_DEMO_LIB_DISPLAY_MENU idtech_display_menu_from_lib;

#endif // if !defined(DEMO_COMMON_INCLUDE_)
