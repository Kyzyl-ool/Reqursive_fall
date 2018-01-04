#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "files.h"
#include "tree_modified.h"


int cur = 0;
char256 printstring;
char256 err;

#define DEBUG

tree* tree_Construct(char* tree_name)
{
	tree* t = (tree *)calloc(1, sizeof(tree));
	t->root = NULL;
	t->name = tree_name;
	return t;
}

void tree_Destroy(tree* t)
{
	#ifdef DEBUG
	assert(t);
	#endif
	tree_node_Destroy(t->root);
	free(t);
}

void tree_node_Destroy(Node* node)
{
	#ifdef DEBUG
	assert(node);
	#endif
	if (node->left)
	{
		tree_node_Destroy(node->left);
	}
	if (node->right)
	{
		tree_node_Destroy(node->right);
	}
	free(node);
}

int tree_Insert_to_end(Node* parental_node, node_code who, type t, data value)
{
	Node* new_node = (Node* )calloc(1, sizeof(Node));
	new_node->t = t;
	new_node->value = value;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->parent = parental_node;
	switch (who)
	{
		case LEFT_NODE:
		{
			parental_node->left = new_node;
			break;
		}
		case RIGHT_NODE:
		{
			parental_node->right = new_node;
			break;
		}
		default:
		{
			#ifdef DEBUG
			printf("tree_Insert_to_end: TREE_INSERT_TO_END_WITH_INVALID_PARENT\n");
			#endif
			free(new_node);
			return TREE_INSERT_TO_END_WITH_INVALID_PARENT;
		}
	}
	return 0;
}

int tree_Delete_node(Node* node)
{
	#ifdef DEBUG
	assert(node);
	#endif
	switch (tree_node_which_am_I_child(node))
	{
		case LEFT_NODE:
		{
			node->parent->left = NULL;
			free(node);
			break;
		}
		case RIGHT_NODE:
		{
			node->parent->right = NULL;
			free(node);
			break;
		}
		case TREE_TRYING_TO_LEARN_ABOUT_ROOT:
		{
			free(node);
			return TREE_TRYING_TO_DELETE_ROOT;
			break;
		}
		default:
		{
			#ifdef DEBUG
			printf("tree_node_Destroy: TREE_NODE_FIASKO\n");
			#endif
			return TREE_NODE_FIASKO;
			break;
		}
	}
	free(node);
	return 0;
}

int tree_node_which_am_I_child(Node* node)
{
	#ifdef DEBUG
	assert(node);
	#endif
	if (node->parent)
	{
		if (node->parent->left && node->parent->left == node)
		{
			return LEFT_NODE;
		}
		if (node->parent->right && node->parent->right == node)
		{
			return RIGHT_NODE;
		}
	}
	else
	{
		return TREE_TRYING_TO_LEARN_ABOUT_ROOT;
	}
	return TREE_NODE_FIASKO;
}

int tree_node_check(Node* node)
{
	int nullnodes = 0, brokennodes = 0;
	if (!node) return (TREE_NODE_IS_NULL << 8);
	else
	{
		if (!node->left)
			if (!(node->left->parent == node))
				brokennodes |= LEFT_NODE;
			else;
		else
			nullnodes |= LEFT_NODE;
			
		if (!node->right)
			if (!(node->right->parent == node))
				brokennodes |= RIGHT_NODE;
			else;
		else
			nullnodes |= RIGHT_NODE;
		
		if (!node->parent)
			if ((!node->parent->left && !(node->parent->left == node)) || (!node->parent->right && !(node->parent->right == node)))
				brokennodes |= PARENT_NODE;
			else;
		else
			nullnodes |= PARENT_NODE;
	}
	
	if (!brokennodes)
		return (TREE_NODE_IS_BROKEN << 8) | (brokennodes);
	else
		return (TREE_NODE_IS_OK << 8) | nullnodes;
}

int tree_node_check_old(Node* node)
{
	if (!node)
	{
		return TREE_NODE_IS_NULL;
	}
	else
	{
		if (node->parent)
		{
			if (node->parent->left)
			{
				if (node->parent->right)
				{
					if (node->parent->left != node && node->parent->right != node)
					{
						return TREE_NODE_IS_BROKEN;
					}
					else;
				}
				else
				{
					if (node->parent->left != node)
					{
						return TREE_NODE_IS_BROKEN;
					}
					else;
				}
			}
			else
			{
				if (node->parent->right)
				{
					if (node->parent->right != node)
					{
						return TREE_NODE_IS_BROKEN;
					}
					else;
				}
				else
				{
					return TREE_NODE_FIASKO;
				}
			}
		}
		else;
		
		if (node->left)
		{
			if (node->left->parent)
			{
				if (node->left->parent != node)
				{
					return TREE_NODE_IS_BROKEN;
				}
				else;
			}
			else
			{
				return TREE_NODE_IS_BROKEN;
			}
		}
		
		if (node->right)
		{
			if (node->right->parent)
			{
				if (node->right->parent != node)
				{
					return TREE_NODE_IS_BROKEN;
				}
				else;
			}
			else
			{
				return TREE_NODE_IS_BROKEN;
			}
		}
		
		return TREE_NODE_IS_OK;
	}
}

