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
        static string msg_to_server(string msg , Socket sender)
        {
            byte[] messageSent = Encoding.ASCII.GetBytes(msg);
            int byteSent = sender.Send(messageSent);
            byte[] messageReceived = new byte[1024];
            int byteRevc = sender.Receive(messageReceived);
            Console.WriteLine(Encoding.ASCII.GetString(messageReceived, 0, byteRevc));
            return Encoding.ASCII.GetString(messageReceived, 0, byteRevc);
        }

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

                    msg_to_server("msz", sender);
                    msg_to_server("msz", sender);
                    msg_to_server("msz", sender);
                    msg_to_server("mct", sender);
                    //msg_to_server("bct 10 10", sender);

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