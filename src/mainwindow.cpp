#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->progressChange(0, 0);

    ui->comboBox_site->addItem(sankaku::fullname,
                               QVariant(sankaku::shortname));
    ui->comboBox_site->addItem(idol::fullname,
                               QVariant(idol::shortname));
    ui->comboBox_site->addItem(konachan::fullname,
                               QVariant(konachan::shortname));
    ui->comboBox_site->addItem(yandere::fullname,
                               QVariant(yandere::shortname));
    ui->comboBox_site->addItem(danbooru::fullname,
                               QVariant(danbooru::shortname));
    ui->comboBox_site->addItem(gelbooru::fullname,
                               QVariant(gelbooru::shortname));
    ui->comboBox_site->addItem(safebooru::fullname,
                               QVariant(safebooru::shortname));
    ui->comboBox_site->addItem(katawa::fullname,
                               QVariant(katawa::shortname));
    ui->comboBox_site->addItem(fourchan::fullname,
                               QVariant(fourchan::shortname));

//    ui->comboBox_site->addItem("Sankaku Channel",   QVariant("sankaku"));
//    ui->comboBox_site->addItem("Idol Complex",      QVariant("idol"));
//    ui->comboBox_site->addItem("Konachan",          QVariant("konachan"));
//    ui->comboBox_site->addItem("Mishimmie",         QVariant("katawa"));
//    ui->comboBox_site->addItem("4chan House",       QVariant("4chan"));
//    ui->comboBox_site->addItem("Yande.re",          QVariant("yande.re"));
//    ui->comboBox_site->addItem("Danbooru",          QVariant("danbooru"));
//    ui->comboBox_site->addItem("Gelbooru",          QVariant("gelbooru"));
//    ui->comboBox_site->addItem("Safebooru",         QVariant("safebooru"));

    m_grabber = new Grabber(this);
    m_tester = new BooruTest(this);

    ui->tableView_job->setModel(this->m_grabber->jobModel());
    ui->tableView_job->verticalHeader()->hide();
    ui->tableView_job->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_job->hideColumn(0);

    bindHandlers();
    defaults();
}

MainWindow::~MainWindow()
{
    delete ui;

//    if (m_grabber != 0) {
//        delete m_grabber;
//    }

//    delete m_tester;
}

void MainWindow::startButtonHandler()
{
    Job newJob = this->getJobSettings();
    this->m_grabber->startNewJob(newJob);
}

void MainWindow::stopButtonHandler()
{
    test();
}

void MainWindow::contButtonHandler()
{
    this->m_grabber->contLastJob();
}

void MainWindow::progressChange(const int current, const int total)
{
    ui->progressBar->setValue(current);
    ui->progressBar->setMaximum(total);
}

void MainWindow::stageChange(GrabberStage stage)
{
    ui->label_STAGE->setText("Stage "
                             + QString::number((int)stage + 1)
                             + " of 3");
    progressChange(0, 0);
}

void MainWindow::logMessage(QString messageText)
{
    QString line = "[";
    line += QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    line += "]" + messageText;
    ui->plainTextEdit_LOG->appendPlainText(line);
//    ui->plainTextEdit_LOG->verticalScrollBar()
//    ui->plainTextEdit_LOG->verticalScrollBar()->setValue(
//                ui->plainTextEdit_LOG->verticalScrollBar()->maximum()
//                );
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
//    connect(this->grabber, SIGNAL(progressChange(int, int)), this,
//            SLOT(progressChange(int,int)));
    connect(this->m_grabber, SIGNAL(progressChange(int, int)), this, SLOT(progressChange(int,int)));
    connect(this->m_grabber, SIGNAL(stageChange(GrabberStage)), this, SLOT(stageChange(GrabberStage)));
    connect(this->m_grabber, SIGNAL(logMessage(QString)), this, SLOT(logMessage(QString)));
}

void MainWindow::test()
{
    m_tester->testing();
}

void MainWindow::defaults()
{
    ui->checkBox_ft_jpg->setChecked(true);
    ui->checkBox_ft_png->setChecked(true);
    ui->checkBox_ft_gif->setChecked(true);

    ui->checkBox_pt_resized->setChecked(true);
    ui->lineEdit_tags->setText("yukinoshita_yukino");
    ui->lineEdit_savepath->setText("pics");
}
