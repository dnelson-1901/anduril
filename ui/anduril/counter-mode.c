// counter-mode.c: Counter mode for Anduril.
// Copyright (C) 2025 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "anduril/counter-mode.h"

uint8_t counter_state(Event event, uint16_t arg) {
    // counter starts at zero each time
    /* actually... maybe let it remember between invocations
     * so it can be used as a torch between counter clicks
    if (event == EV_enter_state) {
        counter_clicks = 0;
    }
    */

    // act like "off" mode except when clicked
    if (!(event & B_FLAGS)) {  // if not a button event
        return off_state(event, arg);
    }

    // up to 15 clicks: add to the counter
    else if ((event & B_FLAGS) == (B_CLICK | B_TIMEOUT)) {
        blink_once();
        counter_clicks += (event & B_COUNT);
        return EVENT_HANDLED;
    }

    // hold: reset counter
    else if (event == EV_click1_hold) {
        counter_clicks = 0;
        if (!arg) blink_once();
        return EVENT_HANDLED;
    }

    // 2H: show current count
    else if (event == EV_click2_hold_release) {
        set_state(counter_readout_state, 0);
        return EVENT_HANDLED;
    }

    // 3H: exit and turn off
    else if (event == EV_click3_hold) {
        empty_event_sequence();
        blink_once();
        set_state(off_state, 0);
        return EVENT_HANDLED;
    }

    return EVENT_NOT_HANDLED;
}

uint8_t counter_readout_state(Event event, uint16_t arg) {
    // 1 click: off
    if (event == EV_1click) {
        set_state(counter_state, 0);
        return EVENT_HANDLED;
    }

    return EVENT_NOT_HANDLED;
}

inline void counter_readout_iter() {
    blink_big_num(counter_clicks);
    set_state_deferred(counter_state, 0);
}

