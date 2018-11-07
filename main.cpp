#include <iostream>
#include <cassert>
#include <stdexcept>
#include <string>
using namespace std;

class Fraction {
public:
    Fraction( int inNumerator = 0, int inDenominator = 1);
    enum RelationalOperators{
        LESS_THAN, GREATER_THAN, LESS_THAN_OR_EQUAL, GREATER_THAN_OR_EQUAL, EQUAL, NOT_EQUAL
    };
    enum ArithmeticOperators{
        ADD, SUBTRACT
    };
    friend std::ostream& operator<<(std::ostream& leftOS, const Fraction& rightOperand);
    friend bool operator<(const Fraction& leftOperand, const Fraction& rightOperand);
    friend bool operator>(const Fraction& leftOperand, const Fraction& rightOperand);
    friend bool operator<=(const Fraction& leftOperand, const Fraction& rightOperand);
    friend bool operator>=(const Fraction& leftOperand, const Fraction& rightOperand);
    friend bool operator!=(const Fraction& leftOperand, const Fraction& rightOperand);
    friend bool operator==(const Fraction& leftOperand, const Fraction& rightOperand);

    friend Fraction operator+(const Fraction& leftOperand, const Fraction& rightOperand);
    friend Fraction operator-(const Fraction& leftOperand, const Fraction& rightOperand);
    friend Fraction operator*(const Fraction& leftOperand, const Fraction& rightOperand);
    friend Fraction operator/(const Fraction& leftOperand, const Fraction& rightOperand);

    Fraction operator+=(const Fraction& rightOperand);
    Fraction operator-=(const Fraction& rightOperand);
    Fraction operator*=(const Fraction& rightOperand);
    Fraction operator/=(const Fraction& rightOperand);

    Fraction operator++();
    Fraction operator++(int);
    Fraction operator--();
    Fraction operator--(int);
private:
    int numerator;
    int denominator;
    friend bool compareFractions(const Fraction& leftOperand, const Fraction& rightOperand, RelationalOperators type);
    friend Fraction addOrSubtract(const Fraction& leftOperand, const Fraction& rightOperand, ArithmeticOperators type);
};







Fraction::Fraction( int inNumerator, int inDenominator){
    assert(inDenominator != 0);
    numerator = inNumerator;
    denominator = inDenominator;
}






std::ostream& operator<<(std::ostream& leftOutput, const Fraction& rightOperand) {
    leftOutput << rightOperand.numerator << "/" << rightOperand.denominator;
    return leftOutput;
}












bool compareFractions(const Fraction& leftOperand, const Fraction& rightOperand, Fraction::RelationalOperators type){
    int leftProduct = leftOperand.numerator * rightOperand.denominator;
    int rightProduct = leftOperand.denominator * rightOperand.numerator;
    switch(type){
        case Fraction::LESS_THAN:
            return leftProduct < rightProduct;
        case Fraction::GREATER_THAN:
            return leftProduct > rightProduct;
        case Fraction::LESS_THAN_OR_EQUAL:
            return leftProduct <= rightProduct;
        case Fraction::GREATER_THAN_OR_EQUAL:
            return  leftProduct >= rightProduct;
        case Fraction::EQUAL:
            return leftProduct == rightProduct;
        case Fraction::NOT_EQUAL:
            return leftProduct != rightProduct;
    }
}






bool operator<(const Fraction& leftOperand, const Fraction& rightOperand){
    return compareFractions(leftOperand, rightOperand, Fraction::LESS_THAN);
}






bool operator>(const Fraction& leftOperand, const Fraction& rightOperand){
    return compareFractions(leftOperand, rightOperand, Fraction::GREATER_THAN);
}






bool operator<=(const Fraction& leftOperand, const Fraction& rightOperand){
    return compareFractions(leftOperand, rightOperand, Fraction::LESS_THAN_OR_EQUAL);
}






bool operator>=(const Fraction& leftOperand, const Fraction& rightOperand){
    return compareFractions(leftOperand, rightOperand, Fraction::GREATER_THAN_OR_EQUAL);
}






bool operator!=(const Fraction& leftOperand, const Fraction& rightOperand){
    return compareFractions(leftOperand, rightOperand, Fraction::NOT_EQUAL);
}






bool operator==(const Fraction& leftOperand, const Fraction& rightOperand){
    return compareFractions(leftOperand, rightOperand, Fraction::EQUAL);
}






