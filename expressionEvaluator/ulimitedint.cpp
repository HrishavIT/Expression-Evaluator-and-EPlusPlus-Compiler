/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"
// #include <iostream>

UnlimitedInt *compare(UnlimitedInt *i1, UnlimitedInt *i2)
{
    if (i1->get_size() > i2->get_size())
    {
        return i1;
    }
    else if (i1->get_size() < i2->get_size())
    {
        return i2;
    }
    else
    {
        for (int i = i1->get_size(); i > 0; i--)
        {
            if (i1->get_array()[i] > i2->get_array()[i])
            {
                return i1;
            }
            else if (i1->get_array()[i] < i2->get_array()[i])
            {
                return i2;
            }
        }
        return i1;
    }
}

UnlimitedInt ::UnlimitedInt()
{
    size = 0;
    sign = 1;
    capacity = 3;
    unlimited_int = new int[capacity];
    for (int i = 0; i < capacity; i++)
    {
        unlimited_int[i] = 0;
    }
    unlimited_int[0] = sign;
    unlimited_int[1] = 0;
}

UnlimitedInt ::~UnlimitedInt()
{
    delete[] unlimited_int;
}

UnlimitedInt ::UnlimitedInt(string s)
{
    capacity = 2 * s.length() + 2;
    unlimited_int = new int[capacity];
    for (int i = 0; i < capacity; i++)
    {
        unlimited_int[i] = 0;
    }
    if (s[0] == '-')
    {
        sign = -1;
    }
    else
    {
        sign = 1;
    }
    int i = s.length() - 1;
    if (sign == -1)
    {
        unlimited_int[0] = -1;
        size = s.length() - 1;
        while (i >= 1)
        {
            unlimited_int[s.length() - i] = int(s[i] - '0');
            i--;
        }
    }
    else
    {
        unlimited_int[0] = 1;
        size = s.length();
        while (i >= 0)
        {
            unlimited_int[s.length() - i] = int(s[i] - '0');
            i--;
        }
    }
    while (unlimited_int[size] == 0)
    {
        size--;
    }
    if (size == 0)
    {
        unlimited_int[0] = 1;
        unlimited_int[1] = 0;
        sign = 1;
        size = 1;
    }
}

UnlimitedInt ::UnlimitedInt(int i)
{
    string s = std::to_string(i);
    capacity = 2 * s.length()+2;
    unlimited_int = new int[capacity];
    for (int i = 0; i < capacity; i++)
    {
        unlimited_int[i] = 0;
    }
    if (s[0] == '-')
    {
        sign = -1;
    }
    else
    {
        sign = 1;
    }
    int j = s.length() - 1;
    if (sign == -1)
    {
        unlimited_int[0] = -1;
        size = s.length() - 1;
        while (j >= 1)
        {
            unlimited_int[s.length() - j] = int(s[j] - '0');
            j--;
        }
    }
    else
    {
        unlimited_int[0] = 1;
        size = s.length();
        while (j >= 0)
        {
            unlimited_int[s.length() - j] = int(s[j] - '0');
            j--;
        }
    }
    while (unlimited_int[size] == 0)
    {
        size--;
    }
    if (size == 0)
    {
        unlimited_int[0] = 1;
        unlimited_int[1] = 0;
        sign = 1;
        size = 1;
    }
}

int UnlimitedInt::get_size()
{
    return size;
}

int UnlimitedInt::get_sign()
{
    return sign;
}

int *UnlimitedInt ::get_array()
{
    return unlimited_int;
}

int UnlimitedInt ::get_capacity()
{
    return capacity;
}

string UnlimitedInt ::to_string()
{
    string s = "";
    bool leading_zeroes = true;
    if (get_sign() == -1)
    {
        s = s + "-";
    }
    for (int i = get_size(); i >= 1; i--)
    {
        if (unlimited_int[i] != 0)
        {
            leading_zeroes = false;
            s = s + std::to_string(unlimited_int[i]);
        }
        else if (unlimited_int[i] == 0 && leading_zeroes == false)
        {
            s = s + std::to_string(unlimited_int[i]);
        }
    }
    if (s == "-")
    {
        s = "0";
    }
    else if (s == "")
    {
        s = "0";
    }
    return s;
}

