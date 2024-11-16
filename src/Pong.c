#include <raylib.h>

static const int screenWidth = 600;
static const int screenHeight = 400;

struct Paddle
{
    Vector2 position;
    Vector2 size;
    int score;
};

struct Ball 
{
    Vector2 position;
    Vector2 velocity;
    float radius;
};

void ballReset(struct Ball* ball)
{
    ball->position.x = screenWidth/2.00;
    ball->position.y = screenHeight/2.00;
    ball->velocity.x = 7; 
    ball->velocity.y = 7; 
    ball->radius = 10;
}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------

    const int paddleWidth = 20;
    const int paddleHeight = 80;

    const int increments = 10;

    InitWindow(screenWidth, screenHeight, "Pong");
    
    struct Paddle paddles[2] = {0};

    paddles[0].position.x = 0;
    paddles[0].position.y = 0;
    paddles[0].size.x = paddleWidth;
    paddles[0].size.y = paddleHeight; 
    paddles[0].score = 0; 

    paddles[1].position.x = screenWidth - paddleWidth;
    paddles[1].position.y = 0;
    paddles[1].size.x = paddleWidth;
    paddles[1].size.y = paddleHeight;
    paddles[1].score = 0; 

    struct Ball ball = {0};
     
    ballReset(&ball);

    int key = GetKeyPressed();
     


    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if(!IsKeyDown(key))
        {
            key = GetKeyPressed(); 
        }  
        switch(key)
        {
            case KEY_W:
                {
                    if(paddles[0].position.y >= increments)
                    {
                        paddles[0].position.y -= increments;
                    }
                }break;
            case KEY_S:
                {
                    if(paddles[0].position.y < screenHeight - paddleHeight)
                    {
                        paddles[0].position.y += increments;
                    }
                }break;
            case KEY_UP:
                {
                    if(paddles[1].position.y >= increments)
                    {
                        paddles[1].position.y -= increments;
                    }
                }break;
            case KEY_DOWN:
                {
                    if(paddles[1].position.y < screenHeight - paddleHeight)
                    {
                        paddles[1].position.y += increments;
                    }
                }break;
        }
        
        
        ball.position.x += ball.velocity.x; 
        ball.position.y += ball.velocity.y; 


        if(ball.position.y + ball.radius >= screenHeight || ball.position.y - ball.radius <= 0)
        {
            ball.velocity.y *= -1;
        }

        
        for(int i = 0 ; i < 2 ; i++)
        {
            if(ball.position.x >= paddles[i].position.x && ball.position.x <= paddles[i].position.x + paddles[i].size.x
            && ball.position.y >= paddles[i].position.y && ball.position.y <= paddles[i].position.y + paddles[i].size.y)
            {
                ball.velocity.x *= -1;
            }
        }

        if(ball.position.x >= screenWidth)
        {
            paddles[0].score++;
            ballReset(&ball);
        }
        if(ball.position.x <= 0)
        {
            paddles[1].score++; 
            ballReset(&ball);
        }
        

        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
    //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);
            DrawCircleV(ball.position,ball.radius,WHITE);
            for(int i = 0 ; i < 2 ; i++)
            {
                if(i == 0)
                {
                    DrawText(TextFormat("%d",paddles[i].score), 120, 0, 40,WHITE);       // Draw text (using default font)
                }
                else
                {
                    DrawText(TextFormat("%d",paddles[i].score), screenWidth - 120, 0, 40, WHITE);       // Draw text (using default font)
                }
                DrawRectangleV(paddles[i].position, paddles[i].size,WHITE);                                  
            }
            
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}





