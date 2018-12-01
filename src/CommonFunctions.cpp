#include "CommonFunctions.hpp"

#include <GDT/CollisionDetection.hpp>

void CommonFns::cleanupLevel(const std::unordered_set<std::size_t> preserveSet, ManagerT& manager)
{
    manager.forMatchingSignature<EC::Meta::TypeList<>>(
        [&preserveSet] (std::size_t id, void* ptr) {
            if(preserveSet.find(id) == preserveSet.end())
            {
                ManagerT* manager = (ManagerT*)ptr;
                manager->deleteEntity(id);
            }
        },
        &manager);
}

void CommonFns::loadLevel(const unsigned int id, ManagerT& manager)
{
    switch(id)
    {
    case 0:
    {
        // ground
        auto id = manager.addEntity();
        manager.addComponent<ECStuff::Pos>(id, 100.0f, 270.0f - 50.0f);
        manager.addComponent<ECStuff::Size>(id, 100.0f, 50.0f);
        manager.addComponent<ECStuff::Drawable>(id, 255, 128, 0);
        id = manager.addEntity();
        manager.addComponent<ECStuff::Pos>(id, 200.0f, 270.0f - 100.0f);
        manager.addComponent<ECStuff::Size>(id, 100.0f, 100.0f);
        manager.addComponent<ECStuff::Drawable>(id, 255, 128, 0);
        id = manager.addEntity();
        manager.addComponent<ECStuff::Pos>(id, 300.0f, 270.0f - 150.0f);
        manager.addComponent<ECStuff::Size>(id, 100.0f, 150.0f);
        manager.addComponent<ECStuff::Drawable>(id, 255, 128, 0);

        // exit
        id = manager.addEntity();
        manager.addComponent<ECStuff::Pos>(id, 435.0f, 270.0f - 40.0f);
        manager.addComponent<ECStuff::Size>(id, 30.0f, 30.0f);
        manager.addComponent<ECStuff::Drawable>(id, 128, 128, 255);
        manager.addComponent<BitsetT>(id);
        manager.getEntityData<BitsetT>(id)->set(4);
    }
        break;
    case 1:
    {
        // ground
        auto id = manager.addEntity();
        manager.addComponent<ECStuff::Pos>(id, 200.0f, 270.0f - 50.0f);
        manager.addComponent<ECStuff::Size>(id, 100.0f, 50.0f);
        manager.addComponent<ECStuff::Drawable>(id, 255, 128, 0);
        id = manager.addEntity();
        manager.addComponent<ECStuff::Pos>(id, 80.0f, 270.0f - 150.0f);
        manager.addComponent<ECStuff::Size>(id, 400.0f, 10.0f);
        manager.addComponent<ECStuff::Drawable>(id, 255, 128, 0);
        id = manager.addEntity();
        manager.addComponent<ECStuff::Pos>(id, 200.0f, 270.0f - 200.0f);
        manager.addComponent<ECStuff::Size>(id, 100.0f, 50.0f);
        manager.addComponent<ECStuff::Drawable>(id, 255, 128, 0);

        // spring
        id = manager.addEntity();
        manager.addComponent<ECStuff::Pos>(id, 10.0f, 270.0f - 10.0f);
        manager.addComponent<ECStuff::Size>(id, 50.0f, 10.0f);
        manager.addComponent<ECStuff::Drawable>(id, 128, 255, 128);
        manager.addComponent<BitsetT>(id);
        manager.getEntityData<BitsetT>(id)->set(9);

        //exit
        id = manager.addEntity();
        manager.addComponent<ECStuff::Pos>(id, 435.0f, 270.0f - 200.0f);
        manager.addComponent<ECStuff::Size>(id, 30.0f, 30.0f);
        manager.addComponent<ECStuff::Drawable>(id, 128, 128, 255);
        manager.addComponent<BitsetT>(id);
        manager.getEntityData<BitsetT>(id)->set(4);
    }
        break;
    default:
        fprintf(stderr, "ERROR: loadLevel got invalid level id!\n");
        break;
    }
}

