#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "add.h"
#include"edit.h"
#include"search.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void readXml();
    void findXml(QString);
    void removeXml(QString );
    void dealEditOver(QString);

private:
    Ui::Widget *ui;
    add a;
    edit e;
    search s;
};
#endif // WIDGET_H
