using System;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Text;

static void Main(string[] args)
{
    IPEndPoint serverEndPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 3000);
    using ( TcpClient client = new TcpClient() )
    {
        client.Connect(serverEndPoint);

        using ( BinaryWriter writer = new BinaryWriter(client.GetStream(), Encoding.ASCII) )
        {
                writer.Write("type ai");
                writer.Write("msz");

        }
    }
}
