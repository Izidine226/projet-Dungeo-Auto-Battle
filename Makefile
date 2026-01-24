CXX = clang++
CXXFLAGS = -std=c++14 -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wcast-align -Wconversion -Wsign-conversion -Wnull-dereference
TARGET_DEBUG = build/Debug/outDebug
TARGET_RELEASE = dungeon
SRCS = main.cpp Combat.cpp Joueur.cpp HeroFactory.cpp
OBJS = build/Debug/main.o build/Debug/Combat.o build/Debug/Joueur.o build/Debug/HeroFactory.o

# Créer les répertoires nécessaires
build/Debug:
	mkdir -p build/Debug

# Compilation des objets individuels
build/Debug/main.o: main.cpp | build/Debug
	$(CXX) $(CXXFLAGS) -g3 -O0 -c main.cpp -o build/Debug/main.o

build/Debug/Combat.o: Combat.cpp | build/Debug
	$(CXX) $(CXXFLAGS) -g3 -O0 -c Combat.cpp -o build/Debug/Combat.o

build/Debug/Joueur.o: Joueur.cpp | build/Debug
	$(CXX) $(CXXFLAGS) -g3 -O0 -c Joueur.cpp -o build/Debug/Joueur.o

build/Debug/HeroFactory.o: HeroFactory.cpp | build/Debug
	$(CXX) $(CXXFLAGS) -g3 -O0 -c HeroFactory.cpp -o build/Debug/HeroFactory.o

# Edition des liens pour le debug (compatible VS Code)
$(TARGET_DEBUG): $(OBJS)
	$(CXX) $(CXXFLAGS) -g3 -O0 $(OBJS) -o $(TARGET_DEBUG)

# Cible par défaut (release)
$(TARGET_RELEASE): $(SRCS)
	$(CXX) $(CXXFLAGS) -O2 -o $(TARGET_RELEASE) $(SRCS)

# Cibles alias pour compatibilité
debug: $(TARGET_DEBUG)
release: $(TARGET_RELEASE)
all: $(TARGET_DEBUG) $(TARGET_RELEASE)

clean:
	rm -rf build $(TARGET_RELEASE)

.PHONY: clean debug release all
