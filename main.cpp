/* Course: CS552 (Data Structures and Algorithm Analysis)
   Batch MSCS 1901
   Name: Zerihun Tilahun Eshete
   ID: TD 3767
   Lab Assignment Five: Linked-list Pointer application*/
#include<iostream>
using namespace std;
#include "linkedList_pointer.cpp"

enum{ADD_FLOAT = 1, ADD_RANGE_OF_FLOAT, REMOVE_FLOAT, REMOVE_RANGE_OF_FLOAT, SEARCH_FLOAT, GET_RANGE_OF_FLOAT, UPDATE, COPY, COUNT, DISPLAY, CLEAR, EXIT};

int menu();

int main()
{
    linkedList<float>list;
    createList(list);

    int choice;
    do
    {
        choice = menu();
        int size;
        char accept;
        bool found = false;
        switch(choice)
        {
            case ADD_FLOAT:
            {
                float newData;
                bool inserted = true;
                cout<<"How many numbers would you like to insert at once? ";
                cin>>size;
                system("cls");
                for(int i=0;i<size && inserted ;i++)
                {
                    if(i == 0)
                        cout<<"Enter floating # "<<i+1<<" to insert: ";
                    else
                        cout<<"Success! Enter floating # "<<i+1<<" to insert: ";
                    cin>>newData;
                    system("cls");
                    inserted = insert(list, newData);
                    if(inserted == false)
                    {
                        cout<<"Machine memory is currently full. ";
                        if(i == 0)
                            cout<< "Sorry no number is able to be inserted. Please try again later."<<endl;
                        else if (i == 1)
                            cout<< "Sorry only one number is able to be inserted successfully. Please try again later."<<endl;
                        else
                            cout<< "Only "<<i<<" numbers are inserted successfully. Please try again later."<<endl;
                    }
                }
                if(inserted)
                    cout<< "All requested numbers are inserted successfully."<<endl;
            }
                break;
            case ADD_RANGE_OF_FLOAT:
            {
                cout<< "NOTE(This is for demonistration purpose only.):\n\nBecause we don't have a list to be to be inserted in the another list:\n1. Create a new linked list\n2. Insert numbers in the new linked list as much as you want\n3. Now insert the new linked list in the other linked list after the position you specify.\n\nPopulate the new list with numbers using the keyboard when requested.\n\nEnter -1 when you are done.\n\n";
                system("pause");
                system("cls");

                float after, newData = 0;
                linkedList<float>addList;
                createList(addList);

                while(newData != -1)
                {
                    cout<<"Enter a floating number(-1 to end the insertion): ";
                    cin>>newData;
                    system("cls");
                    if(newData != -1)
                        insert(addList, newData);
                }
                
                cout<<"New list is successfully populated.\n\nNow proceed to inserting this list to another list after a given target number.\n\nEnter the taret number of the other linked list: ";
                cin>>after;
                system("cls");

                if(list.head == nullptr)// Or isEmpty(list)
                {
                    insertRangeAfter(list, after, addList);
                    cout<< "The destination list is empty.\nThe new list is added at the beginning.\n\n";
                }
                else
                {
                    do
                    {
                        found = insertRangeAfter(list, after, addList);
                        if(found)
                        {
                            cout<<"New list is successfully inserted in the old one\nafter the specified number.\n";
                            accept = 'n';
                        }
                        else
                        {
                            cout<<"Target number not found in the old list.\nWould you like to go again? ";
                            cin>>accept;
                            system("cls");
                        }
                    } while(accept == 'y' || accept == 'Y');
                }
                    if(found == false && (accept == 'n' || accept == 'N'))
                        cout<<"Target number not found in the old list.\nNew list is not inserted.\n";   
            }
                break;
            case REMOVE_FLOAT:
            {
                if(list.head == nullptr)// Or isEmpty(list)
                    cout<< "List is empty. Nothing to remove."<<endl;
                else
                {
                    float deleteData;
                    int count=0;
                    cout<<"How many numbers would you like to delete at once? ";
                    cin>>size;
                    system("cls");
                    for(int i=0;i<size;i++)
                    {
                        if(i==0)
                        {
                            if(count == 0)
                                cout<< "Enter floating # "<<i+1<<" to delete: ";
                            else
                                cout<<"Okay. Enter again floating # "<<i+1<<" to delete: ";
                        }
                        else
                        {
                            if(count == 0)
                                cout<< "Success! Enter floating # "<<i+1<<" to delete: ";
                            else
                                cout<<"Okay. Enter again floating # "<<i+1<<" to delete: ";
                        }
                        cin>>deleteData;
                        system("cls");
                        found = remove(list, deleteData);
                        if(found == false)
                        {
                            cout<< deleteData<<" does not exist in the list. Did you put the wrong number?(y/Y/n/N): ";
                            cin>>accept;
                            system("cls");
                            if(accept == 'y' || accept == 'Y')
                            {
                                i--;
                                count++;
                            }
                            else
                                count = 0;
                        }
                        else
                            count = 0;
                    }
                    cout<< "All numbers are removed successfully!"<<endl;
                }
                
            }
                break;
            case REMOVE_RANGE_OF_FLOAT:
                cout<<"This section is under construction!\nFunction definition is complete.\n";
                break;
            case SEARCH_FLOAT:
            {
                if(list.head == nullptr)// Or isEmpty(list)
                    cout<< "List is empty. Nothing to search."<<endl;
                else
                {
                    node<float>* pos;
                    float searchNum;
                    do
                    {
                        cout<<"Enter the number you would like to search: ";
                        cin>>searchNum;
                        system("cls");
                        found = search(list, searchNum, pos);
                        if(found){
                            cout<<searchNum<<" is found at address "<<pos<<"."<<endl;
                            cout<<pos->data<<endl;}
                        else
                            cout<<searchNum<<" is not found in list"<<endl;
                        system("pause");
                        system("cls");
                        cout<<"Would you like to repeat the searching? (y/Y/n/N): ";
                        cin>>accept;
                        system("cls");
                    } while (accept == 'y' || accept == 'Y');
                }
            }
                break;
            case GET_RANGE_OF_FLOAT:
                cout<<"This section is under construction!\nFunction definition is complete.\n";
                break;
            case UPDATE:
            {
                if(list.head == nullptr)// Or isEmpty(list)
                    cout<< "List is empty. Nothing to update."<<endl;
                else
                {
                    float searchNum, updateNum;
                    do
                    {
                        cout<<"Enter the number you would like to replace: ";
                        cin>>searchNum;
                        cout<<"Enter the new number you would like to add: ";
                        cin>>updateNum;
                        system("cls");
                        found = update(list, searchNum, updateNum);
                        if(found)
                            cout<<searchNum<<" is found and replaced with " <<updateNum<<"."<<endl;
                        else
                            cout<<searchNum<<" is not found."<<endl;
                        system("pause");
                        system("cls");
                        cout<<"Would you like to repeat the updating process? (y/Y/n/N): ";
                        cin>>accept;
                        system("cls");
                    } while (accept == 'y' || accept == 'Y');   
                }
            }
                break;
            case COPY:
            {
                cout<<"This section is under construction.\n";
                // linkedList<float>copyList;
                // createList(copyList);
                // copy(list, copyList);
                // displayList(copyList);
                // cout<< "List is successfully copied!\n";
                
            }
                break;
            case COUNT:
            {
                if(list.head == nullptr)// Or isEmpty(list)
                    cout<< "List is empty. Nothing to count."<<endl;
                else
                {
                    int cnt;
                    count(list, cnt);
                    cout<<"The number of elements is "<<cnt<<"."<<endl;
                }
            }
                break;            
            case DISPLAY:
            {
                if(list.head == nullptr)// Or isEmpty(list)
                    cout<< "List is empty. Nothing to display."<<endl;
                else
                    displayList(list);
            }
                break;
            case CLEAR:
            {
                if(list.head == nullptr)// Or isEmpty(list)
                    cout<< "List is empty. Nothing to clear."<<endl;
                else
                {
                    clear(list);
                    cout<<"list is now distroyed.\n"; 
                }
            }
                break;
            case EXIT:
                cout<<"Exiting Program\n\n";
                break;
        }
        system("pause");
        system("cls");
    } while (choice != EXIT);

}

int menu()
{
    int choice, invalid=0;
    do
    {
        if(invalid == 1)
        {
            cout<<setfill('-')<<setw(52)<<'-'<<setfill(' ')<<endl;
            cout << "Invalid choice! Please select an appropriate number: "<<endl;
            cout<<setfill('-')<<setw(52)<<'-'<<setfill(' ')<<endl;
        }
        else
        {
            cout<<setfill('-')<<setw(35)<<'-'<<setfill(' ')<<endl;
            cout<< "Choose from the menu below: "<<endl;
            cout<<setfill('-')<<setw(35)<<'-'<<setfill(' ')<<endl;
        }
        cout<< "1.  Add float\n2.  Add a Range of floats\n3.  Remove float\n4.  Remove of Range of float\n5.  Search a Float\n6.  Get a Range of Floats\n7.  Update\n8.  Copy\n9.  Count\n10. Display\n11. Clear\n12. Exit \n";
        cout<< "Enter the number of your choice: ";
        cin>>choice;
        if(choice < ADD_FLOAT || choice > EXIT)
            invalid = 1;
        else
            invalid = 0;
        system("cls");
    } while (invalid == 1);

    return choice;

}