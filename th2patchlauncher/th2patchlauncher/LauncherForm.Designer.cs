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
            this.skipIntroBox = new System.Windows.Forms.CheckBox();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.patchTab = new System.Windows.Forms.TabPage();
            this.swapBox = new System.Windows.Forms.ComboBox();
            this.separateSaveBox = new System.Windows.Forms.CheckBox();
            this.altSkinsBox = new System.Windows.Forms.CheckBox();
            this.userPatchBox = new System.Windows.Forms.CheckBox();
            this.gameBox = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.videoTab = new System.Windows.Forms.TabPage();
            this.label2 = new System.Windows.Forms.Label();
            this.fogSlider = new System.Windows.Forms.TrackBar();
            this.resBox = new System.Windows.Forms.ComboBox();
            this.label4 = new System.Windows.Forms.Label();
            this.fovSlider = new System.Windows.Forms.TrackBar();
            this.overrideFOVbox = new System.Windows.Forms.CheckBox();
            this.force32box = new System.Windows.Forms.CheckBox();
            this.unlockFPSbox = new System.Windows.Forms.CheckBox();
            this.detectButton = new System.Windows.Forms.Button();
            this.ResYbox = new System.Windows.Forms.TextBox();
            this.ResXbox = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.musicTab = new System.Windows.Forms.TabPage();
            this.separateTracksBox = new System.Windows.Forms.CheckBox();
            this.ambienceBox = new System.Windows.Forms.CheckBox();
            this.fadeBox = new System.Windows.Forms.CheckBox();
            this.titleBox = new System.Windows.Forms.CheckBox();
            this.randomBox = new System.Windows.Forms.CheckBox();
            this.inputTab = new System.Windows.Forms.TabPage();
            this.drawshadowBox = new System.Windows.Forms.CheckBox();
            this.psxtexBox = new System.Windows.Forms.CheckBox();
            this.drawhudBox = new System.Windows.Forms.CheckBox();
            this.xinputBox = new System.Windows.Forms.CheckBox();
            this.bigDropBox = new System.Windows.Forms.CheckBox();
            this.vibrationBox = new System.Windows.Forms.CheckBox();
            this.aboutTab = new System.Windows.Forms.TabPage();
            this.label5 = new System.Windows.Forms.Label();
            this.linkLabel3 = new System.Windows.Forms.LinkLabel();
            this.linkLabel2 = new System.Windows.Forms.LinkLabel();
            this.linkLabel1 = new System.Windows.Forms.LinkLabel();
            this.quitButton = new System.Windows.Forms.Button();
            this.launchButton = new System.Windows.Forms.Button();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.rendererBox = new System.Windows.Forms.CheckBox();
            this.tabControl1.SuspendLayout();
            this.patchTab.SuspendLayout();
            this.videoTab.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.fogSlider)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.fovSlider)).BeginInit();
            this.musicTab.SuspendLayout();
            this.inputTab.SuspendLayout();
            this.aboutTab.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // skipIntroBox
            // 
            resources.ApplyResources(this.skipIntroBox, "skipIntroBox");
            this.skipIntroBox.Name = "skipIntroBox";
            this.skipIntroBox.UseVisualStyleBackColor = true;
            this.skipIntroBox.CheckedChanged += new System.EventHandler(this.skipIntroBox_CheckedChanged);
            // 
            // tabControl1
            // 
            resources.ApplyResources(this.tabControl1, "tabControl1");
            this.tabControl1.Controls.Add(this.patchTab);
            this.tabControl1.Controls.Add(this.videoTab);
            this.tabControl1.Controls.Add(this.musicTab);
            this.tabControl1.Controls.Add(this.inputTab);
            this.tabControl1.Controls.Add(this.aboutTab);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            // 
            // patchTab
            // 
            this.patchTab.Controls.Add(this.swapBox);
            this.patchTab.Controls.Add(this.separateSaveBox);
            this.patchTab.Controls.Add(this.skipIntroBox);
            this.patchTab.Controls.Add(this.altSkinsBox);
            this.patchTab.Controls.Add(this.userPatchBox);
            this.patchTab.Controls.Add(this.gameBox);
            this.patchTab.Controls.Add(this.label3);
            resources.ApplyResources(this.patchTab, "patchTab");
            this.patchTab.Name = "patchTab";
            this.patchTab.UseVisualStyleBackColor = true;
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
            // separateSaveBox
            // 
            resources.ApplyResources(this.separateSaveBox, "separateSaveBox");
            this.separateSaveBox.Name = "separateSaveBox";
            this.separateSaveBox.UseVisualStyleBackColor = true;
            this.separateSaveBox.CheckedChanged += new System.EventHandler(this.separateSaveBox_CheckedChanged);
            // 
            // altSkinsBox
            // 
            resources.ApplyResources(this.altSkinsBox, "altSkinsBox");
            this.altSkinsBox.Name = "altSkinsBox";
            this.altSkinsBox.UseVisualStyleBackColor = true;
            this.altSkinsBox.CheckedChanged += new System.EventHandler(this.altSkinsBox_CheckedChanged);
            // 
            // userPatchBox
            // 
            resources.ApplyResources(this.userPatchBox, "userPatchBox");
            this.userPatchBox.Name = "userPatchBox";
            this.userPatchBox.UseVisualStyleBackColor = true;
            this.userPatchBox.CheckedChanged += new System.EventHandler(this.userPatchBox_CheckedChanged);
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
            // label3
            // 
            resources.ApplyResources(this.label3, "label3");
            this.label3.Name = "label3";
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
            // label2
            // 
            resources.ApplyResources(this.label2, "label2");
            this.label2.Name = "label2";
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
            this.resBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.resBox_KeyPress);
            // 
            // label4
            // 
            resources.ApplyResources(this.label4, "label4");
            this.label4.Name = "label4";
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
            this.fovSlider.ValueChanged += new System.EventHandler(this.trackBar1_ValueChanged);
            // 
            // overrideFOVbox
            // 
            resources.ApplyResources(this.overrideFOVbox, "overrideFOVbox");
            this.overrideFOVbox.Name = "overrideFOVbox";
            this.overrideFOVbox.UseVisualStyleBackColor = true;
            this.overrideFOVbox.CheckedChanged += new System.EventHandler(this.overrideFOVbox_CheckedChanged);
            // 
            // force32box
            // 
            resources.ApplyResources(this.force32box, "force32box");
            this.force32box.Name = "force32box";
            this.force32box.UseVisualStyleBackColor = true;
            this.force32box.CheckedChanged += new System.EventHandler(this.force32box_CheckedChanged);
            // 
            // unlockFPSbox
            // 
            resources.ApplyResources(this.unlockFPSbox, "unlockFPSbox");
            this.unlockFPSbox.Name = "unlockFPSbox";
            this.unlockFPSbox.UseVisualStyleBackColor = true;
            this.unlockFPSbox.CheckedChanged += new System.EventHandler(this.unlockFPSbox_CheckedChanged);
            // 
            // detectButton
            // 
            resources.ApplyResources(this.detectButton, "detectButton");
            this.detectButton.Name = "detectButton";
            this.detectButton.UseVisualStyleBackColor = true;
            this.detectButton.Click += new System.EventHandler(this.detectButtonClick);
            // 
            // ResYbox
            // 
            resources.ApplyResources(this.ResYbox, "ResYbox");
            this.ResYbox.Name = "ResYbox";
            // 
            // ResXbox
            // 
            resources.ApplyResources(this.ResXbox, "ResXbox");
            this.ResXbox.Name = "ResXbox";
            // 
            // label1
            // 
            resources.ApplyResources(this.label1, "label1");
            this.label1.Name = "label1";
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
            // separateTracksBox
            // 
            resources.ApplyResources(this.separateTracksBox, "separateTracksBox");
            this.separateTracksBox.Name = "separateTracksBox";
            this.separateTracksBox.UseVisualStyleBackColor = true;
            this.separateTracksBox.CheckedChanged += new System.EventHandler(this.separateTracksBox_CheckedChanged);
            // 
            // ambienceBox
            // 
            resources.ApplyResources(this.ambienceBox, "ambienceBox");
            this.ambienceBox.Name = "ambienceBox";
            this.ambienceBox.UseVisualStyleBackColor = true;
            this.ambienceBox.CheckedChanged += new System.EventHandler(this.ambienceBox_CheckedChanged);
            // 
            // fadeBox
            // 
            resources.ApplyResources(this.fadeBox, "fadeBox");
            this.fadeBox.Name = "fadeBox";
            this.fadeBox.UseVisualStyleBackColor = true;
            this.fadeBox.CheckedChanged += new System.EventHandler(this.fadeBox_CheckedChanged);
            // 
            // titleBox
            // 
            resources.ApplyResources(this.titleBox, "titleBox");
            this.titleBox.Name = "titleBox";
            this.titleBox.UseVisualStyleBackColor = true;
            this.titleBox.CheckedChanged += new System.EventHandler(this.titleBox_CheckedChanged);
            // 
            // randomBox
            // 
            resources.ApplyResources(this.randomBox, "randomBox");
            this.randomBox.Name = "randomBox";
            this.randomBox.UseVisualStyleBackColor = true;
            this.randomBox.CheckedChanged += new System.EventHandler(this.randomBox_CheckedChanged);
            // 
            // inputTab
            // 
            this.inputTab.Controls.Add(this.drawshadowBox);
            this.inputTab.Controls.Add(this.psxtexBox);
            this.inputTab.Controls.Add(this.drawhudBox);
            this.inputTab.Controls.Add(this.xinputBox);
            this.inputTab.Controls.Add(this.bigDropBox);
            this.inputTab.Controls.Add(this.vibrationBox);
            resources.ApplyResources(this.inputTab, "inputTab");
            this.inputTab.Name = "inputTab";
            this.inputTab.UseVisualStyleBackColor = true;
            // 
            // drawshadowBox
            // 
            resources.ApplyResources(this.drawshadowBox, "drawshadowBox");
            this.drawshadowBox.Name = "drawshadowBox";
            this.drawshadowBox.UseVisualStyleBackColor = true;
            this.drawshadowBox.CheckedChanged += new System.EventHandler(this.drawshadowBox_CheckedChanged);
            // 
            // psxtexBox
            // 
            resources.ApplyResources(this.psxtexBox, "psxtexBox");
            this.psxtexBox.Name = "psxtexBox";
            this.psxtexBox.UseVisualStyleBackColor = true;
            this.psxtexBox.CheckedChanged += new System.EventHandler(this.psxtexBox_CheckedChanged);
            // 
            // drawhudBox
            // 
            resources.ApplyResources(this.drawhudBox, "drawhudBox");
            this.drawhudBox.Name = "drawhudBox";
            this.drawhudBox.UseVisualStyleBackColor = true;
            this.drawhudBox.CheckedChanged += new System.EventHandler(this.drawhudBox_CheckedChanged);
            // 
            // xinputBox
            // 
            resources.ApplyResources(this.xinputBox, "xinputBox");
            this.xinputBox.Name = "xinputBox";
            this.xinputBox.UseVisualStyleBackColor = true;
            this.xinputBox.CheckedChanged += new System.EventHandler(this.xinputBox_CheckedChanged);
            // 
            // bigDropBox
            // 
            resources.ApplyResources(this.bigDropBox, "bigDropBox");
            this.bigDropBox.Name = "bigDropBox";
            this.bigDropBox.UseVisualStyleBackColor = true;
            this.bigDropBox.CheckedChanged += new System.EventHandler(this.bigDropBox_CheckedChanged);
            // 
            // vibrationBox
            // 
            resources.ApplyResources(this.vibrationBox, "vibrationBox");
            this.vibrationBox.Name = "vibrationBox";
            this.vibrationBox.UseVisualStyleBackColor = true;
            this.vibrationBox.CheckedChanged += new System.EventHandler(this.vibrationBox_CheckedChanged);
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
            // label5
            // 
            resources.ApplyResources(this.label5, "label5");
            this.label5.Name = "label5";
            // 
            // linkLabel3
            // 
            resources.ApplyResources(this.linkLabel3, "linkLabel3");
            this.linkLabel3.Name = "linkLabel3";
            this.linkLabel3.TabStop = true;
            this.linkLabel3.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.linkLabel3_LinkClicked);
            // 
            // linkLabel2
            // 
            resources.ApplyResources(this.linkLabel2, "linkLabel2");
            this.linkLabel2.Name = "linkLabel2";
            this.linkLabel2.TabStop = true;
            this.linkLabel2.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.linkLabel2_LinkClicked);
            // 
            // linkLabel1
            // 
            resources.ApplyResources(this.linkLabel1, "linkLabel1");
            this.linkLabel1.Name = "linkLabel1";
            this.linkLabel1.TabStop = true;
            this.linkLabel1.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.linkLabel1_LinkClicked);
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
            // pictureBox1
            // 
            this.pictureBox1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.pictureBox1.Image = global::th2patchlauncher.Properties.Resources.th22logo;
            resources.ApplyResources(this.pictureBox1, "pictureBox1");
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.TabStop = false;
            // 
            // rendererBox
            // 
            resources.ApplyResources(this.rendererBox, "rendererBox");
            this.rendererBox.Name = "rendererBox";
            this.rendererBox.UseVisualStyleBackColor = true;
            this.rendererBox.CheckedChanged += new System.EventHandler(this.rendererBox_CheckedChanged);
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
            this.tabControl1.ResumeLayout(false);
            this.patchTab.ResumeLayout(false);
            this.patchTab.PerformLayout();
            this.videoTab.ResumeLayout(false);
            this.videoTab.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.fogSlider)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.fovSlider)).EndInit();
            this.musicTab.ResumeLayout(false);
            this.musicTab.PerformLayout();
            this.inputTab.ResumeLayout(false);
            this.inputTab.PerformLayout();
            this.aboutTab.ResumeLayout(false);
            this.aboutTab.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private PictureBox pictureBox1;
        private Button quitButton;
        private Button launchButton;
        private CheckBox skipIntroBox;
        private TabControl tabControl1;
        private TabPage patchTab;
        private CheckBox altSkinsBox;
        private CheckBox userPatchBox;
        private ComboBox gameBox;
        private Label label3;
        private TabPage videoTab;
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
        private CheckBox ambienceBox;
        private CheckBox fadeBox;
        private CheckBox titleBox;
        private CheckBox randomBox;
        private ComboBox resBox;
        private Label label2;
        private TrackBar fogSlider;
        private CheckBox separateSaveBox;
        private CheckBox separateTracksBox;
        private TabPage aboutTab;
        private TabPage inputTab;
        private CheckBox vibrationBox;
        private CheckBox bigDropBox;
        private ComboBox swapBox;
        private CheckBox xinputBox;
        private CheckBox drawshadowBox;
        private CheckBox psxtexBox;
        private CheckBox drawhudBox;
        private LinkLabel linkLabel3;
        private LinkLabel linkLabel2;
        private LinkLabel linkLabel1;
        private Label label5;
        private CheckBox rendererBox;
    }
}

