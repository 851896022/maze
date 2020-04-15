#ifndef MAZEWINDOW_H
#define MAZEWINDOW_H

#include <QMainWindow>
#include <QStack>
#include <QPainter>
#include <QDebug>
#include <QLabel>
#include <QKeyEvent>
#include <QMessageBox>
#include <QDateTime>
#include <QTcpSocket>
#include "historyaudio.h"
#include "help.h"
namespace Ui {
class MazeWindow;
}
struct Coordinate  //迷宫点类
{
    bool Judgment = 1;   //判断是否为墙，1为是，0为不是
    bool Judgemet_2 = 0;  //prim算法用到，深度优先算法没用
};
struct Coordinated  //prim算法用到，深度优先算法没用
{
    int adress;
};
class MazeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MazeWindow(QWidget *parent = 0);
    ~MazeWindow();
    int countN=5;
    //Point *s;
    //QStack <int> s;
    QDateTime startTime;
    QDateTime endTime;
private slots:
    void on_pushButton_clicked();
    void keyPressEvent(QKeyEvent *event);
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

public slots:
    void Sequence(Coordinated *Arry, int n, int &sum);   //把元素从数组删除
    void Store(Coordinated *map_1, Coordinate *map_2, int map, int &k, int n);     //把元素储存进数组
    void PrimeMap(Coordinate *map, int n);
    void draw(Coordinate *map, int n);

private:
    Ui::MazeWindow *ui;
    QWidget *l[99][99];
    bool mapBool[99][99];
    int addressX=0;
    int addressY=0;
    int targetX=0;
    int targetY=0;
    bool isWork = false;
    int type = 0;
    HistoryAudio *ha=NULL;
    help *hp=NULL;
};

#endif // MAZEWINDOW_H
