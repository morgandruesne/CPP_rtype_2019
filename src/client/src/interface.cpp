/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** interface
*/

#include "../include/interface.hpp"

InterfaceCore::InterfaceCore(void) {
    this->window.create(sf::VideoMode(1024, 800), "R-TYPE", sf::Style::Default);
    this->scene = 0;
    this->port = -1;
    this->tcpEntry = false;
    this->UdpEntry = false;
    this->firstCo = false;
    this->lobbyBackground.setPosition((sf::Vector2f){0, 150});
    this->lobbyBackground.setFillColor((sf::Color){0, 0, 0, 128});
    this->lobbyBackground.setSize((sf::Vector2f){1024, 440});
    this->addTexture("../src/client/assets/btn.png");
    this->addTexture("../src/client/assets/player.gif");
    this->addTexture("../src/client/assets/projectiles.gif");
    this->addTexture("../src/client/assets/background1.png");
    this->addTexture("../src/client/assets/background2.png");
    this->addTexture("../src/client/assets/background3.png");
    this->addTexture("../src/client/assets/cloud1.png");
    this->addTexture("../src/client/assets/cloud2.png");
    this->addTexture("../src/client/assets/cloud3.png");
    this->addTexture("../src/client/assets/gradient.png");
    this->addTexture("../src/client/assets/big_eye.png");
    this->addTexture("../src/client/assets/projectile_ennemy.png");
    this->addTexture("../src/client/assets/degueu.gif");
    this->addSprite(this->getTexture(TEXTURE_BTN), sf::IntRect(0, 0, 150, 30));
    this->addSprite(this->getTexture(TEXTURE_BTN), sf::IntRect(0, 30, 150, 30));
    this->addSprite(this->getTexture(TEXTURE_BTN), sf::IntRect(0, 180, 150, 30));
    this->addSprite(this->getTexture(TEXTURE_BTN), sf::IntRect(0, 210, 150, 30));
    this->addSprite(this->getTexture(TEXTURE_BACKGROUND_1), sf::IntRect(0, 0, 1024, 584));
    this->addSprite(this->getTexture(TEXTURE_BACKGROUND_2), sf::IntRect(0, 0, 1024, 400));
    this->addSprite(this->getTexture(TEXTURE_BACKGROUND_3), sf::IntRect(0, 0, 1024, 424));
    this->addSprite(this->getTexture(TEXTURE_CLOUD_1), sf::IntRect(0, 0, 256, 104));
    this->addSprite(this->getTexture(TEXTURE_CLOUD_2), sf::IntRect(0, 0, 208, 74));
    this->addSprite(this->getTexture(TEXTURE_CLOUD_3), sf::IntRect(0, 0, 300, 130));
    this->addSprite(this->getTexture(TEXTURE_GRADIENT), sf::IntRect(0, 0, 1024, 800));
    this->addSprite(this->getTexture(TEXTURE_BIG_EYE), sf::IntRect(0, 0, 130, 106));
    this->addSprite(this->getTexture(TEXTURE_DEGUEU), sf::IntRect(0, 0, 264, 143));
    this->resizeThis(SPRITE_DEGUEU, (sf::Vector2f){2, 2});
    this->addParrallax(SPRITE_BACKGROUND_1, 1024, (sf::Vector2f){0, 216}, 4);
    this->addParrallax(SPRITE_BACKGROUND_2, 1024, (sf::Vector2f){0, 450}, 2);
    this->addParrallax(SPRITE_BACKGROUND_3, 4096, (sf::Vector2f){0, 340}, 1);
    this->addParrallax(SPRITE_CLOUD_1, 1024, (sf::Vector2f){-250, 200}, 5);
    this->addParrallax(SPRITE_CLOUD_2, 2048, (sf::Vector2f){750, 75}, 2);
    this->addParrallax(SPRITE_CLOUD_3, 1536, (sf::Vector2f){1024, 150}, 3);
    this->addParrallax(SPRITE_CLOUD_2, 1536, (sf::Vector2f){100, 220}, 5);
    this->addParrallax(SPRITE_CLOUD_1, 1024, (sf::Vector2f){0, 50}, 1);
    this->clientPlayer = 2;
    this->nbrPlayers = 4;
    this->addPlayer(this->getTexture(TEXTURE_PLAYER), 1);
    this->addPlayer(this->getTexture(TEXTURE_PLAYER), 2);
    this->addPlayer(this->getTexture(TEXTURE_PLAYER), 3);
    this->addPlayer(this->getTexture(TEXTURE_PLAYER), 4);
    this->bufferMusic.loadFromFile("../src/client/assets/acid.ogg");
    this->bufferCamran.loadFromFile("../src/client/assets/camran.ogg");
    this->acid.setBuffer(this->bufferMusic);
    this->camran.setBuffer(this->bufferCamran);
    this->win = false;
    this->state = 0;
}

InterfaceCore::~InterfaceCore(void) {}

InterfaceCore::InterfaceCore(const InterfaceCore&) {}

void    InterfaceCore::addTexture(std::string path) {
    sf::Texture texture;

    texture.loadFromFile(path);
    this->textures.push_back(new sf::Texture(texture));
}

