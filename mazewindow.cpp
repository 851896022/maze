#include "mazewindow.h"
#include "ui_mazewindow.h"
#include <windows.h>
#include <QCryptographicHash>
MazeWindow::MazeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MazeWindow)
{
    ui->setupUi(this);
    for(int i=0;i<99;i++)
    {
        for(int j=0;j<99;j++)
        {
            l[i][j]=NULL;
        }
    }
}

MazeWindow::~MazeWindow()
{
    delete ui;
}

void MazeWindow::on_pushButton_clicked()
{
    for(int i=0;i<99;i++)
    {
        for(int j=0;j<99;j++)
        {
            if(l[i][j]!=NULL)
            {
                l[i][j]->hide();
            }
        }
    }
    type = ui->comboBox->currentIndex();
    switch (type) {
    case 0:countN=5; break;
        case 1:countN=9; break;
        case 2:countN=21; break;
        case 3:countN=35; break;
        case 4:countN=55; break;
        case 5:countN=75; break;
        case 6:countN=99; break;
    default:break;
    }
    int n=countN;
    Coordinate*s = NULL;
    while (s == NULL)
        s = new Coordinate[n*n];
    PrimeMap(s, n);
    ui->label->setMinimumSize(n*10,n*10);
    ui->label->setGeometry(ui->label->geometry().x(),ui->label->geometry().y(),n*10,n*10);
    draw(s,n);

    delete s;
}
void MazeWindow::Sequence(Coordinated *Arry, int n, int &sum)   //把元素从数组删除
{
    int i;
    for (i = n; i < sum; i++)
    {
        Arry[i] = Arry[i + 1];
    }
    sum--;
}

void MazeWindow::Store(Coordinated *map_1, Coordinate *map_2, int map, int &k, int n)     //把元素储存进数组
{
    if (((map + 2) % n != 0)&&map_2[map + 1].Judgemet_2 == 0)
    {
        map_1[k].adress = map + 1;
        map_2[map_1[k].adress].Judgemet_2 = 1;
        k++;
    }
    if (((map - 1) % n != 0) && map_2[map - 1].Judgemet_2 == 0)
    {
        map_1[k].adress = map - 1;
        map_2[map_1[k].adress].Judgemet_2 = 1;
        k++;
    }
    if (((map - n) / n != 0) && map_2[map - n].Judgemet_2 == 0)
    {
        map_1[k].adress = map - n;
        map_2[map_1[k].adress].Judgemet_2 = 1;
        k++;
    }
    if (((map + n) / n != n - 1) && map_2[map + n].Judgemet_2 == 0)
    {
        map_1[k].adress = map + n;
        map_2[map_1[k].adress].Judgemet_2 = 1;
        k++;
    }
}

