#include <iostream>
#include <cmath>

// точка
class Point 
{
    public:
        double x, y;
        Point(double x = 0, double y = 0) : x(x), y(y) {}
};

// родительский класс "фигура"
class Shape 
{
    public:
        // чистая виртуальная функция для проверки принадлежности точки фигуре
        virtual bool contains(Point p) = 0; 
};

// класс "прямоугольник"
class Rectangle : public Shape 
{
    private:
        Point center;
        double width, height;
    public:
        Rectangle(Point c, double w, double h) : center(c), width(w), height(h) {}

    // проверка принадлежности точки прямоугольнику
    bool contains(Point p) override 
    {
        return (p.x >= center.x - width / 2 
                && p.x <= center.x + width / 2
                && p.y >= center.y - height / 2
                && p.y <= center.y + height / 2);
    }

    // создание прямоугольника
    static Rectangle* createRectangle() 
    {
        double cx, cy, w, h;
        std::cout << "Введите центр прямоугольника (x, y): ";
        std::cin >> cx >> cy;
        std::cout << "Введите ширину прямоугольника: ";
        std::cin >> w;
        std::cout << "Введите высоту прямоугольника: ";
        std::cin >> h;

        return new Rectangle(Point(cx, cy), w, h);
    }
};

// класс "круг"
class Circle : public Shape 
{
    private:
        Point center;
        double radius;
    public:
        Circle(Point c, double r) : center(c), radius(r) {}

    // проверка принадлежности точки кругу
    bool contains(Point p) override 
    {
        double dx = p.x - center.x;
        double dy = p.y - center.y;
        return (dx * dx + dy * dy) <= (radius * radius);
    }

    // создание круга
    static Circle* createCircle() 
    {
        double cx, cy, r;
        std::cout << "Введите центр круга (x, y): ";
        std::cin >> cx >> cy;
        std::cout << "Введите радиус круга: ";
        std::cin >> r;

        return new Circle(Point(cx, cy), r);
    }
};

// функция для проверки выражения (A && !(B || D)) || C
bool checkExpression(Shape* A, Shape* B, Shape* C, Shape* D, Point p) 
{
    bool inA = A->contains(p);
    bool inB = B->contains(p);
    bool inC = C->contains(p);
    bool inD = D->contains(p);
    return (inA && !(inB || inD)) || inC;
}

// метод ввода типа фигуры
int inputFigureType()
{
    int figureType;

    std::cout << "Выберите тип фигуры" << std::endl
              << "1 - Прямоугольник, 2 - Круг" << std::endl;
    std::cin >> figureType;

    while (figureType != 1 && figureType != 2)
    {
        std::cout << "Указанного типа фигуры не существует" << std::endl;
        std::cin >> figureType;
    }

    return figureType;
}

// меню
void menu() 
{
    int command;
    Shape* figures[4] = { nullptr };

    // меню через бесконечный цикл
    do 
    {
        std::cout << "Меню:\n" 
                  << "1. Ввести фигуры\n"
                  << "2. Проверить принадлежность точки\n"
                  << "0. Выход\n"
                  << "Выберите действие: ";
        std::cin >> command;

        switch (command)
        {
            // ввод фигур
            case 1: 
            {
                int figureType;

                for (int i = 0; i < 4; i++)
                {
                    figureType = inputFigureType();

                    if (figureType == 1)
                        figures[i] = Rectangle::createRectangle();
                    else if (figureType == 2)
                        figures[i] = Circle::createCircle();
                }
            }
            // проверка принадлежности точки множеству
            case 2: 
            {
                if (figures[0] && figures[1] && figures[2] && figures[3])
                {
                    double x, y;
                    std::cout << "Введите координаты точки (x, y): ";
                    std::cin >> x >> y;
                    Point point(x, y);

                    if (checkExpression(figures[0], figures[1], figures[2], figures[3], point))
                        std::cout << "Точка принадлежит множеству\n";
                    else 
                        std::cout << "Точка не принадлежит множеству\n";
                }
                else
                    std::cout << "Задайте фигуры\n";

                break;
            }
            case 0:
            {
                std::cout << "Выход\n";
                break;
            }
            default:
                std::cout << "Неизвестный код команды\n";
        }
    } 
    while (command != 0);

    // очистка классов
    for (int i = 0; i < 4; ++i) 
        delete figures[i];
}

int main() 
{
    setlocale(LC_ALL, "Russian");
    menu();
}