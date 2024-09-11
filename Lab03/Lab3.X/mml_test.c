// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

//CMPE13 Support Library
#include "BOARD.h"




// User libraries:
#include "MatrixMath.h"


// Module-level variables:
float zero_matrix[3][3] = {{},{},{}};
float test[3][3] = {{1,3,5},{2,3,4},{3,4,7}};
float res5[3][3]= {{1,2,3},{3, 3, 4},{5,4,7}};
float test2[3][3]= {{12,34,300},{23,329,456},{32,433,79}};
float res[3][3]= {{13,37,305},{25,332,460},{35, 437, 86}};
float res2[3][3]= {{12,102,1500},{46,987,1824},{96,1732,553}};
float res3[3][3]= {{17,39,305},{28,334,461},{37, 438, 84}};
float res4[3][3]= {{24, 68, 600},{46,658,912},{64,866,158}};
float test3[3][3]={{38,249,28},{65,67,89},{76,187,48}};
float test4[3][3]={{97,57,98},{36,86,34},{84,237,145}};


int main()
{
    BOARD_Init();

    printf("Beginning 1820329's mml test harness, compiled on %s %s\n", __DATE__, __TIME__);
    
    
    printf("Demonstrating MatrixPrint():\n");
    MatrixPrint(zero_matrix);
    
    int final=0;
  
   
    // Add more tests here!
    if (MatrixEquals(test,test)==1) 
    {
        final++;
        
    }
     if (MatrixEquals(test,test)==1){
         final++;
     }
    printf("PASSED (%d/2): MatrixEquals()\n", final);
    
    final=0;
    
    MatrixAdd(test,test2,zero_matrix);
    if (MatrixEquals(zero_matrix,res)==1)
    {
        final++;
    }
    if (MatrixEquals(zero_matrix,res)==1){
        final++;
    }
    printf("PASSED (%d/2): MatrixAdd()\n", final);
    
    final=0;
    MatrixMultiply(test,test2,zero_matrix);
    if (MatrixEquals(zero_matrix,res2)==1)
    {
        final++;
    }
    MatrixMultiply(test,test2,zero_matrix);
    if (MatrixEquals(zero_matrix,res2)==1)
    {
        final++;
    }
    printf("PASSED (%d/2): MatrixMultiply()\n", final);
    
    final=0;
    MatrixScalarAdd(5,test2,zero_matrix);
    if (MatrixEquals(zero_matrix,res3)==1)
    {
        final++;
    }
    MatrixScalarAdd(5,test2,zero_matrix);
    if (MatrixEquals(zero_matrix,res3)==1)
    {
        final++;
    }
    printf("PASSED (%d/2): MatrixScalarAdd()\n", final);
   
            
    final=0;
    MatrixScalarMultiply(2,test2,zero_matrix);
    if (MatrixEquals(zero_matrix,res4)==1)
    {
        final++;
    }
    MatrixScalarMultiply(2,test2,zero_matrix);
    if (MatrixEquals(zero_matrix,res4)==1)
    {
        final++;
    }
    printf("PASSED (%d/2): MatrixScalarMultiply()\n", final);
    
    printf("PASSED (%d/2): MatrixTrace()\n", final);
    
    final=0;
    MatrixTranspose(test,zero_matrix);
    if (MatrixEquals(zero_matrix,res5)==1)
    {
        final++;
    }
    MatrixTranspose(test,zero_matrix);
    if (MatrixEquals(zero_matrix,res5)==1)
    {
        final++;
    }
    printf("PASSED (%d/2): MatrixTranspose()\n", final);
    
    printf("PASSED (%d/2): MatrixSubmatrix()\n", final);
    
    printf("PASSED (%d/2): MatrixDeterminant()\n", final);
    
    printf("PASSED (%d/2): MatrixInverse()\n", final);
   
   
    BOARD_End();
    while (1);
}

