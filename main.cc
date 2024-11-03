#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>  
#include <ctime>
#include <algorithm>
#include <map> // para evaluar mano, modo dosjgadores

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


<<<<<<< HEAD
void menu( std::vector<carta> barajaCarta);
=======

void menu(std::vector<carta> barajaCarta, std::vector<carta> escaleraReal, std::vector<carta> escaleraColor, std::vector<carta> poker);
>>>>>>> 067d004b410e5a95fe7d005159c8d5423947c06b
void reglas();
void creditos();
void baraja(std::vector<carta>& vect);
void mostrarBaraja(std::vector<carta>& vect);
void barajearCartas(std::vector<carta>& vect);
<<<<<<< HEAD
void unSoloJugador(std::vector<carta>& vect);

void dosJugadores(std::vector<carta>& vect);
void mostrarMano(const std::vector<carta>& mano, const std::string& jugador);
int evaluarMano(const std::vector<carta>& mano);

void mostrarProbabilidadIndividual(std::vector<carta>& vect, std::vector<carta> manoJugador, std::vector<carta> manoMaquina);
void mostrarProbabilidadMazo(std::vector<carta>& vect, std::vector<carta> manoJugador, std::vector<carta> manoMaquina);
=======
void unSoloJugador(std::vector<carta>& vect, std::vector<carta> escaleraReal, std::vector<carta> escaleraColor, std::vector<carta> poker);
void dosJugadores();
void mostrarProbabilidadIndividual(std::vector<carta>& vect, std::vector<carta>& manoJugador, std::vector<carta>& manoMaquina);
void mostrarProbabilidadMazo(std::vector<carta>& vect, std::vector<carta> manoJugador, std::vector<carta> escaleraReal, std::vector<carta> escaleraColor, std::vector<carta> poker);
>>>>>>> 067d004b410e5a95fe7d005159c8d5423947c06b
void estadisticas();
void simulacion();
void apuestas();
void escaleraReal();
void escaleraColor();
void poker();



int main(){
    std::vector<carta> barajaCartas;
    std::vector<carta> auxER;
    std::vector<carta> auxEC;
    std::vector<carta> auxP;
    
    baraja(barajaCartas);
    menu(barajaCartas, auxER, auxEC, auxP);


    return 0;

}

void menu(std::vector<carta> barajaCartas, std::vector<carta> escaleraReal, std::vector<carta> escaleraColor, std::vector<carta> poker){
    int opcion;

    do{
        std::cout << "  VIENVENIDO " << std::endl << std::endl;             //Error de ortografia :/
        std::cout << " LISTO PARA JUGAR? " << std::endl << std::endl; 
        std::cout << " 1 -> reglas del juego" << std::endl;
        std::cout << " 2 -> mostrar baraja" << std::endl;
        std::cout << " 3 -> jugar solo" <<  std::endl;
        std::cout << " 4 -> Jugar dos jugadores\n";
        std::cout << " 5 -> salir" << std::endl;

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
                unSoloJugador(barajaCartas, escaleraReal, escaleraColor, poker);

                break;
             case 4:
                dosJugadores(barajaCartas);
                break;
            case 5:
                std::cout << "Saliendo del juego..." << std::endl;
                break;
            default:
                std::cout << "Opción no válida, intenta de nuevo." << std::endl;
                break;
        }
    } while(opcion != 5); // Salir del menú con la opción 3 //modificar una vez se hayan hecho todas las funciones;

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

void mostrarProbabilidadIndividual(std::vector<carta>& vect, std::vector<carta>& manoJugador, std::vector<carta>& manoMaquina){
   long double totalCartas = vect.size();
   long double totalCartasManoJugador = manoJugador.size();
   std::string cartaBuscada;
   std::string paloBuscado;
   long double casosFavorables = 0.0;
   long double probabilidadIndividual = 0.0;
   long double denominador = 0.0;

   std::cout << "Que carta deseas buscar? " << std::endl;
   std::cin >> cartaBuscada;
   std::cout << "Que palo deseas buscar? " << std::endl;
   std::cin >> paloBuscado;
   
   bool manoObtenida = false;
    for(int i = 0; i < manoJugador.size(); i++){
        if((manoJugador[i].carta == cartaBuscada) && (manoJugador[i].palo == paloBuscado)){
            manoObtenida = true;
            break;
        }
    }

    if(manoObtenida){
        std::cout << "La carta " << cartaBuscada << " de " <<  paloBuscado << " ya se encuentra en tu mano." << std::endl;
        return;
    }

    for(int i = 0; i < vect.size(); i++){
        if((vect[i].palo == paloBuscado) && (vect[i].carta == cartaBuscada)){
            casosFavorables++;
        }
    }

    denominador = (totalCartas - totalCartasManoJugador);

    if (denominador == 0) {
        std::cout << "No es posible calcular la probabilidad, no hay más cartas disponibles en la baraja." << std::endl;
        return;
    }

    probabilidadIndividual = (casosFavorables / denominador) * 100;

    std::cout << " La probabilidad de que la carta " << cartaBuscada << " del palo " <<  paloBuscado << " salga de la baraja es: " << probabilidadIndividual << " % " << std::endl << std::endl;

}

