#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include<string.h>
#include<math.h>
struct Char_Stack
{
	char* arr;
	int sp;
	int size;

	//Constructor (from C++)
	Char_Stack()
	{
		arr = NULL;
		sp = -1;
		size = 0;
	}
};

struct Int_Stack
{
	int* arr;
	int sp;
	int size;

	//Constructor (from C++)
	Int_Stack()
	{
		arr = NULL;
		sp = -1;
		size = 0;
	}
};

int power(int num, int p)
{
	int ans = 0;
	for (int i = 0; i < p; i++)
	{
		ans = num * num;
	}
	return ans;
}

bool Char_Init_Stack(Char_Stack* s, int sz)
{
	if (s->arr != NULL) //In case previous malloc is called
		free(s->arr);
	s->arr = (char*)malloc(sizeof(char) * sz);
	if (s->arr == NULL)
		return false;
	s->size = sz;
	s->sp = -1;
	return true;
}

int Char_Push(Char_Stack* s, char item)
{
	if (s->arr == NULL)
		return -1;	//Stack not initialized !
	if (s->sp + 1 == s->size)
		return -2;	//Stack overflow !

	s->sp = s->sp + 1;	//or s->sp++;
	s->arr[s->sp] = item;
	return 0;
}

int Char_Pop(Char_Stack* s, char* item)
{
	if (s->arr == NULL)
		return -1;	//Stack not initialized !
	if (s->sp == -1)
		return -2;	//Stack underflow !

	*item = s->arr[s->sp];
	s->sp = s->sp - 1;	//s->sp--;
	return 0;
}

int IsEmpty(Char_Stack* s)
{

	if (s->sp == -1)
		return 0;
	else
		return 1;

}

char Char_Top(Char_Stack* s)
{
	if (s->arr == NULL)
		return -1;	//Stack not initialized !
	if (s->sp == -1)
		return -2;	//Stack underflow !

	return s->arr[s->sp];

}

int Int_Top(Int_Stack* s)
{
	if (s->arr == NULL)
		return -1;	//Stack not initialized !
	if (s->sp == -1)
		return -2;	//Stack underflow !

	return s->arr[s->sp];

}

bool Int_Init_Stack(Int_Stack* s, int sz)
{
	if (s->arr != NULL) //In case previous malloc is called
		free(s->arr);
	s->arr = (int*)malloc(sizeof(int) * sz);
	if (s->arr == NULL)
		return false;
	s->size = sz;
	s->sp = -1;
	return true;
}

int Int_Push(Int_Stack* s, int item)
{
	if (s->arr == NULL)
		return -1;	//Stack not initialized !
	if (s->sp + 1 == s->size)
		return -2;	//Stack overflow !

	s->sp = s->sp + 1;	//or s->sp++;
	s->arr[s->sp] = item;
	return 0;
}

int Int_Pop(Int_Stack* s, int* item)
{
	if (s->arr == NULL)
		return -1;	//Stack not initialized !
	if (s->sp == -1)
		return -2;	//Stack underflow !

	*item = s->arr[s->sp];
	s->sp = s->sp - 1;	//s->sp--;
	return 0;
}

int IsEmpty(Int_Stack* s)
{

	if (s->sp == -1)
		return 0;
	else
		return 1;

}

int Priorty_Check(Char_Stack stack, char item)
{
	if (item == '+')
	{


		if (Char_Top(&stack) == '^' || Char_Top(&stack) == '*' || Char_Top(&stack) == '/' || Char_Top(&stack) == '-' || Char_Top(&stack) == '+')
			return false;



	}
	else if (item == '-')
	{


		if (Char_Top(&stack) == '^' || Char_Top(&stack) == '*' || Char_Top(&stack) == '/' || Char_Top(&stack) == '+' || Char_Top(&stack) == '-')
		{

			return false;

		}



	}


	else if (item == '*')
	{


		if (Char_Top(&stack) == '^' || Char_Top(&stack) == '/' || Char_Top(&stack) == '*')
		{


			return false;

		}
		else
		{
			return true;
		}

	}

	else if (item == '/')
	{



		if (Char_Top(&stack) == '^' || Char_Top(&stack) == '*' || Char_Top(&stack) == '/')
		{

			return false;


		}



	}

	else if (item == '^')
	{


		if (Char_Top(&stack) == '^')
			return false;




	}
	else if (item == '(' || item == '[' || item == '{')
	{
		return true;
	}

	else if (IsEmpty(&stack) == 1)
	{
		return true;
	}



	return true;

}

