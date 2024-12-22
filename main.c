/*   * Sadeen
     * 1212164
*/
/* My program uses Linked Lists to store the expressions,
 * a stack to convert infix expressions to postfix, and a tree structure to evaluate expressions.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define Max 50

// Linked List
typedef struct Node {
    char Equation[Max]; // String with 50 characters
    struct Node* next;
} Node;

typedef Node* List;
typedef Node* ptrToNode;
/*--------------------------------------------------------------------------------------------------------------------*/
// Stack structure
typedef struct Stack {
    char elements[Max];
    int top;
} Stack;

typedef Stack* stack;
/*--------------------------------------------------------------------------------------------------------------------*/

typedef struct TreeNode {
    char data[10]; // Data of the node (operator or operand)
    struct TreeNode* left;
    struct TreeNode* right;
}TreeNode;

TreeNode *createNewNode(char D[]) {
    TreeNode *newNode = (TreeNode *) malloc(sizeof(TreeNode));
    strcpy(newNode->data, D);
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to check if the character is an operator
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%');
}

// Function to build the expression tree from postfix expression
TreeNode* buildExpressionTree(char* postfix) {
    /*initializes a stack of pointers to TreeNode with a maximum size of 100,
     and a variable top to keep track of the top of the stack.*/
    TreeNode *stack[100];
    int top = -1;

    //A loop that iterates through each character in postfix expression.
    for (int i = 0; postfix[i] != '\0'; ++i) {
        int j = 0;
       // If the current character is a Digit or a Minus sign indicating a negative number
        if (isdigit(postfix[i]) || (postfix[i] == '-' && isdigit(postfix[i + 1]))) {
            char value[10] = "";
            while(isdigit(postfix[i]) || postfix[i] == '-') {
                value[j++] = postfix[i++]; // The new node is then pushed into the stack.
            }
            i--;
            // it extracts the operand (number) from the postfix expression and creates a new TreeNode for that operand.
            stack[++top] = createNewNode(value);
        }
        //If the current character is an operator, it creates a new TreeNode for that operator.
        // It pops two nodes from the stack (representing the right and left operands)
        // and sets them as the right and left children of the new node. The new node is then pushed back onto the stack.
        else if (isOperator(postfix[i])) {
            char value[] = {postfix[i], '\0'};
            TreeNode *C = createNewNode(value);
            C->right = stack[top--];
            C->left = stack[top--];
            stack[++top] = C;
        }
    }
    return stack[top];
}

// Function to evaluate the expression tree
int evaluateExpressionTree(TreeNode* root) {
    if (root == NULL) {
        printf("Error\n");
        return 0;
    }

    if (isdigit(root->data[0]) || (root->data[0] == '-' && isdigit(root->data[1]))) {
        return strtol(root->data, NULL, 10); // Convert operand string to integer
    }

    //Recursively evaluates the left and right subtrees.
    int leftValue = evaluateExpressionTree(root->left);
    int rightValue = evaluateExpressionTree(root->right);

    switch (root->data[0]) {
        case '+':
            return leftValue + rightValue;

        case '-':
            return leftValue - rightValue;

        case '*':
            return leftValue * rightValue;

        case '/':
            if (rightValue != 0) {
                return leftValue / rightValue;
            } else {
                return INT_MAX; // Handle division by zero error
            }

        case '%':
            if (rightValue != 0) {
                return leftValue % rightValue;
            } else {
                return INT_MAX; // Handle modulo by zero error
            }
    }

    return 0; // Return 0 for an empty tree or invalid input
}

/*--------------------------------------------------------------------------------------------------------------------*/
void Menu();
List ReadFromFile(const char* filename);
void PrintList(List list);
void InitializeStack(stack StacK);
int IsFull(stack StacK);
int IsEmpty(stack StacK);
void Push(stack StacK, char item);
char Pop(stack StacK);
char Peek(stack StacK);
int isOperator(char ch);
TreeNode* buildExpressionTree(char *postfix);
int evaluateExpressionTree(TreeNode* root);
int Precedence(char op);
char* infixToPostfix(char equation[]);
void SaveToFile(List list);

