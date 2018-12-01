#ifndef LD43_COMMON_FNS_HPP
#define LD43_COMMON_FNS_HPP

#include "CommonValues.hpp"

namespace CommonFns
{
    void cleanupLevel(Context& context);

    void loadLevel(const unsigned int id, Context& context);

    void resetWorld(Context& context);

    void loadManagerFns(Context* context);

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
