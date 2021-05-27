//-----------------------------------------------------------------------------------
//	OOP Lesson 3
//-----------------------------------------------------------------------------------

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cassert>

using namespace std;

//----------------------------------------------------------------------------------------------------------------------------
// 1. 
// Создать абстрактный класс Figure(фигура).Его наследниками являются классы Parallelogram(параллелограмм) 
// и Circle(круг).Класс Parallelogram — базовый для классов Rectangle(прямоугольник), Square(квадрат), Rhombus(ромб).
// Для всех классов создать конструкторы.Для класса Figure добавить чисто виртуальную функцию area() (площадь).
// Во всех остальных классах переопределить эту функцию, исходя из геометрических формул нахождения площади.
//----------------------------------------------------------------------------------------------------------------------------
class Figure
{
public:
	Figure() {}
	virtual double area() = 0;
};

class Parallelogram : public Figure
{
private:
	double m_a; //сторона
	double m_h; //высота
public:
	Parallelogram(double a, double h) : m_a(a), m_h(h) {}
	double getA() { return m_a; }
	double getH() { return m_h; }
	//S=ah
	double area() override
	{
		return getA() * getH();
	}
};

class Circle : public Figure
{
private:
	double m_radius;
public:
	Circle(double radius) : m_radius(radius) {}
	double getRadius() { return m_radius; }
	//S = pi*r^2
	double area() override
	{
		double r = getRadius();
		return r * r * M_PI;
	}
};

class Rectangle : public Parallelogram
{
public:
	//Прямоугольник - частный случай параллелограмма, когда все углы 90гр. 
	//Таким образом, одна из сторон соответсвует высоте
	//Поэтому специальной функции для расчета площади не требуется, можно использовать
	//функцию расчета площади параллелограмма
	Rectangle(double a, double b) : Parallelogram(a, b) {}
	//S = ab = ah
};

class Square : public Parallelogram
{
public:
	//Квадрат - частный случай параллелограмма, когда все углы 90гр и все стороны равны. 
	//Поэтому специальной функции для расчета площади не требуется, можно использовать
	//функцию расчета площади параллелограмма
	Square(double a) : Parallelogram(a, a) {}
};

class Rhombus : public Parallelogram
{
	//Ромб - частный случай параллелограмма
	//Ромб может быть задан cтороной и высотой

	Rhombus(double a, double h) : Parallelogram(a, h) {}

};


//----------------------------------------------------------------------------------------------------------------------------
// 
// 2.
// Создать класс Car (автомобиль) с полями company (компания) и model (модель). Классы-наследники: PassengerCar (легковой автомобиль) 
// и Bus (автобус). От этих классов наследует класс Minivan (минивэн). Создать конструкторы для каждого из классов, 
// чтобы они выводили данные о классах. Создать объекты для каждого из классов и посмотреть, в какой последовательности выполняются конструкторы. 
// Обратить внимание на проблему «алмаз смерти». 
// Примечание: если использовать виртуальный базовый класс, то объект самого "верхнего" базового класса создает самый "дочерний" класс
//----------------------------------------------------------------------------------------------------------------------------

class Car
{
private:
	string m_company;
	string m_model;
public:
	Car(const string& company, const string& model) : m_company(company), m_model(model)
	{
		cout << "Car: " << getCompany() << " model: " << getModel() << endl;
	}
	const string& getCompany() { return m_company; }
	const string& getModel() { return m_model; }
};

class PassengerCar : virtual public Car
{
public:
	PassengerCar(const string& company, const string& model) : Car(company, model)
	{
		cout << "Passenger car: " << getCompany() << " model: " << getModel() << endl;
	}
};

class Bus : virtual public Car
{
public:
	Bus(const string& company, const string& model) : Car(company, model)
	{
		cout << "Bus: " << getCompany() << " model: " << getModel() << endl;
	}

};

class Minivan : public PassengerCar, public Bus
{
public:
	Minivan(const string& company, const string& model) : PassengerCar(company, model), Bus(company, model), Car(company, model)
	{
		cout << "Minivan: " << getCompany() << " model: " << getModel() << endl;
	}
};



//----------------------------------------------------------------------------------------------------------------------------
// 3.
// Создать класс : Fraction(дробь).Дробь имеет числитель и знаменатель(например, 3 / 7 или 9 / 2).Предусмотреть, чтобы знаменатель не был равен 0. Перегрузить :
// математические бинарные операторы(+, -, *, / ) для выполнения действий с дробями
// унарный оператор(-)
// логические операторы сравнения двух дробей(== , != , <, >, <= , >= ).
// Примечание : Поскольку операторы < и >= , > и <= — это логические противоположности, попробуйте перегрузить один через другой.
// Продемонстрировать использование перегруженных операторов
//----------------------------------------------------------------------------------------------------------------------------

