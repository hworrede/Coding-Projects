#include <stdio.h>
#include <math.h>
#include "BOARD.h"
#include "MatrixMath.h"
void MatrixPrint(float mat[3][3]);

void MatrixPrint(float mat[3][3])
{
    int w,p;
    for (p = 0; p < 3; p++) {
        for (w = 0; w < 3; w++ ) {
            if (w==2) {
                printf("%lf\n", mat[p][w]);
            }
            else {
                printf("%lf ", mat[p][w]);
            }

        }
    }
}


int MatrixEquals(float mat1[3][3], float mat2[3][3]);

int MatrixEquals(float mat1[3][3], float mat2[3][3])
{
    int w,p;
    for (p = 0; p < 3; p++) {
        for (w = 0; w < 3; w++ ) {
            if (mat1[p][w]==mat2[p][w]) {
                continue;
            }
            else {
                return 0;
            }   

        }
    }
    return 1;
}


void MatrixAdd(float mat1[3][3], float mat2[3][3], float result[3][3]);
void MatrixAdd(float mat1[3][3], float mat2[3][3], float result[3][3])
{
    int w,p;
    for (p = 0; p < 3; p++) {
        for (w = 0; w < 3; w++ ) {
           result[p][w]=mat1[p][w]+mat2[p][w]; 
        }
    }
    
}

void MatrixMultiply(float mat1[3][3], float mat2[3][3], float result[3][3]);
void MatrixMultiply(float mat1[3][3], float mat2[3][3], float result[3][3])
{
    int w,p;
    for (p = 0; p < 3; p++) {
        for (w = 0; w < 3; w++ ) {
           result[p][w]=mat1[p][w]*mat2[p][w]; 
        }
    }
    
}

void MatrixScalarAdd(float x, float mat[3][3], float result[3][3]);
void MatrixScalarAdd(float x, float mat[3][3], float result[3][3])
{
    int w,p;
    for (p = 0; p < 3; p++) {
        for (w = 0; w < 3; w++ ) {
           result[p][w]=mat[p][w]+x; 
        }
    }
    
}

void MatrixScalarMultiply(float x, float mat[3][3], float result[3][3]);
void MatrixScalarMultiply(float x, float mat[3][3], float result[3][3])
{
    int w,p;
    for (p = 0; p < 3; p++) {
        for (w = 0; w < 3; w++ ) {
           result[p][w]=mat[p][w]*x; 
        }
    }
    
}

float MatrixTrace(float mat[3][3]);
float MatrixTrace(float mat[3][3])
{
    int result,w,p;
    for (p = 0; p < 3; p++) {
        for (w = 0; w < 3; w++ ) {
           if (w==p){
           result=result+mat[p][w];
        }
    }  
}
    return result; 
}


void MatrixTranspose(float mat[3][3], float result[3][3]);
void MatrixTranspose(float mat[3][3], float result[3][3])
{
    int w,p;
    for (p = 0; p < 3; p++) {
        for (w = 0; w < 3; w++ ) {
           result[w][p]=mat[p][w]; 
        }
        
    }
    
}


void MatrixSubmatrix(int i, int j, float mat[3][3], float result[2][2]);
void MatrixSubmatrix(int i, int j, float mat[3][3], float result[2][2])
{
    int w,p;
    int b=0;
    int a=0;
    for (p = 0; p < 3; p++)
    {
        for (w = 0; w < 3; w++ ){
            if (p==i||w==j){
                continue;
            }
                else {
                if (a<2){
                    result[b][a]=mat[w][p];
                    p++;
                }
                else
                {
                    a=0;
                    b++;
                    result[b][a]=mat[w][p];
                    p++;
                           
                }
                     
            }
                 
        }
    }
}

float MatrixDeterminant(float mat[3][3]);
float MatrixDeterminant(float mat[3][3])
{
    float var3=mat[0][2]*(mat[1][0]*mat[2][1]-mat[2][0]*mat[1][1]);
    float var= mat[0][0]*((mat[1][1] * mat[2][2])-(mat[2][1]*mat[1][2]));
    float var2=mat[0][1]*(mat[1][0]*mat[2][2]-mat[2][0]*mat[1][2]);
    float final=var-var2*var3;
    return final;
}




void MatrixInverse(float mat[3][3], float result[3][3]);
void MatrixInverse(float mat[3][3], float result[3][3])
{
    float mat1[3][3]={{},{},{}};
    float mat2[3][3]={{},{},{}};
    float main[2][2]= {{},{}};
    
    for (int p = 0; p < 3; p++){
        for (int w = 0; w < 3; w++){
        MatrixSubmatrix(w,p, mat, main);
        if (((w+p)%2)==0)
        {
            mat2[w][p]=((main[0][0]*main[1][1])-(main[0][1]*main [1][0]));
        }
    }
        float big=1 /MatrixDeterminant(mat);
        MatrixScalarMultiply(big,mat2,result);
        MatrixTranspose(mat1, result);
    }       
}
