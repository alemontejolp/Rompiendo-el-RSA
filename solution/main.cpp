/**
 * Propuesta de solución para el problema: "Rompiendo el RSA."
 */

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

///Variable compartida por funciones.
vector<long long>  prime_numbers(1, 2);///Contenedor para los numeros primos.

///Funciones.

/**
 * @description Calcula el siguiente número primo a partir del último
 * primo calculado.
 *
 * @return long long
 */
long long next_prime(void);

/**
 * @description Calcula los factores primos de un número
 * que es producto de dos números primos. Si el argumento no
 * cumple con esta condición, el resultado será errado.
 *
 * @param long long
 *   El número a factorizar.
 * @return vector<long long>
 */
vector<long long> factors_of(long long);

/**
 * @description Calcula el inverso multiplicativo modular de un número
 * dentro de un cuerpo mayor a él usando el algoritmo extendido de euclides.
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
 * @description Convierte un número entero positivo de notación decimal
 * a su correspondiente notación binaria. Si estas condiciones no se
 * cumplen. el resultado podría estar errado.
 *
 * @return vector<int>
 */
vector<int> parse_binary(long long);

/**
 * @description Ejecuta una potenciación módulo de un número. Usada
 * para el cifrado, descifrado o fimado con RSA.
 *
 * Para más información, mirar: https://www.youtube.com/watch?v=C2-kLqWfBaE
 *
 * @param long long
 *  Número base.
 * @param vector<int>
 *  Exponente en binario.
 * @param long long
 *  módulo.
 * @return long long
 */
long long exec_pow(long long, vector<int>, long long);

/**
 * @decript Desencripta un mensaje de texto, recibiendo el
 * criptograma.
 *
 * @param long long
 *   La llave privada.
 * @param long long
 *   El módulo de crifra.
 * @param vector<long long>
 *   El criptograma.
 * @return string
 */
string decript(long long, long long, vector<long long>);

int main(void) {
    int l;///El tamaño del criptograma.
    long long e;///La llave pública.
    long long n;///El módulo de crifra.
    long long current;///El número actual para leer el criptograma.
    vector<long long> C;///El criptograma.

    ///Leer los datos.
    cin >> e >> n >> l;

    for(register int i = 0; i < l; i++) {
        cin >> current;
        C.push_back(current);
    }

    try {
        ///Factorizar el modulo de cifra.
        vector<long long> factors = factors_of(n);
        long long p = factors[0];
        long long q = factors[1];

        ///Calcular la llave privada.
        long long d = inv(e, (p - 1) * (q - 1));

        ///desencriptar.
        cout << decript(d, n, C) << "\n";
    }
    catch(const char* ex) {
        cout << "\nError: " << ex << "\n";
    }
    return 0;
}

long long next_prime(void) {
    long long current = prime_numbers[prime_numbers.size() - 1];
    bool is_prime;

    do {
        is_prime = true;
        current++;
        long long r = sqrt(current);

        for(register int i = 0; r <= prime_numbers[i]; i++) {
            ///Si es el actual es número compuesto.
            if(!(current % prime_numbers[i])) {
                ///No es primo y se rompe el bucle inmediato.
                is_prime = false;
                break;
            }
        }
    } while(!is_prime);

    prime_numbers.push_back(current);
    return current;
}

vector<long long> factors_of(long long num) {
    ///Donde se guardaran los factores primos.
    vector<long long> factors;
    long long r; ///El residuo de la divición para saber si la divición es posible.
    long long p; ///Uno de los factores.
    long long q; ///El otro factor.

    do {
        p = next_prime();
        q = num / p;
        r = num % p;
    } while(r); ///Seguir mientras "r" tenga algún valor.

    factors.push_back(p);
    factors.push_back(q);

    return factors;
}

long long inv(long long num, long long body) {
    ///las variables 'y' son las de la tabla del algoritmo de euclides extentido.
    long long y_0 = 0;///El primer valor de 'y' sub 'i' de la tabla ('y' sub 0).
    long long y_1 = 1;///El segundo valor de 'y' sub 'i' de la tabla ('y' sub 1).
    long long r_body = body;

    while(num) {
        ///Calcula el cociente y el residuo para continar la tabla.
        long long temp = num;
        long long quotient = body / num;
        num = body % num;
        body = temp;

        ///Calcula la siguiente 'y'.
        temp = y_1;
        y_1 = y_0 - quotient * y_1;
        y_0 = temp;
    }

    return (y_0 < 0) ? (y_0 + r_body) : (y_0);
}


vector<int> parse_binary(long long num) {
    vector<int> binary;

    do {
        binary.push_back(num % 2);
        num /= 2;
    }while(num);

    return binary;
}

long long exec_pow(long long base, vector<int> exp, long long mod) {
    long long current = base;
    long long total = 1;
    for(register int i = 0; i < exp.size(); i++) {
        if(exp[i]) {
            total = (total * current) % mod;
        }
        current = (current * current) % mod;
    }

    return total;
}

string decript(long long d, long long n, vector<long long> C) {
    vector<int> exp = parse_binary(d);
    string N;

    for(register int i = 0; i < C.size(); i++) {
        N.push_back(exec_pow(C[i], exp, n));
    }

    return N;
}
