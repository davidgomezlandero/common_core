/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 19:18:02 by davigome          #+#    #+#             */
/*   Updated: 2025/01/04 12:27:42 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"

typedef struct s_stack
{
	int				value;
	int				index;
	int				pos;
	int				target_pos;
	int				cost_a;
	int				cost_b;
	struct s_stack	*next;
}					t_stack;

typedef struct s_nums
{
	char			**values;
	int				num_of_values;
	int				*list;
}					t_nums;

// FT_CHECKS.C //
void				ft_checks(char **argv, t_nums *nums);
void				ft_alloc_mem_values(char **argv, t_nums *nums);
void				ft_cpy_values(char **argv, t_nums *nums);
void				ft_check_sign_digit(t_nums *nums);
void				ft_not_digit(t_nums *nums);

// FT_CHECKS_2.C
void				ft_atoi_list_and_max_min(t_nums *nums);
void				ft_check_reps(t_nums *nums);
void				ft_check_sort(t_nums *nums);
void				ft_nothing_after_sign(t_nums *nums);
void				ft_more_sign(t_nums *nums);

// FT_FREES.C //
void				ft_free_nums(t_nums *nums);
void				ft_free_stack(t_stack **stack);

// FT_UTILS.C //
long long			ft_atoi_long(const char *str);
t_stack				*ft_newlst_value(t_nums *nums, int i);
void				ft_addback_lst(t_stack **stack, t_stack *new);
void				ft_sort(t_nums *nums);

// FT_UTILS_2.C //
void				ft_addfront_lst(t_stack **stack, t_stack *new);
void				ft_calculate_pos(t_stack **stack);
void				ft_initialize_positions(t_stack **stack_a,
						t_stack **stack_b);
int					ft_find_min_position(t_stack **stack_a);
void				ft_update_target(t_stack **stack_a, t_stack *temp_b,
						int pos_min);

// FT_UTILS_3.C //
void				ft_target_pos(t_stack **stack_a, t_stack **stack_b);
void				ft_calculate_cost(t_stack **stack_a, t_stack **stack_b);
int					ft_the_cheap(t_stack **stack_b);
int					ft_size_lst(t_stack **stack);

// FT_START.C //
void				ft_two_values(t_nums *nums);
void				ft_three_values(t_nums *nums);
void				ft_select_algorithm(t_nums *nums);
void				ft_more_values(t_nums *nums);

// FT_START_2.C //
void				ft_move_cheap_to_stack_a(t_stack **stack_a,
						t_stack **stack_b);
void				ft_handle_costs(t_stack **stack_a, t_stack **stack_b,
						t_stack *temp);
void				ft_handle_individual_costs(t_stack **stack_a,
						t_stack **stack_b, t_stack *temp);
void				ft_values_to_stack_a(t_stack **stack_a, t_nums *nums);
void				ft_index_to_stack_a(t_stack **stack_a, t_nums *nums);

// FT_START_3.C //
void				ft_sort_three(t_stack **stack);
void				ft_tostackb_vague(t_stack **stack_a, t_stack **stack_b,
						t_nums *nums);
void				ft_tostackb_vague_2(t_stack **stack_a, t_stack **stack_b);
void				ft_rotate_order(t_stack **stack_a, t_stack **stack_b);

// FT_MOVES.C //
void				ft_ra(t_stack **stack_a);
void				ft_rb(t_stack **stack_b);
void				ft_rra(t_stack **stack_a);
void				ft_rrb(t_stack **stack_b);
void				ft_sa(t_stack **stack_a);

// FT_MOVES_2.C //
void				ft_pb(t_stack **stack_a, t_stack **stack_b);
void				ft_pa(t_stack **stack_a, t_stack **stack_b);
void				ft_moves(t_stack **stack_a, t_stack **stack_b, int move);
void				ft_moves_2(t_stack **stack_a, t_stack **stack_b, int move);

#endif
