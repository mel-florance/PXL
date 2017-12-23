#include "display.h"
#include <iostream>
#include <GL/glew.h>
#include "stb_image.h"

Display::Display(float width, float height, const std::string & title)
{
	m_width = width;
	m_height = height;

	SDL_Init(SDL_INIT_EVERYTHING);
	
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

	m_window = SDL_CreateWindow(
		title.c_str(), 
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width, height,
		SDL_WINDOW_OPENGL
	);

	int req_format = STBI_rgb_alpha;
	int iconWidth, iconHeight, numComponents;
	unsigned char* iconData = stbi_load("./res/textures/icon.png", &iconWidth, &iconHeight, &numComponents, req_format);

	Uint32 rmask, gmask, bmask, amask;
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		int shift = (req_format == STBI_rgb) ? 8 : 0;
		rmask = 0xff000000 >> shift;
		gmask = 0x00ff0000 >> shift;
		bmask = 0x0000ff00 >> shift;
		amask = 0x000000ff >> shift;
	#else
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		amask = (req_format == STBI_rgb) ? 0 : 0xff000000;
	#endif

	int depth, pitch;
	Uint32 pixel_format;
	if (req_format == STBI_rgb) {
		depth = 24;
		pitch = 3 * iconWidth;
		pixel_format = SDL_PIXELFORMAT_RGB24;
	}
	else {
		depth = 32;
		pitch = 4 * iconWidth;
		pixel_format = SDL_PIXELFORMAT_RGBA32;
	}


	SDL_Surface* icon = SDL_CreateRGBSurfaceFrom((void*)iconData, iconWidth, iconHeight, depth, pitch, rmask, gmask, bmask, amask);
	SDL_SetWindowIcon(m_window, icon);

	if (icon == NULL) {
		SDL_Log("Creating window icon surface failed: %s", SDL_GetError());
		stbi_image_free(iconData);
		exit(1);
	}

	SDL_FreeSurface(icon);
	stbi_image_free(iconData);

	m_glContext = SDL_GL_CreateContext(m_window);

	GLenum status = glewInit();

	if (status != GLEW_OK) {
		std::cerr << "Glew failed to initialize!" << std::endl;
	}

	m_isClosed = false;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}


bool Display::isClosed()
{
	return m_isClosed;
}

void Display::clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::swapBuffers()
{
	SDL_GL_SwapWindow(m_window);
	
	SDL_Event e;
	
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			m_isClosed = true;
		}
	}
}

Display::~Display()
{
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

