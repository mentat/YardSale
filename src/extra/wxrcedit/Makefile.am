INCLUDES =  -I.

CXXFLAGS = $(WX_CXXFLAGS)  -g

bin_PROGRAMS = wxrcedit

wxrcedit_SOURCES = \
edapp.cpp\
editor.cpp \
nodehnd.cpp\
nodesdb.cpp \
pe_adv.cpp \
pe_basic.cpp \
preview.cpp \
propedit.cpp \
propframe.cpp \
splittree.cpp \
xmlhelpr.cpp

wxrcedit_LDFLAGS = -L../xrc/
wxrcedit_LDADD = $(WX_LIBS) -lxrc

