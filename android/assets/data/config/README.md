Levels
===

Para crear niveles configura el fichero levels y crea la imagen(80x60px) del nivel con los colores adecuados:

	* Blanco: nada
	* Rojo: Puerta de entrada
	* Verde: Puerta de salida
	* Negro: Tierra por donde caminaran las entidades

GUI
===

Definicion de la interfaz

Acciones:

	* climb
	* stop
	* dig
	* stairs
	* bridge
	* wall
	* explosion
Ejemplo de Configuracion:

{
"GUI":{
        "buttons":[
                    {"position":{"x":5,"y":450,},"text":{"string":"climb","size":15,"font":"Outwrite",},"imageID":"defaultButton","size":{"width":100,"height":100,},"action":"climb"},
                    {"position":{"x":105,"y":450,},"text":{"string":"bridge","size":15,"font":"Outwrite",},"imageID":"defaultButton","size":{"width":100,"height":100,},"action":"bridge"},
                    {"position":{"x":205,"y":450,},"text":{"string":"stairs","size":15,"font":"Outwrite",},"imageID":"defaultButton","size":{"width":100,"height":100,},"action":"stairs"},
                ],
       },
}
