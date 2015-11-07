#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUrl>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPixmap>


class MyGraphicsView : public QGraphicsView
{
public:
    MyGraphicsView(QWidget * parent = 0);
    ~MyGraphicsView();

    void dragEnterEvent(QDragEnterEvent * event);
    void dropEvent(QDropEvent *event);

    void setImage(const QString& url);
    void setImage(const QPixmap& url);
    const QString getImage();
private:
    QGraphicsScene* mScene;
    QGraphicsItem* mItem;
    QString mUrl;
};


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void handlerOpenFile(bool b);
    void handlerSaveAs(bool b);

private:
    Ui::MainWindow *ui;
    QUrl mImageUrl;
    MyGraphicsView *mView;
    QString mPath;
};

#endif // MAINWINDOW_H
