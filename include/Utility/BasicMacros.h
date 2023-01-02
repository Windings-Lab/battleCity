#pragma once

namespace BattleCity::Macros
{
	// ============== Allow Default ================

#define ALLOW_COPY_MOVE_DEFAULT(Class)				\
	Class(const Class &) = default;					\
	Class& operator=(const Class &) = default;		\
	Class(Class&&) noexcept = default;				\
	Class& operator=(Class&&) noexcept = default;

#define ALLOW_COPY_DEFAULT(Class)					\
	Class(const Class &) = default;					\
	Class& operator=(const Class &) = default;

#define ALLOW_MOVE_DEFAULT(Class)					\
	Class(Class&&) noexcept = default;				\
	Class& operator=(Class&&) noexcept = default;

	// ============== Allow Default ================

	// ==============	  Allow  ===================
#define ALLOW_COPY_MOVE(Class)						\
	Class(const Class &);							\
	Class& operator=(const Class &);				\
	Class(Class&&) noexcept;						\
	Class& operator=(Class&&) noexcept;

#define ALLOW_COPY(Class)							\
	Class(const Class &);							\
	Class& operator=(const Class &);

#define ALLOW_MOVE(Class)							\
	Class(Class&&) noexcept;						\
	Class& operator=(Class&&) noexcept;

	// ==============	  Allow  ===================

	// ==============  Disallow  ===================

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

	// ==============  Disallow  ===================
}

