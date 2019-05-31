#ifndef Particle_h
#define Particle_h

#include <iostream>
#include <SDL2/SDL.h>

class Particle : public SDL_Rect{
public:
    Particle(SDL_Window *window, SDL_Rect rect){
        
        // set rect vars
        x = rect.x;
        y = rect.y;
        w = rect.w;
        h = rect.h;
        
        // set physics variables
        xVelocity = 0;
        yVelocity = 0;
        
        // set window
        Window = window;
    }
    
    // for now, all particles are movable, gravitated & bounded
    
    /*
        --- Velocity ---
    */
    void setVelocity(float xv, float yv){
        xVelocity = xv;
        yVelocity = yv;
    }
    
    void applyHorizontalVelocity(float xv){
        xVelocity += xv;
    }
    void applyVerticalVelocity(float yv){
        yVelocity += yv;
    }
    
    void Update(){
        ApplyGravity(); // apply gravity
        
        // apply velocities
        
        // horizontal boundaries
        if(xVelocity > 0 && x + xVelocity > 640 - w) {
            x = 640 - w;
            xVelocity = 0;
        }
        else if(xVelocity < 0 && x + xVelocity < 0){
            x = 0;
            xVelocity = 0;
        }
        else{
            // apply velocity freely
            x += round(xVelocity);
        }
        
        // vertical boundaries
        if(yVelocity < 0 && y + yVelocity < 0) {
            y = 0;
            yVelocity = 0;
        }
        else if(yVelocity > 0 && y + yVelocity > 480 - h){
            y = 480 - h;
            yVelocity = 0;
        }
        else{
            // apply velocity freely
            y += round(yVelocity);
        }
        
    }
    
    /*
        --- Get Positioning ---
    */
    
    SDL_Point getPos(){
        SDL_Point point;
        point.x = x;
        point.y = y;
        
        return point;
    }
    
    /*
     --- Gravity ---
    */
    void ApplyGravity(){
        yVelocity += 0.01;
    }
    
    /*
     --- Friction ---
    */
    void ApplyHorizontalFriction(){
        // xVelocity > 0
        if(xVelocity > 5){
            xVelocity -= 5;
        }
        else if(xVelocity > 0){
            xVelocity = 0;
        }
        
        // xVelocity < 0
        if(xVelocity < -5){
            xVelocity += 5;
        }
        else if(xVelocity < 0){
            xVelocity = 0;
        }
    }
    void ApplyVerticalFriction(){
        // yVelocity > 0
        if(yVelocity > 5){
            yVelocity -= 5;
        }
        else if(yVelocity > 0){
            yVelocity = 0;
        }
        
        // yVelocity < 0
        if(yVelocity < -5){
            yVelocity += 5;
        }
        else if(yVelocity < 0){
            yVelocity = 0;
        }
    }
    void ApplyFriction(){
        ApplyHorizontalFriction();
        ApplyVerticalFriction();
    }
    
    /*
        --- Boundaries ---
    */
    void HandleCollisionCeiling(){
        if(yVelocity < 0 && y + yVelocity < 0) {
            // Particle is collided with ceiling
            y = 0;
            yVelocity = 0;
        }
    }
    
    
protected:
    float xVelocity, yVelocity;
    
    SDL_Window *Window;
    
private:

};

#endif /* Particle_h */

