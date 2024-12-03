#ifndef POKEMON_DETAIL
#define POKEMON_DETAIL

#include "../gamePlay/game.hpp"
#include "point.hpp"

const float SIZE_POKEMON_DETAIL = SQUARE_SIZE * 3;

float positionXDetail = SQUARE_SIZE*(COLUMN+2) + WIDTH_POINT_TABLE/2 - SIZE_POKEMON_DETAIL/2;
float positionYDetail = (5*SQUARE_SIZE)/2;

int pokemonID = 0;

void drawPokemonDetail();
void drawRectangleOutLinePokemonDetail();

#endif