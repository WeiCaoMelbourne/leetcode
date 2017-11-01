/**
Longest Palindromic Substring

Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.

Example:

Input: "babad"

Output: "bab"

Note: "aba" is also a valid answer.
Example:

Input: "cbbd"

Output: "bb"
*/
int find_longest_from_center(char* s, int center, int* start_pos, int* end_pos)
{
    int str_len = strlen(s);
    if (str_len <= 0)
        return 0;

    int pos = 1;
    int max_palindromic_len = 1;
    while (center - pos >= 0 && center + pos <= str_len - 1)
    {
        if (s[center - pos] == s[center + pos])
        {
            max_palindromic_len = pos * 2 + 1;
            *start_pos = center - pos;
            *end_pos = center + pos;
        }
        else
        {
            break;
        }

        pos ++;
    }

    pos = 0;
    while (center - pos >= 0 && center + pos + 1 <= str_len - 1)
    {
        if (s[center - pos] == s[center + pos + 1])
        {
            if ((pos + 1) * 2 > max_palindromic_len)
            {
                max_palindromic_len = (pos + 1) * 2;
                *start_pos = center - pos;
                *end_pos = center + pos + 1;
            }            
        }
        else
        {
            break;
        }

        pos ++;
    }

    return max_palindromic_len;
}

char* longestPalindrome(char* s) {
    const int MAX_LENGTH = 1000;
    char tmp[MAX_LENGTH];
    
    int str_len = strlen(s);
    int cur_pos = 0, max_start = 0;
    int max_palindromic_len = 1;
    while (cur_pos < str_len - 1)
    {
        int start_pos = 0, end_pos = 0;
        int palindromic_len = find_longest_from_center(s, cur_pos, &start_pos, &end_pos);
        if (palindromic_len > max_palindromic_len)
        {
            max_start = start_pos;
            max_palindromic_len = palindromic_len;
        }

        cur_pos ++;
    }
    
    char* result = (char*)malloc(max_palindromic_len + 1);
    memset(result, 0, max_palindromic_len + 1);
    memcpy(result, s + max_start, max_palindromic_len);
    
    return result;
}

#if 0
int is_palindromic(char* s)
{
    printf("%s %s\n", __FUNCTION__, s);
    int str_len = strlen(s);
    if (str_len <= 0)
        return 0;
    
    int median = str_len / 2;
    
    int cur = 0;
    while (cur <= median)
    {
        if (s[cur] != s[str_len - cur - 1])
            return 0;
        cur ++;
    }
    
    return 1;
}

char* longestPalindrome(char* s) {
    const int MAX_LENGTH = 1000;
    char tmp[MAX_LENGTH];
    
    int str_len = strlen(s);
    int cur_pos = 0;
    int max_palindromic_len = 1;
    int max_start = 0;
    while (cur_pos < str_len)
    {
        if (cur_pos + max_palindromic_len > str_len)
            break;
        
        int cur_len = str_len - cur_pos;
        
        while(cur_len > 0 && cur_len > max_palindromic_len)
        {
            memset(tmp, 0, sizeof(tmp));
            memcpy(tmp, s + cur_pos, cur_len);
            tmp[cur_pos + cur_len] = 0;
            if (is_palindromic(tmp))
            {
                max_palindromic_len = cur_len;
                max_start = cur_pos;
                break;
            }   
            
            cur_len --;
        }
        
        cur_pos ++;
    }
    
    char* result = (char*)malloc(max_palindromic_len + 1);
    memset(result, 0, max_palindromic_len + 1);
    memcpy(result, s + max_start, max_palindromic_len);
    
    return result;
}
#endif

#if 0
int find_longest_crossing_palindrome(char* s, int l_pos, int r_pos, int center, int* start_pos, int* end_pos)
{
    int str_len = strlen(s);
    if (str_len <= 0)
        return 0;
    
    if (str_len % 2 == 0)
    {
        int pos = 1;
        while (center + pos <= r_pos && center - pos + 1 >= l_pos)
        {
            if (s[center + pos] == s[center - pos + 1])
            {
                *start_pos = center - pos + 1;
                *end_pos = center + pos;
            }
            else
            {
                return (pos - 1) * 2;
            }   
            
            pos ++;
        }
        
        return (pos - 1) * 2;
    }        
    else
    {
        int pos = 1;
        while (center + pos <= r_pos && center - pos >= l_pos)
        {
            if (s[center + pos] == s[center - pos])
            {
                *start_pos = center - pos;
                *end_pos = center + pos;
            }
            else
            {
                return (pos - 1) * 2 + 1;
            }   
            
            pos ++;
        }
        
        return (pos - 1) * 2 + 1;
    }
}

int find_longest_palindrome(char* s, int l_pos, int r_pos, int* start_pos, int* end_pos)
{
    if (l_pos < r_pos)
    {
        int center = (l_pos + r_pos) / 2;
        int start1, end1, start2, end2, start3, end3;
        int l_longest = find_longest_palindrome(s, l_pos, center, &start1, &end1);
        int r_longest = find_longest_palindrome(s, center + 1, r_pos, &start2, &end2);
        int crossing_longest = find_longest_crossing_palindrome(s, l_pos, r_pos, center, &start3, &end3);
        
        if (l_longest >= r_longest && l_longest >= crossing_longest)
        {
            *start_pos = start1;
            *end_pos = end1;
            return l_longest;
        }
        
        if (r_longest >= l_longest && r_longest >= crossing_longest)
        {
            *start_pos = start2;
            *end_pos = end2;
            return r_longest;
        }
        
        if (crossing_longest >= r_longest && crossing_longest >= l_longest)
        {
            *start_pos = start3;
            *end_pos = end3;
            return crossing_longest;
        }
    }
    
    *start_pos = *end_pos = l_pos;
    return 1;
}

char* longestPalindrome(char* s) {
    int start_pos, end_pos;
    int max_palindromic_len = find_longest_palindrome(s, 0, strlen(s) - 1, &start_pos, &end_pos);
    
    char* result = (char*)malloc(max_palindromic_len + 1);
    memset(result, 0, max_palindromic_len + 1);
    memcpy(result, s + start_pos, max_palindromic_len);
    
    return result;
}
#endif

int main()
{
    char* s = "cwziydanrqvsdtvnnqgjnbrvvwxwqojeqgxhwxdoktjktulemwpbeqscbbtbfvkxsrjetfdrovcrdwzfmnnihtgxybuairswfewvpuscocqifuwylhssldpjrawqdrbvkykpaggspbfrulcktpbofchzikhzxhpocgvdbwpewpywsgqbczmamprklaoovcfecwchhmsaqkhvuvvzjblmgvqpqtnlipgqsanvovylpmxlmxvymppdykphhaamtxjnnlsqfwjwhyywgurteaummwhvavxbcpgrfffxrowluqmqjaugryxdmwvyokdcfcvcytxpixbvwrdgzctejdoaavgtezexmvxgrkpnayvfarkyoruofqmpnsqdzojxqrjsnfwsbzjmaoigytygukqlrcqaxazvmytgfghdczvzphfdbnxtklaiqqsotavdmhiaermluafheowcobjqmrkmlzyas";
    char* r = longestPalindrome(s);
    printf("%s\n", r);
}