#pragma once

#include <stdint.h>
/* Define Vendor Commands.
*/
const uint8_t vcmdNoCommand           =0x00;

const uint8_t vcmdSetDevNumber        =0x01;
const uint8_t vcmdSetDevName          =0x02;
const uint8_t vcmdSetManName          =0x03;
const uint8_t vcmdSetProdName         =0x04;
const uint8_t vcmdSetManDate          =0x05;
const uint8_t vcmdSetHardwareVer      =0x06;
const uint8_t vcmdSetSN               =0x07;

const uint8_t vcmdFlashLEDs			  =0x50;

const uint8_t vcmdGetDescriptors      =0x60;
const uint8_t vcmdGetFwver            =0x61;
const uint8_t vcmdGetFlashSeqnum      =0x62;

const uint8_t vcmdEnterBootloader     =0xF0;
const uint8_t vcmdSoftReset           =0xF1;
const uint8_t vcmdEraseWriteFlashPage =0xF2;

/* Command buffer size
*/
const uint32_t cmdBufferSize =20;

