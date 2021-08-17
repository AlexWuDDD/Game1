#include "gameFramework.h"
#include "gameStage.h"

#include <iostream>

void GameFramework::runGame()
{
	//创建状态数组
	Object* state = new Object[gameStageWidth * gameStageHeight];

	//初始化场景
	initialize(state, gameStageWidth, gameStageHeight, gameStageData);

	//主循环
	while (true) {
		//首先绘制
		draw(state, gameStageWidth, gameStageHeight);
		//通关检测
		if (checkClear(state, gameStageWidth, gameStageHeight)) {
			break;
		}
		char input = getInput();
		updateGame(state, input, gameStageWidth, gameStageHeight);
	}

	//胜利时的提示信息
	std::cout << "Congratulation's! You win." << std::endl;
	//通关
	delete[] state;
	state = nullptr;

	return;
}

char GameFramework::getInput()
{
	std::cout << "a:left d:right w:up s:down. command?" << std::endl;
	char input;
	std::cin >> input;
	return input;
}

void GameFramework::updateGame(Object* state, char input, int width, int height)
{
	//转换为移动量
	int dx = 0;
	int dy = 0;
	switch (input){
	case 'a': dx = -1; break; //左
	case 'd': dx =  1; break; //右
	case 'w': dy = -1; break; //上
	case 's': dy =  1; break; //下
	default:
		break;
	}

	//查找玩家的坐标
	int i = -1; //无具体意义，只是单纯的初始化
	for (i = 0; i < width * height; ++i) {
		if (state[i] == OBJ_MAN || state[i] == OBJ_MAN_ON_GOAL) {
			break;
		}
	}
	int x = i % width; //x的值为除以宽度后的余数
	int y = i / width; //y的值为除以宽度后的商

	//移动后的坐标
	int tx = x + dx;
	int ty = y + dy;
	//检查坐标的最大值和最小值，超出范围则不允许
	if (tx < 0 || ty < 0 || tx >= width || ty >= height) {
		return;
	}

	int p = y * width + x; //玩家位置
	int tp = ty * width + tx; //目标位置

	//A. 要移动的位置是空白或者目的地，玩家移动
	if (state[tp] == OBJ_SPACE || state[tp] == OBJ_GOAL) {
		std::cout << "case A" << std::endl;
		//如果是目的地，则将该处设置为“目的地玩家”
		state[tp] = (state[tp] == OBJ_GOAL ? OBJ_MAN_ON_GOAL : OBJ_MAN);
		//如果已经在目的地了，则将玩家所在位置设置为目的地
		state[p] = (state[p] == OBJ_MAN_ON_GOAL ? OBJ_GOAL : OBJ_SPACE);
	}
	//B.要移动的位置有箱子。如果沿着该方向下一个网格是空白或目的地
	else if (state[tp] == OBJ_BLOCK || state[tp] == OBJ_BLOCK_ON_GOAL) {
		std::cout << "case B" << std::endl;
		//检验沿该方向的第二个网格的位置是否在允许范围内
		int tx2 = tx + dx;
		int ty2 = ty + dy;
		if (tx2 < 0 || ty2 < 0 || tx2 >= width || ty2 >= height) {
			return; //无法移动
		}
		int tp2 = ty2 * width + tx2; //沿该方向的第二个网格的位置
		if (state[tp2] == OBJ_SPACE || state[tp2] == OBJ_GOAL) {
			//逐个替换
			state[tp2] = (state[tp2] == OBJ_GOAL) ? OBJ_BLOCK_ON_GOAL : OBJ_BLOCK;
			state[tp] = (state[tp] == OBJ_BLOCK_ON_GOAL) ? OBJ_MAN_ON_GOAL : OBJ_MAN;
			state[p] = (state[p] == OBJ_MAN_ON_GOAL) ? OBJ_GOAL : OBJ_SPACE;
		}
	}
	else{
		std::cout << "unexpected case" << std::endl;
	}
}

void GameFramework::draw(const Object* state, int width, int height)
{
	//Object枚举类型的顺序
	const char font[] = {' ', '#', '.', 'o', 'O', 'p', 'P'};
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			Object o = state[y*width + x];
			std::cout << font[o];
		}
		std::cout << std::endl;
	}
}

void GameFramework::initialize(Object* state, int width, int height, const char* stageData)
{
	const char* ptr = stageData;
	int x = 0;
	int y = 0;
	while (*ptr != '\0') {
		Object t;
		switch (*ptr){
			case '#': t = OBJ_WALL; break;
			case ' ': t = OBJ_SPACE; break;
			case 'o': t = OBJ_BLOCK; break;
			case 'O': t = OBJ_BLOCK_ON_GOAL; break;
			case '.': t = OBJ_GOAL; break;
			case 'p': t = OBJ_MAN; break;
			case 'P': t = OBJ_MAN_ON_GOAL; break;
			case '\n':
				x = 0; //x返回到最左边
				++y; //y进到下一段
				t = OBJ_UNKNOWN; //没有数据
				break;
			default:
				t = OBJ_UNKNOWN;
				break;
		}
		if (t != OBJ_UNKNOWN){
			state[y*width + x] = t;
			++x;
		}
		++ptr;
	}
}

bool GameFramework::checkClear(const Object* state, int width, int height)
{
	for (int i = 0; i < width * height; ++i) {
		if (state[i] == OBJ_BLOCK) {
			return false;
		}
	}
	return true;
}
