#include "CommonFunctions.hpp"

#include <GDT/CollisionDetection.hpp>

void CommonFns::cleanupLevel(Context& context)
{
    context.manager.forMatchingSignature<EC::Meta::TypeList<>>(
        [&context] (std::size_t id, void* /*ptr*/) {
            if(context.preserveSet.find(id) == context.preserveSet.end())
            {
                context.manager.deleteEntity(id);
            }
        },
        nullptr);
}

void CommonFns::loadLevel(const unsigned int id, Context& context)
{
    switch(id)
    {
    case 0:
    {
        // ground
        auto id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 100.0f, 270.0f - 50.0f);
        context.manager.addComponent<ECStuff::Size>(id, 100.0f, 50.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 64, 0);
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 200.0f, 270.0f - 100.0f);
        context.manager.addComponent<ECStuff::Size>(id, 100.0f, 100.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 64, 0);
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 300.0f, 270.0f - 150.0f);
        context.manager.addComponent<ECStuff::Size>(id, 100.0f, 150.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 64, 0);

        // exit
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 435.0f, 270.0f - 40.0f);
        context.manager.addComponent<ECStuff::Size>(id, 30.0f, 30.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 128, 255);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(4);
    }
        break;
    case 1:
    {
        // ground
        auto id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 200.0f, 270.0f - 50.0f);
        context.manager.addComponent<ECStuff::Size>(id, 100.0f, 50.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 64, 0);
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 80.0f, 270.0f - 150.0f);
        context.manager.addComponent<ECStuff::Size>(id, 400.0f, 10.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 64, 0);
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 200.0f, 270.0f - 200.0f);
        context.manager.addComponent<ECStuff::Size>(id, 100.0f, 50.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 64, 0);

        // spring
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 10.0f, 270.0f - 20.0f);
        context.manager.addComponent<ECStuff::Size>(id, 50.0f, 20.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 255, 128);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(9);

        // exit
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 435.0f, 30.0f);
        context.manager.addComponent<ECStuff::Size>(id, 30.0f, 30.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 128, 255);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(4);
    }
        break;
    case 2:
    {
        // ground
        auto id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 380.0f, 140.0f);
        context.manager.addComponent<ECStuff::Size>(id, 100.0f, 50.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 64, 0);
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 0.0f, 140.0f);
        context.manager.addComponent<ECStuff::Size>(id, 100.0f, 50.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 64, 0);

        // spring
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 205.0f, 230.0f);
        context.manager.addComponent<ECStuff::Size>(id, 50.0f, 20.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 255, 128);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(9);

        // death block
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 0.0f, 250.0f);
        context.manager.addComponent<ECStuff::Size>(id, 480.0f, 20.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 255, 0, 0);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(11);

        // exit
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 10.0f, 100.0f);
        context.manager.addComponent<ECStuff::Size>(id, 30.0f, 30.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 128, 255);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(4);
    }
        break;
    case 3:
    {
        // ground
        auto id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 95.0f, 100.0f);
        context.manager.addComponent<ECStuff::Size>(id, 10.0f, 170.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 64, 0);
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 190.0f, 0.0f);
        context.manager.addComponent<ECStuff::Size>(id, 10.0f, 170.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 64, 0);
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 285.0f, 100.0f);
        context.manager.addComponent<ECStuff::Size>(id, 10.0f, 170.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 64, 0);
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 380.0f, 0.0f);
        context.manager.addComponent<ECStuff::Size>(id, 10.0f, 170.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 64, 0);

        // spring
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 0.0f, 250.0f);
        context.manager.addComponent<ECStuff::Size>(id, 480.0f, 20.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 255, 128);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(9);

        // exit
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 450.0f, 70.0f);
        context.manager.addComponent<ECStuff::Size>(id, 30.0f, 30.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 128, 255);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(4);
    }
        break;
    case 4:
    {
        // ground
        auto id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 400.0f, 250.0f);
        context.manager.addComponent<ECStuff::Size>(id, 80.0f, 20.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 64, 0);
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 300.0f, 250.0f);
        context.manager.addComponent<ECStuff::Size>(id, 80.0f, 20.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 64, 0);
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 200.0f, 250.0f);
        context.manager.addComponent<ECStuff::Size>(id, 80.0f, 20.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 64, 0);

        // death block
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 330.0f, 200.0f);
        context.manager.addComponent<ECStuff::Size>(id, 40.0f, 40.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 255, 0, 0);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(11);
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 230.0f, 200.0f);
        context.manager.addComponent<ECStuff::Size>(id, 40.0f, 40.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 255, 0, 0);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(11);
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 130.0f, 200.0f);
        context.manager.addComponent<ECStuff::Size>(id, 40.0f, 40.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 255, 0, 0);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(11);

        // auto spring
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 390.0f, 240.0f);
        context.manager.addComponent<ECStuff::Size>(id, 10.0f, 20.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 240, 255);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(12);
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 290.0f, 240.0f);
        context.manager.addComponent<ECStuff::Size>(id, 10.0f, 20.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 240, 255);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(12);
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 190.0f, 240.0f);
        context.manager.addComponent<ECStuff::Size>(id, 10.0f, 20.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 240, 255);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(12);

        // ground
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 50.0f, 0.0f);
        context.manager.addComponent<ECStuff::Size>(id, 10.0f, 180.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 64, 0);

        // exit
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 0.0f, 150.0f);
        context.manager.addComponent<ECStuff::Size>(id, 30.0f, 30.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 128, 255);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(4);
    }
        break;
    case 5:
    {
        // ground
        auto id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 0.0f, 235.0f);
        context.manager.addComponent<ECStuff::Size>(id, 50.0f, 35.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 64, 0);

        // death block
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 0.0f, 0.0f);
        context.manager.addComponent<ECStuff::Size>(id, 480.0f, 20.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 255, 0, 0);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(11);

        // auto spring
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 60.0f, 225.0f);
        context.manager.addComponent<ECStuff::Size>(id, 10.0f, 10.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 240, 255);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(12);

        // ground
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 80.0f, 235.0f);
        context.manager.addComponent<ECStuff::Size>(id, 50.0f, 35.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 64, 0);

        // auto spring
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 140.0f, 225.0f);
        context.manager.addComponent<ECStuff::Size>(id, 10.0f, 10.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 240, 255);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(12);

        // ground
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 160.0f, 235.0f);
        context.manager.addComponent<ECStuff::Size>(id, 50.0f, 35.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 64, 0);

        // auto spring
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 220.0f, 225.0f);
        context.manager.addComponent<ECStuff::Size>(id, 10.0f, 10.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 240, 255);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(12);

        // ground
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 240.0f, 235.0f);
        context.manager.addComponent<ECStuff::Size>(id, 50.0f, 35.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 64, 0);

        // auto spring
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 300.0f, 225.0f);
        context.manager.addComponent<ECStuff::Size>(id, 10.0f, 10.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 240, 255);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(12);

        // ground
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 320.0f, 235.0f);
        context.manager.addComponent<ECStuff::Size>(id, 50.0f, 35.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 64, 0);

        // auto spring
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 380.0f, 225.0f);
        context.manager.addComponent<ECStuff::Size>(id, 10.0f, 10.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 240, 255);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(12);

        // ground
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 400.0f, 235.0f);
        context.manager.addComponent<ECStuff::Size>(id, 80.0f, 35.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 64, 0);

        // exit
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 440.0f, 200.0f);
        context.manager.addComponent<ECStuff::Size>(id, 30.0f, 30.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 128, 255);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(4);
    }
        break;
    case 6:
    {
        // ground
        auto id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 410.0f, 250.0f);
        context.manager.addComponent<ECStuff::Size>(id, 70.0f, 20.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 64, 0);

        // death block
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 395.0f, 246.0f);
        context.manager.addComponent<ECStuff::Size>(id, 15.0f, 24.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 255, 0, 0);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(11);

        // ground
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 345.0f, 250.0f);
        context.manager.addComponent<ECStuff::Size>(id, 50.0f, 20.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 64, 0);

        // auto spring
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 330.0f, 240.0f);
        context.manager.addComponent<ECStuff::Size>(id, 15.0f, 30.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 240, 255);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(12);

        // ground
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 345.0f, 100.0f);
        context.manager.addComponent<ECStuff::Size>(id, 30.0f, 20.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 64, 0);

        // key
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 355.0f, 80.0f);
        context.manager.addComponent<ECStuff::Size>(id, 10.0f, 10.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 255, 255, 32);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(14);

        // lock
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 270.0f, 0.0f);
        context.manager.addComponent<ECStuff::Size>(id, 10.0f, 270.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 96, 96, 96);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(15);

        // death block
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 280.0f, 250.0f);
        context.manager.addComponent<ECStuff::Size>(id, 50.0f, 20.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 255, 0, 0);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(11);

        // spring
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 5.0f, 250.0f);
        context.manager.addComponent<ECStuff::Size>(id, 18.0f, 20.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 255, 128);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(9);

        // death block
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 0.0f, 70.0f);
        context.manager.addComponent<ECStuff::Size>(id, 10.0f, 180.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 255, 0, 0);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(11);

        // exit
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 5.0f, 30.0f);
        context.manager.addComponent<ECStuff::Size>(id, 30.0f, 30.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 128, 255);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(4);
    }
        break;
    case 7:
    {
        // auto spring
        auto id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 0.0f, 260.0f);
        context.manager.addComponent<ECStuff::Size>(id, 480.0f, 10.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 240, 255);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(12);
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 30.0f, 130.0f);
        context.manager.addComponent<ECStuff::Size>(id, 30.0f, 10.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 240, 255);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(12);
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 60.0f, 195.0f);
        context.manager.addComponent<ECStuff::Size>(id, 30.0f, 10.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 240, 255);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(12);
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 60.0f, 65.0f);
        context.manager.addComponent<ECStuff::Size>(id, 30.0f, 10.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 240, 255);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(12);
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 90.0f, 130.0f);
        context.manager.addComponent<ECStuff::Size>(id, 30.0f, 10.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 240, 255);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(12);
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 120.0f, 195.0f);
        context.manager.addComponent<ECStuff::Size>(id, 30.0f, 10.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 240, 255);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(12);
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 120.0f, 65.0f);
        context.manager.addComponent<ECStuff::Size>(id, 30.0f, 10.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 240, 255);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(12);
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 150.0f, 130.0f);
        context.manager.addComponent<ECStuff::Size>(id, 30.0f, 10.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 240, 255);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(12);

        // key
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 160.0f, 115.0f);
        context.manager.addComponent<ECStuff::Size>(id, 10.0f, 10.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 255, 255, 32);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(14);

        // auto spring
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 180.0f, 195.0f);
        context.manager.addComponent<ECStuff::Size>(id, 30.0f, 10.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 240, 255);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(12);
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 180.0f, 65.0f);
        context.manager.addComponent<ECStuff::Size>(id, 30.0f, 10.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 240, 255);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(12);
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 230.0f, 130.0f);
        context.manager.addComponent<ECStuff::Size>(id, 30.0f, 10.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 240, 255);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(12);
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 280.0f, 195.0f);
        context.manager.addComponent<ECStuff::Size>(id, 30.0f, 10.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 240, 255);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(12);
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 280.0f, 65.0f);
        context.manager.addComponent<ECStuff::Size>(id, 30.0f, 10.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 240, 255);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(12);
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 330.0f, 130.0f);
        context.manager.addComponent<ECStuff::Size>(id, 30.0f, 10.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 240, 255);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(12);

        // lock
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 420.0f, 0.0f);
        context.manager.addComponent<ECStuff::Size>(id, 60.0f, 90.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 96, 96, 96);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(15);

        // exit
        id = context.manager.addEntity();
        context.manager.addComponent<ECStuff::Pos>(id, 440.0f, 60.0f);
        context.manager.addComponent<ECStuff::Size>(id, 30.0f, 30.0f);
        context.manager.addComponent<ECStuff::Drawable>(id, 128, 128, 255);
        context.manager.addComponent<BitsetT>(id);
        context.manager.getEntityData<BitsetT>(id)->set(4);
    }
        break;
    default:
        // win condition
        context.music.stop();
        context.music.openFromFile("ld43_winmusic.ogg");
        context.music.setLoop(false);
        context.music.play();
        context.globalFlags.set(3);

        context.manager.addComponent<ECStuff::ParticleGen>(context.playerID, 3);
        break;
    }
}

