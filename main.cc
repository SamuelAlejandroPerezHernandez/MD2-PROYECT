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

void crearBaraja(std::vector<carta> &baraja);
void escaleraReal(std::vector<carta> &escaleraReal);
void escaleraColor(std::vector<carta> escaleraColor);
void mostrarBaraja(std::vector<carta> &baraja);
void barajearCartas(std::vector<carta> &baraja);
int evaluarMano(const std::vector<carta> &barajaOroginal);
void probabilidadIndividual(std::vector<carta> &baraja, std::vector<carta> &manoJugador, const std::vector<carta> &barajaOriginal);
void probabilidadMazo(std::vector<carta> &manoJugador, std::vector<carta> &escaleraReal);
void JugarSolo(std::vector<carta> &baraja, std::vector<carta> &barajaOriginal, std::vector<carta> &escaleraReal);
void menu(std::vector<carta> &baraja, std::vector<carta> &manoJugador, std::vector<carta> &barajaCopia, std::vector<carta> &barajaOriginal, std::vector<carta> &escaleraReal);

void reglas();
void creditos();

void dosJugadores(std::vector<carta>& vect);
void mostrarMano(const std::vector<carta>& mano, const std::string& jugador);
int evaluarManos(const std::vector<carta>& mano);
void calcularProbabilidadFutura(const std::vector<carta>& mano, const std::vector<carta>& mazo);

int main(){
    std::vector<carta> baraja;
    std::vector<carta> manoJugador;
    std::vector<carta> barajaOriginal = baraja;
    std::vector<carta> barajaCopia;
    std::vector<carta> escaleraReal;
    std::vector<carta> escaleraColor;

    crearBaraja(baraja);

    barajaOriginal = baraja;
    barajaCopia = baraja;   

    menu(baraja, manoJugador, barajaCopia, barajaOriginal, escaleraReal);


    return 0;

}

void menu(std::vector<carta> &baraja, std::vector<carta> &manoJugador, std::vector<carta> &barajaCopia, std::vector<carta> &barajaOriginal, std::vector<carta>& escaleraReal){
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
                
                break;
            case 2:
                mostrarBaraja(baraja);
                break;
            case 3:
                JugarSolo(baraja, barajaOriginal, escaleraReal);

                break;
            case 4:
                
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


void crearBaraja(std::vector<carta> &baraja){
    std::string cartas[] = {"A", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    std::string palo[] = {"corazones", "diamantes", "espadas", "treboles"};

    for(int i = 0; i < 4; i++){
        for(int j = 0; j <= 13; j++){
            baraja.push_back({cartas[j], palo[i]});

        }
    }
}

void escaleraReal(std::vector<carta> &escaleraReal){
    std::string cartasER[] = {"A", "K", "Q", "J", "10"};
    std::string paloER[] = {"corazones", "diamantes", "espadas", "trboles"};

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 5; j++){
            escaleraReal.push_back({cartasER[j], paloER[i]});
        }
    }
}

void mostrarBaraja(std::vector<carta> &baraja){
    std::cout << " ESTA ES LA BARAJA INGLESA: " << std::endl << std::endl;
    for(int i = 0; i <= baraja.size(); i++){
        std::cout << baraja[i].carta << " de " << baraja[i].palo << std::endl << std::endl;
    }
}

void barajearCartas(std::vector<carta> &baraja){
    srand(static_cast<unsigned int>(time(0))); 
    std::random_shuffle(baraja.begin(), baraja.end());

}

int evaluarMano(const std::vector<carta> &barajaOroginal){
    std::cout << " ESTO ES LO QUE VALE CADA CARTA: " << std::endl << std::endl;


}

void probabilidadIndividual(std::vector<carta> &baraja, std::vector<carta> &manoJugador, const std::vector<carta> &barajaOriginal){
    int casosFavorables = 0;
    std::string paloBuscado;
    std::string cartaBuscada;
    long double denominador = 0.0;
    long double probabilidad = 0.0;
    long double totalCartas = 52;
    long double totalCartasJugador = manoJugador.size();

    std::cout << " QUE CARTA DESEA BUSCAR? " << std::endl << std::endl;
    std::cin >> cartaBuscada;
    std::cout << " QUE PALO DESEA BUSCAR? " << std::endl << std::endl;
    std::cin >> paloBuscado;

    bool manoObtenida = false;
    for(int i = 0; i < manoJugador.size(); i++){
        if((manoJugador[i].carta == cartaBuscada) && (manoJugador[i].palo == paloBuscado)){
            manoObtenida = true;
            break;
        }
    }

    if(manoObtenida){
        std::cout << " LA CARTA " << cartaBuscada << " de " << paloBuscado << " YA ESTA EN TU MANO" << std::endl << std::endl << std::endl;
        return;
    }

    for(int i = 0; i < barajaOriginal.size(); i++){
        if((barajaOriginal[i].carta == cartaBuscada) && (barajaOriginal[i].palo == paloBuscado)){
            
            bool cartaEnMano = false;

            for(int i = 0; i < manoJugador.size(); i++){
                if((manoJugador[i].carta == cartaBuscada) && (manoJugador[i].palo == paloBuscado)){
                    cartaEnMano = true;
                    break;
                }
            }

            if(!cartaEnMano){
                casosFavorables++;
            }
        }
    }

    denominador = (totalCartas - totalCartasJugador);

    if(denominador <= 0){
        std::cout << " NO ES POSIBLE CALCULAR LA PORBABILIDAD: " << std::endl << std::endl;
        return;

    }

    probabilidad = static_cast<long double>(casosFavorables) / denominador;

    std::cout << " LA PROBABILIDAD DE SACAR LA CARTA " <<  cartaBuscada << " DE " << paloBuscado << " ES: " << probabilidad << std::endl << std::endl;

}

