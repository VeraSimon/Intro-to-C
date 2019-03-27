#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib.h"

/*
    Duplicates the input string by dynamically allocating memory for
    the duplicate string using `malloc` and then copying the string
    into the allocated memory. Returns a pointer to the allocated memory.
    You may want to use the string_length function to figure out the
    length of the input string.
*/
char *string_dup(char *src)
{
    int sLen = string_length(src);
    // Yes, chars are 1 byte. Yes, I'm still being explicit for readability sake.
    char *dupe = malloc(sLen * sizeof(char));
    // printf("Source string: %s\n", src);

    int inc = 0;
    while (src[inc] != 0)
    {
        // printf("cur src: %c\n", src[inc]);
        dupe[inc] = src[inc];
        inc++;
    }
    dupe[inc] = 0;

    // printf("Copied string: %s\n", dupe);
    return dupe;
}

/*
    A generic version of string_copy, mem_copy receives a block of memory
    of any type and copies its contents to the destination pointer (dest).
    You may want to cast the input pointers to char pointers first before
    performing the copying. `n` is the amount of data that should be copied
    from `src` to `dest`.
*/
void mem_copy(void *dest, const void *src, int n)
{
    // We're casting these both to `char` because we're actually unsure of the data in `src`, so we want to make sure to grab it 1 byte at a time so we don't muck it up or hop out of bounds while iterating.
    const char *cast_src = (char *)src;
    char *cast_dest = (char *)dest;

    for (int i = 0; i < n; i++)
    {
        cast_dest[i] = cast_src[i];
    }
}

/*
    Given a pointer of `malloc`'d memory, this function will
    attempt to resize the allocated memory to the new specified
    size. Any data that was previously in the old `malloc`'d
    memory should be intact in the new resized block of memory.
    Some edge cases to consider: how should resizing be handled
    in the case when old_size < new_size? What about when
    old_size > new_size?

    ^ According to the description, "Any data that was previously in the old malloc'd memory should be intact in the new resized block of memory." It would follow that if old_size > new_size, we should just bail, lest we risk data loss.
    In the case where new_size > old_size, we could well just ignore the trailing space? Could be useful if someone expected to add more data in addition to what we're starting with.
    - Vera

    Do not use the `realloc` function from the standard libary.
*/
void *resize_memory(void *ptr, int old_size, int new_size)
{
    char *cast_ptr = (char *)ptr;

    if (old_size > new_size)
    {
        // Don't want to lose data. Bail!
        return ptr;
    }
    else
    {
        // Do the hustle!
        char *newMem = malloc(new_size * sizeof(char));
        mem_copy(newMem, cast_ptr, old_size);
        ptr = newMem;
        return (void *)ptr;
    }
}

#ifndef TESTING
int main(void)
{
    char *s = "Some string to duplicate.";
    char *dup = string_dup(s);

    printf("Duplicated string: %s\n", dup);

    int numbers[] = {100, 55, 4, 98, 10, 18, 90, 95, 43, 11, 47, 67, 89, 42, 49, 79};
    int n = sizeof(numbers) / sizeof(numbers[0]);
    int *target = malloc(n * sizeof(int));

    mem_copy(target, numbers, n * sizeof(int));

    printf("Copied array: ");

    for (int i = 0; i < n; i++)
    {
        printf("%d ", target[i]);
    }

    printf("\n");

    char *url = string_dup("http://lambdaschool.com");
    char *path = string_dup("/students/");
    int url_length = string_length(url);
    int path_length = string_length(path);

    int new_length = url_length - 1 + path_length;
    char *new_url = resize_memory(url, url_length, new_length);
    char *p = new_url + url_length;

    while (*path != '\0')
    {
        *p = *path;
        p++;
        path++;
    }

    printf("Full path string: %s\n", new_url);

    return 0;
}
#endif