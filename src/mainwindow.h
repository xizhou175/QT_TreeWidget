#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QMainWindow>
#include <QTreeWidget>
#include <QLabel>
#include <QDebug>
#include <iostream>
#include <QScrollArea>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    enum    treeItemType{itTopItem=1001,itGroupItem,itImageItem};

    //枚举类型，表示列号
    enum    treeColNum{colItem=0, colItemType=1}; //目录树列的编号定义
private:
    QTreeWidget* tree;
    QAction *addFolderAction;
    QAction *addFileAction;
    QAction *deleteAction;
    QAction *scanAction;
    QAction *zoomInAction;
    QAction *zoomOutAction;
    QAction *zoomRealAction;

    QAction *fitHeightAction;
    QAction *fitWidthAction;

    QAction *quitAction;

    QLabel *imageLabel;
    QLabel *labelFilename;
    QPixmap curPixmap;

    QScrollArea *centralWidget;

    void displayImage(QTreeWidgetItem*);

private slots:
    void on_treeFiles_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
    void on_actAddFolder_triggered();
    void on_actAddFile_triggered();
};

#endif // MAINWINDOW_H
