#ifndef VECTOR_H
#define VECTOR_H

#define VEC2(x, y) \
  (vec2) {         \
    x, y           \
  }

typedef struct vec2 {
  float x;
  float y;
} vec2;

float rad2deg(const float rad);

float deg2rad(const float deg);

vec2 rad2vec(const float rad);

vec2 add(const vec2 a, const vec2 b);

vec2 sub(const vec2 a, const vec2 b);

float dot(const vec2 a, const vec2 b);

vec2 mul(const vec2 v, const float scalar);

float len(const vec2 v);

vec2 normal(const vec2 v);

float rotation(const vec2 v);

vec2 rotated(const vec2 v, const float deg);

#endif  // VECTOR_H
