#pragma once

typedef enum input_key {
    INPUT_KEY_LEFT,
    INPUT_KEY_RIGHT,
    INPUT_KEY_UP,
    INPUT_KEY_DOWN,
    INPUT_KEY_JUMP,
    INPUT_KEY_SNEAK,
    INPUT_KEY_ESCAPE
} Input_Key;

typedef enum key_state {
    KS_UNPRESSED,
    KS_PRESSED,
    KS_HELD
} Key_State;

typedef struct input_state {
    Key_State escape;
    Key_State left;
    Key_State right;
    Key_State up;
    Key_State down;
    Key_State jump;
    Key_State sneak;
} Input_State;

void input_update(void);