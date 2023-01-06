#include "PCHeader.h"
#include "TextureStorage.h"

namespace BattleCity::Engine::Texture
{
    void swap(Storage& f, Storage& s) noexcept
    {
        using std::swap;

        swap(f.mTextures, s.mTextures);
        swap(f.mGroups, s.mGroups);
    }

    void Storage::CreateTextures(const PathLibrary& pathLibrary)
    {
        mTextures.CreateData(pathLibrary);
    }
    void Storage::ClearAllTextures() noexcept
    {
        mTextures.clear();
    }
    const Container& Storage::GetTextures() const noexcept
    {
        return mTextures;
    }

    void Storage::CreateGroups(const Container& textures)
    {
        mGroups.CreateData(textures);
    }
    void Storage::ClearAllGroups() noexcept
    {
        mGroups.clear();
    }
    const GroupLibrary& Storage::GetGroups() const noexcept
    {
        return mGroups;
    }

}