#include "GameOverScene.h"
#include "Object3d.h"
#include "SceneManager.h"
#include "TitleScene.h"

using namespace DirectX;

GameOverScene::GameOverScene() :
	input(Input::getInstance()),
	spBase(std::make_unique<SpriteBase>())
{
	const UINT debugTextTexNumber = spBase->loadTexture(L"Resources/debugfont.png");
	debugText.reset(new DebugText(debugTextTexNumber, spBase.get()));
}

void GameOverScene::update()
{
	constexpr XMFLOAT2 textPos = XMFLOAT2(DebugText::fontWidth * 1.5f,
										  DebugText::fontHeight * 1.5f);
	constexpr XMFLOAT4 textCol = XMFLOAT4(1, 1, 1, 1);

	constexpr float headScale = 8.f;
	constexpr float headHei = DebugText::fontHeight * headScale;

	debugText->Print(spBase.get(), "GameOver", textPos.x, textPos.y, headScale);

	debugText->formatPrint(spBase.get(),
						   textPos.x,
						   textPos.y + headHei,
						   1.f,
						   textCol,
						   "Score : %u",
						   SceneManager::getInstange()->score->killEnemyNum);

	{
		constexpr XMFLOAT2 strPos = XMFLOAT2(DebugText::fontWidth * 1.5f,
											 WinAPI::window_height - DebugText::fontHeight * 1.5f);
		debugText->Print(spBase.get(), "Press SPACE...", strPos.x, strPos.y, 1.f);
	}

	// 入力でタイトルに戻る
	if (input->triggerKey(DIK_SPACE))
	{
		SceneManager::getInstange()->changeScene(new TitleScene());
	}
}

void GameOverScene::drawObj3d()
{
}

void GameOverScene::drawFrontSprite()
{
	spBase->drawStart(DX12Base::getInstance()->getCmdList());
	debugText->DrawAll(DX12Base::getInstance(), spBase.get());
}
