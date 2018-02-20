#include <ics46/factory/DynamicFactory.hpp>
#include "myOthelloAI.hpp"

ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, pfarrell::MyOthelloAI, "pfarrellAI (required)");

static const bool black = false;
static const bool white = true;
static const std::pair<int, int> adjacent[8] 
{ std::pair(0,1), std::pair(1,1), std::pair(1,0), std::pair(1,-1), std::pair(0,-1), std::pair(-1,-1), std::pair(-1,0), std::pair(-1,1) };

std::pair<int, int> pfarrell::MyOthelloAI::chooseMove(const OthelloGameState& state)
{
	OthelloCell thisTeam;
	OthelloCell otherTeam;
	if( state.isWhiteTurn() )
	{
		thisTeam = OthelloCell::white;
		otherTeam = OthelloCell::black;
	}
	else
	{
		thisTeam = OthelloCell::black;
		otherTeam = OthelloCell::white;
	}

}

std::vector<std::pair<int, int>> geValidMoves( const OthelloGameState& state, OthelloCell thisTeam, OthelloCell otherTeam )
{	
	//as I understand valid moves are ones that are directly adjacent to the opposite team's tiles
	//and have another "friendly" tile (i.e. of the same team) up,down,left,right, 
	// or diagonal at any distance

	std::vector< std::pair<int, int> > maybeValid();
	std::vector< std::pair<int, int> > valid();

	for(int x = 0; x < state.board().width(); x++)
		for(int y = 0; y < state.board().height(); y++)
		{
			if( state.board().cellAt(x, y) == otherTeam )
				for()

		}
}


