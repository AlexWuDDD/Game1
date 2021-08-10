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
	std::cout << "a:left s:right w:up z:down. command?" << std::endl;
	char input;
	std::cin >> input;
	return input;
}

void GameFramework::updateGame(Object* state, char input, int w, int h)
{
}

void GameFramework::draw(const Object* state, int w, int h)
{
}

void GameFramework::initialize(Object* state, int w, int h, const char* stageData)
{

}

bool GameFramework::checkClear(const Object* state, int w, int h)
{

}