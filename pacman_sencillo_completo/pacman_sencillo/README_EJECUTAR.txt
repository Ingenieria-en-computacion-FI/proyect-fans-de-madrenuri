PAC-MAN SENCILLO EN C CON SDL2

REQUISITOS:
- MSYS2 instalado
- SDL2 instalado en MSYS2
- Compilador gcc

COMO COMPILAR EN MSYS2:

1. Abrir MSYS2 UCRT64.
2. Entrar a la carpeta del proyecto. Ejemplo:
   cd /c/Users/TU_USUARIO/Desktop/pacman_sencillo

3. Compilar:
   gcc main.c -o pacman.exe -lmingw32 -lSDL2main -lSDL2

4. Ejecutar:
   ./pacman.exe

CONTROLES:
- Flecha arriba: mover arriba
- Flecha abajo: mover abajo
- Flecha izquierda: mover izquierda
- Flecha derecha: mover derecha
- Cerrar ventana: salir
- Cuando termina el juego, ESC para salir

ARCHIVOS IMPORTANTES:
- main.c: codigo fuente
- mapa.txt: nivel cargado desde archivo
- puntajes.txt: aqui se guardan los puntajes finales
- sprites/: imagenes BMP del jugador, fantasmas, pared, pellet y fondo

NOTA:
No se usa SDL_ttf ni SDL_image porque el proyecto pide SDL2 y no bibliotecas graficas adicionales.