void CommonFns::resetWorld(Context& context)
{
    context.manager.reset();
    loadManagerFns(&context);
    context.preserveSet.clear();
    context.currentLevel = 0;
    context.currentSize = 50;

    // create player
    auto playerID = context.manager.addEntity();
    context.manager.addComponent<ECStuff::Pos>(playerID, 2.0f, 200.0f);
    context.manager.addComponent<ECStuff::Vel>(playerID);
    context.manager.addComponent<ECStuff::Acc>(playerID, 0.0f, GRAVITY_ACC);
    context.manager.addComponent<ECStuff::Size>(playerID, 50.0f, 50.0f);
    context.manager.addComponent<ECStuff::Drawable>(playerID);
    context.manager.addComponent<BitsetT>(playerID);
    context.manager.getEntityData<BitsetT>(playerID)->set(3);
    context.preserveSet.insert(playerID);
    context.playerID = playerID;
    context.globalFlags.reset(1);

    // create world boundaries
    auto id = context.manager.addEntity();
    context.manager.addComponent<ECStuff::Pos>(id, -50.0f, 0.0f);
    context.manager.addComponent<ECStuff::Vel>(id);
    context.manager.addComponent<ECStuff::Acc>(id);
    context.manager.addComponent<ECStuff::Size>(id, 50.0f, 270.0f);
    context.preserveSet.insert(id);

    id = context.manager.addEntity();
    context.manager.addComponent<ECStuff::Pos>(id, 0.0f, 270.0f);
    context.manager.addComponent<ECStuff::Vel>(id);
    context.manager.addComponent<ECStuff::Acc>(id);
    context.manager.addComponent<ECStuff::Size>(id, 480.0f, 50.0f);
    context.preserveSet.insert(id);

    id = context.manager.addEntity();
    context.manager.addComponent<ECStuff::Pos>(id, 480.0f, 0.0f);
    context.manager.addComponent<ECStuff::Vel>(id);
    context.manager.addComponent<ECStuff::Acc>(id);
    context.manager.addComponent<ECStuff::Size>(id, 50.0f, 270.0f);
    context.preserveSet.insert(id);

    id = context.manager.addEntity();
    context.manager.addComponent<ECStuff::Pos>(id, 0.0f, -50.0f);
    context.manager.addComponent<ECStuff::Vel>(id);
    context.manager.addComponent<ECStuff::Acc>(id);
    context.manager.addComponent<ECStuff::Size>(id, 480.0f, 50.0f);
    context.preserveSet.insert(id);
}

