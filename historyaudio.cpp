#include "historyaudio.h"
#include "ui_historyaudio.h"
#include <QSettings>
HistoryAudio::HistoryAudio(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::HistoryAudio)
{
    ui->setupUi(this);
    /*
    vBox.addWidget(&webView);
    this->setLayout(&vBox);
    webView.page()->profile()->clearHttpCache();
    webView.load(QString("http://html5test.com/"));
    //webView.load(QString("http://localhost:56879/"));
    */

        //()


    ui->axWidget->setControl(QString::fromUtf8("{8856F961-340A-11D0-A96B-00C04FD705A2}"));
    ui->axWidget->setFocusPolicy(Qt::StrongFocus);
    ui->axWidget->setProperty("DisplayAlerts",false);
    ui->axWidget->setProperty("DisplayScrollBars",true);






    QString url="http://n5012346.vicp.cc:9878/maze.html";

    ui->axWidget->dynamicCall("Navigate(const QString&)",url);
    this->setWindowTitle("查询排行榜");

}

HistoryAudio::~HistoryAudio()
{
    delete ui;
}
