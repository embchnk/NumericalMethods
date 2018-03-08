# made by Robert Gałat 2016

#############################################################
#                                                           #
#          Tu Ustawiamy nazwę pliku wynikowego              #
#                i dodatkowe biblioteki                     #
#                                                           #
#                                                           #
#-----------------------------------------------------------#
NAME=test													
LIBRARYS= -lm
#                                                           #
#############################################################


# ustawiamy kompilator
# CXX=g++
# CXX=clang++-3.5
# ustawiamy flagi do kompilacji
CXXFLAGS+= -Wall -O0 $(LIBRARYS) $(GXX_FLAGS) -g -std=c++11

# ustawiamy flagi dla kompilatora, żeby automatycznie wygenerował zależności
DEP_FLAGS=-MMD -MP

# pobieramy wszystkie pliki z rozszerzeniem .cpp i .C z folderu w którym jest makefile
SRC=$(wildcard *.cpp)
SRCC=$(wildcard *.C)

# do tej zmiennej zapisujemy nazwy plików obiektowych jakie mają być zrobione
OBJ=$(SRC:.cpp=.o)
OBJ+=$(SRCC:.C=.o)

#nazwy plików z zależnościami
DEP=$(OBJ:.o=.d)
#nazwa folderu dla plików obiektowych i zależności
OBJDIR := obj

#tworzymy listę plików obiektowych z odpowiednim adresem
OBJS := $(addprefix $(OBJDIR)/,$(OBJ))

DEPS := $(addprefix $(OBJDIR)/,$(DEP))


# najpierw upewniamu się czy mamy folder na pliki obiektowe, potem kompilujemy
.PHONY: all
all: $(OBJDIR) $(NAME)

# to chyba jasne main zależy od plików obiektowych
# kompilacja z flagami do linkowania ( domyślnie ustawione) wszystkie pliki obiektowe i generuj plik wynikowy do pliku o nazwie takiej jak nazwa etykiety( w tym przypadku main)	
$(NAME): $(OBJS) 
	$(CXX) $(LFLAGS) $^ -o $@

# tu tworzymy pliki obiektowe i pliki zależności 
$(OBJDIR)/%.o: %.C
	$(CXX) $(CXXFLAGS) $(DEP_FLAGS) -c $*.C -o $@
$(OBJDIR)/%.o: %.cpp 
	$(CXX) $(CXXFLAGS) $(DEP_FLAGS) -c $*.cpp -o $@

# tworzymy katalog dla plików obiektowych
$(OBJDIR):
	mkdir $(OBJDIR)


# ważne żeby zadziały automatyczne zależności
-include $(DEPS)

.PHONY: clean
clean:
	@rm -rf $(NAME) obj/
.PHONY: run
run:
	./$(NAME)
.PHONY: gdb
gdb:
	gdb ./$(NAME)
.PHONY: valgrind
valgrind:
	valgrind --leak-check=full ./$(NAME)
.PHONY: help
help:
	@clear
	@echo '-----------------------------------------------------------'
	@echo '#   make             - kompilacja i linkowanie projektu   #'
	@echo '#   make help        - wyświetla ten komunikat            #'
	@echo '#   make clean       - czyszczenie projektu               #'
	@echo '#   make run         - uruchamia program                  #'
	@echo '#   make gdb         - uruchamia gdb                      #'
	@echo '#   make valgrind    - uruchamia valgrind                 #'
	@echo '-----------------------------------------------------------'	
	@echo '###########################################################'
	@echo 'OPIS:'
	@echo 'ten makefile został stworzony na zajęcia z cpp na WFiIS'
	@echo 'umożliwia mieszanie rozszerzeń, i obsługuje pliki'
	@echo '.C .cpp .h, które powinny być razem w jenym katalogu'
	@echo 'pliki o tch rozszerzeniach powinny znajdować się w jednym katalogu'
	@echo 'ten makefile tworzy osobny katalog na pliki obiektowe'
	@echo 'i pliki zależności. Umożliwa to łatwe czyszczenie projektu'
	
	@echo 'TODO :'
	@echo 'make git  - do wysyłania na gita'
	@echo 'dodanie katalogów na źródła i nagłówki'