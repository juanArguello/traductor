// Inclusion de libreria a ser utilizadas 
#include "analizadorSintactico.c"

/*
json.trad -> element.trad
element.trad -> object.trad | array.trad
object.trad -> object_.trad 
object_.trad -> attribute_list.trad | ε
array.trad -> array_.trad 
array_.trad -> <item> element_list.trad </item> | ε
element_list.trad -> element.trad element_list_.trad 
element_list_.trad -> </item> <item> element.trad element_list_.trad | ε
attribute_list.trad -> attribute.trad 
attribute_list_.trad ->attribute.trad attribute_list_.trad | ε
attribute.trad -> <attribute_name.trad> attribute_value.trad </attribute_name.trad>
attribute_name.trad -> string.lex
attribute_value.trad -> element_trad | string.lex | number.lex | true.lex | false.lex | null.lex
*/

//Prototipos de procedimientos
//para la traduccion
void json_trad();
void element_trad();
void object_trad();
void objectD_trad();
void array_trad();
void arrayD_trad();
void attribute_list_trad();
void attribute_listD_trad();
void element_list_trad();
void element_listD_trad();
void attribute_trad();
void attribute_name_trad();
void attribute_value_trad();
int espacio=0;
// procedimientos para la impresion en un archivos xml
void cadena_sin_comilla(char* );
void imprimir_espacios();
