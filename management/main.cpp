/**
 * Manejador de acciones para el testeo de casos de pruebas
 * del problema.
 */

#include <iostream>
#include "../libs/rsa.h"
#include <fstream>

using namespace std;

void print_line(ostream* out = &cout);
void generate_key_pair(void);
void print_key(KeyPair, ostream* = &cout);
void exec_encript(void);
void exec_decript(void);
void print_cripto(vector<long long>);

int main(void) {
    string cmd;

    ///Para segurar los numeros aleatorios.
    srand(time(0));

    while(cmd != "exit") {
        try {
            cin >> cmd;

            if(cmd == "rsa") {
                cin >> cmd;

                if(cmd == "keygen") {
                    generate_key_pair();
                }
                else if(cmd == "encript") {
                    exec_encript();
                }
                else if(cmd == "decript") {
                    exec_decript();
                }
                else {
                    throw "Subcomando de 'rsa' no encontrado.";
                }
            }
            else {
                if(cmd != "exit") {
                    throw "Comando no reconocido.";
                }
            }
        }
        catch(const char* ex) {
            print_line();
            cout << "Error!\n";
            cout << ex << "\n";
            print_line();
        }
    }
    return 0;
}

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
