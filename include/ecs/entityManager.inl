// ENTITIES
// --------

void EmptyEntity::init(uint32 _ID)
{
    this->ID = _ID;
    Transform* transform = ComponentManager::createComponent<Transform>(this);
    transform->position = { 17.5f, 17.5f, 17.5f };
    transform->scale    = { 18.5f, 18.5f, 18.5f };
    transform->rotation = { 27.5f, 27.5f, 27.5f };

    components.push_back(transform);
}

void EmptyEntity::destroy()
{
    if(!ComponentManager::deleteComponent<Transform>(this))
        std::cerr << "Something went wrong with this entity!" << std::endl;
}

void Soldier::init(uint32 _ID)
{
    this->ID = _ID;
    Transform* transform = ComponentManager::createComponent<Transform>(this);
    transform->position = { 17.5f, 17.5f, 17.5f };
    transform->scale    = { 18.5f, 18.5f, 18.5f };
    transform->rotation = { 27.5f, 27.5f, 27.5f };

    Stats* stats = ComponentManager::createComponent<Stats>(this);
    stats->hp = 100.0f;
    stats->damage   = 20.0f;
    stats->defense  = 10.0f;
    stats->velocity = 0.5f;

    components.push_back(transform);
    components.push_back(stats);
}

void Soldier::destroy()
{
    if(!ComponentManager::deleteComponent<Transform>(this))
        std::cerr << "Something went wrong with this entity!" << std::endl;
    if(!ComponentManager::deleteComponent<Stats>(this))
        std::cerr << "Something went wrong with this entity!" << std::endl;
}

std::ostream& operator<<(std::ostream& o, Vec3& v)
{
    o << '(' << v.x << ", " << v.y << ", " << v.z << ')';
    return o;
}

void EmptyEntity::print()
{
    Transform* transform = (Transform*)components[0];
    std::cout << "TRANSFORM COMPONENT:\n--------------------" << std::endl;
    std::cout << "Position:\t";
    std::cout << transform->position << std::endl;
    std::cout << "Rotation:\t";
    std::cout << transform->rotation << std::endl;
    std::cout << "Scale:\t\t";
    std::cout << transform->scale << std::endl;
    std::cout << std::endl;
}

void Soldier::print()
{
    std::cout << "------------------------------------" << std::endl;
    std::cout << "Soldier Nr. " << ID << "                      ]" << std::endl;
    std::cout << "------------------------------------" << std::endl;

    Transform* transform = getTransform();
    Stats* stats = getStats();
    std::cout << "TRANSFORM COMPONENT:\n--------------------" << std::endl;
    std::cout << "Position:\t";
    std::cout << transform->position << std::endl;
    std::cout << "Rotation:\t";
    std::cout << transform->rotation << std::endl;
    std::cout << "Scale:\t\t";
    std::cout << transform->scale << std::endl;
    std::cout << std::endl;

    std::cout << "STATS COMPONENT:\n--------------------" << std::endl;
    std::cout << "HP:\t\t";
    std::cout << stats->hp << std::endl;
    std::cout << "Damage:\t\t";
    std::cout << stats->damage << std::endl;
    std::cout << "Defense:\t";
    std::cout << stats->damage << std::endl;
    std::cout << "Velocity:\t";
    std::cout << stats->velocity << std::endl;

    std::cout << "------------------------------------" << std::endl;
}

// ENTITY MANAGER DEFINITIONS
// --------------------------

template <typename E>
E* EntityManager<E>::createEntity()
{
    // Ensure The Type is actually an Entity
    static_assert(std::is_base_of<Entity, E>::value, "The E type MUST be an Entity");

    E* entity = new E;
    entity->init(currentID++);

    entities.push_back(entity);

    return entity;
}

template <typename E>
bool EntityManager<E>::removeEntity(E* entity)
{
    List<Entity*>::iterator i;
    for(i = entities.begin(); i != entities.end(); ++i)
        if((*i)->ID == entity->ID)
        {
            (*i)->destroy();
            delete (*i);
            entities.erase(i);
            return true;
        }
    
    return false;
}

template <typename E>
void EntityManager<E>::clear()
{
    List<Entity*>::iterator i;
    for(i = entities.begin(); i != entities.end(); ++i)
    {
        (*i)->destroy();
        delete (*i);
    }
    entities.clear();
}

template <typename E>
void EntityManager<E>::printEntities()
{
    List<Entity*>::iterator i;
    for(i = entities.begin(); i != entities.end(); ++i)
        (*i)->print();
}
