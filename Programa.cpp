#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <algorithm>

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

    string getNombre() const { return nombre; }
    string getApellido() const { return apellido; }
    int getEdad() const { return edad; }
    string getEspecialidad() const { return especialidad; }
    string getModalidad() const { return modalidad; }


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

    void modificarNombre(const string& nuevoNombre)
    {
        nombre = nuevoNombre;
    }

    void modificarApellido(const string& nuevoApellido)
    {
        apellido = nuevoApellido;
    }

    void modificarEdad(int nuevaEdad)
    {
        if (nuevaEdad > 0)
        {
            edad = nuevaEdad;
        }
        else
        {
            cout << "La edad no puede ser negativa.\n";
        }
    }

    void modificarEspecialidad(const string& nuevaEspecialidad)
    {
        especialidad = nuevaEspecialidad;
    }

    void modificarModalidad(const string& nuevaModalidad)
    {
        modalidad = nuevaModalidad;
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

    string getNombre() const { return nombre; }
    string getApellido() const { return apellido; }
    int getEdad() const { return edad; }
    string getcodigo() const { return codigo; }
    string getciclo() const { return ciclo; }

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

    void modificarNombre(const string& nuevoNombre)
    {
        nombre = nuevoNombre;
    }

    void modificarApellido(const string& nuevoApellido)
    {
        apellido = nuevoApellido;
    }

    void modificarEdad(int nuevaEdad)
    {
        if (nuevaEdad > 0)
        {
            edad = nuevaEdad;
        }
        else
        {
            cout << "La edad no puede ser negativa.\n";
        }
    }
    

    void modificarCodigo(const string& nuevoCodigo)
    {
        codigo = nuevoCodigo;
    }

    void modificarCiclo(const string& nuevoCiclo)
    {
        ciclo = nuevoCiclo;
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

void BusquedaBinariaEstudiantesNombre(vector<Estudiante>& estudiantes, int low, int high, string nombre)
{
    if (low > high)
    {
        cout << "\nNo se encontro ningun estudiante con ese nombre.\n";
        return;
    }

    int mid = (low + high) / 2;
    if (estudiantes[mid].getNombre() == nombre)
    {
        cout << "\nEstudiante encontrado!\n";
        estudiantes[mid].mostrar();
        return;
    }
    else if (nombre < estudiantes[mid].getNombre())
    {
        BusquedaBinariaEstudiantesNombre(estudiantes, low, mid - 1, nombre);
    }
    else
    {
        BusquedaBinariaEstudiantesNombre(estudiantes, mid + 1, high, nombre);
    }
    
}
void BusquedaBInariaProfesoresNombre(vector<Profesor>& profesores, int low, int high, string nombre)
{
    if (low > high)
    {
        cout << "\nNo se encontro ningun profesor con ese nombre.\n";
        return;
    }

    int mid = (low + high) / 2;
    if (profesores[mid].getNombre() == nombre)
    {
        cout << "\nProfesor encontrado!\n";
        profesores[mid].mostrar();
        return;
    }
    else if (nombre < profesores[mid].getNombre())
    {
        BusquedaBInariaProfesoresNombre(profesores, low, mid - 1, nombre);
    }
    else
    {
        BusquedaBInariaProfesoresNombre(profesores, mid + 1, high, nombre);
    }
}

void BusquedaBinariaEstudiantesCodigo(vector<Estudiante>& estudiantes, int low, int high, string codigo)
{
    if (low > high)
    {
        cout << "\nNo se encontro ningun estudiante con ese codigo.\n";
        return;
    }

    int mid = (low + high) / 2;
    if (estudiantes[mid].getcodigo() == codigo)
    {
        cout << "\nEstudiante encontrado!\n";
        estudiantes[mid].mostrar();
        return;
    }
    else if (codigo < estudiantes[mid].getcodigo())
    {
        BusquedaBinariaEstudiantesCodigo(estudiantes, low, mid - 1, codigo);
    }
    else
    {
        BusquedaBinariaEstudiantesCodigo(estudiantes, mid + 1, high, codigo);
    }
}

void BusquedaBinariaProfesoresEspecialidad(vector<Profesor>& profesores, int low, int high, string especialidad)
{
    if (low > high)
    {
        cout << "\nNo se encontro ningun profesor con esa especialidad.\n";
        return;
    }

    int mid = (low + high) / 2;
    if (profesores[mid].getEspecialidad() == especialidad)
    {
        cout << "\nProfesor encontrado!\n";
        profesores[mid].mostrar();
        return;
    }
    else if (especialidad < profesores[mid].getEspecialidad())
    {
        BusquedaBinariaProfesoresEspecialidad(profesores, low, mid - 1, especialidad);
    }
    else
    {
        BusquedaBinariaProfesoresEspecialidad(profesores, mid + 1, high, especialidad);
    }
}

void EliminarProfesores(vector<Profesor>& profesores, string nombre)
{
    bool encontrado = false;

    for (auto it = profesores.begin(); it != profesores.end(); it++)
    {
        if (it->getNombre() == nombre)
        {
            it = profesores.erase(it);
            encontrado = true;
            break;
        }
    }

    //Actualizar el archivo con los datos del profesor eliminado
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

void EliminarEstudiantes(vector<Estudiante>& estudiantes, string nombre)
{
    bool encontrado = false;
    for (auto it = estudiantes.begin(); it != estudiantes.end(); it++)
    {
        if (it->getNombre() == nombre)
        {
            it = estudiantes.erase(it);
            encontrado = true;
            break;
        }
    }

    //Actualizar el archivo con los datos del estudiante eliminado
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

void ModificarProfesores(vector<Profesor>& profesores, const std::string& nombreArchivo)
{
    string nombreBuscado;
    cout << "Ingrese el nombre del profesor a modificar: ";
    cin >> nombreBuscado;
    
    auto it = find_if(profesores.begin(), profesores.end(), [&nombreBuscado](const Profesor& profesor) { return profesor.getNombre() == nombreBuscado; });

    if (it == profesores.end())
    {
        cerr << "No se encontro ningun profesor con ese nombre.\n";
        return;
    }
    
    Profesor& profesor = *it;

    int opcion;
    do 
    {
        cout << " Atributo a modificar:\n";
        cout << " 1. Nombre\n";
        cout << " 2. Apellido\n";
        cout << " 3. Edad\n";
        cout << " 4. Especialidad\n";
        cout << " 5. Modalidad\n";
        cout << " 0. Salir\n";
        cout << "================================================================================\n";
        cout << " Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
            case 1:
            {
                string nuevoNombre;
                cout << "Ingrese el nuevo nombre: ";
                cin >> nuevoNombre;
                profesor.modificarNombre(nuevoNombre);
                break;
            }  
                break;
            case 2:
            {
                string nuevoApellido;
                cout << "Ingrese el nuevo apellido: ";
                cin >> nuevoApellido;
                profesor.modificarApellido(nuevoApellido);
                break;
            }
                break;
            case 3:
            {
                int nuevaEdad;
                cout << "Ingrese la nueva edad: ";
                cin >> nuevaEdad;
                profesor.modificarEdad(nuevaEdad);
                break;
            }
            case 4:
            {
                string nuevaEspecialidad;
                cout << "Ingrese la nueva especialidad: ";
                cin >> nuevaEspecialidad;
                profesor.modificarEspecialidad(nuevaEspecialidad);
                break;
            }
                break;
            case 5:
            {
                string nuevaModalidad;
                cout << "Ingrese la nueva modalidad: ";
                cin >> nuevaModalidad;
                profesor.modificarModalidad(nuevaModalidad);
                break;
            }
                break;
            case 0:
                cout << "Volviendo al menú principal.\n";
                break;
            default:
                cout << "<<< Opcion no valida >>>\n";
                break;
        }
    } while (opcion != 0);

    //Actualizar el archivo con los datos del profesor modificado
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

void ModificarEstudiantes(vector<Estudiante>& estudiantes, const std::string& nombreArchivo)
{
    string nombreBuscado;
    cout << "Ingrese el nombre del estudiante a modificar: ";
    cin >> nombreBuscado;

    auto it = find_if(estudiantes.begin(), estudiantes.end(), [&nombreBuscado](const Estudiante& estudiante) { return estudiante.getNombre() == nombreBuscado; });

    if (it == estudiantes.end())
    {
        cerr << "No se encontro ningun estudiante con ese nombre.\n";
        return;
    }

    Estudiante& estudiante = *it;

    int opcion;
    do
    {
        cout << " Atributo a modificar:\n";
        cout << " 1. Nombre\n";
        cout << " 2. Apellido\n";
        cout << " 3. Edad\n";
        cout << " 4. Codigo\n";
        cout << " 5. Ciclo\n";
        cout << " 0. Salir\n";
        cout << "================================================================================\n";
        cout << " Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
            case 1:
            {
                string nuevoNombre;
                cout << "Ingrese el nuevo nombre: ";
                cin >> nuevoNombre;
                estudiante.modificarNombre(nuevoNombre);
                break;
            }
                break;
            case 2:
            {
                string nuevoApellido;
                cout << "Ingrese el nuevo apellido: ";
                cin >> nuevoApellido;
                estudiante.modificarApellido(nuevoApellido);
                break;
            }
                break;
            case 3:
                int nuevaEdad;
                cout << "Ingrese la nueva edad: ";
                cin >> nuevaEdad;
                estudiante.modificarEdad(nuevaEdad);
                break;
            case 4:
            {
                string nuevoCodigo;
                cout << "Ingrese el nuevo codigo: ";
                cin >> nuevoCodigo;
                estudiante.modificarCodigo(nuevoCodigo);
                break;
            }
                break;
            case 5:
            {
                string nuevoCiclo;
                cout << "Ingrese el nuevo ciclo: ";
                cin >> nuevoCiclo;
                estudiante.modificarCiclo(nuevoCiclo);
                break;
            }
                break;
            case 0:
                cout << "Volviendo al menú principal.\n";
                break;
            default:
                cout << "<<< Opcion no valida >>>\n";
                break;
        }
    } while (opcion != 0);

    //Actualizar el archivo con los datos del estudiante modificado
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

                switch (opcion) 
                {
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
            // Eliminar datos
            case 4:
                cout << "================================= ELIMINAR DATOS ===============================\n";
                cout << " 1. Profesores\n";
                cout << " 2. Estudiantes\n";
                cout << "================================================================================\n";
                cout << " Seleccione una opcion: ";
                cin >> opcion;

                switch (opcion) 
                {
                    case 1:
                    {
                        cout << "Eliminar Profesores\n";
                        cout << "=================\n";
                        cout << "Ingrese el nombre del profesor a eliminar: ";
                        string nombre;
                        cin >> nombre;
                        EliminarProfesores(profesores, nombre);
                        break;
                    }
                        break;
                    case 2:
                    {
                        cout << "Eliminar Estudiantes\n";
                        cout << "=================\n";
                        cout << "Ingrese el nombre del estudiante a eliminar: ";
                        string nombre;
                        cin >> nombre;
                        EliminarEstudiantes(estudiantes, nombre);
                        break;
                    }
                        break;
                    default:
                        cout << "<<< Opcion no valida >>>\n";
                        break;
                }
                break;
            // Modificar datos
            case 5:
            {
                cout << "================================= MODIFICAR DATOS ===============================\n";
                cout << " 1. Profesores\n";
                cout << " 2. Estudiantes\n";
                cout << "================================================================================\n";
                cout << " Seleccione una opcion: ";
                cin >> opcion;

                switch (opcion)
                {
                    case 1:
                        ModificarProfesores(profesores, "profesores.txt");
                        break;
                    case 2:
                        ModificarEstudiantes(estudiantes, "estudiantes.txt");
                        break;
                    default:
                        cout << "<<< Opcion no valida >>>\n";
                        break;
                }
            }
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
                        cout << " 2. Buscar por Especialidad\n";
                        cout << "================================================================================\n";
                        cout << " Seleccione una opcion: ";
                        cin >> opcion;

                        switch (opcion)
                        {
                            case 1:
                            {
                                string nombre;
                                cout << "=============================== BUSCAR POR NOMBRE ===============================\n";
                                cout << " Nombre: ";
                                cin >> nombre;
                                BusquedaBInariaProfesoresNombre(profesores, 0, profesores.size() - 1, nombre);
                            }
                                break;
                            case 2:
                            {
                                string especialidad;
                                cout << "=============================== BUSCAR POR ESPECIALIDAD ===============================\n";
                                cout << " Especialidad: ";
                                cin >> especialidad;
                                BusquedaBinariaProfesoresEspecialidad(profesores, 0, profesores.size() - 1, especialidad);
                            }
                                break;
                            default:
                                cout << "<<< Opcion no valida >>>\n";
                                break;
                        }
                        break;
                    case 2:
                        cout << "=============================== BUSCAR ESTUDIANTES ===============================\n";
                        cout << " 1. Buscar por Nombre\n";
                        cout << " 2. Buscar por Codigo\n";
                        cout << "================================================================================\n";
                        cout << " Seleccione una opcion: ";
                        cin >> opcion;

                        switch (opcion)
                        {
                            case 1:
                            {
                                string nombre;
                                cout << "=============================== BUSCAR POR NOMBRE ===============================\n";
                                cout << " Nombre: ";
                                cin >> nombre;                                
                                BusquedaBinariaEstudiantesNombre(estudiantes, 0, estudiantes.size() - 1, nombre);
                            }
                                break;
                            case 2:
                            {
                                string codigo;
                                cout << "=============================== BUSCAR POR CODIGO ===============================\n";
                                cout << " Codigo: ";
                                cin >> codigo;
                                BusquedaBinariaEstudiantesCodigo(estudiantes, 0, estudiantes.size() - 1, codigo);
                            }
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
