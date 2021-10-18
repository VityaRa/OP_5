#include <algorithm>
#include <thread>
#include <random>
#include <iterator>
#include <vector>
#include <ctime>
#include <iostream>

using namespace std;

//Функция заполнения вектора числами
vector <int> zapoln(size_t size)
{
	vector <int> v(size);
	random_device ran;
	generate(v.begin(), v.end(), [&] {return ran() % 1000 - 499; });
	return v;
}

//Функция, удаляющая элементы, значение которых < 0
vector <int> zadach(vector <int> vec)
{
	bool prow = true;
	while (prow)
	{
		auto it = find_if(execution::par_unseq, vec.begin(), vec.end(), [](int elem) {return elem < 0; });
		if (it == vec.end())
		{
			prow = false;
			continue;
		}
		else
		{
			vec.erase(it);
		}
	}
	return vec;
}



int main()
{
	srand(time(nullptr));
	cout << "Concurrent threads are supported " << thread::hardware_concurrency() << endl;
	vector <int> vec(zapoln(100)); 

	cout << "VEC BEFORE" << endl;
	copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));

	cout << endl << endl << "VEC AFTER" << endl;
	float time_start = clock();
	vec = zadach(vec);
	float time_end = clock();
	copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
	cout << "time" << (time_end - time_start) / CLOCKS_PER_SEC;
	return 0;
}