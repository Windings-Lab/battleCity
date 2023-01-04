#include "PCHeader.h"
#include "Storage.h"

namespace BattleCity::Engine
{
    void swap(Storage& f, Storage& s) noexcept
    {
        using std::swap;

        swap(f.mPathLibrary, s.mPathLibrary);
        swap(f.mTextureContainer, s.mTextureContainer);
    }

    void Storage::CreatePathLibrary(const std::filesystem::path& path)
    {
        mPathLibrary.CreateData(path);
    }
    const Texture::PathLibrary& Storage::GetPathLibrary() const noexcept
    {
        return mPathLibrary;
    }

    void Storage::CreateTextures(const Texture::PathLibrary& pathLibrary)
    {
        mTextureContainer.CreateData(pathLibrary);
    }
    const Texture::Container& Storage::GetTextures() const noexcept
    {
        return mTextureContainer;
    }

}