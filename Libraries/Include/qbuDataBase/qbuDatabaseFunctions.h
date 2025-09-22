#include <QString>
#include <QVariant>

//The following 2 functions will quote the string only if there are internal space characters.

extern QString	singleQuoteIfNotQuoted(QString str);
extern QString  doubleQuoteIfNotQuoted(QString str);
extern QString	singleQuoteIfNecessary(QString str);
extern QString	doubleQuoteIfNecessary(QString str);
extern QString	addBracketsForIdentifierIfNecessary(QString str);
extern bool		isSingleQuoted(QString str);
extern bool		isDoubleQuoted(QString str);
extern QString	toQueryValue(QVariant & vt);
extern QString	toQueryValue(const QVariant & vt);
extern QString	quoteSQLObjectNameIfNecessary(QString str);
extern QString  removeOuterParenthesis(QString str);

extern bool		hasOuterParenthesis(QString str);
extern QString	addOuterParenthesisIfNecessary(QString str);


