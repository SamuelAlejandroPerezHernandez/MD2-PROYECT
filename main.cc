#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstdlib>  
#include <ctime>
#include <algorithm>
#include <map> 
#include <random>

struct carta{
    std::string carta;
    std::string palo;
};

std::string negro = "\033[1;30m";
std::string rojo = "\033[1;91m";
std::string verde = "\033[1;32m";
std::string amarillo = "\033[1;33m";
std::string azul = "\033[1;34m";
std::string magenta = "\033[1;35m";
std::string cyan = "\033[1;36m";
std::string reset = "\033[0m";

void crearBaraja(std::vector<carta> &baraja);
void crearEscaleraReal(std::vector<carta> &escaleraReal);
void mostrarBaraja(std::vector<carta> &baraja);
void barajearCartas(std::vector<carta> &baraja);
void probabilidadIndividual(std::vector<carta> &baraja, std::vector<carta> &manoJugador, const std::vector<carta> &barajaOriginal);
void probabilidadmazo(std::vector<carta> &baraja, std::vector<carta> &manoJugador);
void JugarSolo(std::vector<carta> &baraja, std::vector<carta> &barajaOriginal);
void menu(std::vector<carta> &baraja, std::vector<carta> &manoJugador, std::vector<carta> &barajaCopia, std::vector<carta> &barajaOriginal);

void mostrarManoDosJugadores(const std::vector<carta>& mano, const std::string& jugador);
int evaluarManoDosJugadores(const std::vector<carta>& mano);

void probabilidadIndividualDosJugadores(const std::vector<carta>& baraja, const std::vector<carta>& manoJugador);
void probabilidadMazoDosJugadores(const std::vector<carta>& baraja, const std::vector<carta>& manoJugador);
void turnoDosJugadores(const std::string& nombreJugador, std::vector<carta>& manoJugador, std::vector<carta>& baraja, bool& jugadorSeRetira);
void dosJugadores(std::vector<carta>& baraja);

int main(){
    std::vector<carta> baraja;
    std::vector<carta> manoJugador;
    std::vector<carta> barajaOriginal;
    std::vector<carta> barajaCopia;
    
    crearBaraja(baraja);
    barajaOriginal = baraja;
    barajaCopia = baraja;   
    
    menu(baraja, manoJugador, barajaCopia, barajaOriginal);

    return 0;
}

void menu(std::vector<carta> &baraja, std::vector<carta> &manoJugador, std::vector<carta> &barajaCopia, std::vector<carta> &barajaOriginal){
    int opcion;

    do {
        std::cout << "BIENVENIDO AL JUEGO DE POKER" << std::endl;
        std::cout << "LISTO PARA JUGAR?" << std::endl;
        std::cout << "1 -> Reglas del juego" << std::endl;
        std::cout << "2 -> Mostrar baraja" << std::endl;
        std::cout << "3 -> Jugar solo" << std::endl;
        std::cout << "4 -> Jugar dos jugadores" << std::endl;
        std::cout << "5 -> Salir" << std::endl;

        std::cin >> opcion;

        switch (opcion) {
            case 1:
                // Agregar función de reglas si es necesario
                break;
            case 2:
                mostrarBaraja(baraja);
                break;
            case 3:
                JugarSolo(baraja, barajaOriginal);
                break;
            case 4:
                dosJugadores(baraja);
                break;
            case 5:
                std::cout << "Saliendo del juego..." << std::endl;
                break;
            default:
                std::cout << "Opcion no valida, intenta de nuevo." << std::endl;
                break;
        }
    } while (opcion != 5);
}

void crearBaraja(std::vector<carta> &baraja){
    std::string cartas[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    std::string palo[] = {"corazones", "diamantes", "espadas", "treboles"};

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 13; j++){  
            baraja.push_back({cartas[j], palo[i]});
        }
    }
}

void mostrarBaraja(std::vector<carta> &baraja){
    std::cout << "ESTA ES LA BARAJA INGLESA:" << std::endl;
    for(size_t i = 0; i < baraja.size(); i++){
        std::cout << baraja[i].carta << " de " << baraja[i].palo << std::endl;
    }
}

