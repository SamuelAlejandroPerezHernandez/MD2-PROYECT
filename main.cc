#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstdlib>  
#include <ctime>
#include <algorithm>
#include <map> 

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


void menu(std::vector<carta> barajaCarta, std::vector<carta> escaleraReal, std::vector<carta> escaleraColor, std::vector<carta> poker);
void reglas();
void creditos();
void baraja(std::vector<carta>& vect);
void mostrarBaraja(std::vector<carta>& vect);
void barajearCartas(std::vector<carta>& vect);

void dosJugadores(std::vector<carta>& vect);
void mostrarMano(const std::vector<carta>& mano, const std::string& jugador);
int evaluarMano(const std::vector<carta>& mano);
void calcularProbabilidadFutura(const std::vector<carta>& mano, const std::vector<carta>& mazo);


void unSoloJugador(std::vector<carta>& vect, std::vector<carta> escaleraReal, std::vector<carta> escaleraColor, std::vector<carta> poker);
void mostrarProbabilidadIndividual(std::vector<carta>& vect, std::vector<carta>& manoJugador, std::vector<carta>& manoMaquina);
void mostrarProbabilidadMazo(std::vector<carta>& vect, std::vector<carta> manoJugador, std::vector<carta> escaleraReal, std::vector<carta> escaleraColor, std::vector<carta> poker);
void estadisticas();
void simulacion();
void apuestas();
void escaleraReal();
void escaleraColor();
void poker();
int evaluarMano();
void determinarGanador();



int main(){
    std::vector<carta> barajaCartas;
    std::vector<carta> auxER;
    std::vector<carta> auxEC;
    std::vector<carta> auxP;

    baraja(barajaCartas);
    menu(barajaCartas, auxER, auxEC, auxP);


    return 0;

}

