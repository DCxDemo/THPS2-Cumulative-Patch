using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace thps2patch
{
    public partial class Options
    {
        /// <summary>
        /// A predefined list of resolutions to use in the dropdown list. 
        /// </summary>
        Dictionary<string, string> _resolutions = new Dictionary<string, string>
        {
            {"320x240", "4:3"},
            {"640x480", "4:3"},
            {"800x600", "4:3"},
            {"1024x768", "4:3"},
            {"1440x1080", "4:3" },
            {"1600x1200", "4:3"},
            {"2048x1536", "4:3"},

            { "1280x1024", "5:4" },
            { "1350x1080", "5:4" },

            {"1280x720", "16:9"},
            {"1366x768", "16:9" },
            {"1600x900", "16:9"},
            {"1920x1080", "16:9"},
            {"2048x1152", "16:9"}

            //{"2560x1440", "16:9"} // 2048x2048 is ddraw limit
        };
    }
}