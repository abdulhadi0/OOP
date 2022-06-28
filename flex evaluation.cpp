#include <iostream>
#include <fstream>
using namespace std;


class helper
{
public:
	static int arrSize(char* arr)
	{
		for (int i = 0; i < 160; i++)
		{
			if (arr[i] == NULL)
				return i;
		}
		return 0;
	}
	static char* getStringFromBuffer(char* temp)
	{
		int length = helper::arrSize(temp);
		char* arr = new char[length + 1];
		for (int i = 0; i < length; i++)
		{
			arr[i] = temp[i];
		}
		arr[length] = '\0';
		return arr;
	}
};

class flex
{
	static int totalQuizzes;
	static int totalAssignments;
	static int* assignmentTotals;
	static int* quizTotals;

	char rollNo[9];
	char * fname, * lname;
	int* quiz, *assignments;
	int total;
public:
	static int totalStudents;
	void getTotals(ifstream&);
	void getStudentData(ifstream&);
	void listView();
	int getTotal();
	void detailView();
	char* getRollNo();
	int* getQuizTotals(int&);
	int* getAssignmentTotals(int&);
	flex(const flex& rhs) 
	{ 
	for (int i = 0; i < 9; i++)
	{
		rollNo[i] = rhs.rollNo[i];
	}
	fname = new char[helper::arrSize(rhs.fname)+1];
	fname = helper::getStringFromBuffer(rhs.fname);
	lname = new char[helper::arrSize(rhs.lname) + 1];
	lname = helper::getStringFromBuffer(rhs.lname);
	quiz = new int[totalQuizzes];
	for (int i = 0; i < totalQuizzes; i++)
	{
		quiz[i] = rhs.quiz[i];
	}
	assignments = new int[totalAssignments];
	for (int i = 0; i < totalAssignments; i++)
	{
		assignments[i] = rhs.assignments[i];
	}
	total = rhs.total;
	}
	flex()
	{
		rollNo[0] = '\0';
		fname = 0;
		lname = 0;
		quiz = 0;
		assignments = 0;
		total = 0;
	}
	void operator=(const flex& rhs)
	{
		for (int i = 0; i < 9; i++)
		{
			rollNo[i] = rhs.rollNo[i];
		}
		fname = new char[helper::arrSize(rhs.fname) + 1];
		fname = helper::getStringFromBuffer(rhs.fname);
		lname = new char[helper::arrSize(rhs.lname) + 1];
		lname = helper::getStringFromBuffer(rhs.lname);
		quiz = new int[totalQuizzes];
		for (int i = 0; i < totalQuizzes; i++)
		{
			quiz[i] = rhs.quiz[i];
		}
		assignments = new int[totalAssignments];
		for (int i = 0; i < totalAssignments; i++)
		{
			assignments[i] = rhs.assignments[i];
		}
		total = rhs.total;
	}
	~flex();
};

int flex::totalQuizzes = 0;
int flex::totalAssignments = 0;
int* flex::assignmentTotals = 0;
int* flex::quizTotals = 0;
int flex::totalStudents = 0;

flex::~flex()
{
	delete[] fname;
	delete[] lname;
	delete[] quiz;
	delete[] assignments;
}

void flex::detailView()
{
	cout << "\nStudent Information:\n";
	cout << "Roll No.\t" << rollNo << endl;
	cout << "Name:\t\t" << fname << " " << lname << endl;
	cout << "Quiz Marks:\n";
	for (int i = 0; i < totalQuizzes; i++)
	{
		cout << "\tQ" << i + 1 << "\t" << quiz[i] << "/" << quizTotals[i] << "\n";
	}
	cout << "Assignment Marks:\n";
	for (int i = 0; i < totalAssignments; i++)
	{
		cout << "\tA" << i + 1 << "\t" << assignments[i] << "/" << assignmentTotals[i] << "\n";
	}
	cout << "Total: \t\t\t" << total << endl;
}

void flex::getTotals(ifstream& fin)
{
	fin >> totalQuizzes;
	fin >> totalAssignments;
	quizTotals = new int[totalQuizzes];
	for (int i = 0; i < totalQuizzes; i++)
	{
		fin >> quizTotals[i];
	}
	assignmentTotals = new int[totalAssignments];
	for (int i = 0; i < totalAssignments; i++)
	{
		fin >> assignmentTotals[i];
	}
}

