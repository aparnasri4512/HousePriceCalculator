#include <stdio.h>
#include <stdlib.h>
#include<string.h>

double** allocateMat(int rows, int cols){
     double** mat = (double**)malloc(rows* sizeof(double*));
     for(int i = 0; i < rows; i++){
          mat[i] = (double*)malloc(cols*sizeof(double));
     }
     return mat;
}

// void print_matrix(double** m, int rows, int cols){
//     int i, j;
//     for (i = 0; i < rows; i++) {
//         for (j = 0; j < cols; j++) {
//                 printf("%lf ", m[i][j]);
      
//            }
//           printf("\n");
//     }
//     printf("\n");
// }

void transpose(int rows, int cols, double **mat, double **res){

     //computing transpose
    for(int i = 0; i < rows; i++){
          for(int j = 0; j < cols; j++){
               res[j][i] = mat[i][j];
          }
    }
}


void multiply(int rowsX, int colsX, int rowsY, int colsY, double** dest, double** x, double** y){

     //double add = 0.0;

     for (int i = 0; i < rowsX; i++) { 
        for (int j = 0; j < colsY; j++) { 
            dest[i][j] = 0.0;
            for (int k = 0; k < colsX; k++) { // replace for n
                dest[i][j] += x[i][k] * y[k][j]; 
                
            }
            
            
            //printf("%d ",resultMat[i][j]);
        } 
    }
}

void invert(int rows, double **src, double **dest){

     
     //initializing to identity matrix
     for(int i = 0; i < rows; i++){
          for(int j = 0; j < rows; j++){
               if(i == j){
                    dest[i][j] = 1.0;

               }else{
                    dest[i][j] = 0.0;
               }
          }
     }

     double fact;

     for(int p = 0; p < rows; p++){
          fact = src[p][p];
          for(int j = 0; j < rows; j++){
               src[p][j]= (src[p][j]/fact);
               dest[p][j]=(dest[p][j]/fact);
          }
          
          for(int i = p+1; i < rows; i++){
               fact = src[i][p];
               for(int m = 0; m<rows; m++){
                    src[i][m] = ((src[i][m]) - (src[p][m]*fact));
                    dest[i][m] = ((dest[i][m]) - (dest[p][m]*fact));

               }
          }

     }

     for(int p = rows-1; p >=0; p--){
          for(int i = p-1; i >=0; i--){

               fact = src[i][p];

               for(int m = rows-1; m>=0; m--){
                    src[i][m] = (src[i][m]) - (src[p][m]*fact);
                    dest[i][m] = (dest[i][m]) - (dest[p][m]*fact);

               }
          }
     }

}


void freeMat(double** mat, int num){

     for(int i = 0; i < num; i++){
          free(mat[i]);
     }
     free(mat);
}


//#define CHECK(X) if(X) { printf("Error reading file\n"); exit(EXIT_FAILURE);}

int main(int argc, char **argv){

    FILE *fp = fopen(argv[1], "r");
     int n, k;
     char *train = malloc(10*sizeof(char));
    if(fp == NULL){
          exit(EXIT_FAILURE);
    }
    //int n, k;//k =  number of attributes; n = number of houses
    //char word[265]; // word train
     fscanf(fp, "%s", train);
     fscanf(fp, "%d", &k);
     fscanf(fp, "%d", &n);
     k++;
     //end of reading train
     
     
    
     double **matrixX = allocateMat(n, k);
     

     double **matrixY = allocateMat(n, 1);

          for (int i = 0; i < n; i++) {
               for(int j = 0; j <= k; j++){
                    if(j == 0){
                         matrixX[i][j] = 1.0;
                    }
                    else if(j==k){
                         fscanf(fp, "%lf", &matrixY[i][0]);
                    }
                    else {
                         fscanf(fp, "%lf", &matrixX[i][j]);
                    }

               }
          }
          //print_matrix(matrixX, n, (k+1));
          fclose(fp);
          free(train);

          double **xt = allocateMat(k, n);

          transpose(n, k, matrixX, xt);

          double **xtx = allocateMat((k), (k));

          multiply((k), n, n, (k), xtx, xt, matrixX);

          double **xtxin = allocateMat((k), (k));

          invert((k), xtx, xtxin);

          double **xtxinxt = allocateMat((k), n);

          multiply((k), (k), (k), n, xtxinxt, xtxin, xt);

          double **matrixW = allocateMat((k), 1);
          
          multiply((k), n, n, 1, matrixW, xtxinxt, matrixY);

          //data.txt
          //finding house prices

          //READING IN DATA FILE
          FILE *fp2 = fopen(argv[2], "r");
          int m, k2;
          char *data = malloc(10*sizeof(char));
          if(fp2 == NULL){
               exit(EXIT_FAILURE);
          }

    //int m, k2;//k =  number of attributes; n = number of houses

    //char word2[265]; // word train
          k2++;
          fscanf(fp2, "%s", data);
          fscanf(fp2, "%d", &k2);
          fscanf(fp2, "%d", &m);
          

          double **matrixXn = allocateMat(m, k2);
          for(int i = 0; i < m; i++){
               for(int j = 0; j < (k2); j++){
                    fscanf(fp2, "%lf", &(matrixXn[i][j]));
               }
          }
          fclose(fp2);
          free(data);
          
          //multiply(m, (k+1), (k2+1), 1, matrixYn, matrixXn, matrixW);

          double sum = 0;

          for(int i = 0; i< m; i++){
               sum = matrixW[0][0];
               for(int j = 0; j < (k2); j++){
                    sum+= matrixXn[i][j]*matrixW[j+1][0];
               }
               printf("%0.f\n", sum);
          }

          

          freeMat(matrixX, n);
          freeMat(matrixY, n);
          freeMat(xt, k);
          freeMat(xtx, k);
          freeMat(xtxin, k);
          freeMat(xtxinxt, k);
          freeMat(matrixW, k);
          freeMat(matrixXn, m);
          //freeMat(matrixYn);

          return 0;

    }