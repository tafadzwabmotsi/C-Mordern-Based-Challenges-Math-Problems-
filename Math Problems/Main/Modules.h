#pragma once

#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <random>
#include <array>
#include <iomanip>
#include <algorithm>
#include <string_view>

// Question 2
//==========
// Write a program that, given two positive integers,
// will calculate and print the greatest common divisor of the two.
unsigned int gcd(unsigned int const firstNumber, unsigned int const secondNumber)
{
    if (secondNumber == 0)
        return firstNumber;

    return gcd(secondNumber, firstNumber % secondNumber);
}

// Question 3
//===========
// Write a program that will, given two or more positive integers,
// calculate and print the least common multiple of them all.
unsigned int lcm(unsigned int const firstNumber, unsigned int const secondNumber)
{
    return firstNumber * (secondNumber / gcd(firstNumber, secondNumber));
}

//Question 4
//==========
// Write a program that computes and prints the largest prime number
// that is smaller than a number provided by the user,
// which must be a positive integer.

// helper function isPrime, determines if the number is prime
bool isPrime(int number)
{
    int x = 1;
    while (x <= number)
    {
        if ((x != 1) && (x != number) && (number % x == 0))
            return false;
        x++;
    }

    return true;
}

unsigned int lagerstPrime(unsigned int const primeNumber)
{
    if (!isPrime(primeNumber))
    {
        std::printf("Number not prime : ");
        return -1;
    }

    int number = 1;
    int largest = number;

    while (number <= primeNumber)
    {
        if (isPrime(number) && number != primeNumber)
            largest = number;

        number++;
    }

    return largest;
}

// Question 5
//===========
// Write a program that prints all the prime pairs that differ by six
// up to a limit entered by the user.
void printPrimePairsDifferingBySix(unsigned int const numberLimit)
{

    if (numberLimit < 3)
        return;

    unsigned int start = 2;
    while (start <= numberLimit)
    {
        if (isPrime(start) && isPrime(start + 6))
            std::printf("(%d,%d)", start, start + 6);

        start++;
    }

    std::printf("\n");
    return;
}

// Question 6
//===========
// Write a program that prints all abundant numbers and
// their abundance, up to a number entered by the user.

// find the abundance
unsigned int sumAbundance(unsigned int const number)
{
    int sum = 1;

    for (int i = 2; i < number; i++)
        sum += (number % i == 0) ? i : 0;

    return sum;
}

void printAbundace(unsigned int const limitNumber)
{
    if (limitNumber < 11)
        return;

    for (int number = 10; number <= limitNumber; number++)
    {
        auto sum = sumAbundance(number);

        if (sum > number)
        {
            std::printf("The abundance of %d is %d.\n", number, (sum - number));
        }
    }
    return;
}

// Question 7
//===========
// Write a program that prints the list of all pairs of amicable
// numbers smaller than 1,000,000.
// Def: Two numbers are said to be amicable if the sum of the
//      proper divisors of one number is equal to that of the
//      other number.
//      Eg. (220, 284)

// find sum of proper divisors
unsigned int sumOfProperDivisors(unsigned int number)
{
    return sumAbundance(number);
}

// find amicable pairs
void pairsOfAmicableNumbers(unsigned long long const limit)
{
    for (int i = 2; i <= limit; i++)
    {
        auto firstSum = sumOfProperDivisors(i);
        auto secondSum = sumOfProperDivisors(firstSum);

        if ((i == secondSum) && (secondSum < firstSum))
            std::printf("(%d,%d)", secondSum, firstSum);
        else
            continue;
    }
}

// Question 8:  Armstrong numbers
//===============================
// Write a program that prints all Armstrong numbers with three digits.
// Def: An Armstrong number is a number that is equal to the sum of its
//      own digits when they are raised to the power of the number of digits.
//      Eg. The smallest Armstrong number is 153, which is equal to 1^3 + 5^3 + 3^3

// TODO: separate numbers

// helper power function

int power(int x, int n)
{
    if (n == 0)
        return 1;
    if (n == 1)
        return x;

    return x * power(x, n - 1);
}

std::vector<unsigned int> separatedNumbers(unsigned int number)
{
    std::string strNumber = std::to_string(number);
    std::vector<unsigned int> numbers;

    for (int index = 0; index < strNumber.length(); index++)
        numbers.push_back(power(strNumber[index] - '0', strNumber.length()));

    return numbers;
}

// print Armstrong numbers
void printArmstrongNumbers(unsigned int limit)
{
    // make sure digit is a three digit number
    if (limit < 100)
        return;

    for (int i = 100; i <= limit; i++)
    {
        std::vector<unsigned int> numbers = separatedNumbers(i);
        unsigned int armstrongNumber = 0;

        for (auto num : numbers)
            armstrongNumber += num;

        if (i == armstrongNumber)
            std::printf("%d ", armstrongNumber);
    }

    return;
}

// Question 9: Prime factors of a number
//======================================
// Write a program that prints the prime factors of a number entered by the user.
// Def: The prime factors of a positive integer are the prime numbers that divide
//      that integer exactly.
//      Eg 1:  Prime factors of 8 are 2 x 2 x 2,
//      Eg 2:  Prime factors of 42 are 2 x 3x 7.

// helper function to calculate the largest prime factor of a number
unsigned int largestPrimeFactor(unsigned int number)
{
    int largestPrime = 2;
    for (int i = largestPrime; i < number; i++)
        if (isPrime(i) && (number % i == 0))
            largestPrime = i;

    return largestPrime;
}

