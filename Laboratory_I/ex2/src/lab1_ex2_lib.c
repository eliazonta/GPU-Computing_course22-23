#include "../include/lab1_ex2_lib.h"
#include <math.h>
// Put here the implementation of mu_fn and sigma_fn
dtype mu_fn(dtype* a, int len){
    int sum = 0;
    for (int i = 0; i < len; i++)
    {
        sum += *(a + i);
    }
    return sum/len;
    
}
dtype sigma_fn(dtype* a, int len){
    int sum = 0;
    for (int i = 0; i < len; i++)
    {
        sum += pow(*(a + i) - mu_fn(a, len), 2);
    }   
    return (dtype)sum / len;
}
// -------------------------------------------------
