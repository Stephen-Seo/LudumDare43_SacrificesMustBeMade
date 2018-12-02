SRC_ROOT = ../src
SFML_ROOT = /home/stephen/Downloads/SFML-2.5.0/buildWinReleaseStatic/install
CXX = g++
MINGW_CXX = i686-w64-mingw32-g++
ASM = i686-w64-mingw32-cc
CXX_FLAGS = -c -std=c++14 -Wall -Wextra -Wpedantic -O3 -D NDEBUG
MINGW_CXXFLAGS = -c -std=c++14 -Wall -Wextra -Wpedantic -O3 -D NDEBUG \
           -DSFML_STATIC \
           -I${SFML_ROOT}/include \
           -I${SRC_ROOT} \
           -I${SRC_ROOT}/../include \
           -I${SRC_ROOT}/../GameDevTools/src \
           -I${SRC_ROOT}/../EntityComponentMetaSystem/src \
           -mwindows

OBJDIR = objdir

LINKER_FLAGS = -mwindows -static
RP_LINKER_FLAGS =

LINKER_LIBS =
RP_LINKER_LIBS =

POST_LINKER_LIBS = \
                   -L${SFML_ROOT}/lib \
                   -lsfml-audio-s \
                   -lsfml-graphics-s \
                   -lsfml-window-s \
                   -lsfml-system-s \
                   -lwinmm \
                   -lws2_32 \
                   -lgdi32 \
                   -lopengl32 \
                   -limm32 \
                   -lFLAC \
                   -lfreetype \
                   -lopenal32 \
                   -lvorbisfile \
                   -lvorbis \
                   -lvorbisenc \
                   -logg

SOURCES = ${SRC_ROOT}/main.o \
          ${SRC_ROOT}/ECStuff.o \
          ${SRC_ROOT}/CommonValues.o \
          ${SRC_ROOT}/CommonFunctions.o \
          ${SRC_ROOT}/../GameDevTools/src/GDT/GameLoop.o \
          ${SRC_ROOT}/../GameDevTools/src/GDT/CollisionDetection.o

OBJECTS = $(subst ..,PREV_SUB,$(addprefix $(OBJDIR)/,$(SOURCES)))

define uniq =
  $(eval seen :=)
  $(foreach _,$1,$(if $(filter $_,${seen}),,$(eval seen += $_)))
  ${seen}
endef

all:    LD43_byStephen_BurnedKirby_Seo.exe

LD43_byStephen_BurnedKirby_Seo.exe: ${OBJECTS}
	$(MINGW_CXX) $(LINKER_FLAGS) -o LD43_byStephen_BurnedKirby_Seo.exe ${LINKER_LIBS} ${OBJECTS} ${POST_LINKER_LIBS}

$(call uniq,$(dir $(OBJECTS) $(RP_OBJECTS) $(LUASCRIPTS))):
	mkdir -p $@

clean:
		rm -rf $(OBJDIR)
		rm -f LD43_byStephen_BurnedKirby_Seo.exe

.SECONDEXPANSION:

$(OBJDIR)/%.o: $$(subst PREV_SUB,..,%.cpp) | $$(dir $$@)
	$(MINGW_CXX) $(MINGW_CXXFLAGS) -o $(subst ..,PREV_SUB,$@) $<

# vim: noexpandtab
