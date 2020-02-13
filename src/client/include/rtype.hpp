/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** rtype
*/

#ifndef RTYPE_HPP_
#define RTYPE_HPP_

// Player part

#define ANIM_IDLE       1
#define ANIM_DOWN       2
#define ANIM_UP         3
#define ANIM_LEFT       4
#define ANIM_RIGHT      5

#define PLAYER_SPEED                    5
#define PLAYER_FIRE_DELAY               1000
#define PLAYER_MISSILE_SPEED            20
#define ENNEMY_MOVE_SPEED               10

class PlayerState
{
    public:
        PlayerState();
        int             id_animation;
        int             progress;
        sf::Clock       clock;
};

class Player
{
    public:
        Player();
        Player(sf::Texture *texture, int team);
        void            setState(int id_animation);
        void            moveDown();
        void            moveUp();
        void            moveLeft();
        void            moveRight();
        PlayerState     state;
        sf::Vector2i    posTogo;
        sf::Sprite      *player;
        int             team;
        bool            isDead;
};

// Projectile part

#define ANIM_MOVE_PLAYER_MISSILE        2
#define ANIM_MOVE_BIG_EYE_MISSILE       3

#define PLAYER_MISSILE                  1
#define BIG_EYE_MISSILE                 2

#define DEFAULT_ID                      0

class ProjectileState
{
    public:
        ProjectileState();
        int             id_animation;
        int             progress;
        sf::Vector2f    dest;
        sf::Clock       clock;
};

class Projectile
{
    public:
        Projectile();
        Projectile(int id, sf::Texture *texture, int type, sf::Vector2f pos);
        void            setState(int id_animation);
        void            setDestination(sf::Vector2f dest);
        void            movePlayerMissile();
        void            moveBigEyeMissile();
        void            moveToDest();
        int id;
        ProjectileState state;
        sf::Sprite  *projectile;
        int type;
};

// Ennemy part

#define     ANIM_IDLE_BIG_EYE       2

#define     BIG_EYE                 1

class EnnemyState
{
    public:
        EnnemyState();
        int             id_animation;
        int             progress;
        sf::Clock       clock;
        sf::Vector2f    dest;
};

class Ennemy
{
    public:
        Ennemy();
        Ennemy(int id, sf::Texture *texture, int type, sf::Vector2f pos);
        void            setState(int id_animation);
        void            setDestination(sf::Vector2f dest);
        void            animIdleBigEye();
        void            moveToDest();
        int             id;
        EnnemyState     state;
        sf::Sprite      *ennemy;
        int             type;
};

#endif /* !RTYPE_HPP_ */
