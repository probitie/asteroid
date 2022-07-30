#pragma once
#include<SFML/Graphics.hpp>
#include "Animation.h"
#include "libs.h"


using namespace sf;


/// <summary>
/// ������� ����� ��� ������� ��������
/// </summary>
class Entity
    {
    public:
        // ��������� �������� �� �����
        float x, y, dx, dy, R, angle;
        bool life; // ���������� �� ������ � ���� � ������ ������
        std::string name;
        Animation anim;

        Entity();

        /// <summary>
        /// ������������� ����� ������� ����� ��� ��������
        /// </summary>
        /// <param name="a">��������</param>
        /// <param name="X">��������</param>
        /// <param name="Y">��������</param>
        /// <param name="Angle">���� �������� ������������ �</param>
        /// <param name="radius">������ ��������</param>
        void settings(Animation& a, int X, int Y, float Angle = 0, int radius = 1);

        virtual void update();

        void draw(RenderWindow& app);

        virtual ~Entity();
    };


