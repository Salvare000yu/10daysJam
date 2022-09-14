#pragma once
#include "GameScene.h"

#include "DebugText.h"

#include "Input.h"

#include "ObjSet.h"

#include <memory>

#include <DirectXMath.h>

#include <functional>

class TitleScene :
	public GameScene
{
	// --------------------
	// デバッグテキスト
	// --------------------
	std::unique_ptr<SpriteBase> spCom;
	std::unique_ptr<DebugText> debugText;
	// デバッグテキスト用のテクスチャ番号
	UINT debugTextTexNumber;

	// 3D
	std::unique_ptr<Light> light;
	std::unique_ptr<Camera> camera;
	std::unique_ptr<ObjSet> logoObj;

	Input* input = nullptr;

	// update_何とか関数を格納する
	std::function<void()> update_proc;

	void update_end();
	void update_normal();

public:
	TitleScene();
	void update() override;
	void drawObj3d() override;
	void drawFrontSprite() override;
	void end() override;
};