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
    /// Interaction logic for signup.xaml
    /// </summary>
    public partial class signup : Window
    {
        public NetworkStream _clientStream;
        public signup(NetworkStream n)
        {
            this._clientStream = n;
            InitializeComponent();
         
        }
        private void Login_Click(object sender, RoutedEventArgs e)
        {
            login login = new login(this._clientStream);
            login.Show();
            Close();
        }
        private void button2_Click(object sender, RoutedEventArgs e)
        {
            Reset();
        }
        public void Reset()
        {
            textBoxFirstName.Text = "";
            passwordBox1.Password = "";
            emailBox.Text = "";
            errormessage.Text = "";
        }
        private void button3_Click(object sender, RoutedEventArgs e)
        {
            Close();
        }
       
        private void Submit_Click(object sender, RoutedEventArgs e)
        {
           
            string username;
            string email;
            string password;
            byte[] buffer = null;


            username = textBoxFirstName.Text;
            email = emailBox.Text;
            password = passwordBox1.Password;
            buffer = signupS(email, username, password);
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
                Menu menu = new Menu(_clientStream);
                menu.Show();
                Close();
            }
              
        }
        public byte[] signupS(string email, string username, string password)
        {
            signupSerialize jsonS = new signupSerialize
            {
                email = email,
                username = username,
                password = password,
            };
            string json = JsonConvert.SerializeObject(jsonS);
            string size = json.Length.ToString();

            while (size.Length != 4)
            {
                size = '0' + size;
            }
            byte[] buffer = new ASCIIEncoding().GetBytes( '3' + size + json);
            return buffer;
        }
      }

    }