void escaleraReal(){
    std::vector<carta> escaleraReal;
    std::string cartas[] = {"10", "J", "Q", "K", "A"}; // declarar as 13 opciones de cartas; 
    std::string tipos[] = {"corazones", "diamantes", "treboles", "espadas"}; //declarar los 4 tipos de cartas;

    for(int i = 0; i < 4; i++){ // esto es pa recorrer ambos arreglos;
        for(int j = 0; j < 13; j++){
            escaleraReal.push_back({cartas[j], tipos[i]}); //esto se usa pa que se agrege cada elemento;
            
        }
    }
}

void escaleraColor(){
    std::vector<carta> escaleraColor;
    std::string cartas[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    std::string tipos[] = {"corazones", "diamantes", "treboles", "espadas"};

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 13; j++){
            escaleraColor.push_back({cartas[j], tipos[i]}); 
            
        }
    }

}

void poker(){
    std::vector<carta> poker;
    std::string cartas[] = {"K"};
    std::string tipos[] = {"corazones", "diamantes", "treboles", "espadas"};

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 13; j++){
            poker.push_back({cartas[j], tipos[i]}); 
            
        }
    }

}

void mostrarProbabilidadMazo(std::vector<carta>& vect, std::vector<carta> manoJugador, std::vector<carta> escaleraReal, std::vector<carta> escaleraColor, std::vector<carta> poker){
    long double totalCartas = vect.size();
    long double casosFavorables = 0.0;
    std::string mazo;
    int mazoBuscado;
    long double denominador = 0.0;
    long double totalCartasManoJugador = manoJugador.size();
    long double ProbabilidadMazo = 0.0;
    long double totalCartasManoJugadors = manoJugador.size();



    std::cout << " los  mazos que puede buscar son: " << std::endl << std::endl;
    std::cout << " 1 - escalera real: " << std::endl << std::endl;
    std::cout << " 2 - escalera de color: " << std::endl <<std::endl;
    std::cout << " 3 - poker: " << std::endl << std::endl;

    std::cin >> mazoBuscado;

    switch(mazoBuscado){
        case 1:
        for(int i = 0; i < escaleraReal.size(); i++){
            bool manoObtenida = false;
            for(int i = 0; i < manoJugador.size(); i++){
                if((escaleraReal[i].carta == manoJugador[i].carta) && (escaleraReal[i].palo == manoJugador[i].palo)){
                    manoObtenida = true;
                    break;
                }
            }
            if(!manoObtenida){
                casosFavorables++;
            }
        }
            break;
        case 2:
        for(int i = 0; i < escaleraColor.size(); i++){
            bool manoObtenida = false;
            for(int i = 0; i < manoJugador.size(); i++){
                if((escaleraColor[i].carta == manoJugador[i].carta) && (escaleraColor[i].palo == manoJugador[i].palo)){
                    manoObtenida = true;
                    break;
                }
            }
            if(!manoObtenida){
                casosFavorables++;
            }
        }
            break;
        case 3: 
        for(int i = 0; i < poker.size(); i++){
            bool manoObtenida = false;
            for(int i = 0; i < manoJugador.size(); i++){
                if((poker[i].carta == manoJugador[i].carta) && (poker[i].palo == manoJugador[i].palo)){
                    manoObtenida = true;
                    break;
                }
            }
            if(!manoObtenida){
                casosFavorables++;
            }
        }
            break;
        default:
            break;
    }

    denominador = (totalCartas - totalCartasManoJugadors);

    if (denominador > 0) {
        ProbabilidadMazo = (casosFavorables / denominador) * 100;
        std::cout << "La probabilidad de que armes el mazo seleccionado es: " << ProbabilidadMazo << "%" << std::endl;
    } else {
        std::cout << "No hay suficientes cartas en la baraja para calcular la probabilidad." << std::endl;
    }


}

