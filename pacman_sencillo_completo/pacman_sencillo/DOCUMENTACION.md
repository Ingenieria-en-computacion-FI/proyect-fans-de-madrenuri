# Documentación del proyecto: Pac-Man sencillo

## 1. Análisis del problema

### Entradas
- Teclado: flechas de dirección para mover al jugador.
- Archivo `mapa.txt`: contiene el laberinto del juego.

### Procesos
- Cargar el mapa desde archivo.
- Mostrar el mapa con sprites usando SDL2.
- Mover al jugador si no hay pared.
- Consumir pellets y sumar puntos.
- Mover 4 fantasmas con persecución simple.
- Detectar colisiones entre jugador y fantasmas.
- Restar vidas.
- Determinar victoria o derrota.
- Guardar el puntaje final en `puntajes.txt`.

### Salidas
- Ventana gráfica con el juego.
- Barra inferior con vidas y puntos representados por bloques.
- Archivo `puntajes.txt` con el puntaje final.
- Pantalla final: cuadro verde si gana, cuadro rojo si pierde.

## 2. Reglas del juego

- El jugador inicia con 2 vidas.
- Cada pellet vale 10 puntos.
- Hay 4 fantasmas.
- El juego termina si el jugador pierde sus vidas.
- El juego termina con victoria si consume todos los pellets.

## 3. Modularización

Funciones principales usadas en el programa:

- `cargarMapa`: lee el archivo `mapa.txt` y llena el arreglo bidimensional.
- `posicionValida`: revisa si una posición no es pared.
- `moverJugador`: mueve al jugador y consume pellets.
- `moverFantasma`: mueve un fantasma con reglas simples.
- `moverFantasmas`: mueve todos los fantasmas.
- `revisarColisionFantasma`: revisa si el jugador toca un fantasma.
- `guardarPuntaje`: guarda el puntaje en archivo.
- `renderizarMapa`: dibuja el mapa y los personajes.
- `iniciarSDL`: inicializa SDL2 y carga sprites.
- `cerrarSDL`: libera recursos y cierra SDL2.

## 4. Pseudocódigo general

```text
Inicio
    Cargar mapa desde archivo
    Iniciar SDL2
    Cargar sprites

    Mientras el usuario no cierre la ventana
        Leer eventos del teclado

        Si se presiona una flecha
            intentar mover jugador
            si pisa pellet
                sumar 10 puntos
                eliminar pellet
            revisar colisión con fantasma
        Fin si

        Cada cierto tiempo
            mover fantasmas hacia el jugador
            revisar colisión con fantasma
        Fin cada cierto tiempo

        Dibujar mapa, jugador, fantasmas, vidas y puntaje

        Si vidas son 0
            guardar puntaje
            mostrar derrota
        Fin si

        Si pellets son 0
            guardar puntaje
            mostrar victoria
        Fin si
    Fin mientras

    Cerrar SDL2
Fin
```

## 5. Pseudocódigo: movimiento del jugador

```text
Función moverJugador(cambioFila, cambioColumna)
    nuevaFila = jugadorFila + cambioFila
    nuevaColumna = jugadorColumna + cambioColumna

    Si nueva posición no es pared
        jugadorFila = nuevaFila
        jugadorColumna = nuevaColumna

        Si mapa[jugadorFila][jugadorColumna] es pellet
            cambiar esa posición a espacio vacío
            puntos = puntos + 10
            pellets = pellets - 1
        Fin si
    Fin si

    revisar colisión con fantasmas
Fin función
```

## 6. Pseudocódigo: fantasma

```text
Función moverFantasma(fantasma)
    seMovio = falso

    Si la distancia horizontal es mayor que la vertical
        Si jugador está a la izquierda
            intentar mover izquierda
        Si jugador está a la derecha
            intentar mover derecha
    Si no
        Si jugador está arriba
            intentar mover arriba
        Si jugador está abajo
            intentar mover abajo
    Fin si

    Si no pudo moverse
        intentar arriba
        intentar abajo
        intentar izquierda
        intentar derecha
    Fin si
Fin función
```

## 7. Diagramas de flujo en texto

### Ciclo principal

```text
[Inicio]
   ↓
[Cargar mapa]
   ↓
[Iniciar SDL2]
   ↓
[Leer eventos]
   ↓
[Actualizar jugador/fantasmas]
   ↓
[Revisar victoria o derrota]
   ↓
[Renderizar juego]
   ↓
¿Cerrar ventana?
   ├── No → regresar a Leer eventos
   └── Sí → [Cerrar SDL2] → [Fin]
```

### Movimiento y colisiones

```text
[Tecla presionada]
   ↓
[Calcular nueva posición]
   ↓
¿Es pared?
   ├── Sí → [No mover]
   └── No → [Mover jugador]
              ↓
           ¿Hay pellet?
              ├── Sí → [Sumar 10 puntos]
              └── No → [Continuar]
              ↓
           ¿Toca fantasma?
              ├── Sí → [Restar vida]
              └── No → [Continuar]
```

### Fantasmas

```text
[Inicio movimiento fantasma]
   ↓
[Comparar posición del jugador y fantasma]
   ↓
[Intentar acercarse]
   ↓
¿Hay pared?
   ├── No → [Mover fantasma]
   └── Sí → [Probar otra dirección válida]
   ↓
[Revisar colisión con jugador]
```

## 8. Explicación del uso de archivos

El archivo `mapa.txt` representa el nivel del juego.

Símbolos:

| Símbolo | Significado |
|---|---|
| `#` | Pared |
| `.` | Pellet |
| `P` | Posición inicial del jugador |
| `F` | Posición inicial de un fantasma |
| espacio | Camino libre |

El archivo `puntajes.txt` se crea o actualiza al terminar una partida. En él se guarda el puntaje final.

## 9. Restricciones respetadas

- Se usó lenguaje C.
- Se usó SDL2.
- No se usó C++.
- No se usó motor de videojuegos.
- No se usaron bibliotecas gráficas adicionales.
- No se implementó inteligencia artificial avanzada.
- Los fantasmas usan reglas simples de comparación de posición.
