#include "OthelloAI.hpp"

namespace pfarrell
{

    class MyOthelloAI : public OthelloAI
    {
     public:
        virtual std::pair<int, int> chooseMove(const OthelloGameState& state);
    };

}
