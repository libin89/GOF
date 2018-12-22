#ifndef _COMMAND_H
#define _COMMAND_H

#define SLOT_AMOUNT 7

typedef struct command_tag {
	void (*execute)(void);
}command_st;

command_st *create_lighton_command(void);
command_st *create_lightoff_command(void);
void delete_command(command_st *cmd);

typedef struct remote_control_tag {
	command_st *on_command;
	command_st *off_command;
	void (*set_command)(struct remote_control_tag *remote_control,
			  int slot, command_st on_command,
			  command_st off_command);
	void (*on_button_pushed)(struct remote_control_tag *remote_control,
			   int slot);
	void (*off_button_pushed)(struct remote_control_tag *remote_control,
				int slot);
}remote_control_st;

remote_control_st *create_remote_control(void);
void delete_remote_control(remote_control_st *remote_control);


#endif
