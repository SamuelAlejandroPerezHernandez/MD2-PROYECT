#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstdlib>  
#include <ctime>
#include <algorithm>
#include <map> 
#include <limits>


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

void reglas();
void creditos();

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
        std::cout << azul << "  BIENVENIDO AL JUEGO DE POKER " << reset << std::endl << std::endl;
        std::cout << azul << " LISTO PARA JUGAR? " << reset << std::endl << std::endl;
        std::cout << azul << " 1 -> Reglas del juego" << reset << std::endl << std::endl;
        std::cout << azul << " 2 -> Mostrar baraja" << azul << std::endl << std::endl;
        std::cout << azul << " 3 -> Jugar solo" << reset << std::endl << std::endl;
        std::cout << azul << " 4 -> Jugar dos jugadores" << reset << std::endl << std::endl;
        std::cout << azul << " 5 -> ver creditos: " << reset << std::endl << std::endl;
        std::cout << azul  << " 6 -> Salir" << reset << std::endl << std::endl;

       std::cout << "Ingrese una opción (1-6): ";
        std::cin >> opcion;

        // Validar la entrada
        while (std::cin.fail() || opcion < 1 || opcion > 6) {
            std::cin.clear(); // Limpiar el estado de cin
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignorar el resto de la línea
            std::cout << rojo << "Opción no válida. Por favor, ingrese un número entre 1 y 6: " << reset;
            std::cin >> opcion;
        }

        switch (opcion) {
            case 1:
                reglas();
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
                creditos();
                break;
            case 6:
                std::cout << cyan << "Saliendo del juego..." << reset << std::endl << std::endl;
                break;
            default:
                std::cout << rojo << "Opcion no valida, intenta de nuevo." << std::endl << std::endl;
                break;
        }
    } while (opcion != 6);
}

void reglas(){
    std::cout << azul << "  REGLAS DEL JUEGO " << reset << std::endl << std::endl;
    std::cout << verde << "  1. El juego se juega con una baraja de 52 cartas." << std::endl << std::endl;
    std::cout << "  2. se reparten 1 - 5 cartas al jugador. " << std::endl << std::endl;
    std::cout << " 3. el jugador solo puede pedir una carta por turno: " << std::endl << std::endl;
    std::cout << " 4. el ganador se decide por la suma total del valor de las cartas en su mano: " << std::endl << std::endl;

}

void creditos(){
    std::cout << azul << "  CREDITOS " << reset << std::endl;
    std::cout << amarillo << " este juego fue hecho por: " << std::endl << std::endl;
    std::cout << rojo << " Samuel Alejandro Perez Hernandez: " << reset << std::endl << std::endl;
    std::cout << magenta << " Jaime Antonio Perez Shupan: " << reset << std::endl << std::endl;

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
    std::cout << magenta << " ESTA ES LA BARAJA INGLESA: " << reset << std::endl << std::endl;
        for(int i = 0; i < baraja.size(); i++){
        if(baraja[i].palo == "corazones"){
        std::cout << rojo << baraja[i].carta << " de " << baraja[i].palo << reset << std::endl << std::endl;
        }
        else if(baraja[i].palo == "diamantes"){
            std::cout << azul << baraja[i].carta << " de " << baraja[i].palo << reset << std::endl << std::endl;
        }
        else if(baraja[i].palo == "treboles"){
            std::cout << verde << baraja[i].carta << " de " << baraja[i].palo << reset << std::endl << std::endl;
        }
        else if(baraja[i].palo == "espadas"){
            std::cout << cyan << baraja[i].carta << " de " << baraja[i].palo << reset << std::endl << std::endl;
        }
    }
}

void barajearCartas(std::vector<carta> &baraja){
    srand(static_cast<unsigned int>(time(0))); 
    std::random_shuffle(baraja.begin(), baraja.end());
}

