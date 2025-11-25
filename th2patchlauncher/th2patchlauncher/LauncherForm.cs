using System;
using System.Diagnostics;
using System.IO;
using System.Windows.Forms;
using System.Windows.Forms.VisualStyles;
using thps2patch;

namespace th2patchlauncher
{
    public partial class LauncherForm : Form
    {
        Options op;

        public LauncherForm()
        {
            InitializeComponent();
        }

        string curDir = Directory.GetCurrentDirectory();
        string hawkFile = "THawk2.exe";
        string thawk2filePath => Path.Combine(curDir, hawkFile);

        string configFile = "th2_opt.cfg";
        string configFilePath => Path.Combine(curDir, configFile);

        string patchPath = "patch";
        string levelsFile = "levelpatch.ini";
        string userFile = "userpatch.ini";

        private bool ForcedLaunchRequested(string[] args)
        {
            foreach (var a in args)
            {
                var arg = a.ToUpper();

                //process both minus and slash
                if (arg == "-F" || arg == "/F")
                {
                    //setup form visibility params
                    ShowInTaskbar = false;
                    WindowState = FormWindowState.Minimized;
                    Visible = false;

                    Hide();

                    //wait for the game
                    LaunchTHPS(false);

                    //shutdown
                    Close();

                    return true;
                }
            }

            return false;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            try
            {
                //load options from files
                op = new Options(configFilePath);

                //parse command line, if -F is there, apply patches and quit
                if (!ForcedLaunchRequested(Environment.GetCommandLineArgs()))
                {
                    //if no args, setup UI
                    UpdateControls();
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Something went wrong!\r\n{ex.Message}\r\n\r\n{ex.ToString()}", "Error");
            }
        }

        /// A list of chars to swap officer dick, must coincide with the patch.
        public enum DickSwap
        {
            none = 0,
            bam = 1,
            wolve = 2,
            lilper = 3,
            kor1 = 4,
            kor2 = 5,
            mcsqueeb = 6
        }

        // TO DO: Split settings here in regions, maybe separte functions as well

        private void UpdateControls()
        {
            gameBox.Text = op.GetString("Patch", "Game", "THPS2");
            op.Game = gameBox.Text;

            if (!File.Exists(Path.Combine(".\\", patchPath, levelsFile)))
            {
                op.Game = "THPS2";
                op.SetString("Patch", "Game", "THPS2");
                gameBox.Enabled = false;
            }

            userPatchBox.Checked = op.GetBool("Patch", "UserPatch", true);

            if (!File.Exists(Path.Combine(".\\", patchPath, userFile)))
            {
                op.UserPatch = false;
                userPatchBox.Enabled = false;
                op.SetBool("Patch", "UserPatch", false);
            }


            altSkinsBox.Checked = op.GetBool("Patch", "MoreSkins", false);
            swapBox.Enabled = altSkinsBox.Checked;

            switch (op.GetString("Patch", "DickSwap", "dick").ToLower())
            {
                case "bam": swapBox.SelectedIndex = (int)DickSwap.bam; break;
                case "wolve": swapBox.SelectedIndex = (int)DickSwap.wolve; break;
                case "lilper": swapBox.SelectedIndex = (int)DickSwap.lilper; break;
                case "kor1": swapBox.SelectedIndex = (int)DickSwap.kor1; break;
                case "kor2": swapBox.SelectedIndex = (int)DickSwap.kor2; break;
                case "mcsqueeb": swapBox.SelectedIndex = (int)DickSwap.mcsqueeb; break;

                default: swapBox.SelectedIndex = (int)DickSwap.none; break;
            }


            skipIntroBox.Checked = op.GetBool("Patch", "SkipIntro", true);
            separateSaveBox.Checked = op.GetBool("Patch", "SeparateSaves", true);

            //patch tab

            switch (gameBox.Text.ToUpperInvariant())
            {
                case "THPS1": gameBox.SelectedIndex = 1; break;
                case "THPS3": gameBox.SelectedIndex = 2; break;
                case "THPS4": gameBox.SelectedIndex = 3; break;
                case "MHPB": gameBox.SelectedIndex = 4; break;
                default: gameBox.SelectedIndex = 0; break;
            }



            force32box.Checked = op.GetBool("Video", "Force32Bpp", false);
            unlockFPSbox.Checked = op.GetBool("Video", "UnlockFPS", false);
            rendererBox.Checked = op.GetString("Video", "Renderer", "Hardware") == "Software" ? true : false;
            psxtexBox.Checked = op.GetBool("Video", "DisableNewtex", false);
            drawshadowBox.Checked = op.GetBool("Video", "DrawShadow", true);
            drawhudBox.Checked = op.GetBool("Video", "ShowHUD", true);
            filterBox.Checked = op.GetBool("Video", "TextureFiltering", true);

            op.SetResolution(
                op.GetInt("Video", "ResX", Options.DefaultResolution.Width),
                op.GetInt("Video", "ResY", Options.DefaultResolution.Height)
            );

            op.setResAspectText(resBox, aspectRatioDrop, op.ResolutionString);



            //read fov data
            op.FovScale = op.GetFloat("Video", "FovScale", 1f);
            UpdateFOVbar();

            //maybe fov override?
            overrideFOVbox.Checked = op.GetBool("Video", "OverrideFov", false);



            int fogValue = op.GetInt("Video", "FogScale", 300);
            fogSlider.Value = (int)Math.Sqrt((fogValue - 10) * fogSlider.Maximum);
            fogLabel.Text = fogValue.ToString();
            op.fog = fogValue;


            ambienceBox.Checked = op.GetBool("Music", "PlayAmbience", true);
            fadeBox.Checked = op.GetBool("Music", "Fade", true);
            randomBox.Checked = op.GetBool("Music", "Random", true);
            titleBox.Checked = op.GetBool("Music", "ShowTitle", true);
            separateTracksBox.Checked = op.GetBool("Music", "SeparateTracks", false);





            skyBox.Checked = op.GetBool("Patch", "DisableSky", false);
            railBarBox.Checked = op.GetBool("Patch", "RailBalanceBar", true);

            manualsBox.Checked = op.GetBool("Input", "Manuals", true);
            bigDropBox.Checked = op.GetBool("Input", "BigDrop", true);
            xinputBox.Checked = op.GetBool("Input", "XInput", true);
            vibrationBox.Checked = op.GetBool("Input", "Vibration", true);
            autokickBox.Checked = op.GetBool("Input", "AutoKick", true);


            this.Visible = true;
        }

        private void detectButtonClick(object sender, EventArgs e)
        {
            op.SetResolution();
            op.setResAspectText(resBox, aspectRatioDrop, op.ResolutionString);
        }





        public void LaunchTHPS(bool saveParams)
        {
            //wrong exe should lead to exit before trying to patch.
            if (!File.Exists("Thawk2.exe"))
            {
                MessageBox.Show(ErrorMsg.Thawk2NotFound, "Warning");
                return;
            }

            if (Helpers.FileLocked("Thawk2.exe"))
            {
                MessageBox.Show(ErrorMsg.Thawk2InUse, "Warning");
                return;
            }

            if (!Helpers.isSmallerExe(thawk2filePath))
            {
                MessageBox.Show(ErrorMsg.Thawk2NotSmaller, "Warning");
                return;
            }

            try
            {
                if (saveParams) op.Save();

                Process.Start($".\\{hawkFile}");

                var mp = new MainPatch(op);
                mp.Patch();

                Application.Exit();
            }
            catch (Exception ex)
            {
                MessageBox.Show("oops!\r\n\r\n" + ex.ToString(), ex.Message);
            }
        }

        private void launchButtonClick(object sender, EventArgs e)
        {
            LaunchTHPS(true);
        }

        private void quitButtonClick(object sender, EventArgs e)
        {
            op.Save();
            Application.Exit();
        }

        #region [General tab]

        private void altSkinsBox_CheckedChanged(object sender, EventArgs e)
        {
            op.SetBool("Patch", "MoreSkins", (sender as CheckBox).Checked);
            swapBox.Enabled = altSkinsBox.Checked;
        }

        private void swapBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            op.SetString("Patch", "DickSwap", ((DickSwap)((sender as ComboBox).SelectedIndex)).ToString());
        }

