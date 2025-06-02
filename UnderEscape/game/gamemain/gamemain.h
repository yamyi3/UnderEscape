#pragma once
#include "vivid.h"
#include "character/character.h"
#include "enemy/enemy.h"
#include "stage/stage.h"
#include "gameobject/gameobject.h"

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