int tree_check(tree* t)
{
	#ifdef DEBUG
	printf("WHY ARE YOU USING tree_check?\n");
	#endif
	return 999;
}

char* tree_error_message(int code)
{
	printf("[%X]\n", code >> 8);
	printf("[%X]\n", TREE_NODE_IS_NULL);
	switch (code >> 8)
	{
		#define _RET_CODE(code) case code: { sprintf(err, "[%s", #code); break; }
		_RET_CODE(TREE_NODE_FIASKO)
		_RET_CODE(TREE_NODE_IS_OK)
		_RET_CODE(TREE_IS_OK)
		_RET_CODE(TREE_NODE_IS_BROKEN)
		_RET_CODE(TREE_NODE_IS_NULL)
		_RET_CODE(TREE_INSERT_TO_END_WITH_INVALID_PARENT)
		default: sprintf(err, "TREE_UNKNOWN_ERROR");
	}
	strcat(err, "] ");
	switch (code << 12)
	{
		_RET_CODE(LEFT_NODE)
		_RET_CODE(RIGHT_NODE)
		_RET_CODE(PARENT_NODE)
		#undef _RET_CODE
	}
	return err;
}

char* tree_error_message_old(int code)
{
	switch (code)
	{
		#define _RET_CODE(code) case code: return #code;
		_RET_CODE(TREE_NODE_FIASKO)
		_RET_CODE(TREE_NODE_IS_OK)
		_RET_CODE(TREE_IS_OK)
		_RET_CODE(TREE_NODE_IS_BROKEN)
		_RET_CODE(TREE_NODE_IS_NULL)
		_RET_CODE(TREE_INSERT_TO_END_WITH_INVALID_PARENT)
		default: return "TREE_NODE_UNKNOWN";
		#undef _RET_CODE
	}
}

void tree_print_meaning_of_error_code(int code)
{
	printf("%s\n", tree_error_message(code));
}

void tree_print_meaning_of_error_code_old(int code)
{
	printf("%s\n", tree_error_message_old(code));
}

int tree_Print_GML(tree* t, char* gml_file_name)
{
	#ifdef DEBUG
	assert(t);
	#endif
	FILE* dump = fopen(gml_file_name, "w");
	
	fprintf(dump, "graph\n[\n");
	
	tree_node_print_GML(t->root, dump);
	
	fprintf( dump,"]\n");
	
	fclose(dump);
	return 0;
}

void tree_node_print_GML(Node* node, FILE* dump)
{
	#ifdef DEBUG
	assert(node);
	#endif
	fprintf(dump, "	node\n	[\n		id %llu\n		label \"%s\"\n	]\n\n", (unsigned long long int)node, node_data(node));
	if (node->left)
	{
		tree_node_print_GML(node->left, dump);
		tree_edge_print_GML(node, node->left, 0, dump, "left");
	}
	
	if (node->right)
	{
		tree_node_print_GML(node->right, dump);
		tree_edge_print_GML(node, node->right, 0, dump, "right");
	}
	if (node->parent)
	{
		tree_edge_print_GML(node, node->parent, 0, dump, "parent");
	}
}

void tree_edge_print_GML(Node* node1, Node* node2, double value, FILE* dump, char* who)
{
	#ifdef DEBUG
	assert(node1);
	assert(node2);
	#endif
	if (value)
		fprintf(dump, "	edge\n	[\n		source %llu\n		target %llu		value %lg\n		label \"%s\"\n	]\n", (unsigned long long int)node1, (unsigned long long int)node2, value, who);
	else
		fprintf(dump, "	edge\n	[\n		source %llu\n		target %llu\n		label \"%s\"\n	]\n", (unsigned long long int)node1, (unsigned long long int)node2, who);
}

