#pragma once
#include "GameScene.h"
#include "Input.h"
#include "DebugText.h"

/// @brief 失敗したときのシーン
class GameOverScene :
	public GameScene
{
private:
	Input* input = nullptr;

	std::unique_ptr<SpriteBase> spBase;

	std::unique_ptr<DebugText> debugText;

public:
	GameOverScene();

	void update() override;

	void drawObj3d() override;

	void drawFrontSprite() override;
};

