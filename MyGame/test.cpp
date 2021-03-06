#include "test.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include "Flag.h"

void testKeyboardAndDisplay()
{
	/*键盘和画面输出*/
	char c;
	std::cin >> c;
	std::cout << "Input Character is: " << c << std::endl;
}

void testReadFile(const char* filePath)
{
	std::ifstream inputFile(filePath, std::ifstream::binary);
	if (!inputFile) {
		std::cout << "can not open file: " << filePath <<std::endl;
	}
	inputFile.seekg(0, std::ifstream::end); //移动到末尾
	//位置 = 文件大小
	int fileSize = static_cast<int>(inputFile.tellg());
	inputFile.seekg(0, std::ifstream::beg);//返回到起始位置
	char* fileData = new(std::nothrow) char[fileSize];
	inputFile.read(fileData, fileSize);

	std::cout.write(fileData, fileSize);

	delete[] fileData;
	inputFile.close();
} 

void testWriteFile(const char* filePath)
{
	std::ofstream outputFile("test.txt", std::ofstream::out);
	outputFile << "alex is cool";
	outputFile.close();
}

void testFlag()
{
	Flag flag1(255);
	std::cout << std::boolalpha <<flag1.check(Flag_Postion::FLAG_GOAL) << std::endl;
	Flag flag2(63);
	std::cout << std::boolalpha <<flag2.check(Flag_Postion::FLAG_GOAL) << std::endl;
	Flag flag3(65);
	std::cout << std::boolalpha << flag3.check(Flag_Postion::FLAG_GOAL) << std::endl;
}