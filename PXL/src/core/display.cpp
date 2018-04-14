#include "display.h"

Display::Display(Uint32 width, Uint32 height, const std::string& title, const std::string& icon)
{
	m_size = glm::vec2(width, height);
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 1);

	m_window = SDL_CreateWindow(
		title.c_str(), 
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width, height,
		SDL_WINDOW_OPENGL		  |
		SDL_WINDOW_RESIZABLE	  | 
		SDL_RENDERER_ACCELERATED  |
		SDL_WINDOW_MAXIMIZED
	);

	addIcon(icon);
	m_glContext = SDL_GL_CreateContext(m_window);	

	// Vsync
	SDL_GL_SetSwapInterval(-1);

	if (glewInit() != GLEW_OK)
		std::cerr << "Glew failed to initialize!" << std::endl;
	else 
		m_isClosed = false;

	m_cursors["IBEAM"] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_IBEAM);
	m_cursors["ARROW"] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	m_cursors["HAND"] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	SDL_SetCursor(m_cursors["ARROW"]);

	SDL_ShowCursor(SDL_ENABLE);
}

bool Display::isClosed()
{
	return m_isClosed;
}

void Display::clear(const glm::vec4& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Display::swapBuffers()
{
	SDL_GL_SwapWindow(m_window);
}

bool Display::addIcon(const std::string& filename)
{
	int req_format = 4;
	int depth, pitch;
	Uint32 pixel_format;
	Uint32 rmask, gmask, bmask, amask;
	int iconWidth, iconHeight, numComponents;
	unsigned char* iconData = stbi_load(filename.c_str(), &iconWidth, &iconHeight, &numComponents, req_format);

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
		amask = (req_format == 3) ? 0 : 0xff000000;
	#endif

	if (req_format == 3) {
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

	if (icon == NULL)
	{
		SDL_Log("Creating window icon surface failed: %s", SDL_GetError());
		stbi_image_free(iconData);
		return false;
	}

	SDL_FreeSurface(icon);
	stbi_image_free(iconData);

	return true;
}

Display::~Display()
{
	SDL_GL_DeleteContext(m_glContext);
	SDL_FreeCursor(SDL_GetCursor());
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}