        private void skipIntroBox_CheckedChanged(object sender, EventArgs e)
        {
            op.SetBool("Patch", "SkipIntro", (sender as CheckBox).Checked);
        }

        private void separateSaveBox_CheckedChanged(object sender, EventArgs e)
        {
            op.SetBool("Patch", "SeparateSaves", (sender as CheckBox).Checked);
        }

        private void gameBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            op.SetString("Patch", "Game", (sender as ComboBox).Text);
        }

        #endregion

        #region [Video tab]

        private void rendererBox_CheckedChanged(object sender, EventArgs e)
        {
            bool softrender = (sender as CheckBox).Checked;

            op.SetString("Video", "Renderer", softrender ? "Software" : "Hardware");

            if (softrender)
                force32box.Checked = false;
        }

        private void fovSlider_Scroll(object sender, EventArgs e)
        {

        }

        private void fovSlider_ValueChanged(object sender, EventArgs e)
        {
            op.FovScale = fovSlider.Value / 100f;
            fovLabel.Text = op.FovScale.ToString("0.0##");
        }

        private void fogSlider_ValueChanged(object sender, EventArgs e)
        {
            op.fog = Helpers.MathClamp((int)(Math.Pow(fogSlider.Value, 2) / (float)fogSlider.Maximum + 10f), 10, 750);

            op.SetInt("Video", "FogScale", op.fog);

            fogLabel.Text = op.fog.ToString();
        }

        private void fogSlider_MouseUp(object sender, MouseEventArgs e)
        {
        }



