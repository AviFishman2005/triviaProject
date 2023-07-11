using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace client
{
    public class getRoomStateDeserialize
    {
        public uint status { get; set; }
        public bool hasGameBegun { get; set; }
        public string players { get; set; }
        public uint questionCount { get; set; }

        public int answerTimeout { get; set; }
    }
}
