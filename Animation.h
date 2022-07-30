#pragma once
#include "libs.h"
#include<SFML/Graphics.hpp>
using namespace sf;

/// <summary>
/// �������� ������� ��������
/// </summary>
class Animation
    {
    public:
        float Frame, speed;
        Sprite sprite;
        std::vector<IntRect> frames;

        Animation();
        /// <summary>
        /// �������� ����������� �� ����� ������� ����� ������������ ����� ��������
        /// </summary>
        /// <param name="t">��������</param>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <param name="w"></param>
        /// <param name="h"></param>
        /// <param name="count"></param>
        /// <param name="Speed"></param>
        Animation(Texture& t, int x, int y, int w, int h, int count, float Speed);

        void update();

        bool isEnd();

    };