int main() {
    int s=1;
    struct Node* FileList =  (struct Node *) malloc(sizeof(struct Node));
    struct Node* List=(struct Node *) malloc(sizeof(struct Node));
    FileList->next=NULL;
    List->next=NULL;
    char equation[Max];

    do {
        Menu();
        scanf("%d", &s);
        int flag;
        switch (s) {

            case 1:
                flag =1;
               //Load strings from the input file to the original list
                FileList= ReadFromFile("Input.txt");

                break;

            case 2:
                // Print the Equations from the file with ignoring the special character and While space.
                if(flag==1){
                    if (FileList == NULL) {
                        printf("No strings loaded.\n");
                    }
                    else {
                        PrintList(FileList);
                    }
                }
                else
                    printf("Choose the select 1 to load the Equations From the Input File");
                break;

            case 3:
                if(flag==1){
                    if (FileList == NULL) {
                    printf("No strings loaded.\n");
                    }
                    else {
                    ptrToNode currentNode = FileList->next;

                    while (currentNode != NULL) {
                        strcpy(equation, currentNode->Equation);

                        printf("\nResult for %s : ", equation);

                        char *postfix = infixToPostfix(equation);
                        TreeNode *root = buildExpressionTree(postfix);
                        int result = evaluateExpressionTree(root);
                        if(result != INT_MAX) {
                            printf("%d\n", result);
                        }
                        else
                            printf("\nError: Division/Modulo by zero.\n\n");

                        currentNode = currentNode->next;
                    }
                }}
                else
                    printf("Choose the select 1 to load the Equations From the Input File");
                    break;

                case 4:
                    if(flag==1){
                        if (FileList == NULL) {
                        printf("No strings loaded.\n");
                        }
                        else {
                        ptrToNode currentNode = FileList->next;

                        while (currentNode != NULL) {
                            strcpy(equation, currentNode->Equation);

                            printf("\nPostfix Expression for %s : ", equation);
                            char *postfix = infixToPostfix(equation);

                            printf("%s\n",postfix);

                            currentNode = currentNode->next;
                        }
                    }}
                    else
                        printf("Choose the select 1 to load the Equations From the Input File");
                     break;

            case 5:
                if(flag==1){
                    if (FileList == NULL) {
                        printf("No strings loaded.\n");
                    } else {
                        SaveToFile(FileList);
                        printf("Postfix expressions and results saved to 'OutputFile.txt'.\n");
                }}
                 else
                printf("Choose the select 1 to load the Equations From the Input File");
                break;

            case 6:
                return 0;

            default:
                printf("Invalid Choice. Please try again.\n");
                break;
        }
    } while (1);
}

void Menu() {
    printf("\nHELLO, Choose one :\n");
    printf("  1- Read Equations\n");
    printf("  2- Print Equations\n");
    printf("  3- Evaluate using Expression tree\n");
    printf("  4- Print Postfix Expressions\n");
    printf("  5- Save to Output File (Postfix and Results)\n");
    printf("  6- Exit\n");
}

void PrintList(List list) {
    ptrToNode temp = list;

    if (temp == NULL) {
        printf("Empty List!\n");
        return;
    }
    printf("List of Equations :\n");

    while (temp->next != NULL) {
        printf("%s\n", temp->next->Equation);
        temp = temp->next;
    }
    printf("\n");
}

List ReadFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return NULL;
    }

    List list = (Node *)malloc(sizeof(Node));
    ptrToNode tail = NULL;

    char equation[Max];

    while (fgets(equation, Max, file) != NULL) {
        // Remove trailing newline character, if present
        equation[strcspn(equation, "\n")] = '\0';

        // Filter out characters that are not valid operators or digits and limit to 51 characters
        char validEquation[Max];
        int j = 0;
        int invalidEquation = 0; // Flag to check if the equation has divide by zero

        for (int i = 0; equation[i] != '\0' && j < Max - 1; i++) {
            if (!isspace(equation[i]) && (isdigit(equation[i]) || strchr("+-*/%()", equation[i]) != NULL)) {
                validEquation[j++] = equation[i];
//                // Check for division by zero
//                if (equation[i] == '/' && equation[i + 1] == '0') {
//                    invalidEquation = 1;
//                }
            }
        }
        validEquation[j] = '\0';

        // Skip empty or invalid equations (divide by zero)
        if (j == 0 || invalidEquation) {
            continue;
        }

        ptrToNode newNode = (Node *)malloc(sizeof(Node));
        if (newNode == NULL) {
            printf("Out of Memory!\n");
            fclose(file);
            return NULL;
        }

        strncpy(newNode->Equation, validEquation, Max - 1);
        newNode->Equation[Max - 1] = '\0'; // Ensure null-terminated string
        newNode->next = NULL;

        if (tail != NULL) {
            tail->next = newNode;
        } else {
            list->next = newNode;
        }
        tail = newNode;
    }

    fclose(file);
    return list;
}

