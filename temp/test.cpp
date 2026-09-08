#include <iostream>

class Polygon {
public:
 void print() {std::cout << "Polygon" << std::endl;}
};
class Quadrangle : public Polygon {
public:
 void print() {std::cout << "Quadrangle" << std::endl;}
};
class Rectangle : public Quadrangle {
public:
 void print() {std::cout << "Rectangle" << std::endl;}
};  


main() {
//  Rectangle rectangle;
//  Rectangle* rectanglePtr = &rectangle;
//  //rectangle.print();
//  rectanglePtr-> print();
//  ((Polygon*)rectanglePtr)-> print();
 
//  Quadrangle* quadrangle;
 
//  quadrangle = rectanglePtr;
//  quadrangle->print();
 
 Polygon* polygon;

//  polygon->print();

 ((Quadrangle*)polygon)-> print();
//((Polygon)rectangle).print(); 
}