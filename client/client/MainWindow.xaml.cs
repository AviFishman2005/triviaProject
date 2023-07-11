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
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();



            
            
            communicator connection = new communicator();
            connection.startHandleRequest(4554);
         /*   ThreadStart ts = new ThreadStart(connection.startHandleRequest(4554));
            Thread t = new Thread(ts);
            t.IsBackground = true;
            t.Start();
*/

            Close();
            Thread.Sleep(1000);

        }
        

    }

}
