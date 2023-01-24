#pragma once

namespace BattleCity
{
	namespace Game::World::Object
	{
		enum class Solidness
		{
			Error = -1,
			Hard,       /// Object causes collisions and impedes.
			Soft,       /// Object causes collision, but doesn't impede.
			Spectral,   /// Object doesn't cause collisions.
		};

		enum class Layer
		{
			Error = -1,
			Back,
			Middle,
			Front,
			UI,
			Debug,
			Count
		};

		enum class ExplosionType
		{
			Error = -1,
			Large,
			Small
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
			TankSpawnPointer,
			WorldBoundaries,
			GameOver,
		};

		enum class Direction
		{
			Error = -1,
			Right,
			Left,
			Down,
			Up,
			Count
		};
	}
}
