#ifndef NETWORKRESPONSE_H
#define NETWORKRESPONSE_H

#include <QNetworkReply>

namespace DataMeter {

class HttpResponse {
public:
    HttpResponse(QNetworkReply* reply)
        : m_inner(reply)
    {
    }

    int statusCode() const;

    bool hasNetworkError() const;
    QString errorString() const { return m_inner->errorString(); }

    QString header(const QByteArray& name) const;

    QByteArray content();

private:
    QNetworkReply* m_inner;
    QByteArray m_content;

    void readContent();
};

inline QString HttpResponse::header(const QByteArray& name) const
{
    return m_inner->rawHeader(name);
}

} // namespace DataMeter

#endif // NETWORKRESPONSE_H
