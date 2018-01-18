
/**
 * Implementación de mngritfc.h
 */

void print_line(ostream* out) {
    *out << "------------------------------------------------------------------\n";
}

void generate_key_pair(void) {
    print_line();

    int n_keys, n_primes;
    char in_file;
    ofstream out;

    cout << "Cantidd de llaves: ";
    cin >> n_keys;
    cout << "Cantidad de primos a generar: ";
    cin >> n_primes;
    if(n_primes > 7000) {
        cout << "Es posible que con mas de 7k de primos, el resultado este errado. "
                  << "Desea continuar aun sabiendo esto [S/n]: ";
        char comp;
        cin >> comp;
        if(comp == 'n' || comp == 'N') {
            cout << "Creacion de llaves aborada por falta de capacidad y optimizacion.\n";
            print_line();
            return;
        }
    }
    cout << "Iprimir en archivo de texto [s/n]: ";
    cin >> in_file;
    if(in_file == 's') {
        //throw "La funcion para imprimir un archivo no esta disponible.";
        string filename;
        cout << "Nombre del archivo: ";
        cin >> filename;

        out.open(filename.c_str());
    }

    for(register int i = 0; i < n_keys; i++) {
        if(in_file == 's') {
            print_key(generate_rsa_key_pair(n_primes), &out);
        }
        else {
            print_key(generate_rsa_key_pair(n_primes));
        }
    }
    cout << "Hecho.\n";
    print_line();
}

void print_key(KeyPair k, ostream* out) {
    print_line(out);
    *out << "Llave publica: " << k.public_key << "\n";
    *out << "Llave privada: " << k.private_key << "\n";
    *out << "Modulo de cifra: " << k.mod << "\n";
    *out << "Phi del modulo: " << k.phi_mod << "\n";
    *out << "p: " << k.p << "\n";
    *out << "q: " << k.q << "\n";
    print_line(out);
}

void exec_encript(void) {
    print_line();
    string data;
    long long e;
    long long n;

    cin.ignore();

    cout << "Mensaje a encriptar: ";
    getline(cin, data);
    cout << "Llave publica: ";
    cin >> e;
    cout << "Modulo de cifra: ";
    cin >> n;

    cout << "El criptorama es: \n";
    print_cripto(encript(e, n, data));

    print_line();
}

void exec_decript(void) {
    print_line();
    int length;
    long long d;
    long long n;
    long long current;
    vector<long long> C;

    cout << "Llave privada: ";
    cin >> d;
    cout << "Modulo de crifra: ";
    cin >> n;
    cout << "Longitud del criptograma: ";
    cin >> length;
    cout << "Escribe el criptograma: \n";
    for(register int i = 0; i < length; i++) {
        cin >> current;
        C.push_back(current);
    }

    cout << "El mensaje es: \n";
    cout << decript(d, n, C) << "\n";

    print_line();
}

void print_cripto(vector<long long> C) {
    for(register int i = 0; i < C.size(); i++) {
        cout << C[i] << "\n";
    }
}

void generate_test_cases(void) {
    print_line();
    int n_cases, n_pn;
    char in_file;
    ofstream out;

    cout << "Cantidad de casos de prueba a generar: ";
    cin >> n_cases;
    cout << "Cantidad de numeros primos a usar: ";
    cin >> n_pn;
    if(n_pn > 7000) {
        cout << "Es posible que con mas de 7k de primos, el resultado este errado. "
                  << "Desea continuar aun sabiendo esto [S/n]: ";
        char comp;
        cin >> comp;
        if(comp == 'n' || comp == 'N') {
            cout << "Creacion de llaves aborada por falta de capacidad y optimizacion.\n";
            print_line();
            return;
        }
    }
    cout << "Imprimir en arcvhivo de texto: [S(recomendado)/n]: ";
    cin >> in_file;

    if(in_file == 's' || in_file == 'S') {
        string fn;

        cout << "Nombre del archivo de salida: ";
        cin >> fn;

        out.open(fn.c_str());
    }

    for(register int i = 0; i < n_cases; i++) {
        KeyPair kp = generate_rsa_key_pair(n_pn);
        vector<long long> cript = encript(kp.public_key, kp.mod, rand_data());

        if(in_file == 's' || in_file == 'S') {
            print_test_case(kp, cript, &out);
        }
        else {
            print_test_case(kp, cript);
        }
    }
    cout << "Hecho.\n";
    print_line();
}

void print_test_case(KeyPair key, vector<long long> data, ostream* out) {
    *out << key.public_key << " " << key.mod << " " << data.size() << " ";
    for(register int i = 0; i < data.size(); i++) {
        *out << data[i] << " ";
    }
    *out << "\n";
}

string rand_data(void) {
    return data[rand() % data_size];
}

void calculate_private_key(void) {
    print_line();
    long long e, mod;

    cout << "Clave publica: ";
    cin >> e;
    cout << "Modulo de cifra: ";
    cin >> mod;

    vector<long long> f = factors_of(mod);

    cout << "Llave privada: " << inv(e, (f[0] - 1) * (f[1] - 1)) << "\n";
    print_line();
}

void exec_encript_num(void) {
    print_line();
    long long e, mod, data;
    cout << "Clave publica: ";
    cin >> e;
    cout << "Modulo de cifra: ";
    cin >> mod;
    cout << "Numero a cifrar: ";
    cin >> data;

    vector<int> exp = parse_binary(e);
    cout << "El numero cifrado: " << exec_pow(data, exp, mod) << "\n";
    print_line();
}

void help(void) {
    print_line();
    cout << "Acciones para ejecutar: \n";
    cout << "Al inicio simpre escribir 'rsa', excepto si se usa el comando 'exit'. Ejemplo: 'rsa encript str'.\n\n";
    cout << "geygen --> Genera claves RSA.\n";
    cout << "encript --> \n";
    cout << "\tnum --> Encripta un numero.\n";
    cout << "\tstr --> Encripta una cadena de caracteres.\n";
    cout << "decript --> \n";
    cout << "\tnum --> desencripta un numero.\n";
    cout << "\tstr --> desencripta una cadena de caracteres.\n";
    cout << "testcase --> \n";
    cout << "\tgenerate --> genera casos de prueba.\n";
    cout << "cal-priv-key --> calcula una llave privada.\n";
    cout << "exit --> termina la aplicacion.\n";
    cout << "help --> muestra esta ayuda.\n";
    print_line();
}
