/**
 * Funciones necesarias para el uso del algoritmo RSA.
 * Estas funciones son con motivos didacticos y no
 * están contempladas para el uso real en producción
 * debido a que el tamaño de los números que son
 * capaces de manejar no son lo sufucuentemente grandes
 * para hacer efectivo este algoritmo.
 *
 * Para más información, mirar: https://www.youtube.com/watch?v=CMe0COxZxb0
 */
#ifndef _RSA_H_
#define _RSA_H_

#include <cmath>
#include <vector>
#include <time.h>
#include <cstdlib>

/**
 * @description Estructura que contiene los datos de
 * un par de llaves RSA, así como las mismas llaves.
 */
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

///Variables compartidas por funciones.
std::vector<long long>  prime_numbers(1, 2);///Contenedor para los numeros primos.
                  long  prime_it;///Iterador para los números primos.

/**
 * @description Genera el par de llaves RSA y sus datos
 * asociados.
 *
 * @param int
 *   Cantidad de números primos entre los cuales escoger
 *   Para las operaciones.
 * @return KeyPair
 */
KeyPair generate_rsa_key_pair(int);

/**
 * @description Convierte un número entero positivo de notación decimal
 * a su correspondiente notación binaria. Si estas condiciones no se
 * cumplen. el resultado podría estar errado.
 *
 * @return std::vector<int>
 */
std::vector<int> parse_binary(long long);

/**
 * @description Sólo imprime el número en binario que se le pase.
 *
 * @param std::vector<int>
 *   El número.
 */
void print_binary(std::vector<int>);

/**
 * @description Calcula el inverso multiplicativo modular de un número
 * dentro de otro mayor a él usando el algoritmo extendido de euclides.
 *
 * Para entender mejor esta función, mirar: https://www.youtube.com/watch?v=JGyFkl5_KHM
 *
 * @param long long.
 *   El número dentro del cuerpo.
 * @param long long.
 *   El cuerpo en el que se buscará el inverso.
 * @return long long.
 */
long long inv(long long, long long);

/**
 * @description Elige una posición aleatoria igual o mayor
 * a la cantidad de número primos que existan en el contenedor
 * de números primos (prime_numbers).
 *
 * @return int
 */
int generate_position(void);

/**
 * @description Ejecuta una potenciación módulo de un número. Usada
 * para el cifrado, descifrado o fimado con RSA.
 *
 * Para más información, mirar: https://www.youtube.com/watch?v=C2-kLqWfBaE
 *
 * @param long long
 * Número base.
 * @param std::vector<int>
 * Exponente en binario.
 * @param long long
 * módulo.
 * @return long long
 */
long long exec_pow(long long, std::vector<int>, long long);

/**
 * @description Genera la cantidad de primos que se le indiquen.
 *
 * @param int
 *   La cantidad de primos a generar.
 */
void generate_prime_numbers(int);

/**
 * @description Pasa al siguiente primo wn función del iterador.
 * Si no hay más primos, calcula el que sigue y lo retorna.
 *
 * @return long long
 */
long long next_prime(void);

/**
 * @description Calcula los factores primos de un número
 * que es producto de dos números primos. Si el arumento no
 * cumple con esta condición, el resultado será errado.
 *
 * @param long long
 *   El número a factorizar.
 * @return std::vector<long long>
 */
std::vector<long long> factors_of(long long);

/**
 * @description Encripta un mensaje de texto,
 *
 * @param long long
 *   La llave pública.
 * @param long long
 *   El modulo de cifra.
 * @param string
 *   El mensaje.
 * @return std::vector<long long>
 */
std::vector<long long> encript(long long, long long, std::string);

/**
 * @description Desencripta un mensaje de texto, recibiendo el
 * criptograma.
 *
 * @param long long
 *   La llave privada.
 * @param long long
 *   El módulo de crifra.
 * @param std::vector<long long>
 *   El criptograma.
 * @return std::string
 */
std::string decript(long long, long long, std::vector<long long>);

#include "../src/rsa.cpp"

#endif // _RSA_H_
