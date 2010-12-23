TARGET = twittercli
TEMPLATE = app

# include(../../kqoauth.prf)

QT += network
CONFIG += crypto
CONFIG += kqoauth

macx {
    CONFIG -= app_bundle
    QMAKE_POST_LINK += install_name_tool -change kqoauth.framework/Versions/0/kqoauth \
                       ../../lib/kqoauth.framework/Versions/0/kqoauth $${TARGET}
}
else:unix {
  # the second argument (after colon) is for
  # being able to run make check from the root source directory
#  LIBS += -Wl,-rpath,../../lib:lib
}

#INCLUDEPATH += . ../../src
HEADERS += twittercli.h
SOURCES += twittercli.cpp
