#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#define NPROBS 8

#define LEN 15
#define N 5
#define M 5


#define PRINT_RESULT_VECTOR( V, NAME ) {    \
    printf("%2s: ", NAME);                  \
    for (int i=0; i<LEN; i++)               \
        printf("%4d ", V[i]);               \
    printf("\n");                           \
}

#define PRINT_RESULT_MATRIX(MAT, NAME) {    \
    printf("%2s matrix:\n\t", NAME);        \
    for (int i=0; i<N; i++) {               \
        for (int j=0; j<M; j++)             \
            printf("%4d ", MAT[i*M+j]);     \
        printf("\n\t");                     \
    }                                       \
    printf("\n");                           \
}

// -------- uncomment these two lines when solutions are published --------
//#include "../../solutions/lab1_sol.cu"
//#define RESULTS
// ------------------------------------------------------------------------

#ifndef SOLUTION_STACKVEC_1
#define SOLUTION_STACKVEC_1 { }
#endif

#ifndef SOLUTION_HEAPVEC_1
#define SOLUTION_HEAPVEC_1 { }
#endif

#ifndef SOLUTION_HEAPVEC_2
#define SOLUTION_HEAPVEC_2 { }
#endif

#ifndef SOLUTION_STACKVEC_2
#define SOLUTION_STACKVEC_2 { }
#endif

#ifndef SOLUTION_STACKMAT_1
#define SOLUTION_STACKMAT_1 { }
#endif

#ifndef SOLUTION_HEAPMAT_1
#define SOLUTION_HEAPMAT_1 { }
#endif

#ifndef SOLUTION_HEAPMAT_2
#define SOLUTION_HEAPMAT_2 { }
#endif

#ifndef SOLUTION_STACKMAT_2
#define SOLUTION_STACKMAT_2 { }
#endif


void heap_vec_1(int*a1, int*b1, int*c1, int len){
    for(int i = 0; i < len ; ++i){
        *(c1 +i) = *(a1 +i) + *(b1 +i); 
    }
}
int* heap_vec_2(int*a2, int*b2, int len){
    int* c2 = (int*)malloc(sizeof(int) * LEN);
    for(int i = 0; i < len ; ++i){
        *(c2 +i) = *(a2 +i) + *(b2 +i); 
    }
    return c2;
}
void heap_mat_1(int* a1_mat, int* b1_mat, int* c1_mat, int n, int m){
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            *(c1_mat + i + j) = *(a1_mat + i + j) + *(b1_mat + i + j);
        }
    }
}
int* heap_mat_2(int* a3_mat, int* b3_mat, int n, int m){
    int* c3_mat = (int*)malloc(sizeof(int) * M * N);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            *(c3_mat + i + j * m) = *(a3_mat + i + j * m) + *(b3_mat + i + j * m);
        }   
    }
    return c3_mat;
}
int main(void) {
    // ---------- for timing ----------
    float CPU_times[NPROBS];
    for (int i=0; i<NPROBS; i++)
        CPU_times[i] = 0.0;
    struct timeval temp_1, temp_2;
    // --------------------------------

#ifdef RESULTS
    printf("You are now running the \x1B[31mSOLUTION CODE\x1B[37m:\n");
#else
    printf("You are now running \x1B[31mYOUR CODE\x1B[37m:\n");
#endif
    // ---------------------- Stack vectors 1 ----------------------
    /* Generate three stack vectors a, and b of length "LEN" such
     * that for each i in {0, 1, ... LEN-1} a[i] = i, b[i] = 100 * i.
     * Then compute the vector c = a + b.
     */

#ifdef RESULTS
        SOLUTION_STACKVEC_1
        PRINT_RESULT_VECTOR(c, "c")
#else

int a[LEN], b[LEN], c[LEN];                     
    gettimeofday(&temp_1, (struct timezone*)0); 
    for (int i = 0; i < LEN; i++) {                 
        a[i] = i;                               
        b[i] = i * 100;
        c[i] = a[i] + b[i];
    }               
    PRINT_RESULT_VECTOR(c, "c1 STACK VECTOR");                           
    gettimeofday(&temp_2, (struct timezone*)0); 
    CPU_times[0] = ((temp_2.tv_sec-temp_1.tv_sec) + (temp_2.tv_usec - temp_1.tv_usec) / 1000000.0);

#endif
    // ---------------------- Heap vectors 1 -----------------------
    /* Compute the same result as c but in a heap vector c1 allocated
     * in the main but computed in an extern function.
     */
#ifdef RESULTS
    SOLUTION_HEAPVEC_1
    PRINT_RESULT_VECTOR(c1, "c1")
#else
    gettimeofday(&temp_1, (struct timezone*)0);
    int* c1 = (int*)malloc(sizeof(int) * LEN);
    int* a1 = (int*) malloc(sizeof(int) * LEN);
    int* b1 = (int*) malloc(sizeof(int) * LEN);

    
    for(int i = 0; i < LEN; ++i){
        *(a1 + i) = i;
        *(b1 + i) = i * 100;
        //*(c1 + i) = *(a1 + i) + *(b1 + i);
    }
    heap_vec_1(a1, b1, c1, LEN);
    PRINT_RESULT_VECTOR(c1, "c1 HEAP VECTOR");
    gettimeofday(&temp_2, (struct timezone*)0); 
    CPU_times[1] = ((temp_2.tv_sec-temp_1.tv_sec) + (temp_2.tv_usec - temp_1.tv_usec) / 1000000.0);


#endif
    // ---------------------- Heap vectors 2 -----------------------
    /* Compute the same result as c and c1 in a heap vector c2
     * also allocated in the extern function
     */
#ifdef RESULTS
    SOLUTION_HEAPVEC_2
    PRINT_RESULT_VECTOR(c2, "c2")
#else
    gettimeofday(&temp_1, (struct timezone*)0);
    int* a2 = (int*) malloc(sizeof(int) * LEN);
    int* b2 = (int*) malloc(sizeof(int) * LEN);
    for(int i = 0; i < LEN; ++i){
        *(a2 + i) = i;
        *(b2 + i) = i * 100;
        //*(c1 + i) = *(a1 + i) + *(b1 + i);
    }
    int* c2 = heap_vec_2(a2, b2, LEN);
    PRINT_RESULT_VECTOR(c2, "c2 HEAP VECTOR");
    gettimeofday(&temp_2, (struct timezone*)0); 
    CPU_times[2] = ((temp_2.tv_sec-temp_1.tv_sec) + (temp_2.tv_usec - temp_1.tv_usec) / 1000000.0);


#endif
    // ---------------------- Stack vectors 2 ----------------------
    /* Is it possible to compute the c vector as a stack vector of
     * the extern function and then return it to the main?
     */
#ifdef RESULTS
    SOLUTION_STACKVEC_2
#else
        /* |========================================| */
        /* |           Put here your code           | */
        /* |========================================| */


#endif


    /* Do now the same 4 previous exercises but with the three
     * matrices A, B, C of N rows and M columns where:
     *   1) A[i][j] = i + j
     *   2) B[i][j] = (i + j) * 100
     *   3) C = A + B
     *
     * What are the differences when you change from vectors to
     * matrices?
     */
    // --------------------- Stack matrices ----------------------
#ifdef RESULTS
        SOLUTION_STACKMAT_1
        PRINT_RESULT_MATRIX(((int*)C), "C")
#else
    gettimeofday(&temp_1, (struct timezone*)0);
    int a1_mat[N][M], b1_mat[N][M], c1_mat[N][M];
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            a1_mat[i][j] = i + j;
            b1_mat[i][j] = (i + j) * 100;
            c1_mat[i][j] = a1_mat[i][j] + b1_mat[i][j]; 
            
            printf("\t%d\t",c1_mat[i][j]);
        }
        printf("\n");
            
    }
    //PRINT_RESULT_MATRIX(c1_1, "1 : STACK MATRIX "); // not working properly (?)
    gettimeofday(&temp_2, (struct timezone*)0);
    CPU_times[3] = ((temp_2.tv_sec-temp_1.tv_sec)+(temp_2.tv_usec-temp_1.tv_usec)/1000000.0);

