/*
  KEYBOARD

Summary:
  Состояние клавиатуры
*/
#ifndef KEYBOARD_H
#define KEYBOARD_H
//----------------------------------------------------------------------------
#include "stdint.h"

class Keyboard
{
public :
    // Key codes
    enum Key
    {
        A = 0,
        B, C, D, E, F, G, H, I, J, K, L, M,
        N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
        Num0,
        Num1,
        Num2,
        Num3,
        Num4,
        Num5,
        Num6,
        Num7,
        Num8,
        Num9,
        Escape,
        LControl,     // The left Control key
        LShift,       // The left Shift key
        LAlt,         // The left Alt key
        LSystem,      // The left OS specific key: window (Windows and Linux), apple (MacOS X), ...
        RControl,     // The right Control key
        RShift,       // The right Shift key
        RAlt,         // The right Alt key
        RSystem,      // The right OS specific key: window (Windows and Linux), apple (MacOS X), ...
        Menu,         // The Menu key
        LBracket,     // The [ key
        RBracket,     // The ] key
        SemiColon,    // The ; key
        Comma,        // The , key
        Period,       // The . key
        Quote,        // The ' key
        Slash,        // The / key
        BackSlash,    // The \ key
        Tilde,        // The ~ key
        Equal,        // The = key
        Dash,         // The - key
        Space,        // The Space key
        Return,       // The Return key
        BackSpace,    // The Backspace key
        Tab,          // The Tabulation key
        PageUp,       // The Page up key
        PageDown,     // The Page down key
        End,          // The End key
        Home,         // The Home key
        Insert,       // The Insert key
        Delete,       // The Delete key
        Add,          // +
        Subtract,     // -
        Multiply,     // *
        Divide,       // /
        Left,         // Left arrow
        Right,        // Right arrow
        Up,           // Up arrow
        Down,         // Down arrow
        Numpad0,      // The numpad 0 key
        Numpad1,      // The numpad 1 key
        Numpad2,      // The numpad 2 key
        Numpad3,      // The numpad 3 key
        Numpad4,      // The numpad 4 key
        Numpad5,      // The numpad 5 key
        Numpad6,      // The numpad 6 key
        Numpad7,      // The numpad 7 key
        Numpad8,      // The numpad 8 key
        Numpad9,      // The numpad 9 key
        F1, F2, F3,  F4, F5, F6, F7, F8, F9, F10, F11, F12, F13,  F14, F15,
        Pause,        // The Pause key

        KeyCount      // Keep last -- the total number of keyboard keys
    };
public:
  // Check if a key is pressed
  bool is_pressed(const Key k) const;
};

//----------------------------------------------------------------------------
#endif // KEYBOARD_H