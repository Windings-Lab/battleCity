#pragma once

namespace BattleCity::Macros
{
#define DISALLOW_COPY_MOVE(Class)					\
	Class(const Class &) = delete;					\
	Class& operator=(const Class &) = delete;		\
	Class(Class&&) noexcept = delete;				\
	Class& operator=(Class&&) noexcept = delete;

#define DISALLOW_COPY(Class)						\
	Class(const Class &) = delete;					\
	Class& operator=(const Class &) = delete;

#define DISALLOW_MOVE(Class)						\
	Class(Class&&) noexcept = delete;				\
	Class& operator=(Class&&) noexcept = delete;
}

