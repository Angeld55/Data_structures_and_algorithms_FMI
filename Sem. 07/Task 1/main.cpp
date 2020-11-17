#include "PDA.h"
int main()
{
	PDA automation2(3); //3 initial states

	automation2.makeFinal(2);
	automation2.addTransition(0, 'a', '#', 0, "A#");
	automation2.addTransition(0, 'b', '#', 0, "B#");
	automation2.addTransition(0, '$', '#', 2, "$");

	automation2.addTransition(0, 'a', 'A', 0, "AA");
	automation2.addTransition(0, 'a', 'A', 1, "$");

	automation2.addTransition(0, 'b', 'B', 0, "BB");
	automation2.addTransition(0, 'b', 'B', 1, "$");

	automation2.addTransition(0, 'b', 'A', 0, "BA");
	automation2.addTransition(0, 'a', 'B', 0, "AB");

	automation2.addTransition(1, 'a', 'A', 1, "$");
	automation2.addTransition(1, 'b', 'B', 1, "$");

	automation2.addTransition(1, '$', '#', 2, "$");

	std::cout << automation2.accepts("abbbba") <<endl; //true
	std::cout << automation2.accepts("abab") <<endl; //false

}