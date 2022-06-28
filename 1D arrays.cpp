#include<iostream>
#include<fstream>
using namespace std;



void main()
{
    cout << "----------------------------------------Bubble Sort Result-----------------------------------------\n";
    int size1 = 0;
    int size2 = 0;
    int size3 = 0;
    int* temp1 = &size1;
    int* temp2 = &size2;
    int* temp3 = &size3;
    int number = 0;
        
    ifstream fin("Data1.txt");  

        fin >> size1;
        if (size1 > 0)
        {
            int* array1 = new int[size1];

            cout << "Test case 1: " << endl;
            cout << "Array before Sorting: ";

            for (int i = 0; i < *temp1; i++)
            {
                fin >> *(array1 + i);
            }

            for (int i = 0; i < *temp1; i++)
            {
                cout << *(array1 + i)<<" ";
            }
            cout << endl;

            for (int step = 0; step < *temp1 - 1; step++) {

                for (int i = 0; i < *temp1 - step - 1; i++) {

                    if (*(array1 + i) > *(array1 + i + 1)) {

                        int temp = *(array1 + i);
                        *(array1 + i) = *(array1 + i + 1);
                        *(array1 + i + 1) = temp;
                    }
                }
            }
            cout << "Sorted Array:\n";

            for (int i = 0; i < *temp1; i++)
            {
                cout << *(array1 + i) << " ";
            }
            cout << endl<<endl;
            delete[] array1;
        }
        else
            cout << "Error:            Array Size should be greater than zero.\n";

        fin >> size2;
        if (size2 > 0)
        {
            int* array2 = new int[size2];

            cout << "Test case 2: " << endl;
            cout << "Array before Sorting: ";

            for (int i = 0; i < *temp2; i++)
            {
                fin >> *(array2 + i);
            }

            for (int i = 0; i < *temp2; i++)
            {
                cout << *(array2 + i) << " ";
            }
            cout << endl;

            for (int step = 0; step < *temp2 - 1; step++) {

                for (int i = 0; i < *temp2 - step - 1; i++) {

                    if (*(array2 + i) > *(array2 + i + 1)) {

                        int temp = *(array2 + i);
                        *(array2 + i) = *(array2 + i + 1);
                        *(array2 + i + 1) = temp;
                    }
                }
            }
            cout << "Sorted Array:\n";

            for (int i = 0; i < *temp2; i++)
            {
                cout << *(array2 + i) << " ";
            }
            cout << endl<<endl;
            delete[] array2;
        }
        else
            cout << "Error:            Array Size should be greater than zero.\n";

        fin >> size3;
        if (size3 > 0)
        {
            int* array3 = new int[size3];

            cout << "Test case 3: " << endl;
            cout << "Array before Sorting: ";

            for (int i = 0; i < *temp3; i++)
            {
                fin >> *(array3 + i);
            }

            for (int i = 0; i < *temp1; i++)
            {
                cout << *(array3 + i) << " ";
            }
            cout << endl;

            for (int step = 0; step < *temp3 - 1; step++) {

                for (int i = 0; i < *temp3 - step - 1; i++) {

                    if (*(array3 + i) > *(array3 + i + 1)) {

                        int temp = *(array3 + i);
                        *(array3 + i) = *(array3 + i + 1);
                        *(array3 + i + 1) = temp;
                    }
                }
            }
            cout << "Sorted Array:\n";
            for (int i = 0; i < *temp3; i++)
            {
                cout << *(array3 + i) << " ";
            }
            cout << endl<<endl;
            delete[] array3;
        }
        else
            cout << "Error:            Array Size should be greater than zero.\n";

        fin.close();
        cout << "----------------------------------------Merge Arrays Result-----------------------------------------\n";

        ifstream fin2("Data2.txt");

        int size1a = 0, size1b = 0, size2a = 0, size2b = 0, size3a = 0, size3b = 0;
        int* temp1a = &size1a;
        int* temp1b = &size1b;
        int* temp2a = &size2a;
        int* temp2b = &size2b;
        int* temp3a = &size3a;
        int* temp3b = &size3b;
        fin2 >> size1a;
        int* array1a = new int[size1a];

        cout << "Test case 1: " << endl;
        for (int i = 0; i < *temp1a; i++)
        {
            fin2 >> *(array1a + i);
        }
        for (int i = 0; i < *temp1a; i++)
        {
            cout << *(array1a + i) << " ";
        }
        cout << endl;
        fin2 >> size1b;
        int* array1b = new int[size1b];

        for (int i = 0; i < *temp1b; i++)
        {
            fin2 >> *(array1b + i);
        }
        for (int i = 0; i < *temp1b; i++)
        {
            cout << *(array1b + i) << " ";
        }
        cout << endl;
        int sizeofmerged1 = size1a + size1b;
        int* merged1 = new int[sizeofmerged1];
        for (int i = 0; i < *temp1a + *temp1b; i++)
        {
            if (*(array1a) > *(array1b))
                *(merged1 + i) = *(array1b++);
            else
                *(merged1 + i) = *(array1a++);
        }
        cout << "Merged Array: ";
        for (int i = 0; i < *temp1a+*temp1b; i++)
        {
            cout << *(merged1 + i) << " ";
        }
        cout << endl;

        fin2 >> size2a;
        int* array2a = new int[size2a];

        cout << "Test case 2: " << endl;
        for (int i = 0; i < *temp2a; i++)
        {
            fin2 >> *(array2a + i);
        }
        for (int i = 0; i < *temp2a; i++)
        {
            cout << *(array2a + i) << " ";
        }
        cout << endl;
        fin2 >> size2b;
        int* array2b = new int[size2b];

        for (int i = 0; i < *temp2b; i++)
        {
            fin2 >> *(array2b + i);
        }
        for (int i = 0; i < *temp2b; i++)
        {
            cout << *(array2b + i) << " ";
        }
        cout << endl;
        int sizeofmerged2 = size2a + size2b;
        int* merged2 = new int[sizeofmerged2];
        for (int i = 0; i < *temp2a + *temp2b; i++)
        {
            if (*(array2a) > *(array2b))
                *(merged2 + i) = *(array2b++);
            else
                *(merged2 + i) = *(array2a++);
        }
        cout << "Merged Array: ";
        for (int i = 0; i < *temp2a + *temp2b; i++)
        {
            cout << *(merged2 + i) << " ";
        }
        cout << endl;

        fin2 >> size3a;
        int* array3a = new int[size3a];

        cout << "Test case 3: " << endl;
        for (int i = 0; i < *temp3a; i++)
        {
            fin2 >> *(array3a + i);
        }
        for (int i = 0; i < *temp3a; i++)
        {
            cout << *(array3a + i) << " ";
        }
        cout << endl;
        fin2 >> size3b;
        int* array3b = new int[size3b];

        for (int i = 0; i < *temp3b; i++)
        {
            fin2 >> *(array3b + i);
        }
        for (int i = 0; i < *temp3b; i++)
        {
            cout << *(array3b + i) << " ";
        }
        cout << endl;
        int sizeofmerged3 = size3a + size3b;
        int* merged3 = new int[sizeofmerged3];
        for (int i = 0; i < *temp3a + *temp3b; i++)
        {
            if (*(array3a) > *(array3b))
                *(merged3 + i) = *(array3b++);
            else
                *(merged3 + i) = *(array3a++);
        }
        cout << "Merged Array: ";
        for (int i = 0; i < *temp3a + *temp3b; i++)
        {
            cout << *(merged3 + i) << " ";
        }
        cout << endl;
        //delete[] array1a;
        //delete[] array1b;
        //delete[] array2a;
        //delete[] array2b;
        //delete[] array3a;
        //delete[] array3b;

}