void barajearCartas(std::vector<carta>& baraja){
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(baraja.begin(), baraja.end(), g);
}

void probabilidadIndividual(std::vector<carta> &baraja, std::vector<carta> &manoJugador, const std::vector<carta> &barajaOriginal){
    const std::vector<std::string> cartasValidas = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    const std::vector<std::string> palosValidos = {"corazones", "diamantes", "espadas", "treboles"};

    std::string cartaBuscada;
    std::string paloBuscado;

    while (true) {
        std::cout << "QUE CARTA DESEA BUSCAR? ";
        std::cin >> cartaBuscada;
        if (std::find(cartasValidas.begin(), cartasValidas.end(), cartaBuscada) != cartasValidas.end()) {
            break;
        } else {
            std::cout << "Carta no válida. Las cartas válidas son: ";
            for (const auto& c : cartasValidas) {
                std::cout << c << " ";
            }
            std::cout << std::endl;
        }
    }

    while (true) {
        std::cout << "QUE PALO DESEA BUSCAR? ";
        std::cin >> paloBuscado;
        if (std::find(palosValidos.begin(), palosValidos.end(), paloBuscado) != palosValidos.end()) {
            break;
        } else {
            std::cout << "Palo no válido. Los palos válidos son: ";
            for (const auto& p : palosValidos) {
                std::cout << p << " ";
            }
            std::cout << std::endl;
        }
    }

    int casosFavorables = 0;
    long double denominador = baraja.size();

    bool manoObtenida = false;
    for(size_t i = 0; i < manoJugador.size(); i++){
        if((manoJugador[i].carta == cartaBuscada) && (manoJugador[i].palo == paloBuscado)){
            manoObtenida = true;
            break;
        }
    }

    if(manoObtenida){
        std::cout << "LA CARTA " << cartaBuscada << " de " << paloBuscado << " YA ESTA EN TU MANO" << std::endl;
        return;
    }

    for(size_t i = 0; i < baraja.size(); i++){
        if((baraja[i].carta == cartaBuscada) && (baraja[i].palo == paloBuscado)){
            casosFavorables++;
        }
    }

    if(denominador <= 0){
        std::cout << "NO ES POSIBLE CALCULAR LA PROBABILIDAD" << std::endl;
        return;
    }

    long double probabilidad = static_cast<long double>(casosFavorables) / denominador;

    std::cout << "LA PROBABILIDAD DE SACAR LA CARTA " <<  cartaBuscada << " DE " << paloBuscado << " ES: " << probabilidad << std::endl;
}

void probabilidadmazo(std::vector<carta> &baraja, std::vector<carta> &manoJugador){
    int mazoBuscado;
    std::cout << "¿QUE MANO QUIERE BUSCAR?" << std::endl;
    std::cout << "1 -> PAR" << std::endl;
    std::cout << "2 -> TRIO" << std::endl;
    std::cin >> mazoBuscado;

    if (mazoBuscado == 1) {
        int cartasRestantes = baraja.size();
        int cartasEnMano = manoJugador.size();
        int turnosRestantes = 5 - cartasEnMano;

        if (turnosRestantes <= 0) {
            std::cout << "No hay turnos restantes para mejorar la mano." << std::endl;
            return;
        }

        int casosFavorables = 0;
        for (const auto& cartaMano : manoJugador) {
            for (const auto& cartaBaraja : baraja) {
                if (cartaMano.carta == cartaBaraja.carta && cartaMano.palo != cartaBaraja.palo) {
                    casosFavorables++;
                }
            }
        }

        double probabilidadPar = static_cast<double>(casosFavorables) / cartasRestantes;
        std::cout << "La probabilidad de obtener un PAR es: " << probabilidadPar << std::endl;

    } else if (mazoBuscado == 2) {
        std::cout << "Cálculo de probabilidad de TRIO no implementado aún." << std::endl;
    } else {
        std::cout << "Opción no disponible" << std::endl;
    }
}

