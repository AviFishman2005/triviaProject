using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Net.Sockets;
using System.Net;
using System.Threading;
using Newtonsoft.Json;

namespace client
{ 
    internal class communicator
    {
        public NetworkStream _clientStream;
        public void startHandleRequest(int port)
        {
            TcpClient client = new TcpClient();
            IPEndPoint serverEndPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), port);
            client.Connect(serverEndPoint);
            this._clientStream = client.GetStream();
            this.handleNewClient();
        }
        public void handleNewClient()
        {
            login loginWindow = new login(this._clientStream);

            loginWindow.Show();

           

        }
    }
}
