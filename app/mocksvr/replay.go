// Reference: https://www.linode.com/docs/development/go/developing-udp-and-tcp-clients-and-servers-in-go/
package main

import (
	"fmt"
	"net"
	"os"
	"time"
)

func main() {
	arguments := os.Args
	if len(arguments) == 1 {
		fmt.Println("Please provide port number")
		return
	}

	PORT := ":" + arguments[1]
	l, err := net.Listen("tcp", PORT)
	if err != nil {
		fmt.Println(err)
		return
	}

	fmt.Printf("Listening to port %s\n", arguments[1])
	defer l.Close()

	for {
		conn, err := l.Accept()
		if err != nil {
			fmt.Println(err)
		}
		go handleConnection(conn)
	}

}

func handleConnection(conn net.Conn) {

	fmt.Printf("Incoming connection from %v\n", conn.LocalAddr)

	var buf = make([]byte, 1)

	bytesIncoming := 0

	for {

		//Force a timeout before attempting to read a byte
		conn.SetReadDeadline(time.Now().Add(100 * time.Millisecond))
		bytesRead, err := conn.Read(buf)

		if err != nil {
			fmt.Println()
			fmt.Println(err)
			break
		}

		bytesIncoming += bytesRead

		conn.Write(buf)
		fmt.Print(string(buf))
	}

	conn.Close()

	fmt.Printf("\nConnection closed of %v, bytesRead %d \n", conn.LocalAddr, bytesIncoming)

}
