#ifndef TEST_VARIABLEVALIDATION_H
#define TEST_VARIABLEVALIDATION_H


#include "qobject.h"
#include "qtmetamacros.h"

#include "../DeMorganBracketsExpansion/demorganbracketsexpansion.h"

class test_variableValidation: public QObject
{
   Q_OBJECT
   public:
       void compareErrors(QList<error> expectedErrors, QList<error> errors);

   private slots:
    void variableCorrect_data();
    void variableCorrect();


};

#endif // TEST_VARIABLEVALIDATION_H
