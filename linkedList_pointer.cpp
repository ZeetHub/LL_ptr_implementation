/* Course: CS552 (Data Structures and Algorithm Analysis)
   Batch MSCS 1901
   Name: Zerihun Tilahun Eshete
   ID: TD 3767 
   Lab Assignment Five: Linked-list Pointer application*/

#include<cstdlib>
#include<iomanip>

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

/*
//BEGIN FUNCTION INTERFACES
template <class T>
void createList(linkedList<T> &list, bool sorted=false);
template <class T>
bool isEmpty(linkedList<T> list);
template <class T>
static node<T>* insertionSlot(linkedList<T> list, node<T>* p);
template <class T>
static void insertNode(linkedList<T> &list, node<T> *p, node<T>* prev);
template <class T>
void insert(linkedList<T> &list, T newData);
template <class T>
bool insertRangeAfter(linkedList<T> & list, T after, linkedList <T> range);
template <class T>
static bool nodeToDelete(linkedList<T>list, T targetData, node<T>* prev);
template <class T>
static node<T>* deleteNode(linkedList<T> &list, node<T>* prev);
template <class T>
bool remove(linkedList<T> &list, T targetData);
template <class T>
void removeRange(linkedList<T> & list, T target1, T target2, bool &foundOne, bool &foundTwo);
template <class T>
bool search(linkedList<T>list, T targetData, node<T>* pos);
template <class T>
linkedList<T> getRange(linkedList<T> list, T target1, T target2, bool &foundOne, bool &foundTwo);
template <class T>
bool update(linkedList<T>& list, T targetData, T updateNum);
template <class T>
void copy(linkedList<T> srcList, linkedList<T> &destList);
template <class T>
void count(linkedList<T>list, int &cnt);
template <class T>
void displayList(linkedList<T> list);
template <class T>
void clear(linkedList<T> list);
//END FUNCTION INTERFACES
*/


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
bool insert(linkedList<T> &list, T newData)
{
    bool inserted = false;
    node<T>* p, *prev;
    p = new(nothrow)node<T>;
    if(p != 0)
    {
        p->data = newData;
        if(list.sorted == false)
            prev = list.tail;
        else
            prev = insertionSlot(list, p);
        insertNode(list, p, prev);
        inserted = true;
    }

    return inserted;
}

template <class T>
bool insertRangeAfter(linkedList<T> & list, T after, linkedList <T> range)
{
    node<T> *pos;
    bool found = false;
    if(isEmpty(list))
    {
        range.tail = list.tail;
        list.head = range.head;       
    }
    else
    {
        found = search(list, after, pos);
        if(found)
        {
            range.tail->next = pos->next;
            pos->next = range.head;
        }   
    }

    return found;
}

template <class T>
static bool nodeToDelete(linkedList<T>list, T targetData, node<T>* &prev)
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
static node<T>* deleteNode(linkedList<T> &list, node<T>* &prev)
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
    node<T>* p, *prev;
    if(nodeToDelete(list, targetData, prev))
    {
        p=deleteNode(list, prev);
        delete p;
        return true;
    }

    return false;
}

template <class T>
void removeRange(linkedList<T> & list, T target1, T target2, bool &foundOne, bool &foundTwo)
{
    node<T> *prevPos1, *pos1, *pos2;

    foundOne = search(list, target1, pos1);
    foundTwo = search(list, target2, pos2);

    if(foundOne && foundTwo)
    {   
        nodeToDelete(list, target1, prevPos1);
        prevPos1->next = pos2->next;

        while(pos1 != pos2)
        {
            node<T>* posCpy = pos1;
            pos1 = pos1->next;
            delete posCpy;
        }

        delete pos2;
    }

}

template <class T>
bool search(linkedList<T>list, T targetData, node<T>* &pos)
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
        while(!found && list.head != nullptr)
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
linkedList<T> getRange(linkedList<T> list, T target1, T target2, bool &foundOne, bool &foundTwo)
{
    node<T> *prevPos1, *pos1, *pos2;

    linkedList<T> getList;
    createList(getList);

    foundOne = search(list, target1, pos1);
    foundTwo = search(list, target2, pos2);

    if(foundOne && foundTwo)
    {   
        while(pos1 != pos2)
        {
            insert(getList, pos1->data);
            pos1 = pos1->next;
        }

        insert(getList, target2);
    }

    return getList;
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
void copy(linkedList<T> srcList, linkedList<T> &destList)
{
    destList.head = new(nothrow)node<T>;
    destList.head->data = srcList.head->data;
    // destList.head->next = nullptr;
    // destList.head = 

    node<T>* destListCpy;
    destListCpy = destList.head;


    // destList.tail = srcList.tail;
    // destList.sorted = srcList.sorted;

    while(srcList.head != nullptr)
    {
        destListCpy = new(nothrow)node<T>;
        srcList.head = srcList.head->next;
        destListCpy->data = srcList.head->data;
        destListCpy->next = srcList.head->data;
        // destList.head->next = srcList.head->next;
    }

    destList.head = destListCpy;
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
void displayList(linkedList<T> list)
{
    cout<<setfill('-')<<setw(39)<<'-'<<setfill(' ')<<endl;    
    cout<<setw(12)<<left<<"ADDRESS"<<setw(15)<<right<<"DATA"<<setw(12)<<"NEXT"<<endl;
    cout<<setfill('-')<<setw(39)<<'-'<<setfill(' ')<<endl;
    while(list.head != nullptr)
    {
        cout<<setw(12)<<left<<list.head<<setw(15)<<right<<fixed<<setprecision(2)<<list.head->data<<setfill(' ')<<setw(12)<<list.head->next<<setfill(' ')<<endl;
        list.head = list.head->next;
    }
    cout<<setfill('-')<<setw(39)<<'-'<<setfill(' ')<<endl;
}

template <class T>
void clear(linkedList<T> &list)
{
    while(list.head != nullptr)
    {
        node<T>* headCpy = list.head;
        list.head = list.head->next;
        delete headCpy;
    }
    list.head = list.tail = nullptr;
}