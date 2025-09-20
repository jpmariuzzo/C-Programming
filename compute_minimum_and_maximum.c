#include <stdio.h>
int main() {
    int first = 1;
  	char line [10];
  	int val, maxval, minval;
  	while ((fgets(line, 10, stdin)) != NULL){
      val = atoi(line);
      if ((strcmp(line, "done\n")) == 0) { // return 0 if matchesbreak;
        break;
      }
      val = atoi(line);
      if (first||val>maxval){
        maxval = val;
      }
      if(first||val<minval){
        minval = val;
      }
      first = 0;
    }
  	printf("Maximum %d\n", maxval);
  	printf("Minimum %d\n", minval);
}