#pragma once
#ifndef COLOR_HPP
#define COLOR_HPP

#include <stdint.h>
#include <array>

uint32_t pack_color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a);

// Dark colors
static const uint32_t COLOR_BLACK   =  0;
static const uint32_t COLOR_MAROON  =  1;
static const uint32_t COLOR_GREEN   =  2;
static const uint32_t COLOR_NAVY    =  3;
static const uint32_t COLOR_OLIVE   =  4;
static const uint32_t COLOR_PURPLE  =  5;
static const uint32_t COLOR_TEAL    =  6;
static const uint32_t COLOR_SILVER  =  7;
static const uint32_t COLOR_GRAY    =  8;

// Light Colors
static const uint32_t COLOR_RED     =  9;
static const uint32_t COLOR_LIME    = 10;
static const uint32_t COLOR_BLUE    = 11;
static const uint32_t COLOR_YELLOW  = 12;
static const uint32_t COLOR_FUCHSIA = 13;
static const uint32_t COLOR_AQUA    = 14;
static const uint32_t COLOR_WHITE   = 15;
static const uint32_t COLOR_CLEAR   = 16;

static const std::array<uint32_t, 17> COLORS = {
    pack_color(  0,   0,   0, 255),
    pack_color(128,   0,   0, 255),
    pack_color(  0, 128,   0, 255),
    pack_color(  0,   0, 128, 255),
    pack_color(128, 128,   0, 255),
    pack_color(128,   0, 128, 255),
    pack_color(  0, 128, 128, 255),
    pack_color(192, 192, 192, 255),
    pack_color(128, 128, 128, 255),
    pack_color(255,   0,   0, 255),
    pack_color(  0, 255,   0, 255),
    pack_color(  0,   0, 255, 255),
    pack_color(255, 255,   0, 255),
    pack_color(255,   0, 255, 255),
    pack_color(  0, 255, 255, 255),
    pack_color(255, 255, 255, 255),
    pack_color(  0,   0,   0,   0)
};

#endif