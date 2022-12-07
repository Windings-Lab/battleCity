#pragma once

namespace BattleCity
{
	template <typename FuncType, typename... ArgTypes>
	class TFunction
	{
	public:
		explicit TFunction(FuncType(*func)(ArgTypes&))
			: mFunc(func)
		{
		}

		TFunction(const TFunction& cpy) = delete;
		TFunction(TFunction&& mve) noexcept : mFunc(std::move(mve.mFunc())) {}

		TFunction& operator=(const TFunction&) = delete;
		TFunction& operator=(TFunction&&) = delete;

		~TFunction() = default;

		FuncType& operator()(ArgTypes... params)
		{
			return mFunc(params...);
		}

	private:
		FuncType (*mFunc)(ArgTypes&... args);
	};
}