UnlimitedInt ::UnlimitedInt(int *ulimited_int, int cap, int sgn, int sz)
{
    unlimited_int = ulimited_int;
    capacity = cap;
    sign = sgn;
    size = sz;
}

UnlimitedInt *UnlimitedInt ::add(UnlimitedInt *i1, UnlimitedInt *i2)
{
    UnlimitedInt *i = new UnlimitedInt();
    if (i1->get_size() > i2->get_size())
    {
        if (i1->get_sign() == i2->get_sign())
        {
            i->sign = i1->get_sign();
            i->capacity = i1->get_size() + 3;
            i->unlimited_int = new int[i->capacity];
            for (int k = 0; k < i->capacity; k++)
            {
                i->unlimited_int[k] = 0;
            }
            i->unlimited_int[0] = i->sign;
            int carry = 0;
            for (int j = 1; j <= i2->get_size(); j++)
            {
                i->unlimited_int[j] = (i1->unlimited_int[j] + i2->unlimited_int[j] + carry) % 10;
                carry = (i1->unlimited_int[j] + i2->unlimited_int[j] + carry) / 10;
            }
            for (int k = i2->get_size() + 1; k <= i1->get_size(); k++)
            {
                i->unlimited_int[k] = (i1->unlimited_int[k] + carry) % 10;
                carry = (i1->unlimited_int[k] + carry) / 10;
            }
            i->unlimited_int[i1->get_size() + 1] = carry;
            if (i->unlimited_int[i1->get_size() + 1] == 0)
            {
                i->size = i1->get_size();
            }
            else
            {
                i->size = i1->get_size() + 1;
            }
        }
        else
        {
            i->sign = i1->get_sign();
            i->capacity = i1->get_size() + 2;
            i->unlimited_int = new int[i->capacity];
            for (int k = 0; k < i->capacity; k++)
            {
                i->unlimited_int[k] = 0;
            }
            i->unlimited_int[0] = i->sign;
            int given = 0;
            i->size = i1->size;
            for (int j = 1; j <= i2->get_size(); j++)
            {
                if (i1->unlimited_int[j] - i2->unlimited_int[j] - given < 0)
                {
                    i->unlimited_int[j] = 10 + i1->unlimited_int[j] - i2->unlimited_int[j] - given;
                    given = 1;
                }
                else
                {
                    i->unlimited_int[j] = i1->unlimited_int[j] - i2->unlimited_int[j] - given;
                    given = 0;
                }
            }
            for (int k = i2->get_size() + 1; k <= i1->get_size(); k++)
            {
                if (i1->unlimited_int[k] - given < 0)
                {
                    i->unlimited_int[k] = i1->unlimited_int[k] + 10 - given;
                    given = 1;
                }
                else
                {
                    i->unlimited_int[k] = i1->unlimited_int[k] - given;
                    given = 0;
                }
            }
            while (i->unlimited_int[i->size] == 0)
            {
                i->size = i->size - 1;
            }
            if (i->size == 0)
            {
                i->unlimited_int[0] = 1;
                i->sign = 1;
                i->unlimited_int[1] = 0;
                i->size = i->size + 1;
            }
        }
    }
    else if (i2->get_size() > i1->get_size())
    {
        if (i2->get_sign() == i1->get_sign())
        {
            i->sign = i2->get_sign();
            i->capacity = i2->get_size() + 3;
            i->unlimited_int = new int[i->capacity];
            for (int k = 0; k < i->capacity; k++)
            {
                i->unlimited_int[k] = 0;
            }
            i->unlimited_int[0] = i->sign;
            int carry = 0;
            for (int j = 1; j <= i1->get_size(); j++)
            {
                i->unlimited_int[j] = (i2->unlimited_int[j] + i1->unlimited_int[j] + carry) % 10;
                carry = (i2->unlimited_int[j] + i1->unlimited_int[j] + carry) / 10;
            }
            for (int k = i1->get_size() + 1; k <= i2->get_size(); k++)
            {
                i->unlimited_int[k] = (i2->unlimited_int[k] + carry) % 10;
                carry = (i2->unlimited_int[k] + carry) / 10;
            }
            i->unlimited_int[i2->get_size() + 1] = carry;
            if (i->unlimited_int[i2->get_size() + 1] == 0)
            {
                i->size = i2->get_size();
            }
            else
            {
                i->size = i2->get_size() + 1;
            }
        }
        else
        {
            i->sign = i2->get_sign();
            i->capacity = i2->get_size() + 3;
            i->unlimited_int = new int[i->capacity];
            for (int k = 0; k < i->capacity; k++)
            {
                i->unlimited_int[k] = 0;
            }
            i->unlimited_int[0] = i->sign;
            i->size = i2->size;
            int given = 0;
            for (int j = 1; j <= i1->get_size(); j++)
            {
                if (i2->unlimited_int[j] - i1->unlimited_int[j] - given < 0)
                {
                    i->unlimited_int[j] = 10 + i2->unlimited_int[j] - i1->unlimited_int[j] - given;
                    given = 1;
                }
                else
                {
                    i->unlimited_int[j] = i2->unlimited_int[j] - i1->unlimited_int[j] - given;
                    given = 0;
                }
            }
            for (int k = i1->get_size() + 1; k <= i2->get_size(); k++)
            {
                if (i2->unlimited_int[k] - given < 0)
                {
                    i->unlimited_int[k] = i2->unlimited_int[k] + 10 - given;
                    given = 1;
                }
                else
                {
                    i->unlimited_int[k] = i2->unlimited_int[k] - given;
                    given = 0;
                }
            }
            while (i->unlimited_int[i->size] == 0)
            {
                i->size = i->size - 1;
            }
            if (i->size == 0)
            {
                i->unlimited_int[0] = 1;
                i->sign = 1;
                i->unlimited_int[1] = 0;
                i->size = i->size + 1;
            }
        }
    }
    else
    {
        if (i1->sign != i2->sign)
        {
            i->sign = compare(i1, i2)->get_sign();
            i->capacity = i2->get_size() + 3;
            i->unlimited_int = new int[i->capacity];
            for (int k = 0; k < i->capacity; k++)
            {
                i->unlimited_int[k] = 0;
            }
            i->unlimited_int[0] = i->sign;
            int given = 0;
            i->size = i1->size;
            if (compare(i1, i2) == i1)
            {
                for (int j = 1; j <= i2->get_size(); j++)
                {
                    if (i1->unlimited_int[j] - i2->unlimited_int[j] - given < 0)
                    {
                        i->unlimited_int[j] = 10 + i1->unlimited_int[j] - i2->unlimited_int[j] - given;
                        given = 1;
                    }
                    else
                    {
                        i->unlimited_int[j] = i1->unlimited_int[j] - i2->unlimited_int[j] - given;

                        given = 0;
                    }
                }
                while (i->unlimited_int[i->size] == 0)
                {
                    i->size = i->size - 1;
                }
                if (i->size == 0)
                {
                    i->unlimited_int[0] = 1;
                    i->sign = 1;
                    i->unlimited_int[1] = 0;
                    i->size = i->size + 1;
                }
            }
            else
            {
                for (int j = 1; j <= i1->get_size(); j++)
                {
                    if (i2->unlimited_int[j] - i1->unlimited_int[j] - given < 0)
                    {
                        i->unlimited_int[j] = 10 + i2->unlimited_int[j] - i1->unlimited_int[j] - given;
                        given = 1;
                    }
                    else
                    {
                        i->unlimited_int[j] = i2->unlimited_int[j] - i1->unlimited_int[j] - given;
                        given = 0;
                    }
                }
                while (i->unlimited_int[i->size] == 0)
                {
                    i->size = i->size - 1;
                }
                if (i->size == 0)
                {
                    i->unlimited_int[0] = 1;
                    i->sign = 1;
                    i->unlimited_int[1] = 0;
                    i->size = i->size + 1;
                }
            }
        }
        else
        {
            i->sign = i1->get_sign();
            i->capacity = i1->get_size() + 3;
            i->unlimited_int = new int[i->capacity];
            for (int k = 0; k < i->capacity; k++)
            {
                i->unlimited_int[k] = 0;
            }
            i->unlimited_int[0] = i->sign;
            int carry = 0;
            for (int j = 1; j <= i2->get_size(); j++)
            {
                i->unlimited_int[j] = (i1->unlimited_int[j] + i2->unlimited_int[j] + carry) % 10;
                carry = (i1->unlimited_int[j] + i2->unlimited_int[j] + carry) / 10;
            }
            i->unlimited_int[i1->get_size() + 1] = carry;
            if (i->unlimited_int[i1->get_size() + 1] == 0)
            {
                i->size = i1->get_size();
            }
            else
            {
                i->size = i1->get_size() + 1;
            }
        }
    }
    return i;
}

