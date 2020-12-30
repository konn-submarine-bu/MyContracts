#ifndef ADD_H
#define ADD_H

#include <QWidget>

namespace Ui {
class add;
}

class add : public QWidget
{
    Q_OBJECT

public:
    explicit add(QWidget *parent = nullptr);
    ~add();

private:
    Ui::add *ui;

signals:
    void addOver();
    void addDup(QString);
};

#endif // ADD_H
