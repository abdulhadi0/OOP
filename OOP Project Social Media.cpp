#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class helper;
class user;
class page;
class Facebook;
class object;
class post;
class activity;
class comment;
class Date;

class Date
{
private:
	int date;
	int month;
	int year;
public:
	Date(int d=0,int m= 0,int y =0);
	void loadDateFromFile(ifstream&);
	void Print();
	bool operator==(const Date);
	bool isYesterday();
	int isMemory();
	void operator=(Date&);
};
class helper
{
public:
	static int arrSize(const char* arr)
	{
		for (int i = 0; i < 160; i++)
		{
			if (arr[i] == NULL)
				return i;
		}
		return 0;
	}
	static char* getStringFromBuffer(const char* temp)
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
	static bool compareString(const char* s0, const char* s1)
	{
		if (arrSize(s0) == arrSize(s1))
		{
			for (int i = 0; i < arrSize(s0); ++i)
			{
				if (s0[i] != s1[i])
				{
					return false;
				}
			}
			return true;
		}
		return false;
	}
};
class object
{
protected:
	char* ID;
public:
	virtual ~object()
	{
		delete[] ID;
		ID = 0;
	}
	virtual void addToTimeline(post* ptr){}
	virtual char* getName() { return 0; }
	object() { ID = 0; }
	virtual char* getID() { return 0; }
};
class post
{
private:
	char* ID;
	activity* Activity;
	char* Text;
	Date dateOfPost;
	object* SharedBy;
	object** LikedBy;
	comment** Comments;
	post* memoryPost;
	int totalLikes;
	int totalComments;
public:
	post();
	~post()
	{
		    delete[] ID;
			ID = 0;
			delete[] Text;
			Text = 0;
			SharedBy = 0;
			delete memoryPost;
			delete Activity;
			delete[] Comments;
			delete[] LikedBy;
			memoryPost = 0;
	}
	void readPostFromFile(ifstream&);
	void setSharedBy(object*);
	void setLikedBy(object*);
	void timelineView();
	void homePageView();
	char* GetID();
	void addCommentToPost(comment*);
	void addComment(object*, const char*);
	void LikePost(object*);
	void viewLikedBy();
	void seeMomories();
	int isMemory();
	void addToMemory(const char*);
};
class activity 
{
private:
	int Type;
	char* Value;
public:
	void readActivityFromFile(ifstream&);
	void viewActivity();
	~activity()
	{
		if (Value)
			delete[] Value;
	}
};
class comment
{
private:
	char* ID;
	char* Text;
	object* CommentBy;
public:
	comment();
	~comment()
	{
		delete[] ID;
		ID = 0;
		delete[] Text;
		Text = 0;
		CommentBy = 0;
	}
	void loadCommentID(ifstream&);
	void loadCommentData(ifstream&);
	void SetCommentBy(object*);
	void viewComment();
	void declareComment(object*, const char*);
};
class page : public object
{
	char* pageName;
	post** Timeline;
	int totalPosts;
public:
	page();
	~page();
	void loadPageFromFile(ifstream&);
	char* getID();
	char* getName();
	void setID(const char*);
	void addToTimeline(post*);
	void ViewFriendsTimeline();
	void viewTimeline();
};
class user : public object
{
	char* firstName;
	char* lastName;
	user** friendList;
	page** likedPages;
	post** Timeline;
	int totalLikedPages;
	int totalFriends;
	int totalPosts;
public:
	user();
	~user();
	void loadUserFromFile(ifstream&, char**);
	void likePage(page*); //add a page to likedPages array
	char* getID();
	void setID(const char*);
	void addFriend(user*); // add a friend to friendsList array
	void viewFriendList();
	void declarePageArray();
	void viewLikedPages();
	char* getName();
	void addToTimeline(post*);
	void viewTimeline();
	void viewHomePage();
	void ViewFriendsTimeline();
	void seeYourMemories();
	void shareMemory(post*, const char*);
};
class Facebook
{
	user** Users;
	page** Pages;
	post** Posts;
	comment** Comments;
	static int totalPages;
	static int totalUsers;
	static int totalPosts;
	static int totalComments;
public:
	Facebook();
	~Facebook();
	void loadData(const char*, const  char*, const char*, const char*);
	void loadUsers(const char*);
	void loadPages(const char*);
	void loadPosts(const char*);
	void loadComments(const char*);
	page* searchPageFromID(const char*);
	user* searchUserByID(const char*);
	post* searchPostFromID(const char*);
	void viewLikedList(const char*);
	void run();
	static Date currentDate;
};