int Converter(Char_Stack stack, char* Expression, char* Postfix, int stop_value)
{
	char item;
	int counter = 0;
	for (int iterator = 0; iterator < stop_value; iterator++)
	{

		if (Expression[iterator] >= '0' && Expression[iterator] <= '9')
		{
			Postfix[counter] = Expression[iterator];
			counter++;
		}
		else if (Priorty_Check(stack, Expression[iterator]) == false)
		{
			while (Priorty_Check(stack, Expression[iterator]) == false)
			{


				Char_Pop(&stack, &item);


				Postfix[counter] = item;

				counter++;


			}
			Char_Push(&stack, Expression[iterator]);
		}
		else if (Priorty_Check(stack, Expression[iterator]) == true)
		{
			while (Priorty_Check(stack, Expression[iterator]) == true)
			{

				if (Expression[iterator] == '(')
				{
					Char_Push(&stack, Expression[iterator]);
					break;
				}
				else if (Expression[iterator] == ')')
				{
					break;
				}
				else
				{
					Char_Push(&stack, Expression[iterator]);
				}
			}
		}
		if (Expression[iterator] == ')')
		{
			while (Char_Top(&stack) != '(')
			{
				Char_Pop(&stack, &item);
				Postfix[counter] = item;
				counter++;
			}
			Char_Pop(&stack, &item);
		}

	}









	while (IsEmpty(&stack) == 1 && Char_Top(&stack) != '(')
	{

		Char_Pop(&stack, &item);


		Postfix[counter] = item;

		counter++;

	}


	return(counter);
}

bool isdigit(char ch)
{
	if (ch >= '0' && ch <= '9')
		return true;
	return false;
}
int evaluatepostfix(char  postfix[], Int_Stack* st)
{
	float result = 0;
	if (IsEmpty(st))
		return -1;
	for (int i = 0; i < strlen(postfix); i++)   //read elements of postfix 
	{
		if (isdigit(postfix[i]))  //check that the postfix is only a number from 0 to 9
			Int_Push(st, postfix[i] - '0'); //for removing the effect of ASCII
		else
		{
			int num1, num2;
			Int_Pop(st, &num1);
			Int_Pop(st, &num2);

			switch (postfix[i]) //check operator been passed to evaluate
			{
			case '^'://power
				// In case of IntelliSense error or overflow replace below line with this -> result = pow((double)num2,num1);
				result = pow(num2,num1);
				break;
			case '+': //addition
				result = num2 + num1;
				break;
			case '-': //subtraction
				result = num2 - num1;
				break;
			case '*'://multiplication
				result = num2 * num1;
				break;
			case '/': //division
				if (num1 == 0) //do not allow division by zero
				{
					printf("math error");
					return 0;
				}
				else
					result = num2 / num1;
				break;
			default: //else 0
				printf("invalid operater");
			}
			Int_Push(st, result);
		}
	}
	return Int_Top(st);//the st is left with only one element  //store the answer at the top
}
void main(void)
{
	Int_Stack stc;
	Char_Stack stack;
	char* Expression, * Postfix, item, Top_Of_Stack = 0;
	int User_Space, stop_value = 0, iterator = 0, counter = 0;

retry:
	printf("Enter desired space: ");

	while((scanf("%d", &User_Space)) != 1)
	{
		//fflush(stdin);
		printf("pls type an integar ! \n");
		while(getchar()!='\n');

		goto retry;
	}

	Char_Init_Stack(&stack, User_Space);

	Expression = (char*)calloc(sizeof(char), (User_Space + 1)); //Using malloc to allow for dynamic memory

	Postfix = (char*)calloc(sizeof(char), (User_Space + 1));



	if (Expression == NULL)
	{
		printf("Couldnt allocate memory \n");
		goto retry;
	}
back:
	printf("Enter required expression: ");


	scanf("%s", Expression);

	for (int i = 0; i < strlen(Expression); i++)
	{

		if (Expression[i] >= '0' && Expression[i] <= '9' || Expression[i] == '*' || Expression[i] == '-' || Expression[i] == '^' || Expression[i] == '/' || Expression[i] == '+' || Expression[i] == '(' || Expression[i] == ')' || Expression[i] == '[' || Expression[i] == ']' || Expression[i] == '{' || Expression[i] == '}')
		{
		}
		else
		{
			goto back;

		}

	}

	stop_value = strlen(Expression);


	Converter(stack, Expression, Postfix, stop_value);

	Int_Init_Stack(&stc, User_Space);
	//	puts(Postfix);
	int r = evaluatepostfix(Postfix, &stc);
	printf("The final answer is: %d", r);

	free(Expression);
	free(Postfix);
	getch();


}
