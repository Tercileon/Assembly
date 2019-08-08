/*
 * Printf() Debugging Demo
 */

#include <stdio.h>

// Function prototypes
int add(int a, int b);
int sub(int a, int b);
int div(int a, int b);
int mul(int a, int b);
void clean_stdin(void);

int main() {
    int choice = 0;
    int a = 0;
    int b = 0;
    int value = 0;
    char rerun = 0;

    printf("Simple Calculator\n");
    while (rerun == 0)
    {
        printf("Please choose:\n1: add\n2: subtract\n3: divide\n4: multiply\n");

        scanf("%d", &choice);
        // INSTRUCTOR-ADD: clean_stdin();

        // Route user selection
        switch(choice) {
            case 1:
                printf("Please enter two numbers, separated by a space, that you'd like to add\n");
                scanf("%d %d", &a, &b);
                // INSTRUCTOR-ADD: clean_stdin();
                value = add(a, b);
                break;
            case 2:
                printf("Please enter two numbers, separated by a space, that you'd like to subtract\n");
                scanf("%d %d", &a, &b);
                // INSTRUCTOR-ADD: clean_stdin();
                value = sub(a, b);
                break;
            case 3:
                printf("Please enter two numbers, separated by a space, that you'd like to divide\n");
                scanf("%d %d", &a, &b);
                // INSTRUCTOR-ADD: clean_stdin();
                value = div(a, b);
                break;
            case 4:
                printf("Please enter two numbers, separated by a space, that you'd like to multiply\n");
                scanf("%d %d", &a, &b);
                // INSTRUCTOR-ADD: clean_stdin();
                value = mul(a, b);
                break;
            default:
                printf("INVALID INPUT: ex (5 5)");
        }

        // Print out the returned value
        printf("Value: %d\n", value);

        // Check if user wants to run the calc again
        printf("Run again (y/n)?\n");
        scanf("%d", &rerun); // INSTRUCTOR-REMOVE
        // INSTRUCTOR-ADD: scanf("%d", &rerun);
        if (rerun == 'y' || rerun == 'Y') {
            rerun = 0;
        }
    }


    return 0;
}


// !!Calc Functions!!

// Addition
int add(int a, int b)
{
    return a + b;
}

// Subtraction
int sub(int a, int b)
{
    return a - b;
}

// Division
int div(int a, int b)
{
    return a / b;
}

// Multiplication
int mul(int a, int b)
{
    return a * b;
}

// Function used to clean input stream
void clean_stdin(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}


// Bugs Below




// Bug 1: Need clean_stdin() after all scanf()'s to clear the input stream
// But 2: When capturing re-run, scanf needs %c formatting to capture a char
