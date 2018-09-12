#include <SDL.h>

typedef struct Texture {
	int   w;
	int   h;
	float x;
	int   y;
	float vel;
	SDL_Texture *texture;
} Texture;

Texture player;
Texture chao;
Texture montanhas;
Texture montanhas2;
Texture nuvens;
Texture sol;

SDL_bool running = SDL_TRUE;
SDL_Event event;

SDL_Window *window     = NULL;
SDL_Renderer *renderer = NULL;

Texture createTexture(char *path, float vel)
{
	Texture texture;

	SDL_Surface *bitmap = SDL_LoadBMP(path);

	SDL_SetColorKey(bitmap, SDL_TRUE, SDL_MapRGB(bitmap->format, 0, 255, 255));

	texture.texture = SDL_CreateTextureFromSurface(renderer, bitmap);

	texture.w = bitmap->w;
	texture.h = bitmap->h;
	texture.x = 0;
	texture.y = 0;

	texture.vel = vel;

	SDL_FreeSurface(bitmap);

	return texture;
}

void drawTexture(Texture* texture) {
	SDL_Rect rect = {(int) texture->x, texture->y, texture->w, texture->h};

	SDL_RenderCopy(renderer, texture->texture, NULL, &rect);

	rect.x += texture->w;

	SDL_RenderCopy(renderer, texture->texture, NULL, &rect);
}

void moveTexture(Texture *texture)
{
	texture->x -= texture->vel;

	if (texture->x < -texture->w)
		texture->x = 0;
}

void movePlayer(Texture *texture)
{
	static float frame = 0;
	static const SDL_Rect position = {300, 350, 48, 37};
	static const SDL_Rect parts[5]  = {
		{  0, 0, 48, 37},
		{ 48, 0, 48, 37},
		{ 96, 0, 48, 37},
		{144, 0, 48, 37},
		{152, 0, 48, 37}
	};

	frame = (frame / 4 > 4) ? 0 : ++frame;

	SDL_RenderCopy(renderer, player.texture, &parts[(int)frame / 5], &position);
}

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	window   = SDL_CreateWindow("Test", 50, 50, 640, 480, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

	chao       = createTexture("images/chao.bmp", 15);
	montanhas  = createTexture("images/montanhas.bmp", 8);
	montanhas2 = createTexture("images/montanhas2.bmp", 5);
	nuvens     = createTexture("images/nuvens.bmp", 1);
	sol        = createTexture("images/sol.bmp", 0.5f);
	player     = createTexture("images/player.bmp", 0);

	while (running) {
		while (SDL_PollEvent(&event))
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
				running = SDL_FALSE;

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		drawTexture(&sol);
		drawTexture(&nuvens);
		drawTexture(&montanhas2);
		drawTexture(&montanhas);
		drawTexture(&chao);

		moveTexture(&sol);
		moveTexture(&nuvens);
		moveTexture(&montanhas2);
		moveTexture(&montanhas);
		moveTexture(&chao);

		movePlayer(&player);

		SDL_RenderPresent(renderer);
	}

	return 0;
}