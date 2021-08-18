#ifndef INT_ARRAY_2D
#define INT_ARRAY_2D
class IntArray2D
{
public:
	IntArray2D(int size0, int size1);
	~IntArray2D();
	int& operator()(int index0, int index1);
	const int& operator()(int index0, int index1) const;
private:
	int* mArray;
	const int mSize0;
	const int mSize1;
};


#endif