void menu(std::vector<carta> barajaCartas, std::vector<carta> escaleraReal, std::vector<carta> escaleraColor, std::vector<carta> poker) {
    int opcion;

    do {
        std::cout << "  BIENVENIDO AL JUEGO DE POKER " << std::endl << std::endl;
        std::cout << " LISTO PARA JUGAR? " << std::endl << std::endl;
        std::cout << " 1 -> Reglas del juego" << std::endl;
        std::cout << " 2 -> Mostrar baraja" << std::endl;
        std::cout << " 3 -> Jugar solo" << std::endl;
        std::cout << " 4 -> Jugar dos jugadores" << std::endl;
        std::cout << " 5 -> Salir" << std::endl;

        std::cin >> opcion;

        switch (opcion) {
            case 1:
                reglas();
                break;
            case 2:
                mostrarBaraja(barajaCartas);
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
    } while (opcion != 5);
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
    std::string nombreJugador;
    int opcionTurno = 1;

    std::cout << " ingrese el nombre del jugador: " << std::endl << std::endl;
    std::cin >> nombreJugador;

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

    //quitar los comentarios para mostrar que las cartas siempre son diferentes;

    //std::cout <<  " LA MANO DE " << nombreJugador << " ES " << std::endl << std::endl;
    //for(int i = 0; i < manoJugador.size(); i++){
         //if(manoJugador[i].palo == "corazones"){
            //std::cout << rojo << manoJugador[i].carta << " de " << manoJugador[i].palo << reset << std::endl << std::endl;
        //}
        //else if(manoJugador[i].palo == "diamantes"){
            //std::cout << azul << manoJugador[i].carta << " de " << manoJugador[i].palo << reset << std::endl << std::endl;
        //}
        //else if(manoJugador[i].palo == "treboles"){
            //std::cout << verde << manoJugador[i].carta << " de " << manoJugador[i].palo << reset << std::endl << std::endl;
        //}
        //else if(manoJugador[i].palo == "espadas"){
            //std::cout << cyan << manoJugador[i].carta << " de " << manoJugador[i].palo << reset << std::endl << std::endl;
        //}
    //}

    // despues quitar esto, solo es para probar que no repita;
    //std::cout <<  " LA MANO DE LA MAQUINA ES: " << std::endl << std::endl;
    //for(int i = 0; i < manoMaquina.size(); i++){
         //if(manoMaquina[i].palo == "corazones"){
            //std::cout << rojo << manoMaquina[i].carta << " de " << manoMaquina[i].palo << reset << std::endl << std::endl;
        //}
        //else if(manoMaquina[i].palo == "diamantes"){
            //std::cout << azul << manoMaquina[i].carta << " de " << manoMaquina[i].palo << reset << std::endl << std::endl;
        //}
        //else if(manoMaquina[i].palo == "treboles"){
            //std::cout << verde << manoMaquina[i].carta << " de " << manoMaquina[i].palo << reset << std::endl << std::endl;
        //}
        //else if(manoMaquina[i].palo == "espadas"){
            //std::cout << cyan << manoMaquina[i].carta << " de " << manoMaquina[i].palo << reset << std::endl << std::endl;
        //}
    //}

    for(int i = 0; i < 5; i++){
        std::cout << " ES TURNO DE " <<  nombreJugador << std::endl << std::endl;
        std::cout << " 1 - MENU DE ELECCION: " << std::endl << std::endl;
        std::cout << " 2 - PASAR TURNO: " << std::endl << std::endl;

        std::cin >> opcionTurno;

        switch(opcionTurno){
            case 1:  //menu de eleccion
                do{
                    std::cout << " MENU DE JUEGO: " << std::endl << std::endl;
                    std::cout << " 1 - ver tu mazo: " << std::endl << std::endl;
                    std::cout << " 2 - ver probabilidad individual de una carta: " << std::endl << std::endl;
                    std::cout << " 3 - ver la probabilidad de un mazo: " << std::endl << std::endl;
                    std::cout << " 4 - ver los mazos ganadores: " << std::endl << std::endl;
                    std::cout << " 5 - pedir una carta mas: " << std::endl << std::endl;
                    std::cout << " 6 - terminar turno: " << std::endl << std::endl;

                    std::cin >> opcion_unJugador;

                    switch (opcion_unJugador){
                    case 1: 
                        std::cout <<  " LA MANO DE " << nombreJugador << " ES " << std::endl << std::endl;
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
                        break;
                    case 2:
                        mostrarProbabilidadIndividual(vect, manoJugador, manoMaquina);
                        break;
                    case 3:
                        mostrarProbabilidadMazo(vect, manoJugador, escaleraReal, escaleraColor, poker);
                        break;
                    case 4:

                        break;
                    case 5:
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
                            std::cout << amarillo << " NO PUEDES PEDIR MAS DE UNA CARTA POR TURNO: " << std::endl << std::endl;

                        }
                        break;
                    case 6:
                        std::cout << azul << " TERMINANDO TURNO....... " << std::endl << std::endl;

                        break;
                    default:
                        std::cout << rojo << " OPCION NO VALIDA, POR FAVOR INTRODUCIR " << std::endl << std::endl;
                        break;
                    }

                }while(opcion_unJugador != 6);

                break;
            case 2:
                std::cout << verde << " ACABO tU TURNO: " << std::endl << std::endl;

                break;
            default:
                std::cout << rojo << " OPCION NO VALIDA, POR FAVOR INTRODUCIR " << std::endl << std::endl;
                break;
        }

        std::cout << rojo << " LA MAQUINA YA HIZO SU ELECCION: " << std::endl << std::endl;
        std::cout << rojo << " LA MAQUINA TERMINO SU TURNO: " << std::endl << std::endl;

    }

}


