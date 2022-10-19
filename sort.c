#include <stdio.h>
#include <stdlib.h>
#include <string.h>





/*EL PIVOTE AL PRINCIPIO, ES EL ULTIMO ELEMENTO DEL ARRAY, Y LA POSICION PIVOTE ES EL INICIO DEL ARRAY, NO TENES QUE CAMBIAR DE LUGAR POR ESTO

QUICKSORT, DEFINE UN NUMERO AL QUE VOY A LLAMAR PIVOTE, Y CADA ITERACION VA A QUERER UBICAR ESTE NUMERO PIVOTE, OSEA, CADA ITERACION GUARDO UN ELEMENTO
SE ASUME QUE EL PIVOTE QUE ELEGIMOS, SE COLOCARIA EN LA PRIMER POSICION, Y RECORRO EL VECTOR COMPARANDO ESTE NUMERO PIVOTE CON LOS OTROS
SI ENCUENTRO UN NUMERO, MAS GRANDE EN ESTE CASO DIGAMOS (PUEDE SER MENOR), SE HACE UN SWAP DE ESTE ELEMENTO QUE ENCONTRE CON LA POSICION QUE MARQUE COMO PIVOTE
Y ADELANTE EN UNO LA POSICION DEL PIVOTE, ASI TERMINAR UNA ITERACION DEL VECTOR
CUANDO TERMINAMOS, AHORA CAMBIO EL PIVOTE A LA POSICION QUE QUEDO MARCADA COMO "POSICION PIVOTE"

ME QUEDA UNA MITAD DEL VECTOR CON ELEMENTOS MAYORES AL PRIMER ELEM PIVOTE, Y A LA IZQUIERDA LOS ELEMES MENORES
AHORA SE HACE EL SORT CON LOS ELEMENTOS A LA IZQUIERDA DEL VECTOR, OSEA, ELIJO EL ELEMENTO QUE QUEDO AL LADO IZQUIERDO DEL ELEMENTO DEL MEDIO Y HAGO EL SORT CON ESE ELEMENTO (LO MARCO COMO PIVOTE, Y RECORRO)
LUEGO, CON EL DERECHO, Y ASI

TIENE COMPLEJIDAD O(N CUADRADO)
EN EL CASO FELIZ, ES NLOGN, CUANDO SIEMPRE NOS QUEDA EL ELEMENTO PIVOTE A LA MITAD

*/
int particionar(int *vector, int tamanio)
{               //TIENE UNA COMPLEJIDAD O(N)
        int pos_pivote = tamanio-1;     
        int posicion_final_pivote = 0;//aca donde va a quedar al final del algoritmo

        for (int i = 0; i < tamanio-1;i++) {
                if (vector[i] < vector[pos_pivote]) {
                        swap(vector, i, posicion_final_pivote);
                        posicion_final_pivote++;
                }
        }
        swap(vector, posicion_final_pivote, tamanio-1);
        return posicion_final_pivote;
}

// T(N) = 2*T(N/2) + O(N) => NLOG(N)
//MULTIPLICADO POR 2 PORQUE INVOCO 2 VECES LA FUNCION, SOBRE 2 PORQUE ES A LA MITAD, O(N) POR EL PARTICIONAR
//EL MERGESORT ES SIEMPRE EL N/2, PERO EN QUICK SORT NO SIEMPRE
//POR LO TANTO EN QUICK SORT AL NO SER SIEMPRE LA DIVISION A LA MITAD, EL PEOR CASO ES QUE EL PIVOTE ME DE T(N-1)
// ASI QUE T(N) = T(N-1)+O(N), ACA NO TENGO FRACCION, NO DA TEOREMA MAESTRO, NO PUEDO APLICARLO
//
void quick_sort(int *vector, int tamanio)
{
        if (tamanio <= 1)
                return;

        int posicion_pivote = particionar(vector, tamanio);
        quick_sort(vector, posicion_pivote);
        quick_sort(vector+posicion_pivote+1, tamanio-posicion_pivote-1);
}


