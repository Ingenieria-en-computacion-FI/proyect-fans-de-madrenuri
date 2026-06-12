#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FILAS 15
#define COLUMNAS 20
#define TAM 32
#define ANCHO (COLUMNAS * TAM)
#define ALTO (FILAS * TAM + 50)
#define MAX_FANTASMAS 4

char mapa[FILAS][COLUMNAS + 1];
int jugadorFila = 1, jugadorCol = 1;
int jugadorInicioFila = 1, jugadorInicioCol = 1;
int vidas = 2;
int puntos = 0;
int pellets = 0;
int juegoTerminado = 0;
int victoria = 0;

typedef struct {
    int fila;
    int col;
    int inicioFila;
    int inicioCol;
} Fantasma;

Fantasma fantasmas[MAX_FANTASMAS];
int totalFantasmas = 0;

SDL_Window *ventana = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *texPacman = NULL;
SDL_Texture *texFantasma = NULL;
SDL_Texture *texPared = NULL;
SDL_Texture *texPellet = NULL;
SDL_Texture *texFondo = NULL;

SDL_Texture* cargarTexturaBMP(const char *ruta) {
    SDL_Surface *superficie = SDL_LoadBMP(ruta);
    if (superficie == NULL) {
        printf("No se pudo cargar %s. Error: %s\n", ruta, SDL_GetError());
        return NULL;
    }
    SDL_Texture *textura = SDL_CreateTextureFromSurface(renderer, superficie);
    SDL_FreeSurface(superficie);
    return textura;
}

void dibujarRectangulo(int x, int y, int w, int h, int r, int g, int b) {
    SDL_Rect rect = {x, y, w, h};
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void dibujarTextoSimple(int x, int y, int numero, int r, int g, int b) {
    for (int i = 0; i < numero; i++) {
        dibujarRectangulo(x + i * 18, y, 14, 18, r, g, b);
    }
}

int cargarMapa(const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo del mapa.\n");
        return 0;
    }

    char linea[100];
    pellets = 0;
    totalFantasmas = 0;

    for (int i = 0; i < FILAS; i++) {
        if (fgets(linea, sizeof(linea), archivo) == NULL) {
            fclose(archivo);
            return 0;
        }

        for (int j = 0; j < COLUMNAS; j++) {
            char c = linea[j];
            if (c == '\0' || c == '\n') c = ' ';

            mapa[i][j] = c;

            if (c == 'P') {
                jugadorFila = i;
                jugadorCol = j;
                jugadorInicioFila = i;
                jugadorInicioCol = j;
                mapa[i][j] = ' ';
            }
            else if (c == 'F') {
                if (totalFantasmas < MAX_FANTASMAS) {
                    fantasmas[totalFantasmas].fila = i;
                    fantasmas[totalFantasmas].col = j;
                    fantasmas[totalFantasmas].inicioFila = i;
                    fantasmas[totalFantasmas].inicioCol = j;
                    totalFantasmas++;
                }
                mapa[i][j] = ' ';
            }
            else if (c == '.') {
                pellets++;
            }
        }
        mapa[i][COLUMNAS] = '\0';
    }

    fclose(archivo);
    return 1;
}

int posicionValida(int fila, int col) {
    if (fila < 0 || fila >= FILAS || col < 0 || col >= COLUMNAS) return 0;
    if (mapa[fila][col] == '#') return 0;
    return 1;
}

void reiniciarPosiciones() {
    jugadorFila = jugadorInicioFila;
    jugadorCol = jugadorInicioCol;

    for (int i = 0; i < totalFantasmas; i++) {
        fantasmas[i].fila = fantasmas[i].inicioFila;
        fantasmas[i].col = fantasmas[i].inicioCol;
    }
}

void guardarPuntaje() {
    FILE *archivo = fopen("puntajes.txt", "a");
    if (archivo != NULL) {
        fprintf(archivo, "Puntaje final: %d\n", puntos);
        fclose(archivo);
    }
}

void revisarColisionFantasma() {
    for (int i = 0; i < totalFantasmas; i++) {
        if (fantasmas[i].fila == jugadorFila && fantasmas[i].col == jugadorCol) {
            vidas--;
            if (vidas <= 0) {
                juegoTerminado = 1;
                victoria = 0;
                guardarPuntaje();
            } else {
                reiniciarPosiciones();
            }
        }
    }
}

void moverJugador(int df, int dc) {
    int nuevaFila = jugadorFila + df;
    int nuevaCol = jugadorCol + dc;

    if (posicionValida(nuevaFila, nuevaCol)) {
        jugadorFila = nuevaFila;
        jugadorCol = nuevaCol;

        if (mapa[jugadorFila][jugadorCol] == '.') {
            mapa[jugadorFila][jugadorCol] = ' ';
            puntos += 10;
            pellets--;

            if (pellets <= 0) {
                juegoTerminado = 1;
                victoria = 1;
                guardarPuntaje();
            }
        }
    }

    revisarColisionFantasma();
}

void intentarMoverFantasma(int indice, int df, int dc, int *seMovio) {
    int nf = fantasmas[indice].fila + df;
    int nc = fantasmas[indice].col + dc;

    if (posicionValida(nf, nc)) {
        fantasmas[indice].fila = nf;
        fantasmas[indice].col = nc;
        *seMovio = 1;
    }
}

