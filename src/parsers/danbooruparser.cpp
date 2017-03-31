#include "danbooruparser.h"

DanbooruParser::DanbooruParser()
{
    this->m_http_prefix = "http://";
    this->m_site_url = "danbooru.donmai.us";

    this->m_query_prefix = "/posts?utf8=✓&tags=";
    this->m_query_tag_sep = "+";
    this->m_query_suffix = "&ms=1";
    this->m_tags_max = 2;
//    <li><a rel="next" href="/posts?ms=1&amp;page=2&amp;tags=megumin+thighhighs&amp;utf8=%E2%9C%93">&gt;&gt;</a></li>
//    <a rel="next" href="/posts?page=2&amp;tags=chomusuke">
//    <a rel="next" href="/posts?ms=1&amp;page=2&amp;tags=chomusuke&amp;utf8=%D0%B2%D1%9A%E2%80%9C">
    this->m_rxNextPage = QRegExp("<a rel=\"next\" href=\"(/posts[?].{0,}page=\\d+&amp;tags=.*)\">");
    this->m_rxNextPage.setMinimal(true);
//    <a href="/posts/2661171"><img itemprop="thumbnailUrl" src="
    this->m_rxPost = QRegExp("<a href=\"(/posts/\\d+)\"><img itemprop=\"thumbnailUrl\" src=\"");
    this->m_rxPost.setMinimal(true);
//    <li>Rating: Safe</li>
//    <li>Rating: Questionable</li>
//    <li>Rating: Explicit</li>
    this->m_rxRating   = QRegExp("<li>Rating: (Safe|Questionable|Explicit)</li>");

//    Size: <a href="/data/__aqua_kono_subarashii_sekai_ni_shukufuku_wo_drawn_by_tomifumi__a4f83e79ecdcb7ef37883bc9dfaac025.jpg">635 KB</a>
    QString orig = "Size: <a href=\"(/data/(.*[.]([a-z0-9]{3,4})))\">.*</a>";
    this->m_rxOrig = QRegExp(orig);
    this->m_rxOrig.setMinimal(true);
//    <img width="850" height="1200" id="image" data-original-width="1032" data-original-height="1458" data-large-width="850" data-large-height="1200" data-tags="1girl aqua_(konosuba) ass bare_shoulders blue_eyes blue_hair blush breasts commentary_request detached_sleeves eyedrops fake_tears hair_rings highres kono_subarashii_sekai_ni_shukufuku_wo! long_hair looking_at_viewer lying no_panties no_shoes on_side revision solo thighhighs tomifumi" alt="aqua (kono subarashii sekai ni shukufuku wo!) drawn by tomifumi" data-uploader="EB" data-rating="s" data-flags="" data-has-children="true" data-has-active-children="true" data-score="55" data-fav-count="59" itemprop="contentUrl" src="/data/sample/__aqua_kono_subarashii_sekai_ni_shukufuku_wo_drawn_by_tomifumi__sample-e2fe95d6c6596a60d3609b966b99b7bc.jpg" />
//    <img width="850" height="1201" id="image" data-original-width="1167" data-original-height="1650" data-large-width="850" data-large-height="1201" data-tags="1girl :o arm_at_side artist_name bangs bare_shoulders belt belt_buckle black_legwear blush brown_hair brown_hat buckle checkered checkered_floor collar collarbone cowboy_shot dress flat_chest hat head_tilt highres holding holding_hat kono_subarashii_sekai_ni_shukufuku_wo! long_sleeves looking_at_viewer megumin off-shoulder_dress off_shoulder open_mouth red_dress saraki sidelocks signature single_thighhigh solo standing tassel thighhighs witch_hat" alt="megumin (kono subarashii sekai ni shukufuku wo!) drawn by saraki" data-uploader="Provence" data-rating="q" data-flags="" data-has-children="false" data-has-active-children="false" data-score="32" data-fav-count="44" itemprop="contentUrl" src="/data/sample/__megumin_kono_subarashii_sekai_ni_shukufuku_wo_drawn_by_saraki__sample-b3db89e3dc554d684806ebd549f8fbad.jpg" />

    QString resize = "<img.*id=\"image\".*itemprop=\"contentUrl\" src=\"(/data/sample/(.*sample-[a-z0-9]*[.]([a-z0-9]{3,4})))\" />";
//    QString resize = "<img.*id=\"image\".*src=\"(/data/sample/(.*[.][a-z0-9]{3,4})))\" />";
    this->m_rxResize = QRegExp(resize);
    this->m_rxResize.setMinimal(true);
}

DanbooruParser::~DanbooruParser()
{

}

QString DanbooruParser::name()
{
    return danbooru::fullname;
}

QList<PicInfo> DanbooruParser::getPics(QString htmlText)
{
    QList<PicInfo> pics;

    int pos = this->m_rxOrig.indexIn(htmlText);
    if (pos > -1) {
        QString origUrl  = this->m_rxOrig.cap(1);
        QString origName = this->m_rxOrig.cap(2);
        QString origExt  = this->m_rxOrig.cap(3);

        PicInfo picInfo;
        picInfo.setType(ORIGINAL);
        picInfo.setName(origName);
        picInfo.setFormat( checkFormat( origExt ) );
        picInfo.setUrl( this->m_http_prefix + this->m_site_url + origUrl );

        pics << picInfo;
    }

    pos = this->m_rxResize.indexIn(htmlText);
    cout << "RESIZE" << endl;
    if (pos > -1) {
        QString resUrl  = this->m_rxResize.cap(1);
        QString resName = this->m_rxResize.cap(2);
        QString resExt  = this->m_rxResize.cap(3);

        PicInfo picInfo2;
        picInfo2.setType(RESIZED);
        picInfo2.setName(resName);
        picInfo2.setFormat( checkFormat( resExt ) );
        picInfo2.setUrl( this->m_http_prefix + this->m_site_url + resUrl );

        pics << picInfo2;
    }
    return pics;
}

//QList<PicInfo> DanbooruParser::getPics(QString htmlText)
//{
////    cout << "booru pics" << endl;
//    QList<PicInfo> pics;

//    this->_rxOrig.setMinimal(true);
//    int pos = this->_rxOrig.indexIn(htmlText);
//    if (pos > -1) {
//        QString origUrl  = this->_rxOrig.cap(1);
//        QString origName = this->_rxOrig.cap(2);
//        QString origExt  = this->_rxOrig.cap(3);

//        PicInfo picInfo;
//        picInfo.setType(ORIGINAL);
//        picInfo.setName(origName);
//        picInfo.setFormat( checkFormat( origExt ) );
//        picInfo.setUrl( this->_http_prefix + this->_site_url + origUrl );

//        pics << picInfo;
//    }
//    return pics;
//}
