/*
** EPITECH PROJECT, 2019
** r-type_2019
** File description:
** R-type tcp_connection
*/

#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <cstdlib>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "../../include/GameEngine/game_engine.hpp"

Map::Map(std::string filename)
{
    boost::property_tree::ptree root;
    boost::property_tree::read_json(filename, root);

    int i = 0;
    for (boost::property_tree::ptree::value_type &asset : root.get_child("map"))
    {
        (this->map).push_back(asset.second.data());
    }

    for (boost::property_tree::ptree::value_type &asset : root.get_child("assets"))
    {
        (this->assets_path).push_back(asset.second.data());
    }

    this->background = root.get<std::string>("background");

    for (boost::property_tree::ptree::value_type &enem : root.get_child("enemies"))
    {
        int idx;
        int timer;
        int pos;
        int i = 0;
        for (boost::property_tree::ptree::value_type &cell : enem.second) {
            if (i == 0)
                idx = std::stoi(cell.second.data());
            if (i == 1)
                timer = std::stoi(cell.second.data());
            if (i == 2)
                pos = std::stoi(cell.second.data());
            i++;
        }
        this->enemies.push_back(std::make_tuple(idx, timer, pos));
    }
}

Map::Map(const Map &ref)
{
    for (int i=0; i < ref.map.size(); i++)
        (this->map).push_back(ref.map[i]);
        // std::cout << ref.map[i] << std::endl;
    this->map = ref.map;
    this->assets_path = ref.assets_path;
    this->background = ref.background;
    this->enemies = ref.enemies;
}


Map::~Map()
{
}

void Map::list_assets()
{
    int a = 0;

    for (auto i = this->assets_path.begin(); i != this->assets_path.end(); ++i)
        std::cout << a++ << " : " << *i << std::endl;

}

void Map::show_map()
{
    for (auto i = this->map.begin(); i != this->map.end(); ++i)
        std::cout << *i << std::endl;

}

Projectile::Projectile(std::string path, std::string pwd)
{
    boost::property_tree::ptree root;
    boost::property_tree::read_json(path, root);

    this->name = root.get<std::string>("name");
    this->sprite = pwd + "sprites/" + root.get<std::string>("sprite");
    this->speed = root.get<float>("speed", 0.0);
    this->width = root.get<int>("width", 0);
    this->height = root.get<int>("height", 0);

    this->damage = root.get<float>("damage", 0.0);
    this->reload = root.get<float>("reload", 0.0);

    for (boost::property_tree::ptree::value_type &mv : root.get_child("pattern")) {
        int i = 0;
        float *pat = new float[2];
        for (boost::property_tree::ptree::value_type &cell : mv.second) {
            pat[i] = std::stof(cell.second.data());
            i++;
        }
        this->pattern.push_back(pat);
    }
}

void Projectile::move()
{
    //appliquer le pattern
}

Player::Player(std::string path, std::string pwd)
{
    boost::property_tree::ptree root;
    boost::property_tree::read_json(path, root);

    this->name = root.get<std::string>("name");
    this->sprite = pwd + "sprites/" + root.get<std::string>("sprite");
    this->speed = root.get<float>("speed", 0.0);
    this->width = root.get<int>("width", 0);
    this->height = root.get<int>("height", 0);

    this->life = root.get<float>("life", 0.0);

    for (boost::property_tree::ptree::value_type &weapon : root.get_child("weapons"))
    {
        std::string weap = pwd + "weapons/" + weapon.second.data() + ".json";
        this->weapons.push_back(Projectile(weap, pwd));
    }

    this->alive = true;
}

void Player::move(float mv[2])
{
    std::cout << "move bitch\n";
}

Enemy::Enemy(std::string path, std::string pwd)
{
    boost::property_tree::ptree root;
    boost::property_tree::read_json(path, root);

    this->name = root.get<std::string>("name");
    this->sprite = pwd + "sprites/" + root.get<std::string>("sprite");
    this->speed = root.get<float>("speed", 0.0);
    this->width = root.get<int>("width", 0);
    this->height = root.get<int>("height", 0);

    this->life = root.get<float>("life", 0.0);

    for (boost::property_tree::ptree::value_type &weapon : root.get_child("weapons"))
    {
        std::string weap = pwd + "weapons/" + weapon.second.data() + ".json";
        this->weapons.push_back(Projectile(weap, pwd));
    }

    for (boost::property_tree::ptree::value_type &mv : root.get_child("pattern")) {
        int i = 0;
        float *pat = new float[2];
        for (boost::property_tree::ptree::value_type &cell : mv.second) {
            pat[i] = std::stof(cell.second.data());
            i++;
        }
        this->pattern.push_back(pat);
    }
}

void Enemy::move()
{
    // activer pattern
}



rtype::game_engine::game_engine(std::string src)
{
    char *path = get_current_dir_name();
    std::string str(path);
    DIR *dir;
    struct dirent *ent;
    src = src.substr(0, src.size() - 13);

    std::string pwd = str +  '/' + src + "../../src/assets/maps";

    if ((dir = opendir (pwd.c_str())) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            std::string file(ent->d_name);
            if (file[0] != '.') {
                std::string fullpath = pwd + '/' + file;
                Map map(fullpath);
                this->_maps.push_back(map);
            }
        }
        closedir (dir);
    }

    std::string pwd_base = str +  '/' + src + "../../src/assets/";

    pwd = str +  '/' + src + "../../src/assets/players";
    if ((dir = opendir (pwd.c_str())) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            std::string file(ent->d_name);
            if (file[0] != '.') {
                std::string fullpath = pwd + '/' + file;
                Player play(fullpath, pwd_base);
                this->_players.push_back(play);
            }
        }
        closedir (dir);
    }


    pwd = str +  '/' + src + "../../src/assets/enemies";
    if ((dir = opendir (pwd.c_str())) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            std::string file(ent->d_name);
            if (file[0] != '.') {
                std::string fullpath = pwd + '/' + file;
                Enemy ene(fullpath, pwd_base);
                this->_enemies.push_back(ene);
            }
        }
        closedir (dir);
    }

}

rtype::game_engine::~game_engine()
{
}
