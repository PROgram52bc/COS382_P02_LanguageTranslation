// RDP parser for the postfix problem

// start -> list eof
// list -> expr ';' list
//      |
// expr -> term terms
// terms -> '+' term terms
//      |   '-' term terms
//      |
// term -> factor factors
// factors ->   '*' factor factors
//      |       '/' factor factors
//      |       mod factor factors
//      |
// factor ->    '(' expr ')'
//      |       id
//      |       num
// eof, mod, id, num are captured by lexer

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.h"

struct node {
  char *content;
  struct node *next;
};

struct node *symbols = NULL;

// allocate a new node on heap and prepend it before 'next'
// return the new node
struct node* add_node(const char* content, struct node* next) {
  struct node *new_node = malloc(sizeof(struct node));
  new_node->content = strdup(content);
  new_node->next = next;
  return new_node;
}

// first might be NULL
void clean_nodes(struct node* first) {
  if (first == NULL) {
    return;
  }
  if (first->content != NULL) {
    D(printf("Cleaning node [%s]\n", first->content));
    free(first->content);
  }
  clean_nodes(first->next);
  free(first);
}

// first CANNOT be NULL
void print_nodes(struct node* first, const char* sep) {
  if (first->content == NULL) {
    printf("<NULL>");
  } else {
    printf("%s", first->content);
  }
  if (first->next == NULL) {
    return;
  } else {
    printf("%s", sep);
    print_nodes(first->next, sep);
  }
}

int isToken(const char* s) {
  return strcmp(s, token) == 0;
}

int matchToken(const char* s) {
  int equal = isToken(s);
  next();
  return equal;
}

int matchTokenType(enum TokenType tt) {
  int equal = tt == tokenType;
  next();
  return equal;
}

int expr();

int factor() {
  switch (tokenType) {
    case id:
#if INFIX
      // store symbol
      symbols = add_node(token, symbols);
#endif
    case num:
      INFIX_OUTPUT(token);
      INFIX_OUTPUT(" ");
      return matchTokenType(tokenType);
    case sym:
      RET_IF_FLS(matchToken("("));
      RET_IF_FLS(expr());
      return matchToken(")");
    default:
      return 0;
  }
}

int factors() {
  switch (tokenType) {
    case sym:
      if (isToken("*")) {
        RET_IF_FLS(matchToken("*"));
        RET_IF_FLS(factor());
        INFIX_OUTPUT("* ");
        return factors();
      } else if (isToken("/")) {
        RET_IF_FLS(matchToken("/"));
        RET_IF_FLS(factor());
        INFIX_OUTPUT("/ ");
        return factors();
      }
      break;
    case mod:
      RET_IF_FLS(matchTokenType(mod));
      RET_IF_FLS(factor());
      INFIX_OUTPUT("mod ");
      return factors();
  }
  return 1; // match epsilon
}

int term() {
  RET_IF_FLS(factor());
  return factors();
}

int terms() {
  switch (tokenType) {
    case sym:
      if (isToken("+")) {
        RET_IF_FLS(matchToken("+"));
        RET_IF_FLS(term());
        INFIX_OUTPUT("+ ");
        return terms();
      } else if (isToken("-")) {
        RET_IF_FLS(matchToken("-"));
        RET_IF_FLS(term());
        INFIX_OUTPUT("- ");
        return terms();
      }
      break;
    case mod:
      RET_IF_FLS(matchTokenType(mod));
      RET_IF_FLS(factor());
      INFIX_OUTPUT("mod ");
      return factors();
      break;
  }
  return 1; // match epsilon
}

int expr() {
  RET_IF_FLS(term());
  return terms();
}

int list() {
  if (!(tokenType == sym && isToken("(") ||
        tokenType == id ||
        tokenType == num)) {
    return 1; // match epsilon
  }
  RET_IF_FLS(expr());
  RET_IF_FLS(matchToken(";"));
  INFIX_OUTPUT(";\n");
  return list();
}

int start() {
  RET_IF_FLS(list());
  RET_IF_FLS(matchTokenType(eof));
  INFIX_OUTPUT("eof\n");
#if INFIX
  printf("Symbols: ");
  print_nodes(symbols, ", ");
  printf("\n");
  clean_nodes(symbols);
#endif
  
  return 1;
}

int main() {
  next(); // skip checking error
  if (start()) {
    printf("Successfully matched\n");
  } else {
    printf("Failed to match\n");
  }
}
