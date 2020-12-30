#ifndef EDIT_H
#define EDIT_H

#include <QWidget>

namespace Ui {
class edit;
}

class edit : public QWidget
{
    Q_OBJECT

public:
    explicit edit(QWidget *parent = nullptr);
    ~edit();
    void setNum(QString);
    void setName(QString);
    void setSex(QString);
    void setAge(QString);
    void setTel(QString);
    void setMajor(QString);

signals:
    void editDup(QString);
    void editOver(QString num);

private:
    Ui::edit *ui;
};

#endif // EDIT_H
