#ifndef ECS_H
#define ECS_H

#include "ecs/componentManager.hpp"
#include "ecs/entityManager.hpp"
#include "ecs/system.hpp"

#ifdef ECS_IMPLEMENTATION
    #include "ecs/componentManager.inl"
    #include "ecs/entityManager.inl"
    #include "ecs/system.inl"
#endif

#endif // ECS_H
