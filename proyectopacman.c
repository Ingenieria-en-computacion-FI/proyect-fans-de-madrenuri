#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

// Dimensiones de la ventana del juego
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* argv[]) {
    // 1. Inicializar SDL2 y SDL_image
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Error: No se pudo inicializar SDL2. SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("Error: No se pudo inicializar SDL_image. IMG_Error: %s\n", IMG_GetError());
        SDL_Quit();
        return 1;
    }

    // 2. Crear la Ventana
    SDL_Window* window = SDL_CreateWindow(
        "Pac-Man - MSYS2 & SDL2",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (window == NULL) {
        printf("Error: No se pudo crear la ventana. SDL_Error: %s\n", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // 3. Crear el Renderer (El pintor)
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        printf("Error: No se pudo crear el renderer. SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // 4. Cargar la imagen de los sprites (Fondo rosa)
    // El juego buscará este archivo exactamente en la misma carpeta del .exe
    const char* imagePath = "temporal_sprites.png";
    SDL_Surface* loadedSurface = IMG_Load(imagePath);
    if (loadedSurface == NULL) {
        printf("Error: No se encontro el archivo %s en la raiz. IMG_Error: %s\n", imagePath, IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Convertir la superficie a textura para la tarjeta gráfica
    SDL_Texture* spriteSheet = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface); // Ya no necesitamos la superficie original

    if (spriteSheet == NULL) {
        printf("Error: No se pudo crear la textura. SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // 5. Bucle principal del juego
    bool quit = false;
    SDL_Event e;

    while (!quit) {
        // Manejar eventos (Teclado / Cerrar ventana)
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        quit = true; // Salir con la tecla ESC
                        break;
                }
            }
        }

        // Limpiar la pantalla (Color de fondo: Negro)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Dibujar la imagen de sprites en toda la pantalla para verificar que carga bien
        SDL_RenderCopy(renderer, spriteSheet, NULL, NULL);

        // Actualizar la pantalla
        SDL_RenderPresent(renderer);
        SDL_Delay(16); // Aproximadamente 60 FPS
    }

    // 6. Limpiar memoria y salir
    SDL_DestroyTexture(spriteSheet);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}