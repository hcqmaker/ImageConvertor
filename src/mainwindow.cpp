#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMimeData>
#include <QAction>
#include <QPixmap>
#include <QStringList>
#include <QDebug>
#include <QFileInfo>


MyGraphicsView::MyGraphicsView(QWidget *parent): QGraphicsView(parent)
{
    mScene = new QGraphicsScene(parent);
    this->setScene(mScene);
    mItem = NULL;

    QPixmap tmp(200, 200);
    tmp.fill();

    setImage(tmp);
}

MyGraphicsView::~MyGraphicsView(){}


//--------------------------------------------------------------------
//
void MyGraphicsView::dragEnterEvent(QDragEnterEvent * event)
{
    //QStringList tmpList = event->mimeData()->formats();
    if(event->mimeData()->hasFormat("text/uri-list")) {
            event->acceptProposedAction();
    }
}

//--------------------------------------------------------------------
//
void MyGraphicsView::dropEvent(QDropEvent *event)
{
    const QMimeData *tmpData = event->mimeData();
    if (tmpData && tmpData->urls().size() > 0){
        QUrl tmpURL = tmpData->urls().at(0);
        setImage(tmpURL.toLocalFile());
    }
}


void MyGraphicsView::setImage(const QString& url)
{
    mUrl = url;
    QPixmap tmppixmap(mUrl);
    setImage(tmppixmap);
}

void MyGraphicsView::setImage(const QPixmap& img)
{
    mScene->setSceneRect(0, 0, img.width(), img.height());
    if (mItem){
        mScene->removeItem(mItem);
        delete mItem;
        mItem = NULL;
    }
    mItem = mScene->addPixmap(img);
    mItem->setAcceptDrops(true);
}

const QString MyGraphicsView::getImage()
{
    return mUrl;
}

//==================================================
//
//==================================================

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //mView = new MyGraphicsView(ui->centralWidget);
    mView = new MyGraphicsView();
    ui->verticalLayout->addWidget(mView);
    mView->setAcceptDrops(true);
    mPath = QApplication::applicationDirPath();
    QObject::connect(ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(handlerOpenFile(bool)));
    QObject::connect(ui->actionSaveas, SIGNAL(triggered(bool)), this, SLOT(handlerSaveAs(bool)));
}


MainWindow::~MainWindow()
{
    delete ui;
}


//--------------------------------------------------------------------
//
void MainWindow::handlerOpenFile(bool l)
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), mPath, tr("Image Files (*.*)"));

    QFileInfo tmpFileInfo(fileName);
    mPath = tmpFileInfo.absoluteFilePath();

    mView->setImage(fileName);
}

//--------------------------------------------------------------------
//
void MainWindow::handlerSaveAs(bool b)
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Open Image"), mPath, tr("Image Files (*.*)"));
    QString fpath = mView->getImage();
    QPixmap tmp(fpath);
    tmp.save(filename);
}
