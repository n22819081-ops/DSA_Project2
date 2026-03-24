//
// Created by omgit on 3/21/2026.
//

#ifndef DSA_PROJECT2_TILE_H
#define DSA_PROJECT2_TILE_H
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"

class Tile {
    public:
    // https://www.geeksforgeeks.org/cpp/enumeration-in-cpp/
    // Enum for tile states
    // open | wall | special
        enum TileState {
            Open,
            Wall,
            S_Special,
            P_Special,
            F_Special,
            Crate,
            OpenStair,
            OpenHuman
        };

    private:
        sf::Texture* open_texture;
        sf::Texture* wall_texture;
        sf::Texture* crate_texture;
        sf::Texture* s_special_texture;
        sf::Texture* p_special_texture;
        sf::Texture* f_special_texture;
        sf::Texture* human_texture;
        sf::Texture* stair_texture;

        sf::Sprite sprite;
        TileState state;

    public:
        // Constructor
        Tile(sf::Texture& open_texture, sf::Texture& wall_texture, sf::Texture& s_special_texture,
        sf::Texture& p_special_texture, sf::Texture& f_special_texture, sf::Texture& crate_texture, sf::Texture& human_texture, sf::Texture& stair_texture, float x, float y) :
        open_texture(&open_texture),
        wall_texture(&wall_texture),
        crate_texture(&crate_texture),
        human_texture(&human_texture),
        stair_texture(&stair_texture),
        s_special_texture(&s_special_texture),
        p_special_texture(&p_special_texture),
        f_special_texture(&f_special_texture),
        sprite(open_texture),
        state(Open)
        {
            this->sprite.setPosition(sf::Vector2f(x, y));
        }

        void setState(TileState newState) {
            this->state = newState;
            if (this->state == Open) {
                this->sprite.setTexture(*open_texture);
            }
            if (this->state == OpenStair) {
                this->sprite.setTexture(*stair_texture);
            }
            if (this->state == OpenHuman) {
                this->sprite.setTexture(*human_texture);
            }
            if (this->state == Wall) {
                this->sprite.setTexture(*wall_texture);
            }
            if (this->state == Crate) {
                this->sprite.setTexture(*crate_texture);
            }
            if (this->state == S_Special) {
                this->sprite.setTexture(*s_special_texture);
            }
            if (this->state == P_Special) {
                this->sprite.setTexture(*p_special_texture);
            }
            if (this->state == F_Special) {
                this->sprite.setTexture(*f_special_texture);
            }
        }

        sf::Sprite& getSprite() {
            return this->sprite;
        }

        TileState getState() {
            return this->state;
        }

};
#endif //DSA_PROJECT2_TILE_H