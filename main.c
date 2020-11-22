// Al: Vinícius Patrício Medeiros da Silva
// Nº: 21951799


#include "stdio.h"
#include "stdlib.h"
#include "time.h"

void troca(int *num1, int *num2){ // função que auxliará a troca de elementos do vetor
    int aux;
    aux=*num1;
    *num1=*num2;
    *num2=aux;

}

void contadorAdicionar(int *contador){ // como estarei trabalhando com ponteiro, foi necessário criar essa função
    int aux=*contador;
    aux++;
    *contador=aux;
}

void contadorAumentar(int *contador1, int *contador2){ //  como estarei trabalhando com ponteiro, foi necessário criar essa função
    int aux1=*contador1;
    int aux2=*contador2;
    *contador1=aux1+aux2;
}

void guardarTempo(clock_t tempo, double *guardador){ // função criada para guaardar tempo.
 double aux=(double)tempo;
 *guardador+=aux;

}

// ************************************** QuickSort  *************************************** //
int particiona(int *vetor, int inicio, int fim, int *contador_comp, int *contador_troca){
    int esq, dir, pivo;
    esq=inicio;
    dir=fim;
    pivo=vetor[inicio];
    
    while(esq<dir){   //[P, , , , , , ]
                       //E           D
        while(vetor[esq]<=pivo){       // avança uma posição a esquerda
            esq++;
            contadorAdicionar(contador_comp);         
        }
        
        while(vetor[dir]>pivo){ // recua uma posicao a direta
            dir--;
            contadorAdicionar(contador_comp);        
        }
        
        if(esq<dir){
            troca(&vetor[esq],&vetor[dir]);
            contadorAdicionar(contador_troca);
        }

    }
    vetor[inicio]=vetor[dir];
    contadorAdicionar(contador_troca);
    vetor[dir]=pivo;
    contadorAdicionar(contador_troca);
    return dir;
}

void quickSort( int *vetor, int inicio, int fim, int *contador_comp,int *contador_troca){
    int pivo;
    if(fim>inicio){
        pivo=particiona(vetor, inicio, fim,contador_comp,contador_troca);
        quickSort(vetor,inicio,pivo-1,contador_comp,contador_troca); // chamar a função para primeira  metade
        quickSort(vetor,pivo+1,fim,contador_comp,contador_troca); // chamar a função para segunda metade
    }
}
// *************************************** MergeSort  *************************************** //
void merge( int *vetor, int inicio,int meio, int fim, int *contador_comp, int *contador_troca){
    int *temp, p1, p2, tamanho, i , j, k,aux;
    int fim1 = 0, fim2=0;
    tamanho = fim-inicio+1;
    p1=inicio;
    p2=meio+1;
    temp=malloc(tamanho*sizeof(int));

    if( temp != NULL)
    {
        for(i=0;i<tamanho;i++){
            if(!fim1 && !fim2){
                contadorAdicionar(contador_comp);
                
                if(vetor[p1]<vetor[p2]){ // combinando ordenado
                    temp[i]=vetor[p1++];
                    
                }else{
                    temp[i]=vetor[p2++];
                    contadorAdicionar(contador_troca);
                }              
                if(p1>meio) fim1=1; // vetor 1 acabou?
                if(p2>fim) fim2=1; // vetor2 acabou?
            }else{
                contadorAdicionar(contador_troca);
                if(!fim1)
                    temp[i]=vetor[p1++];
                else
                    temp[i]=vetor[p2++];               
            }
        }
        for(j=0, k=inicio; j<tamanho; j++,k++)
            vetor[k]=temp[j];
    }
    free(temp);
}
void mergeSort( int *vetor, int inicio, int fim, int *contador_comp, int *contador_troca){
    if(inicio<fim)
    {
        int meio = (fim+inicio)/2;
        mergeSort(vetor, inicio, meio,contador_comp,contador_troca); // chama a função para primeira metade
        mergeSort(vetor,meio+1,fim,contador_comp,contador_troca);  // chama a função para segunda metade
        merge(vetor,inicio,meio,fim,contador_comp,contador_troca); // combina as duas metades de forma ordenada 
    }
}
// ****************************** Bolha ***************************** //

