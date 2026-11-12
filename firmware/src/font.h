/*
 * Derived from "lcd library for ssd1306/ssd1309/sh1106 oled-display"
 * by Michael Koehler (Skie-Systems), https://github.com/Sylaina/oled-display
 * Copyright 2016-2018 Skie-Systems.
 *
 * Modified for the Assistive Smart Bracelet project (I2C driver calls,
 * SH1106 support removed, font/mapping adjustments).
 *
 * Licensed under the GNU General Public License v3.0 or later
 * (GPL-3.0-or-later). See the LICENSE file in the repository root.
 */
#ifndef _FONT_H_
#define _FONT_H_

#include <avr/pgmspace.h>
#include <inttypes.h>

/* font data stored in PROGMEM */
extern const uint8_t ssd1306oled_font[][6] PROGMEM;
/* special_char: pairs of {char_code, position_in_font}
   char_code is the 8-bit character code that should map to the glyph
   position_in_font is the index in ssd1306oled_font (0-based)
   table is terminated by {0xFF, 0xFF} */
extern const uint8_t special_char[][2] PROGMEM;

#endif /* _FONT_H_ */