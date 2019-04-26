// 2018.10.13 20171612 - Sungil Kim
// Main.cpp
#include <iostream> // input output stream.
#include "Array.h" // Array Class is defined here.
#include "RangeArray.h" // Range Array Class is defined here.
// "using namespace std" can be danger.
// So, I'll use std::cout, std::endl
int main(){
    int i,x,y;
    // Here, Array Start.
    Array a(10), b(5);
    for(i=0;i<a.length();i++){
        a[i] = i + 1;
    }
    for(i=0;i<b.length();i++){
        b[i] = i * 2;
    }
    std::cout << "a(10) ";
    a.print();
    std::cout << "b(5) ";
    b.print();
	std::cout << "a[-1] ";
    a[-1] = 7;
    x = a[0];
    y = b[0];
    std::cout << "a[0] = " << x << " b[0] = " << y << std::endl;
    // Here, Array End.
    // Range Array Start.
    RangeArray c(-1,3), d(3,7);
    for(i=c.baseValue();i<=c.endValue();i++){
        c[i] = i * 3;
    }
    for(i=d.baseValue();i<=d.endValue();i++){
        d[i] = i * 4;
    }
    std::cout << "c(-1,3) ";
    c.print();
    std::cout << "d(3,7) ";
    d.print();
    std::cout << "c[-2] ";
    c[-2] = 3;
    x = c[-1]; y = d[3];
    std::cout << "c[-1] = " << x << " d[3] = " << y << std::endl;

    return 0;
}
