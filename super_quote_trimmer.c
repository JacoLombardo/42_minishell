#include "minishell.h"

int		main(int argc, char **argv)
{
	char	*line1 = "a\"b\'c\"d\"e\'f\"g";

	printf("%s\n", super_trimmer(line1));

	return (0);
}
