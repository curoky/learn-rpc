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

//go:generate thrift --gen go -o ../idl ../idl/echo.thrift

import (
	"context"

	"github.com/apache/thrift/lib/go/thrift"
	"github.com/curoky/learn-rpc/tutorial/thrift/echo/idl/gen-go/echo"
)

func main() { //nolint
	ctx := context.Background()
	socket := thrift.NewTSocketConf("0.0.0.0:2300", &thrift.TConfiguration{})
	transport := thrift.NewTBufferedTransport(socket, 1024)
	defer transport.Close()
	if err := transport.Open(); err != nil {
		panic(err)
	}
	client := echo.NewEchoClientFactory(transport, thrift.NewTBinaryProtocolFactoryDefault())
	req := echo.Req{Message: "hello"}
	rsp, err := client.Echo(ctx, &req)
	if err != nil {
		panic(err)
	}
	println(rsp.Message)
}
