/****************************************************************************
*
*                           Klepsydra Core Modules
*              Copyright (C) 2019-2020  Klepsydra Technologies GmbH
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
****************************************************************************/

#ifndef CONNECT_SOCKET_H
#define CONNECT_SOCKET_H

#include <klepsydra/socket_core/data_socket.h>

namespace kpsr
{
namespace socket_mdlw
{

/**
 * @brief The ConnectSocket class
 *
 * @copyright Klepsydra Technologies 2019-2020.
 *
 * @version   2.1.0
 *
 * @ingroup kpsr-sockets-internal
 *
 * @details A class the conects to a remote machine. Allows read/write accesses to the remote machine.
 */
class ConnectSocket: public DataSocket
{
public:
    /**
     * @brief ConnectSocket
     * @param host
     * @param port
     */
    ConnectSocket(std::string const& host, int port);

    /**
     * @brief ConnectSocket
     * @param path
     */
    ConnectSocket(std::string path);
};

}
}

#endif