Fraction addOrSubtract(const Fraction& leftOperand, const Fraction& rightOperand, Fraction::ArithmeticOperators type){
    int leftNumerator = (leftOperand.numerator * rightOperand.denominator);
    int rightNumerator = (rightOperand.numerator * leftOperand.denominator);
    int newNumerator;
    switch(type){
        case Fraction::ADD:
            newNumerator = leftNumerator + rightNumerator;
            break;
        case Fraction::SUBTRACT:
            newNumerator = leftNumerator - rightNumerator;
            break;
        default:
            throw std::invalid_argument("Invalid arithmetic operator type");
    }
    int newDenominator = leftOperand.denominator * rightOperand.denominator;
    Fraction sum(newNumerator, newDenominator);
    return sum;
}




Fraction operator+(const Fraction& leftOperand, const Fraction& rightOperand){
    return addOrSubtract(leftOperand, rightOperand, Fraction::ADD);
}






Fraction operator-(const Fraction& leftOperand, const Fraction& rightOperand){
    return addOrSubtract(leftOperand, rightOperand, Fraction::SUBTRACT);
}






Fraction operator*(const Fraction& leftOperand, const Fraction& rightOperand){
    int newNumerator = leftOperand.numerator * rightOperand.numerator;
    int newDenominator = leftOperand.denominator * rightOperand.denominator;
    Fraction product(newNumerator, newDenominator);
    return product;
}






Fraction operator/(const Fraction& leftOperand, const Fraction& rightOperand){
    int newNumerator = leftOperand.numerator * rightOperand.denominator;
    int newDenominator = leftOperand.denominator * rightOperand.numerator;
    Fraction quotient(newNumerator, newDenominator);
    return quotient;
}






Fraction Fraction::operator+=(const Fraction& rightOperand){

    *this = *this + rightOperand;
    return *this;
}






Fraction Fraction::operator-=(const Fraction& rightOperand){

    *this = *this - rightOperand;
    return *this;
}






Fraction Fraction::operator*=(const Fraction& rightOperand){

    *this = *this * rightOperand;
    return *this;
}






Fraction Fraction::operator/=(const Fraction& rightOperand){

    *this = *this / rightOperand;
    return *this;
}







Fraction Fraction::operator++(){
    Fraction one(1);
    *this =  addOrSubtract(*this, one, Fraction::ADD);
    return *this;
}






Fraction Fraction::operator++(int){
    Fraction temp(numerator, denominator), one(1), incrementedFraction;
    incrementedFraction = addOrSubtract(*this, one, Fraction::ADD);
    denominator = incrementedFraction.denominator;
    numerator = incrementedFraction.numerator;
    return temp;
}







Fraction Fraction::operator--(){
    Fraction one(1,1);
    *this = addOrSubtract(*this, one, Fraction::SUBTRACT);
    return *this;
}






Fraction Fraction::operator--(int){
    Fraction temp(numerator, denominator), one(1) , decrementedFraction;
    decrementedFraction = addOrSubtract(*this, one, Fraction::SUBTRACT);
    denominator = decrementedFraction.denominator;
    numerator = decrementedFraction.numerator;
    return temp;
}






void BasicTest();
void RelationTest();
void BinaryMathTest();
void MathAssignTest();
string boolString(bool convertMe);







int main()
{
    BasicTest();
    RelationTest();
    BinaryMathTest();
    MathAssignTest();
}






void BasicTest()
{
    cout << "\n----- Testing basic Fraction creation & printing\n";

    const Fraction fr[] = {Fraction(4, 8), Fraction(-15,21),
                           Fraction(10), Fraction(12, -3),
                           Fraction(), Fraction(28, 6), Fraction(0, 12)};

    for (int i = 0; i < 7; i++){
        cout << "Fraction [" << i <<"] = " << fr[i] << endl;
    }
}






string boolString(bool convertMe) {
    if (convertMe) {
        return "true";
    } else {
        return "false";
    }
}






