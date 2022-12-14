#pragma once
#include "GameScene.h"
#include <memory>

class SceneManager
	: public GameScene
{
public:
	struct Score
	{
		unsigned killEnemyNum = 0u;
	};
	std::unique_ptr<Score> score;

private:
	SceneManager(const SceneManager& sm) = delete;
	SceneManager& operator=(const SceneManager& sm) = delete;
	SceneManager();

	GameScene* nowScene = nullptr;
	GameScene* nextScene = nullptr;

	using UINT = unsigned int;

	UINT postEff2Num = 0U;

public:
	inline UINT getPostEff2Num() { return postEff2Num; }

	inline static SceneManager* getInstange()
	{
		static std::unique_ptr<SceneManager> sm(new SceneManager());
		return sm.get();
	}

	~SceneManager();

	void update() override;
	void drawObj3d() override;
	void drawFrontSprite() override;

	void changeScene(GameScene* nextScene);
};
