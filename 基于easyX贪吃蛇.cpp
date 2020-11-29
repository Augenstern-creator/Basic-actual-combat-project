// 注意事项
// 如果编译不通过，可尝试在在-右键-属性-高级-字符集-使用多字节字符集即可
// 音乐文件可自行替换，将音乐文件放在debug文件夹下或者Release文件夹下即可
// 写在最后
// 需要具备easyX图形库相关知识






#define _CRT_SECURE_NO_DEPRECATE //忽视警告
#define MAX 1000
#include<stdio.h>
#include<graphics.h>   //easyX图形库
#include<conio.h>       //_getch()头文件
#include<time.h>        //随机数头文件
#include<mmsystem.h>    //音乐头文件
#pragma comment(lib,"winmm.lib")  //音乐头文件



/**********************结构体**************/
//坐标属性
typedef struct point
{
	int x, y;
}MYPOINT;
//蛇
struct Snake
{
	MYPOINT xy[MAX];    //坐标
	int position;     //方向
	int num;          //长度
}snake;
//食物
struct
{
	MYPOINT fdxy;      //坐标
	int flag;        //标记
	int grade;		 //分数
}food;
//枚举:方向
enum position{up,down,left,right};


/*********************模块化设计功能***********************/

//初始化蛇
void initSnake()
{
	//前三节：初始化坐标，默认长宽为10
	//蛇尾:在原点
	snake.xy[2].x = 0;
	snake.xy[2].y = 0;
	//蛇身
	snake.xy[1].x = 10;
	snake.xy[1].y = 0;
	//蛇头
	snake.xy[0].x = 20;
	snake.xy[0].y = 0;

	//方向
	snake.position = right;
	snake.num = 3;
}
// 画蛇
void drawSnake()
{
	//绘制填充矩形
	for (int i = 0; i < snake.num; i++)
	{
		setlinecolor(BLACK);
		setfillcolor(RGB(rand() % 255, rand() % 255, rand() % 255));  //设置填充颜色，三原色
		fillrectangle(snake.xy[i].x,snake.xy[i].y,snake.xy[i].x+10,snake.xy[i].y+10);
	}
}
// 蛇动起来
void moveSnake()
{
	//移动的原理：坐标转换
	//蛇身体
	for (int i = snake.num - 1; i > 0; i--)
	{
		snake.xy[i].x = snake.xy[i - 1].x;
		snake.xy[i].y = snake.xy[i - 1].y;
	}
	//蛇头的移动
	switch (snake.position)
	{
	case up:
		snake.xy[0].y -= 10;
		break;
	case down:
		snake.xy[0].y += 10;
		break;
	case left:
		snake.xy[0].x -= 10;
		break;
	case right:
		snake.xy[0].x += 10;
		break;

	}
}
// 按键操作
void keyDown()
{
	char userKey = _getch();
	switch (userKey)
	{
	case 'W':
	case 'w':
	case 72:
		if (snake.position != down)
		{
			snake.position = up;
		}
		break;
	case'S':
	case's':
	case 80:
		if (snake.position != up)
		{
			snake.position = down;
		}
		break;
	case 'A':
	case 'a':
	case 75:
		if (snake.position != right)
		{
			snake.position = left;
		}
		break;
	case 'D':
	case 'd':
	case 77:
		if (snake.position != left)
		{
			snake.position = right;
		}
		break;


	}
}
//初始化食物
void initFood()
{
	food.fdxy.x = rand() % 80 * 10;
	food.fdxy.y = rand() % 60 * 10;
	food.flag = 1;    // 1代表食物存在
	//食物不能出现在蛇的身上
	for (int i = 0; i < snake.num; i++)
	{
		if (food.fdxy.x == snake.xy[i].x && food.fdxy.y == snake.xy[i].y)
		{
			food.fdxy.x = rand() % 80 * 10;
			food.fdxy.y = rand() % 60 * 10;
		}
	}
}
//画食物
void drawFood()
{
	setlinecolor(BLACK);
	setfillcolor(RGB(rand() % 255, rand() % 255, rand() % 255));  //设置填充颜色，三原色
	fillrectangle(food.fdxy.x,food.fdxy.y,food.fdxy.x+10,food.fdxy.y+10);
}
//吃食物
void eatFood()
{
	if (snake.xy[0].x == food.fdxy.x && snake.xy[0].y == food.fdxy.y)
	{
		snake.num++;
		food.flag = 0;
		food.grade += 10;
	}
}
//显示分数
void  showGrade()
{
	//格式化打印
	char grade[20] = "";
	sprintf(grade, "grade:%d", food.grade);
	//设置文字颜色
	settextcolor(LIGHTGREEN);
	settextstyle(25, 0, "楷体");
	outtextxy(600, 50, grade);
}
//蛇死亡
HWND hwnd = NULL;  //定义窗口句柄
int SnakeDie()
{
	//撞墙
	if (snake.xy[0].x > 800 || snake.xy[0].x < 0 || snake.xy[0].y>600 || snake.xy[0].y < 0)
	{
		mciSendString("close 1.mp3", 0, 0, 0);
		MessageBox(hwnd, "同学请您别撞墙好嘛", "Game over!", MB_OK);
		return 1;
	}
	//撞自己
	for (int i = 1; i < snake.num; i++)
	{
		if (snake.xy[0].x == snake.xy[i].x && snake.xy[0].y == snake.xy[i].y)
		{
			mciSendString("close 1.mp3", 0, 0, 0);
			MessageBox(hwnd, "咋了急了？还吃自己呢？", "Game over!", MB_OK);
			return 1;
		}
	}
	return 0;
}














int main()
{
	srand((unsigned int)time(NULL));
	//创建图形窗口:初始化图形环境
	initgraph(800,600);
	setbkcolor(RGB(110, 120, 119));  //设置背景颜色
	mciSendString("open 1.mp3", 0, 0, 0);
	mciSendString("play 1.mp3", 0, 0, 0);
	

	// 画矩形
	//fillrectangle(300, 300, 350, 350);
	initSnake();
	

	//蛇移动
	while (1)
	{
		cleardevice();                  // 清屏，才能使背景颜色显示
		moveSnake();
		drawSnake();
		//只有当键盘按下时候，才调用keyDown函数
		if (_kbhit())
		{
			keyDown();
		}
		if (food.flag == 0)
		{
			initFood();
		}
		if (SnakeDie())
		{
			break;
		}
		drawFood();
		eatFood();
		showGrade();

		Sleep(100);
	}





	_getch(); // 防止闪屏：等待用户输入一个字符
	closegraph();  //关闭创建的窗口
	return 0;
}
