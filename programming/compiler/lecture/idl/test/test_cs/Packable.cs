using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace Test
{
    public class Packable
    {
        // Throws ExceptionOverflow
        public virtual void Pack(Packer packer, Stream s)
        {
        }

        // Throws ExceptionUnderflow
        public virtual void Unpack(Packer packer, Stream s)
        {

        }
    }
}
