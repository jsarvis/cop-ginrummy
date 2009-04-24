# Makefile
# Gin Rummy Simulation
# by Jon Calhoun, Michael Jenzen, Andrea Kosta, Jacob Sarvis 
# UCF - Spring 2009
# COP 4331

# C++

#ProjectName is .cpp file containing Main()
#!!!!    Change for new project    !!!!
PROJECTNAME = GinRummySim

#All .cpp files in the directory
SRCS = $(wildcard *.cpp)
#.o files matching those .cpp files in SRCS
OBJS = $(patsubst %.cpp,%.o,$(SRCS))
#LIBS = pdcurses.lib
GCC = g++
#CFLAGS = 

#Default target
all : $(PROJECTNAME)

#General rule for .cpp files
%.o : %.cpp
	$(GCC) -c $< -o $@

#Linking stage
$(PROJECTNAME): $(OBJS)
	$(GCC) -g -O0 -o $(PROJECTNAME) $(OBJS) $(LIBS)


#Extra dependencies
#!!!!    Change for new project    !!!!
#X.o : X.cpp is implicit, but X.h and W.h are not
SimMgmt.o : SimMgmt.h IOMgmt.h AppError.h
AppError.o : AppError.h
IOMgmt.o : IOMgmt.h AppError.h
GinRummySim.o : GinRummy.h SimMgmt.h
GinRummy.o : GinRummy.h Player.h Dealer.h StockPile.h SimMgmt.h
Player.o : Player.h Dealer.h Card.h CardMsg.h Melds.h MeldsMsg.h SimMgmt.h
Dealer.o : Dealer.h Player.h GinRummy.h Card.h CardMsg.h Melds.h MeldsMsg.h StockPile.h DiscardPile.h SimMgmt.h
DiscardPile.o : DiscardPile.h Card.h CardPile.h SimMgmt.h
StockPile.o : StockPile.h Card.h CardPile.h SimMgmt.h
CardPile.o : CardPile.h Card.h SimMgmt.h
Card.o : Card.h SimMgmt.h
Melds.o : Melds.h Card.h SimMgmt.h
MeldsMsg.o : MeldsMsg.h Melds.h SimMgmt.h
CardMsg.o : CardMsg.h Card.h SimMgmt.h
PlayersMsg.o : PlayersMsg.h SimMgmt.h

#Alt:
#A.o B.o : A.h B.h
#A.o B.o : A.h
#A.o B.o : B.h
