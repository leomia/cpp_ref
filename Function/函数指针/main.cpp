#include <chrono>
void test_bywhile(int nTimes)
{
	int tmpNum = 0;

	while (tmpNum < nTimes)
	{
		tmpNum += 1;
	}
	return;
}

void test_byfor(int nTimes)
{
	int tmpNum = 0;
	for (int i = 0; i < nTimes; i++)
	{
		tmpNum += 1;
	}
	return;
}

typedef void(*lpfunc)(int);							//define a pointer for function
lpfunc funArr[2] = { test_bywhile, test_byfor };	//specify function list

double costtime(void(*lpfun)(int), int nTimes) {
	auto start = std::chrono::high_resolution_clock::now();

	lpfun(nTimes);

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = end - start;
	return duration.count();
}

double costtime1(lpfunc fun, int nTimes) {
	auto start = std::chrono::high_resolution_clock::now();

	fun(nTimes);

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = end - start;
	return duration.count();
}

int main()
{
	double spend1 = costtime(test_bywhile, 10000000);
	double spend2 = costtime(test_byfor, 10000000);
	double spend3 = costtime1(funArr[0], 10000000);
	double spend4 = costtime1(funArr[1], 10000000);
	printf("Thread takes: \n%.4fs\n%.4fs\n%.4fs\
		\n%.4fs\n", spend1, spend2, spend3,spend4);
	return 0;
}


