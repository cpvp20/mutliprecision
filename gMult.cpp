#include <iostream>
#include <string>
#include <sstream>

using namespace std;
class BigInteger
{
public:
    string number;
    bool sign;
    //methods
    BigInteger(string s); // "string" constructor
    BigInteger(int n);    // "int" constructor
    void setNumber(string s);
    void setSign(bool s);
    operator string(); // for conversion from BigInteger to string
    //arithmatic operations
    string add(string number1, string number2);
    string subtract(string number1, string number2);
    string multiply(string n1, string n2);
};

int main()
{
    BigInteger bigN = BigInteger("123");

    string a = bigN.add("123456789123456789", "123456789123456789");
    string s = bigN.subtract("123456789123456789", "123456789123456789");
    string m = bigN.multiply("123456789123456789", "123456789123456789");

    printf("addition is %s \n", a.c_str());
    printf("subtraction is %s \n", s.c_str());
    printf("multiplication is %s \n", m.c_str());

    return 0;
}

//------------------------------------------------------------------------------

BigInteger::BigInteger(string s)
{ // "string" constructor
    if (isdigit(s[0]))
    { // if not signed
        setNumber(s);
        sign = false;
    }
    else
    {
        setNumber(s.substr(1));
        sign = (s[0] == '-');
    }
}

BigInteger::BigInteger(int n)
{ // "int" constructor
    stringstream ss;
    string s;
    ss << n;
    ss >> s;

    if (isdigit(s[0]))
    { // if not signed
        setNumber(s);
        setSign(false);
    }
    else
    {
        setNumber(s.substr(1));
        setSign(s[0] == '-');
    }
}

void BigInteger::setNumber(string s)
{
    number = s;
}

void BigInteger::setSign(bool s)
{
    sign = s;
}

string BigInteger::add(string number1, string number2)
{
    string add = (number1.length() > number2.length()) ? number1 : number2;
    char carry = '0';
    int differenceInLength = abs((int)(number1.size() - number2.size()));

    if (number1.size() > number2.size())
        number2.insert(0, differenceInLength, '0'); // put zeros from left

    else // if(number1.size() < number2.size())
        number1.insert(0, differenceInLength, '0');

    for (int i = number1.size() - 1; i >= 0; --i)
    {
        add[i] = ((carry - '0') + (number1[i] - '0') + (number2[i] - '0')) + '0';

        if (i != 0)
        {
            if (add[i] > '9')
            {
                add[i] -= 10;
                carry = '1';
            }
            else
                carry = '0';
        }
    }
    if (add[0] > '9')
    {
        add[0] -= 10;
        add.insert(0, 1, '1');
    }
    return add;
}

string BigInteger::subtract(string number1, string number2)
{
    string sub = (number1.length() > number2.length()) ? number1 : number2;
    int differenceInLength = abs((int)(number1.size() - number2.size()));

    if (number1.size() > number2.size())
        number2.insert(0, differenceInLength, '0');

    else
        number1.insert(0, differenceInLength, '0');

    for (int i = number1.length() - 1; i >= 0; --i)
    {
        if (number1[i] < number2[i])
        {
            number1[i] += 10;
            number1[i - 1]--;
        }
        sub[i] = ((number1[i] - '0') - (number2[i] - '0')) + '0';
    }

    while (sub[0] == '0' && sub.length() != 1) // erase leading zeros
        sub.erase(0, 1);

    return sub;
}

string BigInteger::multiply(string n1, string n2)
{
    if (n1.length() > n2.length())
        n1.swap(n2);

    string res = "0";
    for (int i = n1.length() - 1; i >= 0; --i)
    {
        string temp = n2;
        int currentDigit = n1[i] - '0';
        int carry = 0;

        for (int j = temp.length() - 1; j >= 0; --j)
        {
            temp[j] = ((temp[j] - '0') * currentDigit) + carry;

            if (temp[j] > 9)
            {
                carry = (temp[j] / 10);
                temp[j] -= (carry * 10);
            }
            else
                carry = 0;

            temp[j] += '0';
        }

        if (carry > 0)
            temp.insert(0, 1, (carry + '0'));

        temp.append((n1.length() - i - 1), '0');

        res = add(res, temp); // O(n)
    }

    while (res[0] == '0' && res.length() != 1) // erase leading zeros
        res.erase(0, 1);

    return res;
}
