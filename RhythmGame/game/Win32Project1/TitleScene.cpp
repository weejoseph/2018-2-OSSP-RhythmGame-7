#include "GameSystem.h"
#include "Sprite.h"
#include "SceneManager.h"

#include "TitleScene.h"


TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{
	_backgroundSprite = new Sprite("backgroundspr", true);
	_backgroundSprite->SetPosition(GameSystem::GetInstance()->GetWindowWidth() / 2,
		GameSystem::GetInstance()->GetWindowHeight() / 2);
}

void TitleScene::Deinit()
{
	delete _backgroundSprite;
}

void TitleScene::Update(int deltaTime)
{
	_backgroundSprite->Update(deltaTime);
}

void TitleScene::Render()
{
	_backgroundSprite->Render();
}

void TitleScene::KeyUp(unsigned int keyCode)
{
	switch (keyCode)
	{
	case SDLK_SPACE:
		SceneManager::GetInstance()->ChangeScene(eScene::SCENE_GAME);
		break;
	default:
		break;
	}
}

void TitleScene::KeyDown(unsigned int keyCode)
{
}
