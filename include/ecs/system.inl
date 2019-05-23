EntityManager<Soldier> MovementSystem::soldiers;

void MovementSystem::init()
{
    for(size_t i = 0; i < 4; ++i)
        soldiers.createEntity();
}

void MovementSystem::update()
{
    soldiers.printEntities();

    std::cout << "----------------" << std::endl;
    std::cout << "MOVEMENT SYSTEM:" << std::endl;
    std::cout << "----------------" << std::endl;

    Soldier* soldier;
    List<BaseComponent*>& memory = ComponentManager::getComponentMemory<Transform>();
    List<BaseComponent*>::iterator i;
    for(i = memory.begin(); i != memory.end(); ++i)
    {
        soldier = (Soldier*)((*i)->entity);
        soldier->getTransform()->position.x += soldier->getStats()->velocity;
        soldier->getTransform()->position.y += soldier->getStats()->velocity;
        soldier->getTransform()->position.z += soldier->getStats()->velocity;
    }

    soldiers.printEntities();
}

void MovementSystem::destroy()
{
    soldiers.clear();
}
