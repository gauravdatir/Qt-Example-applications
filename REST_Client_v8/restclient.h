#ifndef RESTCLIENT_H
#define RESTCLIENT_H

#include <QObject>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>





class RESTClient : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString responseText READ responseText NOTIFY responseTextUpdated)
    Q_PROPERTY(QString imageUrl READ imageUrl NOTIFY imageUrlUpdated)

public:
    RESTClient();

   Q_INVOKABLE void createGetRequest(QUrl requestUrl);

    QString responseText()
    {
        return m_responseStrng;
    }

    QString imageUrl()
    {
        return m_ImageUrl;
    }

public slots:
    void onResponseReceived(QNetworkReply *reply);

signals:
    void responseTextUpdated();
    void imageUrlUpdated();
private:

    void parseImageUrl(QJsonObject jsonObj);

    QNetworkAccessManager *m_networkManager;

    QString m_responseStrng;

    QString m_ImageUrl;

};

#endif // RESTCLIENT_H