void flex::getStudentData(ifstream& fin)
{
	char tempfname[20];
	char templname[20];
	total = 0;
	fin >> rollNo;
	quiz = new int[totalQuizzes];
	fin >> tempfname;
	fname = new char[helper::arrSize(tempfname) + 1];
	fname = helper::getStringFromBuffer(tempfname);
	fin >> templname;
	lname = new char[helper::arrSize(templname) + 1];
	lname = helper::getStringFromBuffer(templname);
	for (int i = 0; i < totalQuizzes; i++)
	{
		fin >> quiz[i];
		total += quiz[i];
	}
	assignments = new int[totalAssignments];
	for (int i = 0; i < totalAssignments; i++)
	{
		fin >> assignments[i];
		total += assignments[i];
	}
}

void flex::listView()
{
	cout << rollNo << "\t"<<fname<<" "<<lname<<"\t\t";
	for (int i = 0; i < totalQuizzes; i++)
	{
		cout << quiz[i] << "\t";
	}
	for (int i = 0; i < totalAssignments; i++)
	{
		cout << assignments[i] << "\t";
	}
	cout << total << endl;
}

int flex::getTotal()
{
	return total;
}

char* flex::getRollNo()
{
	return rollNo;
}

int* flex::getQuizTotals(int& totalquiz)
{
	if (totalquiz == 0)
	{
		totalquiz = totalQuizzes;
		return quizTotals;
	}
	else
		return quiz;
}

int* flex::getAssignmentTotals(int& totalAssignment)
{
	if (totalAssignment == 0)
	{
		totalAssignment = totalAssignments;
		return assignmentTotals;
	}
	else
		return assignments;
}

void SortArray(flex* Students)
{
	int i, j;
	for (i = 0; i < flex::totalStudents - 1; i++)
	{
		for (j = 0; j < flex::totalStudents - i - 1; j++)
			if (Students[j].getTotal() > Students[j + 1].getTotal())
			{
				flex temp = Students[j];
				Students[j] = Students[j + 1];
				Students[j + 1] = temp;
			}
	}
}

int findStudent(char* rollnumber, flex* Students)
{
	int k = 0;
	for (int i = 0; i < flex::totalStudents; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (Students[i].getRollNo()[j] == rollnumber[j])
			{
				k++;
			}
		}
		if (k == 9)
			return i;
		else
			k = 0;
	}
	return 0;
}

