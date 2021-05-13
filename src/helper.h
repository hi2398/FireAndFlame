#pragma once

#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))

// Clamp Vector2 value with MIN and MAX and return a new vector2
// NOTE: Required for virtual mouse, to clamp inside virtual game size
Vector2 ClampValue(Vector2 value, Vector2 MIN, Vector2 MAX) {
    Vector2 result = value;
    result.x = (result.x > MAX.x) ? MAX.x : result.x;
    result.x = (result.x < MIN.x) ? MIN.x : result.x;
    result.y = (result.y > MAX.y) ? MAX.y : result.y;
    result.y = (result.y < MIN.y) ? MIN.y : result.y;
    return result;
}
