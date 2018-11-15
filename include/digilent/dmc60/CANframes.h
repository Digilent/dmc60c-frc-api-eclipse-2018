#pragma once
#include <stdint.h>

/* Define CAN Message ID's supported by Digilent devices.
*/
const uint32_t msgidEnum = 0x00000240; // API = 0x009
const uint32_t msgidEnumSnd	= 0x0206F000; // API = 0x3C0
const uint32_t msgidEnumResp = 0x0206F000; // API = 0x3C0
const uint32_t msgidVendorCmd = 0x0206FC00; // API = 0x3F0
const uint32_t msgidVendorDout = 0x0206FC40; // API = 0x3F1
const uint32_t msgidVendorDin = 0x0206FC80; // API = 0x3F2
const uint32_t msgidVendorSts = 0x0206FCC0; // API = 0x3F3
const uint32_t msgidParamReq = 0x02061800; //
const uint32_t msgidParamResp = 0x02061840; //
const uint32_t msgidParamSet = 0x02061880; //
const uint32_t msgidStsGeneral = 0x02061400; //
const uint32_t msgidStsEncoder = 0x02061480; //
const uint32_t msgidStsAnalog = 0x020614C0; //

const uint32_t msgidControl0 = 0x02060000; //

const uint32_t msgidXtd = 0x20000000; //

/* Define a data structure that can be used to keep track
** of information about enumerated Digilent Motor Controllers.
*/
#define cchManNameMax      28
#define cchProdNameMax     28
#define cchManDateMax      20
#define cchHardwareVerMax  8
#define cchSNMax           12
#define cchDevNameMax      64


/* Define ID's used to identify the different descriptor fields.
*/
const uint8_t idfldNone           =0;
const uint8_t idfldSzDevName      =1;
const uint8_t idfldSzManName      =2;
const uint8_t idfldSzProdName     =3;
const uint8_t idfldSzManDate      =4;
const uint8_t idfldSzHardWareVer  =5;
const uint8_t idfldSzSN           =6;

/* Define CAN Bus error codes that are returned in status packets.
*/
const uint16_t cercNoError             =0x00;
const uint16_t cercNotSupported        =0x01;
const uint16_t cercBadParameter        =0x02;
const uint16_t cercDataRcvMore         =0x03;
const uint16_t cercInBootloader        =0x04;
const uint16_t cercCrcMismatch         =0x05;
const uint16_t cercFlashWriteFailed    =0x06;
const uint16_t cercAckReset            =0x07;


/* Define masks that can be used to parse the fields of fsLimitOverride.
*/
const uint8_t mskFwdLimitDisableOvrd  =0b001;
const uint8_t mskRevLimitDisableOvrd  =0b010;
const uint8_t mskFwdRevLimitOverride  =0b100;

const uint8_t bnFwdLimitDisableOvrd   =0;
const uint8_t bnRevLimitDisableOvrd   =1;
const uint8_t bnFwdRevLimitOverride   =2;

const uint32_t pdidDMC60 =0x60200103;

/* Mask for the DMC60 Device Number
*/
const uint32_t mskCanDevNum =0x0000003F;

const uint32_t cbCansts0	=8;


/**
\struct DMCInfo_t
\brief Contains Manufacturer information
\var DMCInfo_t::sessid
Device Session ID
\var DMCInfo_t::devnum
Device Number
\var DMCInfo_t::pdid
Product ID
\var DMCInfo_t::imgtyp
Current Firmware Image Type
\var DMCInfo_t::fwverApp
Application Firmware Version
\var DMCInfo_t::fwverBoot
Bootloader Firmware Version
\var DMCInfo_t::szDevName
Device Name
\var DMCInfo_t::szManName
Manufacturer Name
\var DMCInfo_t::szProdName
Product Name
\var DMCInfo_t::szManDate
Manufacture Date
\var DMCInfo_t::szHardwareVer
Hardware Revision
\var DMCInfo_t::szSN
Serial Number
*/
typedef struct DMCInfo_t{
	unsigned short	sessid;    // Device Session ID
	unsigned char		devnum;    // Device Number
	unsigned int	pdid;      // Product ID
	unsigned char		imgtyp;    // Current Firmware Image Type
	unsigned short	fwverApp;  // Application Firmware Version
	unsigned short	fwverBoot; // Bootloader Firmware Version
	char		szDevName[cchDevNameMax + 1];         // Device Name
	char		szManName[cchManNameMax + 1];         // Manufacturer Name
	char		szProdName[cchProdNameMax + 1];       // Product Name
	char		szManDate[cchManDateMax + 1];         // Manufacture Date
	char		szHardwareVer[cchHardwareVerMax + 1]; // Hardware Revision
	char		szSN[cchSNMax + 1];                   // Serial Number
} DMCInfo_t;

#pragma pack(push, 1)

