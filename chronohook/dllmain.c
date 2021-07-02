/* SoftwareGuy (Coburn)'s attempt at Chrono Regalia Hook for SegaTools. 
 * This code is licensed under MIT license; don't be a thief.
 */
#include <windows.h>

#include <stddef.h>
#include <stdlib.h>

// Segatools Libraries
#include "platform/platform.h"

#include "board/sg-reader.h"
#include "board/vfd.h"

#include "hook/process.h"

#include "hooklib/gfx.h"
#include "hooklib/serial.h"
#include "hooklib/spike.h"


// Statics

static HMODULE chrono_hook_mod;
static process_entry_t chrono_startup;
static struct chrono_hook_config chrono_hook_cfg;
static int AIME_READER_PORT = 3;

static DWORD CALLBACK chrono_pre_startup(void) {
	HRESULT hr;
	
	dprintf("-- Begin chrono_pre_startup --\n");
	dprintf("ChronoHook has arrived!\n");
	dprintf("This is very experimental hackery and will likely catch fire.\n");	
	
	// Load configuration.
	chrono_hook_config_load(&chrono_hook_cfg, L".\\segatools.ini");
	
	// Hook APIs.
	serial_hook_init();
	
	hr = platform_hook_init(&chrono_hook_cfg.platform, 
		"SDEC", // SDEC: Chrono Regalia
		"ACA0", // ALLS UX
		chrono_hook_mod);
	
	if(FAILED(hr)) {
		dprintf("Configuration file load failure.\n");
		return hr;
	}
	
	// AIME and other payment card reader initialization
	hr = sg_reader_hook_init(&fatego_hook_cfg.aime, AIME_READER_PORT, fatego_hook_mod);
	
	if(FAILED(hr)) {
		dprintf("sg reader/aime hook init failure.\n");
		return hr;
	}
	
	// Kickstart debug helpers.
	spike_hook_init(L".\\segatools.ini");
	
	// Done?
	dprintf("--- End chrono_pre_startup ---\n");
	dprintf("Handing control back to the game.\n");
	
	return chrono_startup();
}

BOOL WINAPI DllMain(HMODULE mod, DWORD cause, void *ctx)
{
    HRESULT hr;

    if (cause != DLL_PROCESS_ATTACH) {
        return TRUE;
    }

    fatego_hook_mod = mod;

    hr = process_hijack_startup(chrono_pre_startup, &chrono_pre_startup);

    if (!SUCCEEDED(hr)) {
        dprintf("Failed to hijack process startup: %x\n", (int) hr);
    }

    return SUCCEEDED(hr);
}