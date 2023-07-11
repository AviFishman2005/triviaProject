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
    /// <summary>
    /// Interaction logic for Window1.xaml
    /// </summary>
    public partial class room : Window
    {
        public NetworkStream _clientStream;
        public string _roomName;
        public bool _isAdmin;

        Thread t1;
        private SynchronizationContext mainThread;

        public room(NetworkStream n, string roomName, bool isAdmin)
        {
            this._clientStream = n;
            this._roomName = roomName;
            this._isAdmin = isAdmin;
            InitializeComponent();
            //Call function that shows the data on screen
            if(_isAdmin)
            {
                leaveRoom.Content = "close";
            }
            else
            {
                startGame.Content = "your not admin";
                startGame.IsEnabled = false;
            }
            Reset();
            mainThread = SynchronizationContext.Current;
            ThreadStart ts1 = new ThreadStart(updateUsersInRoom);
            t1 = new Thread(ts1);
            t1.SetApartmentState(ApartmentState.STA);
            t1.Start();

        }

        public void updateUsersInRoom()//object sender, DoWorkEventArgs e
        {
            while (true)
            {
                try
                {
                    mainThread.Send((object state) => {

                        getRoomStateDeserialize getRoomStateClass = new getRoomStateDeserialize();
                        getRoomStateClass = getRoomAllState(_clientStream);
                        if(getRoomStateClass != null)
                        {
                            string players = getRoomStateClass.players;
                            players = players.Replace(',', '\n');
                            textNames.Text = "Admin: " + players;
                        }
                        else
                        {
                            leaveRoomCommunication();
                        }
                        
                    }, null);
                    Thread.Sleep(3000);
                }
                catch (Exception)
                {
                }
                
            }
        }
        public getRoomStateDeserialize getRoomAllState(NetworkStream clientStream)
        {
            //may have problem with id
            byte[] buffer = new ASCIIEncoding().GetBytes("g0000");

            clientStream.Write(buffer, 0, buffer.Length);
            clientStream.Flush();


            byte[] code = new byte[1];
            byte[] size = new byte[4];
            int bytesRead = clientStream.Read(code, 0, 1);
            bytesRead = clientStream.Read(size, 0, 4);
            string sizeStr = Encoding.ASCII.GetString(size);
            string codeChar = Encoding.ASCII.GetString(code);

            int sizeInt = 0;
            //Way to convert asccii int to int using for loop to insert each value at the righ power
            for (int i = 1; i < 5; i++)
            {

                sizeInt += sizeStr[i - 1] * Convert.ToInt16(Math.Pow(10, (4 - Convert.ToDouble(i)))) + 48;
            }
            byte[] message = new byte[sizeInt];
            bytesRead = clientStream.Read(message, 0, sizeInt);

            string str = Encoding.ASCII.GetString(message);

            if (codeChar == "g")
            {
                getRoomStateDeserialize response = JsonConvert.DeserializeObject<getRoomStateDeserialize>(str);
                return response;

            }
            else
            {
            
                leaveRoomCommunication();
                Menu menu = new Menu(clientStream);
                menu.Show();
                Close();
                return null;
                
            }
        

        }

        public void Reset()
        {
            textTitle.Text = _roomName;
            //get room state from function
            string players = getRoomAllState(_clientStream).players;

            players = players.Replace(',', '\n');
            textNames.Text = "Admin: " + players;
        }
        private void leaveRoomCommunication()
        {
            t1.Abort();
            if (_isAdmin)
            {
                byte[] buffer = new ASCIIEncoding().GetBytes("c0000");
                _clientStream.Write(buffer, 0, buffer.Length);

            }
            else
            {
                byte[] buffer = new ASCIIEncoding().GetBytes("l0000");
                _clientStream.Write(buffer, 0, buffer.Length);

            }

            _clientStream.Flush();


            byte[] code = new byte[1];
            byte[] size = new byte[4];
            int bytesRead = _clientStream.Read(code, 0, 1);
            bytesRead = _clientStream.Read(size, 0, 4);
            string sizeStr = Encoding.ASCII.GetString(size);

            int sizeInt = 0;
            //Way to convert asccii int to int using for loop to insert each value at the righ power
            for (int i = 1; i < 5; i++)
            {

                sizeInt += sizeStr[i - 1] * Convert.ToInt16(Math.Pow(10, (4 - Convert.ToDouble(i)))) + 48;
            }
            byte[] message = new byte[sizeInt];
            bytesRead = _clientStream.Read(message, 0, sizeInt);

            string str = Encoding.ASCII.GetString(message);

            signDeserializer response = JsonConvert.DeserializeObject<signDeserializer>(str);
            if (response.status == 1)
            {
                Menu menu = new Menu(_clientStream);
                menu.Show();
                Close();
            }
        }
        private void leaveRoom_Click(object sender, RoutedEventArgs e)
        {
            leaveRoomCommunication();
        }

        private void startGame_Click(object sender, RoutedEventArgs e)
        {
            t1.Abort();
            byte[] buffer = new ASCIIEncoding().GetBytes("s0000");
            _clientStream.Write(buffer, 0, buffer.Length);
            _clientStream.Flush();


            byte[] code = new byte[1];
            byte[] size = new byte[4];
            int bytesRead = _clientStream.Read(code, 0, 1);
            bytesRead = _clientStream.Read(size, 0, 4);
            string sizeStr = Encoding.ASCII.GetString(size);
            int sizeInt = 0;
            //Way to convert asccii int to int using for loop to insert each value at the righ power
            for (int i = 1; i < 5; i++)
            {

                sizeInt += sizeStr[i - 1] * Convert.ToInt16(Math.Pow(10, (4 - Convert.ToDouble(i)))) + 48;
            }
            byte[] message = new byte[sizeInt];
            bytesRead = _clientStream.Read(message, 0, sizeInt);

            string str = Encoding.ASCII.GetString(message);

            signDeserializer response = JsonConvert.DeserializeObject<signDeserializer>(str);
            if (response.status == 1)
            {
                textNames.Text = "game begin test works";
            }
        }
    }
}
