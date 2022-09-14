#pragma once

#include "GameScene.h"
#include "CameraObj.h"
#include <memory>

#include "Player.h"
#include "ObjSet.h"
#include "Light.h"

#include "Time.h"

#include "Input.h"

#include <functional>

#include "DebugText.h"

#include "Enemy.h"

#include "ParticleMgr.h"

#include "Sound.h"

class RailShoot
	: public GameScene
{
	DX12Base* dxBase = nullptr;
	Input* input = nullptr;

	std::unique_ptr<CameraObj> camera;

	std::unique_ptr<Light> light;

	std::unique_ptr<Time> timer;

	std::unique_ptr<Sound> bgm;

	std::unique_ptr<Sound> particleSE;
	bool playBgmFlag = false;

	// --------------------
	// スプライト
	// --------------------
	std::unique_ptr<SpriteBase> spriteBase;
	std::unique_ptr<DebugText> debugText;

	std::unique_ptr<Sprite> aim2D;

	// --------------------
	// 3Dオブジェクト
	// --------------------
	// 背景のパイプライン
	Object3d::PipelineSet backPipelineSet;

	// 背景と地面
	std::unique_ptr<ObjSet> back;
	std::unique_ptr<ObjSet> ground;

	// 敵
	std::forward_list<std::unique_ptr<Enemy>> enemy;
	std::unique_ptr<ObjModel> enemyModel;
	std::unique_ptr<ObjModel> snailModel;
	std::unique_ptr<ObjModel> enemy2Model;
	std::unique_ptr<ObjModel> enemyBulModel;

	// 自機
	std::unique_ptr<Player> player;
	std::unique_ptr<ObjModel> playerModel;
	std::unique_ptr<ObjModel> playerBulModel;
	UINT playerHp;

	// レールの現在位置を示すオブジェクト
	std::unique_ptr<GameObj> railObj;

	// --------------------
	// パーティクル
	// --------------------
	std::unique_ptr<ParticleMgr> particleMgr;

	// --------------------
	// シーン遷移
	// --------------------
	static const Time::timeType sceneChangeTime;

	Time::timeType startSceneChangeTime{};
	// --------------------
	// スプライン補間
	// --------------------
	std::vector<DirectX::XMVECTOR> splinePoint;
	UINT splineNowFrame = 0u;
	static const UINT splineFrameMax = 120u;
	static const UINT splineIndexDef = 1u;
	UINT splineIndex = splineIndexDef;

	// --------------------
	// プレイ結果
	// --------------------

	UINT killEnemyNum = 0u;

	/// @brief プレイ結果
	enum class PLAY_RESULT : uint8_t
	{
		UNDEF,	// 未定義
		CLEAR,	// 成功
		FAILED	// 失敗
	};
	PLAY_RESULT playResult = PLAY_RESULT::UNDEF;

	// --------------------
	// 敵発生制御
	// --------------------

	// std::stringの2次元配列(vector)
	using CSVType = std::vector<std::vector<std::string>>;

	// 敵発生スクリプトのCSVデータ
	CSVType csvData;

	CSVType loadCsv(const std::string& csvFilePath,
					bool commentFlag = true,
					char divChar = ',',
					const std::string& commentStartStr = "//");

	struct PushEnemyData
	{
		UINT popTime = 0u;
		DirectX::XMFLOAT3 pos{ 0,0,0 };
		DirectX::XMFLOAT3 vel{ 0,0,-1 };
	};

	std::forward_list<std::unique_ptr<PushEnemyData>> enemyPopData;

	struct MusicData
	{
		float bpm = 120.f;
		float startDiffBeatCount = 0;
	};
	std::unique_ptr<MusicData> musicData;
	float oneBeatTime = Time::oneSecF / 2.f;


	class ElapsedTime
	{
	private:
		Time::timeType startTime{};
		Time::timeType nowTime{};

		Time* timer = nullptr;

	public:
		ElapsedTime(Time* timer)
			: timer(timer), startTime(0), nowTime(0)
		{
		}

		inline const Time::timeType& getNowTime() { return nowTime; }
		inline const Time::timeType& getStartTime() { return startTime; }

		void start(Time::timeType startDiffBeatCount = 0)
		{
			startTime = timer->getNowTime() + startDiffBeatCount;
		}
		void update()
		{
			nowTime = timer->getNowTime() - startTime;
		}
	};
	std::unique_ptr<ElapsedTime> musicTimer;

	void createParticle(const DirectX::XMFLOAT3& pos,
						const UINT particleNum = 10U,
						const float startScale = 1.f,
						const float vel = 5.f);

	void addEnemy(const DirectX::XMFLOAT3& pos, const DirectX::XMFLOAT3& vel, float scale = 5.f);

	void changeNextScene();
	void changeGameOverScene();

	// update_何とか関数を格納する
	std::function<void()> update_proc;

	void update_start();
	void update_play();
	void update_end();

public:
	RailShoot();

	void start() override;
	void update() override;
	void drawObj3d() override;
	void drawFrontSprite() override;
	void end() override;

	~RailShoot();

	static DirectX::XMVECTOR splinePosition(const std::vector<DirectX::XMVECTOR>& points,
											size_t startIndex,
											float t);
};