void MazeWindow::PrimeMap(Coordinate *map, int n)
{
    Coordinated *map2 = new Coordinated[(n*n-3*n-2)/2];
    srand((unsigned)time(0));

    int k = 2;
    map2[0].adress = n + 2;
    map2[1].adress = 2 * n + 1;
    map[n + 2].Judgemet_2 = 1;
    map[2 * n + 1].Judgemet_2 = 1;

    int b;
    while(k!=0)
    {
        b = rand() % k;
        if ((map2[b].adress / n) % 2 == 0)
            if (map[map2[b].adress + n].Judgment + map[map2[b].adress - n].Judgment > 0)
            {
                map[map2[b].adress + n].Judgment = 0;
                map[map2[b].adress].Judgment = 0;
                map[map2[b].adress - n].Judgment = 0;
                Store(map2, map, map2[b].adress + n, k, n);
                Store(map2, map, map2[b].adress - n, k, n);
                Sequence(map2, b, k);
                continue;
            }
            else
            {
                Sequence(map2, b, k);
                continue;
            }
        if ((map2[b].adress / n) % 2 == 1)
            if (map[map2[b].adress + 1].Judgment + map[map2[b].adress - 1].Judgment > 0)
            {
                map[map2[b].adress + 1].Judgment = 0;
                map[map2[b].adress].Judgment = 0;
                map[map2[b].adress - 1].Judgment = 0;
                Store(map2, map, map2[b].adress + 1, k, n);
                Store(map2, map, map2[b].adress - 1, k, n);
                Sequence(map2, b, k);
                continue;
            }
            else
            {
                Sequence(map2, b, k);
                continue;
            }
    }
    map[1].Judgment = 0;
    map[n*n - 2].Judgment = 0;
    delete map2;
}
void MazeWindow::draw(Coordinate *map, int n)      //画迷宫的函数，map为指向储存迷宫数组的指针，n为迷宫大小
{
    //初始化
    for(int i=0;i<99;i++)
    {
        for(int j=0;j<99;j++)
        {
            mapBool[i][j]=false;
        }
    }
    addressX = 0;
    addressY = 1;
    targetX = n-1;
    targetY = n-2;

    //画图，黑色为墙，白色为通路
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            if (map[n * x + y].Judgment == 0) {
                if(l[x][y]!=NULL)
                {
                    l[x][y]->deleteLater();
                    l[x][y]=NULL;
                }
                while(l[x][y]==NULL)
                {
                    l[x][y]=new QWidget(ui->label);
                }

                l[x][y]->setGeometry(x*10,y*10,10,10);
                l[x][y]->setAutoFillBackground(true);
                l[x][y]->setPalette(QPalette(QPalette::Background,QColor(Qt::white)));
                l[x][y]->show();
                mapBool[x][y]=true;
                //paint->setPen(Qt::white);
                //paint->drawRect(x * 10, y * 10, x * 10 + 10, y * 10 + 10);
            }
            else
            {

                if(l[x][y]!=NULL)
                {
                    l[x][y]->deleteLater();
                    l[x][y]=NULL;
                }
                while(l[x][y]==NULL)
                {
                    l[x][y]=new QWidget(ui->label);
                }
                l[x][y]->setGeometry(x*10,y*10,10,10);
                l[x][y]->setAutoFillBackground(true);
                l[x][y]->setPalette(QPalette(QPalette::Background,QColor(Qt::black)));
                l[x][y]->show();

            }
        }

    }
    l[addressX][addressY]->setPalette(QPalette(QPalette::Background,QColor(Qt::red)));


}
#include <QInputDialog>
#include <QDir>
void MazeWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_A)
    {
        if(addressX>1)//如果没到边界
        {
            if(mapBool[addressX-1][addressY])//如果可以走
            {
                l[addressX][addressY]->setPalette(QPalette(QPalette::Background,QColor(Qt::white)));
                addressX--;
                l[addressX][addressY]->setPalette(QPalette(QPalette::Background,QColor(Qt::red)));
            }
        }
    }
    else if(event->key() == Qt::Key_W)
    {
        if(addressY>1)//如果没到边界
        {
            if(mapBool[addressX][addressY-1])//如果可以走
            {
                l[addressX][addressY]->setPalette(QPalette(QPalette::Background,QColor(Qt::white)));
                addressY--;
                l[addressX][addressY]->setPalette(QPalette(QPalette::Background,QColor(Qt::red)));
            }
        }
    }
    else if(event->key() == Qt::Key_D)
    {
        if(addressX<countN-1)//如果没到边界
        {
            if(mapBool[addressX+1][addressY])//如果可以走
            {
                l[addressX][addressY]->setPalette(QPalette(QPalette::Background,QColor(Qt::white)));
                addressX++;
                l[addressX][addressY]->setPalette(QPalette(QPalette::Background,QColor(Qt::red)));
                if(addressX == 1 && addressY == 1)
                {
                    isWork = true;
                    startTime=QDateTime::currentDateTime();
                    //qDebug()<<startTime;
                }
            }
        }
    }
    else if(event->key() == Qt::Key_S)
    {
        if(addressY<countN-1)//如果没到边界
        {
            if(mapBool[addressX][addressY+1])//如果可以走
            {
                l[addressX][addressY]->setPalette(QPalette(QPalette::Background,QColor(Qt::white)));
                addressY++;
                l[addressX][addressY]->setPalette(QPalette(QPalette::Background,QColor(Qt::red)));
            }
        }
    }
    if(addressX==targetX && addressY == targetY)
    {
        if(isWork==true)
        {
            endTime=QDateTime::currentDateTime();
            //qDebug()<<endTime;
            qint64 time=startTime.msecsTo(endTime);
            QMessageBox::information(this,"恭喜过关","用时"+
                                     QString::number(time/3600000)+"时"+
                                     QString::number((time%3600000)/60000)+"分"+
                                     QString::number(((time%3600000)%60000)/1000)+"秒"+
                                     QString::number(time%1000)+"毫秒");
            bool ok;
            QString text = QInputDialog::getText(this, tr("上传数据至排行榜"),
                                                       tr("如需上传请输入昵称，否则跳过"), QLineEdit::Normal,
                                                       QDir::home().dirName(), &ok);
            if (ok && !text.isEmpty())
            {
                QTcpSocket socket;
                socket.connectToHost("n5012346.vicp.cc",9879);
                socket.waitForConnected(5000);
                //textLabel->setText(text);
                QString data;
                data+=QString::number(type+1);
                data+="|";
                QString lpRootPathName = "C:\\";
                LPTSTR lpVolumeNameBuffer=new TCHAR[12];//磁盘卷标
                DWORD nVolumeNameSize=12;// 卷标的字符串长度
                DWORD VolumeSerialNumber;//硬盘序列号
                DWORD MaximumComponentLength;// 最大的文件长度
                LPTSTR lpFileSystemNameBuffer=new TCHAR[10];// 存储所在盘符的分区类型的长指针变量
                DWORD nFileSystemNameSize=10;// 分区类型的长指针变量所指向的字符串长度
                DWORD FileSystemFlags;// 文件系统的一此标志

                GetVolumeInformation((LPTSTR)lpRootPathName.utf16(),
                  lpVolumeNameBuffer, nVolumeNameSize,
                  &VolumeSerialNumber, &MaximumComponentLength,
                  &FileSystemFlags,
                  lpFileSystemNameBuffer, nFileSystemNameSize);
                data+=QCryptographicHash::hash (QString::number(VolumeSerialNumber).toLocal8Bit(), QCryptographicHash::Md5 ).toHex();
                data+="|";
                text.remove("|");
                text.remove("-");
                data+=text;
                data+="|";
                data+=QString::number(time);
                socket.write(data.toLocal8Bit());
                socket.flush();
                socket.deleteLater();

            }


            isWork=false;


        }


    }
    //qDebug()<<addressX<<targetX<<addressY<<targetY;
    event->accept();
}














































































