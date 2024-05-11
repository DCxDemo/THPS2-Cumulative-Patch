using IniParser;
using IniParser.Model;
using IniParser.Model.Configuration;
using IniParser.Parser;
using System;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing;

namespace thps2patch
{
    public partial class Options
    {
        public static readonly Size DefaultResolution = new Size(1280, 720);

        string configfilename;
        IniParserConfiguration cfg;
        IniData config;

        #region [ini helper methods]

        private string TryGetValue(string section, string name, string defaultValue)
        {
            var result = config[section][name];
            if (result == null)
            {
                config[section][name] = defaultValue;
                result = defaultValue;
            }
            return result;
        }

        public string GetString(string section, string name, string defaultValue)
        {
            var result = TryGetValue(section, name, defaultValue);
            return result == null ? defaultValue : result;
        }

        public int GetInt(string section, string name, int defaultValue)
        {
            var result = TryGetValue(section, name, defaultValue.ToString());
            return result == null ? defaultValue : Int32.Parse(result);
        }

        public bool GetBool(string section, string name, bool defaultValue)
        {
            var result = TryGetValue(section, name, defaultValue ? "1" : "0");
            return result == null ? defaultValue : result == "1" ? true : false;
        }

        public float GetFloat(string section, string name, float defaultValue)
        {
            var result = TryGetValue(section, name, defaultValue.ToString("0.##"));
            return result == null ? defaultValue : Single.Parse(result);
        }

        public void SetBool(string section, string name, bool value)
        {
            config[section][name] = value ? "1" : "0";
        }

        public void SetInt(string section, string name, int value)
        {
            config[section][name] = value.ToString();
        }

        public void SetFloat(string section, string name, float value)
        {
            config[section][name] = value.ToString();
        }

        public void SetString(string section, string name, string value)
        {
            config[section][name] = value;
        }

        #endregion

        public int ResX = 1280;
        public int ResY = 720;

        public float FovScale
        {
            get { return userFovScale; }
            set {
                userFovScale = Helpers.MathClamp(value, 0.5f, 1.5f);
                SetFloat("Video", "FovScale", userFovScale);
            }
        }

        private float userFovScale = 1f;


        public int fog = 300;

        public bool UserPatch = false;
        public string Game = "THPS2";
        public string ExeName = "Thawk2";




        public Options(string filename)
        {
            configfilename = filename;

            if (!File.Exists(configfilename))
                File.Create(configfilename).Close();

            cfg = new IniParserConfiguration()
            {
                AllowKeysWithoutSection = false,
                CaseInsensitive = true,
                SkipInvalidLines = true,
                CommentString = ";",
                AllowDuplicateKeys = false,
                AssigmentSpacer = "",
                AllowCreateSectionsOnFly = true,
                ThrowExceptionsOnError = false
            };

            var parser = new IniDataParser(cfg);
            config = parser.Parse(File.ReadAllText(configfilename));
        }

        public void Save()
        {
            var parser = new FileIniDataParser();

            //https://stackoverflow.com/questions/5266069/streamwriter-and-utf-8-byte-order-marks
            parser.WriteFile(configfilename, config, new UTF8Encoding(false));
        }

        public Size ParseResText(string resolutionString)
        {
            string str = resolutionString.Trim().Replace(" ", "").ToLower();

            if (str.Contains("x"))
            {
                string[] buf = str.Split('x');

                if (buf.Count() == 2)
                {
                    try
                    {
                        return new Size(Int32.Parse(buf[0]), Int32.Parse(buf[1]));
                    }
                    catch
                    {
                        MessageBox.Show("Please use (X)x(Y) format, example: 1920x1080");
                    }
                }
            }

            return Size.Empty;
        }

        public void SetResolution(int X = 0, int Y = 0)
        {
            if (X > 0 && Y > 0)
            {
                ResX = Helpers.MathClamp(X, 0, 2048);
                ResY = Helpers.MathClamp(Y, 0, 2048);
            }
            else
            {
                ResX = Screen.PrimaryScreen.Bounds.Width;
                ResY = Screen.PrimaryScreen.Bounds.Height;
            }

            SetInt("Video", "ResX", ResX);
            SetInt("Video", "ResY", ResY);

            OnResolutionChanged?.Invoke();
        }

        public delegate void ResolutionChangeHandler();
        public ResolutionChangeHandler OnResolutionChanged;

        public string ResolutionString => $"{ResX}x{ResY}";

        public void applyResolutionListByAspectRatio(ComboBox resbox, string aspectRatio)
        {
            if (resbox.Items.Count > 0) resbox.Items.Clear();

            foreach (var res in _resolutions)
            {
                if (res.Value == aspectRatio)
                {
                    resbox.Items.Add(res.Key);
                }
            }
        }

        //updates resbox and aspect ratio box text accordingly by resolution
        public void setResAspectText(ComboBox resBox, ComboBox aspectRatioBox, string resolutionString)
        {
            aspectRatioBox.SelectedItem = getAspectRatioOfResolution(resolutionString);
            resBox.Text = ResolutionString;
        }

        public string getAspectRatioOfResolution(string resolutionString)
        {
            foreach (var res in _resolutions)
            {
                if (res.Key == resolutionString)
                    return res.Value;
            }

            return "";
        }
    }
}