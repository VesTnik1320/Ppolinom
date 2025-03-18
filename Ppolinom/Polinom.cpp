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
Polinom Polinom::operator+(Polinom& p)
{
    Polinom res(*this);
    for (res.Reset(), p.Reset(); (!res.IsEnd()) && (!p.IsEnd());) {
        Monom rcur = res.GetCurr(), pcur = p.GetCurr();
        if (rcur == pcur) {
            double c = rcur.coeff + pcur.coeff;
            if (c == 0) {
                res.DelCurr();
                p.GoNext();
            }
            else {
                res.GetCurr().coeff = c;
                res.GoNext();
                p.GoNext();
            }
        }
        else if (rcur < pcur) {
            res.InsCurr(pcur);
            p.GoNext();
        }
        else if (pcur < rcur) {
            res.GoNext();
        }
    }
    if (!p.IsEnd()) {
        for (; !p.IsEnd(); p.GoNext()) {
            res.Inslast(p.GetCurr());
        }
    }
    return res;
}
Polinom Polinom::operator-(Polinom& p)
{
    Polinom res, negative = p * (-1);
    res = *this + negative;
    return res;
}
Polinom Polinom::operator*(double coef)
{
    Polinom res(*this);
    if (coef == 0.0) res.Clear();
    else {
        for (res.Reset(); !res.IsEnd(); res.GoNext()) {
            res.GetCurr().coeff *= coef;
        }
    }
    return res;
}

Polinom Polinom::operator*(Polinom p)
{
    Polinom res, multer(*this);
    if (p.sz == 0) return res;
    for (p.Reset(); !(p.IsEnd()); (p.GoNext())) {
        Polinom tmp = (*this * p.GetCurr());
        res = (res + tmp);
    }
    return res;
}

Polinom Polinom::operator*(Monom m)
{
    Polinom res;
    if (m.coeff == 0.0) return res;
    for (Reset(); !IsEnd(); GoNext()) {
        Monom tmp;
        tmp.coeff = GetCurr().coeff * m.coeff;
        tmp.x = m.x + GetCurr().x;
        tmp.y = m.y + GetCurr().y;
        tmp.z = m.z + GetCurr().z;
        res.AddMonom(tmp);
    }
    return res;
}
void Polinom::FromString(const std::string& str) {
    std::istringstream iss(str);  // Создаем поток из строки
    double tmpCoeff;
    iss >> tmpCoeff;  // Читаем первый коэффициент

    while (tmpCoeff != 0) {
        Monom tmpMonom;
        tmpMonom.coeff = tmpCoeff;

        try {
            // Читаем степени x, y, z
            iss >> tmpMonom.x >> tmpMonom.y >> tmpMonom.z;
        }
        catch (const std::exception& e) {
            throw std::runtime_error("Ошибка при чтении степеней: " + std::string(e.what()));
        }

        // Добавляем моном в полином
        this->AddMonom(tmpMonom);  // Используем this для доступа к нестатическому методу

        // Читаем следующий коэффициент
        tmpCoeff = 0;
        iss >> tmpCoeff;
    }
}

std::string Polinom::ToString() {
    std::ostringstream oss;  // Поток для формирования строки
    bool firstMonom = true;  // Флаг для первого монома

    // Используем константные итераторы для обхода полинома
    for (Polinom::iterator it = Begin(); it != End(); ++it) {
        const Monom& monom = *it;  // Получаем текущий моном

        if (monom.coeff == 0) {
            continue;  // Пропускаем мономы с нулевым коэффициентом
        }

        // Добавляем знак перед мономом (кроме первого)
        if (!firstMonom) {
            oss << (monom.coeff > 0 ? " + " : " - ");
        }
        else {
            if (monom.coeff < 0) {
                oss << "-";  // Добавляем минус перед первым мономом, если коэффициент отрицательный
            }
            firstMonom = false;
        }

        // Добавляем коэффициент (без знака)
        double absCoeff = std::abs(monom.coeff);
        if (absCoeff != 1 || (monom.x == 0 && monom.y == 0 && monom.z == 0)) {
            oss << absCoeff;
        }

        // Добавляем переменные и их степени
        if (monom.x != 0) {
            oss << "x";
            if (monom.x != 1) {
                oss << "^" << monom.x;
            }
        }
        if (monom.y != 0) {
            oss << "y";
            if (monom.y != 1) {
                oss << "^" << monom.y;
            }
        }
        if (monom.z != 0) {
            oss << "z";
            if (monom.z != 1) {
                oss << "^" << monom.z;
            }
        }
    }

    // Если все мономы были нулевыми, возвращаем "0"
    if (firstMonom) {
        oss << "0";
    }

    return oss.str();
}