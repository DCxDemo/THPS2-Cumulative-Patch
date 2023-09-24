using System;
using System.Windows.Forms;

namespace th2patchlauncher
{
    static class Program
    {
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            var launcher = new LauncherForm();
            launcher.Visible = false;
            Application.Run(launcher);
        }
    }
}
