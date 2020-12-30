#include "widget.h"
#include "ui_widget.h"
#include<QPushButton>
#include<QFile>
#include<QtXml/QDomDocument>
#include<QTextStream>
#include<QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("学生通讯录");
    QStringList headers;
    headers<<"学号"<<"姓名"<<"性别"<<"年龄"<<"手机"<<"专业";
    ui->treeWidget->setHeaderLabels(headers);
    ui->treeWidget->clear();
    ui->pushButton_allStu->hide();
    readXml();

    connect(ui->pushButton_add, &QPushButton::released,
            [=]()
            {
                a.show();
                a.setWindowTitle("添加学生");
            }
            );
    connect(&a, &add::addOver,
            [=]()
            {
                ui->treeWidget->clear();
                readXml();
            }
            );
    connect(&e, &edit::editOver, this, &Widget::dealEditOver);
    connect(&a, &add::addDup, this, &Widget::removeXml);
    connect(&e, &edit::editDup, this, &Widget::removeXml);
    connect(ui->pushButton_delete, &QPushButton::released,
            [=]()
            {
                if(ui->treeWidget->currentItem())
                {
                    QString num=ui->treeWidget->currentItem()->text(0);
                    removeXml(num);
                    ui->treeWidget->clear();
                    readXml();
                }
            }
            );
    connect(ui->pushButton_edit, &QPushButton::released,
            [=]()
            {
                if(ui->treeWidget->currentItem())
                {
                    e.show();
                    e.setWindowTitle("修改学生");
                    e.setNum(ui->treeWidget->currentItem()->text(0));
                    e.setName(ui->treeWidget->currentItem()->text(1));
                    e.setSex(ui->treeWidget->currentItem()->text(2));
                    e.setAge(ui->treeWidget->currentItem()->text(3));
                    e.setTel(ui->treeWidget->currentItem()->text(4));
                    e.setMajor(ui->treeWidget->currentItem()->text(5));
                }
            }
            );
    connect(ui->pushButton_search, &QPushButton::released,
            [=]()
            {
                s.show();
            }
            );
    connect(&s, &search::find, this, &Widget::findXml);
    connect(&s, &search::allStu,
            [=]()
            {
                ui->pushButton_allStu->show();
            }
            );
    connect(ui->pushButton_allStu, &QPushButton::released,
            [=]()
            {
                ui->treeWidget->clear();
                readXml();
                ui->pushButton_allStu->hide();
            }
            );

}

Widget::~Widget()
{
    delete ui;
}

void Widget::readXml()
{
        QFile file("students.xml");
        if(!file.open(QFile::ReadOnly))
            return;

        QDomDocument doc;
        if(!doc.setContent(&file))
        {
            file.close();
            return;
        }
        file.close();

        QDomElement root=doc.documentElement(); //返回根节点
        QDomNode node=root.firstChild(); //获得第一个子节点
        while(!node.isNull())  //如果节点不空
        {
            QList<QTreeWidgetItem*> items;
            QTreeWidgetItem* item=new QTreeWidgetItem;
            if(node.isElement()) //如果节点是元素
            {
                QDomElement e=node.toElement(); //转换为元素，注意元素和节点是两个数据结构，其实差不多
                QDomNodeList list=e.childNodes();
                for(int i=0;i<list.count();i++) //遍历子元素，count和size都可以用,可用于标签数计数
                {
                    QDomNode n=list.at(i);
                    if(node.isElement())
                    {
                        item->setText(i,n.toElement().text());
                    }
                }
            }
            items.append(item);
            ui->treeWidget->insertTopLevelItems(0,items);
            node=node.nextSibling(); //下一个兄弟节点,nextSiblingElement()是下一个兄弟元素，都差不多
        }

}

void Widget::removeXml(QString num)
{
        QFile file("students.xml");
        if(!file.open(QFile::ReadOnly))
            return;

        //删除一个一级子节点及其元素，外层节点删除内层节点于此相同
        QDomDocument doc;
        if(!doc.setContent(&file))
        {
            file.close();
            return;
        }
        file.close();

        QDomElement root=doc.documentElement();
        QDomNodeList list=doc.elementsByTagName("student"); //由标签名定位
        for(int i=0;i<list.count();i++)
        {
            QDomElement e=list.at(i).toElement();
            if(e.firstChild().firstChild().nodeValue()==num)  //以学号定位
            {
                root.removeChild(list.at(i));
                break;
            }
        }

        if(!file.open(QFile::WriteOnly|QFile::Truncate))
            return;
        //输出到文件
        QTextStream out_stream(&file);
        doc.save(out_stream,4); //缩进4格
        file.close();
}

void Widget::dealEditOver(QString num)
{
    if(num!=ui->treeWidget->currentItem()->text(0)) e.emit editDup(ui->treeWidget->currentItem()->text(0));
    ui->treeWidget->clear();
    readXml();
}

void Widget::findXml(QString str)
{
    ui->treeWidget->clear();
    QFile file("students.xml");
    if(!file.open(QFile::ReadOnly))
        return;

    QDomDocument doc;
    if(!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();

    QDomElement root=doc.documentElement(); //返回根节点
    QDomNode node=root.firstChild(); //获得第一个子节点
    while(!node.isNull())  //如果节点不空
    {
        bool found=0;
        QList<QTreeWidgetItem*> items;
        QTreeWidgetItem* item=new QTreeWidgetItem;
        if(node.isElement()) //如果节点是元素
        {
            QDomElement e=node.toElement(); //转换为元素，注意元素和节点是两个数据结构，其实差不多
            QDomNodeList list=e.childNodes();
            for(int i=0;i<list.count();i++) //遍历子元素，count和size都可以用,可用于标签数计数
            {
                QDomNode n=list.at(i);
                if(node.isElement())
                {
                    item->setText(i,n.toElement().text());
                    if(n.toElement().text()==str) found=1;
                }
            }
        }
        if(found)
        {
            items.append(item);
            ui->treeWidget->insertTopLevelItems(0,items);
        }
        node=node.nextSibling(); //下一个兄弟节点,nextSiblingElement()是下一个兄弟元素，都差不多
    }
}


