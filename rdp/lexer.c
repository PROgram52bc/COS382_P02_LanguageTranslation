// lexical analyzer

#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum TokenType tokenType;
char token[BUFSIZE];

int next() {
  // get the next token in the stream, set tokenType and token to corresponding values
  // return 0 if success, otherwise error.
  int t;
  char *pos = token;
  t = getchar();
  // skip space and new line characters
  while(t==' ' || t=='\t' || t=='\n' || t=='\r') t = getchar();
  if ((t>='A')&&(t<='Z') || (t>='a')&&(t<='z')) {
    // start with a letter, either eof, mod, or id.
    *(pos++) = t;
    t = getchar();
    while((t>='A')&&(t<='Z') || (t>='a')&&(t<='z') || (t>='0')&&(t<='9')) {
      *(pos++) = t;
      t = getchar();
      // check for overflow
      if (pos - token >= BUFSIZE) return -2;
    }
    ungetc(t,stdin);
    if (strcmp(token, "MOD") == 0) { 
      P("[next]: mod");
      tokenType = mod;
    }
    else if (strcmp(token, "EOF") == 0) { 
      P("[next]: EOF");
      tokenType = eof;
    }
    else { 
      P("[next]: id");
      tokenType = id;
    }
  } else if ((t>='0')&&(t<='9')) {
    // start with a number, a num.
    *(pos++) = t;
    t = getchar();
    while((t>='0')&&(t<='9')) {
      *(pos++) = t;
      t = getchar();
      // check for overflow
      if (pos - token >= BUFSIZE) return -2;
    }
    tokenType = num;
    ungetc(t,stdin);
    P("[next]: num");
  } else if (t=='*' || t=='/' || t=='+' || t=='-' || t=='(' || t==')' || t==';') { 
    // a symbol
    *(pos++) = t;
    tokenType = sym;
    P("[next]: sym");
  } else if (t == EOF) {
    // if actual end of file, return
    P("[next]: Actual End of file detected");
    tokenType = eof;
    return 0;
  }
  else {
    // invalid character
    *(pos++) = t;
    P("[next]: invalid character");
    return -1;
  }
  *(pos++) = '\0'; // terminate the string
  return 0;
}

// main function for testing only - remove before use

/* int main() { */
/*   int status = next(); */
/*   while (1) { */
/*     if (status != 0) { */
/*       // handle error */
/*       switch (status) { */
/*         case -1: */
/*           P("Invalid Character"); */
/*           printf("token: %s\n", token); */
/*           break; */
/*         case -2: */
/*           P("[next] exceeds buffer size"); */
/*           break; */
/*       } */
/*       break; */
/*     } else if (tokenType == eof) { */
/*       P("EOF reached"); */
/*       return 0; */
/*     } else { */
/*       printf("token: %s\n", token); */
/*     } */
/*     status = next(); */
/*   } */
/* } */
