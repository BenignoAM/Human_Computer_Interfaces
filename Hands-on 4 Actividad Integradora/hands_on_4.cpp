#include "raylib.h"
#include "rlgl.h"
#include <cmath>

int main() {
    InitWindow(1000, 700, "Actividad Integradora - Transformaciones 2D/3D");
    SetTargetFPS(60);

    int escenaActual = 1;

    // Variables globales para las animaciones
    float t = 0.0f;
    
    // Variables Traslacion 3D
    float traslacionX = -5.0f;
    Camera3D camaraTras = { { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, CAMERA_PERSPECTIVE };
    
    // Variables Rotacion 3D
    float anguloRotacion = 0.0f;
    Camera3D camaraRot = { { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, CAMERA_PERSPECTIVE };

    // Variables Rebote
    float rebotePos = 120.0f;
    int reboteDir = 1;
    float rapidez = 250.0f;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        t += dt;

        // --- NAVEGACION DE MENU ---
        if (IsKeyPressed(KEY_ONE)) escenaActual = 1;
        if (IsKeyPressed(KEY_TWO)) escenaActual = 2;
        if (IsKeyPressed(KEY_THREE)) escenaActual = 3;
        if (IsKeyPressed(KEY_FOUR)) escenaActual = 4;
        if (IsKeyPressed(KEY_FIVE)) escenaActual = 5;
        if (IsKeyPressed(KEY_SIX)) escenaActual = 6;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Menu Superior
        DrawRectangle(0, 0, 1000, 50, DARKGRAY);
        DrawText("Teclas: 1.Traslacion(3D)  2.Rotacion(3D)  3.Rebote(2D)  4.Senoidal(2D)  5.Trayectoria(2D)  6.Orbita(2D)", 20, 15, 18, WHITE);

        // --- LOGICA DE DIBUJO POR ESCENA ---
        if (escenaActual == 1) { // 1. TRASLACION 3D
            UpdateCamera(&camaraTras, CAMERA_ORBITAL);
            traslacionX += 0.03f;
            if (traslacionX > 5.0f) traslacionX = -5.0f;

            BeginMode3D(camaraTras);
            DrawGrid(20, 1.0f);
            DrawCube({ traslacionX, 1.0f, 0.0f }, 2.0f, 2.0f, 2.0f, BLUE);
            DrawCubeWires({ traslacionX, 1.0f, 0.0f }, 2.0f, 2.0f, 2.0f, DARKBLUE);
            EndMode3D();
            DrawText("1. Traslacion 3D", 20, 70, 30, DARKBLUE);
        }
        else if (escenaActual == 2) { // 2. ROTACION 3D
            UpdateCamera(&camaraRot, CAMERA_ORBITAL);
            anguloRotacion += 1.0f;

            BeginMode3D(camaraRot);
            DrawGrid(20, 1.0f);
            rlPushMatrix();
            rlTranslatef(0.0f, 1.0f, 0.0f);
            rlRotatef(anguloRotacion, 0.0f, 1.0f, 0.0f);
            DrawCube({ 0.0f, 0.0f, 0.0f }, 2.0f, 2.0f, 2.0f, ORANGE);
            DrawCubeWires({ 0.0f, 0.0f, 0.0f }, 2.0f, 2.0f, 2.0f, BROWN);
            rlPopMatrix();
            EndMode3D();
            DrawText("2. Rotacion 3D", 20, 70, 30, DARKBLUE);
        }
        else if (escenaActual == 3) { // 3. REBOTE 2D
            rebotePos += (reboteDir * rapidez) * dt;
            if (rebotePos >= 1000 - 30) { reboteDir = -1; rebotePos = 1000 - 30; }
            if (rebotePos <= 30) { reboteDir = 1; rebotePos = 30; }

            DrawCircle(rebotePos, 350, 30, ORANGE);
            DrawText("3. Rebote 2D", 20, 70, 30, DARKBLUE);
            DrawText("x = x + (dir * rapidez) * dt", 20, 110, 20, DARKGRAY);
        }
        else if (escenaActual == 4) { // 4. SENOIDAL 2D
            float m = 80.0f * sinf(2.0f * t);
            DrawCircle(500 + m, 350, 20, RED);
            DrawText("4. Movimiento Senoidal 2D", 20, 70, 30, DARKBLUE);
            DrawText("m = A * sin(w * t)", 20, 110, 20, DARKGRAY);
        }
        else if (escenaActual == 5) { // 5. TRAYECTORIA 2D ANIMADA
            Vector2 P = { 400, 350 }; 
            Vector2 v = { 200, -100 }; 
            Vector2 P_final = { P.x + v.x, P.y + v.y };
            float ciclo = fmod(t, 2.0f) / 2.0f; 
            Vector2 P_animado = { P.x + (v.x * ciclo), P.y + (v.y * ciclo) };

            DrawLineEx(P, P_final, 4, LIGHTGRAY);
            DrawCircleV(P, 8, DARKGRAY); DrawText("Origen (P)", P.x - 20, P.y + 15, 20, DARKGRAY);
            DrawCircleV(P_final, 8, DARKGRAY); DrawText("Destino (P')", P_final.x + 10, P_final.y - 25, 20, DARKGRAY);
            DrawCircleV(P_animado, 12, BLUE);
            DrawLineEx(P, P_animado, 4, BLUE);
            
            DrawText("5. Trayectoria 2D (Animada)", 20, 70, 30, DARKBLUE);
            DrawText("P_actual = P + (v * tiempo)", 20, 110, 20, DARKGRAY);
        }
        else if (escenaActual == 6) { // 6. ORBITA 2D
            float x = 500.0f + 120.0f * cosf(1.5f * t);
            float y = 350.0f + 120.0f * sinf(1.5f * t);

            DrawCircleLines(500, 350, 120, LIGHTGRAY);
            DrawCircle(500, 350, 4, BLACK);
            DrawLine(500, 350, x, y, GRAY);
            DrawCircle(x, y, 10, RED);
            
            DrawText("6. Orbita 2D", 20, 70, 30, DARKBLUE);
            DrawText("x = x0 + r*cos(wt), y = y0 + r*sin(wt)", 20, 110, 20, DARKGRAY);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}