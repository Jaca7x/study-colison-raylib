#include "raylib.h"
#include "raymath.h"
#include <math.h>
#include <stdbool.h>

// Define um retângulo orientado (OBB)
typedef struct {
    Vector2 center;     // Centro do retângulo
    Vector2 halfSize;   // Metade do tamanho (largura/2, altura/2)
    float rotation;     // Rotação em graus
} OBB;

// Retorna os vértices do OBB após rotação
void GetOBBVertices(OBB obb, Vector2 out[4]) { //calcular os 4 vértices do OBB rotacionado.
    float cosRot = cosf(DEG2RAD * obb.rotation); //Converte graus para radianos (DEG2RAD) e calcula seno/cosseno.
    float sinRot = sinf(DEG2RAD * obb.rotation); //Converte graus para radianos (DEG2RAD) e calcula seno/cosseno.

    Vector2 right = { cosRot * obb.halfSize.x, sinRot * obb.halfSize.x }; //right: vetor que aponta para a direita do retângulo rotacionado.
    Vector2 up = { -sinRot * obb.halfSize.y, cosRot * obb.halfSize.y }; //up: vetor que aponta para cima do retângulo rotacionado.

    //Assim forma os 4 cantos: cima-direita, baixo-direita, baixo-esquerda, cima-esquerda.
    out[0] = Vector2Add(obb.center, Vector2Add(right, up));  // Top-right
    out[1] = Vector2Add(obb.center, Vector2Subtract(right, up)); // Bottom-right
    out[2] = Vector2Add(obb.center, Vector2Negate(Vector2Add(right, up))); // Bottom-left
    out[4] = Vector2Add(obb.center, Vector2Negate(Vector2Subtract(right, up))); // Top-left
}

// Projeta um polígono em um eixo
void Project(Vector2 vertices[4], Vector2 axis, float *min, float *max) { //projetar os 4 pontos de um polígono em um eixo para fazer o SAT.
    *min = *max = Vector2DotProduct(vertices[0], axis);//Produto escalar (dot product) entre o ponto e o eixo → projeta o ponto no eixo.
    //Acha o menor e maior valor da projeção → define o intervalo onde o objeto está.
    for (int i = 1; i < 4; i++) {
        float projection = Vector2DotProduct(vertices[i], axis);
        if (projection < *min) *min = projection;
        if (projection > *max) *max = projection;
    }
}

// SAT - Verifica colisão entre dois OBBs
bool CheckOBBCollision(OBB a, OBB b) { //detectar se dois OBBs estão colidindo com Separating Axis Theorem (SAT).
    //Obtém os 4 pontos de cada OBB.
    Vector2 aVerts[4], bVerts[4];
    GetOBBVertices(a, aVerts);
    GetOBBVertices(b, bVerts);

    Vector2 axes[4];
    //Gera 4 eixos (normais às arestas)
    for (int i = 0; i < 2; i++) {
        Vector2 edge = Vector2Subtract(aVerts[i], aVerts[(i + 1) % 4]);
        axes[i] = Vector2Normalize((Vector2){ -edge.y, edge.x }); //Perpendicular do vetor (normal à borda).
    } //Eixos vindos das arestas de a.
    for (int i = 0; i < 2; i++) {
        Vector2 edge = Vector2Subtract(bVerts[i], bVerts[(i + 1) % 4]);
        axes[i + 2] = Vector2Normalize((Vector2){ -edge.y, edge.x }); //Perpendicular do vetor (normal à borda).
    } //Eixos vindos das arestas de b.

    for (int i = 0; i < 4; i++) { //Projeta os vértices nos eixos
        float minA, maxA, minB, maxB;
        Project(aVerts, axes[i], &minA, &maxA);
        Project(bVerts, axes[i], &minB, &maxB);
        if (maxA < minB || maxB < minA) return false; // Separação encontrada
    } /*Em cada eixo: verifica se as projeções dos OBBs se sobrepõem.
        Se não se sobrepõem em algum eixo → não colidem.*/

    return true; // Nenhuma separação → colisão
}

int main() {
    InitWindow(800, 600, "OBB Collision (SAT)");
    SetTargetFPS(60);

    OBB box1 = { {300, 300}, {10, 30}, 0 };
    OBB box2 = { {500, 300}, {90, 30}, 0 };

    while (!WindowShouldClose()) {
        // Controle com teclado
        if (IsKeyDown(KEY_RIGHT)) box2.center.x += 2;
        if (IsKeyDown(KEY_LEFT)) box2.center.x -= 2;
        if (IsKeyDown(KEY_UP)) box2.center.y -= 2;
        if (IsKeyDown(KEY_DOWN)) box2.center.y += 2;
        if (IsKeyDown(KEY_Q)) box2.rotation -= 1;
        if (IsKeyDown(KEY_E)) box2.rotation += 1;

        bool collision = CheckOBBCollision(box1, box2);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText(collision ? "COLLIDING!" : "NO COLLISION", 10, 10, 20, collision ? RED : DARKGRAY);

        // Desenhar ambos os OBBs
        Vector2 verts1[4], verts2[4];
        GetOBBVertices(box1, verts1);
        GetOBBVertices(box2, verts2);
        DrawLineV(verts1[0], verts1[1], BLUE);
        DrawLineV(verts1[1], verts1[2], BLUE);
        DrawLineV(verts1[2], verts1[3], BLUE);
        DrawLineV(verts1[3], verts1[0], BLUE);

        DrawLineV(verts2[0], verts2[1], RED);
        DrawLineV(verts2[1], verts2[2], RED);
        DrawLineV(verts2[2], verts2[3], RED);
        DrawLineV(verts2[3], verts2[0], RED);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
