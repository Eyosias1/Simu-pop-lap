#include "Lib.h"



/*-------------------------------------------------------------------------------*/
/* ReturnYearIntoMonth  is a funtion that convertes a year into month            */
/*                                                                               */
/* Imput : year is the value of a year                                           */
/*                                                                               */
/* Output: the output will be the result of a year converted into month          */
/*-------------------------------------------------------------------------------*/
int    ReturnYearIntoMonth(int year)
{
    return year * 12;
}

/*-------------------------------------------------------------------------------*/
/* ReturnMonthIntoYear  is a funtion that convertes a month into year            */
/*                                                                               */
/* Imput : month is the value of a month                                         */
/*                                                                               */
/* Output: the output will be the result of a month converted into year          */
/*-------------------------------------------------------------------------------*/
int    ReturnMonthIntoYear(int month)
{
    return month / 12;
}


/*-------------------------------------------------------------------------------*/
/* cumulate  is a funtion that cumulates all the values of an array and sends    */
/*                             the total result.                                 */
/*                                                                               */
/* Imput : Tab is an array and size is it's size.                                */
/*                                                                               */
/* Output: the output will be the result of the formula.                         */
/*-------------------------------------------------------------------------------*/
double      cumulate(double * Tab, int size)
{
    double  cum = 0;
    for(int i = 0; i < size; i++)
    {
        cum += Tab[i];
    }
    return cum;
}


/*-------------------------------------------------------------------------------*/
/* doProb  is a function that calculates the probalities based on the            */
/*                             observation made.                                 */
/*                                                                               */
/* Imput : arr is the array of the observation of each class                     */
/*                          and size is it's size.                               */
/* Output: the output will the probablities.                                     */
/*-------------------------------------------------------------------------------*/
double  *   doProb(double * arr, int size)
{
    double      cum     = cumulate(arr, size);
    double  *   ObsProp = calloc(size, sizeof(double));

    for(int i = 0; i < size; i++)
    {
        ObsProp[i] = arr[i] / cum; 
    }

    return ObsProp;
}

/*-------------------------------------------------------------------------------*/
/* CumDensFunc  is the cumulative distribution function                          */
/*                                                                               */
/*                                                                               */
/* Imput : Obs is the array of the observation made, Proba is the array          */
/*          of the probabilities of the obervation and size is it's size.        */
/* Output: the output will the array of The CDF.                                 */
/*-------------------------------------------------------------------------------*/
double  *   CumDensFunc(double * Obs, int size, double * Proba)
{
    double      cum     = cumulate(Obs, size);
    double  *   CumProp = calloc(size, sizeof(double));
    double      tmp = 0;

    for(int i = 0; i < size; i++)
    {
        tmp += Proba[i];
        CumProp[i] = tmp;
    }

    return CumProp;
}

/*-------------------------------------------------------------------------------*/
/* FindCDF     is a generic function finds a discrete distribution               */
/*                                 based on the observation                      */
/* Imput: obs is the array of an obervation and size it's size                   */
/* Output: returns the an array of CDF                                           */
/*-------------------------------------------------------------------------------*/
double *        FindCDF(int size, double * obs)
{
    double  *   Obsprob = doProb(obs, size);
    double  *   CDF     = CumDensFunc(obs, size, Obsprob);
    
    return CDF;
}


/*-------------------------------------------------------------------------------*/
/* confiInter2   is a function that computes the confidence interval of an array */
/*                    of experience passed arround the mean                      */
/*                                                                               */
/* Imput :  exp is the number of times we replicate this experiments. Exp is the */ 
/*              array where we compute the confidence interval mean is the       */
/*                                     is the average                            */
/* Output: void                                                                  */
/*-------------------------------------------------------------------------------*/
void    confiInter2(int exp, double * Exp, double mean, char * str, FILE * fd)
{
    double      vari    = 0;                             // varience
            // we chose a confidence level of 99% and the T score of 99 is found using the table form 1 to 101
                            //   1          2       3       4       5       6           7       8       9       10          11
    double      TTscore[101]  = {1.886,   1.638,  1.533,    1.476,  1.44,     1.415,  1.397,   1.383, 1.372,  1.363,      1.356, 
                                1.35,     1.345,  1.341,    1.337,  1.333,      1.33, 1.328,    1.325, 1.323, 1.321,    1.319, 
                                1.318,      1.316, 1.315,   1.314,  1.313,      1.311, 1.31,    1.309, 1.309, 1.308,    1.307,
                                1.306,      1.306, 1.305,   1.304,  1.304,      1.303, 1.303,   1.302, 1.302, 1.301,    1.301,
                                1.3,        1.3,    1.299,  1.299, 1.299,       1.298, 1.298,   1.298, 1.297, 1.297,    1.297, 
                                1.297,      1.296,  1.296,  1.296, 1.296,       1.295, 1.295,   1.295, 1.295, 1.295,    1.294,
                                1.294,      1.294,  1.294,  1.294, 1.293,       1.293, 1.293,   1.293, 1.293, 1.293,    1.292, 
                                1.292,      1.292,  1.292,  1.292, 1.292,       1.292, 1.292,   1.291, 1.291, 1.291,    1.291, 
                                1.291,      1.291,  1.291,  1.291, 1.291,       1.291, 1.29,    1.29,  1.29,  1.29,     1.66 , 2.576};

    double      EBM;      // is the error bound but also refered as the margin error or the confidence radius
    double      Confimin; // the min interval
    double      Confimax; // the max interval
    double      Tscore;

    mean /= exp;
    for (int i = 0; i < exp; i++)
    {
        vari += pow(Exp[i] - mean, 2); 
    }

    vari        /= exp - 1; 
    Tscore      = (exp > 100) ? TTscore[100]: TTscore[exp - 2]; // why minus 2 because tn-1 and since the array starts with 0 we do -2

    EBM         = Tscore * sqrt(vari / exp);                   // confidence radius or Error bound mean
    Confimin    = mean - EBM;
    Confimax    = mean + EBM;
    fprintf(fd, "the Confidence Interval is [%.8lf, %.8lf] for the %s\nwhith a 99%% and mean %.5lf\n", Confimin, Confimax, str,mean);
}



