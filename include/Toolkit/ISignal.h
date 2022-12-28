#pragma once

#include "Action.h"

namespace BattleCity
{
	template<typename... Args>
	class ISignal
	{
	public:
		ISignal() = default;
		virtual ~ISignal() = default;

		void AddListener(const std::function<void(Args...)>& listener)
		{
			mListener += listener;
		}
		void RemoveAllListeners(void* listenerPtr)
		{
			mListener.RemoveAll();
		}
		void RemoveListener(void* listenerPtr)
		{
			mListener -= listenerPtr;
		}

		template<typename... OpArgs, std::enable_if_t<sizeof...(Args) == sizeof...(OpArgs), int> = 0>
		void Dispatch(OpArgs&&... args) const
		{
			mListener(std::forward<OpArgs>(args)...);
		}

	private:
		Action<Args...> mListener;
	};
}
