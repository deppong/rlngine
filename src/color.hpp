#pragma once
#ifndef COLOR_HPP
#define COLOR_HPP

#include <stdint.h>

uint32_t pack_color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a);

// Dark colors
static const uint32_t COLOR_BLACK   = pack_color(  0,   0,   0, 255);
static const uint32_t COLOR_MAROON  = pack_color(128,   0,   0, 255);
static const uint32_t COLOR_GREEN   = pack_color(  0, 128,   0, 255);
static const uint32_t COLOR_NAVY    = pack_color(  0,   0, 128, 255);
static const uint32_t COLOR_OLIVE   = pack_color(128, 128,   0, 255);
static const uint32_t COLOR_PURPLE  = pack_color(128,   0, 128, 255);
static const uint32_t COLOR_TEAL    = pack_color(  0, 128, 128, 255);
static const uint32_t COLOR_SILVER  = pack_color(192, 192, 192, 255);
static const uint32_t COLOR_GRAY    = pack_color(128, 128, 128, 255);

// Light Colors
static const uint32_t COLOR_RED     = pack_color(255,   0,   0, 255);
static const uint32_t COLOR_LIME    = pack_color(  0, 255,   0, 255);
static const uint32_t COLOR_BLUE    = pack_color(  0,   0, 255, 255);
static const uint32_t COLOR_YELLOW  = pack_color(255, 255,   0, 255);
static const uint32_t COLOR_FUCHSIA = pack_color(255,   0, 255, 255);
static const uint32_t COLOR_AQUA    = pack_color(  0, 255, 255, 255);
static const uint32_t COLOR_WHITE   = pack_color(255, 255, 255, 255);


#endif // COLOR_HPP