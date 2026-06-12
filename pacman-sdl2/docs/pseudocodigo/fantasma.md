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