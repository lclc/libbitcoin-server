/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin-server.
 *
 * libbitcoin-server is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef LIBBITCOIN_SERVER_EXECUTOR_HPP
#define LIBBITCOIN_SERVER_EXECUTOR_HPP

#include <future>
#include <iostream>
#include <memory>
#include <bitcoin/server.hpp>

namespace libbitcoin {
namespace server {

class executor
  : public enable_shared_from_base<executor>
{
public:
    typedef std::shared_ptr<executor> ptr;

    executor(parser& metadata, std::istream&, std::ostream& output,
        std::ostream& error);

    /// This class is not copyable.
    executor(const executor&) = delete;
    void operator=(const executor&) = delete;

    /// Invoke the command indicated by the metadata.
    bool invoke();

private:
    void attach_query_api();
    void attach_subscription_api();

    void do_help();
    void do_settings();
    void do_version();
    bool do_initchain();

    bool run();
    bool verify();
    bool wait_on_stop();
    void initialize_output();
    void monitor_stop(server_node::result_handler);
    void handle_seeded(const code& ec);
    void handle_synchronized(const code& ec);
    void handle_stopped(const code& ec, std::promise<code>& promise);

    notifier::ptr notify_;
    receiver::ptr receive_;
    publisher::ptr publish_;
    server_node::ptr node_;

    parser& metadata_;
    std::ostream& output_;
    bc::ofstream debug_file_;
    bc::ofstream error_file_;
};

// Localizable messages.
#define BS_SETTINGS_MESSAGE \
    "These are the configuration settings that can be set."
#define BS_INFORMATION_MESSAGE \
    "Runs a full bitcoin node in the global peer-to-peer network."

#define BS_UNINITIALIZED_CHAIN \
    "The %1% directory is not initialized."
#define BS_INITIALIZING_CHAIN \
    "Please wait while initializing %1% directory..."
#define BS_INITCHAIN_NEW \
    "Failed to create directory %1% with error, '%2%'."
#define BS_INITCHAIN_EXISTS \
    "Failed because the directory %1% already exists."
#define BS_INITCHAIN_TRY \
    "Failed to test directory %1% with error, '%2%'."

#define BS_NODE_INTERRUPT \
    "Press CTRL-C to stop the server."
#define BS_NODE_STARTING \
    "Please wait while server is starting..."
#define BS_NODE_START_FAIL \
    "Server failed to start with error, %1%."
#define BS_NODE_STARTED \
    "Blockchain is started."
#define BS_NODE_SEEDED \
    "Seeding is complete."
#define BS_NODE_SYNCHRONIZED \
    "Synchronization is complete."

#define BS_NODE_STOPPING \
    "Please wait while server is stopping (code: %1%)..."
#define BS_NODE_UNMAPPING \
    "Please wait while files are unmapped..."
#define BS_NODE_STOP_FAIL \
    "Server stopped with error, %1%."
#define BS_NODE_STOPPED \
    "Server stopped successfully."

#define BS_USING_CONFIG_FILE \
    "Using config file: %1%"
#define BS_USING_DEFAULT_CONFIG \
    "Using default configuration settings."
#define BS_VERSION_MESSAGE \
    "\nVersion Information:\n\n" \
    "libbitcoin-server:     %1%\n" \
    "libbitcoin-node:       %2%\n" \
    "libbitcoin-blockchain: %3%\n" \
    "libbitcoin:            %4%"
#define BS_LOG_HEADER \
    "================= startup =================="

} // namespace server
} // namespace libbitcoin

#endif