/*

DIGAMOS TENGO [2,124,23,5,89,-1,44,643,34]
QUIERO ORDENAR MENOR A MAYOR

DIVIDO A LA MITAD
[2,124,23,5]
DIVIDO
[2,124]
DIVIDO
[2]
HASTA QUE YA NO PUEDO DIVIDIR MAS A LA MITAD
AHORA, AGARRO LA OTRA MITAD, [124], NO SE HACE NADA OTRA VEZ SOLITO
SE UNE EL [2,124], TAN ORDENADOS, LITO
DEL LADO DERECHO ME QUEDO
[23,5]
DIVIDO
[23]
LITO
DIVIDO
[5]
AHORA HAGO MERGE, ORDENANDO
[5,23], ES COMO QUE VOY ORDENANDO CADA PARTE POR SEPARADO
AHORA TENGO EL [5,23] Y EL [2,124],
COMPARAO EL [2] Y EL [5] (LOS PRIMEROS ELEMENTOS RESPECTIVOS ARRAY)
AHORA, COMO 2 ES MENOR A 5 LO PONGO EN MI ARRAY UNIDO GORDO
[2, , , ,]
LUEGO, MOVI LA FLECHITA Y COMPARO [5] CON EL [124]
LITO, AHORA ARMO
[2,5, , ]
AHORA MOVI LA FLECHITA DEL OTRO
COMPARO EL [23] CON EL [124]
TUKI, [2,5,23, ]
Y COMO ME QUEDO QUE RECORRI TODA LA MITAD, METO EL 124
[2,5,23,124]
PUEDO HACER ESTO PORQUE CADA CACHITO ME LLEGA YA ESTA ORDENADO

AHORA HAGO EL ORDENAMIENTO CON LA OTRA MITAD PRINCIPAL ME QUEDO
[89, -1, 44, 643, 34]
DIVIDO
[89, -1]
DIVIDO
[89]
TUKI
AHORA VEO EL [-1]
TUKI
COMPARO, [89] CON [-1]
ARMO [-1, 89]
VUELVO AL AMBITO ANTERIOR
[44,643,34]
DIVIDO
[44], LITO ACA QUEDAMO ESTO
DIVIDO EL OTRO LADO
[643,34]
DIVIDO
[643], TUKI
EL OTRO
[34]
COMPARO [643] CON [34]
ME ARMA [34, 643]
AHORA COMPARO
[34, 643] CON EL [44]
COMPARO [34] CON [44]
TUKI
[34 , ,]
COMPARO [643] CON [44]
[34, 44, ]
QUEDO EL 643 SOLO, ASI QUE
[34,44,643]
Y AHORA COMPARO
Y SIGO, DEA COMPARO LOS QUE QUEDARON DE ESTA MITAD
DESPUES PROCEDO CON LAS 2 MITADES Y YA TA
*/
void merge(int *v1, int t1, int *v2, int t2)
{       //ESTE MERGE ES O(N)
        //SABEMOS V1 Y V2 ESTAN UNO DESPUES DEL OTRO

        int v3[t1+t2];

        int i1=0;
        int i2=0;
        int i3=0;

        while(i1 < t1 && i2 < t2) {
                if (v1[i1] <= v2[i2]) {
                        v3[i3] = v1[i1];
                        i1++;
                }else {
                        v3[i3] = v2[i2];
                        i2++;
                }
                i3++;
        }

        while (i1 < t1) {
                v3[i3] = v1[i1];
                i1++;
                i3++;
        }

        while (i2 < t2) {
                v3[i3] = v2[i2];
                i2++;
                i3++;
        }

        memcpy(v1,v3, (t1+t2)*sizeof(int));
        
}

void merge_inplace(int *v1, int t1, int *v2, int t2)
{
        int i1=0;
        int i2=0;
        int i3=0;

        int *v3 = v1;

        while(i1 < t1 && i2 < t2) {
                if (v1[i1] <= v2[i2]) {
                        v3[i3] = v1[i1];
                        i1++;
                }else {
                        int valor = v2[i2];
                        for(int i = t1; i > i1; i--) {
                                v1[i] = v1[i-1];
                        }
                        t1++;
                        i1++;
                        v3[i3] = valor;
                        i2++;
                }
                i3++;
        }

        memcpy(v1,v3, (t1+t2)*sizeof(int));
}

void merge_sort(int *vector, int tamanio)
{       //T(N) = 2*T(N/2)+O(N) MULTIPLICADO POR 2 YA QUE LO LLAMAMOS 2 VECES, ES N/2 YA QUE LO LLAMAMOS CON VECTORES QUE SON LA MITAD DEL TAMANIO DEL VECTOR ORIGINAL + O(N) QUE ES LA DE LA OPERACION MERGE
//PARTE RECURSIVA, N ELEVADO A LOG BASE B DE A, MI CASO QUEDA N ELEVADO A LOG BASE 2 DE 2, QUE ES N A LA 1. COMO COSAS IGUALES, MULTIPLICAMOS EL O(N) CON LOG(N) O(N)*LOG(N) = NLOGN
//EN LA VERSION CON EL MERGE_INSORT, ES 2*T(N/2) + O(N AL CUADRADO), COMO N < N AL CUADRADO, TIENE UN TIEMPO DE N CUADRADO

//POR TEOREMA MAESTRO, SI 2 PARTES SON IGUALES, AGARRAS CUALQUIER PARTE Y LO MULTIPLICAS POR LOG DE N, POR ESO ARRIBA COMO N = O(N), HICE NOMAS NLOG(N)
//SI LA PARTE NO RECURSIVA MAYOR QUE RECURSIVA, ME QUEDO CON LA PARTE NO RECURSIVA, COMO EL OTRO CASO DE ARRIBA, COMO O(N AL CUADRADO) > N, ME QUEDA O(N CUADRADO)
//SI PARTE RECURSIVA MAYOR QUE RECURSIVA, ME QUEDO CON LA PARTE RECURSIVA, OSEA, FACILITO
        if(tamanio <= 1)
                return;

        int mitad = tamanio/2;

        int *primer_vector = vector;
        int primer_vector_tamanio = mitad;

        int *segundo_vector = vector+primer_vector_tamanio;
        int segundo_vector_tamanio = tamanio-mitad;

        merge_sort(primer_vector, primer_vector_tamanio);
        merge_sort(segundo_vector, segundo_vector_tamanio);

        merge(primer_vector, primer_vector_tamanio, segundo_vector, segundo_vector_tamanio);
}




