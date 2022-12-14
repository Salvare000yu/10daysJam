#include "Looper.h"

#include "Input.h"

#include "DX12Base.h"
#include "SceneManager.h"

#include <DirectXMath.h>

#include "Object3d.h"

#include "Light.h"
#include "SoundBase.h"

Looper::Looper()
{
	Object3d::staticInit();

	// Soundのクラスより先に消えないようにここで生成しておく
	SoundBase::getInstange();
}

Looper::~Looper()
{
}

bool Looper::loopUpdate()
{
	// 入力情報の更新
	Input::getInstance()->update();

	// ESCで終了
	if (Input::getInstance()->hitKey(DIK_ESCAPE)) return true;

	// --------------------
	// シーンマネージャーの更新
	// --------------------
	SceneManager::getInstange()->update();

	return false;
}

bool Looper::loopDraw()
{
	// --------------------
	// シーンマネージャーの描画
	// --------------------
	PostEffect::getInstance()->startDrawScene(DX12Base::getInstance());
	SceneManager::getInstange()->drawObj3d();
	PostEffect::getInstance()->endDrawScene(DX12Base::getInstance());

	constexpr DirectX::XMFLOAT3 clearColor = { 0.f, 0.f, 0.f };	//黒色
	DX12Base::getInstance()->startDraw(clearColor);

	PostEffect::getInstance()->draw(DX12Base::getInstance());

	SceneManager::getInstange()->drawFrontSprite();

	DX12Base::getInstance()->endDraw();

	return false;
}

bool Looper::loop()
{
	if (loopUpdate()) return true;

	if (loopDraw()) return true;

	return false;
}