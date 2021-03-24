#include "vector.h"

#include <math.h>

static const float PI = 3.14159265358979323846f;

float rad2deg(const float rad) {
  return rad * (180 / PI);
}

float deg2rad(const float deg) {
  return deg / (180 / PI);
}

vec2 add(const vec2 a, const vec2 b) {
  return (vec2){a.x + b.x, a.y + b.y};
}

vec2 sub(const vec2 a, const vec2 b) {
  return (vec2){a.x - b.x, a.y - b.y};
}

float dot(const vec2 a, const vec2 b) {
  return a.x * b.x + a.y * b.y;
}

vec2 mul(const vec2 v, const float scalar) {
  return (vec2){v.x * scalar, v.y * scalar};
}

float len(const vec2 v) {
  return sqrtf(v.x * v.x + v.y * v.y);
}

vec2 normal(const vec2 v) {
  const float length = len(v);
  return (vec2){v.x / length, v.y / length};
}

float rotation(const vec2 v) {
  return rad2deg(atan2f(v.x, v.y));
}

vec2 rotated(const vec2 v, const float deg) {
  const float rad = deg2rad(deg);
  const float cos = cosf(rad);
  const float sin = sinf(rad);
  return (vec2){
    .x = cos * v.x - sin * v.y,
    .y = sin * v.x + cos * v.y,
  };
}
