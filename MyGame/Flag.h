#pragma once

enum Flag_Postion {
	FLAG_WALL = (1<<7),
	FLAG_GOAL = (1<<6)
};

class Flag
{
public:
	Flag(int targetNumer);
	bool check(unsigned char) const;
	void set(unsigned char);
	void reset(unsigned char);
private:
	unsigned char mFlags;
};

