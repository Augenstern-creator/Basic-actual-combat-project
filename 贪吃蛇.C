#define _CRT_SECURE_NO_WARNINGS



#include<stdio.h>
#include<stdlib.h>
#include<string.h>   //strncpy 复制字符串头文件
#include<time.h>     //置随机数种子 time 头文件
#include"head.h"     //自己写的头文件
#include<conio.h>    //_getch头文件
#include"windows.h"  //音乐头文件
#include<mmsyscom.h> //音乐头文件
#pragma comment(lib,"winmm.lib") //添加动态链接库



//
//
//播放音乐
void MyPlayMusic();
//显示封面
void showmenu();
//按空格键
void TestSpace();
//停止播放
void StopMusic();
//画背景
void ShowBackground();
//为蛇产生一个随机的位置
void SetSnakeRandPos();
//画蛇
void DrawSnake();
//蛇动
void SnakeMove();
//销毁蛇
void DropSnake();
//蛇随方向动起来
void ChangeSnake();
//蛇死亡判断
BOOL IsSnakeDie();
//产生新的食物
void ProduceFood();
//蛇变长
void SnakeGrowUp();
//计分
void Score();




// 封面
void showmenu()
{
	printf("\t\t\t《欢迎进入贪吃蛇世界》\n");
	printf("\t\t\t《按空格开始游戏》\n");
	printf("\t\t\t《 w a s d 控制蛇的方向 》\n");
}
// 播放音乐
void MyPlayMusic() {
	PlaySound(L"1.wav",NULL,SND_FILENAME | SND_ASYNC);
}

// 监测空格函数
void TestSpace()
{
	char chInput;   //接收空格键
	// 3.按空格键，进入游戏
	while (true)
	{
		chInput = _getch();
		if (' ' == chInput)
		{
			break;
		}
	}
	// 4.进入游戏，音乐播放停止
	PlaySound(NULL, 0, 0);
	// 5.清理控制台
	system("cls");

}
// 音乐停止播放
void StopMusic()
{
	PlaySound(NULL, 0, 0);
}
// 画背景
void ShowBackground()
{
	int i = 0;
	for (i = 0; i < 20; i++)
	{
		printf(g_strGameBack[i]);
	}
	
}
// 画蛇
void DrawSnake()
{
	int i = 0;
	for (i = 0; g_arrSnake[i][0] != 0; i++)
	{
		strncpy(&g_strGameBack[g_arrSnake[i][0]][g_arrSnake[i][1]], "■", 2);
	}
}
// 销毁旧蛇
void DropSnake()
{
	int i = 0;
	for (i = 0; g_arrSnake[i][0] != 0; i++)
	{
		strncpy(&g_strGameBack[g_arrSnake[i][0]][g_arrSnake[i][1]], "  ", 2);
	}
}


