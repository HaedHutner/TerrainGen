#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "../engine/objects/Camera.h"

#include "../engine/renderers/MasterRenderer.h"
#include "../engine/renderers/CubemapRenderer.h"
#include "../engine/renderers/WorldRenderer.h"
#include "../engine/renderers/AsteroidRenderer.h"

#include "objects/Skybox.h"
#include "objects/World.h"
#include "Log.h"

#define SCREEN_X 800
#define SCREEN_Y 600
#define PROJECT_NAME "Terrain Gen"

namespace Game {

	class Game {

		private:
			static Game* instance;

			bool is_running = true;

			GLFWwindow* window_context;
			Camera* camera;

			MasterRenderer* renderer;

			int screen_x = SCREEN_X;
			int screen_y = SCREEN_Y;

			bool mouse_enabled = true;

		public:

			static Game* get_instance();

			bool init();

			void run();

		private:

			Game();

			void tick();

			void update();

			void close();

			static void process_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

			static void process_mouse(GLFWwindow* window, double x, double y);

			static void process_resize(GLFWwindow* window, int x, int y);

			static void process_key_press(GLFWwindow* window);
	};

#define INSTANCE Game::get_instance()
}