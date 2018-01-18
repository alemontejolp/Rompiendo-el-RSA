/**
 * Propuesta de solución para el problema: "Rompiendo el RSA."
 */

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

///Variables compartidas por funciones.
std::vector<long long>  prime_numbers(1, 2);///Contenedor para los numeros primos.
                  long  prime_it;///Iterador para los números primos.

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
 * @description Convierte un número entero positivo de notación decimal
 * a su correspondiente notación binaria. Si estas condiciones no se
 * cumplen. el resultado podría estar errado.
 *
 * @return std::vector<int>
 */
std::vector<int> parse_binary(long long);

/**
 * @decript Desencripta un mensaje de texto, recibiendo el
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

void generate_prime_numbers(int quantity) {
    ///El último número primo en el vector.
    long long current = prime_numbers[prime_numbers.size() - 1];
    ///Cantidad de números primos a calcular.
    for(register int cont = 0; cont < quantity;) {
        ///Para saber si es primo o no despues de aplicar las operaciones.
        bool is_prime_number = true;
        ///El número que sigue. Aun sin saber si es primo o no.
        current++;
        ///Raiz cuadrada para saber cuando parar de comprobar.
        long long this_sqrt = sqrt(current);
        ///Mientras el primo actual sea menor o igual a la raiz, comprueba si es primo o no.
        for(int i = 0; prime_numbers[i] <= this_sqrt; i++) {
            ///Si el residuo es 0, no es primo.
            if(!(current % prime_numbers[i])) {
                is_prime_number = false;
                break;
            }
        }
        ///Si es primo, agregalo al vector.
        if(is_prime_number) {
            cont++;
            prime_numbers.push_back(current);
        }
    }
}

long long next_prime(void) {
    if(prime_it == prime_numbers.size() - 1) {
        ///Sólo generará 1 númeor primo más.
        generate_prime_numbers(1);
    }

    return prime_numbers[++prime_it];
}

std::vector<long long> factors_of(long long num) {
    std::vector<long long> factors;
    ///El número primo actual.
    long long current_prime = prime_numbers[0];
    ///La posición del vector de primos. La [0] = 2.
    prime_it = 0;
    ///El residuo de la divición entre primos. Para saber si es divisible o no.
    int residue = 1;

    ///Mientras el númeor a factorizar sea distinto de 1.
    while(num != 1) {
        residue = num % current_prime;

        if(num < 0 || current_prime < 0 || (num / current_prime) < 0) {
            throw "Uno de los valores es menor a 0. ERROR!!";
        }

        ///Si el residuo es 0, el actual es un factor.
        if(!residue) {
            ///Lo agrega al vector de factores.
            factors.push_back(current_prime);
            ///Actualiza el número.
            num /= current_prime;
            ///Por lo que al dividir, el cociente es el otro primo.
            factors.push_back(num);
            return factors;
        }
        else {
            ///Si el residuo no es 0, trae el siguiente primo.
            current_prime = next_prime();
        }
    }
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


std::vector<int> parse_binary(long long num) {
    std::vector<int> binary;

    do {
        binary.push_back(num % 2);
        num /= 2;
    }while(num);

    return binary;
}

long long exec_pow(long long base, std::vector<int> exp, long long mod) {
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

std::string decript(long long d, long long n, std::vector<long long> C) {
    std::vector<int> exp = parse_binary(d);
    std::string N;

    for(register int i = 0; i < C.size(); i++) {
        N.push_back(exec_pow(C[i], exp, n));
    }

    return N;
}
