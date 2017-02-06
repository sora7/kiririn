#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <fstream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->comboBox_site->addItem("Sankaku Channel", QVariant("sankaku"));
    ui->comboBox_site->addItem("Konachan", QVariant("konachan"));
    ui->comboBox_site->addItem("Yande.re", QVariant("yande.re"));
    ui->comboBox_site->addItem("Safebooru", QVariant("safebooru"));
    ui->comboBox_site->addItem("Danbooru", QVariant("danbooru"));

    ui->tableView_job->setModel(this->grabber.jobModel());
    ui->tableView_job->verticalHeader()->hide();
    ui->tableView_job->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_job->hideColumn(0);

    bindHandlers();

//    startButtonHandler();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startButtonHandler()
{
    Job newJob = this->getJobSettings();
    this->grabber.startNewJob(newJob);

/*
//    cout << "Fuck you asshole!" << endl;
//    Loader loader;
//    loader.loadFile("https://chan.sankakucomplex.com/?next=3823616&amp;tags=patema&amp;page=2", "search2.html");
//    loader.loadFile("https://cs.sankakucomplex.com/data/sample/e3/75/sample-e3750e103c4680fed3d1ee9eb8714cc9.jpg?3773378", "dera.jpg");
////    loader.loadFile("https://chan.sankakucomplex.com/post/show/5034106","post_jpg[0]-r-s.html");

//    QStringList tags;
//    tags << "onodera_kosaki";
//    tags << "nisekoi";
//    tags << "screen_capture";



//    SankakuParser parser;

//    cout << parser.genQueryUrl(tags).toStdString() << endl;

//    SearchInfo sinfo =  parser.parseSearch(Parser::readFile("search2.html"));
//    cout << sinfo << endl;
//    PostInfo postInfo =  parser.parsePost(Parser::readFile("post_jpg[0]-r-s.html"));
//    PostInfo postInfo =  parser.parsePost(Parser::readFile("post.html"));
    //    cout << postInfo << endl;
    */
}

void MainWindow::stopButtonHandler()
{

}

void MainWindow::contButtonHandler()
{
    this->grabber.contLastJob();
}

Job MainWindow::getJobSettings()
{
    Job job;

    job.site = ui->comboBox_site->itemData(ui->comboBox_site->currentIndex()).toString();
    job.tags = ui->lineEdit_tags->text().split(" ");
    job.save_path = ui->lineEdit_savepath->text();

    if (ui->checkBox_rt_safe->isChecked()) {
        job.rating << "safe";
    }
    if (ui->checkBox_rt_questionable->isChecked()) {
        job.rating << "questionable";
    }
    if (ui->checkBox_rt_explicit->isChecked()) {
        job.rating << "explicit";
    }


    if (ui->checkBox_pt_original->isChecked()) {
        job.pic_types << "original";
    }

    if (ui->checkBox_pt_resized->isChecked()) {
        job.pic_types << "resized";
    }


    if (ui->checkBox_ft_jpg->isChecked()) {
        job.file_types << "jpg";
    }
    if (ui->checkBox_ft_png->isChecked()) {
        job.file_types << "png";
    }
    if (ui->checkBox_ft_gif->isChecked()) {
        job.file_types << "gif";
    }
    if (ui->checkBox_ft_webm->isChecked()) {
        job.file_types << "webm";
    }
    if (ui->checkBox_ft_mp4->isChecked()) {
        job.file_types << "mp4";
    }
    cout << job << endl;
    return job;
}


void MainWindow::bindHandlers()
{
    connect(ui->pushButton_START, SIGNAL(clicked()), this, SLOT(startButtonHandler()));
    connect(ui->pushButton_STOP, SIGNAL(clicked()), this, SLOT(stopButtonHandler()));
    connect(ui->pushButton_CONTINUE, SIGNAL(clicked()), this, SLOT(contButtonHandler()));
}
