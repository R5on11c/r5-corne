/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include <stdio.h>
#include "lib/lib8tion/lib8tion.h"
#include "transactions.h"
#include "keymap_extras/keymap_german.h"

typedef struct user_config {
    uint8_t rgb_scale_r;
    uint8_t rgb_scale_g;
    uint8_t rgb_scale_b;
} user_config;

user_config user_state;

enum custom_keycodes {
    RGB_SCALE_UP_R = SAFE_RANGE,
    RGB_SCALE_DOWN_R,
    RGB_SCALE_UP_G,
    RGB_SCALE_DOWN_G,
    RGB_SCALE_UP_B,
    RGB_SCALE_DOWN_B,
    RGB_SCALE_CUSTOM,
    RGB_SCALE_OFF,
};
// ┌───────────────────────────────────────────────────────────┐
// │ d e f i n e   m a c r o n a m e s                         │
// └───────────────────────────────────────────────────────────┘

// READABILITY ├───────────────────────────────────────────────┐

#define M_PREV KC_MEDIA_PREV_TRACK
#define M_PLPA KC_MEDIA_PLAY_PAUSE
#define M_NEXT KC_MEDIA_NEXT_TRACK

// RIGHT HAND THUMB CLUSTER MODS ├─────────────────────────────┐

#define RAI_BSP LT(2, KC_BSPC)

#define TTY_1 LCTL(LALT(KC_F1))
#define TTY_2 LCTL(LALT(KC_F2))
#define TTY_3 LCTL(LALT(KC_F3))
#define TTY_4 LCTL(LALT(KC_F4))
#define TTY_5 LCTL(LALT(KC_F5))

#define RGB_SCALE_STEP 8
/* extern LED_TYPE rgb_matrix_ws2812_array[DRIVER_LED_TOTAL]; */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_LALT,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         DE_Z,    KC_U,    KC_I,    KC_O,   KC_P,  KC_RALT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, DE_ODIA, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    DE_Y,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, DE_MINS, KC_RCTL,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   MO(1),  KC_SPC,     KC_ENT, RAI_BSP,  KC_ESC
                                      //`--------------------------'  `--------------------------'

  ),

  [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_LALT,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, DE_PLUS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,  KC_F11,  KC_F12, XXXXXXX, XXXXXXX,  KC_TAB,                      XXXXXXX, XXXXXXX, DE_GRV, XXXXXXX, XXXXXXX, DE_HASH,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT,   MO(3),  KC_ESC
                                      //`--------------------------'  `--------------------------'
  ),

  [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      DE_CIRC, DE_EXLM, DE_DQUO, DE_SECT,  DE_DLR, DE_PERC,                      DE_AMPR, DE_SLSH, DE_LPRN, DE_RPRN,  DE_EQL, KC_UNDS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, DE_ADIA,   DE_SS, DE_UDIA, XXXXXXX, XXXXXXX,                      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, KC_PIPE, KC_LBRC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, DE_LBRC, DE_RBRC, DE_LCBR, DE_RCBR, XXXXXXX,                      KC_PSCR, DE_TILD, DE_LABK, DE_RABK,  KC_ESC, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   MO(3),  KC_SPC,     KC_ENT, _______,  KC_ESC
                                      //`--------------------------'  `--------------------------'
  ),

  [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX,  M_PREV,  M_PLPA,  M_NEXT, XXXXXXX,                         TTY_1,   TTY_2,   TTY_3,   TTY_4,   TTY_5, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      RGB_SCALE_UP_R, RGB_SCALE_UP_G, RGB_SCALE_UP_B, RGB_SCALE_CUSTOM, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      RGB_SCALE_DOWN_R, RGB_SCALE_DOWN_G, RGB_SCALE_DOWN_B, RGB_SCALE_OFF, XXXXXXX,   TG(4),
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,      KC_ENT, _______,  KC_ESC
                                      //`--------------------------'  `--------------------------'
  ),

  [4] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,    TG(4),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, XXXXXXX,  KC_SPC,      KC_ENT, XXXXXXX, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),
};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return OLED_ROTATION_270;
}

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer"), false);
    switch (layer_state) {
        case L_BASE:
            oled_write_ln_P(PSTR("Dflt"), false);
            break;
        case L_LOWER:
            oled_write_P(PSTR("Lower"), false);
            break;
        case L_RAISE:
            oled_write_P(PSTR("Raise"), false);
            break;
        case L_ADJUST:
        case L_ADJUST|L_LOWER:
        case L_ADJUST|L_RAISE:
        case L_ADJUST|L_LOWER|L_RAISE:
            oled_write_P(PSTR("Adjst"), false);
            break;
    }
    oled_write_P(PSTR("-----"), false);
}


