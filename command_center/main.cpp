#include <QApplication>

#include "glob.h"
#include "core.h"
#include "gui.h"

int main(int argc, char *argv[]) {
    //to not have to flusn it all the time -- alternatively use own log
    setbuf(stdout, NULL);
    QApplication a(argc, argv);
    core = Core_ptr(new Core());
    return a.exec();
}
