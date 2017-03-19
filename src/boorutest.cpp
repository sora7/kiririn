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

void BooruTest::load(QString type, QStringList urlList)
{
    QStringListIterator iter(urlList);
    while(iter.hasNext()) {
        load(type, iter.next());
    }
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
    setBooru("safebooru");
    QStringList urlList;
//    urlList << "https://shimmie.katawa-shoujo.com/post/view/3844";
//    urlList << "https://shimmie.katawa-shoujo.com/post/view/3975?search=hanako";
//    urlList << "https://shimmie.katawa-shoujo.com/post/list/hanako/1";
//    urlList << "https://shimmie.katawa-shoujo.com/post/list/shizune/1";
//    urlList << "https://shimmie.katawa-shoujo.com/post/list/hanako/105";

//    urlList << "https://chan.sankakucomplex.com/?next=3823616&amp;tags=patema&amp;page=2";
//    urlList << "https://chan.sankakucomplex.com/post/show/5034106";
//    urlList << "https://shimmie.4chanhouse.org/index.php?q=/post/list/jp/1";
//    urlList << "https://shimmie.4chanhouse.org/index.php?q=/post/view/5775&search=jp";
//    urlList << "https://shimmie.4chanhouse.org/index.php?q=/post/view/5782&search=jp";
//    urlList << "https://shimmie.4chanhouse.org/index.php?q=/post/view/5717&search=jp";
//    urlList << "https://shimmie.4chanhouse.org/index.php?q=/post/list/a/19";
//    urlList << "https://shimmie.4chanhouse.org/index.php?q=/post/list/a/7";
//    urlList << "https://shimmie.4chanhouse.org/index.php?q=/post/list/conrad%20jp/1";
//    urlList << "https://idol.sankakucomplex.com/?tags=shameimaru_aya+amatsuka_miyu+camera&commit=Search";
//    urlList << "https://idol.sankakucomplex.com/?tags=misaka_mikoto+shirai_kuroko&commit=Search";
//    urlList << "https://idol.sankakucomplex.com/?tags=shirai_kuroko+kanda_midori&commit=Search";
//    urlList << "https://idol.sankakucomplex.com/post/show/446785";
//    urlList << "https://idol.sankakucomplex.com/post/show/663736";
//    urlList << "https://idol.sankakucomplex.com/post/show/294891";
//    urlList << "https://konachan.com/post/show/238330/hatsune_miku-long_hair-re-rin-twintails-vocaloid";
//    urlList << "https://konachan.com/post/show/206617/baseball-black_hair-blue_eyes-brown_hair-hikigaya_";
//    urlList << "https://konachan.com/post/show/215099/brown_hair-cropped-hikigaya_hachiman-kiss-long_hai";
//    urlList << "https://konachan.com/post/show/200176/black_eyes-black_hair-blush-book-drink-hikigaya_ha";
//    urlList << "https://konachan.com/post/show/234649/blush-close-gradient-hikigaya_komachi-short_hair-t";
//    urlList << "https://konachan.com/post?tags=yuigahama_yui";
//    urlList << "https://konachan.com/post?page=3&tags=yukinoshita_yukino";
//    urlList << "https://konachan.com/post?tags=atomix";
//    urlList << "https://konachan.com/post?tags=alice_%28wonderland%29";

//    urlList << "https://yande.re/post?tags=hatsune_miku+kagamine_rin";
//    urlList << "https://yande.re/post?tags=kunikida_hanamaru";
//    urlList << "https://yande.re/post/show/323982";
//    urlList << "https://yande.re/post/show/315898";
//    urlList << "https://yande.re/post/show/386461";
//    urlList << "https://yande.re/post/show/386519";
//    urlList << "https://yande.re/post/show/386510";

//    urlList << "http://danbooru.donmai.us/posts?tags=chomusuke";
//    urlList << "http://danbooru.donmai.us/posts?page=4&tags=aqua_%28konosuba%29";
//    urlList << "http://danbooru.donmai.us/posts/2602900";
//    urlList << "http://danbooru.donmai.us/posts/2657629";
//    urlList << "http://danbooru.donmai.us/posts/2657867";
//    urlList << "http://danbooru.donmai.us/posts/2621161";
//    urlList << "http://danbooru.donmai.us/posts/2623779";

//    urlList << "https://gelbooru.com/index.php?page=post&s=list&tags=ayakura_juu+1girl";
//    urlList << "https://gelbooru.com/index.php?page=post&s=list&tags=spice_and_wolf+official_art";

//    urlList << "https://gelbooru.com/index.php?page=post&s=view&id=3605016";
//    urlList << "https://gelbooru.com/index.php?page=post&s=view&id=3604883";
//    urlList << "https://gelbooru.com/index.php?page=post&s=view&id=1894915";
//    urlList << "https://gelbooru.com/index.php?page=post&s=view&id=3435203";
//    urlList << "http://gelbooru.com/index.php?page=post&s=view&id=3436534";


//    urlList << "https://safebooru.org/index.php?page=post&s=list&tags=seifuku&pid=200";
//    urlList << "https://safebooru.org/index.php?page=post&s=list&tags=altera_%28fate%29";
//    urlList << "https://safebooru.org/index.php?page=post&s=list&tags=gochuumon_wa_usagi_desuka%3F";
//    urlList << "https://safebooru.org/index.php?page=post&s=list&tags=fate%2Fextra";
//    load("search", urlList);
//    urlList.clear();
//    urlList << "https://safebooru.org/index.php?page=post&s=view&id=2177836";
//    urlList << "https://safebooru.org/index.php?page=post&s=view&id=2177840";
//    urlList << "https://safebooru.org/index.php?page=post&s=view&id=2176514";
//    urlList << "https://safebooru.org/index.php?page=post&s=view&id=2177826";
//    urlList << "https://safebooru.org/index.php?page=post&s=view&id=2177820";
//    load("post", urlList);

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
    if (shortname == safebooru::shortname) {
        parser = new SafebooruParser();
    }
}

QString BooruTest::testFilename(QString type, int datasetN)
{
    //    filename template
    //    %booru%_%type%_%datasetN%.txt
    return this->_booru + "_" + type + "_" + QString::number(datasetN) + ".txt";
}
