#include <iostream>
#include <cmath>

// точка
class Point 
{
    public:
        double x, y;
        // конструктор точки
        Point(double x = 0, double y = 0) : x(x), y(y) {}
};

// родительский класс "фигура"
class Shape 
{
    public:
        // виртуальная функция для проверки принадлежности точки фигуре
        virtual bool contains(Point p) = 0; 
};

// класс "прямоугольник"
class Rectangle : public Shape 
{
    private:
        Point center;
        double width, height;
    public:
        // конструктор класса
        Rectangle(Point c, double w, double h) : center(c), width(w), height(h) {}

    // проверка принадлежности точки прямоугольнику
    bool contains(Point p) override 
    {
        return (p.x >= center.x - width / 2 && p.x <= center.x + width / 2 &&
            p.y >= center.y - height / 2 && p.y <= center.y + height / 2);
    }
};

// класс "круг"
class Circle : public Shape 
{
    private:
        Point center;
        double radius;
    public:
        // конструктор класса
        Circle(Point c, double r) : center(c), radius(r) {}

    // проверка принадлежности точки кругу
    bool contains(Point p) override 
    {
        double dx = p.x - center.x;
        double dy = p.y - center.y;
        return (dx * dx + dy * dy) <= (radius * radius);
    }
};

// функция для проверки выражения (!A && (B || D)) || C
bool checkExpression(Shape* A, Shape* B, Shape* C, Shape* D, Point p) 
{
    bool inA = A->contains(p);
    bool inB = B->contains(p);
    bool inC = C->contains(p);
    bool inD = D->contains(p);
    return (!inA && (inB || inC)) || inD;
}

// функция для ввода типа фигуры с проверкой на корректность ввода
int inputFigureType(std::string Letter) 
{
    int figureType;
    while (true) 
    {
        std::cout << "Выберите тип фигуры " + Letter + " (1 - Прямоугольник, 2 - Круг): ";
        std::cin >> figureType;

        // валидация ввода
        if (figureType != 1 && figureType != 2) 
        {
            std::cin.clear();
            std::cout << "Введите 1 или 2\n\n";
        }
        else 
            break; 
    }
    return figureType;
}

// меню
void menu() 
{
    std::string letterName;
    int choice;
    Shape* A = nullptr, * B = nullptr, * C = nullptr, * D = nullptr;

    // меню через бесконечный цикл
    do 
    {
        std::cout << "\nМеню:\n";
        std::cout << "1. Ввести фигуры\n";
        std::cout << "2. Проверить принадлежность точки\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        switch (choice) 
        {
            case 1: 
            {
                // ввод фигур
                int figureType;

                // ввод A
                figureType = inputFigureType("A");

                // определяем тип фигуры
                if (figureType == 1) 
                {
                    // если прямоугольник
                    // центр, ширина, длина и создаём экземляр А
                    double cx, cy, w, l;
                    std::cout << "Введите центр, ширину и длину A:\n";
                    std::cin >> cx >> cy >> w >> l;
                    A = new Rectangle(Point(cx, cy), w, l);
                }
                else if (figureType == 2) 
                {
                    // если круг
                    // центр, радиус и создаём экземляр А
                    double cx, cy, r;
                    std::cout << "Введите центр и радиус A:\n";
                    std::cin >> cx >> cy >> r;
                    A = new Circle(Point(cx, cy), r);
                }

                // ввод B
                figureType = inputFigureType("B");
                if (figureType == 1) 
                {
                    double cx, cy, w, l;
                    std::cout << "Введите центр, ширину и длину B:\n";
                    std::cin >> cx >> cy >> w >> l;
                    B = new Rectangle(Point(cx, cy), w, l);
                }
                else if (figureType == 2) 
                {
                    double cx, cy, r;
                    std::cout << "Введите центр и радиус B:\n";
                    std::cin >> cx >> cy >> r;
                    B = new Circle(Point(cx, cy), r);
                }

                // ввод C
                figureType = inputFigureType("C");
                if (figureType == 1) 
                {
                    double cx, cy, w, l;
                    std::cout << "Введите центр, ширину и длину C:\n";
                    std::cin >> cx >> cy >> w >> l;
                    C = new Rectangle(Point(cx, cy), w, l);
                }
                else if (figureType == 2) 
                {
                    double cx, cy, r;
                    std::cout << "Введите центр и радиус C:\n";
                    std::cin >> cx >> cy >> r;
                    C = new Circle(Point(cx, cy), r);
                }

                // ввод D
                figureType = inputFigureType("D");
                if (figureType == 1) 
                {
                    double cx, cy, w, l;
                    std::cout << "Введите центр, ширину и длину D:\n";
                    std::cin >> cx >> cy >> w >> l;
                    D = new Rectangle(Point(cx, cy), w, l);
                }
                else if (figureType == 2) 
                {
                    double cx, cy, r;
                    std::cout << "Введите центр и радиус D:\n";
                    std::cin >> cx >> cy >> r;
                    D = new Circle(Point(cx, cy), r);
                }
                break;
            }
            case 2: 
            {
                if (A && B && C && D) 
                {
                    // проверка принадлежности точки множеству
                    double x, y;
                    std::cout << "Введите координаты точки (x, y): ";
                    std::cin >> x >> y;
                    Point point(x, y);

                    if (checkExpression(A, B, C, D, point))
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
    while (choice != 0);

    // очистка классов
    delete A;
    delete B;
    delete C;
    delete D;
    letterName = "";
}

int main() 
{
    setlocale(0, "");
    menu();
}