void RelationTest()
{
    cout << "\n----- Testing relational operators between Fractions\n";

    const Fraction fr[] =  {Fraction(3, 6), Fraction(1,2), Fraction(-15,30),
                            Fraction(1,10), Fraction(0,1), Fraction(0,2)};

    for (int i = 0; i < 5; i++) {
        cout << "Comparing " << fr[i] << " to " << fr[i+1] << endl;
        cout << "\tIs left < right? " << boolString(fr[i] < fr[i+1]) << endl;
        cout << "\tIs left <= right? " << boolString(fr[i] <= fr[i+1]) << endl;
        cout << "\tIs left > right? " << boolString(fr[i] > fr[i+1]) << endl;
        cout << "\tIs left >= right? " << boolString(fr[i] >= fr[i+1]) << endl;
        cout << "\tDoes left == right? " << boolString(fr[i] == fr[i+1]) << endl;
        cout << "\tDoes left != right ? " << boolString(fr[i] != fr[i+1]) << endl;
    }

    cout << "\n----- Testing relations between Fractions and integers\n";
    Fraction f(-3,6);
    int num = 2;
    cout << "Comparing " << f << " to " << num << endl;
    cout << "\tIs left < right? " << boolString(f < num) << endl;
    cout << "\tIs left <= right? " << boolString(f <= num) << endl;
    cout << "\tIs left > right? " << boolString(f > num) << endl;
    cout << "\tIs left >= right? " << boolString(f >= num) << endl;
    cout << "\tDoes left == right? " << boolString(f == num) << endl;
    cout << "\tDoes left != right ? " << boolString(f != num) << endl;

    Fraction g(1,4);
    num = -3;
    cout << "Comparing " << num << " to " << g << endl;
    cout << "\tIs left < right? " << boolString(num < g) << endl;
    cout << "\tIs left <= right? " << boolString(num <= g) << endl;
    cout << "\tIs left > right? " << boolString(num > g) << endl;
    cout << "\tIs left >= right? " << boolString(num >= g) << endl;
    cout << "\tDoes left == right? " << boolString(num == g) << endl;
    cout << "\tDoes left != right ? " << boolString(num != g) << endl;
}






void BinaryMathTest()
{
    cout << "\n----- Testing binary arithmetic between Fractions\n";

    const Fraction fr[] = {Fraction(1, 6), Fraction(1,3),
                           Fraction(-2,3), Fraction(5), Fraction(-4,3)};

    for (int i = 0; i < 4; i++) {
        cout << fr[i] << " + " << fr[i+1] << " = " << fr[i] + fr[i+1] << endl;
        cout << fr[i] << " - " << fr[i+1] << " = " << fr[i] - fr[i+1] << endl;
        cout << fr[i] << " * " << fr[i+1] << " = " << fr[i] * fr[i+1] << endl;
        cout << fr[i] << " / " << fr[i+1] << " = " << fr[i] / fr[i+1] << endl;
    }

    cout << "\n----- Testing arithmetic between Fractions and integers\n";
    Fraction f(-1, 2);
    int num = 4;
    cout << f << " + " << num << " = " << f + num << endl;
    cout << f << " - " << num << " = " << f - num << endl;
    cout << f << " * " << num << " = " << f * num << endl;
    cout << f << " / " << num << " = " << f / num << endl;

    Fraction g(-1, 2);
    num = 3;
    cout << num << " + " << g << " = " << num + g << endl;
    cout << num << " - " << g << " = " << num - g << endl;
    cout << num << " * " << g << " = " << num * g << endl;
    cout << num << " / " << g << " = " << num / g << endl;
}






void MathAssignTest()
{
    cout << "\n----- Testing shorthand arithmetic assignment on Fractions\n";

    Fraction fr[] = {Fraction(1, 6), Fraction(4),
                     Fraction(-1,2), Fraction(5)};

    for (int i = 0; i < 3; i++) {
        cout << fr[i] << " += " << fr[i+1] << " = ";
        cout << (fr[i] += fr[i+1]) << endl;
        cout << fr[i] << " -= " << fr[i+1] << " = ";
        cout << (fr[i] -= fr[i+1]) << endl;
        cout << fr[i] << " *= " << fr[i+1] << " = ";
        cout << (fr[i] *= fr[i+1]) << endl;
        cout << fr[i] << " /= " << fr[i+1] << " = ";
        cout << (fr[i] /= fr[i+1]) << endl;
    }

    cout << "\n----- Testing shorthand arithmetic assignment using integers\n";
    Fraction f(-1, 3);
    int num = 3;
    cout << f << " += " << num << " = ";
    cout << (f += num) << endl;
    cout << f << " -= " << num << " = ";
    cout << (f -= num) << endl;
    cout << f << " *= " << num << " = ";
    cout << (f *= num) << endl;
    cout << f << " /= " << num << " = ";
    cout << (f /= num) << endl;

    cout << "\n----- Testing increment/decrement prefix and postfix\n";
    Fraction g(-1, 3);
    cout << "Now g = " << g << endl;
    cout << "g++ = " << g++ << endl;
    cout << "Now g = " << g << endl;
    cout << "++g = " << ++g << endl;
    cout << "Now g = " << g << endl;
    cout << "g-- = " << g-- << endl;
    cout << "Now g = " << g << endl;
    cout << "--g = " << --g << endl;
    cout << "Now g = " << g << endl;
}

