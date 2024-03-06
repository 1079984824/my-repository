#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>
#include <string.h>

#define SNAKE_NUM 500
#define Height 480
#define Length 640

int die = 0;
int score = 0;
char str[500];
struct Snake
{
	int size;
	int big;
	int speed;
	int direction;
	POINT coord[SNAKE_NUM];
}snake;
struct Food
{
	int x;
	int y;
	int r;
	bool flag;
}food;
enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};
void WelcomeGame()
{
	initgraph(Length, Height);
	setbkcolor(RGB(0, 0, 0));
	cleardevice();
	settextstyle(35, 0, "楷体");
	outtextxy(150, 150, "欢迎来到贪吃蛇游戏!");
	settextstyle(25, 0, "微软雅黑");
	outtextxy(200, 400, "@SCU2023141410163        ...请按任意键以继续");
	system("pause");
	cleardevice();
	settextstyle(20, 0, "楷体");
	outtextxy(100, 150, "用 W , S , A , D或 ↑ ，↓ ，← ，→来控制移动");
	settextstyle(25, 0, "微软雅黑");
	outtextxy(200, 400, "@SCU2023141410163        ...请按任意键以继续");
	system("pause");
}
void GameInit()
{
	initgraph(Length, Height);
	snake.size = 3;
	snake.big = 5;
	snake.speed = 10;
	snake.direction = RIGHT;
	for (int i = 0;i < snake.size;i++) {
		snake.coord[snake.size - 1 - i].x = 10 * i + 20;
		snake.coord[i].y = 10;
	}

}
void GameDraw()
{
	BeginBatchDraw();
	setbkcolor(RGB(23, 115, 119));
	cleardevice();
	settextstyle(15, 0, "楷体");
	setcolor(BLACK);
	outtextxy(470, 20, "当前分数为：");
	sprintf_s(str, "%d", score);
	outtextxy(570, 20, str);
	for (int i = 0;i < snake.size;i++) {
		setfillcolor(WHITE);
		solidcircle(snake.coord[i].x, snake.coord[i].y, snake.big);
	}
	if (food.flag) {
		setfillcolor(RED);
		solidcircle(food.x, food.y, food.r);
	}
	EndBatchDraw();
}

void Move()
{
	for (int i = snake.size - 1;i > 0;i--) {
		snake.coord[i].x = snake.coord[i - 1].x;
		snake.coord[i].y = snake.coord[i - 1].y;
	}
	switch (snake.direction)
	{
	case UP:snake.coord[0].y -= snake.speed;
		break;
	case DOWN:snake.coord[0].y += snake.speed;
		break;
	case LEFT:snake.coord[0].x -= snake.speed;
		break;
	case RIGHT:snake.coord[0].x += snake.speed;
		break;
	}
	switch (snake.direction)
	{
	case RIGHT:
		if (snake.coord[0].x >= Length - snake.big) {
			snake.coord[0].x = snake.big - 1;
		}
		break;
	case LEFT:
		if (snake.coord[0].x <= 0) {
			snake.coord[0].x = Length;
		}
		break;
	case DOWN:
		if (snake.coord[0].y >= Height - snake.big) {
			snake.coord[0].y = snake.big - 1;
		}
		break;
	case UP:
		if (snake.coord[0].y <= 0) {
			snake.coord[0].y = Height;
		}
		break;
	}
}
void RandFood()
{
	srand(GetTickCount());
	food.r = 5;
	if (rand() % Length <= food.r + 20) {
		food.x = rand() % Length + food.r + 20;
	}
	else if (rand() % Length >= Length - food.r - 20) {
		food.x = rand() % Length - food.r - 20;
	}
	else {
		food.x = rand() % Length;
	}
	if (rand() % Height <= food.r + 20) {
		food.y = rand() % Height + food.r + 20;
	}
	else if (rand() % Height >= Height - food.r - 20) {
		food.y = rand() % Height - food.r - 20;
	}
	else {
		food.y = rand() % Height;
	}
	food.flag = true;
}
void EatFood()
{
	if (sqrt(pow(snake.coord[0].x - food.x, 2) + pow(snake.coord[0].y - food.y, 2)) < food.r + snake.big) {
		food.flag = false;
		snake.size++;
		score += 10;
	}
}
void Die()
{
	for (int i = 1;i < snake.size;i++) {
		if (sqrt(pow(snake.coord[0].x - snake.coord[i].x, 2) + pow(snake.coord[0].y - snake.coord[i].y, 2)) < 2 * snake.big) {
			Sleep(1000);
			die = 1;
		}
	}
}
void KeyControl()
{
	if (_kbhit()) {
		switch (_getch()) {
		case 'w':
		case 'W':
		case 72:
			if (snake.direction != DOWN) {
				snake.direction = UP;
				break;
			}
		case 's':
		case 'S':
		case 80:
			if (snake.direction != UP) {
				snake.direction = DOWN;
				break;
			}
		case 'a':
		case 'A':
		case 75:
			if (snake.direction != RIGHT) {
				snake.direction = LEFT;
				break;
			}
		case 'd':
		case 'D':
		case 77:
			if (snake.direction != LEFT) {
				snake.direction = RIGHT;
				break;
			}
		case ' ':
			system("pause");
		}
	}
}
void GameOver()
{
	initgraph(Length, Height);
	setbkcolor(RGB(0, 0, 0));
	cleardevice();
	settextstyle(50, 0,"微软雅黑");
	outtextxy(200, 150, "GameOver!");
	settextstyle(25, 0, "微软雅黑");
	outtextxy(200, 400, "@SCU2023141410163");
	outtextxy(200, 250, "您的总分为：");
	sprintf_s(str, "%d", score);
	outtextxy(325, 250, str);
	system("pause");
}
int main()
{
	WelcomeGame();
	GameInit();
	RandFood();
	while (1) {
		Move();
		Die();
		if (die) break;
		GameDraw();
		if (!food.flag) {
			RandFood();
		}
		EatFood();
		KeyControl();
		Sleep(100);
	}
	GameOver();

	return 0;
}