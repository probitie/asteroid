#pragma once
#include<SFML/Graphics.hpp>
#include "Animation.h"
#include "libs.h"


using namespace sf;


/// <summary>
/// базовый класс для игровых обьектов
/// </summary>
class Entity
    {
    public:
        // повышеная точность не нужна
        float x, y, dx, dy, R, angle;
        bool life; // существует ли обьект в игре в данный момент
        std::string name;
        Animation anim;

        Entity();

        /// <summary>
        /// инициализация полей обьекта после его создания
        /// </summary>
        /// <param name="a">анимация</param>
        /// <param name="X">абсцисса</param>
        /// <param name="Y">ордината</param>
        /// <param name="Angle">угол поворота относительно Х</param>
        /// <param name="radius">радиус хитбокса</param>
        void settings(Animation& a, int X, int Y, float Angle = 0, int radius = 1);

        virtual void update();

        void draw(RenderWindow& app);

        virtual ~Entity();
    };


