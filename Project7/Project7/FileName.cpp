#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

template <typename T>
class Array
{
	int size;
	int sm;
	vector<T> m;

public:
	Array(int s) : size(s), sm(0)
	{
		m.resize(s);
	}

	void setM(int siz, const T& value)
	{
		if (siz >= 0 && siz < size)
		{
			m[siz] = value;
			sm++;
		}
	}

	int getSize() const
	{
		return m.size();
	}

	void setSize(int size)
	{
		if (size > m.size())
		{
			m.resize(m.size() + 5);
		}
	}

	int GetUpperBound() const
	{
		return m.size() - sm;
	}

	bool isEmpty() const
	{
		if (m.empty())
		{
			return 1;
		}
		return 0;
	}

	void removeAll()
	{
		m.clear();
		sm = 0;
	}

	T getAt(int index) const
	{
		return m[index];
	}

	void setAt(int index, int a)
	{
		m[index] = a;
	}

	void add(const T& value)
	{
		if (sm == size)
		{
			m.resize(m.size() + 5);
		}
		m.push_back(value);
		sm++;
	}
};

void main()
{
	Array<int> arr(5);
	int choise;
	int a;
	int b;

	do
	{
		cout << "1 - get size" << endl;
		cout << "2 - set size" << endl;
		cout << "3 - get upper bound" << endl;
		cout << "4 - is enemy" << endl;
		cout << "5 - remove all" << endl;
		cout << "6 - get at" << endl;
		cout << "7 - set at" << endl;
		cout << "8 - add" << endl;
		cout << "9 - set arr" << endl;
		cout << "0 - exit" << endl;

		cin >> choise;

		switch (choise)
		{
		case 1:
		{
			cout << arr.getSize() << endl;
			break;
		}
		case 2:
		{
			cin >> a;
			arr.setSize(a);
			break;
		}
		case 3:
		{
			cout << arr.GetUpperBound() << endl;
			break;
		}
		case 4:
		{
			cout << arr.isEmpty() << endl;
			break;
		}
		case 5:
		{
			arr.removeAll();
			break;
		}
		case 6:
		{
			cin >> a;
			cout << arr.getAt(a) << endl;
			break;
		}
		case 7:
		{
			cin >> a;
			cin >> b;
			arr.setAt(a, b);
			break;
		}
		case 8:
		{
			cin >> a;
			arr.add(a);
			break;
		}
		case 9:
		{
			cin >> a >> b;
			arr.setM(a, b);
			break;
		}
		default:
			break;
		}
	} while (choise != 0);
	
	
}