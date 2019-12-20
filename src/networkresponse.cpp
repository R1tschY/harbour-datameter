#include "networkresponse.h"

namespace DataMeter {

int HttpResponse::statusCode() const
{
    return m_inner->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
}

bool HttpResponse::hasNetworkError() const
{
    int error = m_inner->error();
    return error > 0 && error <= QNetworkReply::UnknownNetworkError;
}

QByteArray HttpResponse::content()
{
    if (m_content.isNull()) {
        readContent();
    }
    return m_content;
}

void HttpResponse::readContent()
{
    Q_ASSERT(m_content.isNull());
    m_content = m_inner->readAll();
}

} // namespace DataMeter