UnlimitedInt *UnlimitedInt ::sub(UnlimitedInt *i1, UnlimitedInt *i2)
{
    UnlimitedInt *i = new UnlimitedInt();
    if (i1->size > i2->size)
    {
        if (i1->sign != i2->sign)
        {
            i->sign = i1->get_sign();
            i->capacity = i1->get_size() + 3;
            i->unlimited_int = new int[i->capacity];
            for (int k = 0; k < i->capacity; k++)
            {
                i->unlimited_int[k] = 0;
            }
            i->unlimited_int[0] = i->sign;
            int carry = 0;
            for (int j = 1; j <= i2->get_size(); j++)
            {
                i->unlimited_int[j] = (i1->unlimited_int[j] + i2->unlimited_int[j] + carry) % 10;
                carry = (i1->unlimited_int[j] + i2->unlimited_int[j] + carry) / 10;
            }
            for (int k = i2->get_size() + 1; k <= i1->get_size(); k++)
            {
                i->unlimited_int[k] = (i1->unlimited_int[k] + carry) % 10;
                carry = (i1->unlimited_int[k] + carry) / 10;
            }
            i->unlimited_int[i1->get_size() + 1] = carry;
            if (i->unlimited_int[i1->get_size() + 1] == 0)
            {
                i->size = i1->get_size();
            }
            else
            {
                i->size = i1->get_size() + 1;
            }
        }
        else
        {
            i->sign = i1->get_sign();
            i->capacity = i1->get_size() + 3;
            i->unlimited_int = new int[i->capacity];
            for (int k = 0; k < i->capacity; k++)
            {
                i->unlimited_int[k] = 0;
            }
            i->unlimited_int[0] = i->sign;
            int given = 0;
            i->size = i1->size;
            for (int j = 1; j <= i2->get_size(); j++)
            {
                if (i1->unlimited_int[j] - i2->unlimited_int[j] - given < 0)
                {
                    i->unlimited_int[j] = 10 + i1->unlimited_int[j] - i2->unlimited_int[j] - given;
                    given = 1;
                }
                else
                {
                    i->unlimited_int[j] = i1->unlimited_int[j] - i2->unlimited_int[j] - given;
                    given = 0;
                }
            }
            for (int k = i2->get_size() + 1; k <= i1->get_size(); k++)
            {
                if (i1->unlimited_int[k] - given < 0)
                {
                    i->unlimited_int[k] = i1->unlimited_int[k] + 10 - given;
                    given = 1;
                }
                else
                {
                    i->unlimited_int[k] = i1->unlimited_int[k] - given;
                    given = 0;
                }
            }
            while (i->unlimited_int[i->size] == 0)
            {
                i->size = i->size - 1;
            }
            if (i->size == 0)
            {
                i->unlimited_int[0] = 1;
                i->sign = 1;
                i->unlimited_int[1] = 0;
                i->size = i->size + 1;
            }
        }
    }
    else if (i1->size < i2->size)
    {
        if (i1->sign != i2->sign)
        {
            i->sign = (-1) * i2->get_sign();
            i->capacity = i2->get_size() + 2;
            i->unlimited_int = new int[i->capacity];
            for (int k = 0; k < i->capacity; k++)
            {
                i->unlimited_int[k] = 0;
            }
            i->unlimited_int[0] = i->sign;
            int carry = 0;
            for (int j = 1; j <= i1->get_size(); j++)
            {
                i->unlimited_int[j] = (i2->unlimited_int[j] + i1->unlimited_int[j] + carry) % 10;
                carry = (i2->unlimited_int[j] + i1->unlimited_int[j] + carry) / 10;
            }
            for (int k = i1->get_size() + 1; k <= i2->get_size(); k++)
            {
                i->unlimited_int[k] = (i2->unlimited_int[k] + carry) % 10;
                carry = (i2->unlimited_int[k] + carry) / 10;
            }
            i->unlimited_int[i2->get_size() + 1] = carry;
            if (i->unlimited_int[i2->get_size() + 1] == 0)
            {
                i->size = i2->get_size();
            }
            else
            {
                i->size = i2->get_size() + 1;
            }
        }
        else
        {
            i->sign = (-1) * i2->get_sign();
            i->capacity = i2->get_size() +2;
            i->unlimited_int = new int[i->capacity];
            for (int k = 0; k < i->capacity; k++)
            {
                i->unlimited_int[k] = 0;
            }
            i->unlimited_int[0] = i->sign;
            i->size = i2->size;
            int given = 0;
            for (int j = 1; j <= i1->get_size(); j++)
            {
                if (i2->unlimited_int[j] - i1->unlimited_int[j] - given < 0)
                {
                    i->unlimited_int[j] = 10 + i2->unlimited_int[j] - i1->unlimited_int[j] - given;
                    given = 1;
                }
                else
                {
                    i->unlimited_int[j] = i2->unlimited_int[j] - i1->unlimited_int[j] - given;
                    given = 0;
                }
            }
            for (int k = i1->get_size() + 1; k <= i2->get_size(); k++)
            {
                if (i2->unlimited_int[k] - given < 0)
                {
                    i->unlimited_int[k] = i2->unlimited_int[k] + 10 - given;
                    given = 1;
                }
                else
                {
                    i->unlimited_int[k] = i2->unlimited_int[k] - given;
                    given = 0;
                }
            }
            while (i->unlimited_int[i->size] == 0)
            {
                i->size = i->size - 1;
            }
            if (i->size == 0)
            {
                i->unlimited_int[0] = 1;
                i->sign = 1;
                i->unlimited_int[1] = 0;
                i->size = i->size + 1;
            }
        }
    }
    else
    {
        if (i1->sign != i2->sign)
        {
            i->sign = i1->get_sign();
            i->capacity = i1->get_size() + 3;
            i->unlimited_int = new int[i->capacity];
            for (int k = 0; k < i->capacity; k++)
            {
                i->unlimited_int[k] = 0;
            }
            i->unlimited_int[0] = i->sign;
            int carry = 0;
            for (int j = 1; j <= i2->get_size(); j++)
            {
                i->unlimited_int[j] = (i1->unlimited_int[j] + i2->unlimited_int[j] + carry) % 10;
                carry = (i1->unlimited_int[j] + i2->unlimited_int[j] + carry) / 10;
            }
            i->unlimited_int[i1->get_size() + 1] = carry;
            if (i->unlimited_int[i1->get_size() + 1] == 0)
            {
                i->size = i1->get_size();
            }
            else
            {
                i->size = i1->get_size() + 1;
            }
        }
        else
        {
            i->capacity = i2->get_size() + 2;
            i->unlimited_int = new int[i->capacity];
            for (int k = 0; k < i->capacity; k++)
            {
                i->unlimited_int[k] = 0;
            }
            i->unlimited_int[0] = i->sign;
            int given = 0;
            i->size = i1->size;
            if (compare(i1, i2) == i1)
            {
                i->sign = i1->sign;
                for (int j = 1; j <= i2->get_size(); j++)
                {
                    if (i1->unlimited_int[j] - i2->unlimited_int[j] - given < 0)
                    {
                        i->unlimited_int[j] = 10 + i1->unlimited_int[j] - i2->unlimited_int[j] - given;
                        given = 1;
                    }
                    else
                    {
                        i->unlimited_int[j] = i1->unlimited_int[j] - i2->unlimited_int[j] - given;
                        given = 0;
                    }
                }
                while (i->unlimited_int[i->size] == 0)
                {
                    i->size = i->size - 1;
                }
                if (i->size == 0)
                {
                    i->unlimited_int[0] = 1;
                    i->sign = 1;
                    i->unlimited_int[1] = 0;
                    i->size = i->size + 1;
                }
            }
            else
            {
                i->sign = (-1) * i2->sign;
                for (int j = 1; j <= i1->get_size(); j++)
                {
                    if (i2->unlimited_int[j] - i1->unlimited_int[j] - given < 0)
                    {
                        i->unlimited_int[j] = 10 + i2->unlimited_int[j] - i1->unlimited_int[j] - given;
                        given = 1;
                    }
                    else
                    {
                        i->unlimited_int[j] = i2->unlimited_int[j] - i1->unlimited_int[j] - given;
                        given = 0;
                    }
                }
                while (i->unlimited_int[i->size] == 0)
                {
                    i->size = i->size - 1;
                }
                if (i->size == 0)
                {
                    i->unlimited_int[0] = 1;
                    i->sign = 1;
                    i->unlimited_int[1] = 0;
                    i->size = i->size + 1;
                }
            }
        }
    }
    return i;
}