#endif
    // --------------------- Heap matrices -----------------------
#ifdef RESULTS
        SOLUTION_HEAPMAT_1
        PRINT_RESULT_MATRIX(C1, "C1")
#else
    gettimeofday(&temp_2, (struct timezone*)0);
    int* a2_mat = (int*)malloc(sizeof(int) * N * M);
    int* b2_mat = (int*)malloc(sizeof(int) * N * M);
    int* c2_mat = (int*)malloc(sizeof(int) * N * M);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            *(a2_mat + i + j * M) = i + j;
            *(b2_mat + i + j * M) = (i + j) * 100;
            *(c2_mat + i + j * M) = *(a2_mat + i + j * M) + *(b2_mat + i + j * M);    
        }   
    }
    heap_mat_1(a2_mat, b2_mat, c2_mat, N, M);
    PRINT_RESULT_MATRIX(c2_mat, "C2 HEAP MATRIX");

    gettimeofday(&temp_2, (struct timezone*)0);
    CPU_times[4] = ((temp_2.tv_sec-temp_1.tv_sec)+(temp_2.tv_usec-temp_1.tv_usec)/1000000.0);



#endif

    // --------------------- Heap matrices -----------------------
#ifdef RESULTS
        SOLUTION_HEAPMAT_2
        PRINT_RESULT_MATRIX(C2, "C2")
#else
    gettimeofday(&temp_2, (struct timezone*)0);
    int* a3_mat = (int*)malloc(sizeof(int) * N * M);
    int* b3_mat = (int*)malloc(sizeof(int) * N * M);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            *(a3_mat + i + j * M) = i + j;
            *(b3_mat + i + j * M) = (i + j) * 100;
        }   
    }

    int* c3_mat = heap_mat_2(a3_mat, b3_mat, N, M);
    PRINT_RESULT_MATRIX(c3_mat, "C3 : HEAP MATRIX");
    gettimeofday(&temp_2, (struct timezone*)0);
    CPU_times[5] = ((temp_2.tv_sec-temp_1.tv_sec)+(temp_2.tv_usec-temp_1.tv_usec)/1000000.0);
#endif

    // --------------------- Stack matrices ----------------------
#ifdef RESULTS
        SOLUTION_STACKMAT_2
#else
        /* |========================================| */
        /* |           Put here your code           | */
        /* |========================================| */


#endif

    for (int i=0; i<NPROBS; i++) {
        printf("Problem %d runs in %9.8f CPU time\n", i, CPU_times[i]);
    }
    printf("\n");

    return(0);
}
