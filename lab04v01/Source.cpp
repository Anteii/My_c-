#include "set.h"
#include <set>
#include <ctime>
using namespace std;
	
int main() {
	Set<int> a;
	Set<int> b;
	set<int> sta;
	const int size = 10;
	for (int i = 0; i < size; ++i) {
		int t = rand();
		a.add(t);
		b.add(t);
	}
	auto s = a.begin();
	auto e = a.end();
	while (s != e) {
		cout << *(s++) << " ";
	}
	cout << endl;
	cout << a << endl;
	cout << a.min() << " " << a.max() << endl;
	return 0;
}