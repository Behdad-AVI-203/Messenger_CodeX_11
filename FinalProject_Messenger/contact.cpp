#include "contact.h"

Contact::Contact(QString contactname)
{

    ContactName=contactname;

}

/*void Contact::SetContactMessage(string message,string username)
{


    QFile file("multimap.txt");
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            for (auto it = map.begin(); it != map.end(); ++it) {
                out << it.key() << ":" << it.value() << "\n";
            }
            file.close();
        } else {
            qDebug() << "Error opening file";
            return 1;
        }
}
*/