#ifdef aaaa
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include <graphics.h>

using namespace std;

/**************************/

/******************/
/******************/

struct Coordinate  //迷宫点类
{
    bool Judgment = 1;   //判断是否为墙，1为是，0为不是
    bool Judgemet_2 = 0;  //prim算法用到，深度优先算法没用
};

struct Coordinated  //prim算法用到，深度优先算法没用
{
    int adress;
};

/*********************/
/********prime算法***********/
void Sequence(Coordinated *Arry, int n, int &sum)   //把元素从数组删除
{
    int i;
    for (i = n; i < sum; i++)
    {
        Arry[i] = Arry[i + 1];
    }
    sum--;
}

void Store(Coordinated *map_1, Coordinate *map_2, int map, int &k, int n)     //把元素储存进数组
{
    if (((map + 2) % n != 0)&&map_2[map + 1].Judgemet_2 == 0)
    {
        map_1[k].adress = map + 1;
        map_2[map_1[k].adress].Judgemet_2 = 1;
        k++;
    }
    if (((map - 1) % n != 0) && map_2[map - 1].Judgemet_2 == 0)
    {
        map_1[k].adress = map - 1;
        map_2[map_1[k].adress].Judgemet_2 = 1;
        k++;
    }
    if (((map - n) / n != 0) && map_2[map - n].Judgemet_2 == 0)
    {
        map_1[k].adress = map - n;
        map_2[map_1[k].adress].Judgemet_2 = 1;
        k++;
    }
    if (((map + n) / n != n - 1) && map_2[map + n].Judgemet_2 == 0)
    {
        map_1[k].adress = map + n;
        map_2[map_1[k].adress].Judgemet_2 = 1;
        k++;
    }
}

void PrimeMap(Coordinate *map, int n)
{
    Coordinated *map2 = new Coordinated[(n*n-3*n-2)/2];
    srand((unsigned)time(0));

    int k = 2;
    map2[0].adress = n + 2;
    map2[1].adress = 2 * n + 1;
    map[n + 2].Judgemet_2 = 1;
    map[2 * n + 1].Judgemet_2 = 1;

    int b;
    while(k!=0)
    {
        b = rand() % k;
        if ((map2[b].adress / n) % 2 == 0)
            if (map[map2[b].adress + n].Judgment + map[map2[b].adress - n].Judgment > 0)
            {
                map[map2[b].adress + n].Judgment = 0;
                map[map2[b].adress].Judgment = 0;
                map[map2[b].adress - n].Judgment = 0;
                Store(map2, map, map2[b].adress + n, k, n);
                Store(map2, map, map2[b].adress - n, k, n);
                Sequence(map2, b, k);
                continue;
            }
            else
            {
                Sequence(map2, b, k);
                continue;
            }
        if ((map2[b].adress / n) % 2 == 1)
            if (map[map2[b].adress + 1].Judgment + map[map2[b].adress - 1].Judgment > 0)
            {
                map[map2[b].adress + 1].Judgment = 0;
                map[map2[b].adress].Judgment = 0;
                map[map2[b].adress - 1].Judgment = 0;
                Store(map2, map, map2[b].adress + 1, k, n);
                Store(map2, map, map2[b].adress - 1, k, n);
                Sequence(map2, b, k);
                continue;
            }
            else
            {
                Sequence(map2, b, k);
                continue;
            }
    }
    map[1].Judgment = 0;
    map[n*n - 2].Judgment = 0;
    delete map2;
}
/*******prim算法**********/
/***********************/