typedef struct {
	unsigned char   modeSelect : 4;
	unsigned char   fOverrideBC : 1;
	unsigned char   fBrakeCoast : 1;
	unsigned char   pidsltSelect : 1;
	unsigned char   fRevFeedbackSensor : 1;
	unsigned char   fRevMotor : 1;
	unsigned char	fsLimitOverride : 3;
	unsigned char   rsv1 : 4;
	unsigned char   rsv2 : 8;
	unsigned char   trgtH : 8;
	unsigned char   trgtL : 8;
	unsigned char   trgtM : 8;
	unsigned short        vltgRampSet;
} CANCTRL0;

typedef struct {
	signed short	currentDuty : 16;     // Signed 16bit int
	unsigned char	fFwdLimitPin : 1;	//1 when forward limit pin is high
	unsigned char	fFwdLimitHit : 1;	//1 when forward limit is active
	unsigned char	fFwdLimitDisabled : 1;	//1 when forward limit is disabled
	unsigned char	fFwdLimitNormalClosed : 1;	//1 when forward limit switch is normally closed
	unsigned char	fRevLimitPin : 1;	//1 when reverse limit pin is high
	unsigned char	fRevLimitHit : 1;	//1 when reverse limit is active
	unsigned char	fRevLimitDisabled : 1;	//1 when reverse limit is disabled
	unsigned char	fRevLimitNormalClosed : 1;	//1 when reverse limit switch is normally closed
	unsigned char	fFwdRevLimitOverride: 1;	//1 when limit switch enable state is being overridden by the control frame
	unsigned char	fFwdLimitDisableOverride : 1;	//1 when forward limit switch is disabled by the control frame
	unsigned char	fRevLimitDisableOverride : 1;	//1 when reverse limit switch is disabled by the control frame
	unsigned char	fSoftFwdLimitHit : 1;	//1 when forward soft limit is active
	unsigned char	fSoftFwdLimitEnabled : 1;	//1 when soft forward limit is enabled
	unsigned char	fSoftRevLimitHit : 1;	//1 when reverse soft limit is active
	unsigned char	fSoftRevLimitEnabled : 1;	//1 when soft reverse limit is enabled
	unsigned char	fCurrentLimitActive : 1;	//1 when current limit is active
	unsigned char	fOverTempFault : 1;	//1 if there is an over temp fault
	unsigned char	fUndervoltageFault : 1;	//1 if there is an under voltage fault
	unsigned char	fGateDriverFault : 1;	//1 if there is a gate driver fault
	unsigned char	modeSelect : 4;	//Control mode currently active
	unsigned char	fDivErrby256 : 1;	//1 if the returned closed loop error has been divided by 256
	unsigned char	ClosedLoopErrorL : 8;	//Closed loop error, meaning is specific to the control mode specified by mode select
	unsigned char	ClosedLoopErrorM : 8;
	unsigned char	ClosedLoopErrorH : 8;
} STSGENERAL;

typedef struct {
	unsigned    poscntH : 8;
	unsigned    poscntM : 8;
	unsigned    poscntL : 8;
	unsigned    velcntH : 8;
	unsigned    velcntL : 8;
	unsigned    rsv0 : 8;
	unsigned    rsv1 : 8;
	unsigned    fDivPosBy8 : 1;
	unsigned    fDivVelBy4 : 1;
	unsigned    rsv2 : 6;
} STSENCODER;

typedef struct {
	signed 	vltgAnalogIn : 16;
	signed	crntOutput : 16;
	signed	tmpAmbient : 16;
	signed	vltgVbus	: 16;
} STSANALOG;


typedef struct {
	unsigned short    sessid;
	unsigned long   pdid;
} ENUMRSP0;

typedef struct {
	unsigned short    sessid;
	union {
		struct {
			unsigned short imgtyp : 2;
			unsigned short rsv : 14;
		};
		unsigned short flgs;
	};
	unsigned short    fwverApp;
	unsigned short    fwverBoot;
} ENUMRSP1;

typedef struct {
	union {
		struct {
			unsigned short imgtyp : 2;
			unsigned short rsv : 14;
		};
		unsigned short flgs;
	};
	unsigned short    fwverApp;
	unsigned short    fwverBoot;
} FWVERRSP;

typedef struct {
	unsigned short    sessid;
	unsigned short    cmd;
	unsigned short    PARAM1;
	unsigned short    PARAM2;
} VENDORCMD;

typedef struct {
	unsigned short    cerc;
	unsigned short    cb;
} VENDORSTS;

typedef struct {
	unsigned short	sessid;
	unsigned char	param;
}PARAMREQ;

typedef struct {
	unsigned char    param;
	unsigned long   value;
	unsigned char    perc;
} PARAMRESP;

typedef struct {
	unsigned short	sessid;
	unsigned char	param;
	union {
		struct {
			unsigned char valueL;
			unsigned char valueML;
			unsigned char valueMH;
			unsigned char valueH;
		};
		unsigned long value;
	};
} PARAMSET;
#pragma pack(pop)


