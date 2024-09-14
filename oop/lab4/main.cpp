#include "figures/figures.h"
#include "figures/array.h"

#include <iostream>

using namespace lab4;

template<Number T>
class MainRoutine final {
private:
    void eraseFigure() {
        std::cout << "Input figure index to delete: ";
        size_t n;
        n--;
        std::cin >> n;
        if (n >= data.size()) {
            std::cout << "There's no figure with index " << n + 1 << ".\n";
            return ;
        }
        data.erase(n);
    }

    void pushFigure() {
        std::cout << "Input type of figure from list: [square, triangle, octagon]\n";
        std::string type;
        std::cin >> type;
        try {
            if (type == "square") {
                Square<T> sq;
                std::cin >> sq;
                data.pushBack(std::make_shared<Square<T>>(sq));
            } else if (type == "triangle") {
                Triangle<T> tr;
                std::cin >> tr;
                data.pushBack(std::make_shared<Triangle<T>>(tr));
            } else if (type == "octagon") {
                Octagon<T> oct;
                std::cin >> oct;
                data.pushBack(std::make_shared<Octagon<T>>(oct));
            } else {
                std::cout << "Unknown figure name.\n";
                return;
            }
        } catch (std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
            return ;
        }
        std::cout << "Success.\n";
    }

    void wholeArea() {
        double area = 0;
        for (size_t i = 0; i < data.size(); i++) {
            area += static_cast<double>(*data[i]); 
        }
        std::cout << "General data area: " << area << std::endl;
    }

    void info() {
        std::cout << "Info: \n";
        for (int i = 0; i < data.size(); i++) {
            std::cout << (i + 1) << ":\n";
            std::cout << "  area : " << static_cast<double>(*data[i]) << "\n" <<
                         "  geometric_center : " << data[i]->geometricCenter() << "\n"; 
        }
    }

    Array<std::shared_ptr<Figure<T>>> data;
public:
    void start() {
        std::cout << "Input command from list: [push, erase, info, area]. To exit type: [exit, e, ex]\n";
        std::string command;
        std::cout << "> ";
        std::cin >> command;
        while (command != "exit" && command != "e" && command != "ex") {
            std::cout << "--------------------------------\n";
            if (command == "push") {
                pushFigure();
            } else if (command == "info") {
                info();
            } else if (command == "erase") {
                eraseFigure();
            } else if (command == "area") {
                wholeArea();
            } else {
                std::cout << "Unknown command.\n";
            }
            std::cout << "Input command from list: [push, erase, info, area]. To exit type: [exit, e, ex]\n> ";
            std::cin >> command;
        }
    }
};

int main() {
    MainRoutine<double> r;
    r.start();
}