/**
 * Funciones necesarias para el uso del algoritmo RSA.
 * Estas funciones son con motivos didacticos y no
 * están contempladas para el uso real en producción
 * debido a que el tamaño de los números que son
 * capaces de manejar no son lo sufucuentemente grandes
 * para hacer efectivo este algoritmo.
 */
#ifndef _RSA_H_
#define _RSA_H_

struct KeyPair {
    KeyPair(){}
    KeyPair(
        long long priv,
        long long pub,
        long long n,
        long long phi_n,
        long long _p,
        long long _q):
            private_key(priv),
            public_key(pub),
            mod(n),
            phi_mod(phi_n),
            p(_p),
            q(_q){}

    long long private_key;
    long long public_key;
    long long mod;
    long long phi_mod;
    long long p;
    long long q;
};

     KeyPair    generate_rsa_key_pair(int);
vector <int>    parse_binary(long long);
        void    print_binary(vector<int>);
   long long    inv(long long, long long);

#endif // _RSA_H_
