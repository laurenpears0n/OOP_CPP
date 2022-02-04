// PHYS 30762 Programming in C++
// Assignment 6
// Lauren Pearson

// Shapes class hierarchy

#include<iostream>
#include<cmath>

class shape
{
public:
  virtual int sides()=0;
  virtual double area()=0;
  virtual double volume()=0;
  virtual ~shape(){}
  virtual void print_info()=0;
};

class two_d_shape: public shape 
{
public:
  int no_sides;
  virtual int sides() {return no_sides;}
  virtual double area() {return 0;}
  virtual double volume() {return 0;}
  two_d_shape() {}
  two_d_shape(int no_sides) {}
  ~two_d_shape() {}
  void print_info(){ std::cout<<"Number of sides = "<<sides()<<std::endl<<"Area = "<<area()<<std::endl<<std::endl; }
};

class three_d_shape: public shape 
{
public:
  int no_sides;
  virtual int sides() {return no_sides;}
  virtual double area() {return 0;}
  virtual double volume() {return 0;}
  three_d_shape() {}
  three_d_shape(int no_sides) {}
  ~three_d_shape(){}
  void print_info(){ std::cout<<"Number of sides (faces) = "<<sides()<<std::endl<<"Area = "<<area()<<std::endl<<"Volume = "<<volume()<<std::endl<<std::endl; }
};


class rectangle: public two_d_shape
{
protected:
  double length, width;
public:
  rectangle() : two_d_shape{4}, length{}, width{} {}
  rectangle(double l, double w) : length{l}, width{w} {no_sides=4;}
  double area() {return length*width;}
  ~rectangle() {}
  void print_info()
  {
    std::cout<<"Rectangle, length = "<<length<<", width = "<<width<<std::endl;
    two_d_shape::print_info();
  }
};

class square: public rectangle
{
public:
  square() {}
  square(double a) : rectangle(a,a) {}
  ~square() {}
  void print_info()
  {
    std::cout<<"Square, side length = "<<length<<std::endl;
    two_d_shape::print_info();
  }  
};

class ellipse: public two_d_shape
{
protected:
  double axis_a, axis_b;
public:
  ellipse() : two_d_shape{1}, axis_a{}, axis_b{} {}
  ellipse(double a, double b) : axis_a{a}, axis_b{b}
  {
    no_sides=1;
  }
  double area() {return M_PI*axis_a*axis_b;}
  ~ellipse() {}
  void print_info()
  {
    std::cout<<"Ellipse, axes = "<<axis_a<<", "<<axis_b<<std::endl;
    two_d_shape::print_info();
  }  
};

class circle: public ellipse 
{
public:
  circle () {}
  circle(double a) : ellipse(a,a) {}
  ~circle() {}
  void print_info()
  {
    std::cout<<"Circle, radius = "<<axis_a<<std::endl;
    two_d_shape::print_info();
  }
};

class cuboid: public three_d_shape
{
protected:
  double length, width, depth;
public:
  cuboid () : three_d_shape{6}, length{}, width{}, depth{} {}
  cuboid(double l, double w, double d): length{l}, width{w}, depth{d}
  {
    no_sides=6;
  }
  double area() {return 2*(length*width + length*depth * depth*width);};
  double volume() {return length*width*depth;}
  ~cuboid() {}
  void print_info()
  {
    std::cout<<"Cuboid, length = "<<length<<", width = "<<width<<", depth = "<<depth<<std::endl;
    three_d_shape::print_info();
  }
};

class cube: public cuboid
{
public:
  cube () {}
  cube(double l) : cuboid{l,l,l} {}
  ~cube() {} 
  void print_info()
  {
    std::cout<<"Cube, side length = "<<length<<std::endl;
    three_d_shape::print_info();
  }
};

class ellipsoid: public three_d_shape
{
protected:
  double axis_a, axis_b, axis_c;
public:
  ellipsoid () : three_d_shape{1}, axis_a{}, axis_b{}, axis_c{} {}
  ellipsoid(double a, double b, double c) : axis_a{a}, axis_b{b}, axis_c{c}
  {
    no_sides=1;
  }
  double area() {return 4*M_PI*pow(((pow(axis_a*axis_b, 1.6)+pow(axis_a*axis_c, 1.6)+pow(axis_b*axis_c,1.6))/3),1/1.6);}
  double volume() {return (4*M_PI*axis_a*axis_b*axis_c)/3;}
  ~ellipsoid() {}
  void print_info()
  {
    std::cout<<"Ellipsoid, axes = "<<axis_a<<", "<<axis_b<<", "<<axis_c<<std::endl;
    three_d_shape::print_info();
  }
};

class sphere: public ellipsoid
{
public:
  sphere() {}
  sphere(double r): ellipsoid{r,r,r} {}
  ~sphere() {}
  void print_info()
  {
    std::cout<<"Sphere, radius = "<<axis_a<<std::endl;
    three_d_shape::print_info();
  }
};

class prism: public three_d_shape
{
private:
  int no_sides;
  two_d_shape *bs;
  double depth;
  int sides() {return no_sides;}
public:
  prism() : depth{} {}
  prism(double d, two_d_shape *base) : depth{d}, bs{base} 
  {
    no_sides = bs->sides()+2;
  }
  double volume() {return depth*bs->area();};
  ~prism() {}
  void print_info()
  {
    std::cout<<"Prism: "<<std::endl;
    std::cout<<"Base shape: "<<std::endl;
    bs->print_info();
    std::cout<<"Prism info: "<<std::endl;
    std::cout<<"Sides (faces) = "<<sides()<<std::endl;
    std::cout<<"Depth = "<<depth<<std::endl;
    std::cout<<"Volume = "<<volume()<<std::endl;
  }
};

int main()
{
  shape **shape_array = new shape*[9];
  shape_array[0] = new rectangle(3,5);
  shape_array[1] = new square{9};
  shape_array[2] = new ellipse{7,2};
  shape_array[3] = new circle{6};
  shape_array[4] = new cuboid{7,2,5};
  shape_array[5] = new cube{3};
  shape_array[6] = new ellipsoid{4,8,9};
  shape_array[7] = new sphere{5};
  shape_array[8] = new prism{4, new ellipse{8,6}};

  shape_array[0]->print_info();
  shape_array[1]->print_info();
  shape_array[2]->print_info();
  shape_array[3]->print_info();
  shape_array[4]->print_info();
  shape_array[5]->print_info();
  shape_array[6]->print_info();
  shape_array[7]->print_info();
  shape_array[8]->print_info();

  delete shape_array[0];
  delete shape_array[1];
  delete shape_array[2];
  delete shape_array[3];
  delete shape_array[4];
  delete shape_array[5];
  delete shape_array[6];
  delete shape_array[7];
  delete shape_array[8];
  delete[] shape_array;

  return 0;
}