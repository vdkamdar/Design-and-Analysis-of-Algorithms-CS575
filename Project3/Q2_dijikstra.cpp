#include<iostream>
#include<cstdlib>
#include<fstream>
#include<string>
#include<algorithm>
#define INFINITY 999
using namespace std;

int array[5][5];
int predecessor[5],dist[5];
int visited[5];

void initialize()
{
	int n = 5;
	for(int i=0; i<n; i++)
	{
		visited[i] = 0;
		predecessor[i] = -1;
		dist[i] = INFINITY;
	}
	dist[0]= 0;
}

int unvisited_closest_node()
{
	int n=5;
	int min_dist = INFINITY;
	int unvisited_closest_n;

	for(int i=0; i<n; i++)
	{
		if((dist[i] <= min_dist) && (visited[i]==0))
		{
			unvisited_closest_n = i;
			min_dist = dist[i];
		}
	}
	return unvisited_closest_n;
}

void distance_between_vertex()
{
	int n = 5;
	int min_dist = INFINITY;
	int unvisited_closest_n;

	for(int i=0; i<n; i++)
	{
		unvisited_closest_n = unvisited_closest_node();
		visited[unvisited_closest_n] = 1;
		for(int i=0; i<n; i++)
		{
			if((array[unvisited_closest_n][i]>0) && visited[i]==0)
			{
				if(dist[i] > dist[unvisited_closest_n] + array[unvisited_closest_n][i])
				{
					predecessor[i] = unvisited_closest_n;
					dist[i] = dist[unvisited_closest_n] + array[unvisited_closest_n][i];
				}
			}
		}
	}
}

void display()
{
	int n = 5;
	cout<<"\nVertex\t\tDistance\n";

	for(int i=0 ; i<n; i++)
	{
		cout<<i<<"\t\t"<<dist[i]<<endl;
	}
}

void file_input(char * argv)
{
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
	initialize();
	distance_between_vertex();
	display();
return 0;
}
