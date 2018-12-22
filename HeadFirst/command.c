#include "command.h"
#include <stdio.h>
#include <stdlib.h>
command_st no_command;

void set_command(struct remote_control_tag *remote_control,
		    int slot, command_st on_command,
		    command_st off_command)
{
	remote_control->on_command[slot] = on_command;
	remote_control->off_command[slot] = off_command;
}
void on_button_pushed(struct remote_control_tag *remote_control,
			 int slot)
{
	remote_control->on_command[slot].execute();
}
void off_button_pushed(struct remote_control_tag *remote_control,
			  int slot)
{
	remote_control->off_command[slot].execute();
}

remote_control_st *create_remote_control(void)
{
	remote_control_st *remote_control = NULL;
	int i;

	remote_control = (remote_control_st *)malloc(sizeof(remote_control_st));
	if(!remote_control)
		printf("malloc error.\n");
	
	remote_control->on_command = (command_st *)malloc(sizeof(command_st) * SLOT_AMOUNT);
	if(!(remote_control->on_command)){
		free(remote_control);
		printf("malloc error.\n");
	}	
	remote_control->off_command = (command_st *)malloc(sizeof(command_st) * SLOT_AMOUNT);
	if(!(remote_control->off_command)){
		free(remote_control->on_command);
		free(remote_control);
		printf("malloc error.\n");
	}

	for(i = 0; i < SLOT_AMOUNT; i++) {
		remote_control->on_command[i] = no_command;
		remote_control->off_command[i] = no_command;
	}
	
	remote_control->set_command = set_command;
	remote_control->on_button_pushed = on_button_pushed;
	remote_control->off_button_pushed = off_button_pushed;

	return remote_control;
}

void delete_remote_control(remote_control_st *remote_control)
{
	if(remote_control) {
		if(remote_control->on_command)
			free(remote_control->on_command);
		if(remote_control->off_command)
			free(remote_control->off_command);

		free(remote_control);
	}
}


void lighton(void)
{
	printf("Light on.\n");
}

void lightoff(void)
{
	printf("Light off.\n");
}

command_st *create_lighton_command(void)
{
	command_st *cmd;
	
	cmd = (command_st *)malloc(sizeof(command_st));
	if(!cmd) {
		printf("malloc error.\n");
	}
	cmd->execute = lighton;

	return cmd;
}

command_st *create_lightoff_command(void)
{
	command_st *cmd;
	
	cmd = (command_st *)malloc(sizeof(command_st));
	if(!cmd) {
		printf("malloc error.\n");
	}
	cmd->execute = lightoff;

	return cmd;
}

void delete_command(command_st *cmd)
{
	if(cmd) {
		free(cmd);
		cmd = NULL;
	}
}

void print_remote_control(remote_control_st *remote_control)
{
	int i;

	for(i = 0; i < SLOT_AMOUNT; i++) {
		if(remote_control->on_command[i].execute == NULL)
			printf("[slot %d] on_command, No command. ", i);
		else
			printf("[slot %d] on_command, Has command. ", i);
		if(remote_control->off_command[i].execute == NULL)
			printf("[slot %d] off_command, No command.\n", i);
		else
			printf("[slot %d] off_command, Has command.\n", i);
	}	
}

#ifdef COMMAND
int main(void)
{
	command_st *lighton_cmd = create_lighton_command();
	command_st *lightoff_cmd = create_lightoff_command();
	remote_control_st *remote_control = create_remote_control();

	remote_control->set_command(remote_control, 0, *lighton_cmd, *lightoff_cmd);

	print_remote_control(remote_control);

	remote_control->on_button_pushed(remote_control, 0);
	remote_control->off_button_pushed(remote_control, 0);

	delete_command(lighton_cmd);
	delete_command(lightoff_cmd);
	delete_remote_control(remote_control);
}
#endif