UnlimitedInt *UnlimitedInt ::mul(UnlimitedInt *i1, UnlimitedInt *i2)
{
    if (i1->to_string() == "0" || i2->to_string() == "0")
    {
        UnlimitedInt *i = new UnlimitedInt("0");
        return i;
    }
    UnlimitedInt *i = new UnlimitedInt();
    i->capacity = (i1->size + i2->size) + 2;
    i->size = (i1->size + i2->size);
    i->sign = i1->sign * i2->sign;
    i->unlimited_int = new int[i->capacity];
    for (int k = 0; k < i->capacity; k++)
    {
        i->unlimited_int[k] = 0;
    }
    i->unlimited_int[0] = i->sign;
    int *product = new int[i->capacity];
    int *carry = new int[i->capacity];
    for (int a = 0; a <= i->size; a++)
    {
        product[a] = 0;
        carry[a] = 0;
    }
    for (int j = 1; j <= i2->size; j++)
    {
        for (int k = 1; k <= i1->size; k++)
        {
            product[j + k - 1] = product[j + k - 1] + (i1->unlimited_int[k] * i2->unlimited_int[j]);
            if (product[j + k - 1] >= 10)
            {
                carry[j + k] = carry[j + k] + product[j + k - 1] / 10;
                product[j + k - 1] = product[j + k - 1] % 10;
            }
        }
    }
    for (int j = 1; j < i1->size + i2->size; j++)
    {
        i->unlimited_int[j] = product[j] + carry[j];
        if (i->unlimited_int[j] >= 10)
        {
            carry[j + 1] = carry[j + 1] + i->unlimited_int[j] / 10;
            i->unlimited_int[j] = i->unlimited_int[j] % 10;
        }
    }
    i->unlimited_int[i1->size + i2->size] = carry[i1->size + i2->size] + product[i1->size + i2->size];
    while (i->unlimited_int[i->size] == 0)
    {
        i->size = i->size - 1;
    }
    delete carry;
    delete product;
    return i;
}

