#include "mainwindow.h"
#include <QAction>
#include <QDockWidget>
#include <QMenuBar>
#include <QMessageBox>
#include <QToolBar>
#include <QLayout>
#include <QOpenGLWidget>
#include <QToolButton>
#include <QHeaderView>
#include <QScrollArea>
#include <QLabel>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle( "Hello Widget" );

    QMenu *file = menuBar()->addMenu(tr("&File"));
    QMenu *view = menuBar()->addMenu(tr("&View"));
    QToolBar *toolBar = addToolBar(tr(""));

    auto addFolderButton = new QToolButton(toolBar);
    addFolderButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    addFolderAction = new QAction( QIcon("resources/icons/folder1.bmp"), tr("&Add Folder"), this );
    addFolderAction->setIconText("Add Folder");
    addFolderButton->setDefaultAction(addFolderAction);
    connect(addFolderAction, SIGNAL(triggered()), this, SLOT(on_actAddFolder_triggered()));
    toolBar->addWidget( addFolderButton );

    auto addFileButton = new QToolButton(toolBar);
    addFileButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    addFileAction = new QAction( QIcon("resources/icons/824.bmp"), tr("&Add File"), this );
    addFileAction->setIconText("Add File");
    addFileButton->setDefaultAction(addFileAction);
    connect(addFileAction, SIGNAL(triggered()), this, SLOT(on_actAddFile_triggered()));
    toolBar->addWidget( addFileButton );

    auto deleteButton = new QToolButton(toolBar);
    deleteButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    deleteAction = new QAction( QIcon("resources/icons/delete1.bmp"), tr("&Delete"), this );
    deleteAction->setIconText("Delete");
    deleteButton->setDefaultAction(deleteAction);
    toolBar->addWidget( deleteButton );

    auto scanButton = new QToolButton(toolBar);
    scanButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    scanAction = new QAction( QIcon("resources/icons/fold.bmp"), tr("&Scan"), this );
    scanAction->setIconText("Scan");
    scanButton->setDefaultAction(scanAction);
    toolBar->addWidget( scanButton );

    auto zoomInButton = new QToolButton(toolBar);
    zoomInButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    zoomInAction = new QAction( QIcon("resources/icons/418.bmp"), tr("&Zoom In"), this );
    zoomInAction->setIconText("Zoom In");
    zoomInButton->setDefaultAction(zoomInAction);
    toolBar->addWidget( zoomInButton );

    auto zoomOutButton = new QToolButton(toolBar);
    zoomOutButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    zoomOutAction = new QAction( QIcon("resources/icons/418.bmp"), tr("&Zoom Out"), this );
    zoomOutAction->setIconText("Zoom Out");
    zoomOutButton->setDefaultAction(zoomOutAction);
    toolBar->addWidget( zoomOutButton );

    auto zoomRealButton = new QToolButton(toolBar);
    zoomRealButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    zoomRealAction = new QAction( QIcon("resources/icons/414.bmp"), tr("&Real Size"), this );
    zoomRealAction->setIconText("Real Size");
    zoomRealButton->setDefaultAction(zoomRealAction);
    toolBar->addWidget( zoomRealButton );

    auto fitHeightButton = new QToolButton(toolBar);
    fitHeightButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    fitHeightAction = new QAction( QIcon("resources/icons/422.bmp"), tr("&Fit Height"), this );
    fitHeightAction->setIconText("Fit Height");
    fitHeightButton->setDefaultAction(fitHeightAction);
    toolBar->addWidget( fitHeightButton );

    auto fitWidthButton = new QToolButton(toolBar);
    fitWidthButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    fitWidthAction = new QAction( QIcon("resources/icons/424.bmp"), tr("&Fit Width"), this );
    fitWidthAction->setIconText("Fit Width");
    fitWidthButton->setDefaultAction(fitWidthAction);
    toolBar->addWidget( fitWidthButton );

    auto quitButton = new QToolButton(toolBar);
    quitButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    quitAction = new QAction( QIcon("resources/icons/exit.bmp"), tr("Quit"), this );
    quitAction->setIconText("Quit");
    quitButton->setDefaultAction(quitAction);
    toolBar->addWidget( quitButton );


    QDockWidget* dock = new QDockWidget("Contents Table", this);
    this->addDockWidget( Qt::LeftDockWidgetArea, dock, Qt::Vertical );
    dock->setAllowedAreas( Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea );
    QScrollArea *centralWidget = new QScrollArea(this);
    QLabel *imageLabel = new QLabel;
    centralWidget->setWidget(imageLabel);
    setCentralWidget(centralWidget);

    tree = new QTreeWidget( this );
    tree->setColumnCount(2);
    tree->setHeaderLabels(QStringList()<<"item"<<"type");
    tree->header()->setDefaultAlignment(Qt::AlignCenter);
    dock->setWidget(tree);

    //QTreeWidgetItem *root = new QTreeWidgetItem(tree);
    //root->setText(0, "root");
    //root->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    //root->setCheckState(0, Qt::Unchecked);

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
    QIcon icon("resources/icons/open3.bmp");
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
        QIcon icon("resources/icons/31.ico");
        item->setIcon(colItem, icon);
        item->setText(colItem, str);
        item->setText(colItemType, "type:imageFile");

        item->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsAutoTristate|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        item->setCheckState(colItem, Qt::Unchecked);
        item->setData(colItem, Qt::UserRole, file);

        parentItem->addChild(item);
    }
}

MainWindow::~MainWindow()
{
}
