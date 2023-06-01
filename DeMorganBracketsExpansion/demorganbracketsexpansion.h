#ifndef DEMORGANBRACKETSEXPANSION_H
#define DEMORGANBRACKETSEXPANSION_H

#include <QString>
#include <QList>
#include <QMap>
#include <QDebug>
#include <iostream>

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
    NULL_EXEPTION, // нет ошибки
    PATH_NOT_FOUND, // путь к файлу пустой
    FILE_NOT_FOUND, // файл по пути не найден
    FILE_NOT_OPENED, // нет доступа к файлу
    MORE_THAN_ONE_STRING, // в файле содержится слишком много строк
    UNKNOWN_SYMBOL, // неизвестный символ в названии переменной
    NOT_ENOUGH_OPERATORS, // недостаточно оператором
    NOT_ENOUGH_ARGUMENTS, // недостаточно аргументов
    TO_MANY_SPACES, // слишком много пробелов
    EMPTY_TREE, //пустое древо
    NO_ACCESS_TO_FILE, // нет доступа к файлу
    VARIABLE_STARTS_WITH_DIGIT, // переменная начинается с цифры
    EMPTY_LEXEME // пустая лексема
};

/*!
* \Перечисление типов лексем
*/
enum lexemeType
{
    EMPTY,
    OPERATOR,
    VAR,
    UNKNOWN_LEXEME
};

/*!
* \Структура ошибки
*/
struct error {
    exeption type;
    int position;
    QString data;

    
    // Конструктор по умолчанию
    error(){
        this->type = NULL_EXEPTION;
        this->position = 0;
        this->data = "";
    }
    
    // Конструктор с параметрами
    error(exeption error, int position, QString data){
        this->type = error;
        this->position = position;
        this->data = data;
    }

    // Перегрузка оператора сравнения
    bool operator==(const error &other) const
    {
        return (type == other.type && position == other.position && data == other.data);
    }
};

/*!
* \Структура элемента стека при создании логического дерева
*/
struct stackElement
{
    node *element;
    int position;
};

/*!
 * \Структура оператора
 */
struct operators
{
    operandType type;
    int amountOfOperands;
};

/*!
 * \ Интерпретация поддерживаемых операторов из строки 
 */
const QMap<QString, operators> operatorsMap = {
    {"*", {AND, 2}},
    {"+", {OR, 2}},
    {"!", {NOT, 1}},
    {"-", {XOR, 2}},
    {"*!", {NAND, 2}},
    {"+!", {NOR, 2}}};


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
void treeToString(node *root, QString &str);


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

/*!
* \Проверяет является ли лексема переменной
* \param[in] lexeme - лексема
* \return QList<error> - список ошибок написания переменной (если ошибок нет, то лексема соответствует правилу написания переменной)
*/
QList<error> variableValidation(QString lexeme);

/*!
* \Проверяет является ли лексема оператором
* \param[in] lexeme - лексема
* \return тип лексемы из перечисления lexemeType
*/
lexemeType lexemeClassification(QString lexeme);

/*!
* \Получает строковую интерпретацию оператора
* \param[in] type - тип оператора
* \return строковая интерпретация оператора
*/
QString getIntrpretationOfOperator(operandType type);

/*!
* \Обрабатывает исключения и выводит их в консоль
* \param[in] errors - список ошибок
*/
void exeptionHandler(QList<error> errors);

/*!
* \Копирует узел
* \param[in] root - указатель на корень дерева
* \param[out] copy - указатель на копию узла
*/
void copyNode(node *root, node *copy);

#endif // DEMORGANBRACKETSEXPANSION_H
