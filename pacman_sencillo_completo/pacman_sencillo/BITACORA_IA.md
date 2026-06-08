# Bitácora de desarrollo y uso de IA

## Proyecto
Videojuego tipo Pac-Man simplificado en lenguaje C usando SDL2.

## Equipo
El equipo no tenía experiencia programando, por eso se decidió hacer una versión sencilla, funcional y entendible.

## Decisiones de diseño
- Se decidió usar un solo nivel para mantener el alcance del proyecto.
- El mapa se carga desde `mapa.txt` para cumplir con el requisito de manejo de archivos.
- Se usaron sprites BMP para no necesitar bibliotecas adicionales como SDL_image.
- No se usó SDL_ttf, porque también sería una biblioteca adicional.
- El puntaje y las vidas se representan con bloques de colores.
- Los fantasmas tienen persecución simple, no inteligencia artificial avanzada.

## Problemas encontrados
- Al principio no era claro cómo cargar un mapa desde archivo.
- También había duda sobre cómo usar sprites sin instalar más bibliotecas.
- Se decidió usar archivos BMP porque SDL2 puede cargarlos directamente.
- Para los fantasmas, se evitó usar búsqueda de caminos porque el proyecto no lo pide.

## Uso de herramientas de IA

### Herramienta utilizada
ChatGPT.

### Consulta realizada
“Necesitamos hacer un Pac-Man en C con SDL2, con 1 nivel, 4 fantasmas, 2 vidas, sprites, mapa desde archivo y puntajes guardados. No sabemos programar y debe cumplir restricciones sin IA avanzada.”

### Fragmento de respuesta obtenida
Se recomendó hacer el proyecto por módulos: carga de mapa, movimiento del jugador, colisiones, fantasmas, renderizado y guardado de puntaje. También se sugirió usar sprites BMP para no agregar bibliotecas externas.

### Cómo se utilizó la respuesta
La respuesta se usó como guía para organizar el proyecto. El equipo revisó las funciones, entendió qué hace cada parte y adaptó el mapa, sprites y documentación. La lógica de fantasmas se mantuvo simple para respetar las restricciones del proyecto.

## Distribución sugerida de tareas

| Integrante | Actividad |
|---|---|
| 1 | Revisar SDL2, ventana y renderizado |
| 2 | Revisar archivo `mapa.txt` y carga de mapa |
| 3 | Explicar movimiento del jugador y colisiones |
| 4 | Explicar movimiento de fantasmas |
| 5 | Revisar puntajes, vidas, documentación y presentación |

## Pruebas realizadas

| Prueba | Resultado esperado |
|---|---|
| Abrir el juego | Se abre una ventana con el mapa |
| Mover jugador contra pared | El jugador no atraviesa paredes |
| Comer pellet | El pellet desaparece y suma 10 puntos |
| Tocar fantasma | Se pierde una vida |
| Perder 2 vidas | Se muestra derrota y se guarda puntaje |
| Comer todos los pellets | Se muestra victoria y se guarda puntaje |
| Revisar `puntajes.txt` | Aparece el puntaje final |

## Conclusión
El proyecto permitió aplicar programación estructurada, funciones, arreglos bidimensionales, manejo de archivos y SDL2. La versión es sencilla, pero cumple con los requisitos principales del trabajo final.
