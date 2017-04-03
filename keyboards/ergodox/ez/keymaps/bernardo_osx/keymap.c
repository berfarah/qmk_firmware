// Netable differences vs. the default firmware for the ErgoDox EZ:
// 1. The Cmd key is now on the right side, making Cmd+Space easier.
// 2. The media keys work on OSX (But not on Windows).
#include "ez.h"
#include "debug.h"
#include "action_layer.h"

enum keyboard_layers {
  BASE = 0, // default layer
  NUMS,     // numbers + symbols
  MOVE,     // vim-like movement
  AFK,
};

enum keyboard_macros {
  MACRO_AFK = 0,
  MACRO_WAKE,
  MACRO_OTHER
};

#define BF_AFK M(MACRO_AFK)
#define BF_WAKE M(MACRO_WAKE)
#define BF_LYR(layer) MT(MO(layer), TG(layer)) // Mod or toggle layer (hold vs tap)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |    `   |   1  |   2  |   3  |   4  |   5  |   6  |           | Power|   7  |   8  |   9  |   0  |   -  |   =    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |  [   |           |   ]  |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |Ctrl/Esc|   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '    |
 * |--------+------+------+------+------+------|  L1  |           |  L1  |------+------+------+------+------+--------|
 * | LShift |Z/Ctrl|   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Hyper |  F19 |AltShf| Left | Right|                                       |  Up  | Down |Ctrl/E|  F19 |  Meh |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |  V-  |  V+  |       | Next |Play/Pau|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |  Vx  |       | Prev |        |      |
 *                                 | Space| LGUI |------|       |------|  Bsp   | Enter|
 *                                 |      |      | LAlt |       | LAlt |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = KEYMAP(  // layer 0 : default
        // left hand
        KC_GRV,         KC_1,         KC_2,   KC_3,   KC_4,   KC_5,   KC_6,
        KC_TAB,         KC_Q,         KC_W,   KC_E,   KC_R,   KC_T,   KC_LBRC,
        CTL_T(KC_ESC),  KC_A,         KC_S,   KC_D,   KC_F,   KC_G,
        KC_LSFT,        KC_Z,         KC_X,   KC_C,   KC_V,   KC_B,   MO(NUMS),
        ALL_T(KC_NO),   KC_F19,       KC_LALT,MO(MOVE),MO(NUMS),
                                                      KC_VOLD,KC_VOLU,
                                                              KC_MUTE,
                                               KC_SPC,KC_LGUI,KC_LALT,

        // right hand
        BF_AFK,    KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,          KC_EQL,
        KC_RBRC,     KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,             KC_BSLS,
                     KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,          KC_QUOT,
        MO(NUMS),KC_N, KC_M,   KC_COMM,KC_DOT, KC_SLSH,          KC_RSFT,
                        MO(NUMS),MO(MOVE),CTL_T(KC_ESC),KC_F19,     MEH_T(KC_NO),
        KC_MNXT,        KC_MPLY,
        KC_MPRV,
        KC_LALT,KC_BSPC,KC_ENT
    ),
/* Keymap 1: Number Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   !  |   @  |   #  |   $  |   %  |      |           |      |   ^  |   &  |   *  |   (  |   )  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   1  |   2  |   3  |   4  |   5  |------|           |------|   6  |   7  |   8  |   9  |   0  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// NUMSOLS
[NUMS] = KEYMAP(
       // left hand
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_EXLM,KC_AT,  KC_HASH,KC_DLR, KC_PERC,KC_TRNS,
       KC_GRV, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,
       KC_TRNS,KC_PERC,KC_CIRC,KC_LBRC,KC_RBRC,KC_TILD,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,

       // right hand
       KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_CIRC, KC_AMPR,KC_ASTR, KC_LPRN, KC_RPRN, KC_TRNS,
                KC_6 ,   KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS,
       KC_TRNS, KC_TRNS, KC_1,   KC_2,    KC_3,    KC_SLSH, KC_TRNS,
                         KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),

/* Keymap 2: Movement Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------| LEFT | DOWN |  UP  |RIGHT |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// NUMSOLS
[MOVE] = KEYMAP(
       // left hand
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,

       // right hand
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
               KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,
       KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS
),

/* Keymap 3: AFK Layer
 * All keys wake
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// NUMSOLS
[AFK] = KEYMAP(
       // left hand
       BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,
       BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,
       BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,
       BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,
       BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,
                                       BF_WAKE,BF_WAKE,
                                               BF_WAKE,
                               BF_WAKE,BF_WAKE,BF_WAKE,

       // right hand
       BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,
       BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,
                BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,
       BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,
                         BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,
       BF_WAKE,BF_WAKE,
       BF_WAKE,
       BF_WAKE,BF_WAKE,BF_WAKE
),
};

const uint16_t PROGMEM fn_actions[] = {
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case MACRO_AFK:
        if (!record->event.pressed) {
          layer_on(AFK);
          return MACRO(I(50), D(LCTL), D(LSFT), T(POWER), U(LSFT), U(LCTL), END);
        }
        break;
        case MACRO_WAKE:
        if (!record->event.pressed) {
          layer_off(AFK);
          return MACRO(T(WAKE), END);
        }
        break;
      }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
  rgblight_enable();
  rgblight_mode(1);
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
        case BASE:
            rgblight_setrgb(20,0,35);  // purple
            break;
        case NUMS:
            ergodox_right_led_1_on();
            rgblight_setrgb(0,20,20);  // light blue
            break;
        case MOVE:
            ergodox_right_led_2_on();
            rgblight_setrgb(35,10,0); // orange
            break;
        case AFK:
            ergodox_right_led_3_on();
            rgblight_setrgb(35,0,0); //red
        default:
            break;
    }

};
