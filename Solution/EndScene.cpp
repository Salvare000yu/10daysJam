#include "EndScene.h"

#include "SceneManager.h"

#include "WinAPI.h"

#include "TitleScene.h"

#include "PostEffect.h"

using namespace DirectX;

EndScene::EndScene()
{
	PostEffect::getInstance()->setAlpha(1.f);
	PostEffect::getInstance()->setMosaicNum(DirectX::XMFLOAT2(WinAPI::window_width, WinAPI::window_height));

	input = Input::getInstance();

	spCom.reset(new SpriteBase());

	// デバッグテキスト用のテクスチャ読み込み
	debugTextTexNumber = spCom->loadTexture(L"Resources/debugfont.png");

	debugText.reset(new DebugText(debugTextTexNumber, spCom.get()));
}

void EndScene::update()
{
	// 入力でタイトルへ進む
	if (input->triggerKey(DIK_SPACE))
	{
		SceneManager::getInstange()->changeScene(new TitleScene());
	}


	// 情報表示
	constexpr XMFLOAT2 textPos = XMFLOAT2(DebugText::fontWidth * 1.5f,
										  DebugText::fontHeight * 1.5f);
	constexpr XMFLOAT4 textCol = XMFLOAT4(1, 1, 1, 1);

	constexpr float headScale = 10.f;
	constexpr float headHei = DebugText::fontHeight * headScale;

	debugText->formatPrint(spCom.get(),
						   textPos.x,
						   textPos.y + headHei,
						   1.f,
						   textCol,
						   "Score : %u",
						   SceneManager::getInstange()->score->killEnemyNum);

	debugText->Print(spCom.get(), "END", 0, 0, headScale);
	{
		constexpr XMFLOAT2 strPos = XMFLOAT2(DebugText::fontWidth * 1.5f,
											 WinAPI::window_height - DebugText::fontHeight * 1.5f);
		debugText->Print(spCom.get(), "Press SPACE...", strPos.x, strPos.y, 1.f);
	}
}

void EndScene::drawFrontSprite()
{
	spCom->drawStart(DX12Base::getInstance()->getCmdList());
	debugText->DrawAll(DX12Base::getInstance(), spCom.get());
}