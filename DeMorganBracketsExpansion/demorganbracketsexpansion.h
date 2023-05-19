#ifndef DEMORGANBRACKETSEXPANSION_H
#define DEMORGANBRACKETSEXPANSION_H

#include <QString>
#include <QList>


/*!
* \Перечисление логических операндов
*/
enum operandType {
    NULL_ELEMENT,
    NOT,
    AND,
    OR,
    XOR,
    NAND,
    NOR,
    VARIABLE
  
};


/*!
* \Структура узла логического дерева
*/
struct node {
    QString data;
    operandType type;
    QList<node *> childrens;
};


/*!
* \Перечисление исключений
*/
enum exeption{
    PATH_NOT_FOUND, // путь к файлу пустой
    FILE_NOT_FOUND, // файл по пути не найден
    FILE_NOT_OPENED, // нет доступа к файлу
    MORE_THAN_ONE_STRING, // в файле содержится слишком много строк
    UNKNOWN_SYMBOL, // неизвестный символ в строке
    NOT_ENOUGH_OPERATORS, // недостаточно оператором
    NOT_ENOUGH_ARGUMENTS, // недостаточно аргументов
    NO_SPACE_BETWEEN_OPERANDS, // нет разделителя пробела между операндами
    EMPTY_TREE, //пустое древо
    NO_ACCESS_TO_FILE, // нет доступа к файлу
    INCORRECT_VARIABLE // некорректное имя переменной
};


/*!
* \Структура ошибки
*/
struct error {
    exeption error;
    int position;
    char symbol;
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
void saveStringToFile(QString path, QString str);

#endif // DEMORGANBRACKETSEXPANSION_H
