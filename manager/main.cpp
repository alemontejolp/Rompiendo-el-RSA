/**
 * Manejador de acciones para el testeo de casos de pruebas
 * del problema.
 */

#include "../libs/mngritfc.h"

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
                    cin >> cmd;
                    if(cmd == "num") {
                        exec_encript_num();
                    }
                    else if(cmd == "str") {
                        exec_encript();
                    }
                    else {
                        throw "Error de subcomando encript";
                    }
                }
                else if(cmd == "decript") {
                    cin >> cmd;

                    if(cmd == "num") {
                        exec_decript_num();
                    }
                    else if(cmd == "str") {
                        exec_decript();
                    }
                }
                else if(cmd == "testcase") {
                    cin >> cmd;

                    //TODO.
                    if(cmd == "test") {
                        throw "La funcionalidad para probar los casos aun no esta disponible.";
                    }
                    else if(cmd == "generate") {
                        generate_test_cases();
                    }
                    else {
                        throw "No se reconoce el subcomando de testcase.";
                    }
                }
                else if(cmd == "cal-priv-key") {
                    calculate_private_key();
                }
                else if(cmd == "help") {
                    help();
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
            help();
        }
    }
    return 0;
}