void bolha(int *vetor,int N, int *contador_comp, int *contador_troca){
    if(N<1){
        return ;
    }
    for(int i = 0; i < N; i++){
        if(vetor[i]>vetor[i+1]){
            troca(&vetor[i],&vetor[i+1]);
            contadorAdicionar(contador_troca);
        }
        contadorAdicionar(contador_comp);
    }
    bolha(vetor, N-1, contador_comp,contador_troca);
}
// ****************************** HeapSort ***************************** //
void criarHeap(int *vetor, int inicio, int fim, int *contador_comp, int *contador_troca){
    int aux=vetor[inicio]; //pai
    int j=inicio*2+1;
    while(j<=fim){ // filho menor que o vetor?
        if(j<fim){
            contadorAdicionar(contador_comp); 
            if(vetor[j]<vetor[j+1]){ // quem dos filhos é o maior?
                j=j+1;
            }
        }
        contadorAdicionar(contador_comp);
        if(aux<vetor[j]){ // o pai é menor que o filho?
            contadorAdicionar(contador_troca);
            vetor[inicio]=vetor[j]; // filho se torna pai
            inicio=j;
            j=inicio*2+1;
        }else{
            j=fim+1;
        }
    }
    vetor[inicio]=aux; // antigo pai ocupa o lugar do ultimo filho
}

void heapSort(int *vetor, int N, int *contador_comp, int *contador_troca){
    int i;
    for(i=(N-1)/2;i>=0;i--){ // criar heap a partir de dois dados
        criarHeap(vetor,i,N-1,contador_comp,contador_troca);
    }
    for(i=N-1;i>=1;i--){
        troca(&vetor[0],&vetor[i]); // pega o maior elemento da heap e coloca na sua posição correspondente no vetor
        criarHeap(vetor,0,i-1,contador_comp,contador_troca); // reconstruir a heap
    }
}

// ****************************** Funções de ordenação invertidos ***************************** //

// ************************************** QuickSort Invertido *************************************** //
int particionaInvertido(int *vetor, int inicio, int fim, int *contador_comp, int *contador_troca){
    int esq, dir, pivo;
    esq=inicio;
    dir=fim;
    pivo=vetor[inicio];
    
    while(esq<dir){
        
        while(vetor[esq]>=pivo){
            esq++;
            contadorAdicionar(contador_comp);         
        }
        
        while(vetor[dir]<pivo){
            dir--;
            contadorAdicionar(contador_comp);        
        }
        
        if(esq<dir){
            troca(&vetor[esq],&vetor[dir]);
            contadorAdicionar(contador_troca);
        }

    }
    vetor[inicio]=vetor[dir];
    contadorAdicionar(contador_troca);
    vetor[dir]=pivo;
    contadorAdicionar(contador_troca);
    return dir;
}

void quickSortInvertido( int *vetor, int inicio, int fim, int *contador_comp,int *contador_troca){
    int pivo;
    if(fim>inicio){
        pivo=particionaInvertido(vetor, inicio, fim,contador_comp,contador_troca);
        quickSortInvertido(vetor,inicio,pivo-1,contador_comp,contador_troca);
        quickSortInvertido(vetor,pivo+1,fim,contador_comp,contador_troca);
    }
}