void JugarSolo(std::vector<carta> &baraja, std::vector<carta> &barajaOriginal){
    barajearCartas(baraja);

    int opcionJugador;
    std::string nombreJugador;
    int opcionTurno;

    std::vector<carta> manoJugador;
    manoJugador.push_back(baraja[0]);
    baraja.erase(baraja.begin());

    std::cout << "INGRESE EL NOMBRE DEL JUGADOR: ";
    std::cin >> nombreJugador;
    
    while (manoJugador.size() < 5) {
        std::cout << "ES TU TURNO:" << std::endl;
        std::cout << "1 -> MENU DE OPCIONES DE ELECCIONES" << std::endl;
        std::cout << "2 -> PASAR TURNO" << std::endl;

        std::cin >> opcionJugador;

        switch(opcionJugador){
            case 1:
                do{
                    std::cout << "MENU DE JUEGO:" << std::endl;
                    std::cout << "1 - Ver tu mano" << std::endl;
                    std::cout << "2 - Ver probabilidad individual de una carta" << std::endl;
                    std::cout << "3 - Ver la probabilidad de un mazo" << std::endl;
                    std::cout << "4 - Pedir una carta mas" << std::endl;
                    std::cout << "5 - Terminar turno" << std::endl;

                    std::cin >> opcionTurno;

                    switch(opcionTurno){
                        case 1:
                            std::cout << "LA MANO DE " << nombreJugador << " ES:" << std::endl;
                            for(size_t i = 0; i < manoJugador.size(); i++){
                                if(manoJugador[i].palo == "corazones"){
                                    std::cout << rojo << manoJugador[i].carta << " de " << manoJugador[i].palo << reset << std::endl;
                                }
                                else if(manoJugador[i].palo == "diamantes"){
                                    std::cout << azul << manoJugador[i].carta << " de " << manoJugador[i].palo << reset << std::endl;
                                }
                                else if(manoJugador[i].palo == "treboles"){
                                    std::cout << verde << manoJugador[i].carta << " de " << manoJugador[i].palo << reset << std::endl;
                                }
                                else if(manoJugador[i].palo == "espadas"){
                                    std::cout << cyan << manoJugador[i].carta << " de " << manoJugador[i].palo << reset << std::endl;
                                }
                            }
                            break;
                        case 2:
                            probabilidadIndividual(baraja, manoJugador, barajaOriginal);
                            break;
                        case 3:
                            probabilidadmazo(baraja, manoJugador);
                            break;
                        case 4:
                            if(manoJugador.size() < 5){
                                manoJugador.push_back(baraja[0]);
                                baraja.erase(baraja.begin());
                                std::cout << "Carta añadida a tu mano." << std::endl;
                            }
                            else{
                                std::cout << "NO PUEDES PEDIR MAS DE UNA CARTA POR TURNO" << std::endl;
                            }
                            break;
                        case 5:
                            break;
                        default:
                            std::cout << "Opcion no valida, intenta de nuevo." << std::endl;
                            break;
                    }
                }while(opcionTurno != 5);
                break;
            case 2:
                if(manoJugador.size() < 5){
                    std::cout << "Debes tener al menos 5 cartas para pasar el turno." << std::endl;
                } else {
                    return;
                }
                break;
            default:
                std::cout << "Opcion no valida, intenta de nuevo." << std::endl;
                break;
        }
    }
}

