#include <vector>

using namespace std;

template<typename T>

class myVector : public vector<T>
{

public:
	myVector() :index(0), vector<T>()
	{

	}

	T getIndexData()
	{
		index++;
		if (index >= vector<T>::size())
		{
			index = 0;
		}

		return vector<T>::at(index);
	}

	int getIndex()
	{
		if (index >= vector<T>::size())
		{
			index = 0;
		}

		return index++;
	}

	void SetData(T& data, int index)
	{
		(*this)[index] = data;
		//vector<T>::operator[index] = data;
	}

private:
	int index;

};