UnlimitedInt *UnlimitedInt ::div(UnlimitedInt *i1, UnlimitedInt *i2)
{
    if (compare(i1, i2) == i2)
    {
        return (new UnlimitedInt("0"));
    }
    UnlimitedInt *i = new UnlimitedInt();
    i->size = i1->size - i2->size + 1;
    i->capacity = i1->size - i2->size + 3;
    i->unlimited_int = new int[i->capacity];
    for (int k = 0; k < i->capacity; k++)
    {
        i->unlimited_int[k] = 0;
    }
    i->sign = i1->sign * i2->sign;
    i->unlimited_int[0] = i->sign;
    if (i1->sign == i2->sign)
    {
        for (int k = i->size; k >= 1; k--)
        {
            while (compare(mul(i, i2), i1) == i1)
            {
                i->unlimited_int[k] = i->unlimited_int[k] + 1;
            }
            if (mul(i, i2)->to_string() != i1->to_string())
            {
                i->unlimited_int[k] = i->unlimited_int[k] - 1;
            }
        }
        while (i->unlimited_int[i->size] == 0)
        {
            i->size = i->size - 1;
        }
        if (i->size == 0)
        {
            i->unlimited_int[0] = 1;
            i->unlimited_int[1] = 0;
            i->size = i->size + 1;
            i->sign = 1;
        }
    }
    else
    {
        for (int k = i->size; k >= 1; k--)
        {
            while (compare(mul(i, i2), i1) == i1)
            {
                i->unlimited_int[k] = i->unlimited_int[k] + 1;
            }
            if (mul(i, i2)->to_string() != i1->to_string())
            {
                i->unlimited_int[k] = i->unlimited_int[k] - 1;
            }
        }
        while (i->unlimited_int[i->size] == 0)
        {
            i->size = i->size - 1;
        }
        if (i->size == 0)
        {
            i->unlimited_int[0] = 1;
            i->unlimited_int[1] = 0;
            i->size = i->size + 1;
            i->sign = 1;
        }
        if (mul(i, i2)->to_string() != i1->to_string())
        {
            i = sub(i, new UnlimitedInt("1"));
        }
    }
    return i;
}

