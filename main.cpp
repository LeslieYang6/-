

#include<iostream>
#include<list>
#include<fstream>
#include<cstring>

using namespace std;

#define ListSize 100



struct Student
{
    int number;
    string name;
    int sex;//0，女孩，1，男孩//
    string ID;
    string Class;
};

typedef struct
{
    Student list[ListSize];
    int length;
}SeqList;

void InitList(SeqList *L)
{
    L->length=0;
    ifstream infile("binary_score.dat",ios::in|ios::binary);
    if(!infile)
    {
        cout<<"空文件，初始化";
        infile.close();
        return;
    }
    for(int i=0;i<100;i++)
    {
        if(infile.eof()) {
            break;
        }
        infile.read((char*)&L->list[i].number,sizeof(L->list[i].number));
        infile.read((char*)&L->list[i].sex,sizeof(L->list[i].sex));
        size_t size;
        infile.read((char*)&size,sizeof(size));
        L->list[i].name.resize(size);                  //利用记录下来的size去确定需要string的大小//
        infile.read(&L->list[i].name[0],size);
        infile.read((char*)&size,sizeof(size));
        L->list[i].ID.resize(size);
        infile.read(&L->list[i].ID[0],size);
        infile.read((char*)&size,sizeof(size));
        L->list[i].Class.resize(size);
        infile.read(&L->list[i].Class[0],size);
        L->length++;
    }
    infile.close();
}

int IsEmpty(SeqList L)
{
    if (L.length==0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int GetElem(SeqList L,int i,Student *e)
{
    if (i<1||i>L.length)
    {
        return -1;
    }
    *e=L.list[i-1];
    return 1;
}


int LocateElem(SeqList L,Student e)
{
    for (int i=0;i<L.length;i++)
    {
        if (e.name==L.list[i].name)
        {
            return i;
        }
    }
    return 0;
}




int InsertList(SeqList *L,int i,Student e)
/*在顺序表的第i个位置插入元素e，插入成功返回1，如果插入位置不合法返回-1，顺序表满返回0*/
{
    if (i<1||i>L->length+1)
    {
        printf("插入位置不合法!\n");
        return -1;
    }
    else if (L->length>=ListSize)
    {
        printf("顺序表已满，不能插入数据!\n");
        return 0;
    }
    else
    {
        for (int j=L->length;j>=i;j--)	//将第i位置以后的元素依次后移
        {
            L->list[j]=L->list[j-1];
        }
        L->list[i-1]=e;	//插入元素到第i个位置
        L->length+=1;	//将顺序表长加1
        return 1;
    }
}


int DeleteElem(SeqList *L,int i,Student *e)
/*将顺序表中的第i个位置删除，并将其值赋值给e*/
{
    if (L->length<=0)
    {
        printf("顺序表为空不能进行删除!\n");
        return 0;
    }
    else if (i<1||i>L->length)
    {
        printf("删除位置不合法!\n");
        return -1;
    }
    else
    {
        *e=L->list[i-1];
        for (int j=i;j<=L->length-1;j++)
        {
            L->list[j-1]=L->list[j];
        }
        L->length-=1;
        return 1;
    }
}
void ClearList(SeqList *L)
{
    L->length=0;
}

void CloseList(SeqList *L)
{
    ofstream outfile("binary_score.dat",ios::out|ios::binary|ios::trunc);
    for(int i=0;i<L->length;i++)
    {
        outfile.write((char*)&L->list[i].number,sizeof(L->list[i].number));
        outfile.write((char*)&L->list[i].sex,sizeof(L->list[i].sex));
        size_t size=L->list[i].name.size();
        outfile.write((char*)&size,sizeof(size));
        outfile.write(&L->list[i].name[0],size);
        size=L->list[i].ID.size();
        outfile.write((char*)&size,sizeof(size));
        outfile.write(&L->list[i].ID[0],size);
        size=L->list[i].Class.size();
        outfile.write((char*)&size,sizeof(size));
        outfile.write(&L->list[i].Class[0],size);
    }
    outfile.close();
    L->length=0;
}

int main()
{
    SeqList L;
    InitList(&L);
    Student p;
    p.Class="class 3";
    p.name="leslie";
    p.sex=1;
    p.number=20162931041;
    p.ID="510902199802022854";
    InsertList(&L,1,p);
    InsertList(&L,2,p);
    CloseList(&L);
    SeqList d;
    InitList(&d);
    cout<<d.list[0].ID<<endl;
    cout<<d.list[1].ID<<endl;
}