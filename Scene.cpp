#include "Scene.h"

Scene::Scene()
{

}


Scene::~Scene()
{

}

bool Scene::init(const char * title, int x, int y, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window = SDL_CreateWindow(title, x, y, width, height, flags);

		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
		}

		running = true;
	}
	else {
		return false;
		running = false;
	}

	mode = build;
	tmove = none;
	ticks_last_down_move = 0;
	ticks_last_move = 0;
	ticks_last_rotate = 0;
	Tetris = std::make_unique<TetrisBoard>(10, 30, renderer);
	travel_mode = std::make_unique<Travel>(renderer);
	travel_mode->createPlayer(5, 2, PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_HITBOX_WIDTH, PLAYER_HITBOX_HEIGHT);
	return true;
}

void Scene::recieve_input()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			running = false;
		}
		switch(mode) {
		case build:
			tetris_input(event);
			break;
		case travel:
			travel_input(event);
			break;
		default:
			break;
		}
	}
}

void Scene::update()
{
	switch (mode) {
	case build:
		if ((tmove == rRight || tmove == rLeft || tmove == drop) && ticks_last_rotate >= ticks_rotate) {
			ticks_last_rotate = 0;
			Tetris->update(tmove);
		}
		if ((tmove == mLeft || tmove == mRight || tmove == mDown) && ticks_last_move >= ticks_move) {
			ticks_last_move = 0;
			Tetris->update(tmove);
		}
		update_ticks();
		break;
	case transistion:
		hitbox_manager = std::make_unique<HitboxManager>(Tetris->get_board());
		Tetris->update(clear);
		mode = travel;
		pmove = none_player;
		travel_mode->handleInput(pmove);
		travel_mode->update();
		break;
	case travel:
		travel_mode->handleInput(pmove);
		hitbox_manager->checkCollisions(travel_mode->player);
		travel_mode->update();
		break;
	default:
		break;
	}
}

void Scene::render()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	switch (mode) {
	case build:
		Tetris->render();
		break;
	case transistion:
		break;
	case travel:
		travel_mode->render(Tetris);
		break;
	default:
		break;
	}
	SDL_RenderPresent(renderer);
}

void Scene::clean()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void Scene::update_ticks()
{
	ticks_tetris++;
	ticks_last_down_move++;
	ticks_last_rotate++;
	ticks_last_move++;
	if (ticks_last_down_move >= ticks_down_move) {
		ticks_last_down_move = 0;
		Tetris->update(autoDown);
	}
	if (ticks_tetris >= TICKS_TETRIS) {
		mode = transistion;
	}
}

void Scene::tetris_input(SDL_Event event)
{
	switch (event.type) {
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_z:
			tmove = rLeft;
			break;
		case SDLK_x:
			tmove = rRight;
			break;
		case SDLK_LEFT:
			tmove = mLeft;
			break;
		case SDLK_RIGHT:
			tmove = mRight;
			break;
		case SDLK_DOWN:
			tmove = mDown;
			break;
		case SDLK_SPACE:
			tmove = drop;
			break;
		default:
			break;
		}
		break;
	case SDL_KEYUP:
		tmove = none;
		break;
	default:
		break;
	}
}

void Scene::travel_input(SDL_Event event)
{
	switch (event.type) {
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_LEFT:
			pmove = left_player;
			break;
		case SDLK_RIGHT:
			pmove = right_player;
			break;
		case SDLK_UP:
			pmove = up_player;
			break;
		default:
			break;
		}
		break;
	case SDL_KEYUP:
		pmove = none_player;
		break;
	default:
		break;
	}
}

