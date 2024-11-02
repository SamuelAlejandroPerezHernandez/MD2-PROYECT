#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>  
#include <ctime>
#include <algorithm>

struct carta{
    std::string carta;
    std::string palo;

};

//colores;
std::string negro = "\033[1;30m";
std::string rojo = "\033[1;91m";
std::string verde = "\033[1;32m";
std::string amarillo = "\033[1;33m";
std::string azul = "\033[1;34m";
std::string magenta = "\033[1;35m";
std::string cyan = "\033[1;36m";
std::string reset = "\033[0m";



void menu( std::vector<carta> barajaCarta);
void reglas();
void creditos();
void baraja(std::vector<carta>& vect);
void mostrarBaraja(std::vector<carta>& vect);
void barajearCartas(std::vector<carta>& vect);
void unSoloJugador(std::vector<carta>& vect);
void dosJugadores();
void mostrarProbabilidadIndividual(std::vector<carta>& vect, std::vector<carta> manoJugador, std::vector<carta> manoMaquina);
void mostrarProbabilidadMazo(std::vector<carta>& vect, std::vector<carta> manoJugador, std::vector<carta> manoMaquina);
void estadisticas();
void simulacion();
void apuestas();



int main(){
    std::vector<carta> barajaCartas;
    
    baraja(barajaCartas);
    menu(barajaCartas);

    return 0;

}

void menu( std::vector<carta> barajaCartas){
    int opcion;

    do{
        std::cout << "  VIENVENIDO " << std::endl << std::endl;
        std::cout << " LISTO PARA JUGAR? " << std::endl << std::endl; 
        std::cout << " 1 -> reglas del juego" << std::endl;
        std::cout << " 2 -> mostrar baraja" << std::endl;
        std::cout << " 3 -> jugar solo" <<  std::endl;
        std::cout << " 4 -> salir" << std::endl;

        std::cin >> opcion;
        
        switch(opcion){
            case 1:
                // Puedes implementar la función "reglas" más adelante
                std::cout << "Mostrando las reglas del juego..." << std::endl;
                break;
            case 2:
                mostrarBaraja(barajaCartas); // Mostrar la baraja
                break;
            case 3:
                unSoloJugador(barajaCartas);
                break;
            case 4:
                std::cout << "Saliendo del juego..." << std::endl;
                break;
            default:
                std::cout << "Opción no válida, intenta de nuevo." << std::endl;
                break;
        }
    } while(opcion != 4); // Salir del menú con la opción 3 //modificar una vez se hayan hecho todas las funciones;

}

void reglas(){
    std::cout << " Las reglas del juego de poker son: " << std::endl << std::endl;
}

