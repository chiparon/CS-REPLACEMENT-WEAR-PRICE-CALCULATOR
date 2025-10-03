//main fn.
#include <QApplication>
#include "IoTableDialog.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    IoTableDialog dlg;
    dlg.show();
    return app.exec();
}
