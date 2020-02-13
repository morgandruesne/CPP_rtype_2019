/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** interface
*/

#ifndef INTERFACE_HPP_
#define INTERFACE_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Config.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include "../include/client/tcp_client.hpp"
#include "../include/client/udp_client.hpp"

#include "./rtype.hpp"

#define     TEXTURE_BTN             0
#define     TEXTURE_PLAYER          1
#define     TEXTURE_PROJECTILE      2
#define     TEXTURE_BACKGROUND_1    3
#define     TEXTURE_BACKGROUND_2    4
#define     TEXTURE_BACKGROUND_3    5
#define     TEXTURE_CLOUD_1         6
#define     TEXTURE_CLOUD_2         7
#define     TEXTURE_CLOUD_3         8
#define     TEXTURE_GRADIENT        9
#define     TEXTURE_BIG_EYE         10
#define     TEXTURE_BIG_EYE_MISSILE 11
#define     TEXTURE_DEGUEU          12

#define     SPRITE_PLAY             0
#define     SPRITE_PLAY_HOVER       1
#define     SPRITE_QUIT             2
#define     SPRITE_QUIT_HOVER       3
#define     SPRITE_BACKGROUND_1     4
#define     SPRITE_BACKGROUND_2     5
#define     SPRITE_BACKGROUND_3     6
#define     SPRITE_CLOUD_1          7
#define     SPRITE_CLOUD_2          8
#define     SPRITE_CLOUD_3          9
#define     SPRITE_GRADIENT         10
#define     SPRITE_BIG_EYE          11
#define     SPRITE_DEGUEU           12

#define     PARRALAX_RED_DESERT     0
#define     PARRALAX_DESERT         1
#define     PARRALAX_SKELETON       2
#define     PARRALAX_CLOUD_1        3
#define     PARRALAX_CLOUD_2        4
#define     PARRALAX_CLOUD_3        5
#define     PARRALAX_CLOUD_4        6
#define     PARRALAX_CLOUD_5        7

class Player;

class Parralax
{
    public:
        Parralax(int id, int width, sf::Vector2f pos, int speed);
        int sprite_id;
        int width;
        sf::Vector2f pos;
        int speed;
};

class InterfaceCore
{
    public:
        InterfaceCore(void);
        ~InterfaceCore(void);
        InterfaceCore(const InterfaceCore &);
        void            addSprite(sf::Texture *texture, sf::IntRect rect);
        void            addTexture(std::string path);
        void            addPlayer(sf::Texture *texture, int team);
        void            addProjectile(int id, sf::Texture *texture, int type, sf::Vector2f pos);
        void            addParrallax(int id, int width, sf::Vector2f pos, int speed);
        void            addEnnemy(int id, sf::Texture *texture, int type, sf::Vector2f pos);
        void            drawThisAt(int i, sf::Vector2f pos);
        void            animGameOver();
        void            drawPlayer(int index);
        void            MovePlayer(int index);
        void            drawProjectiles();
        void            drawEnnemies();
        void            drawParralax(int index);
        sf::Texture*    getTexture(int position);
        sf::Sprite      getSprite(int position);
        void            resizeThis(int i, sf::Vector2f pos);
        sf::RenderWindow window;
        sf::Event event;
        int scene;
        sf::Vector2i mousePos;
        bool tcpEntry;
        bool UdpEntry;
        bool firstCo;
        int port;
        rtype::udp_client *uclient;
        std::vector<Player*> players;
        int clientPlayer;
        int nbrPlayers;
        std::vector<Projectile*> projectiles;
        sf::Clock fireDelay;
        std::vector<Parralax*> parralaxes;
        std::vector<Ennemy*> ennemies;
        sf::Clock       clock;
        std::string     ip;
        sf::RectangleShape  lobbyBackground;
        sf::SoundBuffer     bufferMusic;
        sf::SoundBuffer     bufferCamran;
        sf::Sound           acid;
        sf::Sound           camran;
        bool                win;
        int                 state;
    private:
        std::vector<sf::Sprite*> sprites;
        std::vector<sf::Texture*> textures;
};

void displayScene(InterfaceCore *core);
void displayBtnPlay(InterfaceCore   *core);
void displayBtnQuit(InterfaceCore   *core, sf::Vector2i BtnPos);
void displayTextAt(InterfaceCore   *core, sf::Vector2f pos, int size, sf::String str);

void TcpEntry(InterfaceCore   *core, int value);
void UdpEntry(InterfaceCore   *core);
void UdpGame(InterfaceCore   *core);


#endif /* !INTERFACE_HPP_ */
