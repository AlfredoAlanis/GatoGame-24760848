/*
[0][0][0]
[0][0][0]
[0][0][0]
1 vs pc
int gato[3][3];
player = 1
pc = 2
random (player,pc)
casillas_ocupadas = 0
filtro de no ocupacion
input - player - pc -> x,y -2
validar a partir del 5 movimiento
validador / \ - |
resetear el juego,
    limpiar matriz, movimientos, mensajes
puntuaciones
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char gato[3][3]; // matriz del juego
int casillas_ocupadas = 0; // contador de casillas usadas

// función para mostrar el tablero en pantalla
void mostrar() {
    for (int i = 0; i < 3; i++) { // filas
        for (int j = 0; j < 3; j++) { // columnas
            printf("[%c]", gato[i][j]); // muestra el contenido
        }
        printf("\n");
    }
}

// función para revisar si alguien ganó
char ganador() {
    // filas
    for (int i = 0; i < 3; i++) {
        if (gato[i][0] == gato[i][1] && gato[i][1] == gato[i][2] && gato[i][0] != ' ')
            return gato[i][0];
    }
    // columnas
    for (int j = 0; j < 3; j++) {
        if (gato[0][j] == gato[1][j] && gato[1][j] == gato[2][j] && gato[0][j] != ' ')
            return gato[0][j];
    }
    // diagonales
    if (gato[0][0] == gato[1][1] && gato[1][1] == gato[2][2] && gato[0][0] != ' ')
        return gato[0][0];
    if (gato[0][2] == gato[1][1] && gato[1][1] == gato[2][0] && gato[0][2] != ' ')
        return gato[0][2];

    // si nadie gana
    return ' ';
}

int main() {
    srand(time(NULL)); // inicializa los números aleatorios
    int x, y, turno;
    char player = 'X', pc = 'O', win = ' ';
    char otra = 's';
    int puntos_player = 0, puntos_pc = 0;

    printf("=== JUEGO DEL GATO ===\n");

    while (otra == 's' || otra == 'S') {

        // limpiar el tablero
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                gato[i][j] = ' ';

        casillas_ocupadas = 0;
        win = ' ';
        turno = rand() % 2; // decide al azar quién empieza

        // mientras no se llene el tablero ni haya ganador
        while (casillas_ocupadas < 9 && win == ' ') {
            mostrar(); // muestra el tablero actual

            if (turno == 0) { // turno del jugador
                printf("Tu turno (fila columna 0-2): ");
                scanf("%d %d", &x, &y);

                // validaciones simples
                if (x >= 0 && x < 3 && y >= 0 && y < 3) {
                    if (gato[x][y] == ' ') {
                        gato[x][y] = player;
                        casillas_ocupadas++;
                        turno = 1; // pasa turno a la pc
                    } else {
                        printf("Casilla ocupada!\n");
                    }
                } else {
                    printf("Fuera de rango!\n");
                }

            } else { // turno de la PC
                x = rand() % 3;
                y = rand() % 3;
                if (gato[x][y] == ' ') {
                    gato[x][y] = pc;
                    printf("PC juega en [%d][%d]\n", x, y);
                    casillas_ocupadas++;
                    turno = 0;
                }
            }

            // se empieza a revisar si alguien gana a partir del 5to movimiento
            if (casillas_ocupadas >= 5)
                win = ganador();
        }

        mostrar(); // muestra el resultado final

        // mensajes según quien gane
        if (win == player) {
            printf("¡Ganaste!\n");
            puntos_player++;
        } else if (win == pc) {
            printf("Gana la PC!\n");
            puntos_pc++;
        } else {
            printf("Empate!\n");
        }

        // muestra las puntuaciones acumuladas
        printf("Puntos -> Jugador: %d | PC: %d\n", puntos_player, puntos_pc);

        // preguntar si se quiere jugar otra vez
        printf("¿Otra partida? (s/n): ");
        scanf(" %c", &otra);
    }

    printf("Juego terminado. Gracias por jugar.\n");
    return 0;
}