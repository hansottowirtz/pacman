#include <string>
#include "SDL.h"

//Texture wrapper class
class SDLSpriteTexture {
    public:
        //Initializes variables
        SDLSpriteTexture();

        //Deallocates memory
        ~SDLSpriteTexture();

        //Loads image at specified path
        bool loadFromFile(std::string path);

        //Deallocates texture
        void free();

        //Renders texture at given point
        void render(int x, int y, SDL_Rect* clip = NULL);

        //Gets image dimensions
        int getWidth();
        int getHeight();

    private:
        //The actual hardware texture
        SDL_Texture* sdlTexture;

        //Image dimensions
        int width;
        int height;
};
