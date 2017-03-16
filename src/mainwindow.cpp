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
    BooruTest tester("konachan");

    QString url;
//    url = "https://shimmie.katawa-shoujo.com/post/view/3844";
//    url = "https://shimmie.katawa-shoujo.com/post/view/3975?search=hanako";
//    url = "https://shimmie.katawa-shoujo.com/post/list/hanako/1";
//    url = "https://shimmie.katawa-shoujo.com/post/list/shizune/1";
//    url = "https://shimmie.katawa-shoujo.com/post/list/hanako/105";

//    url = "https://chan.sankakucomplex.com/?next=3823616&amp;tags=patema&amp;page=2";
//    url = "https://chan.sankakucomplex.com/post/show/5034106";
//    url = "https://shimmie.4chanhouse.org/index.php?q=/post/list/jp/1";
//    url = "https://shimmie.4chanhouse.org/index.php?q=/post/view/5775&search=jp";
//    url = "https://shimmie.4chanhouse.org/index.php?q=/post/view/5782&search=jp";
//    url = "https://shimmie.4chanhouse.org/index.php?q=/post/view/5717&search=jp";
//    url = "https://shimmie.4chanhouse.org/index.php?q=/post/list/a/19";
//    url = "https://shimmie.4chanhouse.org/index.php?q=/post/list/a/7";
//    url = "https://shimmie.4chanhouse.org/index.php?q=/post/list/conrad%20jp/1";
//    url = "https://idol.sankakucomplex.com/?tags=shameimaru_aya+amatsuka_miyu+camera&commit=Search";
//    url = "https://idol.sankakucomplex.com/?tags=misaka_mikoto+shirai_kuroko&commit=Search";
//    url = "https://idol.sankakucomplex.com/?tags=shirai_kuroko+kanda_midori&commit=Search";
//    url = "https://idol.sankakucomplex.com/post/show/446785";
//    url = "https://idol.sankakucomplex.com/post/show/663736";
//    url = "https://idol.sankakucomplex.com/post/show/294891";
//    url = "https://konachan.com/post/show/238330/hatsune_miku-long_hair-re-rin-twintails-vocaloid";
//    url = "https://konachan.com/post/show/206617/baseball-black_hair-blue_eyes-brown_hair-hikigaya_";
//    url = "https://konachan.com/post/show/215099/brown_hair-cropped-hikigaya_hachiman-kiss-long_hai";
//    url = "https://konachan.com/post/show/200176/black_eyes-black_hair-blush-book-drink-hikigaya_ha";
//    url = "https://konachan.com/post/show/234649/blush-close-gradient-hikigaya_komachi-short_hair-t";
//    url = "https://konachan.com/post?tags=yuigahama_yui";
//    url = "https://konachan.com/post?page=3&tags=yukinoshita_yukino";
//    url = "https://konachan.com/post?tags=atomix";
//    url = "https://konachan.com/post?tags=alice_%28wonderland%29";

    tester.test("search");
    tester.test("post");
}
