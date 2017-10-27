#include<iostream>
#include<cstdlib>
#include<fstream>
#include<string>
#include<algorithm>
using namespace std;

int array[4][100];
int* best_selected;
int* selected_items;
int total_profit;

class Item{
	public:
	int weight;
	int profit;
	int selection;
	int number;
};

float knapsack_fraction(int weight, int profit, int index)
{
	int n = array[0][0];
	int cap = array[3][0];
	float kwf_bound = profit;

	float temp[n+1];
	for(int i = index; i <= n; i++)
	{
   		temp[i] = 0;
	}

	//check if more items can be added

	while (weight < cap && index <= n)
	{
		if(weight + array[1][index] <= cap)
		{
         		temp[index]=1;
         		weight = weight + array[1][index];
			kwf_bound = kwf_bound + array[2][index];
		}
		else
		{
			temp[index]= ((float)cap - (float)weight)/ (float)array[1][index];
	        	weight = cap;
			kwf_bound = kwf_bound + array[2][index]*temp[index];
		}
		index++;
	}
	return kwf_bound;
}


void backtrack(int profit, int weight, int index)
{
	int n = array[0][0];
	int cap = array[3][0];

	if((weight <= cap) && (profit > total_profit))
	{
		total_profit = profit;
		for(int i = 0; i<n; i++)
		{
			best_selected[i] = selected_items[i];
		}
	}

	//Check if it is a promising node

	if(weight < cap)
	{
		int kwf_bound = knapsack_fraction(weight, profit, index);
		if(kwf_bound > total_profit)
		{
			selected_items[index + 1] = 1;
			backtrack(profit + array[2][index+1], weight + array[1][index+1], index+1);
			selected_items[index + 1] = 0;
			backtrack(profit, weight, index+1);
		}
	}
}

void dynamic_knapsack()
{
	int total_weight = 0, temp1=0;
	int n = array[0][0];
	best_selected = new int[n];
	selected_items = new int[n];
	float density[n], temp2=0;

	for(int i=0; i<n; i++)
	{
		selected_items[i] = 0;
	}

	for(int i=0; i<n; i++)
	{
		density[i] = array[2][i] / array[1][i];
	}

	for(int i=0; i<n-1; i++)
	{
		for(int j=i+1; j<n; j++)
		{
			if(density[j] > density[i])
			{
				temp2 = density[i];
				density[i] = density[j];
				density[j] = temp2;
			}
			if(density[j] > density[i])
			{
				temp1 = array[1][i];
				array[1][i] = array[1][j];
				array[1][j] = temp1;

				temp1 = array[2][i];
				array[2][i] = array[2][j];
				array[2][j] = temp1;
			}
		}
	}

//	sort(density, density + n);

	backtrack(0,0,0);
	cout<<"\n";

	for(int i=0; i<n; i++)
	{
		if(best_selected[i]==1)
		{
			cout<<"Weight: "<<array[1][i]<<"\t\tProfit: "<<array[2][i]<<endl;
			total_weight = total_weight + array[1][i];
		}
	}
	cout << "Total weight: " <<total_weight;
	cout << "\tTotal profit: " <<total_profit<<endl;
}

void file_input(char * argv){

	ifstream infile (argv);
	int i=0, j=0, k=0;
	string cNum;
	string first, last;

	if (infile.is_open())
	{
		while (getline(infile, cNum, ','))
		{
			if(cNum.find('\n')!= std::string::npos)
			{
				first = cNum.substr(0, cNum.find('\n'));
				last = cNum.substr(cNum.find('\n')+1, cNum.length());
				array[i][j] = atoi(first.c_str());
				i++;
				j=0;
				array[i][j] = atoi(last.c_str());
				j++;
			}
			else
			{
				array[i][j] = atoi(cNum.c_str());
                                j++;
			}
		}
		infile.close();
	}
	else
	{
		cout << "Error opening file";
	}
}

int main(int argc, char * argv[]){

	file_input(argv[1]);
	dynamic_knapsack();

return 0;
}