void baraja(std::vector<carta>& vect){
    std::string cartas[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"}; // declarar as 13 opciones de cartas; 
    std::string tipos[] = {"corazones", "diamantes", "treboles", "espadas"}; //declarar los 4 tipos de cartas;

    for(int i = 0; i < 4; i++){ // esto es para recorrer ambos arreglos;
        for(int j = 0; j < 13; j++){
            vect.push_back({cartas[j], tipos[i]}); //esto se usa para que se agrege cada elemento;
            
        }
    }
}

void mostrarBaraja(std::vector<carta>& vect){
    std::cout << " ESTA ES LA BARAJA INGLESA CON LA QUE SE JUGARA: " << std::endl << std::endl;
    for(int i = 0; i < vect.size(); i++){         
        if(vect[i].palo == "corazones"){
            std::cout << rojo << vect[i].carta << " de " << vect[i].palo << reset << std::endl << std::endl;
        }
        else if(vect[i].palo == "diamantes"){
            std::cout << azul << vect[i].carta << " de " << vect[i].palo << reset << std::endl << std::endl;
        }
        else if(vect[i].palo == "treboles"){
            std::cout << verde << vect[i].carta << " de " << vect[i].palo << reset << std::endl << std::endl;
        }
        else if(vect[i].palo == "espadas"){
            std::cout << cyan << vect[i].carta << " de " << vect[i].palo << reset << std::endl << std::endl;
        }
    }
}

void barajearCartas(std::vector<carta>& vect){
    srand(static_cast<unsigned int>(time(0))); 
    std::random_shuffle(vect.begin(), vect.end());

}

void mostrarProbabilidadIndividual(std::vector<carta>& vect, std::vector<carta> manoJugador, std::vector<carta> manoMaquina){
    long double total_cartas = vect.size() + manoJugador.size(); // esto iguala el total de cartas al tamño de vector que contiene todas las cartas;
    double casos_favorables = 0; 
    std::string paloBuscado;
    std::string numeroCarta;
    double probaIndi = 0.0;

    std::cout << " ingrese el tipo de carta que busca: " << paloBuscado << std::endl << std::endl;
    std::cin >> paloBuscado;
    std::cout << " ingrese el numero de carta que busca: " << numeroCarta << std::endl << std::endl;
    std::cin >> numeroCarta;

    for(int i = 0; i < total_cartas; i++){
        if((vect[i].carta == numeroCarta) && (vect[i].palo == paloBuscado)){ 
            casos_favorables++;
        }
    }

    for(int i = 0; i <  manoJugador.size(); i++){
        if((manoJugador[i].carta == numeroCarta) && (manoJugador[i].palo == paloBuscado)){
            casos_favorables--;
        }
    }


    probaIndi = (casos_favorables / total_cartas - manoJugador.size());

    std::cout << " la probabilidad de que sacar la " << numeroCarta << " de " << paloBuscado <<  " es: " << std::endl << std::endl;
    std::cout << probaIndi;


}

void mostrarProbabilidadMazo(std::vector<carta>& vect, std::vector<carta> manoJugador, std::vector<carta> manoMaquina){
    long double total_cartas = vect.size();
    double casos_favorables = 0;
    std::string mazo;

    

}

void unSoloJugador(std::vector<carta>& vect){
    barajearCartas(vect);
    int opcion_unJugador;

    std::vector<carta> manoJugador;
    for(int i = 0; i < 5; i++){
        manoJugador.push_back(vect[i]);// esto mete los numero del vector original que fueron generados aleatoriamente dentro del nuevo vector;
    }
    
    vect.erase(vect.begin(), vect.begin() + 5); //esto se usa pa que los numeros que se generan aleatoriamente se guanden en el vector manoJugador y se borren del vetor llamado vec o vector original;

    std::vector<carta> manoMaquina;
    for(int i = 0; i < 5; i++){
        manoMaquina.push_back(vect[i]);
    }

    vect.erase(vect.begin(), vect.begin() + 5);

    std::cout <<  " TU MANO ES: " << std::endl << std::endl;
    for(int i = 0; i < manoJugador.size(); i++){
         if(manoJugador[i].palo == "corazones"){
            std::cout << rojo << manoJugador[i].carta << " de " << vect[i].palo << reset << std::endl << std::endl;
        }
        else if(manoJugador[i].palo == "diamantes"){
            std::cout << azul << manoJugador[i].carta << " de " << vect[i].palo << reset << std::endl << std::endl;
        }
        else if(manoJugador[i].palo == "treboles"){
            std::cout << verde << manoJugador[i].carta << " de " << vect[i].palo << reset << std::endl << std::endl;
        }
        else if(manoJugador[i].palo == "espadas"){
            std::cout << cyan << manoJugador[i].carta << " de " << vect[i].palo << reset << std::endl << std::endl;
        }
    }

    // despues quitar esto, solo es para probar que no repita;
    std::cout <<  " LA MANO DE LA MAQUINA ES: " << std::endl << std::endl;
    for(int i = 0; i < manoMaquina.size(); i++){
         if(manoMaquina[i].palo == "corazones"){
            std::cout << rojo << manoMaquina[i].carta << " de " << vect[i].palo << reset << std::endl << std::endl;
        }
        else if(manoMaquina[i].palo == "diamantes"){
            std::cout << azul << manoMaquina[i].carta << " de " << vect[i].palo << reset << std::endl << std::endl;
        }
        else if(manoMaquina[i].palo == "treboles"){
            std::cout << verde << manoMaquina[i].carta << " de " << vect[i].palo << reset << std::endl << std::endl;
        }
        else if(manoMaquina[i].palo == "espadas"){
            std::cout << cyan << manoMaquina[i].carta << " de " << vect[i].palo << reset << std::endl << std::endl;
        }
    }

    do{
        std::cout << " MENU DE JUEGO: " << std::endl << std::endl;
        std::cout << " 1 - ver probabilidad individual de una carta: " << std::endl << std::endl;
        std::cout << " 2 - ver la probabilidad de un mazo: " << std::endl << std::endl;
        std::cout << " 3 - ver los mazos ganadores: " << std::endl << std::endl;
        std::cout << " 4 - saliendo del menu de juego: " << std::endl << std::endl;

        std::cin >> opcion_unJugador;

        switch (opcion_unJugador){
        case 1:
            mostrarProbabilidadIndividual(vect, manoJugador, manoMaquina);
            break;
        
        default:
            break;
        }

    }while(opcion_unJugador != 4);
    




}







