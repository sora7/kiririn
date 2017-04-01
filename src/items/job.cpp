#include "job.h"

Job::Job()
{
//    this->done = false;
//    this->search_done = false;
//    this->posts_done = false;

    this->m_status = READY;

    this->m_filenameTemplate = "%fname%";
    this->m_tryMax = 3;

    this->m_lastSearchUrl = QString("");
}

Job::~Job()
{
    //    this->jobDB.close();
}

ostream& operator<<(ostream &os, const Job &job)
{
    os << "id: "        << job.m_id << endl;
    os << "site: "      << job.m_site.toStdString() << endl;
    os << "tags: "      << job.m_tags.join(", ").toStdString() << endl;
    os << "save path: " << job.m_savePath.toStdString() << endl;

    os << "pic types: ";
    QList<PicType> picTypesList = job.m_pic_types.toList();
    for (int i = 0; i < picTypesList.count(); i++) {
        os << PicInfo::to_str(picTypesList.at(i));
        os << ", ";
    }
    os << endl;

//     << picTypesList.join(", ").toStdString() << endl;
//    QStringList ratingList(job.rating.toList());
    os << "rating: ";
    QList<PostRating> postRatingList = job.m_rating.toList();
    for (int i = 0; i < postRatingList.count(); i++) {
        os << PostInfo::to_str(postRatingList.at(i));
        os << ", ";
    }
    os << endl;

//    << ratingList.join(", ").toStdString() << endl;



//    QStringList fileTypesList(job.file_types.toList());
    os << "file types: ";
    QList<PicFormat> picFormatList = job.m_pic_formats.toList();
    for (int i = 0; i < picFormatList.count(); i++) {
        os << PicInfo::to_str(picFormatList.at(i));
        os << ", ";
    }
    os << endl;

//    << fileTypesList.join(", ").toStdString() << endl;
    return os;
}

int Job::getId() const
{
    return m_id;
}

void Job::setId(const int value)
{
    m_id = value;
}

void Job::addRating(const PostRating postRating)
{
    this->m_rating << postRating;
}

void Job::addType(const PicType picType)
{
    this->m_pic_types << picType;
}

void Job::addFormat(const PicFormat picFormat)
{
    this->m_pic_formats << picFormat;
}

bool Job::okRating(const PostInfo postInfo) const
{
    if (m_rating.contains(RT_OTHER)) {
        return true;
    }
    if (m_rating.contains(postInfo.getRating())) {
        return true;
    }
    return false;
}

bool Job::picMatch(const PicInfo picInfo) const
{
    bool result = m_pic_types.contains(picInfo.getType()) &&
                  m_pic_formats.contains(picInfo.getFormat());
    return result;
}

string Job::to_str(JobStatus jobStatus)
{
    switch (jobStatus) {
        case READY: {
            return "ready";
        }
        case SEARCH_START: {
            return "search start";
        }
        case SEARCH_DONE: {
            return "search done";
        }
        case POSTS_DONE: {
            return "posts done";
        }
        case PICS_DONE: {
            return "picsc done";
        }
    }
    return "";
}

int Job::getTryMax() const
{
    return m_tryMax;
}

void Job::setTryMax(int value)
{
    m_tryMax = value;
}

QString Job::getFilenameTemplate() const
{
    return m_filenameTemplate;
}

void Job::setFilenameTemplate(const QString &value)
{
    m_filenameTemplate = value;
}

QString Job::getSavePath() const
{
    return m_savePath;
}

void Job::setSavePath(const QString &value)
{
    m_savePath = value;
}

QStringList Job::getTags() const
{
    return m_tags;
}

void Job::setTags(const QStringList &value)
{
    m_tags = value;
}

QString Job::getSite() const
{
    return m_site;
}

void Job::setSite(const QString &value)
{
    m_site = value;
}

QString Job::getLastSearchUrl() const
{
    return m_lastSearchUrl;
}

void Job::setLastSearchUrl(const QString &value)
{
    m_lastSearchUrl = value;
}

QSet<PicFormat> Job::getPicFormats() const
{
    return m_pic_formats;
}

void Job::setPicFormats(const QSet<PicFormat> picFormats)
{
    m_pic_formats = picFormats;
}

QSet<PostRating> Job::getRating() const
{
    return m_rating;
}

void Job::setRating(const QSet<PostRating> postRating)
{
    m_rating = postRating;
}

QSet<PicType> Job::getPicTypes() const
{
    return m_pic_types;
}

void Job::setPicTypes(const QSet<PicType> picTypes)
{
    m_pic_types = picTypes;
}

JobStatus Job::getStatus() const
{
    return m_status;
}

void Job::setStatus(const JobStatus jobStatus)
{
    m_status = jobStatus;
}
