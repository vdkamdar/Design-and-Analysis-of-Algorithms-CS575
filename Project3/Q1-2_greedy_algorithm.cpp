#include<iostream>
#include<cstdlib>
#include<fstream>
#include<string>
#include<algorithm>
using namespace std;

int array[4][100];

class Item{
	public:
	int weight;
	int profit;
	int selection;
	int number;
};

void minimum_weight()
{
	int n=array[0][0];
	int min=0;
	int total_profit = 0;
	int total_weight = array[3][0];
	int* weight_items = new int[n];
	int* selected_items = new int[n];

	for(int i=0; i<n; i++)
	{
		selected_items[i]=0;
	}
	for(int i=0; i<n; i++)
	{
		weight_items[i]=array[1][i];
	}

	for(int temp=0; temp<n; temp++)
	{
		min=1;
		for(int i=0; i<n; i++)
		{
			if(weight_items[min]==-77)
			{
				min++;
			}
			else if(weight_items[i] < weight_items[min])
			{
				min=i;
			}
		}

		if(total_weight >= array[1][min] && total_weight!=0)
		{
			selected_items[min] = 1;
			total_weight = total_weight - array[1][min];
			total_profit = total_profit + array[2][min];
		}
		weight_items[min] = -77;
	}

	total_weight = 0;
	total_profit = 0;

	cout<<"\nMinimum Weight greedy algorithm\n";

	for(int i=0; i<n; i++)
	{
		if(selected_items[i]!=0)
		{
				cout<<"Weight: "<<array[1][i]<<"\t\tProfit: "<<array[2][i]<<"\n";
				total_weight = total_weight + array[1][i];
				total_profit = total_profit + array[2][i];
		}
	}
	cout<<"Total weight: "<<total_weight;
	cout<<"\tTotal profit: "<<total_profit<<endl;
}

void maximum_weight()
{
	int n=array[0][0];
	int max=0;
	int total_profit = 0;
	int total_weight = array[3][0];
	int* weight_items = new int[n];
	int* selected_items = new int[n];

	for(int i=0; i<n; i++)
	{
		selected_items[i]=0;
	}
	for(int i=0; i<n; i++)
	{
		weight_items[i]=array[1][i];
	}

	for(int temp=0; temp<n; temp++)
	{
		max=1;
		for(int i=0; i<n; i++)
		{
			if(weight_items[max]==-77)
			{
				max++;
			}
			else if(weight_items[i] > weight_items[max])
			{
				max=i;
			}
		}

		if(total_weight >= array[1][max] && total_weight!=0)
		{
			selected_items[max] = 1;
			total_weight = total_weight - array[1][max];
			total_profit = total_profit + array[2][max];
		}
		weight_items[max] = -77;
	}

	cout<<"\nMaximum weight greedy algorithm\n";

	total_weight = 0;
	total_profit = 0;

	for(int i=0; i<n; i++)
	{
		if(selected_items[i]!=0)
		{
				cout<<"Weight: "<<array[1][i]<<"\t\tProfit: "<<array[2][i]<<endl;
				total_weight = total_weight + array[1][i];
				total_profit = total_profit + array[2][i];
		}
	}
	cout<<"Total weight: "<<total_weight;
	cout<<"\tTotal profit: "<<total_profit<<endl;
}

void maximum_profit()
{
	int n=array[0][0];
	int max=0;
	int total_profit = 0;
	int total_weight = array[3][0];
	int* profit_items = new int[n];
	int* selected_items = new int[n];

	for(int i=0; i<n; i++)
	{
		selected_items[i]=0;
	}
	for(int i=0; i<n; i++)
	{
		profit_items[i]=array[2][i];
	}

	for(int temp=0; temp<n; temp++)
	{
		max=1;
		for(int i=0; i<n; i++)
		{
			if(profit_items[max]==-77)
			{
				max++;
			}
			else if(profit_items[i] > profit_items[max])
			{
				max=i;
			}
		}

		if(total_weight >= array[1][max] && total_weight!=0)
		{
			selected_items[max] = 1;
			total_weight = total_weight - array[1][max];
			total_profit = total_profit + array[2][max];
		}
		profit_items[max] = -77;
	}

	cout<<"\nMaximum profit greedy algorithm\n";

	total_weight = 0;
	total_profit = 0;

	for(int i=0; i<n; i++)
	{
		if(selected_items[i]!=0)
		{
				cout<<"Weight: "<<array[1][i]<<"\t\tProfit: "<<array[2][i]<<endl;
				total_weight = total_weight + array[1][i];
				total_profit = total_profit + array[2][i];
		}
	}
	cout<<"Total weight: "<<total_weight;
	cout<<"\tTotal profit: "<<total_profit<<endl;
}

void maximum_density()
{
	int n=array[0][0];
	int max=0;
	int total_profit = 0;
	int total_weight = array[3][0];
	int* density_items = new int[n];
	int* selected_items = new int[n];

	for(int i=0; i<n; i++)
	{
		selected_items[i]=0;
	}
	for(int i=0; i<n; i++)
	{
		density_items[i]=array[2][i]/array[1][i];
	}

	for(int temp=0; temp<n; temp++)
	{
		max=1;
		for(int i=0; i<n; i++)
		{
			if(density_items[max]==-77)
			{
				max++;
			}
			else if(density_items[max] < density_items[i])
			{
				max=i;
			}
		}

		if(total_weight >= array[1][max] && total_weight!=0)
		{
			selected_items[max] = 1;
			total_weight = total_weight - array[1][max];
			total_profit = total_profit + array[2][max];
		}
		density_items[max] = -77;
	}


	cout<<"\nMaximum density greedy algorithm\n";

	total_weight = 0;
	total_profit = 0;

	for(int i=0; i<n; i++)
	{
		if(selected_items[i]!=0)
		{
				cout<<"Weight: "<<array[1][i]<<"\t\tProfit: "<<array[2][i]<<endl;
				total_weight = total_weight + array[1][i];
				total_profit = total_profit + array[2][i];
		}
	}
	cout<<"Total weight: "<<total_weight;
	cout<<"\tTotal profit: "<<total_profit<<endl;
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
	minimum_weight();
	maximum_weight();
	maximum_profit();
	maximum_density();

return 0;
}
