#pragma once

namespace BattleCity
{
	// My Experimentation

	template <typename ReturnType, typename... ArgsType>
	class TFunction
	{
		typedef ReturnType(*FuncPtr)(ArgsType... args);
	public:
		explicit TFunction(FuncPtr func)
			: mFuncPtr(func)
		{
		}

		TFunction(const TFunction& cpy) = delete;
		TFunction(TFunction&& mve) noexcept : mFuncPtr(std::move(mve.mFuncPtr()))
		{}
		
		TFunction& operator=(const TFunction&) = delete;
		TFunction& operator=(TFunction&&) = delete;
		
		~TFunction() = default;
		
		ReturnType operator()(ArgsType... params)
		{
			return mFuncPtr(params...);
		}

	private:
		FuncPtr mFuncPtr;
	};

	template <typename MType, typename ReturnType, typename... ArgsType>
	class TFunctionMemeber
	{
		typedef ReturnType(MType::*FuncPtr)(ArgsType... args);
	public:
		explicit TFunctionMemeber(FuncPtr func, MType* obj)
			: mFuncPtr(func), mObj(obj)
		{
		}

		TFunctionMemeber(const TFunctionMemeber& cpy) = delete;
		TFunctionMemeber(TFunctionMemeber&& mve) noexcept
			: mFuncPtr(std::move(mve.mFuncPtr())), mObj(std::move(mve.mObj))
		{}

		TFunctionMemeber& operator=(const TFunctionMemeber&) = delete;
		TFunctionMemeber& operator=(TFunctionMemeber&&) = delete;

		~TFunctionMemeber() = default;

		ReturnType operator()(ArgsType... params)
		{
			return (mObj->*mFuncPtr)(params...);
		}

	private:
		FuncPtr mFuncPtr;
		MType* mObj;
	};
}

