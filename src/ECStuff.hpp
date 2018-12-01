#ifndef LD43_ECSTUFF_HPP
#define LD43_ECSTUFF_HPP

namespace ECStuff
{
    // components
    struct Pos
    {
        Pos(float x = 0.0f, float y = 0.0f);

        float x;
        float y;
        float px;
        float py;
    };

    struct Vel
    {
        Vel(float x = 0.0f, float y = 0.0f);

        float x;
        float y;
    };

    struct Acc
    {
        Acc(float x = 0.0f, float y = 0.0f);

        float x;
        float y;
    };

    struct Size
    {
        Size(float w = 1.0f, float h = 1.0f);

        float w;
        float h;
    };

    struct Drawable
    {
        Drawable(
            unsigned char r = 255,
            unsigned char g = 255,
            unsigned char b = 255,
            unsigned char a = 255);

        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    };

    struct ParticleGen
    {
        ParticleGen(unsigned int type = 0);

        /*
         * 0 - is a pariticle, timer is lifetime
         * 1 - generate type 0 particles
         */
        unsigned int type;
        float timer;
    };

    // tags
}

#endif