void CommonFns::resetWorld(ManagerT& manager, Context& context)
{
    manager.reset();
    loadManagerFns(manager, &context);
    context.preserveSet.clear();
    context.currentLevel = 0;
    context.currentSize = 50;

    // create player
    auto playerID = manager.addEntity();
    manager.addComponent<ECStuff::Pos>(playerID, 2.0f, 200.0f);
    manager.addComponent<ECStuff::Vel>(playerID);
    manager.addComponent<ECStuff::Acc>(playerID, 0.0f, GRAVITY_ACC);
    manager.addComponent<ECStuff::Size>(playerID, 50.0f, 50.0f);
    manager.addComponent<ECStuff::Drawable>(playerID);
    manager.addComponent<BitsetT>(playerID);
    manager.getEntityData<BitsetT>(playerID)->set(3);
    context.preserveSet.insert(playerID);
    context.playerID = playerID;
    context.globalFlags.reset(1);

    // create world boundaries
    auto id = manager.addEntity();
    manager.addComponent<ECStuff::Pos>(id, -50.0f, 0.0f);
    manager.addComponent<ECStuff::Vel>(id);
    manager.addComponent<ECStuff::Acc>(id);
    manager.addComponent<ECStuff::Size>(id, 50.0f, 270.0f);
    context.preserveSet.insert(id);

    id = manager.addEntity();
    manager.addComponent<ECStuff::Pos>(id, 0.0f, 270.0f);
    manager.addComponent<ECStuff::Vel>(id);
    manager.addComponent<ECStuff::Acc>(id);
    manager.addComponent<ECStuff::Size>(id, 480.0f, 50.0f);
    context.preserveSet.insert(id);

    id = manager.addEntity();
    manager.addComponent<ECStuff::Pos>(id, 480.0f, 0.0f);
    manager.addComponent<ECStuff::Vel>(id);
    manager.addComponent<ECStuff::Acc>(id);
    manager.addComponent<ECStuff::Size>(id, 50.0f, 270.0f);
    context.preserveSet.insert(id);

    id = manager.addEntity();
    manager.addComponent<ECStuff::Pos>(id, 0.0f, -50.0f);
    manager.addComponent<ECStuff::Vel>(id);
    manager.addComponent<ECStuff::Acc>(id);
    manager.addComponent<ECStuff::Size>(id, 480.0f, 50.0f);
    context.preserveSet.insert(id);
}

void CommonFns::loadManagerFns(ManagerT& manager, Context* context)
{
    manager.addForMatchingFunction<PhysComponents>(
        CommonFns::physUpdateX,
        context);
    manager.addForMatchingFunction<ColComponents>(
        CommonFns::collDetUpdateX,
        context);
    manager.addForMatchingFunction<ColFinComponents>(
        CommonFns::finUpdateX,
        context);
    manager.addForMatchingFunction<PhysComponents>(
        CommonFns::physUpdateY,
        context);
    manager.addForMatchingFunction<ColComponents>(
        CommonFns::collDetUpdateY,
        context);
    manager.addForMatchingFunction<ColFinComponents>(
        CommonFns::finUpdateY,
        context);
    manager.addForMatchingFunction<FragmentComponents>(
        CommonFns::updateFragments,
        context);
    manager.addForMatchingFunction<ParticleComponents>(
        CommonFns::updateParticles,
        context);
}

