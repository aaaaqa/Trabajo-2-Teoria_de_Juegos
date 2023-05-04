#include "MainGame.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Error.h"
using namespace std;

MainGame::MainGame() {
	window = nullptr;
	width = 800;
	height = 600;
	gameState = GameState::PLAY;
	counter = 0;
}

MainGame::~MainGame() {

}
void MainGame::processInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
			case SDL_QUIT:
				gameState = GameState::EXIT;
				break;
			case SDL_MOUSEMOTION:
				//cout << event.motion.x << " , " << event.motion.y << endl;
				break;
		}
	}
}

void MainGame::init() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Hola", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
			width, height, SDL_WINDOW_OPENGL);
	
	if (window == nullptr) {
		fatalError("SDL not initialized");
	}
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		fatalError("Glew not initialized");
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
}

void MainGame::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	sprite.draw();
	//si tengo elementos actualizo
	SDL_GL_SwapWindow(window);
}

void MainGame::run() {
	init();
	update();
}

void MainGame::update() {
	while (gameState != GameState::EXIT) {
		if (counter % 1 == 0) {
			srand(static_cast <unsigned> (time(0)));
			float LO = 0.1;
			float HI = 0.3;
			float l = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
			float x = -1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1-(-1)-l)));
			float y = -1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1-(-1)-l)));
			sprite.init(x, y, l, l);
		}
		draw();
		processInput();
	}
}