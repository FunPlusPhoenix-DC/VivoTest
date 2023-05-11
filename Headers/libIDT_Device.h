#ifndef __LIBIDT_DEVICE_H___
# define __LIBIDT_DEVICE_H___

# define IN
# define OUT
# define IN_OUT
# include "IDTDef.h"

/**
 * Define the USB hot-plug callback function to monitor the info when
 * plug in/out the reader. <br/>
 * It should be registered using the registerHotplugCallBk,
 * The first integer parameter is device type, and the second integer
 * parameter is either 0: Device Plugged Out or 1: Device Plugged In
 */
typedef void (* pMessageHotplug)(int,
  int);

/**
 * Define the send command callback function to monitor the sending command
 * into the reader. <br/>
 * It should be registered using the registerLogCallBk,
 */
typedef void (* pSendDataLog)(BYTE *,
  int);

/**
 * Define the read response callback function to monitor the reading
 * response from the reader. <br/>
 * It should be registered using the registerLogCallBk,
 */
typedef void (* pReadDataLog)(BYTE *,
  int);

/**
 * Define the EMV callback function to get the transaction
 * message/data/result. <br/>
 * It should be registered using the emv_registerCallBk,
 */
typedef void (* pEMV_callBack)(int,
  int,
  BYTE *,
  int,
  IDTTransactionData *,
  EMV_Callback *,
  int);


/**
 * Define the Worldpay callback function to get the transaction
 * message/data/result. <br/>
 */
typedef void (* pWP_callBack)(char *,
  int,
  int);

/**
 * Define the MSR callback function to get the MSR card data <br/>
 * It should be registered using the msr_registerCallBk, this callback function is for backward compatibility
 */
typedef void (* pMSR_callBack)(int, IDTMSRData);

/**
 * Define the MSR callback function to get pointer to the MSR card data <br/>
 * It should be registered using the msr_registerCallBk, this callback function is recommended instead of pMSR_callBack
 */
typedef void (* pMSR_callBackp)(int, IDTMSRData *);

/**
 * Define the PINPad callback function to get the input PIN Pad data <br/>
 * It should be registered using the pin_registerCallBk,
 */
typedef void (* pPIN_callBack)(int,
  IDTPINData *);

/**
 * Define the LCD callback function to get the input LCDItem <br/>
 * It should be registered using the lcd_registerCallBk,
 */
typedef void (* pLCD_callBack)(int,
  IDTLCDItem *);

/**
 * Define the camera callback function to get the image data <br/>
 * It should be registered using the device_registerCameraCallBk,
 */
typedef void (* pCMR_callBack)(int,
  IDTCMRData *);

/**
 * Define the card status and front switch callback function to get card and front switch status <br/>
 * It should be registered using the device_registerCardStatusFrontSwitchCallBk,
 */
typedef void (* pCSFS_callBack)(BYTE status);

/**
 * Define the FW callback function to get the status of the firmware update <br/>
 * It should be registered using the device_registerFWCallBk,
 */
typedef void (* pFW_callBack)(int,
  int,
  int,
  int,
  int);

/**
 * Define the RKI callback function to get the status of the RKI <br/>
 * It should be registered using the device_registerRKICallBk,
 */
typedef void (* pRKI_callBack)(int,
  char *);

/**
 * Define the comm callback function to get the async url data <br/>
 * It should be registered using the comm_registerHTTPCallback,
 */
typedef void (* httpComm_callBack)(BYTE *,
  int);

/**
 * Define the comm callback function to receive the V4 Protocol packets
 * received by the device from an external source (IP/USB/RS-232)
 * It should be registered using the comm_registerV4Callback,
 * Data callback will contain command, sub-command, and data from V4 packet
 */
typedef void (* v4Comm_callBack)(BYTE,
  BYTE,
  BYTE *,
  int);

/**
 * Define the comm callback function to get FTP file transfer status <br/>
 * It should be passed as a parameter in a FTP request,
 * Signature (int, int, int) = response code, current block, total blocks
 * RESPONSE CODES:
 *        100 = FILE DOWNLOAD STARTED
 *        101 = FILE BLOCK XX OF XX RECEIVED
 *        102 = FILE DOWNLOAD COMPLETED
 *        103 = FILE DOWNLOAD TERMINATED PREMATURELY
 */
typedef void (* ftpComm_callBack)(int,
  int,
  int);

/**
 * Define the log callback function to receive log messages.
 */
typedef void (* pLog_callback)(BYTE, char *);

