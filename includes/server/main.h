#ifndef MAIN_H
# define MAIN_H

# include <czmq.h>
# include "init_rtv.h"

t_byte	handle_typed_message(zsock_t *reader, t_rtv *rtv, char *id);

#endif
