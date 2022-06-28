#include <iostream>
#include <fstream>

using namespace std;

int arrSize(char *arr)
{
	for (int i = 0; i < 160; i++)
	{
		if (arr[i] == NULL)
			return i;
	}
	return 0;
}

void StringConcatenate(char* &str1, char* &str2)
{
	int i = 0, j = 0;
	int size1 = arrSize(str1);
	int size2 = arrSize(str2);
	char* temp = new char[size1+size2+1];
	for (i = 0; i < size1; i++)
	{
		temp[i] = str1[i];
	}
	for (; i < size1+size2; i++)
	{
		temp[i] = str2[j];
		j++;
	}
	temp[i] = '\0';
	delete[] str1;
	str1 = new char[size1 + size2+1];
	str1 = temp;
	temp = NULL;
}

char** StringTokens(char *str)
{
	int count = 0;
	int size = arrSize(str);
	int j = 0, s = 0;
	for (int i = 0; i <= size; i++)
		if (str[i] == 32 || str[i] == NULL)
			count++;
	char** str1 = new char* [count];
	count = 0;
	for (int i = 0; i <= size; i++)
	{
		if (str[i] == 32 || str[i] == NULL)
		{
			str1[count] = new char[i - s + 1];
			for (j = 0; j < i - s; j++)
			{
				str1[count][j] = str[s+j];
			}
			s+=j+1;
			str1[count][j] = '\0';
			count++;
		}
	}
	return str1;
}

char** InverseStringTokens(char* str)
{
	int count = 0, total = 0;
	int size = arrSize(str);
	int j = 0, s = 0;
	for (int i = 0; i <= size; i++)
		if (str[i] == 32 || str[i] == NULL)
			count++;
	total = count;
	char** str1 = new char* [count];
	count = 0;
	for (int i = 0; i <= size; i++)
	{
		if (str[i] == 32 || str[i] == NULL)
		{
			str1[total-count-1] = new char[i - s + 1];
			for (j = 0; j < i - s; j++)
			{
				str1[total-count-1][j] = str[s + j];
			}
			s += j + 1;
			str1[total-count-1][j] = '\0';
			count++;
		}
	}
	return str1;
}

char* ReverseSentence(char* str)
{
	int count = 0, total = 0;
	int size = arrSize(str);
	int j = 0, s = 0;
	for (int i = 0; i <= size; i++)
		if (str[i] == 32 || str[i] == NULL)
			count++;
	total = count;
	char** str1 = new char* [count];
	count = 0;
	for (int i = 0; i <= size; i++)
	{
		if (str[i] == 32 || str[i] == NULL)
		{
			str1[total - count - 1] = new char[i - s + 1];
			for (j = 0; j < i - s; j++)
			{
				str1[total - count - 1][j] = str[s + j];
			}
			s += j + 1;
			str1[total - count - 1][j] = '\0';
			count++;
		}
	}

	j = 0, count = 0;
	char* inverse = new char[size+1];
	for (int i = 0; i < size; i++)
	{
		if (str1[count][j] == NULL)
		{
			count++;
			j = 0;
			inverse[i] = ' ';
			continue;
		}
		inverse[i] = str1[count][j];
		j++;
	}
	inverse[size] = '\0';
	for (int i = 0; i < total; i++)
		delete str1[i];
	delete[] str1;
	str1 = 0;
	return inverse;
}

char* storeString(ifstream& fin)
{
	int size = 0;
	char* temp = new char[80];
	fin.getline(temp, 80);
	size = arrSize(temp);
	char* str1 = new char[size + 1];

	for (int i = 0; i < size + 1; i++)
	{
		str1[i] = temp[i];
	}

	delete[] temp;
	temp = NULL;
	return str1;
}

int CompareString(char* str1, char* str2)
{
	int check1 = 0, check2 =0;
	int size1 = arrSize(str1);
	int size2 = arrSize(str2);

	for (int i = 0; i < size1 + size2; i++)
	{
		if (str1[i] > 64 && str1[i] < 91) //checks if the char is in upper case
		{
			check1++;
			str1[i] += 32;
		}
		if (str2[i] > 64 && str2[i] < 91) //checks if the char is in upper case
		{
			check2++;
			str2[i] += 32;
		}
		if (str1[i] < str2[i])
		{
			if (check1 == 1)
				str1[i] -= 32;
			if (check2 == 1)
				str2[i] -= 32;
			return -1;
		}
			
		else if (str1[i] > str2[i])
		{
			if (check1 == 1)
				str1[i] -= 32;
			if (check2 == 1)
				str2[i] -= 32;
			return 1;
		}	
		else
		{
			if (str1[i] == '\0' && str2[i] == '\0')
			{
				if (check1 == 1)
					str1[i] -= 32;
				if (check2 == 1)
					str2[i] -= 32;
				return 0;
			}
			else if (str1[i] == '\0')
			{
				if (check1 == 1)
					str1[i] -= 32;
				if (check2 == 1)
					str2[i] -= 32;
				return -1;
			}
			else if (str2[i] == '\0')
			{
				if (check1 == 1)
					str1[i] -= 32;
				if (check2 == 1)
					str2[i] -= 32;
				return 1;
			}
		}
		if (check1 == 1)
		{
			str1[i] -= 32;
		}
		if (check2 == 1)
		{
			str2[i] -= 32;
		}	
		check1 = 0, check2 = 0;
	}
	return -2;
}

