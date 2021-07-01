/* SoftwareGuy/Coburn's attempt at FateGO Arcade Hook/IO for SegaTools. 
 * This code is licensed under MIT license; don't be a thief.
 */

#include <windows.h>

#include <assert.h>
#include <limits.h>
#include <stdint.h>

#include "fateio/fateio.h"

#include "util/dprintf.h"

// TODO: Better implementation.

HRESULT fatego_io_init(void)
{
    dprintf("FateIO Hooks initialized!\n");
    return S_OK;
}

HRESULT fatego_io_poll(void)
{
	// Stubbed. I have no idea what to put here.
	return S_OK;
}