char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

static void oled_render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4,
        0x95, 0x96, 0x97, 0x98, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x9F,
    };

    oled_write_P(qmk_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
    return false;
}
#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }
  if (record->event.pressed) {
    set_keylog(keycode, record);
    switch (keycode) {
      case RGB_SCALE_UP_R:
        user_state.rgb_scale_r = qadd8(user_state.rgb_scale_r, RGB_SCALE_STEP);
        return false;
      case RGB_SCALE_DOWN_R:
        user_state.rgb_scale_r = qsub8(user_state.rgb_scale_r, RGB_SCALE_STEP);
        return false;
      case RGB_SCALE_UP_G:
        user_state.rgb_scale_g = qadd8(user_state.rgb_scale_g, RGB_SCALE_STEP);
        return false;
      case RGB_SCALE_DOWN_G:
        user_state.rgb_scale_g = qsub8(user_state.rgb_scale_g, RGB_SCALE_STEP);
        return false;
      case RGB_SCALE_UP_B:
        user_state.rgb_scale_b = qadd8(user_state.rgb_scale_b, RGB_SCALE_STEP);
        return false;
      case RGB_SCALE_DOWN_B:
        user_state.rgb_scale_b = qsub8(user_state.rgb_scale_b, RGB_SCALE_STEP);
        return false;
      case RGB_SCALE_CUSTOM:
        user_state.rgb_scale_r = 0;
        user_state.rgb_scale_g = 40;
        user_state.rgb_scale_b = 8;
        return false;
      case RGB_SCALE_OFF:
        user_state.rgb_scale_r = 0;
        user_state.rgb_scale_g = 0;
        user_state.rgb_scale_b = 0;
        return false;
    }
  }
  return true;
}

void user_sync(void) {
    static user_config last_user_state;
    static bool        needs_sync = false;

    if (memcmp(&user_state, &last_user_state, sizeof(user_config))) {
        needs_sync = true;
        memcpy(&last_user_state, &user_state, sizeof(user_config));
    }

    if (needs_sync) {
        needs_sync = !transaction_rpc_send(USER_SYNC_ID, sizeof(user_config), &user_state);
    }
}

void user_sync_handler(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer, uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(user_state)) {
        memcpy(&user_state, initiator2target_buffer, sizeof(user_config));
    }
}

void keyboard_post_init_user(void) {
    transaction_register_rpc(USER_SYNC_ID, user_sync_handler);

    user_state.rgb_scale_r = 100;
    user_state.rgb_scale_g = 100;
    user_state.rgb_scale_b = 100;

    if (is_keyboard_master()) {
        user_sync();
    }
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    for (uint8_t i = led_min; i < led_max; i++) {
        if (g_led_config.flags[i] & LED_FLAG_UNDERGLOW) {
            /* RGB temp_rgb = {0}; */
            /* temp_rgb.r   = scale8(rgb_matrix_ws2812_array[i].r, user_state.rgb_scale_r); */
            /* temp_rgb.g   = scale8(rgb_matrix_ws2812_array[i].g, user_state.rgb_scale_g); */
            /* temp_rgb.b   = scale8(rgb_matrix_ws2812_array[i].b, user_state.rgb_scale_b); */
            /* rgb_matrix_set_color(i, temp_rgb.r, temp_rgb.g, temp_rgb.b); */
            rgb_matrix_set_color(i, user_state.rgb_scale_r, user_state.rgb_scale_g, user_state.rgb_scale_b);
        }
    }

    return false;
}

void suspend_power_down_user(void) {
    matrix_scan();
}

void housekeeping_task_user(void) {
    if (is_keyboard_master()) {
        user_sync();
    }
}
