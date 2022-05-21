#include <iostream>
#include <conio.h>
#include <string.h>
#include <windows.h>
struct Modelos{
    char name[40], esp[40], sex[40], piel[40];
    int edad;
    float est, tarifaph;
}mod;
void gotoxy(int x,int y){ 
    COORD coord;
    coord.X = x; 
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
int main(){
    system("cls");
    FILE *fachon;
    fachon=fopen("fachon.dat", "w");
    fclose(fachon);
    gotoxy(30, 12); printf("Archivo creado!");
    getch();
    return(0);
}