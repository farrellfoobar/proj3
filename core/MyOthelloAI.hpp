#include "OthelloAI.hpp"

namespace pfarrell
{

    class MyOthelloAI : public OthelloAI
    {
     public:
        std::pair<int, int> chooseMove(const OthelloGameState& state);
        int getResult(bool simTeam, int depth, const OthelloGameState& state);
        int eval( OthelloGameState& state, bool team );
        std::vector<std::pair<int, int>> getValidMoves( std::unique_ptr<OthelloGameState> state );
        std::vector<std::pair<int, int>> getValidMoves( const OthelloGameState& state );
    };

}
