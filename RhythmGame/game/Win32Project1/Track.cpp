#include <stdio.h>
#include <stdlib.h>

#include "GameSystem.h"
#include "Note.h"
#include "Sprite.h"

#include "Track.h"

Track::Track()
{
	_backgroundSprite = NULL;
	_judgeLineSprite = NULL;
	_isKeyDown = false;
	_combo = 0;
	_maxCombo = 0;
}

Track::~Track()
{
	if (NULL != _backgroundSprite)
	{
		delete _backgroundSprite;
		_backgroundSprite = NULL;
	}

	if (NULL != _judgeLineSprite)
	{
		delete _judgeLineSprite;
		_judgeLineSprite = NULL;
	}

	if (NULL != _explosionSprite)
	{
		delete _explosionSprite;
		_explosionSprite = NULL;
	}

	if (NULL != _failEffectSprite)
	{
		delete _failEffectSprite;
		_failEffectSprite = NULL;
	}
}

void Track::Init(int x)
{
	int judgeLineOffset = 100;

	_backgroundSprite = new Sprite("trackspr", true);
	_backgroundSprite->SetPosition(x, GameSystem::GetInstance()->GetWindowHeight() / 2);

	_judgeLineSprite = new Sprite("judgelinespr", true);
	_judgeLineSprite->SetPosition(x, GameSystem::GetInstance()->GetWindowHeight() - judgeLineOffset);

	_explosionSprite = new Sprite("successeffectspr", false);
	_explosionSprite->SetPosition(x, GameSystem::GetInstance()->GetWindowHeight() - judgeLineOffset);
	
	_failEffectSprite = new Sprite("faileffectspr", false);
	_failEffectSprite->SetPosition(x, GameSystem::GetInstance()->GetWindowHeight() / 2);


	float totalPlayingSec = GameSystem::GetInstance()->GetTotalPlayingTime() / 1000.0f;
	float startNoteSec = 1.0f;
	while (startNoteSec < totalPlayingSec)
	{
		Note*	note = new Note(startNoteSec, judgeLineOffset, x);
		_noteList.Append(note);

		int randVal = rand() % 3;
		switch (randVal)
		{
		case 0:
			startNoteSec += 0.25f;
			break;
		case 1:
			startNoteSec += 0.5f;
			break;
		case 2:
			startNoteSec += 0.75f;
			break;
		case 3:
			startNoteSec += 1.0f;
			break;
		}
	}

	_score = 0;

	int judgeTick = GameSystem::GetInstance()->GetTotalPlayingTime();
	_judgeStartTick = judgeTick - 100;
	_judgeEndTick = judgeTick + 100;
}

void Track::Update(int deltaTime)
{
	_backgroundSprite->Update(deltaTime);
	_judgeLineSprite->Update(deltaTime);

	DLinkedListIterator<Note*> itr = _noteList.GetIterator();
	for (itr.begin(); itr.valid(); itr.forth())
	{
		Note* note = itr.item();
		if (note->IsLive())
		{
			note->Update(deltaTime);

			if (_judgeEndTick < note->GetCurrentTime() && false == note->IsPassed())
			{
				note->Passed();
				printf("Fail Effect\n");
				_failEffectSprite->Play();
				_combo = 0;
			}
		}
	}

	_explosionSprite->Update(deltaTime);
	_failEffectSprite->Update(deltaTime);
}

void Track::Render()
{
	_backgroundSprite->Render();
	_judgeLineSprite->Render();

	DLinkedListIterator<Note*> itr = _noteList.GetIterator();
	for (itr.begin(); itr.valid(); itr.forth())
	{
		itr.item()->Render();
	}

	_explosionSprite->Render();
	_failEffectSprite->Render();
}

void Track::Deinit()
{
	if (NULL != _backgroundSprite)
	{
		delete _backgroundSprite;
		_backgroundSprite = NULL;
	}

	if (NULL != _judgeLineSprite)
	{
		delete _judgeLineSprite;
		_judgeLineSprite = NULL;
	}

	if (NULL != _explosionSprite)
	{
		delete _explosionSprite;
		_explosionSprite = NULL;
	}

	if (NULL != _failEffectSprite)
	{
		delete _failEffectSprite;
		_failEffectSprite = NULL;
	}

	DLinkedListIterator<Note*> itr = _noteList.GetIterator();
	for (itr.begin(); itr.valid(); itr.forth())
	{
		delete itr.item();
		_noteList.Remove(itr);
	}
}

void Track::KeyDown()
{
	if (true ==_isKeyDown)
		return;
	_isKeyDown = true;

	bool isJudge = false;
	DLinkedListIterator<Note*> itr = _noteList.GetIterator();
	for (itr.begin(); itr.valid(); itr.forth())
	{
		Note* note = itr.item();

		if (false == note->IsLive())
		{
			continue;
		}

		if (note->IsPassed())
		{
			continue;
		}

		if (note->GetCurrentTime() < _judgeStartTick)
		{
			break;
		}

		if (_judgeStartTick <= note->GetCurrentTime() && note->GetCurrentTime() <= _judgeEndTick)
		{
			isJudge = true;
			break;
		}
	}

	if (isJudge)
	{
		printf("Success Effect\n");
		_explosionSprite->Play();
		_score += 100;
		_combo++;
		itr.item()->SetLive(false);
		if (_combo >= _maxCombo) {
			_maxCombo = _combo;
			Track::SetCombo(_maxCombo);
		}
	}
	else
	{
		_combo = 0;
	}
}

void Track::KeyUp()
{
	_isKeyDown = false;
}
