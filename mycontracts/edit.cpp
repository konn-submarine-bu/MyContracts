#include "edit.h"
#include "ui_edit.h"
#include<QPushButton>
#include<QFile>
#include<QtXml/QDomDocument>
#include<QTextStream>

edit::edit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::edit)
{
    ui->setupUi(this);
    connect(ui->pushButton_edit, &QPushButton::released,
            [=]()
            {
                emit editDup(ui->lineEdit_num->text());
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

                emit editOver(ui->lineEdit_num->text());
                this->close();

            }
            );
    connect(ui->pushButton_close, &QPushButton::released, this, &edit::close);
}

edit::~edit()
{
    delete ui;
}

void edit::setNum(QString num)
{
    ui->lineEdit_num->setText(num);
}
void edit::setName(QString name)
{
    ui->lineEdit_name->setText(name);
}
void edit::setSex(QString sex)
{
    if(sex=="男") ui->radioButton_male->setChecked(1);
    if(sex=="女") ui->radioButton_female->setChecked(1);
}
void edit::setAge(QString age)
{
    ui->lineEdit_age->setText(age);
}
void edit::setTel(QString tel)
{
    ui->lineEdit_tel->setText(tel);
}
void edit::setMajor(QString major)
{
     if(major=="信息安全") ui->comboBox_major->setCurrentIndex(1);
     else if(major=="大数据技术") ui->comboBox_major->setCurrentIndex(2);
     else if(major=="电子信息科学与技术") ui->comboBox_major->setCurrentIndex(3);
     else ui->comboBox_major->setCurrentIndex(0);
}