/*
ES UN METODO NO COMPARATIVO
TIENE UNA COMPLEJIDA O(n)
DIGAMOS TENGO EL VECTOR
[1,4,1,2,7,5,2]
TENGO QUE SABER EL RANGO DE LOS ELEMENTOS DEL ARRAY
ACA, PUEDO DECIR QUE VA DE 0 A 9
ME ARMO NUEVO VECTOR
[ , , , , , , , , , ,] (0 A 9 POSICIONES)

INICIALIZO VECTOR CON 0
[0,0,0,0,0,0,0,0,0,0]
AHORA, RECORRO EL PRIMER VECTOR
VEO QUE TIENE UN 1 EN LA PRIMER POSICION, INCREMENTO LA POSICION 1 EN 1 DEL VECTOR ARME
[0,1,0,0,0,0,0,0,0,0]
AHORA, TENGO UN 4, AUMENTO EN 1 LA POSICION 4
[0,1,0,0,1,0,0,0,0,0]
AHORA OTRO 1
[0,2,0,0,1,0,0,0,0,0] Y REPITO

LUEGO CUANDO TERMINE DE ITERAR, ME QUEDA ALGO TIPO
[0,2,2,0,1,1,0,1,0,0], PONELE
Y TENGO QUE IR SUMANDO IN PLACE DE ESTA MANERA
AGARRO POSICION 0 Y SUMO LO QUE HAY EN POSICION 0 Y 1
2 + 0 = 2
[0,2,2,0,---]
SUMO  1 Y 2
2 + 2 = 4
[0,2, 4, .....]
SUMO 2 Y 3 
[0,2,4, 4]
SUMO 3 Y 4
[0,2,4,4,5]
Y ASI HASTA EL FINAL (ESTO SE HACE TODO IN PLACE)

QUEDA [0,2,4,4,5,6,6,7,7,7]

AHORA, SI, CREO OTRO ARRAY QUE EMPIEZA EN 1 
SE HACE UN CAMINITO
AGARRAS EL PRIMER ELEMENTO DEL VECTOR ORIGINAL (EN ESTE CASO UN 1)
DE ACA VOY A LA POSICION 1 DEL VECTOR QUE RELLENE ANTES (EN ESTE CASO UN 2)
Y VAMOS A LA POSICION 2 DEL VECTOR QUE CREE Y SUMO UNO
[, 1, , , , ,]
Y RESTO EN 1 LA POSICION DEL OTRO
QUEDA [0,1,4,4,5,6,6,7,7,7]
LUEGO REPETIMOS CON EL PROXIMO ELEMENTO DEL PRIMER VECTOR, EN ESTE CASO UN 4
Y HACEMOS ESTE CAMINITO DE VUELTA
OSEA, VAS A LA POSICION 4 DEL VECTOR QUE ARMASTE
QUEDA [0,1,4,4,(5),6,6,7,7,7]
INSERTAS EN LA POSICION 5
[, 1,,,,4,]
Y RESTAS
QUEDA [0,1,4,4,(4),6,6,7,7,7]
HACIENDO LO MISMO HASTA EL TOPE QUEDA ORDENADO
Y EL VECTOR ENTRE MEDIOS QUEDO [0,0,2,4,4,5,6,6,7,7]
[1,1,2,2,4,5,7]
*/
void counting_sort()
{

}


int main()
{
        return 0;
}






/*


ESTABILIDAD UN SORT

CUANDO ORDENAMOS UN CONJUTNO DE DATOS, LOS ELEMENTOS MANTIENEN EL ORDEN RELATIVO ENTRE SI
MERGESORT ES ESTABLE
QUICKSORT NO ES ESTABLE

*/