void dosJugadores(std::vector<carta>& baraja) {
    barajearCartas(baraja);

    std::string nombreJugador1, nombreJugador2;
    std::cout << "Ingrese el nombre del Jugador 1: ";
    std::cin >> nombreJugador1;
    std::cout << "Ingrese el nombre del Jugador 2: ";
    std::cin >> nombreJugador2;

    std::vector<carta> manoJugador1;
    std::vector<carta> manoJugador2;

    bool juegoTerminado = false;
    bool jugador1SeRetira = false;
    bool jugador2SeRetira = false;

    while (!juegoTerminado) {
        turnoDosJugadores(nombreJugador1, manoJugador1, baraja, jugador1SeRetira);

        if (jugador1SeRetira) {
            std::cout << nombreJugador1 << " se retiro. " << nombreJugador2 << " gana el juego!" << std::endl;
            juegoTerminado = true;
            break;
        }

        if (manoJugador1.size() >= 5) {
            juegoTerminado = true;
            continue;
        }

        turnoDosJugadores(nombreJugador2, manoJugador2, baraja, jugador2SeRetira);

        if (jugador2SeRetira) {
            std::cout << nombreJugador2 << " se retiro. " << nombreJugador1 << " gana el juego!" << std::endl;
            juegoTerminado = true;
            break;
        }

        if (manoJugador2.size() >= 5) {
            juegoTerminado = true;
        }
    }

    if (!jugador1SeRetira && !jugador2SeRetira) {
        int puntajeJugador1 = evaluarManoDosJugadores(manoJugador1);
        int puntajeJugador2 = evaluarManoDosJugadores(manoJugador2);

        if (puntajeJugador1 > puntajeJugador2) {
            std::cout << "El ganador es " << nombreJugador1 << "!" << std::endl;
        } else if (puntajeJugador2 > puntajeJugador1) {
            std::cout << "El ganador es " << nombreJugador2 << "!" << std::endl;
        } else {
            std::cout << "Es un empate!" << std::endl;
        }
    }
}

void turnoDosJugadores(const std::string& nombreJugador, std::vector<carta>& manoJugador, std::vector<carta>& baraja, bool& jugadorSeRetira) {
    int opcionJugador;
    int opcionTurno;
    bool cartaPedida = false; 

    std::cout << "Es el turno de " << nombreJugador << std::endl;
    bool turnoTerminado = false;

    while (!turnoTerminado) {
        std::cout << "1 -> Menu de opciones" << std::endl;
        std::cout << "2 -> Retirarse" << std::endl;

        if (cartaPedida) {
            std::cout << "3 -> Pasar turno" << std::endl;
        }

        std::cin >> opcionJugador;

        if (opcionJugador == 1) {
            do {
                std::cout << "Menu de juego:" << std::endl;
                std::cout << "1 - Ver tu mano" << std::endl;
                std::cout << "2 - Ver probabilidad individual de una carta" << std::endl;
                std::cout << "3 - Ver la probabilidad de un mazo" << std::endl;
                std::cout << "4 - Pedir una carta mas" << std::endl;
                std::cout << "5 - Terminar turno" << std::endl;
                std::cin >> opcionTurno;

                switch(opcionTurno){
                    case 1:
                        mostrarManoDosJugadores(manoJugador, nombreJugador);
                        break;
                    case 2:
                        probabilidadIndividualDosJugadores(baraja, manoJugador);
                        break;
                    case 3:
                        probabilidadMazoDosJugadores(baraja, manoJugador);
                        break;
                    case 4:
                        if (manoJugador.size() < 5) {
                            manoJugador.push_back(baraja[0]);
                            baraja.erase(baraja.begin());
                            cartaPedida = true;
                            std::cout << "Carta anadida a tu mano." << std::endl;
                        } else {
                            std::cout << "No puedes tener mas de 5 cartas." << std::endl;
                        }
                        break;
                    case 5:
                        break;
                    default:
                        std::cout << "Opcion no valida, intenta de nuevo." << std::endl;
                        break;
                }
            } while(opcionTurno != 5);
            if (cartaPedida) {
                turnoTerminado = true;
            } else {
                std::cout << "Debes pedir al menos una carta antes de terminar tu turno." << std::endl;
            }
        } else if (opcionJugador == 2) {
            jugadorSeRetira = true;
            turnoTerminado = true;
        } else if (opcionJugador == 3 && cartaPedida) {
            turnoTerminado = true;
        } else {
            std::cout << "Opcion no valida, intenta de nuevo." << std::endl;
        }
    }
}