void    InterfaceCore::addSprite(sf::Texture *texture, sf::IntRect rect) {
    sf::Sprite sprite;

    sprite.setTexture(*texture);
    sprite.setTextureRect(rect);
    sprite.setPosition(sf::Vector2f(0, 0));
    this->sprites.push_back(new sf::Sprite(sprite));
}

void    InterfaceCore::addPlayer(sf::Texture *texture, int team)
{
    this->players.push_back(new Player(texture, team));
}

void    InterfaceCore::addProjectile(int id, sf::Texture *texture, int type, sf::Vector2f pos)
{
    this->projectiles.push_back(new Projectile(id, texture, type, pos));
}

sf::Texture     *InterfaceCore::getTexture(int position) {
    return (this->textures[position]);
}

sf::Sprite    InterfaceCore::getSprite(int position) {
    return (*(this->sprites[position]));
}

void    InterfaceCore::drawThisAt(int i, sf::Vector2f pos) {
    this->sprites[i]->setPosition(pos);
    this->window.draw(this->getSprite(i));
}

void    InterfaceCore::drawProjectiles() {
    for (int i = 0; i < this->projectiles.size(); i++) {
        this->window.draw(*(this->projectiles[i]->projectile));
    }
}

void   InterfaceCore::drawEnnemies() {
    for (int i = 0; i < this->ennemies.size(); i++) {
        this->window.draw(*(this->ennemies[i]->ennemy));
    }
}

void    InterfaceCore::drawPlayer(int index) {
    this->window.draw(*(this->players[index - 1]->player));
}

void    InterfaceCore::MovePlayer(int index) {
    if (this->players[index - 1]->posTogo.y < (int)this->players[index - 1]->player->getPosition().y) {
        this->players[index - 1]->moveUp();
    }
    if (this->players[index - 1]->posTogo.y > (int)this->players[index - 1]->player->getPosition().y) {
        this->players[index - 1]->moveDown();
    }
    if (this->players[index - 1]->posTogo.x < (int)this->players[index - 1]->player->getPosition().x) {
        this->players[index - 1]->moveLeft();
    }
    if (this->players[index - 1]->posTogo.x > (int)this->players[index - 1]->player->getPosition().x) {
        this->players[index - 1]->moveRight();
    }
}

Parralax::Parralax(int id, int width, sf::Vector2f pos, int speed)
{
    this->sprite_id = id;
    this->width = width;
    this->pos = pos;
    this->speed = speed;
}

void    InterfaceCore::addParrallax(int id, int width, sf::Vector2f pos, int speed)
{
    this->sprites[id]->setPosition(pos);
    this->parralaxes.push_back(new Parralax(id, width, pos, speed));
}

void    InterfaceCore::drawParralax(int index)
{
    int sprite_id = this->parralaxes[index]->sprite_id;
    float axe = this->parralaxes[index]->pos.x;

    this->sprites[sprite_id]->setPosition(this->parralaxes[index]->pos);
    this->window.draw(this->getSprite(sprite_id));
    for (float i = axe; i < 1024; i += this->parralaxes[index]->width) {
        this->sprites[sprite_id]->setPosition((sf::Vector2f){i, this->parralaxes[index]->pos.y});
        this->window.draw(this->getSprite(sprite_id));
    }
    if (this->parralaxes[index]->pos.x < 0 - this->parralaxes[index]->width)
        this->parralaxes[index]->pos.x += this->parralaxes[index]->width;
    this->parralaxes[index]->pos.x -= this->parralaxes[index]->speed;
}

void    InterfaceCore::resizeThis(int i, sf::Vector2f pos) {
    this->sprites[i]->setScale(pos.x, pos.y);
}

void    InterfaceCore::addEnnemy(int id, sf::Texture *texture, int type, sf::Vector2f pos)
{
    this->ennemies.push_back(new Ennemy(id, texture, type, pos));
}

void    InterfaceCore::animGameOver()
{
    if (this->clock.getElapsedTime().asMilliseconds() < 50)
        return;
    switch (this->state) {
        case 0:
            this->sprites[SPRITE_DEGUEU]->setTextureRect((sf::IntRect){0, 0, 264, 143});
            break;
        case 50:
            this->sprites[SPRITE_DEGUEU]->setTextureRect((sf::IntRect){0, 144, 264, 143});
            break;
        case 100:
            this->sprites[SPRITE_DEGUEU]->setTextureRect((sf::IntRect){0, 288, 264, 143});
            break;
        case 150:
            this->sprites[SPRITE_DEGUEU]->setTextureRect((sf::IntRect){0, 432, 264, 143});
            break;
        case 200:
            this->sprites[SPRITE_DEGUEU]->setTextureRect((sf::IntRect){265, 432, 264, 143});
            break;
        case 250:
            this->sprites[SPRITE_DEGUEU]->setTextureRect((sf::IntRect){265, 288, 264, 143});
            break;
        case 300:
            this->sprites[SPRITE_DEGUEU]->setTextureRect((sf::IntRect){265, 144, 264, 143});
            break;
        case 350:
            this->sprites[SPRITE_DEGUEU]->setTextureRect((sf::IntRect){265, 0, 264, 143});
            break;
    }
    this->state += 50;
    if (this->state == 400)
        this->state = 0;
    this->clock.restart();
}