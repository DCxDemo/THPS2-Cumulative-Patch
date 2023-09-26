using System;
using System.Globalization;
using System.Windows.Forms;

namespace th2patchlauncher
{
    static class Program
    {
        [STAThread]
        static void Main()
        {
            //in case we're gonna parse floats
            CultureInfo ci = (CultureInfo)CultureInfo.CurrentCulture.Clone();
            ci.NumberFormat.NumberDecimalSeparator = ".";
            CultureInfo.CurrentCulture = ci;

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            //create invisible for our awesome -F bypass flag
            var launcher = new LauncherForm() { Visible = false };
            Application.Run(launcher);
        }
    }
}
