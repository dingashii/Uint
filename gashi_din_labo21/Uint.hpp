/*Author            Gashi Din
 * Date             15.12.2022 10:35
 * Description      Laboratoire noté, class Uint
 * École            HEIG-VD
 * Fichier          Uint.hpp
 */

#ifndef FINALOLABO11_UINT_HPP
#define FINALOLABO11_UINT_HPP

#include <iostream>

using namespace std;

class Uint {
private:
    string nb;
public:
    // Constructors
    Uint(); // Default constructeur
    Uint(size_t n); // Constructeur avec size_t
    explicit operator uint64_t() const; //Cast explicite

    //opérateur rationnel
    bool operator<(const Uint &autre) const;

    bool operator>(const Uint &autre) const;

    bool operator==(const Uint &autre) const;

    bool operator!=(const Uint &autre) const;

    int operator<=(const Uint &other) const;

    int operator>=(const Uint &other) const;



    //opérateur d'affectation
    friend Uint operator+(Uint lhs, const Uint &rhs);

    friend Uint operator*(Uint lhs, const Uint &rhs);

    friend Uint operator-(Uint lhs, const Uint &rhs);

    friend Uint operator/(Uint lhs, const Uint &rhs);

    friend Uint operator%(Uint lhs, const Uint &rhs);

    //Constructeur de decalage des bits
    friend Uint operator<<(Uint lhs, const uint64_t &rhs);


    Uint &operator<<=(const uint64_t &autre);


    //Operateurs arithmetiques
    Uint &operator+=(const Uint &other);

    Uint &operator-=(const Uint &other);

    Uint &operator*=(const Uint &other);

    Uint &operator/=(const Uint &other);

    Uint &operator%=(const Uint &other);

    Uint &operator++();

    Uint &operator--();

    Uint operator--(int);
    Uint operator++(int);


    int operator<=(const Uint &comparer);



    friend std::ostream &operator<<(std::ostream &os, const Uint &autre);// Surcharge l'opérateur << pour sortir un Uint
    friend std::istream &operator>>(std::istream &in, Uint &autre);// Surcharger l'opérateur >> pour lire dans un Uint
    friend Uint expMod(Uint base, Uint exp, Uint mod);
    void eraseZero();


    static Uint gen_bit(const Uint & nbPrime);


};


#endif //FINALOLABO11_UINT_HPP
