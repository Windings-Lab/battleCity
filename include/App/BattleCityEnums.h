#pragma once

namespace BattleCity
{
	namespace Sprite
	{
		enum class Layer
		{
			Error,
			Back,
			Front,
			UI
		};

		enum class Type
		{
			Error,
			TankPlayer,
			TankNPC,
			Bullet,
			Wall,
			Explosion,
			PowerUp,
			Phoenix,
			Flag,
			Background,
			GameOver
		};

		enum class Behaviour
		{
			Error,
			Basic,
			Down,
			Left,
			Right,
			Up,
			ExplosionSmall1,
			ExplosionSmall2,
			ExplosionSmall3,
			ExplosionLarge1,
			ExplosionLarge2,
		};

		using SpritePair = std::pair<Type, Behaviour>;

		struct SpritePairHash
		{
			std::size_t operator()(const SpritePair& s) const
			{
				size_t h1 = std::hash<Type>{}(s.first);
				size_t h2 = std::hash<Behaviour>{}(s.second);
				return h1 ^ (h2 << 1);
			}
		};
	}

	namespace Object
	{
		enum class Solidness
		{
			Error,
			Hard,       /// Object causes collisions and impedes.
			Soft,       /// Object causes collision, but doesn't impede.
			Spectral,   /// Object doesn't cause collisions.
		};

		enum class Type
		{
			Error,
			None,
			TankPlayer,
			TankNPC,
			Bullet,
			Wall,
			Phoenix,
			Explosion,
			PowerUp
		};

		// Do not use int(4) since framework using it for another purpose
		// Look at FRKey
		enum class MovementDirection
		{
			Error,
			Right,
			Left,
			Down,
			Up = 5,
			Idle
		};
	}
}
