#include "loader.h"

size_t write_text(char *data, size_t size, size_t nmemb, string *buffer)
{
  size_t result = 0;
  if (buffer != NULL)
  {
    buffer->append(data, size * nmemb);
    result = size * nmemb;
  }
  return result;
}

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

Loader::Loader()
{
}

QString Loader::loadHtml(QString url)
{
    // sleep for a random interval between 300 and 700 ms
    srand(time(NULL));
    delay(rand_gap(300, 700));

    QString html_text = "";

    char errorBuffer[CURL_ERROR_SIZE];

    CURL *curl;
    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
        curl_easy_setopt(curl, CURLOPT_URL, url.toStdString().c_str());
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, FALSE);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, DEFAULT_UA.c_str());
        curl_easy_setopt(curl, CURLOPT_HEADER, 0);

        string buffer;

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_text);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

        CURLcode result = curl_easy_perform(curl);

        if (result == CURLE_OK) {
            html_text = QString::fromStdString(buffer);
        }
        else {
            cout << "ERROR " << errorBuffer << endl;
        }
    }
    curl_easy_cleanup(curl);

    return html_text;
}

void Loader::loadFile(QString url, QString filename)
{
    // sleep for a random interval between 300 and 700 ms
    srand(time(NULL));
    delay(rand_gap(300, 700));

    char errorBuffer[CURL_ERROR_SIZE];

    CURL *curl;
    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
        curl_easy_setopt(curl, CURLOPT_URL, url.toStdString().c_str());
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, FALSE);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, DEFAULT_UA.c_str());
        curl_easy_setopt(curl, CURLOPT_HEADER, 0);

        FILE *fp;
        fp = fopen(filename.toStdString().c_str(), "wb");

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

        CURLcode result = curl_easy_perform(curl);

        if (result != CURLE_OK) {
            cout << "ERROR " << errorBuffer << endl;
        }

        fclose(fp);
    }
    curl_easy_cleanup(curl);
}

#ifdef DELAY_Q
void delay(int millisec)
{
    QTime wakeTime = QTime::currentTime().addMSecs(millisec);
    while(QTime::currentTime() < wakeTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}
#endif

#ifdef DELAY_T
void delay(int millisec) {
    Sleeper::msleep(millisec);
}
#endif

int rand_gap(int from, int to)
{
    return rand()%(to - from) + from;
}
