/* SoftwareGuy/Coburn's attempt at FateGO Arcade Hook/IO for SegaTools. 
 * This code is licensed under MIT license; don't be a thief.
 */

#include <assert.h>
#include <stddef.h>

// #include "amex/amex.h"
#include "amex/config.h"

#include "board/config.h"
#include "board/sg-reader.h"

#include "hooklib/config.h"
#include "hooklib/gfx.h"

#include "fatehook/config.h"

#include "platform/config.h"
#include "platform/platform.h"

// Loosely modeled after segatools teknoparrot forks' swdc hook stuff...
void fatego_hook_config_load(struct fatego_hook_config *cfg, const wchar_t *filename) {
		assert(cfg != NULL);
		assert(filename != NULL);
		
		platform_config_load(&cfg->platform, filename);
		// amex_config_load(&cfg->amex, filename);
		aime_config_load(&cfg->aime, filename);
		gfx_config_load(&cfg->gfx, filename);	
}