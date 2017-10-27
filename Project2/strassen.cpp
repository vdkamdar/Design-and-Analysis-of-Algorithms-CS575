#include<iostream>
#include<fstream>
#include<cstdlib>
#include<iomanip>
#include<string>
#include<cmath>
#include<ctime>
#include<climits>

using namespace std;

float ** M1, **M2, **RESULT;
int size_n, original_size=0;
void display(float **);
void compose(int);
void setValues(float **, char);
void standardMultiplication(float **, float **, float **, int);
void strassensMultiplication(float **, float **, float **, int);
float ** sMulRecursive(float **, float **, int);
float ** computation(char, float **, float **, int);
void insertSubmatrix(char, float **, float **, int, int, int);

void display(float ** MAT){						//displays the matrix

	if(original_size == 0){						//if input size is power of 2
		cout<<"\n";
		for(int i=0; i<size_n; i++){
			for(int j=0; j<size_n; j++){
				cout.setf(ios::fixed);
				cout.setf(ios::showpoint);
				cout.precision(2);
				cout<<MAT[i][j]<<"\t";
			}
			cout<<"\n\n";
		}
		cout<<"\n";
	}
	else{								//if input size is not power of 2
                cout<<"\n";
                for(int i=0; i<original_size; i++){
                        for(int j=0; j<original_size; j++){
                                cout.setf(ios::fixed);
                                cout.setf(ios::showpoint);
                                cout.precision(2);
                                cout<<MAT[i][j]<<"\t";
                        }
                        cout<<"\n\n";
                }
                cout<<"\n";
	}
	return;
}

float ** computation(char flag, float ** M1, float ** M2, int size){	//compute(add or subtract) the values

	float ** RES;
	 RES = new float*[size];
                for(int i=0; i<size; i++){
                        RES[i] = new float[size];
                }

	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++){
			if(flag=='+'){
				RES[i][j] = M1[i][j] + M2[i][j];
			}
			else if(flag=='-'){
				RES[i][j] = M1[i][j] - M2[i][j];
			}
		}
	}
	return RES;
}

void insertSubmatrix(char flag, float ** MAT, float ** ORIGINAL, int rs, int cs, int size){	//insert values into new matrix when matrix is divided or combined

	int col_j=cs, row, col;
	for(row=0; row<size; row++, rs++){
		for(col=0, cs=col_j; col<size; col++, cs++){
			if(flag=='i'){
				MAT[row][col] = ORIGINAL[rs][cs];
			}
			else if(flag=='c'){
				MAT[rs][cs] = ORIGINAL[row][col];
			}
		}
	}
	return;
}

void standardMultiplication(float ** M1, float ** M2, float ** RESULT, int size){	//standard multiplication

	float sum;
	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++){
			sum = 0;
			for(int k=0; k<size; k++){
				sum = sum+M1[i][k]*M2[k][j];
			}
			RESULT[i][j] = sum;
		}
	}
        cout<<"\nInput matrix A:\n ";
        display(M2);
        cout<<"\nInput matrix B:\n ";
        display(M1);
        cout<<"\nResult matrix by Standard multiplication:\n ";
	display(RESULT);
	return;
}


void strassensMultiplication(float ** M1, float ** M2, float ** RESULT, int n){		//wrapper for strassens multiplication

	RESULT = sMulRecursive(M1, M2, n);
        cout<<"\nResult matrix by Strassens multiplication:\n ";
	display(RESULT);
	return;
}

