#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>

#include "loader.h"
#include "grabber.h"
#include "items/job.h"
#include "boorutest.h"

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

    void onProgress();
    void onProgressMax(int max);

    void stageChange(GrabberStage stage);

    void logMessage(QString messageText);
private:
    Job getJobSettings();

    Ui::MainWindow *ui;
    Grabber* m_grabber;
    BooruTest* m_tester;

    void bindHandlers();

    void test();
    void defaults();
};

#endif // MAINWINDOW_H