UnlimitedInt *UnlimitedInt ::mod(UnlimitedInt *i1, UnlimitedInt *i2)
{
    if (i1->sign == i2->sign)
    {
        return sub(i1, mul(div(i1, i2), i2));
    }
    else if (i1->sign == -1)
    {
        return sub(i1, mul(div(i1, i2), i2));
    }
    else
    {
        return sub(mul(div(i1, i2), i2), i1);
    }
}

// int main()
// {
//     // Create two UnlimitedInt objects for testing
//     UnlimitedInt *num1 = new UnlimitedInt(20);
//     UnlimitedInt *num2 = new UnlimitedInt(-3);

//     // Call the add function to perform addition
//     UnlimitedInt *sum = UnlimitedInt::mod(num1, num2);

//     // Display the results
//     std::cout << "Number 1: " << num1->to_string() << std::endl;
//     std::cout << "Number 2: " << num2->to_string() << std::endl;
//     std::cout << "Sum: " << sum->to_string() << std::endl;
//     // std::cout<<compare(num1, num2)->to_string()<<endl;

//     // Clean up memory
//     delete num1;
//     delete num2;
//     // delete sum;

//     return 0;
// }

// division by zero error

// int main(){
//     UnlimitedInt* num = new UnlimitedInt("277568815104");
//     UnlimitedInt* den = new UnlimitedInt("665416609183179841");
//     cout<<UnlimitedInt::div(den, num)->to_string();
// }