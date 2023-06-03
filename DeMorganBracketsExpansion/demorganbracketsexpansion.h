/*!
*\file
*\brief В данном файле находятся заголовки функций, которые используются для работы программы.
*/

#ifndef DEMORGANBRACKETSEXPANSION_H
#define DEMORGANBRACKETSEXPANSION_H

#include <QString>
#include <QList>
#include <QMap>
#include <QDebug>
#include <iostream>
#include <QFile>
#include <QTextStream>

/*!
* \brief Перечисление логических операндов
*/


enum operandType {
    NULL_ELEMENT, ///< Пустой элемент
    NOT,          ///< Отрицание
    AND,          ///< И
    OR,           ///< Или
    XOR,          ///< Исключающее или
    NAND,         ///< И-не
    NOR,          ///< Или-не
    VARIABLE      ///< Переменная
  
};


/*!
* \brief brief Структура узла логического дерева
*/
struct node {
    QString data;
    operandType type;
    QList<node *> childrens;
};


/*!
* \brief Перечисление исключений
*/
enum exeption{
    NULL_EXEPTION, ///< нет ошибки
    PATH_NOT_FOUND, ///< путь к файлу пустой
    FILE_NOT_FOUND, ///< файл по пути не найден
    FILE_NOT_OPENED, ///< нет доступа к файлу
    MORE_THAN_ONE_STRING, ///< в файле содержится слишком много строк
    UNKNOWN_SYMBOL, ///< неизвестный символ в названии переменной
    NOT_ENOUGH_OPERATORS, ///< недостаточно оператором
    NOT_ENOUGH_ARGUMENTS, ///< недостаточно аргументов
    TO_MANY_SPACES, ///< слишком много пробелов
    EMPTY_TREE, ///< пустое древо
    NO_ACCESS_TO_FILE, ///< нет доступа к файлу
    VARIABLE_STARTS_WITH_DIGIT, // переменная начинается с цифры
    EMPTY_LEXEME, ///< пустая лексема
    TO_MANY_ARGUMENTS ///< передано слишком много аргументов
};

/*!
* \brief Перечисление типов лексем
*/
enum lexemeType
{
    EMPTY, ///< пустая лексема
    OPERATOR,   ///< оператор
    VAR,    ///< переменная
    UNKNOWN_LEXEME ///< неизвестная лексема
};

/*!
* \brief Структура ошибки
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
* \brief Структура элемента стека при создании логического дерева
*/
struct stackElement
{
    node *element; ///< указатель на узел дерева
    int position; ///< позиция элемента в строке
};

/*!
 * \brief Структура оператора
 */
struct operators
{
    operandType type; ///< тип оператора
    int amountOfOperands; ///< количество операндов
};

/*!
 * \brief  Интерпретация поддерживаемых операторов из строки 
 */
const QMap<QString, operators> operatorsMap = {
    {"*", {AND, 2}},
    {"+", {OR, 2}},
    {"!", {NOT, 1}},
    {"-", {XOR, 2}},
    {"*!", {NAND, 2}},
    {"+!", {NOR, 2}}};


/*!
* \brief Преобразует строку с логическим выражением без скобок записанным в обратной польской записи в логическое дерево
* \param[in] expression - строка с логическим выражением
* \return - указатель на корень созданного дерева
* \throw - QList<error> - Выбрасывает лист исключений в случае ошибок обработки файла
*/
node * createLogicalTree(QString expression);


/*!
* \brief Преобразует логическое дерево по правилу де Моргана
* \param[in,out] root - указатель на корень дерева
*/
void deMorganTransform(node *root);


/*!
* \brief Удаляет двойные отрицания в логическом дереве
* \param[in,out] root - указатель на корень дерева
*/
void deleteDoubleNegation(node *root);


/*!
* \brief Преобразует логическое дерево в строку
* \param[in] root - указатель на корень дерева
* \param[out] str - строка в которую необходимо записать результат
*/
void treeToString(node *root, QString &str);


/*!
* \brief  Получает логическое выражение из файла
* \param[in] path - путь к файлу
* \return - строка с логическим выражением
* \throw - QList<error> - Выбрасывает лист исключений в случае ошибок обработки файла
*/
QString getStringFromFile(QString path);


/*!
* \brief  Записывает логическое выражение в файл
* \param[in] path - путь к файлу
* \param[in] str - строка с логическим выражением
* \throw - QList<error> - Выбрасывает лист исключений в случае ошибок обработки файла
*/
void saveStringToFile(QString path, QString str);

/*!
* \brief Проверяет соответствует ли лексема правилам написания переменной
* \param[in] lexeme - лексема
* \return QList<error> - список ошибок написания переменной (если ошибок нет, то лексема соответствует правилу написания переменной)
*/
QList<error> variableValidation(QString lexeme);

/*!
* \brief Классифицирует лексему
* \param[in] lexeme - лексема
* \return тип лексемы из перечисления lexemeType
*/
lexemeType lexemeClassification(QString lexeme);

/*!
* \brief Получает строковую интерпретацию оператора
* \param[in] type - тип оператора
* \return строковая интерпретация оператора
*/
QString getIntrpretationOfOperator(operandType type);

/*!
* \brief Обрабатывает исключения и выводит их в консоль
* \param[in] errors - список ошибок
*/
void exeptionHandler(QList<error> errors);

/*!
* \brief Копирует узел
* \param[in] root - указатель на узел который необходимо скопировать
* \param[in,out] copy - указатель на то, куда необходимо скопировать
*/
void copyNode(node *root, node *copy);

/*!
* \brief Вставляет копии полученного узла между родителем и ребенком n раз
* \param[in] parent - указатель на родителя
* \param[in] childId - номер ребенка
* \param[in] nodeToInsert - указатель на узел, который необходимо вставить
* \param[in] n - сколько копий необходимо вставить
*/
void insertBetween(node *parent, int childId, node *nodeToInsert, int n);

/*!
* \brief Возвращает список подряд идущих узлов определенного типа, каждый узел в ряду должен иметь только одного ребенка
* \param[in] root - указатель на корень дерева
* \param[in] type - тип узла
* \return QList<node*> - список подряд идущих узлов одинакового типа
*/ 
QList<node*> nodeInARow(node *root, int type);

#endif // DEMORGANBRACKETSEXPANSION_H
