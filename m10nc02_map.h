/*
  pico_cnc_map.h - driver code for RP2040 ARM processors

  Part of grblHAL

  Copyright (c) 2021 Terje Io

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdint.h>

#if TRINAMIC_ENABLE
#error Trinamic plugin not supported!
#endif

#if N_ABC_MOTORS > 3
#error "Axis configuration is not supported!"
#endif

#define BOARD_NAME "M10NC02"
#define HAS_BOARD_INIT

typedef union {
    uint32_t value;
    struct {
        uint32_t aux9_out    :1,
                 aux8_out    :1,
                 aux7_out    :1,
                 aux6_out    :1,
                 aux5_out    :1,
                 aux4_out    :1,
                 aux3_out    :1,
                 aux2_out    :1,
                 aux1_out    :1,
                 aux0_out    :1,
                 m5_ena      :1,
                 m4_ena      :1,
                 m3_ena      :1,
                 z_ena       :1,
                 y_ena       :1,
                 x_ena       :1,
                 unused      :16;
    };
} output_sr_t;

typedef union {
    uint16_t value;
    struct {
        uint16_t m5_dir  :1,
                 m4_dir  :1,
                 m3_dir  :1,
                 z_dir   :1,
                 y_dir   :1,
                 x_dir   :1,
                 m5_step :1,
                 m4_step :1,
                 m3_step :1,
                 z_step  :1,
                 y_step  :1,
                 x_step  :1,
                 unused  :4;
    };
} step_dir_t;

typedef union {
    uint32_t value;
    struct {
        step_dir_t set;
        step_dir_t reset;
    };
} step_dir_sr_t;

// Define step pulse output pins.
#define SD_SHIFT_REGISTER   16
#define SD_SR_DATA_PIN      10
#define SD_SR_SCK_PIN       11 // includes next pin (12)

// Define output signals pins.
#define OUT_SHIFT_REGISTER  16
#define OUT_SR_DATA_PIN     7
#define OUT_SR_SCK_PIN      6
#define OUT_SR_LCK_PIN      8

#define AUX_N_OUT           8
#define AUX_OUT_MASK        0xFF

// Define ganged axis or A axis step pulse and step direction output pins.
#if N_ABC_MOTORS > 2
#define M3_AVAILABLE
#define M3_STEP_PIN         0
#define M3_STEP_PORT        GPIO_SR8
#define M3_DIRECTION_PIN    0
#define M3_DIRECTION_PORT   GPIO_SR8
#define M3_LIMIT_PIN        0
#define M3_ENABLE_PIN       0
#define M3_ENABLE_PORT      GPIO_SR16
#define M4_AVAILABLE
#define M4_STEP_PIN         0
#define M4_STEP_PORT        GPIO_SR8
#define M4_DIRECTION_PIN    0
#define M4_DIRECTION_PORT   GPIO_SR8
#define M4_LIMIT_PIN        0
#define M4_ENABLE_PIN       0
#define M4_ENABLE_PORT      GPIO_SR16
#define M5_AVAILABLE
#define M5_STEP_PIN         0
#define M5_STEP_PORT        GPIO_SR8
#define M5_DIRECTION_PIN    0
#define M5_DIRECTION_PORT   GPIO_SR8
#define M5_LIMIT_PIN        0
#define M5_ENABLE_PIN       0
#define M5_ENABLE_PORT      GPIO_SR16
#endif

// Define homing/hard limit switch input pins.
#define X_LIMIT_PIN         0
#define Y_LIMIT_PIN         1
#define Z_LIMIT_PIN         2
#define LIMIT_INMODE        GPIO_IOEXPAND

// Define spindle PWM output pin.
#define SPINDLE_PWM_PORT    GPIO_OUTPUT
#define SPINDLE_PWM_PIN     22

// Define user-control controls (cycle start, reset, feed hold) input pins.
#define RESET_PIN           9
#define FEED_HOLD_PIN       13
#define CYCLE_START_PIN     14
#if SAFETY_DOOR_ENABLE
#define SAFETY_DOOR_PIN     9
#endif
#define CONTROL_INMODE      GPIO_MAP

// Define probe switch input pin.
#define PROBE_PIN           27

#if MPG_MODE == 1
#define MPG_MODE_PIN        AUX_IO3_PIN
#endif