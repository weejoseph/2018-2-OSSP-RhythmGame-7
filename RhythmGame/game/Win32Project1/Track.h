#pragma once

#include "DLinkedList.h"

class Sprite;
class Note;

class Track
{
private:
	DLinkedList<Note*> _noteList;
	Sprite* _backgroundSprite;
	Sprite* _judgeLineSprite;
	Sprite* _explosionSprite;
	Sprite* _failEffectSprite;

	int _judgeStartTick;
	int _judgeEndTick;

	int _score;
	int _combo;
	int _maxCombo;

public:
	Track();
	~Track();

	void Init(int x);
	void Update(int deltaTime);
	void Render();
	void Deinit();

	int GetScore() { return _score;  }
	int GetCombo() { return _combo; }
	void SetCombo(int combo) { _combo = combo; }

	// Input
private:
	bool _isKeyDown;

public:
	void KeyDown();
	void KeyUp();
};