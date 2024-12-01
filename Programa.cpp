#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;

class Persona 
{
protected:
    string nombre;
    string apellido;
    int edad;

public:
    Persona() : nombre(""), apellido(""), edad(0) {}
    Persona(string nom, string ape, int ed) : nombre(nom), apellido(ape), edad(ed) {}
    virtual ~Persona() {}

    virtual void anadirDatos() = 0;
    virtual void ordenarDatos() = 0;
    virtual void mostrar() const = 0;
    virtual void eliminarDatos() = 0;
    virtual void modificarDatos() = 0;
    virtual void buscarDatos() = 0;

    virtual string toString() const = 0;
};

class Profesor : public Persona 
{
private:
    string especialidad;
    string modalidad;

public:
    Profesor() : Persona(), especialidad(""), modalidad("") {}
    Profesor(string nom, string ape, int ed, string esp, string mod)
        : Persona(nom, ape, ed), especialidad(esp), modalidad(mod) {}

    void anadirDatos() override {
        //anadir datos del profesor
    }

    void ordenarDatos() override {
        //ordenar datos del profesor
    }

    void mostrar() const override {
        cout << left << setw(15) << nombre
             << setw(15) << apellido
             << setw(5) << edad
             << setw(20) << especialidad
             << setw(15) << modalidad << endl;
    }

    void eliminarDatos() override {
        //eliminar datos del profesor
    }

    void modificarDatos() override {
        //modificar datos del profesor
    }

    void buscarDatos() override {
        //buscar datos del profesor
    }

    string toString() const override {
        return nombre + "," + apellido + "," + to_string(edad) + "," + especialidad + "," + modalidad;
    }
};

class Estudiante : public Persona {
private:
    string codigo;
    string ciclo;

public:
    Estudiante() : Persona(), codigo(""), ciclo("") {}
    Estudiante(string nom, string ape, int ed, string cod, string cic)
        : Persona(nom, ape, ed), codigo(cod), ciclo(cic) {}

    void anadirDatos() override {
        //añadir datos del estudiante
    }

    void ordenarDatos() override {
        //ordenar datos del estudiante
    }

    void mostrar() const override {
        cout << left << setw(15) << nombre
             << setw(15) << apellido
             << setw(5) << edad
             << setw(20) << codigo
             << setw(15) << ciclo << endl;
    }

    void eliminarDatos() override {
        //eliminar datos del estudiante
    }

    void modificarDatos() override {
        //modificar datos del estudiante
    }

    void buscarDatos() override {
        //buscar datos del estudiante
    }

    string toString() const override {
        return nombre + "," + apellido + "," + to_string(edad) + "," + codigo + "," + ciclo;
    }
};

// Funciones para mostrar datos
void mostrarDatosProfesores(const vector<Profesor>& profesores) {
    cout << "\n=== Profesores ===\n";
    cout << left << setw(15) << "Nombre" << setw(15) << "Apellido" << setw(5) << "Edad"
         << setw(20) << "Especialidad" << setw(15) << "Modalidad" << endl;
    for (const auto& profesor : profesores) 
        profesor.mostrar();
}

void mostrarDatosEstudiantes(const vector<Estudiante>& estudiantes) {
    cout << "\n=== Estudiantes ===\n";
    cout << left << setw(15) << "Nombre" << setw(15) << "Apellido" << setw(5) << "Edad"
         << setw(20) << "Codigo" << setw(15) << "Ciclo" << endl;
    for (const auto& estudiante : estudiantes)
        estudiante.mostrar();
}

// Funcion para cargar los datos iniciales de los profesores y estudiantes
void CargarDatos(vector<Profesor>& profesores, vector<Estudiante>& estudiantes) {
    ifstream archivoProfesores("profesores.txt");
    ifstream archivoEstudiantes("estudiantes.txt");

    if (!archivoProfesores || !archivoEstudiantes) {
        cerr << "Error al abrir los archivos!\n";
        return;
    }

    string linea;

    // Cargar profesores
    while (getline(archivoProfesores, linea)) {
        size_t pos = 0;
        vector<string> datos;
        while ((pos = linea.find(",")) != string::npos) {
            datos.push_back(linea.substr(0, pos));
            linea.erase(0, pos + 1);
        }
        datos.push_back(linea);

        if (datos.size() == 5) {
            Profesor profesor(datos[0], datos[1], stoi(datos[2]), datos[3], datos[4]);
            profesores.push_back(profesor);
        }
    }

    // Cargar estudiantes
    while (getline(archivoEstudiantes, linea)) {
        size_t pos = 0;
        vector<string> datos;
        while ((pos = linea.find(",")) != string::npos) {
            datos.push_back(linea.substr(0, pos));
            linea.erase(0, pos + 1);
        }
        datos.push_back(linea);

        if (datos.size() == 5) {
            Estudiante estudiante(datos[0], datos[1], stoi(datos[2]), datos[3], datos[4]);
            estudiantes.push_back(estudiante);
        }
    }

    archivoProfesores.close();
    archivoEstudiantes.close();
}

int main() {
    vector<Profesor> profesores;
    vector<Estudiante> estudiantes;

    CargarDatos(profesores, estudiantes);

    int opcion;
    do {
        cout << "================================= MENU PRINCIPAL ===============================\n";
        cout << " 1. Anadir Datos\n";
        cout << " 2. Mostrar Datos\n";
        cout << " 3. Ordenar Datos\n";
        cout << " 4. Eliminar Datos\n";
        cout << " 5. Modificar Datos\n";
        cout << " 6. Buscar Datos\n";
        cout << " 0. Salir\n";
        cout << "================================================================================\n";
        cout << " Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            // Anadir datos
            break;
        case 2:
            // Mostrar datos
        {
            int opcion1;
            cout << "============================= MOSTRAR DATOS ==============================\n";
            cout << " 1. Profesores\n";
            cout << " 2. Estudiantes\n";
            cout << "============================================================================\n";
            cout << " Seleccione una opcion: ";
            cin >> opcion1;

            switch (opcion1) {
            case 1:
                mostrarDatosProfesores(profesores);
                break;
            case 2:
                mostrarDatosEstudiantes(estudiantes);
                break;
            default:
                cout << "<<< Opcion no valida >>>\n";
                break;
            }
            break;
        }
        case 3:
            // Ordenar datos
            break;
        case 4:
            // Eliminar datos
            break;
        case 5:
            // Modificar datos
            break;
        case 6:
            // Buscar datos
            break;
        case 0:
            cout << "Cerrando el programa...\n";
            break;
        default:
            cout << "<<< Opcion no valida >>>\n";
            break;
        }
    } while (opcion != 0);

    return 0;
}
