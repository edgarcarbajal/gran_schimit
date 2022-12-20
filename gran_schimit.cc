#include <iostream>
#include <cmath>
#include <sstream>
#include <string>
#include <vector>


double innerprod(std::vector<double>& v1, std::vector<double>& v2);
void add_vect(std::vector<double>& v1, std::vector<double>& v2);
void scal_mult_vect(std::vector<double>& v1, double scalar);

void extract_vects(std::string& str_inp, std::vector<std::vector<double>>& v_set);
bool valid_set(std::vector<std::vector<double>>& v_set);
void print_vect(std::vector<double>& vect);

void gran_schmit(std::vector<std::vector<double>>& v_set, std::vector<std::vector<double>>& orth_set);
void gran_schmit_recursive(std::vector<std::vector<double>>& v_set, std::vector<std::vector<double>>& orth_set);

int main()
{
	std::string input;
	std::getline(std::cin, input);

	std::vector<std::vector<double>> vector_set_S;	//original set of vectors in simple Rn
	std::vector<std::vector<double>> vector_set_T;	//orthogonal set of vectors derrived from S

	while(std::cin.good())				//extracts vectors where each vector separated with a newline!
	{
		extract_vects(input, vector_set_S);
		std::getline(std::cin, input);
	}

	
	if(!valid_set(vector_set_S))	//checks that all vectors have same amount of elements
	{
		printf("Invalid set of vectors! Not all vectors in same dim!(R3, R4, R5, etc...)\n");
		exit(EXIT_FAILURE);
	}


	std::cout << "\nSet of vectors S in R" << vector_set_S[0].size() << '\n';		//print vectors before transf.
	for(size_t i = 0; i < vector_set_S.size(); i++)
	{
		std::cout << "Vector #" << (i+1) << ":\n";
		print_vect(vector_set_S[i]);
	}


	gran_schmit(vector_set_S, vector_set_T);	//transf. vectors


	puts("\nOrthogonal set of vectors T transformed from S using Gran-Schmit");	//print new orthgonal vectors
	for(size_t i = 0; i < vector_set_T.size(); i++)
	{
		std::cout << "Vector #" << (i+1) << ":\n";
		print_vect(vector_set_T[i]);
	}



	puts("\nTo obtain orthonormal vectors of T, just multiply the reciprocal of each vector's magnitude to itself!");
	puts("[ie: (1/|Vi|)*Vi = Ui <--- unit vector of Vi]");
	puts("Will still calculate if want a refrence...");


	double magnitude_temp = 0;
	std::vector<std::vector<double>> vector_set_Tnew(vector_set_T.begin(), vector_set_T.end()); // New set for orthonormal

	for(size_t i = 0; i < vector_set_Tnew.size(); i++)
	{
		magnitude_temp = sqrt(innerprod(vector_set_Tnew[i], vector_set_Tnew[i]));	// |v| = sqrt[(v,v)]

		std::cout << "Vector #" << (i+1) << "'s magnitude: " << magnitude_temp << '\n';

		scal_mult_vect(vector_set_Tnew[i], (1/magnitude_temp));	//change vector copies in T* to be orthonormal
	}



	puts("\nOrthonormal set of vectors T* (T_new) transformed from T by multiplying each vector's magnitude reciprocal");	//print new orthonormal vectors
	for(size_t i = 0; i < vector_set_Tnew.size(); i++)
	{
		std::cout << "Vector #" << (i+1) << ":\n";
		print_vect(vector_set_Tnew[i]);
	}

	return 0;
}






double innerprod(std::vector<double>& v1, std::vector<double>& v2)
{
	//Fail safe-- Check vectors are same size
	
	if(v1.size() != v2.size())
	{
		printf("Failed innerprod! - Vectors not of same size\n");
		exit(EXIT_FAILURE);
	}

	double res = 0;
	for(size_t i = 0; i < v1.size(); i++)
	{
		res += v1[i]*v2[i];
	}

	return res;

}



void add_vect(std::vector<double>& v1, std::vector<double>& v2)
{
	//v1 will have the new result!
	for(size_t i = 0; i < v1.size(); i++)
	{
		 v1[i] += v2[i];
	}
}




void scal_mult_vect(std::vector<double>& v1, double scalar)
{
	//v1 will have new result!!
	for(size_t i = 0; i < v1.size(); i++)
	{
		v1[i] *= scalar;
	}
}



void extract_vects(std::string& str_inp, std::vector<std::vector<double>>& v_set)
{
	double temp = 0;
	std::vector<double> temp_vect;
	std::stringstream strstr(str_inp);
	
	strstr >> temp;
	while(strstr.good())
	{
		temp_vect.push_back(temp);
		strstr >> temp;
	}
	temp_vect.push_back(temp);

	v_set.push_back(temp_vect);
}



bool valid_set(std::vector<std::vector<double>>& v_set)
{
	size_t temp = v_set[0].size();

	for(auto elem : v_set)
	{
		if(elem.size() != temp)
			return false;	
	}

	return true;
}



void print_vect(std::vector<double>& vect)
{
	std::cout << '[';
	for(size_t i = 0; i < vect.size() - 1; i++)
	{
		std::cout << vect[i] << ", ";
	}
	std::cout << vect[vect.size()-1] << "]\n";
}





void gran_schmit(std::vector<std::vector<double>>& v_set, std::vector<std::vector<double>>& orth_set)
{
	//default is setting first vector of S as the first vector of T, and converting all other vectors in S to be orthogonal to it

	//v1 is found, now find the rest with a recursive method
	orth_set.push_back(v_set[0]);

	gran_schmit_recursive(v_set, orth_set);
}


void gran_schmit_recursive(std::vector<std::vector<double>>& v_set, std::vector<std::vector<double>>& orth_set)
{
	if(v_set.size() == orth_set.size())
		return;		//Base case- done if we have same number of vectors in S and T


	std::vector<double> new_vect = v_set[orth_set.size()];	//Uj	- j represents vector in S

	for(size_t i = 0; i < orth_set.size(); i++)	// i represents vector in T
	{
		std::vector<double> temp_vect = orth_set[i];

		double ratio_scalar = innerprod(new_vect, temp_vect) / innerprod(temp_vect, temp_vect);	//(Uj, Vi)/(Vi, Vi)
		scal_mult_vect(temp_vect, ratio_scalar); //ratio_scalar * Vi

		//since we subtract these from the new vect, do -1 scalar_mult then do add funct.
		scal_mult_vect(temp_vect, -1);
		add_vect(new_vect, temp_vect);		//both of thse lines: Uj - (rs*Vi)
	}

	//Push back new vector in T!
	orth_set.push_back(new_vect);

	gran_schmit_recursive(v_set, orth_set); //start recursion again
}
