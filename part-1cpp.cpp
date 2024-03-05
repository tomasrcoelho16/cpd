#include <iostream>
#include <iomanip>
#include <sys/time.h>
#include <cstdlib>

using namespace std;

void OnMult(int m_ar, int m_br) 
{
    struct timeval Time1, Time2;
    char st[100];
    double temp;
    int i, j, k;

    double *pha, *phb, *phc;
    pha = (double *)malloc((m_ar * m_ar) * sizeof(double));
    phb = (double *)malloc((m_ar * m_ar) * sizeof(double));
    phc = (double *)malloc((m_ar * m_ar) * sizeof(double));

    for(i=0; i<m_ar; i++)
        for(j=0; j<m_ar; j++)
            pha[i*m_ar + j] = (double)1.0;

    for(i=0; i<m_br; i++)
        for(j=0; j<m_br; j++)
            phb[i*m_br + j] = (double)(i+1);

    gettimeofday(&Time1, NULL);

    for(i=0; i<m_ar; i++)
    {   
        for(j=0; j<m_br; j++)
        {   
            temp = 0;
            for(k=0; k<m_ar; k++)
            {   
                temp += pha[i*m_ar+k] * phb[k*m_br+j];
            }
            phc[i*m_ar + j] = temp;
        }
    }

    gettimeofday(&Time2, NULL);

    sprintf(st, "Time: %3.3f seconds\n", (double)(Time2.tv_sec - Time1.tv_sec) + (double)(Time2.tv_usec - Time1.tv_usec) / 1000000);
    cout << st;

    // display 10 elements of the result matrix to verify correctness
    cout << "Result matrix: " << endl;
    for(i=0; i<1; i++)
    {   
        for(j=0; j<min(10,m_br); j++)
            cout << phc[j] << " ";
    }
    cout << endl;

    free(pha);
    free(phb);
    free(phc);
}

void OnMultLine(int m_ar, int m_br)
{
    struct timeval Time1, Time2;
    char st[100];
    double temp;
    int i, j, k;

    double *pha, *phb, *phc;
    pha = (double *)malloc((m_ar * m_ar) * sizeof(double));
    phb = (double *)malloc((m_ar * m_ar) * sizeof(double));
    phc = (double *)malloc((m_ar * m_ar) * sizeof(double));

    for(i=0; i<m_ar; i++)
        for(j=0; j<m_ar; j++)
            pha[i*m_ar + j] = (double)1.0;

    for(i=0; i<m_br; i++)
        for(j=0; j<m_br; j++)
            phb[i*m_br + j] = (double)(i+1);

    gettimeofday(&Time1, NULL);

    for(i=0; i<m_ar; i++)
    {   
        for(k=0; k<m_ar; k++)
        {   
            for(j=0; j<m_br; j++)
            {   
                phc[i*m_ar+j] += pha[i*m_ar+k] * phb[k*m_br+j];
            }
        }
    }

    gettimeofday(&Time2, NULL);

    sprintf(st, "Time: %3.3f seconds\n", (double)(Time2.tv_sec - Time1.tv_sec) + (double)(Time2.tv_usec - Time1.tv_usec) / 1000000);
    cout << st;

    // display 10 elements of the result matrix to verify correctness
    cout << "Result matrix: " << endl;
    for(i=0; i<1; i++)
    {   
        for(j=0; j<min(10,m_br); j++)
            cout << phc[j] << " ";
    }
    cout << endl;

    free(pha);
    free(phb);
    free(phc);
}

void OnMultBlock(int m_ar, int m_br, int bkSize)
{
    if(bkSize%2 != 0) {
        cout << "Invalid block size!" << endl;
        return;
    }

    struct timeval Time1, Time2;
    char st[100];
    double temp;

    double *pha, *phb, *phc;
    int i; int j; int k; int ii; int jj; int kk;

    pha = (double *)malloc((m_ar * m_ar) * sizeof(double));
    phb = (double *)malloc((m_ar * m_ar) * sizeof(double));
    phc = (double *)malloc((m_ar * m_ar) * sizeof(double));

    for(i=0; i<m_ar; i++)
        for(j=0; j<m_ar; j++)
            pha[i*m_ar + j] = (double)1.0;

    for(i=0; i<m_br; i++)
        for(j=0; j<m_br; j++)
            phb[i*m_br + j] = (double)(i+1);

    gettimeofday(&Time1, NULL);

    for(ii=bkSize; ii<m_ar + bkSize; ii+= bkSize)
    {
        for(jj=bkSize; jj<m_ar + bkSize; jj+= bkSize)
        {
            for(kk=bkSize; kk<m_ar + bkSize; kk+=bkSize)
            {
                for(i= ii - bkSize; i<ii && i < m_ar; i++)
                {   
                    for(j=jj - bkSize; j<jj && j < m_ar; j++)
                    {   
                        temp = 0;
                        for(k=kk - bkSize; k<kk && k < m_ar; k++)
                        {    
                            temp += pha[i*m_ar+k] * phb[k*m_br+j];
                        }
                        phc[i*m_ar + j] += temp;
                    }
                }
            }
        }
    }

    gettimeofday(&Time2, NULL);
    sprintf(st, "Time: %3.3f seconds\n", (double)(Time2.tv_sec - Time1.tv_sec) + (double)(Time2.tv_usec - Time1.tv_usec) / 1000000);
    cout << st;

    // display 10 elements of the result matrix tto verify correctness
    cout << "Result matrix: " << endl;
    for(i=0; i<1; i++)
    {   
        for(j=0; j<min(10,m_br); j++)
            cout << phc[j] << " ";
    }
    cout << endl;

    free(pha);
    free(phb);
    free(phc);
}

int main (int argc, char *argv[])
{
    char c;
    int lin, col, blockSize;
    int op;

    do {
        cout << endl << "1. Multiplication" << endl;
        cout << "2. Line Multiplication" << endl;
        cout << "3. Block Multiplication" << endl;
        cout << "Selection?: ";
        cin >>op;
        if (op == 0)
            break;
        printf("Dimensions: lins=cols ? ");
        cin >> lin;
        col = lin;

        switch (op){
            case 1: 
                OnMult(lin, col);
                break;
            case 2:
                OnMultLine(lin, col);  
                break;
            case 3:
                cout << "Block Size? ";
                cin >> blockSize;
                OnMultBlock(lin, col, blockSize);  
                break;
        }

    }while (op != 0);

    return 0;
}
