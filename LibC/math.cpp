#include <LibC/math.h>


double modf(double v, double* iptr)
{
    long long int l = *reinterpret_cast<long long int*>(&v);
    long long int sign = l >> 63;
    long long int expo = (l >> 52 & 2047) - 1023;
    long long int mantissa_mask = 4503599627370495;
    long long int mantissa = l & mantissa_mask;

    if (expo >= 52) {
        if (expo != 1024) {
            *iptr = v;
        } else {
            if (mantissa != 0) {
                // nan
            } else {
                // infinity
            }
        }
        return 0;
    }

    if (expo < 0) {
        if (expo != -1023) {
            *iptr = 0;
        } else {
            if (mantissa != 0) {
                // subnormal
            } else {
                // signed zero
            }
        }
        return v;
    }

    /* long long int mantissa_lead_bit = 1ll << 51; */
    /* if (expo < 0) { */
    /*     *iptr = 0; */
    /*     return v; */
    /* } */
    /* mantissa = mantissa << expo; */
    /* *iptr = (mantissa & ~mantissa_mask) >> 52; */
    /* while (mantissa != 0 && (mantissa & mantissa_lead_bit) == 0) { */
    /*     mantissa = mantissa << 1; */
    /*     --expo_f; */
    /* } */
    /* mantissa = mantissa << 1; */
    /* mantissa &= mantissa_mask; */
    /* l = (sign << 63) | ((expo_f + 1023) << 52) | mantissa; */
    return *reinterpret_cast<double*>(&l);
}
