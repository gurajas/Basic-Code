/* C declarations */
%{

#include <stdio.h>
#include <math.h>
#include "debug.h"
#include "SyntaxTree.h"
#include "SymbolTable.h"
#include "Node.h"


/* Prototypes */
static void yyerror(const char *);


/* Import from comp.l */
#ifdef __cplusplus
extern "C" {
#endif

int yylex(void);   /* Lexer function */

#ifdef __cplusplus
}
#endif

extern int lineno;        /* Current line number */


/* Other declarations */
SyntaxTree * tree;        /* The syntax tree */
SymbolTable * symtab;     /* The symbol table */
string mainScopeName;     /* The name of the main scope */


#ifdef DEBUG
int msglevel = 90; /* higher = more debugging messages */
#else
int msglevel = 0;   /* don't bother sensitive souls */
#endif

%}

/* Start symbol */
%start program

/* Tokens */
%token PROGRAM ID VAR NUM INTEGER REAL FUNCTION PROCEDURE 
%token PASCALBEGIN /* BEGIN is used internally by flex :-( */
%token END ADDOP ASSIGNOP IF THEN ELSE WHILE DO RELOP
%token MULOP NOT PROG_PARAMETER IRRELEVANT
%token UMINUS /* unary minus */

/* Types to pass between lexer, rules and actions */
%union {
  char *idStr;
  char *numStr;
  Node *node;
}

%expect 1  /* shift/reduce conflict: dangling ELSE */
%% 

/* GRAMMAR RULES AND ACTIONS */

program:        PROGRAM ID {
                  /* The program name has just been read; save it */
                  mainScopeName = $<idStr>2;

                  /* Free the chars allocated by the lexer */
                  free($<idStr>2);
                  
                  /* Put the program name into the syntax tree */
                  tree->SetProgramName (mainScopeName);
                  
                  /* Create a new scope in the symbol table */
                  symtab->AddScope (mainScopeName);
                }
                ';' declarations subprogram_declarations 
                compound_statement '.'
                ;


type_identifier_list:
                ',' ID type_identifier_list 

                | ':' type
                ; 


declarations:   /* In declarations the VAR-variables are listed for the 
                   program as well as for the procedures and functions. */

                declarations VAR ID 
                
                type_identifier_list ';'

                | /* lambda */
                ;


type:           standard_type

                ;


standard_type:  INTEGER

                | REAL
                ; 


subprogram_declarations:
                subprogram_declarations subprogram_declaration ';'

                | /* lambda */
                ;


subprogram_declaration: 
                subprogram_head declarations compound_statement
                ;


subprogram_head: 
                FUNCTION ID arguments ':' standard_type ';'

                | PROCEDURE ID arguments ';'
                ;


arguments:      '(' parameter_lists ')'

                | /* lambda */
                ;


parameter_lists: parameter_list ';' parameter_lists
                
                | parameter_list 
                ;


parameter_list: ID type_identifier_list
                ;


compound_statement:
                PASCALBEGIN optional_statements END
                ;


optional_statements:
                statement_list

                | /* lambda */
                ;


statement_list: statement

                | statement_list ';' statement
                ;


statement:      variable ASSIGNOP expression
                
                | procedure_statement
                
                | compound_statement
                
                | IF boollikeexp THEN statement optional_else_statement
                
                | WHILE boollikeexp DO statement
                ;


optional_else_statement:
                ELSE statement

                | /* lambda */
                ;


variable:
                ID
                
                ;


procedure_statement:
                ID
                
                | ID '(' expression_list ')' 
                
                ;


expression_list:
                expression
                
                | expression ',' expression_list
                ;

boollikeexp:    expression RELOP expression
                
                | '(' boollikeexp ')' 
                ; /* to allow stuff like "if (a > 3) then" */


expression:     simple_expression
                ;


simple_expression:
                term
                
                | signplus term
        
                | signminus term
        
                | simple_expression '+' term {
                  /*
                  This is an example on how to work with the syntax tree construction routines:
                  
                  ReturnType returnType = ...
                  $<node>$ = tree->CreateParentNode(NODE_ADD, returnType, $<node>1, $<node>3);
                  
                  Using this invocation, we construct a parent node of type NODE_ADD,
                  with child nodes $<node>1 and $<node>3 (these refer to 'simple_expression'
                  resp. 'term'). The return type of this node should be based on that of its
                  child nodes.
                  Using the assignment to $<node>$, the newly created node is passed to a
                  grammar rule at a higher level, where the subtree should be inserted into a
                  larger tree using a similar approach.
                  
                  */
                }
                
                | simple_expression '-' term
                
                | simple_expression ADDOP term
                ;


term:           factor
                
                | term MULOP factor
                ;


factor:         ID
                
                | ID '(' expression_list ')'
                
                | NUM 
                
                | '(' expression ')'
                
                | NOT factor
                
                ;


signplus:       '+'
                ;
                
signminus:      '-' %prec UMINUS
                ;

%%

/* End of rules, more C code will follow now */

void initialize()
{
  /* Create & initialize the abstract data structures */
  tree = new SyntaxTree;
  symtab = new SymbolTable;
}


void cleanup()
{
  /* Free objects */
  delete tree;
  delete symtab; 
}


int main()
{
  int parseResult;
  
  initialize();

  /* Start the parsing procedure */
  parseResult = yyparse();
  
  /* Dump the syntax tree & symbol table */
  tree->Dump (stdout);
  printf("\n");
  symtab->Dump (stdout);
  
  cleanup();
  
  /* Return the exit code. Note that the exit code does not depend on
     parseResult only, but also on the result of your semantic checks */
  return parseResult;
}


static void yyerror(const char *s)
{
  fprintf(stderr, "line %d: %s\n", lineno, s);
}

int yywrap()
{
  return(1);
}
