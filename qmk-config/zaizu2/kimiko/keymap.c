#include QMK_KEYBOARD_H

enum layers {
    _MAIN,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum {
    CAP_DANCE,
};

tap_dance_action_t tap_dance_actions[] = {
    [CAP_DANCE] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* MAIN
 * -------------------------------------------------------------------------------------------------------------------------------------
 * |   `   |   1   |   2   |   3   |   4   |   5   |-----------------------------------|   6   |   7   |   8   |   9   |   0   |   ~   |
 * | TAB   |   Q   |   W   |   E   |   R   |   T   |-----------------------------------|   Y   |   U   |   I   |   O   |   P   | CAPS  |
 * | LSHIFT|   A   |   S   |   D   |   F   |   G   |-----------------------------------|   H   |   J   |   K   |   L   |   ;   |'(RSHIFT)|
 * | LMETA |   Z   |   X   |   C   |   V   |   B   |  MUTE  |      |---| PSCRN|  none  |   N   |   M   |   ,   |   .   |   /   | RMETA |
 * ------------------------| LMETA | LCTRL | LALT  |RET(LOW)| ESC  |---| BSPC |SPC(RAI)| RALT  | RCTRL | RMETA |------------------------
 *
 * CAPS = tap dance CAPWORD,CAPS
 * LOWER = layer tap SPACE(LOWER)
 * RAISE = layer tap BKSPC(RAISE)
 * '(RSHIFT) = mod tap QUOTE(SHIFT)
 */
 [_QWERTY] = LAYOUT(
    KC_GRV,  KC_1, KC_2, KC_3,    KC_4,    KC_5,                                                                                  KC_6,    KC_7,    KC_8,    KC_9,   KC_0,    KC_TILD,
    KC_TAB,  KC_Q, KC_W, KC_E,    KC_R,    KC_T,                                                                                  KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,    CW_TOGG,
    KC_LSFT, KC_A, KC_S, KC_D,    KC_F,    KC_G,                                                                                  KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN, RSFT_T(KC_QUOT),
    KC_LGUI, KC_Z, KC_X, KC_C,    KC_V,    KC_B,    KC_MUTE,                   XXXXXXX,       KC_PSCR, XXXXXXX,                   KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_RGUI,
                         KC_LGUI, KC_LCTL, KC_LALT, LAYER_TAP(TL_LOWR,KC_ENT), KC_ESC,        KC_BSPC, LAYER_TAP(TL_UPPR,KC_SPC), KC_RALT, KC_RCTL, KC_RGUI
),
/* LOWER
 * -------------------------------------------------------------------------------------------------------------------------------------
 * |  F12  |  F1   |  F2   |  F3   |  F4   |  F5   |-----------------------------------|  F6   |  F7   |  F8   |  F9   |  F10  |  F11  |
 * |   !   |   $   |   +   |   =   |   (   |   )   |-----------------------------------|PG_DOWN| HOME  |  END  | PG_UP |   ^   | trans |
 * |   @   |   %   |   -   |   _   |   {   |   }   |-----------------------------------| LEFT  | DOWN  |  UP   | RIGHT |   &   | trans |
 * |   #   |   ^   |   \   |   |   |   [   |   ]   | trans | trans |---| trans | trans | trans | trans | trans | trans |   *   | trans |
 * ------------------------| trans | trans | trans | trans | trans |---| trans | trans | trans | trans | trans |------------------------
 */
[_LOWER] = LAYOUT(
    KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                             KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    KC_EXLM, KC_DLR,  KC_PLUS, KC_EQL,  KC_LPRN, KC_RPRN,                                           KC_PGUP, KC_HOME, KC_END,  KC_PGDN, KC_CIRC, _______,
    KC_AT,   KC_PERC, KC_MINS, KC_UNDS, KC_LCBR, KC_RCBR,                                           KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_AMPR, _______,
    KC_HASH, KC_CIRC, KC_BSLS, KC_PIPE, KC_LBRC, KC_RBRC, _______, _______,       _______, _______, _______, _______, _______, _______, KC_ASTR, _______,
                               _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______,
),
/* RAISE
 * -------------------------------------------------------------------------------------------------------------------------------------
 * |  F12  |  F1   |  F2   |  F3   |  F4   |  F5   |-----------------------------------|  F6   |  F7   |  F8   |  F9   |  F10  |  F11  |
 * | trans |   !   |   @   |   #   |   $   |   %   |-----------------------------------|   ^   |   &   |   *   |   (   |   )   | trans |
 * |   `   |   1   |   2   |   3   |   4   |   5   |-----------------------------------|   6   |   7   |   8   |   9   |   0   |   ~   |
 * |  F12  |  F1   |  F2   |  F3   |  F4   |  F5   | trans | trans |---| trans | trans |  F6   |  F7   |  F8   |  F9   |  F10  |  F11  |
 * ------------------------| trans | trans | trans | trans | trans |---| trans | trans | trans | trans | trans |------------------------
 */
[_RAISE] = LAYOUT(
    KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                             KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                                           KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                              KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_TILD,
    KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, _______,       _______, _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
                               _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______,
),
/* ADJUST
 * ---------------------------------------------------------------------------------------------------------------------------------------
 * | trans | trans | trans | trans | trans |  trans  |-----------------------------------| trans | trans | trans | trans | trans | trans |
 * | trans | trans | trans | trans | trans |  trans  |-----------------------------------| trans | trans | trans | trans | trans | trans |
 * |RGB_TOG|RGB_HUI|RGB_SAI|RGB_BRI|RGB_SPI|C_BRI_INC|-----------------------------------|OUT_BLE| EP_ON | trans | trans | trans | trans |
 * |RGB_EFF|RGB_HUD|RGB_SAD|RGB_BRD|RGB_SPD|C_BRI_DEC| TOG 0 | trans |---| trans | trans | trans | trans | trans | trans | trans | trans |
 * ------------------------| trans | trans |  trans  | trans | trans |---| trans | trans | trans | trans | trans |------------------------
 */
[_ADJUST] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                                           _______, _______, _______, _______, _______, DT_PRNT,
    _______, _______, _______, _______, _______, _______,                                           _______, _______, _______, _______, _______, DT_UP,
    RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, KC_BRIU,                                           KC_VOLU, KC_MUTE, KC_VOLD, _______, _______, DT_DOWN,
    RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, KC_BRID, _______, AG_TOGG,       _______, _______, _______, _______, _______, _______, _______, _______,
                               _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______,
)
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
	[_QWERTY] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
	[_LOWER] =  { ENCODER_CCW_CW(RGB_HUI, RGB_HUD) },
	[_RAISE] =  { ENCODER_CCW_CW(KC_BRIU, KC_BRID) },
	[_ADJUST] = { ENCODER_CCW_CW(XXXXXXX, XXXXXXX) },
};
#endif // ENCODER_MAP_ENABLE
