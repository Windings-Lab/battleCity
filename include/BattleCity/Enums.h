#pragma once

namespace BattleCity
{
	namespace Game::World::Object
	{
		enum class Solidness
		{
			Error,
			Hard,       /// Object causes collisions and impedes.
			Soft,       /// Object causes collision, but doesn't impede.
			Spectral,   /// Object doesn't cause collisions.
		};

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
			None,
			TankPlayer,
			TankNPC,
			Bullet,
			Wall,
			Phoenix,
			Explosion,
			PowerUp,
			WorldBoundaries,
		};

		enum class MovementDirection
		{
			Right,
			Left,
			Down,
			Up,
			Count
		};
	}
}
