/*Author            Gashi Din
 * Date             15.12.2022 10:35
 * Description      Laboratoire noté, class Uint
 * École            HEIG-VD
 * Fichier          Uint.cpp
 */
#include "Uint.hpp"
#include <algorithm>
#include <functional>
#include <random>
using namespace std;

using namespace std;
uint64_t convert(string n){
    uint64_t result = 0;
    uint64_t base = 1;
    for (size_t i = n.size() - 1; i != SIZE_MAX; --i) {
        if (n[i] == '1')
            result += base;
        base *= 2;
    }
    return result;
}
//No args constructor
Uint::Uint()=default;
Uint::Uint(size_t n){
Uint t;
    while (n > 0)
    {
        if (n % 2 == 0)
            t.nb.insert(t.nb.begin(), '0');
        else
            t.nb.insert(t.nb.begin(), '1');
        n /= 2;
    }
    this->nb=t.nb;
}
Uint::operator uint64_t ()const{
    uint64_t result = 0;
    uint64_t base = 1;
    for (size_t i = nb.size() - 1; i != SIZE_MAX; --i) {
        if (nb[i] == '1')
            result += base;
        base *= 2;
    }
    return result;
}

bool Uint::operator<(const Uint& rhs) const {
    if (nb.size() > rhs.nb.size() || nb.size() == rhs.nb.size() && nb > rhs.nb)
        return false;
    else
        return true;
}
bool Uint::operator>(const Uint& rhs) const {
    if (nb.size() < rhs.nb.size() || nb.size() == rhs.nb.size() && nb < rhs.nb)
        return false;
    else
        return true;
}
bool Uint::operator==(const Uint& rhs) const {
    return (*this<=rhs && *this>=rhs)== 0;

}
bool Uint::operator!=(const Uint& rhs) const {
    return (*this<=rhs || *this>=rhs)== 1;
}

Uint& Uint::operator+=(const Uint& autre) {
    Uint sum;
    Uint tmp = autre;
    if (nb.size() > tmp.nb.size()) {
        while (tmp.nb.size() != nb.size()) {
            tmp.nb = '0' + tmp.nb;
        }
    } else if (tmp.nb.size() > nb.size()) {
        while (nb.size() != tmp.nb.size()) {
            nb = '0' + nb;
        }
    }
    int retenue = 0;
    sum.nb.resize(nb.length());
    for (int i = nb.size()-1; i>=0 ; i--) {
        int n1=nb[i]-'0';
        int n2=tmp.nb[i]-'0';
        int result = n1 + n2 + retenue;
        retenue = result / 2;
        result = result % 2;
        sum.nb[i] = result + '0';
    }
    if (retenue > 0 ){
        sum.nb = '1' + sum.nb;
    }
    return *this=sum;
}
Uint& Uint::operator*=(const Uint& autre) {
    Uint mult;
    Uint tmp = autre;
    string d="0";
    if (nb == "0" || tmp.nb == "0") {
        mult.nb="0";
    }
    else{
        for (int i = tmp.nb.size() - 1; i >= 0; i--) {
            if (tmp.nb[i] == '1') {
                if(mult.nb=="0") {
                    mult.nb = nb;
                }else
                    mult+=(*this);
            } else if (tmp.nb[i] == '0') {
                mult.nb= '0' + mult.nb;
            }
            nb.append(d);
        }
    }
    return *this=mult;
}
Uint& Uint::operator-=(const Uint& autre) {
    int x,y;
    Uint result;
    Uint tmp=autre;
    if (*this < tmp) {
        this->nb = "erreur";
        return *this;
    }
    int carry = 0;
    int i = nb.size() - 1;
    int j = autre.nb.size() - 1;
    while (i >= 0 || j >= 0 || carry > 0) {
        if(i>=0){
            x =nb[i--] - '0';
        }else
            x=0;
        if(j>=0){
            y =tmp.nb[j--] - '0';
        }else
            y=0;
        int sum = x - y - carry;
        carry = (sum < 0) ? 1 : 0;
        result.nb.push_back((sum + 2) % 2 + '0');
    }
    reverse(result.nb.begin(), result.nb.end());
    result.eraseZero();
    return *this=result;
}
Uint& Uint::operator/=(const Uint& autre) {
    Uint remainder;
    Uint div;
    Uint tmp = autre;
    if (nb == tmp.nb) {
        div.nb += '1';
    } else {
        for (int i = 0; i < nb.size(); i++) {
            remainder.nb += nb[i];

            uint64_t w = convert(remainder.nb);
            uint64_t ww = convert(tmp.nb);

            if (remainder.nb.size() < tmp.nb.size()) {
                div.nb += "0";

            } else if (remainder.nb.size() >= tmp.nb.size() && (w - ww >= 0)) {
                div.nb += "1";
                remainder -= (tmp);
            } else
                div.nb += '0';
        }
    }
    div.eraseZero();
    return*this=div;
}

