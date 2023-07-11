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
    /// Interaction logic for statistics.xaml
    /// </summary>
    public partial class statistics : Window
    {
        public NetworkStream _clientStream;

        public statistics(NetworkStream n)
        {
            this._clientStream = n;

            InitializeComponent();
        }

        private void button_high_score_Click(object sender, RoutedEventArgs e)
        {

        }

        private void button_personal_stats_Click(object sender, RoutedEventArgs e)
        {
            personalStatistics stats = new personalStatistics(_clientStream);
            Close();
            stats.Show();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            Menu menu = new Menu(_clientStream);
            menu.Show();
            Close();
        }
    }
}
