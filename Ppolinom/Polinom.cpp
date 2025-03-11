#include "Polinom.h"
ostream& operator<<(ostream& out, Polinom& p)
{
    if (p.IsEmpty()) return out;
    p.Reset();
    out << p.GetCurr();
    p.GoNext();
    for (; !p.IsEnd(); p.GoNext()) {
        out << (p.GetCurr().coeff > 1 ? "+" : "") << p.GetCurr();
    }
    return out;
}

istream& operator>>(istream& in, Polinom& p)
{
    double tmpCoeff;
    cin >> tmpCoeff;
    while (tmpCoeff != 0) {
        Monom* tmpMonom = new Monom();
        tmpMonom->coeff = tmpCoeff;
        try {
            cin >> tmpMonom->x >> tmpMonom->y >> tmpMonom->z;
        }
        catch (exception e) { throw e.what(); }
        p.Inslast(*tmpMonom);
        tmpCoeff = 0;
        cin >> tmpCoeff;
    }
    return in;
}

Polinom::Polinom(Monom* p, int sz)
{
    for (size_t i = 0; i < sz; i++)
    {
        Inslast(p[i]);
    }
}

void Polinom::AddMonom(Monom m)
{
    if (IsEmpty())Inslast(m);
    else {
        //добавление первого и последнего звена
        if (pFirst->value < m) {
            InsFirst(m);
            return;
        }
        if (m < pLast->value) {
            Inslast(m);
            return;
        }
        for (Reset(); !IsEnd(); GoNext()) {
            if (GetCurr() < m) {
                Node<Monom>* add = new Node<Monom>(m);
                add->pNext = pCurr;
                pPrev->pNext = add;
                sz++;
                return;
            }
            if (GetCurr() == m) {
                double c = pCurr->value.coeff + m.coeff;
                if (c != 0) pCurr->value.coeff = c;
                else {
                    if (pCurr == pFirst) Pop();
                    else if (pCurr == pLast) {
                        pPrev->pNext = nullptr;
                        pLast = pPrev;
                        sz--;
                        delete pCurr;
                    }
                    else {
                        Node<Monom>* tmp = pCurr;
                        pPrev->pNext = pCurr->pNext;
                        sz--;
                        delete tmp;
                    }
                    return;
                }
            }
        }
    }
}