void CommonFns::loadManagerFns(Context* context)
{
    context->manager.addForMatchingFunction<PhysComponents>(
        CommonFns::physUpdateX,
        context);
    context->manager.addForMatchingFunction<ColComponents>(
        CommonFns::collDetUpdateX,
        context);
    context->manager.addForMatchingFunction<ColFinComponents>(
        CommonFns::finUpdateX,
        context);
    context->manager.addForMatchingFunction<PhysComponents>(
        CommonFns::physUpdateY,
        context);
    context->manager.addForMatchingFunction<ColComponents>(
        CommonFns::collDetUpdateY,
        context);
    context->manager.addForMatchingFunction<ColFinComponents>(
        CommonFns::finUpdateY,
        context);
    context->manager.addForMatchingFunction<FragmentComponents>(
        CommonFns::updateFragments,
        context);
    context->manager.addForMatchingFunction<ParticleComponents>(
        CommonFns::updateParticles,
        context);
}

void CommonFns::physUpdateX(
    std::size_t id,
    void* ptr,
    ECStuff::Pos* pos,
    ECStuff::Vel* vel,
    ECStuff::Acc* acc,
    ECStuff::Size* /*size*/)
{
    Context* context = (Context*)ptr;
    pos->px = pos->x;

    vel->x += acc->x * DELTA_TIME;
    if(context->manager.hasComponent<BitsetT>(id))
    {
        BitsetT* bitset = context->manager.getEntityData<BitsetT>(id);
        if(bitset->test(0) && !bitset->test(1) && vel->x > -MOVE_SPEED)
        {
            vel->x = -MOVE_SPEED;
        }
        else if(bitset->test(1) && !bitset->test(0) && vel->x < MOVE_SPEED)
        {
            vel->x = MOVE_SPEED;
        }
    }
    pos->x += vel->x * DELTA_TIME;

    vel->x /= VEL_DAMPENING;
}

