#pragma once

#include "Scene.h"

class Sprite;

class TitleScene : public Scene
{
private:
	//Sprite* _backgroundSprite;

public:
	TitleScene();
	~TitleScene();

	void Init();
	void Deinit();
	void Update(int deltaTime);
	void Render();

	void KeyUp(unsigned int keyCode);
	void KeyDown(unsigned int keyCode);
};
