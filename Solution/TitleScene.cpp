#include "TitleScene.h"

#include "SceneManager.h"

#include "WinAPI.h"

#include "PlayScene.h"
#include "RailShoot.h"

#include "PostEffect.h"

using namespace DirectX;

TitleScene::TitleScene()
	: light(new Light()),
	camera(new Camera({ .x = WinAPI::window_width, .y = WinAPI::window_height })),
	logoObj(new ObjSet(camera.get(), "Resources/logo", "logo")),
	update_proc(std::bind(&TitleScene::update_normal, this))
{
	input = Input::getInstance();

	spCom.reset(new SpriteBase());

	// デバッグテキスト用のテクスチャ読み込み
	debugTextTexNumber = spCom->loadTexture(L"Resources/debugfont.png");

	debugText.reset(new DebugText(debugTextTexNumber, spCom.get()));

	// カメラ初期化
	camera->setTarget(XMFLOAT3(0, 0, 0));
	camera->setUp(XMFLOAT3(0, 1, 0));
	{
		XMFLOAT3 eye = camera->getTarget();
		eye.z -= 10.f;
		camera->setEye(eye);
		camera->update();
	}

	// 3D
	light->setLightPos(XMFLOAT3(0, 0, 0));

	logoObj->setPos(camera->getTarget());
	constexpr float logoScale = 5.f;
	logoObj->setScale(XMFLOAT3(logoScale, logoScale, logoScale));
	logoObj->setRotation(XMFLOAT3(0, 180, 0));

	PostEffect::getInstance()->changePipeLine(1U);
}

void TitleScene::update()
{
	update_proc();

	constexpr XMFLOAT2 strPos = XMFLOAT2(DebugText::fontWidth * 1.5f, WinAPI::window_height - DebugText::fontHeight * 1.5f);
	debugText->Print(spCom.get(), "Press SPACE...", strPos.x, strPos.y, 1.f);

	light->update();
}

void TitleScene::update_normal()
{
	if (input->triggerKey(DIK_SPACE))
	{
		update_proc = std::bind(&TitleScene::update_end, this);
	}
}

void TitleScene::update_end()
{
	{
		constexpr float speed = 0.2f;

		XMFLOAT3 logoPos = logoObj->getPos();
		logoPos.y -= speed;
		logoObj->setPos(logoPos);

		constexpr float endLine = -10.f;
		if (logoPos.y <= endLine)
		{
			SceneManager::getInstange()->changeScene(new RailShoot());
		}
	}
}

void TitleScene::drawFrontSprite()
{
	spCom->drawStart(DX12Base::getInstance()->getCmdList());
	debugText->DrawAll(DX12Base::getInstance(), spCom.get());
}

void TitleScene::drawObj3d()
{
	Object3d::startDraw();
	logoObj->drawWithUpdate(light.get());
}

void TitleScene::end()
{
	PostEffect::getInstance()->changePipeLine(0U);
}