void CommonFns::physUpdateX(
    std::size_t id,
    void* ptr,
    ECStuff::Pos* pos,
    ECStuff::Vel* vel,
    ECStuff::Acc* acc,
    ECStuff::Size* size)
{
    Context* context = (Context*)ptr;
    pos->px = pos->x;

    vel->x += acc->x * DELTA_TIME;
    if(context->manager->hasComponent<BitsetT>(id))
    {
        BitsetT* bitset = context->manager->getEntityData<BitsetT>(id);
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
    if(context->manager->hasComponent<BitsetT>(id)
        && context->manager->getEntityData<BitsetT>(id)->test(8))
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
    context->manager->forMatchingSignature<ColComponents>(
        [&context, &id, &points] (std::size_t cid, void* ptr,
                ECStuff::Pos* pos, ECStuff::Size* size) {
            if(id != cid)
//                        && context->revertPos.find(cid) == context->revertPos.end())
            {
                if(context->manager->hasComponent<BitsetT>(cid)
                    && context->manager->getEntityData<BitsetT>(cid)->test(8))
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
                    if(context->manager->hasComponent<BitsetT>(id)
                        && context->manager->hasComponent<BitsetT>(cid)
                        && ((context->manager->getEntityData<BitsetT>(id)->test(3)
                                && context->manager->getEntityData<BitsetT>(cid)->test(4))
                            || (context->manager->getEntityData<BitsetT>(id)->test(4)
                                && context->manager->getEntityData<BitsetT>(cid)->test(3))))
                    {
                        // is colliding with exit
                        context->globalFlags.set(0);
                    }
                    else if(context->manager->hasComponent<BitsetT>(id)
                        && context->manager->hasComponent<BitsetT>(cid)
                        && ((context->manager->getEntityData<BitsetT>(id)->test(3)
                                && context->manager->getEntityData<BitsetT>(cid)->test(5))
                            || (context->manager->getEntityData<BitsetT>(id)->test(5)
                                && context->manager->getEntityData<BitsetT>(cid)->test(3))))
                    {
                        // is colliding with fragment
                        if(context->manager->getEntityData<BitsetT>(id)->test(5))
                        {
                            context->manager->getEntityData<BitsetT>(id)->set(7);
                        }
                        else
                        {
                            context->manager->getEntityData<BitsetT>(cid)->set(7);
                        }
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
    std::size_t id,
    void* ptr,
    ECStuff::Pos* pos,
    ECStuff::Vel* vel,
    ECStuff::Acc* acc,
    ECStuff::Size* size)
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
    if(context->manager->hasComponent<BitsetT>(id))
    {
        if(context->manager->getEntityData<BitsetT>(id)->test(8))
        {
            // do not collision check particles
            return;
        }
        context->manager->getEntityData<BitsetT>(id)->reset(10);
    }
    float points[8] = {
        pos->x          , pos->y,
        pos->x + size->w, pos->y,
        pos->x + size->w, pos->y + size->h,
        pos->x,           pos->y + size->h
    };
    context->manager->forMatchingSignature<ColComponents>(
        [&context, &id, &points] (std::size_t cid, void* ptr,
                ECStuff::Pos* pos, ECStuff::Size* size) {
            if(id != cid)
//                        && context->revertPos.find(cid) == context->revertPos.end())
            {
                if(context->manager->hasComponent<BitsetT>(cid)
                    && context->manager->getEntityData<BitsetT>(cid)->test(8))
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
                    if(context->manager->hasComponent<BitsetT>(id)
                        && context->manager->hasComponent<BitsetT>(cid)
                        && ((context->manager->getEntityData<BitsetT>(id)->test(3)
                                && context->manager->getEntityData<BitsetT>(cid)->test(4))
                            || (context->manager->getEntityData<BitsetT>(id)->test(4)
                                && context->manager->getEntityData<BitsetT>(cid)->test(3))))
                    {
                        // is colliding with exit
                        context->globalFlags.set(0);
                    }
                    else if(context->manager->hasComponent<BitsetT>(id)
                        && context->manager->hasComponent<BitsetT>(cid)
                        && ((context->manager->getEntityData<BitsetT>(id)->test(3)
                                && context->manager->getEntityData<BitsetT>(cid)->test(5))
                            || (context->manager->getEntityData<BitsetT>(id)->test(5)
                                && context->manager->getEntityData<BitsetT>(cid)->test(3))))
                    {
                        // is colliding with fragment
                        if(context->manager->getEntityData<BitsetT>(id)->test(5))
                        {
                            context->manager->getEntityData<BitsetT>(id)->set(7);
                        }
                        else
                        {
                            context->manager->getEntityData<BitsetT>(cid)->set(7);
                        }
                    }
                    else if(context->manager->hasComponent<BitsetT>(id)
                        && context->manager->hasComponent<BitsetT>(cid)
                        && ((context->manager->getEntityData<BitsetT>(id)->test(3)
                                && context->manager->getEntityData<BitsetT>(cid)->test(9))
                            || (context->manager->getEntityData<BitsetT>(id)->test(9)
                                && context->manager->getEntityData<BitsetT>(cid)->test(3))))
                    {
                        // is colliding with spring
                        if(context->manager->getEntityData<BitsetT>(id)->test(3))
                        {
                            context->manager->getEntityData<BitsetT>(id)->set(10);
                        }
                        else
                        {
                            context->manager->getEntityData<BitsetT>(cid)->set(10);
                        }
                        context->revertPos.insert(id);
                        context->revertPos.insert(cid);
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
        if(context->manager->hasComponent<BitsetT>(id) && vel->y < 0.0f)
        {
            context->manager->getEntityData<BitsetT>(id)->set(2);
        }
        pos->y = pos->py;
//                vel->y = 0.0f;
        context->revertPos.erase(id);
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
                context->manager->deleteEntity(id);
                ECStuff::Pos* ppos = context->manager->getEntityData<ECStuff::Pos>(context->playerID);
                ECStuff::Size* psize = context->manager->getEntityData<ECStuff::Size>(context->playerID);
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
            context->manager->deleteEntity(id);
        }
        break;
    case 1:
        particle->timer -= DELTA_TIME;
        if(particle->timer <= 0.0f)
        {
            particle->timer = PARTICLE1_GENTIME;
            auto pid = context->manager->addEntity();
            context->manager->addComponent<ECStuff::Pos>(pid,
                pos->x + size->w / 2.0f,
                pos->y + size->h / 2.0f);
            context->manager->addComponent<ECStuff::Vel>(pid,
                std::uniform_real_distribution<float>(
                    -RNG_PART_VEL, RNG_PART_VEL)(context->rng),
                std::uniform_real_distribution<float>(
                    -RNG_PART_VEL, RNG_PART_VEL)(context->rng));
            context->manager->addComponent<ECStuff::Acc>(pid,
                std::uniform_real_distribution<float>(
                    -RNG_PART_ACC, RNG_PART_ACC)(context->rng),
                std::uniform_real_distribution<float>(
                    -RNG_PART_ACC, RNG_PART_ACC)(context->rng));
            context->manager->addComponent<ECStuff::Size>(pid,
                1.0f, 1.0f);
            context->manager->addComponent<ECStuff::ParticleGen>(pid);
            context->manager->getEntityData<ECStuff::ParticleGen>(pid)->timer = PARTICLE1_GEN_LIFETIME;
            context->manager->addComponent<ECStuff::Drawable>(pid,
                255, 255, 255, 255);
            context->manager->addComponent<BitsetT>(pid);
            context->manager->getEntityData<BitsetT>(pid)->set(8);
        }
        break;
    default:
        break;
    }
}
