// Inclusion de libreria a ser utilizadas 
#include "cabeceraTraductor.h"

// Implementacion de los procedimientos para la traduccion
 
void json_trad(){
    element_trad();
}

void element_trad(){
    if(t.componenteLexico == L_LLAVE){
        object_trad();
    }
    else if(t.componenteLexico == L_CORCHETE){
        array_trad();
    }
}

void array_trad(){  
    if(t.componenteLexico == L_CORCHETE){
        match(L_CORCHETE);
        arrayD_trad();
    }
}

void arrayD_trad(){
    if(t.componenteLexico == L_CORCHETE || t.componenteLexico == L_LLAVE){
		fputs("\n",salida);
        imprimir_espacios();
		fputs("<item>\n",salida);
		espacio += 1;
        element_list_trad();
        match(R_CORCHETE);
        imprimir_espacios();
		fputs("</item>\n",salida);
    }
    else if(t.componenteLexico == R_CORCHETE){
		espacio -= 1;
        match(R_CORCHETE);
    }
}

void element_list_trad(){
    if(t.componenteLexico == L_CORCHETE || t.componenteLexico == L_LLAVE){
        element_trad();
        element_listD_trad();
        
    }
}

void element_listD_trad(){
    if(t.componenteLexico == COMA){  
        match(COMA);
		imprimir_espacios();
		fputs("</item>\n",salida);
		imprimir_espacios();
		fputs("<item>\n",salida);
		espacio += 1;
        element_trad();
        element_listD_trad();     
    }
}

void object_trad(){
    if(t.componenteLexico == L_LLAVE){
        match(L_LLAVE);
        objectD_trad();
    }
}

void objectD_trad(){
    if(t.componenteLexico == LITERAL_CADENA){
        attribute_list_trad();
        match(R_LLAVE);

    }
    else if(t.componenteLexico == R_LLAVE){
        match(R_LLAVE);
    }
}

void attribute_list_trad(){
    if(t.componenteLexico == LITERAL_CADENA){
        attribute_trad();
        attribute_listD_trad();
    }
}

void attribute_listD_trad(){
    if (t.componenteLexico == R_LLAVE){
        espacio -= 1;
		return;
    }
    if(t.componenteLexico == COMA){
        match(COMA);
        attribute_trad();
        attribute_listD_trad();
    }
}

void attribute_trad(){
    if(t.componenteLexico == LITERAL_CADENA){
		imprimir_espacios();
        char lexema[TAMANHOLEXICO];
        strcpy(lexema,t.pe->lexema);
		fputs("<",salida);
        attribute_name_trad();
		fputs(">",salida);
        match(DOS_PUNTOS);
        attribute_value_trad();
		fputs("</",salida);
        cadena_sin_comilla(lexema);
		fputs(">\n",salida);		
    }
}

void attribute_name_trad(){
    if(t.componenteLexico == LITERAL_CADENA){    
        cadena_sin_comilla(t.pe->lexema);
        match(LITERAL_CADENA);
    }
}


void attribute_value_trad(){
    if(t.componenteLexico == L_CORCHETE || t.componenteLexico == L_LLAVE){
		espacio += 1;
        element_trad();
    }
    else if(t.componenteLexico == LITERAL_CADENA){
		fputs(t.pe->lexema, salida);
        match(LITERAL_CADENA);
    }
    else if(t.componenteLexico == LITERAL_NUM){
		fputs(t.pe->lexema, salida);
        match(LITERAL_NUM);
    }
    else if(t.componenteLexico == PR_TRUE){
		fputs(t.pe->lexema, salida);
        match(PR_TRUE);
    }
    else if(t.componenteLexico == PR_FALSE){
		fputs(t.pe->lexema, salida);
        match(PR_FALSE);
    }
    else if(t.componenteLexico == PR_NULL){
		fputs(t.pe->lexema, salida);
        match(PR_NULL);
    }
}

void cadena_sin_comilla(char* cadena){
    char string[TAMANHOLEXICO];
	char cad[TAMANHOLEXICO] = "";
    strcpy(string,cadena);
    int i=1;
    while(string[i] != '"'){
		cad[i-1] = string[i];
        i++;
    }
	fputs(cad, salida);
}

void imprimir_espacios(){
    int i;
    for (i=1;i<=espacio;i++){
        fputs("\t", salida);
    }
}


// funcion principal del programa
int main (int argc,char* args[]){
	initTabla();
	initTablaSimbolos();
    if(argc > 1)
    {
        if (!(archivo=fopen(args[1],"rt")))
        {
            printf("Archivo no encontrado.\n");
            exit(1);
        }
        getToken();
        json();
        if(accept){
            fclose(archivo);
            archivo=fopen(args[1],"rt");
			salida=(fopen("output.xml","w"));
            getToken();
            json_trad();
        }
		fclose(salida);
    }else{
        printf("Debe pasar como parametro el path al archivo fuente.\n");
        exit(1);
    }

    return 0;
}
