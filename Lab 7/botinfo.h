#ifndef BOTINFO_H
#define BOTINFO_H

#include <QDialog>

#include "ui_botinfo.h"

#include <QTableWidgetItem>
#include "Bots.h"

namespace Ui {
class botInfo;
}

class botInfo : public QDialog
{
    Q_OBJECT

public:
    explicit botInfo(Bot& bot, QWidget *parent = nullptr);
    ~botInfo();

private:
    Ui::botInfo *ui;
};

#endif // BOTINFO_H
