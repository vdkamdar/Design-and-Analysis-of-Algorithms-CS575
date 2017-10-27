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

void brute_force(){

	int n = array[0][0];
	int k=0;
	int max_profit = 0, max_weight=0, combinations = 1;
	int total_weight, total_profit;
	int temp=0, s_count=0;
	Item* my_items = new Item[n];
	Item* selected_items;

	for(int i=0; i<n; i++)
	{
		combinations = combinations * 2;
	}

	for(int i=0; i<n; i++)
	{
		my_items[i].weight = array[1][i];
		my_items[i].profit = array[2][i];
		my_items[i].selection = 0;
		my_items[i].number = i+1;
	}

	for(int i=1; i<combinations; i++)
	{
		Item* new_items = new Item[n];
		temp=0;
		total_weight=0;
		total_profit=0;
		k=0;

		for(int j=0; j<n; j++)
		{
			if (((i >> j) & 1) != 1)
			{
				continue;
			}
			total_weight = total_weight + my_items[j].weight;
			total_profit = total_profit + my_items[j].profit;
			temp++;
			new_items[k] = my_items[j];
			k++;
		}

		if(total_weight <= array[3][0])
		{
			if(total_profit >= max_profit)
			{
				max_profit = total_profit;
				selected_items = new Item[temp];
				s_count = 0;
				for(int z = 0; z < temp; z++)
				{
					selected_items[z] = new_items[z];
					selected_items[z].selection = 1;
					s_count++;
				}
				free(new_items);
			}
		}
	}

	for(int i=0; i<s_count; i++)
	{
		if(selected_items[i].selection==1){
			cout <<"Weight: "<<array[1][i]<<"\t\tProfit: "<<array[2][i]<<"\n";
			max_weight = max_weight + selected_items[i].weight;
		}
	}

	cout << "Total weight: " << max_weight;
	cout << "\tTotal profit: " << max_profit <<endl;
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

int main(int argc, char * argv[])
{
	file_input(argv[1]);
	brute_force();

return 0;
}
