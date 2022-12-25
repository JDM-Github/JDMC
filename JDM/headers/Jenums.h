#pragma once
#include "Jtypedef.h"

JNAMESPACE JDM {
    JENUM PIXEL {
        NEWLINE = 0xA,
        BLANK = 0x20,
        PIXEL_SOLID = 0x2588,
        S0 = 0x20,
        S1 = 0x2588,
        S2 = 0x2593,
        S3 = 0x2592,
        S4 = 0x2591,
    };

    JENUM Color {
        FG_BLACK = 0x0000,
        FG_BLUE = 0x0001,
        FG_GREEN = 0x0002,
        FG_CYAN = 0x0003,
        FG_RED = 0x0004,
        FG_MAGENTA = 0x0005,
        FG_YELLOW = 0x0006,
        FG_GRAY = 0x0007,
        FG_DARK_GRAY = 0x0008,
        FG_DARK_BLUE = 0x0009,
        FG_DARK_GREEN = 0x000A,
        FG_DARK_CYAN = 0x000B,
        FG_DARK_RED = 0x000C,
        FG_DARK_MAGENTA = 0x000D,
        FG_DARK_YELLOW = 0x000E,
        FG_WHITE = 0x000F,
        BG_BLACK = 0x0000,
        BG_BLUE = 0x0010,
        BG_GREEN = 0x0020,
        BG_CYAN = 0x0030,
        BG_RED = 0x0040,
        BG_MAGENTA = 0x0050,
        BG_YELLOW = 0x0060,
        BG_GRAY = 0x0070,
        BG_DARK_GRAY = 0x0080,
        BG_DARK_BLUE = 0x0090,
        BG_DARK_GREEN = 0x00A0,
        BG_DARK_CYAN = 0x00B0,
        BG_DARK_RED = 0x00C0,
        BG_DARK_MAGENTA = 0x00D0,
        BG_DARK_YELLOW = 0x00E0,
        BG_WHITE = 0x00F0};

    JSTRUCT PixelRGB { JINT R, G, B; };
    JCONST PixelRGB
        GREY{192, 192, 192},
        DARK_GREY{128, 128, 128}, VERY_DARK_GREY{64, 64, 64},
        RED{255, 0, 0}, DARK_RED{128, 0, 0}, VERY_DARK_RED{64, 0, 0},
        YELLOW{255, 255, 0}, DARK_YELLOW{128, 128, 0}, VERY_DARK_YELLOW{64, 64, 0},
        GREEN{0, 255, 0}, DARK_GREEN{0, 128, 0}, VERY_DARK_GREEN{0, 64, 0},
        CYAN{0, 255, 255}, DARK_CYAN{0, 128, 128}, VERY_DARK_CYAN{0, 64, 64},
        BLUE{0, 0, 255}, DARK_BLUE{0, 0, 128}, VERY_DARK_BLUE{0, 0, 64},
        MAGENTA{255, 0, 255}, DARK_MAGENTA{128, 0, 128}, VERY_DARK_MAGENTA{64, 0, 64},
        WHITE{255, 255, 255}, BLACK{0, 0, 0};

    JENUM Keys {
        J_MOUSE_LEFT = 1,
        J_MOUSE_RIGHT = 2,
        J_BACKSPACE = 8,
        J_TAB,
        J_ENTER = 13,
        J_SHIFT = 16,
        J_CTRL,
        J_ALT,
        J_CAPSLOCK = 20,
        J_ESC = 27,
        J_SPACEBAR = 32,
        J_PAGEUP,
        J_PAGEDOWN,
        J_END,
        J_HOME,
        J_LEFTKEY,
        J_UPKEY,
        J_RIGHTKEY,
        J_DOWNKEY,
        J_DELETE = 46,
        J_0KEY = 48,
        J_1KEY,
        J_2KEY,
        J_3KEY,
        J_4KEY,
        J_5KEY,
        J_6KEY,
        J_7KEY,
        J_8KEY,
        J_9KEY,
        J_AKEY = 65,
        J_BKEY,
        J_CKEY,
        J_DKEY,
        J_EKEY,
        J_FKEY,
        J_GKEY,
        J_HKEY,
        J_IKEY,
        J_JKEY,
        J_KKEY,
        J_LKEY,
        J_MKEY,
        J_NKEY,
        J_OKEY,
        J_PKEY,
        J_QKEY,
        J_RKEY,
        J_SKEY,
        J_TKEY,
        J_UKEY,
        J_VKEY,
        J_WKEY,
        J_XKEY,
        J_YKEY,
        J_ZKEY,
        J_WIN = 91,
        J_NOTE = 93,
        J_F1 = 112,
        J_F2,
        J_F3,
        J_F4,
        J_F5,
        J_F6,
        J_F7,
        J_F8,
        J_F9,
        J_F10,
        J_F11,
        J_F12,
        J_LSHIFT = 160,
        J_RSHIFT,
        J_LCTRL,
        J_RCTRL,
        J_LALT,
        J_RALT,
        J_SIMICOLON = 186,
        J_ADD,
        J_COMMA,
        J_MINUS,
        J_DOT,
        J_BSLASH,
        J_DQOUTE,
        J_OBRACKET = 219,
        J_FSLASH,
        J_CBRACKET,
        J_QOUTE,
        J_PRTSC = 255,
    };
};