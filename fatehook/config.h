/* SoftwareGuy/Coburn's attempt at FateGO Arcade Hook/IO for SegaTools. 
 * This code is licensed under MIT license; don't be a thief.
 */

#pragma once

#include <stdbool.h>
#include <stddef.h>

#include "amex/amex.h"
#include "board/sg-reader.h"

// Probably not required.
// #include "hooklib/dvd.h"

// ...

#include "platform/platform.h"

struct fatego_hook_config {
    struct platform_config platform;
    struct amex_config amex;
    struct aime_config aime;
    struct gfx_config gfx;
	// struct dvd_config dvd;
    // struct fatego_dll_config dll;
    // struct zinput_config zinput;
};

void fatego_hook_config_load(
        struct fatego_hook_config *cfg,
        const wchar_t *filename);