// recursive version
void recursivePrimeFactors(unsigned int number, std::vector<unsigned int>& primeNumbers)
{
    if (number == 1)
        ;
    else
    {
        unsigned int largestPrime = largestPrimeFactor(number);
        primeNumbers.push_back(largestPrime);
        recursivePrimeFactors(number / largestPrime, primeNumbers);
    }
}

// non recursive version
std::vector<unsigned int> nonRecursivePrimeNumbers(unsigned int givenNumber)
{
    std::vector<unsigned int> primeNumbers;

    unsigned int number = givenNumber;

    while (number > 1)
    {
        unsigned int largestPrime = largestPrimeFactor(number);
        primeNumbers.push_back(largestPrime);
        number /= largestPrime;
    }

    return primeNumbers;
}

// Question 10: Gray code
//=======================
// Write a program that displays the normal binary representations,
// Gray code representations, and decoded Gray code values for all 5-bit numbers.
// Def: Gray code  is a form of binary encoding where two consecutive numbers
//      differ by only one bit.

unsigned int grayEncode(unsigned int const number)
{
    return number ^ (number >> 1);
}

unsigned int grayDecode(unsigned int grayCode)
{
    for (unsigned int bit = 1U << 31; bit > 1; bit >>= 1)
        if (grayCode & bit)
            grayCode ^= bit >> 1;

    return grayCode;
}

// Question 11. Converting numerical values to Roman
//==================================================
// Write a program that, given a number entered by the user,
// prints its Roman numeral equivalent.
// Roman numerals, as they are known today, ]
// use seven symbols: I = 1, V = 5, X = 10, L = 50,
// C = 100, D = 500, and M = 1000.

std::map<unsigned int, std::string> romanMap()
{
    std::map<unsigned int, std::string> map =
    {
        { 1000, "M" },
        { 900, "CM" },
        { 500, "D" },
        { 400, "CD" },
        { 100, "C" },
        { 90, "XC" },
        { 50, "L" },
        { 40, "XL" },
        { 10, "X" },
        { 9, "IX" },
        { 5, "V" },
        { 4, "IV" },
        { 1, "I" }
    };

    return map;
}

std::string toRoman(unsigned int number) {

    std::string roman;

    std::map<unsigned int, std::string> rPair = romanMap();
    std::map<unsigned int, std::string>::reverse_iterator it = rPair.rbegin();

    for (; it != rPair.rend(); ++it) {
        while (number >= it->first) {
            roman += it->second;
            number -= it->first;
        }
    }

    return roman;
}

// Question 12. Largest Collatz sequence
//======================================
// Write a program that determines and prints which number 
// up to 1 million produces the longest Collatz sequenceand 
// what its length is.
// Def: The Collatz conjecture  is an unproven conjecture that 
//      states that a sequence defined as explained in the following 
//      always reaches 1.
//      Theseries is defined as follows : 
//      start with any positive integer n and obtain each new 
//      term from the previous one : 
//      if the previous term is even, the next term is half the previous term, 
//      or else it is 3 times the previous term plus 1.

std::pair<unsigned long long, long> longestCollartz(unsigned long long const limitingNumber) {
    long length = 0;
    unsigned long long number = 0;

    std::vector<int> cache(limitingNumber + 1, 0);

    for (unsigned long long i = 2; i <= limitingNumber; i++) {
        auto n = i;
        long steps = 0;

        while (n != 0 && n >= i) {

            // n is even
            if ((n % 2) == 1) {
                n /= 2;
            }

            else {
                n = (n * 3) + 1;
            }
        }

        cache[i] = steps + cache[n];

        if (cache[i] > length) {
            length = cache[i];
            number = i;
        }
    }

    return std::make_pair(number, length);
}

// Question 13. Computing the value of Pi
//=======================================
// Write a program that computes the value of Pi with a precision of two decimal digits.

template<class E = std::mt19937 , class D = std::uniform_real_distribution<>>
double computePi(E& engine, D& dist, int const samples = 1000000) {
    
    int hit = 0;

    for (auto i = 0; i < samples; i++) {
        auto x = dist(engine);
        auto y = dist(engine);

        if (y <= std::sqrt(1 - std::pow(x, 2)))
            hit++;
    }

    return 4.0 * hit / samples;
}

void printPi() {
    
    std::random_device rd;
    auto seed_data = std::array<int, std::mt19937::state_size>{};

    std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
    std::seed_seq seq(std::begin(seed_data), std::end(seed_data));

    auto eng = std::mt19937{ seq };
    auto dist = std::uniform_real_distribution<>{ 0, 1 };

    for (auto j = 0; j < 10; j++)
        
        std::cout << std::setprecision(3) << computePi(eng, dist) << std::endl;
}

// Question 14. Validating ISBNs
//==============================
// Write a program that validates that 10-digit values entered by the user, 
// as a string, represent valid ISBN - 10 numbers.

bool validateISNB(std::string_view isbn) {
    auto valid = false;

    if (isbn.size() == 10) {
        if (std::count_if(std::begin(isbn), std::end(isbn), isdigit) == 10 || isbn[isbn.size() - 1] == 'X') {
            auto sum = 0;

            for (auto index = 1; index <= 10; index++) {
                sum += (11 - index) * (isbn[index - 1] - '0');
                std::cout << sum << "\n";
            }

            valid = sum % 11 == 0;
        }
    }

    return valid;
}