class Fraction
{
private:
	double m_numerator;  //числитель
	double m_denominator; //знаменатель
public:
	Fraction(double numerator, double denominator) : m_numerator(numerator), m_denominator(denominator)
	{
		assert(denominator != 0);
	}
	void printFraction()
	{
		cout << m_numerator << "/" << m_denominator << endl;
	}
	Fraction operator+ (const Fraction& frac)
	{
		return Fraction(m_numerator * frac.m_denominator + frac.m_numerator * m_denominator, m_denominator * frac.m_denominator);
	}
	Fraction operator- (const Fraction& frac)
	{
		return Fraction(m_numerator * frac.m_denominator - frac.m_numerator * m_denominator, m_denominator * frac.m_denominator);
	}
	Fraction operator* (const Fraction& frac)
	{
		return Fraction(m_numerator * frac.m_numerator, m_denominator * frac.m_denominator);
	}
	Fraction operator/ (const Fraction& frac)
	{
		return Fraction(m_numerator * frac.m_denominator, m_denominator * frac.m_numerator);
	}
	Fraction operator- () const
	{
		return Fraction(-m_numerator, m_denominator);
	}
	bool operator== (const Fraction& frac) const
	{
		return (m_numerator == frac.m_numerator) && (m_denominator == frac.m_denominator);
	}
	bool operator!= (const Fraction& frac) const
	{
		return !(*this == frac);
	}

	bool operator< (const Fraction& frac) const
	{

		return (m_numerator * frac.m_denominator < frac.m_numerator* m_denominator);
	}

	bool operator> (const Fraction& frac) const
	{
		return  (m_numerator * frac.m_denominator > frac.m_numerator * m_denominator);
	}

	bool operator<= (const Fraction& frac) const
	{
		return !(*this > frac);
	}

	bool operator>= (const Fraction& frac) const
	{
		return !(*this < frac);
	}

};


//----------------------------------------------------------------------------------------------------------------------------
// 4.
// Создать класс Card, описывающий карту в игре БлэкДжек.У этого класса должно быть три поля : 
// масть, значение карты и положение карты(вверх лицом или рубашкой).Сделать поля масть и значение карты 
// типом перечисления(enum).Положение карты - тип bool.Также в этом классе должно быть два метода :
// метод Flip(), который переворачивает карту, т.е.если она была рубашкой вверх, то он ее поворачивает лицом вверх, и наоборот.
// метод GetValue(), который возвращает значение карты, пока можно считать, что туз = 1.
//----------------------------------------------------------------------------------------------------------------------------

enum class eSuit { CLUBS, SPADES, DIAMONDS, HEARTS }; //крести, пики, буби, черви
enum class eValue { ACE = 1, KING, QUEEN, JACK, TEN, NINE, EIGHT, SEVEN, SIX, FIVE, FOUR, THREE, TWO, ONE };

class Card
{
	eSuit m_suit;
	eValue m_value;
	bool m_position;
public:
	Card(eSuit suit, eValue value, bool pos) : m_suit(suit), m_value(value), m_position(pos) {}
	void flip() { m_position = !m_position; }
	eValue getValue() { return m_value; }
};


//----------------------------------------------------------------------------------------------------------------------------
//		main
//----------------------------------------------------------------------------------------------------------------------------
int main()
{
	PassengerCar pc("Toyota", "Camry");
	Bus b("Volvo", "XC90");

	Minivan mv("Mazda", "5");

	Fraction f1(11, 3);
	Fraction f2(5, 8);

	f1.printFraction();
	Fraction fs = -f1;
	fs.printFraction();

	fs = f1 + f2;
	fs.printFraction();
	fs = f1 - f2;
	fs.printFraction();
	fs = f1 * f2;
	fs.printFraction();
	fs = f1 / f2;
	fs.printFraction();


	if (f1 == f2)
		cout << "equal" << endl;
	else
		cout << "not equal" << endl;

	if (f1 != f2)
		cout << "not equal" << endl;
	else
		cout << "equal" << endl;

	if (f1 < f2)
		cout << "f1 < f2" << endl;
	else
		cout << "f1 >= f2" << endl;

	if (f1 > f2)
		cout << "f1 > f2" << endl;
	else
		cout << "f1 <= f2" << endl;

	if (f1 <= f2)
		cout << "f1 <= f2" << endl;


	if (f1 >= f2)
		cout << "f1 >= f2" << endl;


	Card card(eSuit::CLUBS, eValue::ACE, true);
	card.flip();

}
