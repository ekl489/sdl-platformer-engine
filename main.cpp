#include <iostream>
#include <cstdlib> // for maths
#include <SDL2/SDL.h>

//include "Sprite/Player.h"
#include "Sprite/Sprite.h"

int main(int argc, const char * argv[]) {
    
    // Initialize SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        std::cout << "SDL could not initialize. SDL Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    else{
        
        std::cout << "SDL initialized successfully" << std::endl;
    }
    
    /*
        --- Create an SDL window ---
    */
    SDL_Window *window = NULL;
    
    int w = 640, h = 480;
    
    window = SDL_CreateWindow(
                              "Nick's SDL2 Platformer Engine - Example 1",                  // window title
                              SDL_WINDOWPOS_UNDEFINED,           // initial x position
                              SDL_WINDOWPOS_UNDEFINED,           // initial y position
                              w,                               // width, in pixels
                              h,                               // height, in pixels
                              SDL_WINDOW_OPENGL                  // flags - see below
                              );
    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        std::cout << "Could not create SDL window. SDL Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    
    /*
        --- Create an SDL renderer ---
    */
    SDL_Renderer *renderer = NULL;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // TODO: check if renderer created successfully
    
    /*
        --- Player ---
    */
    // Create player model
    SDL_Rect player;
    player.w = 50; // width
    player.h = 50; // height
    player.x = (w / 2) - (player.w / 2); // x (center of screen, from center of rect)
    player.y = (h / 2) - (player.h / 2); // y (center of screen, from center of rect)
    
    // Create player physics
    double xv = 0, yv = 0;
    
    // TEST: sprite class
    SDL_Rect myRect;
    myRect.x = (w / 2) - (player.w / 2);
    myRect.y = (w / 2) - (player.w / 2);
    myRect.w = 30;
    myRect.h = 30;
    
    SDL_Color myColor;
    myColor.r = 0;
    myColor.g = 0;
    myColor.b = 255;
    myColor.a = 255;
    
    Sprite myPlayer = Sprite(window, myRect, myColor);
    
    /*
        --- Game Loop ---
    */
    SDL_Event e; // event
    bool quit = false; // quit program
    
    while (!quit){
        
        /*
            --- Player Object ---
        */
        
        // mySprite.ApplyGravity(); // this will be applied in update()
        
        myPlayer.setVelocity(xv, yv);
        
        myPlayer.Update();
        
        
        std::cout << myPlayer.getPos().x << std::endl;
        
        /*
            --- Apply player physics ---
        */
        
        // Apply gravity;
        yv += 0.01;
        
        // horizontal boundaries
        if(xv > 0 && player.x + xv > w - player.w) {
            player.x = w - player.w;
            xv = 0;
            //xv = xv * -0.05;
        }
        else if(xv < 0 && player.x + xv < 0){
            player.x = 0;
            xv = 0;
        }
        else{
            // apply velocity freely
            player.x += round(xv);
        }
        
        // vertical boundaries
        if(yv < 0 && player.y + yv < 0) {
            player.y = 0;
            yv = 0;
        }
        else if(yv > 0 && player.y + yv > h - player.h){
            player.y = h - player.h;
            yv = 0;
        }
        else{
            // apply velocity freely
            player.y += round(yv);
        }
        

        /*
            --- Update Screen ---
        */
        
        
        
        // Clear screen
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 ); // Set render color to black ( background will be rendered in this color )
        SDL_RenderClear( renderer ); // Clear window
        
        // Render player (object player)
        myPlayer.Draw(renderer);
        
        // Render player (procedurally defined player)
        //SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 ); // Set render color to white ( player will be rendered in this color )
        //SDL_RenderFillRect( renderer, &player ); // Render player
        

        // Render onto window
        SDL_RenderPresent(renderer);
        
        /*
            --- Input Management ---
        */
        
        // Get Events
        while (SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                quit = true;
            }
            if(e.type == SDL_KEYDOWN){
                
                switch(e.key.keysym.sym){
                    case SDLK_LEFT:
                        //xv -= 0.5;//
                        myPlayer.applyHorizontalVelocity(-0.5);
                        break;
                    case SDLK_RIGHT:
                        //xv += 0.5;
                        myPlayer.applyHorizontalVelocity(0.5);
                        break;
                    case SDLK_UP:
                        //yv -= 2;
                        myPlayer.applyVerticalVelocity(2);
                        break;
                    case SDLK_DOWN:
                        //yv += 0.5;
                        break;
                }
            }
            else {
                // reduce xv --> 0
                
                // x > 0
                if(xv > 5){
                    xv -= 5;
                }
                else if(xv > 0){
                    xv = 0;
                }
                
                // x < 0
                if(xv < -5){
                    xv += 5;
                }
                else if(xv < 0){
                    xv = 0;
                }
                
                // reduce yv --> 0
                
                // y > 0
                if(yv > 5){
                    yv -= 5;
                }
                else if(yv > 0){
                    yv = 0;
                }
                
                // y < 0
                if(yv < -5){
                    yv += 5;
                }
                else if(yv < 0){
                    yv = 0;
                }
            }

        }
    }
    
    // ...program has been quit
    
    /*
        --- End Program ---
    */
    
    SDL_DestroyWindow(window); // Close and destroy the window
    SDL_Quit(); // Clean up SDL
    return 0;
}
