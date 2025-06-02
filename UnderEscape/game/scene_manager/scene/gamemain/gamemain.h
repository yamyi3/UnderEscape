#pragma once
#include "vivid.h"
#include"../scene.h"


class GameMainScene : public IScene
{
public:
	GameMainScene(void);
	~GameMainScene(void) = default;

	void Initialize(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Finalize(void)override;

	bool GameFlg() { return true; }

private:
};