/*
tree* tree_Read_GML(char* gml_file_name)
{
	Node* nodes[1024] = {0};
	unsigned long long int ids[1024] = {0};
	int current_id = 0;
	
	tree* t = tree_Construct("Unnamed");
	
	char* text = readfile(gml_file_name);
	int N = amount_of_strings(text);
	char** gml = make_array_of_strings_beginnings_with_sep(text, '\n');
	replace_in_array(text, '\n', '\0');
	for (int i = 0; i < N; i++)
	{
		char256 x;
		sscanf(gml[i], "%s", x);
		if (!strcmp(x, "node"))
		{
			i+=2;
			unsigned long long int id;
			char256 label;
			sscanf(gml[i++], "%s%llu", x, &id);
			sscanf(gml[i], "%s%s", x, label);
			
			ids[current_id] = id;
			nodes[current_id] = (Node* )calloc(1, sizeof(Node));
			array_Assign(nodes[current_id]->sentence, label, 1);
			nodes[current_id]->left = NULL;
			nodes[current_id]->right = NULL;
			nodes[current_id++]->parent = NULL;
			
		}
		else if (!strcmp(x, "edge"))
		{
			i+=2;
			unsigned long long int id1, id2;
			char256 label;
			sscanf(gml[i++], "%s%llu", x, &id1);
			sscanf(gml[i++], "%s%llu", x, &id2);
			sscanf(gml[i], "%s%s", x, label);
			
			if (!strcmp(label, "\"left\""))
			{
				nodes[array_Find(ids, id1, 1024)]->left = nodes[array_Find(ids, id2, 1024)];
			}
			else if (!strcmp(label, "\"right\""))
			{
				nodes[array_Find(ids, id1, 1024)]->right = nodes[array_Find(ids, id2, 1024)];
			}
		}
	}
	
	t->root = nodes[0];
	return t;
}
* */

int array_Find(unsigned long long int* array, unsigned long long int value, int size)
{
	assert(array);
	for (int i = 0; i < size; i++)
	{
		if (array[i] == value)
			return i;
	}
	
	#ifdef DEBUG
	printf("array_Find returned -1\n");
	#endif
	return -1;
}

void array_Assign(char* arr1, char* arr2, char apart_from_ends)
{
	int i = 0;
	if (apart_from_ends)
	{
		for (i = 0; arr2[i+1] != '\"'; i++) arr1[i] = arr2[i+1];
	}
	else
	{
		for (i = 0; arr2[i] != '\0'; i++) arr1[i] = arr2[i];
	}
	arr1[i] = '\0';
}

void tree_Print_DED(tree* t, char* ded_file_name)
{
	#ifdef DEBUG
	assert(t);
	#endif
	FILE* fo = fopen(ded_file_name, "w");
	
	tree_node_print(t->root, fo);
	
	fclose(fo);
}

void tree_node_print(Node* node, FILE* file)
{
	if (node)
	{
		fprintf(file, "(\"%s\"", node_data(node));
		if (node->left)
		{
			tree_node_print(node->left, file);
		}
		if (node->right)
		{
			tree_node_print(node->right, file);
		}
		fprintf(file, ")");
	}
}

tree* tree_Read_DED(char* ded_file_name)
{
	int i = 0;
	char* text = readfile(ded_file_name);
	if (text)
	{
		tree* t = tree_Construct("The tree");
		t->root = tree_read_node(text, &i);
		return t;
	}
	else
	{
		return NULL;
	}
}

