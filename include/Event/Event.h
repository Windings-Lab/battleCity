#pragma once

namespace BattleCity::Event
{
	class Event
	{
	public:
		Event();

		virtual ~Event() = default;

		void SetType(Type newType);
		Type GetType() const;
	private:
		Type mEventType;
	};
}
