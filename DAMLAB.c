#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h> // Necesaria para la función clock()

#define MARGEN 44
#define MARGEN1 65

/*------------------------------------------ESTRUCTURA PARA RECORDS----------------------------------*/

struct records
{
    int tiempo;
    int resultado;
};


/*---------------------------------------------------------------------------------------------------*/

/*--------------------------------Definición Subprocesos Utilidades--------------------------------*/
int nums(int min, int max);
void PintarMenu(char *menu[]);
int CalcularString(char *menu[]);
void PintaBordes(int num);
void PintaMargen(int num);
void PintarDamla();
void gotoxy( int x, int y );
void borraranterior(int x, int y);
void ponerasterisco(int x, int y);
void Pintarperdiste();
void Pintartimeout();
void PintarGanar();
int esNumero(char *cadena);
int leerCadenaNumerica();
/*---------------------------------------------------------------------------------------*/

/*--------------------------------Definición Subprocesos--------------------------------*/
void Jugar(int dificultad, struct records guardarrecords[5], int *contr);
int elegirdificultad();
void elegirbarreras(int barreras,int posicionesbarreras[barreras][2]);
void vislaberinto(int barreras,int posicionesbarreras[barreras][2], int x, int y);
void visrecords(struct records guardarrecords[5], int contr);
/*---------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------ MAIN ---------------------------------------------------------------------------------*/
int main() {

    char *opc[] = {"Jugar","Cambiar Dificultad", "Salir", ""};
    int dificultad=1;
    int opc2=0;
    struct records guardarrecords[5];
    int contr=0;

    do{
    system("cls");
    system("color 5f");
    PintarDamla();
    PintarMenu(opc);

    opc2= leerCadenaNumerica();



    switch (opc2)
    {
    case 1:
        /* Partida */
        Jugar(dificultad, guardarrecords, &contr);
        break;

    case 2:
        /*Elegir Dificultad*/
        dificultad=elegirdificultad();
        break;
    default:
        break;
    }


    }while(opc2!=3);

    return 0;
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------Funciones Subprocesos--------------------------------*/

void Jugar(int dificultad, struct records guardarrecords[5], int *contr){

    int barreras, tiempo;
    char txtdific[10];

    char resp2;


    do
    {
        system("cls");
        fflush(stdin);
        putchar('\n');
        PintaMargen(MARGEN+10);
        switch (dificultad)
        {
        case 1:
            memset(txtdific, 0, sizeof(txtdific));
            strcpy(txtdific, "Facil");
            break;
        case 2:
            memset(txtdific, 0, sizeof(txtdific));
            strcpy(txtdific, "Intermedio");
            break;
        case 3:
            memset(txtdific, 0, sizeof(txtdific));
            strcpy(txtdific, "Dificil");
            break;
        }
        printf("Desea jugar con la dificultad %s (s/n)", txtdific);
        resp2=getchar();

        if(resp2=='n'){
            dificultad=elegirdificultad();
        }else{
            if (resp2!='n' && resp2!='s'){}


        }

    } while (resp2!='s');


    switch (dificultad)
    {
    case 1:
        barreras=20;
        tiempo=30;
        break;
    case 2:
        barreras=40;
        tiempo=15;
        break;
    case 3:
        barreras=80;
        tiempo=5;
        break;
    }

    int posicionesbarreras[barreras][2];
    char resp;
    elegirbarreras(barreras, posicionesbarreras);
    do
    {

        system("cls");
        vislaberinto(barreras, posicionesbarreras, 1, 1 );
        gotoxy(0,23);
        puts("Le gusta este mapa?(s/n)");
        resp=getchar();

        if (resp!='n' && resp!='s')
        { }else{
            if (resp=='n')
            {
                elegirbarreras(barreras, posicionesbarreras);
            }


        }


    } while (resp!='s');

    system("cls");
    int x=1;
    int y=1;
    vislaberinto(barreras, posicionesbarreras, x, y);

    clock_t start_time = clock(); /* Es una variable de la libreria a la cual llamaremos start_time, que se utilizara para almacenar
    el tiempo del inicio del juego, la funcion clock devuelve los ciclos de reloj desde que se crea la variable, es decir, en el momento
    que se va a jugar*/
    int resultado = 0;

    int tiempo1=0;
    int posbarra=1;

    while (resultado==0) {
        if (kbhit()) {
            char tecla = getch();
            switch (tecla) {
            case 'w':
                borraranterior(x, y);
                y--;
                ponerasterisco(x, y);
                break;
            case 's':
                borraranterior(x, y);
                y++;
                ponerasterisco(x, y);
                break;
            case 'd':
                borraranterior(x, y);
                x++;
                ponerasterisco(x, y);
                break;
            case 'a':
                borraranterior(x, y);
                x--;
                ponerasterisco(x, y);
                break;
            default:
                break;
            }
        }

        gotoxy(1, 23);
        printf("%d:%d", ((clock() - start_time) / CLOCKS_PER_SEC), tiempo);

        if ((x <= 0 || x > 60) || (y <= 0 || y >=21)) {
            resultado = 1;
            break;
        }

        for (int i = 0; i < barreras; i++) {
            int x3 = posicionesbarreras[i][0];
            int y3 = posicionesbarreras[i][1];
            if (x == x3 && y == y3) {
                resultado = 1;
                break;
            }
        }





        if (((clock() - start_time) / CLOCKS_PER_SEC) == 1+tiempo1)
        {
            switch (dificultad)
            {
            case 1:
                gotoxy(0+posbarra, 22);
                printf("// ");
                posbarra += 2;
                break;

            case 2:
                gotoxy(0+posbarra, 22);
                printf("//// ");
                posbarra += 4;
                break;

            case 3:
                gotoxy(0+posbarra, 22);
                printf("//////// ");
                posbarra += 8;
                break;

            default:
                break;
            }

            tiempo1++;
        }

        if (x == 60 && y == 20) {
            resultado = 2;
            break;
        }

        if (resultado == 1) {
            break;
        }

        if (((clock() - start_time) / CLOCKS_PER_SEC) == tiempo)
        {
            resultado=3;
        }
        /*En principio los ciclos de reloj no se presentan como segundos,
        pero en primer lugar, llamaremos a la funcion clock(), que nos dará los ciclos de reloj, esto hará que si lo restamos a al variable
        que tenemos ya hecha, que es cuando se inicia la función jugar, nos dará la diferencia y al dividirlo entre "CLOCKS_PER_SEC", nos lo
        pasaria a segundos y ya podriamos calcularlo a tiempo real, permitiendo que no se produzcan parpadeos y el programa sea muchisimo
        mas eficiente y bonito a la vista del usuario*/

    }

    if (*contr==4)
    {
        *contr=0;
    }


    int contr2=*contr;

    switch (resultado) {
    case 1:
        system("cls");
        Pintarperdiste();
        guardarrecords[contr2].resultado=resultado;
        guardarrecords[contr2].tiempo=(clock()-start_time)/CLOCKS_PER_SEC;
        (*contr)++;
        getch();
        visrecords(guardarrecords, contr2);
        getch();
        break;
    case 2:
        system("cls");
        PintarGanar();
        guardarrecords[contr2].resultado=resultado;
        guardarrecords[contr2].tiempo=(clock()-start_time)/CLOCKS_PER_SEC;
        (*contr)++;
        getch();
        visrecords(guardarrecords, contr2);
        getch();
        break;

    case 3:
        system("cls");
        Pintartimeout();
        guardarrecords[contr2].resultado=resultado;
        guardarrecords[contr2].tiempo=(clock()-start_time)/CLOCKS_PER_SEC;
        (*contr)++;
        getch();
        visrecords(guardarrecords, contr2);
        getch();
        break;
    default:
        break;
    }
}

void visrecords(struct records guardarrecords[5], int contr){

        char resultado[10];
        system("color 5f");
        system("cls");
        PintarDamla();

        PintaMargen(MARGEN+32);
        puts("RECORDS:");
        PintaMargen(MARGEN);
        PintaBordes(71);
        for (int i = 0; i <= contr; i++)
        {
            switch (guardarrecords[i].resultado)
            {
            case 1:case 3:
                memset(resultado, 0, sizeof(resultado));
                strcpy(resultado, "Derrota");
                break;

            case 2:
                memset(resultado, 0, sizeof(resultado));
                strcpy(resultado, "Victoria");
                break;

            default:
                break;
            }

            PintaMargen(MARGEN+20);
            printf("%d. Resultado:%s  Segundos:%d\n", i + 1, resultado, guardarrecords[i].tiempo);
        }
        PintaMargen(MARGEN);
        PintaBordes(71);
}

void vislaberinto(int barreras,int posicionesbarreras[barreras][2], int x1, int y1){

    int x, y;
    switch (barreras)
    {
    case 40:
        system("color 2A");
        break;
    case 60:
        system("color E0");
        break;
    case 80:
        system("color 4f");
        break;
    default:
        break;
    }
    for ( int i = 0; i < barreras; i++)
    {
        x=posicionesbarreras[i][0];
        y=posicionesbarreras[i][1];
        gotoxy(x,y);
        printf("#");
    }
    for (int k = 0; k < 22; k++)
    {
        gotoxy(61, k);
        putchar('|');
    }
    for (int k = 0; k < 62; k++)
    {
        gotoxy(k, 21);
        putchar('-');
    }
    gotoxy(x1, y1);
    printf("*");
    gotoxy(60, 20);
    putchar('M');

    gotoxy(61, 22);
    printf("|");
}

void elegirbarreras(int barreras, int posicionesbarreras[barreras][2]) {
    int cont = 0;
    srand(time(NULL));
    while (cont < barreras) {
        int x = rand() % 60 + 1;
        int y = rand() % 20 + 1;
        int repetida = 0;
        for (int i = 0; i < cont; i++) {
            if ((posicionesbarreras[i][0] == x && posicionesbarreras[i][1] == y) || (posicionesbarreras[i][0] == 1 && posicionesbarreras[i][1] == 1) || posicionesbarreras[i][0] == 60 && posicionesbarreras[i][1] == 20) {
                repetida = 1;
                break;
            }
        }
        if (!repetida) {
            posicionesbarreras[cont][0] = x;
            posicionesbarreras[cont][1] = y;
            cont++;
        }
    }



}

int elegirdificultad(){
    char *opc[]={"Nivel Facil", "Nivel Intermedio", "Nivel Dificil", ""};
    int dificultad=0;
    system("cls");
    PintarDamla();
    PintarMenu(opc);
    dificultad=nums(1,3);
    return dificultad;
}

/*---------------------------------------------------------------------------------------*/
/*---------------------------------------Funciones Utilidades---------------------------------------------------*/

void gotoxy( int x, int y ) {
    printf( "\033[%d;%df", y, x );//Se pone al revés xq xa la consola es fila,columna
}

int nums(int min, int max){
    int num;
    do {
        fflush(stdin);
        putchar('\n');
        PintaMargen(MARGEN+10);
        printf("Introduzca una opcion: ");
        scanf("%d", &num);
    } while (num < min || num > max);
    return num;
}

void PintarMenu(char *menu[]) {
    int contador = 0, num=71, i;
    PintaMargen(MARGEN);
    PintaBordes(num);
    while (menu[contador] != NULL && menu[contador][0] != '\0') {
        PintaMargen(MARGEN+10);
        for(i=0;i<=16;i++){
            putchar(' ');
        }
        printf("%d. %s\n", contador + 1, menu[contador]);
        contador++;
    }
    PintaMargen(MARGEN);
    PintaBordes(num);
}

void PintaBordes(int num) {
    int i;
    for (i = 0; i < num+3; i++) {
        putchar('-');
    }
    printf("\n");
}

void PintaMargen(int num) {
    int i;
    for (i = 0; i < num; i++) {
        printf(" ");
    }
}

void PintarDamla(){
    int i;
    char *dam[]={
        "     :::::::::      :::       :::   :::   :::            :::     ::::::::: ",
        "     :+:    :+:   :+: :+:    :+:+: :+:+:  :+:          :+: :+:   :+:    :+: ",
        "    +:+    +:+  +:+   +:+  +:+ +:+:+ +:+ +:+         +:+   +:+  +:+    +:+  ",
        "   +#+    +:+ +#++:++#++: +#+  +:+  +#+ +#+        +#++:++#++: +#++:++#+    ",
        " +#+    +#+ +#+     +#+ +#+       +#+ +#+        +#+     +#+ +#+    +#+    ",
        "#+#    #+# #+#     #+# #+#       #+# #+#        #+#     #+# #+#    #+#  ",
        "#########  ###     ### ###       ### ########## ###     ### #########       "
    };
    for(i=0;i<7;i++){
        PintaMargen(44);
        puts(dam[i]);
    }
    putchar('\n');
}

void Pintarperdiste(){
    int i;
    char *dam[]={
        "  sSSSSs   .S_SSSs     .S_SsS_S.     sSSs          sSSs_sSSs     .S    S.     sSSs   .S_sSSs    ",
        " d%%%%SP  .SS~SSSSS   .SS~S*S~SS.   d%%SP         d%%SP~YS%%b   .SS    SS.   d%%SP  .SS~YS%%b   ",
        "d%S'      S%S   SSSS  S%S `Y' S%S  d%S'          d%S'     `S%b  S%S    S%S  d%S'    S%S   `S%b  ",
        "S%S       S%S    S%S  S%S     S%S  S%S           S%S       S%S  S%S    S%S  S%S     S%S    S%S  ",
        "S&S       S%S SSSS%S  S%S     S%S  S&S           S&S       S&S  S&S    S%S  S&S     S%S    d*S  ",
        "S&S       S&S  SSS%S  S&S     S&S  S&S_Ss        S&S       S&S  S&S    S&S  S&S_Ss  S&S   .S*S ",
        "S&S       S&S    S&S  S&S     S&S  S&S~SP        S&S       S&S  S&S    S&S  S&S~SP  S&S_sdSSS   ",
        "S&S sSSs  S&S    S&S  S&S     S&S  S&S           S&S       S&S  S&S    S&S  S&S     S&S~YSY%b   ",
        "S*b `S%%  S*S    S&S  S*S     S*S  S*b           S*b       d*S  S*b    S*S  S*b     S*S   `S%b  ",
        "S*S   S%  S*S    S*S  S*S     S*S  S*S.          S*S.     .S*S  S*S.   S*S  S*S.    S*S    S%S  ",
        " SS_sSSS  S*S    S*S  S*S     S*S   SSSbs         SSSbs_sdSSS    SSSbs_S*S   SSSbs  S*S    S&S  ",
        "  Y~YSSY  SSS    S*S  SSS     S*S    YSSP          YSSP~YSSY      YSSP~SSS    YSSP  S*S    SSS  ",
        "                SP           SP                                                    SP          ",
        "                 Y            Y                                                     Y           "

    };
    system("color 4f");
    for(i=0;i<14;i++){
        PintaMargen(32);
        puts(dam[i]);
    }
    putchar('\n');

}

void Pintartimeout(){
    int i;
    char *dam[]={
        "_________  ___  _____ ______   _______           ________  ___  ___  _________  ___       ",
        "|\\___   ___\\  \\|\\   _ \\  _   \\|\\  ___ \\         |\\   __   \\|\\  \\|\\  \\|\\___   ___\\  \\      ",
        "\\|___ \\  \\_\\ \\  \\ \\  \\\\__\\ \\  \\ \\   __/|        \\ \\  \\|\\  \\ \\  \\\\  \\|___ \\  \\_\\ \\  \\     ",
        "     \\ \\  \\ \\ \\  \\ \\  \\|__| \\  \\ \\  \\_|/__        \\ \\  \\\\  \\ \\  \\\\  \\   \\ \\  \\ \\ \\  \\    ",
        "      \\ \\  \\ \\ \\  \\ \\  \\    \\ \\  \\ \\  \\_|\\ \\       \\ \\  \\\\  \\ \\  \\\\  \\   \\ \\  \\ \\ \\__\\   ",
        "       \\ \\__\\ \\ \\__\\ \\__\\    \\ \\__\\ \\_______\\       \\ \\_______\\ \\_______\\   \\ \\__\\ \\|__|   ",
        "        \\|__|  \\|__|\\|__|     \\|__|\\|_______|        \\|_______|\\|_______|    \\|__|     ___ ",
        "                                                                                      |\\__\\ ",
        "                                                                                      \\|__|"


    };
    system("color 4f");
    for(i=0;i<9;i++){
        PintaMargen(32);
        puts(dam[i]);
    }
    putchar('\n');

}

void PintarGanar(){
    int i;
    char *dam[]={
        " /$$$$$$$$           /$$                                    /$$                                               /$$ /$$",
        "| $$_____/          | $$                                   | $$                                              | $$| $$",
        "| $$       /$$$$$$$ | $$$$$$$   /$$$$$$   /$$$$$$  /$$$$$$ | $$$$$$$  /$$   /$$  /$$$$$$  /$$$$$$$   /$$$$$$ | $$| $$",
        "| $$$$$   | $$__  $$| $$__  $$ /$$__  $$ /$$__  $$|____  $$| $$__  $$| $$  | $$ /$$__  $$| $$__  $$ |____  $$| $$| $$",
        "| $$__/   | $$  \\ $$| $$  \\ $$| $$  \\ $$| $$  \\__/ /$$$$$$$| $$  \\ $$| $$  | $$| $$$$$$$$| $$  \\ $$  /$$$$$$$|__/|__/",
        "| $$      | $$  | $$| $$  | $$| $$  | $$| $$      /$$__  $$| $$  | $$| $$  | $$| $$_____/| $$  | $$ /$$__  $$        ",
        "| $$$$$$$$| $$  | $$| $$  | $$|  $$$$$$/| $$     |  $$$$$$$| $$$$$$$/|  $$$$$$/|  $$$$$$$| $$  | $$|  $$$$$$$ /$$ /$$",
        "|________/|__/  |__/|__/  |__/ \\______/ |__/      \\_______/|_______/  \\______/  \\_______/|__/  |__/ \\_______/|__/|__/"


    };
    system("color 2A");
    for(i=0;i<8;i++){
        PintaMargen(20);
        puts(dam[i]);
    }
    putchar('\n');

}



void borraranterior(int x, int y){
    gotoxy(x, y);
    putchar(' ');
}

void ponerasterisco(int x, int y){

    gotoxy(x, y);
    putchar('*');
}


int esNumero(char *cadena) {
    int i = 0;


    while (cadena[i] != '\0') {

        if (!(cadena[i] >= '0' && cadena[i] <= '9')) {
            return 0;
        }
        i++;
    }

    return 1;
}


int leerCadenaNumerica() {
    char cadena[100];
    int numero;
    do {
        PintaMargen(MARGEN+10);
        printf("Introduzca una opcion: ");
        scanf("%s", cadena);

        numero = atoi(cadena);

    } while (!esNumero(cadena) || numero<1 || numero>3  );


    return numero;
}


/*------------------------------------------------------------------------------------------*/
