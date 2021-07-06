/* SoftwareGuy/Coburn's attempt at FateGO Arcade Hook/IO for SegaTools. 
 * This code is licensed under MIT license; don't be a thief.
 */
#include <windows.h>

#include <stddef.h>
#include <stdlib.h>

// SegaTool includes, board, hook + hooks, fatehook and fate io, then platform.
#include "board/sg-reader.h"
#include "board/io4.h"
#include "board/vfd.h"

#include "hook/process.h"

#include "hooklib/gfx.h"
#include "hooklib/dvd.h"
#include "hooklib/serial.h"
#include "hooklib/spike.h"

#include "fatehook/config.h"
#include "fateio/fateio.h"

#include "platform/platform.h"
#include "util/dprintf.h"

// No idea.
// #include "MinHook.h"

static HMODULE fatego_hook_mod;
static process_entry_t fatego_startup;
static struct fatego_hook_config fatego_hook_cfg;

// Define some port numbers here that will help us later on.
// This saves us having to modify the code too deeply.
static int AIME_READER_PORT = 3;
static int VFD_COMM_PORT = 4;

// IO4 Stuffs
// Stubbed; this will require some figuring out. Help is welcome.
static HRESULT fate_io4_poll(void *ctx, struct io4_state *state) {
	// Just return for now.
	return S_OK;
};

static const struct io4_ops fate_io4_ops = {
    .poll = fate_io4_poll,
};
// End IO4 Stuffs

static DWORD CALLBACK fatego_pre_startup(void) {
	HRESULT hr;
	
	dprintf("-- Begin fatego_pre_startup --\n");
	dprintf("FateHook has arrived!\n");
	dprintf("This is very experimental hackery and will likely catch fire.\n");	
	
	// Load configuration.
	fatego_hook_config_load(&fatego_hook_cfg, L".\\segatools.ini");
	
	// Hook APIs.
	// DVD Hook is important because otherwise you will get an error
	// from the game if it detects a CD/DVD drive attached to your device.
	// Something something DVD Drive still attached.
	
	serial_hook_init();
	dvd_hook_init(&fatego_hook_cfg.dvd, fatego_hook_mod);
    gfx_hook_init(&fatego_hook_cfg.gfx, fatego_hook_mod);

	// Emulation of the ALLS UX system unit platform.
	hr = platform_hook_init(&fatego_hook_cfg.platform, 
            "SDEJ", // SDEJ: Fate Grand Order Arcade (ALLS UX)
            "ACA1", // ALLS UX Generation 1. ACA0 WILL NOT WORK.
            fatego_hook_mod);
	
	if(FAILED(hr)) {
		dprintf("Configuration file load failure.\n");
		return hr;
	}
	
	// VFD apparently is some type of card system?
	// Hooking this apparently makes the game say
	// CARD SYSTEM: OK on self-test.
	// Apparently on COM1 on a real arcade unit?
	hr = vfd_hook_init(VFD_COMM_PORT);

	if(FAILED(hr)) {
		dprintf("VFD Hook Initialization failure.\n");
		return hr;
	}	
	
	// AIME and other payment card reader initialization
	hr = sg_reader_hook_init(&fatego_hook_cfg.aime, AIME_READER_PORT, fatego_hook_mod);
	
	if(FAILED(hr)) {
		dprintf("SG Reader/Aime Hook Initialization failed.\n");
		return hr;
	}
	
	// IO4 Board Hook Initialization...?
	// Note: This might not be the right one to use, but this is OK for
	// an attempt to see if it'll work.
	hr = io4_hook_init(&fate_io4_ops, fatego_hook_mod);
	
	if(FAILED(hr)) {
		dprintf("IO4 Hook Initialization failed.");
		return hr;
	}
	
	// Kickstart debug helpers.
	spike_hook_init(L".\\segatools.ini");
	
	// Done?
	dprintf("--- End fatego_pre_startup ---\n");
	dprintf("Handing control back to the game.\n");
	
	return fatego_startup();
}

// Definition of the DLL hook file itself.
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