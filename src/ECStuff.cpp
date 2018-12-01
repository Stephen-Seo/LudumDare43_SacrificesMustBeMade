#include "ECStuff.hpp"

ECStuff::Pos::Pos(float x, float y) :
x(x),
y(y)
{}

ECStuff::Vel::Vel(float x, float y) :
x(x),
y(y)
{}

ECStuff::Acc::Acc(float x, float y) :
x(x),
y(y)
{}

ECStuff::Size::Size(float w, float h) :
w(w),
h(h)
{}

ECStuff::Drawable::Drawable(
    unsigned char r,
    unsigned char g,
    unsigned char b,
    unsigned char a) :
r(r),
g(g),
b(b),
a(a)
{}

ECStuff::ParticleGen::ParticleGen(unsigned int type) :
type(type),
timer(0.0f)
{}