int Facebook::totalPages = 0;
int Facebook::totalUsers = 0;
int Facebook::totalPosts = 0;
int Facebook::totalComments = 0;
Date Facebook::currentDate(15,11,2017);

int main()
{
	Facebook fb;
	fb.loadData("Users.txt", "Pages.txt", "Posts.txt", "Comments.txt");
	fb.run();
}

//FACEBOOK CLASS FUNCTIONS

Facebook::Facebook()
{
	Users = 0;
	Pages = 0;
	Comments = 0;
	Posts = 0;
}
Facebook::~Facebook()
{
	for (int i = 0; i < totalUsers; i++)
		delete Users[i];
	delete[] Users;
	for (int i = 0; i < totalPages; i++)
		delete Pages[i];
	delete[] Pages;
	for (int i = 0; i < totalPosts; i++)
		delete Posts[i];
	delete[] Posts;
	for (int i = 0; i < totalComments; i++)
		delete Comments[i];
	delete[] Comments;
}
void Facebook::loadData(const char* usersFile, const char* pagesFile, const char* postsFile, const char* commentsFile)
{
	loadPages(pagesFile);
	loadUsers(usersFile);
	loadPosts(postsFile);
	loadComments(commentsFile);
}
void Facebook::loadUsers(const char* FileName)
{
	ifstream fin;
	fin.open(FileName);
	fin >> totalUsers;
	Users = new user * [totalUsers];
	char*** tempFriendIDs = new char** [totalUsers];
	for (int i = 0; i < totalUsers; i++)
	{
		tempFriendIDs[i] = new char* [10];
		Users[i] = new user;
		Users[i]->loadUserFromFile(fin, tempFriendIDs[i]);
		char* temp = new char[20];
		fin >> temp;
		if (temp[0] != '-')
			Users[i]->declarePageArray();
		while (temp[0] != '-')
		{
			Users[i]->likePage(this->searchPageFromID(temp));
			fin >> temp;
		}
		delete[] temp;
	}
	for (int i = 0; i < totalUsers; i++)
	{
		int j = 0;
		while (tempFriendIDs[i][j][0] != '-')
		{
			Users[i]->addFriend(searchUserByID(tempFriendIDs[i][j]));
			j++;
		}
	}
	for (int i = 0; i < totalUsers; i++)
		for (int j = 0; j < 10; j++)
			delete[] tempFriendIDs[i][j];
	delete[] tempFriendIDs;
}
void Facebook::loadPages(const char* FileName)
{
	ifstream fin;
	fin.open("Pages.txt");
	fin >> totalPages;
	Pages = new page * [totalPages];
	for (int i = 0; i < totalPages; i++)
	{
		Pages[i] = new page;
		Pages[i]->loadPageFromFile(fin);
	}
}
void Facebook::loadPosts(const char* filename)
{
	ifstream fin;
	fin.open(filename);
	fin >> totalPosts;
	Posts = new post * [totalPosts];
	char* temp = new char[20];
	for (int i = 0; i < totalPosts; i++)
	{
		Posts[i] = new post;
		Posts[i]->readPostFromFile(fin);
		fin >> temp;
		object* tempObject = 0;
		if (temp[0] == 'u')
			tempObject = searchUserByID(temp);
		else if (temp[0] == 'p')
			tempObject = searchPageFromID(temp);
		Posts[i]->setSharedBy(tempObject);
		tempObject->addToTimeline(Posts[i]);
		fin >> temp;
		while (temp[0] != '-')
		{
			if (temp[0] == 'u')
				Posts[i]->setLikedBy(searchUserByID(temp));
			else if (temp[0] == 'p')
				Posts[i]->setLikedBy(searchPageFromID(temp));
			fin >> temp;
		}
	}
}
void Facebook::loadComments(const char* filename)
{
	ifstream fin;
	fin.open(filename);
	fin >> totalComments;
	char temp[30];
	Comments = new comment * [totalComments];
	for (int i = 0; i < totalComments; i++)
	{
		Comments[i] = new comment;
		Comments[i]->loadCommentID(fin);
		fin >> temp;
		searchPostFromID(temp)->addCommentToPost(Comments[i]);
		fin >> temp;
		if (temp[0] == 'u')
			Comments[i]->SetCommentBy(searchUserByID(temp));
		else if (temp[0] == 'p')
			Comments[i]->SetCommentBy(searchPageFromID(temp));
		Comments[i]->loadCommentData(fin);
	}
}
page* Facebook::searchPageFromID(const char* pageID)
{
	for (int i = 0; i < totalPages; i++)
	{
		if (helper::compareString(pageID, Pages[i]->getID()))
		{
			return Pages[i];
		}
	}
	return 0;
}
user* Facebook::searchUserByID(const char* userID)
{
	for (int i = 0; i < totalUsers; i++)
	{
		if (helper::compareString(userID, (Users[i]->getID())))
		{
			return Users[i];
		}
	}
	return 0;
}
post* Facebook::searchPostFromID(const char* postID)
{
	for (int i = 0; i < totalPosts; i++)
	{
		if (helper::compareString(postID, Posts[i]->GetID()))
		{
			return Posts[i];
		}
	}
	return 0;
}
void Facebook::viewLikedList(const char* postPtr)
{
	post* temp = searchPostFromID(postPtr);
	if (temp != 0)
	{
		cout << "Post Liked By:\n";
		temp->viewLikedBy();
	}
}
void Facebook::run()
{
	cout << "System Date Set to ";
	currentDate.Print();
	cout << endl;
	const char* tempUserName = "u7";
	user* tempUser = new user;
	//post* tempPost = new post;
	tempUser = searchUserByID(tempUserName);
	cout << "Command:                Set current user: " << tempUserName << endl << endl;

	if (tempUser != 0)
	{
		//OBJECT PRINTING
		cout << tempUser->getName() << " successfully set as Current User\n\n";
		cout << "-----------------------------------------------------------\n";
		cout << "Command:                View Friend List\n-----------------------------------------------------------\n\n";
		tempUser->viewFriendList();
		cout << "-----------------------------------------------------------\n";
		cout << endl;
		cout << "Command:                View Liked Pages\n-----------------------------------------------------------\n\n";
		tempUser->viewLikedPages();
		cout << "-----------------------------------------------------------\n";
		cout << "Command:                View Home Page\n-----------------------------------------------------------\n\n";
		tempUser->viewHomePage();
		cout << "-----------------------------------------------------------\n";
		cout << "Command:                View Timeline\n-----------------------------------------------------------\n\n";
		tempUser->viewTimeline();
		cout << "-----------------------------------------------------------\n";

		//POST PRINTING
		cout << "Command:                ViewLikedPosts(post5)\n-----------------------------------------------------------\n\n";
		viewLikedList("post5");
		cout << "-----------------------------------------------------------\n";
		cout << "Command:                LikePost(post5)\n\n";
		searchPostFromID("post5")->LikePost(tempUser);
		cout << "Command:                ViewLikedPosts(post5)\n-----------------------------------------------------------\n\n";
		viewLikedList("post5");
		cout << "-----------------------------------------------------------\n";

		cout << "Command:                PostComment(post8, Good Luck!)\n\n";
		searchPostFromID("post4")->addComment(tempUser, "Good Luck!");
		cout << "Command:                ViewPost(post4)\n-----------------------------------------------------------\n\n";
		searchPostFromID("post4")->timelineView();
		cout << "-----------------------------------------------------------\n";

		cout << "Command:                PostComment(post8, Thanks for the wishes)\n\n";
		searchPostFromID("post8")->addComment(tempUser, "Thanks for the wishes");
		cout << "Command:                ViewPost(post8)\n-----------------------------------------------------------\n\n";
		searchPostFromID("post8")->timelineView();
		cout << "-----------------------------------------------------------\n";
		cout << "Command:                SeeYourMemories()\n-----------------------------------------------------------\n\n";
		tempUser->seeYourMemories();
		cout << "-----------------------------------------------------------\n";
		cout << "Command:                Share Memory(post10, Never thought I will be specialist in this field....)\n\n";
		cout << "Command:                View Timeline\n-----------------------------------------------------------\n\n";
		tempUser->shareMemory(searchPostFromID("post10"), "Never thought I will be specialist in this field....");
		tempUser->viewTimeline();
		cout << "-----------------------------------------------------------\n";
		cout << "Command:                ViewPage(p1)\n-----------------------------------------------------------\n\n";
		searchPageFromID("p1")->viewTimeline();
		cout << "-----------------------------------------------------------\n";
	}
	else
		cout << "User not found\n";
	const char* tempUserName2 = "u11";
	user* tempUser2 = new user;
	tempUser2 = searchUserByID(tempUserName2);

	if (tempUser2 != 0)
	{
		//OBJECT PRINTING
		cout << tempUser2->getName() << " successfully set as Current User\n\n";
		cout << "Command:                View Home Page\n-----------------------------------------------------------\n\n";
		tempUser2->viewHomePage();
		cout << "-----------------------------------------------------------\n";
		cout << "Command:                View Timeline\n-----------------------------------------------------------\n\n";
		tempUser2->viewTimeline();
		cout << "-----------------------------------------------------------\n";
	}
	else
		cout << "User not found\n";
}

