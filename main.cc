#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstdlib>  
#include <ctime>
#include <algorithm>
#include <map> 
#include <random> // libreria para barajear cartas

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
                std::cout << "Opcion no valida, intenta de nuevo." << std::endl;
                break;
        }
    } while (opcion != 5);
}


void crearBaraja(std::vector<carta> &baraja){
    std::string cartas[] = {"A", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};  /// EL 1 NO.. XD
    std::string palo[] = {"corazones", "diamantes", "espadas", "treboles"};

    for(int i = 0; i < 4; i++){
        for(int j = 0; j <= 13; j++){    /// <13  , NO <=13   
            baraja.push_back({cartas[j], palo[i]});

        }
    }
}

void escaleraReal(std::vector<carta> &escaleraReal){
    std::string cartasER[] = {"A", "K", "Q", "J", "10"};
    std::string paloER[] = {"corazones", "diamantes", "espadas", "trboles"}; /// e

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 5; j++){
            escaleraReal.push_back({cartasER[j], paloER[i]});
        }
    }
}

/* void barajearCartas(std::vector<carta>& vect){
void mostrarBaraja(std::vector<carta> &baraja){
    std::cout << " ESTA ES LA BARAJA INGLESA: " << std::endl << std::endl;
    for(int i = 0; i <= baraja.size(); i++){
        std::cout << baraja[i].carta << " de " << baraja[i].palo << std::endl << std::endl;
    }
}

void barajearCartas(std::vector<carta> &baraja){
    srand(static_cast<unsigned int>(time(0))); 
    std::random_shuffle(baraja.begin(), baraja.end());

}     /// esa es tu uncion original, la cambie x la de abajo pq random_shuffle esta obsoleto

void barajearCartas(std::vector<carta>& vect){
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(vect.begin(), vect.end(), g);


} */  ///CAMBIOS QUE ENTRARON EN CONFLICTO PERO LOS ARREGLE, QUEDAN COMENTADOS POR SI LOS OCUPAS DE NUEVO

void mostrarBaraja(std::vector<carta> &baraja){
    std::cout << " ESTA ES LA BARAJA INGLESA: " << std::endl << std::endl;
    for(size_t i = 0; i < baraja.size(); i++){
        std::cout << baraja[i].carta << " de " << baraja[i].palo << std::endl << std::endl;
    }
}

