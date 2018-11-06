#include "GameSystem.h"
#include "Sprite.h"
#include "SceneManager.h"

#include "LogoScene.h"


LogoScene::LogoScene()
{
}

LogoScene::~LogoScene()
{
}

void LogoScene::Init()
{
	_backgroundSprite = new Sprite("backgroundspr", true);
	_backgroundSprite->SetPosition(GameSystem::GetInstance()->GetWindowWidth() / 2,
		GameSystem::GetInstance()->GetWindowHeight() / 2);

	_waitTick = 3 * 1000;
	_updateTick = 0;
}

void LogoScene::Deinit()
{
	delete _backgroundSprite;
}

void LogoScene::Update(int deltaTime)
{
	_backgroundSprite->Update(deltaTime);

	if (_waitTick < _updateTick)
	{
		SceneManager::GetInstance()->ChangeScene(eScene::SCENE_TITLE);
	}
	_updateTick += deltaTime;
}

void LogoScene::Render()
{
	_backgroundSprite->Render();
}

void LogoScene::KeyUp(unsigned int keyCode)
{
	switch (keyCode)
	{
	case SDLK_SPACE:
		SceneManager::GetInstance()->ChangeScene(eScene::SCENE_TITLE);
		break;
	default:
		break;
	}
}

void LogoScene::KeyDown(unsigned int keyCode)
{
}
