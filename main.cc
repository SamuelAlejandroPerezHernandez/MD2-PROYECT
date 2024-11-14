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
void mostrarBaraja(std::vector<carta> &baraja);
void barajearCartas(std::vector<carta> &baraja);
int evaluarMano(const std::vector<carta> &barajaOroginal);
int valorMano(const std::vector<carta> &barajaOroginal);
void determinarGanador(std::vector<carta> &manoJugador, std::vector<carta> &manoMaquina);
void probabilidadIndividual(std::vector<carta> &baraja, std::vector<carta> &manoJugador, const std::vector<carta> &barajaOriginal);
void probabilidadMazo(std::vector<carta> &manoJugador, const std::vector<carta> &barajaOriginal);
void JugarSolo(std::vector<carta> &baraja, std::vector<carta> &barajaOriginal);
void menu(std::vector<carta> &baraja, std::vector<carta> &manoJugador, std::vector<carta> &barajaCopia, std::vector<carta> &barajaOriginal);

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

    crearBaraja(baraja);

    barajaOriginal = baraja;
    barajaCopia = baraja;   

    menu(baraja, manoJugador, barajaCopia, barajaOriginal);


    return 0;

}

void menu(std::vector<carta> &baraja, std::vector<carta> &manoJugador, std::vector<carta> &barajaCopia, std::vector<carta> &barajaOriginal){
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
                JugarSolo(baraja, barajaOriginal);

                break;
            case 4:
                
                break;
            case 5:
                std::cout << "Saliendo del juego..." << std::endl;
                break;
            default:
                std::cout << "Opcion no válida, intenta de nuevo." << std::endl;
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
    for(int i = 0; i < 1; i++){
        manoJugador.push_back(baraja[i]);
    }
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
                    std::cout << " 6 - ver ganador: " << std::endl << std::endl;
                    std::cout << " 7 - terminar turno: " << std::endl << std::endl;

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
                            probabilidadMazo(manoJugador, barajaOriginal);
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
