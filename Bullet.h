#pragma once
#include "Entity.h"
class Bullet : public Entity
    // класс снаряда, выпущеного игроком
{
public:
    Bullet();

    // обновление позиции за каждый такт
    void  update();

};