void CommonFns::collDetUpdateX(
    std::size_t id,
    void* ptr,
    ECStuff::Pos* pos,
    ECStuff::Size* size)
{
    Context* context = (Context*)ptr;
    if(context->manager.hasComponent<BitsetT>(id)
        && context->manager.getEntityData<BitsetT>(id)->test(8))
    {
        // do not collision check particles
        return;
    }
    float points[8] = {
        pos->x          , pos->y,
        pos->x + size->w, pos->y,
        pos->x + size->w, pos->y + size->h,
        pos->x,           pos->y + size->h
    };
    context->manager.forMatchingSignature<ColComponents>(
        [&context, &id, &points] (std::size_t cid, void* /*ptr*/,
                ECStuff::Pos* pos, ECStuff::Size* size) {
            if(id != cid && context->manager.isAlive(id) && context->manager.isAlive(cid))
//                        && context->revertPos.find(cid) == context->revertPos.end())
            {
                if(context->manager.hasComponent<BitsetT>(cid)
                    && context->manager.getEntityData<BitsetT>(cid)->test(8))
                {
                    // do not collision check particles
                    return;
                }
                else if(GDT::isWithinPolygon(points, 8, pos->x, pos->y)
                    || GDT::isWithinPolygon(points, 8, pos->x + size->w, pos->y)
                    || GDT::isWithinPolygon(points, 8, pos->x + size->w, pos->y + size->h)
                    || GDT::isWithinPolygon(points, 8, pos->x, pos->y + size->h)
                    || GDT::isWithinPolygon(points, 8, pos->x + size->w / 2.0f, pos->y + size->h / 2.0f))
                {
                    if(context->manager.hasComponent<BitsetT>(id)
                        && context->manager.hasComponent<BitsetT>(cid)
                        && ((context->manager.getEntityData<BitsetT>(id)->test(3)
                                && context->manager.getEntityData<BitsetT>(cid)->test(4))
                            || (context->manager.getEntityData<BitsetT>(id)->test(4)
                                && context->manager.getEntityData<BitsetT>(cid)->test(3))))
                    {
                        // is colliding with exit
                        context->globalFlags.set(0);
                    }
                    else if(context->manager.hasComponent<BitsetT>(id)
                        && context->manager.hasComponent<BitsetT>(cid)
                        && ((context->manager.getEntityData<BitsetT>(id)->test(3)
                                && context->manager.getEntityData<BitsetT>(cid)->test(5))
                            || (context->manager.getEntityData<BitsetT>(id)->test(5)
                                && context->manager.getEntityData<BitsetT>(cid)->test(3))))
                    {
                        // is colliding with fragment
                        if(context->manager.getEntityData<BitsetT>(id)->test(5))
                        {
                            context->manager.getEntityData<BitsetT>(id)->set(7);
                        }
                        else
                        {
                            context->manager.getEntityData<BitsetT>(cid)->set(7);
                        }
                    }
                    else if(context->manager.hasComponent<BitsetT>(id)
                        && context->manager.hasComponent<BitsetT>(cid)
                        && ((context->manager.getEntityData<BitsetT>(id)->test(3)
                                && context->manager.getEntityData<BitsetT>(cid)->test(11))
                            || (context->manager.getEntityData<BitsetT>(id)->test(11)
                                && context->manager.getEntityData<BitsetT>(cid)->test(3))))
                    {
                        // is colliding with death block
                        context->playSfx(2);
                        if(context->manager.getEntityData<BitsetT>(id)->test(3))
                        {
                            context->manager.deleteEntity(id);
                        }
                        else
                        {
                            context->manager.deleteEntity(cid);
                        }
                        context->globalFlags.set(1);
                    }
                    else if(context->manager.hasComponent<BitsetT>(id)
                        && context->manager.hasComponent<BitsetT>(cid)
                        && ((context->manager.getEntityData<BitsetT>(id)->test(3)
                                && context->manager.getEntityData<BitsetT>(cid)->test(14))
                            || (context->manager.getEntityData<BitsetT>(id)->test(14)
                                && context->manager.getEntityData<BitsetT>(cid)->test(3))))
                    {
                        // is colliding with key block
                        if(context->manager.getEntityData<BitsetT>(id)->test(3))
                        {
                            context->manager.deleteEntity(cid);
                        }
                        else
                        {
                            context->manager.deleteEntity(id);
                        }
                        context->globalFlags.set(2);
                    }
                    else
                    {
                        context->revertPos.insert(id);
                        context->revertPos.insert(cid);
                    }
                }
            }
        },
        nullptr);
}

