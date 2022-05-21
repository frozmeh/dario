#include <iostream>
#include <conio.h>
#include <string.h>
#include <windows.h>
struct Modelos{
    char name[40], esp[40], sex[40], piel[40];
    int edad;
    float est, tarifaph;
}mod;

void gotoxy(int x, int y);
void Menu();
int BusquedaNombre(char name[40]);
void Incluir();
void Consultar();
void Modificar();
void Eliminar();
void Especialidad();
void Piel();
void MasJoven();

int main(){
    system("cls");
    Menu();
    getch();
    return(0);
}

void Menu(){
    char op[4];
    do{ 
        system("cls"); fflush(stdin);
        puts("MENU DE MODELOS");
        puts("[1] INCLUIR");
        puts("[2] CONSULTAR");
        puts("[3] MODIFICAR");
        puts("[4] ELIMINAR");
        puts("[5] REPORTE POR ESPECIALIDAD");
        puts("[6] REPORTE POR PIEL");
        puts("[7] MAS JOVEN");
        puts("[0] SALIR");
        printf("Digite una opcion: "); gets(op);
        if(strcmp(op, "1")==0) Incluir();
        else if(strcmp(op, "2")==0) Consultar();
        else if(strcmp(op, "3")==0) Modificar();
        else if(strcmp(op, "4")==0) Eliminar();
        else if(strcmp(op, "5")==0) Especialidad();
        else if(strcmp(op, "6")==0) Piel();
        else if(strcmp(op, "7")==0) MasJoven();
        else if(strcmp(op, "0")==0) puts("Saliendo..");
        else puts("Opcion incorrecta");
        getch();
    }while(strcmp(op, "0")!=0);
}

int BusquedaNombre(char name[40]){
    int band=0;
    FILE *fachon;
    fachon=fopen("fachon.dat", "r");
    while(band==0 && fread(&mod, sizeof(mod), 1, fachon)==1)
        if(strcmp(mod.name, name)==0) band=1;
    fclose(fachon);
    return(band);
}
int BusquedaEspecialidad(char esp[40]){
    int band=0;
    FILE *fachon;
    fachon=fopen("fachon.dat", "r");
    while(band==0 && fread(&mod, sizeof(mod), 1, fachon)==1)
        if(strcmp(mod.esp, esp)==0) band=1;
    fclose(fachon);
    return(band);
}
int BusquedaPiel(char piel[40]){
    int band=0;
    FILE *fachon;
    fachon=fopen("fachon.dat", "r");
    while(band==0 && fread(&mod, sizeof(mod), 1, fachon)==1)
        if(strcmp(mod.piel, piel)==0) band=1;
    fclose(fachon);
    return(band);
}

void Incluir(){
    system("CLS");
    char name[40];
    printf("Nombre del Modelo a incluir: "); gets(name);
    if(BusquedaNombre(name)==0){
        strcpy(mod.name, name);
        printf("Especialidad: "); gets(mod.esp);
        printf("Sexo: "); gets(mod.sex);
        printf("Edad: "); scanf("%d", &mod.edad); fflush(stdin);
        printf("Color de piel: "); gets(mod.piel);
        printf("Estatura: "); scanf("%f", &mod.est);
        printf("Tarifa por hora: "); scanf("%f", &mod.tarifaph);
        FILE *fachon;
        fachon=fopen("fachon.dat", "at+");
        fwrite(&mod, sizeof(mod), 1, fachon);
        fclose(fachon);
        printf("Modelo ingresado");
        }else puts("El modelo ya se encuentra en la Agencia");
}

void Consultar(){
    system("CLS");
    char name[40];
    printf("Nombre del Modelo a buscar: "); gets(name);
    if(BusquedaNombre(name)==1){
        printf("\nEspecialidad: %s", mod.esp);
        printf("\nSexo: %s", mod.sex);
        printf("\nEdad: %d", mod.edad);
        printf("\nColor de piel: %s", mod.piel);
        printf("\nEstatura: %.2f", mod.est);
        printf("\nTarifa por hora: %.2f", mod.tarifaph);
        }else printf("\nModelo no encontrada");
}

void Modificar(){
    system("CLS");
    char name[40];
    int b;
    printf("Nombre del Modelo a modificar: "); gets(name);
    b=BusquedaNombre(name);
    if(b==1){
        FILE *fachon;
        FILE *temp;
        fachon=fopen("fachon.dat", "r");
        temp=fopen("temp.dat", "at+");
        while(fread(&mod, sizeof(mod), 1, fachon)==1){
            if(strcmp(name, mod.name)==0){
                printf("Especialidad: "); gets(mod.esp);
                printf("Sexo: "); gets(mod.sex);
                printf("Edad: "); scanf("%d", &mod.edad); fflush(stdin);
                printf("Color de piel: "); gets(mod.piel);
                printf("Estatura: "); scanf("%f", &mod.est);
                printf("Tarifa por hora: "); scanf("%f", &mod.tarifaph);
            }
            fwrite(&mod, sizeof(mod), 1, temp);
        }
        fclose(fachon);
        fclose(temp);
        remove("fachon.dat");
        rename("temp.dat", "fachon.dat");
        printf("Registro modificado");
    }else printf("Modelo no encontrado");
    getch();
}

void Eliminar(){
    system("CLS");
    char name[40];
    int b;
    printf("Nombre del Modelo a eliminar: "); gets(name);
    b=BusquedaNombre(name);
    if(b==1){
        FILE *fachon;
        FILE *temp;
        fachon=fopen("fachon.dat", "r");
        temp=fopen("temp.dat", "at+");
        while(fread(&mod, sizeof(mod), 1, fachon)==1)
            if(strcmp(name, mod.name)!=0) fwrite(&mod, sizeof(mod), 1, temp);
        fclose(fachon);
        fclose(temp);
        remove("fachon.dat");
        rename("temp.dat", "fachon.dat");
        printf("Registro eliminado");
    }else printf("Modelo no encontrado");
}

void Especialidad(){
    char esp[40];
    int band=0, b;
    float totalBs=0;
    printf("Ingrese la especialidad: "); gets(esp);
    if(BusquedaEspecialidad(esp)==1){
        FILE *fachon;
        fachon=fopen("fachon.dat", "r");
        while(fread(&mod, sizeof(mod), 1, fachon)==1)
            if(strcmp(esp, mod.esp)==0){ band=1;
                printf("\nNombre: %s", mod.name);
                printf("\nEdad: %d", mod.edad);
                printf("\nColor de piel: %s", mod.piel);
                printf("\nEstatura: %.2f", mod.est);
                printf("\nTarifa por hora: %.2f", mod.tarifaph);
                totalBs+=mod.tarifaph;
            }
        printf("\nEl total en bolivares que representan es %.2f", totalBs);
    }else puts("No se encontro Modelos con esa especialidad");
}

void Piel(){

}

void MasJoven(){

}

void gotoxy(int x,int y){ 
    COORD coord;
    coord.X = x; 
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}