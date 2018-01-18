
/**
 * Esta es la interfaz de el manehador.
 */

#ifndef _MNGRITFC_H_
#define _MNGRITFC_H_

#include <iostream>
#include "../libs/rsa.h"
#include <fstream>

using namespace std;

string data[] = {
    "{'name':'Alexander','message':'Hola, esto es un mensaje secreto.'}",
    "{'name':'Ekaterina','message':'Mensajito... :3'}",
    "{'name':'Sahsa','message':'Mensaje secreto!'}",
    "{'name':'Brigitte','message':'Hellow wordl!'}",
    "{'name':'Mikasa','message':'Ya no se que poner aqui. xd'}",
    "{'name':'Kary','message':'Tengo hambre! xD'}",
    "{'name':'Ilonka','message':'Otro mensaje secreto.'}",
    "{'name':'Yui','message':'Este es un mensaje secreto!'}",
    "{'name':'Kyouko','message':'I can fly! you can fly?'}",
    "{'name':'Akari','message':'Hello!! :D'}"
};

int data_size = sizeof(data) / sizeof(string);

void print_line(ostream* = &cout);
void generate_key_pair(void);
void print_key(KeyPair, ostream* = &cout);
void exec_encript(void);
void exec_decript(void);
void print_cripto(vector<long long>);
void generate_test_cases(void);
void print_test_case(KeyPair, vector<long long>, ostream* = &cout);
string rand_data(void);
void calculate_private_key(void);
void exec_encript_num(void);
void exec_decript_num(void);
void help(void);

#include "../src/mngritfc.cpp"

#endif // _MNGRITFC_H_
