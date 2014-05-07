Configuracion de Componentes
===

Aqui esta la lista de componentes disponibles con sus parametros.

Componentes:
###

    * Transformable: Componente que indicara que tiene posicion, cuan grande es respecto al tamaño de la sprite proporcionada y su rotacion.
        {
            "id":"transform",
            "properties":{
                            "position":{"x":0,"y":0,},
                            "scale":{"x":1,"y":1,},
                            "rotation":90,
                        },
        },
    * Sprite: Componente para que salga en la pantalla.
        {
            "id":"sprite",
            "properties":{
                            "id":"<ID textura de assets.json>",
                        },
        },
    * Bounds: Componente para que choque contra otras entidades, el suelo etc.
        {
            "id":"bounds",
            "properties":{
                            "left":0,
                            "top":0,
                            "width":10,
                            "height":10,
                        },
        },
    * Destructible: Componente para hacer que una entidad sea destructible, utiliza assets[Imagenes].
        {
            "id":"destructible",
            "properties":{
                            "position":{"x":10,"y":10,},
                            "imageID":"<ID imagen de assets.json>",
                        },
        },
    * In: Componente que hace que aparezcan entidades.
        {
            "id":"in",
            "properties":{
                        },
        },
    * Out: Componente que hace que desaparezcan entidades.
        {
            "id":"out",
            "properties":{
                        },
        },