void probabilidadIndividualDosJugadores(const std::vector<carta>& baraja, const std::vector<carta>& manoJugador){
    const std::vector<std::string> cartasValidas = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    const std::vector<std::string> palosValidos = {"corazones", "diamantes", "espadas", "treboles"};

    std::string cartaBuscada;
    std::string paloBuscado;

    while (true) {
        std::cout << "QUE CARTA DESEA BUSCAR? ";
        std::cin >> cartaBuscada;
        if (std::find(cartasValidas.begin(), cartasValidas.end(), cartaBuscada) != cartasValidas.end()) {
            break;
        } else {
            std::cout << "Carta no valida. Las cartas validas son: ";
            for (const auto& c : cartasValidas) {
                std::cout << c << " ";
            }
            std::cout << std::endl;
        }
    }

    while (true) {
        std::cout << "QUE PALO DESEA BUSCAR? ";
        std::cin >> paloBuscado;
        if (std::find(palosValidos.begin(), palosValidos.end(), paloBuscado) != palosValidos.end()) {
            break;
        } else {
            std::cout << "Palo no valido. Los palos validos son: ";
            for (const auto& p : palosValidos) {
                std::cout << p << " ";
            }
            std::cout << std::endl;
        }
    }

    int casosFavorables = 0;
    long double denominador = baraja.size();

    bool manoObtenida = false;
    for(size_t i = 0; i < manoJugador.size(); i++){
        if((manoJugador[i].carta == cartaBuscada) && (manoJugador[i].palo == paloBuscado)){
            manoObtenida = true;
            break;
        }
    }

    if(manoObtenida){
        std::cout << "LA CARTA " << cartaBuscada << " de " << paloBuscado << " YA ESTA EN TU MANO" << std::endl;
        return;
    }

    for(size_t i = 0; i < baraja.size(); i++){
        if((baraja[i].carta == cartaBuscada) && (baraja[i].palo == paloBuscado)){
            casosFavorables++;
        }
    }

    if(denominador <= 0){
        std::cout << "NO ES POSIBLE CALCULAR LA PROBABILIDAD" << std::endl;
        return;
    }

    long double probabilidad = static_cast<long double>(casosFavorables) / denominador;

    std::cout << "LA PROBABILIDAD DE SACAR LA CARTA " <<  cartaBuscada << " DE " << paloBuscado << " ES: " << probabilidad << std::endl;
}

void probabilidadMazoDosJugadores(const std::vector<carta>& baraja, const std::vector<carta>& manoJugador) {
    int mazoBuscado;
    std::cout << "¿QUE MANO QUIERE BUSCAR?" << std::endl;
    std::cout << "1 -> PAR" << std::endl;
    std::cout << "2 -> TRIO" << std::endl;
    std::cout << "3 -> ESCALERA" << std::endl;
    std::cout << "4 -> COLOR" << std::endl;
    std::cin >> mazoBuscado;

    int cartasRestantes = baraja.size();
    int cartasEnMano = manoJugador.size();
    int turnosRestantes = 5 - cartasEnMano;

    if (turnosRestantes <= 0) {
        std::cout << "No hay turnos restantes para mejorar la mano." << std::endl;
        return;
    }

    if (mazoBuscado == 1) {
        int casosFavorables = 0;
        for (const auto& cartaMano : manoJugador) {
            for (const auto& cartaBaraja : baraja) {
                if (cartaMano.carta == cartaBaraja.carta && cartaMano.palo != cartaBaraja.palo) {
                    casosFavorables++;
                }
            }
        }

        double probabilidadPar = static_cast<double>(casosFavorables) / cartasRestantes;
        std::cout << "La probabilidad de obtener un PAR es: " << probabilidadPar << std::endl;

    } else if (mazoBuscado == 2) {
        // TRIO
        int casosFavorables = 0;
        for (const auto& cartaMano : manoJugador) {
            int cuentaMismaCarta = 0;
            for (const auto& c : manoJugador) {
                if (cartaMano.carta == c.carta) {
                    cuentaMismaCarta++;
                }
            }
            if (cuentaMismaCarta == 2) {
                for (const auto& cartaBaraja : baraja) {
                    if (cartaMano.carta == cartaBaraja.carta) {
                        casosFavorables++;
                    }
                }
                break;
            }
        }
        double probabilidadTrio = static_cast<double>(casosFavorables) / cartasRestantes;
        std::cout << "TRIO es: " << probabilidadTrio << std::endl;

    } else if (mazoBuscado == 3) {
        // ESCALERA
        std::cout << "Calculo de probabilidad de ESCALERA no implementado aun." << std::endl;
    } else if (mazoBuscado == 4) {
        // COLOR
        std::map<std::string, int> conteoPalos;
        for (const auto& c : manoJugador) {
            conteoPalos[c.palo]++;
        }
        int maxPalos = 0;
        std::string paloBuscado;
        for (const auto& p : conteoPalos) {
            if (p.second > maxPalos) {
                maxPalos = p.second;
                paloBuscado = p.first;
            }
        }
        int cartasNecesarias = 5 - maxPalos;
        int casosFavorables = 0;
        for (const auto& cartaBaraja : baraja) {
            if (cartaBaraja.palo == paloBuscado) {
                casosFavorables++;
            }
        }
        double probabilidadColor = static_cast<double>(casosFavorables) / cartasRestantes;
        std::cout << "La probabilidad de obtener COLOR es: " << probabilidadColor << std::endl;

    } else {
        std::cout << "Opcion no disponible" << std::endl;
    }
}


