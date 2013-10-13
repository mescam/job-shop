# here goes our ultimate C Makefile, just wait!
CC	= clang
CFLAGS	= -Wall -g -std=gnu99
LFLAGS	= -lrt -lm
LINKER	= clang -o

TARGET	= jobshop
SRCDIR	= src
OBJDIR	= obj
HEADIR	= include
BINDIR	= bin
TEXDIR	= tex
TEXNAM	= paper_pl.tex

SOURCES		:= $(wildcard $(SRCDIR)/*.c)
INCLUDES	:= $(wildcard $(HEADIR)/*.h)
OBJECTS		:= $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(BINDIR)/$(TARGET)

$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $@ $(LFLAGS) $(OBJECTS)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@echo "CC $<"
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

clean:
	@rm -rf $(OBJECTS)
	@rm -rf $(BINDIR)/$(TARGET)
	@echo "Cleaned working directory"

tex:
	@pdflatex -shell-escape -synctex=1 -interaction=nonstopmode -output-directory=$(TEXDIR) $(TEXDIR)/$(TEXNAM)
	@echo "Compiled TeX file to PDF"

.PHONY:	all clean tex
