#ifndef LD43_COMMON_VALUES_HPP
#define LD43_COMMON_VALUES_HPP

#include <random>

#include <SFML/Audio.hpp>

#include <EC/Manager.hpp>

#include "ECStuff.hpp"

#define DELTA_TIME (1.0f / 120.0f)
#define GRAVITY_ACC 5000.0f
#define VEL_DAMPENING 1.4f
#define JUMP_VEL 2400.0f
#define JUMP_SPRING_VEL 7000.0f
#define MOVE_SPEED 120.0f

#define PARTICLE1_GENTIME 0.2f
#define PARTICLE1_GEN_LIFETIME 0.7f

#define PARTICLE2_GROWTH_RATE 3.0f
#define PARTICLE2_FADE_RATE 1

#define PARTICLE3_GENTIME 0.3f
#define PARTICLE3_GENTIME_VAR 0.2f
#define PARTICLE3_GEN_LIFETIME 2.0f

#define RNG_PART_VEL 400.0f
#define RNG_PART_ACC 200.0f

#define WIN_CENTER_MAGNITUDE 30.0f

#define DEATH_TIMER 4.0f

/*
 * 0 - move left
 * 1 - move right
 * 2 - is grounded
 * 3 - is player
 * 4 - is exit
 * 5 - is fragment
 * 6 - is fragment pick-upable (after player no longer collides with it)
 * 7 - collided with player
 * 8 - is particle
 * 9 - is spring
 * 10 - is on spring
 * 11 - is death block
 * 12 - is auto spring
 * 13 - is on auto spring
 * 14 - is key
 * 15 - is lock
 */
using BitsetT = std::bitset<32>;

using AllComponents = EC::Meta::TypeList<
    ECStuff::Pos,
    ECStuff::Vel,
    ECStuff::Acc,
    ECStuff::Size,
    ECStuff::Drawable,
    BitsetT,
    ECStuff::ParticleGen
>;

using PhysComponents = EC::Meta::TypeList<
    ECStuff::Pos,
    ECStuff::Vel,
    ECStuff::Acc,
    ECStuff::Size
>;

using ColComponents = EC::Meta::TypeList<
    ECStuff::Pos,
    ECStuff::Size
>;

using ColFinComponents = EC::Meta::TypeList<
    ECStuff::Pos,
    ECStuff::Vel
>;

using FadeDrawComponents = EC::Meta::TypeList<
    ECStuff::Pos,
    ECStuff::Size,
    ECStuff::Drawable,
    BitsetT
>;

using DrawComponents = EC::Meta::TypeList<
    ECStuff::Pos,
    ECStuff::Size,
    ECStuff::Drawable
>;

using FragmentComponents = EC::Meta::TypeList<
    BitsetT
>;

using ParticleComponents = EC::Meta::TypeList<
    ECStuff::Pos,
    ECStuff::Size,
    ECStuff::ParticleGen
>;

using AllTags = EC::Meta::TypeList<
>;

using ManagerT = EC::Manager<AllComponents, AllTags>;

struct Context
{
    ManagerT manager;
    std::unordered_set<std::size_t> revertPos;
    BitsetT globalFlags;
    std::unordered_map<unsigned int, sf::SoundBuffer> sfxMap;
    std::vector<sf::Sound> soundPool;
    std::size_t playerID;
    std::default_random_engine rng;
    unsigned int currentSize;
    unsigned int currentLevel;
    std::unordered_set<std::size_t> preserveSet;
    sf::Music music;

    /*
     * globalFlags:
     * 0 - current level exit reached
     * 1 - is player dead
     * 2 - current level key get
     * 3 - win condition
     * 4 - fade black on
     */

    /*
     * sfxMap:
     * 0 - sfx_goalreached.ogg
     * 1 - sfx_jump.ogg
     * 2 - sfx_death.ogg
     * 3 - sfx_keyget.ogg
     */

    void playSfx(const unsigned int& id);
};

#endif
