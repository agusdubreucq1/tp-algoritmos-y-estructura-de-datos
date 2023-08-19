#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <cstring>

using namespace std;

typedef char str20[21];
//ESTRUCTURAS
//*******************************************************************
struct partido{
    int idPartida;
    str20 nomJugador;
    int fecha;
    int puntaje;
};


struct nodo{
    partido info;
    nodo* sgte;
};

//PROTOTIPOS
//*******************************************************************
void inicializarMatriz(int[][11], int);
int tirar(int[]);
void jugar(int[][11], int, bool&);
void numeros(int[], int[][11], int);
bool generala(int[]);
bool poker(int[]);
bool full(int[]);
bool escalera(int[]);
void mostrarResultados(int[][11], int, str20[], str20&, int&);
void puntajeMax(int[][11], int);
nodo* insertarOrdenado(nodo*&, partido);
int cantRegistros (FILE*);
partido pop(nodo*&);







//MAIN
//*******************************************************************
int main(){
    FILE* archivo=fopen("partidos","rb+");   
    bool genSer=false;
    int i, j, jugadores, fecha, idJugada=cantRegistros(archivo)+1;
    partido partido;
    nodo* lista=NULL;
    
    
    cout<<"ingrese la fecha: ";
    cin>>fecha;
    cout<<"\ningrese la cantidad de jugadores: ";
    cin>>jugadores;

    int matriz[jugadores][11]={{-1}};
    str20 nomJug[jugadores];

    inicializarMatriz(matriz, jugadores);
    fseek(archivo,0,SEEK_END);
    srand(time(NULL));

    for(i=0;i<jugadores;i++){
        cout<<"\nnombre del jugador "<<i+1<<" : ";
        cin>>nomJug[i];
    }

    for(i=0;i<11&&genSer==false;i++){
        cout<<"\nRONDA: "<<i+1<<"\n---------------"<<endl;
    for(j=0;j<jugadores &&genSer==false;j++){
        cout<<"\njugador: "<<nomJug[j]<<endl;
    jugar(matriz, j,genSer);
     }
    }

   mostrarResultados(matriz,jugadores,nomJug, partido.nomJugador, partido.puntaje);
   partido.idPartida=idJugada;
   partido.fecha=fecha;

   fwrite(&partido,sizeof(partido),1,archivo);
    
    fseek(archivo,0,SEEK_SET);
       while(fread(&partido,sizeof(partido),1,archivo)){
        insertarOrdenado(lista, partido);
    }
    fclose(archivo);
    i=1;
    cout<<"\nRANKING\npuesto  nombre  puntaje  fecha  idJugada\n";
    while(i<4 && lista!=NULL){
        partido = pop(lista);
        cout<<i<<"       "<<partido.nomJugador<<"     "<<partido.puntaje<<"      "<<partido.fecha<<"  "<<partido.idPartida<<endl;
        i++;
    }


    return 0;}

    //DEFINICION FUNCIONES
    //*******************************************************************

    void inicializarMatriz(int matriz[][11], int fil){
         int i, j;
          for(i=0;i<fil;i++){
            for(j=0;j<11;j++){
              matriz[i][j]=-1;
        }
    }
    }



    void numeros (int vec[], int matriz[][11],int j) {
    str20 columnas[11]={"1", "2", "3", "4", "5", "6", "escalera", "full", "poker", "generala", "generala doble"};
    int i;
    int max=0;
    int maxPos=0;
    for (i=0;i<6;i++) {
    if (vec[i]>max && matriz[j][i]==-1) {
    maxPos=i;
    max=vec[i];
    }
    }
    if (max==0) {
    for (i=10;i>=0;i--) {
		if (matriz[j][i]==-1) {
			matriz[j][i]=0;
            cout<<"\ntache la columna de "<<columnas[i]<<endl;
            
			break;
        }
    }
    }
    else {
	    matriz[j][maxPos]=max*(maxPos+1);
        cout<<"\nsume: "<<max*(maxPos+1)<<" al "<<maxPos+1<<endl;
    }
    }




    int tirar(int vec[]){
    int i;        
    for(i=0;i<5;i++){        
    vec[i]=rand()%6 +1;}  

    i=rand()%3+1;    
    return i;}


    void jugar(int resultados[][11], int j,bool& genSer){
    int i;
    int dados[5];
    int cantTiros = tirar(dados);
    int contador[6]={0};
    for(i=0;i<5;i++){
    contador[dados[i]-1]++;
    }
    //mostrando dados+++++++++++++
    cout<<"dados: "<<endl;
    for(i=0;i<5;i++){
        cout<<dados[i]<<endl;
    }

    if(cantTiros==1){
        if(generala(contador)&& resultados[j][9]==-1 ){//GENERALA SERVIDA
            genSer==true;
            puntajeMax(resultados, j);//(poner puntaje maximo)
            cout<<"\nhice generala servida"<<endl;
        }else{
             if(poker(contador)&& resultados[j][8]==-1 ){
                resultados[j][8]=45;//POKER
                cout<<"\nhice poker servido"<<endl;
             }else{
                    if(full(contador)&& resultados[j][7]==-1){//FULL
                            resultados[j][7]=35;
                            cout<<"\nhice full servido"<<endl;}
                    else{
                        if(escalera(contador)&& resultados[j][6]==-1){
                            resultados[j][6]=25;
                            cout<<"\nhice escalera servida"<<endl;}
                            else{
                                numeros(contador, resultados, j);
                            }}}}}
    else{
        if(generala(contador)&& resultados[j][9]==-1){//GENERALA PUEDE SER DOBLE
            resultados[j][9]=50;
            cout<<"\nhice primer generala"<<endl;
        }else{
            if(generala(contador)&& resultados[j][9]>0 && resultados[j][10]==-1){
                  resultados[j][10]=100;
                  cout<<"\nhice generala doble"<<endl;}
                  else{
             if(poker(contador)&& resultados[j][8]==-1 ){
                resultados[j][8]=40;
                cout<<"\nhice poker"<<endl;//POKER
             }else{
                    if(full(contador)&& resultados[j][7]==-1){//FULL
                            resultados[j][7]=30;
                            cout<<"\nhice full"<<endl;}
                    else{
                        if(escalera(contador)&& resultados[j][6]==-1){
                            resultados[j][6]=20;
                            cout<<"\nhice escalera"<<endl;}
                            else{
                                numeros(contador, resultados, j);
                            }}}}}}
        
    
    }





