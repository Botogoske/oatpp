/***************************************************************************
 *
 * Project         _____    __   ____   _      _
 *                (  _  )  /__\ (_  _)_| |_  _| |_
 *                 )(_)(  /(__)\  )( (_   _)(_   _)
 *                (_____)(__)(__)(__)  |_|    |_|
 *
 *
 * Copyright 2018-present, Leonid Stryzhevskyi, <lganzzzo@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ***************************************************************************/

#ifndef oatpp_web_client_WebSocketConnector_hpp
#define oatpp_web_client_WebSocketConnector_hpp

#include "./HttpRequestExecutor.hpp"

namespace oatpp { namespace web { namespace client {
  
class WebSocketConnector {
public:
  typedef oatpp::data::stream::IOStream Connection;
  typedef oatpp::async::Action Action;
  typedef Action (oatpp::async::AbstractCoroutine::*AsyncCallback)(const std::shared_ptr<Connection>&);
private:
  std::shared_ptr<oatpp::network::ClientConnectionProvider> m_connectionProvider;
  HttpRequestExecutor m_requestExecutor;
public:
  WebSocketConnector(const std::shared_ptr<oatpp::network::ClientConnectionProvider>& connectionProvider)
    : m_connectionProvider(connectionProvider)
    , m_requestExecutor(connectionProvider)
  {}
public:
  
  static std::shared_ptr<WebSocketConnector> createShared(const std::shared_ptr<oatpp::network::ClientConnectionProvider>& connectionProvider) {
    return std::make_shared<WebSocketConnector>(connectionProvider);
  }
  
  /**
   * Connect to server, do websocket-handshake and return Connection which can be then passed to
   * WebSocket constructor
   * (Blocking call)
   */
  std::shared_ptr<Connection> connect(const oatpp::String& path);
  
  /**
   * Connect to server, do websocket-handshake and return Connection which can be then passed to
   * WebSocket constructor
   * (Async call)
   */
  Action connectAsync(oatpp::async::AbstractCoroutine* parentCoroutine, AsyncCallback callback, const oatpp::String& path);
  
};
  
}}}

#endif /* oatpp_web_client_WebSocketConnector_hpp */
