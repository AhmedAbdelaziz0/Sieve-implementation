#include <iostream>

using namespace std;

// no.groups * 6 // 6 is the representation of 2 bits (1 5)
typedef long long Elem;
class Array_Bits2
{
private:
    unsigned char* prime;
    Elem size_of_array;
    const int no_groups = 24;

public:
    Array_Bits2(Elem n)
    {
        size_of_array = n / no_groups + 1;
        prime = new unsigned char[size_of_array];
        prime[0] = 0x7f;
        for(Elem i = size_of_array - 1; i > 0; i--)
            prime[i] = 0xff;

        int8_t toggle_1 = 4;
        unsigned char mask = 0x40;

        for(Elem p = 5; p * p <= n; p += toggle_1, mask >>= 1)
        {
            if(toggle_1 == 4)
                toggle_1 = 2;
            else
                toggle_1 = 4;

            if(mask == 0)
                mask = 0x80;

            if(prime[p / no_groups] & mask)
                for(Elem i = p*p; i <= n; i += 2 * p)
                {
                    if(i % 6 == 1)
                        prime[i / no_groups] &= ((0x80 >> ((i % no_groups) / 6 * 2 ) ^ 0xff));
                    else if(i % 6 == 5)
                        prime[i / no_groups] &= ((0x80 >> ((i % no_groups) / 6 * 2 + 1) ^ 0xff));
                }
        }
    }

    ~Array_Bits2()
    {
        delete[] prime;
    }

    bool is_Prime(Elem location) const
    {
        if(location == 3 || location == 2)
            return true;
        if(location % 6 == 1)
            return prime[location / no_groups] & (0x80 >> ((location % no_groups) / 6 * 2 ));
        else if(location % 6 == 5)
            return prime[location / no_groups] & (0x80 >> ((location % no_groups) / 6 * 2 + 1));
        else
            return false;
    }

    Elem next_prime(Elem num)
    {
        Elem index = num / no_groups;
        Elem loc = num % 24 / 6 * 2;

        if(num % 6 > 1)
            loc ++;

        unsigned char mask = 0x80 >> loc;

        while((prime[index] & mask) == 0)
        {
            mask >>= 1;
            if(mask == 0)
            {
                index += 1;
                mask = 0x80;
            }
        }
        Elem location = index * 24 + 1;
        while(mask)
        {
            mask <<= 1;
            if(mask & 0xAA)
                location += 4;
            else
                location += 2;
        }
        return location;
    }
};



int main()
{
    Array_Bits2 prime(100000);

    cout << prime.is_Prime(19) << endl;
    cout << prime.next_prime(1354) << endl;

    return 0;
}
