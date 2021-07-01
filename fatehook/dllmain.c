/* SoftwareGuy/Coburn's attempt at FateGO Arcade Hook/IO for SegaTools. 
 * This code is licensed under MIT license; don't be a thief.
 */
#include <windows.h>

#include <stddef.h>
#include <stdlib.h>

#include "board/sg-reader.h"
#include "board/io4.h"
#include "board/vfd.h"

#include "hook/process.h"

#include "hooklib/gfx.h"
#include "hooklib/serial.h"
#include "hooklib/spike.h"

#include "fatehook/config.h"
#include "fateio/fateio.h"

// IO4 likely not needed?

#include "platform/platform.h"

#include "util/dprintf.h"
#include "MinHook.h"

static HMODULE fatego_hook_mod;
static process_entry_t fatego_startup;
static struct fatego_hook_config fatego_hook_cfg;

static int AIME_READER_PORT = 3;

static DWORD CALLBACK fatego_pre_startup(void) {
	HRESULT hr;
	
	dprintf("-- Begin fatego_pre_startup --\n");
	dprintf("FateHook has arrived!\n");
	dprintf("This is very experimental hackery and will likely catch fire.\n");	
	
	// Load configuration.
	fatego_hook_config_load(&fatego_hook_cfg, L".\\segatools.ini");
	
	// Hook APIs.
	serial_hook_init();
	
	// TODO: Control hook init. That'll come later if ever.
	
	// Emulation of control hooks would go here...
	// And here...
	
	hr = platform_hook_init(&fatego_hook_cfg.platform, 
            "SDEJ", // SDEJ: Fate Grand Order Arcade (ALLS UX)
            "ACA0", /* Check this - it's an ALLS game. */
            fatego_hook_mod);
	
	if(FAILED(hr)) {
		dprintf("Configuration file load failure.\n");
		return hr;
	}
	
	// I dunno what VFD is.
	/*
	hr = vfd_hook_init(4);

	if(FAILED(hr)) {
		dprintf("vfd hook init failure.\n");
		return hr;
	}
	*/
	
	// AIME and other payment card reader initialization
	hr = sg_reader_hook_init(&fatego_hook_cfg.aime, AIME_READER_PORT, fatego_hook_mod);
	
	if(FAILED(hr)) {
		dprintf("sg reader/aime hook init failure.\n");
		return hr;
	}
	
	// Kickstart debug helpers.
	spike_hook_init(L".\\segatools.ini");
	
	// Done?
	dprintf("--- End fatego_pre_startup ---\n");
	dprintf("Handing control back to the game.\n");
	
	return fatego_startup();
}

BOOL WINAPI DllMain(HMODULE mod, DWORD cause, void *ctx)
{
    HRESULT hr;

    if (cause != DLL_PROCESS_ATTACH) {
        return TRUE;
    }

    fatego_hook_mod = mod;

    hr = process_hijack_startup(fatego_pre_startup, &fatego_startup);

    if (!SUCCEEDED(hr)) {
        dprintf("Failed to hijack process startup: %x\n", (int) hr);
    }

    return SUCCEEDED(hr);
}