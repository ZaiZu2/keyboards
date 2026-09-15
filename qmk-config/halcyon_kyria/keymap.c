#include QMK_KEYBOARD_H

enum layers {
    _WIN, // layer 0 = the default layer on boot
    _MAC,
    _LOWER,
    _RAISE,
    _ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* MAC
     * -----------------------------------------------------------------------------------------------------------------------------------------------------
     * |  TAB   |   Q    |   W    |   E    |   R    |   T    |---------------------------------------|   Y    |   U    |   I    |   O    |   P    |CAPSWORD|
     * | LSHIFT |   A    |   S    |   D    |   F    |   G    |---------------------------------------|   H    |   J    |   K    |   L    |   ;    |'(RSFT) |
     * |  LALT  |   Z    |   X    |   C    |   V    |   B    |  none  | TO WIN |---| PSCRN  |  none  |   N    |   M    |   ,    |   .    |   /    |  RALT  |
     * ---------------------------|ENC:MUTE| LCTRL  |  SPC   | LOWER  |GUI(RET)|---|GUI(ESC)| RAISE  |  BSPC  | RCTRL  |ENC:none|--------------------------
     */
    [_MAC] = LAYOUT(
        KC_TAB,  KC_Q, KC_W, KC_E,    KC_R,    KC_T,                                                                  KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,    CW_TOGG,
        KC_LSFT, KC_A, KC_S, KC_D,    KC_F,    KC_G,                                                                  KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN, RSFT_T(KC_QUOT),
        KC_LALT, KC_Z, KC_X, KC_C,    KC_V,    KC_B,   XXXXXXX,     DF(_WIN),             XXXXXXX,        KC_PSCR,    KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_RALT,
                             KC_MUTE, KC_LCTL, KC_SPC, MO(_LOWER),  LGUI_T(KC_ENT),       RGUI_T(KC_ESC), MO(_RAISE), KC_BSPC, KC_RCTL, XXXXXXX
    ),
    /* WIN
     * -----------------------------------------------------------------------------------------------------------------------------------------------------
     * |  TAB   |   Q    |   W    |   E    |   R    |   T    |---------------------------------------|   Y    |   U    |   I    |   O    |   P    |CAPSWORD|
     * | LSHIFT |   A    |   S    |   D    |   F    |   G    |---------------------------------------|   H    |   J    |   K    |   L    |   ;    |'(RSFT) |
     * |  LGUI  |   Z    |   X    |   C    |   V    |   B    |  none  | TO MAC |---| PSCRN  |  none  |   N    |   M    |   ,    |   .    |   /    |  RGUI  |
     * ---------------------------|ENC:MUTE| LCTRL  |  SPC   | LOWER  |ALT(RET)|---|ALT(ESC)| RAISE  |  BSPC  | RCTRL  |ENC:none|--------------------------
     */
    [_WIN] = LAYOUT(
        KC_TAB,  KC_Q, KC_W, KC_E,    KC_R,    KC_T,                                                                  KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,    CW_TOGG,
        KC_LSFT, KC_A, KC_S, KC_D,    KC_F,    KC_G,                                                                  KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN, RSFT_T(KC_QUOT),
        KC_LGUI, KC_Z, KC_X, KC_C,    KC_V,    KC_B,   XXXXXXX,     DF(_MAC),             XXXXXXX,        KC_PSCR,    KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_RGUI,
                             KC_MUTE, KC_LCTL, KC_SPC, MO(_LOWER),  LALT_T(KC_ENT),       RALT_T(KC_ESC), MO(_RAISE), KC_BSPC, KC_RCTL, XXXXXXX
    ),
    /* LOWER
     * -----------------------------------------------------------------------------------------------------------------------------------------------------
     * | trans  |   !    |   @    |   #    |   $    |   %    |---------------------------------------|   ^    |   &    |   *    |   (    |   )    |  CAPS  |
     * |   `    |   1    |   2    |   3    |   4    |   5    |---------------------------------------|   6    |   7    |   8    |   9    |   0    |   ~    |
     * |  F12   |   F1   |   F2   |   F3   |   F4   |   F5   | trans  |  BOOT  |---| trans  | trans  |   F6   |   F7   |   F8   |   F9   |  F10   |  F11   |
     * ---------------------------| trans  | trans  | trans  | trans  | trans  |---| DELETE | ADJUST | trans  | trans  | trans  |--------------------------
     */
    [_LOWER] = LAYOUT(
        _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                                            KC_CIRC,     KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_CAPS,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                               KC_6,        KC_7,    KC_8,    KC_9,    KC_0,    KC_TILD,
        KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, QK_BOOT,       _______, _______,  KC_F6,       KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
                                   _______, _______, _______, _______, _______,       KC_DEL,  MO(_ADJUST), _______, _______, _______
    ),
    /* RAISE
     * -----------------------------------------------------------------------------------------------------------------------------------------------------
     * |   !    |   $    |   +    |   =    |   (    |   )    |---------------------------------------| PG_UP  |  HOME  |  END   |PG_DOWN |   ^    |  CAPS  |
     * |   @    |   %    |   -    |   _    |   {    |   }    |---------------------------------------|  LEFT  |  DOWN  |   UP   | RIGHT  |   &    | trans  |
     * |   #    |   ^    |   \    |   |    |   [    |   ]    | trans  | trans  |---|  BOOT  | trans  | trans  | INSERT | DELETE | trans  |   *    | trans  |
     * ---------------------------| trans  | trans  | trans  | ADJUST | trans  |---| trans  | trans  | trans  | trans  | trans  |--------------------------
     */
    [_RAISE] = LAYOUT(
        KC_EXLM, KC_DLR,  KC_PLUS, KC_EQL,  KC_LPRN, KC_RPRN,                                                KC_PGUP, KC_HOME, KC_END, KC_PGDN, KC_CIRC, KC_CAPS,
        KC_AT,   KC_PERC, KC_MINS, KC_UNDS, KC_LCBR, KC_RCBR,                                                KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT, KC_AMPR, _______,
        KC_HASH, KC_CIRC, KC_BSLS, KC_PIPE, KC_LBRC, KC_RBRC, _______, _______,           QK_BOOT, _______,  _______, KC_INS,  KC_DEL, _______, KC_ASTR, _______,
                                   _______, _______, _______, MO(_ADJUST), _______,       _______, _______,  _______, _______, _______
    ),
    /* ADJUST
     * -----------------------------------------------------------------------------------------------------------------------------------------------------
     * | trans  | trans  | trans  | trans  | trans  | trans  |---------------------------------------| trans  | trans  | trans  | trans  | trans  | DT_UP  |
     * |RGB_TOG |  HUE+  |  SAT+  |  BRI+  |  SPD+  |SCR_BRI+|---------------------------------------|  VOL+  |  MUTE  |  VOL-  | trans  | trans  |DT_DOWN |
     * |RGB_EFF |  HUE-  |  SAT-  |  BRI-  |  SPD-  |SCR_BRI-| EE_CLR | trans  |---| trans  | trans  | trans  | trans  | trans  | trans  | trans  |DT_PRNT |
     * ---------------------------| trans  | trans  | trans  | trans  | trans  |---| trans  | trans  | trans  | trans  | trans  |--------------------------
     */
    [_ADJUST] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                                            _______, _______, _______, _______, _______, DT_UP,
        RM_TOGG, RM_HUEU, RM_SATU, RM_VALU, RM_SPDU, KC_BRIU,                                            KC_VOLU, KC_MUTE, KC_VOLD, _______, _______, DT_DOWN,
        RM_NEXT, RM_HUED, RM_SATD, RM_VALD, RM_SPDD, KC_BRID, EE_CLR,  _______,        _______, _______, _______, _______, _______, _______, _______, DT_PRNT,
                                   _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    //              left encoder                        right encoder
    [_MAC] =    { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_BRID, KC_BRIU) },
    [_WIN] =    { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_BRID, KC_BRIU) },
    [_LOWER] =  { ENCODER_CCW_CW(RM_HUED, RM_HUEU), ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [_RAISE] =  { ENCODER_CCW_CW(KC_BRID, KC_BRIU), ENCODER_CCW_CW(RM_VALD, RM_VALU) },
    [_ADJUST] = { ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(XXXXXXX, XXXXXXX) },
};
#endif // ENCODER_MAP_ENABLE
