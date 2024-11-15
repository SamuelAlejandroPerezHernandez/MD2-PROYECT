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
void mostrarBaraja(std::vector<carta> &baraja);
void barajearCartas(std::vector<carta> &baraja);
int evaluarMano(const std::vector<carta> &barajaOroginal);
int valorMano(const std::vector<carta> &barajaOroginal);
void determinarGanador(std::vector<carta> &manoJugador, std::vector<carta> &manoMaquina);
void probabilidadIndividual(std::vector<carta> &baraja, std::vector<carta> &manoJugador, const std::vector<carta> &barajaOriginal);
void probabilidadMazo(std::vector<carta> &manoJugador, const std::vector<carta> &barajaOriginal);
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

void barajearCartas(std::vector<carta> &baraja){
    srand(static_cast<unsigned int>(time(0))); 
    std::random_shuffle(baraja.begin(), baraja.end());
}

int evaluarMano(const std::vector<carta> &barajaOroginal){
    int valorCarta = 0;
    int valorTotal = 0;
    std::cout << " ESTO ES LO QUE VALE CADA CARTA: " << std::endl << std::endl;

    for(int i = 0; i < barajaOroginal.size(); i++){
        if(barajaOroginal[i].carta == "2"){
            valorCarta = 2;
        }
        else if(barajaOroginal[i].carta == "3"){
            valorCarta = 3;
        }
        else if(barajaOroginal[i].carta == "4"){
            valorCarta = 4;
        }
        else if(barajaOroginal[i].carta == "5"){
            valorCarta = 5;
        }
        else if(barajaOroginal[i].carta == "6"){
            valorCarta = 6;
        }
        else if(barajaOroginal[i].carta == "7"){
            valorCarta = 7;
        }
        else if(barajaOroginal[i].carta == "8"){
            valorCarta = 8;
        }
        else if(barajaOroginal[i].carta == "9"){
            valorCarta = 9;

        }else if(barajaOroginal[i].carta == "10"){
            valorCarta = 10;

        }else if(barajaOroginal[i].carta == "J"){
            valorCarta = 11;

        }else if(barajaOroginal[i].carta == "Q"){
            valorCarta = 12;

        }else if(barajaOroginal[i].carta == "K"){
            valorCarta = 13;

        }else if(barajaOroginal[i].carta == "A"){
            valorCarta = 14;
        }

        std::cout << "Carta: " << barajaOroginal[i].carta << " Valor: " << valorCarta << std::endl;
        valorTotal = valorTotal + valorCarta;

    }

    return valorTotal;

}

