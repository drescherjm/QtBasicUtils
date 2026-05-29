#include "duParameter.h"
#include "qbuBase/qbuProperyMapXMLHelper.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static QRegularExpression                g_hasNestedSplitter(R"(;\s*[(\d])");

static int                               m_nMetaID = qRegisterMetaType<duParameter>();
static qbuProperyMapXMLHelper            hlpr(m_nMetaID);

static int                               m_nMetaIDPtr = qRegisterMetaType<duParameter*>();
static qbuUserPropPtrHelper<duParameter> ptrHlpr(m_nMetaIDPtr);
