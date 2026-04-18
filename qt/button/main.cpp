#include "widget.h"

#include <QApplication>
#include <QDebug>
#include <QPushButton>
#include <QBoxLayout>
#include <QString>
#include <QList>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    QHBoxLayout layout;
    /* w.show();
    w.resize(200, 200);
    qDebug() << w.geometry(); */

    //staticka tlacitka
    /*QPushButton b1("jedna", &w), b2 ("dva", &w);
    layout.addWidget(&b1);
    layout.addWidget(&b2);
    w.setLayout(&layout);
    w.show();*/

    QPushButton *b;
    QList <QString> barvy;

    barvy << "red" << "navy" << "white" << "olive" << "maroon" << "cyan";

    //dynamicka tlacitka
    for (int i = 0; i < 10; i++){
        //layout.addWidget(new QPushButton(QString("%1").arg(i+1)));

        b = new QPushButton(QString("%1").arg(i+1));
        // konstantní barva:
        //b->setStyleSheet("background: red;");
        //layout.addWidget(b);

        //dynamická barva
        b->setStyleSheet(QString("background: %1").arg(barvy[i%6]));
        layout.addWidget(b);
    }
    w.setLayout(&layout);
    w.show();

    return QCoreApplication::exec();
}