        private void UpdateFOVbar()
        {
            fovSlider.Value = Helpers.MathClamp((int)(100 * op.FovScale), 30, 140);
            fovLabel.Text = op.FovScale.ToString("0.0##");
        }

        private void unlockFPSbox_CheckedChanged(object sender, EventArgs e)
        {
            op.SetBool("Video", "UnlockFPS", (sender as CheckBox).Checked);
        }

        private void force32box_CheckedChanged(object sender, EventArgs e)
        {
            bool force32bits = (sender as CheckBox).Checked;

            op.SetBool("Video", "Force32Bpp", force32bits);

            if (force32bits)
                rendererBox.Checked = false;
        }

        private void aspectRatioDrop_SelectedIndexChanged(object sender, EventArgs e)
        {
            op.applyResolutionListByAspectRatio(resBox, aspectRatioDrop.Text);
        }

        private void resBox_SelectedIndexChanged_1(object sender, EventArgs e)
        {
            var size = op.ParseResText(resBox.Text);

            if (size != null) op.SetResolution(size.Width, size.Height);
        }


        private void resBox_SelectionChangeCommitted(object sender, EventArgs e)
        {
            var size = op.ParseResText(resBox.Text);

            if (size != null) op.SetResolution(size.Width, size.Height);
        }

        #endregion

        #region [Music tab]
        private void randomBox_CheckedChanged(object sender, EventArgs e)
        {
            op.SetBool("Music", "Random", (sender as CheckBox).Checked);
        }

        private void titleBox_CheckedChanged(object sender, EventArgs e)
        {
            op.SetBool("Music", "ShowTitle", (sender as CheckBox).Checked);
        }

        private void fadeBox_CheckedChanged(object sender, EventArgs e)
        {
            op.SetBool("Music", "Fade", (sender as CheckBox).Checked);
        }

        private void ambienceBox_CheckedChanged(object sender, EventArgs e)
        {
            op.SetBool("Music", "PlayAmbience", (sender as CheckBox).Checked);
        }

        private void separateTracksBox_CheckedChanged(object sender, EventArgs e)
        {
            op.SetBool("Music", "SeparateTracks", (sender as CheckBox).Checked);
        }
        #endregion

        #region [Patches tab]
        private void skyBox_CheckedChanged(object sender, EventArgs e)
        {
            op.SetBool("Patch", "DisableSky", (sender as CheckBox).Checked);
        }

        private void vibrationBox_CheckedChanged(object sender, EventArgs e)
        {
            op.SetBool("Input", "Vibration", (sender as CheckBox).Checked);
        }

        private void bigDropBox_CheckedChanged(object sender, EventArgs e)
        {
            op.SetBool("Input", "BigDrop", (sender as CheckBox).Checked);
        }

        private void xinputBox_CheckedChanged(object sender, EventArgs e)
        {
            op.SetBool("Input", "XInput", (sender as CheckBox).Checked);
        }

        private void userPatchBox_CheckedChanged(object sender, EventArgs e)
        {
            op.SetBool("Patch", "UserPatch", (sender as CheckBox).Checked);
        }

        private void manualsBox_CheckedChanged(object sender, EventArgs e)
        {
            op.SetBool("Input", "Manuals", (sender as CheckBox).Checked);
        }

        private void railBarBox_CheckedChanged(object sender, EventArgs e)
        {
            op.SetBool("Patch", "RailBalanceBar", (sender as CheckBox).Checked);
        }

        private void drawshadowBox_CheckedChanged(object sender, EventArgs e)
        {
            op.SetBool("Video", "DrawShadow", (sender as CheckBox).Checked);
        }

        private void drawhudBox_CheckedChanged(object sender, EventArgs e)
        {
            op.SetBool("Video", "ShowHUD", (sender as CheckBox).Checked);
        }

        private void psxtexBox_CheckedChanged(object sender, EventArgs e)
        {
            op.SetBool("Video", "DisableNewTex", (sender as CheckBox).Checked);
        }

        private void autokickBox_CheckedChanged(object sender, EventArgs e)
        {
            op.SetBool("Input", "AutoKick", (sender as CheckBox).Checked);
        }
        #endregion

        #region [About tab]
        private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            Process.Start((sender as LinkLabel).Text);
        }

        private void linkLabel2_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            Process.Start((sender as LinkLabel).Text);
        }

        private void linkLabel3_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            Process.Start((sender as LinkLabel).Text);
        }
        #endregion

        private void overrideFOVbox_CheckStateChanged(object sender, EventArgs e)
        {
        }

        private void overrideFOVbox_CheckedChanged(object sender, EventArgs e)
        {
            fovSlider.Enabled = overrideFOVbox.Checked;
            op.SetBool("Video", "OverrideFov", overrideFOVbox.Checked);

            op.FovScale = op.FovScale; //lol
        }

        private void filterBox_CheckedChanged(object sender, EventArgs e)
        {
            op.SetBool("Video", "TextureFiltering", (sender as CheckBox).Checked);
        }
    }
}