# ifdef __cplusplus
extern "C" {
# endif

/**
 * To register the USB HID hot-plug callback function which
 * implemented in the application to monitor the hotplug message from
 * the SDK.
 */
void
registerHotplugCallBk(pMessageHotplug pMsgHotplug);

/**
 * To register the log callback function which implemented in the
 * application to monitor sending/reading data between application and
 * reader.
 */
void
registerLogCallBk(pSendDataLog pFSend,
  pReadDataLog                 pFRead);

/**
 * To register the emv callback function to get the EMV processing response.  (Pass NULL to disable the callback.)
 */
void
emv_registerCallBk(pEMV_callBack pEMVf);

/**
 * To register the loyalty callback function to get the EMV processing response.  (Pass NULL to disable the callback.)
 *     Only for VP6800
 */
void
loyalty_registerCallBk(pEMV_callBack pEMVf);

/**
 * To register the msr callback function to get the MSR card data.  (Pass NULL to disable the callback.)
 */
void
msr_registerCallBk(pMSR_callBack pMSRf);

/**
 * To register the msr callback function to get the MSR card data pointer.  (Pass NULL to disable the callback.)
 */
void
msr_registerCallBkp(pMSR_callBackp pMSRf);

/**
 * To register the ctls callback function to get the CTLS card data pointer.  It's the same as msr_registerCallBkp().  (Pass NULL to disable the callback.)
 */
void
ctls_registerCallBkp(pMSR_callBackp pMSRf);

///**
// *To register the loyalty MSR callback function to get the MSR card data.  (Pass NULL to disable the callback.)
// */
// void loyalty_registerMSRCallBk(pMSR_callBack pMSRf);
//
///**
// *To register the loyalty MSR callback function to get the MSR card data pointer.  (Pass NULL to disable the callback.)
// */
// void loyalty_registerMSRCallBkp(pMSR_callBackp pMSRf);

/**
 * To register the pin callback function to get the PINPad data.  (Pass NULL to disable the callback.)
 */
void
pin_registerCallBk(pPIN_callBack pPINf);

/**
 * To register the lcd callback function to get the LCDItem.  (Pass NULL to disable the callback.)
 */
void
lcd_registerCallBk(pLCD_callBack pLCDf);

/**
 * To register the camera callback function to get the image data.  (Pass NULL to disable the callback.)
 */
void
device_registerCameraCallBk(pCMR_callBack pCMRf);

/**
 * To register the card status and front switch callback function to get status.  (Pass NULL to disable the callback.)
 */
void
device_registerCardStatusFrontSwitchCallBk(pCSFS_callBack pCSFSf);

/**
 * To register the firmware update callback function to get the
 * firmware update status.  (Pass NULL to disable the callback.)
 */
void
device_registerFWCallBk(pFW_callBack pFWf);

/**
 * To register the RKI callback function to get the
 * RKI status.  (Pass NULL to disable the callback.)
 */
void
device_registerRKICallBk(pRKI_callBack pRKIf);

/**
 * To Get SDK version
 * @return return the SDK version string
 */
char *
SDK_Version();

/**
 * Set the path to use when searching for ID TECH's libraries.
 * If this is not set, the libraries will be searched for with the system's default procedures.
 *
 * @param absoluteLibraryPath The absolute path to ID TECH's libraries.
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 */
int
setAbsoluteLibraryPath(const char * absoluteLibraryPath);

/**
 * Set the path to the config xml file(s) if any <br/>
 *
 * @param path The path to the config xml files (such as "NEO2_Devices.xml"
 * which contains the information of NEO2 devices).
 *    Only need to specify the path to the folder which contains the config files.
 *    File names are not needed.
 *    The maximum length of path is 200 characters including the '\0' at the end.
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
device_setConfigPath(const char * path);

/**
 * Pass the content of the config xml file ("NEO2_Devices.xml") as a string
 * to the SDK instead of reading the config xml file by the SDK
 *     It needs to be called before device_init(), otherwise the SDK will
 *     try to read the config xml file.
 *
 * @param configs The content read from the config xml file ("NEO2_Devices.xml"
 * which contains the information of NEO2 devices).
 * @param len The length of the string configs.  The maximum length is 5000
 * bytes.
 *
 */
int
device_setNEO2DevicesConfigs(IN const char * configs,
  IN int                                     len);

/**
 * Initial the device by USB<br/>
 * It will detect the device and trying connect. <br/>
 * The connect status can be checked by device_isConnected(). <br/>
 * Note: after the function returns success, the function device_setCurrentDevice() has to be called to set the device type.
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
device_init();

/**
 * Set the generation for the NEO 2 or 3 readers<br/>
 *
 * @param gen The generation of the NEO 2/3 readers.  2: NEO 2, 3: NEO 3
 *
 */
void
device_setNEOGen(int gen);

/**
 * Set the alternative device type for the NEO 2 or 3 readers<br/>
 *
 * @param alt The alternative device type of the NEO 2/3 readers.
 *
 */
void
device_setNEOAltDevice(int alt);

/**
 * Initial the device by RS232<br/>
 * It will try to connect to the device with provided deviceType, port_number, and brate. <br/>
 * @param deviceType Device to connect to
 * @param port_number Port number of the device
 *   Port nr. |  Linux  | Windows
 *
 *  -----------------------------
 *
 *  | 0       | ttyS0   | COM1  |
 *
 *  | 1       | ttyS1   | COM2  |
 *
 *  | 2       | ttyS2   | COM3  |
 *
 *  | 3       | ttyS3   | COM4  |
 *
 *  | 4       | ttyS4   | COM5  |
 *
 *  | 5       | ttyS5   | COM6  |
 *
 *  | 6       | ttyS6   | COM7  |
 *
 *  | 7       | ttyS7   | COM8  |
 *
 *  | 8       | ttyS8   | COM9  |
 *
 *  | 9       | ttyS9   | COM10 |
 *
 *  | 10      | ttyS10  | COM11 |
 *
 *  | 11      | ttyS11  | COM12 |
 *
 *  | 12      | ttyS12  | COM13 |
 *
 *  | 13      | ttyS13  | COM14 |
 *
 *  | 14      | ttyS14  | COM15 |
 *
 *  | 15      | ttyS15  | COM16 |
 *
 *  | 16      | ttyUSB0 | n.a.  |
 *
 *  | 17      | ttyUSB1 | n.a.  |
 *
 *  | 18      | ttyUSB2 | n.a.  |
 *
 *  | 19      | ttyUSB3 | n.a.  |
 *
 *  | 20      | ttyUSB4 | n.a.  |
 *
 *  | 21      | ttyUSB5 | n.a.  |
 *
 *  | 22      | ttyAMA0 | n.a.  |
 *
 *  | 23      | ttyAMA1 | n.a.  |
 *
 *  | 24      | ttyACM0 | n.a.  |
 *
 *  | 25      | ttyACM1 | n.a.  |
 *
 *  | 26      | rfcomm0 | n.a.  |
 *
 *  | 27      | rfcomm1 | n.a.  |
 *
 *  | 28      | ircomm0 | n.a.  |
 *
 *  | 29      | ircomm1 | n.a.  |
 *
 *  | 30      | cuau0   | n.a.	|
 *
 *  | 31      | cuau1   | n.a.  |
 *
 *  | 32      | cuau2   | n.a.  |
 *
 *  | 33      | cuau3   | n.a.  |
 *
 *  | 34      | cuaU0   | n.a.  |
 *
 *  | 35      | cuaU1   | n.a.  |
 *
 *  | 36      | cuaU2   | n.a.  |
 *
 *  | 37      | cuaU3   | n.a.  |
 * @param brate Bitrate of the device
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 */
int
rs232_device_init(int deviceType, int port_number, int brate);

/**
 * Set the timeout value for opening the com port <br/>
 *
 * @param timeout should be set to greater than 0 in seconds, otherwise there will be no timeout for opening the com port
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 */
void
set_open_com_port_timeout(int timeout);

/**
 * Sets the current device to talk to <br/>
 * The connect status can be checked by device_isConnected(). <br/>
 * Note: the file "NEO2_Devices.xml" is required for NEO 2 readers
 * @param deviceType Device to connect to
 * @code
 * enum DEVICE_TYPE {
 *     IDT_DEVICE_UNKNOWN=0,
 *     IDT_DEVICE_AUGUSTA_HID,
 *     IDT_DEVICE_AUGUSTA_KB,
 *     IDT_DEVICE_AUGUSTA_S_HID,
 *     IDT_DEVICE_AUGUSTA_S_KB,
 *     IDT_DEVICE_AUGUSTA_S_TTK_HID,
 *     IDT_DEVICE_SPECTRUM_PRO,
 *     IDT_DEVICE_MINISMART_II,
 *     IDT_DEVICE_L80,
 *     IDT_DEVICE_L100,
 *     IDT_DEVICE_UNIPAY,
 *     IDT_DEVICE_UNIPAY_I_V,
 *     IDT_DEVICE_VP3300_AJ,
 *     IDT_DEVICE_KIOSK_III,
 *     IDT_DEVICE_KIOSK_III_S,
 *     IDT_DEVICE_PIP_READER,
 *     IDT_DEVICE_VENDI,
 *     IDT_DEVICE_VP3300_USB,
 *     IDT_DEVICE_UNIPAY_I_V_TTK,
 *     IDT_DEVICE_VP3300_BT,
 *     IDT_DEVICE_VP8800,
 *     IDT_DEVICE_SREDKEY2_HID,
 *     IDT_DEVICE_SREDKEY2_KB,
 *     IDT_DEVICE_NEO2,
 *     IDT_DEVICE_MINISMART_II_COM = IDT_DEVICE_NEO2+5,
 *     IDT_DEVICE_SPECTRUM_PRO_COM,
 *     IDT_DEVICE_KIOSK_III_COM,
 *     IDT_DEVICE_KIOSK_III_S_COM,
 *     IDT_DEVICE_PIP_READER_COM,
 *     IDT_DEVICE_VP3300_COM,
 *     IDT_DEVICE_NEO2_COM,
 *     IDT_DEVICE_MAX_DEVICES = IDT_DEVICE_NEO2_COM+5
 * };
 * @endcode
 * @return RETURN_CODE:    1: success, 0: failed
 */
int
device_setCurrentDevice(int deviceType);

/**
 * Close the device <br/>
 *
 * @return RETURN_CODE:  0: success, 0x0A: failed
 */
int
device_close();

/**
 * Review the return code description.<br/>
 * @param returnCode  the response result.
 * @param description
 * @retval the string for description of response result
 *
 * - 0: "no error, beginning task";
 * - 1: "no response from reader";
 * - 2: "invalid response data";
 * - 3: "time out for task or CMD";
 * - 4: "wrong parameter";
 * - 5: "SDK is doing MSR or ICC task";
 * - 6: "SDK is doing PINPad task";
 * - 7: "SDK is doing CTLS task";
 * - 8: "SDK is doing EMV task";
 * - 9: "SDK is doing Other task";
 * - 10: "err response or data";
 * - 11: "no reader attached";
 * - 12: "mono audio is enabled";
 * - 13: "did connection";
 * - 14: "audio volume is too low";
 * - 15: "task or CMD be canceled";
 * - 16: "UF wrong string format";
 * - 17: "UF file not found";
 * - 18: "UF wrong file format";
 * - 19: "Attempt to contact online host failed";
 * - 20: "Attempt to perform RKI failed";
 * - 22: "Buffer size is not enough";
 * - 0X300: "Key Type(TDES) of Session Key is not same as the related
 *           Master Key.";
 * - 0X400: "Related Key was not loaded.";
 * - 0X500: "Key Same.";
 * - 0X501: "Key is all zero";
 * - 0X502: "TR-31 format error";
 * - 0X702: "PAN is Error Key.";
 * - 0X705: "No Internal MSR PAN (or Internal MSR PAN is erased timeout)";
 * - 0X0C01: "Incorrect Frame Tag";
 * - 0X0C02: "Incorrect Frame Type";
 * - 0X0C03: "Unknown Frame Type";
 * - 0X0C04: "Unknown Command";
 * - 0X0C05: "Unknown Sub-Command";
 * - 0X0C06: "CRC Error";
 * - 0X0C07: "Failed";
 * - 0X0C08: "Timeout";
 * - 0X0C0A: "Incorrect Parameter";
 * - 0X0C0B: "Command Not Supported";
 * - 0X0C0C: "Sub-Command Not Supported";
 * - 0X0C0D: "Parameter Not Supported / Status Abort Command";
 * - 0X0C0F: "Sub-Command Not Allowed";
 * - 0X0D01: "Incorrect Header Tag";
 * - 0X0D02: "Unknown Command";
 * - 0X0D03: "Unknown Sub-Command";
 * - 0X0D04: "CRC Error in Frame";
 * - 0X0D05: "Incorrect Parameter";
 * - 0X0D06: "Parameter Not Supported";
 * - 0X0D07: "Mal-formatted Data";
 * - 0X0D08: "Timeout";
 * - 0X0D0A: "Failed / NACK";
 * - 0X0D0B: "Command not Allowed";
 * - 0X0D0C: "Sub-Command not Allowed";
 * - 0X0D0D: "Buffer Overflow (Data Length too large for reader buffer)";
 * - 0X0D0E: "User Interface Event";
 * - 0X0D11: "Communication type not supported, VT-1, burst, etc.";
 * - 0X0D12: "Secure interface is not functional or is in an intermediate state.";
 * - 0X0D13: "Data field is not mod 8";
 * - 0X0D14: "Pad  - 0X80 not found where expected";
 * - 0X0D15: "Specified key type is invalid";
 * - 0X0D1: "Could not retrieve key from the SAM(InitSecureComm)";
 * - 0X0D17: "Hash code problem";
 * - 0X0D18: "Could not store the key into the SAM(InstallKey)";
 * - 0X0D19: "Frame is too large";
 * - 0X0D1A: "Unit powered up in authentication state but POS must resend the InitSecureComm command";
 * - 0X0D1B: "The EEPROM may not be initialized because SecCommInterface does not make sense";
 * - 0X0D1C: "Problem encoding APDU";
 * - 0X0D20: "Unsupported Index(ILM) SAM Transceiver error - problem communicating with the SAM(Key Mgr)";
 * - 0X0D2: "Unexpected Sequence Counter in multiple frames for single bitmap(ILM) Length error in data returned from the SAM(Key Mgr)";
 * - 0X0D22: "Improper bit map(ILM)";
 * - 0X0D23: "Request Online Authorization";
 * - 0X0D24: "ViVOCard3 raw data read successful";
 * - 0X0D25: "Message index not available(ILM) ViVOcomm activate transaction card type(ViVOcomm)";
 * - 0X0D26: "Version Information Mismatch(ILM)";
 * - 0X0D27: "Not sending commands in correct index message index(ILM)";
 * - 0X0D28: "Time out or next expected message not received(ILM)";
 * - 0X0D29: "ILM languages not available for viewing(ILM)";
 * - 0X0D2A: "Other language not supported(ILM)";
 * - 0X0D41: "Unknown Error from SAM";
 * - 0X0D42: "Invalid data detected by SAM";
 * - 0X0D43: "Incomplete data detected by SAM";
 * - 0X0D44: "Reserved";
 * - 0X0D45: "Invalid key hash algorithm";
 * - 0X0D46: "Invalid key encryption algorithm";
 * - 0X0D47: "Invalid modulus length";
 * - 0X0D48: "Invalid exponent";
 * - 0X0D49: "Key already exists";
 * - 0X0D4A: "No space for new RID";
 * - 0X0D4B: "Key not found";
 * - 0X0D4C: "Crypto not responding";
 * - 0X0D4D: "Crypto communication error";
 * - 0X0D4E: "Module-specific error for Key Manager";
 * - 0X0D4F: "All key slots are full (maximum number of keys has been installed)";
 * - 0X0D50: "Auto-Switch OK";
 * - 0X0D51: "Auto-Switch failed";
 * - 0X0D90: "Account DUKPT Key not exist";
 * - 0X0D91: "Account DUKPT Key KSN exausted";
 * - 0X0D00: "This Key had been loaded.";
 * - 0X0E00: "Base Time was loaded.";
 * - 0X0F00: "Encryption Or Decryption Failed.";
 * - 0X1000: "Battery Low Warning (It is High Priority Response while Battery is Low.)";
 * - 0X1800: "Send 'Cancel Command' after send 'Get Encrypted PIN' & 'Get Numeric' & 'Get Amount';
 * - 0X1900: "Press 'Cancel' key after send 'Get Encrypted PIN' & 'Get Numeric' & 'Get Amount';
 * - 0X30FF: "Security Chip is not connect";
 * - 0X3000: "Security Chip is deactivation & Device is In Removal Legally State.";
 * - 0X3101: "Security Chip is activation &  Device is In Removal Legally State.";
 * - 0X5500: "No Admin DUKPT Key.";
 * - 0X5501: "Admin  DUKPT Key STOP.";
 * - 0X5502: "Admin DUKPT Key KSN is Error.";
 * - 0X5503: "Get Authentication Code1 Failed.";
 * - 0X5504: "Validate Authentication Code Error.";
 * - 0X5505: "Encrypt or Decrypt data failed.";
 * - 0X5506: "Not Support the New Key Type.";
 * - 0X5507: "New Key Index is Error.";
 * - 0X5508: "Step Error.";
 * - 0X5509: "KSN Error";
 * - 0X550A: "MAC Error.";
 * - 0X550B: "Key Usage Error.";
 * - 0X550C: "Mode Of Use Error.";
 * - 0X550F: "Other Error.";
 * - 0X6000: "Save or Config Failed / Or Read Config Error.";
 * - 0X6200: "No Serial Number.";
 * - 0X6900: "Invalid Command - Protocol is right, but task ID is invalid.";
 * - 0X6A01: "Unsupported Command - Protocol and task ID are right, but command is invalid - In this State";
 * - 0X6A00: "Unsupported Command - Protocol and task ID are right, but command is invalid.";
 * - 0X6B00: "Unknown parameter in command - Protocol task ID and command are right, but parameter is invalid.";
 * - 0X6C00: "Unknown parameter in command - Protocol task ID and command are right, but length is out of the requirement.";
 * - 0X7200: "Device is suspend (MKSK suspend or press password suspend).";
 * - 0X7300: "PIN DUKPT is STOP (21 bit 1).";
 * - 0X7400: "Device is Busy.";
 * - 0XE100: "Can not enter sleep mode";
 * - 0XE200: "File has existed";
 * - 0XE300: "File has not existed";
 * - 0XE313: "IO line low -- Card error after session start";
 * - 0XE400: "Open File Error";
 * - 0XE500: "SmartCard Error";
 * - 0XE600: "Get MSR Card data is error";
 * - 0XE700: "Command time out";
 * - 0XE800: "File read or write is error";
 * - 0XE900: "Active 1850 error!";
 * - 0XEA00: "Load bootloader error";
 * - 0XEF00: "Protocol Error- STX or ETX or check error.";
 * - 0XEB00: "Picture is not exist";
 * - 0X2C02: "No Microprocessor ICC seated";
 * - 0X2C06: "no card seated to request ATR";
 * - 0X2D01: "Card Not Supported, ";
 * - 0X2D03: "Card Not Supported, wants CRC";
 * - 0X690D: "Command not supported on reader without ICC support";
 * - 0X8100: "ICC error time out on power-up";
 * - 0X8200: "invalid TS character received - Wrong operation step";
 * - 0X8300: "Decode MSR Error";
 * - 0X8400: "TriMagII no Response";
 * - 0X8500: "No Swipe MSR Card";
 * - 0X8510: "No Financial Card";
 * - 0X8600: "Unsupported F, D, or combination of F and D";
 * - 0X8700: "protocol not supported EMV TD1 out of range";
 * - 0X8800: "power not at proper level";
 * - 0X8900: "ATR length too long";
 * - 0X8B01: "EMV invalid TA1 byte value";
 * - 0X8B02: "EMV TB1 required";
 * - 0X8B03: "EMV Unsupported TB1 only 00 allowed";
 * - 0X8B04: "EMV Card Error, invalid BWI or CWI";
 * - 0X8B06: "EMV TB2 not allowed in ATR";
 * - 0X8B07: "EMV TC2 out of range";
 * - 0X8B08: "EMV TC2 out of range";
 * - 0X8B09: "per EMV96 TA3 must be >  - 0XF";
 * - 0X8B10: "ICC error on power-up";
 * - 0X8B11: "EMV T=1 then TB3 required";
 * - 0X8B12: "Card Error, invalid BWI or CWI";
 * - 0X8B13: "Card Error, invalid BWI or CWI";
 * - 0X8B17: "EMV TC1/TB3 conflict-";
 * - 0X8B20: "EMV TD2 out of range must be T=1";
 * - 0X8C00: "TCK error";
 * - 0XA304: "connector has no voltage setting";
 * - 0XA305: "ICC error on power-up invalid (SBLK(IFSD) exchange";
 * - 0XE301: "ICC error after session start";
 * - 0XFF00: "Request to go online";
 * - 0XFF01: "EMV: Accept the offline transaction";
 * - 0XFF02: "EMV: Decline the offline transaction";
 * - 0XFF03: "EMV: Accept the online transaction";
 * - 0XFF04: "EMV: Decline the online transaction";
 * - 0XFF05: "EMV: Application may fallback to magstripe technology";
 * - 0XFF06: "EMV: ICC detected tah the conditions of use are not satisfied";
 * - 0XFF07: "EMV: ICC didn't accept transaction";
 * - 0XFF08: "EMV: Transaction was cancelled";
 * - 0XFF09: "EMV: Application was not selected by kernel or ICC format error or ICC missing data error";
 * - 0XFF0A: "EMV: Transaction is terminated";
 * - 0XFF0B: "EMV: Other EMV Error";
 * - 0XFFFF: "NO RESPONSE";
 * - 0XF002: "ICC communication timeout";
 * - 0XF003: "ICC communication Error";
 * - 0XF00F: "ICC Card Seated and Highest Priority, disable MSR work request";
 * - 0XF200: "AID List / Application Data is not exist";
 * - 0XF201: "Terminal Data is not exist";
 * - 0XF202: "TLV format is error";
 * - 0XF203: "AID List is full";
 * - 0XF204: "Any CA Key is not exist";
 * - 0XF205: "CA Key RID is not exist";
 * - 0XF206: "CA Key Index it not exist";
 * - 0XF207: "CA Key is full";
 * - 0XF208: "CA Key Hash Value is Error";
 * - 0XF209: "Transaction  format error";
 * - 0XF20A: "The command will not be processing";
 * - 0XF20B: "CRL is not exist";
 * - 0XF20C: "CRL number  exceed max number";
 * - 0XF20D: "Amount, Other Amount, Trasaction Type  are  missing";
 * - 0XF20E: "The Identification of algorithm is mistake";
 * - 0XF20F: "No Financial Card";
 * - 0XF210: "In Encrypt Result state, TLV total Length is greater than Max Length";
 * - 0X1001: "INVALID ARG";
 * - 0X1002: "FILE_OPEN_FAILED";
 * - 0X1003: "FILE OPERATION_FAILED";
 * - 0X2001: "MEMORY_NOT_ENOUGH";
 * - 0X3002: "SMARTCARD_FAIL";
 * - 0X3003: "SMARTCARD_INIT_FAILED";
 * - 0X3004: "FALLBACK_SITUATION";
 * - 0X3005: "SMARTCARD_ABSENT";
 * - 0X3006: "SMARTCARD_TIMEOUT";
 * - 0X3012: "EMV_RESULT_CODE_MSR_CARD_ERROR_FALLBACK";
 * - 0X5001: "EMV_PARSING_TAGS_FAILED";
 * - 0X5002: "EMV_DUPLICATE_CARD_DATA_ELEMENT";
 * - 0X5003: "EMV_DATA_FORMAT_INCORRECT";
 * - 0X5004: "EMV_NO_TERM_APP";
 * - 0X5005: "EMV_NO_MATCHING_APP";
 * - 0X5006: "EMV_MISSING_MANDATORY_OBJECT";
 * - 0X5007: "EMV_APP_SELECTION_RETRY";
 * - 0X5008: "EMV_GET_AMOUNT_ERROR";
 * - 0X5009: "EMV_CARD_REJECTED";
 * - 0X5010: "EMV_AIP_NOT_RECEIVED";
 * - 0X5011: "EMV_AFL_NOT_RECEIVED";
 * - 0X5012: "EMV_AFL_LEN_OUT_OF_RANGE";
 * - 0X5013: "EMV_SFI_OUT_OF_RANGE";
 * - 0X5014: "EMV_AFL_INCORRECT";
 * - 0X5015: "EMV_EXP_DATE_INCORRECT";
 * - 0X5016: "EMV_EFF_DATE_INCORRECT";
 * - 0X5017: "EMV_ISS_COD_TBL_OUT_OF_RANGE";
 * - 0X5018: "EMV_CRYPTOGRAM_TYPE_INCORRECT";
 * - 0X5019: "EMV_PSE_NOT_SUPPORTED_BY_CARD";
 * - 0X5020: "EMV_USER_SELECTED_LANGUAGE";
 * - 0X5021: "EMV_SERVICE_NOT_ALLOWED";
 * - 0X5022: "EMV_NO_TAG_FOUND";
 * - 0X5023: "EMV_CARD_BLOCKED";
 * - 0X5024: "EMV_LEN_INCORRECT";
 * - 0X5025: "CARD_COM_ERROR";
 * - 0X5026: "EMV_TSC_NOT_INCREASED";
 * - 0X5027: "EMV_HASH_INCORRECT";
 * - 0X5028: "EMV_NO_ARC";
 * - 0X5029: "EMV_INVALID_ARC";
 * - 0X5030: "EMV_NO_ONLINE_COMM";
 * - 0X5031: "TRAN_TYPE_INCORRECT";
 * - 0X5032: "EMV_APP_NO_SUPPORT";
 * - 0X5033: "EMV_APP_NOT_SELECT";
 * - 0X5034: "EMV_LANG_NOT_SELECT";
 * - 0X5035: "EMV_NO_TERM_DATA";
 * - 0X5039: "EMV_PIN_ENTRY_TIMEOUT";
 * - 0X6001: "CVM_TYPE_UNKNOWN";
 * - 0X6002: "CVM_AIP_NOT_SUPPORTED";
 * - 0X6003: "CVM_TAG_8E_MISSING";
 * - 0X6004: "CVM_TAG_8E_FORMAT_ERROR";
 * - 0X6005: "CVM_CODE_IS_NOT_SUPPORTED";
 * - 0X6006: "CVM_COND_CODE_IS_NOT_SUPPORTED";
 * - 0X6007: "NO_MORE_CVM";
 * - 0X6008: "PIN_BYPASSED_BEFORE";
 * - 0X7001: "PK_BUFFER_SIZE_TOO_BIG";
 * - 0X7002: "PK_FILE_WRITE_ERROR";
 * - 0X7003: "PK_HASH_ERROR";
 * - 0X8001: "NO_CARD_HOLDER_CONFIRMATION";
 * - 0X8002: "GET_ONLINE_PIN";
 * - 0XD000: "Data not exist";
 * - 0XD001: "Data access error";
 * - 0XD100: "RID not exist";
 * - 0XD101: "RID existed";
 * - 0XD102: "Index not exist";
 * - 0XD200: "Maximum exceeded";
 * - 0XD201: "Hash error";
 * - 0XD205: "System Busy";
 * - 0X0E01: "Unable to go online";
 * - 0X0E02: "Technical Issue";
 * - 0X0E03: "Declined";
 * - 0X0E04: "Issuer Referral transaction";
 * - 0X0F01: "Decline the online transaction";
 * - 0X0F02: "Request to go online";
 * - 0X0F03: "Transaction is terminated";
 * - 0X0F05: "Application was not selected by kernel or ICC format error or ICC missing data error";
 * - 0X0F07: "ICC didn't accept transaction";
 * - 0X0F0A: "Application may fallback to magstripe technology";
 * - 0X0F0C: "Transaction was cancelled";
 * - 0X0F0D: "Timeout";
 * - 0X0F0F: "Other EMV Error";
 * - 0X0F10: "Accept the offline transaction";
 * - 0X0F11: "Decline the offline transaction";
 * - 0X0F21: "ICC detected tah the conditions of use are not satisfied";
 * - 0X0F22: "No app were found on card matching terminal configuration";
 * - 0X0F23: "Terminal file does not exist";
 * - 0X0F24: "CAPK file does not exist";
 * - 0X0F25: "CRL Entry does not exist";
 * - 0X0FFE: "code when blocking is disabled";
 * - 0X0FFF: "code when command is not applicable on the selected device";
 * - 0XF005: "ICC Encrypted C-APDU Data Structure Length Error Or Format Error.";
 * - 0XBBE0: "CM100 Success";
 * - 0XBBE1: "CM100 Parameter Error";
 * - 0XBBE2: "CM100 Low Output Buffer";
 * - 0XBBE3: "CM100 Card Not Found";
 * - 0XBBE4: "CM100 Collision Card Exists";
 * - 0XBBE5: "CM100 Too Many Cards Exist";
 * - 0XBBE6: "CM100 Saved Data Does Not Exist";
 * - 0XBBE8: "CM100 No Data Available";
 * - 0XBBE9: "CM100 Invalid CID Returned";
 * - 0XBBEA: "CM100 Invalid Card Exists";
 * - 0XBBEC: "CM100 Command Unsupported";
 * - 0XBBED: "CM100 Error In Command Process";
 * - 0XBBEE: "CM100 Invalid Command";
 *
 * - 0X9031: "Unknown command";
 * - 0X9032: "Wrong parameter (such as the length of the command is incorrect)";
 *
 * - 0X9038: "Wait (the command couldnt be finished in BWT)";
 * - 0X9039: "Busy (a previously command has not been finished)";
 * - 0X903A: "Number of retries over limit";
 *
 * - 0X9040: "Invalid Manufacturing system data";
 * - 0X9041: "Not authenticated";
 * - 0X9042: "Invalid Master DUKPT Key";
 * - 0X9043: "Invalid MAC Key";
 * - 0X9044: "Reserved for future use";
 * - 0X9045: "Reserved for future use";
 * - 0X9046: "Invalid DATA DUKPT Key";
 * - 0X9047: "Invalid PIN Pairing DUKPT Key";
 * - 0X9048: "Invalid DATA Pairing DUKPT Key";
 * - 0X9049: "No nonce generated";
 * - 0X9949: "No GUID available.  Perform getVersion first.";
 * - 0X9950: "MAC Calculation unsuccessful. Check BDK value.";
 *
 * - 0X904A: "Not ready";
 * - 0X904B: "Not MAC data";
 *
 * - 0X9050: "Invalid Certificate";
 * - 0X9051: "Duplicate key detected";
 * - 0X9052: "AT checks failed";
 * - 0X9053: "TR34 checks failed";
 * - 0X9054: "TR31 checks failed";
 * - 0X9055: "MAC checks failed";
 * - 0X9056: "Firmware download failed";
 *
 * - 0X9060: "Log is full";
 * - 0X9061: "Removal sensor unengaged";
 * - 0X9062: "Any hardware problems";
 *
 * - 0X9070: "ICC communication timeout";
 * - 0X9071: "ICC data error (such check sum error)";
 * - 0X9072: "Smart Card not powered up";
 */
void
device_getResponseCodeString(IN int returnCode, OUT char * despcrition);

/**
 * Review the return code description.<br/>
 * @param returnCode  the response result.
 * @param description
 * @retval the string for description of response result
 *
 * - 0: "no error, beginning task";
 * - 1: "no response from reader";
 * - 2: "invalid response data";
 *
 * - 01: " Incorrect Header Tag";
 * - 02: " Unknown Command";
 * - 03: " Unknown Sub-Command";
 * - 04: " CRC Error in Frame";
 * - 05: " Incorrect Parameter";
 * - 06: " Parameter Not Supported";
 * - 07: " Mal-formatted Data";
 * - 08: " Timeout";
 * - 0A: " Failed / NACK";
 * - 0B: " Command not Allowed";
 * - 0C: " Sub-Command not Allowed";
 * - 0D: " Buffer Overflow (Data Length too large for reader buffer)";
 * - 0E: " User Interface Event";
 * - 10: " Need clear firmware(apply in boot loader only)";
 * - 11: " Communication type not supported, VT-1, burst, etc. Need encrypted firmware (apply in boot loader only)";
 * - 12: " Secure interface is not functional or is in an intermediate state.";
 * - 13: " Data field is not mod 8";
 * - 14: " Pad 0x80 not found where expected";
 * - 15: " Specified key type is invalid";
 * - 16: " Could not retrieve key from the SAM (InitSecureComm)";
 * - 17: " Hash code problem";
 * - 18: " Could not store the key into the SAM (InstallKey)";
 * - 19: " Frame is too large";
 * - 1A: " Unit powered up in authentication state but POS must resend the InitSecureComm command";
 * - 1B: " The EEPROM may not be initialized because SecCommInterface does not make sense";
 * - 1C: " Problem encoding APDU Module-Specific Status Codes ";
 * - 20: " Unsupported Index (ILM) SAM Transceiver error - problem communicating with the SAM (Key Mgr)";
 * - 21: " Unexpected Sequence Counter in multiple frames for single bitmap (ILM)Length error in data returned from the SAM (Key Mgr)
 * - 22: " Improper bit map (ILM)";
 * - 23: " Request Online Authorization";
 * - 24: " ViVOCard3 raw data read successful";
 * - 25: " Message index not available (ILM) ViVOcomm activate transaction card type (ViVOcomm)";
 * - 26: " Version Information Mismatch (ILM)";
 * - 27: " Not sending commands in correct index message index (ILM)";
 * - 28: " Time out or next expected message not received (ILM)";
 * - 29: " ILM languages not available for viewing (ILM)";
 * - 2A: " Other language not supported (ILM)";
 * - 41: " from 41 to 4F, Module-specific errors for Key Manager";
 *
 * - 50: " Auto-Switch OK";
 * - 51: " Auto-Switch failed";
 * - 70: " Antenna Error 80h Use another card";
 * - 81: " Insert or swipe card";
 * - 90: " Data encryption Key does not exist";
 * - 91: " Data encryption Key KSN exhausted";
 */
void
device_getIDGStatusCodeString(IN int returnCode, OUT char * despcrition);

/**
 * Check the device conntected status
 * @return DEVICE_DISCONNECT=0, or DEVICE_CONNECTED = 1
 */
int
device_isConnected();

/**
 * Check if the device is attached to the USB port
 * The function device_init() must be called before this function.
 * @param deviceType, the device type of the USB device
 * @return 1 if the device is attached, or 0 if the device is not attached
 */
int
device_isAttached(int deviceType);

/**
 * Start Transaction Request
 *
 * Authorizes the transaction for an MSR/CTLS/ICC card
 *
 * The tags will be returned in the callback routine.
 *
 * @param amount Transaction amount value (tag value 9F02)
 *        - SEE IMPORTANT NOTE BELOW
 * @param amtOther Other amount value, if any (tag value 9F03)
 *        - SEE IMPORTANT NOTE BELOW
 * @param type Transaction type (tag value 9C).
 * @param timeout Timeout value in seconds.
 * @param tags Any other tags to be included in the request.  Passed
 * as TLV.  Example, tag 9F02 with amount 0x000000000100 would be
 * 0x9F0206000000000100.  If tags 9F02 (amount), 9F03 (other amount), or
 * 9C (transaction type) are included, they will take priority over
 * these values supplied as individual parameters to this method.
 *
 * @param tagsLen The length of tags data buffer.
 *
 * >>>>>IMPORTANT: parameters for amount and amtOther MUST BE PASSED
 *      AS A DOUBLE VALUE WITH DECIMAL POINT.  Example, do not pass 1,
 *      but instead pass 1.0 or 1.00. Otherwise, results will be
 *      unpredictable
 *
 *
 *
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 * Note: if auto poll is on, it will returm the error
 * IDG_P2_STATUS_CODE_COMMAND_NOT_ALLOWED
 *
 * NOTE ON APPLEPAY VAS:
 * To enable ApplePay VAS, first a merchant record must be defined in one of
 * the six available index positions (1-6) using device_setMerchantRecord,
 * then container tag FFEE06 must be sent as part of the additional tags
 * parameter of device_startTransaction.  Tag FFEE06 must contain tag 9F26
 * and 9F22, and can optionanally contain tags 9F2B and DF01.
 * Example FFEE06189F220201009F2604000000009F2B050100000000DF010101
 * 9F22 = two bytes = ApplePay Terminal Applicaiton Version Number.
 *        Hard defined as 0100 for now. (required)
 * 9F26 = four bytes = ApplePay Terminal Capabilities Information (required)
 *  - Byte 1 = RFU
 *  - Byte 2 = Terminal Type
 *  - - Bit 8 = VAS Support    (1=on, 0 = off)
 *  - - Bit 7 = Touch ID Required  (1=on, 0 = off)
 *  - - Bit 6 = RFU
 *  - - Bit 5 = RFU
 *  - - Bit 1, 2, 3, 4
 *  - - - 0 = Payment Terminal
 *  - - - 1 = Transit Terminal
 *  - - - 2 = Access Terminal
 *  - - - 3 = Wireless Handoff Terminal
 *  - - - 4 = App Handoff Terminal
 *  - - - 15 = Other Terminal
 *  - Byte 3 = RFU
 *  - Byte 4 = Terminal Mode
 *  - - 0 = ApplePay VAS OR ApplePay
 *  - - 1 = ApplePay VAS AND ApplePay
 *  - - 2 = ApplePay VAS ONLY
 *  - - 3 = ApplePay ONLY
 *  9F2B = 5 bytes = ApplePay VAS Filter.  Each byte filters for that
 *         specific merchant index  (optional)
 *  DF01 = 1 byte = ApplePay VAS Protocol.  (optional)
 *  - - Bit 1 : 1 = URL VAS, 0 = Full VAS
 *  - - Bit 2 : 1 = VAS Beeps, 0 = No VAS Beeps
 *  - - Bit 3 : 1 = Silent Comm Error, 2 = EMEA Comm Error
 *  - - Bit 4-8 : RFU
 *
 */
int
device_startTransaction(IN double amount,
  IN double                       amtOther,
  IN int                          type,
  IN const int                    _timeout,
  IN BYTE *                       tags,
  IN int                          tagsLen);

/**
 * Start Loyalty Transaction Request
 *       Only for VP6800
 *
 * Authorizes the transaction for an MSR/ICC card
 *
 * The tags will be returned in the callback routine.
 *
 * @param amount Transaction amount value (tag value 9F02)
 *        - SEE IMPORTANT NOTE BELOW
 * @param amtOther Other amount value, if any (tag value 9F03)
 *        - SEE IMPORTANT NOTE BELOW
 * @param type Transaction type (tag value 9C).
 * @param timeout Timeout value in seconds.
 * @param tags Any other tags to be included in the request.  Passed
 * as TLV.  Example, tag 9F02 with amount 0x000000000100 would be
 * 0x9F0206000000000100.  If tags 9F02 (amount), 9F03 (other amount), or
 * 9C (transaction type) are included, they will take priority over
 * these values supplied as individual parameters to this method.
 *
 * @param tagsLen The length of tags data buffer.
 *
 * >>>>>IMPORTANT: parameters for amount and amtOther MUST BE PASSED
 *      AS A DOUBLE VALUE WITH DECIMAL POINT.  Example, do not pass 1,
 *      but instead pass 1.0 or 1.00. Otherwise, results will be
 *      unpredictable
 *
 *
 * @param cardType Set available card to accept. 0 = MSR only. 1 = MSR and ICC.
 *
 * @param iccReadType In case of ICC reading, this is how to behave.
 *      0 = Same as device_startTransaction
 *      1 = When reading ICC, read DF4F(JIS2EquivalentData) in ReadRecord.
 *          If the user swipes an IC card, the reader will ask for using ICC
 *      3 = When reading ICC, read DF4F(JIS2EquivalentData) in ReadRecord.
 *          If the user swipes an IC card, the reader will not ask for using ICC and output MSR data directly
 *
 *
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 * Note: if auto poll is on, it will return the error
 * IDG_P2_STATUS_CODE_COMMAND_NOT_ALLOWED
 *
 * NOTE ON APPLEPAY VAS:
 * To enable ApplePay VAS, first a merchant record must be defined in one of
 * the six available index positions (1-6) using device_setMerchantRecord,
 * then container tag FFEE06 must be sent as part of the additional tags
 * parameter of device_startTransaction.  Tag FFEE06 must contain tag 9F26
 * and 9F22, and can optionanally contain tags 9F2B and DF01.
 * Example FFEE06189F220201009F2604000000009F2B050100000000DF010101
 * 9F22 = two bytes = ApplePay Terminal Applicaiton Version Number.
 *        Hard defined as 0100 for now. (required)
 * 9F26 = four bytes = ApplePay Terminal Capabilities Information (required)
 *  - Byte 1 = RFU
 *  - Byte 2 = Terminal Type
 *  - - Bit 8 = VAS Support    (1=on, 0 = off)
 *  - - Bit 7 = Touch ID Required  (1=on, 0 = off)
 *  - - Bit 6 = RFU
 *  - - Bit 5 = RFU
 *  - - Bit 1, 2, 3, 4
 *  - - - 0 = Payment Terminal
 *  - - - 1 = Transit Terminal
 *  - - - 2 = Access Terminal
 *  - - - 3 = Wireless Handoff Terminal
 *  - - - 4 = App Handoff Terminal
 *  - - - 15 = Other Terminal
 *  - Byte 3 = RFU
 *  - Byte 4 = Terminal Mode
 *  - - 0 = ApplePay VAS OR ApplePay
 *  - - 1 = ApplePay VAS AND ApplePay
 *  - - 2 = ApplePay VAS ONLY
 *  - - 3 = ApplePay ONLY
 *  9F2B = 5 bytes = ApplePay VAS Filter.  Each byte filters for that
 *         specific merchant index  (optional)
 *  DF01 = 1 byte = ApplePay VAS Protocol.  (optional)
 *  - - Bit 1 : 1 = URL VAS, 0 = Full VAS
 *  - - Bit 2 : 1 = VAS Beeps, 0 = No VAS Beeps
 *  - - Bit 3 : 1 = Silent Comm Error, 2 = EMEA Comm Error
 *  - - Bit 4-8 : RFU
 *
 */
int
loyalty_startTransaction(IN double amount, IN double amtOther, IN int type, IN const int _timeout, IN BYTE * tags,
  IN int tagsLen,
  IN const int cardType, IN const int iccReadType);

/**
 * Sets the transaction exponent to be used with device_startTransaction.  Default value is 2
 * @param exponent, The exponent to use when calling device_startTransaction
 */
void
device_setTransactionExponent(int exponent);

/**
 * Start Transaction Request
 *
 * Authorizes the transaction for an MSR/CTLS/ICC card
 *
 * The tags will be returned in the callback routine.
 *
 * @param timeout Timeout value in seconds.
 * @param tags The tags to be included in the request.  Passed as a TLV.
 *   Example, tag 9F02 with amount 0x000000000100 would be 0x9F0206000000000100
 * Be sure to include 9F02 (amount)and9C (transaction type).
 *
 * @param tagsLen The length of tags data buffer.
 *
 * >>>>>IMPORTANT: parameters for amount and amtOther MUST BE PASSED
 * AS A DOUBLE VALUE WITH DECIMAL POINT.  Example, do not pass 1, but
 * instead pass 1.0 or 1.00. Otherwise, results will be unpredictable
 *
 *
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 * Note: if auto poll is on, it will returm the error
 *       IDG_P2_STATUS_CODE_COMMAND_NOT_ALLOWED
 *
 * NOTE ON APPLEPAY VAS:
 * To enable ApplePay VAS, first a merchant record must be defined in
 * one of the six available index positions (1-6) using
 * device_setMerchantRecord, then container tag FFEE06 must be sent as
 * part of the additional tags parameter of device_startTransaction.
 * Tag FFEE06 must contain tag 9F26 and 9F22, and can optionanally
 * contain tags 9F2B and DF01.  Example
 * FFEE06189F220201009F2604000000009F2B050100000000DF010101
 *
 * 9F22 = two bytes = ApplePay Terminal Applicaiton Version Number.
 *        Hard defined as 0100 for now. (required)
 * 9F26 = four bytes = ApplePay Terminal Capabilities Information (required)
 *  - Byte 1 = RFU
 *  - Byte 2 = Terminal Type
 *  - - Bit 8 = VAS Support    (1=on, 0 = off)
 *  - - Bit 7 = Touch ID Required  (1=on, 0 = off)
 *  - - Bit 6 = RFU
 *  - - Bit 5 = RFU
 *  - - Bit 1, 2, 3, 4
 *  - - - 0 = Payment Terminal
 *  - - - 1 = Transit Terminal
 *  - - - 2 = Access Terminal
 *  - - - 3 = Wireless Handoff Terminal
 *  - - - 4 = App Handoff Terminal
 *  - - - 15 = Other Terminal
 *  - Byte 3 = RFU
 *  - Byte 4 = Terminal Mode
 *  - - 0 = ApplePay VAS OR ApplePay
 *  - - 1 = ApplePay VAS AND ApplePay
 *  - - 2 = ApplePay VAS ONLY
 *  - - 3 = ApplePay ONLY
 *  9F2B = 5 bytes = ApplePay VAS Filter.
 *         Each byte filters for that specific merchant index  (optional)
 *  DF01 = 1 byte = ApplePay VAS Protocol.  (optional)
 *  - - Bit 1 : 1 = URL VAS, 0 = Full VAS
 *  - - Bit 2 : 1 = VAS Beeps, 0 = No VAS Beeps
 *  - - Bit 3 : 1 = Silent Comm Error, 2 = EMEA Comm Error
 *  - - Bit 4-8 : RFU
 *
 */
int
device_activateTransaction(IN const int _timeout,
  IN BYTE *                             tags,
  IN int                                tagsLen);

/**
 * Cancel Transaction
 *
 * Cancels the currently executing transaction.
 *
 *
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
device_cancelTransaction();

/**
 * Cancel Loyalty Transaction
 *      Only for VP6800
 *
 * Cancels the currently executing transaction.
 *
 *
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
loyalty_cancelTransaction();

/**
 * Set Cancel Transaction Mode
 *
 * Set the cancel transaction mode to be with or without LCD message
 *
 *
 * @param mode 0: With LCD message 1: Without LCD message
 * @return success or error code.  1: Success, 0: Failed
 *
 */
int
device_setCancelTransactionMode(int mode);

/**
 * Cancel Transaction Silent
 *
 * Cancel transaction with or without showing the LCD message
 *
 *
 * @param enable 0: With LCD message 1: Without LCD message
 * @return success or error code.  Values can be parsed with device_getIDGStatusCodeString
 *
 */
int
device_cancelTransactionSilent(int enable);

/**
 * Cancel Loyalty Transaction Silent
 *      Only for VP6800
 *
 * Cancel transaction with or without showing the LCD message
 *
 *
 * @param enable 0: With LCD message 1: Without LCD message
 * @return success or error code.  Values can be parsed with device_getIDGStatusCodeString
 *
 */
int
loyalty_cancelTransactionSilent(int enable);

/**
 * Drive Free Space
 * This command returns the free and used disk space on the flash drive.
 * @param free Free bytes available on device
 * @param used Used bytes on on device
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
device_getDriveFreeSpace(OUT int * free,
  OUT int *                        used);

/**
 * List Directory
 *  This command retrieves a directory listing of user
 *  accessible files from the reader.
 * @param directoryName Directory Name.  If null, root directory is listed
 * @param directoryNameLen Directory Name Length.  If null, root directory
 *        is listed
 * @param recursive Included sub-directories
 * @param onSD 0: use internal memory, 1: use SD card
 * @directory The returned directory information
 * @directoryLen The returned directory information length
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
device_listDirectory(IN char * directoryName,
  IN int                       directoryNameLen,
  IN int                       recursive,
  IN int                       onSD,
  OUT char *                   directory,
  IN_OUT int *                 directoryLen);

/**
 * Create Directory
 *  This command adds a subdirectory to the indicated path.
 * @param directoryName Directory Name.  The data for this command is
 *  ASCII string with the complete path and directory name you want to create.
 *  You do not need to specify the root directory. Indicate subdirectories
 *  with a forward slash (/).
 * @param directoryNameLen Directory Name Length.
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
device_createDirectory(IN char * directoryName,
  IN int                         directoryNameLen);

/**
 * Delete Directory
 *  This command deletes an empty directory.  For NEO 2 devices, it will delete the directory even the directory is not empty.
 * @param dirName Complete path of the directory you want to delete.
 *   You do not need to specify the root directory. Indicate subdirectories with a forward slash (/).
 *   For NEO 2 devices, to delete the root directory, simply pass "" with 0 for dirNameLen.
 * @param dirNameLen Directory Name Length.
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
device_deleteDirectory(IN char * dirName,
  IN int                         dirNameLen);

/**
 * Transfer File
 *  This command transfers a data file to the reader.
 * @param fileName Filename.  The data for this command is a ASCII string with
 *   the complete path and file name you want to create. You do not need to
 *   specify the root directory. Indicate subdirectories with a forward slash (/)
 * @param filenameLen File Name Length.
 * @param file The data file.
 * @param fileLen File Length.
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
device_transferFile(IN char * fileName,
  IN int                      fileNameLen,
  IN BYTE *                   file,
  IN int                      fileLen);

/**
 * Delete File
 *  This command deletes a file or group of files.
 * @param filename Complete path and file name of the file you want to delete.
 *   You do not need to specify the root directory. Indicate subdirectories
 *   with a forward slash (/).
 * @param filenameLen File Name Length.
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
device_deleteFile(IN char * fileName, IN int fileNameLen);

/**
 * Query File
 *  This command checks if the specified file exists in NAND Flash..
 * @param directoryName Directory name string.  No longer than 32 bytes.  ASCII string, terminated by 0x00.
 * @param directoryNameLen Directory Name Length.
 * @param fileName File name string.  No longer than 32 bytes.  ASCII string, terminated by 0x00.
 * @param fileNameLen File Name Length.
 * @param isExist File exists: 1, File not exists 0.
 * @param timeStamp Latest time stamp of the file.  6 bytes BCD code if the file exists.
 * @param timeStampLen Length of timeStamp.  6 if the file exists, 0 if the file does not exist.
 * @param fileSize Zero-terminated ASCII string of the file size.
 * @param fileSizeLen Length of filesSize.
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
device_queryFile(IN char * directoryName, IN int directoryNameLen, IN char * fileName, IN int fileNameLen,
  OUT int * isExist, OUT BYTE * timeStamp, IN_OUT int * timeStampLen, OUT char * fileSize, IN_OUT int * fileSizeLen);

/**
 * Read Out File from SD Card
 *  This command retrieves a file from the SD card of the reader.
 * @param directoryName Directory name string.  No longer than 32 bytes.  ASCII string, terminated by 0x00.
 * @param directoryNameLen Directory Name Length.
 * @param fileName File name string.  No longer than 32 bytes.  ASCII string, terminated by 0x00.
 * @param fileNameLen File Name Length.
 * @param startingOffset Starting offset in the file to retrieve
 * @param numBytes Number of bytes of file data to retrieve
 * @param fileData  the file  data read from the SD card
 * @param fileDataLen Length of fileData.
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
device_readFileFromSD(IN char * directoryName, IN int directoryNameLen, IN char * fileName, IN int fileNameLen,
  IN int startingOffset, IN int numBytes, OUT BYTE * fileData, IN_OUT int * fileDataLen);

/**
 * Start Listen Notifications
 *  This function enables Card Status and Front Switch notifications.
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
device_startListenNotifications();

/**
 * Stop Listen Notifications
 *  This function disables Card Status and Front Switch notifications.
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
device_stopListenNotifications();

/**
 * DEPRECATED : please use device_getFirmwareVersion_Len(OUT char* firmwareVersion, IN_OUT int *firmwareVersionLen)
 *
 * Polls device for Firmware Version
 *
 * @param firmwareVersion Response returned of Firmware Version; needs to have at least 128 bytes of memory
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 *
 */
int
device_getFirmwareVersion(OUT char * firmwareVersion);

/**
 * Polls device for Firmware Version
 *
 * @param firmwareVersion Response returned of Firmware Version
 * @param firmwareVersionLen Length of Firmware Version
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 *
 */
int
device_getFirmwareVersion_Len(OUT char * firmwareVersion, IN_OUT int * firmwareVersionLen);

/**
 * Polls device for Device Tree Version
 *
 * @param deviceTreeVersion Response returned of Device Tree Version
 * @param deviceTreeVersionLen Length of Device Tree Version
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 *
 */
int
device_getDeviceTreeVersion(OUT char * deviceTreeVersion, IN_OUT int * deviceTreeVersionLen);

/**
 * DEPRECATED : please use device_getDateTime_Len(OUT BYTE* dateTime, IN_OUT int *dateTimeLen)
 *
 * Polls device for Date and Time
 *
 * @param dateTime Response returned of Date and Time; needs to have at least 6 bytes of memory
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 *
 */
int
device_getDateTime(OUT BYTE * dateTime);

/**
 * Polls device for Date and Time
 *
 * @param dateTime Response returned of Date and Time
 * @param dateTime Length of Date and Time
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 *
 */
int
device_getDateTime_Len(OUT BYTE * dateTime, IN_OUT int * dateTimeLen);

/**
 * Control MSR LED - AUGUSTA
 *
 * Controls the LED for the MSR
 *
 *
 * @param indexLED For Augusta, must be set to 1 (MSR LED)
 * @param control LED Status:
 *  - 00: OFF
 *  - 01: RED Solid
 *  - 02: RED Blink
 *  - 11: GREEN Solid
 *  - 12: GREEN Blink
 *  - 21: BLUE Solid
 *  - 22: BLUE Blink
 * @param intervalOn Blink interval ON, in ms    (Range 200 - 2000)
 * @param intervalOff Blink interval OFF, in ms  (Range 200 - 2000)
 *
 *
 * @return RETURN_CODE: Values can be parsed with device_getResponseCodeString
 *
 * intervalOn = 500, int intervalOff = 500
 */
int
device_controlLED(byte indexLED,
  byte                 control,
  int                  intervalOn,
  int                  intervalOff);

/**
 * Control ICC LED - AUGUSTA
 *
 * Controls the LED for the ICC card slot
 *
 *
 * @param controlMode 0 = off, 1 = solid, 2 = blink
 * @param interval Blink interval, in ms  (500 = 500 ms)
 *
 * @return RETURN_CODE: Values can be parsed with device_getResponseCodeString
 */
int
device_controlLED_ICC(int controlMode,
  int                     interval);

/**
 * Control the MSR LED - AUGUSTA
 *
 * Controls the MSR / ICC LED
 * This API not recommended to control ICC LED
 * @param control
 *     - 0x00 = off,
 *     - 0x01 = RED Solid,
 *     - 0x02 = RED Blink,
 *     - 0x11 = GREEN Solid,
 *     - 0x12 = GREEN Blink,
 *     - 0x21 = BLUE Solid,
 *     - 0x22 = BLUE Blink,
 * @param intervalOn Blink interval on time last, in ms
 * (500 = 500 ms, valid from 200 to 2000)
 * @param intervalOff Blink interval off time last, in ms
 * (500 = 500 ms, valid from 200 to 2000)
 *
 *
 * @return RETURN_CODE: Values can be parsed with device_getResponseCodeString
 *
 * int intervalOn = 500, int intervalOff = 500)
 */
int
device_controlLED_MSR(byte control,
  int                      intervalOn,
  int                      intervalOff);

/**
 * Control Beep - AUGUSTA
 *
 * Controls the Beeper
 *
 *
 * @param index For Augusta, must be set to 1 (only one beeper)
 * @param frequency Frequency, range 1000-20000 (suggest minimum 3000)
 * @param duration Duration, in milliseconds (range 1 - 65525)
 *
 * @return RETURN_CODE: Values can be parsed with device_getResponseCodeString
 */
int
device_controlBeep(int index,
  int                  frequency,
  int                  duration);

/**
 * Get DRS Status
 *
 * Gets the status of DRS(Destructive Reset).
 *
 * @param codeDRS
 *  the data format is [DRS SourceBlk Number] [SourceBlk1] ... [SourceBlkN]
 *  [DRS SourceBlk Number] is 2 bytes, format is NumL NumH. It is Number of [SourceBlkX]
 *  [SourceBlkX] is n bytes, Format is [SourceID] [SourceLen] [SourceData]
 *  [SourceID] is 1 byte
 *  [SourceLen] is 1 byte, it is length of [SourceData]
 *
 * [SourceID]    [SourceLen]  [SourceData]
 *    00                1     01 - Application Error
 *    01                1     01 - Application Error
 *    02                1     0x01 - EMV L2 Configuration Check Value Error
 *                            0x02 - Future Key Check Value Error
 *    10                1     01    - Battery Error
 *    11                1     Bit 0 - Tamper Switch 1 (0-No, 1-Error)
 *                            Bit 1 - Tamper Switch 2 (0-No, 1-Error)
 *                            Bit 2 - Tamper Switch 3 (0-No, 1-Error)
 *                            Bit 3 - Tamper Switch 4 (0-No, 1-Error)
 *                            Bit 4 - Tamper Switch 5 (0-No, 1-Error)
 *                            Bit 5 - Tamper Switch 6 (0-No, 1-Error)
 *
 *    12                1     01  - TemperatureHigh or Low
 *    13                1     01  - Voltage High or Low
 *    1F                4     Reg31~24bits, Reg23~16bits, Reg15~8bits, Reg7~0bits
 *
 *    @param codeDRSLen
 *        the length of codeDRS
 *
 * @return RETURN_CODE: Values can be parsed with device_getResponseCodeString()
 * Note: Only support TTK devices
 */
int
device_getDRS(BYTE * codeDRS,
  int *              codeDRSLen);

/**
 * Set the Core Dump Log File Name
 *
 * Set the file name of the log file when the core dump occurs for the firmware
 *
 *
 * @param filename the file name including the path
 * @param filenameLen the length of filename; the maximum length is 99 bytes not including the null character
 *
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
device_setCoreDumpLogFile(IN char * filename, IN int filenameLen);

/**
 * Output Log
 *
 * Save the log to a file
 *
 *
 * @param filename the file name including the path
 * @param filenameLen the length of filename
 *
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
device_outputLog(IN char * filename, IN int filenameLen);

/**
 * Get Key Status
 *
 * Gets the status of loaded keys
 * @param status newFormat for Augusta and miniSmartII only
 *     1: new format of key status
 *     0: reserved format for support previous device
 * @param status
 *     For L80, L100, Augusta and miniSmartII:
 *        When the newFormat is 0, data format as follows.
 *        For Augusta and miniSmartII:
 *          byte 0:  PIN DUKPT Key, Does not support, always 0
 *          byte 1:  PIN Master Key, Does not support, always 0
 *          byte 2:  PIN Session Key, Does not support, always 0
 *          byte 3:  Account/MSR DUKPT Key, 1 Exists, 0 None, 0xFF STOP
 *          byte 4:  Account/ICC DUKPT Key, 1 Exists, 0 None, 0xFF STOP
 *          byte 5:  Admin DUKPT Key, 1 Exists, 0 None, 0xFF STOP
 *        For L80 and L100:
 *          byte 0:  PIN DUKPT Key
 *          byte 1:  PIN Master Key
 *          byte 2:  Standard PIN Session Key
 *          byte 3:  Desjardins PIN Session Key
 *          byte 4:  Account/MSR DUKPT Key, 1 Exists, 0 None, 0xFF STOP, Does not support, always 0
 *          byte 5:  Account/ICC DUKPT Key, 1 Exists, 0 None, 0xFF STOP, Does not support, always 0
 *          byte 6:  Admin DUKPT Key, 1 Exists, 0 None, 0xFF STOP
 *          byte 7:  Data DUKPT Key, 1 Exists, 0 None, 0xFF STOP
 *          byte 8:  MAC DUKPT Key, 1 Exists, 0 None, 0xFF STOP
 *
 *        when the newFormat is 1, data format as follows.
 *         [Block Length] [KeyStatusBlock1] [KeyStatusBlock2]...[KeyStatusBlockN]
 *        Where:
 *        [Block Length] is 2 bytes, format is Len_L Len_H, is KeyStatusBlock Number
 *        [KeyStatusBlockX> is 4 bytes, format is [Key Index and Key Name] [key slot] [key status]:
 *        [Key Index and Key Name] is 1 byte. Please refer to following table
 *            0x14    LCL-KEK to Encrypt Other Keys
 *            0x02    Data encryption Key to Encrypt ICC/MSR
 *            0x05    MAC DUKPT Key for Host-Device - MAC Verification
 *            0x05    MTK DUKPT Key for TTK Self-Test
 *            0x0C    RKI-KEK for Remote Key Injection
 *        [key slot] is 2 bytes. Range is 0 - 9999
 *        the MTK DUKPT Key slot is 16, the others are all 0
 *        [key status] is 1 byte.
 *            0 - Not Exist
 *            1 - Exist
 *        0xFF - (Stop. Only Valid for DUKPT Key)
 *    For NEO2 and SREDKey2:
 *		Each unit of three bytes represents one key's parameters (index and slot).
 *			Key Name Index (1 byte):
 *				0x14 - LCL-KEK
 *				0x01 - Pin encryption Key (NEO2 only)
 *				0x02 - Data encryption Key
 *				0x05 - MAC DUKPT Key
 *				0x0A - PCI Pairing Key (NEO2 only)
 *			Key Slot (2 bytes):
 *				Indicate different slots of a certain Key Name
 *					Example: slot =5 (0x00 0x05), slot=300 (0x01 0x2C)
 *					For BTPay380, slot is always 0
 *		For example, 0x14 0x00 0x00 0x02 0x00 0x00 0x0A 0x00 0x00 will represent
 *			[KeyNameIndex=0x14,KeySlot=0x0000], [KeyNameIndex=0x02,KeySlot=0x0000] and [KeyNameIndex=0x0A,KeySlot=0x0000]
 *
 * @param statusLen the length of status
 *
 * @return RETURN_CODE:    Values can be parsed with device_getResponseCodeString
 */
int
device_getKeyStatus(int * newFormat,
  BYTE *                  status,
  int *                   statusLen);

/**
 * Enter Stop Mode
 *
 * Set device enter to stop mode. In stop mode, LCD display and
 * backlight is off.  Stop mode reduces power consumption to the
 * lowest possible level.  A unit in stop mode can only be woken up
 * by a physical key press.
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString
 */
int
device_enterStopMode();

/**
 *  Set Sleep Mode Timer
 *
 * Set device enter to sleep mode after the given time. In sleep mode,
 * LCD display and backlight is off.
 * Sleep mode reduces power consumption to the lowest possible level.
 * A unit in Sleep mode can only be woken up by a physical key press.
 *
 * @param time Enter sleep time value, in second.
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString
 */
int
device_setSleepModeTime(int time);


/**
 * Verify Backdoor Key to Unlock Security
 *
 * @return RETURN_CODE: Values can be parsed with device_getResponseCodeString
 *
 * Note: The function is only for TTK devices.
 */
int
device_verifyBackdoorKey();

/**
 * Self check for TTK
 * If Self-Test function Failed, then work into De-activation State.
 * If device work into De-activation State, All Sensitive Data will be
 *  erased and it need be fixed in Manufacture.
 * @return RETURN_CODE: Values can be parsed with device_getResponseCodeString
 */
int
device_selfCheck();

/**
 * Ping Device - NEO only
 *
 * Pings the reader.  If connected, returns success.  Otherwise, returns timeout.
 *
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
device_pingDevice();

/**
 * Control User Interface - NEO only
 *
 * Controls the User Interface:  Display, Beep, LED
 *
 * @param values Four bytes to control the user interface
 * Byte[0] = LCD Message
 * Messages 00-07 are normally controlled by the reader.
 * - 00h: Idle Message (Welcome)
 * - 01h: Present card (Please Present Card)
 * - 02h: Time Out or Transaction cancel (No Card)
 * - 03h: Transaction between reader and card is in the middle (Processing...)
 * - 04h: Transaction Pass (Thank You)
 * - 05h: Transaction Fail (Fail)
 * - 06h: Amount (Amount $ 0.00 Tap Card)
 * - 07h: Balance or Offline Available funds (Balance $ 0.00) Messages 08-0B
 *        are controlled by the terminal
 * - 08h: Insert or Swipe card (Use Chip & PIN)
 * - 09h: Try Again(Tap Again)
 * - 0Ah: Tells the customer to present only one card (Present 1 card only)
 * - 0Bh: Tells the customer to wait for authentication/authorization (Wait)
 * - FFh: indicates the command is setting the LED/Buzzer only.
 * Byte[1] = Beep Indicator
 * - 00h: No beep
 * - 01h: Single beep
 * - 02h: Double beep
 * - 03h: Three short beeps
 * - 04h: Four short beeps
 * - 05h: One long beep of 200 ms
 * - 06h: One long beep of 400 ms
 * - 07h: One long beep of 600 ms
 * - 08h: One long beep of 800 ms
 * Byte[2] = LED Number
 * - 00h: LED 0 (Power LED) 01h: LED 1
 * - 02h: LED 2
 * - 03h: LED 3
 * - FFh: All LEDs
 * Byte[3] = LED Status
 * - 00h: LED Off
 * - 01h: LED On
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
device_controlUserInterface(IN BYTE * values);

/**
 * Control Indicators
 *
 * Control the reader.  If connected, returns success.  Otherwise,
 * returns timeout.
 *
 * @param indicator description as follows:
 * - 00h: ICC LED
 * - 01h: Blue MSR
 * - 02h: Red MSR
 * - 03h: Green MSR
 * @param enable  TRUE = ON, FALSE = OFF
 * @return success or error code.  Values can be parsed with
 *        device_getResponseCodeString
 * @see ErrorCode
 */
int
device_controlIndicator(IN int indicator, IN int enable);

/**
 * Get current active device type
 * @return :  return the device type defined as DEVICE_TYPE in the IDTDef.h
 */
int
device_getCurrentDeviceType();

/**
 * Send a Command to NEO device
 *
 * Sends a command  to the NEO device .
 *
 * @param cmd  command to execute.
 * @param subCmd, sub command to execute.
 *
 * @param data buffer of NEO command data.
 * @param dataLen, the length of the buffer data.
 *
 * @param response Response data
 * @param respLen, the length of Response data
 *
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
device_SendDataCommandNEO(IN int cmd,
  IN int                         subCmd,
  IN BYTE *                      data,
  IN int                         dataLen,
  OUT BYTE *                     response,
  IN_OUT int *                   respLen);

/**
 * Send a Command to NGA device
 *
 * Sends a command  to the device .
 *
 * @param cmd buffer of command to execute.
 * @param cmdLen, the length of the buffer cmd.
 *
 * @param data buffer of IDG command data.
 * @param dataLen, the length of the buffer data.
 *
 * @param response Response data
 * @param respLen, the length of Response data
 *
 * @return RETURN_CODE: Values can be parsed with device_getResponseCodeString()
 */
int
device_SendDataCommand(IN BYTE * cmd,
  IN int                         cmdLen,
  IN BYTE *                      data,
  IN int                         dataLen,
  OUT BYTE *                     response,
  IN_OUT int *                   respLen);

/**
 * Send a Command to ITP device
 *
 * Sends a command  to the device .
 *
 * @param cmd buffer of command to execute.
 * @param cmdLen, the length of the buffer cmd.
 *
 * @param data buffer of ITP command data.
 * @param dataLen, the length of the buffer data.
 *
 * @param response Response data
 * @param respLen, the length of Response data
 *
 * @return RETURN_CODE: Values can be parsed with device_getResponseCodeString()
 */
int
device_SendDataCommandITP(IN BYTE * cmd,
  IN int                            cmdLen,
  IN BYTE *                         data,
  IN int                            dataLen,
  OUT BYTE *                        response,
  IN_OUT int *                      respLen);

/**
 * Reboot Device - NGA
 * Executes a command to restart the device.
 * - Card data is cleared, resetting card status bits.
 * - Response data of the previous command is cleared.
 * - Resetting firmware.
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 */
int
device_rebootDevice();

/**
 * Update Firmware - NGA
 * Updates the firmware of the Spectrum Pro K21 HUB or Maxq1050.
 * @param firmwareData Signed binary data of a firmware file provided by IDTech
 * @param firmwareDataLen Length of firmwareData
 * @param firmwareName Firmware name. Must be one of the following two strings
 * (with appropriate version information)
 *  - "SP K21 APP Vx.xx.xxx"
 *  - "SP MAX APP Vx.xx.xxx"
 * @param encryptionType Encryption type
 * - 0 : Plaintext
 * - 1 : TDES ECB, PKCS#5 padding
 * - 2 : TDES CBC, PKCS#5, IV is all 0
 * @param keyBlob Encrypted firmware session key blob, TR-31 Rev B,
 *  wrapped by FW Key (Optional, none if firmware is plaintext)
 * @param keyBlobLen Length of keyBlob
 * @return RETURN_CODE:  Values can be parsed with errorCode.getErrorString()
 *
 * Firmware update status is returned in the callback with the following values:
 * sender = SPECTRUM_PRO
 * state = DeviceState.FirmwareUpdate
 * data = File Progress.  Two bytes, with byte[0] = current block,
 *                     and byte[1] = total blocks. 0x0310 = block 3 of 16
 * transactionResultCode:
 * - RETURN_CODE_DO_SUCCESS = Firmware Update Completed Successfully
 * - RETURN_CODE_BLOCK_TRANSFER_SUCCESS = Current block transferred successfully
 * - Any other return code represents an error condition
 */
int
device_updateFirmware(IN BYTE * firmwareData,
  IN int                        firmwareDataLen,
  IN char *                     firmwareName,
  IN int                        encryptionType,
  IN BYTE *                     keyBlob,
  IN int                        keyBlobLen);

/**
 * Update Firmware with zip file
 * Updates the firmware of NEO 2 devices.
 * @param firmwareZipFilename Firmware zip file name.
 *  - For example "package_VP6300 FW v1.01.003.0432.T.zip"
 * @param firmwareZipFilenameLen Firmware zip file name length
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 *
 * Firmware update status is returned in the callback with the following values:
 * sender = device type
 * state = DEVICE_FIRMWARE_UPDATE
 * current block
 * total blocks
 * ResultCode:
 * - RETURN_CODE_DO_SUCCESS = Firmware Update Completed Successfully
 * - Any other return code represents an error condition
 * Note: to call this function under Windows, the executable file "unzip.exe" is required
 *
 */
//int
//device_updateFirmwareWithZipFile(IN char *firmwareZipFilename, IN int firmwareZipFilenameLen);

/**
 * Get Device Memory Usage Information
 * @param freeHeapSize
 *  Free Heap Size: Available heap size
 *
 * @param notFreedBlockCnt
 *  Memory Not Freed Block Count: Memory in use block count
 *
 * @param minEverFreeHeapSize
 *  Minimum Ever Free Heap Size: The lowest ever available heap size
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
device_getDeviceMemoryUsageInfo(OUT int * freeHeapSize, OUT int * notFreedBlockCnt, OUT int * minEverFreeHeapSize);

/**
 * FeliCa Authentication
 *  Provides a key to be used in a follow up FeliCa Read with MAC (3 blocks max) or Write with MAC (1 block max).
 *		This command must be executed before each Read w/MAC or Write w/MAC command
 *
 * @param key 16-byte key used for MAC generation of Read or Write with MAC
 * @param keyLen length of key, must be 16 bytes
 *
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 *
 */
int
felica_authentication(IN BYTE * key, IN int keyLen);

/**
 * FeliCa Read with MAC Generation
 *
 *  Reads up to 3 blocks with MAC Generation.  FeliCa Authentication must be performed first
 *
 * @param blockCnt Number of blocks in blockList.  Maximum 3 block requests
 * @param blockList Block to read. Each block in blockList = 2 or 3 bytes of data.
 * @param blockListLen Length of blockList.
 *
 * @param blockData Blocks read will be stored in blockData.  Each block is 16 bytes.
 * @param blockDataLen Length of blockData.
 *
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
felica_readWithMac(IN int blockCnt, IN BYTE * blockList, IN int blockListLen, OUT BYTE * blockData,
  OUT int * blockDataLen);

/**
 * FeliCa Write with MAC Generation
 *
 * Writes a block with MAC Generation.  FeliCa Authentication must be performed first
 *
 * @param blockNum Number of block
 * @param blockData  Block to write.
 * @param blockDataLen  Length of blockData.  Must be 16 bytes.
 *
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
felica_writeWithMac(IN BYTE blockNum, IN BYTE * blockData, IN int blockDataLen);

/**
 * FeliCa Read
 *
 * Reads up to 4 blocks.
 *
 * @param serviceCodeList Service Code List. Each service code in Service Code List = 2 bytes of data
 * @param serviceCodeListLen Length of serviceCodeList
 *
 * @param blockCnt Number of blocks in blockList.  Maximum 4 block requests
 * @param blockList Block to read. Each block in blockList = 2 or 3 bytes of data.
 * @param blockListLen Length of blockList.
 *
 * @param blockData Blocks read will be stored in blockData.  Each block 16 bytes.
 * @param blockDataLen Length of blockData.
 *
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
felica_read(IN BYTE * serviceCodeList, IN int serviceCodeListLen, IN int blockCnt, IN BYTE * blockList,
  IN int blockListLen, OUT BYTE * blockData, OUT int * blockDataLen);

/**
 * FeliCa Write
 *
 * Writes a block
 *
 * @param serviceCodeList Service Code List. Each service code in Service Code List = 2 bytes of data
 * @param serviceCodeListLen Length of serviceCodeList
 * @param blockCnt Number of blocks in blockList.  Currently only support 1 block.
 * @param blockList Block list.  Each block in blockList = 2 or 3 bytes of data.
 * @param blockListLen Length of blockData.
 *
 * @param blockData  Block to write.
 * @param blockDataLen Length of blockData.  Must be 16 bytes.
 *
 * @param respData If successful, the Status Flag (2 bytes) is stored in respData.resData.
 *      Status flag response as explained in FeliCA Lite-S User's Manual, Section 4.5
 *
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
felica_write(IN BYTE * serviceCodeList, IN int serviceCodeListLen, IN int blockCnt, IN BYTE * blockList,
  IN int blockListLen, IN BYTE * blockData, IN int blockDataLen, OUT BYTE * statusFlag,
  OUT int * statusFlagLen);

/**
 * FeliCa Poll for Card
 *
 * Polls for a Felica Card
 *
 * @param systemCode System Code.
 * @param systemCodeLen Length of systemCode.  Must be 2 bytes
 *
 * @param respData response data will be stored in respData.  Poll response as explained in FeliCA Lite-S User's Manual
 * @param respDataLen Length of systemCode.
 *
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
felica_poll(IN BYTE * systemCode, IN int systemCodeLen, OUT BYTE * respData, OUT int * respDataLen);

/**
 * FeliCa Send Command
 *
 * Send a Felica Command
 *
 * @param command Command data from settlement center to be sent to felica card
 * @param commandLen: Length of command data
 *
 * @param respData Response data from felica card.
 * @param respDataLen Length of respData.
 *
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
felica_SendCommand(IN BYTE * command, IN int commandLen, OUT BYTE * respData, OUT int * respDataLen);

/**
 * FeliCa Request Service
 *
 * Request Service for a Felica Card
 *
 * @param nodeCode Node Code List.  Each node 2 bytes
 * @param nodeCodeLen Length of nodeCode.
 * @param respData response data will be stored in respData.  Response as explained in FeliCA Lite-S User's Manual
 * @param respDataLen Length of respData.
 *
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
felica_requestService(IN BYTE * nodeCode, IN int nodeCodeLen, OUT BYTE * respData, OUT int * respDataLen);

/**
 * FeliCa Get Code
 *
 * Start the FeliCa get code process
 * Since the firmware timeout is 180 seconds, the SDK timeout of the command is set to 181 seconds.
 *
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
felica_getCode();

/**
 * FeliCa Cancel Code Entry
 *
 * Cancels FeliCa Get Code request
 *
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
felica_cancelCodeEntry();

// long long timeInMilliseconds(void);
// int felica_SendCommandTest(IN BYTE *command, IN int commandLen, OUT BYTE *respData, OUT int *respDataLen);

/**
 * DEPRECATED : please use config_getModelNumber_Len(OUT char* sNumber, IN_OUT int *sNumberLen)
 *
 * Polls device for Model Number
 *
 * @param sNumber  Returns Model Number; needs to have at least 64 bytes of memory
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString
 *
 */
int
config_getModelNumber(OUT char * sNumber);

/**
 * Polls device for Model Number
 *
 * @param sNumber  Returns Model Number
 * @param sNumber  length of Model Number
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString
 *
 */
int
config_getModelNumber_Len(OUT char * sNumber, IN_OUT int * sNumberLen);

///**
// * Set Model Number for the device
// *
// * @param sNumber  Model Number
// *
// * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString
// */
// int config_setModelNumber(IN char* sNumber);

/**
 * Set System Language
 * Sets the language for the message displayed in the LCD screen
 *
 * @param language 2-byte ASCII code, can be "EN" or "JP"
 *
 * @return success or error code.  Values can be parsed with device_getIDGStatusCodeString
 * @see ErrorCode
 */
int
device_setSystemLanguage(char * language);

/**
 * DEPRECATED : please use config_getSerialNumber_Len(OUT char* sNumber, IN_OUT int *sNumberLen)
 *
 * Polls device for Serial Number
 *
 * @param sNumber  Returns Serial Number; needs to have at least 64 bytes of memory
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString
 *
 */
int
config_getSerialNumber(OUT char * sNumber);

/**
 * Polls device for Serial Number
 *
 * @param sNumber  Returns Serial Number
 * @param sNumberLen  Length of Serial Number
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString
 *
 */
int
config_getSerialNumber_Len(OUT char * sNumber, IN_OUT int * sNumberLen);

/**
 * Set the timeout duration for regular commands
 * The new timeout value will affect all the functions actually send (sync) commands
 * that doesn’t need to wait for a callback function, such as device_getFirmwareVersion(),
 * device_pingDevice(), device_SendDataCommandNEO(), device_enablePassThrough(), device_setBurstMode(),
 * device_setPollMode(), device_updateFirmware() …etc.
 *
 * @param millisecond  timeout value in milliseconds.  Please consult the firmware team for the proper value.
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString
 *
 */
int
config_setCmdTimeOutDuration(IN int millisecond);

/**
 * Set the LED Controller - AUGUSTA
 * Set the MSR / ICC LED controlled by software or firmware
 * NOTE: The ICC LED always controlled by software.
 * @param firmwareControlMSRLED
 *  - 1:  firmware control the MSR LED
 *  - 0: software control the MSR LED
 * @param firmwareControlICCLED
 *  - 1:  firmware control the ICC LED
 *  - 0: software control the ICC LED
 * @return RETURN_CODE:    Values can be parsed with device_getResponseCodeString
 */
int
config_setLEDController(int firmwareControlMSRLED,
  int                       firmwareControlICCLED);

/**
 * Get the LED Controller Status - AUGUSTA
 * Get the MSR / ICC LED controlled status by software or firmware
 * NOTE: The ICC LED always controlled by software.
 * @param firmwareControlMSRLED
 *  - 1:  firmware control the MSR LED
 *  - 0: software control the MSR LED
 * @param firmwareControlICCLED
 *  - 1:  firmware control the ICC LED
 *  - 0: software control the ICC LED
 * @return RETURN_CODE:    Values can be parsed with device_getResponseCodeString
 */
int
config_getLEDController(int * firmwareControlMSRLED,
  int *                       firmwareControlICCLED);

/**
 * Set the Beeper Controller - AUGUSTA
 * Set the Beeper controlled by software or firmware
 *
 * @param firmwareControlBeeper  1 means firmware control the beeper,
 *                               0 means software control beeper.
 * @return RETURN_CODE:    Values can be parsed with device_getResponseCodeString
 */
int
config_setBeeperController(int firmwareControlBeeper);

/**
 * Get the Beeper Controller Status - AUGUSTA
 * Set the Beeper controlled Status by software or firmware
 *
 * @param firmwareControlBeeper  1 means firmware control the beeper,
 *                               0 means software control beeper.
 * @return RETURN_CODE: Values can be parsed with device_getResponseCodeString
 */
int
config_getBeeperController(int * firmwareControlBeeper);

/**
 * Set Encryption Control - AUGUSTA
 *
 * Set Encryption Control to switch status between MSR and ICC/EMV function.
 *     Following Encryption status supported:
 *     - MSR ON, ICC/EMV ON,
 *     - MSR ON, ICC/EMV OFF,
 *     - MSR OFF, ICC/EMV OFF,
 *
 * @param msr
 *     - 1:  enable MSR with Encryption,
 *     - 0: disable MSR with Encryption,
 * @param icc
 *     - 1:  enable ICC with Encryption,
 *     - 0: disable ICC with Encryption,
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString
 */
int
config_setEncryptionControl(int msr, int icc);

/**
 * Get Encryption Control - AUGUSTA
 *
 * Get Encryption Control to switch status between MSR and ICC/EMV function.
 *     Following Encryption status supported:
 *     - MSR ON, ICC/EMV ON,
 *     - MSR ON, ICC/EMV OFF,
 *     - MSR OFF, ICC/EMV OFF,
 *
 * @param msr
 *     - 1:  enabled MSR with Encryption,
 *     - 0: disabled MSR with Encryption,
 * @param icc
 *     - 1:  enabled ICC with Encryption,
 *     - 0: disabled ICC with Encryption,
 *
 * @return RETURN_CODE:    Values can be parsed with device_getResponseCodeString
 */
int
config_getEncryptionControl(int * msr,
  int *                           icc);

/**
 * Start remote key injection.
 *
 * @param caPath The path to ca-certificates.crt.  It should be NULL, because the file is not used anymore.
 * @param isProduction 1: The reader is a production unit, 0: The reader is not a production unit
 *
 * @return success or error code.
 * @see ErrorCode
 */
int
device_startRKI(const char * caPath, int isProduction);

/**
 * Enable Pass Through - NEO
 *
 * Enables Pass Through Mode for direct communication with L1
 * interface (power on icc, send apdu, etc).
 *
 * @param enablePassThrough 1 = pass through ON, 0 = pass through OFF
 *
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
device_enablePassThrough(int enablePassThrough);

/**
 * Enable L80 Pass Through
 *
 * Enables Pass Through Mode for direct communication to L80 hook up
 * to NEO II device
 *
 * @param enableL80PassThrough 1 = pass through ON, 0 = pass through OFF
 *
 * @return RETURN_CODE: Values can be parsed with device_getResponseCodeString()
 */
int
device_enableL80PassThrough(int enableL80PassThrough);

/**
 * Enable L100 Pass Through
 *
 * Enables Pass Through Mode for direct communication to L100 hook up
 * to NEO II device
 *
 * @param enableL100PassThrough 1 = pass through ON, 0 = pass through OFF
 *
 * @return RETURN_CODE: Values can be parsed with device_getResponseCodeString()
 */
int
device_enableL100PassThrough(int enableL100PassThrough);

/**
 * Get L80 Pass Through Mode
 *
 * Get current Pass Through Mode for direct communication to L80
 * hook up to NEO II device
 *
 *
 * @return RETURN_CODE: return 1 if L80 Pass Through Mode is TRUE,
 *  0 if L80 Pass Through Mode is FALSE
 */
int
device_getL80PassThroughMode();

/**
 * Get L100 Pass Through Mode
 *
 * Get current Pass Through Mode for direct communication to L100
 * hook up to NEO II device
 *
 *
 * @return RETURN_CODE: return 1 if L100 Pass Through Mode is TRUE,
 *  0 if L100 Pass Through Mode is FALSE
 */
int
device_getL100PassThroughMode();

/**
 * Enables pass through mode for ICC. Required when direct ICC
 * commands are required (power on/off ICC, exchange APDU)
 *
 * @param data The data includes Poll Timeout,
 *      Flags, Contact Interface to Use, Beep Indicator, LED Status,
 *      and Display Strings.
 * @param dataLen length of data
 * @return success or error code.  Values can be parsed
 *      with device_getIDGStatusCodeString
 * @see ErrorCode
 */
int
device_enhancedPassthrough(IN BYTE * data,
  IN int                             dataLen);

/**
 * Send Burst Mode - NEO
 *
 * Sets the burst mode for the device.
 *
 * @param mode 0 = OFF, 1 = Always On, 2 = Auto Exit
 *
 * @return success or error code.  Values can be parsed with
 *  device_getIDGStatusCodeString
 * @see ErrorCode
 */
int
device_setBurstMode(IN BYTE mode);

/**
 * Set Poll Mode - NEO
 *
 * Sets the poll mode forthe device. Auto Poll keeps reader active,
 * Poll On Demand only polls when requested by terminal
 *
 * @param mode 0 = Auto Poll, 1 = Poll On Demand
 *
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
device_setPollMode(IN BYTE mode);

/**
 * Poll for Token
 *
 * Polls for a PICC
 *
 * @param timeout timeout in milliseconds, must be multiple of 10 milliseconds. 30, 120, 630, or 1150 for example.
 *
 * @param respData Response data will be stored in respData.  1 byte of card type, and the Serial Number (or the UID) of the PICC if available.
 * @param respDataLen Length of systemCode.
 *
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
device_pollForToken(IN int timeout, OUT BYTE * respData, IN_OUT int * respDataLen);

/**
 * Set Merchant Record - NEO
 * Sets the merchant record for ApplePay VAS
 *
 * @param index Merchant Record index, valid values 1-6
 * @param enabled Merchant Enabled/Valid flag
 * @param merchantID  Merchant unique identifer registered with Apple.
 *        Example com.idtechproducts.applePay
 * @param merchantURL Merchant URL, when applicable
 *
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 *
 */
int
device_setMerchantRecord(int index,
  int                        enabled,
  char *                     merchantID,
  char *                     merchantURL);

/**
 * DEPRECATED : please use device_getMerchantRecord_Len(IN int index, OUT BYTE * record, IN_OUT int *recordLen)
 *
 * Get Merchant Record
 *
 * Gets the merchant record for the device.
 *
 * @param index Merchant Record index, valid values 1-6
 * @param record; needs to have at least 99 bytes of memory
 *            response data from reader.
 *            Merchant Record Index: 1 byte
 *            enabled: 1 byte
 *            Merchant ID: 32 bytes
 *            Length of Merchant URL: 1 byte
 *            Merchant URL: 64 bytes
 *
 * @return success or error code.  Values can be parsed
 *         with device_getIDGStatusCodeString()
 * @see ErrorCode
 */
int
device_getMerchantRecord(IN int index,
  OUT BYTE *                    record);

/**
 * Get Merchant Record
 *
 * Gets the merchant record for the device.
 *
 * @param index Merchant Record index, valid values 1-6
 * @param record
 *            response data from reader.
 *            Merchant Record Index: 1 byte
 *            enabled: 1 byte
 *            Merchant ID: 32 bytes
 *            Length of Merchant URL: 1 byte
 *            Merchant URL: 64 bytes
 *
 * @param recordLen Length of record
 *
 * @return success or error code.  Values can be parsed
 *         with device_getIDGStatusCodeString()
 * @see ErrorCode
 */
int
device_getMerchantRecord_Len(IN int index,
  OUT BYTE * record, IN_OUT int * recordLen);

/**
 * DEPRECATED : please use device_pollCardReader_Len(OUT BYTE * status, IN_OUT int *statusLen)
 *
 * Poll Card Reader
 *
 * Provides information about the state of the Card Reader
 *
 *    @param status Six bytes indicating card reader information
 *    Byte 0:
 *     - Bit 0: Device Manufacturing CA data valid
 *     - Bit 1: Device Manufacturing Secure data valid
 *     - Bit 2: HOST_CR_MASTER_DUKPT Key valid
 *     - Bit 3: HOST_CR_MAC Keys valid (Authenticated)
 *     - Bit 4: RFU
 *     - Bit 5: RFU
 *     - Bit 6: DATA_DUKPT Key Valid
 *     - Bit 7: Key is initialized (MFK and RSA Key pairs)
 *
 *    Byte 1:
 *     - Bit 0: Firmware Key Valid
 *     - Bit 1: RFU
 *     - Bit 2: CR_PINPAD_MASTER_DUKPT Key valid
 *     - Bit 3: CR_PINPAD_MAC Keys valid (Authenticated)
 *     - Bit 4: DATA Pairing DUKPT Key valid
 *     - Bit 5: PIN Pairing DUKPT Key Valid
 *     - Bit 6: RFU
 *     - Bit 7: RFU
 *
 *    Byte 2:
 *     - Bit 0: RFU
 *     - Bit 1: Tamper Switch #1 Error
 *     - Bit 2: Battery Backup Error
 *     - Bit 3: Temperature Error
 *     - Bit 4: Voltage Sensor Error
 *     - Bit 5: Firmware Authentication Error
 *     - Bit 6: Tamper Switch #2 Error
 *     - Bit 7: Removal Tamper Error
 *
 *    Byte 3:
 *     - Battery Voltage (example 0x32 = 3.2V, 0x24 = 2.4V)
 *
 *    Byte 4:
 *     - Bit 0: Log is Full
 *     - Bit 1: Mag Data Present
 *     - Bit 2: Card Insert
 *     - Bit 3: Removal Sensor connected
 *     - Bit 4: Card Seated
 *     - Bit 5: Latch Mechanism Active
 *     - Bit 6: Removal Sensor Active
 *     - Bit 7: Tamper Detector Active
 *
 *    Byte 5:
 *     - Bit 0: SAM Available
 *     - Bit 1: Chip Card Reader Available
 *     - Bit 2: Host Connected
 *     - Bit 3: Contactless Available
 *     - Bit 4: PINPAD connected
 *     - Bit 5: MSR Header connected
 *     - Bit 6: RFU
 *     - Bit 7: Production Unit
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 */
int
device_pollCardReader(OUT BYTE * status);

/**
 * Poll Card Reader
 *
 * Provides information about the state of the Card Reader
 *
 *    @param status Six bytes indicating card reader information
 *    Byte 0:
 *     - Bit 0: Device Manufacturing CA data valid
 *     - Bit 1: Device Manufacturing Secure data valid
 *     - Bit 2: HOST_CR_MASTER_DUKPT Key valid
 *     - Bit 3: HOST_CR_MAC Keys valid (Authenticated)
 *     - Bit 4: RFU
 *     - Bit 5: RFU
 *     - Bit 6: DATA_DUKPT Key Valid
 *     - Bit 7: Key is initialized (MFK and RSA Key pairs)
 *
 *    Byte 1:
 *     - Bit 0: Firmware Key Valid
 *     - Bit 1: RFU
 *     - Bit 2: CR_PINPAD_MASTER_DUKPT Key valid
 *     - Bit 3: CR_PINPAD_MAC Keys valid (Authenticated)
 *     - Bit 4: DATA Pairing DUKPT Key valid
 *     - Bit 5: PIN Pairing DUKPT Key Valid
 *     - Bit 6: RFU
 *     - Bit 7: RFU
 *
 *    Byte 2:
 *     - Bit 0: RFU
 *     - Bit 1: Tamper Switch #1 Error
 *     - Bit 2: Battery Backup Error
 *     - Bit 3: Temperature Error
 *     - Bit 4: Voltage Sensor Error
 *     - Bit 5: Firmware Authentication Error
 *     - Bit 6: Tamper Switch #2 Error
 *     - Bit 7: Removal Tamper Error
 *
 *    Byte 3:
 *     - Battery Voltage (example 0x32 = 3.2V, 0x24 = 2.4V)
 *
 *    Byte 4:
 *     - Bit 0: Log is Full
 *     - Bit 1: Mag Data Present
 *     - Bit 2: Card Insert
 *     - Bit 3: Removal Sensor connected
 *     - Bit 4: Card Seated
 *     - Bit 5: Latch Mechanism Active
 *     - Bit 6: Removal Sensor Active
 *     - Bit 7: Tamper Detector Active
 *
 *    Byte 5:
 *     - Bit 0: SAM Available
 *     - Bit 1: Chip Card Reader Available
 *     - Bit 2: Host Connected
 *     - Bit 3: Contactless Available
 *     - Bit 4: PINPAD connected
 *     - Bit 5: MSR Header connected
 *     - Bit 6: RFU
 *     - Bit 7: Production Unit
 *
 *     @param statusLen Length of status
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 */
int
device_pollCardReader_Len(OUT BYTE * status, IN_OUT int * statusLen);

/**
 * DEPRECATED : please use device_getSpectrumProKSN_Len(IN int type, OUT BYTE * KSN, IN_OUT int *KSNLen)
 *
 * Get DUKPT KSN
 *
 * Returns the KSN for the provided key index
 *
 * @param type Key type:
 *  - 0: Key Encryption Key (Master Key or KEK)
 *  - 2: Data Encryption Key (DEK)
 *  - 5: MAC Key (MAK)
 *  - 10: RKL Key Encryption Key (REK)
 *  - 20: HSM DUKPT Key
 *
 * @param KSN  Key Serial Number; needs to have at least 10 bytes of memory
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 */
int
device_getSpectrumProKSN(IN int type,
  OUT BYTE *                    KSN);

/**
 * Get DUKPT KSN
 *
 * Returns the KSN for the provided key index
 *
 * @param type Key type:
 *  - 0: Key Encryption Key (Master Key or KEK)
 *  - 2: Data Encryption Key (DEK)
 *  - 5: MAC Key (MAK)
 *  - 10: RKL Key Encryption Key (REK)
 *  - 20: HSM DUKPT Key
 *
 * @param KSN  Key Serial Number
 *
 * @param KSNLen  Length of KSN
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 */
int
device_getSpectrumProKSN_Len(IN int type,
  OUT BYTE * KSN, IN_OUT int * KSNLen);

/**
 * Calibrate reference parameters
 * @param delta Delta value (0x02 standard default value)
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 */
int
device_calibrateParameters(BYTE delta);

/**
 * get RTC date and time of the device
 *
 * @param dateTime
 *            <dateTime Data> is:
 *                 6 byte data for YYMMDDHHMMSS in hex.  For example 0x171003102547 stands for 2017 Oct 3rd 10:25:47
 *
 * @param dateTimeLen
 *                 return 6 bytes if successful
 *
 *
 * @return success or error code. Values can be parsed with device_getResponseCodeString
 * @see ErrorCode
 */
int
device_getRTCDateTime(IN BYTE * dateTime,
  IN_OUT int *                  dateTimeLen);

/**
 * set RTC date and time of the device
 *
 * @param dateTime
 *            <dateTime Data> is:
 *                 6 byte data for YYMMDDHHMMSS in hex.  For example 0x171003102547 stands for 2017 Oct 3rd 10:25:47
 *
 * @param dateTimeLen
 *                 should be always 6 bytes
 *
 * @return success or error code. Values can be parsed with device_getResponseCodeString
 * @see ErrorCode
 */
int
device_setRTCDateTime(IN BYTE * dateTime,
  IN int                        dateTimeLen);

/**
 * Configures the buttons on the ViVOpay Vendi reader
 * @param done
 *     0x01: the Done switch is enabled
 *     0x00: the Done switch is disabled
 *
 * @param swipe
 *     0x01: the Swipe Card switch is enabled
 *     0x00: the Swipe Card switch is disabled
 *
 * @param delay
 *     an unsigned delay value (<= 30) in seconds
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
device_configureButtons(IN BYTE done,
  IN BYTE                       swipe,
  IN BYTE                       delay);

/**
 * Reads the button configuration from the ViVOpay Vendi reader
 * @param done
 *     0x01: the Done switch is enabled
 *     0x00: the Done switch is disabled
 *
 * @param swipe
 *     0x01: the Swipe Card switch is enabled
 *     0x00: the Swipe Card switch is disabled
 *
 * @param delay
 *     an unsigned delay value in seconds
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
device_getButtonConfiguration(OUT BYTE * done,
  OUT BYTE *                             swipe,
  OUT BYTE *                             delay);

/**
 * Stops the blue LEDs on the ViVOpay Vendi reader from flashing in
 * left to right sequence and turns the LEDs off, and contactless
 * function is disable at the same time
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
device_disableBlueLED();

/**
 * Use this function to control the blue LED behavior on the Vendi reader
 *
 * @param data
 *     Sequence data
 *         Byte 0 (Cycle): 0 = Cycle once, 1 = Repeat
 *         Byte 1 (LEDs): LED State Bitmap
 *         Byte 2-3 (Duration): Given in multiples of 10 millisecond
 *         Byte 4 (LED): LED State Bitmap
 *         Byte 5-6 (Duration): Given in multiples of 10 millisecond
 *         Byte 7-24 (Additional LED/Durations): Define up to 8
 *                    LED and duration pairs
 *
 *     LED State Bitmap:
 *         Bit 8: Left blue LED, 0 = off, 1 = on
 *         Bit 7: Center Blue LED, 0 = off, 1 = on
 *         Bit 6: Right Blue LED0 = off, 1 = on
 *         Bit 5: Yellow LED, 0 = off, 1 = on
 *         Bit 4: Reserved for future use
 *         Bit 3: Reserved for future use
 *         Bit 2: Reserved for future use
 *         Bit 1: Reserved for future use
 *
 * @param dataLen
 *     Length of the sequence data: 0 or 4 to 25 bytes
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
device_enableBlueLED(IN BYTE * data, IN int dataLen);

/**
 * Use this function to clear the LCD display
 *
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
device_lcdDisplayClear();

/**
 * Enable or disable the external LCD message
 *   It will turn off the external LCD messages including EMV
 *   transactions.  (For the users who only need MSR and/or CTLS
 *   transactions.)
 *   The function only works for VP5300
 *
 *    @param enableExtLCDMsg  1 = ON, 0 = OFF
 *    @return success or error code.  Values can be parsed
 *           with device_getIDGStatusCodeString
 *    @see ErrorCode
 */
int
device_enableExternalLCDMessages(IN int enableExtLCDMsg);

/**
 * Enable or disable the RF Antenna
 *
 *
 *    @param enableAntenna  1 = ON, 0 = OFF
 *    @return success or error code.  Values can be parsed with device_getIDGStatusCodeString
 *    @see ErrorCode
 */
int
device_enableRFAntenna(IN int enableAntenna);

/**
 * Use this function to turn off the ViVOpay Vendi reader yellow
 * LED. This LED is located below the three blue LEDs
 *
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
device_turnOffYellowLED();

/**
 * Use this function to turn on the ViVOpay Vendi reader yellow
 * LED. This LED is located below the three blue LEDs
 *
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
device_turnOnYellowLED();

/**
 * Use this function to make the buzzer beep once
 *
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
device_buzzerOnOff();

/**
 * Use this function to display text on the LCD display.
 *     On the Vendi reader the LCD is a 2-line character display.
 *
 * @param message
 *     Valid messages for the first line of text are between 1 and 16
 *     printable characters long.
 *     If the text message is greater than 16 bytes but not more than 32 bytes,
 *     byte 17 and onward are displayed as a second row of text.
 *     All messages are left justified on the LCD display.
 *
 * @param messageLen
 *     Length of the message: 1 to 32 bytes
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
device_lcdDisplayLine1Message(IN BYTE * message,
  IN int                                messageLen);

/**
 * Use this function to display the message on line 2 of the LCD display.
 *     On the Vendi reader the LCD is a 2-line character display.
 *
 * @param message
 *     Valid messages are between 1 and 16 printable characters long.
 *     All messages are left justified on the LCD display.
 *
 * @param messageLen
 *     Length of the message: 1 to 16 bytes
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
device_lcdDisplayLine2Message(IN BYTE * message,
  IN int                                messageLen);

/**
 * Start QR Code Scanning
 *
 * Enables QR Code scanning with the default window, waiting for the QR code.
 * @param timeout QR Code Scan Timeout Value.  Between 30 and 65536 seconds.
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 * Note: if auto poll mode is on, it will return command not allowed error
 */
int
device_startQRCodeScan(IN int _timeout);

/**
 * Start QR Code Scanning with Display Window Info
 *
 * Enables QR Code scanning, waiting for the QR code.
 * @param timeout QR Code Scan Timeout Value.  Between 30 and 65536 seconds.
 * @param x the x-coordinate of the display window.
 * @param y the y-coordinate of the display window.
 * @param width the width of the display window.
 * @param height the height of the display window.
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 * Note: if auto poll mode is on, it will return command not allowed error
 */
int
device_startQRCodeScanWithDisplayWindowInfo(IN int _timeout, IN int x, IN int y, IN int width, IN int height);

/**
 * Stop QR Code Scanning
 * Cancels QR Code scanning request.
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
device_stopQRCodeScan();

/**
 * Start Taking Photo
 *
 * Enables the camera to take a photo.
 * @param timeout Photo taking Timeout Value.  Between 30 and 65536 seconds.
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 * Note: if auto poll mode is on, it will return command not allowed error
 */
int
device_startTakingPhoto(IN int _timeout);

/**
 * Stop Taking Photo
 * Cancels Photo Taking request.
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
device_stopTakingPhoto();

/**
 * Stop Audio
 *  This command stops the audio the reader is playing.
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
device_stopAudio();

/**
 * Play Audio
 *  This command command plays an audio file loaded from the inserted SD card. The VP6800 supports 16bit PCM format .WAV files.
 * @param filename Complete path and file name of the wav file you want to play.
 *   You do not need to specify the root directory. Indicate subdirectories with a forward slash (/).
 * @param filenameLen File Name Length.  Maximum file name length is 30.
 * @param onSD 0: use internal memory (the Maximum audio file in Flash is 5M and only 2 audio file is supported), 1: use SD card
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
device_playAudio(IN char * fileName, IN int fileNameLen, IN int onSD);

/**
 * Get Audio Volume
 *  This command retrieves the reader’s audio volume.
 * @param volume Value 0-20, where 0 is silent and 20 is full volume
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
device_getAudioVolume(OUT BYTE * volume);

/**
 * Set Audio Volume
 *  This command sets the reader’s audio volume.
 * @param Value 0-20, where 0 is silent and 20 is full volume
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
device_setAudioVolume(IN BYTE volume);

/**
 * Get Camera Parameters
 *  This command is used to get the camera parameters (e.g., auto/fixed focal length as focus).
 * @param isAutoFocus: 0: fixed focus, 1: auto focus
 * @param focalLength: focal length Value 0x00-0xFF, where 0x00 is the farthest, 0xFF is nearest.  Not used for auto focus.
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
device_getCameraParameters(OUT BYTE * isAutoFocus, OUT BYTE * focalLength);

/**
 * Set Camera Parameters
 *  This command is used to set the camera parameters (e.g., auto/fixed focal length as focus).
 * @param isAutoFocus: 0: fixed focus, 1: auto focus
 * @param focalLength: focal length Value 0x00-0xFF, where 0x00 is the farthest, 0xFF is nearest. Not used for auto focus.
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
device_setCameraParameters(IN BYTE isAutoFocus, IN BYTE focalLength);

/**
 * Get SDK Wait Time
 *
 * Get the SDK wait time for transactions
 *
 * @return SDK wait time in seconds
 *
 */
int
device_getSDKWaitTime();

/**
 * Set SDK Wait Time
 *
 * Set the SDK wait time for transactions
 *
 *
 * @param waitTime The SDK wait time for transaction in seconds
 *
 */
void
device_setSDKWaitTime(int waitTime);

/**
 * Get Thread Stack Size
 *
 * Get the stack size setting for newly created threads
 *
 * @return Thread Stack Size
 *
 */
int
device_getThreadStackSize();

/**
 * Set Thread Stack Size
 *
 * Set the stack size setting for newly created threads
 *
 *
 */
void
device_setThreadStackSize(int threadSize);

/**
 * To SD Card
 *
 * Set the destination of the file or directory function
 *
 * @param forSDCard 0: for internal memory, 1: for SD card
 *
 */
void
device_toSDCard(int forSDCard);

/**
 * Get Tamper Status
 *  This command check the tamper status for NEO 2 readers.
 * @param isTampered 1: the reader is tampered. 0: the reader is not tampered.
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
device_getTamperStatus(OUT int * isTampered);

/**
 * ICC Function enable/disable - AUGUSTA
 * Enable ICC function with or without seated notification
 *
 * @param withNotification
 *  - 1:  with notification when ICC seated status changed,
 *  - 0: without notification.
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString
 */
int
icc_enable(IN int withNotification);

/**
 * ICC Function enable/disable - AUGUSTA
 * Disable ICC function
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString
 */
int
icc_disable();

/**
 * Power On ICC
 *
 * Power up the currently selected microprocessor card in the ICC reader
 * @param ATR, the ATR data response when succeeded power on ICC,
 * @param inLen, the length of ATR data
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 */
int
icc_powerOnICC(OUT BYTE * ATR,
  IN_OUT int *            inLen);

/**
 * Power Off ICC
 *
 * Powers down the ICC
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 *
 * If Success, empty
 * If Failure, ASCII encoded data of error string
 */
int
icc_powerOffICC();

/**
 * Exchange APDU with plain text - AUGUSTA
 * For Non-SRED Augusta Only
 *
 * Sends an APDU packet to the ICC.  If successful, response is the
 * APDU data in response parameter.
 *
 * @param c_APDU    APDU data packet
 * @param cLen     APDU data packet length
 * @param reData    Unencrypted APDU response
 * @param reLen      Unencrypted APDU response data length
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString
 */
int
icc_exchangeAPDU(IN BYTE * c_APDU,
  IN int                   cLen,
  OUT BYTE *               reData,
  IN_OUT int *             reLen);

/**
 * Exchange APDU with encrypted data - AUGUSTA
 * For SRED Augusta Only
 *
 * Sends an APDU packet to the ICC.  If successful, response is the
 * APDU data in response parameter.
 *
 * @param c_APDU    KSN + encytpted APDU data packet, or no KSN (use last known KSN) + encrypted APDU data packet
 *            With KSN:  [0A][KSN][Encrypted C-APDU]
 *            Without KSN:  [00][Encrypted C-APDU]
 *
 *    The format of Raw C-APDU Data Structure of [m-bytes Encrypted C-APDU] is below:
 *     - m = 2 bytes Valid C-APDU Length + x bytes Valid C-APDU + y bytes Padding (0x00)
 *    Note:
 *    For TDES mode: 2+x should be multiple of 8. If it was not multiple of 8, unit should padded y bytes 0x00 automatically (2+x+y should be multiple of 8).
 *    For AES mode: 2+x should be multiple of 16. If it was not multiple of 16, unit should padded y bytes 0x00 automatically (2+x+y should be multiple of 16).
 * @param cLen  data packet length
 * @param reData    response encrypted APDU response.  Can be three options:
 *   - [00] + [Plaintext R-APDU]
 *   - [01] + [0A] + [KSN] + [n bytes Encrypted R-APDU without Status Bytes]    + [2 bytes Status Bytes]
 *   - [01] + [00] + [n bytes Encrypted R-APDU without Status Bytes]    + [2 bytes Status Bytes]
 *
 *    The KSN, when provided, will be 10 bytes.  The KSN will only be provided when
 *    it has changed since the last provided KSN.  Each card Power-On generates a new KSN.
 *    During a sequence of commands where the KSN is identical, the first response
 *    will have a KSN length set to [0x0A] followed by the KSN, while subsequent
 *    commands with the same KSN value will have a KSN length of [0x00] followed by the
 *    Encrypted R-APDU without Status Bytes.
 * @param reLen       encrypted APDU response data length
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString
 */
int
icc_exchangeEncryptedAPDU(IN BYTE * c_APDU,
  IN int                            cLen,
  OUT BYTE *                        reData,
  IN_OUT int *                      reLen);

/**
 * Get APDU KSN - AUGUSTA
 *
 * Retrieves the KSN used in ICC Encypted APDU usage
 *
 * @param KSN Returns the encrypted APDU packet KSN
 * @param inLen KSN data length
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString
 */
int
icc_getAPDU_KSN(OUT BYTE * KSN,
  IN_OUT int *             inLen);

/**
 * Get ICC Function status - AUGUSTA
 * Get ICC Function status about enable/disable and with or without
 * seated notification
 *
 * @param enabled
 * - 1:    ICC Function enabled,
 * - 0: means disabled.
 * @param withNotification 1 means with notification when ICC seated status
 *    changed. 0 means without notification.
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString
 */
int
icc_getFunctionStatus(OUT int * enabled,
  OUT int *                     withNotification);

/**
 * Get Reader Status - AUGUSTA
 *
 * Returns the reader status
 *
 * @param status Pointer that will return with the ICCReaderStatus results.
 *    bit 0:  0 = ICC Power Not Ready, 1 = ICC Powered
 *    bit 1:  0 = Card not seated, 1 = card seated
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString
 */
int
icc_getICCReaderStatus(OUT BYTE * status);

/**
 * Get Key Format For DUKPT - AUGUSTA
 *
 * Specifies how data will be encrypted with Data Key or PIN key (if
 * DUKPT key loaded). This applies to both MSR and ICC
 *
 * @param format Response returned from method:
 * - 'TDES': Encrypted card data with TDES if DUKPT Key had been loaded.(default)
 * - 'AES': Encrypted card data with AES if DUKPT Key had been loaded.
 * - 'NONE': No Encryption.
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString
 */
int
icc_getKeyFormatForICCDUKPT(OUT BYTE * format);

/**
 * Get Key Type for DUKPT - AUGUSTA
 *
 * Specifies the key type used for ICC DUKPT encryption This applies
 * to both MSR and ICC
 *
 * @param type Response returned from method:
 * - 'DATA': Encrypted card data with Data Key DUKPT Key had been loaded.
 *          (default)
 * - 'PIN': Encrypted card data with PIN Key if DUKPT Key had been loaded.
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString
 */
int
icc_getKeyTypeForICCDUKPT(OUT BYTE * type);

/**
 * Set Key Format for DUKPT - AUGUSTA
 *
 * Sets how data will be encrypted, with either TDES or AES (if DUKPT
 * key loaded) This applies to both MSR and ICC
 *
 * @param format encryption Encryption Type
 * - 00: Encrypt with TDES
 * - 01: Encrypt with AES
 * - 02: Encrypt with TransArmor - AUGUSTA only
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString
 */
int
icc_setKeyFormatForICCDUKPT(IN BYTE format);

/**
 * Set Key Type for DUKPT Key - AUGUSTA
 *
 * Sets which key the data will be encrypted with, with either Data
 * Key or PIN key (if DUKPT key loaded) This applies to both MSR and
 * ICC
 *
 * @param type Encryption Type
 * - 00: Encrypt with Data Key
 * - 01: Encrypt with PIN Key
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString
 */
int
icc_setKeyTypeForICCDUKPT(IN BYTE type);

/**
 * Get the ISO8583 1987 version handler.
 *
 * @param ISOHandler A handler with knowledge of the ISO8583 1987 version fields
 *
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
iso8583_get1987Handler(OUT DL_ISO8583_HANDLER * ISOHandler);

/**
 * Get the ISO8583 1993 version handler.
 *
 * @param ISOHandler A handler with knowledge of the ISO8583 1993 version fields
 *
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
iso8583_get1993Handler(OUT DL_ISO8583_HANDLER * ISOHandler);

/**
 * Get the ISO8583 2003 version handler.
 *
 * @param ISOHandler A handler with knowledge of the ISO8583 2003 version fields
 *
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
iso8583_get2003Handler(OUT DL_ISO8583_HANDLER * ISOHandler);

/**
 * Get the specified field's information using the data field.
 *
 * @param dataField - The data field number
 * @param ISOHandler - The ISO8583 handler
 * @param field - The requested field
 *
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
iso8583_getField(IN DL_UINT16 dataField,
  IN DL_ISO8583_HANDLER *     ISOHandler,
  OUT DL_ISO8583_FIELD_DEF *  field);

/**
 * Initialize the ISO8583 message structure.
 *
 * @param ISOMessage - The initialized ISO8583 message structure
 *
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
iso8583_initializeMessage(OUT DL_ISO8583_MSG * ISOMessage);

/**
 * Get the specified message field using the data field.
 *
 * @param dataField - The data field number
 * @param ISOMessage - The ISO8583 message structure
 * @param messageField - The requested message field
 *
 * @return 0 if the if the setting was applied; otherwise, return -1 on failure
 */
int
iso8583_getMessageField(IN DL_UINT16 dataField,
  IN DL_ISO8583_MSG *                ISOMessage,
  OUT DL_ISO8583_MSG_FIELD *         messageField);

/**
 * Set the specified message field.
 *
 * @param dataField - The data field number
 * @param data - The data to apply
 * @param ISOMessage - The ISO8583 message structure
 *
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
iso8583_setMessageField(IN DL_UINT16 dataField,
  IN const DL_UINT8 *                data,
  OUT DL_ISO8583_MSG *               ISOMessage);

/**
 * Remove the specified message field.
 *
 * @param dataField - The data field number
 * @param ISOMessage - The ISO8583 message structure
 *
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
iso8583_removeMessageField(IN DL_UINT16 dataField,
  OUT DL_ISO8583_MSG *                  ISOMessage);

/**
 * Pack the message fields into an array.
 *
 * @param ISOHandler - The ISO8583 handler
 * @param ISOMessage - The ISO8583 message structure
 * @param packedData - The packaged data
 * @param packedDataLength - The packaged data's length
 *
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
iso8583_packMessage(IN const DL_ISO8583_HANDLER * ISOHandler,
  IN const DL_ISO8583_MSG *                       ISOMessage,
  OUT DL_UINT8 *                                  packedData,
  OUT DL_UINT16 *                                 packedDataLength);

/**
 * Unpack the message field array into the ISO8583 message structure.
 *
 * @param ISOHandler - The ISO8583 handler
 * @param packedData - The packaged data
 * @param packedDataLength - The packaged data's length
 * @param ISOMessage - The ISO8583 message structure
 *
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
iso8583_unpackMessage(IN const DL_ISO8583_HANDLER * ISOHandler,
  IN const DL_UINT8 *                               packedData,
  IN DL_UINT16                                      packedDataLength,
  OUT DL_ISO8583_MSG *                              ISOMessage);

/**
 * Deallocate the ISO8583 message structure's memory.
 *
 * @param ISOMessage - The ISO8583 message structure
 *
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
iso8583_freeMessage(IN DL_ISO8583_MSG * ISOMessage);

/**
 * Serialize the message fields into an XML format.
 *
 * @param ISOHandler - The ISO8583 handler
 * @param ISOMessage - The ISO8583 message structure
 * @param serializedMessage - The XML-formatted message
 * @param serializedMessageLength - The XML message's length
 *
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
iso8583_serializeToXML(IN DL_ISO8583_HANDLER * ISOHandler,
  IN DL_ISO8583_MSG *                          ISOMessage,
  OUT BYTE *                                   serializedMessage,
  OUT int *                                    serializedMessageLength);

/**
 * Deserialize the XML-formatted ISO8583 message.
 *
 * @param serializedMessage - The XML-formatted message
 * @param serializedMessageLength - The length of the XML-formatted message
 * @param ISOHandler - A null ISO8583 handler
 * @param ISOMessage - The ISO8583 message structure
 *
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
iso8583_deserializeFromXML(IN BYTE * serializedMessage,
  IN int                             serializedMessageLength,
  OUT DL_ISO8583_HANDLER *           ISOHandler,
  OUT DL_ISO8583_MSG *               ISOMessage);

/**
 * Display the messages in a formatted manner on the screen for
 * verifying results.
 *
 * @param ISOHandler - The ISO8583 handler
 * @param ISOMessage - The ISO8583 message structure
 *
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
iso8583_displayMessage(IN DL_ISO8583_HANDLER * ISOHandler,
  IN DL_ISO8583_MSG *                          ISOMessage);

/**
 * Reset to Initial State.
 *	This command places the reader UI into the
 *  idle state and displays the appropriate idle display.
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
lcd_resetInitialState();

/**
 * Custom Display Mode
 *  Controls the LCD display mode to custom display. Keyboard entry is
 *  limited to the Cancel, Clear, Enter and the function keys, if
 *  present. PIN entry is not permitted while the reader is in Custom
 *  Display Mode
 *
 * @param enable TRUE = enabled, FALSE = disabled
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
lcd_customDisplayMode(IN int enable);

/**
 * Set Foreground and Background Color
 *  This command sets the foreground and background colors of the LCD.
 *
 * @param foreRGB Foreground RGB. 000000 = black, FF0000 = red, 00FF00 = green, 0000FF = blue, FFFFFF = white
 * @param Length of foreRGB.  Must be 3.
 * @param backRGB Background RGB. 000000 = black, FF0000 = red, 00FF00 = green, 0000FF = blue, FFFFFF = white
 * @param Length of backRGB.  Must be 3.
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
lcd_setForeBackColor(IN BYTE * foreRGB,
  IN int                       foreRGBLen,
  IN BYTE *                    backRGB,
  IN int                       backRGBLen);

/**
 * Clear Display
 *  Command to clear the display screen on the reader. It returns the
 *  display to the currently defined background color and terminates
 *  all events
 *
 * @param control for L80 and L100 only.
 *     0:First Line
 *             1:Second Line
 *             2:Third Line
 *             3:Fourth Line
 *             0xFF: All Screen
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
lcd_clearDisplay(IN BYTE control);

/**
 * Enables Signature Capture
 *  This command executes the signature capture screen.  Once a
 *  signature is captured, it is sent to the callback with
 *  DeviceState.Signature, and the data will contain a .png of the
 *  signature
 *
 * @param timeout  Timeout waiting for the signature capture
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
lcd_captureSignature(IN int timeout);

/**
 * Start slide show
 *  You must send images to the reader's memory and send a Start
 *  Custom Mode command to the reader before it will respond to this
 *  commands. Image files must be in .bmp or .png format.
 *
 * @param files Complete paths and file names of the files you want to use,
 *  separated by commas. If a directory is specified, all files in the dirctory
 *  are displayed
 * @param filesLen Length of files
 * @param posX X coordinate in pixels, Range 0-271
 * @param posY Y coordinate in pixels, Range 0-479
 * @param posMode Position Mode
 *  - 0 = Center on Line Y
 *  - 1 = Display at (X, Y)
 *  - 2 - Center on screen
 * @param touchEnable TRUE = Image is touch sensitive
 * @param recursion TRUE = Recursively follow directorys in list
 * @param touchTerminate TRUE = Terminate slideshow on touch (if touch enabled)
 * @param delay Number of seconds between image displays
 * @param loops  Number of display loops.  A zero indicates continuous display
 * @param clearScreen  TRUE = Clear screen
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
lcd_startSlideShow(IN char * files,
  IN int                     filesLen,
  IN int                     posX,
  IN int                     posY,
  IN int                     posMode,
  IN int                     touchEnable,
  IN int                     recursion,
  IN int                     touchTerminate,
  IN int                     delay,
  IN int                     loops,
  IN int                     clearScreen);

/**
 * Cancel slide show
 *  Cancel the slide show currently running
 *
 * @param statusCode If the return code is not Success (0), the kernel may
 * return a four-byte Extended Status Code
 * @param statusCodeLen the length of the Extended Status Code (should be
 * 4 bytes)
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
lcd_cancelSlideShow(OUT BYTE * statusCode,
  IN_OUT int *                 statusCodeLen);

/**
 * Set Display Image
 *  You must send images to the reader's memory and send a Start
 *  Custom Mode command to the reader before it will respond to Image
 *  commands. Image files must be in .bmp or .png format.
 *
 * @param file Complete path and file name of the file you want to
 * use. Example "file.png" will put in root directory, while
 * "ss/file.png" will put in ss directory (which must exist)
 * @param fileLen Length of files
 * @param posX X coordinate in pixels, Range 0-271
 * @param posY Y coordinate in pixels, Range 0-479
 * @param posMode Position Mode
 *  - 0 = Center on Line Y
 *  - 1 = Display at (X, Y)
 *  - 2 - Center on screen
 * @param touchEnable TRUE = Image is touch sensitive
 * @param clearScreen  TRUE = Clear screen
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
lcd_setDisplayImage(IN char * file,
  IN int                      fileLen,
  IN int                      posX,
  IN int                      posY,
  IN int                      posMode,
  IN int                      touchEnable,
  IN int                      clearScreen);

/**
 * Set Background Image
 *  You must send images to the reader?�驴?�s memory and send a Start
 *  Custom Mode command to the reader before it will respond to Image
 *  commands. Image files must be in .bmp or .png format.
 *
 * @param file Complete path and file name of the file you want to
 * use. Example "file.png" will put in root directory, while
 * "ss/file.png" will put in ss directory (which must exist)
 * @param fileLen Length of files
 * @param enable TRUE = Use Background Image, FALSE = Use Background Color
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
lcd_setBackgroundImage(IN char * file, IN int fileLen, IN int enable);

/**
 * DEPRECATED : please use lcd_displayText_Len(IN int posX, IN int posY, IN int displayWidth,
 *		IN int displayHeight, IN int fontDesignation, IN int fontID,
 *		IN int screenPosition, IN char *displayText, OUT BYTE *graphicsID, IN_OUT int *graphicsIDLen)
 *
 * Displays text.
 *
 * Custom Display Mode must be enabled for custom text.
 * PIN pad entry is not allowed in Custom Display Mode but the Cancel, OK, and Clear keys remain active.
 *
 * @param posX X coordinate in pixels
 * @param posY Y coordinate in pixels
 * @param displayWidth Width of the display area in pixels (optional)
 * @param displayHeight Height of the display area in pixels (optional)
 * @param fontDesignation Font designation
 *  1 - Default
 * @param FontID Font styling
 *  | Font ID | Height in pixels | Font Properties                     |
 *
 *  | ------- | ---------------- | ----------------------------------- |
 *
 *  | 1       | 13               | Regular                             |
 *
 *  | 2       | 17               | Regular                             |
 *
 *  | 3       | 17               | Bold                                |
 *
 *  | 4       | 22               | Regular                             |
 *
 *  | 5       | 20               | Regular                             |
 *
 *  | 6       | 20               | Bold                                |
 *
 *  | 7       | 29               | Regular                             |
 *
 *  | 8       | 38               | Regular                             |
 *
 *  | 9       | 38               | Bold                                |
 *
 *  | 10      | 58               | Regular                             |
 *
 *  | 11      | 58               | Bold, mono-space					   |
 *
 *  | 12      | 14               | Regular, mono-space, 8 pixels wide  |
 *
 *  | 13      | 15               | Regular, mono-space, 9 pixels wide  |
 *
 *  | 14      | 17               | Regular, mono-space, 9 pixels wide  |
 *
 *  | 15      | 20               | Regular, mono-space, 11 pixels wide |
 *
 *  | 16      | 21               | Regular, mono-space, 12 pixels wide |
 *
 *  | 17      | 25               | Regular, mono-space, 14 pixels wide |
 *
 *  | 18      | 30               | Regular, mono-space, 17 pixels wide |
 * @param screenPosition Display position
 *  0 - Center on line Y without clearing screen
 *  1 - Center on line Y after clearing screen
 *  2 - Display at (X, Y) without clearing screen
 *  3 - Display at (X, Y) after clearing screen
 *  4 - Display at center of screen without clearing screen
 *  5 - Display at center of screen after clearing screen
 *  6 - Display text right-justified without clearing screen
 *  7 - Display text right-justified after clearing screen
 * @param displayText Display text (Maximum: 1900 characters)
 * @param graphicsID A four byte array containing the ID of the created element (optional)
 *      if graphicsID is NULL, the SDK will not return graphicsID
 *      if graphicsID is not NULL, the SDK will return graphicsID, but it will need 4 bytes of memory
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
lcd_displayText(IN int posX, IN int posY, IN int displayWidth,
  IN int displayHeight, IN int fontDesignation, IN int fontID,
  IN int screenPosition, IN char * displayText, OUT BYTE * graphicsID);

/**
 * Displays text.
 *
 * Custom Display Mode must be enabled for custom text.
 * PIN pad entry is not allowed in Custom Display Mode but the Cancel, OK, and Clear keys remain active.
 *
 * @param posX X coordinate in pixels
 * @param posY Y coordinate in pixels
 * @param displayWidth Width of the display area in pixels (optional)
 * @param displayHeight Height of the display area in pixels (optional)
 * @param fontDesignation Font designation
 *  1 - Default
 * @param FontID Font styling
 *  | Font ID | Height in pixels | Font Properties                     |
 *
 *  | ------- | ---------------- | ----------------------------------- |
 *
 *  | 1       | 13               | Regular                             |
 *
 *  | 2       | 17               | Regular                             |
 *
 *  | 3       | 17               | Bold                                |
 *
 *  | 4       | 22               | Regular                             |
 *
 *  | 5       | 20               | Regular                             |
 *
 *  | 6       | 20               | Bold                                |
 *
 *  | 7       | 29               | Regular                             |
 *
 *  | 8       | 38               | Regular                             |
 *
 *  | 9       | 38               | Bold                                |
 *
 *  | 10      | 58               | Regular                             |
 *
 *  | 11      | 58               | Bold, mono-space					   |
 *
 *  | 12      | 14               | Regular, mono-space, 8 pixels wide  |
 *
 *  | 13      | 15               | Regular, mono-space, 9 pixels wide  |
 *
 *  | 14      | 17               | Regular, mono-space, 9 pixels wide  |
 *
 *  | 15      | 20               | Regular, mono-space, 11 pixels wide |
 *
 *  | 16      | 21               | Regular, mono-space, 12 pixels wide |
 *
 *  | 17      | 25               | Regular, mono-space, 14 pixels wide |
 *
 *  | 18      | 30               | Regular, mono-space, 17 pixels wide |
 * @param screenPosition Display position
 *  0 - Center on line Y without clearing screen
 *  1 - Center on line Y after clearing screen
 *  2 - Display at (X, Y) without clearing screen
 *  3 - Display at (X, Y) after clearing screen
 *  4 - Display at center of screen without clearing screen
 *  5 - Display at center of screen after clearing screen
 *  6 - Display text right-justified without clearing screen
 *  7 - Display text right-justified after clearing screen
 * @param displayText Display text (Maximum: 1900 characters)
 * @param graphicsID A four byte array containing the ID of the created element (optional)
 * @param graphicsIDLen Length of graphicsID (optional)
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
lcd_displayText_Len(IN int posX, IN int posY, IN int displayWidth,
  IN int displayHeight, IN int fontDesignation, IN int fontID,
  IN int screenPosition, IN char * displayText, OUT BYTE * graphicsID, IN_OUT int * graphicsIDLen);

/**
 * Displays text with scroll feature.
 *
 * Custom Display Mode must be enabled.
 *
 * @param posX X coordinate in pixels
 * @param posY Y coordinate in pixels
 * @param displayWidth Width of the display area in pixels (Minimum: 40px)
 *  0 or NULL - Use the full width to display text
 * @param displayHeight Height of the display area in pixels (Minimum: 100px)
 *  0 or NULL - Use the full height to display text
 * @param fontDesignation Font designation
 *  1 - Default
 * @param fontID Font styling
 *  | Font ID | Height in pixels | Font Properties                     |
 *
 *  | ------- | ---------------- | ----------------------------------- |
 *
 *  | 1       | 13               | Regular                             |
 *
 *  | 2       | 17               | Regular                             |
 *
 *  | 3       | 17               | Bold                                |
 *
 *  | 4       | 22               | Regular                             |
 *
 *  | 5       | 20               | Regular                             |
 *
 *  | 6       | 20               | Bold                                |
 *
 *  | 7       | 29               | Regular                             |
 *
 *  | 8       | 38               | Regular                             |
 *
 *  | 9       | 38               | Bold                                |
 *
 *  | 10      | 58               | Regular                             |
 *
 *  | 11      | 58               | Bold, mono-space					   |
 *
 *  | 12      | 14               | Regular, mono-space, 8 pixels wide  |
 *
 *  | 13      | 15               | Regular, mono-space, 9 pixels wide  |
 *
 *  | 14      | 17               | Regular, mono-space, 9 pixels wide  |
 *
 *  | 15      | 20               | Regular, mono-space, 11 pixels wide |
 *
 *  | 16      | 21               | Regular, mono-space, 12 pixels wide |
 *
 *  | 17      | 25               | Regular, mono-space, 14 pixels wide |
 *
 *  | 18      | 30               | Regular, mono-space, 17 pixels wide |
 * @param displayProperties Display properties for the text
 *  0 - Center on line Y without clearing screen
 *  1 - Center on line Y after clearing screen
 *  2 - Display at (X, Y) without clearing screen
 *  3 - Display at (X, Y) after clearing screen
 *  4 - Center on screen without clearing screen
 *  5 - Center on screen after clearing screen
 * @param displayText Display text (Maximum: 3999 characters)
 */
int
lcd_displayParagraph(IN int posX, IN int posY, IN int displayWidth,
  IN int displayHeight, IN int fontDesignation, IN int fontID,
  IN int displayProperties, IN char * displayText);

/**
 * DEPRECATED : please use lcd_displayButton_Len(IN int posX, IN int posY, IN int buttonWidth,
 *		IN int buttonHeight, IN int fontDesignation, IN int fontID,
 *		IN int displayPosition, IN char *buttonLabel, IN int buttonTextColorR,
 *		IN int buttonTextColorG, IN int buttonTextColorB, IN int buttonBackgroundColorR,
 *		IN int buttonBackgroundColorG, IN int buttonBackgroundColorB, OUT BYTE *graphicsID, IN_OUT int *graphicsIDLen)
 *
 * Displays an interactive button.
 *
 * @param posX X coordinate in pixels
 * @param posY Y coordinate in pixels
 * @param buttonWidth Width of the button
 * @param buttonHeight Height of the button
 * @param fontDesignation Font designation
 *  1 - Default
 * @param FontID Font styling
 *  | Font ID | Height in pixels | Font Properties                     |
 *
 *  | ------- | ---------------- | ----------------------------------- |
 *
 *  | 1       | 13               | Regular                             |
 *
 *  | 2       | 17               | Regular                             |
 *
 *  | 3       | 17               | Bold                                |
 *
 *  | 4       | 22               | Regular                             |
 *
 *  | 5       | 20               | Regular                             |
 *
 *  | 6       | 20               | Bold                                |
 *
 *  | 7       | 29               | Regular                             |
 *
 *  | 8       | 38               | Regular                             |
 *
 *  | 9       | 38               | Bold                                |
 *
 *  | 10      | 58               | Regular                             |
 *
 *  | 11      | 58               | Bold, mono-space					   |
 *
 *  | 12      | 14               | Regular, mono-space, 8 pixels wide  |
 *
 *  | 13      | 15               | Regular, mono-space, 9 pixels wide  |
 *
 *  | 14      | 17               | Regular, mono-space, 9 pixels wide  |
 *
 *  | 15      | 20               | Regular, mono-space, 11 pixels wide |
 *
 *  | 16      | 21               | Regular, mono-space, 12 pixels wide |
 *
 *  | 17      | 25               | Regular, mono-space, 14 pixels wide |
 *
 *  | 18      | 30               | Regular, mono-space, 17 pixels wide |
 * @param displayPosition Button display position
 *  0 - Center on line Y without clearing screen and without word wrap
 *  1 - Center on line Y after clearing screen and without word wrap
 *  2 - Display at (X, Y) without clearing screen and without word wrap
 *  3 - Display at (X, Y) after clearing screen and without word wrap
 *  4 - Center button on screen without clearing screen and without word wrap
 *  5 - Center button on screen after clearing screen and without word wrap
 *  64 - Center on line Y without clearing screen and with word wrap
 *  65 - Center on line Y after clearing the screen and with word wrap
 *  66 - Display at (X, Y) without clearing screen and with word wrap
 *  67 - Display at (X, Y) after clearing screen and with word wrap
 *  68 - Center button on screen without clearing screen and with word wrap
 *  69 - Center button on screen after clearing screen and with word wrap
 * @param buttonLabel Button label text (Maximum: 31 characters)
 * @param buttonTextColorR - Red component for foreground color (0 - 255)
 * @param buttonTextColorG - Green component for foreground color (0 - 255)
 * @param buttonTextColorB - Blue component for foreground color (0 - 255)
 * @param buttonBackgroundColorR - Red component for background color (0 - 255)
 * @param buttonBackgroundColorG - Green component for background color (0 - 255)
 * @param buttonBackgroundColorB - Blue component for background color (0 - 255)
 * @param graphicsID A four byte array containing the ID of the created element (optional)
 *      if graphicsID is NULL, the SDK will not return graphicsID
 *      if graphicsID is not NULL, the SDK will return graphicsID, but it will need 4 bytes of memory
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
lcd_displayButton(IN int posX, IN int posY, IN int buttonWidth,
  IN int buttonHeight, IN int fontDesignation, IN int fontID,
  IN int displayPosition, IN char * buttonLabel, IN int buttonTextColorR,
  IN int buttonTextColorG, IN int buttonTextColorB, IN int buttonBackgroundColorR,
  IN int buttonBackgroundColorG, IN int buttonBackgroundColorB, OUT BYTE * graphicsID);

/**
 * Displays an interactive button.
 *
 * @param posX X coordinate in pixels
 * @param posY Y coordinate in pixels
 * @param buttonWidth Width of the button
 * @param buttonHeight Height of the button
 * @param fontDesignation Font designation
 *  1 - Default
 * @param FontID Font styling
 *  | Font ID | Height in pixels | Font Properties                     |
 *
 *  | ------- | ---------------- | ----------------------------------- |
 *
 *  | 1       | 13               | Regular                             |
 *
 *  | 2       | 17               | Regular                             |
 *
 *  | 3       | 17               | Bold                                |
 *
 *  | 4       | 22               | Regular                             |
 *
 *  | 5       | 20               | Regular                             |
 *
 *  | 6       | 20               | Bold                                |
 *
 *  | 7       | 29               | Regular                             |
 *
 *  | 8       | 38               | Regular                             |
 *
 *  | 9       | 38               | Bold                                |
 *
 *  | 10      | 58               | Regular                             |
 *
 *  | 11      | 58               | Bold, mono-space					   |
 *
 *  | 12      | 14               | Regular, mono-space, 8 pixels wide  |
 *
 *  | 13      | 15               | Regular, mono-space, 9 pixels wide  |
 *
 *  | 14      | 17               | Regular, mono-space, 9 pixels wide  |
 *
 *  | 15      | 20               | Regular, mono-space, 11 pixels wide |
 *
 *  | 16      | 21               | Regular, mono-space, 12 pixels wide |
 *
 *  | 17      | 25               | Regular, mono-space, 14 pixels wide |
 *
 *  | 18      | 30               | Regular, mono-space, 17 pixels wide |
 * @param displayPosition Button display position
 *  0 - Center on line Y without clearing screen and without word wrap
 *  1 - Center on line Y after clearing screen and without word wrap
 *  2 - Display at (X, Y) without clearing screen and without word wrap
 *  3 - Display at (X, Y) after clearing screen and without word wrap
 *  4 - Center button on screen without clearing screen and without word wrap
 *  5 - Center button on screen after clearing screen and without word wrap
 *  64 - Center on line Y without clearing screen and with word wrap
 *  65 - Center on line Y after clearing the screen and with word wrap
 *  66 - Display at (X, Y) without clearing screen and with word wrap
 *  67 - Display at (X, Y) after clearing screen and with word wrap
 *  68 - Center button on screen without clearing screen and with word wrap
 *  69 - Center button on screen after clearing screen and with word wrap
 * @param buttonLabel Button label text (Maximum: 31 characters)
 * @param buttonTextColorR - Red component for foreground color (0 - 255)
 * @param buttonTextColorG - Green component for foreground color (0 - 255)
 * @param buttonTextColorB - Blue component for foreground color (0 - 255)
 * @param buttonBackgroundColorR - Red component for background color (0 - 255)
 * @param buttonBackgroundColorG - Green component for background color (0 - 255)
 * @param buttonBackgroundColorB - Blue component for background color (0 - 255)
 * @param graphicsID A four byte array containing the ID of the created element (optional)
 * @param graphicsIDLen Length of graphicsID (optional)
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
lcd_displayButton_Len(IN int posX, IN int posY, IN int buttonWidth,
  IN int buttonHeight, IN int fontDesignation, IN int fontID,
  IN int displayPosition, IN char * buttonLabel, IN int buttonTextColorR,
  IN int buttonTextColorG, IN int buttonTextColorB, IN int buttonBackgroundColorR,
  IN int buttonBackgroundColorG, IN int buttonBackgroundColorB, OUT BYTE * graphicsID, IN_OUT int * graphicsIDLen);

/**
 * DEPRECATED : please use lcd_createList_Len(IN int posX, IN int posY, IN int numOfColumns,
 *		IN int numOfRows, IN int fontDesignation, IN int fontID,
 *		IN int verticalScrollArrowsVisible, IN int borderedListItems, IN int borderdScrollArrows,
 *		IN int touchSensitive, IN int automaticScrolling, OUT BYTE *graphicsID, IN_OUT int *graphicsIDLen)
 *
 * Creates a display list.
 *
 * @param posX X coordinate in pixels
 * @param posY Y coordinate in pixels
 * @param numOfColumns Number of columns to display
 * @param numOfRows Number of rows to display
 * @param fontDesignation Font Designation
 *  1 - Default font
 * @param fontID Font styling
 *  | Font ID | Height in pixels | Font Properties                     |
 *
 *  | ------- | ---------------- | ----------------------------------- |
 *
 *  | 1       | 13               | Regular                             |
 *
 *  | 2       | 17               | Regular                             |
 *
 *  | 3       | 17               | Bold                                |
 *
 *  | 4       | 22               | Regular                             |
 *
 *  | 5       | 20               | Regular                             |
 *
 *  | 6       | 20               | Bold                                |
 *
 *  | 7       | 29               | Regular                             |
 *
 *  | 8       | 38               | Regular                             |
 *
 *  | 9       | 38               | Bold                                |
 *
 *  | 10      | 58               | Regular                             |
 *
 *  | 11      | 58               | Bold, mono-space					   |
 *
 *  | 12      | 14               | Regular, mono-space, 8 pixels wide  |
 *
 *  | 13      | 15               | Regular, mono-space, 9 pixels wide  |
 *
 *  | 14      | 17               | Regular, mono-space, 9 pixels wide  |
 *
 *  | 15      | 20               | Regular, mono-space, 11 pixels wide |
 *
 *  | 16      | 21               | Regular, mono-space, 12 pixels wide |
 *
 *  | 17      | 25               | Regular, mono-space, 14 pixels wide |
 *
 *  | 18      | 30               | Regular, mono-space, 17 pixels wide |
 * @param verticalScrollArrowsVisible Display vertical scroll arrows by default
 * @param borederedListItems Draw border around list items
 * @param borederedScrollArrows Draw border around scroll arrows (if visible)
 * @param touchSensitive List items are touch enabled
 * @param automaticScrolling Enable automatic scrolling of list when new items exceed display area
 * @param graphicsID A four byte array containing the ID of the created element (optional)
 *      if graphicsID is NULL, the SDK will not return graphicsID
 *      if graphicsID is not NULL, the SDK will return graphicsID, but it will need 4 bytes of memory
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
lcd_createList(IN int posX, IN int posY, IN int numOfColumns,
  IN int numOfRows, IN int fontDesignation, IN int fontID,
  IN int verticalScrollArrowsVisible, IN int borderedListItems, IN int borderdScrollArrows,
  IN int touchSensitive, IN int automaticScrolling, OUT BYTE * graphicsID);

/**
 * Creates a display list.
 *
 * @param posX X coordinate in pixels
 * @param posY Y coordinate in pixels
 * @param numOfColumns Number of columns to display
 * @param numOfRows Number of rows to display
 * @param fontDesignation Font Designation
 *  1 - Default font
 * @param fontID Font styling
 *  | Font ID | Height in pixels | Font Properties                     |
 *
 *  | ------- | ---------------- | ----------------------------------- |
 *
 *  | 1       | 13               | Regular                             |
 *
 *  | 2       | 17               | Regular                             |
 *
 *  | 3       | 17               | Bold                                |
 *
 *  | 4       | 22               | Regular                             |
 *
 *  | 5       | 20               | Regular                             |
 *
 *  | 6       | 20               | Bold                                |
 *
 *  | 7       | 29               | Regular                             |
 *
 *  | 8       | 38               | Regular                             |
 *
 *  | 9       | 38               | Bold                                |
 *
 *  | 10      | 58               | Regular                             |
 *
 *  | 11      | 58               | Bold, mono-space					   |
 *
 *  | 12      | 14               | Regular, mono-space, 8 pixels wide  |
 *
 *  | 13      | 15               | Regular, mono-space, 9 pixels wide  |
 *
 *  | 14      | 17               | Regular, mono-space, 9 pixels wide  |
 *
 *  | 15      | 20               | Regular, mono-space, 11 pixels wide |
 *
 *  | 16      | 21               | Regular, mono-space, 12 pixels wide |
 *
 *  | 17      | 25               | Regular, mono-space, 14 pixels wide |
 *
 *  | 18      | 30               | Regular, mono-space, 17 pixels wide |
 * @param verticalScrollArrowsVisible Display vertical scroll arrows by default
 * @param borederedListItems Draw border around list items
 * @param borederedScrollArrows Draw border around scroll arrows (if visible)
 * @param touchSensitive List items are touch enabled
 * @param automaticScrolling Enable automatic scrolling of list when new items exceed display area
 * @param graphicsID A four byte array containing the ID of the created element (optional)
 * @param graphicsIDLen Length of graphicsID (optional)
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
lcd_createList_Len(IN int posX, IN int posY, IN int numOfColumns,
  IN int numOfRows, IN int fontDesignation, IN int fontID,
  IN int verticalScrollArrowsVisible, IN int borderedListItems, IN int borderdScrollArrows,
  IN int touchSensitive, IN int automaticScrolling, OUT BYTE * graphicsID, IN_OUT int * graphicsIDLen);

/**
 * Adds an item to an existing list.
 *
 * Custom Display Mode must be enabled for custom text.
 *
 * @param listGraphicsID Existing list's graphics ID (4 byte array) that is provided during creation
 * @param itemName Item name (Maximum: 127 characters)
 * @param itemID Identifier for the item (Maximum: 31 characters)
 * @param selected If the item should be selected
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
lcd_addItemToList(IN BYTE * listGraphicsID, IN char * itemName, IN char * itemID,
  IN int selected);

/**
 * DEPRECATED : please use lcd_getSelectedListItem_Len(IN BYTE *listGraphicsID, OUT char *itemID, IN_OUT int *itemIDLen)
 *
 * Retrieves the selected item's ID.
 *
 * @param listGraphicsID Existing list's graphics ID (4 byte array) that is provided during creation
 * @param itemID The selected item's ID (Maximum: 32 characters) Need 33 bytes of memory including '\0'
 */
int
lcd_getSelectedListItem(IN BYTE * listGraphicsID, OUT char * itemID);

/**
 * Retrieves the selected item's ID.
 *
 * @param listGraphicsID Existing list's graphics ID (4 byte array) that is provided during creation
 * @param itemID The selected item's ID (Maximum: 32 characters) Need 33 bytes of memory including '\0'
 * @param itemIDLen Length of itemID
 */
int
lcd_getSelectedListItem_Len(IN BYTE * listGraphicsID, OUT char * itemID, IN_OUT int * itemIDLen);

/**
 * Removes all entries from the event queue.
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
lcd_clearEventQueue();

/**
 * DEPRECATED : please use lcd_getInputEvent_Len(IN int timeout, OUT int *dataReceived, OUT BYTE *eventType, IN_OUT int *eventTypeLen,
 *		OUT BYTE *graphicsID, IN_OUT int *graphicsIDLen, OUT BYTE *eventData, IN_OUT int *eventDataLen)
 *
 * Requests input from the reader.
 *
 * @param timeout Timeout amount in seconds
 *  0 - No timeout
 * @param dataReceived Indicates if an event occurred and data was received
 *  0 - No data received
 *  1 - Data received
 * @param eventType The event type (required to be at least 4 bytes), see table below
 * @param graphicsID The graphicID of the event (required to be at least 4 bytes)
 * @param eventData The event data, see table below (required to be at least 73 bytes)
 * | Event Type         | Value (4 bytes) | Event Specific Data                                                 |
 *
 * | ------------------ | --------------- | ------------------------------------------------------------------- |
 *
 * | Button Event       | 00030000h       | Length = Variable												    |
 *
 * |				    |				  |	Byte 1: State (1 = Pressed, other values RFU)					    |
 *
 * |					|				  |	Byte 2 - n: Null terminated caption                                 |
 *
 * | ------------------ | --------------- | ------------------------------------------------------------------- |
 *
 * | Checkbox Event     | 00030001h       | Length = 1 byte													    |
 *
 * |					|			      |	Byte 1: State (1 = Checked, 0 = Unchecked)						    |
 *
 * | ------------------ | --------------- | ------------------------------------------------------------------- |
 *
 * | Line Item Event    | 00030002h       | Length = 5 bytes												    |
 *
 * |					|				  |	Byte 1: State (1 = Item Selected, other values RFU)				    |
 *
 * |					|				  |	Byte 2 - n: Caption of the selected item						    |
 *
 * | ------------------ | --------------- | ------------------------------------------------------------------- |
 *
 * | Keypad Event       | 00030003h       | Length - 3 bytes												    |
 *
 * |					|				  | Byte 1: State (1 = key pressed, 2 = key released, other values RFU) |
 *
 * |					|				  | Byte 2 - 3: Key pressed and Key release                             |
 *
 * |					|				  |		0030h - KEYPAD_KEY_0											|
 *
 * |					|				  |		0031h - KEYPAD_KEY_1											|
 *
 * |					|				  |		0032h - KEYPAD_KEY_2											|
 *
 * |					|				  |		0033h - KEYPAD_KEY_3											|
 *
 * |					|				  |		0034h - KEYPAD_KEY_4											|
 *
 * |					|				  |		0035h - KEYPAD_KEY_5											|
 *
 * |					|				  |		0036h - KEYPAD_KEY_6											|
 *
 * |					|				  |		0037h - KEYPAD_KEY_7											|
 *
 * |					|				  |		0038h - KEYPAD_KEY_8											|
 *
 * |					|				  |		0039h - KEYPAD_KEY_9											|
 *
 * |					|				  | Byte 2 - 3: Only Key pressed										|
 *
 * |					|				  |     000Dh - KEYPAD_KEY_ENTER										|
 *
 * |					|				  |     0008h - KEYPAD_KEY_CLEAR										|
 *
 * |					|				  |     001Bh - KEYPAD_KEY_CANCEL										|
 *
 * |					|				  |     0070h - FUNC_KEY_F1 (Vend III)									|
 *
 * |					|				  |     0071h - FUNC_KEY_F2 (Vend III)									|
 *
 * |					|				  |     0072h - FUNC_KEY_F3 (Vend III)									|
 *
 * |					|				  |     0073h - FUNC_KEY_F4 (Vend III)									|
 *
 * | ------------------ | --------------- | ------------------------------------------------------------------- |
 *
 * | Touchscreen Event  | 00030004h       | Length = 1 - 33 bytes												|
 *
 * |					|				  | Byte 1: State (not used)											|
 *
 * |					|				  | Byte 2 - 33: Image name (zero terminated)							|
 *
 * | ------------------ | --------------- | ------------------------------------------------------------------- |
 *
 * | Slideshow Event    | 00030005h       | Length = 1 byte														|
 *
 * |					|				  | Byte 1: State (not used)											|
 *
 * | ------------------ | --------------- | ------------------------------------------------------------------- |
 *
 * | Transaction Event  | 00030006h       | Length = 9 bytes													|
 *
 * |					|				  | Byte 1: State (not used)											|
 *
 * |					|				  | Byte 2 - 5: Card type (0 = unknown)									|
 *
 * |					|				  | Byte 6 - 9: Status - A four byte, big-endian field					|
 *
 * |					|				  |	Byte 9 is used to store the 1-byte status code						|
 *
 * |					|				  |		00 - SUCCESS													|
 *
 * |					|				  |		08 - TIMEOUT													|
 *
 * |					|				  |		0A - FAILED														|
 *
 * |					|				  | This is not related to the extended status codes					|
 *
 * | ------------------ | --------------- | ------------------------------------------------------------------- |
 *
 * | Radio Button Event | 00030007h       | Length = 73 bytes													|
 *
 * |					|				  | Byte 1: State (1 = Change ins selected button, other values RFU)	|
 *
 * |					|				  | Byte 2 - 33: Null terminated group name								|
 *
 * |					|				  | Byte 34 - 65: Radio button caption									|
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
lcd_getInputEvent(IN int timeout, OUT int * dataReceived, OUT BYTE * eventType,
  OUT BYTE * graphicsID, OUT BYTE * eventData);

/**
 * Requests input from the reader.
 *
 * @param timeout Timeout amount in seconds
 *  0 - No timeout
 * @param dataReceived Indicates if an event occurred and data was received
 *  0 - No data received
 *  1 - Data received
 * @param eventType The event type (required to be at least 4 bytes), see table below
 * @param eventTypeLen Length of eventType
 * @param graphicsID The graphicID of the event (required to be at least 4 bytes)
 * @param graphicsIDLen length of graphicID
 * @param eventData The event data, see table below (required to be at least 73 bytes)
 * | Event Type         | Value (4 bytes) | Event Specific Data                                                 |
 *
 * | ------------------ | --------------- | ------------------------------------------------------------------- |
 *
 * | Button Event       | 00030000h       | Length = Variable												    |
 *
 * |				    |				  |	Byte 1: State (1 = Pressed, other values RFU)					    |
 *
 * |					|				  |	Byte 2 - n: Null terminated caption                                 |
 *
 * | ------------------ | --------------- | ------------------------------------------------------------------- |
 *
 * | Checkbox Event     | 00030001h       | Length = 1 byte													    |
 *
 * |					|			      |	Byte 1: State (1 = Checked, 0 = Unchecked)						    |
 *
 * | ------------------ | --------------- | ------------------------------------------------------------------- |
 *
 * | Line Item Event    | 00030002h       | Length = 5 bytes												    |
 *
 * |					|				  |	Byte 1: State (1 = Item Selected, other values RFU)				    |
 *
 * |					|				  |	Byte 2 - n: Caption of the selected item						    |
 *
 * | ------------------ | --------------- | ------------------------------------------------------------------- |
 *
 * | Keypad Event       | 00030003h       | Length - 3 bytes												    |
 *
 * |					|				  | Byte 1: State (1 = key pressed, 2 = key released, other values RFU) |
 *
 * |					|				  | Byte 2 - 3: Key pressed and Key release                             |
 *
 * |					|				  |		0030h - KEYPAD_KEY_0											|
 *
 * |					|				  |		0031h - KEYPAD_KEY_1											|
 *
 * |					|				  |		0032h - KEYPAD_KEY_2											|
 *
 * |					|				  |		0033h - KEYPAD_KEY_3											|
 *
 * |					|				  |		0034h - KEYPAD_KEY_4											|
 *
 * |					|				  |		0035h - KEYPAD_KEY_5											|
 *
 * |					|				  |		0036h - KEYPAD_KEY_6											|
 *
 * |					|				  |		0037h - KEYPAD_KEY_7											|
 *
 * |					|				  |		0038h - KEYPAD_KEY_8											|
 *
 * |					|				  |		0039h - KEYPAD_KEY_9											|
 *
 * |					|				  | Byte 2 - 3: Only Key pressed										|
 *
 * |					|				  |     000Dh - KEYPAD_KEY_ENTER										|
 *
 * |					|				  |     0008h - KEYPAD_KEY_CLEAR										|
 *
 * |					|				  |     001Bh - KEYPAD_KEY_CANCEL										|
 *
 * |					|				  |     0070h - FUNC_KEY_F1 (Vend III)									|
 *
 * |					|				  |     0071h - FUNC_KEY_F2 (Vend III)									|
 *
 * |					|				  |     0072h - FUNC_KEY_F3 (Vend III)									|
 *
 * |					|				  |     0073h - FUNC_KEY_F4 (Vend III)									|
 *
 * | ------------------ | --------------- | ------------------------------------------------------------------- |
 *
 * | Touchscreen Event  | 00030004h       | Length = 1 - 33 bytes												|
 *
 * |					|				  | Byte 1: State (not used)											|
 *
 * |					|				  | Byte 2 - 33: Image name (zero terminated)							|
 *
 * | ------------------ | --------------- | ------------------------------------------------------------------- |
 *
 * | Slideshow Event    | 00030005h       | Length = 1 byte														|
 *
 * |					|				  | Byte 1: State (not used)											|
 *
 * | ------------------ | --------------- | ------------------------------------------------------------------- |
 *
 * | Transaction Event  | 00030006h       | Length = 9 bytes													|
 *
 * |					|				  | Byte 1: State (not used)											|
 *
 * |					|				  | Byte 2 - 5: Card type (0 = unknown)									|
 *
 * |					|				  | Byte 6 - 9: Status - A four byte, big-endian field					|
 *
 * |					|				  |	Byte 9 is used to store the 1-byte status code						|
 *
 * |					|				  |		00 - SUCCESS													|
 *
 * |					|				  |		08 - TIMEOUT													|
 *
 * |					|				  |		0A - FAILED														|
 *
 * |					|				  | This is not related to the extended status codes					|
 *
 * | ------------------ | --------------- | ------------------------------------------------------------------- |
 *
 * | Radio Button Event | 00030007h       | Length = 73 bytes													|
 *
 * |					|				  | Byte 1: State (1 = Change ins selected button, other values RFU)	|
 *
 * |					|				  | Byte 2 - 33: Null terminated group name								|
 *
 * |					|				  | Byte 34 - 65: Radio button caption									|
 * @param eventDataLen Length of eventData
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
lcd_getInputEvent_Len(IN int timeout, OUT int * dataReceived, OUT BYTE * eventType, IN_OUT int * eventTypeLen,
  OUT BYTE * graphicsID, IN_OUT int * graphicsIDLen, OUT BYTE * eventData, IN_OUT int * eventDataLen);

/**
 * DEPRECATED : please use lcd_createInputField_Len(IN BYTE *specs, IN int specsLen, OUT BYTE *graphicId, IN_OUT int *graphicIdLen)
 *
 * Create an input field on the screen.
 *
 * @param specs The specs of the input field:
 * |  Length (bytes)    |  Description                                                                     |
 *
 * | ------------------ | -------------------------------------------------------------------------------- |
 *
 * |      2 - 4         |  X coordinate in pixels, zero terminated ASCII                                   |
 *
 * | ------------------ | -------------------------------------------------------------------------------- |
 *
 * |      2 - 4         |  Y coordinate in pixels, zero terminated ASCII                                   |
 *
 * | ------------------ | -------------------------------------------------------------------------------- |
 *
 * |      2 - 4         |  Width in pixels, zero terminated ASCII. Set to 0 (30h) for calculated width.    |
 *
 * | ------------------ | -------------------------------------------------------------------------------- |
 *
 * |      2 - 4         |  Height in pixels, zero terminated ASCII. Set to 0 (30h) for calculated height.  |
 *
 * | ------------------ | -------------------------------------------------------------------------------- |
 *
 * |        2           |  Font designation. Default font = 1, zero terminated ASCII                       |
 *
 * | ------------------ | -------------------------------------------------------------------------------- |
 *
 * |      2 - 3         |  Zero terminated ASCII Font ID                                                   |
 *
 * | ------------------ | -------------------------------------------------------------------------------- |
 *
 * |        3           |  Zero terminated ASCII hexadecimal display option flag                           |
 *
 * |					|   Bit 0   0 =  No Border                                                         |
 *
 * |					|           1 =  Show Border                                                       |
 *
 * |					|   Bit 1   0 = Characters are first displayed on the leftmost area of the screen. |
 *
 * |					|	        1 = The first character entered is displayed on the rightmost area of  |
 *
 * |					|               the screen, and, as further digits are entered, characters scroll  |
 *
 * |					|		        from the right to the left.                                        |
 *
 * |					|	Bit 2 - 15  Reserved                                                           |
 *
 * | ------------------ | -------------------------------------------------------------------------------- |
 *
 * |      1 or 9        |  Foreground color, zero terminated ASCII hexadecimal                             |
 *
 * | ------------------ | -------------------------------------------------------------------------------- |
 *
 * |      1 or 9        |  Background color, zero terminated ASCII hexadecimal                             |
 *
 * | ------------------ | -------------------------------------------------------------------------------- |
 *
 * |      1 or 9        |  Border color, zero terminated ASCII hexadecimal                                 |
 *
 * | ------------------ | -------------------------------------------------------------------------------- |
 *
 * |      1 - 65        |  Prefill String, zero terminated ASCII                                           |
 *
 * | ------------------ | -------------------------------------------------------------------------------- |
 *
 * |      1 - 65        |  Format String, zero terminated ASCII                                            |
 * @param specsLen The length of specs
 * @param graphicsID The graphicID of the event (required to be 4 bytes)
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
lcd_createInputField(IN BYTE * specs, IN int specsLen, OUT BYTE * graphicId);

/**
 * Create an input field on the screen.
 *
 * @param specs The specs of the input field:
 * |  Length (bytes)    |  Description                                                                     |
 *
 * | ------------------ | -------------------------------------------------------------------------------- |
 *
 * |      2 - 4         |  X coordinate in pixels, zero terminated ASCII                                   |
 *
 * | ------------------ | -------------------------------------------------------------------------------- |
 *
 * |      2 - 4         |  Y coordinate in pixels, zero terminated ASCII                                   |
 *
 * | ------------------ | -------------------------------------------------------------------------------- |
 *
 * |      2 - 4         |  Width in pixels, zero terminated ASCII. Set to 0 (30h) for calculated width.    |
 *
 * | ------------------ | -------------------------------------------------------------------------------- |
 *
 * |      2 - 4         |  Height in pixels, zero terminated ASCII. Set to 0 (30h) for calculated height.  |
 *
 * | ------------------ | -------------------------------------------------------------------------------- |
 *
 * |        2           |  Font designation. Default font = 1, zero terminated ASCII                       |
 *
 * | ------------------ | -------------------------------------------------------------------------------- |
 *
 * |      2 - 3         |  Zero terminated ASCII Font ID                                                   |
 *
 * | ------------------ | -------------------------------------------------------------------------------- |
 *
 * |        3           |  Zero terminated ASCII hexadecimal display option flag                           |
 *
 * |					|   Bit 0   0 =  No Border                                                         |
 *
 * |					|           1 =  Show Border                                                       |
 *
 * |					|   Bit 1   0 = Characters are first displayed on the leftmost area of the screen. |
 *
 * |					|	        1 = The first character entered is displayed on the rightmost area of  |
 *
 * |					|               the screen, and, as further digits are entered, characters scroll  |
 *
 * |					|		        from the right to the left.                                        |
 *
 * |					|	Bit 2 - 15  Reserved                                                           |
 *
 * | ------------------ | -------------------------------------------------------------------------------- |
 *
 * |      1 or 9        |  Foreground color, zero terminated ASCII hexadecimal                             |
 *
 * | ------------------ | -------------------------------------------------------------------------------- |
 *
 * |      1 or 9        |  Background color, zero terminated ASCII hexadecimal                             |
 *
 * | ------------------ | -------------------------------------------------------------------------------- |
 *
 * |      1 or 9        |  Border color, zero terminated ASCII hexadecimal                                 |
 *
 * | ------------------ | -------------------------------------------------------------------------------- |
 *
 * |      1 - 65        |  Prefill String, zero terminated ASCII                                           |
 *
 * | ------------------ | -------------------------------------------------------------------------------- |
 *
 * |      1 - 65        |  Format String, zero terminated ASCII                                            |
 * @param specsLen The length of specs
 * @param graphicsID The graphicID of the event (required to be 4 bytes)
 * @param graphicsIDLen Length of graphicsID
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
lcd_createInputField_Len(IN BYTE * specs, IN int specsLen, OUT BYTE * graphicId, IN_OUT int * graphicIdLen);

/**
 * Get the keypad data that was entered into the specified Input Field.
 *
 * @param graphicsID The graphicID of the input field (required to be 4 bytes)
 * @param retData return keypad data
 * @param retDataLen The length of retData
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
lcd_getInputFieldValue(IN BYTE * graphicId, OUT BYTE * retData, IN_OUT int * retDataLen);

/**
 * Create Screen
 *
 *  Creates a new screen.
 *  @param screenName  Screen name to use.
 *  @param screenNameLen  Length of screenName.
 *  @param screenID  Screen ID that was created.
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
lcd_createScreen(IN char * screenName, IN int screenNameLen, OUT int * ScreenID);

/**
 * Destroy Screen
 *
 *  Destroys a previously created inactive screen.  The screen cannot be active
 *    @param screenName  Screen name to destroy.  The screen number is assigned with lcd_createScreen.
 *    @param screenNameLen  Length of screenName.
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
lcd_destroyScreen(IN char * screenName, IN int screenNameLen);

/**
 * Get Active Screen
 *
 *  Returns the active screen ID.
 *    @param screenName  Screen name this is active.
 *    @param screenNameLen  Length of screenName.
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
lcd_getActiveScreen(OUT char * screenName, IN_OUT int * screenNameLen);

/**
 * Show Screen
 *
 *  Displays and makes active a previously created screen.
 *    @param screenName  Screen to display.  The screen name is defined with lcd_createScreen.
 *    @param screenNameLen  Length of screenName.
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
lcd_showScreen(IN char * screenName, IN int screenNameLen);

/**
 * Get Button Event
 *
 *  Reports back the ID of the button that encountered a click event after the last Get Button Event.
 *
 *    @param screenID  Screen ID of the last clicked button
 *    @param objectID  Button ID of the last clicked button
 *    @param screenName  Screen Name of the last clicked button
 *    @param screenNameLen  Length of screenName
 *    @param objectName  Button Name of the last clicked button
 *    @param objectNameLen  Length of objectName
 *    @param isLongPress  1 = Long Press, 0 = Short Press
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
lcd_getButtonEvent(OUT int * screenID, OUT int * objectID, OUT char * screenName, IN_OUT int * screenNameLen,
  OUT char * objectName, IN_OUT int * objectNameLen, OUT int * isLongPress);

/**
 * Add Button
 *
 *  Adds a button to a selected screen.  Must execute lcd_createScreen first to establish a screen to draw on.
 *  The SDK timeout of the command is set to 6 seconds.
 *
 *    @param screenName Screen name that will be the target of add button
 *    @param screenNameLen  Length of screenName
 *    @param buttonName Button name that will be the target of add button
 *    @param buttonNameLen  Length of buttonName
 *    @param type Button Type
 *      - Large = 0x01
 *      - Medium = 0x02
 *      - Invisible = 0x03  (70px by 60 px)
 *    @param alignment Position for Button
 *      - 0 = Display object at the horizon center of specified y, while x ignored
 *      - 1 = Display object at specified x andy
 *      - 2 = Display object at center of screen, x, y are both ignored
 *      - 3 = Display object at left of the screen of specified y, while x ignored
 *      - 4 = Display object at right of the screen of specified y, while x ignored
 *    @param xCord  x-coordinate for Button, range 0-271
 *    @param yCord  y-coordinate for Button, range 0-479
 *    @param label Label to show on the button.  Required for Large/Medium buttons.  Not used for Invisible buttons.
 *    @param labelLen  Length of label
 *    @param returnItem The item includes screen ID, object ID, top-left x-coordinate, top-left y-coordinate, bottom-right x-coordinate, bottom-left y-coordinate, which are all assigned to the created button
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 *
 */
int
lcd_addButton(IN char * screenName, IN int screenNameLen, IN char * buttonName, IN int buttonNameLen, IN BYTE type,
  IN BYTE alignment, IN int xCord, IN int yCord, IN char * label, IN int labelLen,
  OUT IDTLCDItem * returnItem);

/**
 * Add Ethernet Settings
 *
 *  Adds an Ethernet settings to a selected screen.  Must execute lcd_createScreen first to establish a screen to draw on.
 *  The SDK timeout of the command is set to 6 seconds.
 *
 *    @param screenName Screen name that will be the target of add widget
 *    @param screenNameLen  Length of screenName
 *    @param objectName Object name that will be the target of add widget
 *    @param objectNameLen  Length of objectName
 *    @param alignment  Position for widget
 *      - 0 = Display object at the horizon center of specified y, while x ignored
 *      - 1 = Display object at specified x and y
 *      - 2 = Display object at center of screen, x, y are both ignored
 *      - 3 = Display object at left of the screen of specified y, while x ignored
 *      - 4 = Display object at right of the screen of specified y, while x ignored
 *    @param xCord  x-coordinate for widget, range 0-271
 *    @param yCord  y-coordinate for widget, range 0-479
 *    @param returnItem The item includes screen ID, object ID, top-left x-coordinate, top-left y-coordinate, bottom-right x-coordinate, bottom-left y-coordinate, which are all assigned to the created widget
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 *   Item  | Maximum can be created for each screen
 *   ----- | -----
 *   Text Area | 20
 *   Large Button | 8
 *   Medium Button | 16
 *   Invisible Button | 16
 *   Numeric Entry | 1
 *   Ethernet Setting | 1
 *   Led widget | 1
 *   image | 20
 */
int
lcd_addEthernet(IN char * screenName, IN int screenNameLen, IN char * objectName, IN int objectNameLen,
  IN BYTE alignment, IN int xCord, IN int yCord, OUT IDTLCDItem * returnItem);

/**
 * Add LED
 *
 *  Adds a LED widget to a selected screen.  Must execute lcd_createScreen first to establish a screen to draw on.
 *  The SDK timeout of the command is set to 6 seconds.
 *
 *    @param screenName Screen name that will be the target of add LED
 *    @param screenNameLen  Length of screenName
 *    @param objectName Object name that will be the target of add LED
 *    @param objectNameLen  Length of objectName
 *    @param alignment  Position for LED
 *      - 0 = Display object at the horizon center of specified y, while x ignored
 *      - 1 = Display object at specified x andy
 *      - 2 = Display object at center of screen, x, y are both ignored
 *      - 3 = Display object at left of the screen of specified y, while x ignored
 *      - 4 = Display object at right of the screen of specified y, while x ignored
 *    @param xCord  x-coordinate for LED, range 0-271
 *    @param yCord  y-coordinate for LED, range 0-479
 *    @param returnItem The item includes screen ID, object ID, top-left x-coordinate, top-left y-coordinate, bottom-right x-coordinate, bottom-left y-coordinate, which are all assigned to the created widget
 *    @param LED Must be 4 bytes, LED 0 = byte 0, LED 1 = byte 1, LED 2 = byte 2, LED 3 = byte 3
 *       - Value 0 = LED OFF
 *       - Value 1 = LED Green
 *       - Value 2 = LED Yellow
 *       - Value 3 = LED Red
 *    @param LEDLen  Length of LED
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 *  Item | Maximum can be created for each screen
 *  ----- | -----
 *  Text Area | 20
 *  Large Button | 8
 *  Medium Button | 16
 *  Invisible Button | 16
 *  Numeric Entry | 1
 *  Ethernet Setting | 1
 *  Led widget | 1
 *  image | 20
 */
int
lcd_addLED(IN char * screenName, IN int screenNameLen, IN char * objectName, IN int objectNameLen, IN BYTE alignment,
  IN int xCord, IN int yCord, OUT IDTLCDItem * returnItem, IN BYTE * LED, IN int LEDLen);

/**
 * Add text
 *
 *  Adds a text component to a selected screen.  Must execute lcd_createScreen first to establish a screen to draw on.
 *  The SDK timeout of the command is set to 6 seconds.
 *
 *    @param screenName Screen name that will be the target of add text
 *    @param screenNameLen  Length of screenName
 *    @param objectName Object name that will be the target of add text
 *    @param objectNameLen  Length of objectName
 *    @param alignment  Position for Text
 *      - 0 = Display object at the horizon center of specified y, while x ignored
 *      - 1 = Display object at specified x andy
 *      - 2 = Display object at center of screen, x, y are both ignored
 *      - 3 = Display object at left of the screen of specified y, while x ignored
 *      - 4 = Display object at right of the screen of specified y, while x ignored
 *    @param xCord  x-coordinate for Text, range 0-271
 *    @param yCord  y-coordinate for Text, range 0-479
 *    @param width  Width of text area
 *    @param height  Height of text area
 *    @param fontID Font ID
 *    @param color Four bytes for color, example, Blue = 0xFF000000, Black = 0x00000000
 *      - Byte 0 = B
 *      - Byte 1 = G
 *      - Byte 2 = R
 *      - Byte 3 = Reserved
 *    @param colorLen  Length of color
 *    @param label Label to show on the text
 *    @param labelLen  Length of label
 *    @param returnItem The item includes screen ID, object ID, top-left x-coordinate, top-left y-coordinate, bottom-right x-coordinate, bottom-left y-coordinate, which are all assigned to the created text area
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 *
 * Font ID | Typography Name | Font | Size
 * ----- | ----- | ----- | -----
 * 0 | RoundBold_12 | RoundBold.ttf | 12
 * 1 | RoundBold_18 | RoundBold.ttf | 18
 * 2 | RoundBold_24 | RoundBold.ttf | 24
 * 3 | RoundBold_36 | RoundBold.ttf | 36
 * 4 | RoundBold_48 | RoundBold.ttf | 48
 * 5 | RoundBold_60 | RoundBold.ttf | 60
 * 6 | RoundBold_72 | RoundBold.ttf | 72
 * 7 | RoundCondensedBold_12 | RoundCondensedBold.ttf | 12
 * 8 | RoundCondensedBold_18 | RoundCondensedBold.ttf | 18
 * 9 | RoundCondensedBold_24 | RoundCondensedBold.ttf | 24
 * 10 | RoundCondensedBold_36 | RoundCondensedBold.ttf | 36
 * 11 | RoundCondensedBold_48 | RoundCondensedBold.ttf | 48
 * 12 | RoundCondensedBold_60 | RoundCondensedBold.ttf | 60
 * 13 | RoundCondensedBold_72 | RoundCondensedBold.ttf | 72
 * 14 | RoundCondensedMedium_12 | RoundCondensedMedium_0.ttf | 12
 * 15 | RoundCondensedMedium_18 | RoundCondensedMedium_0.ttf | 18
 * 16 | RoundCondensedMedium_24 | RoundCondensedMedium_0.ttf | 24
 * 17 | RoundCondensedMedium_36 | RoundCondensedMedium_0.ttf | 36
 * 18 | RoundCondensedMedium_48 | RoundCondensedMedium_0.ttf | 48
 * 19 | RoundCondensedMedium_60 | RoundCondensedMedium_0.ttf | 60
 * 20 | RoundCondensedMedium_72 | RoundCondensedMedium_0.ttf | 72
 * 21 | RoundCondensedSemibold_12 | RoundCondensedSemibold.ttf | 12
 * 22 | RoundCondensedSemibold_18 | RoundCondensedSemibold.ttf | 18
 * 23 | RoundCondensedSemibold_24 | RoundCondensedSemibold.ttf | 24
 * 24 | RoundCondensedSemibold_36 | RoundCondensedSemibold.ttf | 36
 * 25 | RoundCondensedSemibold_48 | RoundCondensedSemibold.ttf | 48
 * 26 | RoundCondensedSemibold_60 | RoundCondensedSemibold.ttf | 60
 * 27 | RoundCondensedSemibold_72 | RoundCondensedSemibold.ttf | 72
 * 28 | RoundMedium_12 | RoundMedium.ttf | 12
 * 29 | RoundMedium_18 | RoundMedium.ttf | 18
 * 30 | RoundMedium_24 | RoundMedium.ttf | 24
 * 31 | RoundMedium_36 | RoundMedium.ttf | 36
 * 32 | RoundMedium_48 | RoundMedium.ttf | 48
 * 33 | RoundMedium_60 | RoundMedium.ttf | 60
 * 34 | RoundMedium_72 | RoundMedium.ttf | 72
 * 35 | RoundSemibold_12 | RoundSemibold.ttf | 12
 * 36 | RoundSemibold_18 | RoundSemibold.ttf | 18
 * 37 | RoundSemibold_24 | RoundSemibold.ttf | 24
 * 38 | RoundSemibold_36 | RoundSemibold.ttf | 36
 * 39 | RoundSemibold_48 | RoundSemibold.ttf | 48
 * 40 | RoundSemibold_60 | RoundSemibold.ttf | 60
 * 41 | RoundSemibold_72 | RoundSemibold.ttf | 72
 *
 * Item | Maximum can be created for each screen
 * ----- | -----
 * Text Area | 20
 * Large Button | 8
 * Medium Button | 16
 * Invisible Button | 16
 * Numeric Entry | 1
 * Ethernet Setting | 1
 * Led widget | 1
 * image | 20
 *
 */
int
lcd_addText(IN char * screenName, IN int screenNameLen, IN char * objectName, IN int objectNameLen, IN BYTE alignment,
  IN int xCord, IN int yCord, IN int width, IN int height, IN BYTE fontID, IN BYTE * color, IN int colorLen,
  IN char * label, IN int labelLen, OUT IDTLCDItem * returnItem);

/**
 * Add Image
 *
 *  Adds a image to a selected screen.  Must execute lcd_createScreen first to establish a screen to draw on.
 *  The SDK timeout of the command is set to 6 seconds.
 *
 *    @param screenName Screen name that will be the target of add image
 *    @param screenNameLen  Length of screenName
 *    @param objectName Object name that will be the target of add image
 *    @param objectNameLen  Length of objectName
 *    @param alignment Position for Image
 *      - 0 = Display object at the horizon center of specified y, while x ignored
 *      - 1 = Display object at specified x and y
 *      - 2 = Display object at center of screen, x, y are both ignored
 *      - 3 = Display object at left of the screen of specified y, while x ignored
 *      - 4 = Display object at right of the screen of specified y, while x ignored
 *    @param xCord  x-coordinate for Image, range 0-271
 *    @param yCord  y-coordinate for Image, range 0-479
 *    @param filename Filename of the image. Must be available in device memory.
 *    @param filenameLen  Length of filename
 *    @param returnItem The item includes screen ID, object ID, top-left x-coordinate, top-left y-coordinate, bottom-right x-coordinate, bottom-left y-coordinate, which are all assigned to the created image
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 *  Item | Maximum can be created for each screen
 *  ----- | -----
 *  Text Area | 20
 *  Large Button | 8
 *  Medium Button | 16
 *  Invisible Button | 16
 *  Numeric Entry | 1
 *  Ethernet Setting | 1
 *  Led widget | 1
 *  image | 20
 */
int
lcd_addImage(IN char * screenName, IN int screenNameLen, IN char * objectName, IN int objectNameLen, IN BYTE alignment,
  IN int xCord, IN int yCord, IN char * filename, IN int filenameLen, OUT IDTLCDItem * returnItem);

/**
 * Add Video
 *
 *  Adds a video to a selected screen.  Must execute lcd_createScreen first to establish a screen to draw on.
 *  The SDK timeout of the command is set to 6 seconds.
 *
 *    @param screenName Screen name that will be the target of add video
 *    @param screenNameLen  Length of screenName
 *    @param objectName Object name that will be the target of add video
 *    @param objectNameLen  Length of objectName
 *    @param alignment Position for Video
 *      - 0 = Display object at the horizon center of specified y, while x ignored
 *      - 1 = Display object at specified x and y
 *      - 2 = Display object at center of screen, x, y are both ignored
 *      - 3 = Display object at left of the screen of specified y, while x ignored
 *      - 4 = Display object at right of the screen of specified y, while x ignored
 *    @param xCord  x-coordinate for Video, range 0-271
 *    @param yCord  y-coordinate for Video, range 0-479
 *    @param filename Filename of the video. Must be available in the sd card.
 *    @param filenameLen  Length of filename
 *    @param returnItem The item includes screen ID, object ID, top-left x-coordinate, top-left y-coordinate, bottom-right x-coordinate, bottom-left y-coordinate, which are all assigned to the created video
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 *  Item | Maximum can be created for each screen
 *  ----- | -----
 *  Text Area | 20
 *  Large Button | 8
 *  Medium Button | 16
 *  Invisible Button | 16
 *  Numeric Entry | 1
 *  Ethernet Setting | 1
 *  Led widget | 1
 *  image | 20
 *  video | 1
 */
int
lcd_addVideo(IN char * screenName, IN int screenNameLen, IN char * objectName, IN int objectNameLen, IN BYTE alignment,
  IN int xCord, IN int yCord, IN char * filename, IN int filenameLen, OUT IDTLCDItem * returnItem);

/**
 * Add Extended Video
 *
 *  Adds a extended video to a selected screen.  Must execute lcd_createScreen first to establish a screen to draw on.
 *  The SDK timeout of the command is set to 6 seconds.
 *
 *    @param screenName Screen name that will be the target of add video
 *    @param screenNameLen  Length of screenName
 *    @param objectName Object name that will be the target of add video
 *    @param objectNameLen  Length of objectName
 *    @param alignment Position for Video
 *      - 0 = Display object at the horizon center of specified y, while x ignored
 *      - 1 = Display object at specified x and y
 *      - 2 = Display object at center of screen, x, y are both ignored
 *      - 3 = Display object at left of the screen of specified y, while x ignored
 *      - 4 = Display object at right of the screen of specified y, while x ignored
 *    @param xCord  x-coordinate for Video, range 0-271
 *    @param yCord  y-coordinate for Video, range 0-479
 *    @param loop  loop the videos when it's done.  0: Do not Loop 1: Loop
 *    @param numVideos  number of video files, range 1-4
 *    @param filenames Filenames of the videos separated by '\0'. Must be available in the sd card.
 *    @param filenamesLen  Length of filenames excluding the last NULL character.  Should be less than 64.
 *    @param returnItem The item includes screen ID, object ID, top-left x-coordinate, top-left y-coordinate, bottom-right x-coordinate, bottom-left y-coordinate, which are all assigned to the created video
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString
 *  Item | Maximum can be created for each screen
 *  ----- | -----
 *  Text Area | 20
 *  Large Button | 8
 *  Medium Button | 16
 *  Invisible Button | 16
 *  Numeric Entry | 1
 *  Ethernet Setting | 1
 *  Led widget | 1
 *  image | 20
 *  video | 1
 */
int
lcd_addExtVideo(IN char * screenName, IN int screenNameLen, IN char * objectName, IN int objectNameLen,
  IN BYTE alignment, IN int xCord, IN int yCord, IN BYTE loop, IN BYTE numVideos, IN char * filenames,
  IN int filenamesLen, OUT IDTLCDItem * returnItem);

/**
 * Clone Screen
 *
 *  Clones an existing screen.
 *    @param screenName  Screen name to clone.
 *    @param screenNameLen  Length of screenName.
 *    @param cloneName  Name of the cloned screen.
 *    @param cloneNameLen  Length of cloneName.
 *    @param cloneID Screen ID of the cloned screen
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
lcd_cloneScreen(IN char * screenName, IN int screenNameLen, IN char * cloneName, IN int cloneNameLen,
  OUT int * cloneID);

/**
 * Update Label
 *
 *  Updates the component label.
 *
 *    @param screenName Screen name that will be the target of update label
 *    @param screenNameLen  Length of screenName.
 *    @param objectName  Identifier of the component
 *    @param objectNameLen  Length of objectName.
 *    @param label Label to show on the component
 *    @param labelLen  Length of label.
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
lcd_updateLabel(IN char * screenName, IN int screenNameLen, IN char * objectName, IN int objectNameLen, IN char * label,
  IN int labelLen);

/**
 * Update Color
 *
 *  Updates the component color, or updates the LED colors if specifying LCD component
 *
 *   @param screenName Screen name that will be the target of update color
 *   @param screenNameLen  Length of screenName.
 *   @param objectName  Identifier of the component
 *   @param objectNameLen  Length of objectName.
 *   @param color \r\n
 *     Non LCD Widget: Four bytes for color, example, Blue = 0xFF000000, Black = 0x00000000
 *      - Byte 0 = B
 *      - Byte 1 = G
 *      - Byte 2 = R
 *      - Byte 3 = Reserved
 *     LCD Widget: Four bytes for  LED color, byte 0 = LED 0, byte 1 = LED 1, byte 2 = LED2, byte 3 = LED 3
 *      - Value 0 = LED OFF
 *      - Value 1 = LED Green
 *      - Value 2 = LED Yellow
 *      - Value 3 = LED Red
 *   @param colorLen  Length of color.
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
lcd_updateColor(IN char * screenName, IN int screenNameLen, IN char * objectName, IN int objectNameLen, IN BYTE * color,
  IN int colorLen);

/**
 * Update Position
 *
 *  Updates the component position.
 *
 *    @param screenName Screen Name that will be the target of update position
 *    @param screenNameLen  Length of screenName.
 *    @param objectName Identifier of the component
 *    @param objectNameLen  Length of objectName.
 *    @param alignment  Alignment for the target
 *      - 0 = Display object at the horizon center of specified y, while x ignored
 *      - 1 = Display object at specified x andy
 *      - 2 = Display object at center of screen, x, y are both ignored
 *      - 3 = Display object at left of the screen of specified y, while x ignored
 *      - 4 = Display object at right of the screen of specified y, while x ignored
 *    @param new_xCord  x-coordinate for Text, range 0-271
 *    @param new_yCord  y-coordinate for Text, range 0-479
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
lcd_updatePosition(IN char * screenName, IN int screenNameLen, IN char * objectName, IN int objectNameLen,
  IN BYTE alignment, IN int new_xCord, IN int new_yCord);

/**
 * Removed Item
 *
 *  Removes a component.
 *
 *    @param screenName Screen name where to remove the target from.
 *    @param screenNameLen  Length of screenName.
 *    @param objectName  Identifier of the component
 *    @param objectNameLen  Length of objectName.
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
lcd_removeItem(IN char * screenName, IN int screenNameLen, IN char * objectName, IN int objectNameLen);

/**
 * Store Screen Info
 *
 *  Store all current screen information from RAM to flash
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
lcd_storeScreenInfo();

/**
 * Load Screen Info
 *
 *  Load all current screen information from RAM to flash
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
lcd_loadScreenInfo();

/**
 * Clear Screen Info
 *
 *  Clear all current screen information in RAM and flash. And then show'power-on screen'
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
lcd_clearScreenInfo();

/**
 * Get All Screens
 *
 *  Get all created screens' name
 *
 *    @param screenNumbers Number of created screens
 *    @param screenInfo Array of all created screens
 *        each element includes
 *           -screenID of a created screen
 *           -screenName of a created screen
 *           -screenNameLen of screenName
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
lcd_getAllScreens(IN_OUT int * screenNumbers, OUT IDTScreenInfo * screenInfo);

/**
 * Get All Objects on Screen
 *
 *  Get all created objects' name on certain screen
 *
 *    @param screenName Screen name to get all objects
 *    @param screenNameLen  Length of screenName
 *    @param objectNumbers Number of created objects
 *    @param returnObjects Array of all created objects
 *       each element includes
 *           -objectID of a created object
 *           -objectName of a created object
 *           -objectNameLen of objectName
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
lcd_getAllObjects(IN char * screenName, IN int screenNameLen, IN_OUT int * objectNumbers,
  OUT IDTObjectInfo * objectInfo);

/**
 * Queery Screen by Name
 *
 *  Check if the given screen exists or not
 *
 *    @param screenName Name of the checked screen
 *    @param screenNameLen  Length of screenName
 *    @param result the checking result
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
lcd_queryScreenbyName(IN char * screenName, IN int screenNameLen, OUT int * result);

/**
 * Link UI with Transaction Message ID
 *
 *  Link an existing Customer UI ID with a specified transaction message ID. During transaction, the linked System UI will be replaced by the linked Customer UI
 *
 *    @param MessageId Transaction Message ID: Refer to Doc “EMV Display Message ID Assignment” Selection by Customer
 *    @param screenName Name of the screen (No longer than 32 bytes including the NULL character)
 *    @param screenNameLen  Length of screenName
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
lcd_linkUIWithTransactionMessageId(IN BYTE MessageId, IN char * screenName, IN int screenNameLen);

/**
 * Queery Object by Name
 *
 *  Check if the given object exists or not. If exists, return all screen names which contains the object of the given object name
 *
 *    @param objectName Name of the checked object
 *    @param objectNameLen Length of objectName
 *    @param objectNumbers Number of the checked object
 *    @param screenInfo Array of all the screen names that contain the object
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
lcd_queryObjectbyName(IN char * objectName, IN int objectNameLen, IN_OUT int * objectNumbers,
  OUT IDTScreenInfo * screenInfo);

/**
 * Queery Screen by ID
 *
 *  Check if the given screen exists or not
 *
 *    @param screenID ID of the checked screen
 *    @param result the checking result
 *    @param screenName Name of the checked screen
 *    @param screenNameLen Length of screenName
 *    @param ip Optional: IP address to execute command on (for IP connected devices)
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
lcd_queryScreenbyID(IN int screenID, OUT int * result, OUT int * screenName, IN_OUT int * screenNameLen);

/**
 * Queery Object by ID
 *
 *  Check if the given object exists or not. If exists, return all screen names which contains the object of the given object ID
 *
 *    @param objectID ID of the checked object
 *    @param objectNumbers Number of the checked object
 *    @param screenInfo screen names containing the item
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
lcd_queryObjectbyID(IN int objectID, OUT int * objectNumbers, OUT IDTScreenInfo * screenInfo);

/**
 * Set Backlight
 *
 *  Set backlight percentage. If the percent > 100, it will be rejected. If 0 < percent < 10, backlight percent will be set to 10.
 *    @param isBacklightOn 0: backlight off 1: backlight on
 *    @param backlightVal Backlight percent value to be sat
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
lcd_setBacklight(IN BYTE isBacklightOn, IN BYTE backlightVal);

/**
 * DEPRECATED : please use emv_getEMVKernelVersion_Len(OUT char* version, IN_OUT int *versionLen)
 *
 * Polls device for EMV Kernel Version
 *
 * @param version Response returned of Kernel Version; needs to have at least 128 bytes of memory.
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 *
 */
int
emv_getEMVKernelVersion(OUT char * version);

/**
 * Polls device for EMV Kernel Version
 *
 * @param version Response returned of Kernel Version
 *
 * @param versionLen Length of version
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 *
 */
int
emv_getEMVKernelVersion_Len(OUT char * version, IN_OUT int * versionLen);

/**
 * Get EMV Kernel check value info
 *
 * @param checkValue Response returned of Kernel check value info
 * @param checkValueLen the length of checkValue
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString
 *
 */
int
emv_getEMVKernelCheckValue(OUT BYTE * checkValue,
  IN_OUT int *                        checkValueLen);

/**
 * Get EMV Kernel configuration check value info
 *
 * @param checkValue Response returned of Kernel configuration check value info
 * @param checkValueLen the length of checkValue
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString
 *
 */
int
emv_getEMVConfigurationCheckValue(OUT BYTE * checkValue,
  IN_OUT int *                               checkValueLen);

/**
 * Enables authenticate for EMV transactions.  If a
 * emv_startTranaction results in code 0x0010 (start transaction
 * success), then emv_authenticateTransaction can automatically
 * execute if parameter is set to TRUE
 * @param authenticate TRUE = auto authenticate, FALSE = manually authenticate
 */
void
emv_setAutoAuthenticateTransaction(IN int authenticate);

/**
 * Enables complete for EMV transactions.  If a
 *  emv_authenticateTranaction results in code 0x0004 (go online),
 *  then emv_completeTransaction can automatically execute if
 *  parameter is set to TRUE
 * @param complete TRUE = auto complete, FALSE = manually complete
 */
void
emv_setAutoCompleteTransaction(IN int complete);

/**
 * Gets auto authenticate value for EMV transactions.
 * @return RETURN_CODE:  TRUE = auto authenticate, FALSE = manually authenticate
 */
int
emv_getAutoAuthenticateTransaction();

/**
 * Gets auto complete value for EMV transactions.
 * @return RETURN_CODE:  TRUE = auto complete, FALSE = manually complete
 */
int
emv_getAutoCompleteTransaction();

/**
 * Allow fallback for EMV transactions.  Default is TRUE
 * @param allow TRUE = allow fallback, FALSE = don't allow fallback
 */
void
emv_allowFallback(IN int allow);

/**
 * Set EMV Transaction Parameters
 *
 * Set the parameters to be used on EMV transactions for an ICC card
 * when Auto Poll is on
 *
 * The tags will be returned in the callback routine.
 *
 * @param amount Transaction amount value  (tag value 9F02)
 * @param amtOther Other amount value, if any  (tag value 9F03)
 * @param type Transaction type (tag value 9C).
 * @param timeout Timeout value in seconds.
 * @param tags Any other tags to be included in the request (Maximum Length = 500 bytes).  Passed as a string.  Example, tag 9F0C with amount 0x000000000100 would be "9F0C06000000000100"
 *   If tags 9F02 (amount), 9F03 (other amount), or 9C (transaction type) are included, they will take priority over these values supplied as individual parameters to this method.
 * Note:  To request tags to be  included in default response, use tag DFEE1A, and specify tag list.
 *    Example four tags 9F02, 9F36, 95, 9F37 to be included in response = DFEE1A079F029F36959F37
 * @param tagsLen the length of tags
 *
 */
void
emv_setTransactionParameters(IN double amount,
  IN double                            amtOther,
  IN int                               type,
  IN int                               timeout,
  IN BYTE *                            tags,
  IN int                               tagsLen);

/**
 * Start EMV Transaction Request
 *
 * Authorizes the EMV transaction for an ICC card
 *
 * The tags will be returned in the callback routine.
 *
 * @param amount Transaction amount value  (tag value 9F02) - SEE IMPORTANT NOTE BELOW
 * @param amtOther Other amount value, if any  (tag value 9F03) - SEE IMPORTANT NOTE BELOW
 * @param exponent Number of characters after decimal point
 * @param type Transaction type (tag value 9C).
 * @param timeout Timeout value in seconds.
 * @param tags Any other tags to be included in the request.  Passed as a TLV stream.  Example, tag 9F0C with amount 0x000000000100 would be 0x9F0C06000000000100
 * If tags 9F02 (amount), 9F03 (other amount), or 9C (transaction type) are included, they will take priority over these values supplied as individual parameters to this method.
 * @param tagsLen Length of tags
 * @param forceOnline TRUE = do not allow offline approval, FALSE = allow ICC to approve offline if terminal capable
 * Note:  To request tags to be  included in default response, use tag DFEE1A, and specify tag list.  Example four tags 9F02, 9F36, 95, 9F37 to be included in response = DFEE1A079F029F36959F37
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString
 * >>>>>IMPORTANT: parameters for amount and amtOther MUST BE PASSED AS A DOUBLE VALUE WITH DECIMAL POINT.  Example, do not pass 1, but instead pass 1.0 or 1.00. Otherwise, results will be unpredictable
 */
int
emv_startTransaction(IN double amount,
  IN double                    amtOther,
  IN int                       exponent,
  IN int                       type,
  IN int                       timeout,
  IN BYTE *                    tags,
  IN int                       tagsLen,
  IN int                       forceOnline);

/**
 * Start EMV Transaction Request
 *
 * Authorizes the EMV transaction for an ICC card
 *
 * The tags will be returned in the callback routine.
 *
 *
 * @param timeout Timeout value in seconds.
 * @param tags Tags to be included in the request.  Passed as a TLV
 * stream.  Example, tag 9F02 with amount 0x000000000100 would be
 * 0x9F0206000000000100
 *
 * @param tagsLen Length of tags
 * @param forceOnline TRUE = do not allow offline approval, FALSE = allow
 * ICC to approve offline if terminal capable
 * Note:  To request tags to be  included in default response, use tag DFEE1A,
 * and specify tag list.  Example four tags 9F02, 9F36, 95, 9F37 to be
 * included in response = DFEE1A079F029F36959F37
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString
 * >>>>>IMPORTANT: parameters for amount and amtOther MUST BE PASSED AS A
 * DOUBLE VALUE WITH DECIMAL POINT.  Example, do not pass 1, but instead
 * pass 1.0 or 1.00. Otherwise, results will be unpredictable.
 */
int
emv_activateTransaction(IN int timeout,
  IN BYTE *                    tags,
  IN int                       tagsLen,
  IN int                       forceOnline);

/**
 * Authenticate EMV Transaction Request
 *
 * Authenticates the EMV transaction for an ICC card.  Execute this
 * after receiving response with result code 0x10 to emv_startTransaction
 *
 * The tags will be returned in the callback routine.
 *
 * @param updatedTLV  TLV stream that can be used to update the following values:
 *   - 9F02: Amount
 *   - 9F03: Other amount
 *   - 9C: Transaction type
 *   - 5F57: Account type
 *  In addition tag DFEE1A can be sent to specify tag list to include in
 *  results. Example four tags 9F02, 9F36, 95, 9F37 to be included in
 *  response = DFEE1A079F029F36959F37
 * @param updatedTLVLen
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString
 */
int
emv_authenticateTransaction(IN BYTE * updatedTLV, IN int updatedTLVLen);

/**
 * Authenticate EMV Transaction Request with Timeout
 *
 * Authenticates the EMV transaction for an ICC card.  Execute this after receiving response with result code 0x10 to emv_startTransaction
 *
 * The tags will be returned in the callback routine.
 *
 * @param timeout Timeout value in seconds.
 * @param updatedTLV  TLV stream that can be used to update the following values:
 *   - 9F02: Amount
 *   - 9F03: Other amount
 *   - 9C: Transaction type
 *   - 5F57: Account type
 *  In addition tag DFEE1A can be sent to specify tag list to include in results. Example four tags 9F02, 9F36, 95, 9F37 to be included in response = DFEE1A079F029F36959F37
 * @param updatedTLVLen
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString
 */
int
emv_authenticateTransactionWithTimeout(IN int timeout, IN BYTE * updatedTLV, IN int updatedTLVLen);

/**
 * Complete EMV Transaction Request
 *
 * Completes the EMV transaction for an ICC card when online
 * authorization request is received from emv_authenticateTransaction
 *
 * The tags will be returned in the callback routine.
 *
 * @param commError Communication error with host.  Set to TRUE(1) if
 * host was unreachable, or FALSE(0) if host response received.  If
 * Communication error, authCode, iad, tlvScripts can be null.
 * @param authCode Authorization code from host.  Two bytes.  Example
 * 0x3030.  (Tag value 8A).  Required
 *
 * @param authCodeLen the length of authCode
 * @param iad Issuer Authentication Data, if any.  Example
 *        0x11223344556677883030 (tag value 91).
 * @param iadLen the length of iadLen
 * @param tlvScripts 71/72 scripts, if any
 * @param tlvScriptsLen the length of tlvScriptsLen
 * @param tlv  Additional TLV data to return with transaction results (if any)
 * @param tlvLen the length of tlv
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString
 */
int
emv_completeTransaction(IN int commError,
  IN BYTE *                    authCode,
  IN int                       authCodeLen,
  IN BYTE *                    iad,
  IN int                       iadLen,
  IN BYTE *                    tlvScripts,
  IN int                       tlvScriptsLen,
  IN BYTE *                    tlv,
  IN int                       tlvLen);

/**
 * Cancel EMV Transaction
 *
 * Cancels the currently executing EMV transaction.
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 */
int
emv_cancelTransaction();

/**
 * Retrieve Transaction Results
 *
 * Retrieves specified EMV tags from the currently executing transaction.
 *
 * @param tags Tags to be retrieved.  Example 0x9F028A will retrieve tags
 * 9F02 and 8A
 * @param tagsLen Length of tag list
 * @param cardData All requested tags returned as unencrypted,
 * encrypted and masked TLV data in IDTTransactionData object
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 */
int
emv_retrieveTransactionResult(IN BYTE * tags,
  IN int                                tagsLen,
  IDTTransactionData *                  cardData);

/**
 * Callback Response LCD Display
 *
 * Provides menu selection responses to the kernel after a callback was received with DeviceState.EMVCallback, and
 * callbackType = EMV_CALLBACK_TYPE.EMV_CALLBACK_TYPE_LCD, and lcd_displayMode = EMV_LCD_DISPLAY_MODE_MENU, EMV_LCD_DISPLAY_MODE_PROMPT,
 * or EMV_LCD_DISPLAY_MODE_LANGUAGE_SELECT
 *
 * @param type If Cancel key pressed during menu selection, then value is EMV_LCD_DISPLAY_MODE_CANCEL.  Otherwise, value can be EMV_LCD_DISPLAY_MODE_MENU, EMV_LCD_DISPLAY_MODE_PROMPT,
 * or EMV_LCD_DISPLAY_MODE_LANGUAGE_SELECT
 * @param selection If type = EMV_LCD_DISPLAY_MODE_MENU or EMV_LCD_DISPLAY_MODE_LANGUAGE_SELECT, provide the selection ID line number. Otherwise, if type = EMV_LCD_DISPLAY_MODE_PROMPT
 * supply either 0x43 ('C') for Cancel, or 0x45 ('E') for Enter/accept
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 */
int
emv_callbackResponseLCD(IN int type,
  byte                         selection);

/**
 * Callback Response MSR Entry
 *
 * Provides MSR information to kernel after a callback was received
 *   with DeviceState.EMVCallback, and callbackType = EMV_CALLBACK_MSR
 *
 * @param MSR Swiped track data
 * @param MSRLen the length of Swiped track data
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 */
int
emv_callbackResponseMSR(IN BYTE * MSR, IN_OUT int MSRLen);

/**
 * Retrieve Application Data by AID
 *
 * Retrieves the Application Data as specified by the AID name passed
 * as a parameter.
 *
 * @param AID Name of ApplicationID. Must be between 5 and 16 bytes
 * @param AIDLen the length of AID data buffer.
 * @param tlv  The TLV elements of the requested AID
 * @param tlvLen the length of tlv data buffer.
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 */
int
emv_retrieveApplicationData(IN BYTE * AID,
  IN int                              AIDLen,
  OUT BYTE *                          tlv,
  IN_OUT int *                        tlvLen);

/**
 * Set Application Data by AID
 *
 * Sets the Application Data as specified by the application name and TLV data
 *
 * @param name Application name, 10-32 ASCII hex characters
 *        representing 5-16 bytes  Example "a0000000031010"
 * @param nameLen the length of name data buffer of Application name,
 * @param tlv  Application data in TLV format
 * @param tlvLen the length of tlv data buffer
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 */
int
emv_setApplicationData(IN BYTE * name,
  IN int                         nameLen,
  IN BYTE *                      tlv,
  IN int                         tlvLen);

/**
 * Set Application Data by TLV
 *
 * Sets the Application Data as specified by the TLV data
 * @param tlv  Application data in TLV format
 *         The first tag of the TLV data must be the group number (DFEE2D).
 *         The second tag of the TLV data must be the AID (9F06)
 *         Example valid TLV, for Group #2, AID a0000000035010:
 *         "dfee2d01029f0607a0000000051010ffe10101ffe50110ffe30114ffe20106"
 * @param tlvLen the length of tlv data buffer
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 */
int
emv_setApplicationDataTLV(IN BYTE * tlv,
  IN int                            tlvLen);

/**
 * Remove Application Data by AID
 *
 * Removes the Application Data as specified by the AID name passed as
 * a parameter
 *
 * @param AID Name of ApplicationID Must be between 5 and 16 bytes
 * @param AIDLen the length of AID data buffer
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 */
int
emv_removeApplicationData(IN BYTE * AID,
  IN int                            AIDLen);

/**
 * Remove All Application Data
 *
 * Removes all the Application Data
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 */
int
emv_removeAllApplicationData();

/**
 * Retrieve AID list
 *
 * Returns all the AID names installed on the terminal.
 *
 * @param AIDList  array of AID name byte arrays
 * @param AIDListLen  the length of AIDList array buffer
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 */
int
emv_retrieveAIDList(OUT BYTE * AIDList,
  IN_OUT int *                 AIDListLen);

/**
 * Retrieve Terminal Data
 *
 * Retrieves the Terminal Data.
 *
 * @param tlv Response returned as a TLV
 * @param tlvLen the length of tlv data buffer
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 */
int
emv_retrieveTerminalData(OUT BYTE * tlv,
  IN_OUT int *                      tlvLen);

/**
 * Set Terminal Data
 *
 * Sets the Terminal Data as specified by the TerminalData structure
 * passed as a parameter
 *
 * @param tlv TerminalData configuration file
 * @param tlvLen the length of tlv data buffer
 *
 * @retval RETURN_CODE:  Return codes listed as typedef enum in
 *         IDTCommon:RETURN_CODE.
 *         Values can be parsed with device_getResponseCodeString()
 */
int
emv_setTerminalData(IN BYTE * tlv,
  IN int                      tlvLen);

/**
 * Sets the terminal major configuration in ICS .
 * @param configuration A configuration value, range 1-23
 * - 1 = 1C
 * - 2 = 2C
 * - 3 = 3C
 * - 4 = 4C
 * - 5 = 5C
 * ...
 * - 23 = 23C
 *
 *  @return RETURN_CODE: Values can be parsed with device_getResponseCodeString()
 */
int
emv_setTerminalMajorConfiguration(IN int configuration);

/**
 * Remove Terminal Data
 *
 * Removes the Terminal Data
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 */
int
emv_removeTerminalData();

/**
 * Retrieve Certificate Authority Public Key
 *
 * Retrieves the CAPK as specified by the RID/Index  passed as a parameter.
 *
 * @param capk 6 bytes CAPK = 5 bytes RID + 1 byte Index
 * @param capkLen the length of capk data buffer
 * @param key Response returned as a CAKey format:
 *  [5 bytes RID][1 byte Index][1 byte Hash Algorithm][1 byte Encryption Algorithm]
 *  [20 bytes HashValue][4 bytes Public Key Exponent][2 bytes Modulus Length][Variable bytes Modulus]
 *  Where:
 *   - Hash Algorithm: The only algorithm supported is SHA-1.The value is set to 0x01
 *   - Encryption Algorithm: The encryption algorithm in which this key is used. Currently support only one type: RSA. The value is set to 0x01.
 *   - HashValue: Which is calculated using SHA-1 over the following fields: RID & Index & Modulus & Exponent
 *   - Public Key Exponent: Actually, the real length of the exponent is either one byte or 3 bytes. It can have two values: 3 (Format is 0x00 00 00 03), or  65537 (Format is 0x00 01 00 01)
 *   - Modulus Length: LenL LenH Indicated the length of the next field.
 *   - Modulus: This is the modulus field of the public key. Its length is specified in the field above.
 * @param keyLen the length of key data buffer
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 */
int
emv_retrieveCAPK(IN BYTE * capk,
  IN int                   capkLen,
  OUT BYTE *               key,
  IN_OUT int *             keyLen);

/**
 * Set Certificate Authority Public Key
 *
 * Sets the CAPK as specified by the CAKey structure
 *
 * @param capk CAKey format:
 *  [5 bytes RID][1 byte Index][1 byte Hash Algorithm][1 byte Encryption Algorithm][20 bytes HashValue][4 bytes Public Key Exponent][2 bytes Modulus Length][Variable bytes Modulus]
 *  Where:
 *   - Hash Algorithm: The only algorithm supported is SHA-1.The value is set to 0x01
 *   - Encryption Algorithm: The encryption algorithm in which this key is used. Currently support only one type: RSA. The value is set to 0x01.
 *   - HashValue: Which is calculated using SHA-1 over the following fields: RID & Index & Modulus & Exponent
 *   - Public Key Exponent: Actually, the real length of the exponent is either one byte or 3 bytes. It can have two values: 3 (Format is 0x00 00 00 03), or  65537 (Format is 0x00 01 00 01)
 *   - Modulus Length: LenL LenH Indicated the length of the next field.
 *   - Modulus: This is the modulus field of the public key. Its length is specified in the field above.
 * @param capkLen the length of capk data buffer
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 */
int
emv_setCAPK(IN BYTE * capk,
  IN int              capkLen);

/**
 * Remove Certificate Authority Public Key
 *
 * Removes the CAPK as specified by the RID/Index
 *
 * @param capk 6 byte CAPK =  5 bytes RID + 1 byte INDEX
 * @param capkLen the length of capk data buffer
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 */
int
emv_removeCAPK(IN BYTE * capk,
  IN int                 capkLen);

/**
 * Remove All Certificate Authority Public Key
 *
 * Removes all the CAPK
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 */
int
emv_removeAllCAPK();

/**
 * Retrieve the Certificate Authority Public Key list
 *
 * Returns all the CAPK RID and Index installed on the terminal.
 *
 * @param keys [key1][key2]...[keyn], each key 6 bytes where
 *  key = 5 bytes RID + 1 byte index
 * @param keysLen the length of keys data buffer
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 */
int
emv_retrieveCAPKList(OUT BYTE * keys, IN_OUT int * keysLen);

/**
 * DEPRECATED : please use emv_retrieveTerminalID_Len(OUT char* terminalID, IN_OUT int *terminalIDLen)
 *
 * Gets the terminal ID as printable characters .
 * @param terminalID Terminal ID string; needs to have at least 30 bytes of memory
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 */
int
emv_retrieveTerminalID(OUT char * terminalID);

/**
 * Gets the terminal ID as printable characters .
 * @param terminalID Terminal ID string
 *
 * @param terminalIDLen Length of terminalID
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 */
int
emv_retrieveTerminalID_Len(OUT char * terminalID, IN_OUT int * terminalIDLen);

/**
 * Sets the terminal ID as printable characters .
 * @param terminalID Terminal ID to set
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 */
int
emv_setTerminalID(IN char * terminalID);

/**
 * Retrieve the Certificate Revocation List
 *
 * Returns the CRL entries on the terminal.
 *
 * @param list [CRL1][CRL2]...[CRLn], each CRL 9 bytes where
 *  CRL = 5 bytes RID + 1 byte index + 3 bytes serial number
 * @param lssLen the length of list data buffer
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 */
int
emv_retrieveCRL(OUT BYTE * list,
  IN_OUT int *             lssLen);

/**
 * Set Certificate Revocation List
 *
 * Sets the CRL
 *
 * @param list CRL Entries containing the RID, Index, and serial numbers to set
 *  [CRL1][CRL2]...[CRLn] where each [CRL]  is 9 bytes:
 *  [5 bytes RID][1 byte CAPK Index][3 bytes serial number]
 * @param lsLen the length of list data buffer
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 */
int
emv_setCRL(IN BYTE * list,
  IN int             lsLen);

/**
 * Retrieve the Certificate Revocation List
 *
 * Returns the CRL entries on the terminal.
 *
 * @param list [CRL1][CRL2]...[CRLn], each CRL 9 bytes where
 *  CRL = 5 bytes RID + 1 byte index + 3 bytes serial number
 * @param lsLen the length of list data buffer
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 */
int
emv_removeCRL(IN BYTE * list,
  IN int                lsLen);

/**
 * Remove All Certificate Revocation List Entries
 *
 * Removes all CRLEntry entries
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 */
int
emv_removeAllCRL();

/**
 * Clear MSR Data
 * Clears the MSR Data buffer
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
msr_clearMSRData();

/**
 * Get MSR Data
 * Reads the MSR Data buffer
 * @param reData Card data
 * @param reLen Card data length
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
msr_getMSRData(OUT BYTE * reData,
  IN_OUT int *            reLen);

/**
 * Disable MSR Swipe
 * Cancels MSR swipe request.
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
msr_cancelMSRSwipe();

/**
 * Start MSR Swipe
 * Enables MSR, waiting for swipe to occur. Allows track selection.
 * Returns IDTMSRData instance to MSR_callBack()
 * @param timeout Swipe Timeout Value
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 * Note: if auto poll mode is on, it will return command not allowed error
 */
int
msr_startMSRSwipe(IN int _timeout);


/**
 * executeTransaction
 *  Requests 3 sets of public keys: encrypting Keys, signing/validating keys, signing/validating 3rd party apps
 *
 * @param data WorldPay data object
 * @param wpCallback WorldPay callback
 * @param requestOnly
 *  - 0 = send transaction and return response,
 *  - 1 = send transaction and return both request and response,
 *  - 2 = do not send transaction, instead return request
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
executeTransaction(WorldPayData * data, pWP_callBack wpCallback, int requestOnly);

/**
 * forwardTransaction
 *  Send the saved data to WorldPay and complete the transaction.
 *
 * @param wpCallback WPCallback is the callback to send the results.  Should the the same as executeTransaction callback.
 * @param forwardID = ID, which could be either unique ID or Memo.
 * @param forwardIDLen The length of forwardID.
 * @param password = password.  If null/blank, no password.
 * @param passwordLen The length of passwordLen.
 * @param bypassProcess = true means read the file from disk, but don't send to WorldPay, then delete the transaction as if you did send to WorldPay.  The purpose of this is to allow them to delete transactions from the storage without sending to WorldPay.
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
forwardTransaction(IN pWP_callBack wpCallback, IN char *forwardID, IN int forwardIDLen, IN char *password, IN int passwordLen, IN int bypassProcessing);

/**
 * Cancels WorldPay transaction.
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
cancelWorldPay();

void
printfChar(BYTE * data, int dataLen);

/**
 * Parser the MSR data from the buffer into IDTMSTData structure
 * @param resData MSR card data buffer
 * @param resLen the length of resData
 * @param cardData the parser result with IDTMSTData structure
 */
void
parseMSRData(IN BYTE * resData, IN int resLen,
  IN_OUT IDTMSRData * cardData);

/**
 * Get Key Format For DUKPT
 *
 * Specifies how data will be encrypted with Data Key or PIN key (if
 * DUKPT key loaded). This applies to both MSR and ICC
 *
 * @param format Response returned from method:
 * - 'TDES': Encrypted card data with TDES if  DUKPT Key had been loaded.
 *           (default)
 * - 'AES': Encrypted card data with AES if DUKPT Key had been loaded.
 * - 'NONE': No Encryption.
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString
 */
int
msr_getKeyFormatForICCDUKPT(OUT BYTE * format);

/**
 * Get Key Type for DUKPT
 *
 * Specifies the key type used for ICC DUKPT encryption.  This applies
 * to both MSR and ICC.
 *
 * @param type Response returned from method:
 * - 'DATA': Encrypted card data with Data Key DUKPT Key had been loaded.
 *           (default)
 * - 'PIN': Encrypted card data with PIN Key if DUKPT Key had been loaded.
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString
 */
int
msr_getKeyTypeForICCDUKPT(OUT BYTE * type);

/**
 * Set Key Format for DUKPT
 *
 * Sets how data will be encrypted, with either TDES or AES (if DUKPT
 * key loaded) This applies to both MSR and ICC
 *
 * @param format encryption Encryption Type
 * - 00: Encrypt with TDES
 * - 01: Encrypt with AES
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString
 */
int
msr_setKeyFormatForICCDUKPT(IN BYTE format);

/**
 * Set Key Type for DUKPT Key
 *
 * Sets which key the data will be encrypted with, with either Data
 * Key or PIN key (if DUKPT key loaded) This applies to both MSR and
 * ICC
 *
 * @param type Encryption Type
 * - 00: Encrypt with Data Key
 * - 01: Encrypt with PIN Key
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString
 */
int
msr_setKeyTypeForICCDUKPT(IN BYTE type);

/**
 * Set MSR Capture Mode.
 *
 * For Non-SRED Augusta Only
 *
 * Switch between Auto mode and Buffer mode. Auto mode only available
 * on KB interface
 *
 *
 * @param isBufferMode
 * - 1: Enter into Buffer mode.
 * - 0: Enter into Auto mode. KB mode only. Swipes automatically captured
 *      and sent to keyboard buffer
 * @param withNotification
 * - 1: with notification when swiped MSR data.
 * - 0: without notification when swiped MSR data.
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString
 */
int
msr_captureMode(int isBufferMode,
  int               withNotification);

/**
 * Flush Track Data
 * Clears any track data being retained in memory by future PIN Block request.
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
msr_flushTrackData();

/**
 * Set Expiration Masking
 *
 * Sets the flag to mask the expiration date
 *
 * @param mask TRUE = mask expiration
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString
 *
 */
int
msr_setExpirationMask(int mask);

/**
 * Get MSR expiration date mask.
 *
 * @param value
 *            5001 <Setting Value>.
 *              setting Value: '0' = masked, '1' = not-masked
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString
 */
int
msr_getExpirationMask(BYTE * value);

/**
 * Set Clear PAN ID.
 *
 * @param val
 *            Set Clear PAN ID to value: Number of digits to show in clear.  Range 0-6.
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString
 */
int
msr_setClearPANID(BYTE val);

/**
 * Get Clear PAN ID.
 *
 * Returns the number of digits that begin the PAN that will be in the clear
 *
 * @param value
 *            4901 <Setting Value>.
 *            setting Value: Number of digits in clear.  Values are char '0' - '6'
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString
 */
int
msr_getClearPANID(BYTE * value);

/**
 * Set MSR Swipe Forced Encryption Option.
 *
 * @param tarck1
 *            Set track1 encryption to true or false.
 * @param tarck2
 *            Set track2 encryption to true or false.
 * @param tarck3
 *            Set track3 encryption to true or false.
 * @param tarck3card0
 *            Set track3 card0 encryption to true or false.
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString
 */
int
msr_setSwipeForcedEncryptionOption(int track1, int track2, int track3, int track3card0);

/**
 * Get MSR Swipe Forced Encryption Option.
 *
 * @param option
 *            8401 <Setting Value>.
 *            Setting Value Byte using lower four bits as flags.  0 = Force Encryption Off, 1 = Force Encryption On
 *				   bit0 = Track 1
 *				   bit1 = Track 2
 *				   bit2 = Track 3
 *				   bit4 = Track 3 Card Option 0
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString
 */
int
msr_getSwipeForcedEncryptionOption(BYTE * option);

/**
 * Set MSR Swipe Mask Option.
 *
 * Sets the swipe mask/clear data sending option
 *
 * @param tarck1
 *            Set track1 mask to true or false.
 * @param tarck2
 *            Set track2 mask to true or false.
 * @param tarck3
 *            Set track3 mask to true or false.
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString
 */
int
msr_setSwipeMaskOption(int track1, int track2, int track3);

/**
 * Get MSR Swipe Mask Option.
 *
 * Gets the swipe mask/clear data sending option
 *
 * @param option
 *            8601 <Setting Value>.
 *            Setting Value Byte using lower three bits as flags.  0 = Mask Option Off, 1 = Mask Option On
 *				   bit0 = Track 1
 *				   bit1 = Track 2
 *				   bit2 = Track 3
 *				   Example: Response 0x03 = Track1/Track2 Masked Option ON, Track3 Masked Option Off
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString
 */
int
msr_getSwipeMaskOption(BYTE * option);

/**
 * Disable MSR
 * Disable MSR functions.
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
msr_disable();

/**
 * Get MSR Function Status.
 *
 * Gets the MSR function status
 *
 * @param enable: 1 = MSR enabled, 0 = MSR disabled
 * @param isBufferMode: 1 = buffer mode, 0 = auto mode
 * @param withNotification: 1 = with notification, 0 = without notification
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString
 */
int
msr_getFunctionStatus(int * enable, int * isBufferMode, int * withNotification);

/**
 * Get Encrypted PIN
 *
 * Requests PIN Entry
 * @param mode
 * - 0x00- Cancel: Cancels PIN entry = also can execute pin_cancelPINEntry(). All other parameters for this method will be ignored
 * - 0x01- Online PIN DUKPT
 * - 0x02- Online PIN MKSK
 * - 0x03- Offline PIN  (No need to define PAN Source or ICC PAN)
 * @param PANSource
 * - 0x00- ICC:  PAN Captured from ICC and must be provided in iccPAN parameter
 * - 0x01- MSR:  PAN Captured from MSR swipe and will be inserted by Spectrum Pro. No need to provide iccPAN parameter.
 * @param iccPAN  PAN captured from ICC.  When PAN captured from MSR, this parameter will be ignored
 * @param iccPANLen  the length of iccPAN
 * @param startTimeout  The amount of time allowed to start PIN entry before timeout
 * @param entryTimeout  The amount of time to enter the PIN after first digit selected before timeout
 * @param language  Valid values "EN" for English, "ES" for Spanish, "ZH" for Chinese, "FR" for French
 * @param languageLen the length of language
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 */
int
pin_getPIN(IN int mode,
  IN int          PANSource,
  IN char *       iccPAN,
  IN int          iccPANLen,
  IN int          startTimeout,
  IN int          entryTimeout,
  IN char *       language,
  IN int          languageLen);

/**
 * Cancel PIN Entry
 *
 * Cancels PIN entry request
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 */
int
pin_cancelPINEntry();

/**
 * Set Key Values
 *
 * Set return key values on or off
 *
 * @param mode  On: 1, Off: 0
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 */
int
pin_setKeyValues(int mode);

/**
 * Get Encrypted DUKPT PIN
 *
 * Requests PIN Entry for online authorization. PIN block and KSN
 * returned in callback function DeviceState.TransactionData with
 * cardData.pin_pinblock.  A swipe must be captured first before this
 * function can execute
 * @param keyType PIN block key type. Valid values 0, 3 for TDES, 4 for AES
 * @param timeout  PIN entry timout
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 */
int
pin_getEncryptedOnlinePIN(IN int keyType,
  IN int                         timeout);

/**
 * Get PAN
 *
 * Requests PAN Entry on pinpad
 *
 * @param getCSC Include Customer Service Code (also known as CVV, CVC)
 * @param timeout  PAN entry timout
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 */
int
pin_getPAN(IN int getCSC,
  IN int          timeout);

/**
 * Prompt for Credit or Debit
 *
 * Requests prompt for Credit or Debit. Response returned in callback function
 * as DeviceState.MenuItem with data MENU_SELECTION_CREDIT = 0,
 * MENU_SELECTION_DEBIT = 1
 *
 * @param currencySymbol Allowed values are $ (0x24), ?�驴??(0xA5), ?�驴??(0xA3), ?�驴??(0xA4), or NULL
 * @param currencySymbolLen length of currencySymbol
 * @param displayAmount  Amount to display (can be NULL)
 * @param displayAmountLen  length of displayAmount
 * @param timeout  Menu entry timout. Valid values 2-20 seconds
 *
 * @param retData If successful, the return code is zero and the data
 * is 1 byte (0: Credit 1: Debit).  If the return code is not zero, it
 * may be a four-byte Extended Status Code
 * @param currencySymbolLen length of currencySymbol
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString()
 */
int
pin_promptCreditDebit(IN char * currencySymbol,
  IN int                        currencySymbolLen,
  IN char *                     displayAmount,
  IN int                        displayAmountLen,
  IN int                        timeout,
  OUT BYTE *                    retData,
  IN_OUT int *                  retDataLen);

/**
 * Get Encrypted PIN
 *
 * Requests PIN Entry
 * @param keyType
 * - 0x00- MKSK-TDES:  External Plaintext PAN
 * - 0x01- DUKPT-TDES:  External Plaintext PAN
 * - 0x10 MKSK-TDES:  External Ciphertext PAN
 * - 0x11 DUKPT-TDES:  External Ciphertext PAN
 *        @param PAN Account Number
 *        @param PANLen length of PAN
 *        @param message Message to display
 *        @param messageLen length of message
 *        @param timeout  PIN entry timeout
 *
 * @return RETURN_CODE:  Values can be parsed with errorCode.getErrorString()
 *
 */
int
pin_getEncryptedPIN(int keyType,
  char *                PAN,
  int                   PANLen,
  char *                message,
  int                   messageLen,
  int                   timeout);

/**
 * Prompt for Key Input
 *
 * Prompts for a numeric key using the secure message according to the
 * following table
 *
 * Msg Id |English Prompt | Portuguese Prompt | Spanish Prompt | French Prompt
 * ---------- | ---------- | ----------  | ---------- | ----------
 * 1 | ENTER | ENTER | INGRESE | ENTREZ
 * 2 | REENTER | RE-INTRODUZIR | REINGRESE | RE-ENTREZ
 * 3 | ENTER YOUR | INTRODUZIR O SEU | INGRESE SU | ENTREZ VOTRE
 * 4 | REENTER YOUR | RE-INTRODUZIR O SEU | REINGRESE SU | RE-ENTREZ VOTRE
 * 5 | PLEASE ENTER | POR FAVOR DIGITE | POR FAVOR INGRESE | SVP ENTREZ
 * 6 | PLEASE REENTER | POR FAVO REENTRAR | POR FAVO REINGRESE | SVP RE-ENTREZ
 * 7 | PO NUMBER | N?�MERO PO | NUMERO PO | No COMMANDE
 * 8 | DRIVER ID | LICEN?�A | LICENCIA | ID CONDUCTEUR
 * 9 | ODOMETER | ODOMETER | ODOMETRO | ODOMETRE
 * 10 | ID NUMBER | N?�MERO ID | NUMERO ID | No IDENT
 * 11 | EQUIP CODE | EQUIP CODE | CODIGO EQUIP | CODE EQUIPEMENT
 * 12 | DRIVERS ID | DRIVER ID | ID CONDUCTOR | ID CONDUCTEUR
 * 13 | JOB NUMBER | EMP N?�MERO | NUMERO EMP | No TRAVAIL
 * 14 | WORK ORDER | TRABALHO ORDEM | ORDEN TRABAJO | FICHE TRAVAIL
 * 15 | VEHICLE ID | ID VE?�CULO | ID VEHICULO | ID VEHICULE
 * 16 | ENTER DRIVER | ENTER DRIVER | INGRESE CONDUCTOR | ENTR CONDUCTEUR
 * 17 | ENTER DEPT | ENTER DEPT | INGRESE DEPT | ENTR DEPARTEMNT
 * 18 | ENTER PHONE | ADICIONAR PHONE | INGRESE TELEFONO | ENTR No TELEPH
 * 19 | ENTER ROUTE | ROUTE ADD | INGRESE RUTA | ENTREZ ROUTE
 * 20 | ENTER FLEET | ENTER FROTA | INGRESE FLOTA | ENTREZ PARC AUTO
 * 21 | ENTER JOB ID | ENTER JOB ID | INGRESE ID TRABAJO | ENTR ID TRAVAIL
 * 22 | ROUTE NUMBER | N?�MERO PATH | RUTA NUMERO | No ROUTE
 * 23 | ENTER USER ID | ENTER USER ID | INGRESE ID USUARIO | ID UTILISATEUR
 * 24 | FLEET NUMBER | N?�MERO DE FROTA | FLOTA NUMERO | No PARC AUTO
 * 25 | ENTER PRODUCT | ADICIONAR PRODUTO | INGRESE PRODUCTO | ENTREZ PRODUIT
 * 26 | DRIVER NUMBER | N?�MERO DRIVER | CONDUCTOR NUMERO | No CONDUCTEUR
 * 27 | ENTER LICENSE | ENTER LICEN?�A | INGRESE LICENCIA | ENTREZ PERMIS
 * 28 | ENTER FLEET NO | ENTER NRO FROTA | INGRESE NRO FLOTA | ENT No PARC AUTO
 * 29 | ENTER CAR WASH | WASH ENTER | INGRESE LAVADO | ENTREZ LAVE-AUTO
 * 30 | ENTER VEHICLE | ENTER VE?�CULO | INGRESE VEHICULO | ENTREZ VEHICULE
 * 31 | ENTER TRAILER | TRAILER ENTER | INGRESE TRAILER | ENTREZ REMORQUE
 * 32 | ENTER ODOMETER | ENTER ODOMETER | INGRESE ODOMETRO | ENTREZ ODOMETRE
 * 33 | DRIVER LICENSE | CARTEIRA DE MOTORISTA | LICENCIA CONDUCTOR | PERMIS CONDUIRE
 * 34 | ENTER CUSTOMER | ENTER CLIENTE | INGRESE CLIENTE | ENTREZ CLIENT
 * 35 | VEHICLE NUMBER | N?�MERO DO VE?�CULO | VEHICULO NUMERO | No VEHICULE
 * 36 | ENTER CUST DATA | ENTER CLIENTE INFO | INGRESE INFO CLIENTE | INFO CLIENT
 * 37 | REENTER DRIVID | REENTRAR DRIVER ID | REINGRESE ID CHOFER | RE-ENTR ID COND
 * 38 | ENTER USER DATA | ENTER INFO USU?�RIO | INGRESE INFO USUARIO | INFO UTILISATEUR
 * 39 | ENTER CUST CODE | ENTER CODE. CLIENTE | INGRESE COD. CLIENTE | ENTR CODE CLIENT
 * 40 | ENTER EMPLOYEE | ENTER FUNCION?�RIO | INGRESE EMPLEADO | ENTREZ EMPLOYE
 * 41 | ENTER ID NUMBER | ENTER N?�MERO ID | INGRESE NUMERO ID | ENTREZ No ID
 * 42 | ENTER DRIVER ID | ENTER ID DRIVER | INGRESE ID CONDUCTOR | No CONDUCTEUR
 * 43 | ENTER FLEET PIN | ENTER PIN FROTA | INGRESE PIN DE FLOTA | NIP PARC AUTO
 * 44 | ODOMETER NUMBER | N?�MERO ODOMETER | ODOMETRO NUMERO | No ODOMETRE
 * 45 | ENTER DRIVER LIC | ENTER DRIVER LIC | INGRESE LIC CONDUCTOR | PERMIS CONDUIRE
 * 46 | ENTER TRAILER NO | NRO TRAILER ENTER | INGRESE NRO TRAILER | ENT No REMORQUE
 * 47 | REENTER VEHICLE | REENTRAR VE?�CULO | REINGRESE VEHICULO | RE-ENTR VEHICULE
 * 48 | ENTER VEHICLE ID | ENTER VE?�CULO ID | INGRESE ID VEHICULO | ENTR ID VEHICULE
 * 49 | ENTER BIRTH DATE | INSERIR DATA NAC | INGRESE FECHA NAC | ENT DT NAISSANCE
 * 50 | ENTER DOB MMDDYY | ENTER FDN MMDDYY | INGRESE FDN MMDDAA | NAISSANCE MMJJAA
 * 51 | ENTER FLEET DATA | ENTER FROTA INFO | INGRESE INFO DE FLOTA | INFO PARC AUTO
 * 52 | ENTER REFERENCE | ENTER REFER?�NCIA | INGRESE REFERENCIA | ENTREZ REFERENCE
 * 53 | ENTER AUTH NUMBR | ENTER N?�MERO AUT | INGRESE NUMERO AUT | No AUTORISATION
 * 54 | ENTER HUB NUMBER | ENTER HUB NRO | INGRESE NRO HUB | ENTREZ No NOYAU
 * 55 | ENTER HUBOMETER | MEDIDA PARA ENTRAR HUB | INGRESE MEDIDO DE HUB | COMPTEUR NOYAU
 * 56 | ENTER TRAILER ID | TRAILER ENTER ID | INGRESE ID TRAILER | ENT ID REMORQUE
 * 57 | ODOMETER READING | QUILOMETRAGEM | LECTURA ODOMETRO | LECTURE ODOMETRE
 * 58 | REENTER ODOMETER | REENTRAR ODOMETER | REINGRESE ODOMETRO | RE-ENT ODOMETRE
 * 59 | REENTER DRIV. ID | REENTRAR DRIVER ID | REINGRESE ID CHOFER | RE-ENT ID CONDUC
 * 60 | ENTER CUSTOMER ID | ENTER CLIENTE ID | INGRESE ID CLIENTE | ENTREZ ID CLIENT
 * 61 | ENTER CUST. ID | ENTER CLIENTE ID | INGRESE ID CLIENTE | ENTREZ ID CLIENT
 * 62 | ENTER ROUTE NUM | ENTER NUM ROUTE | INGRESE NUM RUTA | ENT No ROUTE
 * 63 | ENTER FLEET NUM | FROTA ENTER NUM | INGRESE NUM FLOTA | ENT No PARC AUTO
 * 64 | FLEET PIN | FROTA PIN | PIN DE FLOTA | NIP PARC AUTO
 * 65 | DRIVER # | DRIVER # | CONDUCTOR # | CONDUCTEUR
 * 66 | ENTER DRIVER # | ENTER DRIVER # | INGRESE CONDUCTOR # | ENT # CONDUCTEUR
 * 67 | VEHICLE # | VE?�CULO # | VEHICULO # | # VEHICULE
 * 68 | ENTER VEHICLE # | ENTER VE?�CULO # | INGRESE VEHICULO # | ENT # VEHICULE
 * 69 | JOB # | TRABALHO # | TRABAJO # | # TRAVAIL
 * 70 | ENTER JOB # | ENTER JOB # | INGRESE TRABAJO # | ENTREZ # TRAVAIL
 * 71 | DEPT NUMBER | N?�MERO DEPT | NUMERO DEPTO | No DEPARTEMENT
 * 72 | DEPARTMENT # | DEPARTAMENTO # | DEPARTAMENTO # | DEPARTEMENT
 * 73 | ENTER DEPT # | ENTER DEPT # | INGRESE DEPTO # | ENT# DEPARTEMENT
 * 74 | LICENSE NUMBER | N?�MERO DE LICEN?�A | NUMERO LICENCIA | No PERMIS
 * 75 | LICENSE # | LICEN?�A # | LICENCIA # | # PERMIS
 * 76 | ENTER LICENSE # | ENTER LICEN?�A # | INGRESE LICENCIA # | ENTREZ # PERMIS
 * 77 | DATA | INFO | INFO | INFO
 * 78 | ENTER DATA | ENTER INFO | INGRESE INFO | ENTREZ INFO
 * 79 | CUSTOMER DATA | CLIENTE INFO | INFO CLIENTE | INFO CLIENT
 * 80 | ID # | ID # | ID # | # ID
 * 81 | ENTER ID # | ENTER ID # | INGRESE ID # | ENTREZ # ID
 * 82 | USER ID | USER ID | ID USUARIO | ID UTILISATEUR
 * 83 | ROUTE # | ROUTE # | RUTA # | # ROUTE
 * 84 | ENTER ROUTE # | ADD ROUTE # | INGRESE RUTA # | ENTREZ # ROUTE
 * 85 | ENTER CARD NUM | ENTER N?�MERO DE CART?�O | INGRESE NUM TARJETA | ENTREZ NO CARTE
 * 86 | EXP DATE(YYMM) | VALIDADE VAL (AAMM) | FECHA EXP (AAMM) | DATE EXPIR(AAMM)
 * 87 | PHONE NUMBER | TELEFONE | NUMERO TELEFONO | NO TEL
 * 88 | CVV START DATE | CVV DATA DE IN?�CIO | CVV FECHA INICIO | CVV DATE DE DEBUT
 * 89 | ISSUE NUMBER | N?�MERO DE EMISS?�O | NUMERO DE EMISION | NO DEMISSION
 * 90 | START DATE (MMYY) | DATA DE IN?�CIO (AAMM) | FECHA INICIO (AAMM) | DATE DE DEBUT-AAMM
 *
 *          @param messageID  Message (1-90)
 *          @param languageID 0=English Prompt, 1=Portuguese Prompt, 2=Spanish Prompt, 3=French Prompt
 *          @param maskInput  1 = entry is masked with '*', 0 = entry is displayed on keypad
 *          @param minLen  Minimum input length.  Cannot be less than 1
 *          @param maxLen Maximum input length.  Cannot be greater than 16
 *          @param timeout Timout value, in seconds
 *
 *
 * @return RETURN_CODE:  Values can be parsed with errorCode.getErrorString()
 */

int
pin_promptForKeyInput(int messageID,
  int                     languageID,
  int                     maskInput,
  int                     minLen,
  int                     maxLen,
  int                     timeout);

/**
 * Prompt for Amount Input
 *
 * Prompts for amount input using the secure message according to the
 * following table
 *
 * Msg Id |English Prompt | Portuguese Prompt | Spanish Prompt | French Prompt
 * ---------- | ---------- | ----------  | ---------- | ----------
 * 1 | ENTER | ENTER | INGRESE | ENTREZ
 * 2 | REENTER | RE-INTRODUZIR | REINGRESE | RE-ENTREZ
 * 3 | ENTER YOUR | INTRODUZIR O SEU | INGRESE SU | ENTREZ VOTRE
 * 4 | REENTER YOUR | RE-INTRODUZIR O SEU | REINGRESE SU | RE-ENTREZ VOTRE
 * 5 | PLEASE ENTER | POR FAVOR DIGITE | POR FAVOR INGRESE | SVP ENTREZ
 * 6 | PLEASE REENTER | POR FAVO REENTRAR | POR FAVO REINGRESE | SVP RE-ENTREZ
 * 7 | PO NUMBER | N?�MERO PO | NUMERO PO | No COMMANDE
 * 8 | DRIVER ID | LICEN?�A | LICENCIA | ID CONDUCTEUR
 * 9 | ODOMETER | ODOMETER | ODOMETRO | ODOMETRE
 * 10 | ID NUMBER | N?�MERO ID | NUMERO ID | No IDENT
 * 11 | EQUIP CODE | EQUIP CODE | CODIGO EQUIP | CODE EQUIPEMENT
 * 12 | DRIVERS ID | DRIVER ID | ID CONDUCTOR | ID CONDUCTEUR
 * 13 | JOB NUMBER | EMP N?�MERO | NUMERO EMP | No TRAVAIL
 * 14 | WORK ORDER | TRABALHO ORDEM | ORDEN TRABAJO | FICHE TRAVAIL
 * 15 | VEHICLE ID | ID VE?�CULO | ID VEHICULO | ID VEHICULE
 * 16 | ENTER DRIVER | ENTER DRIVER | INGRESE CONDUCTOR | ENTR CONDUCTEUR
 * 17 | ENTER DEPT | ENTER DEPT | INGRESE DEPT | ENTR DEPARTEMNT
 * 18 | ENTER PHONE | ADICIONAR PHONE | INGRESE TELEFONO | ENTR No TELEPH
 * 19 | ENTER ROUTE | ROUTE ADD | INGRESE RUTA | ENTREZ ROUTE
 * 20 | ENTER FLEET | ENTER FROTA | INGRESE FLOTA | ENTREZ PARC AUTO
 * 21 | ENTER JOB ID | ENTER JOB ID | INGRESE ID TRABAJO | ENTR ID TRAVAIL
 * 22 | ROUTE NUMBER | N?�MERO PATH | RUTA NUMERO | No ROUTE
 * 23 | ENTER USER ID | ENTER USER ID | INGRESE ID USUARIO | ID UTILISATEUR
 * 24 | FLEET NUMBER | N?�MERO DE FROTA | FLOTA NUMERO | No PARC AUTO
 * 25 | ENTER PRODUCT | ADICIONAR PRODUTO | INGRESE PRODUCTO | ENTREZ PRODUIT
 * 26 | DRIVER NUMBER | N?�MERO DRIVER | CONDUCTOR NUMERO | No CONDUCTEUR
 * 27 | ENTER LICENSE | ENTER LICEN?�A | INGRESE LICENCIA | ENTREZ PERMIS
 * 28 | ENTER FLEET NO | ENTER NRO FROTA | INGRESE NRO FLOTA | ENT No PARC AUTO
 * 29 | ENTER CAR WASH | WASH ENTER | INGRESE LAVADO | ENTREZ LAVE-AUTO
 * 30 | ENTER VEHICLE | ENTER VE?�CULO | INGRESE VEHICULO | ENTREZ VEHICULE
 * 31 | ENTER TRAILER | TRAILER ENTER | INGRESE TRAILER | ENTREZ REMORQUE
 * 32 | ENTER ODOMETER | ENTER ODOMETER | INGRESE ODOMETRO | ENTREZ ODOMETRE
 * 33 | DRIVER LICENSE | CARTEIRA DE MOTORISTA | LICENCIA CONDUCTOR | PERMIS CONDUIRE
 * 34 | ENTER CUSTOMER | ENTER CLIENTE | INGRESE CLIENTE | ENTREZ CLIENT
 * 35 | VEHICLE NUMBER | N?�MERO DO VE?�CULO | VEHICULO NUMERO | No VEHICULE
 * 36 | ENTER CUST DATA | ENTER CLIENTE INFO | INGRESE INFO CLIENTE | INFO CLIENT
 * 37 | REENTER DRIVID | REENTRAR DRIVER ID | REINGRESE ID CHOFER | RE-ENTR ID COND
 * 38 | ENTER USER DATA | ENTER INFO USU?�RIO | INGRESE INFO USUARIO | INFO UTILISATEUR
 * 39 | ENTER CUST CODE | ENTER CODE. CLIENTE | INGRESE COD. CLIENTE | ENTR CODE CLIENT
 * 40 | ENTER EMPLOYEE | ENTER FUNCION?�RIO | INGRESE EMPLEADO | ENTREZ EMPLOYE
 * 41 | ENTER ID NUMBER | ENTER N?�MERO ID | INGRESE NUMERO ID | ENTREZ No ID
 * 42 | ENTER DRIVER ID | ENTER ID DRIVER | INGRESE ID CONDUCTOR | No CONDUCTEUR
 * 43 | ENTER FLEET PIN | ENTER PIN FROTA | INGRESE PIN DE FLOTA | NIP PARC AUTO
 * 44 | ODOMETER NUMBER | N?�MERO ODOMETER | ODOMETRO NUMERO | No ODOMETRE
 * 45 | ENTER DRIVER LIC | ENTER DRIVER LIC | INGRESE LIC CONDUCTOR | PERMIS CONDUIRE
 * 46 | ENTER TRAILER NO | NRO TRAILER ENTER | INGRESE NRO TRAILER | ENT No REMORQUE
 * 47 | REENTER VEHICLE | REENTRAR VE?�CULO | REINGRESE VEHICULO | RE-ENTR VEHICULE
 * 48 | ENTER VEHICLE ID | ENTER VE?�CULO ID | INGRESE ID VEHICULO | ENTR ID VEHICULE
 * 49 | ENTER BIRTH DATE | INSERIR DATA NAC | INGRESE FECHA NAC | ENT DT NAISSANCE
 * 50 | ENTER DOB MMDDYY | ENTER FDN MMDDYY | INGRESE FDN MMDDAA | NAISSANCE MMJJAA
 * 51 | ENTER FLEET DATA | ENTER FROTA INFO | INGRESE INFO DE FLOTA | INFO PARC AUTO
 * 52 | ENTER REFERENCE | ENTER REFER?�NCIA | INGRESE REFERENCIA | ENTREZ REFERENCE
 * 53 | ENTER AUTH NUMBR | ENTER N?�MERO AUT | INGRESE NUMERO AUT | No AUTORISATION
 * 54 | ENTER HUB NUMBER | ENTER HUB NRO | INGRESE NRO HUB | ENTREZ No NOYAU
 * 55 | ENTER HUBOMETER | MEDIDA PARA ENTRAR HUB | INGRESE MEDIDO DE HUB | COMPTEUR NOYAU
 * 56 | ENTER TRAILER ID | TRAILER ENTER ID | INGRESE ID TRAILER | ENT ID REMORQUE
 * 57 | ODOMETER READING | QUILOMETRAGEM | LECTURA ODOMETRO | LECTURE ODOMETRE
 * 58 | REENTER ODOMETER | REENTRAR ODOMETER | REINGRESE ODOMETRO | RE-ENT ODOMETRE
 * 59 | REENTER DRIV. ID | REENTRAR DRIVER ID | REINGRESE ID CHOFER | RE-ENT ID CONDUC
 * 60 | ENTER CUSTOMER ID | ENTER CLIENTE ID | INGRESE ID CLIENTE | ENTREZ ID CLIENT
 * 61 | ENTER CUST. ID | ENTER CLIENTE ID | INGRESE ID CLIENTE | ENTREZ ID CLIENT
 * 62 | ENTER ROUTE NUM | ENTER NUM ROUTE | INGRESE NUM RUTA | ENT No ROUTE
 * 63 | ENTER FLEET NUM | FROTA ENTER NUM | INGRESE NUM FLOTA | ENT No PARC AUTO
 * 64 | FLEET PIN | FROTA PIN | PIN DE FLOTA | NIP PARC AUTO
 * 65 | DRIVER # | DRIVER # | CONDUCTOR # | CONDUCTEUR
 * 66 | ENTER DRIVER # | ENTER DRIVER # | INGRESE CONDUCTOR # | ENT # CONDUCTEUR
 * 67 | VEHICLE # | VE?�CULO # | VEHICULO # | # VEHICULE
 * 68 | ENTER VEHICLE # | ENTER VE?�CULO # | INGRESE VEHICULO # | ENT # VEHICULE
 * 69 | JOB # | TRABALHO # | TRABAJO # | # TRAVAIL
 * 70 | ENTER JOB # | ENTER JOB # | INGRESE TRABAJO # | ENTREZ # TRAVAIL
 * 71 | DEPT NUMBER | N?�MERO DEPT | NUMERO DEPTO | No DEPARTEMENT
 * 72 | DEPARTMENT # | DEPARTAMENTO # | DEPARTAMENTO # | DEPARTEMENT
 * 73 | ENTER DEPT # | ENTER DEPT # | INGRESE DEPTO # | ENT# DEPARTEMENT
 * 74 | LICENSE NUMBER | N?�MERO DE LICEN?�A | NUMERO LICENCIA | No PERMIS
 * 75 | LICENSE # | LICEN?�A # | LICENCIA # | # PERMIS
 * 76 | ENTER LICENSE # | ENTER LICEN?�A # | INGRESE LICENCIA # | ENTREZ # PERMIS
 * 77 | DATA | INFO | INFO | INFO
 * 78 | ENTER DATA | ENTER INFO | INGRESE INFO | ENTREZ INFO
 * 79 | CUSTOMER DATA | CLIENTE INFO | INFO CLIENTE | INFO CLIENT
 * 80 | ID # | ID # | ID # | # ID
 * 81 | ENTER ID # | ENTER ID # | INGRESE ID # | ENTREZ # ID
 * 82 | USER ID | USER ID | ID USUARIO | ID UTILISATEUR
 * 83 | ROUTE # | ROUTE # | RUTA # | # ROUTE
 * 84 | ENTER ROUTE # | ADD ROUTE # | INGRESE RUTA # | ENTREZ # ROUTE
 * 85 | ENTER CARD NUM | ENTER N?�MERO DE CART?�O | INGRESE NUM TARJETA | ENTREZ NO CARTE
 * 86 | EXP DATE(YYMM) | VALIDADE VAL (AAMM) | FECHA EXP (AAMM) | DATE EXPIR(AAMM)
 * 87 | PHONE NUMBER | TELEFONE | NUMERO TELEFONO | NO TEL
 * 88 | CVV START DATE | CVV DATA DE IN?�CIO | CVV FECHA INICIO | CVV DATE DE DEBUT
 * 89 | ISSUE NUMBER | N?�MERO DE EMISS?�O | NUMERO DE EMISION | NO DEMISSION
 * 90 | START DATE (MMYY) | DATA DE IN?�CIO (AAMM) | FECHA INICIO (AAMM) | DATE DE DEBUT-AAMM
 *
 *          @param messageID  Message (1-90)
 *          @param languageID 0=English Prompt, 1=Portuguese Prompt, 2=Spanish Prompt, 3=French Prompt
 *          @param minLen  Minimum input length.  Cannot be less than 1
 *          @param maxLen Maximum input length.  Cannot be greater than 15
 *          @param timeout Timout value, in seconds
 *
 *
 * @return RETURN_CODE: Values can be parsed with errorCode.getErrorString()
 */
int
pin_promptForAmountInput(int messageID,
  int                        languageID,
  int                        minLen,
  int                        maxLen,
  int                        timeout);

/**
 * Get Function Key
 *
 * Captures a function key
 *
 *              - Backspace = B
 *              - Cancel = C
 *              - Enter = E
 *              - * = *
 *              - # = #
 *              - Help = ?
 *              - Function Key 1 = F1
 *              - Function Key 2 = F2
 *              - Function Key 3 = F3
 *
 *              @param timeout Timeout, in seconds
 * @return RETURN_CODE:  Values can be parsed with errorCode.getErrorString()
 *
 */
int
pin_getFunctionKey(int timeout);

/**
 * Send Beep
 *
 * Executes a beep request.
 * @param frequency  Frequency, range 200-20000Hz  Not used for NEO 2 devices
 * @param duration Duration, range 16-65535ms  Not used for NEO 2 devices
 *
 *
 * @return RETURN_CODE: Values can be parsed with device_getResponseCodeString
 */

int
pin_sendBeep(int frequency,
  int            duration);

/**
 * Capture PIN
 *
 *  @param timeout Timeout, in seconds. Value of 0 will use system timeout, if any
 *  @param type PAN and Key Type
 * - 00h = MKSK to encrypt PIN, Internal PAN (from MSR)
 * - 01h = DUKPT to encrypt PIN, Internal PAN (from MSR)
 * - 10h = MKSK to encrypt PIN, External Plaintext PAN
 * - 11h = DUKPT to encrypt PIN, External Plaintext PAN
 * - 20h = MKSK to encrypt PIN, External Ciphertext PAN
 * - 21h = DUKPT to encrypt PIN, External Ciphertext PAN
 *
 * @param PAN Personal Account Number (if internal, value is 0)
 * @param PANLen Length of PAN
 * @param minPIN Minimum PIN Length
 * @param maxPIN Maximum PIN Length
 * @param message LCD Message
 * @param messageLen Length of message
 *
 * @return RETURN_CODE:  Values can be parsed with errorCode.getErrorString()
 *
 */
int
pin_capturePin(IN int timeout, IN int type, IN char * PAN, IN int PANLen, IN int minPIN, IN int maxPIN,
  IN char * message, IN int messageLen);

/** * Capture PIN Ext
 *
 * @param type PAN and Key Type
 * - 00h: MKSK to encrypt PIN, Internal PAN (from MSR or Manual PAN Entry or Contactless EMV Transaction)
 * - 01h: DUKPT to encrypt PIN, Internal PAN (from MSR or Manual PAN Entry or Contactless EMV Transaction)
 * - 10h: MKSK to encrypt PIN, External Plaintext PAN
 * - 11h:  DUKPT to encrypt PIN, External Plaintext PAN
 * - 20h: MKSK to encrypt PIN, External Ciphertext PAN (for PIN pad only)
 * - 21h:  DUKPT to encrypt PIN, External Ciphertext PAN (for PIN pad only)
 * - 80h:  MKSK to encrypt PIN, Internal PAN, Verify PIN (from MSR or Manual PAN Entry or Contactless EMV Transaction)
 * - 81h:  DUKPT to encrypt PIN, Internal PAN, Verify PIN (from MSR or Manual PAN Entry or Contactless EMV Transaction)
 * - 90h: MKSK to encrypt PIN, External Plaintext PAN, Verify PIN
 * - 91h: DUKPT to encrypt PIN, External Plaintext PAN, Verify PIN
 *
 * @param PAN Personal Account Number (if internal, value is 0)
 * @param PANLen Length of PAN
 * @param minPIN Minimum PIN Length
 * @param maxPIN Maximum PIN Length
 * @param message LCD Message Up to 2 lines of text, each line 1-16, separated by 0x00
 * @param messageLen Length of 1st scenario LCD message, valid in 00h~21h (0~33).If no LCD message input, length is 00h, and display default msg “PLEASE ENTER PIN”
 * @param verify LCD Message Up to 2 lines of text, each line 1-16, separated by 0x00
 * @param verifyLen Length of 2nd Scenario LCD message.valid in 00h~21h (0~33).This field is present only when PAN and Key Type has Verify PIN.If no LCD message input, length is 00h, and display default msg “ ENTER PIN AGAIN”
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
pin_capturePinExt(IN int type, IN char * PAN, IN int PANLen, IN int minPIN, IN int maxPIN, IN char * message,
  IN int messageLen, IN char * verify, IN int verifyLen);

/**
 * Capture Numeric Input
 *
 *
 * @param timeout Timeout, in seconds. Value of 0 will use system timeout, if any
 * @param function
 *    - 0x00 = Plaintext Input
 *    - 0x01 = Masked Input
 *    - 0x02 = Delayed Masking Input
 *    - 0x10 = Plaintext Input + MSR Active
 *    - 0x11 = Masked Input + MSR Active
 *    - 0x12 = Delayed Masking Input + MSR Active
 * @param minLen Minimum input Length
 * @param maxLen Maximum input Length
 * @param line1 Line 1 of LCD Message - 16 chars max
 * @param line1Len Length of line1
 * @param line2 Line 2 of LCD Message - 16 chars max
 * @param line2Len Length of line2
 * @param signature Display message signed by Numeric Private Key using RSAPSS algorithm:
 *   1. Calculate 32 bytes Hash for ?�斤??Display Flag><Key Max Length>< Key Min Length><Plaintext Display Message>?�斤??
 *   2. Using RSAPSS algorithm calculate the Hash to be 256 bytes Raw Data
 *   3. Using Numeric Private Key to sign the Raw Data to be 256 bytes signature
 * @param signatureLen Length of signature
 *
 * @return RETURN_CODE:  Values can be parsed with errorCode.getErrorString()
 *
 */
int
pin_promptForNumericKeyWithSwipe(IN int timeout, IN BYTE function, IN int minLen, IN int maxLen, IN char * line1,
  IN int line1Len, IN char * line2, IN int line2Len, BYTE * signature,
  IN int signatureLen);

/**
 * Capture Numeric Input
 *
 *
 * @param timeout Timeout, in seconds. Value of 0 will use system timeout, if any
 * @param maskInput
 *     - 0 = Display numeric for numeric key on LCD
 *     - 1 = Display ?��*?�� for numeric key on LCD
 * @param minLen Minimum input Length
 * @param maxLen Maximum input Length
 * @param message Plaintext Display Message. - 16 chars max
 * @param messageLen Length of message
 * @param signature Display message signed by Numeric Private Key using RSAPSS algorithm:
 *    1. Calculate 32 bytes Hash for ?��<Display Flag><Key Max Length>< Key Min Length><Plaintext Display Message>?��
 *    2. Using RSAPSS algorithm calculate the Hash to be 256 bytes Raw Data
 *    3. Using Numeric Private Key to sign the Raw Data to be 256 bytes signature
 *  @param signatureLen Length of signature
 *
 * @return RETURN_CODE:  Values can be parsed with errorCode.getErrorString()
 *
 */
int
pin_promptForNumericKey(IN int timeout, IN int maskInput, IN int minLen, IN int maxLen, IN char * message,
  IN int messageLen, BYTE * signature, IN int signatureLen);

/**
 * Get PIN Input from Prompt
 *          Results returned to PIN Callback.  If successful function key capture, data is returned as
 *          IDTPINData.keyString.
 *
 *
 *          @param mask 0 = no masking, 1 = Display "*" for numeric key according to Pre-Cleartext and Post-Cleartext display
 *        @param preClearText   Range 0-6 Characters to mask at start of text if masking is on;
 *        @param postClearText  Range 0-6 Characters to mask at end of text if masking is on;
 *        @param minLen  Minimum number of digits required to input
 *        @param maxLen  Maximum number of digits allowed to be input
 *        @param lang  Valid values;
 *        "EN" is English display message
 *        "JP" is Japanese display message
 *        "ES" is Spanish display message
 *        "FR" is French display message
 *        "ZH" is Chinese display message
 *        "PT" is Portuguese display message
 *        @param promptID  Valid values:
 *        0x00: Enter Phone Number
 *        0x01: Enter IP Address
 *        0x02: Enter Subnet Mask
 *        0x03: Enter Default Gateway
 *        0x04: Enter Odometer Reading/Mileage
 *        0x05: Enter Employee ID
 *        0x06: Enter Password for Default Factory Setting
 *        0x07: Enter Email Address (Full keyboard)
 *        @param defaultResponse  Default String on input field
 *        @param defaultResponseLen  Length of defaultResponse
 *        @param timeout  Timeout, in seconds
 * @return RETURN_CODE:  Values can be parsed with errorCode.getErrorString()g
 *
 */
int
pin_inputFromPrompt(BYTE mask, BYTE preClearText, BYTE postClearText, int minLen, int maxLen, char * lang,
  BYTE promptID, char * defaultResponse, int defaultResponseLen, int timeout);

/**
 * Capture Amount
 *
 * @param timeout Timeout, in seconds. Value of 0 will use system timeout, if any
 * @param minLen Minimum input Length
 * @param maxLen Maximum input Length
 * @param message LCD Message
 * @param messageLen Length of message
 * @param signature Display message signed by Numeric Private Key using RSAPSS algorithm:
 *  1. Calculate 32 bytes Hash for Display Flag><Key Max Length>< Key Min Length><Plaintext Display Message>
 *  2. Using RSAPSS algorithm calculate the Hash to be 256 bytes Raw Data
 *  3. Using Numeric Private Key to sign the Raw Data to be 256 bytes signature
 * @param signatureLen Length of signature
 * @return RETURN_CODE:  Values can be parsed with errorCode.getErrorString()
 *
 */
int
pin_promptForAmount(IN int timeout, IN int minLen, IN int maxLen, IN char * message, IN int messageLen,
  BYTE * signature, IN int signatureLen);

/**
 * Get Pan
 *
 * prompt the user to manually enter a card PAN and Expiry Date (and optionally CSC) from the keypad and return it to the POS.
 * @param csc Request CSS
 *   @param expDate Request Expiration Date
 *   @param ADR Request Address
 *   @param ZIP Request Zip
 *   @param mod10CK Validate entered PAN passes MOD-10 checking before accepting
 *   @param timeout Number of seconds that the reader waits for the data entry session to complete, stored as a big-endian number. 0 = no timeout
 *   @param encPANOnly Output only encrypted PAN
 *
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString
 */
int
pin_getPanEntry(IN int csc, IN int expDate, IN int ADR, IN int ZIP, IN int mod10CK, IN int timeout, IN int encPANOnly);

/**
 * Save Prompt
 *
 * Saves a message prompt to L80 or L100 memory.
 *      @param promptNumber  Prompt number  (0-9)
 *      @param prompt Prompt string (up to 20 characters)
 *      @param promptLen length of prompt
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString
 *
 */
int
lcd_savePrompt(int promptNumber,
  char *           prompt,
  int              promptLen);

/**
 * Display Prompt on Line
 *
 * Displays a message prompt from L80 or L100 memory.
 *      @param promptNumber  Prompt number  (0-9)
 *      @param lineNumber Line number to display message prompt (1-4)
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString
 *
 */
int
lcd_displayPrompt(int promptNumber,
  int                 lineNumber);

/**
 * Display Message on Line
 *
 *      Displays a message on a display line.
 *        @param lineNumber  Line number to display message on  (1-4)
 *        @param message Message to display
 *        @param messageLen length of message
 * @return RETURN_CODE:  Values can be parsed with device_getResponseCodeString
 *
 */
int
lcd_displayMessage(int lineNumber,
  char *               message,
  int                  messageLen);

/**
 * Enable/Disable LCD Backlight
 * Trns on/off the LCD back lighting.
 * @param enable  TRUE = turn ON backlight, FALSE = turn OFF backlight
 * @return RETURN_CODE: Values can be parsed with device_getResponseCodeString
 *
 */
int
lcd_enableBacklight(int enable);

/**
 * Get Backlight Status
 *
 * Returns the status of the LCD back lighting.
 * @param enabled  1 = Backlight is ON, 0 = Backlight is OFF
 * @return RETURN_CODE: Values can be parsed with device_getResponseCodeString
 */
int
lcd_getBacklightStatus(int * enabled);

/**
 * Request CSR
 *  Requests 3 sets of public keys: encrypting Keys,
 *  signing/validating keys, signing/validating 3rd party apps
 *
 * @param csr RequestCSR structure to return the data
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
ws_requestCSR(OUT RequestCSR * csr);

/**
 * Load SSL Certificate
 *  Loads a SSL certificate
 *
 * @param name Certificate Name
 * @param nameLen Certificate Name Length
 * @param dataDER DER encoded certificate data
 * @param dataDERLen DER encoded certificate data length
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
ws_loadSSLCert(IN char * name,
  IN int                 nameLen,
  IN char *              dataDER,
  IN int                 dataDERLen);

/**
 * Revoke SSL Certificate
 *  Revokes a SSL Certificate by name
 *
 * @param name Name of certificate to revoke
 * @param nameLen Certificate Name Length
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
ws_revokeSSLCert(IN char * name,
  IN int                   nameLen);

/**
 * Delete SSL Certificate
 *  Deletes a SSL Certificate by name
 *
 * @param name Name of certificate to delete
 * @param nameLen Certificate Name Length
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
ws_deleteSSLCert(IN char * name,
  IN int                   nameLen);

/**
 * Get Certificate Chain Type
 *  Returns indicator for using test/production certificate chain
 *
 * @param type 0 = test certificate chain, 1 = production certificate chain
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
ws_getCertChainType(OUT int * type);

/**
 * Update Root Certificate
 *  Updates the root certificate
 *
 * @param name Certificate Name
 * @param nameLen Certificate Name Length
 * @param dataDER DER encoded certificate data
 * @param dataDERLen DER encoded certificate data length
 * @param signature Future Root CA signed (RSASSA PSS SHA256) by current Root CA
 * @param signature length
 *
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
ws_updateRootCertificate(IN char * name,
  IN int                           nameLen,
  IN char *                        dataDER,
  IN int                           dataDERLen,
  IN char *                        signature,
  IN int                           signatureLen);

/**
 * Start CTLS Transaction Request
 *
 * Authorizes the CTLS transaction for an ICC card
 *
 * The tags will be returned in the callback routine.
 *
 * @param amount Transaction amount value    (tag value 9F02) - SEE IMPORTANT NOTE BELOW
 * @param amtOther Other amount value, if any    (tag value 9F03) - SEE IMPORTANT NOTE BELOW
 * @param type Transaction type (tag value 9C).
 * @param timeout Timeout value in seconds.
 * @param tags Any other tags to be included in the request.  Passed as TLV stream.    Example, tag 9F0C with amount 0x000000000100 would be 0x9F0C06000000000100
 * If tags 9F02 (amount), 9F03 (other amount), or 9C (transaction type) are included, they will take priority over these values supplied as individual parameters to this method.
 *
 * @param tagsLen The length of tags data buffer.
 *
 * >>>>>IMPORTANT: parameters for amount and amtOther MUST BE PASSED AS A DOUBLE VALUE WITH DECIMAL POINT.  Example, do not pass 1, but instead pass 1.0 or 1.00. Otherwise, results will be unpredictable
 *
 *
 *
 * @return RETURN_CODE:    Values can be parsed with device_getIDGStatusCodeString()
 * Note: if auto poll is on, it will returm the error IDG_P2_STATUS_CODE_COMMAND_NOT_ALLOWED
 *
 * NOTE ON APPLEPAY VAS:
 * To enable ApplePay VAS, first a merchant record must be defined in one of the six available index positions (1-6) using device_setMerchantRecord, then container tag FFEE06
 * must be sent as part of the additional tags parameter of ctls_startTransaction.  Tag FFEE06 must contain tag 9F26 and 9F22, and can optionanally contain tags 9F2B and DF01.
 * Example FFEE06189F220201009F2604000000009F2B050100000000DF010101
 * 9F22 = two bytes = ApplePay Terminal Applicaiton Version Number.    Hard defined as 0100 for now. (required)
 * 9F26 = four bytes = ApplePay Terminal Capabilities Information (required)
 *  - Byte 1 = RFU
 *  - Byte 2 = Terminal Type
 *  - - Bit 8 = VAS Support    (1=on, 0 = off)
 *  - - Bit 7 = Touch ID Required  (1=on, 0 = off)
 *  - - Bit 6 = RFU
 *  - - Bit 5 = RFU
 *  - - Bit 1, 2, 3, 4
 *  - - - 0 = Payment Terminal
 *  - - - 1 = Transit Terminal
 *  - - - 2 = Access Terminal
 *  - - - 3 = Wireless Handoff Terminal
 *  - - - 4 = App Handoff Terminal
 *  - - - 15 = Other Terminal
 *  - Byte 3 = RFU
 *  - Byte 4 = Terminal Mode
 *  - - 0 = ApplePay VAS OR ApplePay
 *  - - 1 = ApplePay VAS AND ApplePay
 *  - - 2 = ApplePay VAS ONLY
 *  - - 3 = ApplePay ONLY
 *  9F2B = 5 bytes = ApplePay VAS Filter.  Each byte filters for
 *         that specific merchant index  (optional)
 *  DF01 = 1 byte = ApplePay VAS Protocol.  (optional)
 *  - - Bit 1 : 1 = URL VAS, 0 = Full VAS
 *  - - Bit 2 : 1 = VAS Beeps, 0 = No VAS Beeps
 *  - - Bit 3 : 1 = Silent Comm Error, 2 = EMEA Comm Error
 *  - - Bit 4-8 : RFU
 */
int
ctls_startTransaction(IN double amount,
  IN double                     amtOther,
  IN int                        type,
  IN const int                  _timeout,
  IN BYTE *                     tags,
  IN int                        tagsLen);

/**
 * Start CTLS Transaction Request
 *
 * Authorizes the CTLS transaction for an ICC card
 *
 * The tags will be returned in the callback routine.
 *
 * @param timeout Timeout value in seconds.
 * @param tags The tags to be included in the request.  Passed as TLV stream.
 *    Example, tag 9F02 with amount 0x000000000100 would be 0x9F0206000000000100
 *
 *
 * @param tagsLen The length of tags data buffer.
 *
 * >>>>>IMPORTANT: parameters for amount and amtOther MUST BE PASSED AS A
 * DOUBLE VALUE WITH DECIMAL POINT.  Example, do not pass 1, but instead
 * pass 1.0 or 1.00. Otherwise, results will be unpredictable
 *
 *
 *
 * @return RETURN_CODE: Values can be parsed with
 * device_getIDGStatusCodeString() Note: if auto poll is on, it will
 * returm the error IDG_P2_STATUS_CODE_COMMAND_NOT_ALLOWED
 *
 * NOTE ON APPLEPAY VAS:
 * To enable ApplePay VAS, first a merchant record must be defined in
 * one of the six available index positions (1-6) using
 * device_setMerchantRecord, then container tag FFEE06 must be sent as
 * part of the additional tags parameter of ctls_startTransaction.
 * Tag FFEE06 must contain tag 9F26 and 9F22, and can optionanally
 * contain tags 9F2B and DF01.
 * Example FFEE06189F220201009F2604000000009F2B050100000000DF010101
 * 9F22 = two bytes = ApplePay Terminal Applicaiton Version Number.
 *        Hard defined as 0100 for now. (required)
 * 9F26 = four bytes = ApplePay Terminal Capabilities Information (required)
 *  - Byte 1 = RFU
 *  - Byte 2 = Terminal Type
 *  - - Bit 8 = VAS Support    (1=on, 0 = off)
 *  - - Bit 7 = Touch ID Required  (1=on, 0 = off)
 *  - - Bit 6 = RFU
 *  - - Bit 5 = RFU
 *  - - Bit 1, 2, 3, 4
 *  - - - 0 = Payment Terminal
 *  - - - 1 = Transit Terminal
 *  - - - 2 = Access Terminal
 *  - - - 3 = Wireless Handoff Terminal
 *  - - - 4 = App Handoff Terminal
 *  - - - 15 = Other Terminal
 *  - Byte 3 = RFU
 *  - Byte 4 = Terminal Mode
 *  - - 0 = ApplePay VAS OR ApplePay
 *  - - 1 = ApplePay VAS AND ApplePay
 *  - - 2 = ApplePay VAS ONLY
 *  - - 3 = ApplePay ONLY
 *  9F2B = 5 bytes = ApplePay VAS Filter.  Each byte filters for that specific
 *         merchant index  (optional)
 *  DF01 = 1 byte = ApplePay VAS Protocol.  (optional)
 *  - - Bit 1 : 1 = URL VAS, 0 = Full VAS
 *  - - Bit 2 : 1 = VAS Beeps, 0 = No VAS Beeps
 *  - - Bit 3 : 1 = Silent Comm Error, 2 = EMEA Comm Error
 *  - - Bit 4-8 : RFU
 */
int
ctls_activateTransaction(IN const int _timeout,
  IN BYTE *                           tags,
  IN int                              tagsLen);

/**
 * Cancel EMV Transaction
 *
 * Cancels the currently executing EMV transaction.
 *
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
ctls_cancelTransaction();

/**
 * Retrieve Application Data by AID
 *
 * Retrieves the Application Data as specified by the AID name passed
 * as a parameter.
 *
 * @param AID Name of ApplicationID. Must be between 5 and 16 bytes
 * @param AIDLen the length of AID data buffer.
 * @param tlv  The TLV elements of the requested AID
 * @param tlvLen the length of tlv data buffer.
 *
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
ctls_retrieveApplicationData(IN BYTE * AID,
  IN int                               AIDLen,
  OUT BYTE *                           tlv,
  IN_OUT int *                         tlvLen);

/**
 * Set Application Data by AID
 *
 * Sets the Application Data for CTLS as specified by TLV data
 *
 * @param tlv  Application data in TLV format
 *    The first tag of the TLV data must be the group number (FFE4).
 *    The second tag of the TLV data must be the AID (9F06)
 *
 *    Example valid TLV, for Group #2, AID a0000000035010:
 *    "ffe401029f0607a0000000051010ffe10101ffe50110ffe30114ffe20106"
 * @param tlvLen the length of tlv data buffer
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
ctls_setApplicationData(IN BYTE * tlv,
  IN int                          tlvLen);

/**
 * Remove Application Data by AID
 * Removes the Application Data for CTLS as specified by the AID name
 * passed as a parameter
 *
 * @param AID Name of ApplicationID Must be between 5 and 16 bytes
 *
 * @param AIDLen the length of AID data buffer
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
ctls_removeApplicationData(IN BYTE * AID,
  IN int                             AIDLen);

/**
 * Remove All Application Data
 *
 * Removes all the Application Data
 *
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
ctls_removeAllApplicationData();

/**
 * Retrieve AID list
 *
 * Returns all the AID names installed on the terminal for CTLS. .
 *
 * @param AIDList  array of AID name byte arrays
 * @param AIDListLen  the length of AIDList array buffer
 *
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
ctls_retrieveAIDList(OUT BYTE * AIDList,
  IN_OUT int *                  AIDListLen);

/**
 * Retrieve Terminal Data
 *
 * Retrieves the Terminal Data for CTLS. This is configuration group 0
 *  (Tag FFEE - > FFEE0100).  The terminal data can also be retrieved
 *  by ctls_getConfigurationGroup(0).
 *
 * @param tlv Response returned as a TLV
 * @param tlvLen the length of tlv data buffer
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
ctls_retrieveTerminalData(OUT BYTE * tlv,
  IN_OUT int *                       tlvLen);

/**
 * Set Terminal Data
 *
 * Sets the Terminal Data for CTLS as specified by the TLV.  The first
 *  TLV must be Configuration Group Number (Tag FFE4).  The terminal
 *  global data is group 0, so the first TLV would be FFE40100.  Other
 *  groups can be defined using this method (1 or greater), and those
 *  can be retrieved with ctls_getConfigurationGroup(int group), and
 *  deleted with ctls_removeConfigurationGroup(int group).  You cannot
 *  delete group 0
 *
 * @param tlv TerminalData configuration file
 * @param tlvLen the length of tlv data buffer
 *
 * @retval RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
ctls_setTerminalData(IN BYTE * tlv,
  IN int                       tlvLen);

/**
 * Retrieve Certificate Authority Public Key
 *
 * Retrieves the CAPK for CTLS as specified by the RID/Index passed as
 * a parameter.
 *
 * @param capk 6 bytes CAPK = 5 bytes RID + 1 byte Index
 * @param capkLen the length of capk data buffer
 * @param key Response returned as a CAKey format:
 *  [5 bytes RID][1 byte Index][1 byte Hash Algorithm][1 byte Encryption Algorithm]
 *  [20 bytes HashValue][4 bytes Public Key Exponent][2 bytes Modulus Length][Variable bytes Modulus]
 *  Where:
 *   - Hash Algorithm: The only algorithm supported is SHA-1.The value is set to 0x01
 *   - Encryption Algorithm: The encryption algorithm in which this key is used. Currently support only one type: RSA. The value is set to 0x01.
 *   - HashValue: Which is calculated using SHA-1 over the following fields: RID & Index & Modulus & Exponent
 *   - Public Key Exponent: Actually, the real length of the exponent is either one byte or 3 bytes. It can have two values: 3 (Format is 0x00 00 00 03), or  65537 (Format is 0x00 01 00 01)
 *   - Modulus Length: LenL LenH Indicated the length of the next field.
 *   - Modulus: This is the modulus field of the public key. Its length is specified in the field above.
 * @param keyLen the length of key data buffer
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
ctls_retrieveCAPK(IN BYTE * capk,
  IN int                    capkLen,
  OUT BYTE *                key,
  IN_OUT int *              keyLen);

/**
 * Set Certificate Authority Public Key
 *
 * Sets the CAPK as specified by the CAKey structure
 *
 * @param capk CAKey format:
 *  [5 bytes RID][1 byte Index][1 byte Hash Algorithm][1 byte Encryption Algorithm][20 bytes HashValue][4 bytes Public Key Exponent][2 bytes Modulus Length][Variable bytes Modulus]
 *  Where:
 *   - Hash Algorithm: The only algorithm supported is SHA-1.The value is set to 0x01
 *   - Encryption Algorithm: The encryption algorithm in which this key is used. Currently support only one type: RSA. The value is set to 0x01.
 *   - HashValue: Which is calculated using SHA-1 over the following fields: RID & Index & Modulus & Exponent
 *   - Public Key Exponent: Actually, the real length of the exponent is either one byte or 3 bytes. It can have two values: 3 (Format is 0x00 00 00 03), or  65537 (Format is 0x00 01 00 01)
 *   - Modulus Length: LenL LenH Indicated the length of the next field.
 *   - Modulus: This is the modulus field of the public key. Its length is specified in the field above.
 * @param capkLen the length of capk data buffer
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
ctls_setCAPK(IN BYTE * capk,
  IN int               capkLen);

/**
 * Remove Certificate Authority Public Key
 *
 * Removes the CAPK as specified by the RID/Index
 *
 * @param capk 6 byte CAPK =  5 bytes RID + 1 byte INDEX
 * @param capkLen the length of capk data buffer
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
ctls_removeCAPK(IN BYTE * capk,
  IN int                  capkLen);

/**
 * Remove All Certificate Authority Public Key
 *
 * Removes all the CAPK
 *
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
ctls_removeAllCAPK();

/**
 * Retrieve the Certificate Authority Public Key list
 *
 * Returns all the CAPK RID and Index installed on the terminal.
 *
 * @param keys [key1][key2]...[keyn], each key 6 bytes where
 *  key = 5 bytes RID + 1 byte index
 * @param keysLen the length of keys data buffer
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
ctls_retrieveCAPKList(OUT BYTE * keys,
  IN_OUT int *                   keysLen);

/**
 * Set Configuration Group
 *
 * Sets the Configuration Group for CTLS as specified by the TLV data
 *
 * @param tlv  Configuration Group Data in TLV format
 *    The first tag of the TLV data must be the group number (FFE4 or DFEE2D).
 *    A second tag must exist
 * @param tlvLen the length of tlv data buffer
 *
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
ctls_setConfigurationGroup(IN BYTE * tlv,
  IN int                             tlvLen);

/**
 * Get Configuration Group
 *
 * Retrieves the Configuration for the specified Group.
 *
 * @param group Configuration Group
 * @param tlv return data
 * @param tlvLen the length of tlv data buffer
 *
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
ctls_getConfigurationGroup(IN int group,
  OUT BYTE *                      tlv,
  OUT int *                       tlvLen);

/**
 * Retrieve All Configuration Groups
 *
 * Returns all the Configuration Groups installed on the terminal for CTLS
 *
 * @param tlv  The TLV elements data
 * @param tlvLen the length of tlv data buffer.
 *
 * @return RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
ctls_getAllConfigurationGroups(OUT BYTE * tlv,
  IN_OUT int *                            tlvLen);

/**
 * Remove Configuration Group
 *
 * Removes the Configuration as specified by the Group.  Must not by group 0
 *
 * @param group Configuration Group
 *
 * @retval RETURN_CODE: Values can be parsed with device_getIDGStatusCodeString()
 */
int
ctls_removeConfigurationGroup(int group);

/**
 * Display Online Authorization Result
 *  Use this command to display the status of an online authorization request
 *  on the reader's display (OK or NOT OK).
 *  Use this command after the reader sends an online request to the issuer.
 *  The SDK timeout of the command is set to 7 seconds.
 * @param statusCode 1 = OK, 0 = NOT OK, 2 = ARC response 89 for Interac
 * @param TLV Optional TLV for AOSA
 * @param TLVLen TLV Length
 * @return RETURN_CODE:  Values can be parsed with device_getIDGStatusCodeString()
 */
int
ctls_displayOnlineAuthResult(IN int statusCode,
  IN BYTE *                         TLV,
  IN int                            TLVLen);

/**
 * Parse the PIN block data from the buffer into IDTPINData structure
 * @param resData PIN card data buffer
 * @param resLen the length of resData
 * @param cardData the parser result with IDTPINData structure
 */
void
parsePINBlockData(IN BYTE * resData,
  IN int                    resLen,
  IN_OUT IDTPINData *       cardData);

/**
 * Parse the PIN data from the buffer into IDTPINData structure
 * @param resData PIN card data buffer
 * @param resLen the length of resData
 * @param cardData the parser result with IDTPINData structure
 */
void
parsePINData(IN BYTE * resData,
  IN int               resLen,
  IN_OUT IDTPINData *  cardData);


# ifdef __cplusplus
}
# endif


#endif // ifndef __LIBIDT_DEVICE_H___

/*! \file libIDT_Device.h
 * \brief Windows C++ API.
 *
 * Windows C++ Global API methods.
 */

/*! \def IN
 * INPUT parameter.
 */

/*! \def OUT
 * OUTPUT parameter.
 */

/*! \def IN_OUT
 * INPUT / OUTPUT PARAMETER.
 */

/*! \def _DATA_BUF_LEN
 * DATA BUFFER LENGTH
 */
