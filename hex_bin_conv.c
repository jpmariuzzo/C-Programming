// K&R Exercise 3-4.
// Write a function itob(n, s) which converts the unsigned integer n into a binary (base 2) character representation in s. 
// Write itoh, which converts an integer to hexadecimal representation. You can assume that the s variable contains enough space. 
// Make sure to properly terminate s with the end-of-string marker '\0' before returning.
// You can use reverse(s) to reverse a string - make sure you pass a character array and not a string constant to reverse.

#include <stdio.h>
#include <string.h>
int main() {
  char s[1000];
  void itob(), itoh(), reverse();

  itob(42,s);
  printf("42 in base-2 is %s\n", s);
  
  itoh(42,s);
  printf("42 in base-16 is %s\n", s);

  itob(16,s);
  printf("16 in base-2 is %s\n", s);
  
  itoh(16,s);
  printf("16 in base-16 is %s\n", s);

  itob(59,s);
  printf("59 in base-2 is %s\n", s);
  
  itoh(59,s);
  printf("59 in base-16 is %s\n", s);

  itob(100,s);
  printf("100 in base-2 is %s\n", s);
  
  itoh(100,s);
  printf("100 in base-16 is %s\n", s);

  itob(254,s);
  printf("254 in base-2 is %s\n", s);
  
  itoh(254,s);
  printf("254 in base-16 is %s\n", s);
}

void reverse(t)
char t[];
{
    int i, j, len;
    char tmp;
    len = strlen(t);
    for(i=0, j=len-1;;i++,j--) {
        if (j<i) break;
        tmp = t[i];
        t[i] = t[j];
        t[j] = tmp;
    }
    return;
}

// FUNCTION itob(n, s)

void itob(n, s)
int n; 
char s[];
{
    int k; 
    int q;
    
    char bin [1000];
    k = 0;
    q = n;

    if (q==0){
        bin[0] = '0';
        bin[1] = '\0';
    }
    else{
        while (q>0){
            bin[k++] = q%2 + '0';
            q = (q/2);
            }
        bin[k] = '\0';
        reverse(bin);
    }
    
    
    int m;
    for(m=0;(s[m] = bin[m]);m++);
    
    //strcpy(s, bin);
    
}

// FUNCTION itoh(n, s)

void itoh(n, s)
int n;
char s[];
{
    int l; 
    int qh;
    int h;
    
    char hex [1000];
    l = 0;
    qh = n;

    while (qh>0){
        h = qh%16;
        
        if (h >= 0 && h <= 9){
            hex[l++] = h +'0';
        }
        else if (h >= 10 && h <= 15){
            hex[l++] = h - 10 +'a';
        }
        
        qh = (qh/16);
    }
    
    hex[l] = '\0';
    reverse(hex);
    

    int p;
    for(p=0; (s[p] = hex[p]); p++);

    //strcpy(s, hex);
}