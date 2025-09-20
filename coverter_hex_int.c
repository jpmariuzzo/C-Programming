// K&R Exercise 2-2.
// You should write a function (no #include statements are needed) called htoi(str) that converts hexadecimal constant (base-16 0-9 and a-f) to an integer. 
// There will not be a '0x' prefix (like in C) - just assume the input is a hex number. You should not use ctype.h and your code can assume the ASCII character set.
// Each time you run the program, the values you need to convert e903b (base-16) to 954427 (base-10) may be different each time you run the code. 

#include <stdio.h>
#include <string.h> 
int main() {
  int htoi();
  printf("htoi('e903b') = %d\n", htoi("e903b"));
  printf("htoi('f') = %d\n", htoi("f"));
  printf("htoi('F0') = %d\n", htoi("F0"));
  printf("htoi('12fab') = %d\n", htoi("12fab"));
}


int htoi(s) /* convert s to integer */
char s[];
{
    int i, n;

    n = 0;
    for (i = 0; i<strlen(s); ++i)
        if (s[i] >= '0' && s[i] <= '9'){
            n = 16*n + s[i] - '0';
        }
        else if (s[i] >= 'a' && s[i] <= 'f'){
            n = 16*n + s[i] - 'a' + 10;
        }
        else if (s[i] >= 'A' && s[i] <= 'F'){
            n = 16*n + s[i] - 'A' + 10;
        }
    return(n);
}

