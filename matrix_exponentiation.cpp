struct Matrix_exponentiation
{	
	int siz;
	int m_phi=0;
	vector<vector<int>> matrix;


	Matrix_exponentiation(int si,vector<vector<int>> matr): siz(si),matrix(matr){};

	void multiply(vector<vector<int>> &a, vector<vector<int>> &b) 
	{ 		 
		int mul[siz][siz]; 
		for (int i = 0; i < siz; i++) 
		{ 
			for (int j = 0; j < siz; j++) 
			{ 
				mul[i][j] = 0; 
				for (int k = 0; k < siz; k++) 
				{
					mul[i][j] += (a[i][k]*b[k][j]+m_phi)%MOD;
					mul[i][j]%=MOD;
				} 
			} 
		} 

		// storing the multiplication resul in a[][] 
		for (int i=0; i<siz; i++) 
			for (int j=0; j<siz; j++) 
				a[i][j] = mul[i][j]; // Updating our matrix 
	} 
	// Function to compute F raise to power n. 
	void power(vector<vector<int>> &F, int n) 
	{ 
		vector<vector<int>> Ma=matrix;
		if (n==1) 
			return; 

		power(F, n/2); 

		multiply(F, F); 

		if (n%2 != 0) 
			multiply(F, Ma); 
	} 
	vector<vector<int>> findNthTerm(int n)
	{
		vector<vector<int>> F=matrix;
		power(F,n);
		return F;
	}	
};
