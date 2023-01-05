#include "PCHeader.h"
#include "Storage.h"

namespace BattleCity::Engine
{
    void swap(Storage& f, Storage& s) noexcept
    {
        using std::swap;

        swap(f.mTexturePaths, s.mTexturePaths);
        swap(f.mTextures, s.mTextures);
    }

    void Storage::CreatePathLibrary(const std::filesystem::path& path)
    {
        mTexturePaths.CreateData(path);
    }
    void Storage::ClearAllPaths() noexcept
    {
        mTexturePaths.clear();
    }
    const Texture::PathLibrary& Storage::GetPathLibrary() const noexcept
    {
        return mTexturePaths;
    }

    void Storage::CreateTextures(const Texture::PathLibrary& pathLibrary)
    {
        mTextures.CreateData(pathLibrary);
    }
    void Storage::ClearAllTextures() noexcept
    {
        mTextures.clear();
    }
    const Texture::Container& Storage::GetTextures() const noexcept
    {
        return mTextures;
    }

    void Storage::CreateGroups(const Texture::Container& textures)
    {
        mGroups.CreateData(textures);
    }
    void Storage::ClearAllGroups() noexcept
    {
        mGroups.clear();
    }
    const Texture::GroupLibrary& Storage::GetGroups() const noexcept
    {
        return mGroups;
    }

}