#include <iostream>
#include <SFML/Graphics.hpp>

int main(){
        sf::Vector2i position;
        int array[10*5];
        int xWidth = 10;
        int yHeight = 5;
        int array1[10][5];
        std::cout << "Array getting Ready" << std::endl;
        for(int y=0;y<yHeight;++y){
            for(int x=0;x<xWidth;++x){
                array1[x][y] = x*y;
                array[xWidth*y+x] = array1[x][y];
                std::cout << "Pos: " << (xWidth*y+x) << std::endl;
            }
        }
        position.x = 300;
        position.y = 400;
        std::cout << "Cambiamos posiciones de vertex" << std::endl;
        if(position.x != 0 && position.y != 0){
            xWidth += position.x;
            yHeight += position.y;
            std::cout << "Array Mirando valores desde otro sitio";
            for(int y=position.y;y<yHeight;++y){
                for(int x=position.x;x<xWidth;++x){
                    std::cout << "pos: " <<(xWidth-position.x)*(y-position.y)+(x-position.x)
                    << " Contenido: " << array[(xWidth-position.x)*(y-position.y)+(x-position.x)] << std::endl;
                }
            }
        }
        std::cout << "ARRAY 2D" << std::endl;
        for(int i=0;i<10;++i){
            for(int j=0;j<5;++j){
                std::cout << "POS: " << i<< ", "<<j << " Contenido: " << array1[i][j] << std::endl;
            }
        }
        xWidth = 10;
        yHeight = 5;
        std::cout << "ARRAY 1D de posicion fija" << std::endl;
        sf::FloatRect test(300,400,10,5);
        if((xWidth*(401-position.y)+(305-position.x))< xWidth*yHeight){
            //test.contains(305,401)
                // para sacar posiciones directamente se resta la posicion actual
                // con la posicion que quieres ir, se tiene que comprobar que este dentro del rango.
            std::cout << "la posicion esta dentro del rectangulo."<< std::endl;
            std::cout << "Pos Hormiga: 5,1 calc: " << (xWidth*(401-position.y)+(305-position.x))<< " Contenido: " << array[(xWidth*(401-position.y)+(305-position.x))] << std::endl;
        }else{
            std::cout << "la posicion NO esta dentro del rectangulo."<< std::endl;
        }
    return 0;
}
