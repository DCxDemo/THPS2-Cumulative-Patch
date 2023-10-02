using System;
using System.Collections.Generic;
using System.IO;
using System.Windows.Forms;

namespace thps2patch
{
    class LevelPatch
    {
        public string currentgame = "THPS2";

        struct Level
        {
            public string game;
            public int offset;
            public string trig;

            public Level(string g, int o, string t)
            {
                game = g;
                offset = o;
                trig = t;
            }

            public void ModifyOffset(int x)
            {
                offset += x;
            }


            public void ApplyPatch(Mem m)
            {
                string fn = "";

                if (trig.Contains("(file)"))
                {
                    try
                    {
                        fn = ".\\patch\\" + trig.Replace("(file)", "");
                        // System.Windows.Forms.MessageBox.Show(fn);

                        if (File.Exists(fn)) m.WriteFile(offset, fn);
                        return;
                    }
                    catch
                    {
                        File.AppendAllText("patch.log", "Warning: file " + fn + " is missing.\r\n");
                        return;
                    }
                }

                if (trig.Contains("(int32)"))
                {
                    int x = 0;
                    fn = trig.Replace("(int32)", "");

                    if (Int32.TryParse(fn, out x))
                    {
                        m.WriteInt(offset, x);
                    }
                    else
                    {
                        File.AppendAllText("patch.log", "Can't write value " + fn + " at " + offset.ToString("X8") + " - failed to parse int32.\r\n");
                    }
                    return;
                }


                if (trig.Contains("(int16)"))
                {
                    short x = 0;
                    fn = trig.Replace("(int16)", "");

                    if (Int16.TryParse(fn, out x))
                    {
                        m.WriteShort(offset, x);
                    }
                    else
                    {
                        File.AppendAllText("patch.log", "Can't write value " + fn + " at " + offset.ToString("X8") + " - failed to parse int16.\r\n");
                    }
                    return;
                }

                if (trig.Contains("(byte)"))
                {
                    byte x = 0;
                    fn = trig.Replace("(byte)", "");

                    if (Byte.TryParse(fn, out x))
                    {
                        m.WriteByte(offset, x);
                    }
                    else
                    {
                        File.AppendAllText("patch.log", "Can't write value " + fn + " at " + offset.ToString("X8") + " - failed to parse byte.\r\n");
                    }
                    return;
                }


                if (trig.Contains("(float)"))
                {

                    float x = 0;
                    fn = trig.Replace("(float)", "");

                    System.Globalization.NumberStyles style = System.Globalization.NumberStyles.AllowDecimalPoint;
                    System.Globalization.CultureInfo culture = System.Globalization.CultureInfo.CreateSpecificCulture("en-GB");

                    if (Single.TryParse(fn, style, culture, out x))
                    {
                        m.WriteFloat(offset, x);
                    }
                    else
                    {
                        File.AppendAllText("patch.log", "Can't write value " + fn + " at " + offset.ToString("X8") + " - failed to parse float.\r\n");
                    }
                    return;
                }

                m.WriteString(offset, trig);

            }
        }

        List<Level> levels = new List<Level>();

        public void ReadLevels(string f)
        {

            if (File.Exists(f))
            {
                string game = "[]";

                string[] buf = File.ReadAllLines(f);

                foreach (string s in buf)
                {
                    string p = TrimComment(s);

                    switch (p)
                    {
                        case "": break;
                        case "[THPS1]": game = "THPS1"; break;
                        case "[THPS2]": game = "THPS2"; break;
                        case "[THPS3]": game = "THPS3"; break;
                        case "[THPS4]": game = "THPS4"; break;
                        case "[MHPB]": game = "MHPB"; break;
                        case "[GLOBAL]": game = "GLOBAL"; break;
                        default: levels.Add(BakeLevel(p, game)); break;
                    }
                }
            }
            else
            {
                //File.AppendAllText("patch.log", "Warning: patch file " + f + " not found. Ignore this if you don't have LevelPack.");
            }
        }

        //removes everything after #
        private string TrimComment(string s)
        {
            int x = s.IndexOf('#');
            if (x < 0) x = s.Length;
            return s.Substring(0, x).Trim(' ');
        }

        private Level BakeLevel(string s, string game)
        {
            string[] buf = s.Split('=');

            int x = Convert.ToInt32(buf[0], 16);

            return new Level(game, x, buf[1].Replace(@"\*", "*").Replace('*', '\0'));
        }

        public LevelPatch(string f, string s)
        {
            currentgame = s;
            ReadLevels(f);
        }


        public void Patch(string pr)
        {
            try
            {
                Mem mem = new Mem(pr);

                foreach (Level l in levels)
                    if (currentgame == l.game)
                        l.ApplyPatch(mem);

                foreach (Level l in levels)
                    if (l.game == "GLOBAL")
                        l.ApplyPatch(mem);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        //huh?
        public void ModifyKorean()
        {
            for (int i = 0; i < levels.Count; i++)
                levels[i].ModifyOffset(0x3AC8);
        }

    }
}