/***********************/
/***图的深度优先算法***/

Stack* Pathfinding(Coordinate *map,int n)     //寻找迷宫路径的函数，返回一个储存路径的栈，map为指向迷宫数组的指针，n为迷宫大小
{
    int k = 1;
    Stack *x = CreateStack(n*n);
    Stack *v = CreateStack(n*n);
    PushStack(x, 1);
    PushStack(x, n + 1);

    while (1)
    {
        map[x->stack[k - 1]].Judgment = 1;
        if (map[TopStack(x) + 1].Judgment == 0)
        {
            map[x->stack[k - 1]].Judgment = 0;
            PushStack(x, TopStack(x) + 1);
            k++;
            continue;
        }
        else if (map[TopStack(x) + n].Judgment == 0 && TopStack(x) + n < (n*n - 1))
        {
            map[x->stack[k - 1]].Judgment = 0;
            PushStack(x, TopStack(x) + n);
            k++;
            continue;
        }
        else if (map[TopStack(x) - 1].Judgment == 0)
        {
            map[x->stack[k - 1]].Judgment = 0;
            PushStack(x, TopStack(x) - 1);
            k++;
            continue;
        }
        else if (map[TopStack(x) - n].Judgment == 0 && TopStack(x) - n > 0)
        {
            map[x->stack[k - 1]].Judgment = 0;
            PushStack(x, TopStack(x) - n);
            k++;
            continue;
        }
        else if (TopStack(x) == n * n - 2)
        {
            map[x->stack[k - 1]].Judgment = 0;
            while (EmptyStack(x))
            {
                PushStack(v, TopStack(x));
                PopStack(x);
            }
            DestroyStack(x);
            return v;
        }
        else
        {
            map[TopStack(x)].Judgment = 1;
            PopStack(x);
            map[TopStack(x)].Judgment = 0;
            k--;
        }
    }
}

void picture_one(Coordinate *map, int n)      //画迷宫的函数，map为指向储存迷宫数组的指针，n为迷宫大小
{
    // 初始化图形模式
    initgraph(n*10, n*10);

    //画图，黑色为墙，白色为通路
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            if (map[n * x + y].Judgment == 0) {
                setfillcolor(WHITE);
                solidrectangle(x * 10, y * 10, x * 10 + 10, y * 10 + 10);
            }
            else
            {
                //Sleep(10);
                setfillcolor(BLACK);
                solidrectangle(x * 10, y * 10, x * 10 + 10, y * 10 + 10);
            }
        }
    }

    getchar();              // 按任意键继续
}

void picture_two(Stack *s,int n)  //画迷宫路径的函数，s为储存迷宫路径的函数，n为迷宫大小
{
    int num;
    int x, y;
    setfillcolor(RED);   //颜色
    while (EmptyStack(s))
    {
        num = TopStack(s);
        PopStack(s);
        x = num / n;
        y = num % n;
        solidrectangle(x * 10, y * 10, x * 10 + 10, y * 10 + 10);  //画矩阵
        Sleep(10);
    }
    getchar();         //按任意键继续
    closegraph();      //关闭幕布
}

int main()
{
    int n = 2;
    int b;
    while (n % 2 == 0)
    {
        cout << "请输入迷宫大小（大小为奇数）：";
        cin >> n;
        cout << endl;
    }

    Coordinate*s = NULL;
    while (s == NULL)
        s = new Coordinate[n*n];

    cout << "1:深度遍历" << endl;
    cout << "2：prim算法" << endl;
    cin >> b;

    switch (b)
    {
    case 1:CreateMap(s, n); break;
    case 2:PrimeMap(s, n); break;
    }
    cin.ignore();

    picture_one(s, n);
    Stack *Q = Pathfinding(s, n);
    picture_two(Q, n);
    delete s;
    DestroyStack(Q);
    return 0;
}
#endif
#include <QDesktopServices>
void MazeWindow::on_pushButton_2_clicked()
{
    if(ha!=NULL)
    {
        ha->deleteLater();
    }
    ha=new HistoryAudio;
    ha->show();
}

void MazeWindow::on_pushButton_3_clicked()
{
    if(hp!=NULL)
    {
        hp->deleteLater();
    }
    hp=new help;
    hp->show();
}
