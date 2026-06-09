#include "raylib.h"
#include <vector>
#include <cstdio>

struct Ball { 
    Vector2 position;
    Vector2 velocity;
    float radius;
    Color color;
};

void HandleMovement(Ball &ball, int width, int height) {

    ball.position.x += ball.velocity.x;
    ball.position.y += ball.velocity.y;

    if ((ball.position.x > width - ball.radius) || (ball.position.x < ball.radius)) {
        ball.velocity.x *= -1;
    }

    if ((ball.position.y > height - ball.radius) || (ball.position.y < ball.radius)) {
        ball.velocity.y *= -1;
    }
}

void DrawBall(const Ball& ball) {

    DrawCircleV(ball.position, ball.radius, ball.color);
}

void DrawBallPool(int ballPool, float ballRadius, int maxBallSpeed, int width, int height, std::vector<Ball>& balls){

    for (int i = 0; i < ballPool; ++i) {

        float vx = static_cast<float>(GetRandomValue(-maxBallSpeed, maxBallSpeed));
        float vy = static_cast<float>(GetRandomValue(-maxBallSpeed, maxBallSpeed));

        if (vx == 0) vx = 1.0f;
        if (vy == 0) vy = 1.0f;

        balls.push_back( Ball{ 
            
                {
                    static_cast<float>(GetRandomValue(static_cast<int>(ballRadius), width - static_cast<int>(ballRadius))),

                    static_cast<float>(GetRandomValue(static_cast<int>(ballRadius), height - static_cast<int>(ballRadius)))
                },

                { vx, vy },

                ballRadius,

                {
                    static_cast<unsigned char>(GetRandomValue(0, 255)),
                    static_cast<unsigned char>(GetRandomValue(0, 255)),
                    static_cast<unsigned char>(GetRandomValue(0, 255)),
                    255
                }
            }
        );
    }
}

void DrawBall(std::vector<Ball>& balls) {
        
    for (const auto& ball : balls) { 
        DrawBall(ball); 
    }
}

void HandleMovement(std::vector<Ball>& balls, int width, int height) {

    for (auto& ball : balls) {
        HandleMovement(ball, width, height);
    }

}

int main() {

    int width = 600;
    int height = 400;
    float radius = 5.0f;

    int collisionChecks = 0;

    int cellSize = 100;

    int cols = width / cellSize;
    int rows = height / cellSize;

    std::vector<std::vector<int>> grid(cols * rows);

    printf("cols: %d, rows: %d\n", cols, rows);

    std::vector<Ball> balls;

    InitWindow(width, height, "Hello Raylib");
    
    SetTargetFPS(60);

    DrawBallPool(100, radius, 3.0f, width, height, balls);

    for (const auto& ball : balls) {

        int cellX = ball.position.x / cellSize;
        int cellY = ball.position.y / cellSize;

        printf("Ball in cell (%d,%d)\n", cellX, cellY);
    }
        
    while (!WindowShouldClose()) {

            collisionChecks = 0;

            for (auto& cell : grid) {
                cell.clear();
            }

            for (auto& ball : balls){
                ball.color = RED;
            }

            for (int i = 0; i < balls.size(); i++){

                int cellX = balls[i].position.x / cellSize;
                int cellY = balls[i].position.y / cellSize;

                int cellIndex = cellY * cols + cellX;

                grid[cellIndex].push_back(i);
            }

            for (int i = 0; i < grid.size(); i++) {

                if (!grid[i].empty()) {

                    //printf("Cell %d contains %d balls\n", i, (int)grid[i].size());
                }
            }
                    
            for (int cellY = 0; cellY < rows; cellY++) {

                for (int cellX = 0; cellX < cols; cellX++) {

                    int currentCell = cellY * cols + cellX;

                    for (int i = 0; i < grid[currentCell].size(); i++) {

                        for (int j = i + 1; j < grid[currentCell].size(); j++) {

                            int ballA = grid[currentCell][i];

                            int ballB = grid[currentCell][j];

                            collisionChecks++;

                            if (CheckCollisionCircles(
                                balls[ballA].position,
                                balls[ballA].radius,
                                balls[ballB].position,
                                balls[ballB].radius))
                            {
                                balls[ballA].color = WHITE;
                                balls[ballB].color = WHITE;
                            }
                        }
                    }

                    int neighborOffsets[4][2] =
                    {
                        { 1, 0 },
                        { 0, 1 },
                        { 1, 1 },
                        { -1, 1 }
                    };

                    for (int n = 0; n < 4; n++) {

                        int nx = cellX + neighborOffsets[n][0];
                        int ny = cellY + neighborOffsets[n][1];

                        if (nx < 0 || nx >= cols ||
                            ny < 0 || ny >= rows)
                            continue;

                        int neighborCell = ny * cols + nx;

                        for (int a : grid[currentCell]) {

                            for (int b : grid[neighborCell]) {

                                collisionChecks++;

                                if (CheckCollisionCircles(
                                    balls[a].position,
                                    balls[a].radius,
                                    balls[b].position,
                                    balls[b].radius))
                                {
                                    balls[a].color = WHITE;
                                    balls[b].color = WHITE;
                                }
                            }
                        }
                    }
                }
            }
                    
            BeginDrawing();

            ClearBackground(BLACK);
            
            for (int x = 0; x <= width; x += cellSize) {

                DrawLine(x, 0, x, height, DARKGRAY);
            }

            for (int y = 0; y <= height; y += cellSize){
                
                DrawLine(0, y, width, y, DARKGRAY);
            } 

            
            DrawFPS(10, 10);
            
            DrawBall(balls);
            
            DrawText(
            TextFormat("Count: %i", balls.size()),
                10,
                40,
                20,
                WHITE
            );

            DrawText(
            TextFormat("Checks: %d", collisionChecks),
                10,
                70,
                20,
                WHITE
            );





        EndDrawing();
            
        HandleMovement(balls, width, height);

    }


    CloseWindow();
    return 0;
}