//USER CLASS FUNCTIONS

user::user()
{
	ID = 0;
	firstName = 0;
	lastName = 0;
	friendList = 0;
	likedPages = 0;
	totalFriends = 0;
	totalLikedPages = 0;
	Timeline = 0;
	totalPosts = 0;
}
user::~user()
{
	delete[] firstName;
	firstName = 0;
	delete[] lastName;
	lastName = 0;
	delete[] friendList;
	friendList = 0;
	delete[] likedPages;
	likedPages = 0;
	delete[] Timeline;
	Timeline = 0;
}
char* user::getName()
{
	char temp[30]="";
	int i = 0,j=0;
	while (firstName[i] != '\0')
	{
		temp[i] = firstName[i];
		i++;
	}
	temp[i] = ' ';
	i++;
	while (lastName[j] != '\0')
	{
		temp[i] = lastName[j];
		i++;
		j++;
	}
	char* tempname = helper::getStringFromBuffer(temp);
	return tempname;
}
void user::declarePageArray()
{
	likedPages = new page * [10];
	for (int i = 0; i < 10; i++)
	{
		likedPages[i] = new page;
	}
}
void user::loadUserFromFile(ifstream& fin, char** tempFriendID)
{
	int i = 0;
	char* temp = new char[20];
	fin >> temp;
	ID = helper::getStringFromBuffer(temp);
	fin >> temp;
	firstName = helper::getStringFromBuffer(temp);
	fin >> temp;
	lastName = helper::getStringFromBuffer(temp);
	for (int j = 0; j < 10; j++)
		tempFriendID[j] = new char;
	if (temp[0] != '-')
	{
		friendList = new user * [10];
		for (int i = 0; i < 10; i++)
			friendList[i] = new user;
	}
	do
	{
		fin >> temp;
		delete[] tempFriendID[i];
		tempFriendID[i] = helper::getStringFromBuffer(temp);
		i++;
	} while (temp[0] != '-');
	delete[] temp;
}
void user::likePage(page* pageToLike)
{
	likedPages[totalLikedPages++] = pageToLike;
}
char* user::getID()
{
	return ID;
}
void user::setID(const char* rhs)
{
	ID = helper::getStringFromBuffer(rhs);
}
void user::addFriend(user* userToAdd)
{
	friendList[totalFriends++] = userToAdd;
}
void user::viewFriendList()
{
	cout << firstName << " " << lastName << " -- Friend's List\n\n";
	for (int i = 0; i < totalFriends; i++)
	{
		cout << friendList[i]->ID << " - " << friendList[i]->firstName << " " << friendList[i]->lastName << endl;
	}
}
void user::viewLikedPages()
{
	cout << firstName << " " << lastName << " -- Liked Pages\n\n";
	for (int i = 0; i < totalLikedPages; i++)
	{
		cout << likedPages[i]->getID() << likedPages[i]->getName() << endl;
	}
}
void user::addToTimeline(post* ptr)
{
	if (totalPosts == 0)
		Timeline = new post * [10];
	Timeline[totalPosts++] = ptr;
}
void user::viewTimeline()
{
	cout << firstName << " " << lastName << " Timeline: \n\n";
	for (int i = 0; i < totalPosts; i++)
	{
		Timeline[i]->timelineView();
		cout << endl;
	}
}
void user::ViewFriendsTimeline()
{
	for (int i = 0; i < totalPosts; i++)
	{
		Timeline[i]->homePageView();
	}
}
void user::viewHomePage()
{
	cout << firstName << " " << lastName << " Home Page: \n\n";
	for (int i = 0; i < totalFriends; i++)
	{
		friendList[i]->ViewFriendsTimeline();
	}
	for (int i = 0; i < totalLikedPages; i++)
	{
		likedPages[i]->ViewFriendsTimeline();
	}
}
void user::seeYourMemories()
{
	for (int i = 0; i < totalPosts; i++)
	{
		Timeline[i]->seeMomories();
	}
}
void user::shareMemory(post* memory, const char* text)
{
	post* tempPost;
	for (int i = 0; i < totalPosts; i++)
	{
		if (memory->isMemory() > -1)
		{
			if (memory == Timeline[i])
			{
				for (int j = 0; j < i; j++)
				{
					tempPost = Timeline[i];
					Timeline[i] = Timeline[j];
					Timeline[j] = tempPost;
				}
				Timeline[0]->addToMemory(text);
				return;
			}
		}
	}
}

