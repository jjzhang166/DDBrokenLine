#include "ddbrokenline_plugin.h"
#include "ddbrokenline.h"

#include <qdeclarative.h>

void DDBrokenLinePlugin::registerTypes(const char *uri)
{
    // @uri com.ddui.qmlcomponents
    qmlRegisterType<DDBrokenLine>(uri, 1, 0, "DDBrokenLine");
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(DDBrokenLine, DDBrokenLinePlugin)
#endif

