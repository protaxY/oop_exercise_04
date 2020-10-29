//вариант 30 5-угольник, 6-угольник, 7-угольник

#include <tuple>
#include <iostream>
#include <math.h>

const double PI = 3.14159265358979323846264338327950288419716939937510;

template <class T>
struct Pentagon{
    using type = T;
    std::pair<T,T> Center;
    T Radius;
    Pentagon(T x, T y, T r): Center(x,y), Radius(r){
        if (Radius <= 0){
            throw std::invalid_argument("invalid pentagon radius");
        }
    }
};

template <class T>
struct Hexagon{
    using type = T;
    std::pair<T,T> Center;
    T Radius;
    Hexagon(T x, T y, T r): Center(x,y), Radius(r){
        if (Radius <= 0){
            throw std::invalid_argument("invalid hexagon radius");
        }
    }
};

template <class T>
struct Octagon{
    using type = T;
    std::pair<T,T> Center;
    T Radius;
    Octagon(T x, T y, T r): Center(x,y), Radius(r){
        if (Radius <= 0){
            throw std::invalid_argument("invalid octagon radius");
        }
    }
};

template <class T>
typename std::enable_if<std::is_same<T, Pentagon<typename T::type>>::value, void>::type printCurrentFigure(T &pentagon){
    for (int i = 0; i < 5; ++i){
        std::cout << "(" << pentagon.Center.first + pentagon.Radius * sin((double) (i * 72) / 180 * PI) << ", "
        << pentagon.Center.second + pentagon.Radius * cos((double) (i * 72) / 180 * PI) << ")";
    }
}

template <class T>
typename std::enable_if<std::is_same<T, Hexagon<typename T::type>>::value, void>::type printCurrentFigure(T &hexagon){
    for (int i = 0; i < 6; ++i){
        std::cout << "(" << hexagon.Center.first + hexagon.Radius * sin((double) (i * 60) / 180 * PI) << ", "
                  << hexagon.Center.second + hexagon.Radius * cos((double) (i * 60) / 180 * PI) << ")";
    }
}

template <class T>
typename std::enable_if<std::is_same<T, Octagon<typename T::type>>::value, void>::type printCurrentFigure(T &octagon){
    for (int i = 0; i < 8; ++i){
        std::cout << "(" << octagon.Center.first + octagon.Radius * sin((double) (i * 45) / 180 * PI) << ", "
                  << octagon.Center.second + octagon.Radius * cos((double) (i * 45) / 180 * PI) << ")";
    }
}

template <class T, size_t Index>
void print(std::tuple<T> &tup){
    if constexpr (std::tuple_size(tup) == Index){
        return;
    }
    printCurrentFigure(std::get<Index>(tup));
    print<T, Index + 1>;
}

template <class T>
typename std::enable_if<std::is_same<T, Pentagon<typename T::type>>::value, double>::type squareCurrentFigure(T &pentagon){
    return 5 * 0.5 * sin((double) 72 / 180 * PI) * pentagon.Radius * pentagon.Radius;
}

template <class T>
typename std::enable_if<std::is_same<T, Hexagon<typename T::type>>::value, double>::type squareCurrentFigure(T &hexagon){
    return 6 * 0.5 * sin((double) 60 / 180 * PI) * hexagon.Radius * hexagon.Radius;
}

template <class T>
typename std::enable_if<std::is_same<T, Octagon<typename T::type>>::value, double>::type squareCurrentFigure(T &octagon){
    return 8 * 0.5 * sin((double) 45 / 180 * PI) * octagon.Radius * octagon.Radius;
}

template <class T, size_t Index>
double square(std::tuple<T> &tup){
    if constexpr (std::tuple_size(tup) == Index){
        return 0;
    }
    return squareCurrentFigure(std::get<Index>(tup)) + square<T, Index + 1>;
}

int main() {
    std::cout << "tuple content: Pentagon<int>, Hexagon<int>, Octagon<int>, Pentagon<double>, Hexagon<double>, Octagon<double>\n";
    int x,y,radius;
    std::cout << "insert Pentagon<int> center cords and radius:";
    std::cin >> x >> y >> radius;
    Pentagon<int> intPentagon(x,y,radius);
    std::cout << "insert Hexagon<int> center cords and radius:";
    std::cin >> x >> y >> radius;
    Hexagon<int> intHexagon(x,y,radius);
    std::cout << "insert Octagon<int> center cords and radius:";
    std::cin >> x >> y >> radius;
    Octagon<int> intOctagon(x,y,radius);
    std::cout << "insert Pentagon<double> center cords and radius:";
    std::cin >> x >> y >> radius;
    Pentagon<double> doublePentagon(x,y,radius);
    std::cout << "insert Hexagon<double> center cords and radius:";
    std::cin >> x >> y >> radius;
    Hexagon<double> doubleHexagon(x,y,radius);
    std::cout << "insert Octagon<double> center cords and radius:";
    std::cin >> x >> y >> radius;
    Octagon<double> doubleOctagon(x,y,radius);
    std::tuple<Pentagon<int>, Hexagon<int>, Octagon<int>, Pentagon<double>, Hexagon<double>, Octagon<double>> tup(intPentagon, intHexagon, intOctagon, doublePentagon, doubleHexagon, doubleOctagon);
    //print<Pentagon<int>, Hexagon<int>, Octagon<int>, Pentagon<double>, Hexagon<double>, Octagon<double>>(tup);
    double summaryArea = square<Pentagon<int>, Hexagon<int>, Octagon<int>, Pentagon<double>, Hexagon<double>, Octagon<double>,0>(tup);
    return 0;
}