//PAGE CLASS FUNCTIONS

page::page()
{
	ID = 0;
	pageName = 0;
	totalPosts = 0;
	Timeline = 0;
}
page::~page()
{
	delete[] pageName;
	pageName = 0;
	delete[] Timeline;
	Timeline = 0;
}
void page::loadPageFromFile(ifstream& fin)
{
	char* temp = new char[100];
	fin >> temp;
	ID = helper::getStringFromBuffer(temp);
	fin.ignore();
	fin.getline(temp, 100);
	pageName = helper::getStringFromBuffer(temp);
	delete[] temp;
}
char* page::getID()
{
	return ID;
}
char* page::getName()
{
	return pageName;
}
void page::setID(const char* rhs)
{
	ID = helper::getStringFromBuffer(rhs);
}
void page::addToTimeline(post* ptr)
{
	if (totalPosts == 0)
		Timeline = new post * [10];
	Timeline[totalPosts++] = ptr;
}
void page::ViewFriendsTimeline()
{
	for (int i = 0; i < totalPosts; i++)
	{
		Timeline[i]->homePageView();
	}
}
void page::viewTimeline()
{
	for (int i = 0; i < totalPosts; i++)
	{
		Timeline[i]->timelineView();
		cout << endl;
	}
}

//POST CLASS FUNCTIONS

