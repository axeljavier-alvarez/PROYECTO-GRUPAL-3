// REALIZADO POR GRUPO 2
// AXEL, PAULA, HENRY, ERICK
#include <iostream>
using namespace std;

// nombre del archivo no cambia en la variable
// forma dinamica no sera tama�o fijo sino puntero

const char * nombre_archivo = "archivo.dat";

struct Traductor{
	char palabras[20];
	char traduccion[35];
	char funcionalidad[250];
};

// metodo de leer
void Leer();
// metodo
void Crear();

void Actualizar();

void Borrar();

// MENU CON LAS OPCIONES ORDENADAS
main(){
	int opcion;
     char resp;
    do {
        cout << "\n\n\t\t\tMENU DE OPCIONES" << endl;
        cout << "\t\t\t----------------" << endl;
        cout << "\n\t1. Leer listado de palabras"<<endl;
        cout << "\n\t2. Agregar nueva palabra al listado"<<endl;
        cout << "\n\t3. Actualizar palabras"<<endl;
        cout << "\n\t4. Borrar palabras"<<endl;
        cout << "\n\t0. Salir"<<endl;
        cout << "\nSelecciona una opcion: ";
        cin >> opcion;
        
        switch(opcion) {
            case 1:
                Leer();
                break;
            case 2:
                Crear();
                break;
            case 3:
                Actualizar();
                break;
            case 4:
                Borrar();
                break;
            case 0:
                cout << "Ha salido del programa";
                return 0;
            default:
                cout << "Opcion invalida, ingrese de nuevo";
                break;
        }
        
        cout << "\n\nDesea continuar (S/N)? "; // Ask the user if they want to continue
        cin >> resp;

    } while (resp == 's' || resp == 'S');
    
    
    return 0;
}

void Leer(){
	system("cls");
		// rb abre fichero para lectura
	FILE * archivo = fopen(nombre_archivo, "rb");
	
	if(!archivo){
		archivo = fopen(nombre_archivo, "w+b");
	}
	
	Traductor traductor;
	// Determinan el indice o la posicion donde esta el registro
	int id=0;
	// leer lo que esta en el archivo
	fread(&traductor,sizeof(Traductor), 1, archivo);
	cout<<"___________________________"<<endl;
	cout<<"ID "<<"|"<<"    Palabra   "<<"|"<<"  Traduccion  "
	<<"|"<<"      Funcionalidad      "<<endl;
	do{
		
	    cout<<id<<"  |   "<<traductor.palabras<<"   |   "<<traductor.traduccion
		<<"    |     "<<traductor.funcionalidad<<endl;
		// ir aumentando con este operador xd
		
		// IR CAMBIANDO DE REGISTRO
		fread(&traductor,sizeof(Traductor), 1, archivo);

		id+=1;
				// feof hasta el final del registro de los archivos

	}while(feof(archivo)==0);
	
	// cerrar ese archivo de lectura xd
	fclose(archivo);
}

void Crear(){
	// abre o crear un fichero binario
	// abrir el archivo
	FILE * archivo = fopen(nombre_archivo, "a+b");
	char res;
	// declarar
	Traductor traductor;
		
	do{
		// Limpiar el flujo del archivo
		fflush(stdin);
		
		// necesitamos el get de todo
		cout<<"Ingrese la Palabra: ";
		cin.getline(traductor.palabras, 20);
		
		cout<<"Ingrese la traduccion de la palabra: ";
		cin.getline(traductor.traduccion, 35);
		
		cout<<"Ingrese su funcionalidad: ";
		cin.getline(traductor.funcionalidad, 250);
		
		// tenemos que escribir los registros
		// bandera default 1
		fwrite(&traductor,sizeof(Traductor), 1, archivo);
		
		cout<<"Desea ingresar otra palabra(s/n): ";
		cin>>res;
		
	}while(res=='s' || res=='S');
	// cerrar el archivo
	fclose(archivo);
	
	
	// mandar a llamar a leer
	Leer();
}

void Actualizar(){
	// r+b abre fichero para escritura, actualizar crea y borra
	FILE * archivo = fopen(nombre_archivo, "r+b");
	// declarar
	Traductor traductor;
	
	// preguntarle por el id
	int id=0;
	
	Leer(); 
	
	cout<<"Ingrese el ID que desea Modificar: ";
	cin>>id;
	// posicionar mi puntero fseek para posicionar puntero en una determinada posicion
	
	// BUSCAR POR EL ID
	fseek(archivo,id * sizeof(Traductor), SEEK_SET);
	
		cin.ignore();
		
		// Crear(); y actualizar();
		
		// necesitamos el get de todo
		cout<<"Ingrese la Palabra: ";
		cin.getline(traductor.palabras, 20);
		
		cout<<"Ingrese la traduccion de la palabra: ";
		cin.getline(traductor.traduccion, 35);
		
		cout<<"Ingrese su Funcionalidad: ";
		cin.getline(traductor.funcionalidad, 250);
		
		// tenemos que escribir los registros
		// bandera default 1
		fwrite(&traductor,sizeof(Traductor), 1, archivo);
	// cerrar el archivo
	fclose(archivo);	
	// mandar a llamar a leer
	Leer();
}

void Borrar(){
	const char * nombre_archivo_temp = "archivo_temp.dat";
	FILE * archivo = fopen(nombre_archivo, "rb");
	FILE * archivo_temp = fopen(nombre_archivo_temp, "w+b");
	
	Traductor traductor;
	
	int id=0, id_n=0;
	
	cout<<"Ingrese el ID a eliminar:";
	cin>>id;
	
	// recorrer el archivo principal
	while(fread(&traductor,sizeof(Traductor), 1, archivo)){
		
	// en el archivo nuevo agrego todos
	// menos el que quiero que se elimine
		if(id_n != id){
		    fwrite(&traductor,sizeof(Traductor), 1, archivo_temp);

		}
	// se incrementa
		id_n++;
	}
	
    // archivo extra para eliminar algun dato
	fclose(archivo);
	fclose(archivo_temp);
	
	// tiene los datos que quiero en el original
	archivo_temp = fopen(nombre_archivo_temp, "rb");
	// luego escribir dentro del archivo permanente
	archivo = fopen(nombre_archivo, "wb");
	
	// recorrido a archivo_temp
	while(fread(&traductor,sizeof(Traductor), 1, archivo_temp)){
		
		// escribo en mi archivo
		    fwrite(&traductor,sizeof(Traductor), 1, archivo);
}

    fclose(archivo);
	fclose(archivo_temp);
	
	
	Leer(); 

}
