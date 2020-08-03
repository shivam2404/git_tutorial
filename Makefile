## Makefile
## author:  Holger Arndt
## version: 21.11.2017

CPP = cpp
MAKEDEP = $(CPP) -MM -fPIC
QTCXX = g++
QTCXXFLAGS = -Wall -std=c++17 -fPIC
QT5INCBASE := /usr/include/qt5
QT5INC := -I$(QT5INCBASE)/QtCore -I$(QT5INCBASE)/QtGui \
	-I$(QT5INCBASE)/QtWidgets -I$(QT5INCBASE)
QT5LIB := -lQt5Core -lQt5Gui -lQt5Widgets

CCEXE = shapetst
CCSRC := $(CCEXE).cc shapes.cc shapewin.cc
CCOBJ := $(patsubst %.cc,%.o,$(CCSRC))
CCDEP := $(patsubst %.cc,%.dep,$(CCSRC))

all: $(CCEXE)

.SUFFIXES:
.SECONDARY:

%: %.o $(CCOBJ)
	$(QTCXX) $(CCOBJ) -o $@ $(QT5LIB)

%.o: %.cc
	$(QTCXX) $(QT5INC) $(QTCXXFLAGS) -c $<

%.dep: %.cc
	$(MAKEDEP) $< $(QT5INC) | sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' > $@

clean:
	rm -f $(CCOBJ) $(CCDEP) $(CCEXE)

-include $(CCDEP)
