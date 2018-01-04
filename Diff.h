#include "tree_modified.h"

int simplified;

Node* d(Node* node); //Производнпая выражения
Node* c(Node* node); //Копия узла
Node* c_parent(Node* node);
int if_depends_on_variable(Node* node);
Node* simplify(Node* node);
Node* simplifyfy(Node* node);
Node* d_s(Node* node);
int ifequal(Node* node1, Node* node2);
Node* d_complex_function(Node* node, Node* (*diff)(Node* node), Node* argument);

Node* diff_Const(Node* node);
Node* diff_Variable(Node* node);
Node* diff_Multiply(Node* node);
Node* diff_Division(Node* node);
Node* diff_Addition(Node* node);
Node* diff_Difference(Node* node);

Node* diff_Sin(Node* node);
Node* diff_Cos(Node* node);
Node* diff_Tan(Node* node);
Node* diff_Sinh(Node* node);
Node* diff_Cosh(Node* node);
Node* diff_Tanh(Node* node);
Node* diff_Power_function(Node* node);
Node* diff_Exponential_function(Node* node);
Node* diff_Ln_function(Node* node);
Node* diff_Logarithmic_function(Node* node);


void Make_Report(Node* root, char* file_name); //Отчет дифференцирования в LaTeX-формате
void printTeX(Node* node, FILE* f);
