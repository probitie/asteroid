#include "libs.h"
#include "Entity.h"
#include "player.h"
#include "asteroid.h"
#include "bullet.h"
#include "Entity.h"

/// проверка столкновения двух сущностей
bool isCollide(Entity* a, Entity* b)
{
    return (b->x - a->x) * (b->x - a->x) +
        (b->y - a->y) * (b->y - a->y) <
        (a->R + b->R) * (a->R + b->R);
}

int main()
{
    srand(time(0));

    RenderWindow app(VideoMode(W, H), "Spaceship"); // рендерим окно
    app.setFramerateLimit(60); // фпс

    // загрузка текстур с файла
    Texture spaceship_texture, background_texture, explosion_c_texture, rock_texture, fire_red_texture, rock_small_texture, explosion_b_texture;
    spaceship_texture.loadFromFile("images/spaceship.png");
    background_texture.loadFromFile("images/background.jpg");
    explosion_c_texture.loadFromFile("images/explosions/type_C.png");
    rock_texture.loadFromFile("images/rock.png");
    fire_red_texture.loadFromFile("images/fire_red.png");
    rock_small_texture.loadFromFile("images/rock_small.png");
    explosion_b_texture.loadFromFile("images/explosions/type_B.png");

    // размытие текстур
    spaceship_texture.setSmooth(true);
    background_texture.setSmooth(true);
    rock_texture.setSmooth(true);


    Sprite background(background_texture);
    
    Animation sExplosion(explosion_c_texture, 0, 0, 256, 256, 48, 0.5);
    Animation sRock(rock_texture, 0, 0, 64, 64, 16, 0.2);
    Animation sRock_small(rock_small_texture, 0, 0, 64, 64, 16, 0.2);
    Animation sBullet(fire_red_texture, 0, 0, 32, 64, 16, 0.8);
    Animation sPlayer(spaceship_texture, 40, 0, 40, 40, 1, 0);
    Animation sPlayer_go(spaceship_texture, 40, 40, 40, 40, 1, 0);
    Animation sExplosion_ship(explosion_b_texture, 0, 0, 192, 192, 64, 0.5);


    std::list<Entity*> entities;

    // добавляем 15 астероидов в начале
    for (int i = 0;i < 15;i++)
    {
        Asteroid* a = new Asteroid();
        a->settings(sRock, rand() % W, rand() % H, rand() % 360, 25);
        entities.push_back(a);
    }

    Player* p = new Player();
    p->settings(sPlayer, 200, 200, 0, 20);
    entities.push_back(p);

    /////основной цикл игры/////
    while (app.isOpen())
    {
        // за каждый такт мы проверяем, какое действие совершено
        Event event;
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed)
                app.close();

            // выстрелы не должны работать без остановки как, например, движение, тут должно быть ограничение
            if (event.type == Event::KeyPressed)
                if (event.key.code == Keyboard::Space)
                {
                    Bullet* b = new Bullet();
                    b->settings(sBullet, p->x, p->y, p->angle, 10);
                    entities.push_back(b);
                }
        
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) p->angle += 3;
        if (Keyboard::isKeyPressed(Keyboard::Left)) p->angle -= 3;
        if (Keyboard::isKeyPressed(Keyboard::Up)) p->thrust = true;
        else p->thrust = false;
       

        // обработка столкновений
        for (auto a : entities)
            for (auto b : entities)
            {
                //попали в астероид
                if (a->name == "asteroid" && b->name == "bullet")
                    if (isCollide(a, b))
                    {
                        a->life = false;
                        b->life = false;

                        Entity* e = new Entity();
                        e->settings(sExplosion, a->x, a->y);
                        e->name = "explosion";
                        entities.push_back(e);


                        // создаем микро астероиды после уничтожения большого
                        for (int i = 0;i < 2;i++)
                        {
                            if (a->R == 15) continue;
                            Entity* e = new Asteroid();
                            e->settings(sRock_small, a->x, a->y, rand() % 360, 15);
                            entities.push_back(e);
                        }

                    }
                //астероид попал в игрока
                if (a->name == "player" && b->name == "asteroid")
                    if (isCollide(a, b))
                    {
                        b->life = false;

                        Entity* e = new Entity();
                        e->settings(sExplosion_ship, a->x, a->y);
                        e->name = "explosion";
                        entities.push_back(e);

                        p->settings(sPlayer, W / 2, H / 2, 0, 20);
                        p->dx = 0; p->dy = 0;
                    }
            }


        if (p->thrust)  p->anim = sPlayer_go; //анимация движения
        else   p->anim = sPlayer;

        // чтобы анимация взрывов не была бесконечной
        for (auto e : entities)
            if (e->name == "explosion")
                if (e->anim.isEnd()) e->life = 0;

        // создание астероидов
        if (rand() % 150 == 0)
        {
            Asteroid* a = new Asteroid();
            a->settings(sRock, 0, rand() % H, rand() % 360, 25);
            entities.push_back(a);
        }

        for (auto i = entities.begin();i != entities.end();)
        {
            Entity* e = *i;

            e->update();
            e->anim.update();

            if (e->life == false) { i = entities.erase(i); delete e; }
            else i++;
        }

        // отображение на экране
        app.draw(background);
        for (auto i : entities) i->draw(app);
        app.display();
    }

    return 0;
}