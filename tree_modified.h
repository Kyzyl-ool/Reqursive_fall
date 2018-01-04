#define SENTENCE_LENGTH 256

typedef double Node_t;
typedef char char256[SENTENCE_LENGTH];
typedef enum type
{
	OPERATOR,
	VARIABLE,
	NUMBER_INT,
	NUMBER_DOUBLE,
	CONSTANT,
} type;

typedef enum operators
{
	SIN,
	SINH,
	COS,
	COSH,
	COTH,
	COT,
	LN,
	LOG,
	TAN,
	TANH,
	
	PLUS,
	MINUS,
	MULTIPLY,
	DIVIDE,
	POWER,
} operator;

typedef enum vartypes
{
	x,
	y,
	z,
} vartype;

typedef enum constants
{
	E,
	PI,
	PHI,
} constant;

typedef union data
{
	constant c;
	operator o;
	int i;
	double d;
	vartype vt;
} data;

typedef struct Node
{
	data value;
	type t;
	struct Node* left;
	struct Node* right;
	struct Node* parent;
}Node;

typedef struct bintree
{
	Node* root;
	char* name;
	int amount;
}tree;

typedef enum tree_node_codes
{
	LEFT_NODE = 0b10,
	RIGHT_NODE = 0b01,
	PARENT_NODE = 0b100
}node_code;

typedef enum tree_error_codes
{
	TREE_NODE_FIASKO = -1,
	TREE_NODE_IS_OK,
	TREE_IS_OK,
	TREE_NODE_IS_BROKEN,
	TREE_NODE_IS_NULL,
	TREE_INSERT_TO_END_WITH_INVALID_PARENT,
	TREE_TRYING_TO_DELETE_ROOT,
	TREE_TRYING_TO_LEARN_ABOUT_ROOT,
}tree_error_code;

tree* tree_Construct(char* tree_name);
void tree_Destroy(tree* t);
void tree_node_Destroy(Node* node);
int tree_Delete_node(Node* node);

int tree_Insert_to_end(Node* parental_node, node_code who, type t, data value);


int tree_node_which_am_I_child(Node* node);
int tree_node_check(Node* node);
int tree_check(tree* t);
int tree_node_check_old(Node* node);

void tree_node_print_GML(Node* node, FILE* dump);
void tree_edge_print_GML(Node* node1, Node* node2, double value, FILE* dump, char* who);
int tree_Print_GML(tree* t, char* gml_file_name);
void tree_Print_DED(tree* t, char* ded_file_name);
void tree_node_print(Node* node, FILE* file);
tree* tree_Read_DED(char* ded_file_name);
Node* tree_read_node(char* text, int* i);

char* tree_error_message(int code);
char* tree_error_message_old(int code);
void tree_print_meaning_of_error_code(int code);
void tree_print_meaning_of_error_code_old(int code);


//~ tree* tree_Read_GML(char* gml_file_name);


int array_Find(unsigned long long int* array, unsigned long long int value, int size);
void array_Assign(char* arr1, char* arr2, char apart_from_ends);

char* type_to_string(type t);
char* operator_to_string(operator o);
char* constant_to_string(constant c);
char* vartype_to_string(vartype vt);
char* node_data(Node* node);

