#include<iostream>
#include<fstream>
#include<cstring>
#include<ctime>
#include<cstdlib>
#include<climits>

using namespace std;

class contactsBook{

	string first_name[20], last_name[20], phone_num[15];
	public:
		string ** contacts_arr;
		int row, col;
		void create(string file_name);
		void display(string **);
		void sort_contact(string **, int, int);
		int partition(string **, int, int);
		void row_swap(string **, string **);
		void search(string **, char *);
		void delete_contact(char *);
		void insert(char * name);
		void clear_memory();
};


/* create() function takes file as input, creates two-dimensional
dynamic array and stores the contacts and their phone numbers accordingly. */

void contactsBook :: create(string file_name){

	ifstream myfile(file_name.c_str());
	string line, token1, token2, token3;
	int i=0;

	if(myfile.is_open()){
		while(getline(myfile,line)){
			i++;
		}
	}
	myfile.close();

        ifstream myfile1(file_name.c_str());

        row = i, col = 3;
        contacts_arr = new string*[row];

	i = 0;

	if(myfile1.is_open()){
		while(getline (myfile1,line) ){

			if(line[line.size()-1] == '\r')
			{line.erase(line.length()-1);}
			contacts_arr[i] = new string[col];
			token1 = line.substr(0, line.find(" "));
			token2 = line.substr(line.find(" ")+1, line.find(",")-line.find(" ")-1);
			token3 = line.substr(line.find(",")+2, line.length()-line.find(",")-2);
			contacts_arr[i][0] = token1;
			contacts_arr[i][1] = token2;
			contacts_arr[i][2] = token3;
			i++;
		}
	}
	myfile1.close();
}


/* display() function displays the contacts from the contacts book. */

void contactsBook :: display(string ** arr){

	cout<<"\n";
	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++){
			cout <<"\t    "<<arr[i][j];
			if(j==1){
				cout<<",";
			}
		}
		cout << "\n";
	}
	cout<<"\n";
}


/* sort_contact() function sorts the contacts in the order of their Fistname, Lastname and Phonenumber using Randomized Quicksort.
	in function main()- Random number is generated and swapped with the leftmost element to choose a pivot. */

void contactsBook :: sort_contact(string ** arr, int left, int right){

	if(left < right)
	{
		int pi = partition(arr, left, right);

		sort_contact(arr, left, pi-1);
		sort_contact(arr, pi+1, right);
	}
}


/* partition() function Creates a partition: left and right based on the
 pivot for sorting the contacts using Randomized Quicksort  */

int contactsBook :: partition(string ** arr, int l, int r){

	string pivot = arr[l][0];
	int i = r+1;

	for(int j=r; j>=l+1; j--){
		if(arr[j][0].compare(pivot) > 0){
			i--;
			row_swap(&arr[i], &arr[j]);
		}
		else if(arr[j][0].compare(pivot) == 0){
			if(arr[j][1].compare(arr[l][1]) > 0){
				i--;
				row_swap(&arr[i], &arr[j]);
			}
			else if(arr[j][1].compare(arr[l][1]) == 0){
				if(arr[j][2].compare(arr[l][2]) > 0){
					i--;
					row_swap(&arr[i], &arr[j]);
				}
			}
		}
	}
	row_swap(&arr[i-1], &arr[l]);
	return (i-1);
}


/* row_swap() Swaps the rows of the Contacts Book in order to sort them */

void contactsBook :: row_swap(string ** a, string ** b){

	string * temp = *a;
	*a = *b;
	*b = temp;
}


/* search() function Searches the contact in the Contacts Book using Binary Search,
   if not, displays a message on the console. */

void contactsBook :: search(string ** arr, char * name){

	int median, left = 0, right = row - 1, flag = 0;
	string str = name;

	while(left <= right && flag ==0){
		median = (left + right)/2;

		if(str.compare(arr[median][0]+" "+arr[median][1]) < 0){
                        right = median - 1;
		}

		else if(str.compare(arr[median][0]+" "+arr[median][1])>0){
                        left = median + 1;
		}

		else if(str.compare(arr[median][0]+" "+arr[median][1])==0){
			flag = 1;
		}
	}

	if(flag==0){
		cout<<"\n\tContact not found!!\n";
	}

	else{
		cout<<"\n\t"<<str<<", "<<arr[median][2]<<"\n\n";
	}
}


/* delete_contact() function Deletes the contact if found in the Contacts Book,
   if not, then displays a message on the console. */

