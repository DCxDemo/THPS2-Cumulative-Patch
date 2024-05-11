using System;
using System.IO;

namespace thps2patch
{
    public class Helpers
    {
        /// <summary>
        /// Simply checks whether file is accessible.
        /// </summary>
        /// <param name="filename"></param>
        /// <returns></returns>
        public static bool FileLocked(string filename)
        {
            try
            {
                var file = new FileInfo(filename);
                var stream = file.Open(FileMode.Open, FileAccess.Read, FileShare.Read);
                stream.Close();

                return false;
            }
            catch
            {
                return true;
            }
        }

        //used to validate smaller THawk2.exe. Come up with something smarter but fast enough.
        public static bool isSmallerExe(string path)
        {
            bool result = false;

            using (var br = new BinaryReader(File.OpenRead(path)))
            {
                if (br.BaseStream.Length >= 0x1642EC + 4)
                {
                    br.BaseStream.Position = 0x1642EC;

                    if (br.ReadUInt32() == 0xF92BD1F7)
                        result = true;
                }
            }

            return result;
        }

        /// <summary>
        /// A simple Math.Clamp implementation for ints.
        /// </summary>
        /// <param name="value"></param>
        /// <param name="min"></param>
        /// <param name="max"></param>
        /// <returns></returns>
        public static int MathClamp(int value, int min, int max)
        {
            if (max < min) throw new Exception("MAX is less than MIN. please fix.");

            if (value < min) { return min; }
            if (value > max) { return max; }

            return value;
        }

        /// <summary>
        /// A simple Math.Clamp implementation for floats.
        /// </summary>
        /// <param name="value"></param>
        /// <param name="min"></param>
        /// <param name="max"></param>
        /// <returns></returns>
        public static float MathClamp(float value, float min, float max)
        {
            if (max < min) throw new Exception("MAX is less than MIN. please fix.");

            if (value < min) { return min; }
            if (value > max) { return max; }

            return value;
        }
    }
}