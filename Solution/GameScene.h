#pragma once

/// @brief ゲームシーンの基底クラス。すべてのシーンはこのクラスを継承して作る
class GameScene
{
public:
	/// @brief 開始時に呼ばれる関数。実装は任意。
	virtual void start() {};

	/// @brief ゲームループない更新処理。実装必須。
	virtual void update() = 0;

	/// @brief ゲームループ内描画処理。ポストエフェクトがかかる。実装は任意
	virtual void drawObj3d() {};

	/// @brief ゲームループ内前景スプライト描画処理。ポストエフェクトがかからない。実装は任意
	virtual void drawFrontSprite() {};

	/// @brief 終了時に呼ばれる関数。実装は任意
	virtual void end() {};
};