void CommonFns::finUpdateX(
    std::size_t id,
    void* ptr,
    ECStuff::Pos* pos,
    ECStuff::Vel* vel)
{
    Context* context = (Context*)ptr;
    if(context->revertPos.find(id) != context->revertPos.end())
    {
        vel->x = pos->px - pos->x;
        pos->x = pos->px;
//                vel->x = 0.0f;
        context->revertPos.erase(id);
    }
}

void CommonFns::physUpdateY(
    std::size_t /*id*/,
    void* /*ptr*/,
    ECStuff::Pos* pos,
    ECStuff::Vel* vel,
    ECStuff::Acc* acc,
    ECStuff::Size* /*size*/)
{
    pos->py = pos->y;

    vel->y += acc->y * DELTA_TIME;
    pos->y += vel->y * DELTA_TIME;

    vel->y /= VEL_DAMPENING;
}

void CommonFns::collDetUpdateY(
    std::size_t id,
    void* ptr,
    ECStuff::Pos* pos,
    ECStuff::Size* size)
{
    Context* context = (Context*)ptr;
    if(context->manager.hasComponent<BitsetT>(id))
    {
        if(context->manager.getEntityData<BitsetT>(id)->test(8))
        {
            // do not collision check particles
            return;
        }
        context->manager.getEntityData<BitsetT>(id)->reset(10);
        context->manager.getEntityData<BitsetT>(id)->reset(2);
    }
    float points[8] = {
        pos->x          , pos->y,
        pos->x + size->w, pos->y,
        pos->x + size->w, pos->y + size->h,
        pos->x,           pos->y + size->h
    };
    context->manager.forMatchingSignature<ColComponents>(
        [&context, &id, &points] (std::size_t cid, void* /*ptr*/,
                ECStuff::Pos* pos, ECStuff::Size* size) {
            if(id != cid && context->manager.isAlive(id) && context->manager.isAlive(cid))
//                        && context->revertPos.find(cid) == context->revertPos.end())
            {
                if(context->manager.hasComponent<BitsetT>(cid)
                    && context->manager.getEntityData<BitsetT>(cid)->test(8))
                {
                    // do not collision check particles
                    return;
                }
                else if(GDT::isWithinPolygon(points, 8, pos->x, pos->y)
                    || GDT::isWithinPolygon(points, 8, pos->x + size->w, pos->y)
                    || GDT::isWithinPolygon(points, 8, pos->x + size->w, pos->y + size->h)
                    || GDT::isWithinPolygon(points, 8, pos->x, pos->y + size->h)
                    || GDT::isWithinPolygon(points, 8, pos->x + size->w / 2.0f, pos->y + size->h / 2.0f))
                {
                    if(context->manager.hasComponent<BitsetT>(id)
                        && context->manager.hasComponent<BitsetT>(cid)
                        && ((context->manager.getEntityData<BitsetT>(id)->test(3)
                                && context->manager.getEntityData<BitsetT>(cid)->test(4))
                            || (context->manager.getEntityData<BitsetT>(id)->test(4)
                                && context->manager.getEntityData<BitsetT>(cid)->test(3))))
                    {
                        // is colliding with exit
                        context->globalFlags.set(0);
                    }
                    else if(context->manager.hasComponent<BitsetT>(id)
                        && context->manager.hasComponent<BitsetT>(cid)
                        && ((context->manager.getEntityData<BitsetT>(id)->test(3)
                                && context->manager.getEntityData<BitsetT>(cid)->test(5))
                            || (context->manager.getEntityData<BitsetT>(id)->test(5)
                                && context->manager.getEntityData<BitsetT>(cid)->test(3))))
                    {
                        // is colliding with fragment
                        if(context->manager.getEntityData<BitsetT>(id)->test(5))
                        {
                            context->manager.getEntityData<BitsetT>(id)->set(7);
                        }
                        else
                        {
                            context->manager.getEntityData<BitsetT>(cid)->set(7);
                        }
                    }
                    else if(context->manager.hasComponent<BitsetT>(id)
                        && context->manager.hasComponent<BitsetT>(cid)
                        && ((context->manager.getEntityData<BitsetT>(id)->test(3)
                                && context->manager.getEntityData<BitsetT>(cid)->test(9))
                            || (context->manager.getEntityData<BitsetT>(id)->test(9)
                                && context->manager.getEntityData<BitsetT>(cid)->test(3))))
                    {
                        // is colliding with spring
                        if(context->manager.getEntityData<BitsetT>(id)->test(3))
                        {
                            context->manager.getEntityData<BitsetT>(id)->set(10);
                        }
                        else
                        {
                            context->manager.getEntityData<BitsetT>(cid)->set(10);
                        }
                        context->revertPos.insert(id);
                        context->revertPos.insert(cid);
                    }
                    else if(context->manager.hasComponent<BitsetT>(id)
                        && context->manager.hasComponent<BitsetT>(cid)
                        && ((context->manager.getEntityData<BitsetT>(id)->test(3)
                                && context->manager.getEntityData<BitsetT>(cid)->test(11))
                            || (context->manager.getEntityData<BitsetT>(id)->test(11)
                                && context->manager.getEntityData<BitsetT>(cid)->test(3))))
                    {
                        // is colliding with death block
                        context->playSfx(2);
                        if(context->manager.getEntityData<BitsetT>(id)->test(3))
                        {
                            context->manager.deleteEntity(id);
                        }
                        else
                        {
                            context->manager.deleteEntity(cid);
                        }
                        context->globalFlags.set(1);
                    }
                    else if(context->manager.hasComponent<BitsetT>(id)
                        && context->manager.hasComponent<BitsetT>(cid)
                        && ((context->manager.getEntityData<BitsetT>(id)->test(3)
                                && context->manager.getEntityData<BitsetT>(cid)->test(12))
                            || (context->manager.getEntityData<BitsetT>(id)->test(12)
                                && context->manager.getEntityData<BitsetT>(cid)->test(3))))
                    {
                        // is colliding with auto spring
                        if(context->manager.getEntityData<BitsetT>(id)->test(3))
                        {
                            context->manager.getEntityData<BitsetT>(id)->set(13);
                        }
                        else
                        {
                            context->manager.getEntityData<BitsetT>(cid)->set(13);
                        }
                    }
                    else if(context->manager.hasComponent<BitsetT>(id)
                        && context->manager.hasComponent<BitsetT>(cid)
                        && ((context->manager.getEntityData<BitsetT>(id)->test(3)
                                && context->manager.getEntityData<BitsetT>(cid)->test(14))
                            || (context->manager.getEntityData<BitsetT>(id)->test(14)
                                && context->manager.getEntityData<BitsetT>(cid)->test(3))))
                    {
                        // is colliding with key block
                        if(context->manager.getEntityData<BitsetT>(id)->test(3))
                        {
                            context->manager.deleteEntity(cid);
                        }
                        else
                        {
                            context->manager.deleteEntity(id);
                        }
                        context->globalFlags.set(2);
                    }
                    else
                    {
                        context->revertPos.insert(id);
                        context->revertPos.insert(cid);
                    }
                }
            }
        },
        nullptr);
}