int evaluarMano(const std::vector<carta> &barajaOroginal){
    int valorCarta = 0;
    int valorTotal = 0;
    std::cout << verde << " ESTO ES LO QUE VALE CADA CARTA: " << reset << std::endl << std::endl;

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

        std::cout << amarillo << "Carta: " << barajaOroginal[i].carta << " Valor: " << valorCarta << reset << std::endl << std::endl;
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

    std::cout << magenta << " EL VALOR DE LA MANO DEL JUGADOR ES: " << valorJugador << reset << std::endl << std::endl;
    std::cout << azul << " EL VALOR DE LA MANO DE LA MAQUINA ES: " << valorMaquina << reset << std::endl << std::endl;   

    if(sumaValorJugador > sumaValorMaquina){
        std::cout << verde << "GANASTE" << reset << std::endl << std::endl;
    }
    else if(sumaValorMaquina > sumaValorJugador){
        std::cout << rojo << "PERDISTE" << reset << std::endl << std::endl;
    }
    else{
        std::cout << amarillo << "EMPATE" << reset << std::endl << std::endl;
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

        std::vector<std::string> cartasValidas = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
        std::vector<std::string> palosValidos = {"corazones", "diamantes", "espadas", "treboles"};

do {
    std::cout << amarillo << " QUE CARTA DESEA BUSCAR? " << reset << std::endl;
    std::cin >> cartaBuscada;
    if (std::find(cartasValidas.begin(), cartasValidas.end(), cartaBuscada) == cartasValidas.end()) {
        std::cout << rojo << "Carta no valida. Intente nuevamente." << reset << std::endl;
    }
} while (std::find(cartasValidas.begin(), cartasValidas.end(), cartaBuscada) == cartasValidas.end());

do {
    std::cout << rojo << " QUE PALO DESEA BUSCAR? " << reset << std::endl;
    std::cin >> paloBuscado;
    if (std::find(palosValidos.begin(), palosValidos.end(), paloBuscado) == palosValidos.end()) {
        std::cout << rojo << "Palo no valido. Intente nuevamente." << reset << std::endl;
    }
} while (std::find(palosValidos.begin(), palosValidos.end(), paloBuscado) == palosValidos.end());

    bool manoObtenida = false;
    for(int i = 0; i < manoJugador.size(); i++){
        if((manoJugador[i].carta == cartaBuscada) && (manoJugador[i].palo == paloBuscado)){
            manoObtenida = true;
            break;
        }
    }

    if(manoObtenida){
        std::cout << rojo << " LA CARTA " << cartaBuscada << " de " << paloBuscado << " YA ESTA EN TU MANO" << reset << std::endl << std::endl << std::endl;
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
        std::cout << rojo << " NO ES POSIBLE CALCULAR LA PORBABILIDAD: " << reset << std::endl << std::endl;
        return;

    }

    probabilidad = static_cast<long double>(casosFavorables) / denominador;

    std::cout << verde << " LA PROBABILIDAD DE SACAR LA CARTA " <<  cartaBuscada << " DE " << paloBuscado << " ES: " << probabilidad << reset << std::endl << std::endl;

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

    do {
    std::cout << cyan << " QUE MAZO QUIERE BUSCAR: " << std::endl << std::endl;
    std::cout << " 1 -> ESCALERA REAL: " << std::endl << std::endl;
    std::cout << " 2 -> POKER: " << std::endl << std::endl;
    std::cin >> mazoBuscado;

    if (std::cin.fail() || mazoBuscado < 1 || mazoBuscado > 2) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << rojo << "Opción no válida. Por favor, ingrese 1 o 2." << reset << std::endl;
    }
    } while (mazoBuscado < 1 || mazoBuscado > 2);


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
            std::cout << amarillo << "Ingrese su palo (corazones, treboles, diamantes, espadas): " << reset << std::endl << std::endl;
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
                            std::cout << amarillo << " YA TIENES UNA CARTA DEL MAZO DE LA ESCALERA REAL DENTRO DE TU MANO: " << reset << std::endl;
                            cartaEnMano.push_back(escaleraRealSeleccionada[k]);
                            cartasObtenidas = true;
                            break; 
                        }
                    }

                    if (!cartasObtenidas){
                        std::cout << rojo << " CARTA DIFERENTE DETECTADA, LO SIENTO YA NO PUEDES HACER LA ESCALERA REAL" << reset << std::endl << std::endl;
                        std::cout << rojo << " LA PROBABILIDAD AHORA ES 0% " << reset << std::endl << std::endl;

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
                    std::cout << rojo << " NO SE PUEDE CALCULAR LA PROBABILIDAD: " << reset << std::endl << std::endl;
                    break;

                }

                probabilidadMazo = static_cast<long double>(casosFavorables) / denominadores;

                std::cout << verde << " LA PROBABILIDAD DE OBTENER EL MAZO " << mazoBuscado << " EN LOS TURNOS RESTANTE ES " << probabilidadMazo << reset << std::endl << std::endl; 
            

        break;
        case 2:
            cartaDiferente = 0;

            for(int i = 0; i < manoJugador.size(); i++){
                bool cartaObtenida = false;
                for(int j = 0; j < poker.size(); j++){
                    if(manoJugador[i].carta == poker[j].carta && manoJugador[i].palo == poker[j].palo){
                        std::cout << amarillo << " YA TIENE UNA CARTA DEL MANO DE POKER EN SU MANO: " << reset << std::endl << std::endl;
                        cartaObtenida = true;
                        cartaEnMano.push_back(poker[j]);
                        poker.erase(poker.begin() + j);
                        break;
                    }
                }

                if(!cartaObtenida){
                        std::cout << rojo << " CARTA DIFERENTE ENCONTRADA: " << reset << std::endl << std::endl;
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
                std::cout << amarillo << " TIENES MAS DE UNA CARTA DIFERENTE A 'K' POR LO TANTO LA PROBABILIDAD DE CONSEGUIR EL MAZO DE POKER ES: " << probabilidadMazo << reset << std::endl << std::endl;
                probabilidadMazo = 0.0;
            } else if (cartaDiferente == 1 && !tienesK){
                std::cout << amarillo << " AUN NO TIENES UNA K PERO AUN HAY ESPERANZA: " << reset << std::endl << std::endl;
            }


            if(cartaDiferente <= 1){
                casosFavorables = poker.size();   
                denominadores = (totalCartas - totalCartaJugador);
            
                if(denominadores <= 0){
                std::cout << rojo << " NO SE PUEDE CALCULAR LA PROBABILIDAD: " << reset << std::endl << std::endl;
                return;

                }

                probabilidadMazo = static_cast<long double>(casosFavorables) / denominadores;

                std::cout << verde << " LA PROBABILIDAD DE OBTENER EL MAZO " << mazoBuscado << " EN LOS TURNOS RESTANTE ES " << probabilidadMazo << reset << std::endl << std::endl; 
            }
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

    std::cout << cyan << " INGRESE EL NOMBRE DEL JUGADOR: " << reset << std::endl << std::endl;
    std::cin >> nombreJugador;
    
    for(int i = 0; i < 5; i++){
        bool haPedidoCarta = false;
        std::cout << azul << " ES TU TURNO: " << reset << std::endl << std::endl;
        std::cout << verde << " 1 -> MENU DE OPCIONES DE ELECCIONES: " << reset << std::endl << std::endl;
        std::cout << amarillo << " 2 -> PASAR TURNO: " << reset << std::endl << std::endl;
        std::cout << "Ingrese una opcion (1-2): ";
        std::cin >> opcionJugador;

        // Validar la entrada
        while (std::cin.fail() || opcionJugador < 1 || opcionJugador > 2) {
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          std::cout << rojo << "Opción no válida. Por favor, ingrese 1 o 2: " << reset;
          std::cin >> opcionJugador;
                }


        switch(opcionJugador){

            case 1:
                do{
                    std::cout << verde << " MENU DE JUEGO: " << std::endl << std::endl;
                    std::cout << " 1 - ver tu mazo: " << std::endl << std::endl;
                    std::cout << " 2 - ver probabilidad individual de una carta: " << std::endl << std::endl;
                    std::cout << " 3 - ver la probabilidad de un mazo: " << std::endl << std::endl;
                    std::cout << " 4 - ver los mazos ganadores: " << std::endl << std::endl;
                    std::cout << " 5 - pedir una carta mas: " << std::endl << std::endl;
                    std::cout << " 6 - ver ganador: " << std::endl << std::endl;
                    std::cout << " 7 - terminar turno: " << reset << std::endl << std::endl;

                     std::cout << "Ingrese una opción (1-7): ";
                     std::cin >> opcionTurno;

                   while (std::cin.fail() || opcionTurno < 1 || opcionTurno > 7) {
                     std::cin.clear();
                     std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                     std::cout << rojo << "Opcion no valida. Por favor, ingrese un numero entre 1 y 7: " << reset;
                     std::cin >> opcionTurno;
                            }

                    switch(opcionTurno){
                        case 1:
                            std::cout << magenta << " LA MANO DE " << nombreJugador << " ES " << reset << std::endl << std::endl;
                            for(int i = 0; i < manoJugador.size(); i++){
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
                            std::cout << magenta << " MAZOS GANADORES: " << reset << std::endl << std::endl;

                            std::cout << rojo << " ESCALERA REAL: " << reset << std::endl;
                            std::cout << rojo << " A de corazones, K de corazones, Q de corazones, J de corazones, 10 de corazones" << reset << std::endl << std::endl;
                            
                            std::cout << azul << " POKER DE REYES: " << reset << std::endl;
                            std::cout << azul << " Rey de corazones, Rey de diamantes, Rey de tréboles, Rey de espadas, 7 de tréboles" << reset << std::endl << std::endl;
                            break;
                        case 5:
                            if(!haPedidoCarta){
                                if(manoJugador.size() < 5){
                                    for(int i = 0; i < 1; i++){
                                        manoJugador.push_back(baraja[i]);
                                    }
                                    baraja.erase(baraja.begin(), baraja.begin() + 1);

                                    std::cout << azul <<  " TU MANO AHORA ES: " << reset << std::endl << std::endl;
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

                                    haPedidoCarta = true;

                                }
                                else{
                                    std::cout << amarillo << " NO PUEDES PEDIR MAS DE 5 CARTAS: " << reset << std::endl << std::endl;
                                }
                            }
                            else{
                                std::cout << rojo << " NO PUEDES PEDIR MAS DE UNA CARTA POR TURNO: " << reset << std::endl << std::endl;
                            }
                            break;
                        case 6:
                            std::cout << rojo << " ESTA ES LA MANO DE LA MAQUINA: " << reset << std::endl << std::endl;
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

                            std::cout << azul << " ESTA ES TU MANO: " << reset << std::endl << std::endl;
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
    // Barajea las cartas antes de comenzar el juego
    barajearCartas(baraja);

    std::string nombreJugador1, nombreJugador2;
    std::cout << "Ingrese el nombre del Jugador 1: ";
    std::cin >> nombreJugador1;
    std::cout << "Ingrese el nombre del Jugador 2: ";
    std::cin >> nombreJugador2;

    // Vectores para las manos de cada jugador
    std::vector<carta> manoJugador1;
    std::vector<carta> manoJugador2;

    // Reparte una carta a cada jugador desde el final de la baraja
    manoJugador1.push_back(baraja.back());
    baraja.pop_back();

    manoJugador2.push_back(baraja.back());
    baraja.pop_back();

    // Variables para controlar el estado del juego
    bool juegoTerminado = false;
    bool jugador1SeRetira = false;
    bool jugador2SeRetira = false;

    // Bucle principal del juego
    while (!juegoTerminado) {
        turnoDosJugadores(nombreJugador1, manoJugador1, baraja, jugador1SeRetira);

        // Jugador 1 se retiro
        if (jugador1SeRetira) {
            std::cout << nombreJugador1 << " se retiro. " << nombreJugador2 << " gana el juego!" << std::endl;
            juegoTerminado = true;
            break;
        }

        // Jugador 1 tiene 5 o mas cartas
        if (manoJugador1.size() >= 5) {
            juegoTerminado = true;
            continue;
        }

        // Turno del Jugador 2
        turnoDosJugadores(nombreJugador2, manoJugador2, baraja, jugador2SeRetira);

        // Jugador 2 se retiro
        if (jugador2SeRetira) {
            std::cout << nombreJugador2 << " se retiro. " << nombreJugador1 << " gana el juego!" << std::endl;
            juegoTerminado = true;
            break;
        }

        if (manoJugador2.size() >= 5) {
            juegoTerminado = true;
        }
    }

    // Si ninguno de los jugadores se retiro, determina el ganador
    if (!jugador1SeRetira && !jugador2SeRetira) {


        // Muestra las manos finales de ambos jugadores
        std::cout << "\nMano final de " << nombreJugador1 << ":" << std::endl;
        mostrarManoDosJugadores(manoJugador1, nombreJugador1);

        std::cout << "\nMano final de " << nombreJugador2 << ":" << std::endl;
        mostrarManoDosJugadores(manoJugador2, nombreJugador2);

        // Evalua el valor total de las manos de ambos jugadores
        int valorJugador1 = evaluarManoDosJugadores(manoJugador1);
        int valorJugador2 = evaluarManoDosJugadores(manoJugador2);

        std::cout << "\nEl valor de la mano de " << nombreJugador1 << " es: " << valorJugador1 << std::endl;
        std::cout << "El valor de la mano de " << nombreJugador2 << " es: " << valorJugador2 << std::endl;


        // Determina el ganador basado en el valor de las manos
        if (valorJugador1 > valorJugador2) {
            std::cout << "\nEl ganador es " << nombreJugador1 << "!" << std::endl;
        } else if (valorJugador2 > valorJugador1) {
            std::cout << "\nEl ganador es " << nombreJugador2 << "!" << std::endl;
        } else {
            std::cout << "\nEs un empate!" << std::endl;
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

        std::cout << "Ingrese una opcion: ";
        std::cin >> opcionJugador;

        // Validacion de la entrada dependiendo de si puede pasar turno o no
        if (cartaPedida) {
            while (std::cin.fail() || opcionJugador < 1 || opcionJugador > 3) {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout << "Opcion no valida. Por favor, ingrese un numero entre 1 y 3: ";
                std::cin >> opcionJugador;
            }
        } else {
            while (std::cin.fail() || opcionJugador < 1 || opcionJugador > 2) {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout << "Opcion no valida. Por favor, ingrese un numero entre 1 y 2: ";
                std::cin >> opcionJugador;
            }
        }

        if (opcionJugador == 1) {
        
            do {
                std::cout << "Menu de juego:" << std::endl;
                std::cout << "1 - Ver tu mano" << std::endl;
                std::cout << "2 - Ver probabilidad individual de una carta" << std::endl;
                std::cout << "3 - Ver la probabilidad de una mano" << std::endl;
                std::cout << "4 - Pedir una carta mas" << std::endl;
                std::cout << "5 - Salir del menu de opciones" << std::endl;
                std::cout << "Ingrese una opcion (1-5): ";
                std::cin >> opcionTurno;

                
                while (std::cin.fail() || opcionTurno < 1 || opcionTurno > 5) {
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    std::cout << "Opcion no valida. Por favor, ingrese un numero entre 1 y 5: ";
                    std::cin >> opcionTurno;
                }

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
                     
                        if (!cartaPedida) {
                            if (manoJugador.size() < 5) {
                                if (!baraja.empty()) {
                                
                                    manoJugador.push_back(baraja.back());
                                    baraja.pop_back();
                                    cartaPedida = true;
                                    std::cout << "Carta anadida a tu mano." << std::endl;
                                } else {
                                    std::cout << "No hay mas cartas en el mazo." << std::endl;
                                }
                            } else {
                                std::cout << "No puedes tener mas de 5 cartas." << std::endl;
                            }
                        } else {
                            std::cout << "Ya has pedido una carta en este turno." << std::endl;
                        }
                        break;
                    case 5:
                        // Salir del menu de opciones
                        break;
                    default:
                        std::cout << "Opcion no valida, intenta de nuevo." << std::endl;
                        break;
                }
            } while (opcionTurno != 5);
        } else if (opcionJugador == 2) {
            jugadorSeRetira = true;
            turnoTerminado = true;
        } else if (opcionJugador == 3 && cartaPedida) {
   
            turnoTerminado = true;
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
    int casosFavorables = 0;
    long double totalCartas = 52; 
    std::string paloJugador = "";
    long double denominador = 0.0;
    long double probabilidadMazo = 0.0;
    long double totalCartasJugador = manoJugador.size();
    std::vector<carta> cartaEnMano;
    int cartaDiferente = 0;

    do {
        std::cout << cyan << "QUE MANO QUIERES BUSCAR?" << reset << std::endl << std::endl;
        std::cout << "1 -> ESCALERA REAL" << std::endl;
        std::cout << "2 -> POKER" << std::endl;
        std::cin >> mazoBuscado;

        if (std::cin.fail() || mazoBuscado < 1 || mazoBuscado > 2) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << rojo << "Opcion no valida. Por favor, ingresa 1 o 2." << reset << std::endl;
        }
    } while (mazoBuscado < 1 || mazoBuscado > 2);

    // Definicion de las posibles escaleras reales por palo
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

    // Definicion del poker de reyes
    std::vector<carta> poker = {
        {"K", "corazones"}, {"K", "diamantes"}, {"K", "treboles"}, {"K", "espadas"}
    };

    switch (mazoBuscado) {
        case 1:
            // El jugador elige el palo para la Escalera Real
            std::cout << amarillo << "Ingresa el palo (corazones, diamantes, treboles, espadas): " << reset;
            std::cin >> paloJugador;

            // Selecciona la Escalera Real correspondiente al palo elegido
            if (paloJugador == "corazones") {
                escaleraRealSeleccionada = escaleraRealCorazones;
            } else if (paloJugador == "diamantes") {
                escaleraRealSeleccionada = escaleraRealDiamantes;
            } else if (paloJugador == "treboles") {
                escaleraRealSeleccionada = escaleraRealTreboles;
            } else if (paloJugador == "espadas") {
                escaleraRealSeleccionada = escaleraRealEspadas;
            } else {
                std::cout << rojo << "Palo no valido." << reset << std::endl;
                return;
            }

            for (size_t j = 0; j < manoJugador.size(); j++) {
                bool cartaEncontrada = false;
                for (size_t k = 0; k < escaleraRealSeleccionada.size(); k++) {
                    if (manoJugador[j].carta == escaleraRealSeleccionada[k].carta && manoJugador[j].palo == escaleraRealSeleccionada[k].palo) {
                        std::cout << amarillo << "Ya tienes " << manoJugador[j].carta << " de " << manoJugador[j].palo << " en tu mano." << reset << std::endl;
                        cartaEnMano.push_back(escaleraRealSeleccionada[k]);
                        escaleraRealSeleccionada.erase(escaleraRealSeleccionada.begin() + k);
                        cartaEncontrada = true;
                        break;
                    }
                }
                if (!cartaEncontrada) {
                    std::cout << rojo << "Carta diferente detectada, no puedes formar la Escalera Real." << reset << std::endl;
                    std::cout << rojo << "La probabilidad ahora es 0%." << reset << std::endl;
                    return;
                }
            }

            casosFavorables = escaleraRealSeleccionada.size();
            denominador = baraja.size();

            if (denominador <= 0) {
                std::cout << rojo << "No se puede calcular la probabilidad." << reset << std::endl;
                return;
            }

            probabilidadMazo = static_cast<long double>(casosFavorables) / denominador;
            std::cout << verde << "La probabilidad de obtener la Escalera Real es: " << probabilidadMazo << reset << std::endl;
            break;

        case 2:
            cartaDiferente = 0;

            for (size_t i = 0; i < manoJugador.size(); i++) {
                bool cartaObtenida = false;
                for (size_t j = 0; j < poker.size(); j++) {
                    if (manoJugador[i].carta == poker[j].carta && manoJugador[i].palo == poker[j].palo) {
                        std::cout << amarillo << "Ya tienes " << manoJugador[i].carta << " de " << manoJugador[i].palo << " en tu mano." << reset << std::endl;
                        cartaObtenida = true;
                        cartaEnMano.push_back(poker[j]);
                        poker.erase(poker.begin() + j);
                        break;
                    }
                }
                if (!cartaObtenida) {
                    std::cout << rojo << "Carta diferente encontrada." << reset << std::endl;
                    cartaDiferente++;
                }
            }

            if (cartaDiferente > 1) {
                std::cout << rojo << "Tienes mas de una carta diferente a 'K', la probabilidad es 0%." << reset << std::endl;
                return;
            }

            casosFavorables = poker.size();
            denominador = baraja.size();

            if (denominador <= 0) {
                std::cout << rojo << "No se puede calcular la probabilidad." << reset << std::endl;
                return;
            }

            probabilidadMazo = static_cast<long double>(casosFavorables) / denominador;
            std::cout << verde << "La probabilidad de obtener el Poker es: " << probabilidadMazo << reset << std::endl;
            break;

        default:
            std::cout << rojo << "Opcion no valida." << reset << std::endl;
            break;
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
    int valorTotal = 0;

    for (size_t i = 0; i < mano.size(); i++) {
        int valorCarta = 0;

        if (mano[i].carta == "2") {
            valorCarta = 2;
        } else if (mano[i].carta == "3") {
            valorCarta = 3;
        } else if (mano[i].carta == "4") {
            valorCarta = 4;
        } else if (mano[i].carta == "5") {
            valorCarta = 5;
        } else if (mano[i].carta == "6") {
            valorCarta = 6;
        } else if (mano[i].carta == "7") {
            valorCarta = 7;
        } else if (mano[i].carta == "8") {
            valorCarta = 8;
        } else if (mano[i].carta == "9") {
            valorCarta = 9;
        } else if (mano[i].carta == "10") {
            valorCarta = 10;
        } else if (mano[i].carta == "J") {
            valorCarta = 11;
        } else if (mano[i].carta == "Q") {
            valorCarta = 12;
        } else if (mano[i].carta == "K") {
            valorCarta = 13;
        } else if (mano[i].carta == "A") {
            valorCarta = 14;
        }

        valorTotal += valorCarta;

    }

    return valorTotal;
}
