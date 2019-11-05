#include <iostream>

using namespace std;

// Matrix class declaration
class matrix
{
private:
	int matrixRows;
	int matrixCols;
	double matrixData[100][100];
public:
	matrix(int, int);
	~matrix();
	void addData(double, int, int);
	double getData(int, int);
	int getRows(void);
	int getCols(void);
	void print(void);

};

// Matrix class contructor
matrix::matrix(int rows, int cols)
{
	matrixRows = rows;
	matrixCols = cols;
	matrixData[0][0] = 0;
}

// Matrix class destructor
matrix::~matrix()
{

}

// Matrix class to add data
void matrix::addData(double data, int row, int col)
{
	matrixData[row][col] = data;
}

// Matrix class to get data
double matrix::getData(int row, int col)
{
	return matrixData[row][col];
}

// Matrix class to get row size
int matrix::getRows(void)
{
	return matrixRows;
}

// Matrix class to get column size
int matrix::getCols(void)
{
	return matrixCols;
}

// Matrix class to print it on screen
void matrix::print(void)
{
	for (int i = 0; i < this->getRows(); i++)
	{
		for (int j = 0; j < this->getCols(); j++)
		{
			cout << this->getData(i, j) << "    ";
		}
		cout << endl << endl;
	}
}

// Alps Water data
double alps[17][2] = {{194.5, 20.79},
{194.3, 20.79},
{197.9, 22.4},
{198.4, 22.67},
{199.4, 23.15},
{199.9, 23.35},
{200.9, 23.89},
{201.1, 23.99},
{201.4, 24.02},
{201.3, 24.01},
{203.6, 25.14},
{204.6, 26.57},
{209.5, 28.49},
{208.6, 27.76},
{210.7, 29.04},
{211.9, 29.88},
{212.2, 30.06}};

// Books x Grades data
double books[40][3] = { {0,	9,	45},
{1,	15,	57},
{0,	10,	45},
{2,	16,	51},
{4,	10,	65},
{4,	20,	88},
{1,	11,	44},
{4,	20,	87},
{3,	15,	89},
{0,	15,	59},
{2,	8,	66},
{1,	13,	65},
{4,	18,	56},
{1,	10,	47},
{0,	8,	66},
{1,	10,	41},
{3,	16,	56},
{0,	11,	37},
{1,	19,	45},
{4,	12,	58},
{4,	11,	47},
{0,	19,	64},
{2,	15,	97},
{3,	15,	55},
{1,	20,	51},
{0,	6,	61},
{3,	15,	69},
{3,	19,	79},
{2,	14,	71},
{2,	13,	62},
{3,	17,	87},
{2,	20,	54},
{2,	11,	43},
{3,	20,	92},
{4,	20,	83},
{4,	20,	94},
{3,	9,	60},
{1,	8,	56},
{2,	16,	88},
{0,	10,	62} };

// US Census Dataset data
double census[11][2] = { {1900,	75.9950},
{1910,	91.9720},
{1920,	105.7110},
{1930,	123.2030},
{1940,	131.6690},
{1950,	150.6970},
{1960,	179.3230},
{1970,	203.2120},
{1980,	226.5050},
{1990,	249.6330},
{2000,	281.4220} };

// Matrix transposer
matrix* matTrans(matrix* mat)
{
	matrix* result = new matrix(mat->getCols(), mat->getRows());

	for (int i = 0; i < mat->getRows(); i++)
	{
		for (int j = 0; j < mat->getCols(); j++)
		{
			result->addData(mat->getData(i, j), j, i);
		}
	}
	return result;
}

// Matrix multiplier
matrix* matMult(matrix* matA, matrix* matB)
{
	
	if (matA->getCols() != matB->getRows()) 
	{ 
		cout << "Matrix multiplication incompatibility" << endl; 
	}

	matrix* result = new matrix(matA->getRows(), matB->getCols());
	double total;

	for (int i = 0; i < matA->getRows(); i++)
	{
		for (int j = 0; j < matB->getCols(); j++)
		{
			total = 0;
			for (int a = 0; a < matA->getCols(); a++)
			{
				total += matA->getData(i, a) * matB->getData(a, j);
			}
			result->addData(total, i, j);
		}
	}
	return result;
}