void unSoloJugador(std::vector<carta>& vect, std::vector<carta> escaleraReal, std::vector<carta> escaleraColor, std::vector<carta> poker){
    barajearCartas(vect);
    int opcion_unJugador;

    std::vector<carta> manoJugador;
    for(int i = 0; i < 1; i++){
        manoJugador.push_back(vect[i]);// esto mete los numero del vector original que fueron generados aleatoriamente dentro del nuevo vector;
    }
    
    vect.erase(vect.begin(), vect.begin() + 1); //esto se usa pa que los numeros que se generan aleatoriamente se guanden en el vector manoJugador y se borren del vetor llamado vec o vector original;

    std::vector<carta> manoMaquina;
    for(int i = 0; i < 5; i++){
        manoMaquina.push_back(vect[i]);
    }

    vect.erase(vect.begin(), vect.begin() + 5);

    std::cout <<  " TU MANO ES: " << std::endl << std::endl;
    for(int i = 0; i < manoJugador.size(); i++){
         if(manoJugador[i].palo == "corazones"){
            std::cout << rojo << manoJugador[i].carta << " de " << manoJugador[i].palo << reset << std::endl << std::endl;
        }
        else if(manoJugador[i].palo == "diamantes"){
            std::cout << azul << manoJugador[i].carta << " de " << manoJugador[i].palo << reset << std::endl << std::endl;
        }
        else if(manoJugador[i].palo == "treboles"){
            std::cout << verde << manoJugador[i].carta << " de " << manoJugador[i].palo << reset << std::endl << std::endl;
        }
        else if(manoJugador[i].palo == "espadas"){
            std::cout << cyan << manoJugador[i].carta << " de " << manoJugador[i].palo << reset << std::endl << std::endl;
        }
    }

    // despues quitar esto, solo es para probar que no repita;
    std::cout <<  " LA MANO DE LA MAQUINA ES: " << std::endl << std::endl;
    for(int i = 0; i < manoMaquina.size(); i++){
         if(manoMaquina[i].palo == "corazones"){
            std::cout << rojo << manoMaquina[i].carta << " de " << manoMaquina[i].palo << reset << std::endl << std::endl;
        }
        else if(manoMaquina[i].palo == "diamantes"){
            std::cout << azul << manoMaquina[i].carta << " de " << manoMaquina[i].palo << reset << std::endl << std::endl;
        }
        else if(manoMaquina[i].palo == "treboles"){
            std::cout << verde << manoMaquina[i].carta << " de " << manoMaquina[i].palo << reset << std::endl << std::endl;
        }
        else if(manoMaquina[i].palo == "espadas"){
            std::cout << cyan << manoMaquina[i].carta << " de " << manoMaquina[i].palo << reset << std::endl << std::endl;
        }
    }

    do{
        std::cout << " MENU DE JUEGO: " << std::endl << std::endl;
        std::cout << " 1 - ver probabilidad individual de una carta: " << std::endl << std::endl;
        std::cout << " 2 - ver la probabilidad de un mazo: " << std::endl << std::endl;
        std::cout << " 3 - ver los mazos ganadores: " << std::endl << std::endl;
        std::cout << " 4 - pedir una carta mas: " << std::endl << std::endl;
        std::cout << " 5 - saliendo del menu de juego: " << std::endl << std::endl;

        std::cin >> opcion_unJugador;

        switch (opcion_unJugador){
        case 1:
            mostrarProbabilidadIndividual(vect, manoJugador, manoMaquina);
            break;
        case 2:
            mostrarProbabilidadMazo(vect, manoJugador, escaleraReal, escaleraColor, poker);
            break;
        case 3:

            break;
        case 4:
            if(manoJugador.size() < 5){
                for(int i = 0; i < 1; i++){
                    manoJugador.push_back(vect[i]);
                }
                vect.erase(vect.begin(), vect.begin() + 1);

                std::cout <<  " TU MANO AHORA ES: " << std::endl << std::endl;
                for(int i = 0; i < manoJugador.size(); i++){
                    if(manoJugador[i].palo == "corazones"){
                        std::cout << rojo << manoJugador[i].carta << " de " << manoJugador[i].palo << reset << std::endl << std::endl;
                    }
                    else if(manoJugador[i].palo == "diamantes"){
                        std::cout << azul << manoJugador[i].carta << " de " << manoJugador[i].palo << reset << std::endl << std::endl;
                    }
                    else if(manoJugador[i].palo == "treboles"){
                        std::cout << verde << manoJugador[i].carta << " de " << manoJugador[i].palo << reset << std::endl << std::endl;
                    }
                    else if(manoJugador[i].palo == "espadas"){
                        std::cout << cyan << manoJugador[i].carta << " de " << manoJugador[i].palo << reset << std::endl << std::endl;
                    }
                }

            }
            else{
                std::cout << "  NO PUEDES PEDIR MAS CARTAS, YA TIENES 5 " << std::endl << std::endl;

            }
            break;
        case 5:
            std::cout << " SALIENDO DEL MENU....... " << std::endl << std::endl;

            break;
        default:
            std::cout << " OPCION NO VALIDA, POR FAVOR INTRODUCIR " << std::endl << std::endl;
            break;
        }

    }while(opcion_unJugador != 5);
    
}

