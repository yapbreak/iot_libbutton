ACLOCAL_AMFLAGS = -I $(top_srcdir)/m4

include $(top_srcdir)/Makefile.common

lib_LTLIBRARIES = libbutton.la
libbutton_la_SOURCES  = button.h
libbutton_la_SOURCES += button.cpp

include_HEADERS = button.h
libdir = $(prefix)/lib/yapiot/
includedir = $(prefix)/include/yapiot/libbutton

libledextradir = $(prefix)/lib/pkgconfig
libledextra_DATA = button.pc
