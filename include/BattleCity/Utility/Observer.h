#pragma once

namespace BattleCity
{
	class Subject;

	class Observer : std::enable_shared_from_this<Observer>
	{
	public:
		Observer() = default;
		Observer(std::shared_ptr<Subject>);
		virtual ~Observer();

		virtual void PreUnregister() = 0;
		virtual void OnNotify() = 0;

	private:
		std::weak_ptr<Subject> mSubject;
	};
}
