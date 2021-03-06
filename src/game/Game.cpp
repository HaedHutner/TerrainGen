#include "Game.h"

namespace Game {

	Game* Game::instance;

	Game::Game() {

	}

	Game * Game::get_instance()
	{
		if (!instance) instance = new Game();
		return instance;
	}

	bool Game::init()
	{
		Log::info("Initializing GLFW...");
		if (glfwInit() != GL_TRUE) {
			Log::error("GLFW Failed to initialize. Terminating.");
			glfwTerminate();
			return false;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_SAMPLES, 4);

		window_context = glfwCreateWindow(SCREEN_X, SCREEN_Y, PROJECT_NAME, NULL, NULL);

		glfwMakeContextCurrent(window_context);

		glfwSetCursorPosCallback(window_context, process_mouse);
		glfwSetWindowSizeCallback(window_context, process_resize);
		glfwSetKeyCallback(window_context, process_key_callback);

		Log::info("Initializing GLEW...");
		glewExperimental = GL_TRUE;
		GLenum glewSuccess = glewInit();
		if (glewSuccess != GLEW_OK) {
			Log::error("GLEW Failed to initialize. Terminating.");
			fprintf(stderr, "Error: %s\n", glewGetErrorString(glewSuccess));
			glfwTerminate();
			return false;
		}

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

		Log::info((const char*)glGetString(GL_VERSION));
		Log::info((const char*)glGetString(GL_VENDOR));

		Heightmap* map = new Heightmap( 112412, FastNoise::NoiseType::PerlinFractal, FastNoise::FractalType::FBM, glm::vec3 (0, 0, 0), 0.2f, 7, 4, 128.0f);

		Log::info("Loading Shaders...");
		ShaderProgram heightmapProgram = ShaderProgram::from_files("resources/shaders/heightmap_vertex.shader", "resources/shaders/heightmap_fragment.shader");
		ShaderProgram skyboxProgram = ShaderProgram::from_files("resources/shaders/cubemap_vertex.shader", "resources/shaders/cubemap_fragment.shader");
		ShaderProgram asteroidProgram = ShaderProgram::from_files("resources/shaders/asteroid_vertex.shader", "resources/shaders/asteroid_fragment.shader");
		Log::info("Shaders Loaded.");

		camera = new Camera(120.0f, 5.0f, 0.5f, SCREEN_X, SCREEN_Y, { 0, 128.0f, 0 }, { 0, 0, 0 }, { -89.0f, -89.0f });
		renderer = new MasterRenderer(camera);
		//renderer->add_renderer(new HeightmapRenderer(heightmapProgram, camera, map, { "resources/textures/mars_rock.png", "resources/textures/mars_gravel.png", "resources/textures/mars_grass.png", "resources/textures/mars_sand.png" }));

		World* world = new World(map, glm::ivec2(64,64));

		Light* sun = new Light(glm::vec3(0, 100, 0), glm::vec3(1, 1, 1));
		renderer->add_renderer(new WorldRenderer(world, sun, { "resources/textures/mars_rock.png", "resources/textures/mars_gravel.png", "resources/textures/mars_grass.png", "resources/textures/mars_sand.png" }, camera, heightmapProgram));

		Skybox* skybox = new Skybox({ "resources/textures/skybox_left.png", "resources/textures/skybox_right.png","resources/textures/skybox_top.png","resources/textures/skybox_bottom.png","resources/textures/skybox_back.png","resources/textures/skybox_front.png" });
		renderer->add_renderer(new CubemapRenderer(skyboxProgram, camera, skybox));

		//renderer->add_renderer(new AsteroidRenderer(asteroidProgram, camera));

		return true;
	}

	void Game::run()
	{
		glClearColor(0.0f, 0.5f, 0.5f, 1.0f);

		while (is_running) {
			is_running = !glfwWindowShouldClose(window_context);

			tick();

			update();
		}

		close();
	}

	void Game::tick()
	{
		process_key_press(window_context);
	}

	void Game::update()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderer->render();

		glfwSwapBuffers(window_context);
		glfwPollEvents();
	}

	void Game::close()
	{
		glfwTerminate();
		delete camera;
		delete renderer;
	}

	void Game::process_key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			if (INSTANCE->mouse_enabled) {
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				INSTANCE->camera->reset_cursor( (float) INSTANCE->screen_x / 2, (float) INSTANCE->screen_y / 2);
			}
			else {
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			}
			INSTANCE->mouse_enabled = !INSTANCE->mouse_enabled;
		}
	}

	void Game::process_mouse(GLFWwindow * window, double x, double y)
	{
		if (!INSTANCE->mouse_enabled) {
			INSTANCE->camera->process_mouse_input(window, x, y);
		}

	}

	void Game::process_resize(GLFWwindow * window, int x, int y)
	{
		INSTANCE->screen_x = x;
		INSTANCE->screen_y = y;
		glViewport(0, 0, x, y);
		INSTANCE->camera->update_projection(x, y);
	}

	void Game::process_key_press(GLFWwindow * window)
	{
		INSTANCE->camera->process_key_input(window);
	}

}