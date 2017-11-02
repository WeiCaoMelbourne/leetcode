/**
Reverse digits of an integer.

Example1: x = 123, return 321
Example2: x = -123, return -321

click to show spoilers.

Note:
The input is assumed to be a 32-bit signed integer. Your function should return 0 when the reversed integer overflows.
*/

int reverse(int x) {
    int integer_in_array[10];
    memset(integer_in_array, 0, sizeof(integer_in_array));
    
    int positive_x = abs(x);
    if (positive_x < 0)    /* overflow */
        return 0;
    
    int digit_count = 0;
    while (positive_x / 10 > 0)
    {
        integer_in_array[digit_count] = positive_x % 10;
        digit_count ++;
        positive_x /= 10;
    }
    
    integer_in_array[digit_count] = positive_x % 10;
    digit_count ++;
    
    int i = 0;
    int result = 0;
    const int MAX_INT32 = 2147483647;
    for (i = 0; i < digit_count; i++)
    {
        if (result > MAX_INT32 / 10)
            return 0;
        result = result * 10 + integer_in_array[i];
    }
    
    if (x < 0)
        result *= -1;
    
    return result;
}

int main()
{
    int r = reverse(-2147483648);
    printf("%d\n", r);
}