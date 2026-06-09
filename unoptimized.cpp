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

    if ((ball.position.x > width - ball.radius || ball.position.x < ball.radius)) {
        ball.velocity.x *= -1;
    }
    if ((ball.position.y > height - ball.radius || ball.position.y < ball.radius)) {
        ball.velocity.y *= -1;
    }
}

void DrawBall(const Ball& ball) {

    DrawCircleV(ball.position, ball.radius, ball.color);
}

void DrawBallPool(int ballPool, float ballRadius, int maxBallSpeed, int width, int height, std::vector<Ball>& balls) {

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

    std::vector<Ball> balls;

    InitWindow(width, height, "Hello Raylib");
    
    SetTargetFPS(60);

    DrawBallPool(100, radius, 3.0f, width, height, balls);

    for (const auto&ball : balls) {
        
        printf("Ball: %.0f %.0f\n",
            ball.position.x,
            ball.position.y);
        }
        
        while (!WindowShouldClose()) {

            collisionChecks = 0;

            for (auto& ball : balls)
            {
                ball.color = RED;
            }

            for (int i = 0; i < balls.size(); i++) {
                
                for (int j = i + 1; j < balls.size(); j++) {

                    collisionChecks++;

                    if (CheckCollisionCircles(
                        balls[i].position,
                        balls[i].radius,
                        balls[j].position,
                        balls[j].radius))
                    {
                        balls[i].color = WHITE;
                        balls[j].color = WHITE;
                    }
                }
            }     
                    
                    

                    
            BeginDrawing();
            ClearBackground(BLACK);
            
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

