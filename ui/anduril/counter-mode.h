// counter-mode.h: Counter mode for Anduril.
// Copyright (C) 2025 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

// counter mode
uint16_t counter_clicks = 0;
uint8_t counter_state(Event event, uint16_t arg);
uint8_t counter_readout_state(Event event, uint16_t arg);

