#pragma once

template<>
struct std::hash<BattleCity::Sprite::SpritePair>
{
    std::size_t operator()(const BattleCity::Sprite::SpritePair& s) const noexcept
    {
        size_t h1 = std::hash<BattleCity::Sprite::Type>{}(s.first);
        size_t h2 = std::hash<BattleCity::Sprite::Behaviour>{}(s.second);
        return h1 ^ (h2 << 1); // or use boost::hash_combine
    }
};
