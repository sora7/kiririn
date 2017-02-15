#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>

#include "loader.h"
#include "grabber.h"
#include "parsers/sankakuparser.h"
#include "items/job.h"

#include <QMainWindow>

using namespace std;

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
    void startButtonHandler();
    void stopButtonHandler();
    void contButtonHandler();

private:
    Job getJobSettings();

    Ui::MainWindow *ui;
    Grabber grabber;

    void bindHandlers();

    void test();
};

#endif // MAINWINDOW_H
