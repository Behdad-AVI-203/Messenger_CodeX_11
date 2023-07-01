
#include <ReadUserFromFile.h>

QMap<QString, QJsonDocument> ReadUserFromFile()
{
    QMap<QString, QJsonDocument> jsonDocuments;
    QString folderPath = "User/Contacts";

    QDir directory(folderPath);
    QStringList jsonFiles = directory.entryList(QStringList() << "*.json", QDir::Files);

    foreach (QString fileName, jsonFiles) {
        QFile file(directory.absoluteFilePath(fileName));
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Could not open file:" << fileName;
            continue;
        }

        QByteArray jsonData = file.readAll();
        QJsonParseError parseError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
        if (parseError.error != QJsonParseError::NoError) {
            qDebug() << "Error parsing JSON file:" << fileName << "-" << parseError.errorString();
            continue;
        }

        QJsonObject jsonObj = jsonDoc.object();
        int index = 0;
        while (jsonObj.contains("block " + QString::number(index))) {
            QJsonValue blockValue = jsonObj.value("block " + QString::number(index));
            if (blockValue.isObject()) {
                QJsonObject blockObj = blockValue.toObject();
                jsonDocuments[fileName + " - Block " + QString::number(index)] = QJsonDocument(blockObj);
            }
            index++;
        }

        qDebug() << "File Name:" << fileName;
    }

    return jsonDocuments;
}

