#ifndef APPPLUGINENGINE_GLOBAL_H
#define APPPLUGINENGINE_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef QVA_PE_LIB_EXPORTS
# define APPPLUGINENGINE_EXPORT Q_DECL_EXPORT
#else
# define APPPLUGINENGINE_EXPORT Q_DECL_IMPORT
#endif

#endif // APPPLUGINENGINE_GLOBAL_H