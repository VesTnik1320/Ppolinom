#include "TList.h"
#include "Polinom.h"
#include <iostream>
using namespace std;
void main() {

	Monom m[3] = { Monom(1, 2, 1, 1), Monom(-3, 1, 0, 0), Monom(4, 0, 2, 1) };
	Polinom p1(m, 3);
	cout << p1 << endl;
	Monom test1(-4, 0, 2, 1);
	p1.AddMonom(test1);
	cout << p1 << " back del" << endl;

	Monom test2(-1, 2, 1, 1);
	p1.AddMonom(test2);
	cout << p1 << " front del" << endl;

	p1.AddMonom(test1);
	cout << p1 << " back add" << endl;

	p1.AddMonom(test2);
	cout << p1 << " front add" << endl;

	Monom test3(3, 1, 0, 0);
	p1.AddMonom(test3);
	cout << p1 << " mid del" << endl;

	Monom test4(-3, 1, 0, 0);
	p1.AddMonom(test4);
	cout << p1 << " mid add" << endl;
	Polinom::iterator p = p1.Begin();
	for (; p != p1.End(); ++p) {
		cout << *p << "iiter" << endl;
	}
}