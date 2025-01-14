# include <string.h> 
# include <stdio.h> 
# define nochars 256 

 
int max (int a, int b){ 
  return (a > b)? a: b;
} 

void badTable(char str[], int size,int bad[noofchars]) 
{ 
    int i;
    for (i = 0;i<noofchars;i++) 
      bad[i]=-1;  
    for(i = 0; i < size; i++) 
    bad[(int) str[i]] = i; 
} 
  
/* A pattern searching function that uses Bad 
   Character Heuristic of Boyer Moore Algorithm */
void search( char *txt,  char *pat) 
{ 
    int m = strlen(pat); 
    int n = strlen(txt); 
  
    int badchar[NO_OF_CHARS]; 
  
    /* Fill the bad character array by calling  
       the preprocessing function badCharHeuristic()  
       for given pattern */
    badCharHeuristic(pat, m, badchar); 
  
    int s = 0;  // s is shift of the pattern with  
                // respect to text 
    while(s <= (n - m)) 
    { 
        int j = m-1; 
  
        /* Keep reducing index j of pattern while  
           characters of pattern and text are  
           matching at this shift s */
        while(j >= 0 && pat[j] == txt[s+j]) 
            j--; 
  
        /* If the pattern is present at current 
           shift, then index j will become -1 after 
           the above loop */
        if (j < 0) 
        { 
            printf("\n pattern occurs at shift = %d", s); 
  
            /* Shift the pattern so that the next  
               character in text aligns with the last  
               occurrence of it in pattern. 
               The condition s+m < n is necessary for  
               the case when pattern occurs at the end  
               of text */
            s += (s+m < n)? m-badchar[txt[s+m]] : 1; 
  
        } 
  
        else
            /* Shift the pattern so that the bad character 
               in text aligns with the last occurrence of 
               it in pattern. The max function is used to 
               make sure that we get a positive shift.  
               We may get a negative shift if the last  
               occurrence  of bad character in pattern 
               is on the right side of the current  
               character. */
            s += max(1, j - badchar[txt[s+j]]); 
    } 
} 
  
/* Driver program to test above function */
int main() 
{ 
    ; 
    search(txt, pat); 
    return 0; 
} 