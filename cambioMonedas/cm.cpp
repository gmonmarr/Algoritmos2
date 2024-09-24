// Este programa realiza el cambio de monedas de una cantidad de dinero
// se debe ejecutar con el comando ./programa {monedas.txt} {costo} {pago}
// donde monedas.txt es un archivo con las denominaciones de las monedas
// el archivo de entrada tendrá el siguiente formato:
// {número de monedas}
// {denominación de la moneda 1}
// {denominación de la moneda 2}
// ...

// el archivo de salida tendrá el siguiente formato:
// {número de monedas de la moneda 1}
// {número de monedas de la moneda 2}
// ...

/*

CambioMonedas (monedas[], costo, pago)
    cambio = []
    porRegresar = pago - costo
    for i = monedas.size() - 1 to 0
        while monedas[i] <= porRegresar
            cambio.push(monedas[i])
            porRegresar -= monedas[i]
    return cambio

*/


#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

// Función que lee el archivo de entrada y guarda las monedas en un vector
vector<int> leerMonedas(string archivo) {
    ifstream file(archivo);
    
    vector<int> monedas;
    string line;
    int moneda;
    
    if (file.is_open()) {
        // Se ignora la primer línea del archivo
        getline(file, line);
        
        while (getline(file, line)) {
            moneda = stoi(line);
            monedas.push_back(moneda);
        }
        file.close();
    }
    return monedas;
}

// Función que realiza el cambio de monedas
vector<int> cambioMonedas(vector<int> monedas, int costo, int pago) {
    // inicializamos el vector de cambio (cantidad de monedas de cada denominación)
    vector<int> cambio;
    
    // calculamos el total de cambio
    int total = pago - costo;

    // iteramos sobre la lista de mayor a menor denominación
    for (int i = monedas.size() - 1; i >= 0; i--) {
        while (monedas[i] <= total) {
            cambio.push_back(monedas[i]);
            total -= monedas[i];
        }
    }

    return cambio;
}

// Función que escribe el archivo de salida
void escribirCambio(vector<int> cambio) {
    ofstream file("cambio.txt");

    if (file.is_open()) {
        file << cambio.size() << endl;
        for (int i = 0; i < cambio.size(); i++) {
            file << cambio[i] << endl;
        }
        file.close();
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        cout << "Error: número de argumentos inválido" << endl;
        return 1;
    }
    
    // guardamos los argumentos en variables
    string archivo = argv[1];
    int costo = stoi(argv[2]);
    int pago = stoi(argv[3]);

    if (costo > pago) {
        cout << "Error: el costo no puede ser mayor al pago" << endl;
        return 1;
    }

    // obtenemos el vector de monedas y ordenamos
    vector<int> monedas = leerMonedas(archivo);
    sort(monedas.begin(), monedas.end());

    // realizamos el cálculo de cambio 
    vector<int> cambio = cambioMonedas(monedas, costo, pago);

    // escribimos el archivo de salida
    escribirCambio(cambio);

    return 0;
}