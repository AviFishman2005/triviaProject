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
    /// Interaction logic for createRoom.xaml
    /// </summary>
    public partial class createRoom : Window
    {
        public NetworkStream _clientStream;

        public createRoom(NetworkStream n)
        {
            this._clientStream = n;
            InitializeComponent();
            Reset();

        }
        public void Reset()
        {
            inputBoxCount.Text = "5";
            inputRoomName.Text = "room_name";
            inputTta.Text = "4";
            inputMaxPlayers.Text = "3";
        }
        private void createRoomButton_Click(object sender, RoutedEventArgs e)
        {
            uint tta = Convert.ToUInt32(inputTta.Text, 16);
            uint mUsers = Convert.ToUInt32(inputMaxPlayers.Text, 16);
            string name = inputRoomName.Text;
            uint qCount = Convert.ToUInt32(inputBoxCount.Text, 16);


            byte[] buffer = null;

            buffer = createRoomS(tta, mUsers, name, qCount);
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
                Reset();
                errormessage.Text = "Please enter info again";
            }
            else
            {

                room thisRoom = new room(_clientStream, inputRoomName.Text, true);
                thisRoom.Show();
                Close();

                //if room created show the room
            }
          
           
        }
        public byte[] createRoomS(uint tta, uint mUsers, string name, uint qCount)
        {
            createRoomSerialize jsonS = new createRoomSerialize
            {
                answerTimeOut = tta,
                maxUsers = mUsers,
                questionCount = qCount,
                roomName = name,
            };
            string json = JsonConvert.SerializeObject(jsonS);
            string size = json.Length.ToString();

            while (size.Length != 4)
            {
                size = '0' + size;
            }
            
            byte[] buffer = new ASCIIEncoding().GetBytes('6' + size + json);
            return buffer;
        }
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            Menu menu = new Menu(_clientStream);
            menu.Show();
            Close();
        }


    }
}