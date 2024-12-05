#include "pokemonDetail.hpp"

void drawPokemonDetail() {
    sf::RectangleShape detailPokemon(sf::Vector2f(SIZE_POKEMON_DETAIL, SIZE_POKEMON_DETAIL)); 
    detailPokemon.setPosition(positionXDetail, positionYDetail); 
    detailPokemon.setFillColor(pokemonBackground);
    detailPokemon.setOutlineColor(sf::Color::Black);
    detailPokemon.setOutlineThickness(1.f);
    window.draw(detailPokemon);

    if (pokemonID) {
        sf::Texture pokemonTexture;
        pokemonTexture.loadFromFile(POKEMONS[pokemonID]);
        sf::Sprite pokemonSprite;
        pokemonSprite.setTexture(pokemonTexture);
        pokemonSprite.setPosition(positionXDetail, positionYDetail);
        sf::Vector2u originalSize = pokemonTexture.getSize();
        float scaleFactor = (SQUARE_SIZE*3) / originalSize.x;
        pokemonSprite.setScale(scaleFactor, scaleFactor);
        window.draw(pokemonSprite);
    }
}

void drawRectangleOutLinePokemonDetail() {
    sf::RectangleShape rectangleOutLinePokemonDetail(sf::Vector2f(SIZE_POKEMON_DETAIL, SIZE_POKEMON_DETAIL));
    rectangleOutLinePokemonDetail.setPosition(positionXDetail, positionYDetail); 
    rectangleOutLinePokemonDetail.setFillColor(sf::Color::Transparent);
    rectangleOutLinePokemonDetail.setOutlineColor(sf::Color::Green);
    rectangleOutLinePokemonDetail.setOutlineThickness(3.f); 
    window.draw(rectangleOutLinePokemonDetail); 
}