/*-------------------------------------------------------------------------------*/
/* ComputeConfiInter   is a function that calls the function to compute          */ 
/*                 the confidence interval of  arrays which contain values of    */
/*                                    a certain information                      */
/*                                                                               */
/* Imput :  exp is the number of times we replicate this experiments.            */
/*          initialRabNum is the initial rabbit we start of with                 */
/*                      year is the number of years we want to simulate to       */
/* Output: void                                                                  */
/*-------------------------------------------------------------------------------*/
void    ComputeConfiInter(int exp, int initialRabNum, int Years)
{
    FILE * fd = fopen("tp4.txt", "a");
    double  *   Exp      = malloc(exp * sizeof(double));
    double  *   Exp2     = calloc(exp, sizeof(double));
    double  *   Exp3     = calloc(exp, sizeof(double));
    double  *   Exp4     = calloc(exp, sizeof(double));
    double  *   Exp5     = calloc(exp, sizeof(double));
    double  *   Exp6     = calloc(exp, sizeof(double));
    double  *   Exp7     = calloc(exp, sizeof(double));
    double  *   Exp8     = calloc(exp, sizeof(double));
    double  *   Exp9     = calloc(exp, sizeof(double));
    double      mean     = 0;
    double      mean2    = 0;
    double      mean3    = 0;
    double      mean4    = 0;
    double      mean5    = 0;
    double      mean6    = 0;
    double      mean7    = 0;
    double      mean8    = 0;
    double      mean9    = 0;
    Rab_t_Oth_info * info = NULL;
    for (int i = 0; i < exp; i++)
    {
        info = StartRabbitSimu(initialRabNum, Years);
        Exp[i] = info->totRabbitgenerated;
        Exp2[i] = info->totBabiesGen;
        Exp3[i] = info->totNumbRabAlive;
        Exp4[i] = info->numberFemalesAlive;
        Exp5[i] = info->numberMalesAlive;
        Exp6[i] = info->totdeath;
        Exp7[i] = info->totdeathAt_Child_birthFem_Matu;
        Exp8[i] = info->totdeathBeforeMat;
        Exp9[i] = info->totdeathAfMat;
        mean += Exp[i];
        mean2 += Exp2[i];
        mean3 += Exp3[i];
        mean4 += Exp4[i];
        mean5 += Exp5[i];
        mean6 += Exp6[i];
        mean7 += Exp7[i];
        mean8 += Exp8[i];
        mean9 += Exp9[i];
        Free_The_SpaceInfo(info);
    }
    printf("#################### Question 2 of lab 4 ##########################\n");
    printf("For the results for %d years repeated over %d experience, you can have them in the file tp4.txt.\n", Years, exp);
    fprintf(fd, "##############################################\n");
    fprintf(fd, "These are the values for %d years repeated over %d experience\n", Years, exp);
    confiInter2(exp, Exp, mean, "Number of Rabbits Generated", fd);
    confiInter2(exp, Exp2, mean2, "Number of Baby rabbit generated", fd);
    confiInter2(exp, Exp3, mean3, "Number of Rabbit Alive", fd);
    confiInter2(exp, Exp4, mean4, "Number of Rabbit Female Alive", fd);
    confiInter2(exp, Exp5, mean5, "Number of Rabbits Male Alive", fd);
    confiInter2(exp, Exp6, mean6, "Number of Rabbits dead", fd);
    confiInter2(exp, Exp7, mean7, "Number of Female Rabbit dead After giving birth", fd);
    confiInter2(exp, Exp8, mean8, "Number of Rabbits dead before Maturity", fd);
    confiInter2(exp, Exp9, mean9, "Number of Rabbits dead after Maturity", fd);
    free(Exp);
    free(Exp2);
    free(Exp3);
    free(Exp4);
    free(Exp5);
    free(Exp6);
    free(Exp7);
    free(Exp8);
    free(Exp9);
    fclose(fd);
}