// 为蛇产生随机位置
void SetSnakeRandPos()
{
	int nX = -1;
	int nY = -1;
	//产生随机数
	srand((unsigned int)time(NULL)); // 种种子
	// 横向 索引 0-22，蛇有3节，去掉边界，只能索引 1 - 19，默认蛇头朝左
	nX = rand() % 19 + 1;
	nY = rand() % 18 + 1;

	// 初始化蛇的三个节点
	g_arrSnake[0][0] = nY;     //行
	g_arrSnake[0][1] = nX * 2; //列
	g_arrSnake[0][2] = to_west;//方向

	g_arrSnake[1][0] = nY;     //行
	g_arrSnake[1][1] = nX * 2 + 2; //列
	g_arrSnake[1][2] = to_west;//方向

	g_arrSnake[2][0] = nY;     //行
	g_arrSnake[2][1] = nX * 2 + 4; //列
	g_arrSnake[2][2] = to_west;//方向
	//把蛇画到背景上
	DrawSnake();

}
// 蛇动
void SnakeMove()
{
	int i = DEF_SNAKE_LONG - 1;
	//销毁旧蛇
	DropSnake();

	for (i; i >= 1; i--)
	{
		//过滤掉非法蛇身
		if (0 == g_arrSnake[i][0])
		{
			continue;
		}
		// 把前一个节点，赋值给当前节点
		g_arrSnake[i][0] = g_arrSnake[i-1][0];
		g_arrSnake[i][1] = g_arrSnake[i - 1][1];
		g_arrSnake[i][2] = g_arrSnake[i - 1][2];
	}
	
	//处理蛇头
	g_arrSnake[0][2] = g_nSnakeDir;
	if (to_west == g_arrSnake[0][2] || to_east == g_arrSnake[0][2])
	{
		g_arrSnake[0][1] += g_arrSnake[0][2];
	}
	else
	{
		g_arrSnake[0][0] += g_arrSnake[0][2];
	}
	// 画蛇
	DrawSnake();

}
//蛇随方向动起来
void ChangeSnake()
{
	// 异步检测
	
	// GetAsyncKeyState(VK_DOWN); 监测方向键盘 返回 short 类型
	if (GetAsyncKeyState('W'))  //只检测大写
	{
		g_nSnakeDir = to_north;
	}
	else if (GetAsyncKeyState('S'))
	{
		g_nSnakeDir = to_south;
	}
	else if (GetAsyncKeyState('A'))
	{
		g_nSnakeDir = to_west;
	}
	else if (GetAsyncKeyState('D'))
	{
		g_nSnakeDir = to_east;
	}


}
// 蛇死亡判断
BOOL IsSnakeDie()
{
	//蛇东西走，Y不变，X变化,蛇头的下一个是方块，则游戏结束
	if (to_west == g_arrSnake[0][2] || to_east == g_arrSnake[0][2])
	{
		if (0 == strncmp(&g_strGameBack[g_arrSnake[0][0]][g_arrSnake[0][1] + g_arrSnake[0][2]], "■", 2))
		{
			return false;
		}
	}
	else
	{
		if (0 == strncmp(&g_strGameBack[g_arrSnake[0][0] + g_arrSnake[0][2]][g_arrSnake[0][1]], "■", 2))
		{
			return false;
		}
	}

	return true;
}
//产生新的食物
void ProduceFood()
{
	int i = 0;
	//判断是否产生新的食物
	if (false == g_bIsProFood)//否
	{
		return ;
	}

	srand((unsigned int)time(NULL));

	while (1)
	{
		bool bFlag = true;

		g_nLine = rand()%18 + 1;
		g_nLie = rand()%20 + 1;

		for (i = 0; g_arrSnake[i][0] != 0; i++)
		{
			if (g_nLine == g_arrSnake[i][0] && g_nLie == g_arrSnake[i][1])
			{
				 bFlag = false;
				 break;
			}
		}

		if (true == bFlag)
		{
			break;
		}
	}
	
	//坐标画食物
	strncpy(&g_strGameBack[g_nLine][g_nLie*2],  "★", 2);

	g_bIsProFood = false;
}
//蛇变长
void SnakeGrowUp()
{
	//蛇头坐标跟 食物坐标相等
	if (g_nLine == g_arrSnake[0][0] && g_nLie*2 == g_arrSnake[0][1])
	{
		//蛇长大
		if (to_east == g_arrSnake[g_nSnakelen][2])
		{	
			g_arrSnake[g_nSnakelen+1][0] = g_arrSnake[g_nSnakelen][0];
			g_arrSnake[g_nSnakelen+1][1] = g_arrSnake[g_nSnakelen][1] - 2;
			g_arrSnake[g_nSnakelen+1][2] = g_arrSnake[g_nSnakelen][2];
		}
		else if (to_west == g_arrSnake[g_nSnakelen][2])
		{
			g_arrSnake[g_nSnakelen+1][0] = g_arrSnake[g_nSnakelen][0];
			g_arrSnake[g_nSnakelen+1][1] = g_arrSnake[g_nSnakelen][1] + 2;
			g_arrSnake[g_nSnakelen+1][2] = g_arrSnake[g_nSnakelen][2];
		}
		else if (to_north == g_arrSnake[g_nSnakelen][2])
		{
			g_arrSnake[g_nSnakelen+1][0] = g_arrSnake[g_nSnakelen][0] + 1;
			g_arrSnake[g_nSnakelen+1][1] = g_arrSnake[g_nSnakelen][1];
			g_arrSnake[g_nSnakelen+1][2] = g_arrSnake[g_nSnakelen][2];
		}
		else if (to_south == g_arrSnake[g_nSnakelen][2])
		{
			g_arrSnake[g_nSnakelen+1][0] = g_arrSnake[g_nSnakelen][0] - 1;
			g_arrSnake[g_nSnakelen+1][1] = g_arrSnake[g_nSnakelen][1];
			g_arrSnake[g_nSnakelen+1][2] = g_arrSnake[g_nSnakelen][2];
		}

		g_nSnakelen++;
		g_bIsProFood = true;
		g_nScore++;
	}
}
//计分  
void Score()
{
	COORD rd;
	rd.X = 55;
	rd.Y = 8;
	//设置光标位置
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);
	//打印
	printf ("分数"); //g_nScore

	rd.X = 56;
	rd.Y = 9;
	//设置光标位置
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);
	//打印
	printf ("%d", g_nScore*10);
}







int main(void)
{
	
	// 1.显示封面
	showmenu();
	// 2.播放音乐
	MyPlayMusic();
	// 3.按空格键盘
	TestSpace();
	// 4.停止音乐，进入游戏
	StopMusic();
	// 5.进入游戏，重复画背景
	SetSnakeRandPos();   //设置蛇位置，在游戏开始之前只能设置一次
	ShowBackground();
	// 游戏界面
	while (true)
	{
		system("cls");
		//产生食物
		ProduceFood();
		//蛇变长
		SnakeGrowUp();
		//改变方向监测
		ChangeSnake();
		// 先判断，防止蛇在游戏开始开始动碰到墙壁上
		if (false == IsSnakeDie())
		{
			printf("Game Over!");
			break;
		}
		// 蛇动
		SnakeMove();
		// 显示背景
		ShowBackground();
		// 显示分数
		Score();
		Sleep(500);
	}



	system("pause");
	return 0;
}
