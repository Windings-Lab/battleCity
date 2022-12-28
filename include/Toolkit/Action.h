#pragma once

namespace BattleCity
{
	template<typename... Args>
	class Action final
	{
	public:
		Action() = default;
		Action(const std::function<void(Args...)>& function)
		{
			mFunctions.emplace_back(function);
		}
		Action(const std::initializer_list<std::function<void(Args...)>>& functions)
			: mFunctions(functions)
		{}

		void RemoveAll()
		{
			mFunctions.clear();
		}

		template<typename... OpArgs, std::enable_if_t<sizeof...(Args) == sizeof...(OpArgs), int> = 0>
		void operator()(OpArgs&&... args) const noexcept
		{
			for (const auto& function : mFunctions)
			{
				function(std::forward<OpArgs>(args)...);
			}
		}

		void operator+=(const std::function<void(Args...)>& func) noexcept
		{
			mFunctions.emplace_back(func);
		}

		void operator-=(void* funcPtr) noexcept
		{
			const auto& it = std::find_if(mFunctions.begin(), mFunctions.end(), [&funcPtr](std::function<void(Args...)> vecFunc)
				{
					return funcPtr == *vecFunc.target<void(*)(Args...)>();
				});

			if(it == mFunctions.end()) return;

			mFunctions.erase(it);
		}

	private:
		std::vector<std::function<void(Args...)>> mFunctions;
	};
}


