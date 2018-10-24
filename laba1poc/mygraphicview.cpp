#include "mygraphicview.h"

MyGraphicView::MyGraphicView(QWidget *parent)
    : QGraphicsView(parent)   // вызов родительского конструктора
{
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключим скроллбар по горизонтали
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // Отключим скроллбар по вертикали
    this->setAlignment(Qt::AlignCenter);                        // Делаем привязку содержимого к центру
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);    // Растягиваем содержимое по виджету


    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, this->width(), this->height());
    this->setScene(scene);

    status = 0;  // рисовать нельзя, пока не выбрана фигура
}

MyGraphicView::~MyGraphicView()
{
}


void MyGraphicView::mousePressEvent(QMouseEvent *event)
{
    if (status == 0)
        return;

    QPointF pos = this->mapToScene(event->pos().x(), event->pos().y());
    //qDebug() << pos.x() << pos.y();

    if (status == 1)
        scene->addEllipse(pos.x() - 8, pos.y() - 8, 20, 20);   // 8 потому что по умолчанию рисует не на кончике курсора
    else
        if (status == 2)
            scene->addEllipse(pos.x() - 18, pos.y() - 8, 40, 20);

}

void MyGraphicView::treeClicked(const QModelIndex &index)
{
    QVariant name = index.data();
    // qDebug() << name.toString();

    if (name.toString() == "figure")
        status = 0;
    else
        if (name.toString() == "circle")
            status = 1;
    else
        if (name.toString() == "ellipse")
            status = 2;
}
