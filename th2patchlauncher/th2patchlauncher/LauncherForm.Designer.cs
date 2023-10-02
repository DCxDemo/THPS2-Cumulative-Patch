using System.Windows.Forms;

namespace th2patchlauncher
{
    partial class LauncherForm
    {
        /// <summary>
        /// Требуется переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Обязательный метод для поддержки конструктора - не изменяйте
        /// содержимое данного метода при помощи редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(LauncherForm));
            this.aboutTab = new System.Windows.Forms.TabPage();
            this.patchTab = new System.Windows.Forms.TabPage();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.musicTab = new System.Windows.Forms.TabPage();
            this.xinputBox = new System.Windows.Forms.CheckBox();
            this.label5 = new System.Windows.Forms.Label();
            this.quitButton = new System.Windows.Forms.Button();
            this.launchButton = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.gameBox = new System.Windows.Forms.ComboBox();
            this.userPatchBox = new System.Windows.Forms.CheckBox();
            this.altSkinsBox = new System.Windows.Forms.CheckBox();
            this.skipIntroBox = new System.Windows.Forms.CheckBox();
            this.separateSaveBox = new System.Windows.Forms.CheckBox();
            this.swapBox = new System.Windows.Forms.ComboBox();
            this.generalTab = new System.Windows.Forms.TabPage();
            this.linkLabel1 = new System.Windows.Forms.LinkLabel();
            this.drawhudBox = new System.Windows.Forms.CheckBox();
            this.psxtexBox = new System.Windows.Forms.CheckBox();
            this.drawshadowBox = new System.Windows.Forms.CheckBox();
            this.manualsBox = new System.Windows.Forms.CheckBox();
            this.skyBox = new System.Windows.Forms.CheckBox();
            this.linkLabel2 = new System.Windows.Forms.LinkLabel();
            this.bigDropBox = new System.Windows.Forms.CheckBox();
            this.linkLabel3 = new System.Windows.Forms.LinkLabel();
            this.vibrationBox = new System.Windows.Forms.CheckBox();
            this.railBarBox = new System.Windows.Forms.CheckBox();
            this.label1 = new System.Windows.Forms.Label();
            this.ResXbox = new System.Windows.Forms.TextBox();
            this.ResYbox = new System.Windows.Forms.TextBox();
            this.detectButton = new System.Windows.Forms.Button();
            this.unlockFPSbox = new System.Windows.Forms.CheckBox();
            this.force32box = new System.Windows.Forms.CheckBox();
            this.overrideFOVbox = new System.Windows.Forms.CheckBox();
            this.fovSlider = new System.Windows.Forms.TrackBar();
            this.label4 = new System.Windows.Forms.Label();
            this.resBox = new System.Windows.Forms.ComboBox();
            this.fogSlider = new System.Windows.Forms.TrackBar();
            this.label2 = new System.Windows.Forms.Label();
            this.rendererBox = new System.Windows.Forms.CheckBox();
            this.videoTab = new System.Windows.Forms.TabPage();
            this.randomBox = new System.Windows.Forms.CheckBox();
            this.titleBox = new System.Windows.Forms.CheckBox();
            this.fadeBox = new System.Windows.Forms.CheckBox();
            this.ambienceBox = new System.Windows.Forms.CheckBox();
            this.separateTracksBox = new System.Windows.Forms.CheckBox();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.aboutTab.SuspendLayout();
            this.patchTab.SuspendLayout();
            this.tabControl1.SuspendLayout();
            this.musicTab.SuspendLayout();
            this.generalTab.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.fovSlider)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.fogSlider)).BeginInit();
            this.videoTab.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // aboutTab
            // 
            this.aboutTab.Controls.Add(this.label5);
            this.aboutTab.Controls.Add(this.linkLabel3);
            this.aboutTab.Controls.Add(this.linkLabel2);
            this.aboutTab.Controls.Add(this.linkLabel1);
            resources.ApplyResources(this.aboutTab, "aboutTab");
            this.aboutTab.Name = "aboutTab";
            this.aboutTab.UseVisualStyleBackColor = true;
            // 
            // patchTab
            // 
            this.patchTab.Controls.Add(this.railBarBox);
            this.patchTab.Controls.Add(this.skyBox);
            this.patchTab.Controls.Add(this.manualsBox);
            this.patchTab.Controls.Add(this.drawshadowBox);
            this.patchTab.Controls.Add(this.psxtexBox);
            this.patchTab.Controls.Add(this.drawhudBox);
            this.patchTab.Controls.Add(this.xinputBox);
            this.patchTab.Controls.Add(this.bigDropBox);
            this.patchTab.Controls.Add(this.vibrationBox);
            resources.ApplyResources(this.patchTab, "patchTab");
            this.patchTab.Name = "patchTab";
            this.patchTab.UseVisualStyleBackColor = true;
            // 
            // tabControl1
            // 
            resources.ApplyResources(this.tabControl1, "tabControl1");
            this.tabControl1.Controls.Add(this.generalTab);
            this.tabControl1.Controls.Add(this.videoTab);
            this.tabControl1.Controls.Add(this.musicTab);
            this.tabControl1.Controls.Add(this.patchTab);
            this.tabControl1.Controls.Add(this.aboutTab);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            // 
            // musicTab
            // 
            this.musicTab.Controls.Add(this.separateTracksBox);
            this.musicTab.Controls.Add(this.ambienceBox);
            this.musicTab.Controls.Add(this.fadeBox);
            this.musicTab.Controls.Add(this.titleBox);
            this.musicTab.Controls.Add(this.randomBox);
            resources.ApplyResources(this.musicTab, "musicTab");
            this.musicTab.Name = "musicTab";
            this.musicTab.UseVisualStyleBackColor = true;
            // 
            // xinputBox
            // 
            resources.ApplyResources(this.xinputBox, "xinputBox");
            this.xinputBox.Name = "xinputBox";
            this.xinputBox.UseVisualStyleBackColor = true;
            this.xinputBox.CheckedChanged += new System.EventHandler(this.xinputBox_CheckedChanged);
            // 
            // label5
            // 
            resources.ApplyResources(this.label5, "label5");
            this.label5.Name = "label5";
            // 
            // quitButton
            // 
            resources.ApplyResources(this.quitButton, "quitButton");
            this.quitButton.Name = "quitButton";
            this.quitButton.UseVisualStyleBackColor = true;
            this.quitButton.Click += new System.EventHandler(this.quitButtonClick);
            // 
            // launchButton
            // 
            resources.ApplyResources(this.launchButton, "launchButton");
            this.launchButton.Name = "launchButton";
            this.launchButton.UseVisualStyleBackColor = true;
            this.launchButton.Click += new System.EventHandler(this.launchButtonClick);
            // 
            // label3
            // 
            resources.ApplyResources(this.label3, "label3");
            this.label3.Name = "label3";
            // 
            // gameBox
            // 
            this.gameBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.gameBox.FormattingEnabled = true;
            this.gameBox.Items.AddRange(new object[] {
            resources.GetString("gameBox.Items"),
            resources.GetString("gameBox.Items1"),
            resources.GetString("gameBox.Items2"),
            resources.GetString("gameBox.Items3"),
            resources.GetString("gameBox.Items4")});
            resources.ApplyResources(this.gameBox, "gameBox");
            this.gameBox.Name = "gameBox";
            this.gameBox.SelectedIndexChanged += new System.EventHandler(this.gameBox_SelectedIndexChanged);
            // 
            // userPatchBox
            // 
            resources.ApplyResources(this.userPatchBox, "userPatchBox");
            this.userPatchBox.Name = "userPatchBox";
            this.userPatchBox.UseVisualStyleBackColor = true;
            this.userPatchBox.CheckStateChanged += new System.EventHandler(this.userPatchBox_CheckedChanged);
            // 
            // altSkinsBox
            // 
            resources.ApplyResources(this.altSkinsBox, "altSkinsBox");
            this.altSkinsBox.Name = "altSkinsBox";
            this.altSkinsBox.UseVisualStyleBackColor = true;
            this.altSkinsBox.CheckStateChanged += new System.EventHandler(this.altSkinsBox_CheckedChanged);
            // 
            // skipIntroBox
            // 
            resources.ApplyResources(this.skipIntroBox, "skipIntroBox");
            this.skipIntroBox.Name = "skipIntroBox";
            this.skipIntroBox.UseVisualStyleBackColor = true;
            this.skipIntroBox.CheckStateChanged += new System.EventHandler(this.skipIntroBox_CheckedChanged);
            // 
            // separateSaveBox
            // 
            resources.ApplyResources(this.separateSaveBox, "separateSaveBox");
            this.separateSaveBox.Name = "separateSaveBox";
            this.separateSaveBox.UseVisualStyleBackColor = true;
            this.separateSaveBox.CheckStateChanged += new System.EventHandler(this.separateSaveBox_CheckedChanged);
            // 
            // swapBox
            // 
            this.swapBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.swapBox.FormattingEnabled = true;
            this.swapBox.Items.AddRange(new object[] {
            resources.GetString("swapBox.Items"),
            resources.GetString("swapBox.Items1"),
            resources.GetString("swapBox.Items2"),
            resources.GetString("swapBox.Items3"),
            resources.GetString("swapBox.Items4"),
            resources.GetString("swapBox.Items5"),
            resources.GetString("swapBox.Items6")});
            resources.ApplyResources(this.swapBox, "swapBox");
            this.swapBox.Name = "swapBox";
            this.swapBox.SelectedIndexChanged += new System.EventHandler(this.swapBox_SelectedIndexChanged);
            // 
            // generalTab
            // 
            this.generalTab.Controls.Add(this.swapBox);
            this.generalTab.Controls.Add(this.separateSaveBox);
            this.generalTab.Controls.Add(this.skipIntroBox);
            this.generalTab.Controls.Add(this.altSkinsBox);
            this.generalTab.Controls.Add(this.userPatchBox);
            this.generalTab.Controls.Add(this.gameBox);
            this.generalTab.Controls.Add(this.label3);
            resources.ApplyResources(this.generalTab, "generalTab");
            this.generalTab.Name = "generalTab";
            this.generalTab.UseVisualStyleBackColor = true;
            // 
            // linkLabel1
            // 
            resources.ApplyResources(this.linkLabel1, "linkLabel1");
            this.linkLabel1.Name = "linkLabel1";
            this.linkLabel1.TabStop = true;
            this.linkLabel1.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.linkLabel1_LinkClicked);
            // 
            // drawhudBox
            // 
            resources.ApplyResources(this.drawhudBox, "drawhudBox");
            this.drawhudBox.Name = "drawhudBox";
            this.drawhudBox.UseVisualStyleBackColor = true;
            this.drawhudBox.CheckedChanged += new System.EventHandler(this.drawhudBox_CheckedChanged);
            // 
            // psxtexBox
            // 
            resources.ApplyResources(this.psxtexBox, "psxtexBox");
            this.psxtexBox.Name = "psxtexBox";
            this.psxtexBox.UseVisualStyleBackColor = true;
            this.psxtexBox.CheckedChanged += new System.EventHandler(this.psxtexBox_CheckedChanged);
            // 
            // drawshadowBox
            // 
            resources.ApplyResources(this.drawshadowBox, "drawshadowBox");
            this.drawshadowBox.Name = "drawshadowBox";
            this.drawshadowBox.UseVisualStyleBackColor = true;
            this.drawshadowBox.CheckedChanged += new System.EventHandler(this.drawshadowBox_CheckedChanged);
            // 
            // manualsBox
            // 
            resources.ApplyResources(this.manualsBox, "manualsBox");
            this.manualsBox.Name = "manualsBox";
            this.manualsBox.UseVisualStyleBackColor = true;
            this.manualsBox.CheckedChanged += new System.EventHandler(this.manualsBox_CheckedChanged);
            // 
            // skyBox
            // 
            resources.ApplyResources(this.skyBox, "skyBox");
            this.skyBox.Name = "skyBox";
            this.skyBox.UseVisualStyleBackColor = true;
            this.skyBox.CheckedChanged += new System.EventHandler(this.skyBox_CheckedChanged);
            // 
            // linkLabel2
            // 
            resources.ApplyResources(this.linkLabel2, "linkLabel2");
            this.linkLabel2.Name = "linkLabel2";
            this.linkLabel2.TabStop = true;
            this.linkLabel2.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.linkLabel2_LinkClicked);
            // 
            // bigDropBox
            // 
            resources.ApplyResources(this.bigDropBox, "bigDropBox");
            this.bigDropBox.Name = "bigDropBox";
            this.bigDropBox.UseVisualStyleBackColor = true;
            this.bigDropBox.CheckedChanged += new System.EventHandler(this.bigDropBox_CheckedChanged);
            // 
            // linkLabel3
            // 
            resources.ApplyResources(this.linkLabel3, "linkLabel3");
            this.linkLabel3.Name = "linkLabel3";
            this.linkLabel3.TabStop = true;
            this.linkLabel3.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.linkLabel3_LinkClicked);
            // 
            // vibrationBox
            // 
            resources.ApplyResources(this.vibrationBox, "vibrationBox");
            this.vibrationBox.Name = "vibrationBox";
            this.vibrationBox.UseVisualStyleBackColor = true;
            this.vibrationBox.CheckedChanged += new System.EventHandler(this.vibrationBox_CheckedChanged);
            // 
            // railBarBox
            // 
            resources.ApplyResources(this.railBarBox, "railBarBox");
            this.railBarBox.Name = "railBarBox";
            this.railBarBox.UseVisualStyleBackColor = true;
            this.railBarBox.CheckedChanged += new System.EventHandler(this.railBarBox_CheckedChanged);
            // 
            // label1
            // 
            resources.ApplyResources(this.label1, "label1");
            this.label1.Name = "label1";
            // 
            // ResXbox
            // 
            resources.ApplyResources(this.ResXbox, "ResXbox");
            this.ResXbox.Name = "ResXbox";
            // 
            // ResYbox
            // 
            resources.ApplyResources(this.ResYbox, "ResYbox");
            this.ResYbox.Name = "ResYbox";
            // 
            // detectButton
            // 
            resources.ApplyResources(this.detectButton, "detectButton");
            this.detectButton.Name = "detectButton";
            this.detectButton.UseVisualStyleBackColor = true;
            this.detectButton.Click += new System.EventHandler(this.detectButtonClick);
            // 
            // unlockFPSbox
            // 
            resources.ApplyResources(this.unlockFPSbox, "unlockFPSbox");
            this.unlockFPSbox.Name = "unlockFPSbox";
            this.unlockFPSbox.UseVisualStyleBackColor = true;
            this.unlockFPSbox.CheckedChanged += new System.EventHandler(this.unlockFPSbox_CheckedChanged);
            // 
            // force32box
            // 
            resources.ApplyResources(this.force32box, "force32box");
            this.force32box.Name = "force32box";
            this.force32box.UseVisualStyleBackColor = true;
            this.force32box.CheckedChanged += new System.EventHandler(this.force32box_CheckedChanged);
            // 
            // overrideFOVbox
            // 
            resources.ApplyResources(this.overrideFOVbox, "overrideFOVbox");
            this.overrideFOVbox.Name = "overrideFOVbox";
            this.overrideFOVbox.UseVisualStyleBackColor = true;
            this.overrideFOVbox.CheckedChanged += new System.EventHandler(this.overrideFOVbox_CheckedChanged);
            // 
            // fovSlider
            // 
            this.fovSlider.BackColor = System.Drawing.SystemColors.Window;
            resources.ApplyResources(this.fovSlider, "fovSlider");
            this.fovSlider.Maximum = 140;
            this.fovSlider.Minimum = 30;
            this.fovSlider.Name = "fovSlider";
            this.fovSlider.TickFrequency = 10;
            this.fovSlider.Value = 100;
            this.fovSlider.Scroll += new System.EventHandler(this.fovSlider_Scroll);
            this.fovSlider.ValueChanged += new System.EventHandler(this.trackBar1_ValueChanged);
            // 
            // label4
            // 
            resources.ApplyResources(this.label4, "label4");
            this.label4.Name = "label4";
            // 
            // resBox
            // 
            this.resBox.FormattingEnabled = true;
            this.resBox.Items.AddRange(new object[] {
            resources.GetString("resBox.Items"),
            resources.GetString("resBox.Items1"),
            resources.GetString("resBox.Items2"),
            resources.GetString("resBox.Items3"),
            resources.GetString("resBox.Items4"),
            resources.GetString("resBox.Items5"),
            resources.GetString("resBox.Items6"),
            resources.GetString("resBox.Items7"),
            resources.GetString("resBox.Items8"),
            resources.GetString("resBox.Items9"),
            resources.GetString("resBox.Items10"),
            resources.GetString("resBox.Items11"),
            resources.GetString("resBox.Items12"),
            resources.GetString("resBox.Items13"),
            resources.GetString("resBox.Items14")});
            resources.ApplyResources(this.resBox, "resBox");
            this.resBox.Name = "resBox";
            this.resBox.SelectedIndexChanged += new System.EventHandler(this.resBox_SelectedIndexChanged_1);
            this.resBox.SelectionChangeCommitted += new System.EventHandler(this.resBox_SelectionChangeCommitted);
            // 
            // fogSlider
            // 
            this.fogSlider.BackColor = System.Drawing.SystemColors.Window;
            resources.ApplyResources(this.fogSlider, "fogSlider");
            this.fogSlider.Maximum = 740;
            this.fogSlider.Name = "fogSlider";
            this.fogSlider.SmallChange = 10;
            this.fogSlider.TickFrequency = 75;
            this.fogSlider.Value = 740;
            this.fogSlider.Scroll += new System.EventHandler(this.trackBar2_Scroll);
            this.fogSlider.MouseUp += new System.Windows.Forms.MouseEventHandler(this.trackBar2_MouseUp);
            // 
            // label2
            // 
            resources.ApplyResources(this.label2, "label2");
            this.label2.Name = "label2";
            // 
            // rendererBox
            // 
            resources.ApplyResources(this.rendererBox, "rendererBox");
            this.rendererBox.Name = "rendererBox";
            this.rendererBox.UseVisualStyleBackColor = true;
            this.rendererBox.CheckedChanged += new System.EventHandler(this.rendererBox_CheckedChanged);
            // 
            // videoTab
            // 
            this.videoTab.Controls.Add(this.rendererBox);
            this.videoTab.Controls.Add(this.label2);
            this.videoTab.Controls.Add(this.fogSlider);
            this.videoTab.Controls.Add(this.resBox);
            this.videoTab.Controls.Add(this.label4);
            this.videoTab.Controls.Add(this.fovSlider);
            this.videoTab.Controls.Add(this.overrideFOVbox);
            this.videoTab.Controls.Add(this.force32box);
            this.videoTab.Controls.Add(this.unlockFPSbox);
            this.videoTab.Controls.Add(this.detectButton);
            this.videoTab.Controls.Add(this.ResYbox);
            this.videoTab.Controls.Add(this.ResXbox);
            this.videoTab.Controls.Add(this.label1);
            resources.ApplyResources(this.videoTab, "videoTab");
            this.videoTab.Name = "videoTab";
            this.videoTab.UseVisualStyleBackColor = true;
            // 
            // randomBox
            // 
            resources.ApplyResources(this.randomBox, "randomBox");
            this.randomBox.Name = "randomBox";
            this.randomBox.UseVisualStyleBackColor = true;
            this.randomBox.CheckedChanged += new System.EventHandler(this.randomBox_CheckedChanged);
            // 
            // titleBox
            // 
            resources.ApplyResources(this.titleBox, "titleBox");
            this.titleBox.Name = "titleBox";
            this.titleBox.UseVisualStyleBackColor = true;
            this.titleBox.CheckedChanged += new System.EventHandler(this.titleBox_CheckedChanged);
            // 
            // fadeBox
            // 
            resources.ApplyResources(this.fadeBox, "fadeBox");
            this.fadeBox.Name = "fadeBox";
            this.fadeBox.UseVisualStyleBackColor = true;
            this.fadeBox.CheckedChanged += new System.EventHandler(this.fadeBox_CheckedChanged);
            // 
            // ambienceBox
            // 
            resources.ApplyResources(this.ambienceBox, "ambienceBox");
            this.ambienceBox.Name = "ambienceBox";
            this.ambienceBox.UseVisualStyleBackColor = true;
            this.ambienceBox.CheckedChanged += new System.EventHandler(this.ambienceBox_CheckedChanged);
            // 
            // separateTracksBox
            // 
            resources.ApplyResources(this.separateTracksBox, "separateTracksBox");
            this.separateTracksBox.Name = "separateTracksBox";
            this.separateTracksBox.UseVisualStyleBackColor = true;
            this.separateTracksBox.CheckedChanged += new System.EventHandler(this.separateTracksBox_CheckedChanged);
            // 
            // pictureBox1
            // 
            this.pictureBox1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.pictureBox1.Image = global::th2patchlauncher.Properties.Resources.th22logo;
            resources.ApplyResources(this.pictureBox1, "pictureBox1");
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.TabStop = false;
            // 
            // LauncherForm
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.tabControl1);
            this.Controls.Add(this.launchButton);
            this.Controls.Add(this.quitButton);
            this.Controls.Add(this.pictureBox1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.Name = "LauncherForm";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.aboutTab.ResumeLayout(false);
            this.aboutTab.PerformLayout();
            this.patchTab.ResumeLayout(false);
            this.patchTab.PerformLayout();
            this.tabControl1.ResumeLayout(false);
            this.musicTab.ResumeLayout(false);
            this.musicTab.PerformLayout();
            this.generalTab.ResumeLayout(false);
            this.generalTab.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.fovSlider)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.fogSlider)).EndInit();
            this.videoTab.ResumeLayout(false);
            this.videoTab.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private TabPage aboutTab;
        private Label label5;
        private LinkLabel linkLabel3;
        private LinkLabel linkLabel2;
        private LinkLabel linkLabel1;
        private TabPage patchTab;
        private CheckBox railBarBox;
        private CheckBox skyBox;
        private CheckBox manualsBox;
        private CheckBox drawshadowBox;
        private CheckBox psxtexBox;
        private CheckBox drawhudBox;
        private CheckBox xinputBox;
        private CheckBox bigDropBox;
        private CheckBox vibrationBox;
        private TabControl tabControl1;
        private TabPage generalTab;
        private ComboBox swapBox;
        private CheckBox separateSaveBox;
        private CheckBox skipIntroBox;
        private CheckBox altSkinsBox;
        private CheckBox userPatchBox;
        private ComboBox gameBox;
        private Label label3;
        private TabPage videoTab;
        private CheckBox rendererBox;
        private Label label2;
        private TrackBar fogSlider;
        private ComboBox resBox;
        private Label label4;
        private TrackBar fovSlider;
        private CheckBox overrideFOVbox;
        private CheckBox force32box;
        private CheckBox unlockFPSbox;
        private Button detectButton;
        private TextBox ResYbox;
        private TextBox ResXbox;
        private Label label1;
        private TabPage musicTab;
        private CheckBox separateTracksBox;
        private CheckBox ambienceBox;
        private CheckBox fadeBox;
        private CheckBox titleBox;
        private CheckBox randomBox;
        private Button quitButton;
        private Button launchButton;
        private PictureBox pictureBox1;
    }
}

