
/*
ZigZag Conversion
The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R
And then read line by line: "PAHNAPLSIIGYIR"
Write the code that will take a string and make this conversion given a number of rows:

string convert(string text, int nRows);
convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR".

n=numRows
Δ=2n-2    1                           2n-1                         4n-3
Δ=        2                     2n-2  2n                    4n-4   4n-2
Δ=        3               2n-3        2n+1              4n-5       .
Δ=        .           .               .               .            .
Δ=        .       n+2                 .           3n               .
Δ=        n-1 n+1                     3n-3    3n-1                 5n-5
Δ=2n-2    n                           3n-2                         5n-4
*/

char* convert(char* s, int numRows) 
{
    int str_len = strlen(s);
    if (numRows <= 1)
    {
        char* result = (char*)malloc(str_len + 1);
        snprintf(result, (str_len + 1), "%s", s);
        return result;
    }

    char zigzag_array[numRows][str_len];
    
    memset(zigzag_array, ' ', sizeof(zigzag_array));
    
    int cur_pos = 0, cur_row = 0, cur_line = 0;
    while (cur_pos < str_len)
    {
        if (cur_line % (numRows - 1) == 0)
        {
            zigzag_array[cur_row][cur_line] = s[cur_pos];
            cur_pos ++;
        }
        else if (cur_line % (numRows - 1) == numRows - 1 - cur_row % numRows)
        {
            zigzag_array[cur_row][cur_line] = s[cur_pos];
            cur_pos ++;
        }

        cur_row ++;
        if (cur_row == numRows)
        {
            cur_row = 0;
            cur_line ++;
        }
    }
    
    char* result = (char*)malloc(str_len + 1);
    
    cur_pos = 0;
    int i = 0;
    for (; i < numRows; i ++)
    {
        int j = 0;
        for (; j < str_len; j ++)
        {
            if (zigzag_array[i][j] != ' ')
            {
                result[cur_pos] = zigzag_array[i][j];
                cur_pos ++;
            }
        }
    }
    
    result[str_len] = 0;
    return result;
}

int main()
{
    char* s = "Apalindromeisaword,phrase,number,orothersequenceofunitsthatcanbereadthesamewayineitherdirection,withgeneralallowancesforadjustmentstopunctuationandworddividers.";
    char* result = convert(s, 2);
    printf("%s\n", result);
    return 0;
}