void CommonFns::finUpdateY(
    std::size_t id,
    void* ptr,
    ECStuff::Pos* pos,
    ECStuff::Vel* vel)
{
    Context* context = (Context*)ptr;
    if(context->revertPos.find(id) != context->revertPos.end())
    {
        vel->y = pos->py - pos->y;
        if(context->manager.hasComponent<BitsetT>(id) && vel->y < 0.0f)
        {
            context->manager.getEntityData<BitsetT>(id)->set(2);
        }
        pos->y = pos->py;
//                vel->y = 0.0f;
        context->revertPos.erase(id);
    }

    if(context->manager.hasComponent<BitsetT>(id))
    {
        BitsetT* bitset = context->manager.getEntityData<BitsetT>(id);
        if(bitset->test(3) && bitset->test(13))
        {
            bitset->reset(2);
            bitset->reset(13);
            context->playSfx(1);
            vel->y -= JUMP_SPRING_VEL;
            CommonFns::createPlayerFragment(*context);
        }
    }
}

void CommonFns::updateFragments(std::size_t id, void* ptr, BitsetT* bitset)
{
    if(bitset->test(5))
    {
        if(bitset->test(7))
        {
            Context* context = (Context*)ptr;
            if(bitset->test(6) && !context->globalFlags.test(1))
            {
                // player touched fragment, increase player
                context->manager.deleteEntity(id);
                ECStuff::Pos* ppos = context->manager.getEntityData<ECStuff::Pos>(context->playerID);
                ECStuff::Size* psize = context->manager.getEntityData<ECStuff::Size>(context->playerID);
                ppos->x -= 0.5f;
                ppos->y -= 1.0f;
                context->currentSize += 1;
                psize->w = context->currentSize;
                psize->h = context->currentSize;
            }
            bitset->reset(7);
        }
        else
        {
            bitset->set(6);
        }
    }
}

