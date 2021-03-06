#pragma region system include
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#pragma endregion

#pragma region project include
#include "Engine.h"
#include "Renderer.h"
#include "ContentManagement.h"
#include "TextureManagement.h"
#include "Game.h"
#include "Scene.h"
#include "Input.h"
#include "Time.h"
#pragma endregion

#pragma region constructor
CEngine::CEngine()
{
}

CEngine::~CEngine()
{
}
#pragma endregion

#pragma region public function
// initialize sdl
bool CEngine::Init()
{
	// initialize sdl
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		// error message
		LOG_ERROR("SDL not initialized!", SDL_GetError());

		return false;
	}

	// sdl initialized
	else
	{
		// create window
		m_pWindow = SDL_CreateWindow(
			"World of Facades",			// name of window
			SDL_WINDOWPOS_CENTERED,		// position x of screen
			SDL_WINDOWPOS_CENTERED,		// position y of screen
			SCREEN_WIDTH,				// width
			SCREEN_HEIGHT,				// height
			SDL_WINDOW_SHOWN);			// flags

		// if window not created
		if (!m_pWindow)
		{
			// error message
			LOG_ERROR("Window could not be created!", SDL_GetError());

			return false;
		}

		// get surface from window
		m_pSurface = SDL_GetWindowSurface(m_pWindow);

		// if surface not created
		if (!m_pSurface)
		{
			// error message
			LOG_ERROR("Surface could not be created!", SDL_GetError());

			return false;
		}

		// initialize renderer
		m_pRenderer = new CRenderer(m_pWindow);

		// if renderer not created
		if (!m_pRenderer)
		{
			// error message
			LOG_ERROR("Renderer could not be created!", SDL_GetError());

			return false;
		}

		// initialize font
		if (TTF_Init() < 0)
		{
			// error message
			LOG_ERROR("Font could not be created!", SDL_GetError());

			return false;
		}

		// initialize audio
		if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
		{
			// error message
			LOG_ERROR("Audio could not be created!", SDL_GetError());

			return false;
		}

		// create content management system
		m_pCM = new CContentManagement();

		// if content management system not created
		if (!m_pCM)
		{
			// error message
			LOG_ERROR("Content Management System could not be created!", SDL_GetError());

			return false;
		}

		// create texture managemant system
		m_pTM = new CTextureManagement();

		// if texture management could not be created
		if (!m_pTM)
		{
			// error message
			LOG_ERROR("Texture Management System could not be created!", "");

			return false;
		}

		// create time
		m_pTime = new CTime();

		// if time not created
		if (!m_pTime)
		{
			// error message
			LOG_ERROR("Time could not be created!", SDL_GetError());

			return false;
		}

		// engine is running
		m_isRunning = true;

		return true;
	}
}

// load content
bool CEngine::Load()
{
	// create game
	GGame::Get()->Init();

	return true;
}

// running engine
void CEngine::Run()
{
	// as long as engine running
	while (m_isRunning)
	{
		clock_t checkTime = clock();

		Update();

		double updateTime = (clock() - checkTime) / (double)CLOCKS_PER_SEC;

		checkTime = clock();

		Render();

		double renderTime = (clock() - checkTime) / (double)CLOCKS_PER_SEC;

		if (updateTime + renderTime > 1.0f / 40)
		{
			LOG_MESSAGE("Update: ", updateTime);
			LOG_MESSAGE("Render: ", renderTime);
			LOG_MESSAGE("","---");

		}

	}
}

// cleaning up
void CEngine::Clean()
{
	// clean current scene
	if (m_pScene)
		m_pScene->Clean();

	// delete scene
	delete m_pScene;

	// delete game
	delete GGame::Get();

	// delete time
	delete m_pTime;

	// delete content management
	delete m_pCM;

	// delete texture management
	delete m_pTM;

	// delete renderer
	delete m_pRenderer;

	// free sdl components
	// check if exists
	if (m_pSurface != nullptr)
	{
		SDL_FreeSurface(m_pSurface);

	}
	// check if window exists
	if (m_pWindow != nullptr)
	{
		SDL_DestroyWindow(m_pWindow);

	}
}

// change active scene
void CEngine::ChangeScene(CScene * _pScene)
{
	// if new scene nullptr return
	if (!_pScene)
		return;

	// if old scene valid
	if (m_pScene)
	{
		// clean and delete scene
		m_pScene->Clean();
		delete m_pScene;
	}

	// set new scene
	m_pScene = _pScene;

	// initialize new scene
	m_pScene->Init();
}
#pragma endregion

#pragma region private function
// update every frame
void CEngine::Update()
{
	// update time
	m_pTime->Update();

	// refresh input state
	CInput::RefreshState();

	// create sdl event
	SDL_Event e;

	// while getting event
	while (SDL_PollEvent(&e))
	{
		// if event quit set running false
		if (e.type == SDL_EventType::SDL_QUIT)
			m_isRunning = false;

		// parse event to input class
		if (e.type == SDL_EventType::SDL_KEYDOWN || e.type == SDL_EventType::SDL_KEYUP)
			CInput::ParseEvent(e);
	}

	// update content
	m_pCM->Update(m_pTime->GetDeltaTime());


}

// render every frame
void CEngine::Render()
{

	// clear current screen
	m_pRenderer->ClearScreen();

	// render content
	m_pCM->Render(m_pRenderer);

	// present rendered image
	m_pRenderer->Present();


}
#pragma endregion