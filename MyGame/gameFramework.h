#ifndef GAMEFRAMEWORK_H
#define GAMEFRAMEWORK_H

#include "object.h"
#include "gameStage.h"

class GameFramework
{
public:
	static void runGame();
private:
	/*读取场景数据字符串，并将场景转换位Object数组*/
	static void initialize(Object* state, int w, int h, const char* stageData);

	static char getInput();
	static void updateGame(Object* state, char input, int w, int h);
	static void draw(const Object* state, int w, int h);
	/*检测游戏是否通关*/
	static bool checkClear(const Object* state, int w, int h);

};


#endif