void CommonFns::updateParticles(
    std::size_t id,
    void* ptr,
    ECStuff::Pos* pos,
    ECStuff::Size* size,
    ECStuff::ParticleGen* particle)
{
    Context* context = (Context*)ptr;
    switch(particle->type)
    {
    case 0:
        particle->timer -= DELTA_TIME;
        if(particle->timer <= 0.0f)
        {
            context->manager.deleteEntity(id);
        }
        break;
    case 1:
        particle->timer -= DELTA_TIME;
        if(particle->timer <= 0.0f)
        {
            particle->timer = PARTICLE1_GENTIME;
            auto pid = context->manager.addEntity();
            context->manager.addComponent<ECStuff::Pos>(pid,
                pos->x + size->w / 2.0f,
                pos->y + size->h / 2.0f);
            context->manager.addComponent<ECStuff::Vel>(pid,
                std::uniform_real_distribution<float>(
                    -RNG_PART_VEL, RNG_PART_VEL)(context->rng),
                std::uniform_real_distribution<float>(
                    -RNG_PART_VEL, RNG_PART_VEL)(context->rng));
            context->manager.addComponent<ECStuff::Acc>(pid,
                std::uniform_real_distribution<float>(
                    -RNG_PART_ACC, RNG_PART_ACC)(context->rng),
                std::uniform_real_distribution<float>(
                    -RNG_PART_ACC, RNG_PART_ACC)(context->rng));
            context->manager.addComponent<ECStuff::Size>(pid,
                1.0f, 1.0f);
            context->manager.addComponent<ECStuff::ParticleGen>(pid);
            context->manager.getEntityData<ECStuff::ParticleGen>(pid)->timer = PARTICLE1_GEN_LIFETIME;
            context->manager.addComponent<ECStuff::Drawable>(pid,
                255, 255, 255, 255);
            context->manager.addComponent<BitsetT>(pid);
            context->manager.getEntityData<BitsetT>(pid)->set(8);
        }
        break;
    case 2:
        particle->timer -= DELTA_TIME;
        if(particle->timer <= 0.0f)
        {
            context->manager.deleteEntity(id);
        }
        else
        {
            size->w += PARTICLE2_GROWTH_RATE;
            size->h += PARTICLE2_GROWTH_RATE;
            pos->x -= PARTICLE2_GROWTH_RATE / 2.0f;
            pos->y -= PARTICLE2_GROWTH_RATE / 2.0f;
            ECStuff::Drawable* drawable = context->manager.getEntityData<ECStuff::Drawable>(id);
            if((int)drawable->a - PARTICLE2_FADE_RATE <= 0)
            {
                drawable->a = 0;
            }
            else
            {
                drawable->a -= PARTICLE2_FADE_RATE;
            }
        }
        break;
    case 3:
        particle->timer -= DELTA_TIME;
        if(particle->timer <= 0.0f)
        {
            particle->timer = PARTICLE3_GENTIME
                + std::uniform_real_distribution<float>(
                    -PARTICLE3_GENTIME_VAR, PARTICLE3_GENTIME_VAR)
                    (context->rng);
            auto pid = context->manager.addEntity();
            context->manager.addComponent<ECStuff::Pos>(pid,
                pos->x,
                pos->y);
            context->manager.addComponent<ECStuff::Vel>(pid);
            context->manager.addComponent<ECStuff::Acc>(pid);
            context->manager.addComponent<ECStuff::Size>(pid,
                size->w, size->h);
            context->manager.addComponent<ECStuff::ParticleGen>(pid, 2);
            context->manager.getEntityData<ECStuff::ParticleGen>(pid)->timer =
                PARTICLE3_GEN_LIFETIME;
            context->manager.addComponent<ECStuff::Drawable>(pid,
                128 + std::uniform_int_distribution<unsigned char>(0, 127)
                    (context->rng),
                128 + std::uniform_int_distribution<unsigned char>(0, 127)
                    (context->rng),
                128 + std::uniform_int_distribution<unsigned char>(0, 127)
                    (context->rng),
                255);
            context->manager.addComponent<BitsetT>(pid);
            context->manager.getEntityData<BitsetT>(pid)->set(8);
        }
        break;
    default:
        break;
    }
}

