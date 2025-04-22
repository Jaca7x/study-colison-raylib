#include "librays/raylib.h"
#include <stdlib.h>

//                                             AABB EXAMPLE 
//              MÁQUINA                            |                        HUMANO
/*  if (player1.x < player2.x + player2.width &&   |  Se Pos1.x menor que Pos2.x + largura P2 E. - Pos1,2: posição P1/2
    player1.x + player1.width > player2.x &&       |  Pos1.x + largura P1 maior que Pos2.x E. - P1,P2: player1,2
    player1.y < player2.y + player2.height &&      |  Pos1.y menor que Pos2.y + altura P1 E. - x: horizontal y: vertical
    player1.y + player1.height > player2.y) {...}  |  Pos1.y + altura P1 maior que Pos2.y {então colide}.
*/

int main() {

    const int screenWidth = 800;
    const int screeHeight = 600;

    InitWindow(screenWidth, screeHeight, "Collision");

    SetTargetFPS(60);

    Rectangle player1 = {screenWidth / 3, 200, 50, 40};  //Definindo retangulo P1 {x,y,width,height}
    Rectangle player2 = {screenWidth / 2, 200, 100, 40}; //Definindo retangulo P2 {x,y,width,height}

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_A)) player1.x -= 1; //Mover player 1 para esquerda Pos1.x - 1
        if (IsKeyDown(KEY_D)) player1.x += 1; //Mover player 1 para direita Pos1.x + 1
        if (IsKeyDown(KEY_S)) player1.y += 1; //Mover player 1 para baixo Pos1.y + 1
        if (IsKeyDown(KEY_W)) player1.y -= 1; //Mover player 1 para cima Pos1.y - 1  
        
        if (player1.x < player2.x + player2.width &&  //Se Pos1.x menor que Pos2.x + largura P2 E. - Pos1,2: posição P1/2
            player1.x + player1.width > player2.x &&   //Pos1.x + largura P1 maior que Pos2.x E. - P1,P2: player1,2
            player1.y < player2.y + player2.height && //Pos1.y menor que Pos2.y + altura P1 E. - x: horizontal y: vertical
            player1.y + player1.height > player2.y)    //Pos1.y + altura P1 maior que Pos2.y {então colide}.
        {
           DrawText("Colidiu", screenWidth / 2, screeHeight / 2, 20, RED); //Escrevendo texto se houver colisão
        }

        BeginDrawing();
        ClearBackground(BLACK); 

        DrawRectangleRec(player1, RED);  //Desenhando retangulo player 1
        DrawRectangleRec(player2, BLUE); //Desenhando retangulo player 2
        EndDrawing();
    }
    CloseWindow();

    return 0;
}