/*Author            Gashi Din
 * Date             15.12.2022 10:35
 * Description      Laboratoire noté, class Uint
 * École            HEIG-VD
 * Fichier          Prime.cpp
 */

#include "Prime.hpp"
#include "Uint.hpp"
//
// Created by dinga on 23.12.2022.
//
#include <algorithm>
#include "Uint.hpp"
#include <random>

using namespace std;
Uint expMod(Uint base, Uint exp, Uint mod) {
    Uint r(1);

    while (exp >=1) {
        if (exp % 2 == 0) {
            base = (base * base) % mod;
            exp /= 2;
        } else {
            r = (r * base) % mod;
            exp--;
        }
    }
    return r;
}
bool prime(Uint nbPrime) {
    for (uint64_t i = 0; i != 10; i++) {
        Uint alea = Uint::gen_bit(nbPrime);
        //std::cout << " rand " << alea << std::endl;


        Uint q = 1, u = nbPrime - 1;

        while ((u % 2 == 0) && (q == 1)) {
            u = u / 2;
            q = expMod(alea, u, nbPrime);

            if ((q != 1) && (q != nbPrime - 1)) {
                return false;
            }
        }
    }
    return true;
}
