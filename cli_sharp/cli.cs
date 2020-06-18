using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Collections.Generic;
using System.IO.Compression;
using System.Linq;

namespace Client {
    public static class Program {

        // main method
        static void Main(string[] args)
        {
            ExecuteClient_alone();
            //ExecuteClient_whit_ai();
        }

        public static string n_word(this string str, int nb) {
            string[] ret = str.Split(' ');
            if (nb > ret.Length)
                return null;
            return ret[nb];
        }

        static string msg_to_server(string msg , Socket sender)
        {
            string res = "";
            try {
                byte[] messageSent = Encoding.ASCII.GetBytes(msg);
                int byteSent = sender.Send(messageSent);
                byte[] bytes = new byte[1024 * 8];
                List<byte[]> recievingBytes = new List<byte[]>();
                List<int> lenghts = new List<int>();
                int lenght;

                do {
                    lenght = sender.Receive(bytes);
                    res += Encoding.ASCII.GetString(bytes, 0, lenght);
                    Console.WriteLine(Encoding.ASCII.GetString(bytes, 0, lenght)); //! PRINT LES MESSAGE RESSU POUR DEBUD/CLARETé
                 } while (lenght != 0);
                //foreach (var msgs_recv in recievingBytes.Zip(lenghts, Tuple.Create)) { //foreach (byte[] recv in recievingBytes) {
                //    res += Encoding.ASCII.GetString(msgs_recv.Item1, 0, msgs_recv.Item2);
                //};
                return res;
            }   catch (ArgumentNullException ane)
            {
                Console.WriteLine("ArgumentNullException : {0}", ane.ToString());
                return null;
            }
            catch (SocketException se)
            {
                return res;
            }
            catch (Exception e)
            {
                Console.WriteLine("Unexpected exception : {0}", e.ToString());
                return null;
            }
        }

        static Socket Connect_client()
        {
            IPHostEntry ipHost = Dns.GetHostEntry(Dns.GetHostName());
            IPAddress ipAddr = ipHost.AddressList[0];
            IPEndPoint localEndPoint = new IPEndPoint(ipAddr, 8000);
            byte[] messageSent = Encoding.ASCII.GetBytes("type graphic");
            Socket sender = new Socket(ipAddr.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
            int byteSent;

            sender.Connect(localEndPoint);
            sender.ReceiveTimeout = 1000; // 700 MINIMUM PLUS Rapid mais plus risqué
            byteSent = sender.Send(messageSent);
            sender.Send(messageSent);
            //Thread.Sleep(50);
            return sender;
        }

        static void ExecuteClient_alone()
        {
            try
            {
                Socket sender = Connect_client();
                string map_size = msg_to_server("msz", sender);
                string tile_x10_y20 = msg_to_server("bct 10 20", sender);
                string map = msg_to_server("mct", sender);

                Console.WriteLine("La map est des size x : {0}; y : {0}", map_size.n_word(1), map_size.n_word(2));
                Console.WriteLine("map : {0}" ,map);
                sender.Shutdown(SocketShutdown.Both);
                sender.Close();
            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
            }
        }

        static void ExecuteClient_whit_ai()
        {
            try
            {
                Socket sender = Connect_client();
                string ppo = msg_to_server("ppo 0", sender);
                string plv = msg_to_server("plv 0", sender);

                //Console.WriteLine("map : {0}" ,map_size);
                sender.Shutdown(SocketShutdown.Both);
                sender.Close();
            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
            }
        }
    }
}