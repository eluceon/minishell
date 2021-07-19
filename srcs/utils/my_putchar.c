#include "utils.h"

int	myputchar(int nb)
{
	return (write (1, &nb, 1));
}