// Matrix minor build
matrix* matMinor(matrix* mat, int row, int col)
{
	matrix* calc = new matrix(mat->getRows()-1, mat->getCols()-1);

	for (int i = 0; i < mat->getRows(); i++)
	{
		for (int j = 0; j < mat->getCols(); j++)
		{
			if (i != row && j != col)
			{
				int a = i;
				int b = j;
				if (i > row)
				{
					a--;
				}
				if (j > col)
				{
					b--;
				}
				calc->addData(mat->getData(i, j), a, b);
			}
		}
	}
	return calc;
}

// Matrix determinant calculator
double matDet(matrix* mat)
{
	double det = 0;

	//for (int i = 0; i < mat->getRows(); i++)
	//{
	//	for (int j = 0; j < mat->getCols(); j++)
	//	{
	//		cout << mat->getData(i, j) << "    ";
	//	}
	//	cout << endl << endl;
	//}

	if (mat->getRows() == 2)
	{
		det = (mat->getData(0, 0) * mat->getData(1, 1)) - (mat->getData(0, 1) * mat->getData(1, 0));
	}
	else
	{
		for (int a = 0; a < mat->getCols(); a++)
		{
			matrix* calc = matMinor(mat, 0, a);

			if (a % 2 == 0)
			{
				det += mat->getData(0, a) * (matDet(calc));
			}
			else
			{
				det -= mat->getData(0, a) * (matDet(calc));
			}
		}
	}
	//cout << "determinant = " << det << endl << endl;
	return det;
}

// Matrix inverter
matrix* matInv(matrix* mat)
{
	double det = matDet(mat);
	matrix* calc = new matrix(mat->getRows(), mat->getCols());

	if (mat->getRows() == 2)
	{
		calc->addData(mat->getData(1, 1) / det, 0, 0);
		calc->addData(-mat->getData(0, 1) / det, 0, 1);
		calc->addData(-mat->getData(1, 0) / det, 1, 0);
		calc->addData(mat->getData(0, 0) / det, 1, 1);
	}
	else
	{
		matrix* cofactors = new matrix(mat->getRows(), mat->getCols());
		matrix* adjugate = new matrix(mat->getRows(), mat->getCols());

		for (int i = 0; i < mat->getRows(); i++)
		{
			for (int j = 0; j < mat->getCols(); j++)
			{
				if (((i % 2 == 0) && (j % 2 == 0)) || ((i % 2 != 0) && (j % 2 != 0)))
				{
					cofactors->addData(matDet(matMinor(mat, i, j)), i, j);
				}
				else
				{
					cofactors->addData(-matDet(matMinor(mat, i, j)), i, j);
				}
			}
		}

		for (int i = 0; i < cofactors->getRows(); i++)
		{
			for (int j = i; j < cofactors->getCols(); j++)
			{
				if (i == j)
				{	
					adjugate->addData(cofactors->getData(i, j), i, j);
				}
				else
				{
					adjugate->addData(cofactors->getData(i, j), j, i);
					adjugate->addData(cofactors->getData(j, i), i, j);
				}
			}
		}

		for (int i = 0; i < adjugate->getRows(); i++)
		{
			for (int j = 0; j < adjugate->getCols(); j++)
			{
				calc->addData(adjugate->getData(i, j)/det, i, j);
			}
		}
	}
	return calc;
}

// Linear regression
matrix* linear(matrix* x, matrix* y)
{
	cout << "Linear:" << endl << endl;
	
	matrix* xt = matTrans(x);
	matrix* xtx = matMult(xt, x);
	matrix* xty = matMult(xt, y);
	matrix* xtx1 = matInv(xtx);
	matrix* beta = matMult(xtx1, xty);

	beta->print();

	return beta;
}

