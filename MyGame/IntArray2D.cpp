#include "IntArray2D.h"

IntArray2D::IntArray2D(int size0, int size1) :
	mArray(nullptr),
	mSize0(0),
	mSize1(0)	
{
	mArray = new int[size0 * size1];
}

IntArray2D::~IntArray2D()
{
	delete[]  mArray;
	mArray = nullptr;
}

int& IntArray2D::operator()(int index0, int index1)
{
	return mArray[index1 * mSize0 + index0];
}

const int& IntArray2D::operator()(int index0, int index1) const
{
	return mArray[index1 * mSize0 + index0];
}