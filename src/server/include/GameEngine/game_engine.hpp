/*
** EPITECH PROJECT, 2019
** r-type_2019
** File description:
** R-type game_engine
*/

#include <iostream>

#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP


class Map {
    public:
        Map(std::string filename);
        Map(const Map &ref);
        ~Map();

        void list_assets();
        void show_map();

        std::string background;
        std::vector<std::string> map;
        std::vector<std::string> assets_path;
        std::vector<std::tuple<int, int, int>> enemies;
};

class IObject {
    public:
        virtual ~IObject() {};
        virtual std::string get_sprite() = 0;
        virtual std::string get_name() = 0;
        virtual float *get_pos() = 0;
        virtual float *set_pos(float[2]) = 0;
        virtual float get_speed() = 0;
        virtual std::vector<float *>get_pattern() = 0;
        virtual void move() = 0;
        virtual int get_width() = 0;
        virtual int get_height() = 0;

    protected:
        std::string name;
        std::string sprite;
        std::vector<float *>pattern;
        int height;
        int width;
        float pos[2];
        float speed;
};

class Projectile: public IObject {
    public:
        Projectile(std::string path, std::string pwd);

        virtual std::string get_sprite() {return (this->sprite);}
        virtual std::string get_name() {return (this->name);}
        virtual float *get_pos() {return (this->pos);}
        virtual float *set_pos(float nf[2]) {this->pos[0] = nf[0]; this->pos[1] = nf[1]; return (this->pos);}
        virtual float get_speed() {return (this->speed);}
        virtual std::vector<float *>get_pattern() {return (this->pattern);};
        virtual int get_width() {return (this->width);};
        virtual int get_height() {return (this->height);};

        virtual void move();

        float get_damage() {return (this->damage);};
        float get_reload() {return (this->reload);};

    private:
        float damage;
        float reload;
};

class IMob: public IObject {
    public:
        virtual int get_life() = 0;
        virtual Projectile get_weapon(int idx) = 0;
        virtual std::vector<Projectile> get_weapons() = 0;
        virtual int take_damage(int dmg) = 0;

    protected:
        int life;
        std::vector<Projectile> weapons;
};

class Player: public IMob
{
    public:
        Player(std::string path, std::string pwd);

        virtual std::string get_sprite() {return (this->sprite);}
        virtual std::string get_name() {return (this->name);}
        virtual float *get_pos() {return (this->pos);}
        virtual float *set_pos(float nf[2]) {this->pos[0] = nf[0]; this->pos[1] = nf[1]; return (this->pos);}
        virtual float get_speed() {return (this->speed);}
        virtual std::vector<float *>get_pattern() {return (this->pattern);};
        virtual int get_width() {return (this->width);};
        virtual int get_height() {return (this->height);};

        virtual void move() {}

        virtual int get_life() {return (this->life);};
        virtual Projectile get_weapon(int idx) {return (this->weapons[idx]);};
        virtual std::vector<Projectile> get_weapons() {return (this->weapons);};
        virtual int take_damage(int dmg) {this->life -= dmg; return life;}

        void move(float mv[2]);
        bool alive;
};

class Enemy: public IMob
{
    public:
        Enemy(std::string path, std::string pwd);

        virtual std::string get_sprite() {return (this->sprite);}
        virtual std::string get_name() {return (this->name);}
        virtual float *get_pos() {return (this->pos);}
        virtual float *set_pos(float nf[2]) {this->pos[0] = nf[0]; this->pos[1] = nf[1]; return (this->pos);}
        virtual float get_speed() {return (this->speed);}
        virtual std::vector<float *>get_pattern() {return (this->pattern);};
        virtual int get_width() {return (this->width);};
        virtual int get_height() {return (this->height);};
        virtual int take_damage(int dmg) {this->life -= dmg; return life;}

        virtual void move();

        virtual int get_life() {return (this->life);};
        virtual Projectile get_weapon(int idx) {return (this->weapons[idx]);};
        virtual std::vector<Projectile> get_weapons() {return (this->weapons);};
};


namespace rtype {
    class game_engine {
        public:
            game_engine(std::string src);
            ~game_engine();
            std::vector<Map> _maps;
            std::vector<Player> _players;
            std::vector<Enemy> _enemies;
};

}

#endif //GAME_ENGINE_HPP
