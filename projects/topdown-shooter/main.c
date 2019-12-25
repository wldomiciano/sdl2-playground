#include <SDL.h>
#include <stdarg.h>
#include "framework.h"
#include "game.h"

int main() { return game_run("Hello", 400, 400, create, update, destroy); }