void CommonFns::createPlayerFragment(Context& context)
{
    if(context.globalFlags.test(1))
    {
        return;
    }

    // create fragment
    auto id = context.manager.addEntity();
    ECStuff::Pos* ppos = context.manager.getEntityData<ECStuff::Pos>(context.playerID);
    ECStuff::Size* psize = context.manager.getEntityData<ECStuff::Size>(context.playerID);
    context.manager.addComponent<ECStuff::Pos>(id,
        ppos->x + psize->w / 2.0f - 2.0f,
        ppos->y + psize->h * 3.0f / 4.0f - 2.0f);
    context.manager.addComponent<ECStuff::Size>(id, 4.0f, 4.0f);
    context.manager.addComponent<BitsetT>(id);
    context.manager.getEntityData<BitsetT>(id)->set(5);
    context.manager.getEntityData<BitsetT>(id)->set(7);
    context.manager.addComponent<ECStuff::Drawable>(id);
    context.manager.addComponent<ECStuff::ParticleGen>(id, 1);

    // reduce player
    context.currentSize -= 1;
    if(context.currentSize <= 1)
    {
        // player reduced too much, player now dead
        context.playSfx(2);
        context.manager.deleteEntity(context.playerID);
        context.globalFlags.set(1);
    }
    ppos->x += 0.5f;
    ppos->y += 0.5f;
    psize->w = context.currentSize;
    psize->h = context.currentSize;
}
