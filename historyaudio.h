#ifndef HISTORYAUDIO_H
#define HISTORYAUDIO_H

#include <QFrame>
//#include <QtWebEngineWidgets>
#include <QVBoxLayout>
#include <ActiveQt/QAxWidget>
//#include "data/global.h"
namespace Ui {
class HistoryAudio;
}

class HistoryAudio : public QFrame
{
    Q_OBJECT

public:
    explicit HistoryAudio(QWidget *parent = 0);
    ~HistoryAudio();
    //QWebEngineView webView;
    //QVBoxLayout vBox;
private:
    Ui::HistoryAudio *ui;
};

#endif // HISTORYAUDIO_H