float ** sMulRecursive(float ** M1, float ** M2, int size){				//recursive function for strassens multiplication

	float ** A11,** A12,** A21,** A22,** B11,** B12,** B21,** B22;
	float ** P1,** P2,** P3,** P4,** P5,** P6,** P7;
	float ** C11,** C12,** C21,** C22;
	float ** RES;

	if(size == 1){
		RES = new float*[size];
		for(int i=0; i<size; i++){
			RES[i] = new float[size];
		}
		RES[0][0] = M1[0][0] * M2[0][0];
		return RES;
	}

	else{
		RES = new float*[size];
		for(int i=0; i<size; i++){
			RES[i] = new float[size];
		}
		size = size/2;
		A11 = new float*[size];							//form submatrices of size/2 using dynamic memory allocation
                A12 = new float*[size];
                A21 = new float*[size];
                A22 = new float*[size];
                B11 = new float*[size];
                B12 = new float*[size];
                B21 = new float*[size];
                B22 = new float*[size];
                P1 = new float*[size];
                P2 = new float*[size];
                P3 = new float*[size];
                P4 = new float*[size];
                P5 = new float*[size];
                P6 = new float*[size];
                P7 = new float*[size];
                C11 = new float*[size];
                C12 = new float*[size];
                C21 = new float*[size];
                C22 = new float*[size];

		for(int i=0; i<size; i++){
	                A11[i] = new float[size];
	                A12[i] = new float[size];
        	        A21[i] = new float[size];
	                A22[i] = new float[size];
	                B11[i] = new float[size];
	                B12[i] = new float[size];
	                B21[i] = new float[size];
        	        B22[i] = new float[size];
                	P1[i] = new float[size];
	                P2[i] = new float[size];
        	        P3[i] = new float[size];
                	P4[i] = new float[size];
	                P5[i] = new float[size];
	                P6[i] = new float[size];
	                P7[i] = new float[size];
	                C11[i] = new float[size];
	                C12[i] = new float[size];
	                C21[i] = new float[size];
	                C22[i] = new float[size];
		}

		insertSubmatrix('i', A11, M1, 0, 0, size);						//insert values into submatrices after dividing
                insertSubmatrix('i', A12, M1, 0, size, size);
                insertSubmatrix('i', A21, M1, size, 0, size);
                insertSubmatrix('i', A22, M1, size, size, size);
		insertSubmatrix('i', B11, M2, 0, 0, size);
                insertSubmatrix('i', B12, M2, 0, size, size);
                insertSubmatrix('i', B21, M2, size, 0, size);
                insertSubmatrix('i', B22, M2, size, size, size);

		P1 = sMulRecursive(computation('+',A11,A22,size), computation('+',B11,B22,size), size);	//strassens formulae
		P2 = sMulRecursive(computation('+',A21,A22,size), B11, size);
		P3 = sMulRecursive(A11, computation('-',B12,B22,size), size);
		P4 = sMulRecursive(A22, computation('-',B21,B11,size), size);
		P5 = sMulRecursive(computation('+',A11,A12,size), B22, size);
		P6 = sMulRecursive(computation('-',A21,A11,size), computation('+',B11,B12,size), size);
		P7 = sMulRecursive(computation('-',A12,A22,size), computation('+',B21,B22,size), size);

		C11 = computation('-',computation('+',computation('+',P1,P4,size), P7, size), P5, size);
		C12 = computation('+',P3, P5, size);
		C21 = computation('+',P2, P4, size);
		C22 = computation('-',computation('+',computation('+',P1,P3,size), P6,size), P2, size);

                 insertSubmatrix('c', RES, C11, 0, 0, size);						//combine submatrices into result matrix
                 insertSubmatrix('c', RES, C12, 0, size, size);
                 insertSubmatrix('c', RES, C21, size, 0, size);
                 insertSubmatrix('c', RES, C22, size, size, size);

		return RES;
	}
}

void setValues(float ** MAT, char flag){				//initialize the matrix accordingly with 0 or random values

	if(flag == 'i'){						//initialize to zero
		for (int i = 0; i < size_n; i++){
	        	for (int j = 0; j < size_n; j++){
				MAT[i][j] = 0;
			}
		}
	}
	else if(flag == 'r'){						//if power of 2 - initialize entire matrix using random numbers
                for (int i = 0; i < size_n; i++){
                        for (int j = 0; j < size_n; j++){
                              MAT[i][j] = ((5-(-5))*((float)rand()/RAND_MAX))+(-5);
                        }
                }
	}
	else if(flag == 'n'){						//if not  power of 2 - initilaize original matrix using random numbers and other with 0's
		for(int i=0; i<original_size; i++){
			for(int j=0; j<original_size; j++){
				MAT[i][j] = ((5-(-5))*((float)rand()/RAND_MAX))+(-5);
			}
		}
                for(int i=0; i<original_size; i++){
                                for(int j=original_size; j<size_n; j++){
                                        MAT[i][j] = 0;
                        }
                }
                for(int i=original_size; i<size_n; i++){
                                for(int j=0; j<size_n; j++){
                                        MAT[i][j] = 0;
                        }
                }
	}
	return;
}

void compose(int n){						//allocate dynamic memory for matrix

	M1 = new float*[n];
	for(int i=0; i<n; i++){
		M1[i] = new float[n];
	}

        M2 = new float*[n];
        for(int i=0; i<n; i++){
                M2[i] = new float[n];
        }

        RESULT = new float*[n];
        for(int i=0; i<n; i++){
                RESULT[i] = new float[n];
        }
        setValues(M1,'r');
        setValues(M2,'r');
        setValues(RESULT,'i');

	return;
}

int isPowerOfTwo(int n)						//check whether the input size is power of 2
{
	return (!(n & (n - 1)));
}

int main(int argc, char * argv[]){

	srand(time(NULL));
	size_n = atoi(argv[1]);
	int check_value = isPowerOfTwo(size_n);

	if(size_n>0){
		if(check_value != 0){					//is a power of 2
			compose(size_n);
			standardMultiplication(M1, M2, RESULT, size_n);
                        strassensMultiplication(M1, M2, RESULT, size_n);
		}
		else{							//not a power of 2
			int next = pow(2, ceil(log(size_n)/log(2)));
			original_size = size_n;
			size_n = next;
                        compose(size_n);
                        standardMultiplication(M1, M2, RESULT, size_n);
                        strassensMultiplication(M1, M2, RESULT, size_n);
		}
	}
return 0;
}
