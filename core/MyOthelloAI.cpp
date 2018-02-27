#include <ics46/factory/DynamicFactory.hpp>
#include "MyOthelloAI.hpp"
#include <iostream>
#include <stdlib.h> 

ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, pfarrell::MyOthelloAI, "pfarrellAI (required)");

static const int maxDepth = 2;
static bool thisTeam;

std::pair<int, int> pfarrell::MyOthelloAI::chooseMove(const OthelloGameState& state)
{
	assert (maxDepth % 2 == 0);	//odd depths make the ai pick the best move for the opposite team
	thisTeam = state.isWhiteTurn();

	std::unique_ptr<OthelloGameState> stateptr = state.clone();
	std::vector< std::pair<int, int> > possableMoves = pfarrell::MyOthelloAI::getValidMoves(state);
	std::vector< std::unique_ptr<OthelloGameState> > sims( possableMoves.size() );

	int temp(0);
	int bestIndex(0);
	int bestScore;

	//debugging:
	for( int i = 0; i < possableMoves.size(); i++)
	{
		std::cout << possableMoves[i].first << ", " << possableMoves[i].second << std::endl;
	}

	for(int i = 0; i < possableMoves.size(); i++)
	{
		sims[i] = state.clone();
		sims[i]->makeMove(possableMoves[i].first, possableMoves[i].second);
		OthelloGameState& t = *sims[i];
		temp = getResult( !thisTeam, maxDepth, t);

		//score can be negative so there isnt an appropreat minimum value (using min int seem wrong)
		if( i == 0)
			bestScore = temp;

		if( temp > bestScore)
		{
			bestIndex = i;
			bestScore = temp;
		}
	}

	std::cout << "Best: " << bestIndex << std::endl;
	std::cout << "RETURNING: " << possableMoves[bestIndex].first << ", " << possableMoves[bestIndex].second << std::endl;
	return possableMoves[bestIndex];
}

//getResult returns the score of the best outcome, givin that the opponent uses the same eval function
int pfarrell::MyOthelloAI::getResult( bool simTeam, int depth, const OthelloGameState& state)
{
	std::vector<std::pair<int, int>> moves = getValidMoves(state);
	std::vector<int> evaluations(moves.size());
	std::vector< std::unique_ptr<OthelloGameState> > sims(moves.size());

	for(int i = 0; i < moves.size(); i++)
	{
		sims[i] = state.clone();
		sims[i]->makeMove(moves[i].first, moves[i].second);
		evaluations[i] = eval( *sims[i], simTeam );
	} 

	//depth is how many moves, of both teams, we look forward
	std::cout << "depth: " << depth << std::endl;
	std::cout << "Sims size: " << sims.size() << std::endl;

	int bestScore;
	if( moves.size() == 0 )
	{
		if( depth <= 0)
			return eval(*state.clone(), simTeam);

		return getResult( !simTeam, depth-1, *state.clone());
	}
	if( depth <= 0 )
	{
		bestScore = evaluations[0];
		for( int i = 0; i < evaluations.size(); i++)
		{
			if( evaluations[i] > bestScore )
				bestScore = evaluations[i];
		}		

		return bestScore; //base case
	}
	else
	{
		
		for(int i = 0; i < sims.size(); i++)
		{
			evaluations[i] = getResult( !simTeam, depth-1, *sims[i]);
			if(  evaluations[i] > bestScore)
			{
				bestScore = evaluations[i];	 
			}
		}

		return bestScore;
	}
}

int pfarrell::MyOthelloAI::eval( OthelloGameState& state, bool team )
{
	int score = state.whiteScore() - state.blackScore();

	if( !team )
		score = -1*score;

	return score;	
}

std::vector<std::pair<int, int>> pfarrell::MyOthelloAI::getValidMoves( std::unique_ptr<OthelloGameState> state )
{
	std::vector< std::pair<int, int> > validMoves;

	for(int x = 0; x < state->board().width(); x++)
	{
		for(int y = 0; y < state->board().height(); y++)
		{
			if( state->isValidMove(x, y) )
				validMoves.push_back( std::pair(x, y) );
		}
	}

	return validMoves;
}

std::vector<std::pair<int, int>> pfarrell::MyOthelloAI::getValidMoves( const OthelloGameState& state )
{
	std::vector< std::pair<int, int> > validMoves;

	for(int x = 0; x < state.board().width(); x++)
	{
		for(int y = 0; y < state.board().height(); y++)
		{
			if( state.isValidMove(x, y) )
				validMoves.push_back( std::pair(x, y) );
		}
	}

	return validMoves;
}