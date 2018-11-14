#include <iostream>
#ifndef FRACTION_H
#define FRACTION_H
namespace cs_fraction {
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
            friend std::istream& operator>>(std::istream& leftIS, Fraction& rightOperand);

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
            void simplify();
            void correction();

    };
}
#endif //FRACTION_H
/*
OUTPUT:

----- Testing basic Fraction creation & printing
(Fractions should be in reduced form, and as mixed numbers.)
Fraction [0] = 1/2
Fraction [1] = -5/7
Fraction [2] = 10
Fraction [3] = -4
Fraction [4] = 0
Fraction [5] = 4+2/3
Fraction [6] = 0

----- Now reading Fractions from file
Read Fraction = 1/3
Read Fraction = 1/2
Read Fraction = 3/4
Read Fraction = -4/5
Read Fraction = 6
Read Fraction = 5
Read Fraction = -8
Read Fraction = 1+2/5
Read Fraction = -16+2/3
Read Fraction = 1+1/4
Read Fraction = 2
Read Fraction = -4+1/4
Read Fraction = -10+5/6

----- Testing relational operators between Fractions
Comparing 1/2 to 1/2
	Is left < right? false
	Is left <= right? true
	Is left > right? false
	Is left >= right? true
	Does left == right? true
	Does left != right ? false
Comparing 1/2 to -1/2
	Is left < right? false
	Is left <= right? false
	Is left > right? true
	Is left >= right? true
	Does left == right? false
	Does left != right ? true
Comparing -1/2 to 1/10
	Is left < right? true
	Is left <= right? true
	Is left > right? false
	Is left >= right? false
	Does left == right? false
	Does left != right ? true
Comparing 1/10 to 0
	Is left < right? false
	Is left <= right? false
	Is left > right? true
	Is left >= right? true
	Does left == right? false
	Does left != right ? true
Comparing 0 to 0
	Is left < right? false
	Is left <= right? true
	Is left > right? false
	Is left >= right? true
	Does left == right? true
	Does left != right ? false

----- Testing relations between Fractions and integers
Comparing -1/2 to 2
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
1/6 + 1/3 = 1/2
1/6 - 1/3 = -1/6
1/6 * 1/3 = 1/18
1/6 / 1/3 = 1/2
1/3 + -2/3 = -1/3
1/3 - -2/3 = 1
1/3 * -2/3 = -2/9
1/3 / -2/3 = -1/2
-2/3 + 5 = 4+1/3
-2/3 - 5 = -5+2/3
-2/3 * 5 = -3+1/3
-2/3 / 5 = -2/15
5 + -1+1/3 = 3+2/3
5 - -1+1/3 = 6+1/3
5 * -1+1/3 = -6+2/3
5 / -1+1/3 = -3+3/4

----- Testing arithmetic between Fractions and integers
-1/2 + 4 = 3+1/2
-1/2 - 4 = -4+1/2
-1/2 * 4 = -2
-1/2 / 4 = -1/8
3 + -1/2 = 2+1/2
3 - -1/2 = 3+1/2
3 * -1/2 = -1+1/2
3 / -1/2 = -6

----- Testing shorthand arithmetic assignment on Fractions
1/6 += 4 = 4+1/6
4+1/6 -= 4 = 1/6
1/6 *= 4 = 2/3
2/3 /= 4 = 1/6
4 += -1/2 = 3+1/2
3+1/2 -= -1/2 = 4
4 *= -1/2 = -2
-2 /= -1/2 = 4
-1/2 += 5 = 4+1/2
4+1/2 -= 5 = -1/2
-1/2 *= 5 = -2+1/2
-2+1/2 /= 5 = -1/2

----- Testing shorthand arithmetic assignment using integers
-1/3 += 3 = 2+2/3
2+2/3 -= 3 = -1/3
-1/3 *= 3 = -1
-1 /= 3 = -1/3

----- Testing increment/decrement prefix and postfix
Now g = -1/3
g++ = -1/3
Now g = 2/3
++g = 1+2/3
Now g = 1+2/3
g-- = 1+2/3
Now g = 2/3
--g = -1/3
Now g = -1/3
 */