// Quadratic regression
matrix* quad(matrix* x, matrix* y)
{
	cout << "Quadratic:" << endl << endl;

	matrix* x2 = new matrix(x->getRows(), (x->getCols()*2) - 1);

	for (int i = 0; i < x->getRows(); i++)
	{
		x2->addData(1, i, 0);
		for (int j = 1; j < ((x->getCols() * 2) - 1); j++)
		{
			if (j < x->getCols())
			{
				x2->addData(x->getData(i, j), i, j);
			}
			else 
			{
				x2->addData(pow(x->getData(i, j - x->getCols() + 1), 2), i, j);
			}
		}
	}

	matrix* xt = matTrans(x2);
	matrix* xtx = matMult(xt, x2);
	matrix* xty = matMult(xt, y);
	matrix* xtx1 = matInv(xtx);
	matrix* beta = matMult(xtx1, xty);

	beta->print();

	return beta;
}

// Robust regression
matrix* robust(matrix* x, matrix* y, matrix* ref)
{
	cout << "Robust:" << endl << endl;

	matrix* w = new matrix(x->getRows(),1);
	for (int i = 0; i < x->getRows(); i++)
	{
		w->addData(abs(1 / (y->getData(i, 0) - (ref->getData(0, 0) + x->getData(i, 1) * ref->getData(1, 0)))), i, 0);
	}
	//w->print();

	matrix* wx = new matrix(x->getRows(), x->getCols());
	for (int i = 0; i < x->getRows(); i++)
	{
		for (int j = 0; j < x->getCols(); j++)
		{
			wx->addData(x->getData(i, j) * w->getData(i, 0), i, j);
		}
		
	}

	matrix* wy = new matrix(y->getRows(), y->getCols());
	for (int i = 0; i < y->getRows(); i++)
	{
		wy->addData(y->getData(i, 0) * w->getData(i, 0), i, 0);
	}

	matrix* xt = matTrans(x);
	matrix* xtx = matMult(xt, wx);
	matrix* xty = matMult(xt, wy);
	matrix* xtx1 = matInv(xtx);
	matrix* beta = matMult(xtx1, xty);

	beta->print();

	return beta;
}

// Alps Water Calculus
void AlpsCalc(void)
{
	cout << "------------------------  Calculating Alps Water  ------------------------" << endl << endl;
	
	matrix* x = new matrix(17,2);
	for (int i = 0; i < x->getRows(); i++)
	{
		x->addData(1, i, 0);
		x->addData(alps[i][0], i, 1);
	}

	matrix* y = new matrix(17, 1);
	for (int i = 0; i < y->getRows(); i++)
	{
		y->addData(alps[i][1], i, 0);
	}

	matrix* lin = linear(x, y);
	matrix* qua = quad(x, y);
	matrix* rob = robust(x, y, lin);
}

// Books and grades calculus
void BooksCalc(void)
{
	cout << "------------------------  Calculating Books and Grades  ------------------------" << endl << endl;

	matrix* x = new matrix(40, 3);
	for (int i = 0; i < x->getRows(); i++)
	{
		x->addData(1, i, 0);
		x->addData(books[i][0], i, 1);
		x->addData(books[i][1], i, 2);
	}

	matrix* y = new matrix(40, 1);
	for (int i = 0; i < y->getRows(); i++)
	{
		y->addData(books[i][2], i, 0);
	}

	matrix* lin = linear(x, y);
	matrix* qua = quad(x, y);
	matrix* rob = robust(x, y, lin);
}

// US census calculation
void CensusCalc(void)
{
	cout << "------------------------  Calculating US Census  ------------------------" << endl << endl;

	matrix* x = new matrix(11, 2);
	for (int i = 0; i < x->getRows(); i++)
	{
		x->addData(1, i, 0);
		x->addData(census[i][0], i, 1);
	}

	matrix* y = new matrix(11, 1);
	for (int i = 0; i < y->getRows(); i++)
	{
		y->addData(census[i][1], i, 0);
	}

	matrix* lin = linear(x, y);
	matrix* qua = quad(x, y);
	matrix* rob = robust(x, y, lin);
}

// Main loop
int main()
{
	AlpsCalc();

	BooksCalc();

	CensusCalc();
	
	cin.get();
}