void PrintStats(flex* Students)
{
	cout << "-----------------------------------------------------Class Statistics-----------------------------------------------\n\n\t\tQ1\tQ2\tQ3\tQ4\tA1\tA2\tA3\tA4\n";
	cout << "Total:\t\t";

	int totalQuiz = 0;
	int totalAssignment = 0;
	Students[0].getAssignmentTotals(totalAssignment);
	Students[0].getQuizTotals(totalQuiz);
	int* maxQuiz = new int[totalQuiz];
	int* minQuiz = new int[totalQuiz];
	int* avgQuiz = new int[totalQuiz];

	int* maxAssignment = new int[totalAssignment];
	int* minAssignment = new int[totalAssignment];
	int* avgAssignment = new int[totalAssignment];

	int* quizTotals = new int[totalQuiz];
	int* assignmentTotals = new int[totalAssignment];
	int* tempQuiz = new int[totalQuiz];
	int* tempAssignments = new int[totalAssignment];

	totalAssignment = 0, totalQuiz = 0;
	quizTotals=Students[0].getAssignmentTotals(totalAssignment);
	assignmentTotals=Students[0].getQuizTotals(totalQuiz);
	for (int i = 0; i < totalAssignment; i++)
	{
		cout << assignmentTotals[i] << "\t";
	}
	for (int i = 0; i < totalQuiz; i++)
	{
		cout << quizTotals[i]<<"\t";
	}
	cout<<endl;


	for (int j = 0; j < totalQuiz; j++)
	{
		minQuiz[j] = quizTotals[j];
		maxQuiz[j] = 0;
		avgQuiz[j] = 0;
	}
	for (int j = 0; j < totalAssignment; j++)
	{
		minAssignment[j] = assignmentTotals[j];
		maxAssignment[j] = 0;
		avgAssignment[j] = 0;
	}


	for (int i = 0; i < flex::totalStudents; i++)
	{
		tempQuiz = Students[i].getQuizTotals(totalQuiz);
		tempAssignments = Students[i].getAssignmentTotals(totalAssignment);

		for (int j = 0; j < totalQuiz; j++)
		{
			if (tempQuiz[j] < minQuiz[j])
				minQuiz[j] = tempQuiz[j];

			if (tempQuiz[j] > maxQuiz[j])
				maxQuiz[j] = tempQuiz[j];

			avgQuiz[j] += tempQuiz[j];
		}
		for (int j = 0; j < totalAssignment; j++)
		{
			if (tempAssignments[j] < minAssignment[j])
				minAssignment[j] = tempAssignments[j];

			if (tempAssignments[j] > maxAssignment[j])
				maxAssignment[j] = tempAssignments[j];

			avgAssignment[j] += tempAssignments[j];
		}
	}
	cout << "Maximum:\t";
	for (int i = 0; i < totalQuiz; i++)
	{
		cout << maxQuiz[i]<<"\t";
	}
	for (int i = 0; i < totalAssignment; i++)
	{
		cout << maxAssignment[i] << "\t";
	}
	cout << endl;
	cout << "Minimum:\t";
	for (int i = 0; i < totalQuiz; i++)
	{
		cout << minQuiz[i] << "\t";
	}

	for (int i = 0; i < totalAssignment; i++)
	{
		cout << minAssignment[i] << "\t";
	}
	cout << endl;
	cout << "Average:\t";
	for (int i = 0; i < totalQuiz; i++)
	{
		cout << avgQuiz[i] / flex::totalStudents << "\t";
	}
	for (int i = 0; i < totalAssignment; i++)
	{
		cout << avgAssignment[i] / flex::totalStudents << "\t";
	}
	cout << endl;

	delete[] minQuiz, delete[] maxQuiz, delete[] avgQuiz;
	delete[] minAssignment, delete[] maxAssignment, delete[] avgAssignment;
	delete[] quizTotals, delete[] assignmentTotals, delete[] tempQuiz, delete[] tempAssignments;
}

int main()
{
	char roll1[9] = "15L-1234";
	char roll2[9] = "15L-4023";
	ifstream fin;
	fin.open("gradesheet.txt");
	if (fin.fail())
	{
		"File not open.\n";
		return 0;
	}
	else
	{
		fin >> flex::totalStudents;
		flex* Students = new flex[flex::totalStudents];
		Students[0].getTotals(fin);
		for (int i = 0; i <flex::totalStudents; i++)
		{
			Students[i].getStudentData(fin);
		}
		cout << "-------------------------------------------------Data Read from File---------------------------------------------\n\nRollNo.\t\tName\t\t\tQ1\tQ2\tQ3\tQ4\tA1\tA2\tA3\t\A4\tTotal\n\n";
		for (int i = 0; i < flex::totalStudents; i++)
		{
			Students[i].listView();
		}
		cout << "\n-------------------------------------------------Sorted Array---------------------------------------------\n\nRollNo.\t\tName\t\t\tQ1\tQ2\tQ3\tQ4\tA1\tA2\tA3\t\A4\tTotal\n\n";
		SortArray(Students);
		for (int i = 0; i < flex::totalStudents; i++)
		{
			Students[i].listView();
		}


		cout << "----------------------------------------------------Student Information--------------------------------------\n";
		cout << "Enter Student Roll No:\t\t";
		//cin >> roll1;
		cout << roll1 << endl;
		if (findStudent(roll1, Students)==0)
			cout << "Student not found.\n";
		else
			Students[findStudent(roll1, Students)].detailView();


		cout << "----------------------------------------------------Student Information--------------------------------------\n";
		cout << "Enter Student Roll No:\t\t";
		//cin >> roll2;
		cout << roll2 << endl;
		if (findStudent(roll2, Students) == 0)
			cout << "Student not found.\n";
		else
			Students[findStudent(roll2, Students)].detailView();
		PrintStats(Students);
	}

}