#include "job.h"

Job::Job()
{
    this->done = false;
    this->search_done = false;
    this->posts_done = false;

    this->filenames = "%fname%";
    this->try_max = 3;

    this->lastSearchUrl = job::INIT_URL;
}

Job::~Job()
{
    //    this->jobDB.close();
}

ostream& operator<<(ostream &os, const Job &job)
{
    os << "id: "        << job.id << endl;
    os << "site: "      << job.site.toStdString() << endl;
    os << "tags: "      << job.tags.join(", ").toStdString() << endl;
    os << "save path: " << job.save_path.toStdString() << endl;

    QStringList picTypesList(job.pic_types.toList());
    os << "pic types: " << picTypesList.join(", ").toStdString() << endl;
    QStringList ratingList(job.rating.toList());
    os << "rating: "    << ratingList.join(", ").toStdString() << endl;
    QStringList fileTypesList(job.file_types.toList());
    os << "file types: "<< fileTypesList.join(", ").toStdString() << endl;
    return os;
}

int Job::getId() const
{
    return id;
}

void Job::setId(int value)
{
    id = value;
}
