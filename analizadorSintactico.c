// Inclusion de libreria a ser utilizadas 
#include "cabeceraSintactico.h"

//Implementacion de los procedimientos
//gramatica principal de la fuente json
void json(){
	int conj_siguiente[] = {COMA, R_CORCHETE, R_LLAVE, '\0'};
	//synchSet de sincronizacion
	element(conj_siguiente);
}

//El element puede ser un object o un array
void element(int synchSet[]){
    int conj_primero[] = {L_CORCHETE,L_LLAVE,'\0'};
    int conj_siguiente[] = {COMA,R_CORCHETE,R_LLAVE, '\0'};

    check_input(conj_primero, synchSet);

    if(t.componenteLexico == L_LLAVE)
        object(conj_siguiente);
    else if(t.componenteLexico == L_CORCHETE)
        array(conj_siguiente);

    check_input(conj_siguiente, conj_primero);
}

void object(int synchSet[]){
	int conj_primero[] = {L_LLAVE, '\0'};
	int conj_siguiente[] = {COMA, R_CORCHETE, R_LLAVE, '\0'};
	
	check_input(conj_primero, synchSet);

	if (t.componenteLexico == L_LLAVE) {
		match(L_LLAVE);
		object_(conj_siguiente);
	}
	
	check_input(conj_siguiente, conj_primero);
}

// object_ puede ser attribute_list R_LLAVE o R_LLAVE
void object_(int synchSet[]){
	int conj_primero[] = {LITERAL_CADENA, R_LLAVE, '\0'};

	int conj_siguiente[] = {COMA, R_CORCHETE, R_LLAVE, LITERAL_CADENA, '\0'};

	check_input(conj_primero, synchSet);

	if (t.componenteLexico == LITERAL_CADENA){
		attribute_list(synchSet);
		match(R_LLAVE);
	} else if (t.componenteLexico == R_LLAVE){
		match(R_LLAVE);
	}

	check_input(conj_siguiente, conj_primero);
}

void array(int synchSet[]){
	int conj_primero[] = {L_CORCHETE, '\0'};
	int conj_siguiente[] = {COMA, R_CORCHETE, R_LLAVE, '\0'};

	check_input(conj_primero, synchSet);

	if (t.componenteLexico == L_CORCHETE){
		match(L_CORCHETE);
		array_(conj_siguiente);
	}

	check_input(conj_siguiente, conj_primero);

}

// array_ puede ser element_list R_CORCHETE o R_CORCHETE
void array_(int synchSet[]){
	int conj_primero[] = {L_LLAVE, L_CORCHETE, R_CORCHETE, '\0'};

	int conj_siguiente[] = {COMA, R_CORCHETE, R_LLAVE, L_CORCHETE, '\0'};

	check_input(conj_primero, synchSet);

	if ((t.componenteLexico == L_LLAVE) || (t.componenteLexico == L_CORCHETE)){
		
		element_list(conj_siguiente);
		match(R_CORCHETE);
	}
	else if(t.componenteLexico == R_CORCHETE){
		match(R_CORCHETE);
		
	}

	check_input(conj_siguiente, conj_primero);
}


void attribute_list(int synchSet[]){
	int conj_primero[] = {LITERAL_CADENA, '\0'};
	int conj_siguiente[] = {R_LLAVE, '\0'};

	check_input(conj_primero, synchSet);

	if (t.componenteLexico == LITERAL_CADENA){
		attribute(conj_siguiente);
		attribute_list_(conj_siguiente);
	}

	check_input(conj_siguiente, conj_primero);

}

// attribute_list_ puede ser COMA attribute attribute_list o empty string
void attribute_list_(int synchSet[]){

	if (t.componenteLexico == R_LLAVE)
        return;

	int conj_primero[] = {COMA, '\0'};
	int conj_siguiente[] = {R_LLAVE, '\0'};

	check_input(conj_primero, synchSet);


	if (t.componenteLexico == COMA){
		match(COMA);
		attribute(conj_siguiente);
		attribute_list_(conj_siguiente);
	}

	check_input(conj_siguiente, conj_primero);
}


void element_list(int synchSet[]){
	int conj_primero[] = {L_LLAVE, L_CORCHETE, '\0'};
	int conj_siguiente[] = {R_CORCHETE, '\0'};

	check_input(conj_primero, synchSet);

	if((t.componenteLexico == L_LLAVE) || (t.componenteLexico == L_CORCHETE)){
		element(conj_siguiente);
		element_list_(conj_siguiente);
	}

	check_input(conj_siguiente, conj_primero);
}