void InitializeStack(stack StacK) {
    StacK->top = -1;
}

int IsFull(stack StacK) {
    return StacK->top == Max - 1;
}

int IsEmpty(stack StacK) {
    return StacK->top == -1;
}

void Push(stack StacK, char item) {
    if (IsFull(StacK)) {
        printf("Stack Overflow\n");
        return;
    }
    StacK->elements[++(StacK->top)] = item;
}

char Pop(stack StacK) {
    if (IsEmpty(StacK)) {
        printf("Stack Underflow\n");
        return '\0';
    }
    return StacK->elements[(StacK->top)--];
}

// Retrieve the top element of a stack without removing it.
char Peek(stack StacK) {
    if (IsEmpty(StacK)) {
        printf("Stack is Empty\n");
        return '\0';
    }
    return StacK->elements[StacK->top];
}

int Precedence(char op) {  /* الأولوية */
    if (op == '+' || op == '-') {
        return 1;
    }
    else if (op == '*' || op == '/' || op == '%') {
        return 2;
    }
    return 0;
}

void SaveToFile(List list) {
    FILE *file = fopen("Output.txt", "w");

    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    ptrToNode temp = list;

    while (temp->next != NULL) {
        char equation[Max];
        strcpy(equation, temp->next->Equation);

        fprintf(file, "Postfix Expression: ");
        char *postfix = infixToPostfix(equation);
        fprintf(file, "%s", postfix);


        TreeNode  *root = buildExpressionTree(postfix);

        int result = evaluateExpressionTree(root);
        if(result != INT_MAX)
          fprintf(file, "\nResult: %d\n\n", result);
        else
            fprintf(file, "\nError: Division/Modulo by zero.\n\n");

        temp = temp->next;
    }
        fclose(file);
}

char* infixToPostfix(char equation[]) {
    Stack stack;
    InitializeStack(&stack);
    char* postfix = (char*)malloc( sizeof(char));
    int postfixIndex = 0;
    int i;

    for (i = 0; equation[i] != '\0'; i++) {
        if (equation[i] == ' ' || equation[i] == '\t')
            continue;

        if (isdigit(equation[i]) || (equation[i] == '-' && (i == 0 || !isdigit(equation[i - 1])))) {
            char value[10] = "";
            int j = 0;

            // Handle negative numbers
            if (equation[i] == '-') {
                value[j++] = equation[i++];
            }

            while (isdigit(equation[i])) {
                value[j++] = equation[i++];
            }

            i--;
            value[j] = '\0';

            // Add space after the number
            for (j = 0; value[j] != '\0'; j++) {
                postfix[postfixIndex++] = value[j];
            }
            postfix[postfixIndex++] = ' ';
            }
            else if (equation[i] == '(') {
                Push(&stack, equation[i]);
            }
            else if (equation[i] == ')') {
            //pops operators from the stack and appends them to the postfix expression until an opening parenthesis is found.
                while (!IsEmpty(&stack) && Peek(&stack) != '(') {
                    postfix[postfixIndex++] = Pop(&stack);
                }
                Pop(&stack);  // Pop '(' from the stack
            }
            else if (isOperator(equation[i])) {
                while (!IsEmpty(&stack) && Precedence(Peek(&stack)) >= Precedence(equation[i])) {
                    postfix[postfixIndex++] = Pop(&stack);
                }
                Push(&stack, equation[i]);
            }
            }
   /* After processing all characters in the infix expression, any remaining operators in the stack are popped and appended
    to the postfix expression.
    The function then terminates and returns the postfix expression. */
            while (!IsEmpty(&stack)) {
                postfix[postfixIndex++] = Pop(&stack);
            }
            postfix[postfixIndex] = '\0';
            return postfix;
}
