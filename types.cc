#include <string>
#include "types.h"

using namespace std;

const char * ReturnTypeToString(ReturnType returntype) {
	switch (returntype) {
	case UNKNOWN_RT:
		return "UNKNOW return type";
	case ERROR_RT:
		return "Error return type";
	case VOID_RT:
		return "Void return type";
	case INT_RT:
		return "INT return type";
	case REAL_RT:
		return "REAL return type";
	case BOOL_RT:
		return "BOOL return type";
	default:
		return "default";
	}
}

const char * SymbolTypeToString(SymbolType symboltype) {
	switch (symboltype) {
	case UNKNOWN_ST:
		return "UNKNOW return type";
	case ERROR_ST:
		return "Error return type";
	case FUNCTION_ST:
		return "Void return type";
	case LABEL_ST:
		return "INT return type";
	case PARAMETER_ST:
		return "REAL return type";
	case PROCEDURE_ST:
		return "BOOL return type";
	case PROGRAM_ST:
		return "BOOL return type";
	case TEMPVAR_ST:
		return "BOOL return type";
	case VARIABLE_ST:
		return "BOOL return type";
	default:
		return "default";
	}
}

const char * NodeTypeToString(NodeType nodetype) {
	switch (nodetype) {
	case ADD_NODE:
		return "UNKNOW return type";
	case AND_NODE:
		return "Error return type";
	case ASSIGNMENT_NODE:
		return "Void return type";
	case BOOLEXPR_NODE:
		return "INT return type";
	case COERCION_NODE:
		return "REAL return type";
	case DIV_NODE:
		return "BOOL return type";
	case EMPTY_NODE:
		return "UNKNOW return type";
	case ERROR_NODE:
		return "Error return type";
	case EXPRLIST_NODE:
		return "Void return type";
	case FUNCTIONCALL_NODE:
		return "INT return type";
	case IDIV_NODE:
		return "REAL return type";
	case ID_NODE:
		return "BOOL return type";
	case IF_NODE:
		return "BOOL return type";
	case IF_TARGETS_NODE:
		return "BOOL return type";
	case MOD_NODE:
		return "BOOL return type";
	case MUL_NODE:
		return "BOOL return type";
	case NOT_NODE:
		return "BOOL return type";
	case NUM_INT_NODE:
		return "BOOL return type";
	case NUM_REAL_NODE:
		return "BOOL return type";
	case OR_NODE:
		return "BOOL return type";
	case PROCCALL_NODE:
		return "BOOL return type";
	case REL_EQUAL_NODE:
		return "BOOL return type";
	case REL_GTE_NODE:
		return "BOOL return type";
	case REL_GT_NODE:
		return "BOOL return type";
	case REL_LTE_NODE:
		return "BOOL return type";
	case REL_LT_NODE:
		return "BOOL return type";
	case REL_NOTEQUAL_NODE:
		return "BOOL return type";
	case SIGNMINUS_NODE:
		return "BOOL return type";
	case SIGNPLUS_NODE:
		return "BOOL return type";
	case STATEMENT_LIST_NODE:
		return "BOOL return type";
	case SUB_NODE:
		return "BOOL return type";
	case UNKNOWN_NODE:
		return "BOOL return type";
	case WHILE_NODE:
		return "BOOL return type";
	default:
		return "default";
	}
}