// element_list_ puede ser COMA element element_list_ o empty string
void element_list_(int synchSet[]){

	if(t.componenteLexico == R_CORCHETE)
       return;

	int conj_primero[] = {COMA,'\0'};
	int conj_siguiente[] = {R_CORCHETE, '\0'};

	check_input(conj_primero, synchSet);

	

	if (t.componenteLexico == COMA){
		match(COMA);
		element(conj_siguiente);
		element_list_(conj_siguiente);
	}

	check_input(conj_siguiente, conj_primero);
}



void attribute(int synchSet[]){
	int conj_primero[] = {LITERAL_CADENA, '\0'};
	int conj_siguiente[] = {COMA, R_LLAVE, '\0'};

	check_input(conj_primero, synchSet);

	if (t.componenteLexico == LITERAL_CADENA){
		attribute_name(conj_siguiente);
		match(DOS_PUNTOS);
		attribute_value(conj_siguiente);
	}

	check_input(conj_siguiente, conj_primero);
}

// attribute_name tiene solamente LITERAL_CADENA
void attribute_name(int synchSet[]){
	int conj_primero[] = {LITERAL_CADENA, '\0'};
	int conj_siguiente[] = {DOS_PUNTOS, '\0'};

	check_input(conj_primero, synchSet);

	if (t.componenteLexico == LITERAL_CADENA)
		match(LITERAL_CADENA);

	check_input(conj_siguiente, conj_primero);
}

// attribute_value puede ser element o LITERAL_CADENA o LITERAL_NUM o
// PR_TRUE o PR_FALSE o PR_NULL
void attribute_value(int synchSet[]){
	int conj_primero[] = {L_LLAVE, L_CORCHETE, LITERAL_CADENA,
		LITERAL_NUM, PR_TRUE, PR_FALSE, PR_NULL, '\0'};
	int conj_siguiente[] = {COMA, R_LLAVE, '\0'};

	check_input(conj_primero, synchSet);

	if (t.componenteLexico == L_LLAVE){
		element(conj_siguiente);
	}
	else if (t.componenteLexico == L_CORCHETE) {
		element(conj_siguiente);
	}
	else if (t.componenteLexico == LITERAL_CADENA){
		match(LITERAL_CADENA);
	}
	else if (t.componenteLexico == LITERAL_NUM){
		match(LITERAL_NUM);
	}
	else if (t.componenteLexico == PR_TRUE){
		match(PR_TRUE);
	}
	else if (t.componenteLexico == PR_FALSE){
		match(PR_FALSE);
	}
	else if (t.componenteLexico == PR_NULL){
		match(PR_NULL);
	}

	check_input(conj_siguiente, conj_primero);

}

//machea el token y llama al siguiente elemento 
void match(int expectedToken){
    if(t.componenteLexico == expectedToken)
        getToken();
}

//si no esta en el synchSet llama a getToken() 
// imprime errores de la veificacion de entrada
void scanner(int synch[]){
    errorSintactico();
	int indice1 = 0;
    while(t.componenteLexico != synch[indice1] && t.componenteLexico != EOF){   
        if (synch[indice1] == '\0'){
            getToken();
            indice1=0;        
        }
        indice1++;
    }
    
    getToken();
    return;    	   
}

//muestra los errores en pantalla del usuario
void errorSintactico(){
	accept=0;
   	printf("\nError sintactico: Linea %d Se encontro %s\n", numeroLinea, t.pe->lexema);
}

// verifica la entradas
void check_input(int conj_primero[], int conj_siguiente[]){

    int indice1=0;
    if(t.componenteLexico == EOF)
    	return;

    //entra cuando no hay errores
    while(conj_primero[indice1] != '\0') 
    {
        if(t.componenteLexico == conj_primero[indice1])
            return;
        indice1++;
    }
 
 	indice1=0;    
    
    int synchSet[]={1}; //acumulador
    
    while(conj_primero[indice1] != '\0'){ 
        synchSet[indice1] = conj_primero[indice1];
        indice1++;
    }
    int indice2=0;

    while(conj_siguiente[indice2] != '\0'){
        synchSet[indice1] = conj_siguiente[indice2];
        indice1++; //aumenta indice1
        indice2++; //aumenta indice2
    }
    scanner(synchSet);
}