/*
OUTPUT:

----- Testing basic Fraction creation & printing
Fraction [0] = 4/8
Fraction [1] = -15/21
Fraction [2] = 10/1
Fraction [3] = 12/-3
Fraction [4] = 0/1
Fraction [5] = 28/6
Fraction [6] = 0/12

----- Testing relational operators between Fractions
Comparing 3/6 to 1/2
	Is left < right? false
	Is left <= right? true
	Is left > right? false
	Is left >= right? true
	Does left == right? true
	Does left != right ? false
Comparing 1/2 to -15/30
	Is left < right? false
	Is left <= right? false
	Is left > right? true
	Is left >= right? true
	Does left == right? false
	Does left != right ? true
Comparing -15/30 to 1/10
	Is left < right? true
	Is left <= right? true
	Is left > right? false
	Is left >= right? false
	Does left == right? false
	Does left != right ? true
Comparing 1/10 to 0/1
	Is left < right? false
	Is left <= right? false
	Is left > right? true
	Is left >= right? true
	Does left == right? false
	Does left != right ? true
Comparing 0/1 to 0/2
	Is left < right? false
	Is left <= right? true
	Is left > right? false
	Is left >= right? true
	Does left == right? true
	Does left != right ? false

----- Testing relations between Fractions and integers
Comparing -3/6 to 2
	Is left < right? true
	Is left <= right? true
	Is left > right? false
	Is left >= right? false
	Does left == right? false
	Does left != right ? true
Comparing -3 to 1/4
	Is left < right? true
	Is left <= right? true
	Is left > right? false
	Is left >= right? false
	Does left == right? false
	Does left != right ? true

----- Testing binary arithmetic between Fractions
1/6 + 1/3 = 9/18
1/6 - 1/3 = -3/18
1/6 * 1/3 = 1/18
1/6 / 1/3 = 3/6
1/3 + -2/3 = -3/9
1/3 - -2/3 = 9/9
1/3 * -2/3 = -2/9
1/3 / -2/3 = 3/-6
-2/3 + 5/1 = 13/3
-2/3 - 5/1 = -17/3
-2/3 * 5/1 = -10/3
-2/3 / 5/1 = -2/15
5/1 + -4/3 = 11/3
5/1 - -4/3 = 19/3
5/1 * -4/3 = -20/3
5/1 / -4/3 = 15/-4

----- Testing arithmetic between Fractions and integers
-1/2 + 4 = 7/2
-1/2 - 4 = -9/2
-1/2 * 4 = -4/2
-1/2 / 4 = -1/8
3 + -1/2 = 5/2
3 - -1/2 = 7/2
3 * -1/2 = -3/2
3 / -1/2 = 6/-1

----- Testing shorthand arithmetic assignment on Fractions
1/6 += 4/1 = 25/6
25/6 -= 4/1 = 1/6
1/6 *= 4/1 = 4/6
4/6 /= 4/1 = 4/24
4/1 += -1/2 = 7/2
7/2 -= -1/2 = 16/4
16/4 *= -1/2 = -16/8
-16/8 /= -1/2 = -32/-8
-1/2 += 5/1 = 9/2
9/2 -= 5/1 = -1/2
-1/2 *= 5/1 = -5/2
-5/2 /= 5/1 = -5/10

----- Testing shorthand arithmetic assignment using integers
-1/3 += 3 = 8/3
8/3 -= 3 = -1/3
-1/3 *= 3 = -3/3
-3/3 /= 3 = -3/9

----- Testing increment/decrement prefix and postfix
Now g = -1/3
g++ = -1/3
Now g = 2/3
++g = 5/3
Now g = 5/3
g-- = 5/3
Now g = 2/3
--g = -1/3
Now g = -1/3

 */