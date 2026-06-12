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