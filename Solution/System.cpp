#include "System.h"

#include "WinAPI.h"
#include "DX12Base.h"

#include "Input.h"
#include "Looper.h"

#include "Object3d.h"

#include "Light.h"

System::System()
{
}

void System::update()
{
	if (!error)
	{
		// ゲームループ
		while (!WinAPI::getInstance()->processMessage()
			   && !Looper::getInstance()->loop())
		{
		}
	}
}

System::~System()
{
}