#include "mainwindow.h"
#include <QAction>
#include <QDockWidget>
#include <QMenuBar>
#include <QMessageBox>
#include <QToolBar>
#include <QStatusBar>
#include <QLayout>
#include <QOpenGLWidget>
#include <QToolButton>
#include <QHeaderView>
#include <QScrollArea>
#include <QFileDialog>
#include <QImage>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle( "Hello Widget" );

    QMenu *file = menuBar()->addMenu(tr("&File"));
    QMenu *view = menuBar()->addMenu(tr("&View"));
    QToolBar *toolBar = addToolBar(tr(""));
    labelFilename = new QLabel;
    this->statusBar()->addWidget(labelFilename);

    auto addFolderButton = new QToolButton(toolBar);
    addFolderButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    addFolderAction = new QAction( QIcon(":/icons/folder1.bmp"), tr("&Add Folder"), this );
    addFolderAction->setIconText("Add Folder");
    addFolderButton->setDefaultAction(addFolderAction);
    connect(addFolderAction, SIGNAL(triggered()), this, SLOT(on_actAddFolder_triggered()));
    toolBar->addWidget( addFolderButton );

    auto addFileButton = new QToolButton(toolBar);
    addFileButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    addFileAction = new QAction( QIcon(":/icons/824.bmp"), tr("&Add File"), this );
    addFileAction->setIconText("Add File");
    addFileButton->setDefaultAction(addFileAction);
    connect(addFileAction, SIGNAL(triggered()), this, SLOT(on_actAddFile_triggered()));
    toolBar->addWidget( addFileButton );

    auto deleteButton = new QToolButton(toolBar);
    deleteButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    deleteAction = new QAction( QIcon(":/icons/delete1.bmp"), tr("&Delete"), this );
    deleteAction->setIconText("Delete");
    deleteButton->setDefaultAction(deleteAction);
    toolBar->addWidget( deleteButton );

    auto scanButton = new QToolButton(toolBar);
    scanButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    scanAction = new QAction( QIcon(":/icons/fold.bmp"), tr("&Scan"), this );
    scanAction->setIconText("Scan");
    scanButton->setDefaultAction(scanAction);
    toolBar->addWidget( scanButton );

    auto zoomInButton = new QToolButton(toolBar);
    zoomInButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    zoomInAction = new QAction( QIcon(":/icons/418.bmp"), tr("&Zoom In"), this );
    zoomInAction->setIconText("Zoom In");
    zoomInButton->setDefaultAction(zoomInAction);
    toolBar->addWidget( zoomInButton );

    auto zoomOutButton = new QToolButton(toolBar);
    zoomOutButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    zoomOutAction = new QAction( QIcon(":/icons/418.bmp"), tr("&Zoom Out"), this );
    zoomOutAction->setIconText("Zoom Out");
    zoomOutButton->setDefaultAction(zoomOutAction);
    toolBar->addWidget( zoomOutButton );

    auto zoomRealButton = new QToolButton(toolBar);
    zoomRealButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    zoomRealAction = new QAction( QIcon(":/icons/414.bmp"), tr("&Real Size"), this );
    zoomRealAction->setIconText("Real Size");
    zoomRealButton->setDefaultAction(zoomRealAction);
    toolBar->addWidget( zoomRealButton );

    auto fitHeightButton = new QToolButton(toolBar);
    fitHeightButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    fitHeightAction = new QAction( QIcon(":/icons/422.bmp"), tr("&Fit Height"), this );
    fitHeightAction->setIconText("Fit Height");
    fitHeightButton->setDefaultAction(fitHeightAction);
    toolBar->addWidget( fitHeightButton );

    auto fitWidthButton = new QToolButton(toolBar);
    fitWidthButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    fitWidthAction = new QAction( QIcon(":/icons/424.bmp"), tr("&Fit Width"), this );
    fitWidthAction->setIconText("Fit Width");
    fitWidthButton->setDefaultAction(fitWidthAction);
    toolBar->addWidget( fitWidthButton );

    auto quitButton = new QToolButton(toolBar);
    quitButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    quitAction = new QAction( QIcon(":/icons/exit.bmp"), tr("Quit"), this );
    quitAction->setIconText("Quit");
    quitButton->setDefaultAction(quitAction);
    toolBar->addWidget( quitButton );


    QDockWidget* dock = new QDockWidget("Contents Table", this);
    this->addDockWidget( Qt::LeftDockWidgetArea, dock, Qt::Vertical );
    dock->setAllowedAreas( Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea );
    imageLabel = new QLabel;
    centralWidget = new QScrollArea;
    centralWidget->setWidget(imageLabel);
    setCentralWidget(centralWidget);

    tree = new QTreeWidget(dock);
    tree->setColumnCount(2);
    tree->setHeaderLabels(QStringList()<<"item"<<"type");
    tree->header()->setDefaultAlignment(Qt::AlignCenter);
    connect(tree, SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)),
            this, SLOT(on_treeFiles_currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)));
    dock->setWidget(tree);

    //QTreeWidgetItem *root = new QTreeWidgetItem(tree, itTopItem);
    //root->setText(0, "New Item");
    //root->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);

    //QTreeWidgetItem *item = new QTreeWidgetItem(root);
    //item->setText(0, "item");
    //item->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    //item->setCheckState(0, Qt::Unchecked);

    //QVBoxLayout *layout = new QVBoxLayout;
    //layout->addWidget( tree );
    //dock->setLayout( layout );
}