void moverFantasma(int indice) {
    int seMovio = 0;

  
    if (abs(jugadorCol - fantasmas[indice].col) > abs(jugadorFila - fantasmas[indice].fila)) {
        if (jugadorCol < fantasmas[indice].col) intentarMoverFantasma(indice, 0, -1, &seMovio);
        else if (jugadorCol > fantasmas[indice].col) intentarMoverFantasma(indice, 0, 1, &seMovio);
    } else {
        if (jugadorFila < fantasmas[indice].fila) intentarMoverFantasma(indice, -1, 0, &seMovio);
        else if (jugadorFila > fantasmas[indice].fila) intentarMoverFantasma(indice, 1, 0, &seMovio);
    }

    /* Si no pudo moverse por pared, prueba opciones simples. */
    if (!seMovio) intentarMoverFantasma(indice, -1, 0, &seMovio);
    if (!seMovio) intentarMoverFantasma(indice, 1, 0, &seMovio);
    if (!seMovio) intentarMoverFantasma(indice, 0, -1, &seMovio);
    if (!seMovio) intentarMoverFantasma(indice, 0, 1, &seMovio);
}

void moverFantasmas() {
    for (int i = 0; i < totalFantasmas; i++) {
        moverFantasma(i);
    }
    revisarColisionFantasma();
}

void dibujarTextura(SDL_Texture *textura, int x, int y) {
    SDL_Rect destino = {x, y, TAM, TAM};
    if (textura != NULL) {
        SDL_RenderCopy(renderer, textura, NULL, &destino);
    }
}

void renderizarMapa() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            int x = j * TAM;
            int y = i * TAM;

            if (texFondo != NULL) dibujarTextura(texFondo, x, y);
            else dibujarRectangulo(x, y, TAM, TAM, 0, 0, 0);

            if (mapa[i][j] == '#') {
                if (texPared != NULL) dibujarTextura(texPared, x, y);
                else dibujarRectangulo(x, y, TAM, TAM, 0, 0, 180);
            }
            else if (mapa[i][j] == '.') {
                if (texPellet != NULL) dibujarTextura(texPellet, x, y);
                else dibujarRectangulo(x + 12, y + 12, 8, 8, 255, 255, 255);
            }
        }
    }

    dibujarTextura(texPacman, jugadorCol * TAM, jugadorFila * TAM);
    if (texPacman == NULL) dibujarRectangulo(jugadorCol * TAM, jugadorFila * TAM, TAM, TAM, 255, 255, 0);

    for (int i = 0; i < totalFantasmas; i++) {
        dibujarTextura(texFantasma, fantasmas[i].col * TAM, fantasmas[i].fila * TAM);
        if (texFantasma == NULL) dibujarRectangulo(fantasmas[i].col * TAM, fantasmas[i].fila * TAM, TAM, TAM, 255, 0, 0);
    }

    /* Barra inferior: vidas en rojo y puntos como barras verdes.*/
    dibujarRectangulo(0, FILAS * TAM, ANCHO, 50, 30, 30, 30);
    dibujarTextoSimple(15, FILAS * TAM + 15, vidas, 255, 0, 0);
    dibujarTextoSimple(120, FILAS * TAM + 15, puntos / 10, 0, 255, 0);

    if (juegoTerminado) {
        if (victoria) dibujarRectangulo(ANCHO/2 - 70, ALTO/2 - 30, 140, 60, 0, 180, 0);
        else dibujarRectangulo(ANCHO/2 - 70, ALTO/2 - 30, 140, 60, 180, 0, 0);
    }

    SDL_RenderPresent(renderer);
}

int iniciarSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Error al iniciar SDL: %s\n", SDL_GetError());
        return 0;
    }

    ventana = SDL_CreateWindow("Pac-Man sencillo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ANCHO, ALTO, 0);
    if (ventana == NULL) {
        printf("Error al crear ventana: %s\n", SDL_GetError());
        return 0;
    }

    renderer = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Error al crear renderer: %s\n", SDL_GetError());
        return 0;
    }

    texPacman = cargarTexturaBMP("sprites/pacman.bmp");
    texFantasma = cargarTexturaBMP("sprites/fantasma.bmp");
    texPared = cargarTexturaBMP("sprites/pared.bmp");
    texPellet = cargarTexturaBMP("sprites/pellet.bmp");
    texFondo = cargarTexturaBMP("sprites/fondo.bmp");

    return 1;
}

void cerrarSDL() {
    SDL_DestroyTexture(texPacman);
    SDL_DestroyTexture(texFantasma);
    SDL_DestroyTexture(texPared);
    SDL_DestroyTexture(texPellet);
    SDL_DestroyTexture(texFondo);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(ventana);
    SDL_Quit();
}

int main(int argc, char *argv[]) {
    SDL_Event evento;
    int salir = 0;
    Uint32 ultimoMovimientoFantasma = 0;

    srand((unsigned int)time(NULL));

    if (!cargarMapa("mapa.txt")) {
        return 1;
    }

    if (!iniciarSDL()) {
        return 1;
    }

    while (!salir) {
        while (SDL_PollEvent(&evento)) {
            if (evento.type == SDL_QUIT) {
                salir = 1;
            }
            else if (evento.type == SDL_KEYDOWN && !juegoTerminado) {
                switch (evento.key.keysym.sym) {
                    case SDLK_UP:
                        moverJugador(-1, 0);
                        break;
                    case SDLK_DOWN:
                        moverJugador(1, 0);
                        break;
                    case SDLK_LEFT:
                        moverJugador(0, -1);
                        break;
                    case SDLK_RIGHT:
                        moverJugador(0, 1);
                        break;
                }
            }
            else if (evento.type == SDL_KEYDOWN && juegoTerminado) {
                if (evento.key.keysym.sym == SDLK_ESCAPE) salir = 1;
            }
        }

        if (!juegoTerminado) {
            Uint32 ahora = SDL_GetTicks();
            if (ahora - ultimoMovimientoFantasma > 350) {
                moverFantasmas();
                ultimoMovimientoFantasma = ahora;
            }
        }

        renderizarMapa();
        SDL_Delay(16);
    }

    cerrarSDL();
    return 0;
}
