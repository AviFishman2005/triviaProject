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

    public class getAllRooms
    {

        public static List<saveRoom> getStringAllRoom(NetworkStream clientStream)
        {
            //may have problem with id
            byte[] buffer = new ASCIIEncoding().GetBytes("a0000");

            clientStream.Write(buffer, 0, buffer.Length);
            clientStream.Flush();


            byte[] code = new byte[1];
            byte[] size = new byte[4];
            int bytesRead = clientStream.Read(code, 0, 1);
            bytesRead = clientStream.Read(size, 0, 4);
            string sizeStr = Encoding.ASCII.GetString(size);
            int sizeInt = 0;
            //Way to convert asccii int to int using for loop to insert each value at the righ power
            for (int i = 1; i < 5; i++)
            {

                sizeInt += sizeStr[i - 1] * Convert.ToInt16(Math.Pow(10, (4 - Convert.ToDouble(i)))) + 48;
            }
            byte[] message = new byte[sizeInt];
            bytesRead = clientStream.Read(message, 0, sizeInt);

            string str = Encoding.ASCII.GetString(message);

            getAllRoomsDerialize response = JsonConvert.DeserializeObject<getAllRoomsDerialize>(str);
            
            List<saveRoom> allRooms = new List<saveRoom>();
            string codeChar = Encoding.ASCII.GetString(code);

            if (response.Rooms != "" && codeChar == "a")
            {
                response.Rooms = response.Rooms.Remove(response.Rooms.Length - 1);
                List<string> listStrRooms = response.Rooms.Split(',').ToList();

                for (int i = 0; i < listStrRooms.Count; i += 6)
                {
                    allRooms.Add(new saveRoom() { id = Convert.ToUInt16(listStrRooms[i]), isActive = Convert.ToUInt16(listStrRooms[i + 1]), maxUsers = Convert.ToUInt16(listStrRooms[i + 2]), roomName = listStrRooms[i + 3], questionCount = Convert.ToUInt16(listStrRooms[i + 4]), answerTimeOut = Convert.ToUInt16(listStrRooms[i + 5]) });
                }
            }
            return allRooms;
        }

    }
}