void barajearCartas(std::vector<carta>& baraja){
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(baraja.begin(), baraja.end(), g);
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
    int casosFavorables;  //=0
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

    barajearCartas(vect); 
 
 /*
   // para verificar las primeras 5 cartas 
   
    std::cout << "Primeras cinco cartas del mazo después de barajar:\n";
    for (int i = 0; i < 5; ++i) {
        mostrarCarta(vect[i]);
    }
    */



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
                std::cout << "3 - Calcular probabilidad de combinacion\n";
                std::cout << "4 - Retirarse\n";
                if (cartaRecibida) {
                    std::cout << "5 - Pasar turno\n";
                }
                std::cout << "Seleccione una opcion: ";
                std::cin >> opcion;

                switch (opcion) {
                    case 1:
                        if (manoActual.empty()) {
                            std::cout << "Aun no tienes cartas en tu mano.\n";
                        } else {
                            mostrarMano(manoActual, nombreJugador);
                        }
                        break;
                    case 2:
                        if (cartaRecibida) {
                            std::cout << "Ya has recibido una carta en este turno. No puedes recibir mas.\n";
                        } else if (manoActual.size() >= 5) {
                            std::cout << "Ya tienes 5 cartas. No puedes recibir mas.\n";
                        } else if (cartaActual < vect.size()) {
                            manoActual.push_back(vect[cartaActual++]);
                            std::cout << "Carta recibida.\n";
                            cartaRecibida = true;
                        } else {
                            std::cout << "No hay mas cartas en el mazo.\n";
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
                        std::cout << "Opcion no valida. Intente de nuevo.\n";
                        break;
                }
            }
        }

        // determinar el ganador
        if (manoJugador1.size() == 5 && manoJugador2.size() == 5) {
            int puntajeJugador1 = evaluarMano(manoJugador1);
            int puntajeJugador2 = evaluarMano(manoJugador2);

            std::cout << "\nEvaluando las manos...\n";
            if (puntajeJugador1 > puntajeJugador2) {
                std::cout << "¡El ganador es " << nombreJugador1 << " con una mejor mano!\n";
            } else if (puntajeJugador2 > puntajeJugador1) {
                std::cout << "¡El ganador es " << nombreJugador2 << " con una mejor mano!\n";
            } else {
                std::cout << "¡Es un empate!\n";
            }

            return; 
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
    std::map<std::string, int> conteoValores;
    std::map<std::string, int> conteoPalos;

    // Convertir las cartas a num
    std::vector<int> valoresNumericos;

    for (const auto& c : mano) {
        conteoValores[c.carta]++;
        conteoPalos[c.palo]++;

        // Convertir cartas especiales a num
        int valorNumerico;
        if (c.carta == "A") valorNumerico = 14;
        else if (c.carta == "K") valorNumerico = 13;
        else if (c.carta == "Q") valorNumerico = 12;
        else if (c.carta == "J") valorNumerico = 11;
        else valorNumerico = std::stoi(c.carta);

        valoresNumericos.push_back(valorNumerico);
    }

    // Ordenar num
    std::sort(valoresNumericos.begin(), valoresNumericos.end());

 
    bool tieneEscalera = false;
    if (valoresNumericos.size() >= 5) {
        for (size_t i = 0; i <= valoresNumericos.size() - 5; ++i) {
            bool escalera = true;
            for (size_t j = 1; j < 5; ++j) {
                if (valoresNumericos[i + j] != valoresNumericos[i] + j) {
                    escalera = false;
                    break;
                }
            }
            if (escalera) {
                tieneEscalera = true;
                break;
            }
        }
    }

  
    bool tieneColor = false;
    for (const auto& p : conteoPalos) {
        if (p.second >= 5) {
            tieneColor = true;
            break;
        }
    }


    bool tieneEscaleraColor = false;
    if (tieneColor) {



        std::string paloColor;
        for (const auto& p : conteoPalos) {
            if (p.second >= 5) {
                paloColor = p.first;
                break;
            }
        }


        // Obtener los valores num de las cartas del mismo palo
        std::vector<int> valoresColor;
        for (const auto& c : mano) {
            if (c.palo == paloColor) {
                int valorNumerico;
                if (c.carta == "A") valorNumerico = 14;
                else if (c.carta == "K") valorNumerico = 13;
                else if (c.carta == "Q") valorNumerico = 12;
                else if (c.carta == "J") valorNumerico = 11;
                else valorNumerico = std::stoi(c.carta);

                valoresColor.push_back(valorNumerico);
            }
        }
        std::sort(valoresColor.begin(), valoresColor.end());


        // Ver si hay una escalera en el mismo palo
        if (valoresColor.size() >= 5) {
            for (size_t i = 0; i <= valoresColor.size() - 5; ++i) {
                bool escalera = true;
                for (size_t j = 1; j < 5; ++j) {
                    if (valoresColor[i + j] != valoresColor[i] + j) {
                        escalera = false;
                        break;
                    }
                }
                if (escalera) {
                    tieneEscaleraColor = true;
                    break;
                }
            }
        }
    }

    // Otras combinaciones
    int maxRepeticiones = 0;
    int pares = 0;
    int trios = 0;
    bool poker = false;
    for (const auto& v : conteoValores) {
        if (v.second > maxRepeticiones) {
            maxRepeticiones = v.second;
        }
        if (v.second == 2) pares++;
        if (v.second == 3) trios++;
        if (v.second == 4) poker = true;
    }


    if (tieneEscaleraColor && valoresNumericos.back() == 14) return 10; // Escalera Real
    else if (tieneEscaleraColor) return 9;         // Escalera de color
    else if (poker) return 8;                      // Póker
    else if (trios == 1 && pares >= 1) return 7;   // Full House
    else if (tieneColor) return 6;                 // Color
    else if (tieneEscalera) return 5;              // Escalera
    else if (trios == 1) return 4;                 // Trío
    else if (pares >= 2) return 3;                 // Doble par
    else if (pares == 1) return 2;                 // Un par
    else return 1;                                 // Carta alta
}


/* aun no me sale...
void calcularProbabilidadFutura(const std::vector<carta>& mano, const std::vector<carta>& mazo) {
    std::map<std::string, int> conteoValores;
    for (const auto& c : mano) {
        conteoValores[c.carta]++;
    }

    int cartasFaltantesParaPar = 0;
    int cartasFaltantesParaTrio = 0;
    bool posibleEscalera = false;

    for (const auto& par : conteoValores) {
        if (par.second == 1) {
            cartasFaltantesParaPar++;
            cartasFaltantesParaTrio++;
        } else if (par.second == 2) {
            cartasFaltantesParaTrio++;
        }
    }

    // Probabilidad de obtener un Par
    double probabilidadPar = (static_cast<double>(cartasFaltantesParaPar) / mazo.size()) * 100.0;
    if (probabilidadPar > 100) probabilidadPar = 100;

    // Probabilidad de obtener un Trio
    double probabilidadTrio = (static_cast<double>(cartasFaltantesParaTrio) / mazo.size()) * 100.0;
    if (probabilidadTrio > 100) probabilidadTrio = 100;

    // Comprobacion simplificada para una escalera
    std::vector<int> valores;
    for (const auto& par : conteoValores) {
        if (par.first == "A") valores.push_back(1);
        else if (par.first == "J") valores.push_back(11);
        else if (par.first == "Q") valores.push_back(12);
        else if (par.first == "K") valores.push_back(13);
        else valores.push_back(std::stoi(par.first));
    }
    std::sort(valores.begin(), valores.end());
    for (int i = 0; i <= valores.size() - 4; i++) {
        if (valores[i + 3] == valores[i] + 3) {
            posibleEscalera = true;
            break;
        }
    }

    double probabilidadEscalera = posibleEscalera ? (4.0 / mazo.size()) * 100.0 : 0; // Simplificacion

    // Mostrar los resultados
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\nProbabilidades basadas en la mano actual:\n";
    std::cout << " - Par: " << probabilidadPar << "%\n";
    std::cout << " - Trio: " << probabilidadTrio << "%\n";
    std::cout << " - Escalera: " << probabilidadEscalera << "%\n";
}

*/