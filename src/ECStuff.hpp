#ifndef LD43_ECSTUFF_HPP
#define LD43_ECSTUFF_HPP

namespace ECStuff
{
    struct Pos
    {
        Pos(float x = 0.0f, float y = 0.0f);

        float x;
        float y;
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
}

#endif
