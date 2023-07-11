using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace client
{
    public class saveRoom
    {
        public uint id { get; set; }
        public uint isActive { get; set; }
        public uint answerTimeOut { get; set; }
        public uint maxUsers { get; set; }
        public uint questionCount { get; set; }

        public string roomName { get; set; }
    }
}
