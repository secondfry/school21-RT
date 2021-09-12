/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network_render.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 14:46:38 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/12 13:40:35 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NETWORK_RENDER_H
# define NETWORK_RENDER_H

# include <czmq.h>
# include "rtv.h"

void	network_request_render(zsock_t *requester, t_rtv *rtv);
void	network_request_cleanup(zsock_t *requester);

#endif