// *************************************** MergeSort Invertido *************************************** //
void mergeInvertido( int *vetor, int inicio,int meio, int fim, int *contador_comp, int *contador_troca){
    int *temp, p1, p2, tamanho, i , j, k,aux;
    int fim1 = 0, fim2=0;
    tamanho = fim-inicio+1;
    p1=inicio;
    p2=meio+1;
    temp=malloc(tamanho*sizeof(int));

    if( temp != NULL)
    {
        for(i=0;i<tamanho;i++){
            if(!fim1 && !fim2){
                contadorAdicionar(contador_comp);
                
                if(vetor[p1]>vetor[p2]){
                    temp[i]=vetor[p1++];
                    
                }else{
                    temp[i]=vetor[p2++];
                    contadorAdicionar(contador_troca);
                }              
                if(p1>meio) fim1=1;
                if(p2>fim) fim2=1;
            }else{
                contadorAdicionar(contador_troca);
                if(!fim1)
                    temp[i]=vetor[p1++];
                else
                    temp[i]=vetor[p2++];               
            }
        }
        for(j=0, k=inicio; j<tamanho; j++,k++)
            vetor[k]=temp[j];
    }
    free(temp);
}
void mergeSortInvertido( int *vetor, int inicio, int fim, int *contador_comp, int *contador_troca){
    if(inicio<fim)
    {
        int meio = (fim+inicio)/2;
        mergeSortInvertido(vetor, inicio, meio,contador_comp,contador_troca);
        mergeSortInvertido(vetor,meio+1,fim,contador_comp,contador_troca);
        mergeInvertido(vetor,inicio,meio,fim,contador_comp,contador_troca);
    }
}

// ****************************** Bolha invertido ***************************** //

void bolhaInvertido(int *vetor,int N, int *contador_comp, int *contador_troca){
    if(N<1){
        return ;
    }
    for(int i = 0; i < N; i++){
        if(vetor[i]<vetor[i+1]){
            troca(&vetor[i],&vetor[i+1]);
            contadorAdicionar(contador_troca);
        }
        contadorAdicionar(contador_comp);
    }
    bolhaInvertido(vetor, N-1, contador_comp,contador_troca);
}

// ****************************** HeapSort Invertido***************************** //
void criarHeapInvertido(int *vetor, int inicio, int fim, int *contador_comp, int *contador_troca){
    int aux=vetor[inicio];
    int j=inicio*2+1;
    while(j<=fim){
        if(j<fim){
            contadorAdicionar(contador_comp);
            if(vetor[j]>vetor[j+1]){
                j=j+1;
            }
        }
        contadorAdicionar(contador_comp);
        if(aux>vetor[j]){
            contadorAdicionar(contador_troca);
            vetor[inicio]=vetor[j];
            inicio=j;
            j=inicio*2+1;
        }else{
            j=fim+1;
        }
    }
    vetor[inicio]=aux;
}

void heapSortInvertido(int *vetor, int N, int *contador_comp, int *contador_troca){
    int i;
    for(i=(N-1)/2;i>=0;i--){
        criarHeapInvertido(vetor,i,N-1,contador_comp,contador_troca);
    }
    for(i=N-1;i>=1;i--){
        troca(&vetor[0],&vetor[i]);
        criarHeapInvertido(vetor,0,i-1,contador_comp,contador_troca);
    }
}

