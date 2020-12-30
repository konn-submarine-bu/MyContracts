#include "add.h"
#include "ui_add.h"
#include<QPushButton>
#include<QFile>
#include<QtXml/QDomDocument>
#include<QTextStream>

add::add(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::add)
{
    ui->setupUi(this);
    connect(ui->pushButton_add, &QPushButton::released,
            [=]()
            {
                emit addDup(ui->lineEdit_num->text());
                QFile file("students.xml");
                if(!file.open(QFile::ReadOnly))return;

                QDomDocument doc;
                if(!doc.setContent(&file))
                {
                    file.close();
                    return;
                }
                file.close();

                QDomElement root=doc.documentElement();
                QDomElement student=doc.createElement("student");
                QDomText text;

                QDomElement number=doc.createElement("number");
                text=doc.createTextNode(ui->lineEdit_num->text());
                number.appendChild(text);
                student.appendChild(number);

                QDomElement name=doc.createElement("name");
                text=doc.createTextNode(ui->lineEdit_name->text());
                name.appendChild(text);
                student.appendChild(name);

                QDomElement sex=doc.createElement("sex");
                text=doc.createTextNode(ui->radioButton_female->isChecked()? "女" : (ui->radioButton_male->isChecked()? "男":""));
                sex.appendChild(text);
                student.appendChild(sex);

                QDomElement age=doc.createElement("age");
                text=doc.createTextNode(ui->lineEdit_age->text());
                age.appendChild(text);
                student.appendChild(age);

                QDomElement tel=doc.createElement("tel");
                text=doc.createTextNode(ui->lineEdit_tel->text());
                tel.appendChild(text);
                student.appendChild(tel);

                QDomElement major=doc.createElement("major");
                text=doc.createTextNode(ui->comboBox_major->currentText());
                major.appendChild(text);
                student.appendChild(major);

                root.appendChild(student);
                if(!file.open(QFile::WriteOnly|QFile::Truncate)) return;
                QTextStream out_stream(&file);
                doc.save(out_stream,4);
                file.close();

                emit addOver();
                ui->lineEdit_num->clear();
                ui->lineEdit_name->clear();
                ui->radioButton_male->setChecked(1);
                ui->lineEdit_age->clear();
                ui->lineEdit_tel->clear();
                ui->comboBox_major->setCurrentIndex(0);
                this->close();

            }
            );
    connect(ui->pushButton_close, &QPushButton::released,
            [=]()
            {
                ui->lineEdit_num->clear();
                ui->lineEdit_name->clear();
                ui->radioButton_male->setChecked(1);
                ui->lineEdit_age->clear();
                ui->lineEdit_tel->clear();
                ui->comboBox_major->setCurrentIndex(0);
                this->close();
            }
            );
}

add::~add()
{
    delete ui;
}

