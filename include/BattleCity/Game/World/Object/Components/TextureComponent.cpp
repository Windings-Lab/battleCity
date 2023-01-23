#include "PCHeader.h"
#include "TextureComponent.h"

#include "BattleCity/Engine/Texture/BCTexture.h"
#include "BattleCity/Engine/Texture/TextureGroup.h"
#include "BattleCity/Game/World/Object/Object.h"

namespace BattleCity::Game::World::Object::Component
{
	void Texture::Draw(float interpolation)
	{
		auto& objectPos = mObject.GetPosition();
		mCurrentTexture->DrawAt(objectPos.X, objectPos.Y, interpolation);
	}

	void Texture::SetTextureGroup(const Engine::Texture::Group* textureGroup) noexcept
	{
		mTextureGroup = textureGroup;
	}

	void Texture::ChangeTextureTo(Framework::TextureType type)
	{
		mCurrentTexture = mTextureGroup->GetTextureBy(type);

		auto& objectPos = mObject.GetPosition();

		mCurrentTexture->GetSize(mTextureSize.X, mTextureSize.Y);
		mCurrentTexture->SetDrawPosition(objectPos.X, objectPos.Y);
	}

	Framework::TextureType Texture::GetTextureType() const noexcept
	{
		return mCurrentTexture->GetType();
	}

	const Size& Texture::GetSize() const noexcept
	{
		return mTextureSize;
	}
}

