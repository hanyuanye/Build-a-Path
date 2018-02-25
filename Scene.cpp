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
	TTF_Init();

	mode = build;
	tmove = none;
	ticks_last_down_move = 0;
	ticks_last_move = 0;
	ticks_last_rotate = 0;
	std::vector<Vec2d> goal;
	goal.push_back(Vec2d(10, 20));
	std::vector<Vec2d> spike;
	spike.push_back(Vec2d(5, 11));
	Tetris = std::make_unique<TetrisBoard>(20, 30, renderer, goal, spike);
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
		bool updated;
		if ((tmove == rRight || tmove == rLeft || tmove == drop) && ticks_last_rotate >= ticks_rotate) {
			ticks_last_rotate = 0;
			updated = Tetris->update(tmove);
		}
		if ((tmove == mLeft || tmove == mRight || tmove == mDown) && ticks_last_move >= ticks_move) {
			ticks_last_move = 0;
			updated = Tetris->update(tmove);
		}
		update_ticks();
		if (!updated) {
			mode = transistion;
		}
		break;
	case transistion:
		hitbox_manager = std::make_unique<HitboxManager>(Tetris->get_board());
		mode = travel;
		pmove = none_player;
		break;
	case travel:
		travel_mode->handleInput(pmove);
		switch (travel_mode->update(hitbox_manager)) {
		case game_ongoing:
			break;
		case game_won:
			mode = result_screen_won;
			break;
		case game_lost:
			mode = result_screen_lost;
			break;
		default:
			break;
		}
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
	case result_screen_won:
		travel_mode->render(Tetris);
		renderResultScreenWon();
		break;
	case result_screen_lost:
		travel_mode->render(Tetris);
		renderResultScreenLost();
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
		Tetris->update(clear);
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

void Scene::renderResultScreenWon()
{
	std::string game_over_string = "Game Won!";
	TTF_Font* game_over_font = TTF_OpenFont("arial.ttf", 35);
	SDL_Color text_color = { 255, 255, 255 };
	SDL_Surface* surface_font = TTF_RenderText_Solid(game_over_font, game_over_string.c_str(), text_color);
	SDL_Texture* texture_font = SDL_CreateTextureFromSurface(renderer, surface_font);
	SDL_Rect rect = { 75, 300, surface_font->w, surface_font->h };

	SDL_RenderCopy(renderer, texture_font, NULL, &rect);
	TTF_CloseFont(game_over_font);
	SDL_FreeSurface(surface_font);
	SDL_DestroyTexture(texture_font);
	SDL_RenderPresent(renderer);
}

void Scene::renderResultScreenLost()
{
	std::string game_over_string = "Game Lost!";
	TTF_Font* game_over_font = TTF_OpenFont("arial.ttf", 35);
	SDL_Color text_color = { 255, 255, 255 };
	SDL_Surface* surface_font = TTF_RenderText_Solid(game_over_font, game_over_string.c_str(), text_color);
	SDL_Texture* texture_font = SDL_CreateTextureFromSurface(renderer, surface_font);
	SDL_Rect rect = { 75, 300, surface_font->w, surface_font->h };

	SDL_RenderCopy(renderer, texture_font, NULL, &rect);
	TTF_CloseFont(game_over_font);
	SDL_FreeSurface(surface_font);
	SDL_DestroyTexture(texture_font);
	SDL_RenderPresent(renderer);
}

