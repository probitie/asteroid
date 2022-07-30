#pragma once
#include "Entity.h"

class Player : public Entity
/// класс игрока
{
public:
    bool thrust; // движение игрока

    Player();

    // изменение обьекта за каждый такт
    void update();

};