Node* tree_read_node(char* text, int* i)
{
	if (text[*i] == '(')
	{
		Node* node = (Node* )calloc(1, sizeof(Node));
		int ii = 0;
		char256 label;
		*i += 1;
		while (text[*i] != '(' && text[*i] != ')')
		{
			label[ii] = text[*i];
			*i += 1;
			ii++;
		}
		label[ii] = '\0';
		char256 tmp;
		array_Assign(tmp, label, 0);
		switch (tmp[0])
		{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			{
				if (amount_of_char(tmp, '.') > 0)
				{
					node->t = NUMBER_DOUBLE;
					sscanf(tmp, "%lg", &node->value.d);
				}
				else
				{
					node->t = NUMBER_INT;
					sscanf(tmp, "%d", &node->value.i);
				}
				break;
			}
			case '+':
			{
				node->t = OPERATOR;
				node->value.o = PLUS;
				break;
			}
			case '-':
			{
				node->t = OPERATOR;
				node->value.o = MINUS;
				break;
			}
			case '*':
			{
				node->t = OPERATOR;
				node->value.o = MULTIPLY;
				break;
			}
			case '/':
			{
				node->t = OPERATOR;
				node->value.o = DIVIDE;
				break;
			}
			case 'x':
			{
				node->t = VARIABLE;
				node->value.vt = x;
				break;
			}
			case 'y':
			{
				node->t = VARIABLE;
				node->value.vt = y;
				break;
			}
			case 'z':
			{
				node->t = VARIABLE;
				node->value.vt = z;
				break;
			}
			case '^':
			{
				node->t = OPERATOR;
				node->value.o = POWER;
				break;
			}
			case 's':
			{
				node->t = OPERATOR;
				if (tmp[3] == 'h')
				{
					node->value.o = SINH;
				}
				else
				{
					node->value.o = SIN;
				}
				break;
			}
			case 'c':
			{
				node->t = OPERATOR;
				if (tmp[2] == 's')
				{
					if (tmp[3] == 'h')
					{
						node->value.o = COSH;
					}
					else
					{
						node->value.o = COS;
					}
				}
				else
				{
					if (tmp[3] == 'h')
					{
						node->value.o = COTH;
					}
					else
					{
						node->value.o = COT;
					}
				}
				break;
			}
			case 'l':
			{
				if (tmp[1] == 'n')
				{
					node->t = OPERATOR;
					node->value.o = LN;
					break;
				}
				else if (tmp[1] == 'o')
				{
					node->t = OPERATOR;
					node->value.o = LOG;
					break;
				}
			}
			case 'e':
			{
				if (tmp[1] == '\0')
				{
					node->t = CONSTANT;
					node->value.c = E;
				}
				break;
			}
			case 'p':
			{
				if (tmp[1] == 'i')
				{
					node->t = CONSTANT;
					node->value.c = PI;
				}
				else if (tmp[1] == 'h')
				{
					node->t = CONSTANT;
					node->value.c = PHI;
				}
			}
			case 't':
			{
				node->t = OPERATOR;
				if (tmp[3] == 'h')
				{
					node->value.o = TANH;
				}
				else
				{
					node->value.o = TAN;
				}
				break;
			}
			default:
			{
				#ifdef DEBUG
				printf("tree_read_node: UNKNOWN SYMBOL READ\n");
				#endif
			}
			
		}
		
		node->left = tree_read_node(text, i);
		if (node->left) *i += 1;
		node->right = tree_read_node(text, i);
		if (node->right) *i += 1;
		return node;
	}
	else
	{
		return NULL;
	}
}

char* type_to_string(type t)
{
	switch (t)
	{
		#define _RET_CODE(code) case code: return #code;
		_RET_CODE(OPERATOR)
		_RET_CODE(VARIABLE)
		_RET_CODE(NUMBER_INT)
		_RET_CODE(NUMBER_DOUBLE)
		_RET_CODE(CONSTANT)
		default: return "UNKNOWN_TYPE";
		#undef _RET_CODE
	}
}

char* operator_to_string(operator o)
{
	switch (o)
	{
		#define _RET_CODE(code) case code: return #code;
		_RET_CODE(SIN)
		_RET_CODE(COS)
		_RET_CODE(LN)
		_RET_CODE(LOG)
		_RET_CODE(TAN)
		_RET_CODE(COT)
		_RET_CODE(SINH)
		_RET_CODE(COSH)
		_RET_CODE(TANH)
		_RET_CODE(COTH)
		_RET_CODE(PLUS)
		_RET_CODE(MINUS)
		_RET_CODE(MULTIPLY)
		_RET_CODE(DIVIDE)
		_RET_CODE(POWER)
		default:
		{
			#ifdef DEBUG
			printf("operator_to_string HAD GOT UNKNOWN OPERATOR\n");
			#endif
			return "UNKNOWN_OPERATOR";
		}
		#undef _RET_CODE
	}
}

char* vartype_to_string(vartype vt)
{
	switch (vt)
	{
		case x: return "x";
		case y: return "y";
		case z: return "z";
		default: return "UNKNOWN_VARTYPE";
	}
}

char* constant_to_string(constant c)
{
	switch (c)
	{
		case E: return "e";
		case PI: return "pi";
		case PHI: return "phi";
		default: return "UNKNOWN_CONSTANT";
	}
}

char* node_data(Node* node)
{
	#ifdef DEBUG
	assert(node);
	#endif
	for (int i = 0; i < 256; i++) printstring[i] = 0;
	switch (node->t)
	{
		case NUMBER_INT:
		{
			sprintf(printstring, "%d", node->value.i);
			return printstring;
		}
		case NUMBER_DOUBLE:
		{
			sprintf(printstring, "%lg", node->value.d);
			return printstring;
		}
		case VARIABLE:
		{
			sprintf(printstring, "%s", vartype_to_string(node->value.vt));
			return printstring;
		}
		case OPERATOR:
		{
			sprintf(printstring, "%s", operator_to_string(node->value.o));
			return printstring;
		}
		case CONSTANT:
		{
			sprintf(printstring, "%s", constant_to_string(node->value.c));
			return printstring;
		}
		default:
		{
			#ifdef DEBUG
			printf("node_data HAD GOT INVALID NODE TYPE\n");
			#endif
			return "INVALID_NODE_TYPE";
		}
	}
}
