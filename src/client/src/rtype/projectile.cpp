/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** projectile
*/

#include "../../include/interface.hpp"

ProjectileState::ProjectileState()
{
    this->id_animation = ANIM_IDLE;
    this->progress = 0;
}

void    Projectile::setState(int id_animation) {
    this->state.id_animation = id_animation;
    this->state.progress = 0;
}

Projectile::Projectile(int id, sf::Texture *texture, int type, sf::Vector2f pos)
{
    sf::Sprite  sprite;

    this->id = id;
    this->type = type;
    switch (type) {
        case PLAYER_MISSILE:
            sprite.setTexture(*texture);
            sprite.setTextureRect((sf::IntRect){248, 100, 18, 16});
            sprite.setPosition(pos);
            sprite.setScale((sf::Vector2f){2, 2});
            this->setState(ANIM_MOVE_PLAYER_MISSILE);
            break;
        case BIG_EYE_MISSILE:
            sprite.setTexture(*texture);
            sprite.setTextureRect((sf::IntRect){0, 0, 16, 16});
            sprite.setPosition(pos);
            this->setState(ANIM_MOVE_BIG_EYE_MISSILE);
            break;
    }
    this->projectile = new sf::Sprite(sprite);
}

void    Projectile::movePlayerMissile() {
    if (this->state.id_animation != ANIM_MOVE_PLAYER_MISSILE || this->state.clock.getElapsedTime().asMilliseconds() < 50)
        return;
    switch (this->state.progress) {
        case 0:
            this->projectile->setTextureRect((sf::IntRect){216, 136, 50, 16});
            break;
        case 30:
            this->projectile->setTextureRect((sf::IntRect){166, 136, 50, 16});
            break;
        case 50:
            this->projectile->setTextureRect((sf::IntRect){216, 136, 50, 16});
            break;
    }
    this->state.progress += 10;
    if (this->state.progress == 60)
        this->state.progress = 0;
    this->moveToDest();
    this->state.clock.restart();
}

void    Projectile::moveBigEyeMissile() {
    if (this->state.id_animation != ANIM_MOVE_BIG_EYE_MISSILE || this->state.clock.getElapsedTime().asMilliseconds() < 50)
        return;
    this->moveToDest();
    this->state.clock.restart();
}

void    Projectile::setDestination(sf::Vector2f dest)
{
    this->state.dest = dest;
}

void    Projectile::moveToDest()
{
    if (this->state.dest.x != 0 || this->state.dest.y != 0) {
        this->projectile->setPosition(this->state.dest);
        this->state.dest = sf::Vector2f(0, 0);
    }
}