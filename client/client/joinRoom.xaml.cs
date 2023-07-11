using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
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
using System.ComponentModel;

namespace client
{
    /// <summary>
    /// Interaction logic for joinRoom.xaml
    /// </summary>
    public partial class joinRoom : Window
    {
        public NetworkStream _clientStream;
        public List<saveRoom> _allRooms;
        Thread t1;

        private SynchronizationContext mainThread;


        public joinRoom(NetworkStream n)
        {
            this._clientStream = n;
            InitializeComponent();
            mainThread = SynchronizationContext.Current;

            Reset();
            ThreadStart ts1 = new ThreadStart(updateRooms);
            t1 = new Thread(ts1);
            t1.SetApartmentState(ApartmentState.STA);
            t1.Start();
            

            //Call function that sets the join room data 

        }

        public void updateRooms()//object sender, DoWorkEventArgs e
        {
            while (true)
            {
                mainThread.Send((object state) => {
                    _allRooms = getAllRooms.getStringAllRoom(this._clientStream);
                    textRooms.Text = "";
                    for (int i = 0; i < _allRooms.Count; i++)
                    {
                        textRooms.Text += _allRooms[i].roomName + "  "+_allRooms[i].id + "\n";
                    }
                }, null);
                Thread.Sleep(3000);
            }
        }

        //Send join room request to server and recieve confermation and join the room
        private void createRoomButton_Click(object sender, RoutedEventArgs e)
        {
            t1.Abort();
            byte[] buffer = null;
            uint roomId = Convert.ToUInt32(inputRoomId.Text, 16);
            buffer = joinRoomS(roomId);
            this._clientStream.Write(buffer, 0, buffer.Length);
            this._clientStream.Flush();


            byte[] code = new byte[1];
            byte[] size = new byte[4];
            int bytesRead = this._clientStream.Read(code, 0, 1);
            bytesRead = this._clientStream.Read(size, 0, 4);
            string sizeStr = Encoding.ASCII.GetString(size);
            int sizeInt = 0;
            //Way to convert asccii int to int using for loop to insert each value at the righ power
            for (int i = 1; i < 5; i++)
            {

                sizeInt += sizeStr[i - 1] * Convert.ToInt16(Math.Pow(10, (4 - Convert.ToDouble(i)))) + 48;
            }
            byte[] message = new byte[sizeInt];
            bytesRead = this._clientStream.Read(message, 0, sizeInt);

            string str = Encoding.ASCII.GetString(message);

            signDeserializer response = JsonConvert.DeserializeObject<signDeserializer>(str);
            if (response.status != 1)
            {
                joinRoom jRoom = new joinRoom(_clientStream);
                Close();
                jRoom.Show();
            }
            else
            {
                string roomName = "";
                //Get room name and enter room
                for (int i = 0; i < _allRooms.Count; i++)
                {
                    if(_allRooms[i].id == Convert.ToUInt16(inputRoomId.Text))
                    {
                        roomName = _allRooms[i].roomName;
                    }
                }
                room thisRoom = new room(_clientStream, roomName , false);
                thisRoom.Show();
                Close();
                //if room joind show the room
            }
        }
        public void Reset()
        {
            inputRoomId.Text = "999";
            //Gets all rooms to desplay them from the get all rooms function
            _allRooms = getAllRooms.getStringAllRoom(this._clientStream);
            textRooms.Text = "";
            for (int i = 0; i < _allRooms.Count; i++)
            {
                textRooms.Text += _allRooms[i].roomName + "  "+_allRooms[i].id + "\n";
            }

        }
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            t1.Abort();
            Menu menu = new Menu(_clientStream);
            menu.Show();
            Close();
        }

        public byte[] joinRoomS(uint id)
        {
            t1.Abort();
            roomIdSerialize jsonS = new roomIdSerialize
            {
                roomId = id,
            };
            string json = JsonConvert.SerializeObject(jsonS);
            string size = json.Length.ToString();

            while (size.Length != 4)
            {
                size = '0' + size;
            }
            byte[] buffer = new ASCIIEncoding().GetBytes('7' + size + json);
            return buffer;
        }
    }
}