void mostrarManoDosJugadores(const std::vector<carta>& mano, const std::string& jugador) {
    std::cout << "\nMano de " << jugador << ":\n";
    for (size_t i = 0; i < mano.size(); i++) {
        if (mano[i].palo == "corazones") {
            std::cout << rojo << mano[i].carta << " de " << mano[i].palo << reset << "\n";
        } else if (mano[i].palo == "diamantes") {
            std::cout << azul << mano[i].carta << " de " << mano[i].palo << reset << "\n";
        } else if (mano[i].palo == "treboles") {
            std::cout << verde << mano[i].carta << " de " << mano[i].palo << reset << "\n";
        } else if (mano[i].palo == "espadas") {
            std::cout << cyan << mano[i].carta << " de " << mano[i].palo << reset << "\n";
        }
    }
}

int evaluarManoDosJugadores(const std::vector<carta>& mano) {
    std::map<std::string, int> conteoCartas;
    std::map<std::string, int> conteoPalos;
    for (const auto& c : mano) {
        conteoCartas[c.carta]++;
        conteoPalos[c.palo]++;
    }

    int maxRepeticiones = 0;
    for (const auto& par : conteoCartas) {
        if (par.second > maxRepeticiones) {
            maxRepeticiones = par.second;
        }
    }

    bool escalera = false;
    std::vector<int> valores;
    for (const auto& c : mano) {
        if (c.carta == "A") valores.push_back(14);
        else if (c.carta == "K") valores.push_back(13);
        else if (c.carta == "Q") valores.push_back(12);
        else if (c.carta == "J") valores.push_back(11);
        else valores.push_back(std::stoi(c.carta));
    }
    std::sort(valores.begin(), valores.end());
    escalera = true;
    for (size_t i = 1; i < valores.size(); i++) {
        if (valores[i] != valores[i - 1] + 1) {
            escalera = false;
            break;
        }
    }

    bool color = false;
    for (const auto& p : conteoPalos) {
        if (p.second == 5) {
            color = true;
            break;
        }
    }

    if (escalera && color) return 8;          // Escalera de color
    else if (maxRepeticiones == 4) return 7;  // POker
    else if (maxRepeticiones == 3 && conteoCartas.size() == 2) return 6; // Full House
    else if (color) return 5;                 // Color
    else if (escalera) return 4;              // Escalera
    else if (maxRepeticiones == 3) return 3;  // Trio
    else if (maxRepeticiones == 2 && conteoCartas.size() == 3) return 2; // Dos pares
    else if (maxRepeticiones == 2) return 1;  // Un par
    else return 0;                            // Carta alta

    //aun no estan definidos todos
}