void probabilidadmazo(std::vector<carta> &manoJugador, std::vector<carta> &escaleraReal){
    int mazoBuscado;
    int casosFavorables;
    long double totalCartas = 52;
    long double denominadors = 0.0;
    long double  probabilidadMazo = 0.0;
    long double totalCartaJugador = manoJugador.size();

    std::cout << " QUE MAZO QUIERE BUSCAR: " << std::endl << std::endl;
    std::cout << " 1 -> ESCALERA REAL: " << std::endl << std::endl;
    std::cout << " 2 -> ESCALERA DE COLORES: " << std::endl << std::endl;
    std::cout << " 3 -> POKER: " << std::endl << std::endl;

    std::cin >> mazoBuscado;

    switch(mazoBuscado){
        case 1:       
            for(int i = 0; i < escaleraReal.size(); i++){
                bool cartaObtenida = false;
                for(int j = 0; j < manoJugador.size(); j++){
                    if((escaleraReal[i].carta == manoJugador[j].carta) && (escaleraReal[i].palo == manoJugador[j].palo)){
                        cartaObtenida = true;
                        break;
                    }
                    if(!cartaObtenida){
                        casosFavorables++;
                    }
                }
            }
            break;
        case 2:

            break;
        case 3:
            
            break;
    }

    denominadors = (totalCartas - totalCartaJugador);

    if(denominadors <= 0){
        std::cout << " NO SE PUEDE CALCULAR LA PROBABILIDAD: " << std::endl << std::endl;
        return;

    }

    probabilidadMazo = static_cast<long double>(casosFavorables) / denominadors;

    std::cout << " LA PROBABILIDAD DE OBTENER EL MAZO " << mazoBuscado << " EN LOS TURNOS RESTANTE ES " << probabilidadMazo << std::endl << std::endl; 

}

void JugarSolo(std::vector<carta> &baraja, std::vector<carta> &barajaOriginal, std::vector<carta> &escaleraReal){
    barajearCartas(baraja);

    int opcionJugador;
    std::string nombreJugador;
    int opcionTurno;

    std::vector<carta> manoJugador;
    for(int i = 0; i < 1; i++){
        manoJugador.push_back(baraja[i]);
    }
    baraja.erase(baraja.begin());

    std::vector<carta> manoCarta;
    for(int i = 0; i < 5; i++){
        manoCarta.push_back(baraja[i]);
    }
    baraja.erase(baraja.begin(), baraja.begin() + 5);

    std::cout << " INGRESE EL NOMBRE DEL JUGADOR: " << std::endl << std::endl;
    std::cin >> nombreJugador;
    
    for(int i = 0; i < 5; i++){
        std::cout << " ES TU TURNO: " << std::endl << std::endl;
        std::cout << " 1 -> MENU DE OPCIONES DE ELECCIONES: " << std::endl << std::endl;
        std::cout << " 2 -> PASAR TURNO: " << std::endl << std::endl;

        std::cin >> opcionJugador;

        switch(opcionJugador){
            case 1:
                do{
                    std::cout << " MENU DE JUEGO: " << std::endl << std::endl;
                    std::cout << " 1 - ver tu mazo: " << std::endl << std::endl;
                    std::cout << " 2 - ver probabilidad individual de una carta: " << std::endl << std::endl;
                    std::cout << " 3 - ver la probabilidad de un mazo: " << std::endl << std::endl;
                    std::cout << " 4 - ver los mazos ganadores: " << std::endl << std::endl;
                    std::cout << " 5 - pedir una carta mas: " << std::endl << std::endl;
                    std::cout << " 6 - terminar turno: " << std::endl << std::endl;

                    std::cin >> opcionTurno;

                    switch(opcionTurno){
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
                            break;
                        case 2:
                            probabilidadIndividual(baraja, manoJugador, barajaOriginal);
                            break;
                        case 3:
                            probabilidadmazo(manoJugador, escaleraReal);
                            break;
                        case 4:

                            break;
                        case 5:
                            if(manoJugador.size() < 5){
                                for(int i = 0; i < 1; i++){
                                    manoJugador.push_back(baraja[i]);
                                }
                                baraja.erase(baraja.begin(), baraja.begin() + 1);

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
                                std::cout << amarillo << " NO PUEDES PEDIR MAS DE UNA CARTA POR TURNO: " << reset << std::endl << std::endl;

                            }
                            break;
                    }

                }while(opcionTurno != 6);

                break;
            case 2:
                break;

        }
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



int evaluarManos(const std::vector<carta>& mano) {
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
