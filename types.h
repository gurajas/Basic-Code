#ifndef _TYPES_H_
#define _TYPES_H_

#include <string>

using namespace std;

// Return type of a node
typedef enum __returntype {
  UNKNOWN_RT,               // Not (yet) known
  ERROR_RT,                 // Error
  VOID_RT,                  // Void
  INT_RT,                   // Integer
  REAL_RT,                  // Floating point
  BOOL_RT                   // Boolean expression
} ReturnType;


// Type of a symbol
typedef enum __symboltype {
  UNKNOWN_ST,               // Unknown (yet)
  ERROR_ST,                 // Error
  VARIABLE_ST,              // Variable
  PARAMETER_ST,             // Function/Procedure parameter
  PROCEDURE_ST,             // Procedure
  FUNCTION_ST,              // Function
  PROGRAM_ST,               // Program body
  TEMPVAR_ST,               // Temporary variable (not used before assignment 3)
  LABEL_ST                  // Label (not used before assignment 3)
} SymbolType;


// Type of a node in the syntax tree
typedef enum __nodetype {
  /* Meta */
  UNKNOWN_NODE,             // Unknown (yet)
  ERROR_NODE,               // Error
  
  /* Statement list
     left child     One of: NODE_ASSIGNMENT, NODE_IF, NODE_WHILE,
                    NODE_PROCCALL, NODE_FUNCTIONCALL, NODE_STATEMENT_LIST.
     right child    One of: NODE_ASSIGNMENT, NODE_IF, NODE_WHILE,
                    PROCCALL_NODE, NODE_FUNCTIONCALL, NODE_STATEMENT_LIST, or
                    EMPTY_NODE if no more statements follow. */
  STATEMENT_LIST_NODE,

  /* Assignment
     left child     A NODE_ID that identifies the destination variable
     right child    A subtree representing an expression */
  ASSIGNMENT_NODE,

  /* If statement
     left child     A NODE_BOOLEXPR that provides the if condition
     right child    A NODE_IF_TARGETS subtree (if there is an else clause) or
                    a subtree consisting of statements (if there's no else) */
  IF_NODE,

  /* Targets of an if-else-statement
     left child     The statements that have to be executed when the condition
                    of the parent if-statement is true.
     right child    The statements that have to be executed when the condition
                    of the parent if-statement is false, that is, the else
                    part. */
  IF_TARGETS_NODE,

  /* While loop
     left child     A NODE_BOOLEXPR that provides the loop condition
     right child    A subtree consisting of statements */
  WHILE_NODE,

  /* Subprogram calls
     left child     A NODE_ID that identifies the called function/procedure
     right child    A NODE_EXPRLIST that specifies the actual arguments, or
                    NODE_EMPTY if no arguments required. */
  PROCCALL_NODE,
  FUNCTIONCALL_NODE,

  /* Expression list
     left child     A subtree representing an expression
     right child    A subtree representing an expression, another
                    NODE_EXPRLIST, or NODE_EMPTY if no more expressions follow
                    in the expression list. */
  EXPRLIST_NODE,

  /* Boolean-like expression
     child          A subtree with any NODE_REL_ node as parent */
  BOOLEXPR_NODE,

  /* Relational operators
     left child     Left-hand side of the comparison
     right child    Right-hand side of the comparison */
  REL_EQUAL_NODE,           //  = operator
  REL_LT_NODE,              //  < operator
  REL_GT_NODE,              //  > operator
  REL_LTE_NODE,             //  <= operator
  REL_GTE_NODE,             //  >= operator
  REL_NOTEQUAL_NODE,        //  <> operator

  /* Binary arithmetic & logic operations
     left child     Left-hand side of the operation
     right child    Right-hand side of the operation */
  ADD_NODE,                 // Add
  SUB_NODE,                 // Subtract
  OR_NODE,                  // OR operation
  MUL_NODE,                 // Multiply
  DIV_NODE,                 // Divide
  IDIV_NODE,                // Integer division
  MOD_NODE,                 // Modulo
  AND_NODE,                 // AND operation

  /* Leafs
     these nodes have no child nodes */
  NUM_INT_NODE,             // Integer number
  NUM_REAL_NODE,            // Real number
  ID_NODE,                  // Identifier
  EMPTY_NODE,               // Empty leaf (terminates lists etc.)

  /* Unary nodes
     child          The subtree to which the operation has to be applied */
  NOT_NODE,                 // NOT operation
  SIGNPLUS_NODE,            // Unary plus
  SIGNMINUS_NODE,           // Unary minus
  COERCION_NODE            // Int to Real coercion
} NodeType;


/* Prototypes */
const char * ReturnTypeToString (ReturnType returntype);
const char * SymbolTypeToString (SymbolType symboltype);
const char * NodeTypeToString (NodeType nodetype);

#endif
