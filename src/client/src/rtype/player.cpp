/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** player
*/

#include "../../include/interface.hpp"

PlayerState::PlayerState()
{
    this->id_animation = ANIM_IDLE;
    this->progress = 0;
}

void    Player::setState(int id_animation) {
    this->player->setTextureRect((sf::IntRect){33*2, 17*(this->team - 1), 33, 17});
    this->state.id_animation = id_animation;
    this->state.progress = 0;
}

Player::Player(sf::Texture *texture, int team)
{
    sf::Sprite      sprite;
    sf::IntRect     rect = (sf::IntRect) {33 * 2, 17 * (team - 1), 33, 17};

    sprite.setTexture(*texture);
    sprite.setTextureRect(rect);
    sprite.setPosition(sf::Vector2f(70, team * 170));
    sprite.setScale(sf::Vector2f(2, 2));
    this->player = new sf::Sprite(sprite);
    this->team = team;
    this->posTogo.x = 70;
    this->posTogo.y = team * 170;
    this->isDead = false;
}

void    Player::moveUp() {
    if (this->state.clock.getElapsedTime().asMilliseconds() < 10)
        return;
    if (this->state.id_animation == ANIM_IDLE)
        this->setState(ANIM_UP);
    switch (this->state.progress) {
        case 0:
            this->player->setTextureRect((sf::IntRect){33*3, 17 * (this->team - 1), 33, 17});
            break;
        case 50:
            this->player->setTextureRect((sf::IntRect){33*4, 17 * (this->team - 1), 33, 17});
            break;
    }
    this->state.progress += 50;
    this->player->move((sf::Vector2f){0, PLAYER_SPEED * -1});
    this->state.clock.restart();
}

void    Player::moveDown() {
    if (this->state.clock.getElapsedTime().asMilliseconds() < 10)
        return;
    if (this->state.id_animation == ANIM_IDLE)
        this->setState(ANIM_DOWN);
    switch (this->state.progress) {
        case 0:
            this->player->setTextureRect((sf::IntRect){33*1, 17 * (this->team - 1), 33, 17});
            break;
        case 50:
            this->player->setTextureRect((sf::IntRect){33*0, 17 * (this->team - 1), 33, 17});
            break;
    }
    this->state.progress += 50;
    this->player->move((sf::Vector2f){0, PLAYER_SPEED});
    this->state.clock.restart();
}

void    Player::moveLeft() {
    if (this->state.clock.getElapsedTime().asMilliseconds() < 10)
        return;
    if (this->state.id_animation == ANIM_IDLE)
        this->setState(ANIM_LEFT);
    switch (this->state.progress) {
        case 0:
            this->player->setTextureRect((sf::IntRect){33*1, 17 * (this->team - 1), 33, 17});
            break;
    }
    this->state.progress += 50;
    this->player->move((sf::Vector2f){PLAYER_SPEED * -1, 0});
    this->state.clock.restart();
}

void    Player::moveRight() {
    if (this->state.clock.getElapsedTime().asMilliseconds() < 10)
        return;
    if (this->state.id_animation == ANIM_IDLE)
        this->setState(ANIM_RIGHT);
    switch (this->state.progress) {
        case 0:
            this->player->setTextureRect((sf::IntRect){33*3, 17 * (this->team - 1), 33, 17});
            break;
    }
    this->state.progress += 50;
    this->player->move((sf::Vector2f){PLAYER_SPEED, 0});
    this->state.clock.restart();
}