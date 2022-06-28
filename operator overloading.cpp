#include<iostream>
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
};

class MyString
{
    //You can add your code here
private:
    char* str;
    int length;    //not including the null char here
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
    char* Concatenate(char* string1, char* string2)
    {
        int count = 0;
        int length1 = helper::arrSize(string1);
        int length2 = helper::arrSize(string2);

        char* concatenate = new char[length1 + length2 + 1];
        for (int i = 0; i < length1; i++)
        {
            concatenate[count] = string1[i];
            count++;
        }
        for (int i = 0; i < length2; i++)
        {
            concatenate[count] = string2[i];
            count++;
        }
        concatenate[count] = '\0';
        return concatenate;
    }
    int CompareString(char* str1, char* str2)
    {
        int check1 = 0, check2 = 0;
        int size1 = helper::arrSize(str1);
        int size2 = helper::arrSize(str2);

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
        return false;
    }
public:

    //-------------DO_NOT_CHANGE REGION starts below---------------------
    //Do not change the prototypes given below
    MyString operator+(const MyString);
    MyString& operator=(const MyString&);
    bool operator<(MyString);    //Comparison on the basis of ascii values
    //-------------End of DO_NOT_CHANGE REGION---------------------
    MyString();
    friend ostream& operator<<(ostream& out, MyString& string);
    friend istream& operator>>(istream& in, MyString& string);
    bool operator!();
    char& operator[](int);
    char* operator()(int, int);
    ~MyString();
    MyString(const MyString& rhs);
    //Add your class members here    
};

ostream& operator<<(ostream& out, MyString& string)
{
    if (string.str != 0)
        out << string.str;
    else
        out << '\0';
    return out;
}

istream& operator>>(istream& in, MyString& string)
{
    char* temp = new char[80];
    in.getline(temp, 80);
    string.length = helper::arrSize(temp);
    string.str = new char[helper::arrSize(temp) + 1];
    string.str = MyString::getStringFromBuffer(temp);
    return in;
}

MyString::MyString(const MyString& rhs)
{
    length = rhs.length;
    str = new char[helper::arrSize(rhs.str) + 1];
    str = getStringFromBuffer(rhs.str);
}

MyString::MyString()
{
    str = new char[1];
    str[0] = '\0';
    length = 0;
}

bool MyString::operator!()
{
    if (str[0] == '\0' && length == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

MyString MyString::operator+(const MyString string2)
{
    MyString add;
    add.length = helper::arrSize(str) + helper::arrSize(string2.str);
    add.str = Concatenate(str, string2.str);
    return add;
}

MyString& MyString::operator=(const MyString& rhs)
{
    length = rhs.length;
    char* temp = new char[80];
    temp = getStringFromBuffer(rhs.str);
    str = new char[helper::arrSize(rhs.str) + 1];
    str = getStringFromBuffer(temp);
    delete[] temp;
    return *this;
}

bool MyString::operator<(MyString string2)
{
    if (MyString::CompareString(str, string2.str) == -1)
        return true;
    else
        return false;
}

char& MyString::operator[](int index) 
{
    if(index<length)
        return str[index];
    else
        throw exception("Index larger than size");
}

char* MyString::operator()(int index, int size)
{
    if (index - 1 > size)
        throw exception("index greater than size");
    else
    {
        char* temp = new char[size + 1];
        for (int i = index; i < size + index; i++)
        {
            temp[i-index] = str[i];
        }
        temp[size] = '\0';
        return temp;
    }
}

MyString::~MyString()
{
    if(str[0]!='\0')
        delete[] str;
}

//-------------DO_NOT_CHANGE REGION starts below---------------------
void main()
{
    MyString str1, str2, str3, str4;    //Default constructor will make a string of lenght 0 but having null character (only) i.e. empty string
    
    if(!str1)
    {
        cout<<"String 1 is Empty.\n";
        cout<<"Str 1 = "<<str1<<endl<<endl<<endl;
    }
    
    cout << "Enter String 1:\t";
    cin >> str1;


    cout << "Enter String 2:\t";
    cin >> str2;
        

    cout << "\n\n\nUser Entered:\n";
    cout << "String 1 = " << str1 << endl;
    cout << "String 2 = " << str2 << endl<<endl<<endl;

    //What is following code testing?
    cout<<"Before str1 = str1; str1 = "<<str1<<endl;
    str1 = str1;
    cout<<"After str1 = str1, str1 = "<<str1<<endl<<endl<<endl;


    cout<<"Before str4 = str3 = str1+str2\n";
    cout<<"str1 = "<<str1<<endl;
    cout<<"str2 = "<<str2<<endl;
    cout<<"str3 = "<<str3<<endl;
    cout<<"str4 = "<<str4<<endl;

    str4 = str3 = str1+str2;


    cout<<"\n\n\nAfter str4 = str3 = str1+str2\n";
    cout<<"str1 = "<<str1<<endl;
    cout<<"str2 = "<<str2<<endl;
    cout<<"str3 = "<<str3<<endl;
    cout<<"str4 = "<<str4<<endl;

    cout<<"\n\n\nEnter String 3:\t";
    cin >> str3;

    cout<<"\n\n\nEnter String 4:\t";
    cin >> str4;

    
    cout<<"\n\n\nstr3 = "<<str3<<endl;
    cout<<"str4 = "<<str4<<endl;

    if(str3 < str4)
        cout<<"String 3 is Less than String 4.\n";
    else
        cout<<"String 3 is NOT Less than String 4.\n";

    MyString str5 = str1 + str2;
    cout << "\n\n\nStr5:\t" << str5 << endl;
    cout << "Str5[7]:\t" << str5[7] << endl; //Function Call: str5.operator[](7).
    str5[7] = '$';

    cout << "\n\nStr5:\t" << str5 << endl;

   cout << "\n\n\nstr5(5, 10):\t" << str5(5, 10) << endl;// Substring of lenght 10 starting from index 5 . Function Call str5.operator()(5,10) Let the returned MyString or char* leak
    
}
//-------------End of DO_NOT_CHANGE REGION---------------------
