# arg blah 

SUBDIRS = include src

yardsaledocdir = ${prefix}/doc/YardSale
yardsaledoc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS\
	TODO\
	ABOUT-NLS

EXTRA_DIST = $(yardsaledoc_DATA)

doxy:
	doxygen ys_docs.cfg


# Copy all the spec files. Of cource, only one is actually used.
dist-hook:
	for specfile in *.spec; do \
		if test -f $$specfile; then \
			cp -p $$specfile $(distdir); \
		fi \
	done
