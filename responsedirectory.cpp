#include "responsedirectory.h"
#include "mime.h"
#include <QDir>
#include <QFileInfoList>
#include <QTextStream>
#include <QByteArray>
#include <QBuffer>

//Display the first page showing the files
ResponseDirectory::ResponseDirectory(QTcpSocket* socket, QMap<QString, QString>& header, QString dir_name, QString url_path):
    Response(socket, 200, header),
    m_dir_name(dir_name),
    m_url_path(url_path)
{
}

void ResponseDirectory::response()
{
    QDir dir(m_dir_name);
    if (!dir.isReadable())
        return; //TODO error

    QByteArray buffer;
    QBuffer qbuffer(&buffer);
    qbuffer.open(QIODevice::WriteOnly);
    QTextStream sbuffer(&qbuffer);
    sbuffer << "<html><head><title>"
            << m_url_path
            << "</title></head><body><h1>"
            << m_url_path
            << "</h1><hr/><table><tr>"
               "<td>Filename</td>"
               "<td>Size</td>"
               "</tr>";

    dir.setFilter(QDir::Dirs|QDir::Files);
    dir.setSorting(QDir::DirsFirst|QDir::Name);
    QFileInfoList file_list = dir.entryInfoList();

    for (QFileInfoList::Iterator i = file_list.begin(); i != file_list.end(); ++i)
    {
        if (i->isDir())
        {
            sbuffer << QString("<tr><td><a hred='%1'>%2/</a></td><td>-</td></tr>")
                       .arg(m_url_path + i->fileName())
                       .arg(i->fileName());
        }
        else
        {
            sbuffer << QString("<tr><td><a href='%1'>%2</a></td><td>%3</td></tr>")
                                   .arg(m_url_path + i->fileName())
                                   .arg(i->fileName())
                                   .arg(i->size());
        }

    }

    sbuffer << "</table><hr/>"
            << APPLICATION_IDENTIFIER
            << "</body></html>";
    sbuffer.flush();

    m_header["Content-Type"] = Mime::instance().getMimeType("html");
    m_header["content-Length"] = QString("%1").arg(buffer.length());

    responseHeader();

    m_socket->write(buffer);
}
