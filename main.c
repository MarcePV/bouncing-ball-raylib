#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>
#include <stdint.h>
//#include <stdio.h>

typedef struct
{
  Vector2 center;
  Vector2 velocity;
  int radius;
  Color color;
} circle_t;

void apply_acceleration(circle_t *const pCircle, Vector2 a, float dt);
bool bounce(circle_t *const pCircle, int screen_width, int screen_height);

int main()
{
	const int SCREEN_WIDTH = 1920;
	const int SCREEN_HEIGHT = 1080;
  const Vector2 GRAVITY = {0.0f, 5000.0f};
  unsigned int bounces = 0;

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "My First Simulation!");
  SetTargetFPS(240);

  float dt;
  circle_t circle = {0};
  circle.center = (Vector2) {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};
  circle.radius = 50;
  circle.color = RED;

  while (!WindowShouldClose())
  {
    dt = GetFrameTime();
    apply_acceleration(&circle, GRAVITY, dt);
    if (bounce(&circle, SCREEN_WIDTH, SCREEN_HEIGHT)) bounces++;


    BeginDrawing();
      ClearBackground(BLACK);
      DrawText(TextFormat("Bounces: %d", bounces), 100, 100, 100, WHITE);
      DrawText(TextFormat("Gravity: {x = %.2f, y = %.2f}", GRAVITY.x, GRAVITY.y), 100, 200, 100, WHITE);
      DrawLine(0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2, WHITE);
      DrawCircle(circle.center.x, circle.center.y, circle.radius, circle.color);
    EndDrawing();
  }


  CloseWindow();
	return 0;
}
void apply_acceleration(circle_t *const pCircle, Vector2 a, float dt)
{
  // v = vo + at
  pCircle->velocity = Vector2Add(pCircle->velocity, Vector2Scale(a, dt));

  // x = xo + vt
  pCircle->center = Vector2Add(pCircle->center, Vector2Scale(pCircle->velocity, dt));
}

bool bounce(circle_t *const pCircle, int screen_width, int screen_height)
{
  float floor_level = screen_height - pCircle->radius;  

  if (pCircle->center.y > floor_level)
  {
    float h_difference = pCircle->center.y - floor_level;

    pCircle->center.y = floor_level - h_difference;
    pCircle->velocity.y *= -0.95f; 
    
    if (fabs(pCircle->velocity.y) < 150.0f)
    {
      pCircle->center.y = floor_level;
      pCircle->velocity.y = 0.0f;

      return false;
    }

    return true;
  }

  return false;
}

