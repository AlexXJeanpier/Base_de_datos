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
    
    //anadir datos del profesor
    void anadirDatos()
    {
        cout << "\n================================= ANADIR DATOS DEL PROFESOR ===============================\n";
        cout << " Nombre: ";
        cin >> nombre;
        cout << " Apellido: ";
        cin >> apellido;
        cout << " Edad: ";
        cin >> edad;
        cout << " Especialidad: ";
        cin >> especialidad;
        cout << " Modalidad: ";
        cin >> modalidad;

        ofstream archivo("profesores.txt", ios::app);
        if (archivo.is_open())
        {
            archivo << toString() << endl;
            archivo.close();
        }
        else 
        {
            cerr << "Error al abrir el archivo para escribir datos del profesor.\n";
        }
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

    //anadir datos del estudiante
    void anadirDatos()
    {
        cout << "\n================================= ANADIR DATOS DEL ESTUDIANTE ===============================\n";
        cout << " Nombre: ";
        cin >> nombre;
        cout << " Apellido: ";
        cin >> apellido;
        cout << " Edad: ";
        cin >> edad;
        cout << " Codigo: ";
        cin >> codigo;
        cout << " Ciclo: ";
        cin >> ciclo;

        ofstream archivo("estudiantes.txt", ios::app);
        if (archivo.is_open())
        {
            archivo << toString() << endl;
            archivo.close();
        }
        else 
        {
            cerr << "Error al abrir el archivo para escribir datos del estudiante.\n";
        }
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

// Prototipos
void OrdenarProfesores(vector<Profesor>& profesores, int low, int high);
void OrdenarEstudiantes(vector<Estudiante>& estudiantes, int low, int high);
int PartitionProfesores(vector<Profesor>& profesores, int low, int high);
int PartitionEstudiantes(vector<Estudiante>& estudiantes, int low, int high);

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

void anadirDatosProfesores(vector<Profesor>& profesores)
{
    Profesor profesor;
    profesor.anadirDatos();
    profesores.push_back(profesor);
}

void anadirDatosEstudiantes(vector<Estudiante>& estudiantes)
{
    Estudiante estudiante;
    estudiante.anadirDatos();
    estudiantes.push_back(estudiante);
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
    while (getline(archivoEstudiantes, linea)) 
    {
        size_t pos = 0;
        vector<string> datos;
        while ((pos = linea.find(",")) != string::npos) 
        {
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

// Ordenamiento QuickSort
void OrdenarProfesores(vector<Profesor>& profesores, int low, int high)
{
    if (low < high)
    {
        int pivot = PartitionProfesores(profesores, low, high);
        OrdenarProfesores(profesores, low, pivot - 1);
        OrdenarProfesores(profesores, pivot + 1, high);
    }

    //Sobreescribir el archivo con los datos ordenados en el mismo archivo
    ofstream archivo("profesores.txt", ios::trunc);
    if (archivo.is_open())
    {
        for (const auto& profesor : profesores)
        {
            archivo << profesor.toString() << endl;
        }
        archivo.close();
    }
    else
    {
        cerr << "Error al abrir el archivo para escribir datos del profesor.\n";
    }


}

int PartitionProfesores(vector<Profesor>& profesores, int low, int high)
{
    string pivot = profesores[high].toString();
    int i = low - 1;

    for (int j = low; j < high; j++) 
    {
        if (profesores[j].toString() < pivot) 
        {
            i++;
            swap(profesores[i], profesores[j]);
        }
    }
    swap(profesores[i + 1], profesores[high]);
    return i + 1;
}

void OrdenarEstudiantes(vector<Estudiante>& estudiantes, int low, int high)
{
    if (low < high)
    {
        int pivot = PartitionEstudiantes(estudiantes, low, high);
        OrdenarEstudiantes(estudiantes, low, pivot - 1);
        OrdenarEstudiantes(estudiantes, pivot + 1, high);
    }

    //Sobreescribir el archivo con los datos ordenados en el mismo archivo
    ofstream archivo("estudiantes.txt", ios::trunc);
    if (archivo.is_open())
    {
        for (const auto& estudiante : estudiantes)
        {
            archivo << estudiante.toString() << endl;
        }
        archivo.close();
    }
    else
    {
        cerr << "Error al abrir el archivo para escribir datos del estudiante.\n";
    }
}


int PartitionEstudiantes(vector<Estudiante>& estudiantes, int low, int high)
{
    string pivot = estudiantes[high].toString();
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (estudiantes[j].toString() < pivot)
        {
            i++;
            swap(estudiantes[i], estudiantes[j]);
        }
    }
    swap(estudiantes[i + 1], estudiantes[high]);
    return i + 1;
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

        switch (opcion) 
        {
            // Anadir datos
            case 1:
            {
                cout << "================================= ANADIR DATOS ===============================\n";
                cout << " 1. Profesor\n";
                cout << " 2. Estudiante\n";
                cout << "================================================================================\n";
                cout << " Seleccione una opcion: ";
                cin >> opcion;

                switch (opcion) {
                case 1:
                    anadirDatosProfesores(profesores);
                    break;
                case 2:
                    anadirDatosEstudiantes(estudiantes);
                    break;
                default:
                    cout << "<<< Opcion no valida >>>\n";
                    break;
                }
            }
                break;
            // Mostrar datos
            case 2:
            {
                cout << "============================= MOSTRAR DATOS ==============================\n";
                cout << " 1. Profesores\n";
                cout << " 2. Estudiantes\n";
                cout << "============================================================================\n";
                cout << " Seleccione una opcion: ";
                cin >> opcion;

                switch (opcion) {
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
            // Ordenar datos
            case 3:
            {
            
                cout << "================================= ORDENAR DATOS ===============================\n";
                cout << " 1. Profesores\n";
                cout << " 2. Estudiantes\n";
                cout << "================================================================================\n";
                cout << " Seleccione una opcion: ";
                cin >> opcion;

                switch (opcion) 
                {
                    case 1: 
                        OrdenarProfesores(profesores, 0, profesores.size() - 1);
                        cout << "Ordenamiento por Nombre completado.\n";
                        break;
                    case 2:
                        OrdenarEstudiantes(estudiantes, 0, estudiantes.size() - 1);
                        cout << "Ordenamiento por Nombre completado.\n";
                        break;  
                }
                    break;
            }
                break;
            case 4:
                // Eliminar datos
                break;
            case 5:
                // Modificar datos
                break;
            // Buscar datos
            case 6:
                cout << "================================= BUSCAR DATOS ===============================\n";
                cout << " 1. Profesores\n";
                cout << " 2. Estudiantes\n";
                cout << "================================================================================\n";
                cout << " Seleccione una opcion: ";
                cin >> opcion;

                switch (opcion) 
                {
                    case 1:
                        cout << "=============================== BUSCAR PROFESORES ===============================\n";
                        cout << " 1. Buscar por Nombre\n";
                        cout << " 2. Buscar por Apellido\n";
                        cout << " 3. Buscar especialidad\n";
                        cout << "================================================================================\n";
                        cout << " Seleccione una opcion: ";
                        cin >> opcion;

                        switch (opcion)
                        {
                            case 1:
                                break;
                            case 2:
                                break;
                            case 3:
                                break;
                            default:
                                cout << "<<< Opcion no valida >>>\n";
                                break;
                        }
                        break;
                    case 2:
                        cout << "=============================== BUSCAR ESTUDIANTES ===============================\n";
                        cout << " 1. Buscar por Nombre\n";
                        cout << " 2. Buscar por Apellido\n";
                        cout << " 3. Buscar codigo\n";
                        cout << "================================================================================\n";
                        cout << " Seleccione una opcion: ";
                        cin >> opcion;

                        switch (opcion)
                        {
                            case 1:
                                break;
                            case 2:
                                break;
                            case 3:
                                break;
                            default:
                                cout << "<<< Opcion no valida >>>\n";
                                break;
                        }
                        break;
                    default:
                        cout << "<<< Opcion no valida >>>\n";
                        break;
                }
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
