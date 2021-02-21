/*
 * Copyright (c) 2018-2022 curoky(cccuroky@gmail.com).
 *
 * This file is part of learn-rpc.
 * See https://github.com/curoky/learn-rpc for further info.
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
 */
package main

import (
	"context"
	"fmt"
	"net"
	"net/netip"

	"github.com/apache/thrift/lib/go/thrift"
	"github.com/curoky/learn-rpc/tutorial/thrift/echo/idl/gen-go/echo"
)

type EchoHandler struct {
}

func NewEchoHandler() *EchoHandler {
	return &EchoHandler{}
}

func (p *EchoHandler) Echo(ctx context.Context, req *echo.Req) (rsp *echo.Rsp, err error) {
	fmt.Println("request: ", req.Message)
	return &echo.Rsp{Message: req.Message}, nil
}

func main() { //nolint
	socket := thrift.NewTServerSocketFromAddrTimeout(
		net.TCPAddrFromAddrPort(
			netip.MustParseAddrPort("0.0.0.0:2301")), 0)
	processor := echo.NewEchoProcessor(NewEchoHandler())
	// transportFactory := thrift.NewTBufferedTransportFactory(1024)
	transportFactory := thrift.NewTFramedTransportFactoryConf(thrift.NewTTransportFactory(),
		&thrift.TConfiguration{})
	server := thrift.NewTSimpleServer4(processor, socket, transportFactory,
		thrift.NewTBinaryProtocolFactoryDefault())

	fmt.Println("Starting the simple server... on 2301")
	server.Serve()
}
