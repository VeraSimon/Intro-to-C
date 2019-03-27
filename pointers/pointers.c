#include <stdio.h>
#include <string.h>

/*
    Given a character pointer x (that points to an array of chars), and a
    character pointer y, copies the character contents of y over to x. Pointer
    arithmetic is necessary here. Also, make sure x points to a null terminator
    at its end to terminate it properly.

    Example call:

    char buffer[1024];

    string_copy(buffer, "Hello!");
    printf("%s", buffer); // Prints "Hello!"
*/
void string_copy(char *x, char *y)
{
    int yLen = strlen(y);

    for (int i = 0; i < yLen; i++)
    {
        x[i] = y[i];
    }
}

/*
    Searches the input string `str` for the first instance of the
    character `c` (an unsigned char). This function returns a pointer
    that points to the first instance of the character `c` in the
    input string `str`.

    Do not use the `strchr` function from the standard library.
*/
char *find_char(char *str, int c)
{
    // int sLen = string_length(str);

    // for (int i = 0; i <= sLen; i++)
    // {
    //     if (str[i] == c)
    //     {
    //         return &str[i];
    //     }
    // }

    // Bit more concise. Doesn't need a full for loop implementation, since we can just use the null terminator to stop the loop at worst. No pesky worrying about off by 1 errors.
    while (*str != 0)
    {
        if (*str == c)
        {
            return str;
        }
        str++;
    }

    // In case `c` doesn't exist in `str`, otherwise we'd have an edge case where the app crashes due to not returning at all
    return NULL;
}

/*
    Searches the input string `haystack` for the first instance of
    the string `needle`. This function returns a pointer that points
    to the first instance of the string `needle` in the input
    string `haystack`.

    Do not use the `strstr` function from the standard library.
*/
char *find_string(char *haystack, char *needle)
{
    int hLen = strlen(haystack);
    int nLen = strlen(needle);
    char *substring = malloc(nLen * sizeof(char));

    while (*haystack != 0)
    {
        char *startChar = find_char(haystack, needle[0]);

        if (*startChar == 0 || (&startChar + (nLen - 1)) > &haystack[hLen - 1])
        {
            break;
        }

        int isNeedle = 0;
        for (int i = 0; i < nLen; i++)
        {
            if (*startChar != needle[i])
            {
                isNeedle = 0;
                haystack = startChar;
                break;
            }
            substring[i] = *startChar;
            isNeedle = 1;
            startChar++;
        }

        if (isNeedle != 0)
        {
            return substring;
        }
        haystack++;
    }

    // In case needle isn't found
    return NULL;
}

#ifndef TESTING
int main(void)
{
    // Someone forgot to declare their `hello` and `world` variables in case `make tests` wasn't called ;P
    char hello[] = "Hello";
    char world[] = "world!";

    char *found_char = find_char(hello, 'e');
    char *found_string = find_string(world, "or");

    printf("Found char: %s\n", found_char);
    printf("Found string: %s\n", found_string);

    return 0;
}
#endif
