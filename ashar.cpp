#include <iostream>
#include <fstream>

using namespace std;

class Node {
	public:
		long EmployeeNumber;
		string name;
		long MobileNumber;
		long landline;

};

class Directory {
	private:
		Node *node[10];
		int data[10];
		int size;


	public:
		Directory();
		Directory(long eNum, string n, long mn, long ll);
		void insert(long eNum, string n, long mn, long ll);
		void insertInFile(long eNum, string n, long mn, long ll);
		void display();
		~Directory();
};

Directory::Directory() : size(10) {
	Node *node = new Node();
	for(int i=0; i< 10; i++) {
		data[i] = 0;
	}
}

Directory::~Directory() {
	//delete node;
}

Directory::Directory(long eNum, string n, long mn, long ll) {
	//node = new Node();

	// node->EmployeeNumber = eNum;
	// node->name = n;
	// node->MobileNumber = mn;
	// node->landline = ll;

}

void Directory::insert(long eNum, string n, long mn, long ll) {
	int i = mn%10;
	if(data[i] == 0) {			// Hashing
		node[i] = new Node();
		node[i]->EmployeeNumber = eNum;
		node[i]->name = n;
		node[i]->MobileNumber = mn;
		node[i]->landline = ll;
		data[i] = 1;
	}
	else {
		for(int j = i; j < size+i; j++) {
			if(data[(j%size)] == 0) {
				node[(j%size)] = new Node();
				node[(j%size)]->EmployeeNumber = eNum;
				node[(j%size)]->name = n;
				node[(j%size)]->MobileNumber = mn;
				node[(j%size)]->landline = ll;
				data[(j%size)] = 1;
				break;
			}
		}
	}
}


void Directory::insertInFile(long eNum, string n, long mn, long ll) {
	ofstream ofile;
	ofile.open("phoneNumber.txt", ios::app);
	if(ofile.is_open()) {
		ofile << endl;
		ofile << eNum;
		ofile << endl;
		ofile << n;
		ofile << endl;
		ofile << mn;
		ofile << endl;
		ofile << ll;
		ofile << endl;


	}
}


void Directory::display() {

	for(int i=0;i<10; i++) {
		cout << node[i]->EmployeeNumber << endl;
		cout << node[i]->name << endl;
		cout << node[i]->MobileNumber << endl;
		cout << node[i]->landline << endl;
		cout << endl << endl;
	}
}





int main() {

	Directory directory;

	fstream ifile;
	long data, mobile, land;
	string name;

	ifile.open("phoneNumber.txt");
	if(ifile.is_open()) {
		for(int i=0; i<10; i++) {
			ifile >> data;
			fflush(stdin);
			ifile >> name;
			fflush(stdin);
			ifile >> mobile;
			fflush(stdin);
			ifile >> land;
			fflush(stdin);

			cout << endl << endl;
			directory.insert(data, name, mobile, land);
		}
	}

	char choice;
	//cin >> choice;
	do {
		int choosen;
		cout << "\n\n\t\t Telephone Directory\n";
		cout << "\n\n";
		cout << "\t 1. Insert a Number";
		cout << "\n\t 2. Display all the numbers";
		cout << "\n\t 3. Display details of a particular person";
		cout << "\n\n\n Select: ";
		cin >> choosen;
		if(choosen == 1) {
			
			cout << "Enter Employee Number: ";
			cin >> data;
			cout << "Enter name: ";
			cin >> name;
			cout << "Enter Mobile Number: ";
			cin >> mobile;
			cout << "Enter Landline: ";
			cin >> land;
			directory.insert(data, name, mobile, land);
			directory.insertInFile(data, name, mobile, land);

		}
		else if(choosen == 2) {
			directory.display();
		}

		cout << "\n\n\nDo you wish to continue: ";
		cin >> choice;
	}while(choice == 'y');


	ifile.close();
}
