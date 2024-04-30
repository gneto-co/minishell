/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:27:56 by gneto-co          #+#    #+#             */
/*   Updated: 2024/03/04 11:05:49 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu.h"

// run that in your file
// cc .menu/* -o .menu_exe && ./.menu_exe

char		g_name[] = "pipex";
char		*g_args[] = {
	"in_file \"grep i\" \"wc -l\" pipex_out",
	"in_file \"ls -l -a\" \"grep 16\" pipex_out"
	};
char		*g_exe[] = {
	"< in_file grep i | wc -l > original_out",
	"< in_file ls -l -a | grep 16 > original_out"
	};
int			arg_i = 0;

#pragma region ex_number

static void	ex_0(void)
{
	char	c = 0;
    
	printf("\033]0;Tests Menu\007");
	while (c != 'q')
	{
		fflush(stdout);
		printf
		(
			"\nChose your test:\n"
			"\n\033[94m 0\x1b[0m < in_file grep # | wc -l > infile"
			"\n\033[94m 1\x1b[0m < in_file ls -l -a | grep 16 > original_out"
			"\n ---------"
			"\n\033[36m c\x1b[0m clear screen"
			"\n\033[31m q\x1b[0m to quit"
			"\n\n> "
		);
		scanf(" %c", &c);
		getchar();

		system("clear");

		if (c == 'q')
			break;
		else if (c == '0')
		{
			arg_i = 0;
		}
		else if (c == '1')
		{
			arg_i = 1;
		}
	}
	system("clear");
}

static void	ex_1(void)
{
	char	*str;
	int		j;

	j = 0;
	printf("\npipex output:\n\n");
	str = ft_multi_strjoin(" ./%s %s", g_name, g_args[arg_i]);
	system(str);
	printf("\n\noriginal output:\n\n");
	system(g_exe[arg_i]);
	free(str);
}
static void	ex_2(void)
{
	char	*str;

	str = ft_multi_strjoin("valgrind ./%s %s", g_name, g_args[arg_i]);
	system(str);
	free(str);
}

static void	ex_3(void)
{
	system("make re");
}

static void	ex_4(void)
{
	system("make fclean");
}

static void	ex_5(void)
{
	return ;
}

#pragma endregion

#pragma region ex_letter

static void	ex_g(void)
{
    char    *order;
    char    *commit = NULL;
	char	c = 0;
	size_t len = 0;
	ssize_t read;
    
	system("cd ..");
	printf("\033]0;GitHub Menu\007");
	while (c != 'q')
	{
		fflush(stdout);
		printf
		(
			"\nChose your git command:\n"
			"\n\033[94m 1\x1b[0m add & commit"
			"\n\033[94m 2\x1b[0m push"
			"\n\033[94m 3\x1b[0m pull"
			"\n\033[94m 4\x1b[0m log"
			"\n ---------"
			"\n\033[36m c\x1b[0m clear screen"
			"\n\033[31m q\x1b[0m to quit"
			"\n\n> "
		);
		scanf(" %c", &c);
		getchar();

		system("clear");

		if (c == 'q')
			break;
		else if (c == '1')
		{
			printf("\nType your commit message: \n> ");
			read = getline(&commit, &len, stdin);
			if (commit[read - 1] == '\n')
				commit[read - 1] = '\0';
			order = ft_multi_strjoin("git add . && git commit -m \"%s\"", commit);
			system(order);
			free(order);
			free(commit);
		}
		else if (c == '2')
			system("git push && git log");
		else if (c == '3')
			system("git pull");
		else if (c == '4')
			system("git log");
	}
	system(g_name);
	system("clear");
}

static void	ex_n(void)
{
	system("clear");
	printf("\033[34mnorminette test (only errors): \033[0m\n");
	system("find . -type d \\( -name '.menu' -o -name 'backups' -o -name 'mlx_linux' \\)"
	" -prune -o -type f \\( -name '*.c' -o -name '*.h' \\)"
	" -exec norminette {} \\; | grep -E 'Error|Warning'");
}

static void	ex_r(void)
{
    system("cc .menu/* -o .menu_exe_temp && mv .menu_exe_temp .menu_exe && ./.menu_exe");
	exit(0);
}

static void	ex_q(void)
{
	system("rm .menu_exe");
	system("clear");
	exit(0);
}

static void ex_b(void)
{
	int nb = 0;
	int fd;
	char *str;
	system("mkdir backups");
	system("ls backups > backups/.bk.txt");
	fd = open("backups/.bk.txt", O_RDONLY);
	while((str = get_next_line(fd)))
	{
		nb = ft_atoi(str);
		free(str);
	}
	nb++;
	str = ft_multi_strjoin("rsync -av --exclude=\".git\" --exclude=\".*\" --exclude=\"backups\" . ./backups/%d",nb);
	system(str);
	system("rm backups/.bk.txt && clear");
	printf("\n\033[32mBackup number %d created\x1b[0m\n", nb);
	free(str);
}

#pragma endregion

static char	main_menu()
{	
	char	c;
	
	fflush(stdout);
	printf("\033]0;Test Menu\007");
	printf
	(
		"\nExecute:\n"
		"\n\033[35m 0\x1b[0m tests menu"
		"\n\033[93m 1\x1b[0m ./fdf"
		"\n\033[93m 2\x1b[0m valgrind ./fdf"
		"\n\033[32m 3\x1b[0m make re"
		"\n\033[32m 4\x1b[0m make fclean"
		"\n ---------"
		"\n\033[94m g\x1b[0m git menu"
		"\n\033[95m n\x1b[0m norminette"
		"\n\033[91m b\x1b[0m create new backup"
		"\n\033[36m c\x1b[0m clear screen"
		"\n\033[31m r\x1b[0m to reload"
		"\n\033[31m q\x1b[0m to quit"
		"\n\n> "
	);
	scanf(" %c", &c);
	return (c);
}

static void	sort_number(char c)
{
	if (c == '0')
		ex_0();
	else if (c == '1')
		ex_1();
	else if (c == '2')
		ex_2();
	else if (c == '3')
		ex_3();
	else if (c == '4')
		ex_4();
	else if (c == 'g')
		ex_g();
	else if (c == 'n')
		ex_n();
	else if (c == 'b')
		ex_b();
	else if (c == 'r')
		ex_r();
	else if (c == 'q')
		ex_q();
}

int	main(void)
{
	char	c;

	c = 0;
	system("clear");
	while (c != 'q')
	{
		c = main_menu();
		system("clear");
		sort_number(c);
	}
}
