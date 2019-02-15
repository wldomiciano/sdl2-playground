#include "scene.h"

DEFINE(forest, CREATE, UPDATE);

Player* player;
GoblinHorde* goblins;
DragonHorde* dragons;
Map* map;
MovingPlatform platform;

static void create() {
    map = createMap("forest.map");
    player = createPlayer();
    goblins = createGoblinHorde(10);
    dragons = createDragonHorde(5);

    add(player);
    add(map);
    add(goblins);
    add(dragons);
}

static void update() {
    updateGoblinHorde(goblins);
    updateDragonHorde(dragons);
    updatePlayer(player);
}

// static void render() {
//     renderMap(map);
//     renderGoblinHorde(goblins);
//     renderDragonHorde(dragons);
//     renderPlayer(player);
// }

static void destroy() {
    destroyMap(map);
    destroyGoblinHorde(goblins);
    destroyDragonHorde(dragons);
    destroyPlayer(player);
}