void dosJugadores(std::vector<carta>& vect) {
    std::string nombreJugador1, nombreJugador2;
    std::cout << "Ingrese el nombre del Jugador 1: ";
    std::cin >> nombreJugador1;
    std::cout << "Ingrese el nombre del Jugador 2: ";
    std::cin >> nombreJugador2;
    std::vector<carta> manoJugador1;
    std::vector<carta> manoJugador2;

    int opcion;
    bool juegoTerminado = false;
    int cartaActual = 0;
    bool cartaRecibidaJugador1 = false;
    bool cartaRecibidaJugador2 = false;

    while (!juegoTerminado) {
        for (int jugador = 1; jugador <= 2 && !juegoTerminado; ++jugador) {
            std::string nombreJugador = (jugador == 1) ? nombreJugador1 : nombreJugador2;
            std::vector<carta>& manoActual = (jugador == 1) ? manoJugador1 : manoJugador2;
            bool& cartaRecibida = (jugador == 1) ? cartaRecibidaJugador1 : cartaRecibidaJugador2;

            bool turnoCompleto = false;
            while (!turnoCompleto) {
                std::cout << "\nTurno de " << nombreJugador << ":\n";
                std::cout << "1 - Ver mano\n";
                std::cout << "2 - Recibir carta\n";
                std::cout << "3 - Calcular probabilidad de combinación\n";
                std::cout << "4 - Retirarse\n";
                if (cartaRecibida) {
                    std::cout << "5 - Pasar turno\n";
                }
                std::cout << "Seleccione una opción: ";
                std::cin >> opcion;

                switch (opcion) {
                    case 1:
                        if (manoActual.empty()) {
                            std::cout << "Aún no tienes cartas en tu mano.\n";
                        } else {
                            mostrarMano(manoActual, nombreJugador);
                        }
                        break;
                    case 2:
                        if (cartaRecibida) {
                            std::cout << "Ya has recibido una carta en este turno. No puedes recibir más.\n";
                        } else if (manoActual.size() >= 5) {
                            std::cout << "Ya tienes 5 cartas. No puedes recibir más.\n";
                        } else if (cartaActual < vect.size()) {
                            manoActual.push_back(vect[cartaActual++]);
                            std::cout << "Carta recibida.\n";
                            cartaRecibida = true;
                        } else {
                            std::cout << "No hay más cartas en el mazo.\n";
                        }
                        break;
                    case 3:
                        calcularProbabilidadFutura(manoActual, vect);
                        break;
                    case 4:
                        std::cout << nombreJugador << " se retira. El otro jugador gana.\n";
                        juegoTerminado = true;
                        turnoCompleto = true;
                        break;
                    case 5:
                        if (cartaRecibida) {
                            std::cout << "Turno pasado al siguiente jugador.\n";
                            cartaRecibida = false;
                            turnoCompleto = true;
                        } else {
                            std::cout << "Debes recibir al menos una carta antes de pasar el turno.\n";
                        }
                        break;
                    default:
                        std::cout << "Opción no válida. Intente de nuevo.\n";
                        break;
                }
            }
        }
    }
}


void mostrarMano(const std::vector<carta>& mano, const std::string& jugador) {
    std::cout << "\nMano de " << jugador << ":\n";
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
    // Este mapa es para contar la frecuencia de cada valor de carta en la mano
    std::map<std::string, int> conteoValores;
    std::map<std::string, int> conteoPalos;

    for (const auto& c : mano) {
        conteoValores[c.carta]++;
        conteoPalos[c.palo]++;
    }

    bool tienePar = false;
    bool tieneTrio = false;
    bool tieneColor = false;
    bool tieneEscalera = false;

    // Para verificar pares tríos y color
    for (const auto& par : conteoValores) {
        if (par.second == 2) {
            tienePar = true;
        }
        if (par.second == 3) {
            tieneTrio = true;
        }
    }

    for (const auto& palo : conteoPalos) {
        if (palo.second >= 5) {
            tieneColor = true;
        }
    }

    // Verificar escalera (simplificado)
    std::vector<int> valores;
    for (const auto& par : conteoValores) {
        if (par.first == "A") valores.push_back(1);
        else if (par.first == "J") valores.push_back(11);
        else if (par.first == "Q") valores.push_back(12);
        else if (par.first == "K") valores.push_back(13);
        else valores.push_back(std::stoi(par.first));
    }
    std::sort(valores.begin(), valores.end());
    for (int i = 0; i <= valores.size() - 5; i++) {
        if (valores[i + 4] == valores[i] + 4) {
            tieneEscalera = true;
            break;
        }
    }

    // Determinar el puntaje de la mano
    if (tieneEscalera && tieneColor) {
        return 9; // Escalera de color
    } else if (tieneColor) {
        return 6; // Color
    } else if (tieneEscalera) {
        return 5; // Escalera
    } else if (tieneTrio && tienePar) {
        return 7; // Full House
    } else if (tieneTrio) {
        return 3; // Trío
    } else if (tienePar) {
        return 2; // Par
    }

    return 1; // Carta alta
}

void calcularProbabilidadFutura(const std::vector<carta>& mano, const std::vector<carta>& mazo) { //ESTO TIENE ERRORES AUN, DASN NUMEROS ENTEROS
    int cartasFaltantesParaPar = 0;
    std::map<std::string, int> conteoValores;

    for (const auto& c : mano) {
        conteoValores[c.carta]++;
    }

    for (const auto& par : conteoValores) {
        if (par.second == 1) {
            cartasFaltantesParaPar++;
        }
    }

    double probabilidadPar = (static_cast<double>(cartasFaltantesParaPar) / mazo.size()) * 100.0;
    if (probabilidadPar > 100) probabilidadPar = 100; // Limitar a un máximo de 100%
    std::cout << std::fixed << std::setprecision(2) << "\nProbabilidad de formar un par en el siguiente turno: " << probabilidadPar << "%\n";
}
