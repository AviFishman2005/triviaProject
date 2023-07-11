﻿using System;
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
    /// Interaction logic for highScore.xaml
    /// </summary>
    public partial class highScore : Window
    {
        public NetworkStream _clientStream;

        public highScore(NetworkStream n)
        {
            this._clientStream = n;

            InitializeComponent();
            getStatistics();
            //this.BackgroundImage = Properties.Resources.Leaderboard_blog;
        }
        private void getStatistics()
        {
            byte[] buffer = new ASCIIEncoding().GetBytes("b0000");

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
         //   sizeInt = 1000;
            byte[] message = new byte[sizeInt];
            bytesRead = this._clientStream.Read(message, 0, sizeInt);

            string str = Encoding.ASCII.GetString(message);

            statDeserialize response = JsonConvert.DeserializeObject<statDeserialize>(str);
            if (response.status == 1)
            {
                string text = "";
                List<string> listResponse = response.statistics.Split(',').ToList();
                for (int i = 0; i < listResponse.Count() - 1; i+=2)
                {
                    text += listResponse[i] + ": " + listResponse[i+1] + " points\n";
                     
                }
                heighScore.Text = text;

            }
        }
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            Menu menu = new Menu(_clientStream);
            menu.Show();
            Close();
        }
    }
}

