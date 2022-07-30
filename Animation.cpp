#include "Animation.h"

Animation::Animation() {}
/// <summary>
/// текстура разбивается на части которые будут образовывать кадры анимации
/// </summary>
/// <param name="t">текстура</param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="w"></param>
/// <param name="h"></param>
/// <param name="count"></param>
/// <param name="Speed"></param>
Animation::Animation(Texture& t, int x, int y, int w, int h, int count, float Speed)
{
    Frame = 0;
    speed = Speed;

    for (int i = 0;i < count;i++)
        frames.push_back(IntRect(x + i * w, y, w, h));

    sprite.setTexture(t);
    sprite.setOrigin(w / 2, h / 2);
    sprite.setTextureRect(frames[0]);
}


void Animation::update()
{
    Frame += speed;
    int n = frames.size();
    if (Frame >= n) Frame -= n;
    if (n > 0) sprite.setTextureRect(frames[int(Frame)]);
}

bool Animation::isEnd()
{
    return Frame + speed >= frames.size();
}