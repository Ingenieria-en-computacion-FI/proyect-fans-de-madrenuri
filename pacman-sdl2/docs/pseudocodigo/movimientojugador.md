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