/* SoftwareGuy/Coburn's attempt at FateGO Arcade Hook/IO for SegaTools. 
 * This code is licensed under MIT license; don't be a thief.
 */

#pragma once

#include <windows.h>
#include <stdint.h>

// Operator buttons.
enum {
	fatego_IO_OPBTN_TEST = 0x01,
	fatego_IO_OPBTN_SERVICE = 0x02,
};

HRESULT fatego_io_init(void);

HRESULT fatego_io_poll(void);