post::post()
{
	ID = 0;
	Activity = 0;
	Text = 0;
	dateOfPost;
	SharedBy =0;
	Comments = 0;
	LikedBy =0;
	totalLikes = 0;
	totalComments = 0;
	memoryPost = 0;
}
void post::readPostFromFile(ifstream& fin)
{
	int activityCheck = 0;
	char* temp = new char[100];
	fin >> activityCheck;
	fin >> temp;
	ID = helper::getStringFromBuffer(temp);
	dateOfPost.loadDateFromFile(fin);
	fin.ignore();
	fin.getline(temp, 100);
	Text = helper::getStringFromBuffer(temp);
	if (activityCheck == 2)
	{
		Activity = new activity;
		Activity->readActivityFromFile(fin);
	}
}
void post::setSharedBy(object* ObjectPtr)
{
	SharedBy = ObjectPtr;
}
void post::setLikedBy(object* ObjectPtr)
{
	if (totalLikes == 0)
		LikedBy = new object* [10];
	LikedBy[totalLikes++] = ObjectPtr;
}
void post::timelineView()
{
	if (memoryPost)
	{
		cout << "~~~" << SharedBy->getName() << " shared a memory~~~...";
		memoryPost->dateOfPost.Print();
		cout << memoryPost->Text << endl;
		cout << "\t\t(" << isMemory() << " years old)\n";
	}
	cout << SharedBy->getName();
	if(Activity)
		Activity->viewActivity();
	cout << " '"<<Text << "'...";
	dateOfPost.Print();
	for (int i = 0; i < totalComments; i++)
	{
		Comments[i]->viewComment();
	}
}
void post::homePageView()
{
	if (dateOfPost == Facebook::currentDate || dateOfPost.isYesterday())
	{
		cout<<SharedBy->getName();
		if (Activity)
			Activity->viewActivity();
		else
			cout << " shared ";
		cout << "'" << Text << "'\n";
		for (int i = 0; i < totalComments; i++)
		{
			Comments[i]->viewComment();
		}
		cout << endl;
	}
}
char* post::GetID()
{
	return ID;
}
void post::addCommentToPost(comment* Commentptr)
{
	if (totalComments == 0)
		Comments = new comment * [10];
	Comments[totalComments++] = Commentptr;
}
void post::viewLikedBy()
{
	for (int i = 0; i < totalLikes; i++)
	{
			cout << LikedBy[i]->getID() << " - " << LikedBy[i]->getName() << endl;
	}
	if (totalLikes == 0)
		cout << "No Object Liked this Post.\n";
}
void post::LikePost(object* addToLiked)
{
	setLikedBy(addToLiked);
}
void post::addComment(object* user, const char* text)
{
	comment* temp =  new comment;
	temp->declareComment(user, text);
	addCommentToPost(temp);
}
void post::seeMomories()
{
	if (isMemory() > -1)
	{
		cout << "We hope you enjoy looking back and sharing your memories on Facebook, from the most recent to those long ago.\n\n";
		cout << "On this Day\n";
		cout << dateOfPost.isMemory() << " Years Ago\n";
		timelineView();
		cout << endl;
	}
}
int post::isMemory()
{
	return dateOfPost.isMemory();
}
void post::addToMemory(const char* text)
{
	memoryPost = new post;
	memoryPost->dateOfPost = Facebook::currentDate;
	memoryPost->Text = helper::getStringFromBuffer(text);
}

