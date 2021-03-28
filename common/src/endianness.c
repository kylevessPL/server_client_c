#include <endianness.h>

uint64_t htond(double hostdouble)
{
    char* src = (char*) &hostdouble;
    uint64_t res;
    char *dest = (char*) &res;
    if (!IS_BIG_ENDIAN)
    {
        for (int i = 0; i < sizeof(double); i++)
        {
            dest[i] = src[sizeof(double) - i - 1];
        }
        return res;
    }
    for (int i = 0; i < sizeof(double); i++)
    {
        dest[i] = src[i];
    }
    return res;
}

double ntohd(uint64_t netdouble)
{
    char* src = (char*) &netdouble;
    double res;
    char *dest = (char*) &res;
    if (!IS_BIG_ENDIAN)
    {
        for (int i = 0; i < sizeof(double); i++)
        {
            dest[i] = src[sizeof(double) - i - 1];
        }
        return res;
    }
    for (int i = 0; i < sizeof(double); i++)
    {
        dest[i] = src[i];
    }
    return res;
}