char** storeStudents(ifstream& fin, int& counter)
{
	char* temp = new char[20];
	char** tempstudents = new char* [100];
	while (fin.getline(temp, 20))
	{
		tempstudents[counter] = new char[20];
		for(int i =0;i<20;i++)
			tempstudents[counter][i] = temp[i];
		counter++;
	}
	int k = 0;
	char** students = new char* [counter];
	for (int i = 0; i < counter; i++)
	{
		while (tempstudents[i][k] != NULL)
		{
			k++;
		}
		students[i] = new char[k + 1];
		k = 0;
	}
	k = 0;
	for (int i = 0; i < counter; i++)
	{
		while (tempstudents[i][k] != NULL)
		{

			students[i][k] = tempstudents[i][k];
			k++;
		}
		students[i][k] = '\0';
		k = 0;
	}

	for (int i = 0; i < counter; i++)
		delete[] tempstudents[i];
	delete[] tempstudents;
	tempstudents = NULL;
	return students;
}

void DisplayStringList(char** list, int size)
{
	for(int i =0;i<size;i++)
	{
		cout << list[i] << endl;
	}
}

void bubbleSort(char **arr, int size)
{
	int i, j;
	char* temp = new char[20];
	for (i = 0; i < size -1; i++)
	{
		for (j = 0; j < size - i - 1; j++)
		{
			if (CompareString(arr[j],arr[j + 1])==1)
			{
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j + 1] = temp;
			}
		}
	}
}

int main()
{
	int i = 0, size1 = 0, count = 0, studentlist = 0;
	ifstream fin;
	fin.open("Data.txt");
	char* str1 = storeString(fin);
	char* str2 = storeString(fin);
	cout << "Testing String Concatinate: \n\n";
	cout << "String 1: " << str1 << endl << "String 2: " << str2 << endl;
	StringConcatenate(str1, str2);
	cout << "\n\nAfter Concatination: \n";
	cout << endl << "String 1: " << str1 << endl << "String 2: " << str2 << endl << endl;
	cout << "------------------------------------------------------------------------------------------------------------\n";

	size1 = arrSize(str1);
	for (int i = 0; i <= size1; i++)
		if (str1[i] == 32 || str1[i] == NULL)
			count++;

	cout << "\nTesting StringTtokens: \n\nTokens of String 1 are as follows:\n\n";

	char** arr = StringTokens(str1);
	for (int i = 0; i < count; i++)
	{
		cout << arr[i] << endl;
	}
	cout << endl;

	cout << "------------------------------------------------------------------------------------------------------------\n";
	cout << "\nTesting InverseStringTtokens: \n\nTokens of the string in reverse order are as follows:\n\n";

	char** inverse = InverseStringTokens(str1);
	for (int i = 0; i < count; i++)
	{
		cout << inverse[i] << endl;
	}
	cout << "------------------------------------------------------------------------------------------------------------\n\nTesting ReverseSentence: \n\n";
	char* reverse = ReverseSentence(str1);
	cout << reverse << endl << endl;
	
	cout << "------------------------------------------------------------------------------------------------------------\n\nTesting Sorting StudentNames: \n\n";
	char** students = storeStudents(fin, studentlist);
	cout << "Before Sorting: " << endl<<endl;
	DisplayStringList(students, studentlist);

	bubbleSort(students, studentlist);
	cout <<endl<< "After Sorting: " << endl<<endl;
	DisplayStringList(students, studentlist);

	for (int i = 0; i < studentlist; i++)
		delete[] students[i];
	delete[] students;
	students = NULL;
	for (int i = 0; i < count; i++)
	{
		delete[] inverse[i];
		delete[] arr[i];
	}
	delete[] inverse;
	delete[] arr;
	delete[] str1;
	delete[] str2;
	str1 = 0;
	str2 = 0;
	arr = 0;
	inverse = 0;
}