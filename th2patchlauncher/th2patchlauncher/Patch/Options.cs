using System;
using System.Linq;
using System.Text;
using System.IO;
using System.Windows.Forms;
using IniParser;
using IniParser.Model;
using IniParser.Model.Configuration;
using IniParser.Parser;
using System.Globalization;

namespace th2patchlauncher
{
    public class Options
    {
        string configfilename;
        IniParserConfiguration cfg;
        IniData config;

        public string GetString(string section, string name, string defaultValue)
        {
            var result = config[section][name];
            return result == null ? defaultValue : result;
        }

        public int GetInt(string section, string name, int defaultValue)
        {
            var result = config[section][name];
            return result == null ? defaultValue : Int32.Parse(result);
        }

        public bool GetBool(string section, string name, bool defaultValue)
        {
            var result = config[section][name];
            return result == null ? defaultValue : result == "1" ? true : false;
        }

        public float GetFloat(string section, string name, float defaultValue)
        {
            var result = config[section][name];
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
        public int ZoomMin = 30;
        public int ZoomMax = 140;
        public bool Force32BPP = true;
        public bool UnlockFPS = true;
        public string Game = "THPS2";
        public string ExeName = "Thawk2";
        public bool UserPatch = false;
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

        public bool BigDropEnabled = true;
        public bool Vibration = true;
        public bool XInputEnabled = true;

        public void ChangeZoom(int x)
        {
            if (x < ZoomMin) return;
            if (x > ZoomMax) return;
            ZoomFactor = x;
        }

        public Options(string filename)
        {
            configfilename = filename;

            if (!File.Exists(configfilename))
                File.Create(configfilename).Close();

            cfg = new IniParserConfiguration();
            cfg.AllowKeysWithoutSection = false;
            cfg.CaseInsensitive = true;
            cfg.SkipInvalidLines = true;
            cfg.CommentString = ";";
            cfg.AllowDuplicateKeys = false;
            cfg.AssigmentSpacer = "";

            var parser = new IniDataParser(cfg);
            config = parser.Parse(File.ReadAllText(configfilename));

            ResX = Int32.Parse(config["VIDEO"]["ResX"]);
            ResY = Int32.Parse(config["Video"]["ResY"]);
            FogScale = Int32.Parse(config["Video"]["FogScale"]);

            if (ResX == 0 || ResY == 0)
            {
                ResX = 1280;
                ResY = 720;
            }

            if (FogScale < 10) FogScale = 10;
            if (FogScale > 750) FogScale = 750;

            SkipIntro = Convert.ToBoolean(Int32.Parse(config["Patch"]["SkipIntro"]));
            Force32BPP = Convert.ToBoolean(Int32.Parse(config["Video"]["Force32bpp"]));
            UnlockFPS = Convert.ToBoolean(Int32.Parse(config["Video"]["UnlockFPS"]));
            AltSkins = Convert.ToBoolean(Int32.Parse(config["Patch"]["MoreSkins"]));
            DickSwap = config["Patch"]["DickSwap"];
            Game = config["Patch"]["Game"];
            SeparateSave = Convert.ToBoolean(Int32.Parse(config["Patch"]["SeparateSaves"]));
            UserPatch = GetBool("Patch", "UserPatch", false);

            MusicAmbience = Convert.ToBoolean(Int32.Parse(config["Music"]["PlayAmbience"]));
            MusicFade = Convert.ToBoolean(Int32.Parse(config["Music"]["Fade"]));
            MusicTitle = Convert.ToBoolean(Int32.Parse(config["Music"]["ShowTitle"]));
            MusicRandom = Convert.ToBoolean(Int32.Parse(config["Music"]["Random"]));
            SeparateTracks = Convert.ToBoolean(Int32.Parse(config["Music"]["SeparateTracks"]));

            BigDropEnabled = Convert.ToBoolean(Int32.Parse(config["Input"]["BigDrop"]));
            XInputEnabled = Convert.ToBoolean(Int32.Parse(config["Input"]["XInput"]));
            Vibration = Convert.ToBoolean(Int32.Parse(config["Input"]["Vibration"]));

            CultureInfo ci = (CultureInfo)CultureInfo.CurrentCulture.Clone();
            ci.NumberFormat.NumberDecimalSeparator = ".";
            CultureInfo.CurrentCulture = ci;

            ZoomFactor = (int)(Single.Parse(config["Video"]["FOV"]) * 100);

            DrawShadow = Convert.ToBoolean(Int32.Parse(config["Video"]["DrawShadow"]));
            ShowHUD = Convert.ToBoolean(Int32.Parse(config["Video"]["ShowHUD"]));
            DisableNewTex = Convert.ToBoolean(Int32.Parse(config["Video"]["DisableNewTex"]));

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
            ChangeZoom((int)(ourzoom + (100.0f - ourzoom) / 2.0f));
        }

        public float GetZoom() => ZoomFactor / 100.0f;

        public void Save()
        {
            var parser = new FileIniDataParser();
            parser.WriteFile(configfilename, config, new UTF8Encoding(false));
        }

        public bool ParseResText(string x)
        {
            string str = x.ToLower().Trim().Replace(" ", "");

            if (str.Contains("x"))
            {
                string[] buf = str.Split('x');

                if (buf.Count() == 2)
                {
                    try
                    {
                        ResX = Int32.Parse(buf[0]);
                        ResY = Int32.Parse(buf[1]);

                        SetInt("Video", "ResX", ResX);
                        SetInt("Video", "ResY", ResY);

                        return true;
                    }
                    catch
                    {
                        ResX = 640;
                        ResY = 480;

                        SetInt("Video", "ResX", ResX);
                        SetInt("Video", "ResY", ResY);

                        return true;
                    }
                }
            }

            return false;
        }

        public string GetResText()
        {
            return ResX + "x" + ResY;
        }

        public void DetectResolution()
        {
            ResX = Screen.PrimaryScreen.Bounds.Width;
            ResY = Screen.PrimaryScreen.Bounds.Height;
        }
    }
}