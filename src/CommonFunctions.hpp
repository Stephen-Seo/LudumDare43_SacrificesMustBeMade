#ifndef LD43_COMMON_FNS_HPP
#define LD43_COMMON_FNS_HPP

#include "CommonValues.hpp"

namespace CommonFns
{
    void cleanupLevel(const std::unordered_set<std::size_t> preserveSet, ManagerT& manager);

    void loadLevel(const unsigned int id, ManagerT& manager);

    void resetWorld(ManagerT& manager, Context& context);

    void loadManagerFns(ManagerT& manager, Context* context);

    void physUpdateX(std::size_t id, void* ptr,
        ECStuff::Pos* pos, ECStuff::Vel* vel,
        ECStuff::Acc* acc, ECStuff::Size* size);

    void collDetUpdateX(std::size_t id, void* ptr,
        ECStuff::Pos* pos, ECStuff::Size* size);

    void finUpdateX(std::size_t id, void* ptr,
        ECStuff::Pos* pos, ECStuff::Vel* vel);

    void physUpdateY(std::size_t id, void* ptr,
        ECStuff::Pos* pos, ECStuff::Vel* vel,
        ECStuff::Acc* acc, ECStuff::Size* size);

    void collDetUpdateY(std::size_t id, void* ptr,
        ECStuff::Pos* pos, ECStuff::Size* size);

    void finUpdateY(std::size_t id, void* ptr,
        ECStuff::Pos* pos, ECStuff::Vel* vel);

    void updateFragments(std::size_t id, void* ptr, BitsetT* bitset);

    void updateParticles(std::size_t id, void* ptr,
        ECStuff::Pos* pos, ECStuff::Size* size, ECStuff::ParticleGen* particle);
}

#endif