bool generala(int contador[])
{
    bool gen=false;
    if(contador[0]==5 || contador[1]==5 || contador[2]==5   || contador[3] ==5 
        || contador[4]==5 || contador[5] ==5){
            gen=true;
        }
        return gen;
}


bool poker(int contador[]){
   bool pok=false;
   if(contador[0]==4 || contador[1]==4 || contador[2]==4 
    || contador[3] ==4 || contador[4]==4 || contador[5] ==4){
                pok=true;}
    return pok;            
}


bool full(int contador[]){
  bool ful=false;
  if((contador[0]==3 || contador[1]==3 || contador[2]==3   || contador[3] ==3 || contador[4]==3 
    || contador[5] ==3 )&&(contador[0]==2 || contador[1]==2 || contador[2]==2   || contador[3] ==2 
    || contador[4]==2 || contador[5] ==2)){
        ful=true;
    }
    return ful;

}


bool escalera(int contador[]){
    bool esca=false;
    if((contador[2]==1 && contador[3]==1 && contador[4]==1)
    &&((contador[0]==1 && contador[1]==1)||(contador[1]==1 && contador[5]==1)
    ||(contador[5]==1 && contador[0]==1))){
        esca=true;
    }
    return esca;
}


void mostrarResultados(int resultados[][11],int j, str20 nomJug[], str20& nomGan, int& puntajeGan){
     int sumas[j]={0};
     int i, k, max=0, maxPos=0;

     for(i=0;i<j;i++){
         for(k=0;k<11;k++){
             sumas[i]+=resultados[i][k];
         }
     }

     for(i=0;i<j;i++){
        cout<<"\njugador: "<<nomJug[i]<<"  puntaje: "<<sumas[i]<<endl;
         if(sumas[i]>max || i==0){
             max=sumas[i];
             maxPos=i;
         }
     }
     cout<<"\n-----------------\nGANADOR: "<<nomJug[maxPos]<<endl;
     strcpy(nomGan, nomJug[maxPos]);
     puntajeGan=sumas[maxPos];
}


void puntajeMax(int matriz[][11], int j){
    matriz[j][0]=6;
    matriz[j][1]=12;
    matriz[j][2]=18;
    matriz[j][3]=24;
    matriz[j][4]=30;
    matriz[j][5]=36;
    matriz[j][6]=25;
    matriz[j][7]=35;
    matriz[j][8]=45;
    matriz[j][9]=50;
    matriz[j][10]=100;
}

nodo* insertarOrdenado(nodo*& lista, partido ingreso){
    nodo* p=new nodo();
    strcpy(p->info.nomJugador,ingreso.nomJugador);
    p->info.idPartida=ingreso.idPartida;
    p->info.fecha=ingreso.fecha;
    p->info.puntaje=ingreso.puntaje;
    if(lista==NULL || ingreso.puntaje>lista->info.puntaje){
        p->sgte=lista;
        lista=p;
    }else{
        nodo* aux=lista;
        while(aux->sgte!=NULL && ingreso.puntaje<aux->sgte->info.puntaje){
            aux=aux->sgte;
        }
        p->sgte=aux->sgte;
        aux->sgte=p;
    }
    return p;
}

int cantRegistros (FILE* f) {
    int actual=ftell(f);
    fseek(f,0,SEEK_END);
    int cantidad=ftell(f)/sizeof(partido);
    fseek(f,actual,SEEK_SET);
    return cantidad;
}

partido pop(nodo*& lista){
    partido n=lista->info;
    nodo* aux=lista;
    lista=lista->sgte;
    delete aux;
    return n;
}
