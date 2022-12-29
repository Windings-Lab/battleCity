#pragma once

namespace BattleCity::Manager
{
	struct Manager
	{
		Manager() = default;

		DISALLOW_COPY_MOVE(Manager)

		virtual ~Manager() = 0;

		virtual void OnInit() = 0;
		virtual void OnClose() = 0;
	};
}
