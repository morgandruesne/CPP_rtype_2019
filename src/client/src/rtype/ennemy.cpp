/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** ennemy
*/

#include "../../include/interface.hpp"

EnnemyState::EnnemyState()
{
    this->id_animation = ANIM_IDLE;
    this->progress = 0;
}

Ennemy::Ennemy(int id, sf::Texture *texture, int type, sf::Vector2f pos)
{
    sf::Sprite  sprite;

    this->id = id;
    this->type = type;
    switch (type) {
        case BIG_EYE:
            sprite.setTexture(*texture);
            sprite.setTextureRect((sf::IntRect){0, 0, 130, 106});
            sprite.setPosition(pos);
            this->setState(ANIM_IDLE_BIG_EYE);
            break;
    }
    this->ennemy = new sf::Sprite(sprite);
}

void    Ennemy::setState(int id_animation)
{
    this->state.id_animation = id_animation;
    this->state.progress = 0;
}

void    Ennemy::animIdleBigEye()
{
    if (this->state.id_animation != ANIM_IDLE_BIG_EYE || this->state.clock.getElapsedTime().asMilliseconds() < 50)
        return;
    switch (this->state.progress) {
        case 0:
            this->ennemy->setTextureRect((sf::IntRect){0, 0, 130, 106});
            break;
        case 20:
            this->ennemy->setTextureRect((sf::IntRect){0, 106, 130, 106});
            break;
    }
    this->state.progress += 10;
    if (this->state.progress == 40)
        this->state.progress = 0;
    this->moveToDest();
    this->state.clock.restart();
}

void    Ennemy::setDestination(sf::Vector2f dest)
{
    this->state.dest = dest;
}

void    Ennemy::moveToDest()
{
    if (this->state.dest.x != 0 || this->state.dest.y != 0) {
        this->ennemy->setPosition(this->state.dest);
        this->state.dest = sf::Vector2f(0, 0);
    }
}