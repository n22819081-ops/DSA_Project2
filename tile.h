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
            F_Special
        };

    private:
        sf::Texture* open_texture;
        sf::Texture* wall_texture;
        sf::Texture* s_special_texture;
        sf::Texture* p_special_texture;
        sf::Texture* f_special_texture;

        sf::Sprite sprite;
        TileState state;

    public:
        // Constructor
        Tile(sf::Texture& open_texture, sf::Texture& wall_texture, sf::Texture& s_special_texture,
        sf::Texture& p_special_texture, sf::Texture& f_special_texture, float x, float y) :
        open_texture(&open_texture),
        wall_texture(&wall_texture),
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
            if (this->state == Wall) {
                this->sprite.setTexture(*wall_texture);
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