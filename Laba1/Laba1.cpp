// Laba1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cmath>
using namespace std;
const int a = 13;
const double b = -0.2;
const double c = 1.44;
const double d = 0.23;
const double eps = 0.0001;

const double e = 2.718;
double func(double x, double y) {
    return a * x + b * y + pow(e, c * pow(x, 2) + d * pow(y, 2));
}
double func_derivate_by_x(double x, double y) {
    return a+ 2*c*x * pow(e, c * pow(x, 2) + d * pow(y, 2));
}
double func_derivate_by_y(double x, double y) {
    return b+ 2*d*y * pow(e, c * pow(x, 2) + d * pow(y, 2));
}
double alpha = 1;
struct Grad {
    double x;
    double y;
    
    Grad(double x, double y) {
        this->x = func_derivate_by_x(x,y);
        this->y = func_derivate_by_y(x,y);
    }
   
    Grad(const Grad &g) {
        this->x = g.x;
        this->y = g.y;
    }
    void nextPoint(double x, double y) {
        this->x = x - alpha * this->x;
        this->y = y - alpha * this->y;
  
    }
    void reload(double x, double y) {
        this->x = func_derivate_by_x(x, y);
        this->y = func_derivate_by_y(x, y);
    }
    double lengthGradient() {
        return sqrt(pow(this->x, 2) + pow(this->y, 2));
    }
};

Grad nextPoint(double x, double y) {
    Grad gr(x, y);
    gr.x = x - alpha * gr.x;
    gr.y = y - alpha * gr.y;
    return gr;
}
int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "a:" << a << endl;
    cout << "b:" << b << endl;
    cout << "c:" << c << endl;
    cout << "d:" << d << endl;
    double x = 0;
    double y = 0;
    int index = 0;;
    
    cout << "Начальные точки:(" << x << ',' << y << ')' << endl;
    cout << "Index" << "\t" << "X" << "\t" << "Y" << "\t" << "f(x,y)" << "\t" << "dF/dx" << "\t" << "dF/dx" << "\t" << "alpha" << endl;
    Grad grad(x, y);
    std::cout.precision(4);
    std::cout.setf(std::ios::fixed, std::ios::floatfield);
    while (grad.lengthGradient() >= eps)
    {
        Grad next = nextPoint(x, y); 
        double currentValue = func(x, y);

        if (func(next.x, next.y) > currentValue) {
            alpha /= 2;
           grad.reload(x, y);
        
        }
        else
        {
            
            cout <<index++<< "\t" << x << "\t" << y << " " << currentValue << "\t" << grad.x << "\t" << grad.y << "\t" << alpha << endl;
            x = next.x;
            y = next.y;
            grad.reload(x,y);
        }
    }

    cout <<endl<< "f min = f(" << x << ',' << y << ") = " << func(x, y) << endl;
}

