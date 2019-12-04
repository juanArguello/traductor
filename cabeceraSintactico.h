// Librerias utilizadas 
#include "analizadorLexico.c"


//Gramatica simplificada del BNF JSON
/* 
json               ---> element eof
element            ---> objet | array
object             ---> { object_
object_            --->  attribute_list } | }
array              ---> [ array_
array_             ---> element_list ] | ]
attribute_list     ---> attribute attribute_list_
attribute_list_    ---> ,attribute attribute_list | e
element_list       ---> element element_list_
element_list_ 	   --->  ,element element_list_ | e
attribute          ---> attribute_name : attribute_value
attribute_name     ---> string
attribute_value    ---> element | string | number | true | false | null
*/

//variables globales
int accept=1;

// prototipos de procedimientos
//procedimientos de la Gramatica JSON
void json();
void element(int []);
void object(int []);
void object_(int []);
void array(int []);
void array_(int []);
void attribute_list(int []);
void attribute_list_(int []);
void element_list(int []);
void element_list_(int []);
void attribute(int []);
void attribute_name(int []);
void attribute_value(int []);
//procedimientos para matchear y verificar las entradas de los
//conjuntos primeros y siguientes. Ademas emitir posible error sintacico.
void match(int);
void scanner(int []);
void errorSintactico();
void check_input(int [], int []);

