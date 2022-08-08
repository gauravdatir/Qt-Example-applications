#include "restclient.h"

RESTClient::RESTClient()
{
    m_networkManager = new QNetworkAccessManager(this);

    connect(m_networkManager, &QNetworkAccessManager::finished, this, &RESTClient::onResponseReceived);
}

void RESTClient::onResponseReceived(QNetworkReply *reply)
{

    QByteArray respBytes = reply->readAll();

    QJsonDocument jsondocResponse = QJsonDocument::fromJson(respBytes);

    QJsonObject jsonRespObject = jsondocResponse.object();

    parseImageUrl(jsonRespObject);

    QString jsonStringResp(jsondocResponse.toJson(QJsonDocument::Indented));

    m_responseStrng = jsonStringResp;

    emit responseTextUpdated();

    /*
    QString rep = QString::fromStdString(reply->readAll().toStdString());
    qDebug() << rep;
*/
}

void RESTClient::parseImageUrl(QJsonObject jsonObj)
{
    QJsonValue imageURLVal = jsonObj.value(QStringLiteral("url"));
    m_ImageUrl = imageURLVal.toString();
    emit imageUrlUpdated();
}

void RESTClient::createGetRequest(QUrl requestUrl)
{
    if(!requestUrl.isEmpty())
    {
        QNetworkRequest request(requestUrl);
        m_networkManager->get(request);
    }
    else {
        qDebug() << "Request URL is empty";
        m_responseStrng = m_responseStrng + "Request URL is empty";
        emit responseTextUpdated();
    }

}
