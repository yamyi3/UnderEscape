#pragma once
#include "vivid.h"
#include "character.h"
#include "enemy.h"
#include "stage.h"
#include "gameobject.h"

class GameMain
{
public:
	GameMain(void);
	~GameMain(void) = default;

	void Initialize(void);
	void Update(void);
	void Draw(void);
	void Finalize(void);

private:
	Character character;
	Enemy enemy;
	Stage stage;
	Gameobject gameobject;
};