void determinarGanador(std::vector<carta> &manoJugador, std::vector<carta> &manoMaquina){
    int valorJugador = evaluarMano(manoJugador);
    int valorMaquina = evaluarMano(manoMaquina);
    int sumaValorJugador = 0;
    int sumaValorMaquina = 0; 

    for(int i = 0; i < 5; i++){
        sumaValorJugador = sumaValorJugador + valorJugador;
    }

    for(int i = 0; i < 5; i++){
        sumaValorMaquina = sumaValorMaquina + valorMaquina;
    }

    std::cout << " EL VALOR DE LA MANO DEL JUGADOR ES: " << valorJugador << std::endl << std::endl;
    std::cout << " EL VALOR DE LA MANO DE LA MAQUINA ES: " << valorMaquina << std::endl << std::endl;   

    if(sumaValorJugador > sumaValorMaquina){
        std::cout << "GANASTE" << std::endl << std::endl;
    }
    else if(sumaValorMaquina > sumaValorJugador){
        std::cout << "PERDISTE" << std::endl << std::endl;
    }
    else{
        std::cout << "EMPATE" << std::endl << std::endl;
    }
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

void probabilidadMazo(std::vector<carta> &manoJugador, const std::vector<carta> &barajaOriginal){
    int mazoBuscado;
    int casosFavorables = 0;
    long double totalCartas = 52;
    std::string paloJugador = "";
    long double denominadores = 0.0;
    long double  probabilidadMazo = 0.0;
    long double totalCartaJugador = manoJugador.size();
    std::vector<carta> cartaEnMano;
    int cartaDiferente = 0;
    bool tienesK = false;

    std::cout << " QUE MAZO QUIERE BUSCAR: " << std::endl << std::endl;
    std::cout << " 1 -> ESCALERA REAL: " << std::endl << std::endl;
    std::cout << " 2 -> POKER: " << std::endl << std::endl;
    std::cout << " 3 -> ESCALERA DE COLORES: " << std::endl << std::endl;

    std::cin >> mazoBuscado;

    //estos son los vectores pa la escalera real;
    std::vector<carta> escaleraRealCorazones = {
        {"A", "corazones"}, {"10", "corazones"}, {"J", "corazones"}, {"Q", "corazones"}, {"K", "corazones"}
    };

    std::vector<carta> escaleraRealTreboles = {
        {"A", "treboles"}, {"10", "treboles"}, {"J", "treboles"}, {"Q", "treboles"}, {"K", "treboles"}
    };

    std::vector<carta> escaleraRealDiamantes = {
        {"A", "diamantes"}, {"10", "diamantes"}, {"J", "diamantes"}, {"Q", "diamantes"}, {"K", "diamantes"}
    };

    std::vector<carta> escaleraRealEspadas = {
        {"A", "espadas"}, {"10", "espadas"}, {"J", "espadas"}, {"Q", "espadas"}, {"K", "espadas"}
    };

    std::vector<carta> escaleraRealSeleccionada;

    //estos son los vectores pa el mazo de poker osea tener los 4 reyes o k;
    std::vector<carta> poker = {
        {"K", "diamantes"}, {"K", "corazones"}, {"K", "treboles"}, {"K", "espadas"}
    };

    switch(mazoBuscado){
        case 1:
            std::cout << "Ingrese su palo (corazones, treboles, diamantes, espadas): " << std::endl << std::endl;
            std::cin >> paloJugador;

            if(paloJugador == "corazones"){
                escaleraRealSeleccionada = escaleraRealCorazones;

            }else if(paloJugador == "treboles"){
                escaleraRealSeleccionada = escaleraRealTreboles;

            }else if(paloJugador == "diamantes"){
                escaleraRealSeleccionada = escaleraRealDiamantes;   

            }else if(paloJugador == "espadas"){
                escaleraRealSeleccionada = escaleraRealEspadas;

            }

            for (int j = 0; j < manoJugador.size(); j++) {
                bool cartasObtenidas = false;
                for (int k = 0; k < escaleraRealSeleccionada.size(); k++) {
                    if ((manoJugador[j].carta == escaleraRealSeleccionada[k].carta) && (manoJugador[j].palo == escaleraRealSeleccionada[k].palo)){
                            std::cout << " YA TIENES UNA CARTA DEL MAZO DE LA ESCALERA REAL DENTRO DE TU MANO: " << std::endl;
                            cartaEnMano.push_back(escaleraRealSeleccionada[k]);
                            cartasObtenidas = true;
                            break; 
                        }
                    }

                    if (!cartasObtenidas){
                        std::cout << " CARTA DIFERENTE DETECTADA, LO SIENTO YA NO PUEDES HACER LA ESCALERA REAL" << std::endl << std::endl;
                        std::cout << " LA PROBABILIDAD AHORA ES 0% " << std::endl << std::endl;

                        return;
                }
            }

            for (int j = 0; j < manoJugador.size(); j++) {
                for (int k = 0; k < escaleraRealSeleccionada.size(); k++) {
                    if ((cartaEnMano[j].carta == escaleraRealSeleccionada[k].carta) && (cartaEnMano[j].palo == escaleraRealSeleccionada[k].palo)){
                        escaleraRealSeleccionada.erase(escaleraRealSeleccionada.begin() + k);
                        break; 
                    }
                }   
            }

            
                casosFavorables = escaleraRealSeleccionada.size();
            
                denominadores = (totalCartas - totalCartaJugador);

                if(denominadores <= 0){
                    std::cout << " NO SE PUEDE CALCULAR LA PROBABILIDAD: " << std::endl << std::endl;
                    break;

                }

                probabilidadMazo = static_cast<long double>(casosFavorables) / denominadores;

                std::cout << " LA PROBABILIDAD DE OBTENER EL MAZO " << mazoBuscado << " EN LOS TURNOS RESTANTE ES " << probabilidadMazo << std::endl << std::endl; 
            

        break;
        case 2:
            cartaDiferente = 0;

            for(int i = 0; i < manoJugador.size(); i++){
                bool cartaObtenida = false;
                for(int j = 0; j < poker.size(); j++){
                    if(manoJugador[i].carta == poker[j].carta && manoJugador[i].palo == poker[j].palo){
                        std::cout << " YA TIENE UNA CARTA DEL MANO DE POKER EN SU MANO: " << std::endl << std::endl;
                        cartaObtenida = true;
                        cartaEnMano.push_back(poker[j]);
                        poker.erase(poker.begin() + j);
                        break;
                    }
                }

                if(!cartaObtenida){
                        std::cout << " CARTA DIFERENTE ENCONTRADA: " << std::endl << std::endl;
                        cartaDiferente++;
                }
            }

            for(int i = 0; i < manoJugador.size(); i++){
                if(manoJugador[i].carta == "K"){
                    tienesK = true;
                    break;
                }
            }

            if (cartaDiferente > 1) {
                std::cout << "TIENES MAS DE UNA CARTA DIFERENTE A 'K' POR LO TANTO LA PROBABILIDAD DE CONSEGUIR EL MAZO DE POKER ES: " << probabilidadMazo << std::endl << std::endl;
                probabilidadMazo = 0.0;
            } else if (cartaDiferente == 1 && !tienesK){
                std::cout << "AUN NO TIENES UNA K PERO AUN HAY ESPERANZA: " << std::endl << std::endl;
            }


            casosFavorables = poker.size();

                
            denominadores = (totalCartas - totalCartaJugador);

            if(denominadores <= 0){
                std::cout << " NO SE PUEDE CALCULAR LA PROBABILIDAD: " << std::endl << std::endl;
                return;

            }

            probabilidadMazo = static_cast<long double>(casosFavorables) / denominadores;

            std::cout << " LA PROBABILIDAD DE OBTENER EL MAZO " << mazoBuscado << " EN LOS TURNOS RESTANTE ES " << probabilidadMazo << std::endl << std::endl; 

        break;
        default:

        break;
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

    std::vector<carta> manoMaquina;
    for(int i = 0; i < 5; i++){
        manoMaquina.push_back(baraja[i]);
    }
    baraja.erase(baraja.begin(), baraja.begin() + 5);

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

    std::cout << " INGRESE EL NOMBRE DEL JUGADOR: " << std::endl << std::endl;
    std::cin >> nombreJugador;
    
    while (manoJugador.size() < 5) {
        std::cout << "ES TU TURNO:" << std::endl;
        std::cout << "1 -> MENU DE OPCIONES DE ELECCIONES" << std::endl;
        std::cout << "2 -> PASAR TURNO" << std::endl;

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
                    std::cout << " 6 - ver ganador: " << std::endl << std::endl;
                    std::cout << " 7 - terminar turno: " << std::endl << std::endl;

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
                            probabilidadMazo(manoJugador, barajaOriginal);
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

                        case 6:
                            std::cout << " ESTA ES LA MANO DE LA MAQUINA: " << std::endl << std::endl;
                            for(int i = 0; i < manoJugador.size(); i++){
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

                            std::cout << " ESTA ES TU MANO: " << std::endl << std::endl;
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

                            determinarGanador(manoJugador, manoMaquina);
                            break;
                    }

                }while(opcionTurno != 7);

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
    std::cout << "3 -> COLOR" << std::endl;
    std::cout << "4 -> ESCALERA REAL" << std::endl;
    std::cout << "5 -> POKER" << std::endl;
    std::cin >> mazoBuscado;

    int cartasRestantes = baraja.size();
    int cartasEnMano = manoJugador.size();
    int turnosRestantes = 5 - cartasEnMano;

    if (turnosRestantes <= 0) {
        std::cout << "No hay turnos restantes para mejorar la mano." << std::endl;
        return;
    }

    std::map<std::string, int> conteoCartas;
    for (const auto& c : manoJugador) {
        conteoCartas[c.carta]++;
    }

    if (mazoBuscado == 1) {
        // PAR
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
        for (const auto& par : conteoCartas) {
            std::string cartaBuscada = par.first;
            int countInHand = par.second;
            int countInDeck = 0;
            for (const auto& cartaBaraja : baraja) {
                if (cartaBaraja.carta == cartaBuscada) {
                    countInDeck++;
                }
            }

            int cartasNecesarias = 3 - countInHand;
            if (cartasNecesarias <= 0) {
                std::cout << "Ya tienes un Trío de " << cartaBuscada << "." << std::endl;
                return;
            }
            if (countInDeck >= cartasNecesarias) {
                casosFavorables += countInDeck;
            }
        }

        if (casosFavorables == 0) {
            std::cout << "No es posible formar un Trío." << std::endl;
            return;
        }

        double probabilidadTrio = static_cast<double>(casosFavorables) / cartasRestantes;
        std::cout << "La probabilidad de obtener un TRIO es: " << probabilidadTrio << std::endl;

    } else if (mazoBuscado == 3) {
        // COLOR
        int casosFavorables = 0;
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
        for (const auto& cartaBaraja : baraja) {
            if (cartaBaraja.palo == paloBuscado) {
                casosFavorables++;
            }
        }
        double probabilidadColor = static_cast<double>(casosFavorables) / cartasRestantes;
        std::cout << "La probabilidad de obtener COLOR es: " << probabilidadColor << std::endl;

    } else if (mazoBuscado == 4) {
        // ESCALERA REAL
        std::string paloJugador;
        std::cout << "Ingrese su palo (corazones, treboles, diamantes, espadas): " << std::endl;
        std::cin >> paloJugador;

        std::vector<std::string> cartasNecesarias = {"10", "J", "Q", "K", "A"};
        std::vector<std::string> cartasFaltantes;
        for (const auto& carta : cartasNecesarias) {
            bool encontrada = false;
            for (const auto& cartaMano : manoJugador) {
                if (cartaMano.carta == carta && cartaMano.palo == paloJugador) {
                    encontrada = true;
                    break;
                }
            }
            if (!encontrada) {
                cartasFaltantes.push_back(carta);
            }
        }

        int casosFavorables = 0;
        for (const auto& cartaFaltante : cartasFaltantes) {
            for (const auto& cartaBaraja : baraja) {
                if (cartaBaraja.carta == cartaFaltante && cartaBaraja.palo == paloJugador) {
                    casosFavorables++;
                    break;
                }
            }
        }

        if (casosFavorables == 0) {
            std::cout << "No es posible formar una Escalera Real." << std::endl;
            return;
        }

        double probabilidadEscaleraReal = static_cast<double>(casosFavorables) / cartasRestantes;
        std::cout << "La probabilidad de obtener la ESCALERA REAL es: " << probabilidadEscaleraReal << std::endl;

    } else if (mazoBuscado == 5) {
        // POKER
        std::string cartaBuscada;
        int maxRepeticiones = 0;
        for (const auto& par : conteoCartas) {
            if (par.second > maxRepeticiones) {
                maxRepeticiones = par.second;
                cartaBuscada = par.first;
            }
        }

        if (maxRepeticiones < 1) {
            std::cout << "No tienes cartas suficientes para formar un Poker." << std::endl;
            return;
        }

        int cartasNecesarias = 4 - maxRepeticiones;
        int countInDeck = 0;
        for (const auto& cartaBaraja : baraja) {
            if (cartaBaraja.carta == cartaBuscada) {
                countInDeck++;
            }
        }

        if (countInDeck < cartasNecesarias) {
            std::cout << "No es posible formar un Poker con la carta " << cartaBuscada << "." << std::endl;
            return;
        }

        double probabilidadPoker = static_cast<double>(countInDeck) / cartasRestantes;
        std::cout << "La probabilidad de obtener un POKER con la carta " << cartaBuscada << " es: " << probabilidadPoker << std::endl;

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
}
