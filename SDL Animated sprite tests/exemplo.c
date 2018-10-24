struct SpriteSheet {
    SDL_Texture* texture;
    int quantRegions;
    SDL_Rect* regions;
};

struct Sprite {
    SpriteSheet* sheet;
    int region;
    double angle;
    SDL_Point position;
    SDL_Point scale;
    SDL_Point center;
    SDL_RendererFlip flip;
};

struct AnimatedSprite {
    Sprite* sprite;
    int quantAnimations;
    int currentAnimation;
    Animation* animations;
};

struct Animation {
    float speed;
    int currentFrame;
    int quantFrames;
    int* frames;
};

Animation* getCurrentAnimationPointer(AnimatedSprite* sprite) {
    return &sprite->animations[ sprite->currentAnimation ];
}

int getCurrentAnimation(AnimatedSprite* sprite) {
    return sprite->currentAnimation;
}

Animation* getAnimation(AnimatedSprite* sprite, int animationIndex) {
    return &sprite->animations[ animationIndex ];
}

int main(int argc, char const *argv[]) {
    int image = loadImage("path.jpg");

    SpriteSheet* sheet = createSpriteSheet("/path/to/image.jpg");
    Sprite* player = createSprite(sheet, 0);

    AnimatedSprite* player = createAnimatedSprite(sheet, 3);
    int playerWalk = createAnimation(player, 4, 1.0, 0, 1, 2, 3);
    int playerJump = createAnimation(player, 5, 1.0, 4, 5, 6, 7, 8);
    int playerAttack = createAnimation(player, 4, 1.5, 9, 10, 11, 12);

    playAnimation(player, playerWalk);

    return 0;
}
