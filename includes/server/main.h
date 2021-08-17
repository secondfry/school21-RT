#ifndef MAIN_H
# define MAIN_H

# include <czmq.h>
# include "init_rtv.h"

typedef struct s_params {
	t_rtv	*rtv;
	int		*data;
	short	ya;
	short	yb;
	short	xa;
	short	xb;
}				t_params;

# define THREAD_COUNT 8

t_byte	handle_typed_message(zsock_t *reader, t_rtv *rtv, char *id);
t_byte	handle_render(t_rtv *rtv, zsock_t *reader);

#endif
