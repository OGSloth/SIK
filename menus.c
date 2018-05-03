#include "err.h"
#include <unistd.h>
#include <stdio.h>
#define keep "\e[H\e[J"

void make_menu(int opt, int type, int reciver){
    int cleaning = write(reciver, keep, 6);
    if(cleaning != 6)
        syserr("writing to client socket");
    int men_err = 0;
    if(type == 0){
        if(opt == 0){
            men_err += write(reciver, "\e[1;34m[*]Opcja A\015\n\e[0m[]Opcja B\015\n[]Koniec\015\n", 44);
        }
        else if(opt == 1){
            men_err += write(reciver, "[]Opcja A\015\n\e[1;34m[*]Opcja B\015\n\e[0m[]Koniec\015\n", 44);    
        }
        else if(opt == 2){
            men_err += write(reciver, "[]Opcja A\015\n[]Opcja B\015\n\e[1;34m[*]Koniec\015\n\e[0m", 44);
        }
        else
            syserr("Unknown Error\n");
        if(men_err != 44)
            syserr("writing to client socket");
    }
    else if(type == 1){
        if(opt == 0){
            men_err += write(reciver, "\e[1;34m[*]Opcja B1\015\n\e[0m[]Opcja B2\015\n[]Wstecz\015\n", 46);     
        }
        else if(opt == 1){
            men_err += write(reciver, "[]Opcja B1\015\n\e[1;34m[*]Opcja B2\015\n\e[0m[]Wstecz\015\n", 46); 
        }
        else if(opt == 2){
            men_err += write(reciver, "[]Opcja B1\015\n[]Opcja B2\015\n\e[1;34m[*]Wstecz\015\n\e[0m", 46); 
        }
        else
            syserr("Unknown Error\n");  
        if(men_err != 46)
            syserr("writing to client socket");;
    }
    else
        syserr("Unknown Error\n");
    
}

void make_after_menu(int opt, int type, int reciver){
    int cleaning = write(reciver, keep, 6);
    if(cleaning != 6)
        syserr("writing to client socket");
    int men_err = 0;
    if(type == 0){
        if(opt == 0){
            men_err += write(reciver, "\e[1;34m[*]Opcja A\015\n\e[0m[]Opcja B\015\n[]Koniec\015\nA\015\n", 47);
        }
        else if(opt == 1){
            men_err += write(reciver, "[]Opcja A\015\n\e[1;34m[*]Opcja B\e[0m\015\n[]Koniec\015\n", 47);    
        }
        else if(opt == 2){
            men_err += write(reciver, "[]Opcja A\015\n[]Opcja B\015\n[*]\e[1;34mKoniec\015\n\e[0m", 47);
        }
        else
            syserr("Unknown Error\n");
         //printf("MEN ERR = %d\n", men_err);
        if(men_err != 47)
            syserr("writing to client socket");
    }
    else if(type == 1){
        if(opt == 0){
            men_err += write(reciver, "\e[1;34m[*]Opcja B1\015\n\e[0m[]Opcja B2\015\n[]Wstecz\015\nB1", 48);     
        }
        else if(opt == 1){
            men_err += write(reciver, "[]Opcja B1\015\n\e[1;34m[*]Opcja B2\015\n\e[0m[]Wstecz\015\nB2", 48); 
        }
        else if(opt == 2){
            men_err += write(reciver, "[]Opcja B1\015\n[]Opcja B2\015\n\e[1;34m[*]Wstecz\015\n\e[0m", 48); 
        }
        else
            syserr("Unknown Error\n");
       if(men_err != 37 && men_err != 48)
            syserr("writing to client socket");
    }
    else
        syserr("Unknown Error\n");
    
}

/*
int menu1(int reciver){
    int men_err = 0;
    men_err += write(reciver, "[*]Opcja A\n", 12);
    men_err += write(reciver, "[]Opcja B\n", 11);
    men_err += write(reciver, "[]KONIEC\n", 10);
    return men_err;
}

int menu2(int reciver){
    int men_err = 0;
    men_err += write(reciver, "[]Opcja A\n", 11);
    men_err += write(reciver, "[*]Opcja B\n", 12);
    men_err += write(reciver, "[]KONIEC\n", 10);
    return men_err;
}

int menu3(int reciver){
    int men_err = 0;
    men_err += write(reciver, "[]Opcja A\n", 11);
    men_err += write(reciver, "[]Opcja B\n", 11);
    men_err += write(reciver, "[*]KONIEC\n", 11);
    return men_err;
}

void menus(int opt, int reciver){
    write(reciver, keep, 6);
    int ext = 0;
    if(opt == 0)
        ext = menu1(reciver);
    else if(opt == 1)
        ext = menu2(reciver);
    else if(opt == 2)
        ext = menu3(reciver);
    if(ext != 33)
         syserr("writing to client socket");  
}
*/
