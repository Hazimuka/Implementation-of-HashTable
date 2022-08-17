//2019341_Muhammad Khuzaima Abbasi
//2019215_Muhammad Umar Niazi


//This program works perfectly most of the time. But sometimes it gives errors for no reason.
//If such a situation happens, would you please just restart it. Thank You.
#include <iostream>
#include<string>
#include<fstream>
using namespace std;

const int Size = 10;//Size of hashtable, It will remain unchanged

void Menu();

class HashTable// The class through which all functions will be performed
{
public:

    struct Node//Used to create node
    {
        string name = "", primary = "", secondary = "", address = "";
        int Sr;

        int Ctr=0;
        Node* Prv;
        Node* Next;

    };




private:

    Node* Hash[Size];//declaring hashtable

public:
    void initialize();

    int HashFun(string Name);//declaring hash function

    void Insert(int Serial, string Name, string pri, string sec, string Add, int Count);//Declaring insert function

    void Search(string Name,int count);// declaring a Search Funtion

    void Delete(string Name, int count);// deleting a node from the hastable


};

int HashTable::HashFun(string Name)//Calculating the index position via Name
{
    int value = 0;

    for (int i = 0; Name[i] != '\0'; i++)
    {
        value += int(Name[i]);

    }

    return value % Size;

}

void HashTable::initialize()//Initializing all Hashvalues to Null
{

    for (int i = 0; i < Size; i++)
    {
        Hash[i] = NULL;

    }
}

void HashTable::Insert(int Serial,string Name, string pri, string sec, string Add, int count)//Insert into hashtable
{

   int key = HashFun(Name);

    Node* temp = new Node;
    temp->Ctr = count;
    temp->Sr = Serial;
    temp->name = Name;
    temp->address = Add;
    temp->primary = pri;
    temp->secondary = sec;

    if (key > 9 && key < 0)//Key is out of bound
    {
        cout << "Index does not exist" << endl;


    }

    else if (Hash[key] == NULL)//Free hash Index
    {

        Hash[key] = temp;
        temp->Prv = NULL;
        temp->Next = NULL;

        cout << "Node added at Index " << key << endl;


    }

    else if (Hash[key] != NULL)//collision occurs
    {

        cout << "Collision has occurred" << endl << endl;

        

           Node* App=Hash[key];

        

        while (App->Next!= NULL)
        {
            App = App->Next;

        }

      
        App->Next = temp;
        temp->Prv = App;

        temp->Next = NULL;

        cout << "Node added at index "<<key<<", at the end of the Link" << endl;

    }

}

void HashTable::Search(string Name, int counter)//Search for a name in the HashTable
{

   int key = HashFun(Name);

    Node* Temp = Hash[key];
   
    int i = 0;

    while (Temp!=NULL)//Traversing the LinkList
    {
        if (Temp->name == Name && Temp->Ctr == counter)//If name found
        {
            cout << "Name Found in Hash Table" << endl << endl;

            cout << " Located at index position " << key << endl;
            cout << " Serial Number " << Temp->Sr << endl;
            cout << " Primary Number " << Temp->primary << endl;
            cout << " Secondary Number " << Temp->secondary << endl;
            cout << " Address " << Temp->address << endl;
            cout << " Counter " << Temp->Ctr << endl << endl;

            return;
        }
        
        Temp = Temp->Next;
 
        
    }
        cout << "Name does not exist in the Hash Table" << endl;  //if name does not exist 

}

void HashTable::Delete(string Name, int count)//Deleting a record from the HashTable
{
    int key = HashFun(Name);

    Node* Temp = Hash[key];
    Node* Trash = Temp->Prv;

    Node* Garbage = Temp->Next;

    while (Temp != NULL )//Traversing the LinkList
    {
      
       
        if (Temp->name == Name && Temp->Prv== NULL && Temp->Ctr == count)//If record is in the Table
        {

            if (Garbage != NULL)
            {
                Garbage->Prv = NULL;
                Hash[key] = Garbage;
                Temp->Next = NULL;

            }

            Temp = NULL;
            delete Temp;


            cout << "Record is deleted" << endl;

            return;
        }

        else if (Temp->name == Name && Temp->Prv != NULL && Temp->Ctr == count)//If record is in the Chain
        {
            if (Garbage == NULL)//Last Node
            {
                Trash->Next = Garbage;
            }

            else if (Garbage != NULL)//Node in between
            {
                Trash->Next = Garbage;
                Garbage->Prv = Trash;


            }

            Temp->Prv = NULL;

            Temp->Next = NULL;

            delete Temp;

            cout << "Record Deleted" << endl;

            return;
        }

       
        Temp = Temp->Next;
        Trash = Temp->Prv;

         Garbage = Temp->Next;
    }
    
    cout<<"Record to be deleted does not exist"<<endl;//Loop completes all iterations but node is not found
   

}

int main()
{
    Menu();//calling menu
}

void Menu()// Menu to use the program
{
    char choice = ' ';

    bool Cope = true;
    ifstream file;
    string Name, Add, Pri, Sec;
    int Sr,counter=0;
    HashTable Obj;

    Obj.initialize();

    while (Cope == true)//Menu will remain unless exited
    {
        cout << "Enter your Option" << endl << endl;

        cout << "1: Insert a record into the HashTable" << endl;
        cout << "2: Search for a record in the HashTable through a name" << endl;
        cout << "3: Delete a record in the HashTable" << endl;
        cout << "4: Exit the program" << endl;

        cin >> choice;

        switch (choice)
        {

        case'1':
        {
            file.open("Table.txt", ios::in);//Creating a txt file to read from

            while (!file.eof())//Until there is no text to red
            {
                cout << "Do you wish to insert a record,y/n" << endl;
                char option = ' ';

                cin >> option;

              
                if (option == 'n')
                {

                    break;


                }

                else if (option== 'y')
                {

                    file >> Sr >> Name >> Pri >> Sec >> Add;

                    cout << "Enter counter" << endl;
                    cin >> counter;

                    Obj.Insert(Sr, Name, Pri, Sec, Add,counter);

                    
                }

                else
                {
                    cout << "Invalid input. "<<"Returning to menu" << endl;
                    
                    break;

                }

               
            }
            file.close();
            break;

        }
        case'2':
        {

            cout << "Enter the Name of the Record you have to search for" << endl;
            cin >> Name;
            cout << "Enter the counter" << endl;
            cin >> counter;
            Obj.Search(Name,counter);

            break;


        }
        case '3':
        {
            cout << "Enter the name of the record to be deleted" << endl;
            cin >> Name;
            cout << "Enter the counter" << endl;
            cin >> counter;
            Obj.Delete(Name,counter);

            break;
        }

        case '4':
        {
            Cope = false;

            break;


        }

        default:
        {

            cout << "Invalid Choice." << " Retuning to menu" << endl << endl;
            break;

        }
        }

        }
    }