//ACTIVITY CLASS FUNCTIONS

void activity::readActivityFromFile(ifstream& fin)
{
	fin >> Type;
	char* temp = new char[50];
	char* tempValue = new char[30];
	const char* tempType = new char[20];
	int i = 0, j = 0;
	if (Type == 1)
		tempType = "Feeling";
	else if (Type == 2)
		tempType = "Thinking about";
	else if (Type == 3)
		tempType = "Making";
	else if (Type == 4)
		tempType = "Celebrating";
	else
		tempType = "Invalid";
	while (tempType[i] != '\0')
	{	
		temp[i] = tempType[i];
		i++;
	}
	temp[i] = ' ';
	i++;
	fin.ignore();
	fin.getline(tempValue,100);
	while (tempValue[j] != '\0')
	{
		temp[i] = tempValue[j];
		i++;
		j++;
	}
	temp[i] = '\0';
	Value = helper::getStringFromBuffer(temp);
	//delete[] tempType;
	delete[] tempValue;
	delete[] temp;
}
void activity::viewActivity()
{
	cout <<" is " << Value << endl;
}

//DATE CLASS FUNCTIONS

Date::Date(int d, int m, int y)
{
	date = d;
	month = m;
	year = y;
}
void Date::Print()
{
	cout << date << "/" << month << "/" << year << endl;
}
void Date::loadDateFromFile(ifstream& fin)
{
	fin >> date;
	fin >> month;
	fin >> year;
}
bool Date::operator==(Date rhs)
{
	if (rhs.date == date)
		if (rhs.month = month)
			if (rhs.year = year)
				return 1;
	return 0;
}
bool Date::isYesterday()
{
	if (Facebook::currentDate.date != 1)
		if (Facebook::currentDate.date - 1 == date)
			if (Facebook::currentDate.month == month)
				if (Facebook::currentDate.year == year)
					return 1;
	else if (Facebook::currentDate.date == 1 && Facebook::currentDate.month != 1)
		if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10)
			if (date == 31 && Facebook::currentDate.year == year)
				return 1;
		else if (month == 4 || month == 6 || month == 9 || month == 11)
			if (date == 30 && Facebook::currentDate.year == year)
				return 1;
		else if (month == 2)
			if (date == 28 && Facebook::currentDate.year == year)
				return 1;
	else if (Facebook::currentDate.date == 1 && Facebook::currentDate.month == 1)
		if (date == 31 && month == 12 && year == Facebook::currentDate.year - 1)
			return 1;
	return 0;
}
int Date::isMemory()
{
	if (date == Facebook::currentDate.date && month == Facebook::currentDate.month)
		return Facebook::currentDate.year - year;
	return -1;
}
void Date::operator=(Date& rhs)
{
	date = rhs.date;
	month = rhs.month;
	year = rhs.year;
}

//COMMENT CLASS FUNCTIONS

comment::comment()
{
	ID = 0;
	Text = 0;
	CommentBy = 0;
}
void comment::loadCommentID(ifstream& fin)
{
	char temp[10];
	fin >> temp;
	ID = helper::getStringFromBuffer(temp);
}
void comment::loadCommentData(ifstream& fin)
{
	char temp[100];
	fin.ignore();
	fin.getline(temp, 100);
	Text = helper::getStringFromBuffer(temp);
}
void comment::SetCommentBy(object* ptr)
{
	CommentBy = ptr;
}
void comment::viewComment()
{
	cout <<"\t\t" << CommentBy->getName() << " wrote: '" << Text << "'" << endl;
}
void comment::declareComment(object* user, const char* text)
{
	CommentBy = user;
	Text = helper::getStringFromBuffer(text);
}
