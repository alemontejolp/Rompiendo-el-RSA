
/**
 * Implementación de "./libs/rsa.h
 */

KeyPair generate_rsa_key_pair(int quantity) {
    if(quantity > prime_numbers.size()) {
        generate_prime_numbers(quantity - prime_numbers.size());
    }

    ///Elige los números secretos 'p' y 'q'.
    long long p = 0;
    long long q = 0;

    while(p == q || p == 0 || q == 0) {
        p = prime_numbers[generate_position()];
        q = prime_numbers[generate_position()];
        //std::cout << "[generate_rsa_key_pair] p: " << p << "\n";
        //std::cout << "[generate_rsa_key_pair] q: " << q << "\n";
    }

    ///Calcula el módulo de cifra.
    long long mod = p * q;

    ///Calcula el indicador phi de euler del módulo.
    long long phi_mod = (p - 1) * (q - 1);

    ///Elige la llave pública.
    if(prime_numbers.size() < 3)
        throw "Por convencion, la llave publica no debe ser igual a alguno de los numeros secretos, por lo que deberian estar disponibles más de 2 numeros primos y este no es el caso.";

    long long pub = prime_numbers[generate_position()];
    while(pub == q || pub == p) {
        pub = prime_numbers[generate_position()];
    }

    ///Calcula la llave privada.
    long long priv = inv(pub, phi_mod);

    KeyPair kp(priv, pub, mod, phi_mod, p, q);
    return kp;
}

int generate_position(void) {
    ///Más de 1 porque si no, se intentaria una división entre cero más adelante.
    if(prime_numbers.size() < 2) throw "Debe haber mas de 1 primo para elegir.";

    int i = rand() % prime_numbers.size();
    if(i < (prime_numbers.size() - 1) / 2) {
        i += rand() % ((prime_numbers.size()- 1) / 2);
    }//std::cout << "[generate_position] i = " << i << "\n";

    return i;
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
        //std::cout << "[generate_prime_numbers] numero a comprobar si es primo: " << current << ".\n";
        ///Raiz cuadrada para saber cuando parar de comprobar.
        long this_sqrt = sqrt(current);
        //std::cout << "[generate_prime_numbers] raiz cuadrada del numero anterior: " << this_sqrt << ".\n";
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
            //std::cout << "[prime_numbers] " << current << " es primo, se agrega al vector.\n";
            cont++;
            prime_numbers.push_back(current);
        } //else std::cout << "[prime_numbers] " << current << " no es primo.\n";
    }
}

long long next_prime(void) {
    //std::cout << "[next_prime] devolviendo siguiente numero primo.\n";
    if(prime_it == prime_numbers.size() - 1) {
        //std::cout << "[next_prime] iniciar calculo de nuevo numero primo.\n";
        ///Sólo generará 1 númeor primo más.
        generate_prime_numbers(1);
    }
    //std::cout << "[next_prime] siguiente numero primo: " << prime_numbers[this->prime_it + 1] << ".\n";
    return prime_numbers[++prime_it];
}

std::vector<long long> factors_of(long long num) {
    std::vector<long long> factors;
    //std::cout << "[factors_of] Calculando factores de: " << num << ".\n";
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
            //std::cout << "[factors_of] " << current_prime << " no es factor de: " << num << ".\n";
            //if(num == -1) {std::cin.ignore(); std::cin.get();}
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

void print_binary(std::vector<int> bin) {
    std::cout << "Numero binario resultante: \n";
    for(register int i = 0; i < bin.size(); i++) {
        std::cout << bin[bin.size() - i - 1];
    }
    std::cout << "\n";
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

std::vector<long long> encript(long long e, long long n, std::string N) {
    std::vector<int> exp = parse_binary(e);
    std::vector<long long> C;

    for(register int i = 0; i < N.size(); i++) {
        C.push_back(exec_pow(N[i], exp, n));
    }

    return C;
}

std::string decript(long long d, long long n, std::vector<long long> C) {
    std::vector<int> exp = parse_binary(d);
    std::string N;

    for(register int i = 0; i < C.size(); i++) {
        N.push_back(exec_pow(C[i], exp, n));
    }

    return N;
}
