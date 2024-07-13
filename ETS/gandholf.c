#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>
#include <string.h>

#define NOMBRE_ARCHIVO "user.txt"
#define LONGITUD_MAXIMA_CADENA 1000
#define MAX_PASSWD_LEN 256

FILE *archivo;

void menuServer();
int checkFile(char user[],char pass[]);
void login(char user[],char pass[]);
void registro(char user[],char pass[]);
void agregarLibro();
void get_password(char *password, int max_length, int y, int x);

int main(void){
    
    menuServer();
 

}

void menuServer(){

    initscr();
    printw("Hola Mundo: Bienvenidos al Server de Gandholf\n");
    printw("LOL\n");
    printw("[1] Iniciar Sesión como Cliente     ");
    printw("[2] Agregar Libros al Inventario\n");

    refresh();
    int op=getchar();
    if( op == 49){
        char us[50]="$\0";
        char ps[50]="%\0";
        char user[50];
        char pass[50];


        clear();
        printw("Log In\n");
        mvprintw(1,0,"Usuario:");
        mvprintw(2,0,"Contraseña:");

        mvscanw(1,12,"%s",user);
        noecho();             // Desactiva el eco automático de caracteres
        cbreak();             // Desactiva el modo de entrada en buffer
        keypad(stdscr, TRUE); // Habilita el uso de teclas especiales como backspace
        get_password(pass,50,2,11);

        echo();
        keypad(stdscr, FALSE);
        printw("\n");
        
        strcat(user,"%\0");
        strcat(pass,".\0");

        strcat(us,user);
        strcat(ps,pass);

        printw("%s\n",us);
        printw("%s\n",ps);

        getch();

        login(us,ps);


        refresh();
        getch();

    } else if ( op == 50){

        printw("Agregar Libro\n");
        agregarLibro();
        refresh();
        getch();

    }else{


    refresh();
    getch();
    endwin();

    }

   endwin();


}

void login(char user[],char pass[]){

    int var =checkFile(user,pass);
    if(var==1){
        printw("Usuario Encontrado Correctamente\n");
    }else if(var==-1){
        printw("Usuario Encontrado Correctamente\n");
        printw("Contraseña Incorrecta\n");
    }else{
        printw("Usuario No Encontrado\n");
        printw("¿Deseas Registrarte con estos datos?    [S]-Si     [N]-No\n");
        refresh();
        int op=getchar();

        //int para S = 115
        //int para N = 110

        if (op==110){
            printw("NO");
            refresh();
            return;
        } else if ( op == 115){

            printw("SI");
            refresh();
            getch();

            registro(user,pass);

        } else{
            printw("QUIZA");
        }
    }
    return;
}

void registro(char user[],char pass[]){
    
    char nom[50];
    printw("Ingresa tu Nombre:");
    scanw("%s",nom);
    printw("%s",nom);
    getch();
    archivo = fopen(NOMBRE_ARCHIVO, "r+"); // Modo lectura
    // Aquí vamos a ir almacenando cada línea
    char buffer[LONGITUD_MAXIMA_CADENA];             
    
    //Identificar úlitmo identificador
    int i=0;
    while (fgets(buffer, LONGITUD_MAXIMA_CADENA, archivo)){
        i++;
    }  

    //Pasar de int a string
    char id[50];
    sprintf(id, "%d", i);
    //Concatenar toda la información
    strcat(id,"#");
    strcat(id,nom);
    strcat(id,user);
    id[strlen(id) - 1] = '\0';// user = $user% pass = %pass.
    //Por lo tanto se elimina el ultimo caracter de user para mantener el formato de registro
    strcat(id,pass);
    printw("%s\n",id);
    printw("Registro Existoso\n");
    // Añade el registro 
    fprintf(archivo, "%s\n",id);
    fclose(archivo);
}


int checkFile(char user[],char pass[]){

    archivo = fopen(NOMBRE_ARCHIVO, "r"); // Modo lectura

    if(archivo==NULL){
        printw("No se pudo abrir archivo\n");
        getch();
    }else{
        printw("Checando Archivo...\n");
    }
    
    char bufer[LONGITUD_MAXIMA_CADENA];         // Aquí vamos a ir almacenando cada línea
    while (fgets(bufer, LONGITUD_MAXIMA_CADENA, archivo))
    {
        // Aquí, justo ahora, tenemos ya la línea. Le vamos a remover el salto
        strtok(bufer, "\n");
        // La imprimimos, pero realmente podríamos hacer cualquier otra cosa
        printw("La línea es: '%s'\n", bufer);


        if (strstr(bufer, user) != NULL) { //Usuario existe
            printw("Existe en los usuario\n");
            

            if (strstr(bufer, pass) != NULL) {//Contraseña Correcta
                printw("Contraseña correcta\n");
                return 1;
            }else{
                printw("Contraseña incorrecta\n");//Contraseña Incorrecta
                return -1;
            }


        } else {//Usuario No Existe
        
        }
        refresh();
    
    }
    fclose(archivo);
    return 0;

    
}



void get_password(char *password, int max_length, int y, int x) {
    int ch, i = 0;
    move(y, x); // Mueve el cursor a la posición deseada
    while (i < max_length - 1) {

        ch = getch();
        if (ch == '\n' || ch == '\r') {
            break; // Termina la entrada si es salto de línea
        }
        if (ch == 127 || ch == KEY_BACKSPACE || ch == '\b') { // Manejo de borrado
            if (i > 0) {
                password[i] = '\0';
                i--;
                
                mvaddch(y, x + i, ' '); // Borra el asterisco de la pantalla
                move(y, x + i);
                refresh();
            }
        } else {
            password[i++] = ch;
            mvaddch(y, x + i - 1, '*');
            //mvaddch(y+1, x+1 + i - 1, password[i-1]);
            refresh();
        }
    }
    password[i] = '\0'; // Termina la cadena con un nulo
    return;
}

void agregarLibro(){

    archivo = fopen("catalogo.txt", "r+"); // Modo lectura
    // Aquí vamos a ir almacenando cada línea
    char buffer[LONGITUD_MAXIMA_CADENA];             
    
    //Identificar úlitmo identificador
    int i=0;
    while (fgets(buffer, LONGITUD_MAXIMA_CADENA, archivo)){
        i++;
    }  
    printw("%d",i);

    char nombre[100];
    int stock;

    clear();
    mvprintw(1,0,"Nombre del Libro: ");
    mvprintw(2,3,"Existencia: ");
    mvscanw(1,17,"%99[^\n]",nombre);
    mvscanw(2,17,"%d",&stock);
    printw("%s",nombre);
    printw("%d",stock);
}