int main(){

srand(time(NULL)); // srand foi colocado para tirar o bug de gerar os os mesmos números
int tamanho=1000;

printf("Tamanho do vetor:%d\n",tamanho);

int *vetor=malloc(tamanho*sizeof(int));
int *vetor1=malloc(tamanho*sizeof(int));
int *vetor2=malloc(tamanho*sizeof(int));
int *vetor3=malloc(tamanho*sizeof(int));

// variáveis criadas para determinar as contagens do método QuickSort
int contadorComp_quick;
int contadorTroca_quick;
int contadorCompTotal_quick=0;
int contadorTrocTotal_quick=0;
int mediaComp_quick=0;
int mediaTroc_quick=0;
clock_t tempoExec_quick;
double tempoExecTotal_quick=0;
double mediaTempo_quick=0;


// variáveis criadas para determinar as contagens do método MergeSort
int contadorComp_merge;
int contadorTroca_merge;
int contadorCompTotal_merge=0;
int contadorTrocTotal_merge=0;
int mediaComp_merge=0;
int mediaTroc_merge=0;
clock_t tempoExec_merge;
double tempoExecTotal_merge=0;
double mediaTempo_merge=0;

// variáveis criadas para determinar as contagens do método BubbleSort
int contadorComp_bolha;
int contadorTroca_bolha;
int contadorCompTotal_bolha=0;
int contadorTrocTotal_bolha=0;
int mediaComp_bolha=0;
int mediaTroc_bolha=0;
clock_t tempoExec_bolha;
double tempoExecTotal_bolha=0;
double mediaTempo_bolha=0;
// variáveis criadas para determinar as contagens do método HeapSort
int contadorComp_heap;
int contadorTroca_heap;
int contadorCompTotal_heap=0;
int contadorTrocTotal_heap=0;
int mediaComp_heap=0;
int mediaTroc_heap=0;
clock_t tempoExec_heap;
double tempoExecTotal_heap=0;
double mediaTempo_heap=0;
// ******************************************************************** //


printf("************************************* 40 VETORES ***************************************\n");
printf("| Metodo de Ordenacao | Numero de trocas | Numero de comparacoes | Tempo de execucao  |\n");
for(int i=0;i<40;i++){ // esse laço foi criado para poder analisar 40 vetores criados
    
    for(int j=0;j<tamanho;j++){  // criando o vetor de acordo com o tamanho dado
        vetor[j] = rand() % 99999;
        vetor1[j] = vetor[j];
        vetor2[j] = vetor[j];
        vetor3[j] = vetor[j];
    }
 
// ************* BubbleSort  ************* //
    contadorComp_bolha=0;
    contadorTroca_bolha=0;
    
    tempoExec_bolha=clock();
    bolha(vetor,tamanho,&contadorComp_bolha,&contadorTroca_bolha);
    tempoExec_bolha=clock()-tempoExec_bolha;
    guardarTempo(tempoExec_bolha,&tempoExecTotal_bolha);
    printf("|     BubbleSort      |    %02d        |         %02d        |      %.04lf       |\n",contadorTroca_bolha,contadorComp_bolha,((double)tempoExec_bolha)/((CLOCKS_PER_SEC/1000)));

    contadorAumentar(&contadorCompTotal_bolha,&contadorComp_bolha);
    contadorAumentar(&contadorTrocTotal_bolha,&contadorTroca_bolha);
// ************* QuickSort  ************* //
    contadorComp_quick=0;
    contadorTroca_quick=0;

    tempoExec_quick=clock();
    quickSort(vetor1,0,tamanho-1,&contadorComp_quick,&contadorTroca_quick);
    tempoExec_quick=clock()-tempoExec_quick;
    guardarTempo(tempoExec_quick,&tempoExecTotal_quick);
    printf("|      QuickSort      |      %02d        |          %02d        |       %.04lf       |\n",contadorTroca_quick,contadorComp_quick,((double)tempoExec_quick)/((CLOCKS_PER_SEC/1000)));
    
    contadorAumentar(&contadorCompTotal_quick,&contadorComp_quick);
    contadorAumentar(&contadorTrocTotal_quick,&contadorTroca_quick);


// ************* MergeSort  ************* //
    contadorComp_merge=0;
    contadorTroca_merge=0;

    tempoExec_merge=clock();
    mergeSort(vetor2,0,tamanho-1,&contadorComp_merge,&contadorTroca_merge);
    tempoExec_merge=clock()-tempoExec_merge;
    guardarTempo(tempoExec_merge,&tempoExecTotal_merge);
    printf("|      MergeSort      |      %02d        |           %02d        |       %.04lf       |\n",contadorTroca_merge,contadorComp_merge,((double)tempoExec_merge)/((CLOCKS_PER_SEC/1000)));

    contadorAumentar(&contadorCompTotal_merge,&contadorComp_merge);
    contadorAumentar(&contadorTrocTotal_merge,&contadorTroca_merge);

// ************* HeapSort  ************* //
    contadorComp_heap=0;
    contadorTroca_heap=0;

    tempoExec_heap=clock();
    heapSort(vetor3,tamanho,&contadorComp_heap,&contadorTroca_heap);
    tempoExec_heap=clock()-tempoExec_heap;
    guardarTempo(tempoExec_heap,&tempoExecTotal_heap);
    printf("|       HeapSort      |      %02d        |          %02d        |       %.04lf       |\n",contadorTroca_heap,contadorComp_heap,((double)tempoExec_heap)/((CLOCKS_PER_SEC/1000)));

    contadorAumentar(&contadorCompTotal_heap,&contadorComp_heap);
    contadorAumentar(&contadorTrocTotal_heap,&contadorTroca_heap);


printf("\n");
}// depois de guardar as informações gerais de cada algoritmo de ordenação, agora vai ser mostrado a média de cada um;

// média do numero de de trocas e comprações do método BubbleSort
mediaComp_bolha=contadorCompTotal_bolha/40;
mediaTroc_bolha=contadorTrocTotal_bolha/40;
mediaTempo_bolha=tempoExecTotal_bolha/40;


// média do numero de de trocas e comprações do método QuickSort
mediaTroc_quick=contadorTrocTotal_quick/40;
mediaComp_quick=contadorCompTotal_quick/40;
mediaTempo_quick=tempoExecTotal_quick/40;

// média do numero de de trocas e comprações do método MergeSort
mediaTroc_merge=contadorTrocTotal_merge/40;
mediaComp_merge=contadorCompTotal_merge/40;
mediaTempo_merge=tempoExecTotal_merge/40;
// média do numero de de trocas e comprações do método HeapSort
mediaTroc_heap=contadorTrocTotal_heap/40;
mediaComp_heap=contadorCompTotal_heap/40;
mediaTempo_heap=tempoExecTotal_heap/40;


printf("******************************* ANALISE MEDIA DOS 40 VETORES ********************************\n");
printf("|Metodo de Ordenacao| N medio de troca |  N medio de comparacao |   Tempo de execucao (ms) |\n");
printf("|     BubbleSort    |     %02d       |          %02d        |         %.4lf          |\n",mediaTroc_bolha,mediaComp_bolha,mediaTempo_bolha);
printf("|      QuickSort    |       %02d       |           %02d        |          %.4lf          |\n",mediaTroc_quick,mediaComp_quick,mediaTempo_quick);
printf("|       MegeSort    |       %02d       |            %02d        |          %.4lf          |\n",mediaTroc_merge,mediaComp_merge,mediaTempo_merge);
printf("|       HeapSort    |       %02d       |           %02d        |          %.4lf          |\n",mediaTroc_heap,mediaComp_heap,mediaTempo_heap);



// agora vai ser analisado o tempo de executação, numero de trocas e comparações de um vetor já ordenado.
    
// ************* BubbleSort  ************* //    
    contadorComp_bolha=0;
    contadorTroca_bolha=0;
    
    tempoExec_bolha=clock();
    bolha(vetor,tamanho,&contadorComp_bolha,&contadorTroca_bolha);
    tempoExec_bolha=clock()-tempoExec_bolha;

// ************* QuickSort  ************* //
    contadorComp_quick=0;
    contadorTroca_quick=0;

    tempoExec_quick=clock();
    quickSort(vetor,0,tamanho-1,&contadorComp_quick,&contadorTroca_quick);
    tempoExec_quick=clock()-tempoExec_quick;

// ************* MergeSort  ************* //
    contadorComp_merge=0;
    contadorTroca_merge=0;

    tempoExec_merge=clock();
    mergeSort(vetor,0,tamanho-1,&contadorComp_merge,&contadorTroca_merge);
    tempoExec_merge=clock()-tempoExec_merge;

// ************* HeapSort  ************* //
    contadorComp_heap=0;
    contadorTroca_heap=0;

    tempoExec_heap=clock();
    heapSort(vetor,tamanho,&contadorComp_heap,&contadorTroca_heap);
    tempoExec_heap=clock()-tempoExec_heap;


printf("\n******************************* ANALISE DE UM VETOR ORDENADO ********************************\n");
printf("|Metodo de Ordenacao|    N de troca    |    N de comparacao      |   Tempo de execucao (ms) |\n");
printf("|     BubbleSort    |         %02d       |         %02d          |         %.4lf           |\n",contadorTroca_bolha,contadorComp_bolha,((double)tempoExec_bolha)/((CLOCKS_PER_SEC/1000)));
printf("|      QuickSort    |       %02d       |         %02d          |         %.4lf           |\n",contadorTroca_quick,contadorComp_quick,((double)tempoExec_quick)/((CLOCKS_PER_SEC/1000)));
printf("|       MegeSort    |       %02d       |           %02d          |         %.4lf           |\n",contadorTroca_merge,contadorComp_merge,((double)tempoExec_merge)/((CLOCKS_PER_SEC/1000)));
printf("|       HeapSort    |       %02d       |          %02d          |         %.4lf           |\n",contadorTroca_heap,contadorComp_heap,((double)tempoExec_heap)/((CLOCKS_PER_SEC/1000)));


// A seguir vai ser analisado o numero de trocas e de comparçoes e tambem o tempo gasto para ordenar inversamente

for(int j=0;j<tamanho;j++){  // criando o vetor de acordo com o tamanho dado
    vetor[j] = rand() % 99999;
    vetor1[j] = vetor[j];
    vetor2[j] = vetor[j];
    vetor3[j] = vetor[j];
}

// ************* BubbleSort  ************* //
    contadorComp_bolha=0;
    contadorTroca_bolha=0;
    
    tempoExec_bolha=clock();
    bolhaInvertido(vetor,tamanho,&contadorComp_bolha,&contadorTroca_bolha);
    tempoExec_bolha=clock()-tempoExec_bolha;

// ************* QuickSort  ************* //
    contadorComp_quick=0;
    contadorTroca_quick=0;

    tempoExec_quick=clock();
    quickSortInvertido(vetor1,0,tamanho-1,&contadorComp_quick,&contadorTroca_quick);
    tempoExec_quick=clock()-tempoExec_quick;

// ************* MergeSort  ************* //
    contadorComp_merge=0;
    contadorTroca_merge=0;

    tempoExec_merge=clock();
    mergeSortInvertido(vetor2,0,tamanho-1,&contadorComp_merge,&contadorTroca_merge);
    tempoExec_merge=clock()-tempoExec_merge;

// ************* HeapSort  ************* //
    contadorComp_heap=0;
    contadorTroca_heap=0;

    tempoExec_heap=clock();
    heapSortInvertido(vetor3,tamanho,&contadorComp_heap,&contadorTroca_heap);
    tempoExec_heap=clock()-tempoExec_heap;
    guardarTempo(tempoExec_heap,&tempoExecTotal_heap);

printf("\n************************* ANALISE DE UM VETOR ORDENADO INVERSAMENTE **************************\n");
printf("|Metodo de Ordenacao|    N de troca    |    N de comparacao      |   Tempo de execucao (ms)  |\n");
printf("|     BubbleSort    |     %02d       |          %02d         |         %.4lf           |\n",contadorTroca_bolha,contadorComp_bolha,((double)tempoExec_bolha)/((CLOCKS_PER_SEC/1000)));
printf("|      QuickSort    |       %02d       |           %02d         |          %.4lf           |\n",contadorTroca_quick,contadorComp_quick,((double)tempoExec_quick)/((CLOCKS_PER_SEC/1000)));
printf("|       MegeSort    |       %02d       |            %02d         |          %.4lf           |\n",contadorTroca_merge,contadorComp_merge,((double)tempoExec_merge)/((CLOCKS_PER_SEC/1000)));
printf("|       HeapSort    |       %02d       |           %02d         |          %.4lf           |\n",contadorTroca_heap,contadorComp_heap,((double)tempoExec_heap)/((CLOCKS_PER_SEC/1000)));
   
}