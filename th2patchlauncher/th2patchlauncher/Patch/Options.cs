using IniParser;
using IniParser.Model;
using IniParser.Model.Configuration;
using IniParser.Parser;
using System;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace thps2patch
{
    public class Options
    {
        string configfilename;
        IniParserConfiguration cfg;
        IniData config;

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
            var result = TryGetValue(section, name, defaultValue.ToString());
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

        public int ResX = 1280;
        public int ResY = 720;

        public bool OverrideFOV = false;
        public int ZoomFactor = 100;

        public bool UserPatch = false;
        public string Game = "THPS2";
        public string ExeName = "Thawk2";

        /*
        public bool Force32BPP = true;
        public bool UnlockFPS = true;
 


        public bool AltSkins = false;
        public bool SkipIntro = true;
        public int FogScale = 750;

        public bool ShowHUD = true;
        public bool DrawShadow = true;
        public bool DisableNewTex = true;

        public bool SeparateSave = false;
        public bool SeparateTracks = false;

        public bool MusicFade = true;
        public bool MusicRandom = false;
        public bool MusicTitle = false;
        public bool MusicAmbience = true;
        public string DickSwap = "";

        public bool ManualsEnabled = true;
        public bool BigDropEnabled = true;
        public bool Vibration = true;
        public bool XInputEnabled = true;
        */

        public int ValidateRange(int value, int min, int max)
        {
            if (value < min) { return min; }
            if (value > max) { return max; }
            return value;
        }

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

            /*
            //what a mess

            foreach (string s in buf)
            {
                if (s.Contains('='))
                {
                    string[] bb = s.Split('=');

                    switch (bb[0])
                    {
                        case "ZoomFactor":
                            if (bb[1] == "auto")
                            {
                                AutoFOV();
                            }
                            else
                            {
                                try
                                {
                                    OverrideFOV = true;
                                    ZoomFactor = Int32.Parse(bb[1]);
                                }
                                catch { }
                            } break;

                        case "UserPatch": try { UserPatch = Boolean.Parse(bb[1]); }
                            catch { } break;
                    }
                }
            }
            */
        }

        public void AutoFOV()
        {
            OverrideFOV = false;
            int ourzoom = (int)((4.0f * ResY) / (3.0f * ResX) * 100.0f);
            ZoomFactor = ValidateRange((int)(ourzoom + (100.0f - ourzoom) / 2.0f), 30, 140);
        }

        public float GetZoom() => ZoomFactor / 100.0f;

        public void Save()
        {
            var parser = new FileIniDataParser();

            //https://stackoverflow.com/questions/5266069/streamwriter-and-utf-8-byte-order-marks
            parser.WriteFile(configfilename, config, new UTF8Encoding(false));
        }

        public void ParseResText(string x)
        {
            string str = x.Trim().Replace(" ", "").ToLower();

            if (str.Contains("x"))
            {
                string[] buf = str.Split('x');

                if (buf.Count() == 2)
                {
                    try
                    {
                        ResX = Int32.Parse(buf[0]);
                        ResY = Int32.Parse(buf[1]);

                        SetResolution(ResX, ResY);

                        return;
                    }
                    catch
                    {
                        MessageBox.Show("Please use (X)x(Y) format, example: 1920x1080");
                    }
                }
            }

            SetResolution(1280, 720);
        }

        public void SetResolution(int X, int Y)
        {
            ResX = X;
            ResY = Y;

            SetInt("Video", "ResX", ResX);
            SetInt("Video", "ResY", ResY);

            OnResolutionChanged?.Invoke();
        }

        public delegate void ResolutionChangeHandler();
        public ResolutionChangeHandler OnResolutionChanged;

        public string ResolutionString => $"{ResX}x{ResY}";

        public void DetectResolution()
        {
            ResX = Screen.PrimaryScreen.Bounds.Width;
            ResY = Screen.PrimaryScreen.Bounds.Height;

            SetResolution(ResX, ResY);
        }
    }
}