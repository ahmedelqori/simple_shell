#include "shell.h"

/**
 * add_rvar_node - adds a variable at the end
 * of a r_var linked list.
 * @head: head of the singly linked list.
 * @lvar: represents length of the variable.
 * @val: represents value of the variable.
 * @lval: represents ength of the value.
 * Return: returns address of the head.
 */
r_var *add_rvar_node(r_var **head, int lvar, char *val, int lval)
{
	r_var *new, *temp;

	new = malloc(sizeof(r_var));
	if (new == NULL)
		return (NULL);

	new->len_var = lvar;
	new->val = val;
	new->len_val = lval;

	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * free_rvar_list - frees a 'r_var' linked list
 * @head: head of the singly linked list.
 * Return: nothing to return.
 */
void free_rvar_list(r_var **head)
{
	r_var *temp;
	r_var *cur;

	if (head != NULL)
	{
		cur = *head;
		while ((temp = cur) != NULL)
		{
			cur = cur->next;
			free(temp);
		}
		*head = NULL;
	}
}
