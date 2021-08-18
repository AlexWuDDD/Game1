#include "Flag.h"

Flag::Flag(int targetNumer) :
	mFlags(targetNumer)
{}

bool Flag::check(unsigned char f) const
{
	return ((mFlags & f) != 0) ? true : false;
}

void Flag::set(unsigned char f)
{
	mFlags |= f;
}

void Flag::reset(unsigned char f)
{
	//mFlags &= (f ^ 255);
	mFlags &= (~f);
}