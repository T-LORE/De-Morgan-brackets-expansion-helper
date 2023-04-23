#ifndef DEMORGANBRACKETSEXPANSION_H
#define DEMORGANBRACKETSEXPANSION_H

#include <QString>
#include <QList>
enum operandType {
    NOT,
    AND,
    OR,
    XOR,
    VARIABLE
};

struct node {
    QString data;
    operandType type;
    node *left;
    node *right;
};


enum exeption{
    PATH_NOT_FOUND, // путь к файлу пустой
    FILE_NOT_FOUND, // файл по пути не найден
    FILE_NOT_OPENED, // нет доступа к файлу
    MORE_THAN_ONE_STRING, // в файле содержится слишком много строк
    WRONG_SYMBOL, // неизвестный символ в строке
    NOT_ENOUGH_OPERATORS, // недостаточно оператором
    NOT_ENOUGH_ARGUMENTS, // недостаточно аргументов
    NO_SPACE_BETWEEN_OPERANDS, // нет разделителя пробела между операндами
    EMPTY_TREE //пустое древо



};

struct error {
    exeption error;
    int position;
    char symbol;
};

struct errors {
    QList<error> lsit;
};

/*!
* \Преобразует строку с логическим выражением без скобок записанным в обратной польской записи в логическое дерево
* \param[in] expression - строка с логическим выражением
* \return - указатель на корень созданного дерева
* \throw - (Выбрасывает исключения в случае ошибок обработки строки)
*/
node * createLogicalTree(QString expression);


/*!
* \Преобразует логическое дерево по правилу де Моргана
* \param[in,out] root - указатель на корень дерева
*/
void deMorganTransform(node *root);


/*!
* \Удаляет двойные отрицания в логическом дереве
* \param[in,out] root - указатель на корень дерева
*/
void deleteDoubleNegation(node *root);


/*!
* \Преобразует логическое дерево в строку
* \param[in] root - указатель на корень дерева
* \param[out] str - строка в которую необходимо записать результат
*/
void treeToString(node *root, QString str);

/*!
* \ Получает логическое выражение из файла
* \param[in] path - путь к файлу
* \return - строка с логическим выражением
* \throw - (Выбрасывает исключения в случае ошибок обработки файла)
*/
QString getStringFromFile(QString path);

/*!
* \ Записывает логическое выражение в файл
* \param[in] path - путь к файлу
* \param[in] str - строка с логическим выражением
* \throw - (Выбрасывает исключения в случае ошибок обработки файла)
*/
void saveStringToFile(QString path);

#endif // DEMORGANBRACKETSEXPANSION_H
