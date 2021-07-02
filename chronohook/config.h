/* SoftwareGuy/Coburn's attempt at Chrono Regalia Hook for SegaTools.
 * This code is licensed under MIT license; don't be a thief.
 */

#pragma once

#include <stdbool.h>
#include <stddef.h>

#include "amex/amex.h"
#include "board/sg-reader.h"

// ...
#include "platform/platform.h"

struct chrono_hook_config {
    struct platform_config platform;
    struct amex_config amex;
    struct aime_config aime;
};

void chrono_hook_config_load(
        struct chrono_hook_config *cfg,
        const wchar_t *filename);