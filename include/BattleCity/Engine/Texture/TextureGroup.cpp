#include "PCHeader.h"
#include "TextureGroup.h"

#include "BCTexture.h"

namespace BattleCity::Engine::Texture
{
    Group::~Group() = default;

    void Group::Add(const Texture* texture)
    {
        mGroupContainer.try_emplace(texture->GetType(), texture);
    }
    const Texture* Group::GetTextureBy(Framework::TextureType type) const
    {
        return mGroupContainer.at(type);
    }

    size_t Group::size() const noexcept
    {
        return mGroupContainer.size();
    }

}