void dosJugadores(std::vector<carta>& vect) {
    barajearCartas(vect);

    std::vector<carta> manoJugador1;
    std::vector<carta> manoJugador2;

    // Repartir manos
    for (int i = 0; i < 5; i++) {
        manoJugador1.push_back(vect[i]);
        manoJugador2.push_back(vect[i + 5]);
    }
    vect.erase(vect.begin(), vect.begin() + 10); // esto quita las cartas

    int opcionJugador1, opcionJugador2;
    bool turnoJugador1 = true;

    do {
        std::cout << (turnoJugador1 ? "Turno de Jugador 1" : "Turno de Jugador 2") << std::endl;

        if (turnoJugador1) {
            std::cout << "Opciones para Jugador 1:\n";
            std::cout << "1 - Ver mano\n";
            std::cout << "2 - Retirarse\n";
            std::cout << "3 - Pasar turno\n";
            std::cin >> opcionJugador1;

            switch (opcionJugador1) {
                case 1:
                    mostrarMano(manoJugador1, "Jugador 1");
                    break;
                case 2:
                    std::cout << "Jugador 1 se retira. Jugador 2 gana.\n";
                    return;
                case 3:
                    turnoJugador1 = false; // Cambiar al J2
                    break;
                default:
                    std::cout << "Opción no válida. Intenta de nuevo.\n";
                    break;
            }
        } else {
            std::cout << "Opciones para Jugador 2:\n";
            std::cout << "1 - Ver mano\n";
            std::cout << "2 - Retirarse\n";
            std::cout << "3 - Pasar turno\n";
            std::cin >> opcionJugador2;

            switch (opcionJugador2) {
                case 1:
                    mostrarMano(manoJugador2, "Jugador 2");
                    break;
                case 2:
                    std::cout << "Jugador 2 se retira. Jugador 1 gana.\n";
                    return;
                case 3:
                    turnoJugador1 = true; // Cambiar al J1
                    break;
                default:
                    std::cout << "Opción no válida. Intenta de nuevo.\n";
                    break;
            }
        }
    } while (opcionJugador1 != 3 || opcionJugador2 != 3); // Ambos deben pasar turno para terminar

    // Evaluar las manos de los jugadores
    int resultadoJugador1 = evaluarMano(manoJugador1);                                                 
    int resultadoJugador2 = evaluarMano(manoJugador2);

    std::cout << "Resultado de Jugador 1: " << resultadoJugador1 << "\n";
    std::cout << "Resultado de Jugador 2: " << resultadoJugador2 << "\n";

    // Determinar al ganador
    if (resultadoJugador1 > resultadoJugador2) {
        std::cout << "Jugador 1 gana con una mejor mano!\n";
    } else if (resultadoJugador2 > resultadoJugador1) {
        std::cout << "Jugador 2 gana con una mejor mano!\n";
    } else {
        std::cout << "Empate, ambos jugadores tienen la misma mano!\n";
    }
}

void mostrarMano(const std::vector<carta>& mano, const std::string& jugador) {   // Mostrar mano, para jugado 1 y jugador 2
    std::cout << "Mano de " << jugador << ":\n";
    for (const auto& c : mano) {
        if (c.palo == "corazones") {
            std::cout << rojo << c.carta << " de " << c.palo << reset << "\n";
        } else if (c.palo == "diamantes") {
            std::cout << azul << c.carta << " de " << c.palo << reset << "\n";
        } else if (c.palo == "treboles") {
            std::cout << verde << c.carta << " de " << c.palo << reset << "\n";
        } else if (c.palo == "espadas") {
            std::cout << cyan << c.carta << " de " << c.palo << reset << "\n";
        }
    }
}


int evaluarMano(const std::vector<carta>& mano) {
    // Mapa para contar la frecuencia de cada valor de carta en la mano
    std::map<std::string, int> conteoValores;
    for (const auto& c : mano) {
        conteoValores[c.carta]++;
    }

    bool tienePar = false;
    bool tieneTrio = false;

    for (const auto& par : conteoValores) {
        if (par.second == 2) {
            tienePar = true;
        }
        if (par.second == 3) {
            tieneTrio = true;
        }
    }

    // Determinar el puntaje de la mano
    if (tieneTrio && tienePar) {
        return 6;
    } else if (tieneTrio) {
        return 3; 
    } else if (tienePar) {
        return 2; 
    }

    return 1; 
}
