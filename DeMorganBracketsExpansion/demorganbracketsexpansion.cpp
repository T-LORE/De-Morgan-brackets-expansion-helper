#include "demorganbracketsexpansion.h"
#include <iostream>
#include <QFile>
#include <QList>
#include <QTextStream>

node *createLogicalTree(QString expression)
{
    return 0;
}

void deMorganTransform(node *root)
{

}

void deleteDoubleNegation(node *root)
{

}

void treeToString(node *root, QString str)
{

}

QString getStringFromFile(QString path)

{   
    QList<error> errorList;

    if (path.isEmpty()) {
        // Путь к файлу пустой
        error pathError;
        pathError.error = PATH_NOT_FOUND;
        errorList.append(pathError);
        throw errorList;
    }

    QFile file(path);
    if (!file.exists()) {
        // Файл по пути не найден
        error fileError;
        fileError.error = FILE_NOT_FOUND;
        errorList.append(fileError);
        throw errorList;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // Нет доступа к файлу
        error fileError;
        fileError.error = FILE_NOT_OPENED;
        errorList.append(fileError);
        throw errorList;
    }

    QTextStream in(&file);
    QString line = in.readLine();

    if (!line.isNull() && !in.atEnd()) {
        // В файле содержится больше одной строки
        error multipleStringsError;
        multipleStringsError.error = MORE_THAN_ONE_STRING;
        errorList.append(multipleStringsError);
        throw errorList;
    }

    return line;

}

void saveStringToFile(QString path)
{

}
