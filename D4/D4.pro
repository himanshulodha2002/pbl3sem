QT += network widgets

HEADERS += httpwindow.h \
    main_data.h
SOURCES += httpwindow.cpp \
           main.cpp
FORMS += authenticationdialog.ui

# install
target.path = $$[QT_INSTALL_EXAMPLES]/network/http
INSTALLS += target
