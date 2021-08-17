#ifndef MAIN_H
# define MAIN_H

# include <czmq.h>
# include "init_rtv.h"

void	run_cluster(t_rtv *rtv);
void	cluster_request(t_rtv *rtv);
void	network_request_render(zsock_t *requester, t_rtv *rtv);

#endif