Uint &Uint::operator%=(const Uint &autre) {
    Uint remainder;
    Uint div;
    Uint tmp = autre;
    if (nb == tmp.nb) {
        div.nb += '1';
    } else {
        for (int i = 0; i < nb.size(); i++) {
            remainder.nb += nb[i];

            uint64_t w = convert(remainder.nb);
            uint64_t ww = convert(tmp.nb);

            if (remainder.nb.size() < tmp.nb.size()) {
                div.nb += "0";

            } else if (remainder.nb.size() >= tmp.nb.size() && (w - ww >= 0)) {
                div.nb += "1";
                remainder -= (tmp);
            } else
                div.nb += '0';
        }
    }
    remainder.eraseZero();
    return*this=remainder;
}
Uint& Uint::operator++(){*this+=1; return *this;}



Uint Uint::operator++(int) {
    Uint tmp = *this;
    ++(*this);
    return tmp;
}
Uint& Uint::operator--(){*this-=1; return *this;}

Uint Uint::operator--(int) {
    Uint tmp = *this;
    --(*this);
    return tmp;
}


Uint &Uint::operator<<=(const uint64_t &autre) {
    nb.append(autre, '0');
    return *this;
}

Uint operator+(Uint lhs, const Uint &rhs) {
    lhs += rhs;
    return lhs;
}
Uint operator-(Uint lhs, const Uint &rhs) {
    lhs -= rhs;
    return lhs;
}
Uint operator*(Uint lhs, const Uint &rhs) {
    lhs *= rhs;
    return lhs;
}
Uint operator/(Uint lhs, const Uint &rhs) {
    lhs /= rhs;
    return lhs;
}
Uint operator%(Uint lhs, const Uint &rhs) {
    lhs %= rhs;
    return lhs;
}

int Uint::operator<=(const Uint &comparer) {
    if (nb == "0" && comparer.nb == "0") return 1;
    if (nb.size() < comparer.nb.size())
        return 1;
    else
        return 0;
}

Uint operator<<(Uint lhs, const uint64_t &rhs) { return lhs <<= rhs; }

ostream &operator<<(std::ostream &os, const Uint &autre) {
    os << autre.nb;
    return os;
}

istream &operator>>(std::istream &in, Uint &autre) {
    in >> autre.nb;
    return in;
}
void Uint::eraseZero() {
    int i;
    while (this->nb[0] == '0' &&
           this->nb.size() > 1) {
        i = 1;
        nb.erase(0, i);
    }
}
int Uint::operator<=( const Uint &other) const
{
    if (nb.size() < other.nb.size())
        return 1;
    if(nb < other.nb)
        return 1;
    else
        for (size_t i = 0; i < nb.size(); i++) {
            if (nb.at(i) > other.nb.at(i))
                return 1;
        }
    return 0;
}

int Uint::operator>=(const Uint &other) const
{
    if (nb.size() > other.nb.size())
        return 1;
    if(nb > other.nb)
        return 1;
    else
        for (size_t i = 0; i < nb.size(); i++) {
            if (nb.at(i) < other.nb.at(i))
                return 1;
        }
    return 0;
}
Uint Uint::gen_bit(const Uint& nbPrime) {
    int compte;

    Uint res;
    res+='1';
    random_device rd;
    mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    uniform_real_distribution<> dis(0, 2);
        for (compte = nbPrime.nb.size()-1; compte > 0; compte--) {

            int m =dis(gen);
            if (m)
                res.nb= '1'+ res.nb;
            else
                res.nb= '0'+res.nb;
        }
    return res;
}




