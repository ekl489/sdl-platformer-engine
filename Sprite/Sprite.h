#ifndef Sprite_h
#define Sprite_h

#include <iostream>
#include <SDL2/SDL.h>

#include "./Particle.h"

/*
    --- Sprite ---
 
    - A sprite IS a particle (with positioning)
    - A sprite IS an SDL_Rect (because that is how a sprite is visually represented)
*/

class Sprite : public Particle, public std::SDL_Rect {
public:
    Sprite(SDL_Window *window, SDL_Rect Rect, SDL_Color Color) : Particle(window, Rect) {
        color = Color;
    }
    
    void Draw(SDL_Renderer *renderer){
        
        std::cout << x << ":" << y << std::endl;
        
        // get initial renderer color
        Uint8 r = 0, g = 0, b = 0, a = 0;
        Uint8 *R = &r, *G = &g, *B = &b, *A = &a;
        SDL_GetRenderDrawColor(renderer, R, G, B, A);
        
        // draw rect
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &rect);
        
        // reset renderer color
        SDL_SetRenderDrawColor(renderer, r, g, b, a);
    }
protected:
    //SDL_Rect rect;
    SDL_Color color;
};

#endif /* Sprite_h */
