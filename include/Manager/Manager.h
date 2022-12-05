#pragma once

namespace BattleCity::Manager
{


	class Manager
	{
	protected:
		enum class Type
		{
			Error = 0,
			Game,
			World,
			Sprite
		};
		explicit Manager(Type);
	public:
		Manager() = delete;
		Manager(const Manager&) = delete;
		Manager(Manager&&) = delete;

		Manager& operator=(const Manager&) = delete;
		Manager& operator=(Manager&&) = delete;

		virtual ~Manager() = 0;

		virtual void StartUp() = 0;
		virtual void ShutDown() = 0;

		Type GetType() const;
	private:
		Type mType;
	};
}
