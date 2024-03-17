// --------------steps to create a pong game------------------
//1. Create a blank screen & Game loop   
//2. Draw the paddles and the ball
//3. Move the ball around
//4. Check for a collision with all edges
//5. Move the player's paddle
//6. Move the CPU paddle with Artificial Intelligence
//7. Check for a collision with the paddles
//8. Add scoring


#include <iostream>
#include <raylib.h>
using namespace std;

Color Green = Color{38,185,154,255};
Color Dark_Green = Color{ 20,160,133,255 };
Color Light_Green = Color{ 129,204,184,255 };
Color Yellow = Color{ 243,213,91,255 };

int player_score = 0;
int cpu_score = 0;


class Ball{
public:
	float x, y;
	int speed_x, speed_y;
	int radius;


	void Draw() {
		DrawCircle(x, y, radius, Yellow);
	}

	void Update()
	{
		x += speed_x;
		y += speed_y;

		if (y + radius >= GetScreenHeight() || y - radius <= 0) speed_y *= -1;
		if (x + radius >= GetScreenWidth() || x - radius <= 0) speed_x *= -1;

		if (x - radius <= 0) // player_wins
		{
			player_score++;
			ResetBall();
		}
		if (x + radius >= GetScreenWidth()) // cpu_wins
		{
			cpu_score++;
			ResetBall();
		}
	}

	void ResetBall()
	{
		x = GetScreenWidth() / 2;
		y = GetScreenHeight() / 2;

		int speed_choices[2] = { -1,1 };
		speed_x *= speed_choices[GetRandomValue(0, 1)];
		speed_y *= speed_choices[GetRandomValue(0, 1)];
	}
};

class Paddle {

protected:
	void LimitMovement() {
		if (y <= 0) {
			y = 0;
		}

		if (y + height >= GetScreenHeight()) {
			y = GetScreenHeight() - height;
		}
	}
public:
	float x, y;
	float width, height;
	int speed;

	void Draw() {
		DrawRectangle(x, y, width, height, WHITE);
	}

	void Update(){
		if (IsKeyDown(KEY_UP)) {
			y = y - speed;
		}

		if (IsKeyDown(KEY_DOWN)) {
			y = y + speed;
		}

		LimitMovement();
	}
};

class CpuPaddle:public Paddle {
public:
	void Update(int ball_y) {
		if (y + height / 2 > ball_y) {
			y = y - speed;
		}
		if (y + height / 2 <= ball_y) {
			y += speed;
		}

		LimitMovement();
	}
};

Ball ball;
Paddle player;
CpuPaddle cpu;


int main()
{
	cout << "Hello World!\n";

	// 1--------------------------------------- blank screen for our game

	const int screen_width = 800;
	const int screen_height = 600; //these variables are made constant using const keyword bcz we won't change their value.
	InitWindow(screen_width, screen_height, "My Pong Game"); // this function initializes the window . it takes 3 arguments height and width of screen along with a title of window. 

	SetTargetFPS(60); // to define how fast the game should run . the integer used as argument is the no. of frames per second.


	ball.radius = 20;
	ball.x = screen_width / 2;
	ball.y = screen_height / 2;
	ball.speed_x = 7;
	ball.speed_y = 7;

	player.width = 25;
	player.height = 120;
	player.x = screen_width - player.width - 10;
	player.y = screen_height / 2 - player.height / 2;
	player.speed = 15;
		

	cpu.width = 25;
	cpu.height = 120;
	cpu.x = 10;
	cpu.y = screen_height / 2 - cpu.height / 2;
	cpu.speed = 6;





	//2----------------------------------------- Game Loop


	while (WindowShouldClose() == false) { // WindowShouldClose function end the loop if escape key on the keyboard is pressed or close icon the window is pressed . 

		BeginDrawing();  // this function creates a blank canvas . so that we can  draw our game objects.


		//Updating
		ball.Update();
		player.Update();
		cpu.Update(ball.y);

		//Checking for an collision
		if (CheckCollisionCircleRec(Vector2{ ball.x,ball.y }, ball.radius, Rectangle{ player.x,player.y,player.width,player.height })) {
			ball.speed_x *= -1;
		};

		if (CheckCollisionCircleRec(Vector2{ ball.x,ball.y }, ball.radius, Rectangle{ cpu.x,cpu.y,cpu.width,cpu.height })) {
			ball.speed_x *= -1;
		};



	    // Drawing
		ClearBackground(Dark_Green); 	// erasing the previous traces of the ball
		DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, Green);
		DrawCircle(screen_width / 2, screen_height / 2, 150, Light_Green);

		ball.Draw(); // Drawing a ball 
		cpu.Draw();// Drawing the rectangular paddles for computer
		player.Draw();// Drawing the rectangular paddles for user
		DrawLine(screen_width/2, 0, screen_width/2, screen_height, WHITE); // Drawing the line that separates the two sections.
		DrawText(TextFormat("%i", cpu_score), screen_width / 4 - 20, 20, 80, WHITE);
		DrawText(TextFormat("%i", player_score), 3* screen_width / 4 - 20, 20, 80, WHITE);

		EndDrawing();// it ends the canvas drawing.

	}


	  





	CloseWindow(); //every time we create a window it needs to be closed or destroyed at some point of time.hence we use this function.

	return 0;
}

