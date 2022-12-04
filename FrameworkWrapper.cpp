#include "FrameworkWrapper.h"

#include "GameManager.h"
#include "WorldManager.h"
#include "Screen.h"
#include "Sprites.h"
#include "TankPlayer.h"

namespace battleCity
{
	void FrameworkWrapper::PreInit(int& width, int& height, bool& fullscreen)
	{
		width = SCR.GetWidth();
		height = SCR.GetHeight();
		fullscreen = SCR.GetFullscreen();
	}

	bool FrameworkWrapper::Init()
	{
		StartAllManagers();
		return true;
	}

	void FrameworkWrapper::Close()
	{
		ShutDownAllManagers();
	}

	bool FrameworkWrapper::Tick()
	{
		GM.Update();
		return GM.GetGameOver();
	}

	const char* FrameworkWrapper::GetTitle()
	{
		return "Tanks";
	}

	void FrameworkWrapper::onKeyPressed(FRKey k)
	{
		if (mPlayer->GetHealth() > 0)
		{
			mEventKeyboard.SetKey(k);
			mEventKeyboard.SetKeyboardAction(EventKeyboardAction::KEY_PRESSED);
			mPlayer->movementSet(k);
			mPlayer->EventHandler(mEventKeyboard);
		}
	}

	void FrameworkWrapper::onKeyReleased(FRKey k)
	{
		if (mPlayer->GetHealth() > 0)
		{
			mEventKeyboard.SetKey(k);
			mEventKeyboard.SetKeyboardAction(EventKeyboardAction::KEY_RELEASED);
			mPlayer->movementErase(k);
			mPlayer->EventHandler(mEventKeyboard);
		}
	}

	void FrameworkWrapper::onMouseMove(int x, int y, int xrelative, int yrelative)
	{
		mEventMouse.SetMousePosition({ static_cast<float>(x), static_cast<float>(y) });
	}

	void FrameworkWrapper::onMouseButtonClick(FRMouseButton button, bool isReleased)
	{
		if (mPlayer->GetHealth() > 0)
		{
			mEventMouse.SetMouseButton(button);
			mEventMouse.SetMouseAction(isReleased);
			mPlayer->EventHandler(mEventMouse);
		}
	}

	TankPlayer* GetPlayer(int id)
	{
		return dynamic_cast<TankPlayer*>(WM.GetAllObjects().mList.at(id).get());
	}

	void FrameworkWrapper::StartAllManagers()
	{
		GM.StartUp();
		WM.StartUp();

		mPlayer = GetPlayer(WM.GetPlayerID());
	}

	void FrameworkWrapper::ShutDownAllManagers()
	{
		GM.ShutDown();
		SPR.deleteAll();
		WM.ShutDown();
	}

}
