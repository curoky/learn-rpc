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
	"log"
	"os"

	"github.com/apache/thrift/lib/go/thrift"
	thrifter "github.com/thrift-iterator/go"
	"github.com/thrift-iterator/go/general"
	cli "github.com/urfave/cli/v2"
)

type ProxyServer struct {
	serverSocket *thrift.TServerSocket
	proxyToIP    string
	proxyToPort  int
}

func CreateProxyServer(listenIP string, listenPort int, proxyToIP string, proxyToPort int) *ProxyServer {
	serverSocket, err := thrift.NewTServerSocket(fmt.Sprintf("%s:%d", listenIP, listenPort))
	if err != nil {
		panic(err)
	}
	return &ProxyServer{
		serverSocket: serverSocket,
		proxyToIP:    proxyToIP,
		proxyToPort:  proxyToPort,
	}
}

func (p *ProxyServer) Serve() {
	err := p.serverSocket.Listen()
	if err != nil {
		panic(err)
	}

	for {
		client, err := p.serverSocket.Accept()
		if err != nil {
			panic(err)
		}
		if client != nil {
			go func() {
				defer client.Close()

				decoder := thrifter.NewDecoder(client, []byte{})
				var message general.Message
				if err != decoder.Decode(&message) {
					panic(err)
				}

				socket := thrift.NewTSocketConf(
					fmt.Sprintf("%s:%d", p.proxyToIP, p.proxyToPort),
					&thrift.TConfiguration{},
				)

				transport := thrift.NewTFramedTransportConf(socket, &thrift.TConfiguration{})
				defer transport.Close()
				if err := transport.Open(); err != nil {
					panic(err)
				}
				if err != thrifter.NewEncoder(transport).Encode(&message) {
					panic(err)
				}
				transport.Flush(context.Background())
				_, err = transport.Read([]byte{})
				if err != nil {
					panic(err)
				}
				rsp := make([]byte, transport.RemainingBytes())
				cnt, err := transport.Read(rsp)
				if err != nil {
					panic(err)
				}
				fmt.Println("rsp:", cnt)
				_, err = client.Write(rsp)
				if err != nil {
					panic(err)
				}
				// buf, _ := thrifter.MarshalMessage(message)
				// js, _ := thrifter.ToJSON(buf)
				// fmt.Println(js)
			}()
		}
	}
}

func main() {
	app := &cli.App{
		// Name: "Buffered to Framed",
		// Usage: "",
		Flags: []cli.Flag{
			&cli.StringFlag{
				Name:  "listen-ip",
				Value: "0.0.0.0",
			},
			&cli.IntFlag{
				Name:  "listen-port",
				Value: 2300,
			},
			&cli.StringFlag{
				Name:  "proxy-to-ip",
				Value: "0.0.0.0",
			},
			&cli.IntFlag{
				Name:  "proxy-to-port",
				Value: 2301,
			},
		},
		Action: func(c *cli.Context) error {
			server := CreateProxyServer(c.String("listen-ip"), c.Int("listen-port"), c.String("proxy-to-ip"), c.Int("proxy-to-port"))
			server.Serve()
			return nil
		},
	}

	err := app.Run(os.Args)
	if err != nil {
		log.Fatal(err)
	}
}
