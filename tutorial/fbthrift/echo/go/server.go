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
	"fmt"

	// "github.com/curoky/learn-rpc/tutorial/fbthrift/echo/idl/gen-go/echo"
	"github.com/curoky/learn-rpc/tutorial/fbthrift/echo/idl/gen-go/echo"
	thrift "github.com/facebook/fbthrift/thrift/lib/go/thrift"
)

type EchoHandler struct {
}

func NewEchoHandler() *EchoHandler {
	return &EchoHandler{}
}

func (p *EchoHandler) Echo(req *echo.Req) (rsp *echo.Rsp, err error) {
	fmt.Println("request: ", req.Message)
	return &echo.Rsp{Message: req.Message}, nil
}

func main() { //nolint
	socket, err := thrift.NewServerSocket("0.0.0.0:2300")
	if err != nil {
		panic(err)
	}

	processor := echo.NewEchoProcessor(NewEchoHandler())
	transportFactory := thrift.NewBufferedTransportFactory(1024)
	server := thrift.NewSimpleServer4(processor, socket, transportFactory,
		thrift.NewBinaryProtocolFactoryDefault())

	fmt.Println("Starting the simple server... on 2300")
	server.Serve()
}
