#ifndef ECS_COMPONENT_H
#define ECS_COMPONENT_H

#include "system/common.hpp"

class Entity;

struct BaseComponent
{
    Entity* entity;
};

template <typename T>
struct Component : public BaseComponent
{
    static const uint32 ID;
    static const uint32 SIZE;
};

struct Vec3
{
    float x;
    float y;
    float z;
};

struct Transform : public Component<Transform>
{
    Vec3 position;
    Vec3 rotation;
    Vec3 scale;
};

struct BoxCollider : public Component<BoxCollider>
{
    bool isTrigger;
    Vec3 center;
    Vec3 size;
};

struct Stats : public Component<Stats>
{
    float hp;
    float damage;
    float defense;
    float velocity;
};

#endif // ECS_COMPONENT_H
