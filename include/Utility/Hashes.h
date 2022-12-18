#pragma once

template<>
struct std::hash<SpriteTypeBehaviourPair>
{
    std::size_t operator()(SpriteTypeBehaviourPair const& s) const noexcept
    {
        size_t h1 = std::hash<BattleCity::Manager::SpriteType>{}(s.first);
        size_t h2 = std::hash<BattleCity::Object::Behaviour>{}(s.second);
        return h1 ^ (h2 << 1); // or use boost::hash_combine
    }
};
