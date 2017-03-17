#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include <fstream>

#include "boorutest.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->comboBox_site->addItem("Sankaku Channel",   QVariant("sankaku"));
    ui->comboBox_site->addItem("Idol Complex",      QVariant("idol"));
    ui->comboBox_site->addItem("Konachan",          QVariant("konachan"));
    ui->comboBox_site->addItem("Mishimmie",         QVariant("katawa"));
    ui->comboBox_site->addItem("4chan House",       QVariant("4chan"));

//    ui->comboBox_site->addItem("Yande.re", QVariant("yande.re"));
//    ui->comboBox_site->addItem("Safebooru", QVariant("safebooru"));
//    ui->comboBox_site->addItem("Danbooru", QVariant("danbooru"));

    ui->tableView_job->setModel(this->grabber.jobModel());
    ui->tableView_job->verticalHeader()->hide();
    ui->tableView_job->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_job->hideColumn(0);

    bindHandlers();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startButtonHandler()
{
    Job newJob = this->getJobSettings();
    this->grabber.startNewJob(newJob);
}

void MainWindow::stopButtonHandler()
{
    test();
}

void MainWindow::contButtonHandler()
{
    this->grabber.contLastJob();
}

Job MainWindow::getJobSettings()
{
    Job job;

    job.setSite(ui->comboBox_site->itemData(
                    ui->comboBox_site->currentIndex()).toString()
                );
    job.setTags(ui->lineEdit_tags->text().split(" "));
    job.setSavePath(ui->lineEdit_savepath->text());

    if (ui->checkBox_rt_safe->isChecked()) {
        job.addRating(SAFE);
    }
    if (ui->checkBox_rt_questionable->isChecked()) {
        job.addRating(QUESTIONABLE);
    }
    if (ui->checkBox_rt_explicit->isChecked()) {
        job.addRating(EXPLICIT);
    }
    if (ui->checkBox_rt_OTHER->isChecked()) {
        job.addRating(RT_OTHER);
    }

    if (ui->checkBox_pt_original->isChecked()) {
        job.addType(ORIGINAL);
    }

    if (ui->checkBox_pt_resized->isChecked()) {
        job.addType(RESIZED);
    }


    if (ui->checkBox_ft_jpg->isChecked()) {
        job.addFormat(JPG);
    }
    if (ui->checkBox_ft_png->isChecked()) {
        job.addFormat(PNG);
    }
    if (ui->checkBox_ft_gif->isChecked()) {
        job.addFormat(GIF);
    }
    if (ui->checkBox_ft_webm->isChecked()) {
        job.addFormat(WEBM);
    }
    if (ui->checkBox_ft_mp4->isChecked()) {
        job.addFormat(MP4);
    }
    cout << job << endl;
    return job;
}


void MainWindow::bindHandlers()
{
    connect(ui->pushButton_START,    SIGNAL(clicked()), this,
            SLOT(startButtonHandler()));
    connect(ui->pushButton_STOP,     SIGNAL(clicked()), this,
            SLOT(stopButtonHandler()));
    connect(ui->pushButton_CONTINUE, SIGNAL(clicked()), this,
            SLOT(contButtonHandler()));
}

void MainWindow::test()
{
    BooruTest tester;
    tester.testing();
}