void MainWindow::on_actAddFolder_triggered()
{
    QString fullname = QFileDialog::getExistingDirectory();
    if( fullname.isEmpty() ) return;
    QString dir = fullname.right( fullname.length() - fullname.lastIndexOf('/') - 1 );
    QTreeWidgetItem *parentItem = tree->currentItem();
    if(!parentItem)
    {
        parentItem = tree->invisibleRootItem();
    }
    QTreeWidgetItem *curItem = new QTreeWidgetItem(parentItem, itGroupItem);
    QIcon icon(":/icons/open3.bmp");
    curItem->setIcon(colItem, icon);
    curItem->setText(colItem, dir);
    curItem->setText(colItemType, "type:group");

    curItem->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsAutoTristate|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    curItem->setCheckState(colItem, Qt::Unchecked);
}

void MainWindow::on_actAddFile_triggered()
{
    QStringList files = QFileDialog::getOpenFileNames( this, "", "", "*.jpg" );

    QTreeWidgetItem *parentItem;
    QTreeWidgetItem *curItem = tree->currentItem();
    if( curItem->type() == itImageItem )
    {
        parentItem = curItem->parent();
    }
    else
    {
        parentItem = curItem;
    }
    if( parentItem == nullptr )
        return;
    foreach(auto file, files )
    {
        QTreeWidgetItem *item = new QTreeWidgetItem(parentItem, itImageItem);
        QString str = file.right( file.length() - file.lastIndexOf('/') - 1 );
        QIcon icon(":/icons/31.ico");
        item->setIcon(colItem, icon);
        item->setText(colItem, str);
        item->setText(colItemType, "type:imageFile");

        item->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsAutoTristate|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        item->setCheckState(colItem, Qt::Unchecked);
        item->setData(colItem, Qt::UserRole, file);

        parentItem->addChild(item);
    }
}

void MainWindow::on_treeFiles_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    //当前节点选择变化时触发
    Q_UNUSED(previous);

    if  (current==NULL)
        return;

    int var=current->type();//节点的类型

    switch(var)
    {
        case  itTopItem: //顶层节点
          this->addFolderAction->setEnabled(true);
          this->addFileAction->setEnabled(true);
          this->deleteAction->setEnabled(false);    //顶层节点不能删除
          break;

        case  itGroupItem: //文件组节点
          this->addFolderAction->setEnabled(true);
          this->addFileAction->setEnabled(true);
          this->deleteAction->setEnabled(true);    //顶层节点不能删除
          break;

        case  itImageItem: //图片文件节点
          this->addFolderAction->setEnabled(false);
          this->addFileAction->setEnabled(true);
          this->deleteAction->setEnabled(true);    //顶层节点不能删除
          displayImage(current); //显示图片
          break;
    }
}

void MainWindow::displayImage(QTreeWidgetItem* item)
{
    QString fileName = item->data(colItem, Qt::UserRole).toString();
    labelFilename->setText(fileName);
    curPixmap.load(fileName);

    int w = centralWidget->width();//得到scrollArea的高度
    int realw = curPixmap.width();//原始图片的实际宽度
    float pixRatio = float( w ) / realw;

    QPixmap pix = curPixmap.scaledToWidth( w );
    imageLabel->setPixmap(curPixmap);
}

MainWindow::~MainWindow()
{
}
