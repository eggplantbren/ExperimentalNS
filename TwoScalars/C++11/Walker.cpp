#include "Walker.h"

template<class Type>
Walker<Type>::Walker()
:direction(point.get_scalars().size())
{

}

template<class Type>
void Walker<Type>::initialise()
{
	point.from_prior();
	point.from_prior_tiebreakers();
}

