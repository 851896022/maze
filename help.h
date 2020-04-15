#ifndef HELP_H
#define HELP_H

#include <QFrame>

namespace Ui {
class help;
}

class help : public QFrame
{
    Q_OBJECT

public:
    explicit help(QWidget *parent = 0);
    ~help();

private:
    Ui::help *ui;
};

#endif // HELP_H
