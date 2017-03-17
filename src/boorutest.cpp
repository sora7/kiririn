#include "boorutest.h"

BooruTest::BooruTest()
{
}

BooruTest::~BooruTest()
{
    delete this->parser;
}

void BooruTest::load(QString type, QString url)
{
    QString fname;
    int datasetCount = 1;
    while (QFile::exists(fname = testFilename(type, datasetCount))) {
        datasetCount++;
    }

    Loader loader;
    loader.loadFile(url, fname);
}

void BooruTest::test(QString type, int datasetN)
{
    if (datasetN == 0) {
        int count = 1;
        while (QFile::exists( testFilename(type, count) )) {
            this->test(type, count);
            count++;
        }
    }
    else {
        cout << "Dataset #" << datasetN << endl;
        QString fname = testFilename(type, datasetN);
        if (type == "search") {
            SearchInfo sinfo =  parser->parseSearch(BooruParser::readFile(fname));
            cout << sinfo << endl;
        }
        else {
            PostInfo pinfo =  parser->parsePost(BooruParser::readFile(fname));
            cout << pinfo << endl;
        }
    }
}

void BooruTest::testing()
{
    setBooru("gelbooru");
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

//    url = "https://yande.re/post?tags=hatsune_miku+kagamine_rin";
//    url = "https://yande.re/post?tags=kunikida_hanamaru";
//    url = "https://yande.re/post/show/323982";
//    url = "https://yande.re/post/show/315898";
//    url = "https://yande.re/post/show/386461";
//    url = "https://yande.re/post/show/386519";
//    url = "https://yande.re/post/show/386510";

//    QStringList tags;
//    tags << "hatsune_miku";
//    tags << "kagamine_rin";
//    cout << parser->genQueryUrl(tags).toStdString() << endl;

//    url = "http://danbooru.donmai.us/posts?tags=chomusuke";
//    url = "http://danbooru.donmai.us/posts?page=4&tags=aqua_%28konosuba%29";
//    url = "http://danbooru.donmai.us/posts/2602900";
//    url = "http://danbooru.donmai.us/posts/2657629";
//    url = "http://danbooru.donmai.us/posts/2657867";
//    url = "http://danbooru.donmai.us/posts/2621161";
//    url = "http://danbooru.donmai.us/posts/2623779";

//    url = "https://gelbooru.com/index.php?page=post&s=list&tags=ayakura_juu+1girl";
//    url = "https://gelbooru.com/index.php?page=post&s=list&tags=spice_and_wolf+official_art";

//    url = "https://gelbooru.com/index.php?page=post&s=view&id=3605016";
//    url = "https://gelbooru.com/index.php?page=post&s=view&id=3604883";
//    url = "https://gelbooru.com/index.php?page=post&s=view&id=1894915";
//    url = "https://gelbooru.com/index.php?page=post&s=view&id=3435203";
//    url = "http://gelbooru.com/index.php?page=post&s=view&id=3436534";

    test("search");
    test("post");
}

void BooruTest::setBooru(QString shortname)
{
    this->_booru = shortname;
    if (shortname == sankaku::shortname) {
        parser = new SankakuChannelParser();
    }
    if (shortname == idol::shortname) {
        parser = new IdolComplexParser();
    }
    if (shortname == katawa::shortname) {
        parser = new MishimmieParser();
    }
    if (shortname == fourchan::shortname) {
        parser = new FourChanHouseParser();
    }
    if (shortname == konachan::shortname) {
        parser = new KonachanParser();
    }
    if (shortname == yandere::shortname) {
        parser = new YandeReParser();
    }
    if (shortname == danbooru::shortname) {
        parser = new DanbooruParser();
    }
    if (shortname == gelbooru::shortname) {
        parser = new GelbooruParser();
    }
}

QString BooruTest::testFilename(QString type, int datasetN)
{
    //    filename template
    //    %booru%_%type%_%datasetN%.txt
    return this->_booru + "_" + type + "_" + QString::number(datasetN) + ".txt";
}