void contactsBook :: delete_contact(char * name){

//Searches for name and phone number using binary search

	int median, left = 0, right = row - 1, median_pn, left_pn=median-5, right_pn=median + 5, flag = 0, i, j, delete_i, equal=0;
        string full_name = name;

        while(left <= right && flag ==0){
                median = (left + right)/2;

                if(full_name.compare(contacts_arr[median][0]+" "+contacts_arr[median][1]+", "+contacts_arr[median][2]) < 0){
                        right = median - 1;
                }

                else if(full_name.compare(contacts_arr[median][0]+" "+contacts_arr[median][1]+", "+contacts_arr[median][2]) > 0){
                        left = median + 1;
                }

                else if(full_name.compare(contacts_arr[median][0]+" "+contacts_arr[median][1]+", "+contacts_arr[median][2]) == 0){
		        flag = 1;
                }
        }

/* If found deletes the contact by making a deep copy and referencing the old array to the new copy,
   else displays a message on the console
*/

   if(flag == 1){

	row = row - 1;

	string ** delete_arr = new string*[row];

	for(i=0; i<row; i++){
		delete_arr[i] = new string[col];
	}

	for(i=0; i<=median-1; i++){
		for(j=0; j<col; j++){
			delete_arr[i][j] = contacts_arr[i][j];
		}
	}

        for(i=median+1; i<row+1; i++){
                for(j=0; j<col; j++){
			delete_i = i - 1;
                        delete_arr[delete_i][j] = contacts_arr[i][j];
                }
        }

	for(i = 0; i < row+1; i++){
	    delete[] contacts_arr[i];
	}
	delete[] contacts_arr;

	contacts_arr = delete_arr;
	delete_arr = NULL;
	display(contacts_arr);
   }

   else{
	cout<<"\n\t Contact not found!!\n";
   }

}


/* insert() function Inserts contact in the Contacts Book and keeps it sorted. */

void contactsBook :: insert(char * name_phone){

        int i, j;

        row = row + 1;

        string ** insert_arr = new string*[row];

        for(i=0; i<row; i++){
                insert_arr[i] = new string[col];
        }

        for(i=0; i<row-1; i++){
                for(j=0; j<col; j++){
                        insert_arr[i][j] = contacts_arr[i][j];
                }
        }

	string str = name_phone;
	insert_arr[row-1][0] = str.substr(0, str.find(" "));
        insert_arr[row-1][1] = str.substr(str.find(" ")+1, str.find(",")-str.find(" ")-1);
	insert_arr[row-1][2] = str.substr(str.find(",")+2, str.length()-str.find(",")-2);

	for(i = 0; i < row-1; i++){
            delete[] contacts_arr[i];
        }
	delete[] contacts_arr;

	contacts_arr = insert_arr;
	insert_arr = NULL;
	sort_contact(contacts_arr, 0, row-1);
        display(contacts_arr);
}


/* clear_memory() function clears the memory before the program is terminated. */

void contactsBook :: clear_memory(){

	int i;

	for(i = 0; i < row; i++){
            delete[] contacts_arr[i];
        }
	delete[] contacts_arr;
}


/* main() performs the Switch case for: Sort, Search, Delete, Insert and Terminate.
   With respective calls to the functions defined above. */

int main(int argc, char * argv[]){

	string file_name = argv[1];
	bool exit = false;
	int choice, median;
	char name[100];
	char new_name[100];
	char phone_number[15];

	contactsBook records;
	records.create(file_name);
	int rand_num;

	while(!exit){

		cout<<"\n\t 1) Sort_contact";
		cout<<"	\n\t 2) Search";
		cout<<"	\n\t 3) Delete";
		cout<<"	\n\t 4) Insert";
		cout<<" \n\t 5) Terminate";
		cout<<"	\n\t Enter your choice: \t";
		cin>>choice;

		switch(choice){

			case 1:
		        rand_num = rand()%(records.row) + 1;
		        records.row_swap(&(records.contacts_arr[rand_num]), &(records.contacts_arr[0]));
			records.sort_contact(records.contacts_arr, 0, (records.row)-1);
			records.display((records.contacts_arr));
			break;

			case 2:
			cin.ignore();
			cout<<"\n\t Enter the Name: ";
			cin.getline(name, 100);
			records.search(records.contacts_arr, name);
			break;

			case 3:
			cin.ignore();
                        cout<<"\n\t Enter the Name and Phone number: ";
                        cin.getline(new_name, 100);
			records.delete_contact(new_name);
			break;

			case 4:
			cin.ignore();
                        cout<<"\n\t Enter the Name and Phone number: ";
                        cin.getline(name, 100);
			records.insert(name);
			break;

			case 5:
			records.clear_memory();
			exit=true;
			break;
		}

	}
        return 0;
}
