// Standard libraries
#include <stdio.h>
#include <math.h>


//User libraries:
#include "BOARD.h"

#ifdef PIC32
// Microchip libraries
#include <xc.h>
#endif


// **** Declare function prototypes ****
double Add(double operand1, double operand2);
double Subtract(double operand1, double operand2);
double Divide(double operand1, double operand2);
double Multiply(double operand1, double operand2);
double Average(double operand1, double operand2);
double AbsoluteValue(double operand);
double FahrenheitToCelsius(double operand);
double CelsiusToFahrenheit(double operand);
double Tangent(double operand);
double Round(double operand);
//add more prototypes here


void CalculatorRun(void)
{
    while(1) {
    printf("\n\nWelcome to Hagos's calculator program! Compiled at %s %s\n",__DATE__, __TIME__);

    // Your code here
    char rate;
    double var=0.0, first=0.0, second=0.0, dig=0.0;
    printf("Enter a mathematical operation to perform (*,/,+,-,f,t,a,c,m): ");
    scanf("%c", &rate);
    while(getchar() != '\n');
    
    if (rate=='*' || rate=='/' || rate=='+' || rate=='-'|| rate=='m')
    {
        printf("Enter the first operator: ");
        scanf("%lf",&first);
        while(getchar() != '\n');
        printf("Enter the second operator: ");
        scanf("%lf",&second);
        while(getchar() != '\n');
        switch(rate) {
            case '*':
                dig = Multiply(first, second);
                printf("Results of (%lf * %lf): %lf", first, second, dig);
                continue;
            case '/':
                dig = Divide(first, second);
                printf("Results of (%lf / %lf): %lf", first, second, dig);
                continue; 
            case '+':
                dig = Add(first, second);
                printf("Results of (%lf + %lf): %lf", first, second, dig);
                continue;
            case '-':
                dig = Subtract(first, second);
                printf("Results of (%lf - %lf): %lf", first, second, dig);
                continue;
            case 'm':
                var=Average(first, second);
                printf("Results of ((%lf+%lf)/2): %lf", first, second, var);
                continue;
                
     
        }
    
    }
    else if (rate=='f' || rate=='t' || rate=='a' || rate=='c' )
    {
        printf("Enter the value: ");
        scanf("%lf", &dig);
        while(getchar() != '\n');
        
        switch(rate) {
            
            case 'f':
                var=CelsiusToFahrenheit(dig);
                printf("Results of (%lf C->F): %lf", dig, var);
                continue; 
            case 't':
                var=Tangent(dig);
                printf("Results of tan(%lf): %lf", dig, var);
                continue;
            case 'a':
                var=AbsoluteValue(dig);
                printf("Results of |%lf|: %lf", dig, var);
                continue;
            case 'c':
                var=FahrenheitToCelsius(dig);
                printf("Results of (%lf F->C): %lf", dig, var);
                continue;
          
        
    } 
    }
    else if (rate=='q')
    {
        printf("Calculator is Quitting.");
        break;
       
    }
       
    
    else
    {
        printf("Please input a valid operator");
    }
    BOARD_End();
    while (1);
}
}


/********************************************************************************
 * Define the Add function here.
 ********************************************************************************/
double Add(double operand1, double operand2)
{
    double simply= operand1 + operand2;
    return simply;
}

/********************************************************************************
 * Define the Subtract function here.
 ********************************************************************************/
double Subtract(double operand1, double operand2)
{
	double simply= operand1 - operand2;
    return simply;
}

/********************************************************************************
 * Define the Multiply function here.
 ********************************************************************************/
double Multiply(double operand1, double operand2)
{
    double simply= operand1 * operand2;
    return simply;
}

/********************************************************************************
 * Define the Divide function here.
 ********************************************************************************/
double Divide(double operand1, double operand2)
{
	double simply= operand1 / operand2;
    return simply;
}

/********************************************************************************
 * Define the Absolute Value function here.
 ********************************************************************************/
double AbsoluteValue(double operand)
{
    double simply = operand;
    if (operand<0)

    {
        simply=(operand*-1);
    
    }  
    return simply;
}

/*********************************************************************************
 * Define the Fahrenheit to Celsius function here.
 ********************************************************************************/
double FahrenheitToCelsius(double operand)
{
    double simply= ((operand-32)*0.5556);
    return simply;
}

/*********************************************************************************
 * Define the Celsius to Fahrenheit function here.
 ********************************************************************************/
double CelsiusToFahrenheit(double operand)
{
    double simply= ((operand*1.8)+32);
    return simply;
}
/********************************************************************************
 * Define the Average function here.
 *******************************************************************************/
double Average(double operand1, double operand2)
{
    double simply= ((operand1+operand2)/2);
    return simply;
}

/*********************************************************************************
 * Define the Tangent function that takes input in degrees.
 ********************************************************************************/
double Tangent(double operand)
{
    double conversion= ((M_PI/180)*operand);
    double simply=tan(conversion);
    return simply;
}

/*********************************************************************************
 * Define the Round function here.
 * In order to receive the extra credit your calculator MUST ALSO CORRECTLY utilize
 * this function.
 ********************************************************************************/
//double Round(double operand)






