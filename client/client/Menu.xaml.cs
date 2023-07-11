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
    /// Interaction logic for Menu.xaml
    /// </summary>
    public partial class Menu : Window
    {
        public NetworkStream _clientStream;

        public Menu(NetworkStream n)
        {
            this._clientStream = n;

            InitializeComponent();
        }
        private void creatRoomB_Click(object sender, RoutedEventArgs e)
        {
            createRoom cRoom = new createRoom(_clientStream);
            Close();
            cRoom.Show();
        }

        private void signout_button_Click(object sender, RoutedEventArgs e)
        {

            byte[] buffer = new ASCIIEncoding().GetBytes("50000");

            _clientStream.Write(buffer, 0, buffer.Length);
            _clientStream.Flush();


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
            if (response.status == 1)
            {
                login l = new login(_clientStream);
                l.Show();
                Close();
            
            }

        }

        private void statsB_Click(object sender, RoutedEventArgs e)
        {
            personalStatistics stats = new personalStatistics(_clientStream);
            Close();
            stats.Show();
        }

        private void statsA_Click(object sender, RoutedEventArgs e)
        {
            highScore stats = new highScore(_clientStream);
            Close();
            stats.Show();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            joinRoom jRoom = new joinRoom(_clientStream);
            Close();
            jRoom.Show();
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {

        }
    }
}
