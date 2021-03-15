#ifndef TOKENS_H
#define TOKENS_H

enum TokenType {
  mod,
  id,
  eof,
  num,
  sym
};
extern char token[];
extern enum TokenType tokenType;
int next();

// simulate an exception by returning 0
#define RET_IF_FLS(x) if ((x) == 0) return 0;

#define DEBUG 0
#define INFIX 1
#define BUFSIZE 256

#if DEBUG
#define P(x) (puts(x))
#define D(x) (x)
#else 
#define P(x) do{}while(0)
#define D(x) do{}while(0)
#endif

#if INFIX 
#define INFIX_OUTPUT(x) (fputs(x, stdout))
#else 
#define INFIX_OUTPUT(x) do{}while(0)
#endif

#endif
