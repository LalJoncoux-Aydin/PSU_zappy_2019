using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;

namespace Client {
    class Program {
        static void Main(string[] args)
        {
            ExecuteClient();
        }
        // main method
        static void ExecuteClient()
        {
            try
            {
                IPHostEntry ipHost = Dns.GetHostEntry(Dns.GetHostName());
                IPAddress ipAddr = ipHost.AddressList[0];
                IPEndPoint localEndPoint = new IPEndPoint(ipAddr, 8000);
                Socket sender = new Socket(ipAddr.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
                byte[] messagebuff = new byte[1024]; 
                try {
                    //sender.Receive(messagebuff);
                    sender.Connect(localEndPoint);
                    byte[] messageSent = Encoding.ASCII.GetBytes("type graphic");
                    int byteSent = sender.Send(messageSent);
                    sender.Send(messageSent);
                    //Thread.Sleep(5000);
                   // 
                    messageSent = Encoding.ASCII.GetBytes("msz");
                    int i = 0;
                    while(0 == i) {
                        Thread.Sleep(50);
                        i = sender.Send(messageSent);
                        Console.WriteLine("i = {0}\n", i);
                    //Console.WriteLine("message msz send");
                        byte[] messageReceived = new byte[1024];
                    
                    ///////////////////////////////////////////////////
                        i = sender.Receive(messageReceived);
                        Console.WriteLine(Encoding.ASCII.GetString(messageReceived,
                                                                   0, i));
                        Console.WriteLine("i = {0}\n", i);
                    ////////////////////////////////////////////////
                    }
                    sender.Shutdown(SocketShutdown.Both);
                    sender.Close();
                }
                catch (ArgumentNullException ane)
                {
                    Console.WriteLine("ArgumentNullException : {0}", ane.ToString());
                }
                catch (SocketException se)
                {
                    Console.WriteLine("SocketException : {0}", se.ToString());
                }
                catch (Exception e)
                {
                    Console.WriteLine("Unexpected exception : {0}", e.ToString());
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
            }
        }
    }
}