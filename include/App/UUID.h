#pragma once

namespace BattleCity
{
	class UUID
	{
	protected:
		UUID();

	public:
		virtual ~UUID() = 0;

		int GetID() const noexcept;

	private:
		int mID;
	};
}
