#include "utils.h"

#define GAME_WIDTH  800
#define GAME_HEIGHT 800
#define MAP_COLS    10
#define MAP_ROWS    10

void draw_map(int* map) {
  SDL_Rect cell    = {0, 0, GAME_WIDTH / MAP_COLS, GAME_HEIGHT / MAP_ROWS};
  int      mapSize = MAP_COLS * MAP_ROWS;

  for (int i = 0; i < mapSize; i++) {
    if (map[i] != 0) {
      switch (map[i]) {
        case 1:
          SDL_SetRenderDrawColor(renderer, 100, 255, 100, 255);
          break;
        case 2:
          SDL_SetRenderDrawColor(renderer, 100, 100, 255, 255);
          break;
        case 3:
          SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
          break;
      }

      SDL_RenderFillRect(renderer, &cell);
    }

    cell.x += cell.w;

    if ((i + 1) % MAP_COLS == 0) {
      cell.y += cell.h;
      cell.x = 0;
    }
  }
}

void draw_grid(int cols, int rows) {
  int colWidth  = GAME_WIDTH / cols;
  int rowHeight = GAME_HEIGHT / rows;

  SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);

  int x1 = 0, x2 = GAME_WIDTH;
  for (int row = 1; row < rows; row++) {
    int rowPos = row * rowHeight;
    SDL_RenderDrawLine(renderer, x1, rowPos, x2, rowPos);
  }

  int y1 = 0, y2 = GAME_HEIGHT;
  for (int col = 1; col < cols; col++) {
    int colPos = col * colWidth;
    SDL_RenderDrawLine(renderer, colPos, y1, colPos, y2);
  }
}

typedef struct Node {
  int H;
  int G;
  int F;
  int block;
} Node;

int xyToInt(int x, int y) {
  return y * MAP_COLS + x;
}

int      closedListIndex = 0;
SDL_bool hasInArray(int* array, int position) {
  for (int i = 0; i < closedListIndex; i++) {
    if (array[i] == position) return SDL_TRUE;
  }

  return SDL_FALSE;
}

int main(__attribute__((unused)) int argc, __attribute__((unused)) char** argv) {
  create_game(GAME_WIDTH, GAME_HEIGHT);

  SDL_Rect cat             = {0, 1, 80, 80};
  SDL_Rect bone            = {8, 8, 80, 80};
  Node     openList[4]     = {0};
  int      closedList[100] = {0};
  int      openListIndex   = 0;

  int bonePosition = xyToInt(bone.x, bone.y);

  int map[MAP_COLS * MAP_ROWS] = {
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 3,
    3, 0, 0, 3, 0, 3, 0, 0, 0, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 0, 3,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 3,
    3, 0, 0, 0, 0, 3, 0, 3, 3, 3,
    3, 0, 0, 0, 0, 3, 0, 0, 0, 3,
    3, 0, 3, 3, 0, 3, 3, 3, 3, 3,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3};

  int catPosition = xyToInt(cat.x, cat.y);

  printf("cat: %d  |  bone: %d\n\n", catPosition, bonePosition);

  while (is_running()) {
    handle_input();

    openListIndex = 0;
    if (catPosition != bonePosition) {
      closedList[closedListIndex++] = catPosition;

      int leftBlock  = catPosition - 1;
      int rightBlock = catPosition + 1;
      int topBlock   = catPosition - 10;
      int botBlock   = catPosition + 10;

      if (!hasInArray(closedList, leftBlock) && map[leftBlock] != 3) {
        openList[openListIndex].H     = SDL_abs(bonePosition - leftBlock);
        openList[openListIndex].G     = 1;
        openList[openListIndex].F     = openList[openListIndex].H + openList[openListIndex].G;
        openList[openListIndex].block = leftBlock;
        openListIndex++;
      }

      if (!hasInArray(closedList, rightBlock) && map[rightBlock] != 3) {
        openList[openListIndex].H     = SDL_abs(bonePosition - rightBlock);
        openList[openListIndex].G     = 1;
        openList[openListIndex].F     = openList[openListIndex].H + openList[openListIndex].G;
        openList[openListIndex].block = rightBlock;
        openListIndex++;
      }

      if (!hasInArray(closedList, topBlock) && map[topBlock] != 3) {
        openList[openListIndex].H     = SDL_abs(bonePosition - topBlock);
        openList[openListIndex].G     = 1;
        openList[openListIndex].F     = openList[openListIndex].H + openList[openListIndex].G;
        openList[openListIndex].block = topBlock;
        openListIndex++;
      }

      if (!hasInArray(closedList, botBlock) && map[botBlock] != 3) {
        openList[openListIndex].H     = SDL_abs(bonePosition - botBlock);
        openList[openListIndex].G     = 1;
        openList[openListIndex].F     = openList[openListIndex].H + openList[openListIndex].G;
        openList[openListIndex].block = botBlock;
        openListIndex++;
      }

      Node lesser = openList[0];
      for (int i = 1; i < openListIndex; i++) {
        if (openList[i].F < lesser.F)
          lesser = openList[i];
      }

      cat.x = lesser.block % 10;
      cat.y = lesser.block / 10;

      catPosition = lesser.block;
    }

    map[catPosition]  = 1;
    map[bonePosition] = 2;
    printf("Cat position before render: %d\n", catPosition);

    SDL_SetRenderDrawColor(renderer, 230, 230, 230, 255);
    SDL_RenderClear(renderer);
    draw_grid(10, 10);
    draw_map(map);
    render_present();

    SDL_Delay(500);
  }

  destroy_game();
  return 0;
}
