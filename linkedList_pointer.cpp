/* Name: Zerihun Tilahun Eshete
   ID: TD 3767 
   Assignment Five: Linked-list Pointer application*/
#include<iostream>

template <class T>
struct node
{
    T data;
    node<T> *next;
};

template <class T>
struct linkedList
{
    node<T> *head;
    node<T> *tail;
    bool sorted;
};

template <class T>
void createList(linkedList<T> &list, bool sorted=false)
{
    list.head = list.tail = nullptr;
    list.sorted = sorted;
}

template <class T>
bool isEmpty(linkedList<T> list)
{
    return list.head == nullptr;
}

template <class T>
static node<T>* insertionSlot(linkedList<T> list, node<T>* p)
{
    bool found=0;
    node<T>* prev=nullptr;
    while(list.head != nullptr && !found)
    {
        if(list.head->data < p->data)
        {
            prev = list.head;
            list.head = list.head->next;
        }
        else
        {
            found = true;
        }
    }
    return prev;
}

template <class T>
static void insertNode(linkedList<T> &list, node<T> *p, node<T>* prev)
{
    if(list.head==nullptr)
    {
		p->next=nullptr;
		list.head=list.tail=p;
	}
    else if (prev == nullptr)
    {
		p->next = list.head;
		list.head = p;
	}
    else
    {
		p->next = prev->next;
		prev->next = p;
		if(prev==list.tail)
            list.tail=p;
	}

}

template <class T>
void insert(linkedList<T> &list, T newData)
{
    node<T>* p, *prev;
    p->data = newData;
    if(list.sorted == false)
        prev = list.tail;
    else
        prev = insertionSlot(list, p);
    insertNode(list, p, prev);
}

template <class T>
static bool nodeToDelete(linkedList<T>list, T targetData, node<T>* prev)
{
    bool found = false, inList = true;
    prev = nullptr;
    if(list.sorted)
    {   
        while(!found && inList)
        {
            if(list.head->data < targetData)
            {
                prev = list.head;
                list.head = list.head->next;
                if(list.head == nullptr)
                {
                    inList = false;
                    return inList;
                }
            }
            else if(list.head->data == targetData)
            {
                found = true;
            }
            else
            {
                inList = false;
                return inList;
            }
        }
    }
    else
    {
        while(!found && list.head != nullptr)
        {
            if(list.head->data != targetData)
            {
                prev = list.head;
                list.head = list.head->next;
            }
            else
            {
                found = true;
            }
        }
    }

    return found;
}

template <class T>
static node<T>* deleteNode(linkedList<T> &list, node<T>* prev)
{
    node<T>* p;
    if(list.head==list.tail)
    {
        p=list.head;
        list.head=list.tail=nullptr;
    }
    else if(prev == nullptr)
    {
        p=list.head;
        list.head = list.head->next;
    }
    else
    {
        p=prev->next;
        prev->next = p->next;
        if(prev->next == list.tail)
            list.tail = prev;
    }
    return p;
}

template <class T>
bool remove(linkedList<T> &list, T targetData)
{
    node<T>* p, prev;
    if(nodeToDelete(list, targetData, prev))
    {
        p=deleteNode(list, prev);
        delete p;
        return true;
    }

    return false;
}

template <class T>
bool search(linkedList<T>list, T targetData, node<T>* pos)
{
    bool found = false, inList = true;
    pos = nullptr;
    if(list.sorted)
    {   
        while(!found && inList)
        {
            if(list.head->data < targetData)
            {
                list.head = list.head->next;
                if(list.head == nullptr)
                {
                    inList = false;
                    return inList;
                }
            }
            else if(list.head->data == targetData)
            {
                pos = list.head;
                found = true;
            }
            else
            {
                inList = false;
                return inList;
            }
        }
    }
    else
    {
        while(!found && list.head !=NIL)
        {
            if(list.head->data == targetData)
            {
                pos = list.head;
                found = true;
            }
            else
            {
                list.head = list.head->next;
            }
        }
    }
    return found;
}

template <class T>
bool update(linkedList<T>& list, T targetData, T updateNum)
{
    node<T>* pos;
    bool found = false;
    found = search(list, targetData, pos);
    if(found)
        pos->data = updateNum;

    return found;
}

template <class T>
void count(linkedList<T>list, int &cnt)
{
    cnt = 0;
    while(list.head != nullptr)
    {
        list.head = list.head->next;
        cnt++;
    }
}

template <class T>
void copy(linkedList<T> srcList, linkedList<T> &destList)
{
    node<T>* srcListCpy;
    srcListCpy = srcList.head;

    destList.tail = srcList.tail;
    destList.sorted = srcList.sorted;

    while(srcList.head != nullptr)
    {
        destList.head->data = srcList.head->data;
        destList.head->next = srcList.head->next;
        srcList.head = srcList.head->next;
        destList.head = destList.head->next;
    }

    destList.head = srcListCpy;
}

template <class T>
void displayList(linkedList<T> list)
{
    cout<<setw(10)<<"ADDRESS"<<setfill(' ')<<setw(10)<<"DATA"<<setfill(' ')<<setw(10)<<"NEXT"<<endl;
    cout<<setfill('-')<<setw(25)<<'-'<<setfill(' ')<<endl;
    while(list.head != nullptr)
    {
        cout<<setw(5)<<list.head<<setfill(' ')<<setw(10)<<right<<list.head->data<<setfill(' ')<<setw(10)<<list.head->next<<setfill(' ')<<endl;
        list.head = list.head->next;
    }
    system("pause");
    system("cls");
}
