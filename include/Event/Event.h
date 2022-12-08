#pragma once

namespace BattleCity
{
	class Event
	{
	public:
		Event();

		virtual ~Event() = default;

		void SetType(EventEnum::Type newType);
		EventEnum::Type GetType() const;
	private:
		EventEnum::Type mEventType;
	};
}
