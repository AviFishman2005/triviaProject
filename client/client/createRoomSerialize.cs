using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace client
{
    internal class createRoomSerialize
    {
        public uint answerTimeOut { get; set; }
        public uint maxUsers { get; set; }
        public uint questionCount { get; set; }

        public string roomName { get; set; }
    }
}
