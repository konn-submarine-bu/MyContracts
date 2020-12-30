#include "search.h"
#include "ui_search.h"

search::search(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::search)
{
    ui->setupUi(this);
    this->setWindowTitle("查找学生信息");
    connect(ui->pushButton_search, &QPushButton::released,
            [=]()
            {     
                emit find(ui->lineEdit->text());
                ui->lineEdit->clear();
                emit allStu();
                this->close();
            }
            );
    connect(ui->pushButton_close_2, &QPushButton::released,
            [=]()
            {
                ui->lineEdit->clear();
                this->close();
            }
            );
}

search::~search()
{
    delete ui;
}
