#pragma once
#include "Monom.h"
#include "TList.h"
#include <string>
class Polinom : public TList<Monom> {
public:
	Polinom() : TList<Monom>() {}
	Polinom(const Polinom& p) : TList<Monom>(p) {}
	Polinom(Monom* p, int sz);

	void AddMonom(Monom m);
	friend ostream& operator <<(ostream& out, Polinom& p);
	friend istream& operator >>(istream& in, Polinom& p);
};
